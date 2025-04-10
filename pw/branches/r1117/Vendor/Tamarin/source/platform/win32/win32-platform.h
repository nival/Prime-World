/* -*- tab-width: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __avmplus_win32_platform__
#define __avmplus_win32_platform__

/**
 * We have avmplus.vcproj compiled with the /W4 warning level
 * which is quite picky.  Disable warnings we don't care about.
 */
#ifdef _MSC_VER
	#pragma warning(disable:4201) // nonstandard extension used : nameless struct/union
	#pragma warning(disable:4512) // assignment operator could not be generated
	#pragma warning(disable:4511) // can't generate copy ctor
	#pragma warning(disable:4127) // conditional expression is constant - appears to be compiler noise primarily
	#pragma warning(disable:4611) // interaction between _setjmp and destruct
	#pragma warning(disable:4725) // instruction may be inaccurate on some Pentiums
	#pragma warning(disable:4611) // interaction between '_setjmp' and C++ object destruction is non-portable
	#pragma warning(disable:4251) // X needs to have dll-interface to be used by clients of class Y

	// enable some that are off even in /W4 mode, but are still handy
	#pragma warning(default:4265)	// 'class' : class has virtual functions, but destructor is not virtual
	#pragma warning(default:4905)	// wide string literal cast to 'LPSTR'
	#pragma warning(default:4906)	// string literal cast to 'LPWSTR'
	#pragma warning(default:4263)	// 'function' : member function does not override any base class virtual member function
	#pragma warning(default:4264)	// 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden
	#pragma warning(default:4266)	// 'function' : no override available for virtual member function from base 'type'; function is hidden
	#pragma warning(default:4242)   // 'identifier' : conversion from 'type1' to 'type2', possible loss of data
	#pragma warning(default:4263)   // member function does not override any base class virtual member function
	#pragma warning(default:4296)	// expression is always true (false) (Generally, an unsigned variable was used in a comparison operation with zero.)

	// some that might be useful to turn on someday, but would require too much twiddly code tweaking right now
	//	#pragma warning(error:4820) // 'bytes' bytes padding added after construct 'member_name' (MSFT system headers generate zillions of these, sadly)
#endif

#define VMPI_memcpy			::memcpy
#define VMPI_memset 		::memset	
#define VMPI_memcmp 		::memcmp	
#define VMPI_memmove 		::memmove	
#define VMPI_memchr			::memchr	
#define VMPI_strcmp 		::strcmp
#define VMPI_strcat 		::strcat
#define VMPI_strchr 		::strchr
#define VMPI_strrchr 		::strrchr
#define VMPI_strcpy 		::strcpy
#define VMPI_strlen 		::strlen
#define VMPI_strncat 		::strncat
#define VMPI_strncmp 		::strncmp
#define VMPI_strncpy 		::strncpy
#define VMPI_strtol			::strtol
#define VMPI_strstr			::strstr

#define VMPI_sprintf		::sprintf
#define VMPI_snprintf		::_snprintf
#define VMPI_sscanf			::sscanf

#define VMPI_atoi			::atoi
// these aren't prefixed b/c off winmo/pcre problems with ? : expressions
#define VMPI_tolower 		tolower
#define VMPI_islower		islower
#define VMPI_toupper		toupper
#define VMPI_isupper 		isupper
#define VMPI_isdigit 		isdigit
#define VMPI_isalnum 		isalnum
#define VMPI_isxdigit 		isxdigit
#define VMPI_isspace 		isspace
#define VMPI_isgraph 		isgraph
#define VMPI_isprint 		isprint
#define VMPI_ispunct 		ispunct
#define VMPI_iscntrl 		iscntrl
#define VMPI_isalpha 		isalpha
#ifdef UNDER_CE
	#define VMPI_abort() ::TerminateProcess(GetCurrentProcess(), 0)
#else
	#define VMPI_abort   ::abort
#endif

#define VMPI_exit           ::exit

#ifdef UNDER_CE
	#define vsnprintf ::_vsnprintf
#endif

#include <stddef.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <ctype.h>
#include <limits.h>

#include <windows.h>
#include <malloc.h>

#if defined(UNDER_CE) 
// winmo complains if we try to include <new> and it complains if someone else includes new before us so...
#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void* operator new(size_t, void* p) { return p; }
#endif
#else
// others want the system new
#include <new>
#endif

#ifdef _ARM_
	// Windows Mobile doesn't provide intptr_t or uintptr_t
	typedef __int32				intptr_t; 
	typedef unsigned __int32	uintptr_t; 
