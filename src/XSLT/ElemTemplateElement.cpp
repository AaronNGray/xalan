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
#include "ElemTemplateElement.hpp"



#include <cassert>



#include <sax/AttributeList.hpp>
#include <sax/SAXException.hpp>


#include <PlatformSupport/AttributeListImpl.hpp>
#include <PlatformSupport/DOMStringPrintWriter.hpp>

#include <XMLSupport/FormatterToText.hpp>

#include <XPath/MutableNodeRefList.hpp>
#include <XPath/XPath.hpp>


#include "Constants.hpp"
#include "ElemForEach.hpp"
#include "ElemSort.hpp"
#include "ElemTemplate.hpp"
#include "NodeSortKey.hpp"
#include "NodeSorter.hpp"
#include "Stylesheet.hpp"
#include "StylesheetExecutionContext.hpp"
#include "StylesheetRoot.hpp"
#include "SelectionEvent.hpp"
#include "TracerEvent.hpp"


/** 
 * @param processor The XSLT Processor.
 * @param stylesheetTree The owning stylesheet.
 * @param name The name of the element.
 * @param atts The element attributes.
 * @param lineNumber The line in the XSLT file that the element occurs on.
 * @param columnNumber The column index in the XSLT file that the element occurs on.
 * @exception SAXException Never.
 */
ElemTemplateElement::ElemTemplateElement(
	StylesheetConstructionContext&	/* constructionContext */,
	Stylesheet& stylesheetTree, 
	const DOMString& name, 
	int lineNumber, 
	int columnNumber) :
		UnimplementedElement(&stylesheetTree),
		PrefixResolver(),
		m_stylesheet(stylesheetTree),
		m_lineNumber(lineNumber),
		m_columnNumber(columnNumber),
		m_defaultSpace(true),
		m_finishedConstruction(false),
		m_namespaces(m_stylesheet.getCurrentNamespace()),
		m_elemName(name),
		m_parentNode(0),
		m_nextSibling(0),
		m_firstChild(0)
{
}


ElemTemplateElement::~ElemTemplateElement()
{
}


NodeImpl* ElemTemplateElement::getParentNode() 
{
	return m_parentNode;
}


void ElemTemplateElement::setParentNode(NodeImpl* elem)
{
	assert(!elem || dynamic_cast<ElemTemplateElement *>(elem));
	m_parentNode = dynamic_cast<ElemTemplateElement *>(elem);
}


NodeImpl* ElemTemplateElement::getNextSibling() 
{
	return m_nextSibling;
}


void ElemTemplateElement::setNextSibling(NodeImpl* elem)
{
	assert(!elem || dynamic_cast<ElemTemplateElement *>(elem));
	m_nextSibling = dynamic_cast<ElemTemplateElement *>(elem);
}



ElemTemplateElement*
ElemTemplateElement::getFirstChild() const
{
	return m_firstChild;
}



ElemTemplateElement*
ElemTemplateElement::getNextSibling() const
{
	return m_nextSibling;
}



ElemTemplateElement*
ElemTemplateElement::getParentNode() const
{
	return m_parentNode;
}



DOMString
ElemTemplateElement::getTagName()
{
	return m_elemName;
}



DOMString
ElemTemplateElement::getNodeName()
{
	return m_elemName;
}



DOMString
ElemTemplateElement::getNamespaceForPrefix(const DOMString& prefix) const
{
    DOMString nameSpace;
    if(m_finishedConstruction == true)
    {
		 if(!isEmpty(prefix))
		 {
			 ElemTemplateElement*  elem = const_cast<ElemTemplateElement *>(this);
			 while(isEmpty(nameSpace) && elem != 0)
			 {
				 NamespaceVectorType nsVector = elem->getNameSpace();
				 nameSpace = QName::getNamespaceForPrefix(nsVector, prefix);
				 if (! isEmpty(nameSpace)) break;
				 assert(elem);
				 assert(dynamic_cast<ElemTemplateElement *>(elem->getParentNode()));
				 elem = dynamic_cast<ElemTemplateElement *>(elem->getParentNode());
			 }
		 }
		 else
		 {
			 nameSpace = getStylesheet().getNamespaceForPrefixFromStack(prefix);
		 }
    }
    else
    {
		nameSpace = getStylesheet().getNamespaceForPrefixFromStack(prefix);
    }
    if(isEmpty(nameSpace))
      error("Can not resolve namespace prefix: "+prefix);
    return nameSpace;
}



