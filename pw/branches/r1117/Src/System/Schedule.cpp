#include "stdafx.h"
#include "Schedule.h"
#include "sleep.h"
#include <vector>
#include <map>
#include <list>


class Schedule::Worker : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Worker, threading::IThreadJob, BaseObjectMT );
public:
  const static size_t ReserveSize = 64;
  const static size_t EventsBufferLimit = 1024 * 64;

  Worker() :
  scheduleSequence( 0 )
  {
    incoming.reserve( ReserveSize );
    buffer.reserve( ReserveSize );
  }

  bool Poll( timer::Time _now )
  {
    bool eventsWasProcessed = false;
    if ( PollImmidiateEvents() )
      eventsWasProcessed = true;
    if ( PollSchedule( _now ) )
      eventsWasProcessed = true;
    return eventsWasProcessed;
  }

  void Add( IScheduleCallback * _evt, TScheduleAuxParam _aux )
  {
    threading::MutexLock lock( incomingMtx );
    NI_VERIFY( incoming.size() <= EventsBufferLimit, "Event buffer overflow", return );
    incoming.push_back( EventItem( _evt, _aux ) );
  }


  void Add( IScheduleCallback * _evt, timer::Time _when, TScheduleAuxParam _aux )
  {
    threading::MutexLock lock( scheduleMtx );
    NI_VERIFY( schedule.size() <= EventsBufferLimit, "Event buffer overflow", return );
    schedule[ScheduleKey( _when * 1e6 , scheduleSequence++ )] = EventItem( _evt, _aux );
  }

private:
  typedef unsigned long long Sequence;
  typedef unsigned long long Microseconds;

  struct EventItem
  {
    StrongMT<IScheduleCallback> callback;
    TScheduleAuxParam aux;
    EventItem() : aux( 0 ) {}
    EventItem( IScheduleCallback * _cb, TScheduleAuxParam _aux ) : callback( _cb ), aux( _aux ) {}
  };

  struct ScheduleKey
  {
    Microseconds when;
    Sequence sequence;
    ScheduleKey() : when( 0 ), sequence( 0 ) {}
    ScheduleKey( Microseconds _when, Sequence _seq ) : when( _when ), sequence( _seq ) {}
    bool operator < ( const ScheduleKey & other ) const {
      if ( when < other.when )
        return true;
      if ( when > other.when )
        return false;
      return sequence < other.sequence; };
  };

  typedef std::vector<EventItem> EvtQueue;
  typedef std::map<ScheduleKey, EventItem> EvtSchedule;

  threading::Mutex incomingMtx, bufferMtx;
  EvtQueue incoming, buffer;

  threading::Mutex scheduleMtx;
  EvtSchedule schedule;
  Sequence scheduleSequence;

  virtual void Work( volatile bool & isRunning )
  {
    while( isRunning )
    {
      if ( !Poll( timer::Now() ) )
        nival::sleep( 10 );
    }
  }


  bool PollImmidiateEvents()
  {
    threading::MutexLock lock( bufferMtx );

    {
      threading::MutexLock lock2( incomingMtx );
      incoming.swap( buffer );
    }

    if ( buffer.empty() )
      return false;
    
    for( EvtQueue::iterator it = buffer.begin(); it != buffer.end(); ++it )
      it->callback->AsyncEvent( it->aux );

    buffer.clear();
    return true;
  }


  bool PollSchedule( timer::Time _now )
  {
    Microseconds now = _now * 1e6;
    std::list<EventItem> cash;

    {
      threading::MutexLock lock( scheduleMtx );

      EvtSchedule::iterator it = schedule.begin();
      for( ; it != schedule.end(); ++it )
        if ( now >= it->first.when )
          cash.push_back( it->second );
        else
          break;

      schedule.erase( schedule.begin(), it );
    }

    if ( cash.empty() )
      return false;

    while ( !cash.empty() )
    {
      cash.front().callback->AsyncEvent( cash.front().aux );
      cash.pop_front();
    }
    return true;
  }
};











Schedule::Schedule( bool _syncMode )
{
  worker = new Worker;

  if ( !_syncMode )
    thread = new threading::JobThread( worker, "AsyncEventsWorker" );
}



void Schedule::Add( IScheduleCallback * _evt, TScheduleAuxParam _aux )
{
  worker->Add( _evt, _aux );
}



void Schedule::Add( IScheduleCallback * _evt, timer::Time _when, TScheduleAuxParam _aux )
{
  worker->Add( _evt, _when, _aux );
}



void Schedule::SyncPoll( timer::Time _now )
{
  NI_VERIFY( !thread, "Sync polling async event", return );
  worker->Poll( _now );
}
