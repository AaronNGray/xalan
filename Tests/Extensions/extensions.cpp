/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2002 The Apache Software Foundation.  All rights 
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
#include <strstream.h>
#else
#include <iostream>
#include <strstream>
#endif



// This is here for memory leak testing. 
#if !defined(NDEBUG) && defined(_MSC_VER)
#include <crtdbg.h>
#endif



#include <xercesc/util/PlatformUtils.hpp>



// EXTENSION HEADERS...
#include <xalanc/XalanExtensions/FunctionDifference.hpp>
#include <xalanc/XalanExtensions/FunctionDistinct.hpp>
#include <xalanc/XalanExtensions/FunctionEvaluate.hpp>
#include <xalanc/XalanExtensions/FunctionHasSameNodes.hpp>
#include <xalanc/XalanExtensions/FunctionIntersection.hpp>
#include <xalanc/XalanExtensions/FunctionNodeSet.hpp>



#include <xalanc/XalanTransformer/XalanTransformer.hpp>



// HARNESS HEADERS...
#include <Harness/XMLFileReporter.hpp>
#include <Harness/FileUtility.hpp>
#include <Harness/HarnessInit.hpp>



XALAN_USING_STD(cerr)
XALAN_USING_STD(cout)
XALAN_USING_STD(endl)



// GLOBAL VARIABLES...
const char* const	resultString = "The specified function is not available: http://xml.apache.org/xalan:nodeset";


XALAN_USING_XALAN(FileUtility)
XALAN_USING_XALAN(XalanDOMString)
XALAN_USING_XALAN(XalanTransformer)
XALAN_USING_XALAN(XMLFileReporter)
XALAN_USING_XALAN(XSLTInputSource)
XALAN_USING_XALAN(XSLTResultTarget)



void
setHelp(FileUtility&	h)
{
	h.args.getHelpStream() << endl
		 << "extensions dirname [-out]"
		 << endl
		 << endl
		 << "dirname		(base directory for xml-xalan\\test\\tests\\extensions)"
		 << endl
		 << "-out dirname	(base directory for output)"
		 << endl;
}


// Generate the various filenames needed for testing.
void
generateFiles(
			const XalanDOMString&	fileName,
			const XalanDOMString&	currentDir,
			XalanDOMString&			xml, 
			XalanDOMString&			xsl,
			XalanDOMString&			out,
			XalanDOMString&			gold,
			const char*				test,
			FileUtility&			h)
{
	// Set up the input/output files.
	const XalanDOMString testName(h.generateFileName(fileName,"out"));

	xsl = h.args.base + currentDir + FileUtility::s_pathSep + fileName;
	xml = h.generateFileName(xsl,"xml");
	h.data.xmlFileURL = xml;
	h.data.xslFileURL = xsl;

	out =  h.args.output + currentDir + FileUtility::s_pathSep + XalanDOMString(test) + testName; 

	gold = h.args.gold + currentDir + FileUtility::s_pathSep + testName;

}

//	TestCase1
//  API Call: 
//		None. Verfies default behavior of XalanTransformer.
//	Comments:
//		This testcase is called once for each function that XalanC implements. It verfies that the function 
//		was properly installed and working correctly within the transformer.  All functions are preinstalled
//		globally. Currently XalanC supports the following extensions; difference, distinct, evaluate, 
//		hasSameNodes, intersection and nodeset. 
//		 
void
TestCase1(
			XalanTransformer&		xalan,
			const XalanDOMString&	fileName,
			const XalanDOMString&	currentDir,
			XMLFileReporter&		logFile,
			FileUtility&			h)
{
	
	XalanDOMString	xml, xsl, theOutputFile, theGoldFile;
		
	generateFiles(fileName, currentDir, xml, xsl, theOutputFile, theGoldFile, "tc1-", h);

	h.data.testOrFile = XalanDOMString("TestCase1: ") + fileName;
	h.data.xmlFileURL = xml;
	h.data.xslFileURL = xsl;

	// Create the InputSources and ResultTraget.
	const XSLTInputSource	xmlInputSource(xml);
	const XSLTInputSource	xslInputSource(xsl);
	const XSLTResultTarget	theResultTarget(theOutputFile);

	// Perform the transform and check the results.
	xalan.transform(xmlInputSource, xslInputSource, theResultTarget);	
	h.checkResults(theOutputFile, theGoldFile, logFile);

}

