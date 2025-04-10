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

#ifndef __avmplus_system_selection__
#define __avmplus_system_selection__

// Standard operating system, CPU, word size, and endianness selection
// for tier-one AVM platforms.  This file defines all the AVMSYSTEM_
// names.  It would normally be included into a feature definition file.

// operating system

#ifdef UNIX
  #define AVMSYSTEM_UNIX 1
#else
  #define AVMSYSTEM_UNIX 0
#endif
#ifdef _MAC
  #define AVMSYSTEM_MAC  1
#else
  #define AVMSYSTEM_MAC  0
#endif
#ifdef WIN32
  #define AVMSYSTEM_WIN32 1
#else
  #define AVMSYSTEM_WIN32 0
#endif
#ifdef __SYMBIAN32__ // defined by Symbian S60 tool chain
  #define AVMSYSTEM_SYMBIAN 1
#else
  #define AVMSYSTEM_SYMBIAN 0
#endif

#ifdef WEBOS
  #define AVMSYSTEM_WEBOS 1
#else
  #define AVMSYSTEM_WEBOS 0
#endif

// cpu, word size

#undef SIXTYFOURBIT

#if AVMSYSTEM_MAC || AVMSYSTEM_UNIX

  #if defined(__i386__) || defined(__i386)
    #define AVMSYSTEM_IA32   1
  #else
    #define AVMSYSTEM_IA32   0 
  #endif

  #if defined(__x86_64__)
    #define AVMSYSTEM_AMD64  1
    #define SIXTYFOURBIT
  #else
    #define AVMSYSTEM_AMD64  0
  #endif

  #if defined(__ppc__) || defined(__powerpc__) || (__ppc64__) || (__powerpc64__)
    #define AVMSYSTEM_PPC    1
    #if (__ppc64__) || (__powerpc64__)
      #define SIXTYFOURBIT
    #endif
  #else
    #define AVMSYSTEM_PPC    0
  #endif

  #if defined(__arm__) || defined(__ARM__)
    #define AVMSYSTEM_ARM    1
  #else
    #define AVMSYSTEM_ARM    0
  #endif

  #if defined(__sparc__) || defined(__sparc)
    #define AVMSYSTEM_SPARC  1
  #else
    #define AVMSYSTEM_SPARC  0
  #endif

  #if defined(__mips__) || defined(__MIPS__)
    #define AVMSYSTEM_MIPS   1
  #else
    #define AVMSYSTEM_MIPS   0
  #endif

#endif  // mac || unix

#if AVMSYSTEM_WIN32

  #ifdef _M_X64
    #define AVMSYSTEM_AMD64  1
    #define SIXTYFOURBIT
  #else
    #define AVMSYSTEM_AMD64  0
  #endif

  #if defined(_ARM_)
    #define AVMSYSTEM_ARM    1
  #else
    #define AVMSYSTEM_ARM    0
  #endif

  #if !AVMSYSTEM_AMD64 && !AVMSYSTEM_ARM
    #define AVMSYSTEM_IA32 1
  #else
    #define AVMSYSTEM_IA32 0
  #endif

  #define AVMSYSTEM_PPC    0
  #define AVMSYSTEM_SPARC  0
  #define AVMSYSTEM_MIPS   0

#endif  // win32

#if AVMSYSTEM_SYMBIAN

  #define AVMSYSTEM_PPC		0
  #define AVMSYSTEM_AMD64	0
  #define AVMSYSTEM_SPARC	0

  #if defined(__ARMCC__)
    #define AVMSYSTEM_ARM    1
  #else
    #define AVMSYSTEM_ARM    0
  #endif

  #if !AVMSYSTEM_ARM
    #define AVMSYSTEM_IA32 1
  #else
    #define AVMSYSTEM_IA32 0
  #endif

#endif // symbian

#ifdef SIXTYFOURBIT
  #define AVMSYSTEM_32BIT 0
  #define AVMSYSTEM_64BIT 1
#else
  #define AVMSYSTEM_32BIT 1
  #define AVMSYSTEM_64BIT 0
#endif

#undef SIXTYFOURBIT

// endianness

#if AVMSYSTEM_IA32 || AVMSYSTEM_AMD64
  #define AVMSYSTEM_LITTLE_ENDIAN       1
  #define AVMSYSTEM_BIG_ENDIAN          0
#elif AVMSYSTEM_ARM
  #if defined _MSC_VER
    #define AVMSYSTEM_LITTLE_ENDIAN     1
    #define AVMSYSTEM_BIG_ENDIAN        0
  #elif defined __GNUC__
    #if AVMSYSTEM_MAC && AVMSYSTEM_ARM
        #include <machine/endian.h>
        #define __BYTE_ORDER BYTE_ORDER
    #else 
		#include <endian.h>
    #endif
    #if __BYTE_ORDER == LITTLE_ENDIAN
      #define AVMSYSTEM_LITTLE_ENDIAN   1
      #define AVMSYSTEM_BIG_ENDIAN      0
      #if __FLOAT_WORD_ORDER == BIG_ENDIAN
        #define AVMSYSTEM_DOUBLE_MSW_FIRST 1
      #endif
	#else
      #define AVMSYSTEM_LITTLE_ENDIAN   0
      #define AVMSYSTEM_BIG_ENDIAN      1
    #endif
  #elif defined __ARMCC__
    #define AVMSYSTEM_LITTLE_ENDIAN   1
    #define AVMSYSTEM_BIG_ENDIAN      0
  #endif
#elif AVMSYSTEM_PPC || AVMSYSTEM_SPARC
  #define AVMSYSTEM_LITTLE_ENDIAN       0
  #define AVMSYSTEM_BIG_ENDIAN          1
#elif AVMSYSTEM_MIPS
  #if defined __GNUC__
    #include <endian.h>
    #if __BYTE_ORDER == LITTLE_ENDIAN
      #define AVMSYSTEM_LITTLE_ENDIAN   1
      #define AVMSYSTEM_BIG_ENDIAN      0
    #else
      #define AVMSYSTEM_LITTLE_ENDIAN   0
      #define AVMSYSTEM_BIG_ENDIAN      1
    #endif
  #endif
#else
  #error "Error in test to determine endianness"
#endif

#ifndef AVMSYSTEM_DOUBLE_MSW_FIRST
  #define AVMSYSTEM_DOUBLE_MSW_FIRST 0
#endif

#ifndef AVMSYSTEM_ARM_FPU
  #define AVMSYSTEM_ARM_FPU 0
#endif

#endif
