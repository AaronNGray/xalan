/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights 
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
#include "FunctionNamespaceURI.hpp"



#include <PlatformSupport/DOMStringHelper.hpp>



#include <DOMSupport/DOMServices.hpp>



#include "XObjectFactory.hpp"



FunctionNamespaceURI::FunctionNamespaceURI()
{
}



FunctionNamespaceURI::~FunctionNamespaceURI()
{
}



static const XalanDOMString		theEmptyString;



XObjectPtr
FunctionNamespaceURI::execute(
		XPathExecutionContext&	executionContext,
		XalanNode*				context)
{
	if (context == 0)
	{
		executionContext.error("The namespace-uri() function requires a non-null context node!");

		// Dummy return value...
		return XObjectPtr(0);
	}
	else
	{
		const XalanDOMString*		theResult = &theEmptyString;

		const XalanNode::NodeType	theType = context->getNodeType();

		if (theType == XalanNode::ELEMENT_NODE)
		{
			theResult = &context->getNamespaceURI();
		}
		else if (theType == XalanNode::ATTRIBUTE_NODE)
		{
			const XalanDOMString&	theNodeName = context->getNodeName();

			if (equals(theNodeName, DOMServices::s_XMLNamespace) == false &&
				startsWith(theNodeName, DOMServices::s_XMLNamespaceWithSeparator) == false)
			{
				theResult = &context->getNamespaceURI();
			}
		}
		else
		{
			theResult = &context->getNamespaceURI();
		}

		assert(theResult != 0);

		return executionContext.getXObjectFactory().createStringReference(*theResult);
	}
}



XObjectPtr
FunctionNamespaceURI::execute(
		XPathExecutionContext&	executionContext,
		XalanNode*				/* context */,			
		const XObjectPtr		arg1)
{
	assert(arg1.null() == false);	
	
	const NodeRefListBase&	theList = arg1->nodeset();

	if (theList.getLength() == 0)
	{
		return executionContext.getXObjectFactory().createStringReference(theEmptyString);
	}
	else
	{
		assert(theList.item(0) != 0);

		return execute(executionContext, theList.item(0));
	}
}



XObjectPtr
FunctionNamespaceURI::execute(
			XPathExecutionContext&	executionContext,
			XalanNode*				context,			
			const XObjectPtr		/* arg1 */,
			const XObjectPtr		/* arg2 */)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



XObjectPtr
FunctionNamespaceURI::execute(
			XPathExecutionContext&	executionContext,
			XalanNode*				context,			
			const XObjectPtr		/* arg1 */,
			const XObjectPtr		/* arg2 */,
			const XObjectPtr		/* arg3 */)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



XObjectPtr
FunctionNamespaceURI::execute(
			XPathExecutionContext&			executionContext,
			XalanNode*						context,
			int								/* opPos */,
			const XObjectArgVectorType&		/* args */)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
Function*
#else
FunctionNamespaceURI*
#endif
FunctionNamespaceURI::clone() const
{
	return new FunctionNamespaceURI(*this);
}



const XalanDOMString
FunctionNamespaceURI::getError() const
{
	return XALAN_STATIC_UCODE_STRING("The namespace-uri() function takes zero arguments or one argument!");
}
