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
 *
 * @author <a href="mailto:david_n_bertoni@lotus.com">David N. Bertoni</a>
 */

#include "Constants.hpp"



#include <PlatformSupport/DOMStringHelper.hpp>



static XalanDOMString		ATTRNAME_CASEORDER;
static XalanDOMString		ATTRNAME_COUNT;
static XalanDOMString		ATTRNAME_DATATYPE;
static XalanDOMString		ATTRNAME_DECIMALSEPARATOR;
static XalanDOMString		ATTRNAME_DEFAULT;
static XalanDOMString		ATTRNAME_DEFAULTSPACE;
static XalanDOMString		ATTRNAME_DIGIT;
static XalanDOMString		ATTRNAME_DIGITGROUPSEP;
static XalanDOMString		ATTRNAME_DISABLE_OUTPUT_ESCAPING;
static XalanDOMString		ATTRNAME_ELEMENTS;
static XalanDOMString		ATTRNAME_EXCLUDE_RESULT_PREFIXES;
static XalanDOMString		ATTRNAME_EXTENSIONELEMENTPREFIXES;
static XalanDOMString		ATTRNAME_ESCAPE_URLS;
static XalanDOMString		ATTRNAME_FORMAT;
static XalanDOMString		ATTRNAME_FROM;
static XalanDOMString		ATTRNAME_GROUPINGSEPARATOR;
static XalanDOMString		ATTRNAME_GROUPINGSIZE;
static XalanDOMString		ATTRNAME_HREF;
static XalanDOMString		ATTRNAME_ID;
static XalanDOMString		ATTRNAME_INDENTAMOUNT;
static XalanDOMString		ATTRNAME_INDENTRESULT;
static XalanDOMString		ATTRNAME_INFINITY;
static XalanDOMString		ATTRNAME_LANG;
static XalanDOMString		ATTRNAME_LETTERVALUE;
static XalanDOMString		ATTRNAME_MATCH;
static XalanDOMString		ATTRNAME_MINUSSIGN;
static XalanDOMString		ATTRNAME_MODE;
static XalanDOMString		ATTRNAME_NAME;
static XalanDOMString		ATTRNAME_NAMESPACE;
static XalanDOMString		ATTRNAME_NAN;
static XalanDOMString		ATTRNAME_NDIGITSPERGROUP;
static XalanDOMString		ATTRNAME_OMIT_META_TAG;
static XalanDOMString		ATTRNAME_ORDER;
static XalanDOMString		ATTRNAME_OUTPUT_CDATA_SECTION_ELEMENTS;
static XalanDOMString		ATTRNAME_OUTPUT_DOCTYPE_PUBLIC;
static XalanDOMString		ATTRNAME_OUTPUT_DOCTYPE_SYSTEM;
static XalanDOMString		ATTRNAME_OUTPUT_ENCODING;
static XalanDOMString		ATTRNAME_OUTPUT_INDENT;
static XalanDOMString		ATTRNAME_OUTPUT_MEDIATYPE;
static XalanDOMString		ATTRNAME_OUTPUT_METHOD;
static XalanDOMString		ATTRNAME_OUTPUT_OMITXMLDECL;
static XalanDOMString		ATTRNAME_OUTPUT_STANDALONE;
static XalanDOMString		ATTRNAME_OUTPUT_VERSION;
static XalanDOMString		ATTRNAME_PATTERNSEPARATOR;
static XalanDOMString		ATTRNAME_PERCENT;
static XalanDOMString		ATTRNAME_PERMILLE;
static XalanDOMString		ATTRNAME_PREFIX;
static XalanDOMString		ATTRNAME_PRIORITY;
static XalanDOMString		ATTRNAME_RESULTNS;
static XalanDOMString		ATTRNAME_RESULT_PREFIX;
static XalanDOMString		ATTRNAME_SELECT;
static XalanDOMString		ATTRNAME_STYLESHEET_PREFIX;
static XalanDOMString		ATTRNAME_TERMINATE;
static XalanDOMString		ATTRNAME_TEST;
static XalanDOMString		ATTRNAME_TYPE;
static XalanDOMString		ATTRNAME_USE;
static XalanDOMString		ATTRNAME_USEATTRIBUTESETS;
static XalanDOMString		ATTRNAME_VALUE;
static XalanDOMString		ATTRNAME_VERSION;
static XalanDOMString		ATTRNAME_SPACE;
static XalanDOMString		ATTRNAME_ZERODIGIT;

static XalanDOMString		ATTRTYPE_CDATA;

