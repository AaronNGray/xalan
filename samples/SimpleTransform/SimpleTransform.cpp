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

#include <xalanc/Include/PlatformDefinitions.hpp>



#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iostream>
#endif



#include <xercesc/util/PlatformUtils.hpp>



#include <xalanc/XalanTransformer/XalanTransformer.hpp>


#include "XalanMemoryManagerImpl.hpp"


int
main(
			int		argc,
			char*	/* argv */[])
{
	XALAN_USING_STD(cerr)
	XALAN_USING_STD(endl)

	int	theResult = -1;

	if (argc != 1)
	{
		cerr << "Usage: SimpleTransform"
			 << endl
			 << endl;
	}
	else
	{
		try
		{
			XALAN_USING_XERCES(XMLPlatformUtils)
            
            XALAN_USING_XERCES(XMLUni)

			XALAN_USING_XALAN(XalanTransformer)

            XalanMemoryManagerImpl memoryManager;

			// Call the static initializer for Xerces.
			XMLPlatformUtils::Initialize( 
                                    XMLUni::fgXercescDefaultLocale,
                                    0,
                                    0,
                                    &memoryManager );

			// Initialize Xalan.
			XalanTransformer::initialize( memoryManager );

			{
				// Create a XalanTransformer.
				XalanTransformer theXalanTransformer( memoryManager );

				// The assumption is that the executable will be run
				// from same directory as the input files.
				theResult = theXalanTransformer.transform("foo.xml", "foo.xsl", "foo.out");

				if(theResult != 0)
				{
					cerr << "SimpleTransform Error: \n" << theXalanTransformer.getLastError()
						 << endl
						 << endl;
				}
			}

			// Terminate Xalan...
			XalanTransformer::terminate();

			// Terminate Xerces...
			XMLPlatformUtils::Terminate();

			// Clean up the ICU, if it's integrated...
			XalanTransformer::ICUCleanUp();
		}
		catch(...)
		{
			cerr << "Initialization failed!" << endl;
		}
	}

	return theResult;
}
