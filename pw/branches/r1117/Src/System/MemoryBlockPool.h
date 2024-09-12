#pragma once

#include "DefaultTypes.h"
#include "noncopyable.h"

namespace memory
{

class MemoryBlock
{
  friend class MemoryBlockPool;

public:
  MemoryBlock() : _size( 0 ), _buffer( 0 ), _subpoolIndex( -1 ) {}

  MemoryBlock( size_t size, byte * buffer, int subpoolIndex ) :
  _size( size ),
  _buffer( buffer ),
  _subpoolIndex( subpoolIndex )
  {}

  ~MemoryBlock() {
    /*Do Nothing*/ }

  size_t size() const { return _size; }

  byte * buffer() const { return _buffer; }

private:
  size_t  _size;
  byte *  _buffer;
  int     _subpoolIndex; //Needed for fast indexing; 0 for extra-large blocks
};



class MemoryBlockPool : public NonCopyable
{
public:
  MemoryBlockPool( int subPoolsCount, int reserveBlocks, size_t baseSize = 32, size_t sizeGrowAdd = 0, size_t sizeGrowPercent = 200 );
  ~MemoryBlockPool();

  void AllocBlock( MemoryBlock & block, size_t size );
  void FreeBlock( MemoryBlock & block );

  void AllowClearMemoryBlocks( bool clear ) { _clearMemory = clear; }
  void SetPooledBlocksLimit( size_t limit ) { _pooledBlocksLimit = limit; }

  size_t AllocatedBlocks() const { return _allocatedBlocks; }
  size_t AllocatedMemory() const { return _allocatedMemory; }
  size_t PooledBlocks() const { return _pooledBlocks; }
  size_t PooledMemory() const { return _pooledMemory; }

private:
  struct SSubPool {
    size_t                    blockSize;
    vector<MemoryBlock>       blocks;
    size_t                    allocatedBlocks;
    size_t                    allocatedMemory;
    size_t                    pooledMemory;

    SSubPool() : blockSize( 0 ), allocatedBlocks( 0 ), allocatedMemory( 0 ), pooledMemory( 0 ) {}
  };

  const size_t            _baseSize, _sizeGrowAdd, _sizeGrowPercent;
  bool                    _clearMemory;
  size_t                  _pooledBlocksLimit;
  vector<SSubPool>        _subPools;
  size_t                  _allocatedBlocks;
  size_t                  _allocatedMemory;
  size_t                  _pooledBlocks;
  size_t                  _pooledMemory;

  void _AllocateBlock( MemoryBlock & block, size_t size, int subpoolIndex );
  void _FreeBlock( MemoryBlock & block );
  void _FinishBlockAllocation( MemoryBlock & block );
};

} //namespace memory
