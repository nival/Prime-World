//
//	cryptolib.pkcs1.c
//
//	PKCS #1 primitives implementation.
//


#include "cryptolib.pkcs1.h"


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsaes_oaep_context_get_size(
	VOID );

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


#ifdef CRYPTOLIB_CODE_SECTION
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsaes_oaep_encrypt )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsaes_oaep_decrypt )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_alg_get_size )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_alg_create_no_relocs )
#ifndef CRYPTOLIB_NO_RELOCS
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_alg_create )
#endif
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_alg_delete )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_init )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_process )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_finish_generate )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_finish_verify )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_generate )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_pss_verify )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_alg_get_size )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_alg_create_no_relocs )
#ifndef CRYPTOLIB_NO_RELOCS
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_alg_create )
#endif
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_alg_delete )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_init )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_process )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_finish_generate )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_finish_verify )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_generate )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, pkcs1_rsassa_v15_verify )
#endif


//
//	Fill memory block with the specified byte value.
//
//	dst		- Pointer to the memory block to fill.
//	size	- Number of bytes to fill.
//	value	- Byte value to fill with.
//

LOCAL
FORCEINLINE
VOID
pkcs1_memset(
	OUT	PVOID	dst,
	IN	SIZE_T	size,
	IN	UINT8	value )
{
	PUINT8	d;
	SIZE_T	i;

	d = ( PUINT8 )dst;
	for( i = 0; i < size; i++ )
	{
		d[ i ] = value;
	}
}


//
//	Fill memory block with zeros.
//
//	dst		- Pointer to the memory block to fill.
//	size	- Number of bytes to fill.
//

LOCAL
FORCEINLINE
VOID
pkcs1_memzero(
	OUT	PVOID	dst,
	IN	SIZE_T	size )
{
	pkcs1_memset( dst, size, 0 );
}


//
//	Copy memory block.
//
//	dst		- Pointer to the destination memory block.
//	src		- Pointer to the source memory block.
//	size	- Number of bytes to copy.
//

LOCAL
FORCEINLINE
VOID
pkcs1_memcopy(
	OUT	PVOID	dst,
	IN	PCVOID	src,
	IN	SIZE_T	size )
{
	PUINT8	d;
	PCUINT8	s;
	SIZE_T	i;

	d = ( PUINT8 )dst;
	s = ( PCUINT8 )src;
	for( i = 0; i < size; i++ )
	{
		d[ i ] = s[ i ];
	}
}


//
//	Copy memory block with care of the destination block borders.
//
//	dst			- Pointer to the destination memory block.
//	dst_size	- Size in bytes of the destination memory block.
//	dst_offset	- Offset in bytes in the destination memory block to start copying from.
//	src			- Pointer to the source memory block.
//	size		- Number of bytes to copy.
//

LOCAL
FORCEINLINE
VOID
pkcs1_memcopy_care(
	OUT	PVOID	dst,
	IN	SIZE_T	dst_size,
	IN	SIZE_T	dst_offset,
	IN	PCVOID	src,
	IN	SIZE_T	size )
{
	PCUINT8	s;
	PUINT8	d;
	SIZE_T	i;

	s = ( PCUINT8 )src;
	d = ( PUINT8 )dst;
	for( i = 0; i < size; i++ )
	{
		if( ( dst_offset + i ) < dst_size )
		{
			d[ dst_offset + i ] = s[ i ];
		}
	}
}


//
//	Xor (exclusive or) memory blocks.
//
//	src1	- Pointer to an input memory block 1.
//	src2	- Pointer to an input memory block 2.
//	dst		- Pointer to an output memory block.
//	size	- Size in bytes of a memory blocks.
//

LOCAL
FORCEINLINE
VOID
pkcs1_memxor(
	OUT	PVOID	dst,
	IN	PCVOID	src1,
	IN	PCVOID	src2,
	IN	SIZE_T	size )
{
	PUINT8	d;
	PCUINT8	s1;
	PCUINT8	s2;
	SIZE_T	i;

	d = ( PUINT8 )dst;
	s1 = ( PCUINT8 )src1;
	s2 = ( PCUINT8 )src2;
	for( i = 0; i < size; i++ )
	{
		d[ i ] = s1[ i ] ^ s2[ i ];
	}
}


//
//	Compare memory blocks.
//
//	src1	- Pointer to an input memory block 1.
//	src2	- Pointer to an input memory block 2.
//	size	- Size in bytes of a memory blocks.
//

LOCAL
FORCEINLINE
BOOLEAN
pkcs1_is_memequal(
	IN	PCVOID	src1,
	IN	PCVOID	src2,
	IN	SIZE_T	size )
{
	PCUINT8	s1;
	PCUINT8	s2;
	SIZE_T	i;

	s1 = ( PCUINT8 )src1;
	s2 = ( PCUINT8 )src2;
	for( i = 0; i < size; i++ )
	{
		if( s1[ i ] != s2[ i ] ) return FALSE;
	}

	return TRUE;
}


//
//	Check that memory block contains zeros.
//
//	src		- Pointer to an input memory block.
//	size	- Size in bytes of a memory block.
//

LOCAL
FORCEINLINE
BOOLEAN
pkcs1_is_memzero(
	IN	PCVOID	src,
	IN	SIZE_T	size )
{
	PCUINT8	s;
	SIZE_T	i;

	s = ( PCUINT8 )src;
	for( i = 0; i < size; i++ )
	{
		if( s[ i ] != 0x00 ) return FALSE;
	}

	return TRUE;
}


//
//	PKCS #1 v2.1, Section 4.1.
//	I2OSP converts a nonnegative integer to an octet string of a specified length.
//
//	octets	- Pointer to an output octet string.
//	integer	- Pointer to an input integer.
//	size	- Size in bytes of an input integer and an output octet string.
//

LOCAL
FORCEINLINE
VOID
pkcs1_i2osp(
	OUT	PUINT8	octets,
	IN	PCUINT8	integer,
	IN	SIZE_T	size )
{
	SIZE_T	i;

	for( i = 0; i < size; i++ )
	{
		octets[ i ] = integer[ size - 1 - i ];
	}
}