DOMString
ElemTemplateElement::getURI() const
{
	return getStylesheet().getBaseIdentifier();
}



/** 
 * See if this is a xmlns attribute, and, if so, process it.
 * 
 * @param attrName Qualified name of attribute.
 * @param atts The attribute list where the element comes from (not used at 
 *      this time).
 * @param which The index into the attribute list (not used at this time).
 * @return True if this is a namespace name.
 */
bool
ElemTemplateElement::isAttrOK(
			int						tok,
			const DOMString&		attrName,
			const AttributeList&	/* atts */,
			int						/* which */) const
{
    bool isXMLNS = (Constants::TATTRNAME_XMLNSDEF == tok) 
		|| startsWith(attrName,Constants::ATTRNAME_XMLNS);

    // TODO: Well, process it...

    return isXMLNS;  
}


/** 
 * See if this is a xmlns attribute, and, if so, process it.
 * 
 * @param attrName Qualified name of attribute.
 * @param atts The attribute list where the element comes from (not used at 
 *      this time).
 * @param which The index into the attribute list (not used at this time).
 * @return True if this is a namespace name.
 */
bool
ElemTemplateElement::isAttrOK(
			const DOMString&				attrName,
			const AttributeList&			atts,
			int								which,
			StylesheetConstructionContext&	constructionContext) const
{
    return m_stylesheet.isAttrOK(attrName, atts, which, constructionContext);
}

/** 
 * Tell whether or not this is a xml:space attribute and, if so, process it.
 * 
 * @param aname The name of the attribute in question.
 * @param atts The attribute list that owns the attribute.
 * @param which The index of the attribute into the attribute list.
 * @return True if this is a xml:space attribute.
 */
void ElemTemplateElement::processSpaceAttr(const AttributeList&	atts, int which)
{
	const DOMString spaceVal = atts.getValue(which);

	if(equals(spaceVal, "default") == true)
	{
		m_defaultSpace = true;
	}
	else if(equals(spaceVal, "preserve") == true)
	{
		m_defaultSpace = false;
	}
	else
	{
		error("xml:space has an illegal value: " + spaceVal);
	}
}



/** 
 * Tell whether or not this is a xml:space attribute and, if so, process it.
 * 
 * @param aname The name of the attribute in question.
 * @param atts The attribute list that owns the attribute.
 * @param which The index of the attribute into the attribute list.
 * @return True if this is a xml:space attribute.
 */
bool ElemTemplateElement::processSpaceAttr(const DOMString& aname, 
	const AttributeList& atts, int which)
{
    const bool	isSpaceAttr = equals(aname, "xml:space");

    if(isSpaceAttr == true)
    {
		const DOMString spaceVal = atts.getValue(which);

		if(equals(spaceVal, "default"))
		{
			m_defaultSpace = true;
		}
		else if(equals(spaceVal, "preserve") == true)
		{
			m_defaultSpace = false;
		}
		else
		{
			error("xml:space has an illegal value: " + spaceVal);
		}
    }

    return isSpaceAttr;
}



/** 
 * Validate that the string is an NCName.
 * 
 * @param s The name in question.
 * @return True if the string is a valid NCName according to XML rules.
 * @see http://www.w3.org/TR/REC-xml-names#NT-NCName
 */
bool ElemTemplateElement::isValidNCName(const DOMString& s)
{
    int len = length(s);
    XMLCh c = charAt(s,0);

    if(!(isLetterOrDigit(c) || (c == '_')))
      return false;

    if(len > 0)
    {
      for(int i = 1; i < len; i++)
      {
        c = charAt(s,i);   
        if(!(isLetterOrDigit(c) || (c == '_') || (c == '-') || (c == '.')))
          return false;
      }
    }

    return true;
}


/** Execute the element's primary function.  Subclasses of this
 * function may recursivly execute down the element tree.
 * 
 * @exception XSLProcessorException 
 * @exception java.net.MalformedURLException 
 * @exception java.io.FileNotFoundException 
 * @exception java.io.IOException 
 * @exception SAXException 
 * @param processor The XSLT Processor.
 * @param sourceTree The input source tree.
 * @param sourceNode The current context node.
 * @param mode The current mode.
 */
void ElemTemplateElement::execute(StylesheetExecutionContext& executionContext, const DOM_Node& sourceTree, 
	const DOM_Node& sourceNode, const QName& mode) const
{
	if(0 != getStylesheet().getStylesheetRoot().getTraceListeners())
    {
		getStylesheet().getStylesheetRoot().fireTraceEvent(
			TracerEvent(executionContext, sourceTree, sourceNode, mode, *this));
	}    
}


