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
#include "DOMServices.hpp"



#include <vector>



#include <XalanDOM/XalanAttr.hpp>
#include <XalanDOM/XalanCDATASection.hpp>
#include <XalanDOM/XalanComment.hpp>
#include <XalanDOM/XalanDOMString.hpp>
#include <XalanDOM/XalanDocument.hpp>
#include <XalanDOM/XalanDocumentFragment.hpp>
#include <XalanDOM/XalanElement.hpp>
#include <XalanDOM/XalanNamedNodeMap.hpp>
#include <XalanDOM/XalanNodeList.hpp>
#include <XalanDOM/XalanProcessingInstruction.hpp>
#include <XalanDOM/XalanText.hpp>



#include <PlatformSupport/DOMStringHelper.hpp>
#include <PlatformSupport/XalanUnicode.hpp>



#include "DOMSupportException.hpp"



// These XalanDOMString instances will hold the actual
// data.  This way, the DOMSupport references can be const,
// but we can initialize the data when we want to.
static XalanDOMString	s_XMLString;
static XalanDOMString	s_XMLStringWithSeparator;
static XalanDOMString	s_XMLNamespaceURI;
static XalanDOMString	s_XMLNamespace;
static XalanDOMString	s_XMLNamespaceWithSeparator;
static XalanDOMString	s_XMLNamespaceSeparatorString;



const XalanDOMString&	DOMServices::s_XMLString = ::s_XMLString;
const XalanDOMString&	DOMServices::s_XMLStringWithSeparator = ::s_XMLStringWithSeparator;
const XalanDOMString&	DOMServices::s_XMLNamespaceURI = ::s_XMLNamespaceURI;
const XalanDOMString&	DOMServices::s_XMLNamespace = ::s_XMLNamespace;
const XalanDOMString&	DOMServices::s_XMLNamespaceWithSeparator = ::s_XMLNamespaceWithSeparator;
const XalanDOMString&	DOMServices::s_XMLNamespaceSeparatorString  = ::s_XMLNamespaceSeparatorString;
const XalanDOMString	DOMServices::s_emptyString;



// These four unsigned ints will hold the actual
// data.  This way, the DOMSupport references can be const,
// but we can initialize the data when we want to.
static unsigned int		s_XMLStringLength = 0;
static unsigned int		s_XMLStringWithSeparatorLength = 0;
static unsigned int		s_XMLNamespaceURILength = 0;
static unsigned int		s_XMLNamespaceLength = 0;
static unsigned int		s_XMLNamespaceWithSeparatorLength = 0;
static unsigned int		s_XMLNamespaceSeparatorStringLength = 0;



const unsigned int&		DOMServices::s_XMLStringLength = ::s_XMLStringLength;
const unsigned int&		DOMServices::s_XMLStringWithSeparatorLength = ::s_XMLStringWithSeparatorLength;
const unsigned int&		DOMServices::s_XMLNamespaceURILength = ::s_XMLNamespaceURILength;
const unsigned int&		DOMServices::s_XMLNamespaceLength = ::s_XMLNamespaceLength;
const unsigned int&		DOMServices::s_XMLNamespaceWithSeparatorLength = ::s_XMLNamespaceWithSeparatorLength;
const unsigned int&		DOMServices::s_XMLNamespaceSeparatorStringLength = ::s_XMLNamespaceSeparatorStringLength;



DOMServices::WhitespaceSupport::WhitespaceSupport()
{
}



DOMServices::WhitespaceSupport::~WhitespaceSupport()
{
}



DOMServices::WhitespaceSupportDefault::WhitespaceSupportDefault()
{
}



DOMServices::WhitespaceSupportDefault::~WhitespaceSupportDefault()
{
}



bool
DOMServices::WhitespaceSupportDefault::isIgnorableWhitespace(const XalanText&	node) const
{
	const XalanDOMString	theData(node.getData());

	const unsigned int	theLength = length(theData);

	unsigned int i = 0;

	for (; i < theLength; i++)
	{
		const XalanDOMChar	theChar = charAt(theData, i);

		if (!isXMLWhitespace(theChar))
		{
			break;
		}
	}

	return i == theLength ? true : false;
}



