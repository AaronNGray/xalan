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
#include "FunctionNodeSet.hpp"



#include <xalanc/PlatformSupport/XalanMessageLoader.hpp>



#include <xalanc/XPath/XNodeSetBase.hpp>
#include <xalanc/XPath/XObjectFactory.hpp>
#include <xalanc/XPath/XalanDocumentFragmentNodeRefListBaseProxy.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XalanDocumentFragmentXNodeSetBaseProxy : public XNodeSetBase
{
public:

	XalanDocumentFragmentXNodeSetBaseProxy(
                MemoryManagerType&  theManager,
                const XObjectPtr&	theXObject) :
		XNodeSetBase(theManager),
		m_xobject(theXObject),
		m_proxy(theXObject->rtree())
	{
	}

    static XalanDocumentFragmentXNodeSetBaseProxy*
    create(
            MemoryManagerType&  theManager,
            const XObjectPtr&	theXObject)
    {
        XalanDocumentFragmentXNodeSetBaseProxy*     theResult;

        return XalanConstruct(theManager, theResult, theManager, theXObject);
    }

	XalanDocumentFragmentXNodeSetBaseProxy(
                MemoryManagerType&                              theManager,
                const XalanDocumentFragmentXNodeSetBaseProxy&	theSource) :
		XNodeSetBase(theSource, theManager),
		m_xobject(theSource.m_xobject),
		m_proxy(theSource.m_proxy)
	{
	}

	virtual
	~XalanDocumentFragmentXNodeSetBaseProxy()
	{
	}


	virtual const NodeRefListBase&
	nodeset() const
	{
		return m_proxy;
	}

	virtual void
	dereferenced()
	{
		delete this;
	}

	virtual XalanNode*
	item(size_type	index) const
	{
		return m_proxy.item(index);
	}

	virtual size_type
	getLength() const
	{
		return m_proxy.getLength();
	}

private:

	const XObjectPtr									m_xobject;

	const XalanDocumentFragmentNodeRefListBaseProxy		m_proxy;
};



FunctionNodeSet::FunctionNodeSet(bool	convertString) :
	m_convertString(convertString)
{
}



FunctionNodeSet::~FunctionNodeSet()
{
}



XObjectPtr
FunctionNodeSet::execute(
			XPathExecutionContext&			executionContext,
			XalanNode*						context,
			const XObjectArgVectorType&		args,
			const LocatorType*				locator) const
{
	if (args.size() != 1)
	{
        XalanDOMString  theError(executionContext.getMemoryManager());

		executionContext.error(getError(theError), context, locator);
	}

	assert(args[0].null() == false);

	const XObject::eObjectType	theType = args[0]->getType();

	if (theType == XObject::eTypeResultTreeFrag ||
		(theType == XObject::eTypeString && m_convertString == true))
	{
        return XObjectPtr(
                    XalanDocumentFragmentXNodeSetBaseProxy::create(
                        executionContext.getMemoryManager(),
                        args[0]));
	}
	else
	{
        const XPathExecutionContext::GetAndReleaseCachedString  theGuard(executionContext);

        XalanDOMString&     theMessage = theGuard.get();

		executionContext.warn(
			getInvalidArgumentTypeError(theMessage),
			context,
			locator);

		return args[0];
	}
}



#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
Function*
#else
FunctionNodeSet*
#endif
FunctionNodeSet::clone(MemoryManagerType&   theManager) const
{
    return XalanCopyConstruct(theManager, *this);
}



const XalanDOMString&
FunctionNodeSet::getError(XalanDOMString&   theResult) const
{
    return XalanMessageLoader::getMessage(
                XalanMessages::FunctionAcceptsOneArgument_1Param,
                theResult,
                "nodeset");
}



const XalanDOMString&
FunctionNodeSet::getInvalidArgumentTypeError(XalanDOMString&    theResult) const
{
	return XalanMessageLoader::getMessage(
                XalanMessages::InvalidArgumentTypeFunction_1Param,
                theResult,
                "nodeset");
}



XALAN_CPP_NAMESPACE_END
