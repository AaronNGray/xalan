/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2004 The Apache Software Foundation.  All rights 
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



#include <cstdio>

#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iostream>
#endif

// This is here for memory leak testing. 
#if !defined(NDEBUG) && defined(_MSC_VER)
#include <crtdbg.h>
#endif



#include <xercesc/util/PlatformUtils.hpp>



#include <xalanc/PlatformSupport/XalanUnicode.hpp>



#include <xalanc/XSLT/XSLTInputSource.hpp>
#include <xalanc/XSLT/XSLTResultTarget.hpp>



#include <xalanc/XalanTransformer/XalanTransformer.hpp>



#include <Harness/XMLFileReporter.hpp>
#include <Harness/FileUtility.hpp>
#include <Harness/HarnessInit.hpp>



XALAN_USING_STD(cerr)
XALAN_USING_STD(cout)
XALAN_USING_STD(endl)



XALAN_USING_XALAN(FileUtility)
XALAN_USING_XALAN(XalanDOMString)



void
setHelp(FileUtility&	h)
{
	h.args.getHelpStream() << endl
		 << "params dirname [-out]"
		 << endl
		 << endl
		 << "dirname		(base directory for \'capi\' testcases)"
		 << endl
		 << "-out dirname	(base directory for output)"
		 << endl;
}



//	This function returns the testcase number.  All of these tests are called
//	params0X, and there are only 6 of them,  so we can pick off the
//	second X to determine what test number we're dealing with.  We need to
//	know which test because each test gets different parameters. This code will
//  need modification if the number of tests changes.
int
getTestNumber(const XalanDOMString&		theFile)
{
	assert(8 < theFile.length());

	return theFile[7] - XALAN_CPP_NAMESPACE_QUALIFIER XalanUnicode::charDigit_0;
}