void
DOMServices::initialize()
{
	::s_XMLString = XALAN_STATIC_UCODE_STRING("xml");
	::s_XMLStringWithSeparator = XALAN_STATIC_UCODE_STRING("xml:");
	::s_XMLNamespaceURI = XALAN_STATIC_UCODE_STRING("http://www.w3.org/XML/1998/namespace");
	::s_XMLNamespace = XALAN_STATIC_UCODE_STRING("xmlns");
	::s_XMLNamespaceWithSeparator = XALAN_STATIC_UCODE_STRING("xmlns:");
	::s_XMLNamespaceSeparatorString = XALAN_STATIC_UCODE_STRING(":");

	::s_XMLStringLength = length(DOMServices::s_XMLString);
	::s_XMLStringWithSeparatorLength = length(DOMServices::s_XMLStringWithSeparator);
	::s_XMLNamespaceURILength = length(DOMServices::s_XMLNamespaceURI);
	::s_XMLNamespaceLength = length(DOMServices::s_XMLNamespace);
	::s_XMLNamespaceWithSeparatorLength = length(DOMServices::s_XMLNamespaceWithSeparator);
	::s_XMLNamespaceSeparatorStringLength = length(DOMServices::s_XMLNamespaceSeparatorString);
}



void
DOMServices::terminate()
{
	releaseMemory(::s_XMLString);
	releaseMemory(::s_XMLNamespaceURI);
	releaseMemory(::s_XMLNamespace);
	releaseMemory(::s_XMLNamespaceWithSeparator);

	::s_XMLStringLength = 0;
	::s_XMLNamespaceURILength = 0;
	::s_XMLNamespaceLength = 0;
	::s_XMLNamespaceWithSeparatorLength = 0;
}



XalanDOMString
DOMServices::getNodeData(const XalanNode&	node)
{
	XalanDOMString	data;

	getNodeData(node, data);

	return data;
}



void
DOMServices::getNodeData(
			const XalanNode&	node,
			XalanDOMString&		data)
{
	switch(node.getNodeType())
	{
	case XalanNode::DOCUMENT_FRAGMENT_NODE:
		{
			const XalanDocumentFragment&		theDocumentFragment =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanDocumentFragment&)node;
#else
				static_cast<const XalanDocumentFragment&>(node);
#endif
			getNodeData(theDocumentFragment, data);
		}
		break;

	case XalanNode::DOCUMENT_NODE:
		{
			const XalanDocument&	theDocument =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanDocument&)node;
#else
				static_cast<const XalanDocument&>(node);
#endif
			getNodeData(theDocument, data);
		}
		break;

	case XalanNode::ELEMENT_NODE:
		{
			const XalanElement&		theElement =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanElement&)node;
#else
				static_cast<const XalanElement&>(node);
#endif
			getNodeData(theElement, data);
		}
		break;

	case XalanNode::TEXT_NODE:
	case XalanNode::CDATA_SECTION_NODE:
		{
			const XalanText&	theTextNode =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanText&)node;
#else
				static_cast<const XalanText&>(node);
#endif

				getNodeData(theTextNode, data);
		}
		break;

	case XalanNode::ATTRIBUTE_NODE:
		{
			const XalanAttr&		theAttr =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanAttr&)node;
#else
				static_cast<const XalanAttr&>(node);
#endif
			getNodeData(theAttr, data);
		}
		break;

	case XalanNode::COMMENT_NODE:
		{
			const XalanComment&		theComment =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanComment&)node;
#else
				static_cast<const XalanComment&>(node);
#endif
			getNodeData(theComment, data);
		}
		break;

	case XalanNode::PROCESSING_INSTRUCTION_NODE:
		{
			const XalanProcessingInstruction&		thePI =
#if defined(XALAN_OLD_STYLE_CASTS)
				(const XalanProcessingInstruction&)node;
#else
				static_cast<const XalanProcessingInstruction&>(node);
#endif
			getNodeData(thePI, data);
		}
		break;

	default:
		// ignore
		break;
	}
}



XalanDOMString
DOMServices::getNodeData(const XalanDocument&	document)
{
	XalanDOMString	data;

	getNodeData(document, data);

	return data;
}



void
DOMServices::getNodeData(
			const XalanDocument&	document,
			XalanDOMString&			data)
{
	const XalanNode*	child = document.getFirstChild();

	while(child != 0)
	{
		const XalanNode::NodeType	theType = child->getNodeType();

		if (theType == XalanNode::ELEMENT_NODE ||
			theType == XalanNode::TEXT_NODE ||
			theType == XalanNode::CDATA_SECTION_NODE)
		{
			getNodeData(*child, data);
		}

		child = child->getNextSibling();
	}
}