static XalanDOMString		ATTRVAL_CASEORDER_LOWER;
static XalanDOMString		ATTRVAL_CASEORDER_UPPER;
static XalanDOMString		ATTRVAL_DATATYPE_NUMBER;
static XalanDOMString		ATTRVAL_DATATYPE_TEXT;
static XalanDOMString		ATTRVAL_DEFAULT;
static XalanDOMString		ATTRVAL_DEFAULT_PREFIX;
static XalanDOMString		ATTRVAL_DEFAULT_TEXT_RULE;
static XalanDOMString		ATTRVAL_INFINITY;
static XalanDOMString		ATTRVAL_NAN;
static XalanDOMString		ATTRVAL_NO;
static XalanDOMString		ATTRVAL_ORDER_ASCENDING;
static XalanDOMString		ATTRVAL_ORDER_DESCENDING;
static XalanDOMString		ATTRVAL_OUTPUT_METHOD_HTML;
static XalanDOMString		ATTRVAL_OUTPUT_METHOD_TEXT;
static XalanDOMString		ATTRVAL_OUTPUT_METHOD_XML;
static XalanDOMString		ATTRVAL_PRESERVE;
static XalanDOMString		ATTRVAL_SIMPLE;
static XalanDOMString		ATTRVAL_STRIP;
static XalanDOMString		ATTRVAL_THIS;
static XalanDOMString		ATTRVAL_YES;

static XalanDOMString		DEFAULT_WHITESPACE_SEPARATOR_STRING;

static XalanDOMString		ELEMNAME_ANY_STRING;
static XalanDOMString		ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_APPLY_TEMPLATES_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_ATTRIBUTESET_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_ATTRIBUTE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_CHOOSE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_COMMENT_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_COPY_OF_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_COPY_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_DECIMALFORMAT_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_DISPLAYIF_STRING;
static XalanDOMString		ELEMNAME_ELEMENT_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_FALLBACK_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_FOREACH_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_HTML_STRING;
static XalanDOMString		ELEMNAME_IF_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_MESSAGE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_NUMBER_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_OTHERWISE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_PARAM_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_PI_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_SORT_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_TEMPLATE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_TEXT_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_VALUEOF_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_VARIABLE_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_WHEN_WITH_PREFIX_STRING;
static XalanDOMString		ELEMNAME_WITHPARAM_WITH_PREFIX_STRING;

static XalanDOMString		PSEUDONAME_NODE;



