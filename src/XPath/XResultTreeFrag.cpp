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
// Class header file.
#include "XResultTreeFrag.hpp"



#include <dom/DOM_Node.hpp>
#include <dom/DOM_NodeList.hpp>
#include <dom/DOM_Text.hpp>



#include <PlatformSupport/DOMStringHelper.hpp>



#include "NodeRefListBase.hpp"
#include "ResultTreeFragBase.hpp"
#include "XObjectTypeCallback.hpp"
#include "XPathSupport.hpp"



XResultTreeFrag::XResultTreeFrag(
			XPathEnvSupport&			envSupport,
			XPathSupport&				support,
			const ResultTreeFragBase&	val,
			bool						deepClone) :
	XObject(&envSupport),
	m_support(support),
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	m_value(dynamic_cast<ResultTreeFragBase*>(val.clone(deepClone)))
#else
	m_value(val.clone(deepClone))
#endif
{
}



XResultTreeFrag::XResultTreeFrag(
			const XResultTreeFrag&	source,
			bool					deepClone) :
	XObject(source),
	m_support(source.m_support),
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	m_value(dynamic_cast<ResultTreeFragBase*>(source.m_value->clone(deepClone)))
#else
	m_value(source.m_value->clone(deepClone))
#endif
{
}



XResultTreeFrag::~XResultTreeFrag()
{
}



XResultTreeFrag::eObjectType
XResultTreeFrag::getType() const
{
	return eTypeResultTreeFrag;
}



DOMString
XResultTreeFrag::getTypeString() const
{
	return "#RESULT_TREE_FRAG";
}



double
XResultTreeFrag::num() const
{
	const DOMString		theValue = m_support.getNodeData(DOM_ResultTreeFragBase(m_value.get()));

	return DOMStringToDouble(theValue);
}



bool
XResultTreeFrag::boolean() const
{
    bool					fResult = false;

    const NodeRefListBase&	nl = m_value->getChildNodesAsNodeRefList();

    const int		nChildren = nl.getLength();

    for(int i = 0; i < nChildren; i++)
    {
		const DOM_Node	n = nl.item(i);

		if(DOM_Node::TEXT_NODE == n.getNodeType())
		{
			const DOM_Text&		theTextNode =
				static_cast<const DOM_Text&>(n);

			if (m_support.isIgnorableWhitespace(theTextNode) ||
			    length(trim(theTextNode.getData())) == 0)
			{
				continue;
			}
      
			fResult = true;
			break;
		}
	}

    return fResult;
}



DOMString
XResultTreeFrag::str() const
{
	return m_support.getNodeData(DOM_ResultTreeFragBase(m_value.get()));
}



const ResultTreeFragBase&
XResultTreeFrag::rtree() const
{
	return *m_value.get();
}



ResultTreeFragBase&
XResultTreeFrag::rtree()
{
	return *m_value.get();
}



const NodeRefListBase&
XResultTreeFrag::nodeset() const
{
	return m_value->getChildNodesAsNodeRefList();
}



const MutableNodeRefList&
XResultTreeFrag::mutableNodeset() const
{
	error("Can't cast XResultTreeFrag to MutableNodeRefList");

	// error will throw, so this is just a dummy
	// value to satisfy the compiler.
	return *static_cast<MutableNodeRefList*>(0);
}



MutableNodeRefList&
XResultTreeFrag::mutableNodeset()
{
	error("Can't cast XResultTreeFrag to MutableNodeRefList");

	// error will throw, so this is just a dummy
	// value to satisfy the compiler.
	return *static_cast<MutableNodeRefList*>(0);
}



void
XResultTreeFrag::ProcessXObjectTypeCallback(XObjectTypeCallback&	theCallbackObject)
{
	theCallbackObject.ResultTreeFragment(*this,
										 rtree());
}



void
XResultTreeFrag::ProcessXObjectTypeCallback(XObjectTypeCallback&	theCallbackObject) const
{
	theCallbackObject.ResultTreeFragment(*this,
										 rtree());
}



bool
XResultTreeFrag::equals(const XObject&	theRHS) const
{
	return ::equals(str(), theRHS.str());
}
