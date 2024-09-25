//
//	cryptolib.hash.h
//
//	Abstract hash algorithm definition.
//


#pragma once


#include "cryptolib.defines.h"


//
//	Define hash algorithm IDs.
//

#define MD5_ALGORITHM_ID	1
#define SHA1_ALGORITHM_ID	2
#define SHA512_ALGORITHM_ID	3


//
//	Define minimum and maximum hash sizes.
//

#define HASH_MIN_BITSIZE	128  // MD5 is the minimum
#define HASH_MIN_SIZE		( HASH_MIN_BITSIZE / 8 )
#define HASH_MAX_BITSIZE	512  // SHA512 is the maximum
#define HASH_MAX_SIZE		( HASH_MAX_BITSIZE / 8 )


typedef VOID ( CRYPTOLIB_API *PHASH_INIT )(
		struct _HASH_ALGORITHM	*alg );

typedef VOID ( CRYPTOLIB_API *PHASH_PROCESS )(
		struct _HASH_ALGORITHM	*alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size );

typedef VOID ( CRYPTOLIB_API *PHASH_FINISH )(
		struct _HASH_ALGORITHM	*alg,
	OUT	PVOID					hash );

typedef VOID ( CRYPTOLIB_API *PHASH_COMPUTE )(
		struct _HASH_ALGORITHM	*alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	OUT	PVOID					hash );


typedef struct _HASH_ALGORITHM
{
	UINT32			id;

	SIZE_T			hash_bitsize;
	SIZE_T			hash_size;

	PHASH_INIT		init;
	PHASH_PROCESS	process;
	PHASH_FINISH	finish;
	PHASH_COMPUTE	compute;
} HASH_ALGORITHM, *PHASH_ALGORITHM;
