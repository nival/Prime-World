//
//	cryptolib.rsa.c
//
//	RSA asymmetric cipher algorithm implementation.
//


#include "cryptolib.rsa.h"


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


#ifdef CRYPTOLIB_CODE_SECTION
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, rsa_alg_get_size )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, rsa_alg_create_no_relocs )
#ifndef CRYPTOLIB_NO_RELOCS
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, rsa_alg_create )
#endif
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, rsa_alg_delete )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, rsa_do_pub )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, rsa_do_pvt )
#endif


LOCAL
FORCEINLINE
VOID
rsa_memset(
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


LOCAL
FORCEINLINE
VOID
rsa_memzero(
	OUT	PVOID	dst,
	IN	SIZE_T	size )
{
	rsa_memset( dst, size, 0 );
}


LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
rsa_number_load(
	OUT	PRSA_NUMBER	a,
	IN	PCVOID		buffer,
	IN	SIZE_T		buffer_size )
{
	PCUINT8	data;
	SIZE_T	data_size;
	SIZE_T	i, j;

	data = ( PCUINT8 )buffer;
	data_size = buffer_size;

	//
	// Check buffer size.
	//

	if( data_size > RSA_NUMBER_SIZE )
	{
		return STATUS_CRYPTOLIB_REPRESENTATIVE_TOO_LARGE;
	}

	//
	// Determine number size in units.
	//

	a->len = data_size / RSA_UNIT_SIZE;
	if( ( data_size % RSA_UNIT_SIZE ) != 0 ) a->len++;

	//
	// Load number from the buffer.
	//

	for( i = 0; i < ( data_size / RSA_UNIT_SIZE ); i++ )
	{
		a->num[ i ] = 0;
		for( j = 0; j < RSA_UNIT_SIZE; j++ )
		{
			a->num[ i ] |= data[ ( i * RSA_UNIT_SIZE ) + j ] << ( j * 8 );
		}
	}

	if( ( data_size % RSA_UNIT_SIZE ) != 0 )
	{
		a->num[ i ] = 0;
		for( j = 0; j < ( data_size % RSA_UNIT_SIZE ); j++ )
		{
			a->num[ i ] |= data[ ( i * RSA_UNIT_SIZE ) + j ] << ( j * 8 );
		}
	}

	//
	// Normalize number size.
	//

	while( ( a->len != 0 ) && ( a->num[ a->len - 1 ] == 0 ) )
	{
		a->len--;
	}

#ifdef CRYPTOLIB_DEBUG
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif

	return STATUS_CRYPTOLIB_SUCCESS;
}


LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
rsa_number_store(
	OUT	PVOID			buffer,
	IN	SIZE_T			buffer_size,
	IN	PCRSA_NUMBER	a )
{
	PUINT8	data;
	SIZE_T	data_size;
	SIZE_T	a_size;
	SIZE_T	i;
	SIZE_T	x, y;

	data = ( PUINT8 )buffer;
	data_size = buffer_size;

	//
	// Determine number size in bytes.
	//

	a_size = a->len * RSA_UNIT_SIZE;
	while( a_size != 0 )
	{
		x = ( a_size - 1 ) / RSA_UNIT_SIZE;
		y = ( a_size - 1 ) % RSA_UNIT_SIZE;
		if( ( UINT8 )( a->num[ x ] >> ( y * 8 ) ) != 0 ) break;
		a_size--;
	}

	//
	// Check buffer size.
	//

	if( data_size < a_size )
	{
		return STATUS_CRYPTOLIB_REPRESENTATIVE_TOO_LARGE;
	}

	//
	// Store number to buffer.
	//

	for( i = 0; i < a_size; i++ )
	{
		x = i / RSA_UNIT_SIZE;  y = i % RSA_UNIT_SIZE;
		data[ i ] = ( UINT8 )( a->num[ x ] >> ( y * 8 ) );
	}

	for( i = a_size; i < data_size; i++ )
	{
		data[ i ] = 0x00;
	}

	return STATUS_CRYPTOLIB_SUCCESS;
}


LOCAL
FORCEINLINE
BOOLEAN
rsa_number_is_zero(
	IN	PCRSA_NUMBER	a )
{
	return a->len == 0;
}


LOCAL
FORCEINLINE
VOID
rsa_number_copy_0(
	OUT	PRSA_NUMBER	a )
{
#ifdef CRYPTOLIB_DEBUG
	SIZE_T	i;
#endif

	a->len = 0;

#ifdef CRYPTOLIB_DEBUG
	for( i = n->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif
}


LOCAL
FORCEINLINE
VOID
rsa_number_copy_1(
	OUT	PRSA_NUMBER	a )
{
#ifdef CRYPTOLIB_DEBUG
	SIZE_T	i;
#endif

	a->num[ 0 ] = 1;
	a->len = 1;

#ifdef CRYPTOLIB_DEBUG
	for( i = n->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif
}


LOCAL
FORCEINLINE
VOID
rsa_number_copy(
	OUT	PRSA_NUMBER		a,
	IN	PCRSA_NUMBER	b )
{
	SIZE_T	i;

	a->len = b->len;
	for( i = 0; i < b->len; i++ ) a->num[ i ] = b->num[ i ];

#ifdef CRYPTOLIB_DEBUG
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif
}


LOCAL
FORCEINLINE
RSA_UNIT
rsa_number_test_bit(
	IN	PCRSA_NUMBER	a,
	IN	SIZE_T			n )
{
	SIZE_T	x, y;

	x = n / RSA_UNIT_BITSIZE;  y = n % RSA_UNIT_BITSIZE;

	if( x < a->len )
	{
		return ( a->num[ x ] >> y ) & 1;
	}
	else
	{
		return 0;
	}
}


LOCAL
FORCEINLINE
VOID
rsa_number_or_1(
	IN OUT	PRSA_NUMBER	a )
{
#ifdef CRYPTOLIB_DEBUG
	SIZE_T	i;
#endif

	if( a->len == 0 )
	{
		a->num[ 0 ] = 1;
		a->len = 1;
	}
	else
	{
		a->num[ 0 ] |= 1;
	}

#ifdef CRYPTOLIB_DEBUG
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif
}


LOCAL
FORCEINLINE
RSA_UNIT
rsa_number_shl(
	IN OUT	PRSA_NUMBER	a,
	IN		SIZE_T		n )
{
	RSA_UNIT	carry;
	SIZE_T		i;

	n %= RSA_UNIT_BITSIZE;
	if( n == 0 ) return 0;

	carry = 0;
	for( i = 0; i < a->len; i++ )
	{
		RSA_UNIT	temp;

		temp = a->num[ i ];
		a->num[ i ] = ( temp << n ) | carry;
		carry = temp >> ( RSA_UNIT_BITSIZE - n );
	}

	if( carry != 0 )
	{
		if( a->len < RSA_NUMBER_UNITSIZE )
		{
			a->num[ a->len ] = carry;
			a->len++;
			carry = 0;
		}
	}

	while( ( a->len > 0 ) && ( a->num[ a->len - 1 ] == 0 ) ) a->len--;

#ifdef CRYPTOLIB_DEBUG
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif

	return carry;
}


LOCAL
FORCEINLINE
RSA_UNIT
rsa_number_shr(
	IN OUT	PRSA_NUMBER	a,
	IN		SIZE_T		n )
{
	RSA_UNIT	carry;
	SIZE_T		i;

	n %= RSA_UNIT_BITSIZE;
	if( n == 0 ) return 0;

	carry = 0;
	for( i = a->len - 1; ( SSIZE_T )i >= 0; i-- )
	{
		RSA_UNIT	temp;

		temp = a->num[ i ];
		a->num[ i ] = ( temp >> n ) | ( carry << ( RSA_UNIT_BITSIZE - n ) );
		carry = temp & ( ( ( RSA_UNIT )1 << n ) - 1 );
	}

	while( ( a->len > 0 ) && ( a->num[ a->len - 1 ] == 0 ) ) a->len--;

#ifdef CRYPTOLIB_DEBUG
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif

	return carry;
}


LOCAL
FORCEINLINE
RSA_UNIT
rsa_number_sub(
	IN OUT	PRSA_NUMBER		a,
	IN		PCRSA_NUMBER	b )
{
	RSA_DUNIT	carry;
	SIZE_T		len;
	SIZE_T		i;

	if( a->len > b->len )
	{
		len = a->len;
	}
	else
	{
		len = b->len;
	}

	carry = 0;
	for( i = 0; i < len; i++ )
	{
		RSA_UNIT	a_unit, b_unit;

		if( i < a->len ) a_unit = a->num[ i ]; else a_unit = 0;
		if( i < b->len ) b_unit = b->num[ i ]; else b_unit = 0;

		carry = ( RSA_DUNIT )a_unit - ( RSA_DUNIT )b_unit - carry;
		a->num[ i ] = ( RSA_UNIT )carry;
		carry >>= ( RSA_DUNIT_BITSIZE - 1 );
	}

	if( carry != 0 )
	{
		for( i = len; i < RSA_NUMBER_UNITSIZE; i++ )
		{
			a->num[ i ] = ( RSA_UNIT )-1;
		}
		a->len = RSA_NUMBER_UNITSIZE;
	}
	else
	{
		a->len = len;
		while( ( a->len > 0 ) && ( a->num[ a->len - 1 ] == 0 ) ) a->len--;
	}

#ifdef CRYPTOLIB_DEBUG
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif

	return ( RSA_UNIT )carry;
}


LOCAL
FORCEINLINE
BOOLEAN
rsa_number_equal(
	IN	PCRSA_NUMBER	a,
	IN	PCRSA_NUMBER	b )
{
	SIZE_T	i;

	if( a->len != b->len ) return FALSE;

	for( i = a->len - 1; ( SSIZE_T )i >= 0; i-- )
	{
		if( a->num[ i ] != b->num[ i ] ) return FALSE;
	}

	return TRUE;
}


LOCAL
FORCEINLINE
BOOLEAN
rsa_number_greater_or_equal(
	IN	PCRSA_NUMBER	a,
	IN	PCRSA_NUMBER	b )
{
	SIZE_T	i;

	if( a->len < b->len ) return FALSE;
	if( a->len > b->len ) return TRUE;

	for( i = a->len - 1; ( SSIZE_T )i >= 0; i-- )
	{
		if( a->num[ i ] < b->num[ i ] ) return FALSE;
		if( a->num[ i ] > b->num[ i ] ) return TRUE;
	}

	return TRUE;
}


LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
rsa_number_mul(
			PRSA_ALGORITHM	rsa_alg,
	IN OUT	PRSA_NUMBER		a,
	IN		PCRSA_NUMBER	b )
{
	PRSA_NUMBER	t;
	SIZE_T		i, j;

	t = &rsa_alg->stack_frame.number_mul.t;

	t->len = RSA_NUMBER_UNITSIZE;
	rsa_memzero( t->num, RSA_NUMBER_SIZE );

	//
	// Multiply...
	//

	for( i = 0; i < b->len; i++ )
	{
		RSA_DUNIT	carry;

		carry = 0;
		for( j = 0; j < a->len; j++ )
		{
			carry += ( RSA_DUNIT )a->num[ j ] * ( RSA_DUNIT )b->num[ i ];
			carry += t->num[ i + j ];
			t->num[ i + j ] = ( RSA_UNIT )carry;
			carry >>= RSA_UNIT_BITSIZE;
		}
		if( ( i + j ) >= RSA_NUMBER_UNITSIZE )
		{
			return STATUS_CRYPTOLIB_OVERFLOW;
		}
		t->num[ i + j ] = t->num[ i + j ] + ( RSA_UNIT )carry;
	}

	//
	// Determine size of the product.
	//

	while( ( t->len > 0 ) && ( t->num[ t->len - 1 ] == 0 ) ) t->len--;

	rsa_number_copy( a, t );

	return STATUS_CRYPTOLIB_SUCCESS;
}


LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
rsa_number_mod(
			PRSA_ALGORITHM	rsa_alg,
	IN OUT	PRSA_NUMBER		a,
	IN		PCRSA_NUMBER	b )
{
	SIZE_T		d;
	PRSA_NUMBER	c;
	SIZE_T		i, j;

	c = &rsa_alg->stack_frame.number_mod.c;

	//
	// Check for division by zero.
	//

	if( b->len == 0 ) return STATUS_CRYPTOLIB_DIVISION_BY_ZERO;

	//
	// Normalize.
	//

	rsa_number_copy( c, b );

	CRYPTOLIB_ASSERT( c->num[ c->len - 1 ] != 0 );
	for( d = 0; d < RSA_UNIT_BITSIZE; d++ )
	{
		RSA_UNIT	mask;

		mask = ( RSA_UNIT )1 << ( RSA_UNIT_BITSIZE - 1 - d );
		if( ( c->num[ c->len - 1 ] & mask ) != 0 ) break;
	}
	rsa_number_shl( c, d );
	rsa_number_shl( a, d );

	if( a->len >= RSA_NUMBER_UNITSIZE ) return STATUS_CRYPTOLIB_OVERFLOW;
	a->num[ a->len ] = 0;

	//
	// Divide...
	//

	for( i = a->len - c->len; ( SSIZE_T )i >= 0; i-- )
	{
		RSA_DUNIT	temp;
		RSA_UNIT	q;
		BOOLEAN		q_found = FALSE;
		PRSA_NUMBER	t;
		RSA_DUNIT	carry;

		t = &rsa_alg->stack_frame.number_mod.t;

		// Calculate estimated value of q.
		temp  = ( RSA_DUNIT )a->num[ i + c->len - 1 ];
		temp |= ( RSA_DUNIT )a->num[ i + c->len - 0 ] << RSA_UNIT_BITSIZE;
		temp /= c->num[ c->len - 1 ];
		if( temp > RSA_UNIT_MAX ) temp = RSA_UNIT_MAX;
		q = ( RSA_UNIT )temp;

		// Calculate actual value of q.
		while( !q_found && ( q > 0 ) )
		{
			// Multiply divisor by q (store to t).
			carry = 0;
			for( j = 0; j < c->len; j++ )
			{
				carry += ( RSA_DUNIT )c->num[ j ] * q;
				t->num[ j ] = ( RSA_UNIT )carry;
				carry >>= RSA_UNIT_BITSIZE;
			}
			CRYPTOLIB_ASSERT( j < RSA_NUMBER_UNITSIZE );
			t->num[ j ] = ( RSA_UNIT )carry;

			// Check that t not greater than current block of dividend.
			q_found = TRUE;
			for( j = c->len; ( SSIZE_T )j >= 0; j-- )
			{
				if( t->num[ j ] > a->num[ i + j ] )
				{
					q_found = FALSE;
					break;
				}
				if( t->num[ j ] < a->num[ i + j ] )
				{
					break;
				}
			}

			if( !q_found ) q--;
		}

		if( q > 0 )
		{
			// Subtract t from current block of dividend.
			carry = 0;
			for( j = 0; j <= c->len; j++ )
			{
				carry = ( RSA_DUNIT )a->num[ i + j ] - carry;
				carry -= ( RSA_DUNIT )t->num[ j ];
				a->num[ i + j ] = ( RSA_UNIT )carry;
				carry >>= RSA_DUNIT_BITSIZE - 1;
			}
			CRYPTOLIB_ASSERT( carry == 0 );
		}
	}

	//
	// Determine size of the remainder.
	//

	if( c->len < a->len ) a->len = c->len;
	while( ( a->len > 0 ) && ( a->num[ a->len - 1 ] == 0 ) ) a->len--;

	//
	// Denormalize.
	//

	rsa_number_shr( a, d );

#ifdef CRYPTOLIB_DEBUG
	// Fill not used part with ones for debugging.
	for( i = a->len; i < RSA_NUMBER_UNITSIZE; i++ )
	{
		a->num[ i ] = RSA_UNIT_MAX;
	}
#endif

	return STATUS_CRYPTOLIB_SUCCESS;
}


LOCAL
FORCEINLINE
VOID
rsa_number_mod_slow(
			PRSA_ALGORITHM	rsa_alg,
	IN OUT	PRSA_NUMBER		a,
	IN		PCRSA_NUMBER	b )
// Slow computation of remainder, only for debugging.
{
	PRSA_NUMBER	t;
	SIZE_T		i;

	t = &rsa_alg->stack_frame.number_mod.t;

	rsa_number_copy( t, a );
	rsa_number_copy_0( a );

	for( i = ( t->len * RSA_UNIT_BITSIZE ) - 1; ( SSIZE_T )i >= 0; i-- )
	{
		rsa_number_shl( a, 1 );

		if( rsa_number_test_bit( t, i ) )
		{
			rsa_number_or_1( a );
		}

		if( rsa_number_greater_or_equal( a, b ) )
		{
			rsa_number_sub( a, b );
		}
	}
}


LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
rsa_number_mul_mod(
			PRSA_ALGORITHM	rsa_alg,
	IN OUT	PRSA_NUMBER		a,
	IN		PCRSA_NUMBER	b,
	IN		PCRSA_NUMBER	c )
{
	CRYPTOLIB_STATUS	status;

	status = rsa_number_mul( rsa_alg, a, b );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) return status;

	status = rsa_number_mod( rsa_alg, a, c );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) return status;

	return STATUS_CRYPTOLIB_SUCCESS;
}


LOCAL
FORCEINLINE
CRYPTOLIB_STATUS
rsa_number_mod_exp(
		PRSA_ALGORITHM	rsa_alg,
	OUT	PRSA_NUMBER		o,
	IN	PCRSA_NUMBER	i,
	IN	PCRSA_NUMBER	e,
	IN	PCRSA_NUMBER	m )
{
	PRSA_NUMBER			i2;
	SIZE_T				bit;
	CRYPTOLIB_STATUS	status;

	i2 = &rsa_alg->stack_frame.number_mod_exp.i2;

	rsa_number_copy_1( o );
	rsa_number_copy( i2, i );

	for( bit = 0; bit < ( e->len * RSA_UNIT_BITSIZE ); bit++ )
	{
		if( rsa_number_test_bit( e, bit ) )
		{
			status = rsa_number_mul_mod( rsa_alg, o, i2, m );
			if( status != STATUS_CRYPTOLIB_SUCCESS ) return status;
		}

		status = rsa_number_mul_mod( rsa_alg, i2, i2, m );
		if( status != STATUS_CRYPTOLIB_SUCCESS ) return status;
	}

	return STATUS_CRYPTOLIB_SUCCESS;
}


EXTERN_C
SIZE_T
CRYPTOLIB_API
rsa_alg_get_size(
	VOID )
{
	CRYPTOLIB_PAGED_CODE();

	return sizeof( RSA_ALGORITHM );
}


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
	IN	PASYMMETRIC_DO_PVT	fn_do_pvt )
{
	CRYPTOLIB_PAGED_CODE();

	rsa_memzero( rsa_alg, sizeof( RSA_ALGORITHM ) );

	if( key_bitsize < RSA_KEY_MIN_BITSIZE )
	{
		return STATUS_CRYPTOLIB_INVALID_KEY;
	}

	if( key_bitsize > RSA_KEY_MAX_BITSIZE )
	{
		return STATUS_CRYPTOLIB_INVALID_KEY;
	}

	rsa_alg->alg.key_bitsize = key_bitsize;
	rsa_alg->alg.key_size = key_bitsize / 8;
	if( ( key_bitsize % 8 ) != 0 ) rsa_alg->alg.key_size++;

	if( key_modulus == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_modulus );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_modulus, key_modulus, rsa_alg->alg.key_size );
	}

	if( key_pub_exponent == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_pub_exponent );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_pub_exponent, key_pub_exponent, rsa_alg->alg.key_size );
	}

	if( key_pvt_exponent == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_pvt_exponent );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_pvt_exponent, key_pvt_exponent, rsa_alg->alg.key_size );
	}

	if( key_p == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_p );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_p, key_p, rsa_alg->alg.key_size );
	}

	if( key_q == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_q );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_q, key_q, rsa_alg->alg.key_size );
	}

	if( key_dp == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_dp );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_dp, key_dp, rsa_alg->alg.key_size );
	}

	if( key_dq == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_dq );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_dq, key_dq, rsa_alg->alg.key_size );
	}

	if( key_inverse_q == NULL )
	{
		rsa_number_copy_0( &rsa_alg->key_inverse_q );
	}
	else
	{
		rsa_number_load( &rsa_alg->key_inverse_q, key_inverse_q, rsa_alg->alg.key_size );
	}

	rsa_alg->alg.do_pub = fn_do_pub;
	rsa_alg->alg.do_pvt = fn_do_pvt;

	return STATUS_CRYPTOLIB_SUCCESS;
}


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
	IN	PCVOID			key_inverse_q )
{
	CRYPTOLIB_PAGED_CODE();

	return rsa_alg_create_no_relocs( rsa_alg,
		key_bitsize, key_modulus, key_pub_exponent, key_pvt_exponent,
		key_p, key_q, key_dp, key_dq, key_inverse_q,
		rsa_do_pub, rsa_do_pvt );
}
#endif