/** 
 * Process the children of a template.
 * 
 * @param processor The XSLT processor instance.
 * @param sourceTree The input source tree.
 * @param sourceNode The current context node.
 * @param mode The current mode.
 * @exception XSLProcessorException Thrown from one of the child execute 
 *     methods.
 * @exception java.net.MalformedURLException Might be thrown from the       
 *      document() function, or from xsl:include or xsl:import.
 * @exception java.io.FileNotFoundException Might be thrown from the        
 *      document() function, or from xsl:include or xsl:import.
 * @exception java.io.IOException Might be thrown from the document()       
 *      function, or from xsl:include or xsl:import.
 * @exception SAXException Might be thrown from the  document() function, or
 *      from xsl:include or xsl:import.
 */
void ElemTemplateElement::executeChildren(StylesheetExecutionContext& executionContext, 
	const DOM_Node& sourceTree, const DOM_Node& sourceNode, const QName& mode) const
{
    for (ElemTemplateElement* node = m_firstChild; node != 0; node = node->m_nextSibling) 
    {
      node->execute(executionContext, sourceTree, sourceNode, mode);
    }
}


/** 
 * Take the contents of a template element, process it, and
 * convert it to a string.
 * 
 * @exception XSLProcessorException Thrown from one of the child execute  
 *     methods.
 * @exception java.net.MalformedURLException Might be thrown from the       
 *      document() function, or from xsl:include or xsl:import.
 * @exception java.io.FileNotFoundException Might be thrown from the        
 *      document() function, or from xsl:include or xsl:import.
 * @exception java.io.IOException Might be thrown from the  document()      
 *      function, or from xsl:include or xsl:import.
 * @exception SAXException Might be thrown from the  document() function, or
 *      from xsl:include or xsl:import.
 * @param processor The XSLT processor instance.
 * @param sourceTree The primary source tree.
 * @param sourceNode The current source node context.
 * @param mode The current mode.
 * @return The stringized result of executing the elements children.
 */
DOMString ElemTemplateElement::childrenToString(StylesheetExecutionContext& executionContext, 
	const DOM_Node& sourceTree, const DOM_Node& sourceNode, const QName& mode) const
{ 
	FormatterListener* const	savedFListener = executionContext.getFormatterListener();

	DOMStringPrintWriter		thePrintWriter;

	FormatterToText				theFormatter(thePrintWriter);

	try
	{
		executionContext.setFormatterListener(&theFormatter);

		const DOMString	savedPendingName = executionContext.getPendingElementName();

		try
		{
			executionContext.setPendingElementName(DOMString());

			const AttributeListImpl		savedPendingAttributes(executionContext.getPendingAttributes());

			try
			{
				executionContext.setPendingAttributes(AttributeListImpl());

				executeChildren(executionContext, sourceTree, sourceNode, mode);
			}
			catch(...)
			{
				executionContext.setPendingAttributes(savedPendingAttributes);

				throw;
			}

			executionContext.setPendingAttributes(savedPendingAttributes);
		}
		catch(...)
		{
			executionContext.setPendingElementName(savedPendingName);

			throw;
		}

		executionContext.setPendingElementName(savedPendingName);
	}
	catch(...)
	{
		executionContext.setFormatterListener(savedFListener);

		throw;
	}

	executionContext.setFormatterListener(savedFListener);

	return thePrintWriter.getString();
}



/** 
 * Perform a query if needed, and call transformChild for each child.
 * 
 * @param stylesheetTree The owning stylesheet tree.
 * @param xslInstruction The stylesheet element context (deprecated -- I do 
 *      not think we need this).
 * @param template The owning template context.
 * @param sourceTree The input source tree.
 * @param sourceNodeContext The current source node context.
 * @param mode The current mode.
 * @param selectPattern The XPath with which to perform the selection.
 * @param xslToken The current XSLT instruction (deprecated -- I do not     
 *     think we want this).
 */
