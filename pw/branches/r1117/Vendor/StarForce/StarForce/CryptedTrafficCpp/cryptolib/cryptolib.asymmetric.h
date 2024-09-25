//
//	cryptolib.asymmetric.h
//
//	Abstract asymmetric cipher algorithm definition.
//


#pragma once


#include "defines.h"
#include "cryptolib.defines.h"


typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PASYMMETRIC_DO_PUB )(
		struct _ASYMMETRIC_ALGORITHM	*alg,
	IN	PCVOID							input,
	OUT	PVOID							output );

typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PASYMMETRIC_DO_PVT )(
		struct _ASYMMETRIC_ALGORITHM	*alg,
	IN	PCVOID							input,
	OUT	PVOID							output );


typedef struct _ASYMMETRIC_ALGORITHM
{
	SIZE_T	key_bitsize;
	SIZE_T	key_size;

	PASYMMETRIC_DO_PUB	do_pub;
	PASYMMETRIC_DO_PVT	do_pvt;
} ASYMMETRIC_ALGORITHM, *PASYMMETRIC_ALGORITHM;
