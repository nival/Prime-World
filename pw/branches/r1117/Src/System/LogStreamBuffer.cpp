/**
  @TODO: убрать ifdef, заменить на кроссплатформенные функции (готовые, если есть или сделать).
 */

#include "stdafx.h"

#include "LogStreamBuffer.h"
#include "System/InlineProfiler.h"
#include "LogHelpers.h"


namespace NLogg
{

void StreamBuffer::WriteHeader( unsigned headerFormat )
{
  NI_PROFILE_HEAVY_FUNCTION;

  char buf[128] = "";

  if ( entryInfo.level == LEVEL_ASSERT )
  {
    Push( entryInfo.filename );
    char buf[32];
#if defined( NV_WIN_PLATFORM )
    sprintf_s( buf, "(%d): ", entryInfo.line );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "(%d): ", entryInfo.line );
#endif
    Push( buf );
  }

  if( headerFormat == EHeaderFormat::Default )
  {
    // request: don't write default channel name as "[.]"
#if defined( NV_WIN_PLATFORM )
    sprintf_s( buf, "(%04u) %02u:%02u:%02u.%03u %s%s%s %s: ", entryInfo.threadId,
                                            entryInfo.time.wHour, entryInfo.time.wMinute, entryInfo.time.wSecond, entryInfo.time.wMilliseconds,
                                            entryInfo.channel ? "[" : "", entryInfo.channel ? entryInfo.channel : "", entryInfo.channel ? "]" : "",
                                            MessageLevelToString( entryInfo.level ) );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "(%04u) %02u:%02u:%02u.%03u %s%s%s %s: ", ::pthread_self(),
                                            entryInfo.time.wHour, entryInfo.time.wMinute, entryInfo.time.wSecond, entryInfo.time.wMilliseconds,
                                            entryInfo.channel ? "[" : "", entryInfo.channel ? entryInfo.channel : "", entryInfo.channel ? "]" : "",
                                            MessageLevelToString( entryInfo.level ) );
#endif
    Push( buf );
    return;
  }

  // go flag by flag..
  if ( headerFormat & EHeaderFormat::ThreadId )
  {
#if defined( NV_WIN_PLATFORM )
    sprintf_s( buf, "(%04u) ", ::GetCurrentThreadId() );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "(%04u) ", ::pthread_self() );
#endif
    Push( buf );
  }

  if ( headerFormat & EHeaderFormat::Timestamp )
  {
#if defined( NV_WIN_PLATFORM )
    sprintf_s( buf, "%02u:%02u:%02u.%03u ", entryInfo.time.wHour, entryInfo.time.wMinute, entryInfo.time.wSecond, entryInfo.time.wMilliseconds );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "%02u:%02u:%02u.%03u ", entryInfo.time.wHour, entryInfo.time.wMinute, entryInfo.time.wSecond, entryInfo.time.wMilliseconds );
#endif
    Push( buf );
  }

  if ( ( headerFormat & EHeaderFormat::ChannelName ) && entryInfo.channel ) // request: dont write default channel name as "[.]"
  {
#if defined( NV_WIN_PLATFORM )
    sprintf_s( buf, "[%s] ", entryInfo.channel );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "[%s] ", entryInfo.channel );
#endif
    Push( buf );
  }

  if ( headerFormat & EHeaderFormat::Severity )
  {
#if defined( NV_WIN_PLATFORM )
    sprintf_s( buf, "%s: ", MessageLevelToString( entryInfo.level ) );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "%s: ", MessageLevelToString( entryInfo.level ) );
#endif
    Push( buf );
  }
}


} //namespace NLogg
