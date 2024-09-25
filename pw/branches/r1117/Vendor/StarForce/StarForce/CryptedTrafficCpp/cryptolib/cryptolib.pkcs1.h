//
//	cryptolib.pkcs1.h
//
//	PKCS #1 primitives implementation.
//


#pragma once

#include "defines.h"
#include "cryptolib.defines.h"
#include "cryptolib.rsa.h"
#include "cryptolib.hash.h"
#include "cryptolib.signature.h"


#define STATUS_CRYPTOLIB_PKCS1_UNKNOWN_MGF		( ( CRYPTOLIB_STATUS )0xEE020101 )
#define STATUS_CRYPTOLIB_PKCS1_MASK_TOO_LONG	( ( CRYPTOLIB_STATUS )0xEE020102 )


#define PKCS1_MGF1_ID 1


typedef struct _PKCS1_RSAES_OAEP_STACK_FRAME
{
	union
	{
		struct
		{
			UINT8	db[ RSA_KEY_MAX_SIZE ];
			UINT8	em[ RSA_KEY_MAX_SIZE ];
			UINT8	m[ RSA_KEY_MAX_SIZE ];
			UINT8	c[ RSA_KEY_MAX_SIZE ];
		} rsaes_oaep_encrypt;

		struct
		{
			UINT8	c[ RSA_KEY_MAX_SIZE ];
			UINT8	m[ RSA_KEY_MAX_SIZE ];
			UINT8	em[ RSA_KEY_MAX_SIZE ];
			UINT8	seed[ HASH_MAX_SIZE ];
			UINT8	db[ RSA_KEY_MAX_SIZE - HASH_MIN_SIZE - 1 ];
		} rsaes_oaep_decrypt;
	};
} PKCS1_RSAES_OAEP_STACK_FRAME, *PPKCS1_RSAES_OAEP_STACK_FRAME;


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsaes_oaep_context_get_size(
	VOID );

//
//	PKCS #1 v2.1, Section 7.1.1.
//	RSAES-OAEP-ENCRYPT( ( n, e ), M, L )
//
//	stack_frame		- Pointer to a stack frame to use.
//	rsa_alg			- Pointer to a RSA algorithm to use.
//	hash_alg		- Pointer to a hash algorithm to use.
//	mgf_id			- Mask Generation Function to use.
//	seed			- Pointer to a random seed.  Size of the seed is a hash size of the specified
//						hash algorithm.
//	label			- Pointer to an optional label to be associated with the message.
//	label_size		- Size in bytes of the label.
//	message			- Pointer to a message to be encrypted.
//	message_size	- Size in bytes of the message, where mLen <= k-2hLen-2.
//

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsaes_oaep_encrypt(
		PPKCS1_RSAES_OAEP_STACK_FRAME	stack_frame,
	IN	PRSA_ALGORITHM					rsa_alg,
	IN	PHASH_ALGORITHM					hash_alg,
	IN	UINT32							mgf_id,
	IN	PCVOID							seed,
	IN	PCVOID							label,
	IN	SIZE_T							label_size,
	IN	PCVOID							message,
	IN	SIZE_T							message_size,
	OUT	PVOID							ciphertext );

//
//	PKCS #1 v2.1, Section 7.1.2.
//	RSAES-OAEP-DECRYPT( K, C, L )
//
//	stack_frame		- Pointer to a stack frame to use.
//	rsa_alg			- Pointer to a RSA algorithm to use.
//	hash_alg		- Pointer to a hash algorithm to use.
//	mgf_id			- Mask Generation Function to use.
//	label			- Pointer to an optional label whose association with the message is to be verified.
//	label_size		- Size in bytes of the label.
//	ciphertext		- Pointer to an input ciphertext to be decrypted.
//	message			- Pointer to an output decrypted message.
//	message_size	- Pointer to an output size in bytes of the message, where mLen <= k-2hLen-2.
//

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsaes_oaep_decrypt(
		PPKCS1_RSAES_OAEP_STACK_FRAME	stack_frame,
	IN	PRSA_ALGORITHM					rsa_alg,
	IN	PHASH_ALGORITHM					hash_alg,
	IN	UINT32							mgf_id,
	IN	PCVOID							label,
	IN	SIZE_T							label_size,
	IN	PCVOID							ciphertext,
	OUT	PVOID							message,
	OUT	PSIZE_T							message_size );