//	TestCase2
//  API Call:
//		XalanTransformer::uninstallExternalFunctionGlobal
//	Comments:
//		This test verifies that the 'nodeset' function is properly uninstalled via the api.
//		Output file should NOT contain data. 
//
void
TestCase2(
			XalanTransformer&		xalan,
			const XalanDOMString&	fileName,
			const XalanDOMString&	currentDir,
			const XalanDOMString&	theNamespace,
			XMLFileReporter&		logFile,
			FileUtility&			h)
{	

	XalanDOMString	xml, xsl, theOutputFile, theGoldFile;
	
	generateFiles(fileName, currentDir, xml, xsl, theOutputFile, theGoldFile, "tc2-", h);
	h.data.testOrFile = XalanDOMString("TestCase2");
	h.data.xmlFileURL = xml;
	h.data.xslFileURL = xsl;

	// Create the InputSources and ResultTraget.
	const XSLTInputSource	xmlInputSource(xml);
	const XSLTInputSource	xslInputSource(xsl);
	const XSLTResultTarget	theResultTarget(theOutputFile);

	// UnInstall the external Global function "nodeset"
	xalan.uninstallExternalFunctionGlobal(
					theNamespace,
					XalanDOMString("nodeset"));

	//Perform the transform and check the results.
	xalan.transform(xmlInputSource, xslInputSource, theResultTarget);

	h.checkAPIResults(xalan.getLastError(), 
						  resultString,
						  "transformer.uninstallExternalFunctionGlobal()",
						  logFile,
						  theOutputFile,
						  theGoldFile,
						  true);
}
//	TestCase3:
//  API Call:	
//		XalanTransformer::installExternalFunction
//		XalanTransformer::uninstallExternalFunction
//  Comments:
//		This tests the installExternalFunction method of XalanTransformer using the nodeset function.
//		Output file should NOT contain data.
//
void TestCase3(
			XalanTransformer&		xalan,
			const XalanDOMString&	fileName,
			const XalanDOMString&	currentDir,
			const XalanDOMString&	theNamespace,
			XMLFileReporter&		logFile,
			FileUtility&			h)
{
	XALAN_USING_XALAN(FunctionNodeSet)

	XalanDOMString	xml, xsl, theOutputFile, theGoldFile;
	
	generateFiles(fileName, currentDir, xml, xsl, theOutputFile, theGoldFile, "tc3-", h);

	h.data.testOrFile = XalanDOMString("TestCase3a");
	h.data.xmlFileURL = xml;
	h.data.xslFileURL = xsl;

	// Create the InputSources and ResultTraget.
	const XSLTInputSource	xmlInputSource(xml);
	const XSLTInputSource	xslInputSource(xsl);
	const XSLTResultTarget	theResultTarget(theOutputFile);

	// Install the external function "nodeset"
	xalan.installExternalFunction(theNamespace,
								  XalanDOMString("nodeset"),
								  FunctionNodeSet());

	// Perform the transform and check the results.
	xalan.transform(xmlInputSource, xslInputSource, theResultTarget);

	h.checkResults(theOutputFile, theGoldFile, logFile);

	// Because we install the function locally, this second instance of the transformer 
	// should _NOT_ run the test successfully.
	XalanTransformer newEngine;
	h.data.testOrFile = XalanDOMString("TestCase3b");

	//Perform the transform and check the results.
	newEngine.transform(xmlInputSource, xslInputSource, theResultTarget);
	h.checkAPIResults(newEngine.getLastError(), 
							   resultString,
						       "transformer.installExternalFunction()",
						       logFile,
							   theOutputFile,
							   theGoldFile,
							   true);

	// Now unInstall the external function "nodeset". Once again the transform should
	// _NOT_ run the test successfully
	h.data.testOrFile = XalanDOMString("TestCase3c");
	xalan.uninstallExternalFunction(theNamespace, XalanDOMString("nodeset"));

	// Perform the transform and check the results.
	xalan.transform(xmlInputSource, xslInputSource, theResultTarget);
	h.checkAPIResults(xalan.getLastError(), 
							   resultString,
						       "transformer.uninstallExternalFunction()",
						       logFile,
							   theOutputFile,
							   theGoldFile,
							   true);

}

