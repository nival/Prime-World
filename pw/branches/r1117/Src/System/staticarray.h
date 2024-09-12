#ifndef _STATIC_ARRAY_H_
#define _STATIC_ARRAY_H_


// no size, capacity only, should never call destructor
// the main purpose is the loading data which can be modified in runtime 
template< typename T, unsigned int _capacity, bool enableDestructor = true >
class StaticArray
{
	T array[_capacity];
public:
	typedef const T* const_iterator;
	typedef T* iterator;
	typedef const T& const_reference;
	typedef T& reference;

	~StaticArray() 
	{ 
		if(!enableDestructor)
			NI_ALWAYS_ASSERT("dont call me!"); 
	}

	unsigned int capacity() const	{	return _capacity; }

	const_reference operator[]( unsigned int index ) const	{	ASSERT(index<_capacity); return array[index]; }
	reference operator[]( unsigned int index ) { ASSERT(index<_capacity); return array[index];	}

	const_iterator begin() const { return array;	}
	iterator begin() { return array;	}

	const_iterator end() const { return (array + _capacity); }
	iterator end() { return (array + _capacity); }

	const_iterator at( unsigned int index ) const	{	ASSERT(index<_capacity); return &array[index]; }
	iterator at( unsigned int index ) {	ASSERT(index<_capacity); return &array[index]; }
};

#endif