//
//	PKCS #1 v2.1, Section 4.1.
//	I2OSP converts a nonnegative integer to an octet string of a specified length.
//
//	octets	- Pointer to an output octet string.
//	integer	- 32-bit input integer.
//

LOCAL
FORCEINLINE
VOID
pkcs1_i2osp_uint32(
	OUT	PUINT8	octets,
	IN	UINT32	integer )
{
	octets[ 0 ] = ( UINT8 )( integer >> 24 );
	octets[ 1 ] = ( UINT8 )( integer >> 16 );
	octets[ 2 ] = ( UINT8 )( integer >>  8 );
	octets[ 3 ] = ( UINT8 )( integer >>  0 );
}


//
//	PKCS #1 v2.1, Section 4.1.
//	I2OSP converts a nonnegative integer to an octet string of a specified length.
//
//	octets			- Pointer to an output octet string.
//	octets_size		- Intended size in bytes of on output octet string.
//	integer			- Pointer to an input integer.
//	integer_size	- Size in bytes of an input integer.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_i2osp_ex(
	OUT	PUINT8	octets,
	IN	SIZE_T	octets_size,
	IN	PCUINT8	integer,
	IN	SIZE_T	integer_size )
{
	SIZE_T	i;

	for( i = octets_size; i < integer_size; i++ )
	{
		if( integer[ i ] != 0x00 )
		{
			return STATUS_CRYPTOLIB_REPRESENTATIVE_TOO_LARGE;
		}
	}

	for( i = 0; i < octets_size; i++ )
	{
		octets[ i ] = integer[ octets_size - 1 - i ];
	}

	return STATUS_CRYPTOLIB_SUCCESS;
}


//
//	PKCS #1 v2.1, Section 4.2.
//	OS2IP converts an octet string to a nonnegative integer.
//
//	integer			- Pointer to an output integer.
//	integer_size	- Size in bytes of an output integer.
//	octets			- Pointer to an input octet string.
//	octets_size		- Size in bytes of an input octet string.
//

LOCAL
FORCEINLINE
VOID
pkcs1_os2ip(
	OUT	PUINT8	integer,
	IN	SIZE_T	integer_size,
	IN	PCUINT8	octets,
	IN	SIZE_T	octets_size )
{
	SIZE_T	i;

	CRYPTOLIB_ASSERT( integer_size >= octets_size );

	for( i = 0; i < octets_size; i++ )
	{
		integer[ i ] = octets[ octets_size - 1 - i ];
	}

	for( i = octets_size; i < integer_size; i++ )
	{
		integer[ i ] = 0x00;
	}
}


//
//	PKCS #1 v2.1, Section B.2.1.
//	MGF1 is a Mask Generation Function based on a hash function.
//
//	mask		- Pointer to the output generated mask value.
//	mask_size	- Intended size in bytes of the mask.
//	hash_alg	- Pointer to a hash algorithm to use.
//	seed		- Pointer to a random bytes seed from which mask is generated.
//	seed_size	- Size in bytes of the seed.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_mgf1(
	OUT	PVOID			mask,
	IN	SIZE_T			mask_size,
	IN	PHASH_ALGORITHM	hash_alg,
	IN	PCVOID			seed,
	IN	SIZE_T			seed_size )
{
	UINT64				iterations;
	UINT32				counter;
	SIZE_T				mask_pos;
	CRYPTOLIB_STATUS	status;

	//
	// Compute number of iterations.
	//

	iterations = ( UINT64 )mask_size / hash_alg->hash_size;
	if( ( mask_size % hash_alg->hash_size ) != 0 ) iterations++;
	if( iterations > MAX_UINT32 )
	{
		status = STATUS_CRYPTOLIB_PKCS1_MASK_TOO_LONG;
		goto done;
	}

	//
	// Iterate...
	//

	mask_pos = 0;
	for( counter = 0; counter < ( UINT32 )iterations; counter++ )
	{
		UINT8	c[ 4 ];
		UINT8	hash[ HASH_MAX_SIZE ];

		pkcs1_i2osp_uint32( c, counter );

		hash_alg->init( hash_alg );
		hash_alg->process( hash_alg, seed, seed_size );
		hash_alg->process( hash_alg, c, 4 );
		hash_alg->finish( hash_alg, hash );

		pkcs1_memcopy_care( mask, mask_size, mask_pos, hash, hash_alg->hash_size );
		mask_pos += hash_alg->hash_size;

		pkcs1_memzero( c, sizeof( c ) );
		pkcs1_memzero( hash, sizeof( hash ) );
	}

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	return status;
}


//
//	PKCS #1 v2.1, Section B.2.
//	MGF is a Mask Generation Function.
//
//	mgf_id		- MGF ID to use.
//	mask		- Pointer to the output generated mask value.
//	mask_size	- Intended size in bytes of the mask.
//	hash_alg	- Pointer to a hash algorithm to use.
//	seed		- Pointer to a random bytes seed from which mask is generated.
//	seed_size	- Size in bytes of the seed.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_mgf(
	IN	UINT32			mgf_id,
	OUT	PVOID			mask,
	IN	SIZE_T			mask_size,
	IN	PHASH_ALGORITHM	hash_alg,
	IN	PCVOID			seed,
	IN	SIZE_T			seed_size )
{
	if( mgf_id == PKCS1_MGF1_ID )
	{
		return pkcs1_mgf1( mask, mask_size, hash_alg, seed, seed_size );
	}
	else
	{
		return STATUS_CRYPTOLIB_PKCS1_UNKNOWN_MGF;
	}
}


//
//	PKCS #1 v2.1, Section 5.1.1.
//	RSAEP( ( n, e ), m )
//
//	rsa_alg	- Pointer to a RSA algorithm to use.
//	m		- Pointer to an input message representative.
//	c		- Pointer to an output ciphertext representative.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_rsaep(
	IN	PRSA_ALGORITHM	rsa_alg,
	IN	PCVOID			m,
	OUT	PVOID			c )
{
	return rsa_alg->alg.do_pub( &rsa_alg->alg, m, c );
}


