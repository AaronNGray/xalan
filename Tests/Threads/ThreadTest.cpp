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

// Base header file.  Must be first.
#include <xalanc/Include/PlatformDefinitions.hpp>



#include <cassert>
#include <ctime>



#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iostream>
#endif



#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/Mutexes.hpp>



#include <xalanc/Include/XalanAutoPtr.hpp>



#include <xalanc/XalanTransformer/XalanTransformer.hpp>



#if defined(WIN32)

#include <csignal>
#include <process.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#elif defined(XALAN_POSIX2_AVAILABLE)

#include <csignal>

// This is a workaround for a Tru64 compiler bug...
#if defined(XALAN_STRICT_ANSI_HEADERS) && defined(TRU64)
#include <csetjmp>
typedef long sigjmp_buf[_JBLEN];
#endif
#include <pthread.h>
#include <unistd.h>

#else
#error Unsupported platform!
#endif



XALAN_USING_STD(cerr)
XALAN_USING_STD(cout)
XALAN_USING_STD(endl)


	
#if defined(XALAN_STRICT_ANSI_HEADERS)
	using std::atoi;
	using std::signal;
	using std::strcmp;
#endif

	
	
	// This is here for memory leak testing.
#if defined(_DEBUG)
#include <crtdbg.h>
#endif



typedef XERCES_CPP_NAMESPACE_QUALIFIER XMLMutex			XMLMutexType;
typedef XERCES_CPP_NAMESPACE_QUALIFIER XMLMutexLock		XMLMutexLockType;



class SynchronizedCounter
{
public:

	SynchronizedCounter();

	~SynchronizedCounter();

	void
	increment();

	void
	decrement();

	long
	getCounter() const;

private:

	XMLMutexType	m_mutex;

	long			m_counter;
};



SynchronizedCounter::SynchronizedCounter() :
	m_mutex(),
	m_counter(0)
{
}



SynchronizedCounter::~SynchronizedCounter()
{
}



void
SynchronizedCounter::increment()
{
	const XMLMutexLockType	theLock(&m_mutex);

	if (m_counter < LONG_MAX)
	{
		++m_counter;
	}
}



void
SynchronizedCounter::decrement()
{
	const XMLMutexLockType	theLock(&m_mutex);

	if (m_counter > 0)
	{
		--m_counter;
	}
}



long
SynchronizedCounter::getCounter() const
{
	return m_counter;
}



struct
ThreadInfo
{
	ThreadInfo(
			long					theThreadNumber = 0L,
			SynchronizedCounter*	theCounter = 0) :
		m_threadNumber(theThreadNumber),
		m_counter(theCounter),
		m_done(false)
	{
	}

	long					m_threadNumber;

	SynchronizedCounter*	m_counter;

	bool					m_done;
};



XALAN_USING_XALAN(XalanCompiledStylesheet)
XALAN_USING_XALAN(XalanDOMChar)
XALAN_USING_XALAN(XalanDOMString)
XALAN_USING_XALAN(XalanParsedSource)



// Used to hold compiled stylesheet and pre-parsed source...
const XalanCompiledStylesheet*	glbCompiledStylesheet = 0;
const XalanParsedSource*		glbParsedSource = 0;
bool							fContinue = true;

const XalanDOMChar*				theStylesheetFileName = 0;
const XalanDOMChar*				theSourceFileName = 0;


