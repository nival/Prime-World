//
//	Defines.h
//
//	Description:
//		Base types defines.
//


#pragma once


#define MAX_INT8   ( INT8   )0x7F
#define MIN_INT8   ( INT8   )0x80
#define MAX_INT16  ( INT16  )0x7FFF
#define MIN_INT16  ( INT16  )0x8000
#define MAX_INT32  ( INT32  )0x7FFFFFFF
#define MIN_INT32  ( INT32  )0x80000000
#define MAX_INT64  ( INT64  )0x7FFFFFFFFFFFFFFF
#define MIN_INT64  ( INT64  )0x8000000000000000

#define MAX_UINT8  ( UINT8  )0xFF
#define MIN_UINT8  ( UINT8  )0
#define MAX_UINT16 ( UINT16 )0xFFFF
#define MIN_UINT16 ( UINT16 )0
#define MAX_UINT32 ( UINT32 )0xFFFFFFFF
#define MIN_UINT32 ( UINT32 )0
#define MAX_UINT64 ( UINT64 )0xFFFFFFFFFFFFFFFF
#define MIN_UINT64 ( UINT64 )0

#ifdef _WIN64
#define MAX_SIZE_T ( SIZE_T )MAX_UINT64
#define MIN_SIZE_T ( SIZE_T )MIN_UINT64
#else
#define MAX_SIZE_T ( SIZE_T )MAX_UINT32
#define MIN_SIZE_T ( SIZE_T )MIN_UINT32
#endif

#define BITSIZEOF_UINT8  ( sizeof( UINT8  ) * 8 )
#define BITSIZEOF_UINT16 ( sizeof( UINT16 ) * 8 )
#define BITSIZEOF_UINT32 ( sizeof( UINT32 ) * 8 )
#define BITSIZEOF_UINT64 ( sizeof( UINT64 ) * 8 )
#define BITSIZEOF_SIZE_T ( sizeof( SIZE_T ) * 8 )


#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY( ar ) ( sizeof( ar ) / sizeof( ar[ 0 ] ) )
#endif


#define CONST		const
#define LOCAL		static
#define EXTERN		extern
#define FORCEINLINE	__forceinline
#define STDCALL		__stdcall

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

#ifndef _WINDOWS_
typedef void			 VOID;
typedef char			 CHAR;
typedef	short			 WCHAR;
#endif

typedef VOID                     *PVOID,   **PPVOID;
typedef signed __int8    INT8,   *PINT8,   **PPINT8;
typedef signed __int16   INT16,  *PINT16,  **PPINT16;
typedef signed __int32   INT32,  *PINT32,  **PPINT32;
typedef signed __int64   INT64,  *PINT64,  **PPINT64;
typedef unsigned __int8  UINT8,  *PUINT8,  **PPUINT8;
typedef unsigned __int16 UINT16, *PUINT16, **PPUINT16;
typedef unsigned __int32 UINT32, *PUINT32, **PPUINT32;
typedef unsigned __int64 UINT64, *PUINT64, **PPUINT64;
typedef UINT8            BYTE,   *PBYTE,   **PPBYTE;
typedef CHAR             ACHAR,  *PACHAR,  **PPACHAR;
typedef WCHAR                    *PWCHAR,  **PPWCHAR;
typedef BYTE			 BOOLEAN;   

#if defined(_WIN64)
    typedef __int64 INT_PTR, *PINT_PTR;
    typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

    typedef __int64 LONG_PTR, *PLONG_PTR;
    typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
#else
    typedef int INT_PTR, *PINT_PTR;
    typedef unsigned int UINT_PTR, *PUINT_PTR;

    typedef long LONG_PTR, *PLONG_PTR;
    typedef unsigned long ULONG_PTR, *PULONG_PTR;
#endif

typedef ULONG_PTR			SIZE_T, *PSIZE_T;
typedef LONG_PTR			SSIZE_T, *PSSIZE_T;
typedef SIZE_T						*PSIZE_T, **PPSIZE_T;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif


typedef CONST VOID   *PCVOID,   **PPCVOID;
typedef CONST INT8   *PCINT8,   **PPCINT8;
typedef CONST INT16  *PCINT16,  **PPCINT16;
typedef CONST INT32  *PCINT32,  **PPCINT32;
typedef CONST INT64  *PCINT64,  **PPCINT64;
typedef CONST UINT8  *PCUINT8,  **PPCUINT8;
typedef CONST UINT16 *PCUINT16, **PPCUINT16;
typedef CONST UINT32 *PCUINT32, **PPCUINT32;
typedef CONST UINT64 *PCUINT64, **PPCUINT64;
typedef CONST BYTE   *PCBYTE,   **PPCBYTE;
typedef CONST ACHAR  *PCACHAR,  **PPCACHAR;
typedef CONST WCHAR  *PCWCHAR,  **PPCWCHAR;
typedef CONST ACHAR  *PCASTR,   **PPCASTR;
typedef CONST WCHAR  *PCWSTR,   **PPCWSTR;
