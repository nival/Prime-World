#include "stdafx.h"
#include "dummyallocator.h"

//void* operator new( size_t _size, DummyAllocator* _allocator, unsigned int _alignmentSize )
//{
//	size_t oldSize = _allocator->GetSize();
//	_allocator->currentSize += _size;
//	_allocator->Normalize( _alignmentSize );
//	NI_ASSERT( _allocator->currentSize < _allocator->GetCapacity(), "allocator overfull" );
//	void* ptr = &(_allocator->pStorage[oldSize]);
//	return ptr;
//}
//
//void* operator new[]( size_t _size, DummyAllocator* _allocator, unsigned int _alignmentSize )
//{
//	size_t oldSize = _allocator->GetSize();
//	_allocator->currentSize += _size;
//	_allocator->Normalize( _alignmentSize );
//	NI_ASSERT( _allocator->currentSize < _allocator->GetCapacity(), "allocator overfull" );
//	void* ptr = &(_allocator->pStorage[oldSize]);
//	return ptr;
//}

