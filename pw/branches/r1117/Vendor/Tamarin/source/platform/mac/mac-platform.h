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

#ifndef __avmplus_mac_platform__
#define __avmplus_mac_platform__

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
#define VMPI_snprintf		::snprintf
#define VMPI_sscanf			::sscanf

#define VMPI_atoi	::atoi
#define VMPI_tolower ::tolower	
#define VMPI_islower ::islower	
#define VMPI_toupper ::toupper	
#define VMPI_isupper ::isupper	
#define VMPI_isdigit ::isdigit	
#define VMPI_isalnum ::isalnum	
#define VMPI_isxdigit ::isxdigit	
#define VMPI_isspace ::isspace	
#define VMPI_isgraph ::isgraph	
#define VMPI_isprint ::isprint	
#define VMPI_ispunct ::ispunct	
#define VMPI_iscntrl ::iscntrl	
#define VMPI_isalpha ::isalpha
#define VMPI_abort   ::abort
#define VMPI_exit    ::exit

// Set up a jmp_buf suitable for VMPI_longjmpNoUnwind.
#define VMPI_setjmpNoUnwind ::setjmp

// Jump to an active jmp_buf that was set up by VMPI_setjmpNoUnwind.
// Under no circumstances may C++ destructors be unwound during the
// jump (MSVC likes to do this by default).
#define VMPI_longjmpNoUnwind ::longjmp

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <ctype.h>
#include <limits.h>

#include <inttypes.h>
#include <alloca.h>

#if defined(AVMPLUS_MAC_CARBON) || defined(AVMPLUS_PPC)
	#include <CoreServices/CoreServices.h>   // for MakeDataExecutable
#endif
#include <mach/mach.h>                   // for vm_protect()
#include <AvailabilityMacros.h>

#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <new>
#include <libkern/OSAtomic.h>

typedef void *maddr_ptr;

#ifdef AVMPLUS_MAC_CARBON
    /**
	 * On Mac Carbon, if you compile with Altivec support,
	 * setjmp is redirected to __vec_setjmp and longjmp is redirected
	 * to __vec_longjmp.  These routines do not gracefully degrade if
	 * the CPU does not have Altivec... they just crash.
	 *
	 * We don't need Altivec support in the places where exceptions
	 * are thrown and caught, so this code forces the setjmp/longjmp
	 * implementation to be the old school, non-Altivec versions.
	 */
    typedef long *jmp_buf[70];
    extern "C"
    {
    	int __setjmp(jmp_buf jmpbuf);
    	void longjmp(jmp_buf jmpbuf, int value);
    }

    #define setjmp __setjmp
#else
    #include <setjmp.h>
#endif

#ifdef __GNUC__
// don't force inlining when debugging, just causes pain.
#  ifdef DEBUG
#    define REALLY_INLINE inline
#  else
#    define REALLY_INLINE inline __attribute__((always_inline))
#  endif
// only define FASTCALL for x86-32; other gcc versions will spew warnings
#  ifdef AVMPLUS_IA32
#    ifndef VMCFG_AOT // Doesn't work with llvm compiler (need a better symbol for this, but don't know one) 
#      define FASTCALL __attribute__((fastcall))
#    endif
#  endif
#endif // __GNUC__

#if defined(__GNUC__)
	#define AVMPLUS_ALIGN8(type) type __attribute__ ((aligned (8)))
	#define AVMPLUS_ALIGN16(type) type __attribute__ ((aligned (16)))
#else
	#error "Unrecognized compiler"
#endif

// "verify" is a Mac thing, it gets in the way of our code
// FIXME: should clean up our code, as this #undef will leak into the AVM embedder's code

#undef verify

/**
* Type defintion for an opaque data type representing platform-defined spin lock 
* @see VMPI_lockInit(), VMPI_lockAcquire()
*/
struct vmpi_spin_lock_t
{
	volatile OSSpinLock lock;
};

REALLY_INLINE void VMPI_lockInit(vmpi_spin_lock_t* lock)
{
	lock->lock = OS_SPINLOCK_INIT;
}

REALLY_INLINE void VMPI_lockDestroy(vmpi_spin_lock_t* lock)
{
	lock->lock = OS_SPINLOCK_INIT;
}

REALLY_INLINE bool VMPI_lockAcquire(vmpi_spin_lock_t* lock)
{
	::OSSpinLockLock((OSSpinLock*)&lock->lock);
	return true;
}

REALLY_INLINE bool VMPI_lockRelease(vmpi_spin_lock_t* lock)
{
	::OSSpinLockUnlock((OSSpinLock*)&lock->lock);
	return true;
}

REALLY_INLINE bool VMPI_lockTestAndAcquire(vmpi_spin_lock_t* lock)
{
	return ::OSSpinLockTry((OSSpinLock*)&lock->lock);
}

#endif // __avmplus_mac_platform__
