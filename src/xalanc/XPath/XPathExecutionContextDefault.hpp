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
 * $ Id: $
 *
 *
 * @author <a href="mailto:david_n_bertoni@lotus.com">David N. Bertoni</a>
 */
#if !defined(XPATHEXECUTIONCONTEXTDEFAULT_HEADER_GUARD_1357924680)
#define XPATHEXECUTIONCONTEXTDEFAULT_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <xalanc/XPath/XPathDefinitions.hpp>



#include <deque>



#include <xalanc/Include/XalanObjectCache.hpp>



#include <xalanc/XalanDOM/XalanDOMString.hpp>



// Base class include file.
#include <xalanc/XPath/XPathExecutionContext.hpp>



#include <xalanc/PlatformSupport/XalanDOMStringCache.hpp>



#include <xalanc/XPath/MutableNodeRefList.hpp>
#include <xalanc/XPath/XalanQNameByValue.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class DOMSupport;
class XPathEnvSupport;
class XalanQName;



/**
 * A basic implementation of the class XPathExecutionContext.
 */
class XALAN_XPATH_EXPORT XPathExecutionContextDefault : public XPathExecutionContext
{
public:

#if defined(XALAN_NO_STD_NAMESPACE)
	typedef deque<XalanNode*>				CurrentNodeStackType;
	typedef deque<const NodeRefListBase*>	ContextNodeListStackType;
#else
	typedef std::deque<XalanNode*>				CurrentNodeStackType;
	typedef std::deque<const NodeRefListBase*>	ContextNodeListStackType;
#endif

	/**
	 * Construct an XPathExecutionContextDefault object
	 *
	 * @param theXPathEnvSupport XPathEnvSupport class instance
	 * @param theDOMSupport		 DOMSupport class instance
	 * @param theXobjectFactory  factory class instance for XObjects
	 * @param theCurrentNode     current node in the source tree
	 * @param theContextNodeList node list for current context
	 * @param thePrefixResolver  pointer to prefix resolver to use
	 */	
	XPathExecutionContextDefault(
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			XObjectFactory&			theXObjectFactory,
			XalanNode*				theCurrentNode = 0,
			const NodeRefListBase*	theContextNodeList = 0,
			const PrefixResolver*	thePrefixResolver = 0);

	/**
	 * Construct an XPathExecutionContextDefault object
	 *
	 * @param theXPathEnvSupport XPathEnvSupport class instance
	 * @param theXObjectFactory  factory class instance for XObjects
	 * @param theCurrentNode     current node in the source tree
	 * @param theContextNodeList node list for current context
	 * @param thePrefixResolver  pointer to prefix resolver to use
	 */
	explicit
	XPathExecutionContextDefault(
			XalanNode*				theCurrentNode = 0,
			const NodeRefListBase*	theContextNodeList = 0,
			const PrefixResolver*	thePrefixResolver = 0);

	virtual
	~XPathExecutionContextDefault();


	/**
	 * Get the XPathEnvSupport instance.
	 *
	 * @return a pointer to the instance.
	 */
	XPathEnvSupport*
	getXPathEnvSupport() const
	{
		return m_xpathEnvSupport;
	}

	/**
	 * Set the XPathEnvSupport instance.
	 *
	 * @param theSupport a reference to the instance to use.
	 */
	void
	setXPathEnvSupport(XPathEnvSupport*		theSupport)
	{
		m_xpathEnvSupport = theSupport;
	}

	/**
	 * Set the DOMSupport instance.
	 *
	 * @param theDOMSupport a reference to the instance to use.
	 */
	void
	setDOMSupport(DOMSupport*	theDOMSupport)
	{
		m_domSupport = theDOMSupport;
	}

	/**
	 * Set the XObjectFactory instance.
	 *
	 * @param theFactory a reference to the instance to use.
	 */
	void
	setXObjectFactory(XObjectFactory*	theXObjectFactory)
	{
		m_xobjectFactory = theXObjectFactory;
	}

	/**
	 * Get a reference to the scratch QNameByValue instance.
	 *
	 * @return A reference to a QNameByValue instance.
	 */
	XalanQNameByValue&
	getScratchQName() const
	{
#if defined(XALAN_NO_MUTABLE)
		return ((XPathExecutionContextDefault*)this)->m_scratchQName;
#else
		return m_scratchQName;
#endif
	}

	// These interfaces are inherited from XPathExecutionContext...

	virtual void
	reset();

	virtual XalanNode*
	getCurrentNode() const;

	virtual void
	pushCurrentNode(XalanNode*		theCurrentNode);

	virtual void
	popCurrentNode();

	virtual bool
	isNodeAfter(
			const XalanNode&	node1,
			const XalanNode&	node2) const;

	virtual void
	pushContextNodeList(const NodeRefListBase&	theList);

	virtual void	
	popContextNodeList();

	virtual const NodeRefListBase&
	getContextNodeList() const;

	virtual size_type
	getContextNodeListLength() const;

