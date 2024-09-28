#include "stdafx.h"


#include "TimeUtils.h"

void GetOsLocalTime(struct tm *tim)
{
  time_t t;
  time(&t);
  localtime_s( tim, &t);
  tim->tm_mon++;
  tim->tm_year += 1900;
}



void GetOsUtcTime( struct tm * tim )
{
  time_t t;
  time(&t);
  *tim = *gmtime( &t );
  tim->tm_mon++;
  tim->tm_year += 1900;
}