XalanDOMString
DOMServices::getNodeData(const XalanDocumentFragment&	documentFragment)
{
	XalanDOMString	data;

	getNodeData(documentFragment, data);

	return data;
}



void
DOMServices::getNodeData(
			const XalanDocumentFragment&	documentFragment,
			XalanDOMString&					data)
{
	const XalanNodeList* const	nl = documentFragment.getChildNodes();
	assert(nl != 0);

	const unsigned int	n = nl->getLength();

	for(unsigned int i = 0; i < n; ++i)
	{
		const XalanNode* const		child = nl->item(i);
		assert(child != 0);

		const XalanNode::NodeType	theType = child->getNodeType();

		if (theType == XalanNode::ELEMENT_NODE ||
			theType == XalanNode::TEXT_NODE ||
			theType == XalanNode::CDATA_SECTION_NODE)
		{
			getNodeData(*child, data);
		}
	}
}



XalanDOMString
DOMServices::getNodeData(const XalanElement&	element)
{
	XalanDOMString	data;

	getNodeData(element, data);

	return data;
}



void
DOMServices::getNodeData(
			const XalanElement&		element,
			XalanDOMString&			data)
{
	const XalanNode*	child = element.getFirstChild();

	while(child != 0)
	{
		const XalanNode::NodeType	theType = child->getNodeType();

		if (theType == XalanNode::ELEMENT_NODE ||
			theType == XalanNode::TEXT_NODE ||
			theType == XalanNode::CDATA_SECTION_NODE)
		{
			getNodeData(*child, data);
		}

		child = child->getNextSibling();
	}
}



const XalanDOMString&
DOMServices::getNameOfNode(const XalanNode&		n)
{
	const XalanNode::NodeType	theNodeType =
				n.getNodeType();

	if (theNodeType == XalanNode::ATTRIBUTE_NODE)
	{
		const XalanDOMString&	theName = n.getNodeName();

		if (startsWith(theName, s_XMLNamespaceWithSeparator) == true)
		{
			// Special case for namespace nodes...
			return n.getLocalName();
		}
		else
		{
			return theName;
		}
	}
	else if (theNodeType == XalanNode::ELEMENT_NODE ||
			 theNodeType == XalanNode::PROCESSING_INSTRUCTION_NODE)
	{
		return n.getNodeName();
	}
	else
	{
		return s_emptyString;
	}
}



const XalanDOMString&
DOMServices::getNamespaceOfNode(const XalanNode&	n)
{
	if (n.getNodeType() == XalanNode::ATTRIBUTE_NODE)
	{
		const XalanDOMString&	theNodeName = n.getNodeName();

		// Special case for namespace nodes...
		if (startsWith(theNodeName, DOMServices::s_XMLNamespaceWithSeparator) == true ||
			equals(theNodeName, DOMServices::s_XMLNamespace) == true)
		{
			return s_emptyString;
		}
		else
		{
			return n.getNamespaceURI();
		}
	}
	else
	{
		return n.getNamespaceURI();
	}
}



