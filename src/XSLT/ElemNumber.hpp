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
  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
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
#if !defined(XALAN_ELEMNUMBER_HEADER_GUARD)
#define XALAN_ELEMNUMBER_HEADER_GUARD 



// Base include file.  Must be first.
#include <XSLT/XSLTDefinitions.hpp>



#include <vector>



// Base class header file.
#include <XSLT/ElemTemplateElement.hpp>



#include <XPath/NodeRefListBase.hpp>



#include <XSLT/CountersTable.hpp>
#include <XSLT/DecimalToRoman.hpp>
#include <XSLT/XalanNumberingResourceBundle.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class AVT;
class MutableNodeRefList;
class XalanNumberFormat;
class XPath;
class XPathExecutionContext;



class ElemNumber: public ElemTemplateElement
{
public:

	typedef CountersTable::CountType	CountType;

	enum eLevel
	{
		eSingle,
		eMultiple,
		eAny
	};

#if defined(XALAN_NO_STD_NAMESPACE)
	typedef vector<CountType>		CountTypeArrayType;
#else
	typedef std::vector<CountType>	CountTypeArrayType;
#endif

	/**
	 * Perform static initialization.  See class XSLTInit.
	 */
	static void
	initialize();

	/**
	 * Perform static shut down.  See class XSLTInit.
	 */
	static void
	terminate();

	/**
	 * Construct an object corresponding to an "xsl:number" element
	 * 
	 * @param constructionContext context for construction of object
	 * @param stylesheetTree      stylesheet containing element
	 * @param atts                list of attributes for element
	 * @param lineNumber				line number in document
	 * @param columnNumber			column number in document
	 * @param id				  The unique ID within the stylesheet for this xsl:number element
	 */
	ElemNumber(
			StylesheetConstructionContext&	constructionContext,
			Stylesheet&						stylesheetTree,
			const AttributeListType&		atts,
			int								lineNumber,
			int								columnNumber,
			unsigned long					id);

	virtual
	~ElemNumber();

	// These methods are inherited from ElemTemplateElement ...

	virtual const XalanDOMString&
	getElementName() const;

	virtual void
	execute(StylesheetExecutionContext&		executionContext) const;

	unsigned long
	getID() const
	{
		return m_id;
	}

	/**
	 * Get the previous node to be counted.
	 */
	XalanNode* getPreviousNode(
			StylesheetExecutionContext&		executionContext,
			XalanNode*						pos) const;

	/**
	 * Get the target node that will be counted..
	 */
	XalanNode* getTargetNode(
			StylesheetExecutionContext&		executionContext,
			XalanNode*						sourceNode) const;

protected:

	/**
	 * Given a 'from' pattern (ala xsl:number), a match pattern 
	 * and a context, find the first ancestor that matches the 
	 * pattern (including the context handed in).
	 *
	 * @param executionContext The current execution context
	 * @param matchPatternString The match pattern.
	 * @param matchPatternString The count match pattern.
	 * @param node The context node
	 * @return A pointer to the matched node.
	 */
	XalanNode*
	findAncestor(
			StylesheetExecutionContext&		executionContext,
			const XPath*					fromMatchPattern,
			const XPath*					countMatchPattern,
			XalanNode*						context) const;

	/**
	 * Given a 'from' pattern (ala xsl:number), a match pattern 
	 * and a context, find the first ancestor that matches the 
	 * pattern (including the context handed in).
	 *
	 * @param executionContext The current execution context
	 * @param matchPatternString The match pattern.
	 * @param matchPatternString The count match pattern.
	 * @param node The context node
	 * @return A pointer to the matched node.
	 */
	XalanNode*
	findPrecedingOrAncestorOrSelf(
			StylesheetExecutionContext&		executionContext,
			const XPath*					fromMatchPattern,
			const XPath*					countMatchPattern,
			XalanNode*						context) const;

	/**
	 * Get the count match pattern, or a default value.
	 */
	const XPath*
	getCountMatchPattern(
			StylesheetExecutionContext&		executionContext,
			XalanNode*						contextNode) const;

	/**
	 * Given an XML source node, get the count according to the 
	 * parameters set up by the xsl:number attributes.
	 */
	void
	getCountString(
			StylesheetExecutionContext&		executionContext,
			XalanDOMString&					theResult) const;