//	TestCase4:
//  API Call: 
//		XalanTransformer::installExternalFunctionGlobal
//	Comments:
//		This tests uses transformer method installExternalFunctionGlobal to add the nodeset function. 
//		The output file should contain data.
//
void TestCase4(
			XalanTransformer&		xalan,
			const XalanDOMString&	fileName,
			const XalanDOMString&	currentDir,
			const XalanDOMString&	theNamespace,
			XMLFileReporter&		logFile,
			FileUtility&			h)
{
	XALAN_USING_XALAN(FunctionNodeSet)
	
	XalanDOMString	xml, xsl, theOutputFile, theGoldFile;

	generateFiles(fileName, currentDir, xml, xsl, theOutputFile, theGoldFile, "tc4-", h);
	h.data.testOrFile = XalanDOMString("TestCase4a");
	h.data.xmlFileURL = xml;
	h.data.xslFileURL = xsl;

	// Create the InputSources and ResultTraget.
	const XSLTInputSource	xmlInputSource(xml);
	const XSLTInputSource	xslInputSource(xsl);
	const XSLTResultTarget	theResultTarget(theOutputFile);

	// Install the external function "nodeset" Globally
	xalan.installExternalFunctionGlobal(theNamespace,
										XalanDOMString("nodeset"),
										FunctionNodeSet());

	// Perform the transform and check the results.
	xalan.transform(xmlInputSource, xslInputSource, theResultTarget);
	h.checkResults(theOutputFile, theGoldFile, logFile);

	// Create a second transformer and verify that it can 'see' the extension as well...
	XalanTransformer newEngine;
	h.data.testOrFile = XalanDOMString("TestCase4b");

	newEngine.transform(xmlInputSource, xslInputSource, theResultTarget);
	h.checkResults(theOutputFile, theGoldFile, logFile);

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

	// Set the program help string,  then get the command line parameters.
	//
	setHelp(h);	

	if (h.getParams(argc, argv, "EXTENSION-RESULTS") == true)
	{
		const XalanDOMString	currentDir("library");
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
			try
			{
				// Generate Unique Run id. (Only used to name the result logfile.)
				const XalanDOMString	UniqRunid = h.generateUniqRunid();

				// Defined basic constants for file manipulation 
				const XalanDOMString	drive(h.getDrive());
				const XalanDOMString	resultsFile(drive + h.args.output + currentDir + UniqRunid + FileUtility::s_xmlSuffix);
				
				XMLFileReporter	logFile(resultsFile);
				logFile.logTestFileInit("C++ Extension Testing. ");
				logFile.logTestCaseInit(currentDir);

				cout << "Performing Extension testing ..." << endl;

				XalanTransformer	xalan;				
						
				// Check that output directory is there.
				XalanDOMString		fileName;
						
				const XalanDOMString	theOutputDir(h.args.output + currentDir);

				h.checkAndCreateDir(theOutputDir);

				typedef FileUtility::FileNameVectorType		FileNameVectorType;

				// Get the files found in the "cextension" directory
				const FileNameVectorType	files = h.getTestFileNames(h.args.base, currentDir, true);

				// TestCase1 is used to verify correct functioning of the default extension functions
				TestCase1(xalan, files[0], currentDir, logFile, h);	// Difference function
				TestCase1(xalan, files[1], currentDir, logFile, h);	// Distinct 
				TestCase1(xalan, files[2], currentDir, logFile, h);	// Evaluate 
				TestCase1(xalan, files[3], currentDir, logFile, h);	// HasSameNodes 
				TestCase1(xalan, files[4], currentDir, logFile, h);	// Intersection 
				TestCase1(xalan, files[5], currentDir, logFile, h);	// NodeSet01 - basic testing
				TestCase1(xalan, files[6], currentDir, logFile, h);	// NodeSet02 - extensive RTF testing. 

				const XalanDOMString	theNamespace("http://xml.apache.org/xalan");

				// These testcases are used to test the Install/Uninstall Function API's of the transformer.
				TestCase2(xalan, files[5], currentDir, theNamespace, logFile, h);
				TestCase3(xalan, files[5], currentDir, theNamespace, logFile, h);
				TestCase4(xalan, files[5], currentDir, theNamespace, logFile, h);

				logFile.logTestCaseClose("Done", "Pass");
				h.reportPassFail(logFile, UniqRunid);
					
				logFile.logTestFileClose("C++ Extension Testing: ", "Done");
				logFile.close();

				h.analyzeResults(xalan, resultsFile);
			}
			catch(...)
			{
				cerr << "Exception caught!!!" << endl << endl;

				theResult = -1;
			}
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
