//
//	cryptolib.rsa.h
//
//	RSA asymmetric cipher algorithm implementation.
//


#pragma once

#include "defines.h"
#include "cryptolib.defines.h"
#include "cryptolib.asymmetric.h"


typedef UINT32 RSA_UNIT;
typedef UINT64 RSA_DUNIT;

typedef RSA_UNIT *PRSA_UNIT;
typedef CONST RSA_UNIT *PCRSA_UNIT;
typedef RSA_DUNIT *PRSA_DUNIT;
typedef CONST RSA_DUNIT *PCRSA_DUNIT;


#define RSA_UNIT_MAX		( ( RSA_UNIT )-1 )
#define RSA_UNIT_BITSIZE	( sizeof( RSA_UNIT ) * 8 )
#define RSA_UNIT_SIZE		( sizeof( RSA_UNIT ) )

#define RSA_DUNIT_MAX		( ( RSA_DUNIT )-1 )
#define RSA_DUNIT_BITSIZE	( sizeof( RSA_DUNIT ) * 8 )
#define RSA_DUNIT_SIZE		( sizeof( RSA_DUNIT ) )

#define RSA_KEY_MIN_BITSIZE		64
#define RSA_KEY_MAX_BITSIZE		2048
#define RSA_KEY_MIN_SIZE		( RSA_KEY_MIN_BITSIZE / 8 )
#define RSA_KEY_MAX_SIZE		( RSA_KEY_MAX_BITSIZE / 8 )
#define RSA_KEY_MIN_UNITSIZE	( RSA_KEY_MIN_SIZE / RSA_UNIT_SIZE )
#define RSA_KEY_MAX_UNITSIZE	( RSA_KEY_MAX_SIZE / RSA_UNIT_SIZE )

#define RSA_NUMBER_BITSIZE	( ( RSA_KEY_MAX_BITSIZE * 2 ) + ( RSA_UNIT_BITSIZE * 2 ) )
#define RSA_NUMBER_SIZE		( RSA_NUMBER_BITSIZE / 8 )
#define RSA_NUMBER_UNITSIZE	( RSA_NUMBER_SIZE / RSA_UNIT_SIZE )


typedef struct _RSA_NUMBER
{
	SIZE_T		len;
	RSA_UNIT	num[ RSA_NUMBER_UNITSIZE ];
} RSA_NUMBER, *PRSA_NUMBER;
typedef const RSA_NUMBER *PCRSA_NUMBER;

typedef struct _RSA_STACK_FRAME
{
	struct
	{
		RSA_NUMBER	i;
		RSA_NUMBER	o;
	} do_pub;

	struct
	{
		RSA_NUMBER	i;
		RSA_NUMBER	o;
	} do_pvt;

	struct
	{
		RSA_NUMBER	i2;
	} number_mod_exp;

	union
	{
		struct
		{
			RSA_NUMBER	t;
		} number_mul;

		struct
		{
			RSA_NUMBER	c;
			RSA_NUMBER	t;
		} number_mod;
	};
} RSA_STACK_FRAME, *PRSA_STACK_FRAME;

typedef struct _RSA_ALGORITHM
{
	ASYMMETRIC_ALGORITHM	alg;

	RSA_NUMBER				key_modulus;
	RSA_NUMBER				key_pub_exponent;
	RSA_NUMBER				key_pvt_exponent;
	RSA_NUMBER				key_p;
	RSA_NUMBER				key_q;
	RSA_NUMBER				key_dp;
	RSA_NUMBER				key_dq;
	RSA_NUMBER				key_inverse_q;

	RSA_STACK_FRAME			stack_frame;
} RSA_ALGORITHM, *PRSA_ALGORITHM;


typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PRSA_ALG_CREATE_NO_RELOCS )(
		PRSA_ALGORITHM		rsa_alg,
	IN	SIZE_T				key_bitsize,
	IN	PCVOID				key_modulus,
	IN	PCVOID				key_pub_exponent,
	IN	PCVOID				key_pvt_exponent,
	IN	PCVOID				key_p,
	IN	PCVOID				key_q,
	IN	PCVOID				key_dp,
	IN	PCVOID				key_dq,
	IN	PCVOID				key_inverse_q,
	IN	PASYMMETRIC_DO_PUB	fn_do_pub,
	IN	PASYMMETRIC_DO_PVT	fn_do_pvt );

typedef VOID ( CRYPTOLIB_API *PRSA_ALG_DELETE )(
		PRSA_ALGORITHM		rsa_alg );


EXTERN_C
SIZE_T
CRYPTOLIB_API
rsa_alg_get_size(
	VOID );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
rsa_alg_create_no_relocs(
		PRSA_ALGORITHM		rsa_alg,
	IN	SIZE_T				key_bitsize,
	IN	PCVOID				key_modulus,
	IN	PCVOID				key_pub_exponent,
	IN	PCVOID				key_pvt_exponent,
	IN	PCVOID				key_p,
	IN	PCVOID				key_q,
	IN	PCVOID				key_dp,
	IN	PCVOID				key_dq,
	IN	PCVOID				key_inverse_q,
	IN	PASYMMETRIC_DO_PUB	fn_do_pub,
	IN	PASYMMETRIC_DO_PVT	fn_do_pvt );

#ifndef CRYPTOLIB_NO_RELOCS
EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
rsa_alg_create(
		PRSA_ALGORITHM	rsa_alg,
	IN	SIZE_T			key_bitsize,
	IN	PCVOID			key_modulus,
	IN	PCVOID			key_pub_exponent,
	IN	PCVOID			key_pvt_exponent,
	IN	PCVOID			key_p,
	IN	PCVOID			key_q,
	IN	PCVOID			key_dp,
	IN	PCVOID			key_dq,
	IN	PCVOID			key_inverse_q );
#endif

EXTERN_C
VOID
CRYPTOLIB_API
rsa_alg_delete(
		PRSA_ALGORITHM	rsa_alg );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
rsa_do_pub(
		PASYMMETRIC_ALGORITHM	alg,
	IN	PCVOID					input,
	OUT	PVOID					output );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
rsa_do_pvt(
		PASYMMETRIC_ALGORITHM	alg,
	IN	PCVOID					input,
	OUT	PVOID					output );
