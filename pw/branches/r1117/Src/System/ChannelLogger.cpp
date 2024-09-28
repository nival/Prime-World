#include "stdafx.h"

#include "ChannelLogger.h"
#include "Dumper.h"
#include "System/InlineProfiler.h"
#include <System/ported/cwfn.h>

namespace NLogg
{

CChannelLogger::~CChannelLogger()
{
  channels.clear();
}



bool CChannelLogger::IsChannelPresent( const char* szChannelName ) const
{
  if ( szChannelName == NULL ) 
    return false;

  threading::ReadLockGuard guard( mutex );

  if ( channels.find( szChannelName ) != channels.end() )
    return true;
  //for ( TChannels::const_iterator it = channels.begin(); it != channels.end(); ++it )
  //  if ( strcmp(it->szName, szChannelName) == 0 )
  //    return true;

  return false;
}



const CLogger::TDumpers* CChannelLogger::GetDumpContext( const char *szChannelName, const ELevel eLevel ) const
{
  //Already locked above
  //threading::ReadLockGuard guard( mutex );

  unsigned dwMsgLevel = GetLevelMask(eLevel);
  if( szChannelName )
  {
    TChannels::const_iterator it = channels.find( szChannelName );
    if ( it != channels.end() )
    {
      if ( dwMsgLevel & it->second->levelFilter ) 
        // found, severity ok for this channel
        return !it->second->dumpers.empty() ? &it->second->dumpers : &dumpers; // если собственный контекст нулевой, берем унаследованный 
      else
        return NULL; // found, but level mask doesnt include given msg severity: NO DUMP
    }
  }
  else
  {
    if( dwMsgLevel & dwLevelFilter )
    {// msg severity ok for default logging
      return &dumpers; // поскольку имя канала нулевое, всегда берем унаследованный контекст
    }
  }

  // FAIL: NO DUMP
  return NULL;
}



bool CChannelLogger::SetChannelLevelFilter( const char* szChannelName, unsigned long dwNewLevelFilter )
{
  threading::ReadLockGuard guard( mutex );

  if( szChannelName )
  {
    TChannels::const_iterator it = channels.find( szChannelName );
    if ( it != channels.end() )
    {
      it->second->levelFilter = dwNewLevelFilter;
      return true; // success
    }
  }
  else
  {// NULL name, set default logging-level mask (for "broadcast to all possible dumpers" writes
    dwLevelFilter = dwNewLevelFilter;
    return true; // success
  }

  return false; // fail, no such name found
}



void CChannelLogger::Log( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  UpdateCounters( entryInfo );

  threading::ReadLockGuard guard( mutex );

  Notify( entryInfo, headerAndText, textOnly );

  const TDumpers* pDumpers = GetDumpContext( entryInfo.channel, entryInfo.level );


  if ( pDumpers != 0 && !pDumpers->empty() )
  {// valid dumper set exists (named or default), for given msg severity level
    for ( TDumpers::const_iterator it = pDumpers->begin(); it != pDumpers->end(); ++it )
      (*it)->Dump( entryInfo, headerAndText, textOnly );
  }
  else
  {
    //Сейчас не зарегистрирован ни один dumper и для того чтобы сообщение не потерялось выведем
    //его хоть куда-нибудь
    OutputDebugString( headerAndText );
  }
}



bool CChannelLogger::AddChannel( const char * _name, const TDumpers & _dumpers, unsigned _levelFilter )
{
  RemoveChannel( _name );

  threading::WriteLockGuard guard( mutex );

  if( _levelFilter == LEVEL_INHERIT )
    _levelFilter = dwLevelFilter;

  channels[ _name ] = new SLoggingChannel( _name, _dumpers, _levelFilter );

  return true;
}



bool CChannelLogger::RemoveChannel( const char* szChannelName )
{
  threading::WriteLockGuard guard( mutex );

  TChannels::iterator it = channels.find( szChannelName );
  if ( it == channels.end() )
    return false;

  channels.erase( it );
  return true;
}



bool CChannelLogger::AddChannel( const char * name, CDumper * dumper1, unsigned levelFilter )
{
  TDumpers chanDumpers;
  chanDumpers.push_back( dumper1 );
  return AddChannel( name, chanDumpers, levelFilter );
}



bool CChannelLogger::AddChannel( const char * name, CDumper * dumper1, CDumper * dumper2, unsigned levelFilter )
{
  TDumpers chanDumpers;
  chanDumpers.push_back( dumper1 );
  chanDumpers.push_back( dumper2 );
  return AddChannel( name, chanDumpers, levelFilter );
}



bool CChannelLogger::AddChannel( const char * name, CDumper * dumper1, CDumper * dumper2, CDumper * dumper3, unsigned levelFilter )
{
  TDumpers chanDumpers;
  chanDumpers.push_back( dumper1 );
  chanDumpers.push_back( dumper2 );
  chanDumpers.push_back( dumper3 );
  return AddChannel( name, chanDumpers, levelFilter );
}



bool CChannelLogger::AddChannel( const char * name, CDumper * dumper1, CDumper * dumper2, CDumper * dumper3, CDumper * dumper4, unsigned levelFilter )
{
  TDumpers chanDumpers;
  chanDumpers.push_back( dumper1 );
  chanDumpers.push_back( dumper2 );
  chanDumpers.push_back( dumper3 );
  chanDumpers.push_back( dumper4 );
  return AddChannel( name, chanDumpers, levelFilter );
}



void CChannelLogger::ClearAllDumpers()
{
  {
    threading::WriteLockGuard guard( mutex );
    channels.clear();
  }

  CLogger::ClearAllDumpers();
}



SCounters CChannelLogger::GetCounters()
{
  return SCounters( (SCounters &)counters );
}



void CChannelLogger::UpdateCounters( const SEntryInfo & entryInfo )
{
  switch ( entryInfo.level )
  {
    case LEVEL_WARNING:
#if defined( NV_WIN_PLATFORM )
      InterlockedIncrement( &counters.warnings );
#elif defined( NV_LINUX_PLATFORM )
      __sync_fetch_and_add( &counters.warnings, 1 );
#endif
      break;

    case LEVEL_ERROR:
#if defined( NV_WIN_PLATFORM )
      InterlockedIncrement( &counters.errors );
#elif defined( NV_LINUX_PLATFORM )
      __sync_fetch_and_add( &counters.errors, 1 );
#endif
      break;

    case LEVEL_ASSERT:
#if defined( NV_WIN_PLATFORM )
      InterlockedIncrement( &counters.asserts );
#elif defined( NV_LINUX_PLATFORM )
      __sync_fetch_and_add( &counters.asserts, 1 );
#endif
      break;

    case LEVEL_CRITICAL:
#if defined( NV_WIN_PLATFORM )
      InterlockedIncrement( &counters.criticals );
#elif defined( NV_LINUX_PLATFORM )
      __sync_fetch_and_add( &counters.criticals, 1 );
#endif
      break;
  }
}


} // namespace NLogg

// quick & dirty TESTING/ DUMPING

namespace NLogg {

void CChannelLogger::TEST_LOG( const char *szFileName, const unsigned long dwLine, const ELevel eLevel, const char *szMessage, 
                               const char *szChannelName )
{ 
  SEntryInfo entryInfo( eLevel, szFileName, dwLine, szChannelName );

  CLogger::Log( entryInfo, szMessage, szMessage );
}



static void DUMP_CONTEXT( const CLogger::TDumpers & pDumpersContext_ )
{
  printf("context 0x%08x\n", pDumpersContext_ );

  if( !pDumpersContext_.empty() )
  {
    CLogger::TDumpers::const_iterator it = pDumpersContext_.begin();
    while ( it != pDumpersContext_.end() )
    {
      printf("- dumper 0x%08x\n", *it);
      ++it;
    }
  }
}



void CChannelLogger::DUMP_CHANNELS() const
{
  TChannels::const_iterator it = channels.begin();
  while ( it != channels.end() )
  {
    printf("channel %s (size %d):\n", it->second->name.c_str(), channels.size());
    DUMP_CONTEXT( it->second->dumpers );
    ++it;
  }
  printf("\n");
}


} // namespace NLogg

