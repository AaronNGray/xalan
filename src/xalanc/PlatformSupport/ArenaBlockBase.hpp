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

#if !defined(ARENABLOCKBASE_INCLUDE_GUARD_1357924680)
#define ARENABLOCKBASE_INCLUDE_GUARD_1357924680


#include <cassert>
#include <set>
#include <memory>



#if defined(XALAN_NO_STD_ALLOCATORS) && !defined(XALAN_NO_SELECTIVE_TEMPLATE_INSTANTIATION)
#include <xalanc/PlatformSupport/XalanAllocator.hpp>
#endif


XALAN_CPP_NAMESPACE_BEGIN


#if defined(XALAN_NO_SELECTIVE_TEMPLATE_INSTANTIATION)

template <class Type>
class ArenaBlockAllocator
{
public:

	typedef typename T		size_type;
	typedef ptrdiff_t		difference_type;
	typedef Type*			pointer;
	typedef const Type*		const_pointer;
	typedef Type&			reference;
	typedef const Type&		const_reference;
	typedef Type			value_type;

	ArenaBlockAllocator()
	{
	}

	ArenaBlockAllocator(const ArenaBlockAllocator<Type>&)
	{
	};

	~ArenaBlockAllocator()
	{
	}

	pointer
	allocate(
			size_type		size,
			const void*		/* hint */ = 0)
	{
		return (pointer)operator new(size * sizeof(Type));
	}

	void
	deallocate(
				pointer		p,
				size_type	/* n */)
	{
		operator delete(p);
	}
};
#endif


template<class ObjectType,
#if defined(XALAN_NO_DEFAULT_TEMPLATE_ARGUMENTS)
		 class size_Type>
#else
		 class size_Type  = size_t >
#endif
class ArenaBlockBase
{
public:

#if defined(XALAN_NO_SELECTIVE_TEMPLATE_INSTANTIATION)
	typedef ArenaBlockAllocator<ObjectType>		AllocatorType;
#elif defined(XALAN_NO_STD_ALLOCATORS)
	typedef XalanAllocator<ObjectType>			AllocatorType;
#else
	typedef std::allocator<ObjectType>			AllocatorType;
#endif

	typedef size_Type							size_type;

	ArenaBlockBase(size_type	theBlockSize) :	
		m_allocator(),
		m_objectCount(0),
		m_blockSize(theBlockSize),
#if defined(XALAN_NEW_STD_ALLOCATOR)
		m_objectBlock(m_allocator.allocate(m_blockSize))
#else
		m_objectBlock(m_allocator.allocate(m_blockSize, 0))
#endif
	{
		assert(theBlockSize > 0);

		assert(m_objectBlock != 0);
	}

	~ArenaBlockBase()
	{
		// Release the memory...
		m_allocator.deallocate(m_objectBlock, m_blockSize);

	}
	/*
	 * Find out if there is a block available.
	 *
	 * @return true if one is available, false if not.
	 */
	bool
	blockAvailable() const
	{
		return m_objectCount < m_blockSize ? true : false;
	}


	/*
	 * Find out if there are any block is allocated
	 *
	 * @return true if one is available, false if not.
	 */
	bool
	isEmpty() const
	{
		return m_objectCount == 0 ? true : false;
	}

	/*
	 * Get the number of objects currently allocated in the
	 * block.
	 *
	 * @return The number of objects allocated.
	 */
	size_type
	getCountAllocated() const
	{
		return m_objectCount;
	}

	/*
	 * Get the block size, that is, the number
	 * of objects in each block.
	 *
	 * @return The size of the block
	 */
	size_type
	getBlockSize() const
	{
		return m_blockSize;
	}


	/*
	 * Determine if this block owns the specified object block.
	 * Note that, unlike ownsObject(), there does not need to
	 * be an object at the address.
	 *
	 * @param theObject the address of the object
	 * @return true if we own the object block, false if not.
	 */
	bool
	ownsBlock(const ObjectType*		theObject) const
	{
		return isInBorders(theObject, m_blockSize);
	}

protected:
	/*
	 * Determine if this block is located between beginning of the array
	 * and the "rightBorder" array member (not included)
	 * @param theObject the address of the object
	 *		  rightBorder the right 
	 * @return true if we own the object block, false if not.
	 */
	bool
	isInBorders( const ObjectType*	theObject, size_type rightBoundary) const
	{
		if ( rightBoundary > m_blockSize )
		{
			rightBoundary = m_blockSize;
		}
		// Use less<>, since it's guaranteed to do pointer
		// comparisons correctly...
		XALAN_STD_QUALIFIER less<const ObjectType*>		functor;

		if (functor(theObject, m_objectBlock) == false &&
			functor(theObject, m_objectBlock + rightBoundary) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
	 * Determine the offset into the block for the given address.
	 * Behavior is undefined if the address is not within our
	 * block
	 *
	 * @param theObject the address of the object
	 * @return the offset
	 */
	size_type
	getBlockOffset(const ObjectType*	theObject) const
	{
		assert(size_type( (theObject - m_objectBlock) / sizeof(ObjectType) ) < m_blockSize);

		return theObject - m_objectBlock;
	}

	/*
	 * Determine the address within our block of the object
	 * at the specified offset.
	 * Behavior is undefined if the offset is greater than the
	 * block size.
	 *
	 * @param theObject the address of the object
	 * @return the offset
	 */
	ObjectType*
	getBlockAddress(size_type	theOffset) const
	{
		assert(theOffset < m_blockSize);

		return m_objectBlock + theOffset;
	}

	// data members...
	AllocatorType		m_allocator;
	
	size_type			m_objectCount;

	const size_type		m_blockSize;

	ObjectType*			m_objectBlock;



private:

	// Not implemented...
	ArenaBlockBase(const ArenaBlockBase<ObjectType>&);

	ArenaBlockBase<ObjectType>&
	operator=(const ArenaBlockBase<ObjectType>&);

	bool
	operator==(const ArenaBlockBase<ObjectType>&) const;


};

XALAN_CPP_NAMESPACE_END



#endif	// !defined(ARENABLOCKBASE_INCLUDE_GUARD_1357924680)
