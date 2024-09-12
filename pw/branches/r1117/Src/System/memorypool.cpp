#include "stdafx.h"
#include "memorypool.h"
#if defined( NV_LINUX_PLATFORM )
#include <stdlib.h>
#include <malloc.h>
#endif


void MemoryBlock::Release()
{
	Clear();
#if defined( NV_WIN_PLATFORM )
	Aligned_Free( pData );
#elif defined( NV_LINUX_PLATFORM )
  ::free( pData );
#endif
	pData = 0;
	size = 0;
}

void MemoryBlock::Initialize( unsigned int memoryBlockSize )
{
	size = memoryBlockSize;
#if defined( NV_WIN_PLATFORM )
	pData = static_cast<unsigned char*>(Aligned_MAlloc( memoryBlockSize, 512 ));
#elif defined( NV_LINUX_PLATFORM )
  pData = 0;
  void * ptr = 0;
  if ( ::posix_memalign( &ptr, 512, memoryBlockSize ) == 0 )
  {
    pData = static_cast<unsigned char*>( ptr );
  }
#endif
	NI_ASSERT( pData, "cant allocate memory" );
}

void MemoryBlock::Clear()
{
	payload = 0;
}

void* MemoryBlock::Allocate( unsigned int size )
{
	unsigned int oldPayload = payload;
	payload += size;
	Normalize();
	return pData + oldPayload;
}

void MemoryBlock::Normalize( unsigned int _alignmentSize /*= 512 */ )
{
	NI_ASSERT( (_alignmentSize >= 4) && !((_alignmentSize-1)&_alignmentSize), "alignment is NOT the power of two" );
	payload += _alignmentSize - payload & (_alignmentSize-1);
}

void MemoryPool::AllocateNewBlock( unsigned int blockSize )
{
  systemLog( NLogg::LEVEL_DEBUG ) << "MemoryPool: " << poolName.c_str() << "; allocated size: " << GetAllocatedSize() << "; payload: " << GetPayload() << endl;

  memoryBlocks.push_back();
  memoryBlocks.back().Initialize( blockSize );

	systemLog( NLogg::LEVEL_DEBUG ) << "MemoryPool: " << poolName.c_str() << "; new allocated size: " << GetAllocatedSize() << endl;
}

void* MemoryPool::AllocateMemory( unsigned int size, const nstl::string& fileName )
{
	stats[fileName] = size;

  MemoryBlocks::iterator it = memoryBlocks.begin();
  MemoryBlocks::iterator last = memoryBlocks.end();

	for ( ; it != last; ++it )
	{
		if ( it->GetLeftover() > size )
			return it->Allocate(size);
	}

  if ( size < MEMORY_BLOCK_SIZE )
  {
    AllocateNewBlock( MEMORY_BLOCK_SIZE );
  }
  else
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("resource is too huge! %d < %d", size, MEMORY_BLOCK_SIZE) );
    AllocateNewBlock( size );
  }

	return memoryBlocks.back().Allocate( size );
}

unsigned int MemoryPool::GetAllocatedSize() const
{
	unsigned int allocatedSize = 0;

  MemoryBlocks::const_iterator it = memoryBlocks.begin();
  MemoryBlocks::const_iterator last = memoryBlocks.end();

  for ( ; it != last; ++it )
  {
    allocatedSize += it->GetSize();
  }

	return allocatedSize;
}

void MemoryPool::ReleaseEmptyBlocks()
{
  MemoryBlocks::iterator it = memoryBlocks.begin();
  MemoryBlocks::iterator last = memoryBlocks.end();

  for ( ; it != last; ++it )
  {
		if ( it->IsEmpty() )
			it->Release();
	}
}

void MemoryPool::Clear()
{
  MemoryBlocks::iterator it = memoryBlocks.begin();
  MemoryBlocks::iterator last = memoryBlocks.end();

  for ( ; it != last; ++it )
  {
		it->Clear();
  }

	currentBlockCount = 0;

	stats.clear();
}

void MemoryPool::Release()
{
  MemoryBlocks::iterator it = memoryBlocks.begin();
  MemoryBlocks::iterator last = memoryBlocks.end();

  for ( ; it != last; ++it )
  {
    it->Release();
  }

	currentBlockCount = 0;
}

unsigned int MemoryPool::GetPayload() const
{
  MemoryBlocks::const_iterator it = memoryBlocks.begin();
  MemoryBlocks::const_iterator last = memoryBlocks.end();

	unsigned int payload = 0;

  for ( ; it != last; ++it )
  {
    payload += it->GetPayload();
  }

	return payload;
}

