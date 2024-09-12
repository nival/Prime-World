#include "stdafx.h"
#include "TimeUtils.h"

void GetOsLocalTime( struct tm *tim )
{
	time_t local_time;
	time( &local_time );

	*tim = *localtime( &local_time );

	tim->tm_mon++;
	tim->tm_year += 1900;
}

void GetOsUtcTime( struct tm * tim )
{
  time_t utc_time;
  time(&utc_time);
  *tim = *gmtime( &utc_time );
  tim->tm_mon++;
  tim->tm_year += 1900;
}
