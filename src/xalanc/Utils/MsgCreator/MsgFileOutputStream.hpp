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

// This file is simplified version of XalanFileOutputStream.hpp / .cpp

#if !defined(MSGFILEOUTPUTSTREAM_1357924680)
#define MSGFILEOUTPUTSTREAM_1357924680

#include "xalanc/Include/PlatformDefinitions.hpp"



#include <cstdio>



XERCES_CPP_NAMESPACE_USE




// Class responsible for printing into file with UTF16


class  MsgFileOutputStream
{
public :

#if defined(XALAN_STRICT_ANSI_HEADERS)
    typedef std::FILE*  HandleType;
#else
    typedef FILE*       HandleType;
#endif

    /**
     * Construct an MsgFileOutputStream object.
     * 
     * @param theFileName name of file
     * @param theBufferSize The size of the transcoding buffer
     */
    MsgFileOutputStream(const char*     theFileName);

    virtual
    ~MsgFileOutputStream();


    class OpenException
    {
    public:

        /**
         * Construct an OpenException exception object for an exception
         * that occurred when opening a file.
         * 
         * @param theFileName  The name of file.
         * @param theErrorCode The errno for the error encountered
         */
        OpenException(
            const char*     theFileName,
            int             theErrorCode);

        ~OpenException();

        char    m_message[1200];
    };

    class WriteException
    {
    public:

        /**
         * Construct an WriteException exception object for an exception
         * that occurred while writing to a file.
         * 
         * @param theFileName  The name of file.
         * @param theErrorCode The errno for the error encountered
         */
        WriteException(
                const char*     theFileName,
                int             theErrorCode);

        ~WriteException();

        char    m_message[1200];
    };

    void
    write(
            const XMLCh*    theString,
            unsigned int    theLength);

    void 
    write(
            const char*     theString,
            unsigned int    theLength);

    void 
    writeAsASCII(
            const char*     theString,
            unsigned int    theLength);

    void
    writeAsASCII(
            const XMLCh*    theString,
            unsigned int    theLength);

    void
    writeUTFPrefix();

protected:

    void
    writeData(
            const char*     theBuffer,
            unsigned int    theBufferLength);

    void
    doFlush();

private:

    // These are not implemented...
    MsgFileOutputStream(const MsgFileOutputStream&);

    MsgFileOutputStream&
    operator=(const MsgFileOutputStream&);

    bool
    operator==(const MsgFileOutputStream&) const;


    // Data members...
    const char* const   m_fileName;

    const HandleType    m_handle;
};


#endif //   MSGFILEOUTPUTSTREAM_1357924680