#if defined(WIN32)
static BOOL __stdcall
signalHandler(DWORD		theSignalType)
{
	if (theSignalType == CTRL_C_EVENT ||
		theSignalType == CTRL_BREAK_EVENT)
	{
		fContinue = false;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
#elif defined(XALAN_POSIX2_AVAILABLE)
extern "C"
{
static void
signalHandler(int)
{
	fContinue = false;
}
}
#else
#error Unsupported platform!
#endif



#if defined(WIN32)

extern "C"
{
	void thePreparsedThreadRoutine(void* param);

	typedef void (*ThreadRoutineType)(void* param);
}

void
#elif defined(XALAN_POSIX2_AVAILABLE)

extern "C"
{
	void* thePreparsedThreadRoutine(void* param);

	typedef void* (*ThreadRoutineType)(void* param);
}

void*
#else
#error Unsupported platform!
#endif
thePreparsedThreadRoutine(void*		param)
{
// This routine uses compiled stylesheet (glbStylesheetRoot), which is set using the 
// theProcessor.setStylesheetRoot method. The transform is done using the theProcessor's
// process() method.

#if defined(XALAN_OLD_STYLE_CASTS)
	ThreadInfo* const		theInfo = (ThreadInfo*)param;
#else
	ThreadInfo* const		theInfo = reinterpret_cast<ThreadInfo*>(param);
#endif

	assert(theInfo != 0);

	theInfo->m_counter->increment();

	try
	{
		XALAN_USING_XALAN(LongToDOMString)
		XALAN_USING_XALAN(XalanTransformer)

		// Our input file.  The assumption is that the executable will be run
		// from same directory as the input files.

		// Generate the output file name.
		const XalanDOMString	theOutputFile(
				XalanDOMString("birds") +
				LongToDOMString(theInfo->m_threadNumber) +
				XalanDOMString(".out"));

		// Create a transformer...
		XalanTransformer	theTransformer;

		// Do the transform...
		theTransformer.transform(*glbParsedSource, glbCompiledStylesheet, theOutputFile);
	}
	catch(...)
	{
		cerr << "Exception caught in thread " << theInfo->m_threadNumber;
	}

	// Decrement the counter because we're done...
	theInfo->m_counter->decrement();

	theInfo->m_done = true;

#if defined(XALAN_POSIX2_AVAILABLE)
	return 0;
#endif
}



#if defined(WIN32)

extern "C" void theUnparsedThreadRoutine(void* param);

void
#elif defined(XALAN_POSIX2_AVAILABLE)

extern "C" void* theUnparsedThreadRoutine(void* param);

void*
#else
#error Unsupported platform!
#endif
theUnparsedThreadRoutine(void*		param)
{
// This routine compiles a stylesheet and a source document

#if defined(XALAN_OLD_STYLE_CASTS)
	ThreadInfo* const		theInfo = (ThreadInfo*)param;
#else
	ThreadInfo* const		theInfo = reinterpret_cast<ThreadInfo*>(param);
#endif

	assert(theInfo != 0);

	theInfo->m_counter->increment();

	try
	{
		XALAN_USING_XALAN(LongToDOMString)
		XALAN_USING_XALAN(XalanTransformer)

		// Our input file.  The assumption is that the executable will be run
		// from same directory as the input files.

		// Generate the output file name.
		const XalanDOMString	theOutputFile(
				XalanDOMString("birds") +
				LongToDOMString(theInfo->m_threadNumber) +
				XalanDOMString(".out"));

		// Create a transformer...
		XalanTransformer	theTransformer;

		assert(theSourceFileName != 0 && theStylesheetFileName != 0);

		// Do the transform...
		theTransformer.transform(
			theSourceFileName,
			theStylesheetFileName,
			theOutputFile);
	}
	catch(...)
	{
		cerr << "Exception caught in thread " << theInfo->m_threadNumber;
	}

	// Decrement the counter because we're done...
	theInfo->m_counter->decrement();

	theInfo->m_done = true;

#if defined(XALAN_POSIX2_AVAILABLE)
	return 0;
#endif
}



inline void
doSleep(unsigned int	theMilliseconds)
{
#if defined(WIN32)
	Sleep(theMilliseconds);
#elif defined(XALAN_POSIX2_AVAILABLE)
	usleep(theMilliseconds * 10);
#else
#error Unsupported platform!
#endif
}



bool
createThread(
			ThreadInfo&			theThreadInfo,
			ThreadRoutineType	theThreadRoutine)
{
	theThreadInfo.m_done = false;

#if defined(WIN32)

	const unsigned long		theThreadID =
			_beginthread(theThreadRoutine, 4096, reinterpret_cast<LPVOID>(&theThreadInfo));

	if (theThreadID == unsigned(-1))
	{
		theThreadInfo.m_done = true;

		return false;
	}
	else
	{
		return true;
	}

#elif defined(XALAN_POSIX2_AVAILABLE)

	pthread_t	theThread;

	const int	theResult = pthread_create(&theThread, 0, theThreadRoutine, (void*)&theThreadInfo);

	if (theResult != 0)
	{
		theThreadInfo.m_done = true;

		return false;
	}
	else
	{
#if defined(OS390)
		pthread_detach(&theThread);
#else
		pthread_detach(theThread);
#endif

		return true;
	}
#else
#error Unsupported platform!
#endif
}



void
doCountedThreads(
			const SynchronizedCounter&	theCounter,
			clock_t&					theClock)
{
	cout << "Waiting for active threads to finish..." << endl;

	unsigned int	theCheckCount = 0;

	do
	{
		doSleep(2000);

		// Check a couple of times, just in case, since
		// getCounter() is not synchronized...
		if (theCounter.getCounter() == 0)
		{
			if (theCheckCount == 0)
			{
				theClock = clock();
			}

			++theCheckCount;
		}
	}
	while(theCheckCount < 2);
}



void
startThread(
			ThreadInfo					theThreadInfo[],
			long						theThreadNumber)
{
	bool	fResult = false;

	const bool	fPreparsed = theThreadNumber % 2 == 0 ? true : false;

	if (fPreparsed == true)
	{
		fResult = createThread(theThreadInfo[theThreadNumber], thePreparsedThreadRoutine);
	}
	else
	{
		fResult = createThread(theThreadInfo[theThreadNumber], theUnparsedThreadRoutine);
	}

	if (fResult == false)
	{
		cerr << endl << "Unable to create thread!" << endl;
	}
	else
	{
		cout << "Started thread number " << theThreadNumber << ", using ";

		if (fPreparsed == true)
		{
			cout << "pre-parsed documents." << endl;
		}
		else
		{
			cout << "unparsed documents." << endl;
		}
	}
}



void
doContinuousThreads(
			const SynchronizedCounter&	theCounter,
			ThreadInfo					theThreadInfo[],
			long						theThreadCount,
			clock_t&					theClock)
{
	while(fContinue == true)
	{
		if (theCounter.getCounter() < theThreadCount)
		{
			for (long i = 0; i < theThreadCount && fContinue == true; ++i)
			{
				if (theThreadInfo[i].m_done == true)
				{
					startThread(theThreadInfo, i);
				}
			}
		}
	}

	doCountedThreads(theCounter, theClock);
}



void
doThreads(
			long	theThreadCount,
			bool	fContinuous)
{
	if (fContinuous == true)
	{
#if defined(WIN32)
		SetConsoleCtrlHandler(
				signalHandler,
				TRUE);
#elif defined(XALAN_POSIX2_AVAILABLE)
		signal(SIGINT, signalHandler);
#else
#error Unsupported platform!
#endif

		cout << endl << "Running in continuous mode." << endl;
	}

	cout << endl << "Starting " << theThreadCount << " threads." << endl;

	XALAN_USING_XALAN(XalanArrayAutoPtr)

	XalanArrayAutoPtr<ThreadInfo>	theThreadInfo(new ThreadInfo[theThreadCount]);

	try
	{
		cout << endl << "Clock before starting threads: " << clock() << endl;

		SynchronizedCounter		theCounter;

		long	i = 0;

		while (i < theThreadCount && fContinue == true)
		{
			theThreadInfo[i].m_threadNumber = i;
			theThreadInfo[i].m_counter = &theCounter;

			startThread(theThreadInfo.get(), i);

			++i;
		}

		clock_t		theClock = 0;

		if (i == 0)
		{
			cerr << endl << "No threads were created!" << endl;
		}
		else
		{
			if (fContinuous == true)
			{
				doContinuousThreads(
					theCounter,
					theThreadInfo.get(),
					theThreadCount,
					theClock);
			}
			else
			{
				doCountedThreads(theCounter, theClock);
			}
		}

		cout << endl << "Clock after threads: " << theClock << endl;
	}
	catch(...)
	{
		cerr << "Exception caught!!!"
			 << endl
			<< endl;
	}
}



void
Usage()
{
	cerr << "Usage: ThreadTest [-c] [count]"
		 << endl
		 << endl;
}



int
main(
			int		argc,
			char*	argv[])
{
#if !defined(NDEBUG) && defined(_MSC_VER)
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
#endif

	if (argc > 3)
	{
		Usage();
	}
	else
	{
		bool	fContinuous = false;
		int		threadCount = 0;

		if (argc == 1)
		{
			threadCount = 60;
		}
		else
		{
			if (strcmp(argv[1], "-c") == 0)
			{
				fContinuous = true;
			}

			if (argc == 2)
			{
				if (fContinuous == true)
				{
					threadCount = 60;
				}
				else
				{
					threadCount = atoi(argv[1]);
				}
			}
			else if (argc == 3)
			{
				if (fContinuous == true)
				{
					threadCount = atoi(argv[2]);
				}
				else
				{
					Usage();
				}
			}
		}

		if (threadCount > 0)
		{
			try
			{
				XALAN_USING_XERCES(XMLPlatformUtils)

				XALAN_USING_XALAN(XalanTransformer)

				// Initialize Xerces...
				XMLPlatformUtils::Initialize();

				// Initialize Xalan...
				XalanTransformer::initialize();

				try
				{
					// Create a XalanTransformer.  We won't actually use this to transform --
					// it's just acting as a factory for the compiled stylesheet and
					// pre-parsed source document.  Note that we can't let the individual
					// threads use this as a factory without serializing access to it, but
					// we can share the stylesheet and source document.
					XalanTransformer		theXalanTransformer;

					const XalanDOMString	theXSLFileName("birds.xsl");

					theStylesheetFileName = theXSLFileName.c_str();

					theXalanTransformer.compileStylesheet(theStylesheetFileName, glbCompiledStylesheet);
					assert(glbCompiledStylesheet != 0);

					// Compile the XML source document as well. All threads will use
					// this binary representation of the source tree.
					const XalanDOMString	theXMLFileName("birds.xml");

					theSourceFileName = theXMLFileName.c_str();

					theXalanTransformer.parseSource(theSourceFileName, glbParsedSource);
					assert(glbParsedSource != 0);

					doThreads(threadCount, fContinuous);

					theStylesheetFileName = 0;
					theSourceFileName = 0;
				}
				catch(...)
				{
					cerr << "Exception caught!!!"
						 << endl
						 << endl;
				}

				// Terminate Xalan...
				XalanTransformer::terminate();

				// Terminate Xerces...
				XMLPlatformUtils::Terminate();

				// Clean up the ICU, if it's integrated.
				XalanTransformer::ICUCleanUp();
			}
			catch(...)
			{
				cerr << "Initialization failed!!!"
					 << endl
					 << endl;
			}
		}
	} 

	return 0;
}
