/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
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
#if !defined(XPATHEXPRESSION_HEADER_GUARD_1357924680)
#define XPATHEXPRESSION_HEADER_GUARD_1357924680



// Base header file.  Must be first.
#include <XPath/XPathDefinitions.hpp>



#include <deque>
#include <map>
#include <set>
#include <vector>

#if defined(XALAN_NO_IOSFWD)
#if defined(XALAN_OLD_STREAM_HEADERS)
#include <iostream.h>
#else
#include <ostream>
#endif
#else
#include <iosfwd>
#endif



#include <XalanDOM/XalanDOMString.hpp>



#include <PlatformSupport/DOMStringHelper.hpp>
#include <PlatformSupport/PrintWriter.hpp>



#include <XPath/XToken.hpp>
#include <XPath/XPathException.hpp>



class XALAN_XPATH_EXPORT XPathExpression
{
public:

	/**
	 * List of operations codes.
	 *
	 * Code for the descriptions of the operations codes:
	 * [UPPER CASE] indicates a literal value,
	 * [lower case] is a description of a value,
	 *		([length] always indicates the length of the operation,
	 *		 including the operations code and the length integer.)
	 * {UPPER CASE} indicates the given production,
	 * {description} is the description of a new production,
	 *		(For instance, {boolean expression} means some expression 
	 *		 that should be resolved to a boolean.)
	 *	* means that it occurs zero or more times,
	 *	+ means that it occurs one or more times,
	 *	? means that it is optional.
	 *
	 * returns: indicates what the production should return.
	 */
	enum eOpCodes
	{
		/**
		 * [ENDOP]
		 * Some operators may like to have a terminator.
		 */
		eENDOP = -1,

		/**
		 * [EMPTY]
		 * Empty slot to indicate NULL.
		 */
		eEMPTY = -2,

		/**
		 * [ELEMWILDCARD]
		 * Means ELEMWILDCARD ("*"), used instead 
		 * of string index in some places.
		 */
		eELEMWILDCARD = -3,

		/**
		 * [OP_XPATH]
		 * [length]
		 *	{expression}
		 * 
		 * returns: 
		 *	XNodeSet
		 *	XNumber
		 *	XString
		 *	XBoolean
		 *	XRTree
		 *	XObject
		 */
		eOP_XPATH = 1,

		/**
		 * [OP_OR]
		 * [length]
		 *	{boolean expression}
		 *	{boolean expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_OR = 2,

		/**
		 * [OP_AND]
		 * [length]
		 *	{boolean expression}
		 *	{boolean expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_AND = 3,

		/**
		 * [OP_NOTEQUALS]
		 * [length]
		 *	{expression}
		 *	{expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_NOTEQUALS = 4,

		/**
		 * [OP_EQUALS]
		 * [length]
		 *	{expression}
		 *	{expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_EQUALS = 5,

		/**
		 * [OP_LTE] (less-than-or-equals)
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_LTE = 6,

		/**
		 * [OP_LT] (less-than)
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_LT = 7,

		/**
		 * [OP_GTE] (greater-than-or-equals)
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_GTE = 8,

		/**
		 * [OP_GT] (greater-than)
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_GT = 9,

		/**
		 * [OP_PLUS]
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_PLUS = 10,

		/**
		 * [OP_MINUS]
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_MINUS = 11,

		/**
		 * [OP_MULT]
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_MULT = 12,

		/**
		 * [OP_DIV]
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_DIV = 13,

		/**
		 * [OP_MOD]
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_MOD = 14,

		/**
		 * [OP_QUO]
		 * [length]
		 *	{number expression}
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_QUO = 15,

		/**
		 * [OP_NEG]
		 * [length]
		 *	{number expression}
		 * 
		 * returns: 
		 *	XNumber
		 */
		eOP_NEG = 16,

		/**
		 * [OP_STRING] (cast operation)
		 * [length]
		 *	{expression}
		 * 
		 * returns: 
		 *	XString
		 */
		eOP_STRING = 17,

