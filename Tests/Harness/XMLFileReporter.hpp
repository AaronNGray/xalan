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
 *
 *
 */
#if !defined(HARNESS_HEADER_GUARD_1357924680)
#define HARNESS_HEADER_GUARD_1357924680



#include <Harness/HarnessDefinitions.hpp>



#include <cstdio>
#include <map>



#include <xalanc/XalanDOM/XalanDOMString.hpp>



XALAN_CPP_NAMESPACE_BEGIN



// This class is exported from the Harness.dll
class HARNESS_API XMLFileReporter 
{
public:

#if defined(XALAN_NO_STD_NAMESPACE)
	typedef map<XalanDOMString, XalanDOMString, less<XalanDOMString> >	Hashtable;
#else
	typedef std::map<XalanDOMString, XalanDOMString>	Hashtable;
#endif

#if defined(XALAN_STRICT_ANSI_HEADERS)
	typedef std::FILE	FileHandleType;
#else
	typedef FILE		FileHandleType;
#endif

public:


	// Construct and initialize this reporter with specified filename, if
	// the filename is not empty.
	XMLFileReporter(const XalanDOMString& fileName = XalanDOMString());

	// Initialize this XMLFileReporter.  Must be called before attempting to log anything.
	bool initialize();

	// Accessor for flushing; is set from properties.
	bool getFlushOnCaseClose();

	// Accessor methods for our properties block.
	const XalanDOMString& getFileName() const;

	// Accessor methods for our properties block.
	void setFileName(const XalanDOMString& fileName);

	// Accessor methods for our properties block.
	void setFileName(const char* fileName)
	{
		setFileName(XalanDOMString(fileName));
	}

	//
	// Is this Reporter still running OK?  
	// @returns status - true if an error has occoured, false if it's still working fine
	// <P>XMLFileReporter should just about never have errors.</P>
	bool checkError();

	  
	//
	// Is this Reporter ready to log results?  
	// @returns status - true if it's ready to report, false otherwise
	bool isReady();

	// Flush this reporter - ensure our File is flushed.
	void flush();


	// Close this reporter - ensure our File, etc. are closed.
	void close();

	//-----------------------------------------------------
	//-------- Testfile / Testcase start and stop routines --------
	//-----------------------------------------------------

	/**
	* Report that a testfile has started.  
	* @param msg message to log out
	*/
	void logTestFileInit(const XalanDOMString& msg);

	void logTestFileInit(const char*	msg)
	{
		logTestFileInit(XalanDOMString(msg));
	}

	/**
	* Report that a testfile has finished, and report it's result.  
	* @param msg message to log out
	* @param result result of testfile
	*/
	void logTestFileClose(const XalanDOMString& msg, const XalanDOMString& result);

	void logTestFileClose(const char* msg, const char* result)
	{
		logTestFileClose(XalanDOMString(msg), XalanDOMString(result));	
	}

	void logTestCaseInit(const XalanDOMString& msg);

	void logTestCaseInit(const char*	msg)
	{
		logTestCaseInit(XalanDOMString(msg));
	}

	/**
	* Report that a testcase has finished, and report it's result.  
	* @param msg message to log out
	* @param result result of testfile
	*/
	void logTestCaseClose(const XalanDOMString& msg, const XalanDOMString& result);

	void logTestCaseClose(const char* msg, const char* result)
	{
		logTestCaseClose(XalanDOMString(msg), XalanDOMString(result));
	}
	//-----------------------------------------------------
	//-------- Test results reporting and logging routines --------
	//-----------------------------------------------------


	/**
	* Report a comment to result file with specified severity.  
	* <P>Record format: &lt;message level="##"&gt;msg&lt;/message&gt;</P>
	* @param level severity or class of message.
	* @param msg comment to log out.
	*/
	void logMessage(int level, const XalanDOMString& msg);

	/**
	* Logs out statistics to result file with specified severity.  
	* <P>Record format: &lt;statistic level="##" desc="msg"&gt;&lt;longval&gt;1234&lt;/longval&gt;&lt;doubleval&gt;1.234&lt;/doubleval&gt;&lt;/statistic&gt;</P>
	* @param level severity of message.
	* @param lVal statistic in long format.
	* @param dVal statistic in double format.
	* @param msg comment to log out.
	*/
	void logStatistic (int level, long lVal, double dVal, const XalanDOMString& msg);

