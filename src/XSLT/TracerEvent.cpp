/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
#include "TracerEvent.hpp"

#include <dom/DOMString.hpp>
#include <dom/DOM_Node.hpp>
#include <dom/DOM_Element.hpp>
#include <dom/DOM_NodeList.hpp>

#include <PlatformSupport/DOMStringHelper.hpp>


/**
 * This is the parent class of events generated for tracing the
 * progress of the XSL processor.
 */
  /**
   * Create an event originating at the given node of the style tree.
   * @param processor The XSLT Processor.
   * @param sourceTree The input source tree.
   * @param sourceNode The current context node.
   * @param mode The current mode.
   * @param m_styleNode node in the style tree reference for the event.
   * Should not be null.  That is not enforced.
   */
TracerEvent::TracerEvent(
	const XSLTEngineImpl* processor, 
	const DOM_Node& sourceTree, 
	const DOM_Node& sourceNode,
	const QName& mode, 
	const ElemTemplateElement& styleNode): m_pProcessor(processor), m_sourceTree(sourceTree),
		m_sourceNode(sourceNode), m_mode(mode), m_styleNode(styleNode)

  {
  }

  /**
   Returns a string representation of the node.
   The string returned for elements will contain the element name
   and any attributes enclosed in angle brackets.
   The string returned for attributes will be of form, "name=value."

   @param n any DOM node. Must not be null.

   @return a string representation of the given node.
   */
DOMString TracerEvent::printNode(const DOM_Node& n)
{
	// in Java was thigs: String r = n.hashCode() + " ";

	DOMString r = LongToDOMString(reinterpret_cast<long>(&n)) + " ";
	
	if (n.getNodeType() == DOM_Node::ELEMENT_NODE)
	{
		r += "<" + n.getNodeName();

		DOM_Node c = n.getFirstChild();

		while (c != 0)
		{
			if (c.getNodeType() == DOM_Node::ATTRIBUTE_NODE)
			{
				r += printNode(c) + " ";
			}
			c = c.getNextSibling();
		}

		r += ">";
	}
	else
	{
		if (n.getNodeType() == DOM_Node::ATTRIBUTE_NODE)
		{
			r += n.getNodeName() + "=" + n.getNodeValue();
		}
		else
		{
			r += n.getNodeName();
		}
	}
	
	return r;
}

  /**
   Returns a string representation of the node list.
   The string will contain the list of nodes inside square braces.
   Elements will contain the element name
   and any attributes enclosed in angle brackets.
   Attributes will be of form, "name=value."

   @param l any DOM node list. Must not be null.

   @return a string representation of the given node list.
   */
DOMString TracerEvent::printNodeList(const DOM_NodeList& l)
{
	// in Java was this: String r = l.hashCode() + "[";
	DOMString r = LongToDOMString(reinterpret_cast<long>(&l)) + "[";

	int len = l.getLength() - 1;
	int i = 0;

	while (i < len)
	{
		DOM_Node n = l.item(i);
		if (n != 0)
		{
			r += printNode(n) + ", ";
		}
		++i;
	}
	if (i == len)
	{
		DOM_Node n = l.item(len);
		if (n != 0)
		{
			r += printNode(n);
		}
	}
	return r + "]";
}