// Note functional overlap with NamespaceResolver's 
// getNamespaceOfNode() method.  
//
// ***** Also: although this may not yet impact Xalan,
// as of DOM Level 2 it is possible for a hand-constructed DOM to 
// have namespaced nodes with no declaration in scope. In DOM2 it's 
// considered the responsibility of application code such as DOM 
// serializers to recognize these cases and synthesize appropriate 
// declarations when necessary. DOM3 is expected to add 
// some form of namespaceNormalize() operation to assist this task.
//
// DOM3 may also add a resolveNamespacePrefix() operation 
// which is aware of these issues and can generate reasonable 
// results even for a non-NS-normalized tree. The expected logic
// is that a Namespaced node with a prefix will constitute an
// implicit declaration of that prefix. 
//
// If we cut over to DOM2 and want to accept DOMs from sources other
// than the parser, we need to decide between demanding a 
// namespace-normalized DOM as input, doing a normalize pass
// (full treewalk, expensive), or recognizing implicit declarations.
const XalanDOMString&
DOMServices::getNamespaceForPrefix(
			const XalanDOMString&	prefix,
			const XalanElement&		namespaceContext)
{
	const XalanDOMString*	theNamespace = &s_emptyString;

	// Reserved xml: is hardcoded
	if(equals(prefix, s_XMLString) == true)
	{
		theNamespace = &s_XMLNamespaceURI;
	}
	else
	{
		XalanNode::NodeType		type;
		const XalanNode*		parent = &namespaceContext;
    
		// Consider elements until NS is resolved, or we run out of
		// ancestors, or we hit something other than an Element or 
		// EntityReference node (ie, Document or DocumentFragment)
		while (parent != 0 && length(*theNamespace) == 0
			&& ((type = parent->getNodeType()) == XalanNode::ELEMENT_NODE
				|| type == XalanNode::ENTITY_REFERENCE_NODE)) 
		{
			if (type == XalanNode::ELEMENT_NODE) 
			{
				// Scan the attributes for xmlns:* or xmlns:
				// (The latter is the prefix=="" case.)
				const XalanNamedNodeMap* const	nnm = parent->getAttributes();
				assert(nnm != 0);

				const unsigned int				theLength = nnm->getLength();

				for (unsigned int i = 0;  i < theLength;  i ++) 
				{
					const XalanNode* const	attr = nnm->item(i);
					assert(attr != 0);

					const XalanDOMString&		aname = attr->getNodeName();

					const unsigned int			len = length(aname);

					const bool isPrefix = len <= s_XMLNamespaceWithSeparatorLength ? false :
							equals(substring(aname,
											 0,
											 s_XMLNamespaceWithSeparatorLength),
								   s_XMLNamespaceWithSeparator);

					if (equals(aname, s_XMLNamespace) || isPrefix) 
					{
						// slightly inefficient for default decl.
						const unsigned int	index = indexOf(aname,
															XalanUnicode::charColon);

						const XalanDOMString	p = (isPrefix)
							? substring(aname,index + 1,len) 
							: XalanDOMString();

						if (equals(p, prefix) == true)
						{
							theNamespace = &attr->getNodeValue();

							break;
						}
					}
				}
			}

			parent = getParentOfNode(*parent);
		}
	}

	assert(theNamespace != 0);

	return *theNamespace;
}



bool
DOMServices::isNodeAfter(
			const XalanNode&	node1,
			const XalanNode&	node2)
{
	assert(node1.getOwnerDocument() == node2.getOwnerDocument());
	assert(node1.getNodeType() != XalanNode::DOCUMENT_NODE &&
			node2.getNodeType() != XalanNode::DOCUMENT_NODE);

	if (node1.isIndexed() == true)
	{
		assert(node2.isIndexed() == true);

		return node1.getIndex() > node2.getIndex() ? true : false;
	}
	else
	{
		bool	isNodeAfter = false;

		const XalanNode*	parent1 = getParentOfNode(node1);

		const XalanNode*	parent2 = getParentOfNode(node2);

		// Optimize for most common case
		if(parent1 == parent2) // then we know they are siblings
		{
			isNodeAfter = isNodeAfterSibling(*parent1,
											 node1,
											 node2);
		}
		else
		{
			// General strategy: Figure out the lengths of the two 
			// ancestor chains, and walk up them looking for the 
			// first common ancestor, at which point we can do a 
			// sibling compare.  Edge condition where one is the 
			// ancestor of the other.

			// Count parents, so we can see if one of the chains 
			// needs to be equalized.
			int nParents1 = 2;
			int nParents2 = 2; // count node & parent obtained above

			while(parent1 != 0)
			{
				nParents1++;
				parent1 = getParentOfNode(*parent1);
			}

			while(parent2 != 0)
			{
				nParents2++;
				parent2 = getParentOfNode(*parent2);
			}

			// adjustable starting points
			const XalanNode*	startNode1 = &node1;
			const XalanNode*	startNode2 = &node2;

			// Do I have to adjust the start point in one of 
			// the ancesor chains?
			if(nParents1 < nParents2)
			{
				// adjust startNode2
				const int	adjust = nParents2 - nParents1;

				for(int i = 0; i < adjust; i++)
				{
					startNode2 = getParentOfNode(*startNode2);
				}
			}
			else if(nParents1 > nParents2)
			{
				// adjust startNode1
				const int	adjust = nParents1 - nParents2;

				for(int i = 0; i < adjust; i++)
				{
					startNode1 = getParentOfNode(*startNode1);
				}
			}

			// so we can "back up"
			const XalanNode*	prevChild1 = 0;
			const XalanNode*	prevChild2 = 0;
			  
			// Loop up the ancestor chain looking for common parent.
			while(0 != startNode1)
			{
				if(startNode1 == startNode2) // common parent?
				{
					if(0 == prevChild1) // first time in loop?
					{
						// Edge condition: one is the ancestor of the other.
						isNodeAfter = (nParents1 < nParents2) ? true : false;

						break; // from while loop
					}
					else
					{
						isNodeAfter = isNodeAfterSibling(*startNode1,
														 *prevChild1,
														 *prevChild2);

						break; // from while loop
					}
				}

				prevChild1 = startNode1;
				assert(prevChild1 != 0);

				startNode1 = getParentOfNode(*startNode1);
				assert(startNode1 != 0);

				prevChild2 = startNode2;
				assert(prevChild2 != 0);

				startNode2 = getParentOfNode(*startNode2);
				assert(startNode2 != 0);
			}
		}

		return isNodeAfter;
	}
}