const XalanDOMString&		Constants::ATTRNAME_CASEORDER = ::ATTRNAME_CASEORDER;
const XalanDOMString&		Constants::ATTRNAME_COUNT = ::ATTRNAME_COUNT;
const XalanDOMString&		Constants::ATTRNAME_DATATYPE = ::ATTRNAME_DATATYPE;
const XalanDOMString&		Constants::ATTRNAME_DECIMALSEPARATOR = ::ATTRNAME_DECIMALSEPARATOR;
const XalanDOMString&		Constants::ATTRNAME_DEFAULT = ::ATTRNAME_DEFAULT;
const XalanDOMString&		Constants::ATTRNAME_DEFAULTSPACE = ::ATTRNAME_DEFAULTSPACE;
const XalanDOMString&		Constants::ATTRNAME_DIGIT = ::ATTRNAME_DIGIT;
const XalanDOMString&		Constants::ATTRNAME_DIGITGROUPSEP = ::ATTRNAME_DIGITGROUPSEP;
const XalanDOMString&		Constants::ATTRNAME_DISABLE_OUTPUT_ESCAPING  = ::ATTRNAME_DISABLE_OUTPUT_ESCAPING;
const XalanDOMString&		Constants::ATTRNAME_ELEMENTS = ::ATTRNAME_ELEMENTS;
const XalanDOMString&		Constants::ATTRNAME_ESCAPE_URLS = ::ATTRNAME_ESCAPE_URLS;
const XalanDOMString&		Constants::ATTRNAME_EXCLUDE_RESULT_PREFIXES = ::ATTRNAME_EXCLUDE_RESULT_PREFIXES;
const XalanDOMString&		Constants::ATTRNAME_EXTENSIONELEMENTPREFIXES = ::ATTRNAME_EXTENSIONELEMENTPREFIXES;
const XalanDOMString&		Constants::ATTRNAME_FORMAT = ::ATTRNAME_FORMAT;
const XalanDOMString&		Constants::ATTRNAME_FROM = ::ATTRNAME_FROM;
const XalanDOMString&		Constants::ATTRNAME_GROUPINGSEPARATOR = ::ATTRNAME_GROUPINGSEPARATOR;
const XalanDOMString&		Constants::ATTRNAME_GROUPINGSIZE = ::ATTRNAME_GROUPINGSIZE;
const XalanDOMString&		Constants::ATTRNAME_HREF = ::ATTRNAME_HREF;
const XalanDOMString&		Constants::ATTRNAME_ID = ::ATTRNAME_ID;
const XalanDOMString&		Constants::ATTRNAME_INDENTAMOUNT = ::ATTRNAME_INDENTAMOUNT;
const XalanDOMString&		Constants::ATTRNAME_INDENTRESULT = ::ATTRNAME_INDENTRESULT;
const XalanDOMString&		Constants::ATTRNAME_INFINITY = ::ATTRNAME_INFINITY;
const XalanDOMString&		Constants::ATTRNAME_LANG = ::ATTRNAME_LANG;
const XalanDOMString&		Constants::ATTRNAME_LETTERVALUE = ::ATTRNAME_LETTERVALUE;
const XalanDOMString&		Constants::ATTRNAME_MATCH = ::ATTRNAME_MATCH;
const XalanDOMString&		Constants::ATTRNAME_MINUSSIGN = ::ATTRNAME_MINUSSIGN;
const XalanDOMString&		Constants::ATTRNAME_MODE = ::ATTRNAME_MODE;
const XalanDOMString&		Constants::ATTRNAME_NAME = ::ATTRNAME_NAME;
const XalanDOMString&		Constants::ATTRNAME_NAMESPACE = ::ATTRNAME_NAMESPACE;
const XalanDOMString&		Constants::ATTRNAME_NAN = ::ATTRNAME_NAN;
const XalanDOMString&		Constants::ATTRNAME_NDIGITSPERGROUP = ::ATTRNAME_NDIGITSPERGROUP;
const XalanDOMString&		Constants::ATTRNAME_OMIT_META_TAG = ::ATTRNAME_OMIT_META_TAG;
const XalanDOMString&		Constants::ATTRNAME_ORDER = ::ATTRNAME_ORDER;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_CDATA_SECTION_ELEMENTS  = ::ATTRNAME_OUTPUT_CDATA_SECTION_ELEMENTS;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_DOCTYPE_PUBLIC = ::ATTRNAME_OUTPUT_DOCTYPE_PUBLIC;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_DOCTYPE_SYSTEM = ::ATTRNAME_OUTPUT_DOCTYPE_SYSTEM;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_ENCODING = ::ATTRNAME_OUTPUT_ENCODING;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_INDENT = ::ATTRNAME_OUTPUT_INDENT;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_MEDIATYPE = ::ATTRNAME_OUTPUT_MEDIATYPE;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_METHOD = ::ATTRNAME_OUTPUT_METHOD;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_OMITXMLDECL = ::ATTRNAME_OUTPUT_OMITXMLDECL;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_STANDALONE  = ::ATTRNAME_OUTPUT_STANDALONE;
const XalanDOMString&		Constants::ATTRNAME_OUTPUT_VERSION = ::ATTRNAME_OUTPUT_VERSION;
const XalanDOMString&		Constants::ATTRNAME_PATTERNSEPARATOR = ::ATTRNAME_PATTERNSEPARATOR;
const XalanDOMString&		Constants::ATTRNAME_PERCENT = ::ATTRNAME_PERCENT;
const XalanDOMString&		Constants::ATTRNAME_PERMILLE = ::ATTRNAME_PERMILLE;
const XalanDOMString&		Constants::ATTRNAME_PREFIX = ::ATTRNAME_PREFIX;
const XalanDOMString&		Constants::ATTRNAME_PRIORITY = ::ATTRNAME_PRIORITY;
const XalanDOMString&		Constants::ATTRNAME_RESULTNS = ::ATTRNAME_RESULTNS;
const XalanDOMString&		Constants::ATTRNAME_RESULT_PREFIX = ::ATTRNAME_RESULT_PREFIX;
const XalanDOMString&		Constants::ATTRNAME_SELECT = ::ATTRNAME_SELECT;
const XalanDOMString&		Constants::ATTRNAME_STYLESHEET_PREFIX = ::ATTRNAME_STYLESHEET_PREFIX;
const XalanDOMString&		Constants::ATTRNAME_TERMINATE = ::ATTRNAME_TERMINATE;
const XalanDOMString&		Constants::ATTRNAME_TEST = ::ATTRNAME_TEST;
const XalanDOMString&		Constants::ATTRNAME_TYPE = ::ATTRNAME_TYPE;
const XalanDOMString&		Constants::ATTRNAME_USE = ::ATTRNAME_USE;
const XalanDOMString&		Constants::ATTRNAME_USEATTRIBUTESETS = ::ATTRNAME_USEATTRIBUTESETS;
const XalanDOMString&		Constants::ATTRNAME_VALUE = ::ATTRNAME_VALUE;
const XalanDOMString&		Constants::ATTRNAME_VERSION = ::ATTRNAME_VERSION;
const XalanDOMString&		Constants::ATTRNAME_SPACE = ::ATTRNAME_SPACE;
const XalanDOMString&		Constants::ATTRNAME_ZERODIGIT = ::ATTRNAME_ZERODIGIT;

