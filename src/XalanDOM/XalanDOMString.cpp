/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2000 The Apache Software Foundation.  All rights 
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

#include "XalanDOMString.hpp"



#include <cassert>



#include <Include/XalanAutoPtr.hpp>



#include <cstdlib>



const XalanDOMChar	XalanDOMString::s_empty = 0;



XalanDOMString::XalanDOMString() :
	m_data(),
	m_size(0)
{
}



XalanDOMString::XalanDOMString(
			const XalanDOMString&	theSource,
			size_type				theStartPosition,
			size_type				theCount) :
	m_data(),
	m_size(0)
{
	if (theSource.length() != 0)
	{
		append(theSource, theStartPosition, theCount);
	}
}



XalanDOMString::XalanDOMString(
			const XalanDOMChar*		theString,
			size_type				theCount) :
	m_data(),
	m_size(0)
{
	assert(theString != 0);

	if (*theString != 0)
	{
		append(theString, theCount);
	}
}



XalanDOMString::XalanDOMString(
			const char*		theString,
			size_type		theCount) :
	m_data(),
	m_size(0)
{
	assert(theString != 0);

	if (*theString != 0)
	{
		append(theString, theCount);
	}

	invariants();
}



XalanDOMString::XalanDOMString(
			size_type		theCount,
			XalanDOMChar	theChar) :
	m_data(),
	m_size(0)
{
	if (theCount != 0)
	{
		XalanDOMCharVectorType(real_size_type(theCount) + 1, theChar).swap(m_data);

		// Null-terminate it...
		m_data.back() = 0;

		m_size = theCount;
	}

	invariants();
}



void
XalanDOMString::resize(
			size_type		theCount,
			XalanDOMChar	theChar)
{
	invariants();

	const size_type		theOldSize = size();

	if (theCount != theOldSize)
	{
		if (theOldSize == 0)
		{
			// If the string is of 0 length, resize but add an
			// extra byte for the terminating byte.
			m_data.resize(real_size_type(theCount) + 1, theChar);
		}
		else
		{
			// If the string is not of 0 length, resize but
			// put a copy of theChar where the terminating
			// byte used to be.
			m_data.resize(real_size_type(theCount), theChar);

			m_data[real_size_type(theOldSize)] = theChar;
		}

		m_size = theCount;

		// Terminate...
		m_data.back() = 0;
	}

	invariants();
}



void
XalanDOMString::erase(
			size_type	theStartPosition,
			size_type	theCount)
{
	invariants();

	const size_type		theActualCount =
			theCount == size_type(npos) ? length() : theCount;

	if (theStartPosition == 0 && theCount >= size())
	{
		m_data.erase(m_data.begin(), m_data.end());

		m_size = 0;
	}
	else
	{
		const iterator		i = getIteratorForPosition(theStartPosition);

		m_data.erase(i, i + (theActualCount));

		const size_type		theNewSize = size_type(m_data.size());
		assert(real_size_type(theNewSize) == m_data.size());

		if (theNewSize < 2)
		{
			m_size = 0;
		}
		else
		{
			m_size = theNewSize - 1;
		}
	}

	invariants();
}



XalanDOMString&
XalanDOMString::assign(
		const_iterator	theFirstPosition,
		const_iterator	theLastPosition)
{
	invariants();

	erase();

	invariants();

	insert(begin(), theFirstPosition, theLastPosition);

	invariants();

	return *this;
}



XalanDOMString&
XalanDOMString::append(
			const XalanDOMChar*		theString,
			size_type				theCount)
{
	const size_type		theLength =
			theCount == size_type(npos) ? length(theString) : theCount;

	if (theLength != 0)
	{
		if (m_data.size() == 0)
		{
			m_data.reserve(real_size_type(theLength) + 1);

			m_data.insert(m_data.end(), theString, theString + theLength);

			m_data.push_back(0);

			m_size = theLength;

			assert(length() == theLength);
		}
		else
		{
			m_data.insert(getBackInsertIterator(), theString, theString + theLength);

			m_size += theCount;
		}
	}

	invariants();

	return *this;
}