	void
	getCountString(
			StylesheetExecutionContext&		executionContext,
			const MutableNodeRefList&		ancestors,
			CountersTable&					ctable,
			CountType						numberList[],
			NodeRefListBase::size_type		numberListLength,
			XalanDOMString&					theResult) const;

	/**
	 * Get the ancestors, up to the root, that match the
	 * pattern.
	 * @param patterns if non-0, count only nodes
	 * that match this pattern, if 0 count all ancestors.
	 * @param executionContext The current execution context.
	 * @param node Count this node and it's ancestors.
	 * @param stopAtFirstFound If true, only get the first matching ancestor
	 * @param ancestors The ancestors that match the pattern.
	 */
	void
	getMatchingAncestors(
			StylesheetExecutionContext&		executionContext,
			XalanNode*						node, 
			bool							stopAtFirstFound,
			MutableNodeRefList&				ancestors) const;

	/**
	 * Get a formatter.
	 * @param executionContext The current execution context.
	 * @return A new XalanNumberFormat instance.  The caller owns the memory.
	 */
	XalanNumberFormat*
	getNumberFormatter(StylesheetExecutionContext&		executionContext) const;

	/**
	 * Format an array of integrals into a formatted string.
	 *
	 * @param executionContext The current execution context.
	 * @param theList Array of one or more integer numbers.
	 * @param theListLength The length of the array.
	 * @param formattedNumber The formatted number result.
	 */
	void
	formatNumberList(	
			StylesheetExecutionContext&		executionContext,
			const CountType					theList[],
			NodeRefListBase::size_type		theListLength,
			XalanDOMString&					formattedNumber) const;

	/**
	 * Convert an intergral into alphabetic counting, in other words
	 * count using the sequence A B C ... Z.
	 * @param val Value to convert -- must be greater than zero.
	 * @param table a table containing one character for each digit in the radix
	 * @param theResult A string representing alpha count of number.
	 * @see XSLTEngineImpl#DecimalToRoman
	 *
	 * Note that the radix of the conversion is inferred from the size
	 * of the table.
	 */
	static void
	int2singlealphaCount(
			CountType				val,
			const XalanDOMString&	table,
			XalanDOMString&			theResult);
		
	/**
	 * Convert an integral into alphabetic counting, in other words 
	 * count using the sequence A B C ... Z AA AB AC.... etc.
	 * @param val Value to convert -- must be greater than zero.
	 * @param table a table containing one character for each digit in the radix
	 * @param length the table length
	 * @param result returns the stringrepresenting alpha count of number.
	 * @see XSLTEngineImpl#DecimalToRoman
	 * 
	 * Note that the radix of the conversion is inferred from the size
	 * of the table.
	 */
	static void
	int2alphaCount(
			CountType					val,
			const XalanDOMChar			table[],
			XalanDOMString::size_type	length,
			XalanDOMString&				theResult);

	/**
	 * Convert a long integer into traditional alphabetic counting, in other words
	 * count using the traditional numbering.
	 * @param val Value to convert -- must be greater than zero.
	 * @param table a table containing one character for each digit in the radix
	 * @return String representing alpha count of number.
	 * @see XSLProcessor#DecimalToRoman
	 *
	 * Note that the radix of the conversion is inferred from the size
	 * of the table.
	 */
	static void
	tradAlphaCount(
			CountType			val,
			XalanDOMString&		theResult);

	/**
	 * Convert an integral into roman numerals.
	 * @param val Value to convert.
	 * @param prefixesAreOK true to enable prefix notation (e.g. 4 = "IV"), false to disable prefix notation (e.g. 4 = "IIII").
	 * @param theResult The formatted Roman numeral string.
	 * @see DecimalToRoman
	 * @see m_romanConvertTable
	 */
	static void
	long2roman(
			CountType			val,
			bool				prefixesAreOK,
			XalanDOMString&		theResult);

private:

	void
	evaluateLetterValueAVT(
			StylesheetExecutionContext&		executionContext,
			XalanDOMString&					value) const;

	void
	traditionalAlphaCount(
			CountType								theValue,
			const XalanNumberingResourceBundle&		theResourceBundle,
			XalanDOMString&							theResult) const;

	/*
	 * Get Formatted number
	 */
	void
	getFormattedNumber(
			StylesheetExecutionContext&		executionContext,
			XalanDOMChar					numberType,
			XalanDOMString::size_type		numberWidth,
			CountType						listElement,
			XalanDOMString&					theResult) const;