	void logStatistic (int level, long lVal, double dVal, const char*	msg)
	{
		logStatistic(level, lVal, dVal, XalanDOMString(msg));
	}

	// This routine will add an attribute to the attribute list.
	void addMetricToAttrs(char* desc, double theMetric, Hashtable& attrs);

	/**
    * Logs out a element to results with specified severity.
    * Uses user-supplied element name and attribute list.  Currently
    * attribute values and msg are forced .toString().  Also,
    * 'level' is forced to be the first attribute of the element.
    * @param level severity of message.
    * @param element name of enclosing element
    * @param attrs hash of name=value attributes; note that the
    * caller must ensure they're legal XML
	* @param msg comment to log out.
	*/
	void logElementWAttrs(int level, const XalanDOMString& element, Hashtable attrs, const XalanDOMString& msg);

	void logElementWAttrs(int level,  const char* element, Hashtable attrs, const char* msg)
	{
		logElementWAttrs(level, XalanDOMString(element), attrs, XalanDOMString(msg));
	}

	void logElement(int level, const XalanDOMString& element, const XalanDOMString& msg);

	void logElement(const XalanDOMString& element, const XalanDOMString& msg);
	/**
	* Report an arbitrary XalanDOMString to result file with specified severity.  
	* <P>Appends and prepends \\n newline characters at the start and 
	* end of the message to separate it from the tags.</P>
	* <P>Record format: &lt;arbitrary level="##"&gt;<BR/>
	* msg<BR/>
	* &lt;/arbitrary&gt;
	* </P>
	* @param level severity or class of message.
	* @param msg arbitrary XalanDOMString to log out.
	*/
	void logArbitraryMessage (int level, const XalanDOMString& msg);

	/**
	* Report a complete Hashtable to result file with specified severity.  
	* <P>Indents each hashitem within the table.</P>
	* <P>Record format: &lt;hashtable level="##" desc="msg"/&gt;<BR/>
	* &nbsp;&nbsp;&lt;hashitem key="key1"&gt;value1&lt;/hashitem&gt;<BR/>
	* &nbsp;&nbsp;&lt;hashitem key="key2"&gt;value2&lt;/hashitem&gt;<BR/>
	* &lt;/hashtable&gt;
	* </P>
	* @param level severity or class of message.
	* @param hash Hashtable to log the contents of. 
	* @param msg decription of the Hashtable.
	*/
	/*
	void logHashtable (int level, Hashtable hash, const XalanDOMString& msg);
	*/

	/**
	* Writes out a Pass record with comment.  
	* <P>Record format: &lt;checkresult result="PASS" desc="comment"/&gt;</P>
	* @param comment comment to log with the pass record.
	*/
	void logCheckPass(const XalanDOMString& comment);

	/**
	* Writes out an ambiguous record with comment.  
	* <P>Record format: &lt;checkresult result="AMBG" desc="comment"/&gt;</P>
	* @param comment comment to log with the ambg record.
	*/
	void logCheckAmbiguous(const XalanDOMString& comment);

	/**
	* Writes out a Fail record with comment.  
	* <P>Record format: &lt;checkresult result="FAIL" desc="comment"/&gt;</P>
	* @param comment comment to log with the fail record.
	*/
	void logCheckFail(const XalanDOMString& comment);

	void logCheckFail(const XalanDOMString& test, Hashtable faildata, Hashtable actexp);

	void logCheckFail(const XalanDOMString& test, Hashtable actexp);

	void logErrorResult(const XalanDOMString& test, const XalanDOMString& reason);

	/**
	* Writes out a Error record with comment.  
	* <P>Record format: &lt;checkresult result="ERRR" desc="comment"/&gt;</P>
	* @param comment comment to log with the error record.
	*/
	void logCheckErr(const XalanDOMString& comment);