	virtual size_type
	getContextNodeListPosition(const XalanNode&		contextNode) const;

	virtual bool
	elementAvailable(const XalanQName&	theQName) const;

	virtual bool
	elementAvailable(
			const XalanDOMString&	theName,
			const LocatorType*		locator) const;

	virtual bool
	functionAvailable(const XalanQName&		theQName) const;

	virtual bool
	functionAvailable(
			const XalanDOMString&	theName,
			const LocatorType*		locator) const;

	virtual const XObjectPtr
	extFunction(
			const XalanDOMString&			theNamespace,
			const XalanDOMString&			functionName,
			XalanNode*						context,
			const XObjectArgVectorType&		argVec,
			const LocatorType*				locator);

	virtual XalanDocument*
	parseXML(
			const XalanDOMString&	urlString,
			const XalanDOMString&	base) const;

	virtual MutableNodeRefList*
	borrowMutableNodeRefList();

	virtual bool
	returnMutableNodeRefList(MutableNodeRefList*	theList);

	virtual MutableNodeRefList*
	createMutableNodeRefList() const;

	virtual XalanDOMString&
	getCachedString();

	virtual bool
	releaseCachedString(XalanDOMString&		theString);

	virtual void
	getNodeSetByKey(
			XalanDocument*			doc,
			const XalanQName&		qname,
			const XalanDOMString&	ref,
			MutableNodeRefList&		nodelist);

	virtual void
	getNodeSetByKey(
			XalanDocument*			doc,
			const XalanDOMString&	name,
			const XalanDOMString&	ref,
			const LocatorType*		locator,
			MutableNodeRefList&		nodelist);

	virtual const XObjectPtr
	getVariable(
			const XalanQName&	name,
			const LocatorType*	locator = 0);

	virtual const PrefixResolver*
	getPrefixResolver() const;

	virtual void
	setPrefixResolver(const PrefixResolver*		thePrefixResolver);

	virtual const XalanDOMString*
	getNamespaceForPrefix(const XalanDOMString&		prefix) const;

	virtual XalanDOMString
	findURIFromDoc(const XalanDocument*		owner) const;

	virtual const XalanDOMString&
	getUnparsedEntityURI(
			const XalanDOMString&		theName,
			const XalanDocument&		theDocument) const;

	virtual bool
	shouldStripSourceNode(const XalanNode&	node);

	virtual XalanDocument*
	getSourceDocument(const XalanDOMString&		theURI) const;

	virtual void
	setSourceDocument(
			const XalanDOMString&	theURI,
			XalanDocument*			theDocument);

	virtual const XalanDecimalFormatSymbols*
	getDecimalFormatSymbols(const XalanQName&	qname);


	// These interfaces are inherited from ExecutionContext...

	virtual void
	error(
			const XalanDOMString&	msg,
			const XalanNode* 		sourceNode = 0,
			const LocatorType* 		locator = 0) const;

	virtual void
	error(
			const char*			msg,
			const XalanNode* 	sourceNode = 0,
			const LocatorType* 	locator = 0) const;

	virtual void
	warn(
			const XalanDOMString&	msg,
			const XalanNode* 		sourceNode = 0,
			const LocatorType* 		locator = 0) const;

	virtual void
	warn(
			const char*			msg,
			const XalanNode* 	sourceNode = 0,
			const LocatorType* 	locator = 0) const;

	virtual void
	message(
			const XalanDOMString&	msg,
			const XalanNode* 		sourceNode = 0,
			const LocatorType* 		locator = 0) const;

	virtual void
	message(
			const char*			msg,
			const XalanNode* 	sourceNode = 0,
			const LocatorType* 	locator = 0) const;

protected:

	typedef XalanObjectCache<MutableNodeRefList, DefaultCacheCreateFunctor<MutableNodeRefList>, DeleteFunctor<MutableNodeRefList>, ClearCacheResetFunctor<MutableNodeRefList> >	NodeListCacheType;

	enum { eNodeListCacheListSize = 50 };

	struct ContextNodeListPositionCache
	{
		ContextNodeListPositionCache() :
			m_node(0),
			m_index(0)
		{
		}

		void
		clear()
		{
			if (m_node != 0)
			{
				m_node = 0;
			}
		}

		const XalanNode*	m_node;

		size_type			m_index;
	};

	XPathEnvSupport*						m_xpathEnvSupport;

	DOMSupport*								m_domSupport;

	CurrentNodeStackType					m_currentNodeStack;

	ContextNodeListStackType				m_contextNodeListStack;

	const PrefixResolver*					m_prefixResolver;

	XalanDOMString							m_currentPattern;

	NodeListCacheType						m_nodeListCache;

	XalanDOMStringCache						m_stringCache;

	mutable ContextNodeListPositionCache	m_cachedPosition;

	mutable XalanQNameByValue				m_scratchQName;

	static const NodeRefList	s_dummyList;
};



XALAN_CPP_NAMESPACE_END



#endif	// XPATHEXECUTIONCONTEXTDEFAULT_HEADER_GUARD_1357924680
