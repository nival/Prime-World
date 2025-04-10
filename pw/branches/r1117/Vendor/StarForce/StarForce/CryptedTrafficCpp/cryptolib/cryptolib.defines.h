//
//	cryptolib.defines.h
//
//	Defines for crypto library.
//


#pragma once


//
//	Use this macro to place code to the specific section.
//

//#define CRYPTOLIB_CODE_SECTION PAGE


//
//	Use this macro to avoid relocations in resulting code.
//

//#define CRYPTOLIB_NO_RELOCS


//
//	Use this define only for testing and debugging purposes, remove in release.
//

//#define CRYPTOLIB_DEBUG


//
//	Define macro used for assumption.
//

#define CRYPTOLIB_ASSUME( X ) __assume( X )


//
//	Define macro used for assertion.
//

#define CRYPTOLIB_ASSERT( X ) __noop


//
//	Define macro used for paged code assertion.
//

#define CRYPTOLIB_PAGED_CODE __noop


//
//	Define a calling convention for functions.
//

#ifdef _M_IX86
#define CRYPTOLIB_API __stdcall
#else
#define CRYPTOLIB_API
#endif


//
//	Define the status type.
//

typedef UINT32 CRYPTOLIB_STATUS;


//
//	Define the status values.
//

#define STATUS_CRYPTOLIB_SUCCESS							( ( CRYPTOLIB_STATUS )0x00000000 )
#define STATUS_CRYPTOLIB_ERROR								( ( CRYPTOLIB_STATUS )0xEE020001 )
#define STATUS_CRYPTOLIB_UNKNOWN_HASH_ALGORITHM				( ( CRYPTOLIB_STATUS )0xEE020002 )
#define STATUS_CRYPTOLIB_KEY_NOT_SET						( ( CRYPTOLIB_STATUS )0xEE020003 )
#define STATUS_CRYPTOLIB_INVALID_KEY						( ( CRYPTOLIB_STATUS )0xEE020004 )
#define STATUS_CRYPTOLIB_REPRESENTATIVE_TOO_LARGE			( ( CRYPTOLIB_STATUS )0xEE020005 )
#define STATUS_CRYPTOLIB_OVERFLOW							( ( CRYPTOLIB_STATUS )0xEE020006 )
#define STATUS_CRYPTOLIB_DIVISION_BY_ZERO					( ( CRYPTOLIB_STATUS )0xEE020007 )
#define STATUS_CRYPTOLIB_MESSAGE_TOO_LONG					( ( CRYPTOLIB_STATUS )0xEE020008 )
#define STATUS_CRYPTOLIB_INTENDED_ENCODED_MESSAGE_TOO_SHORT	( ( CRYPTOLIB_STATUS )0xEE020009 )
