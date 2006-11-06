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



// Base header file.  Must be first.
#include <xalanc/Include/PlatformDefinitions.hpp>



#include <stdio.h>
#include <sstream>



#if defined(WIN32)
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif



#include <xalanc/Include/XalanMemoryManagement.hpp>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>



#include "Utils.hpp"



XALAN_USING_XALAN(XalanMemMgrs)
XALAN_USING_XALAN(CharVectorType)
XALAN_USING_XALAN(TranscodeToLocalCodePage)
XALAN_USING_XALAN(c_str)

XALAN_USING_STD(ostringstream)
XALAN_USING_STD(fstream)
XALAN_USING_STD(ofstream)



bool checkFileExists(const XalanDOMString& fileName)
{
	CharVectorType     theResult(XalanMemMgrs::getDefaultXercesMemMgr());
    TranscodeToLocalCodePage(fileName, theResult, true);

	FILE* fileHandle  = fopen(c_str(theResult), "r");

	if (fileHandle != 0)
	{
		fclose(fileHandle);
		return true;
	}
	else
	{
		return false;
	}
}



XalanDOMString getWorkingDirectory()
{
	char path[4096];
	getcwd(path, 4096);
	return XalanDOMString(path);
}



const XalanDOMChar* getPathSep()
{
	return XalanFileUtility::s_pathSep;
}



void fileToStream(
        const XalanDOMString&   fileName,
        istringstream&          resultStream)
{
    CharVectorType resultFileName;
    fileName.transcode(resultFileName);
    fstream resultFile(c_str(resultFileName));

    ostringstream fileOutputStream;

    char ch; 

    while(resultFile.get(ch))
    {
        fileOutputStream.put(ch);
    }
    resultStream.str(fileOutputStream.str());
}



void copyFile(
		const XalanDOMString&	destFile,
		const XalanDOMString&	sourceFile)
{
    CharVectorType sourceFileName;
    sourceFile.transcode(sourceFileName);
    fstream sourceFileStream(c_str(sourceFileName));

	CharVectorType destFileName;
    destFile.transcode(destFileName);
    ofstream destFileStream(c_str(destFileName));

	char ch;

	while (sourceFileStream.get(ch))
	{
		destFileStream.put(ch);
	}

	sourceFileStream.close();
	destFileStream.close();
}