//****************************************************************
//	PKCS #1 v2.1 - PSS Signature Algorithm.
//****************************************************************


typedef struct _PKCS1_EMSA_PSS_ENCODE_STACK_FRAME
{
	UINT8	db[ RSA_KEY_MAX_SIZE - HASH_MIN_SIZE - 1 ];
} PKCS1_EMSA_PSS_ENCODE_STACK_FRAME, *PPKCS1_EMSA_PSS_ENCODE_STACK_FRAME;

typedef struct _PKCS1_EMSA_PSS_VERIFY_STACK_FRAME
{
	UINT8	db[ RSA_KEY_MAX_SIZE - HASH_MIN_SIZE - 1 ];
} PKCS1_EMSA_PSS_VERIFY_STACK_FRAME, *PPKCS1_EMSA_PSS_VERIFY_STACK_FRAME;

typedef struct _PKCS1_RSASSA_PSS_STACK_FRAME
{
	union
	{
		struct
		{
			UINT8								em[ RSA_KEY_MAX_SIZE ];
			UINT8								m[ RSA_KEY_MAX_SIZE ];
			UINT8								s[ RSA_KEY_MAX_SIZE ];
			PKCS1_EMSA_PSS_ENCODE_STACK_FRAME	emsa_pss_encode;
		} finish_generate;

		struct
		{
			UINT8								s[ RSA_KEY_MAX_SIZE ];
			UINT8								m[ RSA_KEY_MAX_SIZE ];
			UINT8								em[ RSA_KEY_MAX_SIZE ];
			PKCS1_EMSA_PSS_VERIFY_STACK_FRAME	emsa_pss_verify;
		} finish_verify;
	};
} PKCS1_RSASSA_PSS_STACK_FRAME, *PPKCS1_RSASSA_PSS_STACK_FRAME;

typedef struct _PKCS1_RSASSA_PSS_ALGORITHM
{
	SIGNATURE_ALGORITHM				alg;
	PRSA_ALGORITHM					rsa_alg;
	PHASH_ALGORITHM					hash_alg;
	UINT32							mgf_id;
	PHASH_ALGORITHM					mgf_hash_alg;
	UINT8							salt[ RSA_KEY_MAX_SIZE ];
	SIZE_T							salt_size;
	PKCS1_RSASSA_PSS_STACK_FRAME	stack_frame;
} PKCS1_RSASSA_PSS_ALGORITHM, *PPKCS1_RSASSA_PSS_ALGORITHM;


typedef CRYPTOLIB_STATUS ( CRYPTOLIB_API *PPKCS1_RSASSA_PSS_ALG_CREATE_NO_RELOCS )(
		PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg,
	IN	PRSA_ALGORITHM				rsa_alg,
	IN	PHASH_ALGORITHM				hash_alg,
	IN	UINT32						mgf_id,
	IN	PHASH_ALGORITHM				mgf_hash_alg,
	IN	PCVOID						salt,
	IN	SIZE_T						salt_size,
	IN	PSIGNATURE_INIT				fn_init,
	IN	PSIGNATURE_PROCESS			fn_process,
	IN	PSIGNATURE_FINISH_GENERATE	fn_finish_generate,
	IN	PSIGNATURE_FINISH_VERIFY	fn_finish_verify,
	IN	PSIGNATURE_GENERATE			fn_generate,
	IN	PSIGNATURE_VERIFY			fn_verify );

typedef VOID ( CRYPTOLIB_API *PPKCS1_RSASSA_PSS_ALG_DELETE )(
		PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg );


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsassa_pss_alg_get_size(
	VOID );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_pss_alg_create_no_relocs(
		PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg,
	IN	PRSA_ALGORITHM				rsa_alg,
	IN	PHASH_ALGORITHM				hash_alg,
	IN	UINT32						mgf_id,
	IN	PHASH_ALGORITHM				mgf_hash_alg,
	IN	PCVOID						salt,
	IN	SIZE_T						salt_size,
	IN	PSIGNATURE_INIT				fn_init,
	IN	PSIGNATURE_PROCESS			fn_process,
	IN	PSIGNATURE_FINISH_GENERATE	fn_finish_generate,
	IN	PSIGNATURE_FINISH_VERIFY	fn_finish_verify,
	IN	PSIGNATURE_GENERATE			fn_generate,
	IN	PSIGNATURE_VERIFY			fn_verify );

