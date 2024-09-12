#ifndef _STATIC_ARRAY_2D_H_
#define _STATIC_ARRAY_2D_H_

#include "staticarray.h"

template< typename T, unsigned int xsize, unsigned ysize >
class StaticArray2D
{
	StaticArray<T, xsize> row[ysize];
public:
	typedef const StaticArray<T, xsize>* const_iterator;
	typedef StaticArray<T, xsize>* iterator;
	typedef const StaticArray<T, xsize>& const_reference;
	typedef StaticArray<T, xsize>& reference;

	const_reference operator[]( unsigned int index ) const	{	ASSERT(index<ysize); return row[index]; }
	reference operator[]( unsigned int index ) { ASSERT(index<ysize); return row[index];	}

	const_iterator begin() const { return row[0];	}
	iterator begin() { return row[0];	}

	const_iterator end() const { return row[ysize]; }
	iterator end() { return row[ysize]; }

	const_iterator at( unsigned int index ) const	{	 ASSERT(index<ysize); return &row[index]; }
	iterator at( unsigned int index ) {	ASSERT(index<ysize); return &row[index]; }
};

#endif

