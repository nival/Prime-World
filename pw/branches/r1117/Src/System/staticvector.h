#ifndef _STATICVECTOR_H_
#define _STATICVECTOR_H_

#include "dummyallocator.h"

// in-game allowed only constant methods
template< typename T > 
class StaticVector
{
	unsigned __int32 count;
	unsigned __int32 offset;

#ifndef TOOLSET_IS_PRESENT
	StaticVector();
#endif

public:
#ifndef TOOLSET_IS_PRESENT
	~StaticVector() 
	{
		//NI_ALWAYS_ASSERT( "don't call me" );
	}
#endif

	typedef const T* const_iterator;

	const unsigned int size() const
	{
		return count;
	}
  
  // doesn't work for nested StaticVectors
  const unsigned int getMemorySize() const
  {
    // BEWARE! Totally useless method! Usually alignment is applied in allocator! [12/1/2010 paul.smirnov]
    return offset + count * sizeof(T);
  }

	__forceinline const T& operator[]( unsigned int i ) const
	{
		//NI_ASSERT( count, "memory is corrupted" );
		//NI_ASSERT( offset, "memory is corrupted" );
		//NI_ASSERT( i < count, "bad index" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return pBody[i];
	}

	__forceinline const_iterator begin() const
	{
		//NI_ASSERT( count, "memory is corrupted" );
		//NI_ASSERT( offset, "memory is corrupted" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return pBody;
	}

	const_iterator end() const
	{
		//NI_ASSERT( count, "memory is corrupted" );
		//NI_ASSERT( offset, "memory is corrupted" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return pBody + count;
	}

	__forceinline const_iterator at( unsigned int i ) const
	{
		//NI_ASSERT( count, "memory is corrupted" );
		//NI_ASSERT( offset, "memory is corrupted" );
		//NI_ASSERT( i < count, "bad index" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return &pBody[i];
	}

//////////////////////////////////////////////////////////////////////////
// non constant methods to use in exporters
#ifdef TOOLSET_IS_PRESENT
	StaticVector() : offset( 0 ), count ( 0 ) 
	{
		//NI_STATIC_ASSERT( sizeof(StaticVector) == 8, perhaps_compiler_made_padding );
	}

	T& operator[]( unsigned int i ) 
	{
		//NI_ASSERT( i < count, "bad index" );
		T* pBody = (T*)((unsigned char*)this + offset);
		return pBody[i];
	}

	void resize( unsigned int _size, DummyAllocator* pAllocator )
	{
		//NI_ASSERT( _size > 0, "size should be positive" );
		count = _size;
		//NI_ASSERT( offset == 0, "static vector already resized" );
		//const T* pBody = new(_allocator, 16) T[_size];
		const T* pBody = reinterpret_cast<const T*>(pAllocator->Allocate( _size * sizeof(T), 16 ));
		offset = unsigned int ( (unsigned char*)pBody - (unsigned char*)this );
	}
#endif//#ifdef TOOLSET_IS_PRESENT
//////////////////////////////////////////////////////////////////////////

};//class StaticVector

#endif 		// _STATICVECTOR_H_

