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
#include "XNull.hpp"



#include "ResultTreeFrag.hpp"
#include "XObjectTypeCallback.hpp"
#include "XPathEnvSupport.hpp"



XNull::XNull(
			XPathEnvSupport&	envSupport,
			XPathSupport&		support) :
	XObject(&envSupport, &support),
	m_resultTreeFrag(new ResultTreeFrag(*envSupport.getDOMFactory(),
										support))
{
}



XNull::XNull(
			const XNull&	source,
			bool			deepClone) :
	XObject(source),
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	m_resultTreeFrag(static_cast<ResultTreeFragBase*>(source.m_resultTreeFrag->cloneNode(deepClone)))
#else
	m_resultTreeFrag(source.m_resultTreeFrag->clone(deepClone))
#endif
{
}



XNull::~XNull()
{
}



#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
XObject*
#else
XNull*
#endif
XNull::clone() const
{
	return new XNull(*this, false);
};



XNull::eObjectType
XNull::getType() const
{
	return eTypeNull;
}



XalanDOMString
XNull::getTypeString() const
{
	return XALAN_STATIC_UCODE_STRING("#NULL");
}



double
XNull::num() const
{
	return 0.0;
}



bool
XNull::boolean() const
{
	return false;
}



XalanDOMString
XNull::str() const
{
	return XalanDOMString();
}



const ResultTreeFragBase&
XNull::rtree() const
{
	return *m_resultTreeFrag.get();
}



ResultTreeFragBase&
XNull::rtree()
{
	return *m_resultTreeFrag.get();
}



const NodeRefListBase&
XNull::nodeset() const
{
	error("Can't cast XNull to NodeRefListBase");

	// error will throw, so this is just a dummy
	// value to satisfy the compiler.
	return *static_cast<NodeRefListBase*>(0);
}



const MutableNodeRefList&
XNull::mutableNodeset() const
{
	error("Can't cast XNull to MutableNodeRefList");

	// error will throw, so this is just a dummy
	// value to satisfy the compiler.
	return *static_cast<MutableNodeRefList*>(0);
}



MutableNodeRefList&
XNull::mutableNodeset()
{
	error("Can't cast XNull to MutableNodeRefList");

	// error will throw, so this is just a dummy
	// value to satisfy the compiler.
	return *static_cast<MutableNodeRefList*>(0);
}



void
XNull::ProcessXObjectTypeCallback(XObjectTypeCallback&	theCallbackObject)
{
	theCallbackObject.Null(*this);
}



void
XNull::ProcessXObjectTypeCallback(XObjectTypeCallback&	theCallbackObject) const
{
	theCallbackObject.Null(*this);
}