		/**
		 * [OP_BOOL] (cast operation)
		 * [length]
		 *	{expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_BOOL = 18,

		/**
		 * [OP_NUMBER] (cast operation)
		 * [length]
		 *	{expression}
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eOP_NUMBER = 19,

		/**
		 * [OP_UNION]
		 * [length]
		 *	{PathExpr}+
		 * 
		 * returns: 
		 *	XNodeSet
		 */
		eOP_UNION = 20,

		/**
		 * [OP_LITERAL]
		 * [3]
		 * [index to token]
		 * 
		 * returns: 
		 *	XString
		 */
		eOP_LITERAL = 21,

		/**
		 * [OP_VARIABLE]
		 * [3]
		 * [index to token]
		 * 
		 * returns: 
		 *	XString
		 */
		eOP_VARIABLE = 22,

		/**
		 * [OP_GROUP]
		 * [length]
		 *	{expression}
		 * 
		 * returns: 
		 *	XNodeSet
		 *	XNumber
		 *	XString
		 *	XBoolean
		 *	XRTree
		 *	XObject
		 */
		eOP_GROUP = 23,

		/**
		 * [OP_NUMBERLIT] (Number literal.)
		 * [3]
		 * [index to token]
		 * 
		 * returns: 
		 *	XString
		 */
		eOP_NUMBERLIT = 24,

		/**
		 * [OP_ARGUMENT] (Function argument.)
		 * [length]
		 *	{expression}
		 * 
		 * returns: 
		 *	XNodeSet
		 *	XNumber
		 *	XString
		 *	XBoolean
		 *	XRTree
		 *	XObject
		 */
		eOP_ARGUMENT = 25,

		/**
		 * [OP_EXTFUNCTION] (Extension function.)
		 * [length]
		 * [index to namespace token]
		 * [index to function name token]
		 *  {OP_ARGUMENT}*
		 * 
		 * returns: 
		 *  XNodeSet
		 *  XNumber
		 *  XString
		 *  XBoolean
		 *  XRTree
		 *  XObject
		 */
		eOP_EXTFUNCTION = 26,

		/**
		 * [OP_FUNCTION]
		 * [length]
		 * [FUNC_name]
		 *  {OP_ARGUMENT}*
		 * [ENDOP]
		 * 
		 * returns: 
		 *  XNodeSet
		 *  XNumber
		 *  XString
		 *  XBoolean
		 *  XRTree
		 *  XObject
		 */
		eOP_FUNCTION = 27,

		/**
		 * [OP_LOCATIONPATH]
		 * [length]
		 *	 {FROM_stepType}
		 * | {function}{predicate}*
		 * [ENDOP]
		 * 
		 * (Note that element and attribute namespaces and 
		 * names can be wildcarded '*'.)
		 * 
		 * returns: 
		 *	XNodeSet
		 */
		eOP_LOCATIONPATH = 28,

		/**
		 * [OP_PREDICATE]
		 * [length]
		 *	{expression}
		 * [ENDOP] (For safety)
		 * 
		 * returns: 
		 *	XBoolean or XNumber
		 */
		eOP_PREDICATE = 29,
  