const XalanDOMString&		Constants::ATTRTYPE_CDATA = ::ATTRTYPE_CDATA;

const XalanDOMString&		Constants::ATTRVAL_CASEORDER_LOWER = ::ATTRVAL_CASEORDER_LOWER;
const XalanDOMString&		Constants::ATTRVAL_CASEORDER_UPPER = ::ATTRVAL_CASEORDER_UPPER;
const XalanDOMString&		Constants::ATTRVAL_DATATYPE_NUMBER = ::ATTRVAL_DATATYPE_NUMBER;
const XalanDOMString&		Constants::ATTRVAL_DATATYPE_TEXT = ::ATTRVAL_DATATYPE_TEXT;
const XalanDOMString&		Constants::ATTRVAL_DEFAULT = ::ATTRVAL_DEFAULT;
const XalanDOMString&		Constants::ATTRVAL_DEFAULT_PREFIX = ::ATTRVAL_DEFAULT_PREFIX;
const XalanDOMString&		Constants::ATTRVAL_DEFAULT_TEXT_RULE = ::ATTRVAL_DEFAULT_TEXT_RULE;
const XalanDOMString&		Constants::ATTRVAL_INFINITY = ::ATTRVAL_INFINITY;
const XalanDOMString&		Constants::ATTRVAL_NAN = ::ATTRVAL_NAN;
const XalanDOMString&		Constants::ATTRVAL_NO = ::ATTRVAL_NO;
const XalanDOMString&		Constants::ATTRVAL_ORDER_ASCENDING = ::ATTRVAL_ORDER_ASCENDING;
const XalanDOMString&		Constants::ATTRVAL_ORDER_DESCENDING = ::ATTRVAL_ORDER_DESCENDING;
const XalanDOMString&		Constants::ATTRVAL_OUTPUT_METHOD_HTML = ::ATTRVAL_OUTPUT_METHOD_HTML;
const XalanDOMString&		Constants::ATTRVAL_OUTPUT_METHOD_TEXT = ::ATTRVAL_OUTPUT_METHOD_TEXT;
const XalanDOMString&		Constants::ATTRVAL_OUTPUT_METHOD_XML = ::ATTRVAL_OUTPUT_METHOD_XML;
const XalanDOMString&		Constants::ATTRVAL_PRESERVE = ::ATTRVAL_PRESERVE;
const XalanDOMString&		Constants::ATTRVAL_SIMPLE = ::ATTRVAL_SIMPLE;
const XalanDOMString&		Constants::ATTRVAL_STRIP = ::ATTRVAL_STRIP;
const XalanDOMString&		Constants::ATTRVAL_THIS = ::ATTRVAL_THIS;
const XalanDOMString&		Constants::ATTRVAL_YES = ::ATTRVAL_YES;

const XalanDOMString&		Constants::DEFAULT_WHITESPACE_SEPARATOR_STRING = ::DEFAULT_WHITESPACE_SEPARATOR_STRING;

const XalanDOMString&		Constants::ELEMNAME_ANY_STRING = ::ELEMNAME_ANY_STRING;
const XalanDOMString&		Constants::ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING = ::ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_APPLY_TEMPLATES_WITH_PREFIX_STRING = ::ELEMNAME_APPLY_TEMPLATES_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_ATTRIBUTESET_WITH_PREFIX_STRING = ::ELEMNAME_ATTRIBUTESET_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_ATTRIBUTE_WITH_PREFIX_STRING = ::ELEMNAME_ATTRIBUTE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING = ::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_CHOOSE_WITH_PREFIX_STRING = ::ELEMNAME_CHOOSE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_COMMENT_WITH_PREFIX_STRING = ::ELEMNAME_COMMENT_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_COPY_OF_WITH_PREFIX_STRING = ::ELEMNAME_COPY_OF_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_COPY_WITH_PREFIX_STRING = ::ELEMNAME_COPY_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_DECIMALFORMAT_WITH_PREFIX_STRING = ::ELEMNAME_DECIMALFORMAT_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_ELEMENT_WITH_PREFIX_STRING = ::ELEMNAME_ELEMENT_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_FALLBACK_WITH_PREFIX_STRING = ::ELEMNAME_FALLBACK_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_FOREACH_WITH_PREFIX_STRING = ::ELEMNAME_FOREACH_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_HTML_STRING = ::ELEMNAME_HTML_STRING;
const XalanDOMString&		Constants::ELEMNAME_IF_WITH_PREFIX_STRING = ::ELEMNAME_IF_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_MESSAGE_WITH_PREFIX_STRING = ::ELEMNAME_MESSAGE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_NUMBER_WITH_PREFIX_STRING = ::ELEMNAME_NUMBER_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_OTHERWISE_WITH_PREFIX_STRING = ::ELEMNAME_OTHERWISE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_PARAM_WITH_PREFIX_STRING = ::ELEMNAME_PARAM_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_PI_WITH_PREFIX_STRING = ::ELEMNAME_PI_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_SORT_WITH_PREFIX_STRING = ::ELEMNAME_SORT_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_TEMPLATE_WITH_PREFIX_STRING = ::ELEMNAME_TEMPLATE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_TEXT_WITH_PREFIX_STRING = ::ELEMNAME_TEXT_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_VALUEOF_WITH_PREFIX_STRING = ::ELEMNAME_VALUEOF_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_VARIABLE_WITH_PREFIX_STRING = ::ELEMNAME_VARIABLE_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_WHEN_WITH_PREFIX_STRING = ::ELEMNAME_WHEN_WITH_PREFIX_STRING;
const XalanDOMString&		Constants::ELEMNAME_WITHPARAM_WITH_PREFIX_STRING = ::ELEMNAME_WITHPARAM_WITH_PREFIX_STRING;