int
runTests(
			int		argc,
			char*	argv[])
{
	int				theResult = 0;

	XALAN_USING_XALAN(HarnessInit)

	HarnessInit		xmlPlatformUtils;

	FileUtility		h;

	char testCase[15];
	XalanDOMString fileName, theGoldFile;
	const XalanDOMString  currentDir("params");

	// Set the program help string,  then get the command line parameters.
	//
	setHelp(h);

	// Get the command line parameters.
	//
	if (h.getParams(argc, argv, "PARAMS-RESULTS") == true)
	{
		const XalanDOMString	extDir(h.args.base + currentDir);

		// Check that the base directory is correct.
		if ( !h.checkDir(extDir) )
		{
			cout << "Invalid base directory - " << extDir << endl;
			cout << h.args.getHelpMessage();

			theResult = -1;
		}
		else
		{
			XALAN_USING_XALAN(XalanTransformer)
			XALAN_USING_XALAN(XMLFileReporter)

			XalanTransformer	xalan;

			// Generate Unique Run id. (Only used to name the result logfile.)
			const XalanDOMString	UniqRunid = h.generateUniqRunid();

			// Defined basic constants for file manipulation
			const XalanDOMString	drive(h.getDrive());
			const XalanDOMString	resultFilePrefix("params");
			const XalanDOMString	resultsFile(drive + h.args.output + resultFilePrefix + UniqRunid + FileUtility::s_xmlSuffix);
			
			XMLFileReporter		logFile(resultsFile);

			logFile.logTestFileInit("Param Testing: Testing ability to pass parameters to stylesheets. ");

			try
			{
				bool embedFlag =  false;
					
				// Get the files found in the "params" directory
				const XalanDOMString  theOutputDir = h.args.output + currentDir;

				// Check that output directory is there.
				h.checkAndCreateDir(theOutputDir);

				typedef FileUtility::FileNameVectorType		FileNameVectorType;

				const FileNameVectorType	files = h.getTestFileNames(h.args.base, currentDir, true);
				logFile.logTestCaseInit(currentDir);

				for(FileNameVectorType::size_type i = 0; i < files.size(); ++i)
				{
					fileName = files[i];
					sprintf(testCase, "%s%d","TestCase",i+1);
					h.data.testOrFile = testCase;

					// Set up the input/output files.
					const XalanDOMString  theXSLFile= h.args.base + currentDir + FileUtility::s_pathSep + fileName;
					XalanDOMString		  theXMLFile;
					
					// Neither testcase 7 nor 8 utilize xml source files. Both use fragment identifiers,
					// so the generation of xml file is unnecessary.
					// Testcase 7 tests: <?xml-stylesheet type="text/xsl" href="#style1-23.34.123456789_345"?>
					// Testcase 8 tests: <?xml-stylesheet type="text/xsl" href="foo.xsl"?>
					if ( i+1 <= 6 )
					{
						theXMLFile = h.generateFileName(theXSLFile, "xml");
					}

					h.data.xmlFileURL = theXMLFile;
					h.data.xslFileURL = theXSLFile;

					const XalanDOMString  theOutput =  h.args.output + currentDir + FileUtility::s_pathSep + fileName; 
					const XalanDOMString  theOutputFile = h.generateFileName(theOutput, "out");
					theGoldFile = h.args.gold + currentDir + FileUtility::s_pathSep + fileName;
					theGoldFile = h.generateFileName(theGoldFile, "out");

					XALAN_USING_XALAN(XSLTResultTarget);
					XALAN_USING_XALAN(XSLTInputSource);

					const XSLTResultTarget	theResultTarget(theOutputFile);
					const XSLTInputSource	xslInputSource(theXSLFile);
					const XSLTInputSource	xmlInputSource(theXMLFile);
							
					// Set the desired parameters
					switch (getTestNumber(fileName))
					{	
						case 2:
							xalan.setStylesheetParam("in1", "'A '");

							xalan.setStylesheetParam("in2", "'B '");

							xalan.setStylesheetParam(
								XalanDOMString("in3"),
								XalanDOMString("'C '"));
							xalan.setStylesheetParam(
								XalanDOMString("in4"),
								XalanDOMString("'D '"));
							xalan.setStylesheetParam(
								XalanDOMString("in5"),
								XalanDOMString("'E '"));
							break;

						case 3:
							xalan.setStylesheetParam(
								XalanDOMString("'xyz:in1'"),
								XalanDOMString("'DATA'"));
							break;

						case 7:
							{
								const XSLTInputSource	embed07InputSource(theXSLFile);
								xalan.transform(embed07InputSource, theResultTarget);
								h.data.testOrFile += XALAN_STATIC_UCODE_STRING(" (Embed01)");
								embedFlag = true;
								break;
							}

						case 8:
							{
								const XSLTInputSource	embed08InputSource(theXSLFile);
								xalan.transform(embed08InputSource, theResultTarget);
								h.data.testOrFile += XALAN_STATIC_UCODE_STRING(" (Embed02)");
								embedFlag = true;
								break;
							}
						default:
							xalan.setStylesheetParam(
								XalanDOMString("input"),
								XalanDOMString("'testing 1 2 3'"));
							break;
					}

					// Do a total end to end transform with no pre parsing of either xsl or xml files.
					if (!embedFlag)
					{
						xalan.transform(xmlInputSource, xslInputSource, theResultTarget);
					}

					// Check and report the results.
					h.checkResults(theOutputFile, theGoldFile, logFile);
				}
								
				logFile.logTestCaseClose("Done", "Pass");
			}
			catch(...)
			{
				cerr << "Exception caught!!!" << endl << endl;

				theResult = -1;
			}

			h.reportPassFail(logFile, UniqRunid);
			logFile.logTestFileClose("Param Testing: ", "Done");
			logFile.close();

			h.analyzeResults(xalan, resultsFile);
		}
	}

	return theResult;
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

	int	theResult = 0;

	try
	{
		XALAN_USING_XERCES(XMLPlatformUtils)

		XALAN_USING_XALAN(XalanTransformer)

		// Call the static initializers for xerces and xalan, and create a transformer
		//
		XMLPlatformUtils::Initialize();

		XalanTransformer::initialize();

		theResult = runTests(argc, argv);

		XalanTransformer::terminate();

		XMLPlatformUtils::Terminate();

		XalanTransformer::ICUCleanUp();
	}
	catch(...)
	{
		cerr << "Initialization failed!" << endl << endl;

		theResult = -1;
	}

	return theResult;
}
