/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2003 The Apache Software Foundation.  All rights 
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
#include "ElemCallTemplate.hpp"



#include <xercesc/sax/AttributeList.hpp>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>
#include <xalanc/PlatformSupport/XalanMessageLoader.hpp>



#include "AVT.hpp"
#include "Constants.hpp"
#include "ElemTemplate.hpp"
#include "Stylesheet.hpp"
#include "StylesheetConstructionContext.hpp"
#include "StylesheetExecutionContext.hpp"
#include "StylesheetRoot.hpp"



XALAN_CPP_NAMESPACE_BEGIN



ElemCallTemplate::ElemCallTemplate(
			StylesheetConstructionContext&	constructionContext,
			Stylesheet&						stylesheetTree,
			const AttributeListType&		atts,
			int								lineNumber,
			int								columnNumber) :
	ElemTemplateElement(constructionContext,
						stylesheetTree,
						lineNumber,
						columnNumber,
						StylesheetConstructionContext::ELEMNAME_CALL_TEMPLATE),
	m_templateName(0),
	m_template(0)
{
	const unsigned int	nAttrs = atts.getLength();

	for(unsigned int i = 0; i < nAttrs; i++)
	{
		const XalanDOMChar*	const	aname = atts.getName(i);

		if(equals(aname, Constants::ATTRNAME_NAME))
		{
			m_templateName = constructionContext.createXalanQName(
					atts.getValue(i),
					getStylesheet().getNamespaces(),
					getLocator());

			if (m_templateName->isValid() == false)
			{
				constructionContext.error(
						XalanMessageLoader::getMessage(
							XalanMessages::AttributeValueNotValidQName_2Param,
							Constants::ATTRNAME_NAME.c_str(),
							atts.getValue(i)),
						0,
						this);
			}
		}
		else if(!isAttrOK(aname, atts, i, constructionContext))
		{
			constructionContext.error(
					XalanMessageLoader::getMessage(
						XalanMessages::TemplateHasIllegalAttribute_2Param,
							Constants::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING.c_str(),
							aname),
					0,
					this);
		}
	}

	if (m_templateName == 0)
	{
		constructionContext.error(
			XalanMessageLoader::getMessage(
				XalanMessages::TemplateMustHaveAttribute_2Param,
				Constants::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING,
				Constants::ATTRNAME_NAME),
			0,
			this);
	}
}



ElemCallTemplate::~ElemCallTemplate()
{
}



const XalanDOMString&
ElemCallTemplate::getElementName() const
{
	return Constants::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING;
}



void
ElemCallTemplate::execute(StylesheetExecutionContext&	executionContext) const
{
	ElemTemplateElement::execute(executionContext);

	assert(m_template != 0);

	const StylesheetExecutionContext::ParamsPushPop		thePushPop(
				executionContext,
				*this);

	m_template->execute(executionContext);
}



void
ElemCallTemplate::postConstruction(
			StylesheetConstructionContext&	constructionContext,
			const NamespacesHandler&		theParentHandler)
{
	assert(m_templateName != 0);

	m_template = getStylesheet().getStylesheetRoot().findNamedTemplate(*m_templateName);

	if(m_template == 0)
	{
		constructionContext.error(
			XalanMessageLoader::getMessage(XalanMessages::CannotFindNamedTemplate),
			0,
			this);
	}

	// OK, now we can chain-up...
	ElemTemplateElement::postConstruction(constructionContext, theParentHandler);
}



bool
ElemCallTemplate::childTypeAllowed(int	xslToken) const
{
	if (xslToken == StylesheetConstructionContext::ELEMNAME_WITH_PARAM)
	{
		return true;
	}
	else
	{
		return false;
	}
}



XALAN_CPP_NAMESPACE_END