		/**
		 * [NODETYPE_COMMENT]
		 * No size or arguments.
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODETYPE_COMMENT = 1030,
		
		/**
		 * [NODETYPE_TEXT]
		 * No size or arguments.
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODETYPE_TEXT = 1031,
		
		/**
		 * [NODETYPE_PI]
		 * [index to token]
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODETYPE_PI = 1032,
		
		/**
		 * [NODETYPE_NODE]
		 * No size or arguments.
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODETYPE_NODE = 1033,
		
		/**
		 * [NODENAME]
		 * [index to ns token or EMPTY]
		 * [index to name token]
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODENAME = 34,
		
		/**
		 * [NODETYPE_ROOT]
		 * No size or arguments.
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODETYPE_ROOT = 35,
		
		/**
		 * [NODETYPE_ANY]
		 * No size or arguments.
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eNODETYPE_ANYELEMENT = 36,

		/**
		 * [FROM_stepType]
		 * [length, including predicates]
		 * [length of just the step, without the predicates]
		 * {node test}
		 * {predicates}?
		 * 
		 * returns: 
		 *	XBoolean
		 */
		eFROM_ANCESTORS = 37,
		eFROM_ANCESTORS_OR_SELF = 38,
		eFROM_ATTRIBUTES = 39,
		eFROM_CHILDREN = 40,
		eFROM_DESCENDANTS = 41,
		eFROM_DESCENDANTS_OR_SELF = 42,
		eFROM_FOLLOWING = 43,
		eFROM_FOLLOWING_SIBLINGS = 44,
		eFROM_PARENT = 45,
		eFROM_PRECEDING = 46,
		eFROM_PRECEDING_SIBLINGS = 47,
		eFROM_SELF = 48,
		eFROM_NAMESPACE = 49,
		// eFROM_ATTRIBUTE = 50,
		// eFROM_DOC = 51,
		// eFROM_DOCREF = 52,
		// eFROM_ID = 53,
		// eFROM_IDREF = 54,
		eFROM_ROOT = 55,

		/**
		 * [OP_UNION]
		 * [length]
		 *  {PathExpr}+
		 * 
		 * returns: 
		 *  XNodeSet
		 */
		eOP_MATCHPATTERN = 92,

		/**
		 * [OP_UNION]
		 * [length]
		 *  {PathExpr}+
		 * 
		 * returns: 
		 *  XNodeSet
		 */
		eOP_LOCATIONPATHPATTERN = 93,

		// For match patterns
		eMATCH_ATTRIBUTE = 94,
		eMATCH_ANY_ANCESTOR = 95,
		eMATCH_IMMEDIATE_ANCESTOR = 96,
		eMATCH_ANY_ANCESTOR_WITH_PREDICATE = 97,

		// Always add _before_ this one.
		eOpCodeNextAvailable
	};	// enum eOpCodes

	/**
	 * The length is always the opcode position + 1. Length is always expressed
	 * as the opcode+length bytes, so it is always 2 or greater.  This is the
	 * offset from the op code where the length is stored.  It will always
	 * remain one.
	 */
#if defined(XALAN_INLINE_INITIALIZATION)
	const int	s__opCodeMapLengthIndex = 1;
#else
	enum eDummy
	{
		s__opCodeMapLengthIndex = 1
	};
#endif

	/**
	 * Exception class thrown when an invalid XPath expression is encountered
	 */
	class XALAN_XPATH_EXPORT XPathExpressionException : public XPathException
	{
	public:

		/**
		 * Construct an XPathExpressionException object.
		 * 
		 * @param theMessage string error message
		 */
		XPathExpressionException(const XalanDOMString&	theMessage);

		virtual~
		XPathExpressionException();
	};

	/**
	 * Exception class thrown when an invalid XPath operation code is encountered
	 */
	class XALAN_XPATH_EXPORT InvalidOpCodeException : public XPathExpressionException
	{
	public:

		/**
		 * Construct an InvalidOpCodeException object.
		 * 
		 * @param theOpCode operation code that caused the exception
		 */
		InvalidOpCodeException(int	theOpCode);

		virtual~
		InvalidOpCodeException();

	private:

		static XalanDOMString
		FormatErrorMessage(int	theOpCode);
	};

	/**
	 * Exception class thrown when an invalid number of XPath arguments is
	 * encountered
	 */
	class XALAN_XPATH_EXPORT InvalidArgumentCountException : public XPathExpressionException
	{
	public:

		/**
		 * Construct an InvalidArgumentCountException object.
		 * 
		 * @param theOpCode operation code that caused the exception
		 * @param theExpectedCount the correct number of arguments for "opcode"
		 * @param theSuppliedCount the number of arguments supplied
		 */
		InvalidArgumentCountException(
			int		theOpCode,
			int		theExpectedCount,
			int		theSuppliedCount);

		virtual~
		InvalidArgumentCountException();

