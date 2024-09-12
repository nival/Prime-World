#ifndef __2DARRAY_H_
#define __2DARRAY_H_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////////////////////////////////////////////////////////////////////////////////////////////////////
template < class T > 
struct CBoundCheck
{
	T *data;
	int nSize;
	CBoundCheck( T *d, int nS ) 
	{ 
		data = d; 
		nSize = nS; 
	}
	T& operator[]( int i ) 
	{ 
		ASSERT( i>=0 && i<nSize ); 
		return data[i]; 
	}

	const T& operator[]( int i ) const 
	{ 
		ASSERT( i>=0 && i<nSize ); 
		return data[i]; 
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template < class T >
class CArray2D
{
public:
	typedef T ValueType;
	typedef T *PT;
#ifdef _DEBUG
  typedef CBoundCheck<T> SubArray; 
  typedef const CBoundCheck<T> SubArrayConst; 
#else
  typedef T *SubArray;
  typedef const T *SubArrayConst;
#endif

private:
	T *data;
	T **pData;
	int nXSize, nYSize;
	void Copy( const CArray2D &a ) 
	{ 
		if ( !( a.IsEmpty() ) )
		{
			nXSize = a.nXSize;
			nYSize = a.nYSize;
			Create(); 
			for( int i = 0; i < nXSize*nYSize; i++ ) 
				data[i] = a.data[i]; 
		}
		else
		{
			nXSize = nYSize = 0;
			data = 0;
			pData = 0;
		}
	}
	void Destroy() 
	{ 
		if ( data ) 
			delete[] data; 
		if ( pData ) 
			delete[] pData; 
	}
	void Create() 
	{ 
		data = new T[ nXSize*nYSize ]; 
		pData = new PT[ nYSize ]; 
		for( int i = 0; i < nYSize; i++) 
			pData[i] = data+i*nXSize; 
	}
public:
	CArray2D() : data(0), pData(0), nXSize(0), nYSize(0) {}
	CArray2D( int xsize, int ysize ) { nXSize = xsize; nYSize = ysize; Create(); }
	CArray2D( const CArray2D &a ) { Copy(a); }
	CArray2D& operator=( const CArray2D &a ) 
	{ 
		if ( nXSize == a.nXSize && nYSize == a.nYSize )
		{
			for ( int k = 0, nTotal = nXSize * nYSize; k < nTotal; ++k )
				data[k] = a.data[k];
		}
		else
		{
			Destroy(); Copy(a); 
		}
		return *this; 
	}
	~CArray2D() { Destroy(); }
	void SetSizes( int xsize, int ysize ) 
	{ 
		if ( nXSize == xsize && nYSize == ysize ) 
			return; 
		Destroy(); 
		nXSize = xsize; 
		nYSize = ysize; 
		Create(); 
	}
	void Clear() { Destroy(); data = 0; pData = 0; nXSize = 0; nYSize = 0; }
#ifdef _DEBUG
	CBoundCheck<T> operator[]( int i ) 
	{ 
 		ASSERT( i>=0 && i<nYSize ); 
		return CBoundCheck<T>( pData[i], nXSize ); 
	}

	const CBoundCheck<T> operator[]( int i ) const 
	{ 
		ASSERT( i>=0 && i<nYSize ); 
		return CBoundCheck<T>( pData[i], nXSize ); 
	}
#else
	const T* operator[]( int i ) const 
	{ 
#ifdef _DEBUG
		ASSERT( i>=0 && i<nYSize ); 
#endif
		return pData[i]; 
	}

	T* operator[]( int i ) 
	{ 
#ifdef _DEBUG
		ASSERT( i>=0 && i<nYSize ); 
#endif
		return pData[i]; 
	}
#endif
	int GetSizeX() const { return nXSize; }
	int GetSizeY() const { return nYSize; }
	bool IsEmpty() const { return pData == 0; }
	void FillZero() { memset( data, 0, sizeof( T ) * nXSize * nYSize ); }
	void FillEvery( const T &a ) { for ( int i = 0; i < nXSize * nYSize; i++ ) data[i] = a; }
	void Swap( CArray2D<T> &arr )
	{
		swap( data, arr.data );
		swap( pData, arr.pData );
		swap( nXSize, arr.nXSize );
		swap( nYSize, arr.nYSize );
	}

	inline const T& Get(int x, int y) const
	{
		int lx = x;
		int ly = y;

		if (lx < 0) lx = 0;
		if (ly < 0) ly = 0;
		if (lx >= GetSizeX()) lx = GetSizeX() - 1;
		if (ly >= GetSizeY()) ly = GetSizeY() - 1;
		return operator[](ly)[lx];
	}

	inline const T& GetUnsafe(int x, int y) const
	{
		return data[y * nXSize + x];
	}

	inline T& Get(int x, int y) 
	{
		return operator[](y)[x];
	}

	inline T& Set(int x, int y, const T& value) 
	{
		T& ref = operator[](y)[x];
		ref = value;
		return ref;
	}

	void CopyRow(T* dest, int size, int x_delta, int row) const
	{
		for (int i = 0; i < size; ++i)
		{
			dest[i] = Get(i+x_delta, row);
		}
	}

	void CopyColumn(T* dest, int size, int column, int y_delta) const
	{
		for (int i = 0; i < size; ++i)
		{
			dest[i] = Get(column, i+y_delta);
		}
	}

};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class CArray3D;
template<class T> 
class CArray3DFetcher
{
	T *pData;
	CArray3D<T> &a;
public:
	CArray3DFetcher( T *_pData, CArray3D<T> &_a ): pData(_pData), a(_a) {}
#ifdef _DEBUG
	CBoundCheck<T> operator[]( int i ) const { ASSERT( i>=0 && i<a.GetYSize() ); return CBoundCheck<T>( &pData[i*a.GetXSize()], a.GetXSize() ); }
#else
	T* operator[]( int i ) const 
	{ 
#ifdef _DEBUG
		ASSERT( i>=0 && i<a.GetYSize() ); 
#endif
		return &pData[i*a.GetXSize()]; 
	}
#endif
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> 
class CArray3D
{
	ZDATA
		vector<T> data;
	int nXSize, nYSize, nZSize, nXYSize;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&data); f.Add(3,&nXSize); f.Add(4,&nYSize); f.Add(5,&nZSize); f.Add(6,&nXYSize); return 0; }
	CArray3D(): nXSize(0), nYSize(0), nZSize(0), nXYSize(0){}
	int GetXSize() const { return nXSize; }
	int GetYSize() const { return nYSize; }
	int GetZSize() const { return nZSize; }
	void SetSizes( int nX, int nY, int nZ ) { nXSize = nX; nYSize = nY; nZSize = nZ; nXYSize = nXSize * nYSize; data.resize( nZSize * nXYSize ); }
	void FillEvery( const T &a ) { fill( data.begin(), data.end(), a ); }
#ifdef _DEBUG
	CArray3DFetcher<T> operator[]( int i ) { ASSERT( i>=0 && i<nZSize ); return CArray3DFetcher<T>( &data[i*nXYSize], *this ); }
#else
	CArray3DFetcher<T> operator[]( int i ) 
	{ 
#ifdef _DEBUG
		ASSERT( i>=0 && i<nZSize ); 
#endif
		return CArray3DFetcher<T>( &data[i*nXYSize], *this ); 
	}
#endif
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
