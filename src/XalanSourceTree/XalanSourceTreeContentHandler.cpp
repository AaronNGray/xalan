/*
 * The Apache Software License, Version 1.1
 * 
 * Copyright (c) 1999-2000 The Apache Software Foundation.	All rights
 * reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer. 
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in
 *	  the documentation and/or other materials provided with the
 *	  distribution.
 * 
 * 3. The end-user documentation included with the redistribution,
 *	  if any, must include the following acknowledgment:  
 *		 "This product includes software developed by the
 *		  Apache Software Foundation (http://www.apache.org/)."
 *	  Alternately, this acknowledgment may appear in the software itself,
 *	  if and wherever such third-party acknowledgments normally appear.
 * 
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *	  not be used to endorse or promote products derived from this
 *	  software without prior written permission. For written 
 *	  permission, please contact apache\@apache.org.
 * 
 * 5. Products derived from this software may not be called "Apache",
 *	  nor may "Apache" appear in their name, without prior written
 *	  permission of the Apache Software Foundation.
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.	IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
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
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

#include "XalanSourceTreeContentHandler.hpp"



#include <XalanDOM/XalanDOMException.hpp>



#include <PlatformSupport/DOMStringHelper.hpp>



#include "XalanSourceTreeDocument.hpp"
#include "XalanSourceTreeElement.hpp"
#include "XalanSourceTreeHelper.hpp"



XalanSourceTreeContentHandler::XalanSourceTreeContentHandler(
			XalanSourceTreeDocument*	theDocument,
			bool						fAccumulateText) :
	ContentHandler(),
	DTDHandler(),
	LexicalHandler(),
	m_document(theDocument),
	m_currentElement(0),
	m_elementStack(),
	m_lastChild(0),
	m_lastChildStack(),
	m_accumulateText(fAccumulateText),
	m_textBuffer(),
	m_inDTD(false)
{
}



XalanSourceTreeContentHandler::~XalanSourceTreeContentHandler()
{
}



void
XalanSourceTreeContentHandler::characters(
			const	XMLCh* const	chars,
			const unsigned int		length)
{
	assert(m_inDTD == false);

	if (m_currentElement == 0)
	{
		if (isXMLWhitespace(chars) == false)
		{
			throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);
		}
	}
	else if (m_accumulateText == true)
	{
		append(m_textBuffer, chars, length);
	}
	else
	{
		doCharacters(chars, length);
	}
}



void
XalanSourceTreeContentHandler::endDocument()
{
	assert(m_inDTD == false);

	// Pop off the dummy value that we pushed in 
	// startDocument()...
	m_elementStack.pop_back();

	assert(m_document->getDocumentElement() != 0);

	assert(m_elementStack.empty() == true);
	assert(m_lastChildStack.empty() == true);

	assert(isEmpty(m_textBuffer) == true);
}



void
XalanSourceTreeContentHandler::endElement(
			const XMLCh* const	/* uri */, 
			const XMLCh* const	/* localname */, 
			const XMLCh* const	/* qname */)
{
	assert(m_inDTD == false);

	// Process any text that we may have accumulated...
	processAccumulatedText();

	assert(m_elementStack.empty() == false);

	// Pop the element of the stack...
	m_elementStack.pop_back();

	assert(m_elementStack.empty() == false);

	// Get the element from the back of the
	// stack.
	m_currentElement = m_elementStack.back();

	assert(m_lastChildStack.empty() == false);

	m_lastChild = m_lastChildStack.back();

	// Pop the last child stack
	m_lastChildStack.pop_back();
}



// A helper function to manage appending the new child.
template <class ParentNodeType, class ChildNodeType>
inline void
doAppendChildNode(
			ParentNodeType*		theParent,
			XalanNode*&			theLastChild,
			ChildNodeType		theNewChild)
{
	assert(theParent != 0);
	assert(theNewChild != 0);

	if (theLastChild == 0)
	{
		theParent->appendChildNode(theNewChild);
	}
	else
	{
		XalanSourceTreeHelper::appendSibling(theLastChild, theNewChild);
	}

	theLastChild = theNewChild;
}



// A helper function to manage appending the new child.
template <class ChildNodeType>
inline void
doAppendChildNode(
			XalanSourceTreeDocument*	theDocument,
			XalanSourceTreeElement*		theCurrentElement,
			XalanNode*&					theLastChild,
			ChildNodeType				theNewChild)
{
	assert(theDocument != 0);
	assert(theNewChild != 0);

	if (theCurrentElement == 0)
	{
		// If there is no current element. it means we haven't
		// created the document element yet, so always append
		// to the document, rather than the last child.
		theDocument->appendChildNode(theNewChild);
	}
	else
	{
		doAppendChildNode(theCurrentElement, theLastChild, theNewChild);
	}
}



void
XalanSourceTreeContentHandler::ignorableWhitespace(
			const XMLCh* const	chars,
			const unsigned int	length)
{
	assert(m_inDTD == false);

	// Ignore any whitespace reported before the document element has been parsed.
	if (m_elementStack.empty() == false)
	{
		assert(m_currentElement != 0);

		processAccumulatedText();

		XalanSourceTreeText*	theNewTextNode =
			m_document->createTextIWSNode(chars, length, m_currentElement);

		doAppendChildNode(m_currentElement, m_lastChild, theNewTextNode);
	}
}



void
XalanSourceTreeContentHandler::processingInstruction(
		const XMLCh* const	target,
		const XMLCh* const	data)
{
	assert(m_inDTD == false);

	processAccumulatedText();

	XalanSourceTreeProcessingInstruction* const		theNewPI =
		m_document->createProcessingInstructionNode(target, data, m_currentElement);

	doAppendChildNode(
			m_document,
			m_currentElement,
			m_lastChild,
			theNewPI);
}



