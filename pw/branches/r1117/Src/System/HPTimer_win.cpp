#include "stdafx.h"

#include "HPTimer.h"
#include "Thread.h"


namespace NHPTimer 
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool gSafeMode = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const double         FreqResampleRate = 0.1;

//To ensure atomic access to variables
#define MY_VOLATILE volatile __declspec(align(8))

static MY_VOLATILE STime    gStartTime = 0;
static MY_VOLATILE STime    gFrequency = 0;
static MY_VOLATILE STime    gLastCounter = 0;
static MY_VOLATILE STime    gLastFreqQuery = 0;
static MY_VOLATILE STime    gFreqQueryPeriod = 0;

//Affinity stuff
static  unsigned long       gProcMask = 0;
static unsigned long        gSysMask = 0;
static HANDLE               gThread = 0;
static HANDLE               gProc = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double GetTimerFrequency()
{
  return (double)gFrequency;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateHPTimerFrequency()
{
  MY_VOLATILE STime lastCounter, lastFreqQuery;
  lastCounter = gLastCounter;
  lastFreqQuery = gLastFreqQuery;

  STime queryAge = lastCounter - lastFreqQuery;
  if ( queryAge >= gFreqQueryPeriod )
  {
    MY_VOLATILE STime freq;
    ::QueryPerformanceFrequency( (LARGE_INTEGER *)&freq );
    STime period = (STime)( gFrequency * FreqResampleRate );

    gFrequency = freq;
    gFreqQueryPeriod = period;
    gLastFreqQuery = gLastCounter;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Init()
{
  NI_ASSERT( sizeof(LARGE_INTEGER) == sizeof(STime), "" );

  //Save curent process affinity
  gProc = GetCurrentProcess();
  GetProcessAffinityMask( gProc, &gProcMask, &gSysMask );

  ::QueryPerformanceCounter( (LARGE_INTEGER *)&gStartTime );
  gLastCounter = gStartTime;

  UpdateHPTimerFrequency();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetSafeMode( bool safe )
{
  gSafeMode = safe;
}

//IMPORTANT!
// Q274323 refers to PM (PCI) timer and performance counter time leaps occured on early 2k chipsets (e.g. Pentium II chipsets)
// This timer still can be used with /usepmtimer in Boot.ini but problems should be gone nowdays
// On current PCs with Windows XP QueryPerformanceCounter commounly uses 'rdtsc'
// But on many AMD multicore CPUs another problem emerge: sometimes time value 'steps back' for about 100-300 ms.
// This is commonly fixed by setting timer thread affinity to one core
// This problem described in KB895980
// Experiments shows that most Window Vista versions are using PM timer again

//By now we will trust to QueryPerformanceCounter() but filter non-ascend values

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetTime( STime & time )
{
  MY_VOLATILE STime frequency = gFrequency;

  //Kind of thread-riscy.
  if ( !frequency )
    Init();

  //Special case
  if ( gSafeMode )
  {
    ::SetThreadAffinityMask( GetCurrentThread(), 1 );
    STime curTime;
    ::QueryPerformanceCounter( (LARGE_INTEGER *)&curTime );
    ::SetThreadAffinityMask( GetCurrentThread(), gProcMask );
    time = curTime - gStartTime;

    UpdateHPTimerFrequency();
    return;
  }

  //We do not want to use affinity tricks, let's trick another way
  MY_VOLATILE STime lastCounter = gLastCounter; //remember global in thread's stack

  // Query the timer
  MY_VOLATILE STime curTime;
  ::QueryPerformanceCounter( (LARGE_INTEGER *)&curTime );

  //Fix for multicore/multithread timer issues
  if ( curTime < lastCounter )
    time = lastCounter - gStartTime;
  else
  {
    gLastCounter = curTime;
    time = curTime - gStartTime;
  }

  UpdateHPTimerFrequency();
}

} // namespace HPTimer



namespace timer
{

int TimeZoneOffsetInMinutes()
{
  TIME_ZONE_INFORMATION tzi;
  ZeroMemory( &tzi, sizeof( tzi ) );
  DWORD tz = GetTimeZoneInformation( &tzi );
  if ( tz == TIME_ZONE_ID_UNKNOWN )
    return -tzi.Bias;
  else if ( tz == TIME_ZONE_ID_STANDARD )
    return -( tzi.Bias + tzi.StandardBias );
  else if ( tz == TIME_ZONE_ID_DAYLIGHT )
    return -( tzi.Bias + tzi.DaylightBias );

  NI_ALWAYS_ASSERT( "Could not get current time zone" );
  return 0;
}



Time DecodedTimeToScalar( const DecodedTime & t )
{
  ::FILETIME ft;
  memset( &ft, 0, sizeof( ft ) );
  SystemTimeToFileTime( &t, &ft );

  Time sec = 1e-7 * ( (Time)ft.dwHighDateTime * (Time)0x100000000 + (Time)ft.dwLowDateTime );
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

} //namespace timer