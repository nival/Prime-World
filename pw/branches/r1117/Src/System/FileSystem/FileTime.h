#ifndef _FILE_TIME_H_
#define _FILE_TIME_H_

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <time.h>


#if defined( NV_WIN_PLATFORM )
  #pragma warning( push )
  #pragma warning( disable: 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SWin32Time
{
	union
	{
		struct
		{
			unsigned long seconds : 5;								// seconds (0..29 with 2 sec. interval)
			unsigned long minutes : 6;								// minutes (0..59)
			unsigned long hours	 : 5;								// hours (0..23)
			unsigned long day		 : 5;								// day (1..31)
			unsigned long month	 : 4;								// month(1..12)
			unsigned long year		: 7;								// year (0..119 relative to 1980)
		};
		struct
		{
			unsigned short wTime;
			unsigned short wDate;
		};
		unsigned long dwFulltime;
	};
	//
	SWin32Time() {	}
	SWin32Time( const unsigned long _dwFulltime ) : dwFulltime( _dwFulltime ) {	}
	unsigned short GetDate() const { return wDate; }
	unsigned short GetTime() const { return wTime; }
	unsigned long  GetFullTime() const { return dwFulltime; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transforms DOS date/time format (time_t) to the Win32 date/time format (SWin32Time)
inline unsigned long DOSToWin32DateTime( time_t dostime )
{
	// transform DOS time to local time 'tm' structure
	tm time;
#if defined( NV_WIN_PLATFORM )
	  localtime_s( &time, &dostime );
#elif defined( NV_LINUX_PLATFORM )
    time = *localtime( &dostime );
#endif	  
	// fill 'SWin32Time' structure to automagically convert to Win32 date/time format
	SWin32Time filetime;
	filetime.year		= time.tm_year - 80;	// due to 'tm' year relative to 1900 year, but we need relative to 1980
	filetime.month	 = time.tm_mon + 1;		// due to the month represented in the '0..11' format, but we need in '1..12'
	filetime.day		 = time.tm_mday;			// day in '1..31' format
	filetime.hours	 = time.tm_hour;			// hours in '0..23' format
	filetime.minutes = time.tm_min;				// minutes in '0..59' format
	filetime.seconds = time.tm_sec / 2;		// due to win32 seconds resolution are 2 sec. (i.e. seconds represented in '0..29' format)

	return filetime.GetFullTime();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform time in seconds to string representation
inline wstring TimeSecondsToTimeString( float secondsIn )
{  
  int hours( secondsIn/3600 );
  int minutes( (secondsIn - 3600*hours)/60 );
  int seconds(  secondsIn - 3600*hours - 60*minutes);
  wstring timeResult(L"");
  
  //add hours
  if ( hours != 0 )
    timeResult = NStr::IntToWStr(hours) + L":";
  
  //add minutes
  if ( minutes != 0 )    
  {    
    timeResult += (hours != 0 && minutes < 10) ? L"0" : L"";
    timeResult += NStr::IntToWStr(minutes) + L":";
  }
  else if ( hours != 0 )
  {
    timeResult += L"00";  
    timeResult += L":"; 
  }
  
  //add the seconds
  timeResult += (!timeResult.empty() && seconds < 10) ? L"0" : L"";
  timeResult += NStr::IntToWStr(seconds);

  return timeResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transforms Win32 date/time format (SWin32Time) to the DOS date/time format (time_t)
inline time_t Win32ToDOSDateTime( const unsigned long _w32time )
{
	struct SConvert
	{
		union
		{
			struct	
			{
				unsigned long seconds : 5;								// seconds (0..29 with 2 sec. interval)
				unsigned long minutes : 6;								// minutes (0..59)
				unsigned long hours	 : 5;								// hours (0..23)
				unsigned long day		 : 5;								// day (1..31)
				unsigned long month	 : 4;								// month(1..12)
				unsigned long year		: 7;								// year (0..119 relative to 1980)
			};
			unsigned long dwFullTime;
		};
	};
	SConvert w32time;
	w32time.dwFullTime = _w32time;
	// compose 'tm' structure. for details you can see a function above
	tm tmTime;
	Zero( tmTime );
	tmTime.tm_year = int( w32time.year ) + 80;
	tmTime.tm_mon	= int( w32time.month ) - 1;
	tmTime.tm_mday = int( w32time.day );
	tmTime.tm_hour = int( w32time.hours );
	tmTime.tm_min	= int( w32time.minutes );
	tmTime.tm_sec	= int( w32time.seconds ) * 2;
	// convert 'tm' to 'time_t'
	time_t result = mktime( &tmTime );
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transforms FILETIME to Win32 date/time (SWin32Time)

#if defined( NV_WIN_PLATFORM )

inline unsigned long FILETIMEToWin32DateTime( const FILETIME &filetime )
{
	FILETIME localfiletime;
	FileTimeToLocalFileTime( &filetime, &localfiletime );
	SWin32Time win32time;
	FileTimeToDosDateTime( &localfiletime, &win32time.wDate, &win32time.wTime );
	return win32time.GetFullTime();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transforms FILETIME to TM time 
inline void FILETIMEToTMTime( const FILETIME &filetime, tm *pTMTime )
{
	struct SConvert
	{
		union
		{
			struct	
			{
				unsigned long seconds : 5;								// seconds (0..29 with 2 sec. interval)
				unsigned long minutes : 6;								// minutes (0..59)
				unsigned long hours 	: 5;								// hours (0..23)
				unsigned long day		  : 5;								// day (1..31)
				unsigned long month	  : 4;								// month(1..12)
				unsigned long year		: 7;								// year (0..119 relative to 1980)
			};
			unsigned long dwFullTime;
		};
	};
	SConvert w32time;
	FILETIME localfiletime;
	FileTimeToLocalFileTime( &filetime, &localfiletime );
	SWin32Time win32time;
	FileTimeToDosDateTime( &localfiletime, &win32time.wDate, &win32time.wTime );
	w32time.dwFullTime = win32time.GetFullTime();
	// compose 'tm' structure. for details you can see a function above
	Zero( *pTMTime );
	pTMTime->tm_year = int( w32time.year ) + 80;
	pTMTime->tm_mon	= int( w32time.month ) - 1;
	pTMTime->tm_mday = int( w32time.day );
	pTMTime->tm_hour = int( w32time.hours );
	pTMTime->tm_min	= int( w32time.minutes );
	pTMTime->tm_sec	= int( w32time.seconds ) * 2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transforms Win32 date/time (SWin32Time) to FILETIME
inline FILETIME Win32DateTimeToFILETIME( const unsigned long win32time )
{
	FILETIME localft;
	DosDateTimeToFileTime( HIWORD(win32time), LOWORD(win32time), &localft );
	FILETIME filetime;
	LocalFileTimeToFileTime( &localft, &filetime );
	return filetime;
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined( NV_WIN_PLATFORM )
  #pragma warning( pop )
#endif  

#endif
