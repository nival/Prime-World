#include "stdafx.h"
#include "RatingSortMmWorker.h"
#include "System/InlineProfiler.h"

namespace mmaking
{

class RatingSortWorker::WorkerThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( WorkerThread, threading::IThreadJob, BaseObjectMT );
public:
  WorkerThread() :
  eventBusy( true, false ),
  eventComplete( true, false )
  {}

  bool Start( RatingSortJob * newJob ) {
    NI_PROFILE_HEAVY_FUNCTION;

    if ( eventBusy.Wait( 0 ) )
      return false;

    eventComplete.Reset();

    job = newJob;
    eventBusy.Set();
    return true;
  }

  threading::Event & CompleteEvent() { return eventComplete; }

private:
  virtual void Work( volatile bool & isRunning ) {
    NI_PROFILE_THREAD;
    while ( isRunning )
    {
      if ( !eventBusy.Wait( 500 ) )
        continue;

      NI_ASSERT( job, "No job to do" );
      {
        NI_PROFILE_BLOCK( "Job" );
        job->Do();
        job = 0;

        eventBusy.Reset();
        eventComplete.Set();
      }
    }
  }

  threading::Event        eventBusy, eventComplete;
  StrongMT<RatingSortJob> job; //Carefull! 'StrongMT<>' object is protected only by above events
};











RatingSortWorker::RatingSortWorker( unsigned threadsNumber ) :
mode( ModeIdle ),
activeJobNumber( 0 )
{
  workerThreads.resize( threadsNumber );
  threadObjects.resize( threadsNumber );

  for ( size_t i = 0; i < workerThreads.size(); ++i ) {
    workerThreads[i] = new WorkerThread;
    threadObjects[i] = new threading::JobThread( workerThreads[i], "MmWorker", 10000 );
  }

  completeEvents.resize( workerThreads.size() );
  for ( size_t i = 0; i < workerThreads.size(); ++i )
    completeEvents[i] = workerThreads[i]->CompleteEvent().GetHandle();
}



RatingSortWorker::~RatingSortWorker()
{
  workerThreads.clear();

  for ( size_t i = 0; i < threadObjects.size(); ++i )
    threadObjects[i]->AsyncStop();

  threadObjects.clear();
}



void RatingSortWorker::Start()
{
  NI_VERIFY( mode == ModeIdle, "", return );
  mode = ModeWorking;
  activeJobNumber = 0;
}



void RatingSortWorker::AddJob( RatingSortJob * job )
{
  NI_VERIFY( mode == ModeWorking, "", return );
  
  NI_VERIFY( activeJobNumber < workerThreads.size(), "Too many jobs!", return );

  StrongMT<WorkerThread> thread = workerThreads[activeJobNumber];
  bool ok = thread->Start( job );
  ++activeJobNumber;

  NI_ASSERT( ok, "Could not add job!" );
}



bool RatingSortWorker::WaitAll( unsigned timeout )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( mode == ModeWorking || mode == ModeWaiting, "", return false );
  NI_VERIFY( activeJobNumber > 0 && activeJobNumber <= completeEvents.size(), "", return false );
  mode = ModeWaiting;

  DWORD waitResult = WaitForMultipleObjects( activeJobNumber, &completeEvents[0], TRUE, timeout );
  if ( ( waitResult >= WAIT_OBJECT_0 ) && ( waitResult < WAIT_OBJECT_0 + activeJobNumber ) )
  {
    //Job's done
    mode = ModeIdle;
    return true;
  }

  return false;
}

} //namespace mmaking