const XalanDOMString&		Constants::PSEUDONAME_NODE = ::PSEUDONAME_NODE;



void
Constants::initialize()
{
	::ATTRNAME_CASEORDER = XALAN_STATIC_UCODE_STRING("case-order");
	::ATTRNAME_COUNT = XALAN_STATIC_UCODE_STRING("count");
	::ATTRNAME_DATATYPE = XALAN_STATIC_UCODE_STRING("data-type");
	::ATTRNAME_DECIMALSEPARATOR = XALAN_STATIC_UCODE_STRING("decimal-separator");
	::ATTRNAME_DEFAULT = XALAN_STATIC_UCODE_STRING("default");
	::ATTRNAME_DEFAULTSPACE = XALAN_STATIC_UCODE_STRING("default-space");
	::ATTRNAME_DIGIT = XALAN_STATIC_UCODE_STRING("digit");
	::ATTRNAME_DIGITGROUPSEP = XALAN_STATIC_UCODE_STRING("digit-group-sep");
	::ATTRNAME_DISABLE_OUTPUT_ESCAPING  = XALAN_STATIC_UCODE_STRING("disable-output-escaping");
	::ATTRNAME_ELEMENTS = XALAN_STATIC_UCODE_STRING("elements");
	::ATTRNAME_ESCAPE_URLS = XALAN_STATIC_UCODE_STRING("use-url-escaping");
	::ATTRNAME_EXCLUDE_RESULT_PREFIXES = XALAN_STATIC_UCODE_STRING("exclude-result-prefixes");
	::ATTRNAME_EXTENSIONELEMENTPREFIXES = XALAN_STATIC_UCODE_STRING("extension-element-prefixes");
	::ATTRNAME_FORMAT = XALAN_STATIC_UCODE_STRING("format");
	::ATTRNAME_FROM = XALAN_STATIC_UCODE_STRING("from");
	::ATTRNAME_GROUPINGSEPARATOR = XALAN_STATIC_UCODE_STRING("grouping-separator");
	::ATTRNAME_GROUPINGSIZE = XALAN_STATIC_UCODE_STRING("grouping-size");
	::ATTRNAME_HREF = XALAN_STATIC_UCODE_STRING("href");
	::ATTRNAME_ID = XALAN_STATIC_UCODE_STRING("id");
	::ATTRNAME_INDENTAMOUNT = XALAN_STATIC_UCODE_STRING("indent-amount");
	::ATTRNAME_INDENTRESULT = XALAN_STATIC_UCODE_STRING("indent-result");
	::ATTRNAME_INFINITY = XALAN_STATIC_UCODE_STRING("infinity");
	::ATTRNAME_LANG = XALAN_STATIC_UCODE_STRING("lang");
	::ATTRNAME_LETTERVALUE = XALAN_STATIC_UCODE_STRING("letter-value");
	::ATTRNAME_MATCH = XALAN_STATIC_UCODE_STRING("match");
	::ATTRNAME_MINUSSIGN = XALAN_STATIC_UCODE_STRING("minus-sign");
	::ATTRNAME_MODE = XALAN_STATIC_UCODE_STRING("mode");
	::ATTRNAME_NAME = XALAN_STATIC_UCODE_STRING("name");
	::ATTRNAME_NAMESPACE = XALAN_STATIC_UCODE_STRING("namespace");
	::ATTRNAME_NAN = XALAN_STATIC_UCODE_STRING("NaN");
	::ATTRNAME_NDIGITSPERGROUP = XALAN_STATIC_UCODE_STRING("n-digits-per-group");
	::ATTRNAME_OMIT_META_TAG = XALAN_STATIC_UCODE_STRING("omit-meta-tag");
	::ATTRNAME_ORDER = XALAN_STATIC_UCODE_STRING("order");
	::ATTRNAME_OUTPUT_CDATA_SECTION_ELEMENTS  = XALAN_STATIC_UCODE_STRING("cdata-section-elements");
	::ATTRNAME_OUTPUT_DOCTYPE_PUBLIC = XALAN_STATIC_UCODE_STRING("doctype-public");
	::ATTRNAME_OUTPUT_DOCTYPE_SYSTEM = XALAN_STATIC_UCODE_STRING("doctype-system");
	::ATTRNAME_OUTPUT_ENCODING = XALAN_STATIC_UCODE_STRING("encoding");
	::ATTRNAME_OUTPUT_INDENT = XALAN_STATIC_UCODE_STRING("indent");
	::ATTRNAME_OUTPUT_MEDIATYPE = XALAN_STATIC_UCODE_STRING("media-type");
	::ATTRNAME_OUTPUT_METHOD = XALAN_STATIC_UCODE_STRING("method");
	::ATTRNAME_OUTPUT_OMITXMLDECL = XALAN_STATIC_UCODE_STRING("omit-xml-declaration");
	::ATTRNAME_OUTPUT_STANDALONE  = XALAN_STATIC_UCODE_STRING("standalone");
	::ATTRNAME_OUTPUT_VERSION = XALAN_STATIC_UCODE_STRING("version");
	::ATTRNAME_PATTERNSEPARATOR = XALAN_STATIC_UCODE_STRING("pattern-separator");
	::ATTRNAME_PERCENT = XALAN_STATIC_UCODE_STRING("percent");
	::ATTRNAME_PERMILLE = XALAN_STATIC_UCODE_STRING("per-mille");
	::ATTRNAME_PREFIX = XALAN_STATIC_UCODE_STRING("prefix");
	::ATTRNAME_PRIORITY = XALAN_STATIC_UCODE_STRING("priority");
	::ATTRNAME_RESULTNS = XALAN_STATIC_UCODE_STRING("result-ns");
	::ATTRNAME_RESULT_PREFIX = XALAN_STATIC_UCODE_STRING("result-prefix");
	::ATTRNAME_SELECT = XALAN_STATIC_UCODE_STRING("select");
	::ATTRNAME_STYLESHEET_PREFIX = XALAN_STATIC_UCODE_STRING("stylesheet-prefix");
	::ATTRNAME_TERMINATE = XALAN_STATIC_UCODE_STRING("terminate");
	::ATTRNAME_TEST = XALAN_STATIC_UCODE_STRING("test");
	::ATTRNAME_TYPE = XALAN_STATIC_UCODE_STRING("type");
	::ATTRNAME_USE = XALAN_STATIC_UCODE_STRING("use");
	::ATTRNAME_USEATTRIBUTESETS = XALAN_STATIC_UCODE_STRING("use-attribute-sets");
	::ATTRNAME_VALUE = XALAN_STATIC_UCODE_STRING("value");
	::ATTRNAME_VERSION = XALAN_STATIC_UCODE_STRING("version");
	::ATTRNAME_SPACE = XALAN_STATIC_UCODE_STRING("space");
	::ATTRNAME_ZERODIGIT = XALAN_STATIC_UCODE_STRING("zero-digit");

	::ATTRTYPE_CDATA = XALAN_STATIC_UCODE_STRING("CDATA");

	::ATTRVAL_CASEORDER_LOWER = XALAN_STATIC_UCODE_STRING("lower-first");
	::ATTRVAL_CASEORDER_UPPER = XALAN_STATIC_UCODE_STRING("upper-first");
	::ATTRVAL_DATATYPE_NUMBER = XALAN_STATIC_UCODE_STRING("number");
	::ATTRVAL_DATATYPE_TEXT = XALAN_STATIC_UCODE_STRING("text");
	::ATTRVAL_DEFAULT = XALAN_STATIC_UCODE_STRING("default");
	::ATTRVAL_DEFAULT_PREFIX = XALAN_STATIC_UCODE_STRING("#default");
	::ATTRVAL_DEFAULT_TEXT_RULE = XALAN_STATIC_UCODE_STRING("text() | @*");
	::ATTRVAL_INFINITY = XALAN_STATIC_UCODE_STRING("Infinity");
	::ATTRVAL_NAN = XALAN_STATIC_UCODE_STRING("NaN");
	::ATTRVAL_NO = XALAN_STATIC_UCODE_STRING("no");
	::ATTRVAL_ORDER_ASCENDING = XALAN_STATIC_UCODE_STRING("ascending");
	::ATTRVAL_ORDER_DESCENDING = XALAN_STATIC_UCODE_STRING("descending");
	::ATTRVAL_OUTPUT_METHOD_HTML = XALAN_STATIC_UCODE_STRING("html");
	::ATTRVAL_OUTPUT_METHOD_TEXT = XALAN_STATIC_UCODE_STRING("text");
	::ATTRVAL_OUTPUT_METHOD_XML = XALAN_STATIC_UCODE_STRING("xml");
	::ATTRVAL_PRESERVE = XALAN_STATIC_UCODE_STRING("preserve");
	::ATTRVAL_SIMPLE = XALAN_STATIC_UCODE_STRING("simple");
	::ATTRVAL_STRIP = XALAN_STATIC_UCODE_STRING("strip");
	::ATTRVAL_THIS = XALAN_STATIC_UCODE_STRING(".");
	::ATTRVAL_YES = XALAN_STATIC_UCODE_STRING("yes");

	::DEFAULT_WHITESPACE_SEPARATOR_STRING = XALAN_STATIC_UCODE_STRING(" \t\n\r");

	::ELEMNAME_ANY_STRING = XALAN_STATIC_UCODE_STRING("any");
	::ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:apply-imports");
	::ELEMNAME_APPLY_TEMPLATES_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:apply-templates");
	::ELEMNAME_ATTRIBUTESET_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:attribute-set");
	::ELEMNAME_ATTRIBUTE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:attribute");
	::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:call-template");
	::ELEMNAME_CHOOSE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:choose");
	::ELEMNAME_COMMENT_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:comment");
	::ELEMNAME_COPY_OF_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:copy-of");
	::ELEMNAME_COPY_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:copy");
	::ELEMNAME_DECIMALFORMAT_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:decimal-format");
	::ELEMNAME_DISPLAYIF_STRING = XALAN_STATIC_UCODE_STRING("display-if");
	::ELEMNAME_ELEMENT_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:element");
	::ELEMNAME_FALLBACK_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:fallback");
	::ELEMNAME_FOREACH_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:for-each");
	::ELEMNAME_HTML_STRING = XALAN_STATIC_UCODE_STRING("HTML");
	::ELEMNAME_IF_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:if");
	::ELEMNAME_MESSAGE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:message");
	::ELEMNAME_NUMBER_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:number");
	::ELEMNAME_OTHERWISE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:otherwise");
	::ELEMNAME_PARAM_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:param");
	::ELEMNAME_PI_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:processing-instruction");
	::ELEMNAME_SORT_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:sort");
	::ELEMNAME_TEMPLATE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:template");
	::ELEMNAME_TEXT_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:text");
	::ELEMNAME_VALUEOF_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:value-of");
	::ELEMNAME_VARIABLE_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:variable");
	::ELEMNAME_WHEN_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:when");
	::ELEMNAME_WITHPARAM_WITH_PREFIX_STRING = XALAN_STATIC_UCODE_STRING("xsl:with-param");

	::PSEUDONAME_NODE = XALAN_STATIC_UCODE_STRING("node()");
}