//
//	PKCS #1 v2.1, Section 5.1.2.
//	RSADP( K, c )
//
//	rsa_alg	- Pointer to a RSA algorithm to use.
//	c		- Pointer to an input ciphertext representative.
//	m		- Pointer to an output message representative.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_rsadp(
	IN	PRSA_ALGORITHM	rsa_alg,
	IN	PCVOID			c,
	OUT	PVOID			m )
{
	return rsa_alg->alg.do_pvt( &rsa_alg->alg, c, m );
}


//
//	PKCS #1 v2.1, Section 5.2.1.
//	RSASP1( K, m )
//
//	rsa_alg	- Pointer to a RSA algorithm to use.
//	m		- Pointer to an input message representative.
//	s		- Pointer to an output signature representative.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_rsasp1(
	IN	PRSA_ALGORITHM	rsa_alg,
	IN	PCVOID			m,
	OUT	PVOID			s )
{
	return rsa_alg->alg.do_pvt( &rsa_alg->alg, m, s );
}


//
//	PKCS #1 v2.1, Section 5.2.2.
//	RSAVP1( ( n, e ), s )
//
//	rsa_alg	- Pointer to a RSA algorithm to use.
//	s		- Pointer to an input signature representative.
//	m		- Pointer to an output message representative.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_rsavp1(
	IN	PRSA_ALGORITHM	rsa_alg,
	IN	PCVOID			s,
	OUT	PVOID			m )
{
	return rsa_alg->alg.do_pub( &rsa_alg->alg, s, m );
}


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsaes_oaep_context_get_size(
	VOID )
{
	return sizeof( PKCS1_RSAES_OAEP_STACK_FRAME );
}


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
	OUT	PVOID							ciphertext )
{
	SIZE_T				key_size;
	SIZE_T				hash_size;
	UINT8				label_hash[ HASH_MAX_SIZE ];
	SIZE_T				ps_size;
	PUINT8				db;
	SIZE_T				db_size;
	PUINT8				em;
	PUINT8				m;
	PUINT8				c;
	CRYPTOLIB_STATUS	status;

	CRYPTOLIB_PAGED_CODE();

	key_size = rsa_alg->alg.key_size;
	hash_size = hash_alg->hash_size;

	db = stack_frame->rsaes_oaep_encrypt.db;
	em = stack_frame->rsaes_oaep_encrypt.em;
	m = stack_frame->rsaes_oaep_encrypt.m;
	c = stack_frame->rsaes_oaep_encrypt.c;

	//
	// Check algorithms combination valid.
	//

	if( key_size < ( ( 2 * hash_size ) + 2 ) )
	{
		status = STATUS_CRYPTOLIB_ERROR;
		goto done;
	}

	//
	// Check message size.
	//

	if( message_size > ( key_size - ( 2 * hash_size ) - 2 ) )
	{
		status = STATUS_CRYPTOLIB_MESSAGE_TOO_LONG;
		goto done;
	}

	//
	// Compute hash of the label.
	//

	hash_alg->compute( hash_alg, label, label_size, label_hash );

	//
	// Compose data-block.
	//
	// db = label_hash | ps | 0x01 | message
	//

	db_size = key_size - hash_size - 1;
	ps_size = key_size - message_size - ( 2 * hash_size ) - 2;
	pkcs1_memcopy( db, label_hash, hash_size );
	pkcs1_memzero( db + hash_size, ps_size );
	db[ hash_size + ps_size ] = 0x01;
	pkcs1_memcopy( db + hash_size + ps_size + 1, message, message_size );

	//
	// Compose encoded message.
	//
	// em = 0x00 | seed ^ mgf( db ^ mgf( seed ) ) | db ^ mgf( seed )
	//

	em[ 0 ] = 0x00;

	status = pkcs1_mgf( mgf_id, em + 1 + hash_size, db_size, hash_alg, seed, hash_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_memxor( em + 1 + hash_size, db, em + 1 + hash_size, db_size );

	status = pkcs1_mgf( mgf_id, em + 1, hash_size, hash_alg, em + 1 + hash_size, db_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_memxor( em + 1, seed, em + 1, hash_size );

	//
	// Encrypt encoded message by RSA.
	//

	pkcs1_os2ip( m, key_size, em, key_size );
	status = pkcs1_rsaep( rsa_alg, m, c );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_i2osp( ( PUINT8 )ciphertext, c, key_size );

	//
	// Encryption done.
	//

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PKCS1_RSAES_OAEP_STACK_FRAME ) );
	pkcs1_memzero( label_hash, sizeof( label_hash ) );
	ps_size = 0;
	db_size = 0;

	return status;
}


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
	OUT	PSIZE_T							message_size )
{
	SIZE_T				key_size;
	SIZE_T				hash_size;
	UINT8				label_hash[ HASH_MAX_SIZE ];
	PUINT8				c;
	PUINT8				m;
	PUINT8				em;
	PUINT8				seed;
	PUINT8				db;
	SIZE_T				db_size;
	SIZE_T				msg_offset;
	CRYPTOLIB_STATUS	status;

	CRYPTOLIB_PAGED_CODE();

	key_size = rsa_alg->alg.key_size;
	hash_size = hash_alg->hash_size;

	c = stack_frame->rsaes_oaep_decrypt.c;
	m = stack_frame->rsaes_oaep_decrypt.m;
	em = stack_frame->rsaes_oaep_decrypt.em;
	seed = stack_frame->rsaes_oaep_decrypt.seed;
	db = stack_frame->rsaes_oaep_decrypt.db;

	//
	// Check algorithms combination valid.
	//

	if( key_size < ( ( 2 * hash_size ) + 2 ) )
	{
		status = STATUS_CRYPTOLIB_ERROR;
		goto done;
	}

	//
	// Decrypt encoded message by RSA.
	//

	pkcs1_os2ip( c, key_size, ( PCUINT8 )ciphertext, key_size );
	status = pkcs1_rsadp( rsa_alg, c, m );
	if( status != STATUS_CRYPTOLIB_SUCCESS )
	{
		status = STATUS_CRYPTOLIB_ERROR;
		goto done;
	}
	pkcs1_i2osp( em, m, key_size );

	//
	// Compute hash of the label.
	//

	hash_alg->compute( hash_alg, label, label_size, label_hash );

	//
	// Decompose encoded message.
	//
	// em = 0x00 | seed ^ mgf( db ^ mgf( seed ) ) | db ^ mgf( seed )
	//

	db_size = key_size - hash_size - 1;

	status = pkcs1_mgf( mgf_id, seed, hash_size, hash_alg, em + 1 + hash_size, db_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_memxor( seed, em + 1, seed, hash_size );

	status = pkcs1_mgf( mgf_id, db, db_size, hash_alg, seed, hash_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_memxor( db, em + 1 + hash_size, db, db_size );

	//
	// Decompose data-block.
	//
	// db = label_hash | ps | 0x01 | message
	//

	if( !pkcs1_is_memequal( db, label_hash, hash_size ) )
	{
		status = STATUS_CRYPTOLIB_ERROR;
		goto done;
	}

	msg_offset = hash_size;
	while( ( msg_offset < db_size ) && ( db[ msg_offset ] == 0x00 ) )
	{
		msg_offset++;
	}
	if( ( msg_offset == db_size ) || ( db[ msg_offset ] != 0x01 ) )
	{
		status = STATUS_CRYPTOLIB_ERROR;
		goto done;
	}
	msg_offset++;

	if( em[ 0 ] != 0x00 )
	{
		status = STATUS_CRYPTOLIB_ERROR;
		goto done;
	}

	//
	// Copy message.
	//

	pkcs1_memcopy( message, db + msg_offset, db_size - msg_offset );
	*message_size = db_size - msg_offset;

	//
	// Decryption done.
	//

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PKCS1_RSAES_OAEP_STACK_FRAME ) );
	pkcs1_memzero( label_hash, sizeof( label_hash ) );
	db_size = 0;
	msg_offset = 0;

	return status;
}


