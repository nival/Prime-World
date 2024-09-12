#ifndef __NSTL_HEAP_H__
#define __NSTL_HEAP_H__

#pragma once

//{WORKAROUND FOR HEAP
template< class TIter>
int* get_diff( const TIter &it ) { return (int*)0; }
#define distance_type(x) (get_diff(x))
//}

namespace nstl 
{

template <class _RandomAccessIterator>
void push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last);


template <class _RandomAccessIterator, class _Compare>
void 
push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
					_Compare __comp);

template <class _RandomAccessIterator, class _Distance, class _Tp>
void 
__adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
							_Distance __len, _Tp __val);

template <class _RandomAccessIterator, class _Tp, class _Distance>
inline void 
__pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
					 _RandomAccessIterator __result, _Tp __val, _Distance*)
{
	*__result = *__first;
	__adjust_heap(__first, _Distance(0), _Distance(__last - __first), __val);
}

template <class _RandomAccessIterator>
void pop_heap(_RandomAccessIterator __first, 
				_RandomAccessIterator __last);

template <class _RandomAccessIterator, class _Distance,
					class _Tp, class _Compare>
void
__adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
							_Distance __len, _Tp __val, _Compare __comp);

template <class _RandomAccessIterator, class _Tp, class _Compare, 
					class _Distance>
inline void 
__pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
					 _RandomAccessIterator __result, _Tp __val, _Compare __comp,
					 _Distance*)
{
	*__result = *__first;
	__adjust_heap(__first, _Distance(0), _Distance(__last - __first), 
								__val, __comp);
}

template <class _RandomAccessIterator, class _Compare>
void 
pop_heap(_RandomAccessIterator __first,
				 _RandomAccessIterator __last, _Compare __comp);

template <class _RandomAccessIterator>
void 
make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last);

template <class _RandomAccessIterator, class _Compare>
void 
make_heap(_RandomAccessIterator __first, 
					_RandomAccessIterator __last, _Compare __comp);

template <class _RandomAccessIterator>
inline
void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
	while (__last - __first > 1)
		pop_heap(__first, __last--);
}

template <class _RandomAccessIterator, class _Compare>
inline
void 
sort_heap(_RandomAccessIterator __first,
					_RandomAccessIterator __last, _Compare __comp)
{
	while (__last - __first > 1)
		pop_heap(__first, __last--, __comp);
}


template <class _RandomAccessIterator, class _Distance, class _Tp>
inline
void 
__push_heap(_RandomAccessIterator __first,
						_Distance __holeIndex, _Distance __topIndex, _Tp __val)
{
	_Distance __parent = (__holeIndex - 1) / 2;
	while (__holeIndex > __topIndex && *(__first + __parent) < __val) {
		*(__first + __holeIndex) = *(__first + __parent);
		__holeIndex = __parent;
		__parent = (__holeIndex - 1) / 2;
	}		
	*(__first + __holeIndex) = __val;
}

template <class _RandomAccessIterator, class _Distance>
inline void 
__push_heap_aux(_RandomAccessIterator __first,
								_RandomAccessIterator __last, _Distance*)
{
	__push_heap(__first, _Distance((__last - __first) - 1), _Distance(0), 
							(*(__last - 1)));
}

template <class _RandomAccessIterator>
void 
push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
	__push_heap_aux(__first, __last,
									distance_type(__first));
}


template <class _RandomAccessIterator, class _Distance, class _Tp, 
					class _Compare>
inline
void
__push_heap(_RandomAccessIterator __first, _Distance __holeIndex,
						_Distance __topIndex, _Tp __val, _Compare __comp)
{
	_Distance __parent = (__holeIndex - 1) / 2;
	while (__holeIndex > __topIndex && __comp(*(__first + __parent), __val)) {
		*(__first + __holeIndex) = *(__first + __parent);
		__holeIndex = __parent;
		__parent = (__holeIndex - 1) / 2;
	}
	*(__first + __holeIndex) = __val;
}

template <class _RandomAccessIterator, class _Compare,
					class _Distance>
inline void 
__push_heap_aux(_RandomAccessIterator __first,
								_RandomAccessIterator __last, _Compare __comp,
								_Distance*) 
{
	__push_heap(__first, _Distance((__last - __first) - 1), _Distance(0), 
							(*(__last - 1)), __comp);
}