static inline void
doTranscode(
			const char*					theString,
			XalanDOMString::size_type	theCount,
			XalanDOMCharVectorType&		theVector)
{
	assert(theString != 0);

	if (theCount == XalanDOMString::size_type(XalanDOMString::npos))
	{
		if (TranscodeFromLocalCodePage(theString, theVector, true) == false)
		{
			throw XalanDOMString::TranscodingError();
		}
	}
	else
	{
		if (TranscodeFromLocalCodePage(theString, theCount, theVector, true) == false)
		{
			throw XalanDOMString::TranscodingError();
		}
	}
}



XalanDOMString&
XalanDOMString::append(
			const char*		theString,
			size_type		theCount)
{
	invariants();

	const size_type		theLength =
			theCount == size_type(npos) ? length(theString) : theCount;

	if (theLength != 0)
	{
		if (size() == 0)
		{
			doTranscode(theString, theLength, m_data);
		}
		else
		{
			XalanDOMCharVectorType	theTempVector;

			doTranscode(theString, theLength, theTempVector);

			append(&*theTempVector.begin(), size_type(theTempVector.size()));
		}

		m_size = size_type(m_data.size()) - 1;

		assert(real_size_type(m_size) == m_data.size() - 1);
	}

	invariants();

	return *this;
}


XalanDOMString&
XalanDOMString::append(
			size_type		theCount,
			XalanDOMChar	theChar)
{
	invariants();

	if (m_data.size() == 0)
	{
		m_data.insert(m_data.end(), real_size_type(theCount) + 1, theChar);

		m_data.back() = 0;

		m_size = theCount;

		assert(length() == theCount);
	}
	else
	{
		m_data.insert(getBackInsertIterator(), real_size_type(theCount), theChar);

		m_size += theCount;
	}

	invariants();

	return *this;
}



XalanDOMString&
XalanDOMString::insert(
			size_type				thePosition,
			const XalanDOMChar*		theString,
			size_type				theCount)
{
	invariants();

	m_data.insert(getIteratorForPosition(thePosition), theString, theString + theCount);

	m_size += theCount;

	invariants();

	return *this;
}



XalanDOMString&
XalanDOMString::insert(
			size_type		thePosition,
			size_type		theCount,
			XalanDOMChar	theChar)
{
	invariants();

	m_data.insert(getIteratorForPosition(thePosition), real_size_type(theCount), theChar);

	m_size += theCount;

	invariants();

	return *this;
}



XalanDOMString::iterator
XalanDOMString::insert(
			iterator		thePosition,
			XalanDOMChar	theChar)
{
	invariants();

	m_data.insert(thePosition, theChar);

	++m_size;

	invariants();

	return thePosition;
}



void
XalanDOMString::insert(
			iterator		thePosition,
			size_type		theCount,
			XalanDOMChar	theChar)
{
	invariants();

	m_data.insert(thePosition, real_size_type(theCount), theChar);

	m_size += theCount;

	invariants();
}



void
XalanDOMString::insert(
		iterator		theInsertPosition,
		const_iterator	theFirstPosition,
		const_iterator	theLastPosition)
{
	invariants();

	m_data.insert(theInsertPosition, theFirstPosition, theLastPosition);

	m_size = size_type(m_data.size()) - 1;

	assert(real_size_type(m_size) == m_data.size() - 1);

	invariants();
}



template <class Type, class SizeType>
int
doCompare(
			const Type*		theLHS,
			SizeType		theLHSLength,
			const Type*		theRHS,
			SizeType		theRHSLength)
{
	int					theResult = 0;

	if (theLHSLength != 0 || theRHSLength != 0)
	{
		Type		theLHSChar = Type(0);
		Type		theRHSChar = Type(0);

		SizeType	i = 0;

		for(; i < theLHSLength && i < theRHSLength; i++)
		{
			theLHSChar = theLHS[i];
			theRHSChar = theRHS[i];

			if (theLHSChar != theRHSChar)
			{
				break;
			}
		}

		if (i == theLHSLength)
		{
			// We reached the end of theLHS...
			if (i != theRHSLength)
			{
				// but not the end of theRHS.
				theResult = -1;
			}
		}
		else if (i == theRHSLength)
		{
			// We reached the end of theRHS string...
			if (i != theLHSLength)
			{
				// but not the end of theLHS string.
				theResult = 1;
			}
		}
		else
		{
			// We didn't reach the end of _either_ string, so
			// return the difference between the two characters
			// that caused the problem.
			theResult = theLHSChar - theRHSChar;
		}
	}

	return theResult;
}