	private:

		static XalanDOMString
		FormatErrorMessage(
			int		theOpCode,
			int		theExpectedCount,
			int		theSuppliedCount);
	};

	/**
	 * Exception class thrown when an invalid XPath argument is encountered
	 */
	class XALAN_XPATH_EXPORT InvalidArgumentException : public XPathExpressionException
	{
	public:

		/**
		 * Construct an InvalidArgumentException object.
		 * 
		 * @param theOpCode operation code that caused the exception
		 * @param theValue invalid argument value
		 */
		InvalidArgumentException(
			int	theOpCode,
			int	theValue);

		virtual~
		InvalidArgumentException();

	private:

		static XalanDOMString
		FormatErrorMessage(
				int		theOpCode,
				int		theValue);
	};

	/**
	 * Exception class thrown when an invalid token position is encountered
	 */
	class XALAN_XPATH_EXPORT InvalidRelativeTokenPosition : public XPathExpressionException
	{
	public:

		/**
		 * Construct an InvalidRelativeTokenPosition object.
		 * 
		 * @param theOffset the offset that caused the problem.
		 */
		InvalidRelativeTokenPosition(int	theOffset);

		virtual~
		InvalidRelativeTokenPosition();

	private:

		static XalanDOMString
		FormatErrorMessage(int	theOffset);
	};


#if defined(XALAN_NO_NAMESPACES)

	typedef vector<int>						OpCodeMapType;
	typedef deque<XToken>					TokenQueueType;
	typedef vector<int>						PatternMapType;

	typedef map<int, int, less<int> >		OpCodeLengthMapType;

	typedef OpCodeMapType::value_type		OpCodeMapValueType;
	typedef OpCodeMapType::size_type		OpCodeMapSizeType;

	typedef set<OpCodeMapValueType, less<OpCodeMapValueType> >	NodeTestSetType;

	typedef vector<OpCodeMapValueType>		OpCodeMapValueVectorType;

#else

	typedef std::vector<int>				OpCodeMapType;
	typedef std::deque<XToken>				TokenQueueType;
	typedef std::vector<int>				PatternMapType;
	typedef std::map<int, int>				OpCodeLengthMapType;

	typedef OpCodeMapType::value_type		OpCodeMapValueType;
	typedef OpCodeMapType::size_type		OpCodeMapSizeType;

	typedef std::set<OpCodeMapValueType>	NodeTestSetType;
	typedef std::vector<OpCodeMapValueType> OpCodeMapValueVectorType;

#endif

	typedef TokenQueueType::value_type		TokenQueueValueType;
	typedef TokenQueueType::size_type		TokenQueueSizeType;
	typedef PatternMapType::value_type		PatternMapValueType;
	typedef PatternMapType::size_type		PatternMapSizeType;

	explicit
	XPathExpression();

	~XPathExpression();

	/**
	 * Reset the expression.
	 */
	void
	reset();

	/**
	 * Shrink internal tables.
	 */
	void
	shrink();

	/**
	 * Retrieve number of elements in the operations code map.
	 * 
	 * @return size of operations code map
	 */
	OpCodeMapSizeType
	opCodeMapSize() const
	{
		return m_opMap.size();
	}

	/**
	 * Retrieve length of the operations code map stored in the map. The length
	 * of the entire map is stored after the first op code.  That offset is
	 * determined by this const static member.  Note that as expressions are
	 * defined recursively, this is really just the length of the first
	 * expression in the map, which is the top of the parse tree. Any
	 * subexpression will also have a length entry at the same offset from the
	 * beginning of the subexpression.
	 * 
	 * @return length of operations code map
	 */
	OpCodeMapValueType
	opCodeMapLength() const
	{
		const OpCodeMapSizeType		theSize = opCodeMapSize();

		if (theSize > s__opCodeMapLengthIndex)
		{
			assert(theSize ==
				OpCodeMapSizeType(m_opMap[s__opCodeMapLengthIndex]));

			return m_opMap[s__opCodeMapLengthIndex];
		}
		else
		{
			return theSize;
		}
	}