void
ElemTemplateElement::transformSelectedChildren(
			StylesheetExecutionContext&		executionContext,
			const Stylesheet&				stylesheetTree, 
			const ElemTemplateElement&		xslInstruction, // xsl:apply-templates or xsl:for-each
			const ElemTemplateElement*		theTemplate, // The template to copy to the result tree
			const DOM_Node&					/*sourceTree*/, 
			const DOM_Node&					sourceNodeContext, 
			const QName&					mode, 
			const XPath*					selectPattern, 
			int								xslToken) const
{
	// Sort the nodes according to the xsl:sort method
	int tok = xslInstruction.getXSLToken();
	
	std::vector<NodeSortKey> keys;

	if((Constants::ELEMNAME_APPLY_TEMPLATES == tok) ||
		(Constants::ELEMNAME_FOREACH == tok))
	{
		const ElemForEach* foreach = static_cast<const ElemForEach *>(&xslInstruction);
		int nChildren = foreach->getSortElems().size();
		
		// March backwards, performing a sort on each xsl:sort child.
		// Probably not the most efficient method.
		for(int i = 0; i < nChildren; i++)
		{
			ElemSort* sort = (foreach->getSortElems())[i];
			
			const DOMString langString = (!isEmpty(sort->getLangAVT())) ? 
				executionContext.evaluateAttrVal(sourceNodeContext, DOM_UnimplementedElement(sort), sort->getLangAVT()): DOMString();

			const DOMString dataTypeString = executionContext.evaluateAttrVal(sourceNodeContext, DOM_UnimplementedElement(sort), sort->getDataTypeAVT());

			bool treatAsNumbers = ((!isEmpty(dataTypeString)) && equals(dataTypeString,Constants::ATTRVAL_DATATYPE_NUMBER)) ? 
				true : false;

			const DOMString	orderString = executionContext.evaluateAttrVal(sourceNodeContext, DOM_UnimplementedElement(sort), sort->getOrderAVT());

			bool descending = ((!isEmpty(orderString)) &&  equals(orderString,Constants::ATTRVAL_ORDER_DESCENDING))? 
				true : false;

			assert(sort->getSelectPattern() != 0);

			NodeSortKey key(executionContext, 
				*sort->getSelectPattern(), 
				treatAsNumbers, 
				descending, 
				langString, 
				xslInstruction);

			keys.push_back(key);
		}
	}

	MutableNodeRefList sourceNodes;

	if (0 != selectPattern)
	{
		XObject* const	result = selectPattern->execute(
			sourceNodeContext,
			xslInstruction,
			executionContext.getXPathExecutionContext());

		sourceNodes = result->mutableNodeset();
	
		if(0 != getStylesheet().getStylesheetRoot().getTraceListeners())
		{
			getStylesheet().getStylesheetRoot().fireSelectedEvent(
				SelectionEvent(executionContext, 
					sourceNodeContext,
					*this,
					"select",
					*selectPattern,
					result));
		}
	}
	else if (keys.size() > 0)
	{
		sourceNodes = sourceNodeContext.getChildNodes();
	}

	const int	nNodes = sourceNodes.getLength();

	if(nNodes > 0)
	{
		if (keys.size() > 0)
		{
			NodeSorter sorter(executionContext.getXPathExecutionContext());

			sorter.sort(sourceNodes, keys);
		}

		const MutableNodeRefList	savedContextNodeList(executionContext.getContextNodeList());

		executionContext.setContextNodeList(sourceNodes);

		try
		{
			if(executionContext.isTraceSelect())
				executionContext.traceSelect(
					DOM_UnimplementedElement(const_cast<ElemTemplateElement*>(&xslInstruction)), 
					sourceNodes);

			for(int i = 0; i < nNodes; i++) 
			{
				const DOM_Node childNode = sourceNodes.item(i);
				
				DOM_Document ownerDoc = childNode.getOwnerDocument();
				if((DOM_Node::DOCUMENT_NODE != childNode.getNodeType()) && (ownerDoc == 0))
				{
					error(DOMString("Child node does not have an owner document!"));
				}

				transformChild(
					executionContext,
					stylesheetTree, 
					&xslInstruction,
					theTemplate, 
					ownerDoc, 
					sourceNodeContext, 
					childNode,
					mode, 
					xslToken);
			}
		}
		catch(...)
		{
			executionContext.setContextNodeList(savedContextNodeList);

			throw;
		}

		executionContext.setContextNodeList(savedContextNodeList);
	}

}

/** 
 * Given an element and mode, find the corresponding
 * template and process the contents.
 * 
 * @param stylesheetTree The current Stylesheet object.
 * @param xslInstruction The calling element (deprecated -- I dont think we 
 *      need this).
 * @param template The template to use if xsl:for-each, or null.
 * @param sourceTree The source DOM tree.
 * @param selectContext The selection context.
 * @param child The source context node.
 * @param mode The current mode, may be null.
 * @param xslToken ELEMNAME_APPLY_TEMPLATES, ELEMNAME_APPLY_IMPORTS, or     
 *      ELEMNAME_FOREACH.
 * @return true if applied a template, false if not.
 */