#endif

typedef void *maddr_ptr;

// Set up a jmp_buf suitable for VMPI_longjmpNoUnwind.
//#define VMPI_setjmpNoUnwind ::setjmp

// Jump to an active jmp_buf that was set up by VMPI_setjmpNoUnwind.
// Under no circumstances may C++ destructors be unwound during the
// jump (MSVC likes to do this by default).
//#define VMPI_longjmpNoUnwind ::longjmp

#ifdef VMCFG_64BIT
	#include <setjmpex.h>
	extern "C"
	{
		_int64 __cdecl longjmp64(jmp_buf jmpbuf, _int64 arg);
	}
	#define VMPI_setjmpNoUnwind(buf)    ::setjmp(buf)
	#define VMPI_longjmpNoUnwind(buf,n) ::longjmp64(buf,n)
#else
	#include <setjmp.h>
	#define VMPI_setjmpNoUnwind(buf)    ::setjmp(buf)
	#define VMPI_longjmpNoUnwind(buf,n) ::longjmp(buf,n)
#endif

#ifndef UNDER_CE
  // Newer versions of the Windows SDK set up the intrinsics slightly differently
  // than VC8. Only include intrin.h if the SDK doesn't declare it.
  #ifndef InterlockedBitTestAndSet
    #include <intrin.h>
  #endif
  #include <emmintrin.h>

  #ifdef VTUNE
    #include "JITProfiling.h"
  #endif
#endif

// Windows doesn't support inttypes.h or most C99 types directly
typedef __int8				int8_t;
typedef __int16				int16_t;
typedef __int32				int32_t;
typedef __int64				int64_t;
typedef unsigned __int8		uint8_t;
typedef unsigned __int16	uint16_t;
typedef unsigned __int32	uint32_t; 
typedef unsigned __int64	uint64_t;

// This must come after all the include files
#if defined _MSC_VER && !defined DEBUG
	#pragma intrinsic(memcmp)
	#pragma intrinsic(memcpy)
	#pragma intrinsic(memset)
	#pragma intrinsic(strlen)
	#pragma intrinsic(strcpy)
	#pragma intrinsic(strcat)
#endif

#if _MSC_VER
    #define REALLY_INLINE __forceinline
	#define FASTCALL __fastcall
#elif __GNUC__
	#define FASTCALL __attribute__((fastcall))
#else
    #define FASTCALL 
#endif 

#if defined(_MSC_VER)
	#define AVMPLUS_ALIGN8(type) __declspec(align(8)) type
	#define AVMPLUS_ALIGN16(type) __declspec(align(16)) type
#elif defined(__GNUC__)
	#define AVMPLUS_ALIGN8(type) type __attribute__ ((aligned (8)))
	#define AVMPLUS_ALIGN16(type) type __attribute__ ((aligned (16)))
#else
	#error "Unrecognized compiler"
#endif

#if defined(_MSC_VER) && _MSC_VER < 1400 && defined(FEATURE_NANOJIT)
    #define NJ_NO_VARIADIC_MACROS
#endif

/**
* Type defintion for an opaque data type representing platform-defined spin lock 
* @see VMPI_lockInit(), VMPI_lockAcquire()
*/
struct vmpi_spin_lock_t 
{
	volatile LONG lock;
};


REALLY_INLINE void VMPI_lockInit(vmpi_spin_lock_t* lock)
{
	lock->lock = 0;
}

REALLY_INLINE void VMPI_lockDestroy(vmpi_spin_lock_t* lock)
{
	lock->lock = 0;
}

REALLY_INLINE bool VMPI_lockAcquire(vmpi_spin_lock_t *lock)
{
	int tries = 0;
	while (::InterlockedCompareExchange((LPLONG)&lock->lock, 1, 0) != 0)
	{
		++tries;
		// We used to reset to zero if we got to 100. This resets to 0 at 64 instead, with no branch.
		tries &= 63;
		// if tries == 0, we just rolled over 64, so we Sleep(1) to give other threads a chance to run... otherwise we Sleep(0)
		::Sleep(tries == 0);
	}
	return true;
}

REALLY_INLINE bool VMPI_lockRelease(vmpi_spin_lock_t *lock)
{
	::InterlockedExchange((LPLONG)&lock->lock, 0);
	return true;
}

REALLY_INLINE bool VMPI_lockTestAndAcquire(vmpi_spin_lock_t *lock)
{
	return ::InterlockedCompareExchange((LPLONG)&lock->lock, 1, 0) == 0;
}

#endif // __avmplus_win32_platform__

