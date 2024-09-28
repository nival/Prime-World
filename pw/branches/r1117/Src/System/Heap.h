#ifndef __HEAP_H__
#define __HEAP_H__

#pragma once

template <class T, class TCmp>
class CSortedVector
{
	TCmp cmp;
	typedef vector<T> CTElements;
	CTElements elements;
public:
	void Reserve( const size_t size ) { elements.reserve( size ); }
	
	void Push( const T& el )
	{
		// find first element that TCmp is true for it
		CTElements::iterator it = lower_bound( elements.begin(), elements.end(), el, cmp );
		elements.insert( it, el );
	}
	void Remove( const T& el )
	{
		CTElements::iterator it = lower_bound( elements.begin(), elements.end(), el, cmp );
		for( CTElements::iterator rem = it; rem != elements.end(); ++rem ) 
		{
			if ( *rem == el )
			{
				elements.erase( rem );
				break;
			}
		}
	}
	const T& operator[]( const int n ) const { return elements[n]; }
	T& operator[]( const int n ) { return elements[n]; }
	int Size() const { return elements.size(); }
	int GetReserved() const { return elements.capacity(); }
	void Clear() { elements.clear(); }
	int operator&( IBinSaver &saver )
	{
		saver.Add( 1, &elements );
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// на вершине куче находится наибольший элемент
// bool Cmp::operator()(const T &a, const T &b) должен возвращать true в случае a < b
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct SVoidSwap
{
	void operator()( const T &a, const T &b, const int aIndex, const int bIndex ) { }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap = SVoidSwap<T> >
class CHeap
{
	TCmp cmp;
	TWillSwap WillSwap;
	
	// нумерация элементов от 1!
	vector<T> heap;
	int nEl;

	// перебалансирует, начиная с эл. k и вверх
	int Balance( int k );
public:
	int operator&( IBinSaver &saver );	

	CHeap() : nEl( 0 ), heap( 1 ) { }
	CHeap( const int nSize ) : heap( nSize + 1 ), nEl( 0 ) { }

	void Reserve( const int nSize ) { if ( nSize + 1 > heap.size() ) heap.resize( nSize + 1 ); }

	const int Size() const { return nEl; }
	const int GetReserved() const { return heap.size() - 1; }

	bool IsEmpty() const { return nEl == 0; }

	void Erase( const int n );
	void Clear() { heap.clear(); nEl = 0; heap.resize( 1 ); }

	// возвращает индекс, куда элемент попал
	int Push( const T& el );
	const T Pop();

	// перебалансировать при увеличении элемента на позиции k
	int Increased( const int k );

	const T& GetMaxEl() const { return heap[1]; }
	T& GetMaxEl() { NI_ASSERT( nEl >= 1, "The heap is empty" );	return heap[1]; }

	const T& operator[]( const int n ) const { return heap[n + 1]; }
	T& operator[]( const int n ) { return heap[n + 1]; }

	void Remove( const T& el );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
void CHeap<T, TCmp, TWillSwap>::Remove( const T& el )
{
	for ( int i = 0; i < Size(); ++i )
	{
		if ( (*this)[i] == el )
		{
			Erase( i );
			return;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::Balance( int k )
{
	while ( k > 1 && cmp( heap[k / 2], heap[k] ) )
	{
		WillSwap( heap[k], heap[k/2], k-1, k/2-1 );
		swap( heap[k], heap[k/2] );
		k /= 2;
	}

	return k-1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::Push( const T& el )
{
	heap[++nEl] = el;	

	return Balance( nEl );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::Increased( const int k )
{
	return Balance( k + 1 );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
void CHeap<T, TCmp, TWillSwap>::Erase( const int n )
{
	int k = n + 1;
	NI_ASSERT( k >= 1 && k <= nEl, "Wrong element to erase from heap" );
	WillSwap( heap[k], heap[nEl], k-1, nEl-1 );
	heap[k] = heap[nEl];
	--nEl;

	while ( 2*k + 1 <= nEl && ( cmp( heap[k], heap[2*k] ) || cmp( heap[k], heap[2*k + 1] ) ) )
	{
		if ( cmp( heap[2*k], heap[2*k + 1 ] ) )
		{
			WillSwap( heap[k], heap[2*k + 1], k-1, 2*k );
			swap( heap[k], heap[2*k + 1] );
			k *= 2;
			++k;
		}
		else
		{
			WillSwap( heap[k], heap[2*k], k-1, 2*k-1 );
			swap( heap[k], heap[2*k] );
			k *= 2;
		}
	}

	if ( k > 0 && 2*k + 1 > nEl && 2 * k <= nEl && cmp( heap[k], heap[2*k] ) )
	{
		WillSwap( heap[k], heap[2*k], k-1, 2*k-1 );
		swap( heap[k], heap[2*k] );
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
const T CHeap<T, TCmp, TWillSwap>::Pop()
{
	const T result( heap[1] );
	Erase( 0 );
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TCmp, class TWillSwap>
int CHeap<T, TCmp, TWillSwap>::operator&( IBinSaver &ss )
{
	ss.Add( 1, &heap );
	ss.Add( 2, &nEl );
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __HEAP_H__