int
XalanDOMString::compare(const XalanDOMChar*		theString) const
{
	invariants();

	return doCompare(c_str(), length(), theString, length(theString));
}



int
XalanDOMString::compare(
			size_type				thePosition1,
			size_type				theCount1,
			const XalanDOMChar*		theString,
			size_type				theCount2) const
{
	invariants();

	return doCompare(c_str() + thePosition1, theCount1, theString, theCount2);
}



XalanDOMString::CharVectorType
XalanDOMString::transcode() const
{
	invariants();

	CharVectorType	theResult;

	if (TranscodeToLocalCodePage(c_str(), length(), theResult, true) == false)
	{
		throw TranscodingError();
	}

	return theResult;
}



static inline XalanDOMString::size_type
length(const XalanDOMChar*	theString)
{
	assert(theString != 0);

	const XalanDOMChar*		theStringPointer = theString;

	while(*theStringPointer != 0)
	{
		theStringPointer++;
	}

	return XalanDOMString::size_type(theStringPointer - theString);
}



bool
XalanDOMString::equals(
			const XalanDOMChar*		theLHS,
			size_type				theLHSLength,
			const XalanDOMChar*		theRHS,
			size_type				theRHSLength)
{
	if (theLHSLength != theRHSLength)
	{
		return false;
	}
	else if (theLHSLength == 0)
	{
		return true;
	}
	else
	{
		const XalanDOMChar* const	theEnd = theLHS + theLHSLength;

		while(*theLHS == *theRHS)
		{
			++theLHS;

			if (theLHS == theEnd)
			{
				return true;
			}
			else
			{
				++theRHS;
			}
		}

		return false;
	}
}



bool
XalanDOMString::equals(
			const XalanDOMString&	theLHS,
			const XalanDOMString&	theRHS)
{
	const XalanDOMString::size_type		theLHSLength = theLHS.size();
	const XalanDOMString::size_type		theRHSLength = theRHS.size();

	if (theLHSLength != theRHSLength)
	{
		return false;
	}
	else
	{
		return equals(theLHS.c_str(), theLHSLength, theRHS.c_str(), theRHSLength);
	}
}



XalanDOMString::size_type
XalanDOMString::length(const XalanDOMChar*	theString)
{
	return ::length(theString);
}



XalanDOMString::size_type
XalanDOMString::length(const char*	theString)
{
	assert(theString != 0);

	assert(strlen(theString) < real_size_type(npos));

	return size_type(strlen(theString));
}



#if defined(XALAN_USE_XERCES_LOCAL_CODEPAGE_TRANSCODERS)



#include <util/XMLString.hpp>