EXTERN_C
VOID
CRYPTOLIB_API
rsa_alg_delete(
		PRSA_ALGORITHM	rsa_alg )
{
	CRYPTOLIB_PAGED_CODE();

	rsa_memzero( rsa_alg, sizeof( RSA_ALGORITHM ) );
}


EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
rsa_do_pub(
		PASYMMETRIC_ALGORITHM	alg,
	IN	PCVOID					input,
	OUT	PVOID					output )
{
	PRSA_ALGORITHM		rsa_alg;
	SIZE_T				key_size;
	PRSA_NUMBER			i;
	PRSA_NUMBER			o;
	CRYPTOLIB_STATUS	status;

	CRYPTOLIB_PAGED_CODE();

	rsa_alg = ( PRSA_ALGORITHM )alg;
	key_size = alg->key_size;

	i = &rsa_alg->stack_frame.do_pub.i;
	o = &rsa_alg->stack_frame.do_pub.o;

	if( rsa_alg->key_modulus.len == 0 )
	{
		status = STATUS_CRYPTOLIB_KEY_NOT_SET;
		goto done;
	}
	if( rsa_alg->key_pub_exponent.len == 0 )
	{
		status = STATUS_CRYPTOLIB_KEY_NOT_SET;
		goto done;
	}

	status = rsa_number_load( i, input, key_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	if( rsa_number_greater_or_equal( i, &rsa_alg->key_modulus ) )
	{
		status = STATUS_CRYPTOLIB_REPRESENTATIVE_TOO_LARGE;
		goto done;
	}

	status = rsa_number_mod_exp( rsa_alg, o, i, &rsa_alg->key_pub_exponent, &rsa_alg->key_modulus );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	status = rsa_number_store( output, key_size, o );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	rsa_memzero( &rsa_alg->stack_frame, sizeof( RSA_STACK_FRAME ) );

	return status;
}


EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
rsa_do_pvt(
		PASYMMETRIC_ALGORITHM	alg,
	IN	PCVOID					input,
	OUT	PVOID					output )
{
	PRSA_ALGORITHM		rsa_alg;
	SIZE_T				key_size;
	PRSA_NUMBER			i;
	PRSA_NUMBER			o;
	CRYPTOLIB_STATUS	status;

	CRYPTOLIB_PAGED_CODE();

	rsa_alg = ( PRSA_ALGORITHM )alg;
	key_size = alg->key_size;

	i = &rsa_alg->stack_frame.do_pvt.i;
	o = &rsa_alg->stack_frame.do_pvt.o;

	if( rsa_alg->key_modulus.len == 0 )
	{
		status = STATUS_CRYPTOLIB_KEY_NOT_SET;
		goto done;
	}
	if( rsa_alg->key_pvt_exponent.len == 0 )
	{
		status = STATUS_CRYPTOLIB_KEY_NOT_SET;
		goto done;
	}

	status = rsa_number_load( i, input, key_size );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	if( rsa_number_greater_or_equal( i, &rsa_alg->key_modulus ) )
	{
		status = STATUS_CRYPTOLIB_REPRESENTATIVE_TOO_LARGE;
		goto done;
	}

	status = rsa_number_mod_exp( rsa_alg, o, i, &rsa_alg->key_pvt_exponent, &rsa_alg->key_modulus );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	status = rsa_number_store( output, key_size, o );
	if( status != STATUS_CRYPTOLIB_SUCCESS ) goto done;

	status = STATUS_CRYPTOLIB_SUCCESS;

done:

	rsa_memzero( &rsa_alg->stack_frame, sizeof( RSA_STACK_FRAME ) );

	return status;
}
