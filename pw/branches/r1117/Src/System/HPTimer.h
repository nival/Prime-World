#ifndef _HPTIMER_H_
#define _HPTIMER_H_

#include "System/config.h"

#if defined( NV_LINUX_PLATFORM )
#include "time.h"
#endif

namespace NHPTimer
{

#ifdef WIN32
  typedef LONGLONG STime;
#else
  typedef long long STime;
#endif

typedef double  FTime;

void          Init();

void          SetSafeMode( bool safe );

void          GetTime( STime & time );
FTime         GetScalarTime();
FTime         GetTimePassedAndUpdateTime( STime &Time );
FTime         GetTimePassedAndUpdateTimeWithLowerLimit( STime &time, FTime lowerLimit );

FTime         Time2Seconds( const STime &time );

FTime         GetTimerFrequency();

inline int Time2Milliseconds(STime value)
{
  return int(Time2Seconds(value)*1000);
}

inline int Milliseconds2Seconds(int value)
{
  return value*0.001f;
}

inline STime Seconds2Time(double value)
{
  return value*GetTimerFrequency();
}

inline STime Milliseconds2Time(int value)
{
  return value*GetTimerFrequency()*0.001;
}

} // namespace NHPTimer


//More usable synonims to NHPTimer::FTime and NHPTimer::GetScalarTime()
namespace timer
{
  typedef NHPTimer::FTime Time;
  typedef NHPTimer::STime Ticks;

#if defined( NV_WIN_PLATFORM )

  struct DecodedTime : public ::SYSTEMTIME {
    DecodedTime() {
      wYear = 0;
      wMonth = 0;
      wDayOfWeek = 0;
      wDay = 0;
      wHour = 0;
      wMinute = 0;
      wSecond = 0;
      wMilliseconds = 0;
    }
  };

#else

  struct DecodedTime {

    DecodedTime()
    {
      wYear = 0;
      wMonth = 0;
      wDayOfWeek = 0;
      wDay = 0;
      wHour = 0;
      wMinute = 0;
      wSecond = 0;
      wMilliseconds = 0;
    }

    nival::uint16_t wYear;
    nival::uint16_t wMonth;
    nival::uint16_t wDayOfWeek;
    nival::uint16_t wDay;
    nival::uint16_t wHour;
    nival::uint16_t wMinute;
    nival::uint16_t wSecond;
    nival::uint16_t wMilliseconds;

  };

#endif


  inline Time Now() { return NHPTimer::GetScalarTime(); }
  inline Ticks GetTicks() { Ticks now; NHPTimer::GetTime( now ); return now; }

  void LocalDecodedTime( DecodedTime & t );
  inline void UtcDecodedTime( DecodedTime & t )
  {
#if defined( NV_WIN_PLATFORM )
    GetSystemTime( &t );
#elif defined( NV_LINUX_PLATFORM )
    time_t tn = time(0);
    struct tm * now = localtime( &tn );
    t.wYear = now->tm_year;
    t.wMonth = now->tm_mon;
    t.wDayOfWeek = now->tm_wday;
    t.wDay = now->tm_mday;
    t.wHour = now->tm_hour;
    t.wMinute = now->tm_min;
    t.wSecond = now->tm_sec;
    t.wMilliseconds = 0;
#endif
  }

  int TimeZoneOffsetInMinutes();

  Time DecodedTimeToScalar( const DecodedTime & t ); //Seconds since January 1, 1601 (UTC).
  void SetupEpoch( DecodedTime & t );

} //namespace timer

#endif