//****************************************************************
//	PKCS #1 v2.1 - PSS Signature Algorithm.
//****************************************************************


//
//	PKCS #1 v2.1, Section 9.1.1.
//	EMSA-PSS-ENCODE( M, emBits )
//
//	stack_frame		- Pointer to a stack frame to use.
//	hash_alg		- Pointer to a hash algorithm to use.
//	mgf_id			- Mask Generation Function to use.
//	mgf_hash_alg	- Pointer to a hash algorithm for MGF to use.
//	salt			- Pointer to an input salt value.
//	salt_size		- Size in bytes of the salt.
//	m_hash			- Pointer to a hash value of the message.
//	em_bitsize		- Size in bits of the encoded message.
//	em				- Pointer to an output encoded message.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_emsa_pss_encode(
		PPKCS1_EMSA_PSS_ENCODE_STACK_FRAME	stack_frame,
	IN	PHASH_ALGORITHM						hash_alg,
	IN	UINT32								mgf_id,
	IN	PHASH_ALGORITHM						mgf_hash_alg,
	IN	PCUINT8								salt,
	IN	SIZE_T								salt_size,
	IN	PCUINT8								m_hash,
	IN	SIZE_T								em_bitsize,
	OUT	PUINT8								em )
{
	SIZE_T				em_size;
	SIZE_T				hash_size;
	UINT8				hash[ HASH_MAX_SIZE ];
	SIZE_T				ps_size;
	PUINT8				db;
	SIZE_T				db_size;
	UINT8				zero_bytes[ 8 ];
	CRYPTOLIB_STATUS	status;

	em_size = em_bitsize / 8;
	if( ( em_bitsize % 8 ) != 0 ) em_size++;

	hash_size = hash_alg->hash_size;

	db = stack_frame->db;

	pkcs1_memzero( zero_bytes, 8 );

	//
	// Check encoded message size.
	//

	if( em_size < ( hash_size + salt_size + 2 ) )
	{
		status = STATUS_CRYPTOLIB_INTENDED_ENCODED_MESSAGE_TOO_SHORT;
		goto done;
	}

	//
	// Compute hash of the message hash and salt.
	//
	// hash = hash_alg( 0 0 0 0 0 0 0 0 | m_hash | salt )
	//

	hash_alg->init( hash_alg );
	hash_alg->process( hash_alg, zero_bytes, 8 );
	hash_alg->process( hash_alg, m_hash, hash_size );
	hash_alg->process( hash_alg, salt, salt_size );
	hash_alg->finish( hash_alg, hash );

	//
	// Compose data-block.
	//
	// db = ps | 0x01 | salt
	//

	db_size = em_size - hash_size - 1;
	ps_size = em_size - salt_size - hash_size - 2;
	pkcs1_memzero( db, ps_size );
	db[ ps_size ] = 0x01;
	pkcs1_memcopy( db + ps_size + 1, salt, salt_size );

	//
	// Compose encoded message.
	//
	// em = db ^ mgf( hash ) | hash | 0xBC
	//

	status = pkcs1_mgf( mgf_id, em, db_size, mgf_hash_alg, hash, hash_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	pkcs1_memxor( em, db, em, db_size );

	if( ( em_bitsize % 8 ) != 0 )
	{
		em[ 0 ] &= ( 1 << ( em_bitsize % 8 ) ) - 1;
	}

	pkcs1_memcopy( em + db_size, hash, hash_size );
	em[ db_size + hash_size ] = 0xBC;

	//
	// Encoding done.
	//

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PKCS1_EMSA_PSS_ENCODE_STACK_FRAME ) );
	pkcs1_memzero( hash, sizeof( hash ) );
	ps_size = 0;
	db_size = 0;

	return status;
}


//
//	PKCS #1 v2.1, Section 9.1.2.
//	EMSA-PSS-VERIFY( M, EM, emBits )
//
//	stack_frame		- Pointer to a stack frame to use.
//	hash_alg		- Pointer to a hash algorithm to use.
//	mgf_id			- Mask Generation Function to use.
//	mgf_hash_alg	- Pointer to a hash algorithm for MGF to use.
//	salt_size		- Size in bytes of the salt.
//	m_hash			- Pointer to a hash value of the message.
//	em				- Pointer to an input encoded message.
//	em_bitsize		- Size in bits of the encoded message.
//

