/*************************************************************************
 *
 *              INTEL CORPORATION PROPRIETARY INFORMATION
 *  This software is supplied under the terms of a license agreement or
 *  nondisclosure agreement with Intel Corporation and may not be copied
 *  or disclosed except in accordance with the terms of that agreement.
 *
 *    Copyright(c) 2002-2007 Intel Corporation. All Rights Reserved.
 *
 ************************************************************************/

#ifndef _VTUNEAPITYPES_H_
#define _VTUNEAPITYPES_H_

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
// For varialbe sized types (such as casting a pointer to do math on it), use
// the UIOP and SIOP types. UIOP is an "Unsigned Integer Or Pointer" which will
// be 4 bytes on a 32-bit machine and 8 bytes on a 64-bit machine.
//
// The GENSTRING type is intended to be the beginnings of handling
// localization issues. Future API's should use the GENSTRING type
// so that they can be more easily internationalized in the future.
//
// NOTE: Since we are trying to avoid adding MS'isms and un*x'isms to
// this file, do NOT define things like WORD/DWORD/__u8 etc in this
// file. The goal is to define types which are specific to VTune(TM) analyzer and
// independant of OS, Architecture, and compiler and then use this
// file to map the types to a particualar implemenation.
//

typedef void* PVOID;

typedef unsigned short* GENSTRING;

typedef   signed char       S8;
typedef unsigned char       U8;

typedef   signed short      S16;
typedef unsigned short      U16;

typedef   signed int        S32;
typedef unsigned int        U32;

#ifdef __linux__
typedef   signed long long  S64;
typedef unsigned long long  U64;
#else
typedef   signed __int64    S64;
typedef unsigned __int64    U64;
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

#if defined(_M_IX86) || defined(__i386__)
typedef S32                 SIOP;
typedef U32                 UIOP;
#elif defined(_M_IA64) || defined(__ia64__)
typedef S64                 SIOP;
typedef U64                 UIOP;
#elif defined(_M_AMD64) || defined(__x86_64__)
typedef S64                 SIOP;
typedef U64                 UIOP;
#else
#error "Unknown architecture detected"
#endif

#if !defined(TRUE)
#define TRUE    1
#endif

#if !defined(FALSE)
#define FALSE   0
#endif

//
// Define NULL pointer value
//
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

//
// These are useful for nops for function prototypes to help
// a code reviewer determine the intent of function arguments.
// They are advisery only...
//
// An example of their use would be:
//
//
// NTSTATUS  GetU64RegistryValue(
//        IN GENSTR keyPath,
//        IN GENSTR keyName,
//        OUT U64 *pValue);
//
//
// In this case, the function prototype makes it obvious that the keyPath
// and keyName parameters are input only and the pValue parameter is only
// used for output. Once again, this is avisory only and it is up to
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

#endif

/* vim: set ts=8 sw=4 sts=4 et : */