void
Constants::terminate()
{
	releaseMemory(::ATTRNAME_CASEORDER);
	releaseMemory(::ATTRNAME_COUNT);
	releaseMemory(::ATTRNAME_DATATYPE);
	releaseMemory(::ATTRNAME_DECIMALSEPARATOR);
	releaseMemory(::ATTRNAME_DEFAULT);
	releaseMemory(::ATTRNAME_DEFAULTSPACE);
	releaseMemory(::ATTRNAME_DIGIT);
	releaseMemory(::ATTRNAME_DIGITGROUPSEP);
	releaseMemory(::ATTRNAME_DISABLE_OUTPUT_ESCAPING);
	releaseMemory(::ATTRNAME_ELEMENTS);
	releaseMemory(::ATTRNAME_ESCAPE_URLS);
	releaseMemory(::ATTRNAME_EXCLUDE_RESULT_PREFIXES);
	releaseMemory(::ATTRNAME_EXTENSIONELEMENTPREFIXES);
	releaseMemory(::ATTRNAME_FORMAT);
	releaseMemory(::ATTRNAME_FROM);
	releaseMemory(::ATTRNAME_GROUPINGSEPARATOR);
	releaseMemory(::ATTRNAME_GROUPINGSIZE);
	releaseMemory(::ATTRNAME_HREF);
	releaseMemory(::ATTRNAME_ID);
	releaseMemory(::ATTRNAME_INDENTAMOUNT);
	releaseMemory(::ATTRNAME_INDENTRESULT);
	releaseMemory(::ATTRNAME_INFINITY);
	releaseMemory(::ATTRNAME_LANG);
	releaseMemory(::ATTRNAME_LETTERVALUE);
	releaseMemory(::ATTRNAME_MATCH);
	releaseMemory(::ATTRNAME_MINUSSIGN);
	releaseMemory(::ATTRNAME_MODE);
	releaseMemory(::ATTRNAME_NAME);
	releaseMemory(::ATTRNAME_NAMESPACE);
	releaseMemory(::ATTRNAME_NAN);
	releaseMemory(::ATTRNAME_NDIGITSPERGROUP);
	releaseMemory(::ATTRNAME_OMIT_META_TAG);
	releaseMemory(::ATTRNAME_ORDER);
	releaseMemory(::ATTRNAME_OUTPUT_CDATA_SECTION_ELEMENTS);
	releaseMemory(::ATTRNAME_OUTPUT_DOCTYPE_PUBLIC);
	releaseMemory(::ATTRNAME_OUTPUT_DOCTYPE_SYSTEM);
	releaseMemory(::ATTRNAME_OUTPUT_ENCODING);
	releaseMemory(::ATTRNAME_OUTPUT_INDENT);
	releaseMemory(::ATTRNAME_OUTPUT_MEDIATYPE);
	releaseMemory(::ATTRNAME_OUTPUT_METHOD);
	releaseMemory(::ATTRNAME_OUTPUT_OMITXMLDECL);
	releaseMemory(::ATTRNAME_OUTPUT_STANDALONE);
	releaseMemory(::ATTRNAME_OUTPUT_VERSION);
	releaseMemory(::ATTRNAME_PATTERNSEPARATOR);
	releaseMemory(::ATTRNAME_PERCENT);
	releaseMemory(::ATTRNAME_PERMILLE);
	releaseMemory(::ATTRNAME_PREFIX);
	releaseMemory(::ATTRNAME_PRIORITY);
	releaseMemory(::ATTRNAME_RESULTNS);
	releaseMemory(::ATTRNAME_RESULT_PREFIX);
	releaseMemory(::ATTRNAME_SELECT);
	releaseMemory(::ATTRNAME_STYLESHEET_PREFIX);
	releaseMemory(::ATTRNAME_TERMINATE);
	releaseMemory(::ATTRNAME_TEST);
	releaseMemory(::ATTRNAME_TYPE);
	releaseMemory(::ATTRNAME_USE);
	releaseMemory(::ATTRNAME_USEATTRIBUTESETS);
	releaseMemory(::ATTRNAME_VALUE);
	releaseMemory(::ATTRNAME_VERSION);
	releaseMemory(::ATTRNAME_SPACE);
	releaseMemory(::ATTRNAME_ZERODIGIT);

	releaseMemory(::ATTRTYPE_CDATA);

	releaseMemory(::ATTRVAL_CASEORDER_LOWER);
	releaseMemory(::ATTRVAL_CASEORDER_UPPER);
	releaseMemory(::ATTRVAL_DATATYPE_NUMBER);
	releaseMemory(::ATTRVAL_DATATYPE_TEXT);
	releaseMemory(::ATTRVAL_DEFAULT);
	releaseMemory(::ATTRVAL_DEFAULT_PREFIX);
	releaseMemory(::ATTRVAL_DEFAULT_TEXT_RULE);
	releaseMemory(::ATTRVAL_INFINITY);
	releaseMemory(::ATTRVAL_NAN);
	releaseMemory(::ATTRVAL_NO);
	releaseMemory(::ATTRVAL_ORDER_ASCENDING);
	releaseMemory(::ATTRVAL_ORDER_DESCENDING);
	releaseMemory(::ATTRVAL_OUTPUT_METHOD_HTML);
	releaseMemory(::ATTRVAL_OUTPUT_METHOD_TEXT);
	releaseMemory(::ATTRVAL_OUTPUT_METHOD_XML);
	releaseMemory(::ATTRVAL_PRESERVE);
	releaseMemory(::ATTRVAL_SIMPLE);
	releaseMemory(::ATTRVAL_STRIP);
	releaseMemory(::ATTRVAL_THIS);
	releaseMemory(::ATTRVAL_YES);

	releaseMemory(::DEFAULT_WHITESPACE_SEPARATOR_STRING);

	releaseMemory(::ELEMNAME_ANY_STRING);
	releaseMemory(::ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_APPLY_TEMPLATES_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_ATTRIBUTESET_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_ATTRIBUTE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_CALLTEMPLATE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_CHOOSE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_COMMENT_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_COPY_OF_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_COPY_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_DECIMALFORMAT_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_DISPLAYIF_STRING);
	releaseMemory(::ELEMNAME_ELEMENT_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_FALLBACK_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_FOREACH_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_HTML_STRING);
	releaseMemory(::ELEMNAME_IF_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_MESSAGE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_NUMBER_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_OTHERWISE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_PARAM_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_PI_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_SORT_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_TEMPLATE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_TEXT_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_VALUEOF_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_VARIABLE_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_WHEN_WITH_PREFIX_STRING);
	releaseMemory(::ELEMNAME_WITHPARAM_WITH_PREFIX_STRING);

	releaseMemory(::PSEUDONAME_NODE);
}
