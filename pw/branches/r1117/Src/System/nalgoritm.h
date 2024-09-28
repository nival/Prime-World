#ifndef NALGORITHM_H__
#define NALGORITHM_H__

#include <stdlib.h>
#include "npair.h"
#include "nalgobase.h"
//#include "ntype_traits.h"
//#include "niterator_base.h"

namespace nstl
{
template <typename T>
void Remove( T* todel, vector<CObj<T> >& container )
{
	typedef typename vector<CObj<T> >::iterator vecIterator;
	for (vecIterator it = container.begin(); it != container.end(); )
	{
		if ( *it == todel )
		{
			*it = 0;
			it = container.erase( it );
		}
		else
		{
			it++;
		}
	}
}

// helper function for iter swap
template <class _Tp>
inline void __swap(_Tp& __a, _Tp& __b) {
	_Tp __tmp = __a;
	__a = __b;
	__b = __tmp;
}

template <class _ForwardIter1, class _ForwardIter2>
inline void iter_swap(_ForwardIter1 __i1, _ForwardIter2 __i2)
{
	__swap(*__i1, *__i2);
}

// TEMPLATE FUNCTION advance
template<class _InIt, class _Diff> inline
void advance(_InIt& _Where, _Diff _Off)
{	// increment iterator by offset, arbitrary iterators
	_Advance(_Where, _Off );
}

template<class _InIt, class _Diff> inline
void _Advance(_InIt& _Where, _Diff _Off)
{	// increment iterator by offset, input iterators
	for (; 0 < _Off; --_Off)
		++_Where;
}

// lower_bound uses less to compare
template<class _ForwardIter, class _Tp > inline
_ForwardIter lower_bound( _ForwardIter _First, _ForwardIter _Last, const _Tp& _Val )
{
	return (__lower_bound(_First, _Last, _Val, less(), (int*)0));
}
// lower_bound uses Pred to compare
template<class _ForwardIter, class _Tp, class _Compare > inline
_ForwardIter lower_bound( _ForwardIter _First, _ForwardIter _Last, const _Tp& _Val, _Compare _comp )
{
	return (__lower_bound(_First, _Last, _Val, _comp, (int*)0));
}


// adjacent_find.
template <class _ForwardIter>
_ForwardIter
adjacent_find(_ForwardIter __first, _ForwardIter __last) {
	if (__first == __last)
		return __last;
	_ForwardIter __next = __first;
	while(++__next != __last) {
		if (*__first == *__next)
			return __first;
		__first = __next;
	}
	return __last;
}

template <class _ForwardIter, class _BinaryPredicate>
_ForwardIter
adjacent_find(_ForwardIter __first, _ForwardIter __last,
							_BinaryPredicate __binary_pred) {
								if (__first == __last)
									return __last;
								_ForwardIter __next = __first;
								while(++__next != __last) {
									if (__binary_pred(*__first, *__next))
										return __first;
									__first = __next;
								}
								return __last;
							}

