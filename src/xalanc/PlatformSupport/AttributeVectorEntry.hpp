/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2002 The Apache Software Foundation.  All rights 
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
#if !defined(ATTRIBUTEVECTORENTRY_HEADER_GUARD_1357924680)
#define ATTRIBUTEVECTORENTRY_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <xalanc/PlatformSupport/PlatformSupportDefinitions.hpp>



#include <vector>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XALAN_PLATFORMSUPPORT_EXPORT AttributeVectorEntry
{
public:

#if defined(XALAN_NO_STD_NAMESPACE)
	typedef vector<XMLCh>		XMLChVectorType;
#else
	typedef std::vector<XMLCh>	XMLChVectorType;
#endif

	AttributeVectorEntry(
			const XMLChVectorType&	theName,
			const XMLChVectorType&	theValue,
			const XMLChVectorType&	theType) :
		m_Name(theName),
		m_Value(theValue),
		m_Type(theType)
	{
	}

	AttributeVectorEntry(
			const XMLCh*	theName,
			const XMLCh*	theValue,
			const XMLCh*	theType) :
		m_Name(theName, theName + length(theName) + 1),
		m_Value(theValue, theValue + length(theValue) + 1),
		m_Type(theType, theType + length(theType) + 1)
	{
	}

	AttributeVectorEntry() :
		m_Name(),
		m_Value(),
		m_Type()
	{
	}

    virtual
	~AttributeVectorEntry()
	{
	}

	void
	clear()
	{
		m_Name.clear();
		m_Value.clear();
		m_Type.clear();
	}

	XMLChVectorType		m_Name;
	XMLChVectorType		m_Value;
	XMLChVectorType		m_Type;

	// A convenience function to find the length of a null-terminated
	// array of XMLChs
	static const XMLCh*
	endArray(const XMLCh*	data)
	{
		assert(data != 0);

		while(*data)
		{
			++data;
		}

		return data;
	}
};



XALAN_CPP_NAMESPACE_END



#endif	// ATTRIBUTEVECTORENTRY_HEADER_GUARD_1357924680