template <class SourceType, class TargetType, class SizeType, class LengthFunctionType>
bool
doXercesTranscode(
			const SourceType*			theSourceString,
			SizeType					theSourceStringLength,
			bool						theSourceStringIsNullTerminated,
#if defined(XALAN_NO_NAMESPACES)
			vector<TargetType>&			theTargetVector,
#else
			std::vector<TargetType>&	theTargetVector,
#endif
			bool						terminate,
			LengthFunctionType			theLengthFunction)
{
	const SourceType*	theRealSourceString = theSourceString;

	SizeType			theRealSourceStringLength = theSourceStringLength;

	XalanArrayAutoPtr<SourceType>		theGuard;

	if (theSourceStringIsNullTerminated == true)
	{
		theRealSourceStringLength = theLengthFunction(theSourceString);
	}
	else
	{
		theGuard.reset(new SourceType[theRealSourceStringLength + 1]);
		assert(theGuard.get() != 0);

		for (SizeType index = 0; index < theRealSourceStringLength; ++index)
		{
			theGuard[index] = theSourceString[index];
		}

		theGuard[theRealSourceStringLength] = SourceType(0);

		theRealSourceString = theGuard.get(); 
	}

	// Initially, let's guess the the transcoded string will be of the same
	// length as the UTF-16 string.
	theTargetVector.resize(theRealSourceStringLength + 1, TargetType(0));

	assert(theRealSourceString != 0);

	unsigned int	theAttempts = 0;
	bool			fSuccess = false;

	do
	{
		// $$$ ToDo: We should use the Xerces transcoder interface
		// instead of XMLString::transcode(), so we can better control
		// error handling and failures due to inadequate space.
		fSuccess = XMLString::transcode(
					theRealSourceString,
					&*theTargetVector.begin(),
					theTargetVector.size() - 1);

		if (fSuccess == false)
		{
			if (theAttempts > 2)
			{
				break;
			}
			else
			{
				++theAttempts;

				theTargetVector.resize(theTargetVector.size() + 10, TargetType(0));
			}
		}
	} while (fSuccess == false);

	if (fSuccess == false)
	{
		theTargetVector.clear();
	}
	else if (terminate == false)
	{
		while(theTargetVector.back() == TargetType(0))
		{
			theTargetVector.pop_back();
		}
	}

	return fSuccess;
}

#endif



static bool
doTranscodeToLocalCodePage(
			const XalanDOMChar*			theSourceString,
			XalanDOMString::size_type	theSourceStringLength,
			bool						theSourceStringIsNullTerminated,
			CharVectorType&				theTargetVector,
			bool						terminate)
{
	typedef XalanDOMString::real_size_type	real_size_type;

    // Short circuit if it's a null pointer, or of length 0.
    if (!theSourceString || (!theSourceString[0]))
    {
		if (terminate == true)
		{
			theTargetVector.resize(1);

			theTargetVector.back() = '\0';
		}
		else
		{
			theTargetVector.clear();
		}

        return true;
	}
#if defined(XALAN_USE_XERCES_LOCAL_CODEPAGE_TRANSCODERS)
	else
	{
		return doXercesTranscode(
					theSourceString,
					theSourceStringLength,
					theSourceStringIsNullTerminated,
					theTargetVector,
					terminate,
					length);
	}
#else
	const wchar_t*	theTempSource = 0;

	// If our char sizes are not the same, or the input string is not null-terminated,
	// we have to use a temporary buffer.
	XalanArrayAutoPtr<wchar_t>	theTempSourceJanitor;

#if !defined(XALAN_XALANDOMCHAR_USHORT_MISMATCH)
	// This is a short-cut for when the theSourceString is mull-terminated _and_
	// XalanDOMChar and wchar_t are the same thing.
	if (theSourceStringIsNullTerminated == true)
	{
		theTempSource = theSourceString;
	}
	else
#endif
	{
		if (theSourceStringIsNullTerminated == true)
		{
			theSourceStringLength = length(theSourceString);
		}

		theTempSourceJanitor.reset(new wchar_t[real_size_type(theSourceStringLength) + 1]);

		for (size_t	index = 0; index < size_t(theSourceStringLength); ++index)
		{
			theTempSourceJanitor[index] = wchar_t(theSourceString[index]);
		}

		theTempSourceJanitor[size_t(theSourceStringLength)] = 0;

		theTempSource = theTempSourceJanitor.get();
	}

    // See how many chars we need to transcode.
    const size_t	targetLen = ::wcstombs(0, theTempSource, 0);

	if (targetLen == size_t(-1))
	{
		return false;
	}
	else
	{
		// Resize, adding one byte if terminating...
		theTargetVector.resize(terminate == true ? targetLen + 1 : targetLen);

		//  And transcode our temp source buffer to the local buffer. Terminate
		//
		if (wcstombs(&theTargetVector[0], theTempSource, targetLen) == size_t(-1))
		{
			theTargetVector.clear();

			return false;
		}
		else
		{
			if (terminate == true)
			{
				theTargetVector.back() = '\0';
			}

			return true;
		}
	}
#endif
}