#ifndef CRYPTOLIB_NO_RELOCS
EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_pss_alg_create(
		PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg,
	IN	PRSA_ALGORITHM				rsa_alg,
	IN	PHASH_ALGORITHM				hash_alg,
	IN	UINT32						mgf_id,
	IN	PHASH_ALGORITHM				mgf_hash_alg,
	IN	PCVOID						salt,
	IN	SIZE_T						salt_size );
#endif

EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_pss_alg_delete(
		PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg );

EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_pss_init(
		PSIGNATURE_ALGORITHM	alg );

EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_pss_process(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_pss_finish_generate(
		PSIGNATURE_ALGORITHM	alg,
	OUT	PVOID					signature );

EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_pss_finish_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					signature );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_pss_generate(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	OUT	PVOID					signature );

EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_pss_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	IN	PCVOID					signature );


//****************************************************************
//	PKCS #1 v2.1 - v1.5 Signature Algorithm.
//****************************************************************


typedef struct _PKCS1_RSASSA_V15_STACK_FRAME
{
	union
	{
		struct
		{
			UINT8	em[ RSA_KEY_MAX_SIZE ];
			UINT8	m[ RSA_KEY_MAX_SIZE ];
			UINT8	s[ RSA_KEY_MAX_SIZE ];
		} finish_generate;

		struct
		{
			UINT8	s[ RSA_KEY_MAX_SIZE ];
			UINT8	m[ RSA_KEY_MAX_SIZE ];
			UINT8	em[ RSA_KEY_MAX_SIZE ];
			UINT8	em_expected[ RSA_KEY_MAX_SIZE ];
		} finish_verify;
	};
} PKCS1_RSASSA_V15_STACK_FRAME, *PPKCS1_RSASSA_V15_STACK_FRAME;

typedef struct _PKCS1_RSASSA_V15_ALGORITHM
{
	SIGNATURE_ALGORITHM				alg;
	PRSA_ALGORITHM					rsa_alg;
	PHASH_ALGORITHM					hash_alg;
	PKCS1_RSASSA_V15_STACK_FRAME	stack_frame;
} PKCS1_RSASSA_V15_ALGORITHM, *PPKCS1_RSASSA_V15_ALGORITHM;


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_get_size(
	VOID );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_create_no_relocs(
		PPKCS1_RSASSA_V15_ALGORITHM	v15_alg,
	IN	PRSA_ALGORITHM				rsa_alg,
	IN	PHASH_ALGORITHM				hash_alg,
	IN	PSIGNATURE_INIT				fn_init,
	IN	PSIGNATURE_PROCESS			fn_process,
	IN	PSIGNATURE_FINISH_GENERATE	fn_finish_generate,
	IN	PSIGNATURE_FINISH_VERIFY	fn_finish_verify,
	IN	PSIGNATURE_GENERATE			fn_generate,
	IN	PSIGNATURE_VERIFY			fn_verify );

#ifndef CRYPTOLIB_NO_RELOCS
EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_create(
		PPKCS1_RSASSA_V15_ALGORITHM	v15_alg,
	IN	PRSA_ALGORITHM				rsa_alg,
	IN	PHASH_ALGORITHM				hash_alg );
#endif

EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_delete(
		PPKCS1_RSASSA_V15_ALGORITHM	v15_alg );

EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_v15_init(
		PSIGNATURE_ALGORITHM	alg );

EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_v15_process(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_finish_generate(
		PSIGNATURE_ALGORITHM	alg,
	OUT	PVOID					signature );

EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_v15_finish_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					signature );

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_generate(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	OUT	PVOID					signature );

EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_v15_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	IN	PCVOID					signature );
