//
//	cryptolib.sha1.c
//
//	SHA1 hash algorithm implementation.
//


#include "defines.h"
#include "cryptolib.sha1.h"


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


#ifdef CRYPTOLIB_CODE_SECTION
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_alg_get_size )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_alg_create_no_relocs )
#ifndef CRYPTOLIB_NO_RELOCS
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_alg_create )
#endif
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_alg_delete )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_init )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_process )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_finish )
#pragma alloc_text( CRYPTOLIB_CODE_SECTION, sha1_compute )
#endif


LOCAL
FORCEINLINE
VOID
sha1_memset(
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
sha1_memzero(
	OUT	PVOID	dst,
	IN	SIZE_T	size )
{
	sha1_memset( dst, size, 0 );
}


LOCAL
FORCEINLINE
VOID
sha1_memcopy(
	OUT	PVOID	dst,
	IN	PCVOID	src,
	IN	SIZE_T	size )
{
	PUINT8	d;
	PCUINT8	s;
	SIZE_T	i;

	d = ( PUINT8 )dst;
	s = ( PUINT8 )src;
	for( i = 0; i < size; i++ )
	{
		d[ i ] = s[ i ];
	}
}


LOCAL
FORCEINLINE
VOID
sha1_load(
	OUT	PUINT32	values,
	IN	SIZE_T	values_count,
	IN	PCUINT8	bytes )
{
	SIZE_T	i;

	for( i = 0; i < values_count; i++ )
	{
		values[ i ] = 0;
		values[ i ] |= ( UINT32 )bytes[ ( i * sizeof( UINT32 ) ) + 0 ] << 24;
		values[ i ] |= ( UINT32 )bytes[ ( i * sizeof( UINT32 ) ) + 1 ] << 16;
		values[ i ] |= ( UINT32 )bytes[ ( i * sizeof( UINT32 ) ) + 2 ] <<  8;
		values[ i ] |= ( UINT32 )bytes[ ( i * sizeof( UINT32 ) ) + 3 ] <<  0;
	}
}


LOCAL
FORCEINLINE
VOID
sha1_store(
	IN	PCUINT32	values,
	IN	SIZE_T		values_count,
	OUT	PUINT8		bytes )
{
	SIZE_T	i;

	for( i = 0; i < values_count; i++ )
	{
		bytes[ ( i * sizeof( UINT32 ) ) + 0 ] = ( UINT8 )( values[ i ] >> 24 );
		bytes[ ( i * sizeof( UINT32 ) ) + 1 ] = ( UINT8 )( values[ i ] >> 16 );
		bytes[ ( i * sizeof( UINT32 ) ) + 2 ] = ( UINT8 )( values[ i ] >>  8 );
		bytes[ ( i * sizeof( UINT32 ) ) + 3 ] = ( UINT8 )( values[ i ] >>  0 );
	}
}


LOCAL
FORCEINLINE
UINT32
sha1_rol(
	IN	UINT32	v,
	IN	SIZE_T	n )
{
	return ( v << n ) | ( v >> ( 32 - n ) );
}


LOCAL
FORCEINLINE
UINT32
sha1_blk(
	IN	PUINT32	block,
	IN	SIZE_T	i )
{
	UINT32	v;

	v  = block[ ( i + 13 ) % 16 ];
	v ^= block[ ( i +  8 ) % 16 ];
	v ^= block[ ( i +  2 ) % 16 ];
	v ^= block[ ( i +  0 ) % 16 ];
	v  = sha1_rol( v, 1 );

	block[ i % 16 ] = v;

	return v;
}


LOCAL
FORCEINLINE
UINT32
sha1_r0(
	IN	UINT32	v,
	IN	UINT32	w,
	IN	UINT32	x,
	IN	UINT32	y,
	IN	PUINT32	block,
	IN	SIZE_T	i )
{
	return ( ( w & ( x ^ y ) ) ^ y ) + block[ i ] + 0x5A827999 + sha1_rol( v, 5 );
}


LOCAL
FORCEINLINE
UINT32
sha1_r1(
	IN	UINT32	v,
	IN	UINT32	w,
	IN	UINT32	x,
	IN	UINT32	y,
	IN	PUINT32	block,
	IN	SIZE_T	i )
{
	return ( ( w & ( x ^ y ) ) ^ y ) + sha1_blk( block, i ) + 0x5A827999 + sha1_rol( v, 5 );
}


LOCAL
FORCEINLINE
UINT32
sha1_r2(
	IN	UINT32	v,
	IN	UINT32	w,
	IN	UINT32	x,
	IN	UINT32	y,
	IN	PUINT32	block,
	IN	SIZE_T	i )
{
	return ( w ^ x ^ y ) + sha1_blk( block, i ) + 0x6ED9EBA1 + sha1_rol( v, 5 );
}


LOCAL
FORCEINLINE
UINT32
sha1_r3(
	IN	UINT32	v,
	IN	UINT32	w,
	IN	UINT32	x,
	IN	UINT32	y,
	IN	PUINT32	block,
	IN	SIZE_T	i )
{
	return ( ( ( w | x ) & y ) | ( w & x ) ) + sha1_blk( block, i ) + 0x8F1BBCDC + sha1_rol( v, 5 );
}


LOCAL
FORCEINLINE
UINT32
sha1_r4(
	IN	UINT32	v,
	IN	UINT32	w,
	IN	UINT32	x,
	IN	UINT32	y,
	IN	PUINT32	block,
	IN	SIZE_T	i )
{
	return ( w ^ x ^ y ) + sha1_blk( block, i ) + 0xCA62C1D6 + sha1_rol( v, 5 );
}


LOCAL
FORCEINLINE
VOID
sha1_transform(
		PSHA1_ALGORITHM	sha1_alg,
	IN	PCUINT8			bytes )
{
	PSHA1_STATE	state;
	UINT32		a, b, c, d, e;
	UINT32		block[ 16 ];

	state = &sha1_alg->state;

	//
	// Load the input.
	//

	sha1_load( block, 16, bytes );

	//
	// Load state into our registers.
	//

	a = state->value[ 0 ];
	b = state->value[ 1 ];
	c = state->value[ 2 ];
	d = state->value[ 3 ];
	e = state->value[ 4 ];

	//
	// Transform...
	//

	e += sha1_r0( a, b, c, d, block,  0 );  b = sha1_rol( b, 30 );
	d += sha1_r0( e, a, b, c, block,  1 );  a = sha1_rol( a, 30 );
	c += sha1_r0( d, e, a, b, block,  2 );  e = sha1_rol( e, 30 );
	b += sha1_r0( c, d, e, a, block,  3 );  d = sha1_rol( d, 30 );
	a += sha1_r0( b, c, d, e, block,  4 );  c = sha1_rol( c, 30 );
	e += sha1_r0( a, b, c, d, block,  5 );  b = sha1_rol( b, 30 );
	d += sha1_r0( e, a, b, c, block,  6 );  a = sha1_rol( a, 30 );
	c += sha1_r0( d, e, a, b, block,  7 );  e = sha1_rol( e, 30 );
	b += sha1_r0( c, d, e, a, block,  8 );  d = sha1_rol( d, 30 );
	a += sha1_r0( b, c, d, e, block,  9 );  c = sha1_rol( c, 30 );
	e += sha1_r0( a, b, c, d, block, 10 );  b = sha1_rol( b, 30 );
	d += sha1_r0( e, a, b, c, block, 11 );  a = sha1_rol( a, 30 );
	c += sha1_r0( d, e, a, b, block, 12 );  e = sha1_rol( e, 30 );
	b += sha1_r0( c, d, e, a, block, 13 );  d = sha1_rol( d, 30 );
	a += sha1_r0( b, c, d, e, block, 14 );  c = sha1_rol( c, 30 );
	e += sha1_r0( a, b, c, d, block, 15 );  b = sha1_rol( b, 30 );

	d += sha1_r1( e, a, b, c, block, 16 );  a = sha1_rol( a, 30 );
	c += sha1_r1( d, e, a, b, block, 17 );  e = sha1_rol( e, 30 );
	b += sha1_r1( c, d, e, a, block, 18 );  d = sha1_rol( d, 30 );
	a += sha1_r1( b, c, d, e, block, 19 );  c = sha1_rol( c, 30 );

	e += sha1_r2( a, b, c, d, block, 20 );  b = sha1_rol( b, 30 );
	d += sha1_r2( e, a, b, c, block, 21 );  a = sha1_rol( a, 30 );
	c += sha1_r2( d, e, a, b, block, 22 );  e = sha1_rol( e, 30 );
	b += sha1_r2( c, d, e, a, block, 23 );  d = sha1_rol( d, 30 );
	a += sha1_r2( b, c, d, e, block, 24 );  c = sha1_rol( c, 30 );
	e += sha1_r2( a, b, c, d, block, 25 );  b = sha1_rol( b, 30 );
	d += sha1_r2( e, a, b, c, block, 26 );  a = sha1_rol( a, 30 );
	c += sha1_r2( d, e, a, b, block, 27 );  e = sha1_rol( e, 30 );
	b += sha1_r2( c, d, e, a, block, 28 );  d = sha1_rol( d, 30 );
	a += sha1_r2( b, c, d, e, block, 29 );  c = sha1_rol( c, 30 );
	e += sha1_r2( a, b, c, d, block, 30 );  b = sha1_rol( b, 30 );
	d += sha1_r2( e, a, b, c, block, 31 );  a = sha1_rol( a, 30 );
	c += sha1_r2( d, e, a, b, block, 32 );  e = sha1_rol( e, 30 );
	b += sha1_r2( c, d, e, a, block, 33 );  d = sha1_rol( d, 30 );
	a += sha1_r2( b, c, d, e, block, 34 );  c = sha1_rol( c, 30 );
	e += sha1_r2( a, b, c, d, block, 35 );  b = sha1_rol( b, 30 );
	d += sha1_r2( e, a, b, c, block, 36 );  a = sha1_rol( a, 30 );
	c += sha1_r2( d, e, a, b, block, 37 );  e = sha1_rol( e, 30 );
	b += sha1_r2( c, d, e, a, block, 38 );  d = sha1_rol( d, 30 );
	a += sha1_r2( b, c, d, e, block, 39 );  c = sha1_rol( c, 30 );

	e += sha1_r3( a, b, c, d, block, 40 );  b = sha1_rol( b, 30 );
	d += sha1_r3( e, a, b, c, block, 41 );  a = sha1_rol( a, 30 );
	c += sha1_r3( d, e, a, b, block, 42 );  e = sha1_rol( e, 30 );
	b += sha1_r3( c, d, e, a, block, 43 );  d = sha1_rol( d, 30 );
	a += sha1_r3( b, c, d, e, block, 44 );  c = sha1_rol( c, 30 );
	e += sha1_r3( a, b, c, d, block, 45 );  b = sha1_rol( b, 30 );
	d += sha1_r3( e, a, b, c, block, 46 );  a = sha1_rol( a, 30 );
	c += sha1_r3( d, e, a, b, block, 47 );  e = sha1_rol( e, 30 );
	b += sha1_r3( c, d, e, a, block, 48 );  d = sha1_rol( d, 30 );
	a += sha1_r3( b, c, d, e, block, 49 );  c = sha1_rol( c, 30 );
	e += sha1_r3( a, b, c, d, block, 50 );  b = sha1_rol( b, 30 );
	d += sha1_r3( e, a, b, c, block, 51 );  a = sha1_rol( a, 30 );
	c += sha1_r3( d, e, a, b, block, 52 );  e = sha1_rol( e, 30 );
	b += sha1_r3( c, d, e, a, block, 53 );  d = sha1_rol( d, 30 );
	a += sha1_r3( b, c, d, e, block, 54 );  c = sha1_rol( c, 30 );
	e += sha1_r3( a, b, c, d, block, 55 );  b = sha1_rol( b, 30 );
	d += sha1_r3( e, a, b, c, block, 56 );  a = sha1_rol( a, 30 );
	c += sha1_r3( d, e, a, b, block, 57 );  e = sha1_rol( e, 30 );
	b += sha1_r3( c, d, e, a, block, 58 );  d = sha1_rol( d, 30 );
	a += sha1_r3( b, c, d, e, block, 59 );  c = sha1_rol( c, 30 );

	e += sha1_r4( a, b, c, d, block, 60 );  b = sha1_rol( b, 30 );
	d += sha1_r4( e, a, b, c, block, 61 );  a = sha1_rol( a, 30 );
	c += sha1_r4( d, e, a, b, block, 62 );  e = sha1_rol( e, 30 );
	b += sha1_r4( c, d, e, a, block, 63 );  d = sha1_rol( d, 30 );
	a += sha1_r4( b, c, d, e, block, 64 );  c = sha1_rol( c, 30 );
	e += sha1_r4( a, b, c, d, block, 65 );  b = sha1_rol( b, 30 );
	d += sha1_r4( e, a, b, c, block, 66 );  a = sha1_rol( a, 30 );
	c += sha1_r4( d, e, a, b, block, 67 );  e = sha1_rol( e, 30 );
	b += sha1_r4( c, d, e, a, block, 68 );  d = sha1_rol( d, 30 );
	a += sha1_r4( b, c, d, e, block, 69 );  c = sha1_rol( c, 30 );
	e += sha1_r4( a, b, c, d, block, 70 );  b = sha1_rol( b, 30 );
	d += sha1_r4( e, a, b, c, block, 71 );  a = sha1_rol( a, 30 );
	c += sha1_r4( d, e, a, b, block, 72 );  e = sha1_rol( e, 30 );
	b += sha1_r4( c, d, e, a, block, 73 );  d = sha1_rol( d, 30 );
	a += sha1_r4( b, c, d, e, block, 74 );  c = sha1_rol( c, 30 );
	e += sha1_r4( a, b, c, d, block, 75 );  b = sha1_rol( b, 30 );
	d += sha1_r4( e, a, b, c, block, 76 );  a = sha1_rol( a, 30 );
	c += sha1_r4( d, e, a, b, block, 77 );  e = sha1_rol( e, 30 );
	b += sha1_r4( c, d, e, a, block, 78 );  d = sha1_rol( d, 30 );
	a += sha1_r4( b, c, d, e, block, 79 );  c = sha1_rol( c, 30 );

	//
	// Update state.
	//

	state->value[ 0 ] += a;
	state->value[ 1 ] += b;
	state->value[ 2 ] += c;
	state->value[ 3 ] += d;
	state->value[ 4 ] += e;

	//
	// Wipe variables.
	//

	a = b = c = d = e = 0;
	sha1_memzero( block, sizeof( block ) );
}


EXTERN_C
SIZE_T
CRYPTOLIB_API
sha1_alg_get_size(
	VOID )
{
	CRYPTOLIB_PAGED_CODE();

	return sizeof( SHA1_ALGORITHM );
}


EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
sha1_alg_create_no_relocs(
		PSHA1_ALGORITHM	sha1_alg,
	IN	PHASH_INIT		fn_init,
	IN	PHASH_PROCESS	fn_process,
	IN	PHASH_FINISH	fn_finish,
	IN	PHASH_COMPUTE	fn_compute )
{
	CRYPTOLIB_PAGED_CODE();

	sha1_memzero( sha1_alg, sizeof( SHA1_ALGORITHM ) );

	sha1_alg->alg.id = SHA1_ALGORITHM_ID;

	sha1_alg->alg.hash_bitsize = SHA1_HASH_BITSIZE;
	sha1_alg->alg.hash_size = SHA1_HASH_SIZE;

	sha1_alg->alg.init    = fn_init;
	sha1_alg->alg.process = fn_process;
	sha1_alg->alg.finish  = fn_finish;
	sha1_alg->alg.compute = fn_compute;

	return STATUS_CRYPTOLIB_SUCCESS;
}


#ifndef CRYPTOLIB_NO_RELOCS
EXTERN_C
CRYPTOLIB_STATUS
CRYPTOLIB_API
sha1_alg_create(
		PSHA1_ALGORITHM	sha1_alg )
{
	CRYPTOLIB_PAGED_CODE();

	return sha1_alg_create_no_relocs( sha1_alg,
		sha1_init, sha1_process, sha1_finish, sha1_compute );
}
#endif


EXTERN_C
VOID
CRYPTOLIB_API
sha1_alg_delete(
		PSHA1_ALGORITHM	sha1_alg )
{
	CRYPTOLIB_PAGED_CODE();

	sha1_memzero( sha1_alg, sizeof( SHA1_ALGORITHM ) );
}


EXTERN_C
VOID
CRYPTOLIB_API
sha1_init(
		PHASH_ALGORITHM	alg )
{
	PSHA1_ALGORITHM	sha1_alg;
	PSHA1_STATE		state;

	CRYPTOLIB_PAGED_CODE();

	sha1_alg = ( PSHA1_ALGORITHM )alg;
	state = &sha1_alg->state;

	state->value[ 0 ] = 0x67452301;
	state->value[ 1 ] = 0xEFCDAB89;
	state->value[ 2 ] = 0x98BADCFE;
	state->value[ 3 ] = 0x10325476;
	state->value[ 4 ] = 0xC3D2E1F0;

	state->count = 0;

	sha1_memzero( state->buffer, 64 );
}


EXTERN_C
VOID
CRYPTOLIB_API
sha1_process(
		PHASH_ALGORITHM	alg,
	IN	PCVOID			buffer,
	IN	SIZE_T			buffer_size )
{
	PSHA1_ALGORITHM	sha1_alg;
	PSHA1_STATE		state;
	PCUINT8			bytes;
	SIZE_T			bytes_size;
	SIZE_T			index;
	SIZE_T			partial_size;
	SIZE_T			i;

	CRYPTOLIB_PAGED_CODE();

	sha1_alg = ( PSHA1_ALGORITHM )alg;
	state = &sha1_alg->state;

	bytes = ( PCUINT8 )buffer;
	bytes_size = buffer_size;

	//
	// Transform as many times as possible.
	//

	index = ( SIZE_T )( ( state->count / 8 ) % 64 );
	partial_size = 64 - index;

	if( bytes_size >= partial_size )
	{
		sha1_memcopy( &state->buffer[ index ], bytes, partial_size );
		sha1_transform( sha1_alg, state->buffer );

		for( i = partial_size; ( i + 63 ) < bytes_size; i += 64 )
		{
			sha1_transform( sha1_alg, bytes + i );
		}

		index = 0;
	}
	else
	{
		i = 0;
	}

	//
	// Buffer remaining input.
	//

	sha1_memcopy( &state->buffer[ index ], bytes + i, bytes_size - i );

	//
	// Update number of bits.
	//

	state->count += ( UINT64 )bytes_size * 8;
}


EXTERN_C
VOID
CRYPTOLIB_API
sha1_finish(
		PHASH_ALGORITHM	alg,
	OUT	PVOID			hash )
{
	PSHA1_ALGORITHM	sha1_alg;
	PSHA1_STATE		state;
	UINT8			bits[ 8 ];
	SIZE_T			index;
	UINT8			padding[ 64 ];
	SIZE_T			padding_size;

	CRYPTOLIB_PAGED_CODE();

	sha1_alg = ( PSHA1_ALGORITHM )alg;
	state = &sha1_alg->state;

	//
	// Save number of bits.
	//

	bits[ 0 ] = ( UINT8 )( state->count >> 56 );
	bits[ 1 ] = ( UINT8 )( state->count >> 48 );
	bits[ 2 ] = ( UINT8 )( state->count >> 40 );
	bits[ 3 ] = ( UINT8 )( state->count >> 32 );
	bits[ 4 ] = ( UINT8 )( state->count >> 24 );
	bits[ 5 ] = ( UINT8 )( state->count >> 16 );
	bits[ 6 ] = ( UINT8 )( state->count >>  8 );
	bits[ 7 ] = ( UINT8 )( state->count >>  0 );

	//
	// Pad out to 56 mod 64.
	//

	sha1_memzero( padding, 64 );
	padding[ 0 ] = 0x80;

	index = ( SIZE_T )( ( state->count / 8 ) % 64 );
	if( index < 56 )
	{
		padding_size = 56 - index;
	}
	else
	{
		padding_size = ( 64 + 56 ) - index;
	}
	alg->process( alg, padding, padding_size );

	//
	// Append length.
	//

	alg->process( alg, bits, 8 );

	//
	// Store state in digest.
	//

	sha1_store( state->value, 5, ( PUINT8 )hash );

	//
	// Wipe state.
	//

	sha1_memzero( state, sizeof( SHA1_STATE ) );
}


EXTERN_C
VOID
CRYPTOLIB_API
sha1_compute(
		PHASH_ALGORITHM	alg,
	IN	PCVOID			buffer,
	IN	SIZE_T			buffer_size,
	OUT	PVOID			hash )
{
	CRYPTOLIB_PAGED_CODE();

	alg->init( alg );
	alg->process( alg, buffer, buffer_size );
	alg->finish( alg, hash );
}
