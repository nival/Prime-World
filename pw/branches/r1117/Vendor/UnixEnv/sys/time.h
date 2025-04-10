#pragma once

#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC 1
struct timespec {
  long tv_sec;
  long tv_nsec;
};
#endif /* HAVE_STRUCT_TIMESPEC */

#include <WinSock2.h> //  just for timeval

int sleep(int ms);
void usleep(int waitTime);