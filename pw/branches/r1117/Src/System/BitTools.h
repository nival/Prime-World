#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// трюки с битами
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Return the next power of 2 higher than the input
// If the input is already a power of 2, the output will be the same as the input.
// Got this from Brian Sharp's sweng mailing list.
inline int GetNextPow2( DWORD n )
{
	n -= 1;
	n |= n >> 16;
	n |= n >> 8;
	n |= n >> 4;
	n |= n >> 2;
	n |= n >> 1;

	return n + 1;
}
inline int GetNextPow2( int n ) { return GetNextPow2( DWORD(n) ); }

// получить старший включенный бит
inline int GetMSB( DWORD n )
{
	int k = 0;
	if ( n & 0xFFFF0000 ) k = 16, n >>= 16;
	if ( n & 0x0000FF00 ) k += 8, n >>= 8;
	if ( n & 0x000000F0 ) k += 4, n >>= 4;
	if ( n & 0x0000000C ) k += 2, n >>= 2;
	if ( n & 0x00000002 ) k += 1;
	return k;
}
inline int GetMSB( int n ) { return GetMSB( DWORD(n) ); }
inline int GetMSB( WORD n )
{
	int k = 0;
	if ( n & 0xFF00 ) k	= 8, n >>= 8;
	if ( n & 0x00F0 ) k += 4, n >>= 4;
	if ( n & 0x000C ) k += 2, n >>= 2;
	if ( n & 0x0002 ) k += 1;
	return k;
}
inline int GetMSB( short n ) { return GetMSB( WORD(n) ); }
inline int GetMSB( BYTE n )
{
	int k = 0;
	if ( n & 0xF0 ) k	= 4, n >>= 4;
	if ( n & 0x0C ) k += 2, n >>= 2;
	if ( n & 0x02 ) k += 1;
	return k;
}
inline int GetMSB( char n ) { return GetMSB( BYTE(n) ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// получить младший включенный бит
inline int GetLSB( DWORD n )
{
	int k = 0;
	if ( (n & 0x0000FFFF) == 0 ) k = 16, n >>= 16;
	if ( (n & 0x000000FF) == 0 ) k += 8, n >>= 8;
	if ( (n & 0x0000000F) == 0 ) k += 4, n >>= 4;
	if ( (n & 0x00000003) == 0 ) k += 2, n >>= 2;
	if ( (n & 0x00000001) == 0 ) k += 1;
	return k;
}
inline int GetLSB( int n ) { return GetLSB( DWORD(n) ); }
inline int GetLSB( WORD n )
{
	int k = 0;
	if ( (n & 0x00FF) == 0 ) k	= 8, n >>= 8;
	if ( (n & 0x000F) == 0 ) k += 4, n >>= 4;
	if ( (n & 0x0003) == 0 ) k += 2, n >>= 2;
	if ( (n & 0x0001) == 0 ) k += 1;
	return k;
}
inline int GetLSB( short n ) { return GetLSB( WORD(n) ); }
inline int GetLSB( BYTE n )
{
	int k = 0;
	if ( (n & 0x0F) == 0 ) k	= 4, n >>= 4;
	if ( (n & 0x03) == 0 ) k += 2, n >>= 2;
	if ( (n & 0x01) == 0 ) k += 1;
	return k;
}
inline int GetLSB( char n ) { return GetLSB( BYTE(n) ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// подсчёт колличества ненулевых бит в числе
// 0x49249249ul // = 0100_1001_0010_0100_1001_0010_0100_1001
// 0x381c0e07ul // = 0011_1000_0001_1100_0000_1110_0000_0111
inline int GetNumBits( DWORD v )
{
	v = (v & 0x49249249ul) + ((v >> 1) & 0x49249249ul) + ((v >> 2) & 0x49249249ul);
	v = ((v + (v >> 3)) & 0x381c0e07ul) + ((v >> 6) & 0x381c0e07ul);
	return int( (v + (v >> 9) + (v >> 18) + (v >> 27)) & 0x3f );
}
inline int GetNumBits( int v ) { return GetNumBits( DWORD(v) ); }
inline int GetNumBits( BYTE v )
{
	v = (v & 0x55) + ((v >> 1) & 0x55);
	v = (v & 0x33) + ((v >> 2) & 0x33);
	return int( (v & 0x0f) + ((v >> 4) & 0x0f) );
}
inline int GetNumBits( char v ) { return GetNumBits( BYTE(v) ); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
