/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2002 The Apache Software Foundation.  All rights 
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
#include "XercesTextBridge.hpp"



#include <cassert>



#include <DOMSupport/DOMServices.hpp>



#include "XercesBridgeHelper.hpp"
#include "XercesBridgeNavigator.hpp"
#include "XercesDOMException.hpp"
#include "XercesDocumentBridge.hpp"



XercesTextBridge::XercesTextBridge(
			const DOM_Text&					theXercesText,
			const XercesBridgeNavigator&	theNavigator) :
	XalanText(),
	m_xercesNode(theXercesText),
	m_navigator(theNavigator)
{
	assert(m_xercesNode.isNull() == false);
}



XercesTextBridge::~XercesTextBridge()
{
}



const XalanDOMString&
XercesTextBridge::getNodeName() const
{
	return m_navigator.getPooledString(m_xercesNode.getNodeName());
}



const XalanDOMString&
XercesTextBridge::getNodeValue() const
{
	return m_navigator.getPooledString(m_xercesNode.getNodeValue());
}



XercesTextBridge::NodeType
XercesTextBridge::getNodeType() const
{
	return TEXT_NODE;
}



XalanNode*
XercesTextBridge::getParentNode() const
{
	return m_navigator.getParentNode(m_xercesNode);
}



const XalanNodeList*
XercesTextBridge::getChildNodes() const
{
	return 0;
}



XalanNode*
XercesTextBridge::getFirstChild() const
{
	return 0;
}



XalanNode*
XercesTextBridge::getLastChild() const
{
	return 0;
}



XalanNode*
XercesTextBridge::getPreviousSibling() const
{
	return m_navigator.getPreviousSibling(m_xercesNode);
}



XalanNode*
XercesTextBridge::getNextSibling() const
{
	return m_navigator.getNextSibling(m_xercesNode);
}



const XalanNamedNodeMap*
XercesTextBridge::getAttributes() const
{
	return 0;
}



XalanDocument*
XercesTextBridge::getOwnerDocument() const
{
	return m_navigator.getOwnerDocument();
}



#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
XalanNode*
#else
XercesTextBridge*
#endif
XercesTextBridge::cloneNode(bool	deep) const
{
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	return m_navigator.cloneNode(this, m_xercesNode, deep);
#else
	XercesTextBridge* const	theBridge =
		static_cast<XercesTextBridge*>(m_navigator.cloneNode(this, m_xercesNode, deep));

	return theBridge;
#endif
}



XalanNode*
XercesTextBridge::insertBefore(
			XalanNode*	/* newChild */,
			XalanNode*	/* refChild */)
{
	throw XercesDOMException(XercesDOMException::HIERARCHY_REQUEST_ERR);

	return 0;
}



XalanNode*
XercesTextBridge::replaceChild(
			XalanNode*	/* newChild */,
			XalanNode*	/* oldChild */)
{
	throw XercesDOMException(XercesDOMException::HIERARCHY_REQUEST_ERR);

	return 0;
}



XalanNode*
XercesTextBridge::removeChild(XalanNode*	/* oldChild */)
{
	throw XercesDOMException(XercesDOMException::HIERARCHY_REQUEST_ERR);

	return 0;
}



XalanNode*
XercesTextBridge::appendChild(XalanNode*	/* newChild */)
{
	throw XercesDOMException(XercesDOMException::HIERARCHY_REQUEST_ERR);

	return 0;
}



bool
XercesTextBridge::hasChildNodes() const
{
	return false;
}


void
XercesTextBridge::setNodeValue(const XalanDOMString&	nodeValue)
{
	XercesBridgeHelper::setNodeValue(m_xercesNode, nodeValue);
}



void
XercesTextBridge::normalize()
{
	XercesBridgeHelper::normalize(m_xercesNode);
}



bool
XercesTextBridge::isSupported(
			const XalanDOMString&	feature,
			const XalanDOMString&	version) const
{
	return m_xercesNode.isSupported(
				XercesBridgeHelper::XalanDOMStringToXercesDOMString(feature),
				XercesBridgeHelper::XalanDOMStringToXercesDOMString(version));
}



const XalanDOMString&
XercesTextBridge::getNamespaceURI() const
{
	return m_navigator.getPooledString(m_xercesNode.getNamespaceURI());
}



const XalanDOMString&
XercesTextBridge::getPrefix() const
{
	return m_navigator.getPooledString(m_xercesNode.getPrefixImpl());
}



const XalanDOMString&
XercesTextBridge::getLocalName() const
{
	return m_navigator.getPooledString(m_xercesNode.getLocalNameImpl());
}



void
XercesTextBridge::setPrefix(const XalanDOMString&	prefix)
{
	XercesBridgeHelper::setPrefix(m_xercesNode, prefix);
}



bool
XercesTextBridge::isIndexed() const
{
	return m_navigator.getOwnerDocument()->isIndexed();
}



unsigned long
XercesTextBridge::getIndex() const
{
	return m_navigator.getIndex();
}



const XalanDOMString&
XercesTextBridge::getData() const
{
	return m_navigator.getPooledString(m_xercesNode.getDataImpl());
}



unsigned int
XercesTextBridge::getLength() const
{
	return m_xercesNode.getLength();
}



XalanDOMString
XercesTextBridge::substringData(
			unsigned int	offset, 
			unsigned int	count) const
{
	return XercesBridgeHelper::substringData(m_xercesNode, offset, count);
}



void
XercesTextBridge::appendData(const XalanDOMString&	arg)
{
	XercesBridgeHelper::appendData(m_xercesNode, arg);
}



void
XercesTextBridge::insertData(
			unsigned int			offset,
			const XalanDOMString& 	arg)
{
	XercesBridgeHelper::insertData(m_xercesNode, offset, arg);
}



void
XercesTextBridge::deleteData(
			unsigned int	offset, 
			unsigned int	count)
{
	XercesBridgeHelper::deleteData(m_xercesNode, offset, count);
}



void
XercesTextBridge::replaceData(
			unsigned int			offset, 
			unsigned int			count, 
			const XalanDOMString&	arg)
{
	XercesBridgeHelper::replaceData(m_xercesNode, offset, count, arg);
}



XalanText*
XercesTextBridge::splitText(unsigned int	offset)
{
	return m_navigator.splitText(m_xercesNode, offset);
}



bool
XercesTextBridge::isIgnorableWhitespace() const
{
	return isXMLWhitespace(getData());
}