		// replace_if, replace_copy, replace_copy_if

template <class _ForwardIter, class _Predicate, class _Tp>
//_STLP_INLINE_LOOP void
void replace_if(_ForwardIter __first, _ForwardIter __last, _Predicate __pred, const _Tp& __new_value) {
	//_STLP_DEBUG_CHECK(__check_range(__first, __last))
	for ( ; __first != __last; ++__first)
		if (__pred(*__first))
			*__first = __new_value;
}

template <class _InputIter, class _OutputIter, class _Tp>
_OutputIter
replace_copy(_InputIter __first, _InputIter __last,_OutputIter __result,
const _Tp& __old_value, const _Tp& __new_value) {
		for ( ; __first != __last; ++__first, ++__result)
			*__result = *__first == __old_value ? __new_value : *__first;
	return __result;
}

template <class _Iterator, class _OutputIter, class _Predicate, class _Tp>
	_OutputIter
	replace_copy_if(_Iterator __first, _Iterator __last,
	_OutputIter __result,
	_Predicate __pred, const _Tp& __new_value) {
			for ( ; __first != __last; ++__first, ++__result)
				*__result = __pred(*__first) ? __new_value : *__first;
		return __result;
	}


// random_shuffle

// TEMPLATE FUNCTION random_shuffle
template<class _RanIt,
class _Diff> inline
	void _Random_shuffle(_RanIt _First, _RanIt _Last, _Diff *)
{	// shuffle [_First, _Last)
	const int _RANDOM_BITS = 15;	// minimum random bits from rand()
	const int _RANDOM_MAX = (1U << _RANDOM_BITS) - 1;

	_RanIt _Next = _First;
	for (unsigned long _Index = 2; ++_Next != _Last; ++_Index)
	{	// assume unsigned long big enough for _Diff count
		unsigned long _Rm = _RANDOM_MAX;
		unsigned long _Rn = ::rand() & _RANDOM_MAX;
		for (; _Rm < _Index && _Rm != ~0UL;
			_Rm = _Rm << _RANDOM_BITS | _RANDOM_MAX)
			_Rn = _Rn << _RANDOM_BITS | _RANDOM_MAX;	// build random value

		nstl::iter_swap(_Next, _First + _Diff(_Rn % _Index));	// swap a pair
	}
}

template<class _RanIt> inline
	void random_shuffle(_RanIt _First, _RanIt _Last)
{	// shuffle [_First, _Last)
	if (_First != _Last)
		_Random_shuffle(_First, _Last, (int*)(0));
}

// TEMPLATE FUNCTION random_shuffle WITH RANDOM FN
template<class _RanIt,
class _Fn1,
class _Diff> inline
	void _Random_shuffle(_RanIt _First, _RanIt _Last, _Fn1& _Func, _Diff *)
{	// shuffle nonempty [_First, _Last) using random function _Func
	_RanIt _Next = _First;

	for (_Diff _Index = 2; ++_Next != _Last; ++_Index)
		nstl::iter_swap(_Next, _First + _Diff(_Func(_Index)));
}

template<class _RanIt,
class _Fn1> inline
	void random_shuffle(_RanIt _First, _RanIt _Last, _Fn1& _Func)
{	// shuffle [_First, _Last) using random function _Func
	if (_First != _Last)
		_Random_shuffle(_First, _Last, _Func, (int*)(0));
}


// TEMPLATE FUNCTION max_element WITH PRED
template<class _FwdIt,
class _Pr> inline
	_FwdIt max_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred = less() )
{	// find largest element, using _Pred
	_FwdIt _Found = _First;
	if (_First != _Last)
		for (; ++_First != _Last; )
			if (_Pred(*_Found, *_First))
				_Found = _First;
	return (_Found);
}
// for_each.	Apply a function to every element of a range.
template <class _InputIter, class _Function>
_Function
for_each(_InputIter __first, _InputIter __last, _Function __f) {
	for ( ; __first != __last; ++__first)
		__f(*__first);
	return __f;
}

// _unique_copy
template <class _InputIterator, class _OutputIterator, class _BinaryPredicate,	 class _Tp>
_OutputIterator
__unique_copy(_InputIterator __first, _InputIterator __last,
							_OutputIterator __result,
							_BinaryPredicate __binary_pred, _Tp&) {
	_Tp __val = *__first;
	*__result = __val;
	while (++__first != __last)
		if (!__binary_pred(__val, *__first)) {
			__val = *__first;
			*++__result = __val;
		}
	return ++__result;
}
// uniquie_copy
template <class _InputIter, class _OutputIter>
_OutputIter
unique_copy(_InputIter __first, _InputIter __last, _OutputIter __result) {

	if (__first == __last) return __result;
	return __unique_copy(__first, __last, __result, equal_to(),
											 //iterator_category(__result) );
											 *__first );
}