XALAN_DOM_EXPORT_FUNCTION(bool)
TranscodeToLocalCodePage(
			const XalanDOMChar*			theSourceString,
			XalanDOMString::size_type	theSourceStringLength,
			CharVectorType&				theTargetVector,
			bool						terminate)
{
	return doTranscodeToLocalCodePage(theSourceString, theSourceStringLength, false, theTargetVector, terminate);
}



XALAN_DOM_EXPORT_FUNCTION(bool)
TranscodeToLocalCodePage(
			const XalanDOMChar*		theSourceString,
			CharVectorType&			theTargetVector,
			bool					terminate)
{
	return doTranscodeToLocalCodePage(theSourceString, 0, true, theTargetVector, terminate);
}



static bool
doTranscodeFromLocalCodePage(
			const char*					theSourceString,
			XalanDOMString::size_type	theSourceStringLength,
			bool						theSourceStringIsNullTerminated,
			XalanDOMCharVectorType&		theTargetVector,
			bool						terminate)
{
	typedef XalanDOMString::size_type	size_type;

    // Short circuit if it's a null pointer, or of length 0.
    if (!theSourceString || (!theSourceString[0]))
    {
		if (terminate == true)
		{
			theTargetVector.resize(1);

			theTargetVector.back() = '\0';
		}
		else
		{
			theTargetVector.clear();
		}

        return true;
	}
#if defined(XALAN_USE_XERCES_LOCAL_CODEPAGE_TRANSCODERS)
	else
	{
		return doXercesTranscode(
					theSourceString,
					theSourceStringLength,
					theSourceStringIsNullTerminated,
					theTargetVector,
					terminate,
					strlen);
	}
#else
	if (theSourceStringIsNullTerminated == true)
	{
		assert(strlen(theSourceString) < XalanDOMString::npos);

		theSourceStringLength = size_type(strlen(theSourceString));
	}

    // See how many chars we need to transcode.
	const size_t	theTargetLength =
			::mbstowcs(0, theSourceString, size_t(theSourceStringLength));

	if (theTargetLength == size_t(-1))
	{
		return false;
	}
	else
	{
#if defined(XALAN_XALANDOMCHAR_USHORT_MISMATCH)
		typedef XalanDOMString::WideCharVectorType	WideCharVectorType;

		WideCharVectorType	theTempResult;

		theTempResult.resize(terminate == true ? theTargetLength + 1 : theTargetLength);

		wchar_t* const	theTargetPointer = &theTempResult[0];
#else
		theTargetVector.resize(terminate == true ? theTargetLength + 1 : theTargetLength);

		wchar_t* const	theTargetPointer = &theTargetVector[0];
#endif

		if (mbstowcs(theTargetPointer, theSourceString, size_t(theSourceStringLength)) == size_t(-1))
		{
			theTargetVector.clear();

			return false;
		}
		else
		{
#if defined(XALAN_XALANDOMCHAR_USHORT_MISMATCH)
			const WideCharVectorType::size_type		theTempSize = theTempResult.size();

			theTargetVector.reserve(theTempSize);

			for(WideCharVectorType::size_type i = 0; i < theTempSize; ++i)
			{
				theTargetVector.push_back(theTempResult[i]);
			}
#endif

			if (terminate == true)
			{
				theTargetVector.back() = '\0';
			}

			return true;
		}
	}
#endif
}



XALAN_DOM_EXPORT_FUNCTION(bool)
TranscodeFromLocalCodePage(
			const char*					theSourceString,
			XalanDOMString::size_type	theSourceStringLength,
			XalanDOMCharVectorType&		theTargetVector,
			bool						terminate)
{
	return doTranscodeFromLocalCodePage(theSourceString, theSourceStringLength, false, theTargetVector, terminate);
}



XALAN_DOM_EXPORT_FUNCTION(bool)
TranscodeFromLocalCodePage(
			const char*					theSourceString,
			XalanDOMCharVectorType&		theTargetVector,
			bool						terminate)
{
	return doTranscodeFromLocalCodePage(theSourceString, 0, true, theTargetVector, terminate);
}
