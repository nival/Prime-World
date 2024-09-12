/*
 * TypeProxy.h
 *
 *  Created on: 15.10.2008
 *      Author: earnol
 */

#ifndef TYPEPROXY_H_
#define TYPEPROXY_H_
#include "sysapi.h"

#ifndef _interface
  #define _interface struct
#endif // _interface

/**
* This macro uses parameter x.
*    It defined like <br><B>#define NI_USE_PARAM(x) ((x)=(x))</B>
*
* @memo     Use parameter x
* @param    x    parameter to use
* @return   parametr value
* @header   DiTypes.h
*/
#ifndef NI_USE_PARAM
  #define NI_USE_PARAM(x)      ((void)(x))
#endif


//define socket types and classes
#ifdef NI_PLATF_WIN
typedef SOCKET NiSocket;
#define NI_SERVER_LOG(a) printf a
#define NI_SERVER_LOG_L2(a)  printf a
#define NI_SERVER_LOG_L5(a)  //printf a
//#define NI_VERIFY(a, b, c)
#endif

#ifdef NI_PLATF_LINUX
typedef  int   NiSocket;
#define NI_SERVER_LOG(a)  //syslog(LOG_NOTICE, a)
#define NI_SERVER_LOG_L2(a)  //syslog(LOG_NOTICE, a)
#define NI_SERVER_LOG_L5(a)  //syslog(LOG_NOTICE, a)
#define SOCKET_ERROR  -1
#define NI_ASSERT(cond, msg)   if(!(cond)) printf(msg);
#define NI_ALWAYS_ASSERT(msg)  printf(msg);
#define ASSERT(a)              NI_ASSERT(a, __FILE__)
#define UINT8   unsigned char
#define UINT16  unsigned short int
#define LONG   long
#define DWORD   unsigned int
#define NI_VERIFY(a, b, c)
#endif

#ifdef NI_PLATF_WIN
  #include <errno.h>
  #include "Win32/Thread.h"
  #include "Win32/Semaphore.h"
  #include "Win32/Mutex.h"
  #include <sys/types.h>
  #include <sys/stat.h>

  #include "../System/Asserts.h"
  #include "../System/nlist.h"
  #include "../System/nvector.h"
  #include "../System/nstring.h"
  using namespace nstl;
  #include "../System/StrProc.h"
  #include "../System/Logger.h"
  #include "../System/LoggerStream.h"
  #include "../System/SystemLog.h"

#else
  #include <sys/errno.h>
  #include "linux/Thread.h"
  #include "linux/Semaphore.h"
  #include "linux/Mutex.h"
#endif

#include "../System/nlist.h"
#include "../System/nstring.h"

template <typename CT, typename valT>
static CT* int_itoa(valT value, CT* result, int base )
{
  // check that the base if valid
  if (base < 2 || base > 16) { *result = L'\0'; return result; }
  CT* out = result;
  valT quotient = value;
  do
  {
    valT remn = quotient % base;
    if(remn < 0)
      remn = -remn;
    *out = L"0123456789abcdef"[remn];
    ++out;
    quotient /= base;
  } while ( quotient );
  // Only apply negative sign for base 10
  if(value < 0 && base == 10) *out++ = L'-';

  nstl::reverse(result, out);

  *out = L'\0';
  return result;
}

#ifndef mabs
  #define mabs(a) (((a)<0)?(-(a)):(a))
#endif

#ifdef NI_PLATF_LINUX

#ifndef min
  #define min(a, b) (((a)<(b))?(a):(b))
#endif

inline long InterlockedExchangeAdd( volatile long * Addend, long Increment )
{
long ret;
__asm__ (
/* lock for SMP systems */
"lock\n\t"
"xaddl %0,(%1)"
:"=r" (ret)
:"r" (Addend), "0" (Increment)
:"memory" );
return ret;
}

inline long InterlockedIncrement( volatile long* Addend )
{
return InterlockedExchangeAdd( Addend, 1 );
}

inline long InterlockedDecrement( volatile long* Addend )
{
return InterlockedExchangeAdd( Addend, -1 );
}

inline long InterlockedCompareExchange(volatile long *dest, long exch, long comp)
{
long old;

__asm__ __volatile__ ("lock; cmpxchgl %2, %0"
: "=m" (*dest), "=a" (old)
: "r" (exch), "m" (*dest), "a" (comp));
return(old);
}

inline long InterlockedExchange(long* volatile Target, long Value)
{
long ReturnValue;

__asm __volatile(
"lock xchgl %2,(%1)"
: "=r" (ReturnValue)
: "r" (Target), "0" (Value)
: "memory");

return ReturnValue;
}
#endif //NI_PLATF_LINUX

#endif /* TYPEPROXY_H_ */
