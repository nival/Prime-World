//
//	cryptolib.sha1.h
//
//	SHA1 hash algorithm implementation.
//


#pragma once


#include "cryptolib.defines.h"
#include "cryptolib.hash.h"


#define SHA1_HASH_BITSIZE	160
#define SHA1_HASH_SIZE		( SHA1_HASH_BITSIZE / 8 )


typedef struct _SHA1_STATE
{
	UINT32	value[ 5 ];
	UINT64	count;
	UINT8	buffer[ 64 ];
} SHA1_STATE, *PSHA1_STATE;

typedef struct _SHA1_ALGORITHM
{
	HASH_ALGORITHM	alg;
	SHA1_STATE		state;
} SHA1_ALGORITHM, *PSHA1_ALGORITHM;


typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PSHA1_ALG_CREATE_NO_RELOCS )(
		PSHA1_ALGORITHM	sha1_alg,
	IN	PHASH_INIT		fn_init,
	IN	PHASH_PROCESS	fn_process,
	IN	PHASH_FINISH	fn_finish,
	IN	PHASH_COMPUTE	fn_compute );

typedef VOID ( CRYPTOLIB_API *PSHA1_ALG_DELETE )(
		PSHA1_ALGORITHM	sha1_alg );


EXTERN_C
SIZE_T
CRYPTOLIB_API
sha1_alg_get_size(
	VOID );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
sha1_alg_create_no_relocs(
		PSHA1_ALGORITHM	sha1_alg,
	IN	PHASH_INIT		fn_init,
	IN	PHASH_PROCESS	fn_process,
	IN	PHASH_FINISH	fn_finish,
	IN	PHASH_COMPUTE	fn_compute );

#ifndef CRYPTOLIB_NO_RELOCS
EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
sha1_alg_create(
		PSHA1_ALGORITHM	sha1_alg );
#endif

EXTERN_C
VOID
CRYPTOLIB_API
sha1_alg_delete(
		PSHA1_ALGORITHM	sha1_alg );

EXTERN_C
VOID
CRYPTOLIB_API
sha1_init(
		PHASH_ALGORITHM	alg );

EXTERN_C
VOID
CRYPTOLIB_API
sha1_process(
		PHASH_ALGORITHM	alg,
	IN	PCVOID			buffer,
	IN	SIZE_T			buffer_size );

EXTERN_C
VOID
CRYPTOLIB_API
sha1_finish(
		PHASH_ALGORITHM	alg,
	OUT	PVOID			hash );

EXTERN_C
VOID
CRYPTOLIB_API
sha1_compute(
		PHASH_ALGORITHM	alg,
	IN	PCVOID			buffer,
	IN	SIZE_T			buffer_size,
	OUT	PVOID			hash );
