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
#if !defined(XALANMEMMGRHELPER_HEADER_GUARD_1357924680)
#define XALANMEMMGRHELPER_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <xalanc/PlatformSupport/PlatformSupportDefinitions.hpp>



#include <xalanc/Include/XalanMemMgrAutoPtr.hpp>




XALAN_CPP_NAMESPACE_BEGIN

template <class Type>
Type*
cloneObjWithMemMgr(const Type& other, MemoryManagerType& theManager)
{

    XalanMemMgrAutoPtr<Type, false> theGuard( theManager , (Type*)theManager.allocate(sizeof(Type)));

    Type* theResult = theGuard.get();

    new (theResult) Type(other, theManager);

    theGuard.release();
    
    return theResult;
}



template <class Type>
Type*
cloneObj(const Type& other, MemoryManagerType& theManager)
{

    XalanMemMgrAutoPtr<Type, false> theGuard( theManager , (Type*)theManager.allocate(sizeof(Type)));

    Type* theResult = theGuard.get();

    new (theResult) Type(other);

    theGuard.release();
    
    return theResult;
}

template <class Type>
class CreateObjFunctor
{
public:
	Type*
	operator()(MemoryManagerType& theManager)
	{
		
		XalanMemMgrAutoPtr<Type, false> theGuard( theManager , (Type*)theManager.allocate(sizeof(Type)));
		
		Type* theResult = theGuard.get();
		
		new (theResult) Type(theManager);
		
		theGuard.release();
		
		return theResult;
	}
};

template <class Type>
void
destroyObjWithMemMgr( Type* ptr, MemoryManagerType& theManager)
{
    if( ptr == 0 )
        return;

    ptr->~Type();

    theManager.deallocate((void*)ptr);
}



XALAN_CPP_NAMESPACE_END



#endif	// if !defined(XALANMEMMGRHELPER_HEADER_GUARD_1357924680)