bool
ElemTemplateElement::transformChild(
			StylesheetExecutionContext& executionContext,
			const Stylesheet&			stylesheet_tree, 
			const ElemTemplateElement*	xslInstruction, // xsl:apply-templates or xsl:for-each
			const ElemTemplateElement*	theTemplate, // may be null
			const DOM_Node&				sourceTree, 
			const DOM_Node&				selectContext,
			const DOM_Node&				child,
			const QName&				mode,
			int							xslToken) const
{
	bool doApplyTemplate = true; // return value
	bool shouldStrip = false;

	const int nodeType = child.getNodeType();
	const Stylesheet* stylesheetTree = &stylesheet_tree;

	bool isApplyImports = xslToken == Constants::ELEMNAME_APPLY_IMPORTS;

	if(!shouldStrip) // rcw: odd, seems that shouldStripis always false
	{
		if(0 == theTemplate)
		{
			// Find the XSL template that is the best match for the 
			// element, and call buildResultFromTemplate.
			const Stylesheet*	foundStylesheet = 0;

			if(!isApplyImports)
			{
				
				stylesheetTree = &getStylesheet().getStylesheetRoot();
			}
			
			theTemplate = stylesheetTree->findTemplate(executionContext, sourceTree, child, mode,
				isApplyImports,	foundStylesheet);
			
			if(isApplyImports && (0 != theTemplate))
			{
				stylesheetTree = foundStylesheet;
			}
			// mode = null; // non-sticky modes
		}

		if(doApplyTemplate)  //rcw: seems to always be true
		{
			if(0 == theTemplate)
			{
				switch(nodeType)
				{
				case DOM_Node::DOCUMENT_FRAGMENT_NODE:
				case DOM_Node::ELEMENT_NODE:
					theTemplate = getStylesheet().getStylesheetRoot().getDefaultRule();
					break;

				case DOM_Node::CDATA_SECTION_NODE:
				case DOM_Node::TEXT_NODE:
				case DOM_Node::ATTRIBUTE_NODE:
					theTemplate = getStylesheet().getStylesheetRoot().getDefaultTextRule();
					break;

				case DOM_Node::DOCUMENT_NODE:
					theTemplate = getStylesheet().getStylesheetRoot().getDefaultRootRule();
					break;
				case DOM_Node::COMMENT_NODE:
				case DOM_Node::PROCESSING_INSTRUCTION_NODE:
					break;
				default:
					assert(false);
					break;

				}     
				if(0 != theTemplate)
				{
				  // Not sure if this is needed. -sb
					stylesheetTree = &getStylesheet().getStylesheetRoot();
				}
			}
			
			if(0 != theTemplate)
			{
				executionContext.resetCurrentState(sourceTree, child);
				
				if(theTemplate == getStylesheet().getStylesheetRoot().getDefaultTextRule())
				{
					switch(nodeType)
					{
					case DOM_Node::CDATA_SECTION_NODE:
					case DOM_Node::TEXT_NODE:
						executionContext.cloneToResultTree(
							child, false, false, false);
						break;
					case DOM_Node::ATTRIBUTE_NODE:
						{
							//rcw: DOM_node has no virtual funcs so we can't do a dynamic_cast<>.
							const DOM_Attr& attr = static_cast<const DOM_Attr&>(child);
							DOMString val = attr.getValue();
							executionContext.characters(toCharArray(val), 
								0, length(val));
						}
						break;
					default:
						assert(false);
						break;
					}
				}
				else
				{
					bool doPush = (xslToken != Constants::ELEMNAME_FOREACH);

					if(doPush)
					{
						executionContext.pushContextMarker(DOM_UnimplementedElement(const_cast<ElemTemplateElement*>(theTemplate)), child);

						if (xslInstruction != 0)
						{
							executionContext.pushParams(*xslInstruction, 
									sourceTree, selectContext, mode,
									DOM_UnimplementedElement(const_cast<ElemTemplateElement*>(theTemplate)));
						}
					}

					if(0 != getStylesheet().getStylesheetRoot().getTraceListeners())
					{
						TracerEvent te(executionContext, sourceTree, child, 
							mode, *theTemplate);

						getStylesheet().getStylesheetRoot().fireTraceEvent(te);
					}
					theTemplate->executeChildren(executionContext, 
						sourceTree, child, mode);

					if(doPush)
					{
						executionContext.popCurrentContext();
					}
				}

				executionContext.resetCurrentState(sourceTree, selectContext);
			}
		}
	}

	return doApplyTemplate;
}


