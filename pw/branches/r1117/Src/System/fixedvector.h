#ifndef FIXED_VECTOR_H_
#define FIXED_VECTOR_H_

template< typename T, unsigned int _capacity, bool enableDestructor = true >
class FixedVector
{
	T array[_capacity];
	unsigned int _size;
public:
	typedef const T* const_iterator;
	typedef T* iterator;
	typedef const T& const_reference;
	typedef T& reference;

	FixedVector() : _size(0) {}
	FixedVector(unsigned int size) : _size(size) {}

	~FixedVector()
	{
		if(!enableDestructor)
			NI_ALWAYS_ASSERT(" dont call me!");
	}

	unsigned int size() const	{	return _size; }
	unsigned int capacity() const	{	return _capacity; }
	void setsize(unsigned int size) {	ASSERT(size<=_capacity); _size = size; }

	const_reference operator[]( unsigned int index ) const	{	ASSERT(index<_size); return array[index]; }
	reference operator[]( unsigned int index ) { ASSERT(index<_size); return array[index];	}

	const_iterator begin() const { return &array[0];	}
	iterator begin() { return &array[0];	}

	const_iterator end() const { return &array[_size]; }
	iterator end() { return &array[_size]; }

	const_iterator at( unsigned int index ) const	{	ASSERT(index<_size); return &array[index]; }
	iterator at( unsigned int index ) {	ASSERT(index<_size); return &array[index]; }

	reference push_back() { ASSERT(_size<_capacity); return array[_size++]; }
	reference push_back(const T& _value) {
		T& value = push_back();
		value = _value;
		return value;
	}
	void clear() {
		setsize(0);
	}
};

#endif

