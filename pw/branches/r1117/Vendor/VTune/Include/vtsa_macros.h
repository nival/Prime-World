/**********************************************************************************************
 * INTEL CONFIDENTIAL
 * Copyright 2004-2008 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to the source code
 * ("Material") are owned by Intel Corporation or its suppliers or licensors. Title to the
 * Material remains with Intel Corporation or its suppliers and licensors. The Material
 * contains trade secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright and trade secret
 * laws and treaty provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or disclosed in any way
 * without Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual property right
 * is granted to or conferred upon you by disclosure or delivery of the Materials, either
 * expressly, by implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in writing.
 */

#ifndef __VTSA_MACROS_H__
#define __VTSA_MACROS_H__

#include "vtsa_static_env.h"

#if defined(VTSA_OS_WINDOWS)
#pragma once
#elif defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)
// Do they have a "#pragma once" equivilent?
#else
#error "unknown os"
#endif


//
// VTSA_UNALIGNED is to be used for indicating a pointer is unaligned
// in the future if we need to expand this to differentiate between
// windows, linux, darwin, etc. don't forget to update this macro
//
// Note that the following is really only for windows ia32 compilation
//

#if defined(VTSA_32BIT)

#define VTSA_UNALIGNED

#elif defined(VTSA_64BIT)

#define VTSA_UNALIGNED __unaligned

#else
#error "Unexpected bitsize seen"
#endif




//
// VERIFY_SIZEOF let's you insert a compile-time check that the size of a data
// type (e.g. a struct) is what you think it should be.  Usually it is
// important to know what the actual size of your struct is, and to make sure
// it is the same across all platforms.  So this will prevent the code from
// compiling if something happens that you didn't expect, whether it's because
// you counted wring, or more often because the compiler inserted padding that
// you don't want.
//
// NOTE: 'elem' and 'size' must both be identifier safe, e.g. matching the
// regular expression /^[0-9a-zA-Z_]$/.
//
// Example:
//   typedef struct { void *ptr; int data; } mytype;
//   VERIFY_SIZEOF(mytype, 8);
//                         ^-- this is correct on 32-bit platforms, but fails
//                             on 64-bit platforms, indicating a possible
//                             portability issue.
//
#define VERIFY_SIZEOF(type, size) \
    enum { sizeof_ ## type ## _eq_ ## size = 1 / (int)(sizeof(type) == size) }


//
// __TIMESTAMP__ normally indicates the modification
// time of a file, but not all compilers support that. For
// those that don't, just use the current compile time
//
#define DATE_TIME __DATE__" "__TIME__


#if !defined(__TIMESTAMP__)
#define __TIMESTAMP__   DATE_TIME
#endif

//
// This is the standard method we are using for all (new) exported
// functions. We are avoiding dllimport/dllexport due to added complexity
// when working with static libraries.
//
// Header files which export functions should look like:
// VTSA_API
// type VTSA_APICALL foo(args);
//
// This allows us to add declspec import/export later (via VTSA_API)
// and setup the standard calling convention (via VTSA_APICALL).
// See sampling.h for an example.
//
#if defined(VTSA_OS_WINDOWS)

//
// As mentioned above, we aren't dealing with dllimport/dllexport
// going forward. By definition, VTSA_API can only be used
// on C exports (not C++), but since C exports is where
// we are going in the future, that makes sense...
//
#if defined(SEP_EXPORTS)
#define VTSA_API __declspec(dllexport)
#else
#define VTSA_API __declspec(dllimport)
#endif

#define SAMPUTIL_APICALL __stdcall
#if defined(SAMPUTIL_STATIC)
#define SAMPUTIL_API
#else
#if defined(SAMPUTIL_EXPORTS)
#define SAMPUTIL_API __declspec(dllexport)
#else
#define SAMPUTIL_API __declspec(dllimport)
#endif
#endif

//
// All DLL exports are (by convention) stdcall in windows
//
#define VTSA_APICALL __stdcall

#elif defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)
//
// linux and darwin don't care about all that dll complexity...
//
#define VTSA_API
#define VTSA_APICALL
#define UNREFERENCED_PARAMETER(param)
#define SAMPUTIL_API
#define SAMPUTIL_APICALL

#else
#error "Unknown OS"
#endif


//
// These are useful for nops for function prototypes to help
// a code reviewer determine the intent of function arguments.
// They are advisory only...
//
// An example of their use would be:
//
//
// S32 foo(
//        IN VTSA_CHAR *path,
//        OUT U64 *pValue);
//
//
// In this case, the function prototype makes it obvious that the keyPath
// and keyName parameters are input only and the pValue parameter is only
// used for output. Once again, this is advisory only and it is up to
// the implementer to make sure the prototype does not mis-lead
// other programmers.
//
//
#if !defined(IN)
#define IN
#endif

#if !defined(OUT)
#define OUT
#endif

#if !defined(INOUT)
#define INOUT
#endif

#if !defined(OPTIONAL)
#define OPTIONAL
#endif


//
// Format string macros - FSI64RAW, FSS64, FSS64, FSX64
//
// Provides a portable way to use 64-bit numbers in format strings for printf,
// sprintf, scanf, etc.  The macros use string concatenation to insert to
// proper modifiers.  The basic macros (FSS64, FSU64, FSX64) do not allow for
// any modifers for width, padding, etc., but if you need those you can revert
// to the FSI64RAW macro as a format modifier.
//
// Similar macros are also provided for printing SIOPs and UIOPs, due to the
// ambiguity of their bitsize - FSIOPRAW, FSSIOP, FSUIOP, FSXIOP.
//
// Examples:
//   printf("My number is "FSU64" - do you like it?\n", (U64)9876543210);
//   printf("My number in hex is 0x%016"FSI64RAW"X.\n", (U64)9875643210);
//
// Mnemonics:
//   FS: format string
//   S:  signed
//   U:  unsigned
//   X:  unsigned hex
//

#if defined(VTSA_OS_LINUX)

#define FSI64RAW "ll"

#elif defined(VTSA_OS_WINDOWS)

#define FSI64RAW "I64"

#else
#error "Unexpected OS seen"
#endif

#define FSS64 "%"FSI64RAW"d"
#define FSU64 "%"FSI64RAW"u"
#define FSX64 "%"FSI64RAW"x"


#if defined(VTSA_32BIT)

#define FSIOPRAW

#elif defined(VTSA_64BIT)

#define FSIOPRAW FSI64RAW

#else
#error "Unexpected bitsize seen"
#endif

#define FSSIOP "%"FSIOPRAW"d"
#define FSUIOP "%"FSIOPRAW"u"
#define FSXIOP "%"FSIOPRAW"x"


//
// Format string macros - CONST_S64(val) & CONST_U64(val)
//
// Provides a portable way to use 64-bit numbers in constants.
//
// Mnemonics:
//   S:  signed
//   U:  unsigned
//

#if defined(VTSA_OS_LINUX)

#define CONST_I64RAW LL

#elif defined(VTSA_OS_WINDOWS)

#define CONST_I64RAW I64

#else
#error "Unexpected OS seen"
#endif

#define CONCAT(a,b) a##b
#define XCONCAT(a,b) CONCAT(a,b)

#define CONST_S64(val)	XCONCAT(val, CONST_I64RAW)
#define CONST_U64(val)	XCONCAT(XCONCAT(val, U), CONST_I64RAW)


#endif  // __VTSA_MACROS_H__