template <class _InputIter, class _OutputIter, class _BinaryPredicate>
_OutputIter
unique_copy(_InputIter __first, _InputIter __last,_OutputIter __result,
						_BinaryPredicate __binary_pred) {
	if (__first == __last) return __result;
	return __unique_copy(__first, __last, __result, __binary_pred,
											 //iterator_category(__result));
											 *__first);
}

// uniquie
template <class _ForwardIter>
inline _ForwardIter unique(_ForwardIter __first, _ForwardIter __last) {
	__first = adjacent_find(__first, __last);
	return unique_copy(__first, __last, __first);
}

template <class _ForwardIter, class _BinaryPredicate>
inline _ForwardIter unique(_ForwardIter __first, _ForwardIter __last,
										_BinaryPredicate __binary_pred) {
	__first = adjacent_find(__first, __last, __binary_pred);
	return unique_copy(__first, __last, __first, __binary_pred);
}

template<class _InIt1,
	class _InIt2,
	class _OutIt> inline
	_OutIt set_union(_InIt1 _First1, _InIt1 _Last1,
		_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest)
	{
	for (; _First1 != _Last1 && _First2 != _Last2; )
		if (*_First1 < *_First2)
			*_Dest++ = *_First1, ++_First1;
		else if (*_First2 < *_First1)
			*_Dest++ = *_First2, ++_First2;
		else
			*_Dest++ = *_First1, ++_First1, ++_First2;
	_Dest = copy(_First1, _Last1, _Dest);
	return (copy(_First2, _Last2, _Dest));
	}

template<class _InIt1,
	class _InIt2,
	class _OutIt,
	class _Pr> inline
	_OutIt set_union(_InIt1 _First1, _InIt1 _Last1,
		_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
	{
	for (; _First1 != _Last1 && _First2 != _Last2; )
		if (_Pred(*_First1, *_First2))
			*_Dest++ = *_First1, ++_First1;
		else if (_Pred(*_First2, *_First1))
			*_Dest++ = *_First2, ++_First2;
		else
			*_Dest++ = *_First1, ++_First1, ++_First2;
	_Dest = copy(_First1, _Last1, _Dest);
	return (copy(_First2, _Last2, _Dest));
	}

template <class _InputIter1, class _InputIter2, class _OutputIter, class _Compare>
inline _OutputIter set_difference(_InputIter1 __first1, _InputIter1 __last1,
																	_InputIter2 __first2, _InputIter2 __last2,
																	_OutputIter __result, _Compare __comp)
{
	while (__first1 != __last1 && __first2 != __last2)
	{
		if (__comp(*__first1, *__first2))
		{
			*__result = *__first1;
			++__first1;
			++__result;
		}
		else if (__comp(*__first2, *__first1))
			++__first2;
		else
		{
			++__first1;
			++__first2;
		}
	}

	return copy(__first1, __last1, __result);
}

template<class _InIt1, class _InIt2, class _OutIt>
inline _OutIt merge(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2, _InIt2 _Last2, _OutIt _Dest)
{	// copy merging ranges, both using operator<
	for (; _First1 != _Last1 && _First2 != _Last2; ++_Dest)
		if (*_First2 < *_First1)
			*_Dest = *_First2, ++_First2;
		else
			*_Dest = *_First1, ++_First1;

	_Dest = copy(_First1, _Last1, _Dest);	// copy any tail
	return copy(_First2, _Last2, _Dest);
}

// this implementation seems to be too common for me...

/*template <typename V, typename T> void PushUnique(V &v, T const &t)
{
  if (v.end() == find(v.begin(), v.end(), t)
  {
    v.push_back(t);
  }
}*/

// ... and I decided to use stricter one:

template <typename T> void PushUnique(vector<T> &v, T const &t)
{
  if (v.end() == find(v.begin(), v.end(), t))
  {
    v.push_back(t);
  }
}

}

#endif //NALGORITHM_H__
