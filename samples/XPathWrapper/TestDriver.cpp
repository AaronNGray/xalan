/*
 * Copyright 1999-2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
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

#include "XPathWrapper.hpp"



#include <xercesc/util/XMLException.hpp>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>



#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <fstream.h>
#include <iostream.h>
#else
#include <fstream>
#include <iostream>
#endif



// This is here for memory leak testing. 
#if !defined(NDEBUG) && defined(_MSC_VER)
#include <crtdbg.h>
#endif



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

    XALAN_USING_STD(cerr)
	XALAN_USING_STD(cout)
	XALAN_USING_STD(endl)
	XALAN_USING_STD(ifstream)

	if (argc < 4)
	{
		cerr << "Usage: TestDriver XMLFilePath Context XPathExpression" << endl;
		return -1;
	}

	XPathWrapper::ChVectorType	theXML;

	ifstream	in(argv[1]);

	// slow and dirty dump of the xml file into a buffer
	char c;
	while(in.get(c))
		theXML.push_back(c);
	theXML.push_back('\0');

	///////////////////////////////////////////..

	// create your XPath helper object
	XPathWrapper helper;

	try
	{
		// call evaluate, passing in the XML string, the context string and the xpath string
		const XPathWrapper::CharVectorTypeVectorType	result = helper.evaluate(&*theXML.begin(), argv[2], argv[3]);

		// take the resulting string vector	and do whatever you want with it:
		size_t len = result.size();

		cout << "the result set has " << len << " strings\n";

		for (size_t i=0; i<len; i++)
			cout << "item " << (i+1) << "= \"" << &*result[i].begin() << "\"" << endl;
	}
	catch(const XERCES_CPP_NAMESPACE_QUALIFIER XMLException&)
	{
		cerr << "Exception caught!  Exiting..." << endl;
	}

	return 0;
}
