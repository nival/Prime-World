
#include "stdafx.h"
#include "HPTimer.h"
#include <time.h>


namespace NHPTimer {

static  STime         gLastTime = 0;
static  int64         gStartTime = {0};
static  int64         gFrequency = {0};

FTime GetTimerFrequency()
{
	return gFrequency;
}

void Init()
{
  struct timespec ts = { 0 };
  NI_VERIFY_NO_RET( ::clock_gettime( CLOCK_REALTIME, &ts ) == 0, "Error in clock_gettime()" );
  gFrequency = 1000000;
  gStartTime =
    static_cast< int64 >( ts.tv_sec ) * gFrequency + static_cast< int64 >( ts.tv_nsec / 1000 );
}


void GetTime( STime & time )
{
  if ( 0 == gStartTime )
    Init();

  struct timespec ts = { 0 };
  NI_VERIFY_NO_RET( ::clock_gettime( CLOCK_REALTIME, &ts ) == 0, "Error in clock_gettime()" );

  const int64 curTime =
    static_cast< int64 >( ts.tv_sec ) * gFrequency + static_cast< int64 >( ts.tv_nsec / 1000 );

  time = curTime - gStartTime;
  gLastTime = curTime;
}

void UpdateHPTimerFrequency()
{
}

} // namespace HPTimer


namespace timer
{

int TimeZoneOffsetInMinutes()
{
  struct timeval tv = { 0 };
  struct timezone tz = { 0 };
  if ( ::gettimeofday( &tv, &tz ) == 0 )
  {
    return tz.tz_minuteswest;
  }
  /*
  TIME_ZONE_INFORMATION tzi;
  ZeroMemory( &tzi, sizeof( tzi ) );
  DWORD tz = GetTimeZoneInformation( &tzi );
  if ( tz == TIME_ZONE_ID_UNKNOWN )
    return -tzi.Bias;
  else if ( tz == TIME_ZONE_ID_STANDARD )
    return -( tzi.Bias + tzi.StandardBias );
  else if ( tz == TIME_ZONE_ID_DAYLIGHT )
    return -( tzi.Bias + tzi.DaylightBias );
  */

  NI_ALWAYS_ASSERT( "Could not get current time zone" );
  return 0;
}


Time DecodedTimeToScalar( const DecodedTime & t )
{
  struct tm tt;
  memset( &tt, 0, sizeof( tm ) );
  Time sec = static_cast< Time >( ::mktime( &tt ) );
  return sec;
}


void SetupEpoch( DecodedTime & t )
{
  memset( &t, 0, sizeof( t ) );
  t.wYear = 1970;
  t.wMonth = 1;
  t.wDayOfWeek = 2;
  t.wDay = 1;
  t.wHour = 0;
  t.wMinute = 0;
  t.wSecond = 0;
  t.wMilliseconds = 0;
}

} // namespace timer
