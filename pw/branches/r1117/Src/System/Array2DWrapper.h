#ifndef ARRAY_2D_WRAPPER_H_
#define ARRAY_2D_WRAPPER_H_

#include "noncopyable.h"

template<typename T>
class Array2DWrapper
	: private NonCopyable
{
public:
	typedef T ValueType;
	typedef T* Pointer;

private:
	Pointer data;
	int sizeX;
	int sizeY;
	int pitch;

public:
	Array2DWrapper() : data( 0 ), sizeX( 0 ), sizeY( 0 ), pitch( 0 ) {}
	Array2DWrapper( Pointer _data, int _sizeX, int _sizeY, int _pitch ) : data( _data ), sizeX( _sizeX ), sizeY( _sizeY ), pitch( _pitch ) {}

	void Set( Pointer _data, int _sizeX, int _sizeY, int _pitch ) { data = _data; sizeX = _sizeX; sizeY = _sizeY; pitch = _pitch; }
	const Pointer Get() const { return data; }
	
	int GetSizeX() const { return sizeX; }
	int GetSizeY() const { return sizeY; }

	const T& operator () ( int x, int y ) const
	{
#ifdef _DEBUG
		ASSERT( data );
		ASSERT( x >= 0 && x < sizeX );
		ASSERT( y >= 0 && y < sizeY );
#endif
		return data[y * pitch + x];
	}
	
	T& operator () ( int x, int y )
	{
#ifdef _DEBUG
		ASSERT( data );
		ASSERT( x >= 0 && x < sizeX );
		ASSERT( y >= 0 && y < sizeY );
#endif
		return data[y * pitch + x];
	}

	inline const T& Get(int x, int y) const
	{
		return operator()(x, y);
	}

	inline T& Set(int x, int y, const T& value) 
	{
		T& value_reference = operator()(x, y);
		value_reference = value;
		return value_reference;
	}
};

#endif