	const XPath*	m_countMatchPattern;
	const XPath*	m_fromMatchPattern;
	const XPath*	m_valueExpr;

	CountType		m_level; // = Constants.NUMBERLEVEL_SINGLE;

	const AVT*		m_format_avt;
	const AVT*		m_lang_avt;
	const AVT*		m_lettervalue_avt;
	const AVT*		m_groupingSeparator_avt;
	const AVT*		m_groupingSize_avt;

	const unsigned long		m_id;

	/**
 	 * The string "@".
 	 */
 	static const XalanDOMChar				s_atString[];

		/**
 	 * The string "text()".
 	 */
 	static const XalanDOMString&			s_textString;

	/**
 	 * The string "comment()".
 	 */
 	static const XalanDOMString&			s_commentString;

	/**
 	 * The string "/".
 	 */
 	static const XalanDOMString&			s_slashString;

	/**
 	 * The string "processing-instruction(".
 	 */
 	static const XalanDOMChar				s_piString[];

	/**
 	 * The string "level".
 	 */
 	static const XalanDOMChar				s_levelString[];

	/**
 	 * The string "multiple".
 	 */
 	static const XalanDOMChar				s_multipleString[];

	/**
 	 * The string "any".
 	 */
 	static const XalanDOMChar				s_anyString[];

	/**
 	 * The string "single".
 	 */
 	static const XalanDOMChar				s_singleString[];

	/**
 	 * The string "alphabetic".
 	 */
 	static const XalanDOMChar				s_alphabeticString[];

	/**
 	 * The string "traditional".
 	 */
 	static const XalanDOMChar				s_traditionalString[];

	/**
 	 * The string "#error".
 	 */
 	static const XalanDOMChar				s_errorString[];

	/**
	* Chars for converting integers into alpha counts.
	*/
	static const XalanDOMChar				s_alphaCountTable[];

	static const XalanDOMString::size_type	s_alphaCountTableSize;

	static const XalanDOMChar				s_elalphaCountTable[];

	static const XalanDOMString::size_type	s_elalphaCountTableSize;

	/**
	 * Table to help in converting decimals to roman numerals.
	 * @see XSLTEngineImpl#DecimalToRoman
	 * @see XSLTEngineImpl#long2roman
	 */
	static const DecimalToRoman				s_romanConvertTable[];

	/**
	 * numbering resource bundle for Greek numbering.
	 */
	static const XalanNumberingResourceBundle&	s_elalphaResourceBundle;


public:

	/**
	 * This class returns tokens using non-alphanumberic characters as
	 * delimiters. 
	 */
	class NumberFormatStringTokenizer
	{
	public:

		typedef XalanDOMString::size_type	size_type;

		/**
		 * Construct a NumberFormatStringTokenizer.
		 *
		 * @param theString string to tokenize
		 */
		NumberFormatStringTokenizer(const XalanDOMString&	theString);

		/**
		 * Sets the string to tokenize.
		 *
		 * @param theString  new string to tokenize
		 */
		void
		setString(const XalanDOMString&	theString);

		/**
		 * Reset tokenizer so that nextToken() starts from the beginning.
		 */
		void
		reset()
		{
			m_currentPosition = 0;
		}

		/**
		 * Retrieve the next token to be parsed; behavior is undefined if there
		 * are no more tokens
		 * 
		 * @return next token string
		 */
		XalanDOMString
		nextToken();

		/**
		 * Retrieve the next token to be parsed.
		 * 
		 * @param theToken The next token string
		 */
		void
		nextToken(XalanDOMString&	theToken);

		/**
		 * Determine if there are tokens remaining
		 * 
		 * @return true if there are more tokens
		 */
		bool
		hasMoreTokens() const
		{
			return m_currentPosition >= m_maxPosition ? false : true;
		}

		/**
		 * Count the number of tokens yet to be parsed
		 * 
		 * @return number of remaining tokens
		 */
		size_type
		countTokens() const;

	private:

		size_type				m_currentPosition;

		size_type				m_maxPosition;

		const XalanDOMString*	m_string;
	};
	
private:
};



XALAN_CPP_NAMESPACE_END



#endif	// XALAN_ELEMNUMBER_HEADER_GUARD
