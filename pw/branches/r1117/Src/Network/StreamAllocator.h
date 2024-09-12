#ifndef STREAMALLOCATOR_H_D3ADE14F_5D92
#define STREAMALLOCATOR_H_D3ADE14F_5D92

#include "Network.h"
#include "System/TSPool.h"


namespace Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StreamAllocator : public BaseObjectMT, public IStreamAllocator
{
  NI_DECLARE_REFCOUNT_CLASS_2( StreamAllocator, BaseObjectMT, IStreamAllocator )

public:
  StreamAllocator();
  ~StreamAllocator(); 

  virtual CObj<Stream> Allocate();
  virtual void Release( const CObj<Stream> & stream );

private:
  threading::Mutex mutex;
  vector<CObj<Stream> > pool;

  //Statistics
  unsigned  allocated, released, createdNew, reUsed, maxPoolSize;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MockStreamAllocator : public BaseObjectMT, public IStreamAllocator
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockStreamAllocator, BaseObjectMT, IStreamAllocator )

public:
  virtual CObj<Stream> Allocate()
  {
    threading::MutexLock lock( mutex );
    CObj<Stream> result = new MemoryStream;
    streamsInUse.insert( result );
    streamsOld.remove( result );
    return result;
  }
  virtual void Release( const CObj<Stream> & stream )
  {
    threading::MutexLock lock( mutex );
    hash_set<void*>::iterator it = streamsInUse.find( stream );
    NI_ASSERT( it != streamsInUse.end(), "Received stream that is outside of the pool" );

    hash_set<void*>::iterator it2 = streamsOld.find( stream );
    NI_ASSERT( it2 == streamsInUse.end(), "Received stream that is double-released" );

    streamsInUse.erase( it );
    streamsOld.insert( stream );
  }

  MockStreamAllocator() {}

  hash_set<void*> streamsInUse;
  hash_set<void*> streamsOld;
  threading::Mutex mutex;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif //#define STREAMALLOCATOR_H_D3ADE14F_5D92
