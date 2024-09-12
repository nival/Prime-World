#include "stdafx.h"

#include "HPTimer.h"

namespace NHPTimer
{

FTime GetScalarTime()
{
  STime t;
  GetTime( t );
  return Time2Seconds( t );
}



FTime GetTimePassedAndUpdateTime( STime &time )
{
  STime old(time);
  GetTime( time );
  return FTime(time - old) / GetTimerFrequency();
}



FTime GetTimePassedAndUpdateTimeWithLowerLimit( STime &time, FTime lowerLimit )
{
	STime  old(time);
	FTime delta;

	lowerLimit *= GetTimerFrequency();
	do 
	{
		GetTime( time );
		delta = FTime(time - old);
	} while (delta < lowerLimit);
	return delta / GetTimerFrequency();
}



FTime Time2Seconds( const STime &time )
{
  return FTime(time) / GetTimerFrequency();
}



struct SHPTimerInit
{
  SHPTimerInit() 
  { 
    NHPTimer::Init(); 
  }
};

static SHPTimerInit hptInit;

} //namespace NHPTimer

namespace timer
{

#if defined( NV_WIN_PLATFORM )

void LocalDecodedTime( DecodedTime & t )
{
  GetLocalTime( &t );
}

#elif defined( NV_LINUX_PLATFORM )

void LocalDecodedTime( DecodedTime & t )
{
  timeval current_time;
  gettimeofday( &current_time, NULL );

  tm * decoded_time = localtime( &current_time.tv_sec );

  t.wYear = decoded_time->tm_year + 1900;
  t.wMonth = decoded_time->tm_mon + 1;
  t.wDayOfWeek = 0;
  t.wDay = decoded_time->tm_mday;
  t.wHour = decoded_time->tm_hour;
  t.wMinute = decoded_time->tm_min;
  t.wSecond = decoded_time->tm_sec;
  t.wMilliseconds = current_time.tv_usec / 1000;
}

#endif

} // namespace timer