void
XalanSourceTreeContentHandler::setDocumentLocator(const Locator* const	/* locator */)
{
}



void
XalanSourceTreeContentHandler::startDocument()
{
	assert(m_inDTD == false);

	m_currentElement = 0;

	m_elementStack.clear();

	m_elementStack.reserve(eDefaultStackSize);

	m_lastChild = 0;

	m_lastChildStack.clear();

	m_lastChildStack.reserve(eDefaultStackSize);

	if (m_accumulateText == true)
	{
		clear(m_textBuffer);

		reserve(m_textBuffer, eDefaultTextBufferSize);
	}

	// Push a dummy value for the current element, so we
	// don't have to check for an empty stack in endElement().
	m_elementStack.push_back(ElementStackType::value_type(0));
}



void
XalanSourceTreeContentHandler::startElement(
			const XMLCh* const	uri,
			const XMLCh* const	localname,
			const XMLCh* const	qname,
			const Attributes& 	attrs)
{
	// $$$ ToDo: This is a workaround for a bug in Xerces 1.5.1.
#if 1
	if (m_currentElement == 0 && m_inDTD == true)
	{
		m_inDTD = false;
	}
#endif
	assert(m_inDTD == false);

	processAccumulatedText();

	XalanSourceTreeElement* const	theNewElement =
		createElement(uri, localname, qname, attrs, m_currentElement);

	doAppendChildNode(
			m_document,
			m_currentElement,
			m_lastChild,
			theNewElement);

	m_elementStack.push_back(theNewElement);

	m_lastChildStack.push_back(m_lastChild);

	m_currentElement = theNewElement;

	m_lastChild = 0;
}



void
XalanSourceTreeContentHandler::startPrefixMapping(
		const XMLCh* const	/* prefix */,
		const XMLCh* const	/* uri */)
{
	assert(m_inDTD == false);
}



void
XalanSourceTreeContentHandler::endPrefixMapping(const XMLCh* const	/* prefix */)
{
	assert(m_inDTD == false);
}



void
XalanSourceTreeContentHandler::skippedEntity(const XMLCh* const		/* name */)
{
}



void
XalanSourceTreeContentHandler::notationDecl(
			const XMLCh* const    name,
			const XMLCh* const    publicId,
			const XMLCh* const    systemId)
{
}



void
XalanSourceTreeContentHandler::unparsedEntityDecl(
			const XMLCh* const    name,
			const XMLCh* const    publicId,
			const XMLCh* const    systemId,
			const XMLCh* const    notationName)
{
	assert(m_document != 0);

	m_document->unparsedEntityDeclaration(name, publicId, systemId, notationName);
}



void
XalanSourceTreeContentHandler::resetDocType()
{
}



void
XalanSourceTreeContentHandler::comment(
			const XMLCh* const	chars,
			const unsigned int	length)
{
	assert(m_document != 0);

	if (m_inDTD == false)
	{
		processAccumulatedText();

		XalanSourceTreeComment* const	theNewComment =
			m_document->createCommentNode(chars, length, m_currentElement);

		doAppendChildNode(
				m_document,
				m_currentElement,
				m_lastChild,
				theNewComment);
	}
}



void
XalanSourceTreeContentHandler::endCDATA()
{
	assert(m_inDTD == false);
}



void
XalanSourceTreeContentHandler::endDTD()
{
	m_inDTD = false;

	assert(m_document != 0);
}



void
XalanSourceTreeContentHandler::endEntity(const XMLCh* const		name)
{
	assert(m_document != 0);
}


void
XalanSourceTreeContentHandler::startCDATA()
{
	assert(m_inDTD == false);
}



void
XalanSourceTreeContentHandler::startDTD(
			const XMLCh* const	name,
			const XMLCh* const	publicId,
			const XMLCh* const	systemId)
{
	assert(m_inDTD == false);
	assert(m_document != 0);

	m_inDTD = true;
}



void
XalanSourceTreeContentHandler::startEntity(const XMLCh* const	name)
{
	assert(m_document != 0);
}



void
XalanSourceTreeContentHandler::setDocument(XalanSourceTreeDocument*	theDocument)
{
	m_document = theDocument;
}



XalanSourceTreeElement*
XalanSourceTreeContentHandler::createElement(
			const XMLCh* const			uri,
			const XMLCh* const			localname,
			const XMLCh* const			qname,
			const Attributes& 			attrs,
			XalanSourceTreeElement*		theOwnerElement)
{
	assert(m_inDTD == false);

	if (length(uri) != 0)
	{
		return m_document->createElementNode(uri, localname, qname, attrs, theOwnerElement);
	}
	else
	{
		return m_document->createElementNode(qname, attrs, theOwnerElement);
	}
}



void
XalanSourceTreeContentHandler::processAccumulatedText()
{
	assert(m_inDTD == false);

	if (isEmpty(m_textBuffer) == false)
	{
		doCharacters(c_wstr(m_textBuffer), length(m_textBuffer));

		clear(m_textBuffer);
	}
}



void
XalanSourceTreeContentHandler::doCharacters(
			const XMLCh*	chars,
			unsigned int	length)
{
	assert(m_inDTD == false);

	assert(m_currentElement != 0);

	XalanSourceTreeText*	theNewTextNode = 
				m_document->createTextNode(chars, length, m_currentElement);

	doAppendChildNode(m_currentElement, m_lastChild, theNewTextNode);
}