	/**
	* Escapes a XalanDOMString to remove <, >, ', &, and " so it's valid XML.  
	* <P>Stolen mostly from Xalan applet sample.</P>
	* @param s XalanDOMString to escape.
	* @return XalanDOMString that has been escaped.
	*/
	XalanDOMString escapestring(const XalanDOMString& s);


private:

	/**
	* worker method to dump the xml header and open the resultsfile element.  
	*/
	bool startResultsFile();

	/**
	* worker method to close the resultsfile element.  
	*/
	bool closeResultsFile();

	/**
	* worker method to prints to the resultsfile.  
	*/
	bool printToFile(const XalanDOMString& output);

	void
	initStrings();

	/**
	* worker method to prints to the resultsfile.  
	*/
	XalanDOMString getDateTimeString();
	
	/** Key for Properties block that denotes our output filename.  */
	XalanDOMString	OPT_FILENAME;

	/** XML tagnames for results file structure.  */
	XalanDOMString	ELEM_RESULTSFILE;
	XalanDOMString	ELEM_TESTFILE;
	XalanDOMString	ELEM_FILERESULT;
	XalanDOMString	ELEM_TESTCASE;
	XalanDOMString	ELEM_CASERESULT;
	XalanDOMString	ELEM_CHECKRESULT;
	XalanDOMString	ELEM_STATISTIC;
	XalanDOMString	ELEM_LONGVAL;
	XalanDOMString	ELEM_DOUBLEVAL;
	XalanDOMString	ELEM_MESSAGE;
	XalanDOMString	ELEM_ARBITRARY;
	XalanDOMString	ELEM_HASHTABLE;
	XalanDOMString	ELEM_HASHITEM;

	/** XML attribute names for results file structure.  */
	XalanDOMString	ATTR_LEVEL;
	XalanDOMString	ATTR_DESC;
	XalanDOMString	ATTR_TIME;
	XalanDOMString	ATTR_RESULT;
	XalanDOMString	ATTR_KEY;
	XalanDOMString	ATTR_FILENAME;
	XalanDOMString	LESS_THAN;
	XalanDOMString	GREATER_THAN;
	XalanDOMString	EQUALS_QUOTE;
	XalanDOMString	SPACE;
	XalanDOMString	QUOTE;
	XalanDOMString	QUOTE_SPACE;
	XalanDOMString	QUOTE_GREATER_THAN;
	XalanDOMString	QUOTE_SOLIDUS_GREATER_THAN;
	XalanDOMString	PASS;
	XalanDOMString	AMBG;
	XalanDOMString	ERRR;
	XalanDOMString	FAIL;
	XalanDOMString	LESS_THAN_SOLIDUS;
	XalanDOMString	XML_HEADER;
	XalanDOMString	REASON_EQUALS_QUOTE;

	/** 
	* Optimization: for heavy use methods, form pre-defined constants to save on XalanDOMString concatenation.  
	* <P>Note the indent; must be updated if we ever switch to another indenting method.</P>
	*/
	XalanDOMString	TESTCASEINIT_HDR;
	XalanDOMString	TESTCASECLOSE_HDR;
	XalanDOMString	MESSAGE_HDR;
	XalanDOMString	STATISTIC_HDR;
	XalanDOMString	ARBITRARY_HDR;
	XalanDOMString	HASHTABLE_HDR;
	XalanDOMString	HASHITEM_HDR;
	XalanDOMString	CHECKPASS_HDR;
	XalanDOMString	CHECKAMBG_HDR;
	XalanDOMString	CHECKERRR_HDR;
	XalanDOMString	CHECKFAIL_HDR;
	XalanDOMString	CHECKFAIL_FTR;

	/** If we have output anything yet.  */
	bool m_anyOutput;

	/** Name of the file we're outputing to.  */
	XalanDOMString m_fileName;

	/** File reference and other internal convenience variables.  */
	FileHandleType* m_fileHandle;

	/** If we're ready to start outputting yet.  */
	bool m_ready;

	/** If an error has occoured in this Reporter.  */
	bool m_error;

	/** If we should flush after every logTestCaseClose.  */
	bool m_flushOnCaseClose;

};        // end of class XMLFileReporter



XALAN_CPP_NAMESPACE_END



#endif
