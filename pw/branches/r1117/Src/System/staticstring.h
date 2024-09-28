#ifndef _STATICSTRING_H_
#define _STATICSTRING_H_

#include "dummyallocator.h"

template<typename T>
class _BaseStaticString
{
	unsigned __int32 offset;
	unsigned __int32 _length;
#ifndef TOOLSET_IS_PRESENT
	_BaseStaticString();
#endif
public:
#ifndef TOOLSET_IS_PRESENT
	~_BaseStaticString() 
	{
		NI_ALWAYS_ASSERT( "don't call me" );
	}
#endif

	typedef const T* const_iterator;

	const_iterator begin() const
	{
		NI_ASSERT( _length, "memory is corrupted" );
		NI_ASSERT( offset, "memory is corrupted" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return pBody;
	}

	const_iterator end() const
	{
		NI_ASSERT( _length, "memory is corrupted" );
		NI_ASSERT( offset, "memory is corrupted" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return pBody + _length;
	}

	const T* c_str() const
	{
		NI_ASSERT( _length, "memory is corrupted" );
		NI_ASSERT( offset, "memory is corrupted" );
		const T* pBody = (T*)((unsigned char*)this + offset);
		return pBody;
	}

	unsigned int length() const
	{
		return _length;
	}


#ifdef TOOLSET_IS_PRESENT
	_BaseStaticString() : offset(0), _length(0)
	{
		NI_STATIC_ASSERT( sizeof(_BaseStaticString) == 8, perhaps_compiler_made_padding );
	}
	~_BaseStaticString()
	{

	}

	unsigned int Construct( const T* pBegin, unsigned int len, DummyAllocator* pAllocator )
	{
		NI_ASSERT( len > 0 && len < 256, "too long or too short string");
		NI_ASSERT(offset == 0, "already constructed");
		_length = len + sizeof(T);
		T* pBody = reinterpret_cast<T*>(pAllocator->Allocate( _length * sizeof(T), 16 ));
		memcpy( pBody, pBegin, len );
		pBody[len] = 0x00;
		offset = unsigned int ( (unsigned char*)pBody - (unsigned char*)this );
		return _length;
	}
#endif
};


typedef _BaseStaticString<char> StaticString;
typedef _BaseStaticString<wchar_t> StaticWString;

#endif

