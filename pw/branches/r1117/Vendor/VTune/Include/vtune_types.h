/**********************************************************************************************
 * INTEL CONFIDENTIAL
 * Copyright 2002-2008 Intel Corporation All Rights Reserved.
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

#if !defined(__VTUNE_TYPES_H__)
#define __VTUNE_TYPES_H__

#include "vtsa_static_env.h"

//
// Everyone has been including vtune_types.h as a global include
// file, so as we split out the macros and warnings, we need to
// make sure that everyone gets these files too.
// 
#include "vtsa_macros.h"
#include "vtsa_warnings.h"


#if defined(VTSA_OS_WINDOWS)
#pragma once
#elif defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)
// Do they have a "#pragma once" equivilent?
#else
#error "unknown os"
#endif

//
// The only basic types allowed in *.h files going forward will be
// the types listed below. The types give explicit sizes and allows
// for more portability between OSes, architectures and compilers.
// 
// All OS/compiler/architecture differences for the various types
// can be put in this one file and future porting effort can be minimized.
//
//
// The types basic format for the types is U for unsigned and S for signed
// followed by the size in bits. For example, U8 is an unsigned 8-bit type
// while S64 is a signed 64-bit type.
//
// For variable sized types (such as casting a pointer to do math on it), use
// the UIOP and SIOP types. UIOP is an "Unsigned Integer Or Pointer" which will
// be 4 bytes on a 32-bit machine and 8 bytes on a 64-bit machine.
//
// The GENSTRING type is intended to be the beginnings of handling
// localization issues. Future API's should use the GENSTRING type
// so that they can be more easily internationalized in the future.
//
// NOTE: Since we are trying to avoid adding MS'isms and un*x'isms to
// this file, do NOT define things like WORD/DWORD/__u8 etc in this
// file. The goal is to define types which are specific to vtune and
// independant of OS, Architecture, and compiler and then use this
// file to map the vtune types to a particular implementation.
//

typedef void* PVOID;

//
// For String Handling
//
// Allow us to change the definition of STCHAR depending on how we compile
// This will allow for a more gradual migration to localization when we
// are ready... For now, UNICODE tends to be undefined, so we will
// get the char that everyone expects...
//
#if  defined(UNICODE)

#if !defined(SAG_COM)  //only temporary...
#include <wchar.h>
#endif

typedef wchar_t     STCHAR;
#define VTSA_T(x)   L ## x 

#else

typedef char        STCHAR;
#define VTSA_T(x)   x 

#endif

// 
// For API strings ONLY
// All external API's should use VTSA_CHAR which is defined as wchar_t by default
// i.e. by default compile time define VTSA_SETUP_ASCII_ENVIRONMENT is not set
// To enable environments where there is no Unicode support, we can compile
// with VTSA_SETUP_ASCII_ENVIRONMENT to enable ASCII based sampling support
// More details on this in document SEP_string_type_consistent_usage.doc in CVS under doc/design
//
#if defined( VTSA_SETUP_ASCII_ENVIRONMENT )

typedef char VTSA_CHAR;

#else

#if !defined(SAG_COM)  //only temporary...

#if !defined(_WCHAR_T_DEFINED)
#include <wchar.h>
#endif

#endif

typedef wchar_t VTSA_CHAR;

#endif

typedef   signed char       S8;
typedef unsigned char       U8;

typedef   signed short      S16;
typedef unsigned short      U16;

typedef   signed int        S32;
typedef unsigned int        U32;

#if defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)

typedef   signed long long  S64;
typedef unsigned long long  U64;

#elif defined(VTSA_OS_WINDOWS)

typedef   signed __int64    S64;
typedef unsigned __int64    U64;

#else
#error "Unexpected OS seen"
#endif

//
// And the pointer casts
// Designed to be of varying size so that pointers can be
// cast to this type, have math operations done, and then cast
// back into pointers without losing bits.
//
// The names come from:
// Signed Int Or Pointer (SIOP)
// Unsigned Int Or Pointer (UIOP)

#if defined(VTSA_32BIT)

typedef S32                 SIOP;
typedef U32                 UIOP;

#elif defined(VTSA_64BIT)

typedef S64                 SIOP;
typedef U64                 UIOP;

#else 
#error "Unexpected bitsize seen"
#endif


#if !defined(TRUE)
#define TRUE    1
#endif

#if !defined(FALSE)
#define FALSE   0
#endif

typedef U32   VTBOOL;


//
// Define NULL pointer value
//
#if !defined(NULL)

#if defined(__cplusplus)
#define NULL    0
#else
#define NULL    ((void *)0)
#endif

#endif


#endif  // __VTUNE_TYPES_H__

