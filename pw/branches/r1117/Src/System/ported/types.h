#ifndef __TYPES_H_INCLUDED__618004__
#define __TYPES_H_INCLUDED__618004__

#include "System/config.h"
#include "System/types.h"

#if defined( NV_LINUX_PLATFORM )

	#include <limits.h>

	typedef nival::uint8_t	BYTE;
	typedef nival::uint16_t	WORD;
	typedef nival::uint32_t	DWORD;
	typedef int				BOOL;
	typedef nival::uint_t	UINT;
	typedef nival::uint64_t	UINT64;

	typedef nival::int64_t	__int64;

	typedef char			TCHAR;

	typedef nival::str_t	LPSTR;
	typedef nival::cstr_t	LPCSTR;

	typedef nival::wstr_t	LPWSTR;
	typedef nival::cwstr_t	LPCWSTR;

	typedef void *			PVOID;
	typedef void *			LPVOID;

	typedef BOOL *			LPBOOL;

	#define __forceinline	inline
	#define TRUE			1
	#define FALSE			0

	#if !defined( _cdecl )
		#define _cdecl
	#endif

	struct GUID {

		DWORD	Data1;
		WORD	Data2;
		WORD	Data3;
		BYTE	Data4[ 8 ];

	};

	typedef GUID		UUID;

	typedef int			HRESULT;
	typedef int			errno_t;

	#define _I64_MIN ( -9223372036854775807ll - 1 )
	#define _I64_MAX 9223372036854775807ll
	#define _UI64_MAX 0xffffffffffffffffull

	#if !defined( MAX_PATH )
		#define MAX_PATH PATH_MAX
	#endif

	enum { NV_INFINITE = -1 };

	enum {
		THREAD_PRIORITY_LOWEST  = -2,
		THREAD_PRIORITY_NORMAL  = 0,
		THREAD_PRIORITY_HIGHEST = 2
	};

#endif // defined( NV_LINUX_PLATFORM )
#endif // __TYPES_H_INCLUDED__618004__

