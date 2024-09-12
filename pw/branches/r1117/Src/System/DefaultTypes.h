#ifndef _DEFAULT_TYPES_H_
#define _DEFAULT_TYPES_H_

#include "System/config.h"

#include <stdio.h>
#include <wchar.h>
#if defined( NV_WIN_PLATFORM )
#include <stdlib.h>
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char byte;

#ifdef WIN32
	typedef __int64 int64;			// due to lack of 'long long' type support
	typedef unsigned __int64 QWORD;		// quad word
#else
	typedef long long int64;		// due to lack of 'long long' type support
	typedef unsigned long long QWORD;	// quad word
#endif

typedef QWORD uint64;

namespace ni_detail
{

  typedef unsigned char		Byte;

  typedef char			SInt8;
  typedef short			SInt16;
  typedef int			SInt32;
  typedef int64			SInt64;

  typedef unsigned char		UInt8;
  typedef unsigned short	UInt16;
  typedef unsigned int		UInt32;
  typedef QWORD			UInt64;

} //namespace detail

typedef unsigned short ushort;

#ifndef _interface
	#define _interface struct
#endif // _interface

#ifdef WIN32
	#define CCDECL __cdecl
	#define RETARG _Ret_bytecap_(_Size)
#else
	// The cdecl calling convention is native in gcc
#ifndef CCDECL
	#define CCDECL
#endif
	//In last GCC version alloc_size is "known"...
	//#define RETARG    __attribute__ ((alloc_size(1)))
	#define RETARG
#endif

#if defined( NV_WIN_PLATFORM )

	inline uint64 wcstoi64(wchar_t const *str)
	{
		return _wcstoi64(str, NULL, 10);
	}

	inline uint64 wcstoui64(wchar_t const *str)
	{
		return _wcstoui64(str, NULL, 10);
	}

#elif defined( NV_LINUX_PLATFORM )

	static int64 wcstoi64(wchar_t const *str)
	{
		int64 value = 0;
		if (swscanf(str, L"%I64i", &value) > 0)
			return value;

		return 0;
	}

	static uint64 wcstoui64(wchar_t const *str)
	{
		uint64 value = 0;
		if (swscanf(str, L"%I64u", &value) > 0)
			return value;

		return 0;
	}

#endif

#endif

