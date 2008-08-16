/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the  "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// Class header file.
#include "XNull.hpp"



#include "XObjectTypeCallback.hpp"



XALAN_CPP_NAMESPACE_BEGIN



XalanDOMString   XNull::s_nullString(XalanMemMgrs::getDummyMemMgr());


static const XalanDOMChar   s_null[] =
{
    XalanUnicode::charLessThanSign,
    XalanUnicode::charLetter_n,
    XalanUnicode::charLetter_u,
    XalanUnicode::charLetter_l,
    XalanUnicode::charLetter_l,
    XalanUnicode::charGreaterThanSign,
    0
};



XNull::XNull(MemoryManager&     theMemoryManager) :
	XObject(eTypeNull, theMemoryManager)
{
}



XNull::XNull(
            const XNull&	source,
            MemoryManager&  theMemoryManager) :
	XObject(source, theMemoryManager)
{
}



XNull::~XNull()
{
}



const XalanDOMString&
XNull::getTypeString() const
{
	return s_nullString;
}



double
XNull::num(XPathExecutionContext&   /* executionContext */) const
{
    return DoubleSupport::getNaN();
}



bool
XNull::boolean(XPathExecutionContext&   /* executionContext */) const
{
	return false;
}



const XalanDOMString&
XNull::str(XPathExecutionContext&   /* executionContext */) const
{
    return XNull::str();
}



const XalanDOMString&
XNull::str() const
{
	return s_nullString;
}



void
XNull::str(
            XPathExecutionContext&  /* executionContext */,
			FormatterListener&	    formatterListener,
			MemberFunctionPtr	    function) const
{
    string(s_nullString, formatterListener, function);
}



void
XNull::str(
			FormatterListener&	    formatterListener,
			MemberFunctionPtr	    function) const
{
    string(s_nullString, formatterListener, function);
}



void
XNull::str(
            XPathExecutionContext&  /* executionContext */,
            XalanDOMString&         theBuffer) const
{
    theBuffer.append(s_nullString);
}



void
XNull::str(XalanDOMString&  theBuffer) const
{
    theBuffer.append(s_nullString);
}



double
XNull::stringLength(XPathExecutionContext&  /* executionContext */) const
{
	return (sizeof(s_null) / sizeof(s_null[0])) - 1;
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



void
XNull::initialize()
{
	s_nullString = s_null;
}



void
XNull::terminate()
{
	releaseMemory(s_nullString, XalanMemMgrs::getDummyMemMgr());
}
XALAN_CPP_NAMESPACE_END
