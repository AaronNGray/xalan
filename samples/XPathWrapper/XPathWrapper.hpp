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
#if !defined(XPATH_WRAPPER_HEADER_GUARD_1357924680)
#define XPATH_WRAPPER_HEADER_GUARD_1357924680



#include <string>
#include <vector>



#include <Include/PlatformDefinitions.hpp>



#if defined(WIN32)
#ifdef _XPathWrapper
#define XALAN_XPATHWRAPPER_EXPORT XALAN_PLATFORM_EXPORT
#else
#define XALAN_XPATHWRAPPER_EXPORT XALAN_PLATFORM_IMPORT
#else
#define XALAN_XPATHWRAPPER_EXPORT
#endif



class XPathWrapperImpl;



class XALAN_XPATHWRAPPER_EXPORT XPathWrapper
{

public:

	XPathWrapper();

	virtual
	~XPathWrapper();

	// Given an xml document and an xpath context and expression in the form of (ascii) string objects,
	// this function parses the XML document, evaluates the xpath and returns the result, as a list of 
	// string objects

#if defined(XALAN_NO_NAMESPACES)
	vector<string>
	evaluate(
		const string&	xml, 
		const string&	context, 
		const string&	path);
#else
	std::vector<std::string>
	evaluate(
		const std::string&	xml, 
		const std::string&	context, 
		const std::string&	path);
#endif

private:

	// not implemented
	XPathWrapper(const XPathWrapper&);

	XPathWrapper&
	operator=(const XPathWrapper&);

	bool
	operator==(const XPathWrapper&) const;


	XPathWrapperImpl* const		pImpl;
};


#endif	// XPATH_WRAPPER_HEADER_GUARD_1357924680
