#include "stdafx.h"
#include "StreamAllocator.h"

#define ENABLE_STREAMS_RECYCLING

//Enable statistic collection
#define COLLECT_ALLOCATOR_STATISTICS( code ) code
//Disable collection
//#define COLLECT_ALLOCATOR_STATISTICS( code )

namespace Network
{

const static int MAX_STREAMS_POOL = 4096;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StreamAllocator::StreamAllocator() :
allocated( 0 ), released( 0 ), createdNew( 0 ), reUsed( 0 ), maxPoolSize( 0 )
{
  pool.reserve( MAX_STREAMS_POOL );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StreamAllocator::~StreamAllocator()
{
  DebugTrace( "StreamAllocator: allocated %u, createdNew %u, maxPoolSize %u", allocated, createdNew, maxPoolSize );
}



#ifdef ENABLE_STREAMS_RECYCLING


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> StreamAllocator::Allocate()
{
  threading::MutexLock lock( mutex );

  COLLECT_ALLOCATOR_STATISTICS( ++allocated );

  if ( pool.empty() )
  {
    COLLECT_ALLOCATOR_STATISTICS( ++createdNew );
    return new MemoryStream;
  }
  else
  {
    COLLECT_ALLOCATOR_STATISTICS( ++reUsed );
    NI_ASSERT( !pool.empty(), "Stream pool is not empty!" );
    CObj<Stream> result = pool.back();
    pool.pop_back();
    return result;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamAllocator::Release( const CObj<Stream> & stream )
{
  threading::MutexLock lock( mutex );

  COLLECT_ALLOCATOR_STATISTICS( ++released );
  COLLECT_ALLOCATOR_STATISTICS( maxPoolSize = Max( maxPoolSize, (unsigned)pool.size() ) );

  //Limit pool size
  if ( pool.size() >= pool.capacity() )
    return;

  stream->SetSize( 0 );
  pool.push_back( stream );
}



#else //ENABLE_STREAMS_RECYCLING



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> StreamAllocator::Allocate()
{
  return new MemoryStream;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamAllocator::Release( const CObj<Stream> & stream )
{
}

#endif //ENABLE_STREAMS_RECYCLING


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

