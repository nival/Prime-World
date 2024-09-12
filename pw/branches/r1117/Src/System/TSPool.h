#ifndef TSPOOL_H_41422944_435E_4140_ACAE
#define TSPOOL_H_41422944_435E_4140_ACAE

#include "nchunked_list.h"
#include "Thread.h"
#include "TSList.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TStore, class TRet = TStore>
class TSPool
{
public:
  TSPool() : freeQueue( 4096 ) {}
  ~TSPool() 
  {
    typename chunked_list<TStore>::iterator it = allocated.begin();
    for( ; it; ++it )
    {
      TStore& s = *it;
      NI_ASSERT( s.GetObjCount() == 1, "Stream has unreleased CObjs" );
      NI_ASSERT( s.GetRefCount() == 0, "Stream has unreleased CPtrs" );
    }
  }
  TRet* Alloc() 
  { 
    TRet* pS = 0;
    allocateLock.Lock();

    if ( !freeQueue.Dequeue( pS ) )
    {
      pS = &allocated.add();
#ifdef TRACK_COBJECTS_POINTERS
			CObjectBase::SObjCounter::TrackRef( pS, this, true );
#endif
      CObjectBase::SObjCounter::AddRef( pS );
    }
    allocateLock.Unlock();
    return pS;
  }

  void Release( TRet* pS ) 
  {
    releaseLock.Lock();
    freeQueue.Enqueue( pS );
    releaseLock.Unlock();
  }
private:
  threading::Mutex allocateLock;
  threading::Mutex releaseLock;
  chunked_list<TStore> allocated;
  SPSCQueue<TRet*> freeQueue;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //#define TSPOOL_H_41422944_435E_4140_ACAE
