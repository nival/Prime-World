#include "stdafx.h"
#include "Profiler3UIData.h"
#include <Psapi.h>


namespace profiler3ui
{

SamplingData::SamplingData() :
lastSyncOperation( 0 ),
memoryUsage( 0 )
{
}



void SamplingData::Update()
{
  const NHPTimer::FTime syncPeriod = 0.25;

  NHPTimer::FTime now = NHPTimer::GetScalarTime();
  const bool sync = ( now > ( lastSyncOperation + syncPeriod ) );

  if ( sync )
  {
    lastSyncOperation = now;

    SyncThreads();
    UpdateMemoryUsage();
  }

  UpdateThreadTimings();

  if ( sync )
  {
    RetrieveRootEvents();
    SyncWorstEvents();
  }
}



void SamplingData::EnableSampling( profiler3::TThreadId threadId, bool enable )
{
  if ( threadId )
  {
    TThreads::iterator it = threads.find( threadId );
    NI_VERIFY( it != threads.end(), "Unknown thread", return );

    it->second.samplingEnabled = enable;
    it->second.rootEvents.clear();
    it->second.worstEvents.Clear();
    profiler3::GetControl()->EnableSampling( threadId, enable );
  }
  else
    for ( TThreads::iterator it = threads.begin(); it != threads.end(); ++it )
    {
      it->second.samplingEnabled = enable;
      it->second.rootEvents.clear();
      it->second.worstEvents.Clear();
      profiler3::GetControl()->EnableSampling( it->first, enable );
    }
}



bool SamplingData::GetThreadInfo( profiler3::TThreadId threadId, SThreadInformation & info ) const
{
  TThreads::iterator it = threads.find( threadId );
  if ( it == threads.end() )
    return false;

  info.osThreadId = it->second.osThreadId;
  info.alive = it->second.alive;
  info.samplingEnabled = it->second.samplingEnabled;
  info.kernelTimePerc = it->second.kernelPerc;
  info.userTimePerc = it->second.userPerc;

  return true;
}



void SamplingData::PopNewThreads( vector<profiler3::TThreadId> & result )
{
  result.clear();
  for ( TThreads::iterator it = threads.begin(); it != threads.end(); ++it )
    if ( it->second.newThread )
    {
      it->second.newThread = false;
      result.push_back( it->first );
    }
}



void SamplingData::SyncThreads()
{
  profiler3::GetControl()->GetThreadList( threadsInfoBuffer );

  for ( TThreads::iterator it = threads.begin(); it != threads.end(); ++it )
    it->second.valid = false;

  for ( int i = 0; i < threadsInfoBuffer.size(); ++i )
  {
    SThread & thrd = threads[threadsInfoBuffer[i].threadId];
    thrd.valid = true;
    if ( thrd.newThread )
    {
      thrd.samplingEnabled = threadsInfoBuffer[i].samplingEnabled;
      thrd.osThreadId = threadsInfoBuffer[i].osThreadId;
    }
    thrd.alive = threadsInfoBuffer[i].alive;
  }

  for ( TThreads::iterator it = threads.begin(); it != threads.end(); )
    if ( it->second.valid )
      ++it;
    else
      it = threads.erase( it );
}



void SamplingData::UpdateThreadTimings()
{
  const NHPTimer::FTime MeasurePeriod = 1.0;
  for ( TThreads::iterator it = threads.begin(); it != threads.end(); ++it )
  {
    SThread & thrd = it->second;

    NHPTimer::FTime now = NHPTimer::GetScalarTime();
    NHPTimer::FTime realDelta = now - thrd.lastMeasureTime;

    if ( realDelta < MeasurePeriod )
      continue;

    HANDLE h = OpenThread( READ_CONTROL | THREAD_QUERY_INFORMATION, FALSE, it->second.osThreadId );
    if ( !h )
      continue;

    FILETIME ftCr, ftEx, ftKern, ftUser;
    BOOL result = GetThreadTimes( h, &ftCr, &ftEx, &ftKern, &ftUser );
    CloseHandle( h );

    if ( !result )
      continue;

    NHPTimer::FTime kernel = ( (LARGE_INTEGER &)ftKern ).QuadPart * ( 1e-9 * 100.0 ); //нановремя
    NHPTimer::FTime user = ( (LARGE_INTEGER &)ftUser ).QuadPart * ( 1e-9 * 100.0 );

    NHPTimer::FTime kernelDelta = kernel - thrd.kernelTime;
    NHPTimer::FTime userDelta = user - thrd.userTime;

    thrd.kernelPerc = (int)( 100 * kernelDelta / realDelta );
    thrd.userPerc = (int)( 100 * userDelta / realDelta );

    thrd.kernelTime = kernel;
    thrd.userTime = user;

    thrd.lastMeasureTime = now;
  }
}



void SamplingData::UpdateMemoryUsage()
{
  PROCESS_MEMORY_COUNTERS pmc;
  ZeroMemory( &pmc, sizeof( pmc ) );
  pmc.cb = sizeof( pmc );
  GetProcessMemoryInfo( GetCurrentProcess(), &pmc, sizeof( pmc ) );

  memoryUsage = pmc.PagefileUsage;
}



void SamplingData::RetrieveRootEvents()
{
  for ( TThreads::iterator it = threads.begin(); it != threads.end(); ++it )
  {
    profiler3::TThreadId threadId = it->first;
    SThread & thrd = it->second;

    if ( thrd.samplingEnabled )
      profiler3::GetControl()->AdjustRootEventsToTimeline( threadId, thrd.rootEvents );
  }
}



void SamplingData::SyncWorstEvents()
{
  for ( TThreads::iterator it = threads.begin(); it != threads.end(); ++it )
  {
    profiler3::TThreadId threadId = it->first;
    SThread & thrd = it->second;

    if ( thrd.samplingEnabled )
      profiler3::GetControl()->SyncWorstEvents( threadId, thrd.worstEvents );
  }
}



const profiler3::SRootEventDesc * SamplingData::GetRootEvent( profiler3::TThreadId threadId, int eventId, profiler3::TOsThreadId & osThreadId ) const
{
  if ( !threadId || eventId < 0 )
    return 0;

  TThreads::const_iterator it = threads.find( threadId );
  if ( it == threads.end() )
    return 0;
  const profiler3::TRootEventsDescription & events = it->second.rootEvents;

  for ( int i = 0; i < events.size(); ++i )
    if ( events[i].id == eventId )
    {
      osThreadId = it->second.osThreadId;
      return &events[i];
    }
  return 0;
}



const profiler3::TRootEventsDescription * SamplingData::GetNextEnabledThreadRootEvents( profiler3::TThreadId & threadId, profiler3::TOsThreadId & osThreadId ) const
{
  TThreads::const_iterator it = threads.begin();

  if ( threadId )
  {
    it = threads.find( threadId );
    if ( it != threads.end() )
      ++it;
  }

  while( it != threads.end() )
  {
    if ( it->second.samplingEnabled )
    {
      threadId = it->first;
      osThreadId = it->second.osThreadId;
      return &it->second.rootEvents;
    }
    else
      ++it;
  }
  threadId = 0;
  return 0;
}



unsigned SamplingData::GetEnabledThreadsCount() const
{
  int count = 0;
  for ( TThreads::const_iterator it = threads.begin(); it != threads.end(); ++it )
    if ( it->second.samplingEnabled )
      ++count;
  return count;
}



unsigned SamplingData::GetDeadThreadsCount() const
{
  int count = 0;
  for ( TThreads::const_iterator it = threads.begin(); it != threads.end(); ++it )
    if ( !it->second.alive )
      ++count;
  return count;
}



const profiler3::SWorstEventsSet * SamplingData::GetWorstEventsSet( profiler3::TThreadId threadId ) const
{
  if ( !threadId )
    return 0;

  TThreads::const_iterator it = threads.find( threadId );
  if ( it == threads.end() )
    return 0;

  return &it->second.worstEvents;
}

} //namespace profiler3ui