template <class _RandomAccessIterator, class _Compare>
void 
push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
					_Compare __comp) 
{
	__push_heap_aux(__first, __last, __comp,
									distance_type(__first));
}

template <class _RandomAccessIterator, class _Distance, class _Tp>
void 
__adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
							_Distance __len, _Tp __val) {
	_Distance __topIndex = __holeIndex;
	_Distance __secondChild = 2 * __holeIndex + 2;
	while (__secondChild < __len) {
		if (*(__first + __secondChild) < *(__first + (__secondChild - 1)))
			__secondChild--;
		*(__first + __holeIndex) = *(__first + __secondChild);
		__holeIndex = __secondChild;
		__secondChild = 2 * (__secondChild + 1);
	}
	if (__secondChild == __len) {
		*(__first + __holeIndex) = *(__first + (__secondChild - 1));
		__holeIndex = __secondChild - 1;
	}
	__push_heap(__first, __holeIndex, __topIndex, __val);
}


template <class _RandomAccessIterator>
inline void 
__pop_heap_aux(_RandomAccessIterator __first, _RandomAccessIterator __last) {
	__pop_heap(__first, __last - 1, __last - 1, 
						 (*(__last - 1)), distance_type(__first));
}

template <class _RandomAccessIterator>
void pop_heap(_RandomAccessIterator __first, 
				_RandomAccessIterator __last) {
	__pop_heap_aux(__first, __last);
}

template <class _RandomAccessIterator, class _Distance,
					class _Tp, class _Compare>
void
__adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
							_Distance __len, _Tp __val, _Compare __comp)
{
	_Distance __topIndex = __holeIndex;
	_Distance __secondChild = 2 * __holeIndex + 2;
	while (__secondChild < __len) {
		if (__comp(*(__first + __secondChild), *(__first + (__secondChild - 1))))
			__secondChild--;
		*(__first + __holeIndex) = *(__first + __secondChild);
		__holeIndex = __secondChild;
		__secondChild = 2 * (__secondChild + 1);
	}
	if (__secondChild == __len) {
		*(__first + __holeIndex) = *(__first + (__secondChild - 1));
		__holeIndex = __secondChild - 1;
	}
	__push_heap(__first, __holeIndex, __topIndex, __val, __comp);
}


template <class _RandomAccessIterator, class _Compare>
inline void 
__pop_heap_aux(_RandomAccessIterator __first,
							 _RandomAccessIterator __last, _Compare __comp)
{
	__pop_heap(__first, __last - 1, __last - 1, *(__last - 1), __comp,
						 distance_type(__first));
}


template <class _RandomAccessIterator, class _Compare>
void 
pop_heap(_RandomAccessIterator __first,
				 _RandomAccessIterator __last, _Compare __comp)
{
		__pop_heap_aux(__first, __last, __comp);
}

template <class _RandomAccessIterator, class _Tp, class _Distance>
inline
void 
__make_heap(_RandomAccessIterator __first,
						_RandomAccessIterator __last, _Tp*, _Distance*)
{
	if (__last - __first < 2) return;
	_Distance __len = __last - __first;
	_Distance __parent = (__len - 2)/2;
		
	while (true) {
		__adjust_heap(__first, __parent, __len, _Tp(*(__first + __parent)));
		if (__parent == 0) return;
		__parent--;
	}
}

template <class _RandomAccessIterator>
void 
make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
	__make_heap(__first, __last,
							value_type(__first), distance_type(__first));
}

template <class _RandomAccessIterator, class _Compare,
					class _Tp, class _Distance>
inline
void
__make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
						_Compare __comp, _Tp*, _Distance*)
{
	if (__last - __first < 2) return;
	_Distance __len = __last - __first;
	_Distance __parent = (__len - 2)/2;
		
	while (true) {
		__adjust_heap(__first, __parent, __len, _Tp(*(__first + __parent)),
									__comp);
		if (__parent == 0) return;
		__parent--;
	}
}

template <class _RandomAccessIterator, class _Compare>
void 
make_heap(_RandomAccessIterator __first, 
					_RandomAccessIterator __last, _Compare __comp)
{
	__make_heap(__first, __last, __comp,
							value_type(__first), ptrdiff_t(__first));
}

}

#endif // __NSTL_HEAP_H__