	/**
	 * Retrieve number of elements in the token queue.
	 * 
	 * @return size of token queue
	 */
	TokenQueueSizeType
	tokenQueueSize() const
	{
		return m_tokenQueue.size();
	}

	/**
	 * Retrieve number of elements in the pattern map.
	 * 
	 * @return size of pattern map
	 */
	PatternMapSizeType
	patternMapSize() const
	{
		return m_patternMap.size();
	}

	/**
	 * Retrieve the value of an operation code at a specified position in the
	 * list.
	 * 
	 * @param opPos position in list
	 * @return value of operation code
	 */
	OpCodeMapValueType
	getOpCodeMapValue(OpCodeMapSizeType		opPos) const
	{
		return m_opMap[opPos];
	}

	/**
	 * Retrieve the length of an operation code at a specified position in the
	 * list.
	 * 
	 * @param opPos position in list
	 * @return length of operation code
	 */
	OpCodeMapValueType
	getOpCodeLength(OpCodeMapSizeType	opPos) const;

	/**
	 * Retrieve the position of the next operation code at a specified position
	 * in the list.
	 * 
	 * @param opPos position in list
	 * @return position of next operation code
	 */
	OpCodeMapValueType
	getNextOpCodePosition(OpCodeMapSizeType		opPos) const
	{
		assert(opPos < opCodeMapSize());

		return opPos + m_opMap[opPos + s__opCodeMapLengthIndex];
	}

	/**
	 * Set the arguments for an operation code at a specified index in the
	 * list.
	 * 
	 * @param opPos position in list
	 * @param theOpCode operation code
	 * @param theIndex  index in list
	 * @param theArgs   vector or arguments to supply
	 */
	void
	setOpCodeArgs(
			eOpCodes							theOpCode,
			OpCodeMapSizeType					theIndex,
			const OpCodeMapValueVectorType&		theArgs);

	/**
	 * Add an operation code to the list.
	 * 
	 * @param theOpCode operation code
	 */
	void
	appendOpCode(eOpCodes	theOpCode);

	/**
	 * Add an operation code with supplied arguments to the list.
	 * 
	 * @param theOpCode operation code
	 * @param theArgs   vector or arguments to supply
	 */
	void
	appendOpCode(eOpCodes							theOpCode,
				 const OpCodeMapValueVectorType&	theArgs)
	{
		appendOpCode(theOpCode);

		setOpCodeArgs(theOpCode,
					  m_lastOpCodeIndex,
					  theArgs);
	}

	/**
	 * Insert an operation code at a specified index in the list.
	 * 
	 * @param theOpCode operation code
	 * @param theIndex  index in list
	 */
	OpCodeMapValueType
	insertOpCode(
			eOpCodes			theOpCode,
			OpCodeMapSizeType	theIndex);

	/**
	 * Update the length of an operation code at a specified index in the list.
	 * This presumes that the other opcodes have been appended to the
	 * expression, and that the specified op code's length needs to be set.
	 * The size includes the normal length of the opcode, plus the length of
	 * its subexpressions.
	 * 
	 * @param theIndex  index in list
	 */
	void
	updateOpCodeLength(OpCodeMapSizeType	theIndex)
	{
		assert(theIndex < opCodeMapSize());

		updateOpCodeLength(m_opMap[theIndex], theIndex);
	}

	/**
	 * Update the length of an operation code that has moved to a new index in
	 * the list.
	 * 
	 * @param theOpCode        operation code
	 * @param theOriginalIndex original index in list
	 * @param theNewIndex      new index in list
	 */
	void
	updateShiftedOpCodeLength(
			OpCodeMapValueType	theOpCode,
			OpCodeMapSizeType	theOriginalIndex,
			OpCodeMapSizeType	theNewIndex);

