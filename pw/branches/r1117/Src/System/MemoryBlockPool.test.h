//!Component('System/MemoryBlockPool')
//!Component('System/InlineProfiler')
//!Component('System/Random')
#include "stdafx.h"

#include "MemoryBlockPool.h"
#include "RandomGenerator.h"
#include <vector>
#include "cxxtest/TestSuite.h"

class Test_MemoryBlockPool :  public CxxTest::TestSuite
{
public:
  
  void test_smoke()
  {
    memory::MemoryBlockPool pool( 4, 16, 32 );
    pool.AllowClearMemoryBlocks( true );

    memory::MemoryBlock block;
    pool.AllocBlock( block, 50 );

    TS_ASSERT( block.size() == 64 );
    TS_ASSERT( block.buffer() );
    for ( size_t i = 0; i < block.size(); ++i )
      TS_ASSERT( block.buffer()[i] == 0 );

    TS_ASSERT( pool.AllocatedBlocks() == 1 );
    TS_ASSERT( pool.AllocatedMemory() == 64 );

    pool.FreeBlock( block );

    TS_ASSERT( pool.AllocatedBlocks() == 0 );
    TS_ASSERT( pool.AllocatedMemory() == 0 );
    TS_ASSERT( pool.PooledBlocks() == 1 );
    TS_ASSERT( pool.PooledMemory() == 64 );
  }


  void test_reuse()
  {
    memory::MemoryBlockPool pool( 4, 16, 32 );
    pool.AllowClearMemoryBlocks( false );

    memory::MemoryBlock block;

    pool.AllocBlock( block, 50 );
    TS_ASSERT( block.size() == 64 );
    TS_ASSERT( block.buffer() );

    const char * text = "Test text";
    memcpy( block.buffer(), text, strlen( text ) + 1 );
    pool.FreeBlock( block );

    pool.AllocBlock( block, 55 );
    TS_ASSERT( block.size() == 64 );
    TS_ASSERT( block.buffer() );
    TS_ASSERT( memcmp( block.buffer(), text, strlen( text ) + 1 ) == 0 );
    pool.FreeBlock( block );
  }


  void test_additive_grow()
  {
    memory::MemoryBlockPool pool( 10, 16, 1000, 1000, 100 );

    memory::MemoryBlock block1;
    pool.AllocBlock( block1, 100 );
    TS_ASSERT( block1.size() == 1000 );
    TS_ASSERT( block1.buffer() );

    memory::MemoryBlock block2;
    pool.AllocBlock( block2, 4500 );
    TS_ASSERT( block2.size() == 5000 );
    TS_ASSERT( block2.buffer() );

    pool.FreeBlock( block2 );
    pool.FreeBlock( block1 );
  }


  void test_out_of_bounds()
  {
    memory::MemoryBlockPool pool( 4, 16, 256 );

    memory::MemoryBlock block;
    pool.AllocBlock( block, 3000 );

    TS_ASSERT( block.size() == 3000 );
    TS_ASSERT( block.buffer() );

    pool.FreeBlock( block );
  }


  void test_smoke_many()
  {
    memory::MemoryBlockPool pool( 4, 16, 64 );

    memory::MemoryBlock block1;
    pool.AllocBlock( block1, 1 );
    TS_ASSERT( block1.size() == 64 );
    TS_ASSERT( block1.buffer() );

    memory::MemoryBlock block2;
    pool.AllocBlock( block2, 400 );
    TS_ASSERT( block2.size() == 512 );
    TS_ASSERT( block2.buffer() );

    memory::MemoryBlock block3;
    pool.AllocBlock( block3, 100 );
    TS_ASSERT( block3.size() == 128 );
    TS_ASSERT( block3.buffer() );

    pool.FreeBlock( block2 );
    pool.FreeBlock( block1 );

    memory::MemoryBlock block4;
    pool.AllocBlock( block4, 200 );
    TS_ASSERT( block4.size() == 256 );
    TS_ASSERT( block4.buffer() );

    pool.FreeBlock( block3 );
    pool.FreeBlock( block4 );
  }


  void test_pool_limit()
  {
    memory::MemoryBlockPool pool( 4, 64, 32 );
    pool.SetPooledBlocksLimit( 32 );

    std::vector<memory::MemoryBlock> blocks100;
    for ( int i = 0; i < 50; ++i ) {
      memory::MemoryBlock block;
      pool.AllocBlock( block, 100 );
      blocks100.push_back( block );
    }

    TS_ASSERT( pool.PooledBlocks() == 0 );
    TS_ASSERT( pool.PooledMemory() == 0 );
    TS_ASSERT( pool.AllocatedBlocks() == 50 );
    TS_ASSERT( pool.AllocatedMemory() == 128 * 50 );

    for ( int i = 0; i < (int)blocks100.size(); ++i )
      pool.FreeBlock( blocks100[i] );
    blocks100.clear();

    TS_ASSERT( pool.PooledBlocks() == 32 );
    TS_ASSERT( pool.PooledMemory() == 32 * 128 );
    TS_ASSERT( pool.AllocatedBlocks() == 0 );
    TS_ASSERT( pool.AllocatedMemory() == 0 );

    std::vector<memory::MemoryBlock> blocks200;
    for ( int i = 0; i < 77; ++i ) {
      memory::MemoryBlock block;
      pool.AllocBlock( block, 200 );
      blocks200.push_back( block );
    }

    TS_ASSERT( pool.PooledBlocks() == 32 );
    TS_ASSERT( pool.PooledMemory() == 32 * 128 );
    TS_ASSERT( pool.AllocatedBlocks() == 77 );
    TS_ASSERT( pool.AllocatedMemory() == 256 * 77 );

    for ( int i = 0; i < (int)blocks200.size(); ++i )
      pool.FreeBlock( blocks200[i] );
    blocks200.clear();

    TS_ASSERT( pool.PooledBlocks() == 32 + 32 );
    TS_ASSERT( pool.PooledMemory() == 32 * 128 + 256 * 32 );
    TS_ASSERT( pool.AllocatedBlocks() == 0 );
    TS_ASSERT( pool.AllocatedMemory() == 0 );
  }


  void test_random()
  {
    memory::MemoryBlockPool pool( 5, 16, 128 );
    pool.SetPooledBlocksLimit( 0 );

    std::vector<memory::MemoryBlock> blocks;
    blocks.reserve( 1000 );

    NRandom::RandomGenerator rnd( 10 );

    for ( int i = 0; i < 10000; ++i ) {
      //something like normal distribution from 5 to 2000 with expected value 1000
      int size = 0;
      for ( int j = 0; j < 5; ++j )
        size += rnd.Next( 1, 400 );

      memory::MemoryBlock block;
      pool.AllocBlock( block, size );

      for ( int k = 0; k < size; ++k )
        block.buffer()[k] = k & 0xff;

      blocks.push_back( block );

      //remove every 10th block
      if ( ( i % 10 ) == 0 ) {
        int idx = rnd.Next( 0, blocks.size() - 1 );
        pool.FreeBlock( blocks[idx] );
        blocks.erase( blocks.begin() + idx );
      }
    }

    TS_ASSERT( pool.AllocatedBlocks() == 9000 );

    size_t allocated = pool.AllocatedMemory();

    for ( size_t i = 0; i < blocks.size(); ++i )
      pool.FreeBlock( blocks[i] );

    TS_ASSERT( pool.AllocatedBlocks() == 0 );
    TS_ASSERT( pool.AllocatedMemory() == 0 );
    TS_ASSERT( pool.PooledBlocks() == 9000 );
    TS_ASSERT( pool.PooledMemory() == allocated );
  }
};
