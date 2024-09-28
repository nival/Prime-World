//
//	cryptolib.signature.h
//
//	Abstract signature algorithm definition.
//


#pragma once


#include "cryptolib.defines.h"


typedef VOID ( CRYPTOLIB_API *PSIGNATURE_INIT )(
		struct _SIGNATURE_ALGORITHM	*alg );

typedef VOID ( CRYPTOLIB_API *PSIGNATURE_PROCESS )(
		struct _SIGNATURE_ALGORITHM	*alg,
	IN	PCVOID						buffer,
	IN	SIZE_T						buffer_size );

typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PSIGNATURE_FINISH_GENERATE )(
		struct _SIGNATURE_ALGORITHM	*alg,
	OUT	PVOID						signature );

typedef BOOLEAN ( CRYPTOLIB_API *PSIGNATURE_FINISH_VERIFY )(
		struct _SIGNATURE_ALGORITHM	*alg,
	IN	PCVOID						signature );

typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PSIGNATURE_GENERATE )(
		struct _SIGNATURE_ALGORITHM	*alg,
	IN	PCVOID						buffer,
	IN	SIZE_T						buffer_size,
	OUT	PVOID						signature );

typedef BOOLEAN ( CRYPTOLIB_API *PSIGNATURE_VERIFY )(
		struct _SIGNATURE_ALGORITHM	*alg,
	IN	PCVOID						buffer,
	IN	SIZE_T						buffer_size,
	IN	PCVOID						signature );


typedef struct _SIGNATURE_ALGORITHM
{
	SIZE_T						signature_bitsize;
	SIZE_T						signature_size;

	PSIGNATURE_INIT				init;
	PSIGNATURE_PROCESS			process;
	PSIGNATURE_FINISH_GENERATE	finish_generate;
	PSIGNATURE_FINISH_VERIFY	finish_verify;
	PSIGNATURE_GENERATE			generate;
	PSIGNATURE_VERIFY			verify;
} SIGNATURE_ALGORITHM, *PSIGNATURE_ALGORITHM;


EXTERN_C
SIZE_T
CRYPTOLIB_API
signature_get_signature_bitsize(
		PSIGNATURE_ALGORITHM	alg );

EXTERN_C
SIZE_T
CRYPTOLIB_API
signature_get_signature_size(
		PSIGNATURE_ALGORITHM	alg );

EXTERN_C
VOID
CRYPTOLIB_API
signature_init(
		PSIGNATURE_ALGORITHM	alg );

EXTERN_C
VOID
CRYPTOLIB_API
signature_process(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
signature_finish_generate(
		PSIGNATURE_ALGORITHM	alg,
	OUT	PVOID					signature );

EXTERN_C
BOOLEAN
CRYPTOLIB_API
signature_finish_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					signature );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
signature_generate(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	OUT	PVOID					signature );

EXTERN_C
BOOLEAN
CRYPTOLIB_API
signature_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	IN	PCVOID					signature );
