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
 *
 * $ Id: $
 *
 */

#include "NodeSortKey.hpp"



#include <PlatformSupport/DOMStringHelper.hpp>




NodeSortKey::NodeSortKey(
			ExecutionContext&		executionContext,
			const XPath&			selectPat, 
			bool					treatAsNumbers, 
			bool					descending,
			const XalanDOMString&	/* langValue */, 
			const PrefixResolver&	resolver) :
	m_executionContext(&executionContext),
	m_selectPat(&selectPat),
	m_treatAsNumbers(treatAsNumbers),
	m_descending(descending),
	m_prefixResolver(&resolver)
{
#if 0
	// $$$ ToDo: What do we do about this?
	if(0 != length(langValue))
	{
		m_locale = new Locale(langValue.toUpperCase(), 
							Locale.getDefault().getDisplayCountry());

		if(null == m_locale)
		{
			// m_processor.warn("Could not find locale for <sort xml:lang="+langValue);
			m_locale = Locale.getDefault();
		}
	}
	else
	{
		m_locale = Locale.getDefault();
	}

	m_col = Collator.getInstance(m_locale);

	if(null == m_col)
	{
		executionContext.warn("Could not find Collator for <sort xml:lang=" + langValue);

		m_col = Collator.getInstance();
	}
#endif
}



NodeSortKey::NodeSortKey() :
	m_executionContext(0),
	m_selectPat(0),
	m_treatAsNumbers(false),
	m_descending(false),
	m_prefixResolver(0)
{
}



NodeSortKey::NodeSortKey(const NodeSortKey&		theSource) :
	m_executionContext(theSource.m_executionContext),
	m_selectPat(theSource.m_selectPat),
	m_treatAsNumbers(theSource.m_treatAsNumbers),
	m_descending(theSource.m_descending),
	m_prefixResolver(theSource.m_prefixResolver)
{
}



NodeSortKey::~NodeSortKey()
{
}



NodeSortKey&
NodeSortKey::operator=(const NodeSortKey&	theRHS)
{
	if (this != &theRHS)
	{
		m_executionContext = theRHS.m_executionContext;
		m_selectPat = theRHS.m_selectPat;
		m_treatAsNumbers = theRHS.m_treatAsNumbers;
		m_descending = theRHS.m_descending;
		m_prefixResolver = theRHS.m_prefixResolver;
	}

	return *this;
}


/*
 *      $ Log: $
 */
