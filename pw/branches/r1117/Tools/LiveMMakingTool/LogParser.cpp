#include "stdafx.h"
#include "LogParser.h"

namespace mm_test
{

NI_ENUM_BEGIN_STD( ELogVersion );
  NI_ENUM_ITEM( v82x );
  NI_ENUM_ITEM( v902 );
  NI_ENUM_ITEM( v903 );
  NI_ENUM_ITEM( v911 );
  NI_ENUM_ITEM( v914 );
  NI_ENUM_ITEM( v923 );
  NI_ENUM_ITEM( trunk );
NI_ENUM_END_STD;


static void SetupTM( tm & t, const Timestamp & ts ) {
  memset( &t, 0, sizeof( tm ) );
  t.tm_year   = ts.date.year - 1900;
  t.tm_mon    = ts.date.mon - 1;
  t.tm_mday   = ts.date.day;
  t.tm_hour   = ts.time.hour;
  t.tm_min    = ts.time.minute;
  t.tm_sec    = ts.time.sec;
}



static void SetupTM( Timestamp & ts, const tm & t ) {
  ts.date.year    = t.tm_year + 1900;
  ts.date.mon     = t.tm_mon + 1;
  ts.date.day     = t.tm_mday;
  ts.time.hour    = t.tm_hour;
  ts.time.minute  = t.tm_min;
  ts.time.sec     = t.tm_sec;
}



timer::Time TimeDiff( const Timestamp & ts1, const Timestamp & ts0 )
{
  tm t0, t1;
  SetupTM( t0, ts0 );
  SetupTM( t1, ts1 );

  __time64_t tt0 = _mktime64( &t0 ), tt1 = _mktime64( &t1 );

  timer::Time delta = (timer::Time)tt1 - (timer::Time)tt0;

  delta += (timer::Time)( 1e-3 * ts1.time.ms - 1e-3 * ts0.time.ms );

  return delta;
}



void Advance( Timestamp & ts, timer::Time delta )
{
  tm t;
  SetupTM( t, ts );

  float frac = 1e-3f * ts.time.ms;
  frac += delta - floorf( (float)delta );

  __time64_t tt = _mktime64( &t );

  tt += (__time64_t)floor( delta );
  if ( frac >= 1.0f ) {
    ++tt;
    frac -= 1.0f;
  }

  //const tm * newt = _gmtime64( &tt );
  const tm * newt = localtime( &tt );

  SetupTM( ts, *newt );
  ts.time.ms = (int)floorf(frac * 1e3f);
}

} //namespace mm_test