bool
DOMServices::isNodeAfterSibling(
			const XalanNode&	parent,
			const XalanNode&	child1,
			const XalanNode&	child2)
{
	bool	isNodeAfterSibling = false;

	const XalanNode::NodeType	child1type = child1.getNodeType();
	const XalanNode::NodeType	child2type = child2.getNodeType();

	if(XalanNode::ATTRIBUTE_NODE != child1type &&
	   XalanNode::ATTRIBUTE_NODE == child2type)
	{
		// always sort attributes before non-attributes.
		isNodeAfterSibling = false;
	}
	else if(XalanNode::ATTRIBUTE_NODE == child1type &&
			XalanNode::ATTRIBUTE_NODE != child2type)
	{
		// always sort attributes before non-attributes.
		isNodeAfterSibling = true;
	}
	else if(XalanNode::ATTRIBUTE_NODE == child1type)
	{
		const XalanNamedNodeMap*	children = parent.getAttributes();
	  
		const unsigned int	nNodes = children->getLength();

		bool				found1 = false;
		bool				found2 = false;

		for(unsigned int i = 0; i < nNodes; i++)
		{
			const XalanNode*	child = children->item(i);

			if(&child1 == child)
			{
				if(found2 == true)
				{
					isNodeAfterSibling = true;
					break;
				}
		  
				found1 = true;
			}
			else if(&child2 == child)
			{
				if(found1 == true)
				{
					isNodeAfterSibling = false;
					break;
				}
		  
				found2 = true;
			}
		}
	}
	else
	{
		const XalanNode*	child = parent.getFirstChild();

		bool			found1 = false;
		bool			found2 = false;

		while(child != 0)
		{
			if(&child1 == child)
			{
				if(found2 == true)
				{
					isNodeAfterSibling = true;
					break;
				}

				found1 = true;
			}
			else if(&child2 == child)
			{
				if(found1 == true)
				{
					isNodeAfterSibling = false;
					break;
				}

				found2 = true;
			}

			child = child->getNextSibling();
		}

		assert(found1 != found2);
	}

	return isNodeAfterSibling;
}



XalanNode*
DOMServices::findOwnerElement(
			const XalanNode&	attr,
			XalanNode&			element)
{

    XalanNode*	parent = 0;

	const XalanNamedNodeMap* const	attrs = element.getAttributes();

	if(attrs != 0)
	{
		const unsigned int	nAttrs = attrs->getLength();

		for(unsigned int i = 0; i < nAttrs; i++)
		{
			if(attrs->item(i) == &attr)
			{
				parent = &element;
					
				break;
			}
		}
	}

	if(parent == 0)
    {
		bool		fFound = false;

		XalanNode*	child = element.getFirstChild();

		while(child != 0 && fFound == false)
		{
			if(child->getNodeType() == XalanNode::ELEMENT_NODE)
			{
				parent = findOwnerElement(attr, *child);

				if(parent != 0)
				{
					fFound = true;
				}
			}

			if (fFound == false)
			{
				child = child->getNextSibling();
			}
		}
    }

	return parent;
}
