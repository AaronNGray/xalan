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
// Class header file...
#include "XercesTextOutputStream.hpp"



#include <sstream>



#if defined(_MSC_VER)
#include "windows.h"
#else
#define INVALID_HANDLE_VALUE 0
#endif



#include <util/Janitor.hpp>
#include <util/XMLString.hpp>



#include <PlatformSupport/DOMStringHelper.hpp>





const XercesTextOutputStream::BufferType::size_type	XercesTextOutputStream::s_bufferSize = 8192;



XercesTextOutputStream::XercesTextOutputStream() :
	TextOutputStream()
{
}



XercesTextOutputStream::~XercesTextOutputStream()
{
}



void
XercesTextOutputStream::flush()
{
	flushBuffer();

	doFlush();
}



void
XercesTextOutputStream::write(const XMLCh* const	theBuffer)
{
	assert(theBuffer != 0);

	const BufferType::size_type		theLength =
		static_cast<BufferType::size_type>(length(theBuffer));

	if (theLength + m_buffer.size() > s_bufferSize)
	{
		flushBuffer();
	}

	if (theLength > s_bufferSize)
	{
		doWrite(theBuffer);
	}
	else
	{
		m_buffer.insert(m_buffer.end(),
						theBuffer,
						theBuffer + theLength);
	}
}



void
XercesTextOutputStream::write(const char* const	theBuffer)
{
	assert(theBuffer != 0);

	flushBuffer();

	writeData(theBuffer,
		      strlen(theBuffer));
}



void
XercesTextOutputStream::write(
			const char*		theBuffer,
			unsigned long	theBufferLength)
{
	assert(theBuffer != 0);

	flushBuffer();

	writeData(theBuffer,
			  theBufferLength);
}



void
XercesTextOutputStream::flushBuffer()
{
	if (m_buffer.size() > 0)
	{
		m_buffer.push_back(0);

		doWrite(m_buffer.begin());

		m_buffer.clear();
	}
}



void
XercesTextOutputStream::doWrite(const XMLCh*	theBuffer)
{
	assert(theBuffer != 0);

    char* const	tmpVal = XMLString::transcode(theBuffer);

    ArrayJanitor<char> janTmp(tmpVal);

	writeData(tmpVal,
			  strlen(tmpVal));
}



XercesTextOutputStreamException::XercesTextOutputStreamException(
		const DOMString&	theMessage,
		const DOMString&	theType) :
	XercesPlatformSupportException(theMessage,
								theType)
{
}



XercesTextOutputStreamException::~XercesTextOutputStreamException()
{
}
