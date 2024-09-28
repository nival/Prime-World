#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
// класс для последовательной записи/считывания данных, включая возможность записи
// или считывания побитных данных, может использоваться на произовольных областях
// памяти
class BitStream
{
public:
	enum Mode
	{
		read,
		write
	};

protected:
	char *pCurrent;
	char *pBitPtr;				 // for bit writing
	unsigned int nBits;
	unsigned char nBitsCount; // bits and bit counter
	static unsigned int nBitsMask[32];

#ifdef _DEBUG
	Mode mode;
	char *pReservedEnd;
	void CheckCurrentR() { ASSERT( pCurrent <= pReservedEnd ); ASSERT( mode == read ); }
	void CheckCurrentW() { ASSERT( pCurrent <= pReservedEnd ); ASSERT( mode == write ); }
#else
	void CheckCurrentR() {}
	void CheckCurrentW() {}
#endif

	inline void Init( char *pData, Mode _mode, int nSize );
public:
	BitStream( void *pData, Mode _mode, int nSize ) { Init( (char*)pData, _mode, nSize ); }
	// result of read/write beyond data range is not determined
	void Read( void *pDest, unsigned int nSize ) { memcpy( pDest, pCurrent, nSize ); pCurrent += nSize; CheckCurrentR(); }
	void Write( const void *pSrc, unsigned int nSize ) { memcpy( pCurrent, pSrc, nSize ); pCurrent += nSize; CheckCurrentW(); }
	void ReadCString( string &res ) { int nLeng = strlen( (char*)pCurrent ); res.assign( (char*)pCurrent, nLeng ); pCurrent += nLeng + 1; CheckCurrentR(); }
	void WriteCString( const char *pSrc ) { int nLeng = strlen( pSrc ); memcpy( pCurrent, pSrc, nLeng + 1 ); pCurrent += nLeng + 1; CheckCurrentW(); }
	void FlushBits() { if ( nBitsCount ) { nBitsCount = 0; if ( pBitPtr ) pBitPtr[0] = (char)nBits; } }
	// not more then 24 bits per call
	inline void WriteBits( unsigned int _nBits, unsigned int _nBitsCount );
	inline void WriteBit( unsigned int _nBits );
	inline unsigned int ReadBits( unsigned int _nBitsCount );
	inline unsigned int ReadBit();
	// even more direct access, try to not use it, read only
	const char* GetCurrentPtr() const { return pCurrent; }
	// get pointer to place to write to later (not later then this object will be destructed)
	char* WriteDelayed( int nSize ) { char *pRes = pCurrent; pCurrent += nSize; CheckCurrentW(); return pRes; }
	//
	template <class T> inline void Write( const T &a ) { Write( &a, sizeof(a) ); }
	template <class T> inline void Read( T &a ) { Read( &a, sizeof(a) ); }
	
	friend class CBitEmbedded;
};

template<> inline void BitStream::Write<string>( const string &a ) { WriteCString( a.c_str() ); }
template<> inline void BitStream::Read<string>( string &a ) { ReadCString( a ); }


////////////////////////////////////////////////////////////////////////////////////////////////////
// класс для выполнения побитного и скоростного ввода/вывода в поток общего назначения
// после того, как с MemoryStream начинает работать BitLocker прямые операции с 
// MemoryStream приведут к некорректному результату
class MemoryStream;
class BitLocker: public BitStream
{
	MemoryStream *pData;
	char *pBuffer;
public:
	BitLocker(): BitStream( 0, read, 0 ) { pData = 0; }
	~BitLocker();
	// once per life of this object
	void LockRead( MemoryStream &data, unsigned int nSize );
	void LockWrite( MemoryStream &data, unsigned int nSize );
	// alloc additional buffer space, for better perfomance minimize number of this 
	// function calls
	void ReserveRead( unsigned int nSize );
	void ReserveWrite( unsigned int nSize );
	void Free();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class CBitEmbedded: public BitStream
{
	BitStream &bits;

	CBitEmbedded &operator=( const CBitEmbedded & ) { return *this; }
public:
	CBitEmbedded( BitStream &_bits ): 
#ifdef _DEBUG
		BitStream( _bits.pCurrent, _bits.mode, _bits.pReservedEnd - _bits.pCurrent )
#else
		BitStream( _bits.pCurrent, read, 0 )
#endif
		, bits(_bits) {}
	
	~CBitEmbedded() { bits.pCurrent = pCurrent; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// BitStream realization
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void BitStream::Init( char *pData, Mode _mode, int nSize )
{
	pCurrent = pData; nBitsCount = 0; pBitPtr = 0;
#ifdef _DEBUG
	mode = _mode;
	pReservedEnd = pCurrent + nSize;
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void BitStream::WriteBits( unsigned int _nBits, unsigned int _nBitsCount )
{
	if ( nBitsCount != 0 )
	{
		nBits += ( _nBits << nBitsCount );
		nBitsCount += _nBitsCount;
	}
	else
	{
		pBitPtr = pCurrent++;
		nBits = _nBits;
		nBitsCount = _nBitsCount;
	}
	while ( nBitsCount > 8 )
	{
		pBitPtr[0] = (unsigned char)nBits; //( nBits & 0xff );
		nBits >>= 8; nBitsCount -= 8;
		pBitPtr = pCurrent++;
	}
	CheckCurrentW();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void BitStream::WriteBit( unsigned int _nBits )
{
	if ( nBitsCount == 0 )
	{
		pBitPtr = pCurrent++;
		nBits = _nBits;
		nBitsCount = 1;
	}
	else
	{
		nBits += ( _nBits << nBitsCount );
		nBitsCount++;
	}
	if ( nBitsCount > 8 )
	{
		pBitPtr[0] = (unsigned char)nBits; //( nBits & 0xff );
		nBits >>= 8; nBitsCount -= 8;
		pBitPtr = pCurrent++;
	}
	CheckCurrentW();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int BitStream::ReadBits( unsigned int _nBitsCount )
{
	while ( nBitsCount < _nBitsCount )
	{
		nBits += ((unsigned int)*pCurrent++) << nBitsCount;
		nBitsCount += 8;
	}
	int nRes = nBits & nBitsMask[ _nBitsCount - 1 ];
	nBits >>= _nBitsCount;
	nBitsCount -= _nBitsCount;
	CheckCurrentR();
	return nRes;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int BitStream::ReadBit()
{
	if ( nBitsCount < 1 )
	{
		nBits = ((unsigned int)*pCurrent++);
		nBitsCount = 8;
	}
	int nRes = nBits & 1;
	nBits >>= 1;
	nBitsCount--;
	CheckCurrentR();
	return nRes;
}
