#include "stdafx.h"

#include "MemoryBlockPool.h"

namespace memory
{

MemoryBlockPool::MemoryBlockPool( int subPoolsCount, int reserveBlocks, size_t baseSize, size_t sizeGrowAdd, size_t sizeGrowPercent ) :
_baseSize( baseSize ), _sizeGrowAdd( sizeGrowAdd ), _sizeGrowPercent( sizeGrowPercent ),
_clearMemory( true ),
_pooledBlocksLimit( 256 ),
_allocatedBlocks( 0 ), _allocatedMemory( 0 ),
_pooledBlocks( 0 ), _pooledMemory( 0 )
{
  _subPools.resize( (size_t)subPoolsCount );

  size_t blockSize = _baseSize;
  for ( int i = 0; i < subPoolsCount; ++i ) {
    _subPools[i].blockSize = blockSize;
    blockSize = ( (QWORD)( blockSize + sizeGrowAdd ) * (QWORD)sizeGrowPercent ) / (QWORD)100;

    _subPools[i].blocks.reserve( reserveBlocks );
  }
}



MemoryBlockPool::~MemoryBlockPool()
{
  //This module used by logging system itself,
  //we cannot use NI_ASSERT here.
  assert( _allocatedBlocks == 0 );
  assert( _allocatedMemory == 0 );

  for ( size_t i = 0; i < (size_t)_subPools.size(); ++i )
  {
    for ( size_t j = 0; j < (size_t)_subPools[i].blocks.size(); ++j )
      _FreeBlock( _subPools[i].blocks[j] );

    _subPools[i].blocks.clear();
  }
  _subPools.clear();
}



void MemoryBlockPool::AllocBlock( MemoryBlock & block, size_t size )
{
  assert( block._subpoolIndex == -1 );
  assert( !block._size );
  assert( !block._buffer );

  for ( int i = 0; i < (int)_subPools.size(); ++i )
  {
    SSubPool & subpool = _subPools[i];
    if ( subpool.blockSize >= size )
    {
      if ( !subpool.blocks.empty() )
      {
        block = subpool.blocks.back();
        subpool.blocks.pop_back();

        assert( _pooledBlocks > 0 );
        assert( _pooledMemory >= block._size );
        --_pooledBlocks;
        _pooledMemory -= block._size;
        subpool.pooledMemory -= block._size;
      }
      else
        _AllocateBlock( block, subpool.blockSize, i );

      ++subpool.allocatedBlocks;
      subpool.allocatedMemory += block._size;

      _FinishBlockAllocation( block );
      return;
    }
  }

  //requested size is too big for our pool, use heap
  _AllocateBlock( block, size, -1 );
  _FinishBlockAllocation( block );
}



void MemoryBlockPool::FreeBlock( MemoryBlock & block )
{
  assert( block._size );
  assert( block._buffer );

  --_allocatedBlocks;
  _allocatedMemory -= block._size;

  if ( block._subpoolIndex < 0 ) {
    _FreeBlock( block );
  }
  else
  {
    NI_VERIFY( block._subpoolIndex < (int)_subPools.size(), "", return );
    SSubPool & subpool = _subPools[block._subpoolIndex];

    if ( _pooledBlocksLimit && ( (size_t)subpool.blocks.size() >= _pooledBlocksLimit ) )
    {
      _FreeBlock( block );
    }
    else
    {
      subpool.blocks.push_back( block );
      subpool.pooledMemory += block._size;

      ++_pooledBlocks;
      _pooledMemory += block._size;
    }

    --subpool.allocatedBlocks;
    subpool.allocatedMemory -= block._size;
  }

  block = MemoryBlock();
}



void MemoryBlockPool::_AllocateBlock( MemoryBlock & block, size_t size, int subpoolIndex )
{
  block = MemoryBlock( size, new byte[size], subpoolIndex );
}



void MemoryBlockPool::_FreeBlock( MemoryBlock & block )
{
  assert( block._buffer );
  delete[] block._buffer;
  block._buffer = 0;
}



void MemoryBlockPool::_FinishBlockAllocation( MemoryBlock & block )
{
  ++_allocatedBlocks;
  _allocatedMemory += block._size;

  if ( _clearMemory )
    memset( block._buffer, 0, block._size );
}

} //namespace memory
