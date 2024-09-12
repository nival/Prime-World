#ifndef BITDATA_H_
#define BITDATA_H_

#include "2DArray.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class CBitArray2DRLEWrapper;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CArray1Bit
{
	int xSize;
	vector<BYTE> array;

	const BYTE GetByteMask( int nIndex ) const { return ( nIndex == 0 ) ? 0xFF : 0xFF >> ( 8 - nIndex ); }
public:
	int operator&( _interface IBinSaver &saver ) { saver.Add( 1, &array ); saver.Add( 2, &xSize ); return 0; }

  CArray1Bit() : xSize(0) {}
	CArray1Bit( const int size ) { SetSize( size ); }
	CArray1Bit( const CArray1Bit &a ) : xSize( a.xSize ), array( a.array ) { }
	~CArray1Bit() {}
	//
	const CArray1Bit& operator=( const CArray1Bit &a ) { xSize = a.xSize; array = a.array; return *this; }
	//
	void SetSize( const int size ) { xSize = size; if ( !IsEmpty() ) array.resize( ( ( size-1 ) >> 3) + 1 ); }
	void Clear() { xSize = 0; array.clear(); }
	void FillZero() { if ( !IsEmpty() ) memset( &(array[0]), 0, array.size() ); }

	//
	int GetSize() const { return xSize; }
	bool IsEmpty() const { return xSize == 0; }

	//
	void SetData( const int n ) { array[n >> 3] |= 1 << (n & 7); }
	const BYTE GetData( const int n ) const { return ( array[n >> 3] >> (n & 7) ) & 1; }
	void RemoveData( const int n ) { array[n >> 3] &= ~( 1 << (n & 7) ); }

	//
	bool operator==( const CArray1Bit &a ) const
	{
		if ( a.xSize != xSize )
			return false;
		if ( xSize == 0 )
			return true;
		const int nSize = ( xSize - 1 ) >> 3;
		for ( int i = 0; i < nSize; ++i )
			if ( array[i] != a.array[i] )
				return false;
		const int nLastSizeMask = GetByteMask( xSize & 0x00000007 );
		return ( array[nSize] & nLastSizeMask ) == ( a.array[nSize] & nLastSizeMask );
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool operator>( const CArray1Bit &a ) const
	{
		if ( IsEmpty() )
			return false;
		if ( a.IsEmpty() )
			return true;
		const int nSize = ( xSize - 1 ) >> 3;
		int nLastSizeMask = GetByteMask( xSize & 0x00000007 );
		const int nSizeA = ( a.xSize - 1) >> 3;
		int nLastSizeAMask = GetByteMask( a.xSize & 0x00000007 );
		int i = nSize;
		if ( nSize > nSizeA )
		{
			if ( ( array[nSize] & nLastSizeMask ) > 0 )
				return true;
			for ( i = nSize - 1; i > nSizeA; --i )
				if ( array[i] > 0 )
					return true;
			nLastSizeMask = 0xFF;
		}
		else if ( nSize < nSizeA )
		{
			if ( ( a.array[nSizeA] & nLastSizeAMask ) > 0 )
				return false;
			for ( i = nSizeA - 1; i > nSize; --i )
				if ( a.array[i] > 0 )
					return false;
			nLastSizeAMask = 0xFF;
		}
		if ( ( array[i] & nLastSizeMask ) > ( a.array[i] & nLastSizeAMask ) )
			return true;
		for ( --i; i >= 0; --i )
			if ( array[i] > a.array[i] )
				return true;
		return false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool operator<( const CArray1Bit &a ) const
	{
		if ( a.IsEmpty() )
			return false;
		if ( IsEmpty() )
			return true;
		const int nSize = ( xSize - 1 ) >> 3;
		int nLastSizeMask = GetByteMask( xSize & 0x00000007 );
		const int nSizeA = ( a.xSize - 1) >> 3;
		int nLastSizeAMask = GetByteMask( a.xSize & 0x00000007 );
		int i = nSize;
		if ( nSize > nSizeA )
		{
			if ( ( array[nSize] & nLastSizeMask ) > 0 )
				return false;
			for ( i = nSize - 1; i > nSizeA; --i )
				if ( array[i] > 0 )
					return false;
			nLastSizeMask = 0xFF;
		}
		else if ( nSize < nSizeA )
		{
			if ( ( a.array[nSizeA] & nLastSizeAMask ) > 0 )
				return true;
			for ( i = nSizeA - 1; i > nSize; --i )
				if ( a.array[i] > 0 )
					return true;
			nLastSizeAMask = 0xFF;
		}
		if ( ( array[i] & nLastSizeMask ) < ( a.array[i] & nLastSizeAMask ) )
			return true;
		for ( --i; i >= 0; --i )
			if ( array[i] < a.array[i] )
				return true;
		return false;
	}

	//
	void operator|=( const CArray1Bit &a )
	{
		if ( a.IsEmpty() )
			return;
		const int nSizeA = ( a.xSize - 1 ) >> 3;
		if ( nSizeA+1 > array.size() )
			array.resize( nSizeA+1, 0 );
		const int nLastSizeA = a.xSize & 0x00000007;
		for ( int i = 0; i < nSizeA; ++i )
			array[i] |= a.array[i];
		array[nSizeA] |= ( a.array[nSizeA] & GetByteMask( nLastSizeA ) );
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int operator&=( const CArray1Bit &a )
	{
		if ( IsEmpty() && a.IsEmpty() )
			return 0;
		const int nMinSize = ( xSize < a.xSize ) ? ( xSize - 1 ) >> 3 : ( a.xSize - 1 ) >> 3;
		const int nMinLastSize = ( xSize < a.xSize ) ? xSize & 0x00000007 : a.xSize & 0x00000007;
		for ( int i =0; i < nMinSize; ++i )
			array[i] &= a.array[i];
		array[nMinSize] &= ( a.array[nMinSize] | ~GetByteMask( nMinLastSize ) );
		return 0;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const CArray1Bit operator~() const
	{
		CArray1Bit a;
		a.xSize = xSize;
		if ( IsEmpty() )
			return a;
		const int nSize = ( xSize - 1 ) >> 3;
		a.array.resize( nSize + 1 );
		int nLastSize = xSize & 0x00000007;
		for ( int i = 0; i < nSize; ++i )
			a.array[i] = ~array[i];
		a.array[nSize] = ( ~array[nSize] ) & GetByteMask( nLastSize );
		return a;
	}
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CArray1Bit operator<<( int n )
  {
    if (n <= 0)
      return *this;

    CArray1Bit shifted(GetSize());
    shifted.FillZero();

    int numBytes = n >> 3;
    int numBits = n & 7;

    int targ = 0;
    int src = numBytes;
    for (; targ < array.size() - numBytes - 1; ++targ)
    {
      shifted.array[targ] = (array[src] >> numBits) & 0xFF;
      ++src;
      shifted.array[targ] |= (array[src] << (8 - numBits)) & 0xFF; // if numBits == 0 this will do nothing, but it's faster than "if"
    }

    shifted.array[targ] = (array[src] >> numBits) & 0xFF; // part of last byte

    return shifted;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CArray1Bit operator>>( int n )
  {
    if (n <= 0)
      return *this;

    CArray1Bit shifted(GetSize());
    shifted.FillZero();

    int numBytes = n >> 3;
    int numBits = n & 7;

    int targ = array.size() - 1;
    int src = targ - numBytes;
    for (; targ > numBytes; --targ)
    {
      shifted.array[targ] = (array[src] << numBits) & 0xFF;
      --src;
      shifted.array[targ] |= (array[src] >> (8 - numBits)) & 0xFF; // if numBits == 0 this will do nothing, but it's faster than "if"
    }

    shifted.array[targ] = (array[src] << numBits) & 0xFF; // part of last byte

    return shifted;
  }
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const bool IsZeroFilled() const
	{
		for ( int i = 0; i < array.size(); ++i )
		{
			if ( array[i] != 0 )
				return false;
		}
		return true;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CArray4Bit
{
	int nSize;
	vector<BYTE> array;
public:
	int operator&( _interface IBinSaver &saver ) {	saver.Add( 1, &array ); saver.Add( 2, &nSize ); return 0; }

	CArray4Bit() { }
	CArray4Bit( const int size ) { SetSize( size ); }
	CArray4Bit( const CArray4Bit &a ) : nSize( a.nSize ), array( a.array ) { }
	~CArray4Bit() {}
	//
	const CArray4Bit& operator=( const CArray4Bit &a ) { nSize = a.nSize; array = a.array; return *this; }
	//
	void SetSize( const int size )
	{
		nSize = size;
		if ( size == 0 )
			array.clear();
		else
			array.resize( ((size-1) >> 1) + 1 );
	}
	void Clear() { nSize = 0; array.clear(); }
	void FillZero() { if ( !IsEmpty() ) memset( &(array[0]), 0, array.size() ); }
	//
	int GetSize() const { return nSize; }
	bool IsEmpty() const { return nSize == 0; }

	void SetData( const int n, const BYTE cData )
	{
		RemoveData( n );
		array[n >> 1] |= cData << ( (n & 1) << 2 );
	}

	const BYTE GetData( const int n ) const
	{
		return ( array[n >> 1] >> ( (n & 1) << 2 ) ) & 0xf;
	}

	void RemoveData( const int n )
	{
		array[n >> 1] &= 0xf0 >> ( (n & 1) << 2 );
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CArray2D4Bit
{
	int xSize;
	CArray2D<BYTE> array;
public:
	int operator&( _interface IBinSaver &saver ) {	saver.Add( 1, &xSize ); saver.Add( 2, &array ); return 0; }

	CArray2D4Bit() : xSize( 0 ) {}
	CArray2D4Bit( const int xsize, const int ysize ) { SetSizes( xsize, ysize ); }
	CArray2D4Bit( const CArray2D4Bit &a ) : xSize( a.xSize ), array( a.array ) { }
	~CArray2D4Bit() {}
	//
	const CArray2D4Bit& operator=( const CArray2D4Bit &a ) { xSize = a.xSize; array = a.array; return *this; }
	//
	void SetSizes( const int xsize, const int ysize ) { xSize = xsize; array.SetSizes( (xsize >> 1) + 1, ysize ); }
	void Clear() { xSize = 0; array.Clear(); }
	void FillZero() { array.FillZero(); }
	void FillOne() { array.FillEvery( 0xFF ); }

	//
	int GetSizeX() const { return xSize; }
	int GetSizeY() const { return array.GetSizeY(); }
	//
	bool IsEmpty() const { return array.IsEmpty(); }

	void SetData( const int x, const int y, const BYTE cData )
	{
		RemoveData( x, y );
		array[y][x >> 1] |= cData << ( (x & 1) << 2 );
	}

	const BYTE GetData( const int x, const int y ) const
	{
		return ( array[y][x >> 1] >> ( (x & 1) << 2 ) ) & 0xf;
	}

	void RemoveData( const int x, const int y )
	{
		array[y][x >> 1] &= 0xf0 >> ( (x & 1) << 2 );
	}

	friend class CBitArray2DRLEWrapper<CArray2D4Bit>;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CArray2D1Bit
{
	int xSize;
	CArray2D<BYTE> array;
public:
	int operator&( _interface IBinSaver &saver ) {	saver.Add( 1, &xSize ); saver.Add( 2, &array ); return 0; }

	CArray2D1Bit() : xSize( 0 ) {	}
	CArray2D1Bit( const int xsize, const int ysize )	{ SetSizes( xsize, ysize ); }
	CArray2D1Bit( const CArray2D1Bit &a ) : xSize( a.xSize ), array( a.array ) { }
	~CArray2D1Bit() {}
	//
	const CArray2D1Bit& operator=( const CArray2D1Bit &a ) { xSize = a.xSize; array = a.array; return *this; }
	//
	void SetSizes( const int xsize, const int ysize ) { xSize = xsize; array.SetSizes( (xsize >> 3) + 1, ysize ); }
	void Clear() { xSize = 0; array.Clear(); }
	void FillZero() { array.FillZero(); }
	void SetZeroFast() { array.FillZero(); }
	//
	void CopyEqualSizes( CArray2D1Bit & dest ) 
	{ 
		//NI_ASSERT( xSize == dest.xSize && array.GetSizeX() == dest.array.GetSizeX() && array.GetSizeY() == dest.array.GetSizeY(), "cannot copy, unequal sizes" );
		array = dest.array;
		//memcpy( array.GetBuffer(), dest.array.GetBuffer(), array.GetSizeX() * array.GetSizeY() );
	}
	void Set1() 
	{ 
		//array.FillEvery( unsigned int(-1) );
		memset( &(array[0][0]), (unsigned int)(-1), array.GetSizeX() * array.GetSizeY());
	};

	int GetSizeX() const { return xSize; }
	int GetSizeY() const { return array.GetSizeY(); }
	//
	bool IsEmpty() const { return array.IsEmpty(); }

	void SetData( const int x, const int y )
	{
		array[y][x >> 3] |= 1 << (x & 7);
	}

	const BYTE GetData( const int x, const int y ) const
	{
		return ( array[y][x >> 3] >> (x & 7) ) & 1;
	}

	void RemoveData( const int x, const int y )
	{
		array[y][x >> 3] &= ~( 1 << (x & 7) );
	}

	friend class CBitArray2DRLEWrapper<CArray2D1Bit>;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
