#pragma once

class DummyAllocator
{
	unsigned int currentSize;
	const unsigned int storageCapacity;
	unsigned char* pStorage;
	//friend void* operator new( size_t _size, DummyAllocator* _allocator, unsigned int _alignmentSize );
	//friend void* operator new[]( size_t _size, DummyAllocator* _allocator, unsigned int _alignmentSize );
	
	DummyAllocator& operator=(const DummyAllocator&);
public:
	void Normalize( unsigned int _alignmentSize = 4 )
	{
		NI_ASSERT( (_alignmentSize >= 4) && !((_alignmentSize-1)&_alignmentSize), "alignment is NOT the power of two" );
		currentSize += _alignmentSize - currentSize & (_alignmentSize-1);
	}
	DummyAllocator( unsigned int _storageCapacity ) : storageCapacity(_storageCapacity), currentSize(0), pStorage(0) 
	{
		pStorage = static_cast<unsigned char*>( Aligned_MAlloc( storageCapacity, 16 ) );
		memset(pStorage, 0, storageCapacity);
	}
	~DummyAllocator()
	{
		Aligned_Free(pStorage);
	}
	void* Allocate(unsigned int _size, unsigned int _alignmentSize )
	{
		unsigned int oldSize = currentSize;
		currentSize += _size;
		Normalize( _alignmentSize );
		NI_ASSERT( currentSize < storageCapacity, "allocator overfull" );
		void* ptr = &(pStorage[oldSize]);
		return ptr;
	}
	void Clear()
	{
		ASSERT(pStorage);
		currentSize = 0;
	}
	const void* GetData() const { return pStorage; }
	unsigned int GetSize() const { return currentSize; }
	unsigned int GetCapacity() const { return storageCapacity; }
	
};

//void* operator new( size_t _size, DummyAllocator* _allocator, unsigned int _alignmentSize );
//
//
//void* operator new[]( size_t _size, DummyAllocator* _allocator, unsigned int _alignmentSize );