	/**
	 * Update the length of an operation code at a specified index in the list.
	 * This presumes that the other opcodes have been appended to the
	 * expression, and that the specified op code's length needs to be set.
	 * The size includes the normal length of the opcode, plus the length of
	 * its subexpressions.
	 * 
	 * @param theOpCode operation code at specified index
	 * @param theIndex  index in list
	 */
	void
	updateOpCodeLength(
			OpCodeMapValueType	theOpCode,
			OpCodeMapSizeType	theIndex);

	/**
	 * Whether the operation code is one of the node test types, for example,
	 * "ancestor::" or "child::"
	 *
	 * @param theOpCode operation code
	 * @return true if code represents a node test
	 */
	static bool
	isNodeTestOpCode(OpCodeMapValueType		theOpCode);

	/**
	 * Update the length of an operation code after a node test code.
	 * 
	 * @param theIndex  index in list
	 */
	void
	updateOpCodeLengthAfterNodeTest(OpCodeMapSizeType	theIndex);

	/**
	 * Whether there are any more tokens in the token queue.
	 *
	 * @return true if there are more tokens
	 */
	bool
	hasMoreTokens() const
	{
		return tokenQueueSize() - m_currentPosition > 0 ? true : false;
	}

	/**
	 * Retrieve the current position in the token queue.
	 *
	 * @return position in queue
	 */
	TokenQueueSizeType
	getTokenPosition() const
	{
		return m_currentPosition;
	}

	/**
	 * Set the current position in the token queue to zero.
	 */
	void
	resetTokenPosition()
	{
		m_currentPosition = 0;
	}

	/**
	 * Set the current position in the token queue to a specified value.
	 *
	 * @param thePosition value of position to set
	 */
	void
	setTokenPosition(TokenQueueSizeType		thePosition)
	{
		const TokenQueueSizeType	theSize = tokenQueueSize();

		m_currentPosition = thePosition > theSize ? theSize : thePosition;
	}

	/**
	 * Set the current position in the token queue to a specified value.
	 *
	 * @param thePosition value of position to set
	 */
	void
	setTokenPosition(int	thePosition)
	{
		setTokenPosition(thePosition > 0 ? TokenQueueSizeType(thePosition) : 0);
	}

	/**
	 * Retrieve a token at the specified position in the token queue.
	 * 
	 * @param thePosition position in queue
	 * @return pointer to XObject token
	 */
	const XObject*
	getToken(TokenQueueSizeType		thePosition) const
	{
		assert(thePosition < tokenQueueSize());

		return &m_tokenQueue[thePosition];
	}

	/**
	 * Retrieve the next token in the token queue.
	 * 
	 * @return pointer to XObject token
	 */
	const XObject*
	getNextToken()
	{
		if (hasMoreTokens() == true)
		{
			return getToken(m_currentPosition++);
		}
		else
		{
			return 0;
		}
	}

	/**
	 * Retrieve the previous token in the token queue.
	 * 
	 * @return pointer to XObject token
	 */
	const XObject*
	getPreviousToken()
	{
		if (m_currentPosition > 0)
		{
			return getToken(--m_currentPosition);
		}
		else
		{
			return 0;
		}
	}

	/**
	 * Retrieve a token at the specified offset relative to the current
	 * position in the token queue.
	 * 
	 * @param theOffset offset from current position
	 * @return pointer to XObject token
	 */
	const XObject*
	getRelativeToken(int	theOffset) const
	{
		const int	thePosition = int(m_currentPosition) + theOffset;

		if (thePosition < 0 ||
			thePosition >= int(tokenQueueSize()))
		{
			return 0;
		}
		else
		{
			return getToken(thePosition);
		}
	}

	/**
	 * Push a token onto the token queue.
	 * 
	 * @param theToken the string value to push
	 */
	void
	pushToken(const XalanDOMString&		theToken)
	{
		m_tokenQueue.push_back(XToken(theToken));
	}

	/**
	 * Push a token onto the token queue.
	 * 
	 * @param theToken the number value to push
	 */
	void
	pushToken(double	theToken)
	{
		m_tokenQueue.push_back(XToken(theToken));
	}