LOCAL
FORCEINLINE
BOOLEAN
pkcs1_emsa_pss_verify(
		PPKCS1_EMSA_PSS_VERIFY_STACK_FRAME	stack_frame,
	IN	PHASH_ALGORITHM						hash_alg,
	IN	UINT32								mgf_id,
	IN	PHASH_ALGORITHM						mgf_hash_alg,
	IN	SIZE_T								salt_size,
	IN	PCUINT8								m_hash,
	IN	PCUINT8								em,
	IN	SIZE_T								em_bitsize )
{
	SIZE_T				em_size;
	SIZE_T				hash_size;
	UINT8				hash[ HASH_MAX_SIZE ];
	SIZE_T				ps_size;
	PUINT8				db;
	SIZE_T				db_size;
	UINT8				zero_bytes[ 8 ];
	CRYPTOLIB_STATUS	status;
	BOOLEAN				valid;

	em_size = em_bitsize / 8;
	if( ( em_bitsize % 8 ) != 0 ) em_size++;

	hash_size = hash_alg->hash_size;

	db = stack_frame->db;

	pkcs1_memzero( zero_bytes, 8 );

	valid = FALSE;

	//
	// Check encoded message size.
	//

	if( em_size < ( hash_size + salt_size + 2 ) ) goto done;

	//
	// Decompose encoded message.
	//
	// em = db ^ mgf( hash ) | hash | 0xBC
	//

	if( em[ em_size - 1 ] != 0xBC ) goto done;

	if( ( em_bitsize % 8 ) != 0 )
	{
		if( ( em[ 0 ] >> ( em_bitsize % 8 ) ) != 0 ) goto done;
	}

	ps_size = em_size - salt_size - hash_size - 2;
	db_size = em_size - hash_size - 1;

	status = pkcs1_mgf( mgf_id, db, db_size, mgf_hash_alg, em + db_size, hash_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	pkcs1_memxor( db, em, db, db_size );

	if( ( em_bitsize % 8 ) != 0 )
	{
		db[ 0 ] &= ( 1 << ( em_bitsize % 8 ) ) - 1;
	}

	//
	// Decompose data-block.
	//
	// db = ps | 0x01 | salt
	//

	if( !pkcs1_is_memzero( db, ps_size ) ) goto done;
	if( db[ ps_size ] != 0x01 ) goto done;

	//
	// Compute hash of the message hash and salt.
	//
	// hash = hash_alg( 0 0 0 0 0 0 0 0 | m_hash | salt )
	//

	hash_alg->init( hash_alg );
	hash_alg->process( hash_alg, zero_bytes, 8 );
	hash_alg->process( hash_alg, m_hash, hash_size );
	hash_alg->process( hash_alg, db + db_size - salt_size, salt_size );
	hash_alg->finish( hash_alg, hash );

	//
	// Compare hash values.
	//

	valid = pkcs1_is_memequal( em + db_size, hash, hash_size );

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PKCS1_EMSA_PSS_VERIFY_STACK_FRAME ) );
	pkcs1_memzero( hash, sizeof( hash ) );
	ps_size = 0;
	db_size = 0;

	return valid;
}


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsassa_pss_alg_get_size(
	VOID )
{
	CRYPTOLIB_PAGED_CODE();

	return sizeof( PKCS1_RSASSA_PSS_ALGORITHM );
}


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
	IN	PSIGNATURE_VERIFY			fn_verify )
{
	CRYPTOLIB_PAGED_CODE();

	pkcs1_memzero( pss_alg, sizeof( PKCS1_RSASSA_PSS_ALGORITHM ) );

	pss_alg->alg.signature_bitsize = rsa_alg->alg.key_size * 8;
	pss_alg->alg.signature_size    = rsa_alg->alg.key_size;

	pss_alg->alg.init            = fn_init;
	pss_alg->alg.process         = fn_process;
	pss_alg->alg.finish_generate = fn_finish_generate;
	pss_alg->alg.finish_verify   = fn_finish_verify;
	pss_alg->alg.generate        = fn_generate;
	pss_alg->alg.verify          = fn_verify;

	pss_alg->rsa_alg = rsa_alg;
	pss_alg->hash_alg = hash_alg;
	pss_alg->mgf_id = mgf_id;
	pss_alg->mgf_hash_alg = mgf_hash_alg;
	if( salt_size > RSA_KEY_MAX_SIZE ) salt_size = RSA_KEY_MAX_SIZE;
	if( salt == NULL )
	{
		pkcs1_memzero( pss_alg->salt, salt_size );
	}
	else
	{
		pkcs1_memcopy( pss_alg->salt, salt, salt_size );
	}
	pss_alg->salt_size = salt_size;

	return STATUS_CRYPTOLIB_SUCCESS;
}


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
	IN	SIZE_T						salt_size )
{
	CRYPTOLIB_PAGED_CODE();

	return pkcs1_rsassa_pss_alg_create_no_relocs( pss_alg,
		rsa_alg, hash_alg, mgf_id, mgf_hash_alg, salt, salt_size,
		pkcs1_rsassa_pss_init, pkcs1_rsassa_pss_process,
		pkcs1_rsassa_pss_finish_generate, pkcs1_rsassa_pss_finish_verify,
		pkcs1_rsassa_pss_generate, pkcs1_rsassa_pss_verify );
}
#endif


EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_pss_alg_delete(
		PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg )
{
	CRYPTOLIB_PAGED_CODE();

	pkcs1_memzero( pss_alg, sizeof( PKCS1_RSASSA_PSS_ALGORITHM ) );
}


EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_pss_init(
		PSIGNATURE_ALGORITHM	alg )
{
	PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg;

	CRYPTOLIB_PAGED_CODE();

	pss_alg = ( PPKCS1_RSASSA_PSS_ALGORITHM )alg;

	pss_alg->hash_alg->init( pss_alg->hash_alg );
}


EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_pss_process(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size )
{
	PPKCS1_RSASSA_PSS_ALGORITHM	pss_alg;

	CRYPTOLIB_PAGED_CODE();

	pss_alg = ( PPKCS1_RSASSA_PSS_ALGORITHM )alg;

	pss_alg->hash_alg->process( pss_alg->hash_alg, buffer, buffer_size );
}


//
//	PKCS #1 v2.1, Section 8.1.1.
//	RSASSA-PSS-SIGN( K, M )
//
//	alg			- Pointer to the RSASSA-PSS algorithm.
//	signature	- Pointer to an output signature.
//

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_pss_finish_generate(
		PSIGNATURE_ALGORITHM	alg,
	OUT	PVOID					signature )
{
	PPKCS1_RSASSA_PSS_ALGORITHM		pss_alg;
	PPKCS1_RSASSA_PSS_STACK_FRAME	stack_frame;
	SIZE_T							key_bitsize;
	SIZE_T							key_size;
	UINT8							m_hash[ HASH_MAX_SIZE ];
	SIZE_T							em_bitsize;
	SIZE_T							em_size;
	PUINT8							em;
	PUINT8							m;
	PUINT8							s;
	CRYPTOLIB_STATUS				status;

	CRYPTOLIB_PAGED_CODE();

	pss_alg = ( PPKCS1_RSASSA_PSS_ALGORITHM )alg;

	key_bitsize = pss_alg->rsa_alg->alg.key_bitsize;
	key_size = pss_alg->rsa_alg->alg.key_size;

	stack_frame = &pss_alg->stack_frame;
	em = stack_frame->finish_generate.em;
	m = stack_frame->finish_generate.m;
	s = stack_frame->finish_generate.s;

	//
	// Finish computing hash of the message.
	//

	pss_alg->hash_alg->finish( pss_alg->hash_alg, m_hash );

	//
	// Apply the EMSA-PSS encoding operation.
	//

	em_bitsize = key_bitsize - 1;
	em_size = em_bitsize / 8;
	if( ( em_bitsize % 8 ) != 0 ) em_size++;

	status = pkcs1_emsa_pss_encode( &stack_frame->finish_generate.emsa_pss_encode,
		pss_alg->hash_alg, pss_alg->mgf_id, pss_alg->mgf_hash_alg,
		pss_alg->salt, pss_alg->salt_size,
		m_hash, em_bitsize, em );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	//
	// Encrypt encoded message by RSA.
	//

	pkcs1_os2ip( m, key_size, em, em_size );
	status = pkcs1_rsasp1( pss_alg->rsa_alg, m, s );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_i2osp( ( PUINT8 )signature, s, key_size );

	//
	// Signature generation done.
	//

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PPKCS1_RSASSA_PSS_STACK_FRAME ) );
	pkcs1_memzero( m_hash, sizeof( m_hash ) );

	return status;
}


//
//	PKCS #1 v2.1, Section 8.1.2.
//	RSASSA-PSS-VERIFY( ( n, e ), M, S )
//
//	alg			- Pointer to the RSASSA-PSS algorithm.
//	signature	- Pointer to an input signature to validate.
//

EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_pss_finish_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					signature )
{
	PPKCS1_RSASSA_PSS_ALGORITHM		pss_alg;
	PPKCS1_RSASSA_PSS_STACK_FRAME	stack_frame;
	SIZE_T							key_bitsize;
	SIZE_T							key_size;
	UINT8							m_hash[ HASH_MAX_SIZE ];
	SIZE_T							em_bitsize;
	SIZE_T							em_size;
	PUINT8							s;
	PUINT8							m;
	PUINT8							em;
	CRYPTOLIB_STATUS				status;
	BOOLEAN							valid;

	CRYPTOLIB_PAGED_CODE();

	pss_alg = ( PPKCS1_RSASSA_PSS_ALGORITHM )alg;

	key_bitsize = pss_alg->rsa_alg->alg.key_bitsize;
	key_size = pss_alg->rsa_alg->alg.key_size;

	stack_frame = &pss_alg->stack_frame;
	s = stack_frame->finish_verify.s;
	m = stack_frame->finish_verify.m;
	em = stack_frame->finish_verify.em;

	valid = FALSE;

	//
	// Finish computing hash of the message.
	//

	pss_alg->hash_alg->finish( pss_alg->hash_alg, m_hash );

	//
	// Decrypt encoded message by RSA.
	//

	pkcs1_os2ip( s, key_size, ( PCUINT8 )signature, key_size );
	status = pkcs1_rsavp1( pss_alg->rsa_alg, s, m );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	em_bitsize = key_bitsize - 1;
	em_size = em_bitsize / 8;
	if( ( em_bitsize % 8 ) != 0 ) em_size++;
	status = pkcs1_i2osp_ex( em, em_size, m, key_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	//
	// Apply the EMSA-PSS verification operation.
	//

	valid = pkcs1_emsa_pss_verify( &stack_frame->finish_verify.emsa_pss_verify,
		pss_alg->hash_alg, pss_alg->mgf_id, pss_alg->mgf_hash_alg,
		pss_alg->salt_size, m_hash, em, key_bitsize - 1 );

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PKCS1_RSASSA_PSS_STACK_FRAME ) );
	pkcs1_memzero( m_hash, sizeof( m_hash ) );

	return valid;
}


EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_pss_generate(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	OUT	PVOID					signature )
{
	CRYPTOLIB_PAGED_CODE();

	alg->init( alg );
	alg->process( alg, buffer, buffer_size );
	return alg->finish_generate( alg, signature );
}


EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_pss_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	IN	PCVOID					signature )
{
	CRYPTOLIB_PAGED_CODE();

	alg->init( alg );
	alg->process( alg, buffer, buffer_size );
	return alg->finish_verify( alg, signature );
}


//****************************************************************
//	PKCS #1 v2.1 - v1.5 Signature Algorithm.
//****************************************************************