/** 
 * Throw a template element error.
 * 
 * @param msg Description of the error that occured.
 */

void ElemTemplateElement::error(const DOMString& msg) const
{
	DOMString errMsg("ElemTemplateElement error: " + msg);

	throw SAXException(toCharArray(errMsg));
}


NodeImpl*
ElemTemplateElement::cloneNode(bool /*deep*/)
{
	//should not be called
	assert(false);	
	return 0;
}



// Implemented DOM Element methods.

/** 
 * Add a child to the child list.
 * 
 * @exception DOMException 
 * @param newChild 
 */
NodeImpl* ElemTemplateElement::appendChild(NodeImpl* newChild)
{
	if(0 == newChild)
	{
		error("Trying to add a null child!");
	}
	
	NodeImpl* elem = newChild;
	
	if(0 == m_firstChild)
	{
		assert(dynamic_cast<ElemTemplateElement*>(elem));
		m_firstChild = dynamic_cast<ElemTemplateElement*>(elem);
	}
	else
	{
		assert(dynamic_cast<ElemTemplateElement*>(getLastChild()));
		ElemTemplateElement* last = dynamic_cast<ElemTemplateElement*>(getLastChild());
		assert(last != 0);
		last->setNextSibling(elem);
	}
	
 	dynamic_cast<ElemTemplateElement*>(elem)->setParentNode(this);
	
	return newChild;
}



/*
 *	Remove a node from the child list
 */
NodeImpl* ElemTemplateElement::removeChild(NodeImpl *oldChild)
{
	if(0 == oldChild)
	{
		error("Trying to remove a null child!");
	}

	NodeImpl *pTest = m_firstChild;

	// first try the common, easy cases
	if (pTest == 0)
		return 0;

	if (pTest == oldChild)
	{
		m_firstChild = 0;
		return pTest;
	}

	// now we walk this singly-linked list, peeling one ahead, since we need be
	// able to patch up the list

	while (pTest->getNextSibling() != 0 && pTest->getNextSibling() != oldChild)
		pTest = pTest->getNextSibling();

	NodeImpl* ret = pTest->getNextSibling();

	if (pTest->getNextSibling() != 0)
		dynamic_cast<ElemTemplateElement*>(pTest)->setNextSibling(pTest->getNextSibling()->getNextSibling());

	return ret;
}


/** 
 * Tell if there are child nodes.
 */
bool ElemTemplateElement::hasChildNodes()
{
    return (0 != m_firstChild);
}

  
/** 
 * Get the type of the node.
 */
short ElemTemplateElement::getNodeType()
{
    return DOM_Node::ELEMENT_NODE;
}

/** Return the nodelist (same reference).
 */
NodeListImpl* ElemTemplateElement::getChildNodes()
{
	return this;
}
  

/** Get the first child
 */
NodeImpl* ElemTemplateElement::getFirstChild() 
{
    return m_firstChild;
}


/** Get the last child.
 */
NodeImpl* ElemTemplateElement::getLastChild()
{
	ElemTemplateElement* lastChild = 0;
	assert(!m_firstChild || dynamic_cast<ElemTemplateElement*>(m_firstChild));

	for (ElemTemplateElement* node = m_firstChild; 
		node != 0; node = node->m_nextSibling) 
	{
		assert(dynamic_cast<ElemTemplateElement*>(node));

		lastChild = node;
	}

	return lastChild;
}


/** 
 * NodeList method: Count the immediate children of this node
 * 
 * @return int
 */
unsigned int ElemTemplateElement::getLength()
{
    // It is assumed that the getChildNodes call synchronized
    // the children. Therefore, we can access the first child
    // reference directly.
    int count = 0;

    for (ElemTemplateElement* node = m_firstChild; node != 0; node = node->m_nextSibling) 
    {
      count++;
    }
    return count;

} 


/** 
 * NodeList method: Return the Nth immediate child of this node, or
 * null if the index is out of bounds.
 * 
 * @param index 
 * @return org.w3c.dom.Node
 */
NodeImpl* ElemTemplateElement::item(unsigned int	index) 
{
    // It is assumed that the getChildNodes call synchronized
    // the children. Therefore, we can access the first child
    // reference directly.
    ElemTemplateElement*	node = m_firstChild;

    for (unsigned int i = 0; i < index && node != 0; i++) 
    {
		node = node->m_nextSibling;
    }

    return node;
}