	/**
	 * Insert a token onto the token queue at the
	 * current position.
	 *
	 * @param theToken the string value to push
	 */
	void
	insertToken(const XalanDOMString&	theToken)
	{
		m_tokenQueue.insert(m_tokenQueue.begin() + (m_currentPosition - 1), XToken(theToken));
	}

	/**
	 * Insert a token onto the token queue at the
	 * current position.
	 *
	 * @param theToken the string value to push
	 */
	void
	insertToken(double	theToken)
	{
		m_tokenQueue.insert(m_tokenQueue.begin() + (m_currentPosition - 1), XToken(theToken));
	}

	/**
	 * Replace a token in the token queue.
	 * 
	 * @param theOffset the offset at which to replace the token.
	 * @param theToken string value for the new token
	 */
	void
	replaceRelativeToken(
			int						theOffset,
			const XalanDOMString&	theToken)
	{
		assert(c_wstr(theToken) != 0);

		const int	thePosition = int(m_currentPosition) + theOffset;

		if (thePosition < 0 ||
			thePosition >= int(tokenQueueSize()))
		{
			throw InvalidRelativeTokenPosition(theOffset);
		}

		m_tokenQueue[thePosition] = theToken;
	}

	/**
	 * Replace a token in the token queue.
	 * 
	 * @param theOffset the offset at which to replace the token.
	 * @param theToken double value for the new token
	 */
	void
	replaceRelativeToken(
			int		theOffset,
			double	theToken)
	{
		assert(theToken != 0);

		const int	thePosition = int(m_currentPosition) + theOffset;

		if (thePosition < 0 || thePosition >= int(tokenQueueSize()))
		{
			throw InvalidRelativeTokenPosition(theOffset);
		}

		m_tokenQueue[thePosition] = theToken;
	}

	/**
	 * Diagnostic function to output the operation code map.
	 * 
	 * @param thePrintWriter   output device
	 * @param theStartPosition starting position in map
	 */
	void
	dumpOpCodeMap(PrintWriter&			thePrintWriter,
				  OpCodeMapSizeType		theStartPosition = 0) const;

	/**
	 * Diagnostic function to output the operation code map.
	 * 
	 * @param theStream output stream
	 * @param theStartPosition starting position in map
	 */
	void
	dumpOpCodeMap(
#if defined(XALAN_NO_NAMESPACES)
			ostream&			theStream,
#else
			std::ostream&		theStream,
#endif
			OpCodeMapSizeType	theStartPosition = 0) const;

	/**
	 * Diagnostic function to output the token queue.
	 * 
	 * @param thePrintWriter   output device
	 * @param theStartPosition starting position in token queue
	 */
	void
	dumpTokenQueue(PrintWriter&			thePrintWriter,
				   TokenQueueSizeType	theStartPosition = 0) const;

	/**
	 * Diagnostic function to output the token queue.
	 * 
	 * @param thePrintWriter   output device
	 * @param theStartPosition starting position in token queue
	 */
	void
	dumpTokenQueue(
#if defined(XALAN_NO_NAMESPACES)
			ostream&			theStream,
#else
			std::ostream&		theStream,
#endif
			TokenQueueSizeType	theStartPosition = 0) const;

	/**
	 * Diagnostic function to output the remaining tokens in the token queue.
	 * 
	 * @param thePrintWriter   output device
	 */
	void
	dumpRemainingTokenQueue(PrintWriter&	thePrintWriter) const;

	/**
	 * Diagnostic function to output the remaining tokens in the token queue.
	 * 
	 * @param theStream The output stream
	 */
	void
#if defined(XALAN_NO_NAMESPACES)
	dumpRemainingTokenQueue(ostream&		theStream) const;
#else
	dumpRemainingTokenQueue(std::ostream&	theStream) const;
#endif

	/**
	 * Push a token onto the token queue and its index onto the operations code
	 * map.
	 *
	 * @param theToken string value of the token to push
	 */
	void
	pushArgumentOnOpCodeMap(const XalanDOMString&	theToken);