//
//	PKCS #1 v2.1, Section 9.2.
//	EMSA-PKCS1-V1_5-ENCODE( M, emLen )
//
//	hash_alg	- Pointer to a hash algorithm used for message hash.
//	m_hash		- Pointer to a hash value of the message.
//	em_size		- Size in bytes of the encoded message.
//	em			- Pointer to an output encoded message.
//

LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
pkcs1_emsa_v15_encode(
	IN	PHASH_ALGORITHM	hash_alg,
	IN	PCUINT8			m_hash,
	IN	SIZE_T			em_size,
	OUT	PUINT8			em )
{
	SIZE_T				hash_size;
	UINT32				hash_alg_id;
	UINT8				hash_alg_id_bytes[ 19 ];
	SIZE_T				hash_alg_id_bytes_size;
	SIZE_T				ps_size;
	CRYPTOLIB_STATUS	status;

	hash_size = hash_alg->hash_size;
	hash_alg_id = hash_alg->id;

	//
	// Determine hash algorithm ID in DER encoding.
	//

	if( hash_alg_id == MD5_ALGORITHM_ID )
	{
		UINT8	id_bytes[ 18 ] =
				{
					0x30, 0x20, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86,
					0x48, 0x86, 0xF7, 0x0D, 0x02, 0x05, 0x05, 0x00,
					0x04, 0x10
				};

		pkcs1_memcopy( hash_alg_id_bytes, id_bytes, sizeof( id_bytes ) );
		hash_alg_id_bytes_size = sizeof( id_bytes );
	}
	else if( hash_alg_id == SHA1_ALGORITHM_ID )
	{
		UINT8	id_bytes[ 15 ] =
				{
					0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2B, 0x0E,
					0x03, 0x02, 0x1A, 0x05, 0x00, 0x04, 0x14
				};

		pkcs1_memcopy( hash_alg_id_bytes, id_bytes, sizeof( id_bytes ) );
		hash_alg_id_bytes_size = sizeof( id_bytes );
	}
	else if( hash_alg_id == SHA512_ALGORITHM_ID )
	{
		UINT8	id_bytes[ 19 ] =
				{
					0x30, 0x51, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,
					0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03, 0x05,
					0x00, 0x04, 0x40
				};

		pkcs1_memcopy( hash_alg_id_bytes, id_bytes, sizeof( id_bytes ) );
		hash_alg_id_bytes_size = sizeof( id_bytes );
	}
	else
	{
		status = STATUS_CRYPTOLIB_UNKNOWN_HASH_ALGORITHM;
		goto done;
	}

	//
	// Check encoded message size.
	//

	if( em_size < ( 2 + 8 + 1 + hash_alg_id_bytes_size + hash_size ) )
	{
		status = STATUS_CRYPTOLIB_INTENDED_ENCODED_MESSAGE_TOO_SHORT;
		goto done;
	}

	//
	// Compose encoded message.
	//
	// em = 0x00 | 0x01 | ps | 0x00 | t
	//

	ps_size = em_size - ( 2 + 1 + hash_alg_id_bytes_size + hash_size );
	em[ 0 ] = 0x00;
	em[ 1 ] = 0x01;
	pkcs1_memset( em + 2, ps_size, 0xFF );
	em[ 2 + ps_size ] = 0x00;
	pkcs1_memcopy( em + 2 + ps_size + 1, hash_alg_id_bytes, hash_alg_id_bytes_size );
	pkcs1_memcopy( em + 2 + ps_size + 1 + hash_alg_id_bytes_size, m_hash, hash_size );

	//
	// Encoding done.
	//

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	//
	// Wipe variables and exit.
	//

	hash_size = 0;
	hash_alg_id = 0;
	pkcs1_memzero( hash_alg_id_bytes, sizeof( hash_alg_id_bytes ) );
	hash_alg_id_bytes_size = 0;
	ps_size = 0;

	return status;
}


EXTERN_C
SIZE_T
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_get_size(
	VOID )
{
	CRYPTOLIB_PAGED_CODE();

	return sizeof( PKCS1_RSASSA_V15_ALGORITHM );
}


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
	IN	PSIGNATURE_VERIFY			fn_verify )
{
	CRYPTOLIB_PAGED_CODE();

	if( ( hash_alg->id != MD5_ALGORITHM_ID ) &&
		( hash_alg->id != SHA1_ALGORITHM_ID ) &&
		( hash_alg->id != SHA512_ALGORITHM_ID ) )
	{
		return STATUS_CRYPTOLIB_UNKNOWN_HASH_ALGORITHM;
	}

	pkcs1_memzero( v15_alg, sizeof( PKCS1_RSASSA_V15_ALGORITHM ) );

	v15_alg->alg.signature_bitsize = rsa_alg->alg.key_size * 8;
	v15_alg->alg.signature_size    = rsa_alg->alg.key_size;

	v15_alg->alg.init            = fn_init;
	v15_alg->alg.process         = fn_process;
	v15_alg->alg.finish_generate = fn_finish_generate;
	v15_alg->alg.finish_verify   = fn_finish_verify;
	v15_alg->alg.generate        = fn_generate;
	v15_alg->alg.verify          = fn_verify;

	v15_alg->rsa_alg = rsa_alg;
	v15_alg->hash_alg = hash_alg;

	return STATUS_CRYPTOLIB_SUCCESS;
}


#ifndef CRYPTOLIB_NO_RELOCS
EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_create(
		PPKCS1_RSASSA_V15_ALGORITHM	v15_alg,
	IN	PRSA_ALGORITHM				rsa_alg,
	IN	PHASH_ALGORITHM				hash_alg )
{
	CRYPTOLIB_PAGED_CODE();

	return pkcs1_rsassa_v15_alg_create_no_relocs( v15_alg,
		rsa_alg, hash_alg,
		pkcs1_rsassa_v15_init, pkcs1_rsassa_v15_process,
		pkcs1_rsassa_v15_finish_generate, pkcs1_rsassa_v15_finish_verify,
		pkcs1_rsassa_v15_generate, pkcs1_rsassa_v15_verify );
}
#endif


EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_v15_alg_delete(
		PPKCS1_RSASSA_V15_ALGORITHM	v15_alg )
{
	CRYPTOLIB_PAGED_CODE();

	pkcs1_memzero( v15_alg, sizeof( PKCS1_RSASSA_V15_ALGORITHM ) );
}


EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_v15_init(
		PSIGNATURE_ALGORITHM	alg )
{
	PPKCS1_RSASSA_V15_ALGORITHM	v15_alg;

	CRYPTOLIB_PAGED_CODE();

	v15_alg = ( PPKCS1_RSASSA_V15_ALGORITHM )alg;

	v15_alg->hash_alg->init( v15_alg->hash_alg );
}


EXTERN_C
VOID
CRYPTOLIB_API
pkcs1_rsassa_v15_process(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size )
{
	PPKCS1_RSASSA_V15_ALGORITHM	v15_alg;

	CRYPTOLIB_PAGED_CODE();

	v15_alg = ( PPKCS1_RSASSA_V15_ALGORITHM )alg;

	v15_alg->hash_alg->process( v15_alg->hash_alg, buffer, buffer_size );
}


//
//	PKCS #1 v2.1, Section 8.2.1.
//	RSASSA-PKCS1-V1_5-SIGN( K, M )
//
//	alg			- Pointer to the RSASSA-V1_5 algorithm.
//	signature	- Pointer to an output signature.
//

EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_finish_generate(
		PSIGNATURE_ALGORITHM	alg,
	OUT	PVOID					signature )
{
	PPKCS1_RSASSA_V15_ALGORITHM		v15_alg;
	PPKCS1_RSASSA_V15_STACK_FRAME	stack_frame;
	SIZE_T							key_size;
	UINT8							m_hash[ HASH_MAX_SIZE ];
	SIZE_T							em_size;
	PUINT8							em;
	PUINT8							m;
	PUINT8							s;
	CRYPTOLIB_STATUS				status;

	CRYPTOLIB_PAGED_CODE();

	v15_alg = ( PPKCS1_RSASSA_V15_ALGORITHM )alg;

	key_size = v15_alg->rsa_alg->alg.key_size;

	stack_frame = &v15_alg->stack_frame;
	em = stack_frame->finish_generate.em;
	m = stack_frame->finish_generate.m;
	s = stack_frame->finish_generate.s;

	//
	// Finish computing hash of the message.
	//

	v15_alg->hash_alg->finish( v15_alg->hash_alg, m_hash );

	//
	// Apply the EMSA-PKCS1-V1_5 encoding operation.
	//

	em_size = key_size;

	status = pkcs1_emsa_v15_encode( v15_alg->hash_alg, m_hash, em_size, em );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	//
	// Encrypt encoded message by RSA.
	//

	pkcs1_os2ip( m, key_size, em, em_size );
	status = pkcs1_rsasp1( v15_alg->rsa_alg, m, s );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	pkcs1_i2osp( ( PUINT8 )signature, s, key_size );

	//
	// Signature generation done.
	//

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PPKCS1_RSASSA_V15_STACK_FRAME ) );
	pkcs1_memzero( m_hash, sizeof( m_hash ) );

	return status;
}


EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_v15_finish_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					signature )
{
	PPKCS1_RSASSA_V15_ALGORITHM		v15_alg;
	PPKCS1_RSASSA_V15_STACK_FRAME	stack_frame;
	SIZE_T							key_size;
	UINT8							m_hash[ HASH_MAX_SIZE ];
	SIZE_T							em_size;
	PUINT8							s;
	PUINT8							m;
	PUINT8							em;
	PUINT8							em_expected;
	CRYPTOLIB_STATUS				status;
	BOOLEAN							valid;

	CRYPTOLIB_PAGED_CODE();

	v15_alg = ( PPKCS1_RSASSA_V15_ALGORITHM )alg;

	key_size = v15_alg->rsa_alg->alg.key_size;

	stack_frame = &v15_alg->stack_frame;
	s = stack_frame->finish_verify.s;
	m = stack_frame->finish_verify.m;
	em = stack_frame->finish_verify.em;
	em_expected = stack_frame->finish_verify.em_expected;

	valid = FALSE;

	//
	// Finish computing hash of the message.
	//

	v15_alg->hash_alg->finish( v15_alg->hash_alg, m_hash );

	//
	// Decrypt encoded message by RSA.
	//

	pkcs1_os2ip( s, key_size, ( PCUINT8 )signature, key_size );
	status = pkcs1_rsavp1( v15_alg->rsa_alg, s, m );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;
	em_size = key_size;
	status = pkcs1_i2osp_ex( em, em_size, m, key_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	//
	// Apply the EMSA-PKCS1-V1_5 encoding operation.
	//

	status = pkcs1_emsa_v15_encode( v15_alg->hash_alg, m_hash, em_size, em_expected );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	//
	// Compare decrypted encoded message with exptected encoded message.
	//

	valid = pkcs1_is_memequal( em, em_expected, em_size );

done:

	//
	// Wipe variables and exit.
	//

	pkcs1_memzero( stack_frame, sizeof( PKCS1_RSASSA_V15_STACK_FRAME ) );
	key_size = 0;
	pkcs1_memzero( m_hash, sizeof( m_hash ) );
	em_size = 0;
	s = NULL;
	m = NULL;
	em = NULL;
	em_expected = NULL;

	return valid;
}


EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
pkcs1_rsassa_v15_generate(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	OUT	PVOID					signature )
{
	CRYPTOLIB_PAGED_CODE();

	alg->init( alg );
	alg->process( alg, buffer, buffer_size );
	return alg->finish_generate( alg, signature );
}


EXTERN_C
BOOLEAN
CRYPTOLIB_API
pkcs1_rsassa_v15_verify(
		PSIGNATURE_ALGORITHM	alg,
	IN	PCVOID					buffer,
	IN	SIZE_T					buffer_size,
	IN	PCVOID					signature )
{
	CRYPTOLIB_PAGED_CODE();

	alg->init( alg );
	alg->process( alg, buffer, buffer_size );
	return alg->finish_verify( alg, signature );
}