	/**
	 * Push a token onto the token queue and its index onto the operations code
	 * map.
	 *
	 * @param theToken number value of the token to push
	 */
	void
	pushArgumentOnOpCodeMap(double	theToken);

	/**
	 * Push the current position in the token queue onto the operations code
	 * map.
	 */
	void
	pushCurrentTokenOnOpCodeMap();

	/**
	 * Retrieve a pattern in the pattern map at the specified position.
	 * position in the token queue.
	 * 
	 * @param thePatternPosition position in pattern map
	 * @return match pattern
	 */
	PatternMapValueType
	getPattern(int	thePatternPosition) const
	{
		assert(int(patternMapSize()) > thePatternPosition);

		return m_patternMap[thePatternPosition];
	}

	/**
	 * Retrieve a pattern in the pattern map at the specified position.
	 * position in the token queue.
	 * 
	 * @param thePatternPosition position in pattern map
	 * @return match pattern
	 */
	PatternMapValueType
	getPattern(PatternMapSizeType	thePatternPosition) const
	{
		assert(patternMapSize() > thePatternPosition);

		return m_patternMap[thePatternPosition];
	}

	/**
	 * Push a pattern onto the pattern map.
	 *
	 * @param thePattern match pattern to push
	 */
	void
	pushPattern(PatternMapValueType	thePattern)
	{
		m_patternMap.push_back(thePattern);
	}

	/**
	 * Adjust the value of a pattern at a specified index in the pattern map.
	 *
	 * @param theIndex      index in map
	 * @param theAdjustment value of adjustment to add
	 */
	void
	adjustPattern(
			OpCodeMapSizeType	theIndex,
			PatternMapValueType	theAdjustment)
	{
		m_patternMap[theIndex] += theAdjustment;
	}

	/**
	 * Change the current pattern in the pattern map.
	 *
	 * @param thePattern match pattern to make current
	 */
	void
	setCurrentPattern(const XalanDOMString&		thePattern)
	{
		m_currentPattern = thePattern;
	}

	/**
	 * Retrieve the current pattern in the pattern map.
	 * 
	 * @return string for current match pattern
	 */
	const XalanDOMString&
	getCurrentPattern() const
	{
		return m_currentPattern;
	}

	/**
	 * An operations map is used instead of a proper parse tree.  It contains
	 * operations codes and indexes into the m_tokenQueue. We use an array
	 * instead of a full parse tree in order to cut down on the number of
	 * objects created.
	 */
	OpCodeMapType			m_opMap;

	/**
	 * The index of the last opcode that was appended or inserted.
	 *
	 */
	OpCodeMapSizeType		m_lastOpCodeIndex;

	/**
	 * The queue of used tokens. The current token is the token at the end of
	 * the m_tokenQueue. The idea is that the queue can be marked and a
	 * sequence of tokens can be reused.
	 */
	TokenQueueType			m_tokenQueue;

	/**
	 *  The current position in the token queue.
	 */
	TokenQueueSizeType		m_currentPosition;

	/**
	 * This holds a map to the m_tokenQueue that tells where the top-level
	 * elements are. It is used for pattern matching so the m_tokenQueue can be
	 * walked backwards. Each element that is a 'target', (right-most top level
	 * element name) has TARGETEXTRA added to it.
	 * 
	 */
	 // Ignore this, it is going away.
	PatternMapType			m_patternMap;

	/**
	 * The current pattern string, for diagnostics purposes.
	 */
	XalanDOMString			m_currentPattern;

private:

	// Default vector allocation sizes.
	enum
	{
		eDefaultOpMapSize = 100,
		eDefaultPatternMapSize = 100
	};

	// A map of Op codes to op code lengths.
	const static OpCodeLengthMapType	s_opCodeLengths;

	static OpCodeLengthMapType
	IntializeOpCodeLengthMap();

	// A static set of Op codes that are node tests.
	const static NodeTestSetType		s_NodeTestOpCodes;

	static NodeTestSetType
	InitializeNodeTestSet();
};



#endif	// XPATHEXPRESSION_HEADER_GUARD_1357924680
