/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *	 You should not attempt to use it directly.
 */


#ifndef NALGOBASE_H__
#define NALGOBASE_H__

#include "npair.h"

//#ifdef NI_PLATF_LINUX

  #include "string.h"
#include "nuninitialized.h"
#include <algorithm>

//#endif

//#include "ntype_traits.h"
//#include "niterator_base.h"

namespace nstl
{

/*# if ! defined (_NSTL_CSTDDEF)
#	include <cstddef>
# endif

#ifndef _NSTL_CSTRING
# include <cstring>
#endif

#ifndef _NSTL_CLIMITS
# include <climits>
#endif

# if ! defined (_NSTL_CSTDLIB)
#	include <cstdlib>
# endif

# ifndef _NSTL_INTERNAL_PAIR_H
#	include <stl/_pair.h>
# endif

#ifndef _NSTL_INTERNAL_ITERATOR_BASE_H
# include <stl/_iterator_base.h>
#endif

*/

template <class _Pair>
struct _Select1st {
	const typename _Pair::first_type& operator()(const _Pair& __x) const {
		return __x.first;
	}
};

// swap and iter_swap
template <class _Tp>
inline void swap(_Tp& __a, _Tp& __b) {
	_Tp __tmp = __a;
	__a = __b;
	__b = __tmp;
}

struct less { 
	template<class T>
	inline bool operator()( const T a, const T b ) const { return a < b; } 
};
struct less_equal { 
  template<class T>
  inline bool operator()( const T a, const T b ) const { return a <= b; } 
};
struct greater { 
	template<class T>
	inline bool operator()( const T a, const T b ) const { return a > b; } 
};
struct greater_equal { 
  template<class T>
  inline bool operator()( const T a, const T b ) const { return a >= b; } 
};
struct equal_to{ 
	template<class T>
	inline bool operator()( const T a, const T b ) const { return a == b; } 
};

template<class T>
struct equal_predicate
{
	const T &sample;
	equal_predicate( T _sample ) :
		sample( _sample )
	{}

	bool operator()( const T &ref ) const
	{
		return sample == ref;
	}
};
//template <class _ForwardIter1, class _ForwardIter2>
//inline void iter_swap(_ForwardIter1 __i1, _ForwardIter2 __i2) {
//	swap(*__i1, *__i2);
//}

template<class T>
int inline distance( T a, T b )
{
	int nRes = 0;
	for ( ; a != b; ++a ) 
		++nRes;
	return nRes;
}
//--------------------------------------------------
// min and max

template <class _Tp>
inline const _Tp& (min)(const _Tp& __a, const _Tp& __b) { return __b < __a ? __b : __a; }
template <class _Tp>
inline const _Tp& (max)(const _Tp& __a, const _Tp& __b) {	return	__a < __b ? __b : __a; }

template <class _Tp, class _Compare>
inline const _Tp& (min)(const _Tp& __a, const _Tp& __b, _Compare __comp) { 
	return __comp(__b, __a) ? __b : __a;
}

template <class _Tp, class _Compare>
inline const _Tp& (max)(const _Tp& __a, const _Tp& __b, _Compare __comp) {
	return __comp(__a, __b) ? __b : __a;
}

//--------------------------------------------------
// copy

// All of these auxiliary functions serve two purposes.	(1) Replace
// calls to copy with memmove whenever possible.	(Memmove, not memcpy,
// because the input and output ranges are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count.

template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last,
													_OutputIter __result ) {
	for ( ; __first != __last; ++__result, ++__first)
		*__result = *__first;
	return __result;
}

//--------------------------------------------------
// copy_backward auxiliary functions

template <class _BidirectionalIter1, class _BidirectionalIter2>
inline _BidirectionalIter2 copy_backward(_BidirectionalIter1 __first, 
																					 _BidirectionalIter1 __last, 
																					 _BidirectionalIter2 __result )
{
	while (__first != __last)
		*--__result = *--__last;
	return __result;
}

//--------------------------------------------------
// copy_n (not part of the C++ standard)

/*template <class _InputIter, class _Size, class _OutputIter>
_NSTL_INLINE_LOOP 
pair<_InputIter, _OutputIter> __copy_n(_InputIter __first, _Size __count,
																			 _OutputIter __result,
																			 const input_iterator_tag &) {
	for ( ; __count > 0; --__count) {
		*__result = *__first;
		++__first;
		++__result;
	}
	return pair<_InputIter, _OutputIter>(__first, __result);
}

template <class _RAIter, class _Size, class _OutputIter>
inline pair<_RAIter, _OutputIter>
__copy_n(_RAIter __first, _Size __count,
				 _OutputIter __result,
				 const random_access_iterator_tag &) {
	_RAIter __last = __first + __count;
	return pair<_RAIter, _OutputIter>(__last, copy(__first, __last, __result));
}

template <class _InputIter, class _Size, class _OutputIter>
inline pair<_InputIter, _OutputIter>
__copy_n(_InputIter __first, _Size __count, _OutputIter __result) {
	_NSTL_FIX_LITERAL_BUG(__first)
	return __copy_n(__first, __count, __result, _NSTL_ITERATOR_CATEGORY(__first, _InputIter));
}

template <class _InputIter, class _Size, class _OutputIter>
inline pair<_InputIter, _OutputIter>
copy_n(_InputIter __first, _Size __count, _OutputIter __result) {
	_NSTL_FIX_LITERAL_BUG(__first)
	return __copy_n(__first, __count, __result, _NSTL_ITERATOR_CATEGORY(__first, _InputIter));
}
*/
//--------------------------------------------------
// fill and fill_n


template <class _ForwardIter, class _Tp>
inline
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __val) {
	for ( ; __first != __last; ++__first)
		*__first = __val;
}

template <class _OutputIter, class _Size, class _Tp>
inline
_OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp& __val) {
	for ( ; __n > 0; --__n, ++__first)
		*__first = __val;
	return __first;
}


// Specialization: for one-byte types we can use memset.

inline void fill(unsigned char* __first, unsigned char* __last,
								 const unsigned char& __val) {
	unsigned char __tmp = __val;
	memset(__first, __tmp, __last - __first);
}
/*# ifndef _NSTL_NO_SIGNED_BUILTINS
inline void fill(signed char* __first, signed char* __last,
								 const signed char& __val) {
	signed char __tmp = __val;
	memset(__first, __STATIC_CAST(unsigned char,__tmp), __last - __first);
}
# endif*/
inline void fill(char* __first, char* __last, const char& __val) {
	char __tmp = __val;
	memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

#ifdef _NSTL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Size>
inline unsigned char* fill_n(unsigned char* __first, _Size __n,
														 const unsigned char& __val) {
	fill(__first, __first + __n, __val);
	return __first + __n;
}

template <class _Size>
inline signed char* fill_n(char* __first, _Size __n,
													 const signed char& __val) {
	fill(__first, __first + __n, __val);
	return __first + __n;
}

template <class _Size>
inline char* fill_n(char* __first, _Size __n, const char& __val) {
	fill(__first, __first + __n, __val);
	return __first + __n;
}

#endif /* _NSTL_FUNCTION_TMPL_PARTIAL_ORDER */


//--------------------------------------------------
// equal and mismatch
/*
template <class _InputIter1, class _InputIter2>
_NSTL_INLINE_LOOP
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
																				_InputIter1 __last1,
																				_InputIter2 __first2) {
	_NSTL_FIX_LITERAL_BUG(__first2)
	_NSTL_DEBUG_CHECK(__check_range(__first1, __last1))
	while (__first1 != __last1 && *__first1 == *__first2) {
		++__first1;
		++__first2;
	}
	return pair<_InputIter1, _InputIter2>(__first1, __first2);
}

template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
_NSTL_INLINE_LOOP
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
																				_InputIter1 __last1,
																				_InputIter2 __first2,
																				_BinaryPredicate __binary_pred) {
	_NSTL_FIX_LITERAL_BUG(__first2)
	_NSTL_DEBUG_CHECK(__check_range(__first1, __last1))
	while (__first1 != __last1 && __binary_pred(*__first1, *__first2)) {
		++__first1;
		++__first2;
	}
	return pair<_InputIter1, _InputIter2>(__first1, __first2);
}
*/
template <class _InputIter1, class _InputIter2>
inline
bool equal(_InputIter1 __first1, _InputIter1 __last1,
									_InputIter2 __first2) {
	for ( ; __first1 != __last1; ++__first1, ++__first2)
		if (!(*__first1 == *__first2))
			return false;
	return true;
}

template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
inline
bool equal(_InputIter1 __first1, _InputIter1 __last1,
									_InputIter2 __first2, _BinaryPredicate __binary_pred) {
	for ( ; __first1 != __last1; ++__first1, ++__first2)
		if (!__binary_pred(*__first1, *__first2))
			return false;
	return true;
}

//--------------------------------------------------
// lexicographical_compare and lexicographical_compare_3way.
// (the latter is not part of the C++ standard.)

template <class _InputIter1, class _InputIter2>
inline 
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
														 _InputIter2 __first2, _InputIter2 __last2)
{
	for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2) 
	{
		if (*__first1 < *__first2)
			return true;
		if (*__first2 < *__first1)
			return false;
	}
	return __first1 == __last1 && __first2 != __last2;
}

template <class _InputIter1, class _InputIter2, class _Compare>
inline 
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
														 _InputIter2 __first2, _InputIter2 __last2,
														 _Compare __comp)
{
	for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2) 
	{
		if (__comp(*__first1, *__first2))
			return true;
		if (__comp(*__first2, *__first1))
			return false;
	}
	return __first1 == __last1 && __first2 != __last2;
}

inline bool 
lexicographical_compare(const unsigned char* __first1,
												const unsigned char* __last1,
												const unsigned char* __first2,
												const unsigned char* __last2)
{
	const size_t __len1 = __last1 - __first1;
	const size_t __len2 = __last2 - __first2;

	const int __result = memcmp(__first1, __first2, (min) (__len1, __len2));
	return __result != 0 ? (__result < 0) : (__len1 < __len2);
}

/*
# if !(CHAR_MAX == SCHAR_MAX)
inline bool lexicographical_compare(const char* __first1, const char* __last1,
																		const char* __first2, const char* __last2)
{

	return lexicographical_compare((const unsigned char*) __first1,
																 (const unsigned char*) __last1,
																 (const unsigned char*) __first2,
																 (const unsigned char*) __last2);
}
#endif // CHAR_MAX == SCHAR_MAX 

template <class _InputIter1, class _InputIter2>
int __lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
																	 _InputIter2 __first2, _InputIter2 __last2);

inline int
__lexicographical_compare_3way(const unsigned char* __first1,
															 const unsigned char* __last1,
															 const unsigned char* __first2,
															 const unsigned char* __last2)
{
	const ptrdiff_t __len1 = __last1 - __first1;
	const ptrdiff_t __len2 = __last2 - __first2;
	const int __result = memcmp(__first1, __first2, (min) (__len1, __len2));
	return __result != 0 ? __result 
											 : (__len1 == __len2 ? 0 : (__len1 < __len2 ? -1 : 1));
}
*/
/*
# if !(CHAR_MAX == SCHAR_MAX)
inline int 
__lexicographical_compare_3way(const char* __first1, const char* __last1,
															 const char* __first2, const char* __last2)
{
	return __lexicographical_compare_3way((const unsigned char*) __first1,
																				(const unsigned char*) __last1,
																				(const unsigned char*) __first2,
																				(const unsigned char*) __last2);
}
# endif
*/
// count
template <class _InputIter, class _Tp>
inline int
count(_InputIter __first, _InputIter __last, const _Tp& __val) {
	int __n = 0;
	for ( ; __first != __last; ++__first)
		if (*__first == __val)
			++__n;
	return __n;
}

// find and find_if. Note find may be expressed in terms of find_if if appropriate binder was available.
template <class _InputIter, class _Tp>
inline 
_InputIter find(_InputIter __first, _InputIter __last, const _Tp& __val)
{
	while (__first != __last && !(*__first == __val))
		++__first;
	return __first;
}
template <class _InputIter, class _Predicate>
inline 
_InputIter find_if(_InputIter __first, _InputIter __last, _Predicate __pred)
{
	while (__first != __last && !__pred(*__first))
		++__first;
	return __first;
}

// search.
template <class _ForwardIter1, class _ForwardIter2, class _BinaryPred>
inline 
_ForwardIter1 search(_ForwardIter1 __first1, _ForwardIter1 __last1,
										 _ForwardIter2 __first2, _ForwardIter2 __last2, _BinaryPred	__predicate)
{
	// Test for empty ranges
	if (__first1 == __last1 || __first2 == __last2)
		return __first1;

	// Test for a pattern of length 1.
	_ForwardIter2 __tmp(__first2);
	++__tmp;
	if (__tmp == __last2) {
		while (__first1 != __last1 && !__predicate(*__first1, *__first2))
			++__first1;
		return __first1;		
	}

	// General case.

	_ForwardIter2 __p1, __p;

	__p1 = __first2; ++__p1;

	//	_ForwardIter1 __current = __first1;

	while (__first1 != __last1) {
		while (__first1 != __last1) {
			if (__predicate(*__first1, *__first2))
				break;
			++__first1;
		}
		while (__first1 != __last1 && !__predicate(*__first1, *__first2))
			++__first1;
		if (__first1 == __last1)
			return __last1;

		__p = __p1;
		_ForwardIter1 __current = __first1; 
		if (++__current == __last1) return __last1;

		while (__predicate(*__current, *__p)) {
			if (++__p == __last2)
				return __first1;
			if (++__current == __last1)
				return __last1;
		}

		++__first1;
	}
	return __first1;
}

// find_first_of
template <class _InputIter, class _ForwardIter>
inline 
_InputIter __find_first_of(_InputIter __first1, _InputIter __last1,
													 _ForwardIter __first2, _ForwardIter __last2)
{
	for ( ; __first1 != __last1; ++__first1) 
		for (_ForwardIter __iter = __first2; __iter != __last2; ++__iter)
			if (*__first1 == *__iter)
				return __first1;
	return __last1;
}

/*template <class _ForwardIter1, class _ForwardIter2, 
					class _BinaryPredicate>
_ForwardIter1 
find_end(_ForwardIter1 __first1, _ForwardIter1 __last1, 
				 _ForwardIter2 __first2, _ForwardIter2 __last2,
				 _BinaryPredicate __comp);
*/
// replace
template <class _ForwardIter, class _Tp>
inline void 
replace(_ForwardIter __first, _ForwardIter __last,
				const _Tp& __old_value, const _Tp& __new_value) {
	for ( ; __first != __last; ++__first)
		if (*__first == __old_value)
			*__first = __new_value;
}

template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
_ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
															const _Tp& __val, _Compare __comp, _Distance*)
{
	_Distance __len = __last - __first;//distance(__first, __last);
	_Distance __half;
	_ForwardIter __middle;

	while (__len > 0) {
		__half = __len >> 1;
		__middle = __first;
		__middle += __half; // advance()
		if (__comp(*__middle, __val)) {
			__first = __middle;
			++__first;
			__len = __len - __half - 1;
		}
		else
			__len = __half;
	}
	return __first;
}





				// find_end, with and without an explicitly supplied comparison function.
				// Search [first2, last2) as a subsequence in [first1, last1), and return
				// the *last* possible match.	Note that find_end for bidirectional iterators
				// is much faster than for forward iterators.

				// find_end for forward iterators. 
/*
				template <class _ForwardIter1, class _ForwardIter2,
				class _BinaryPredicate>
					_ForwardIter1 __find_end(_ForwardIter1 __first1, _ForwardIter1 __last1,
					_ForwardIter2 __first2, _ForwardIter2 __last2,
					const forward_iterator_tag &, const forward_iterator_tag &,
					_BinaryPredicate __comp)
				{
					if (__first2 == __last2)
						return __last1;
					else {
						_ForwardIter1 __result = __last1;
						while (1) {
							_ForwardIter1 __new_result
								= search(__first1, __last1, __first2, __last2, __comp);
							if (__new_result == __last1)
								return __result;
							else {
								__result = __new_result;
								__first1 = __new_result;
								++__first1;
							}
						}
					}
				}

				// find_end for bidirectional iterators.	Requires partial specialization.
#if defined ( _NSTL_CLASS_PARTIAL_SPECIALIZATION )

#if ! defined (_NSTL_INTERNAL_ITERATOR_H)
				_NSTL_END_NAMESPACE
# include <stl/_iterator.h>
					_NSTL_BEGIN_NAMESPACE 
#endif

					template <class _BidirectionalIter1, class _BidirectionalIter2,
				class _BinaryPredicate>
					_BidirectionalIter1
					__find_end(_BidirectionalIter1 __first1, _BidirectionalIter1 __last1,
					_BidirectionalIter2 __first2, _BidirectionalIter2 __last2,
					const bidirectional_iterator_tag &, const bidirectional_iterator_tag &, 
					_BinaryPredicate __comp)
				{
					typedef reverse_iterator<_BidirectionalIter1> _RevIter1;
					typedef reverse_iterator<_BidirectionalIter2> _RevIter2;

					_RevIter1 __rlast1(__first1);
					_RevIter2 __rlast2(__first2);
					_RevIter1 __rresult = search(_RevIter1(__last1), __rlast1,
						_RevIter2(__last2), __rlast2,
						__comp);

					if (__rresult == __rlast1)
						return __last1;
					else {
						_BidirectionalIter1 __result = __rresult.base();
						advance(__result, -distance(__first2, __last2));
						return __result;
					}
				}
#endif // _NSTL_CLASS_PARTIAL_SPECIALIZATION 

				template <class _ForwardIter1, class _ForwardIter2, 
				class _BinaryPredicate>
					_ForwardIter1 
					find_end(_ForwardIter1 __first1, _ForwardIter1 __last1, 
					_ForwardIter2 __first2, _ForwardIter2 __last2,
					_BinaryPredicate __comp)
				{
					_NSTL_DEBUG_CHECK(__check_range(__first1, __last1))
						_NSTL_DEBUG_CHECK(__check_range(__first2, __last2))
						return __find_end(__first1, __last1, __first2, __last2,
# if defined (_NSTL_CLASS_PARTIAL_SPECIALIZATION)
						_NSTL_ITERATOR_CATEGORY(__first1, _ForwardIter1),
						_NSTL_ITERATOR_CATEGORY(__first2, _ForwardIter2),
# else
						forward_iterator_tag(),
						forward_iterator_tag(),
# endif
						__comp);
				}

*/



		// count_if
/*template <class _InputIter, class _Predicate>
	_STLP_INLINE_LOOP _STLP_DIFFERENCE_TYPE(_InputIter)
	count_if(_InputIter __first, _InputIter __last, _Predicate __pred) {
		_STLP_DEBUG_CHECK(__check_range(__first, __last))
			_STLP_DIFFERENCE_TYPE(_InputIter) __n = 0;
		for ( ; __first != __last; ++__first)
			if (__pred(*__first))
				++__n;
		return __n;
	}

	// adjacent_find.
	template <class _ForwardIter>
		_STLP_INLINE_LOOP _ForwardIter 
		adjacent_find(_ForwardIter __first, _ForwardIter __last) {
			_STLP_DEBUG_CHECK(__check_range(__first, __last))
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
			_STLP_INLINE_LOOP _ForwardIter 
			adjacent_find(_ForwardIter __first, _ForwardIter __last,
			_BinaryPredicate __binary_pred) {
				_STLP_DEBUG_CHECK(__check_range(__first, __last))
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


template <class _ForwardIter1, class _ForwardIter2>
_ForwardIter1 search(_ForwardIter1 __first1, _ForwardIter1 __last1,
_ForwardIter2 __first2, _ForwardIter2 __last2);

// search_n.	Search for __count consecutive copies of __val.
template <class _ForwardIter, class _Integer, class _Tp>
_ForwardIter search_n(_ForwardIter __first, _ForwardIter __last,
_Integer __count, const _Tp& __val);
template <class _ForwardIter, class _Integer, class _Tp, class _BinaryPred>
_ForwardIter search_n(_ForwardIter __first, _ForwardIter __last,
_Integer __count, const _Tp& __val, _BinaryPred __binary_pred);

template <class _InputIter, class _ForwardIter>
inline _InputIter find_first_of(_InputIter __first1, _InputIter __last1,
_ForwardIter __first2, _ForwardIter __last2) {
_STLP_DEBUG_CHECK(__check_range(__first1, __last1))
	_STLP_DEBUG_CHECK(__check_range(__first2, __last2))
	return __find_first_of(__first1, __last1, __first2, __last2,__equal_to(_STLP_VALUE_TYPE(__first1, _InputIter)));
}

template <class _InputIter, class _ForwardIter, class _BinaryPredicate>
inline _InputIter 
find_first_of(_InputIter __first1, _InputIter __last1,
_ForwardIter __first2, _ForwardIter __last2,_BinaryPredicate __comp) {
	_STLP_DEBUG_CHECK(__check_range(__first1, __last1))
		_STLP_DEBUG_CHECK(__check_range(__first2, __last2))
		return __find_first_of(__first1, __last1, __first2, __last2,__comp);
}

template <class _ForwardIter1, class _ForwardIter2>
	_ForwardIter1 
	find_end(_ForwardIter1 __first1, _ForwardIter1 __last1, 
	_ForwardIter2 __first2, _ForwardIter2 __last2);

// swap_ranges
template <class _ForwardIter1, class _ForwardIter2>
	_STLP_INLINE_LOOP _ForwardIter2 
	swap_ranges(_ForwardIter1 __first1, _ForwardIter1 __last1, _ForwardIter2 __first2) {
		_STLP_DEBUG_CHECK(__check_range(__first1, __last1))
			for ( ; __first1 != __last1; ++__first1, ++__first2)
				iter_swap(__first1, __first2);
		return __first2;
	}
*/
	// transform
	template <class _InputIter, class _OutputIter, class _UnaryOperation>
		_OutputIter 
		transform(_InputIter __first, _InputIter __last, _OutputIter __result, _UnaryOperation __opr) {
				for ( ; __first != __last; ++__first, ++__result)
					*__result = __opr(*__first);
			return __result;
		}
		template <class _InputIter1, class _InputIter2, class _OutputIter, class _BinaryOperation>
			_OutputIter 
			transform(_InputIter1 __first1, _InputIter1 __last1, 
			_InputIter2 __first2, _OutputIter __result,_BinaryOperation __binary_op) {
					for ( ; __first1 != __last1; ++__first1, ++__first2, ++__result)
						*__result = __binary_op(*__first1, *__first2);
				return __result;
			}
/*
			// replace_if, replace_copy, replace_copy_if

			template <class _ForwardIter, class _Predicate, class _Tp>
				_STLP_INLINE_LOOP void 
				replace_if(_ForwardIter __first, _ForwardIter __last, _Predicate __pred, const _Tp& __new_value) {
					_STLP_DEBUG_CHECK(__check_range(__first, __last))
						for ( ; __first != __last; ++__first)
							if (__pred(*__first))
								*__first = __new_value;
				}

				template <class _InputIter, class _OutputIter, class _Tp>
					_STLP_INLINE_LOOP	_OutputIter 
					replace_copy(_InputIter __first, _InputIter __last,_OutputIter __result,
					const _Tp& __old_value, const _Tp& __new_value) {
						_STLP_DEBUG_CHECK(__check_range(__first, __last))
							for ( ; __first != __last; ++__first, ++__result)
								*__result = *__first == __old_value ? __new_value : *__first;
						return __result;
					}

					template <class _Iterator, class _OutputIter, class _Predicate, class _Tp>
						_STLP_INLINE_LOOP _OutputIter 
						replace_copy_if(_Iterator __first, _Iterator __last,
						_OutputIter __result,
						_Predicate __pred, const _Tp& __new_value) {
							_STLP_DEBUG_CHECK(__check_range(__first, __last))
								for ( ; __first != __last; ++__first, ++__result)
									*__result = __pred(*__first) ? __new_value : *__first;
							return __result;
						}

						// generate and generate_n

						template <class _ForwardIter, class _Generator>
							_STLP_INLINE_LOOP void 
							generate(_ForwardIter __first, _ForwardIter __last, _Generator __gen) {
								_STLP_DEBUG_CHECK(__check_range(__first, __last))
									for ( ; __first != __last; ++__first)
										*__first = __gen();
}

template <class _OutputIter, class _Size, class _Generator>
	_STLP_INLINE_LOOP _OutputIter 
	generate_n(_OutputIter __first, _Size __n, _Generator __gen) {
		for ( ; __n > 0; --__n, ++__first)
			*__first = __gen();
		return __first;
	}
*/
	// remove, remove_if, remove_copy, remove_copy_if

	template <class _InputIter, class _OutputIter, class _Tp>
		_OutputIter 
		remove_copy(_InputIter __first, _InputIter __last,_OutputIter __result, const _Tp& __val) {
				for ( ; __first != __last; ++__first)
					if (!(*__first == __val)) {
						*__result = *__first;
						++__result;
					}
					return __result;
		}

		template <class _InputIter, class _OutputIter, class _Predicate>
			_OutputIter 
			remove_copy_if(_InputIter __first, _InputIter __last, _OutputIter __result, _Predicate __pred) {
					for ( ; __first != __last; ++__first)
						if (!__pred(*__first)) {
							*__result = *__first;
							++__result;
						}
						return __result;
			}

			template <class _ForwardIter, class _Tp>
				inline _ForwardIter 
				remove(_ForwardIter __first, _ForwardIter __last, const _Tp& __val) {
					__first = find(__first, __last, __val);
					if (__first == __last)
						return __first;
					else { 
						_ForwardIter __next = __first;
						return remove_copy(++__next, __last, __first, __val);
					}
				}

				template <class _ForwardIter, class _Predicate>
					 _ForwardIter 
					remove_if(_ForwardIter __first, _ForwardIter __last, _Predicate __pred) {
						__first = find_if(__first, __last, __pred);
						if ( __first == __last )
							return __first;
						else {
							_ForwardIter __next = __first;
							return remove_copy_if(++__next, __last, __first, __pred);
						}
					}
/*
					// unique and unique_copy
					template <class _InputIter, class _OutputIter>
						_OutputIter unique_copy(_InputIter __first, _InputIter __last, _OutputIter __result);

					template <class _InputIter, class _OutputIter, class _BinaryPredicate>
						_OutputIter unique_copy(_InputIter __first, _InputIter __last,_OutputIter __result,
						_BinaryPredicate __binary_pred);

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

							// reverse and reverse_copy, and their auxiliary functions

							template <class _BidirectionalIter>
								_STLP_INLINE_LOOP void 
								__reverse(_BidirectionalIter __first, _BidirectionalIter __last, const bidirectional_iterator_tag &) {
									while (true)
										if (__first == __last || __first == --__last)
											return;
										else
											iter_swap(__first++, __last);
								}


								template <class _RandomAccessIter>
									_STLP_INLINE_LOOP void 
									__reverse(_RandomAccessIter __first, _RandomAccessIter __last, const random_access_iterator_tag &) {
										for (; __first < __last; ++__first) iter_swap(__first, --__last);
									}
*/
									template <class _BidirectionalIter>
										inline void 
										reverse(_BidirectionalIter __first, _BidirectionalIter __last) {
											for(;;)
												if (__first == __last || __first == --__last)
													return;
												else
													swap( *__first++, *__last);
//											_STLP_DEBUG_CHECK(__check_range(__first, __last))
												//__reverse(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _BidirectionalIter));
										}
/*
										template <class _BidirectionalIter, class _OutputIter>
											_STLP_INLINE_LOOP
											_OutputIter reverse_copy(_BidirectionalIter __first,
											_BidirectionalIter __last,
											_OutputIter __result) {
												_STLP_DEBUG_CHECK(__check_range(__first, __last))
													while (__first != __last) {
														--__last;
														*__result = *__last;
														++__result;
													}
													return __result;
											}

											// rotate and rotate_copy, and their auxiliary functions

											template <class _EuclideanRingElement>
												_STLP_INLINE_LOOP
												_EuclideanRingElement __gcd(_EuclideanRingElement __m,
												_EuclideanRingElement __n)
											{
												while (__n != 0) {
													_EuclideanRingElement __t = __m % __n;
													__m = __n;
													__n = __t;
												}
												return __m;
											}

											template <class _ForwardIter>
												_ForwardIter 
												rotate(_ForwardIter __first, _ForwardIter __middle, _ForwardIter __last);

											template <class _ForwardIter, class _OutputIter>
												inline _OutputIter rotate_copy(_ForwardIter __first, _ForwardIter __middle,
												_ForwardIter __last, _OutputIter __result) {
													return copy(__first, __middle, copy(__middle, __last, __result));
												}

												// random_shuffle

												template <class _RandomAccessIter>
													void random_shuffle(_RandomAccessIter __first, _RandomAccessIter __last);

												template <class _RandomAccessIter, class _RandomNumberGenerator>
													void random_shuffle(_RandomAccessIter __first, _RandomAccessIter __last,
													_RandomNumberGenerator& __rand);

# ifndef _STLP_NO_EXTENSIONS
												// random_sample and random_sample_n (extensions, not part of the standard).

												template <class _ForwardIter, class _OutputIter, class _Distance>
													_OutputIter random_sample_n(_ForwardIter __first, _ForwardIter __last,
													_OutputIter __out, const _Distance __n);

												template <class _ForwardIter, class _OutputIter, class _Distance,
												class _RandomNumberGenerator>
													_OutputIter random_sample_n(_ForwardIter __first, _ForwardIter __last,
													_OutputIter __out, const _Distance __n,
													_RandomNumberGenerator& __rand);

												template <class _InputIter, class _RandomAccessIter>
													_RandomAccessIter
													random_sample(_InputIter __first, _InputIter __last,
													_RandomAccessIter __out_first, _RandomAccessIter __out_last);

												template <class _InputIter, class _RandomAccessIter, 
												class _RandomNumberGenerator>
													_RandomAccessIter
													random_sample(_InputIter __first, _InputIter __last,
													_RandomAccessIter __out_first, _RandomAccessIter __out_last,
													_RandomNumberGenerator& __rand);

# endif // _STLP_NO_EXTENSIONS 

												// partition, stable_partition, and their auxiliary functions

												template <class _ForwardIter, class _Predicate>
													_ForwardIter partition(_ForwardIter __first, _ForwardIter __last, _Predicate	 __pred);


												template <class _ForwardIter, class _Predicate>
													_ForwardIter 
													stable_partition(_ForwardIter __first, _ForwardIter __last, _Predicate __pred);

												// sort() and its auxiliary functions. 
*/

# define	__stl_threshold	16

template <class _RandomAccessIter, class _Tp, class _Compare>
void __unguarded_linear_insert(_RandomAccessIter __last, _Tp __val, 
_Compare __comp) {
_RandomAccessIter __next = __last;
--__next;	
while (__comp(__val, *__next)) {
	*__last = *__next;
	__last = __next;
	--__next;
}
*__last = __val;
}

template <class _RandomAccessIter, class _Tp, class _Compare>
inline void __linear_insert(_RandomAccessIter __first, 
_RandomAccessIter __last, _Tp __val, _Compare __comp) {	 
	//*TY 12/26/1998 - added __val as a paramter
	//	_Tp __val = *__last;				//*TY 12/26/1998 - __val supplied by caller
	if (__comp(__val, *__first)) {
		copy_backward(__first, __last, __last + 1);
		*__first = __val;
	}
	else
		__unguarded_linear_insert(__last, __val, __comp);
}

template <class _RandomAccessIter, class _Compare>
	void __insertion_sort(_RandomAccessIter __first,
	_RandomAccessIter __last, _Compare __comp) {
		if (__first == __last) return;
		for (_RandomAccessIter __i = __first + 1; __i != __last; ++__i)
			__linear_insert(__first, __i, *__i, __comp);	//*TY 12/26/1998 - supply *__i as __val
	}

	template <class _RandomAccessIter, class _Compare>
		void __unguarded_insertion_sort_aux(_RandomAccessIter __first, 
		_RandomAccessIter __last,
		_Compare __comp) {
			for (_RandomAccessIter __i = __first; __i != __last; ++__i)
				__unguarded_linear_insert(__i, *__i, __comp);
		}

		template <class _RandomAccessIter, class _Compare>
			inline void __unguarded_insertion_sort(_RandomAccessIter __first, 
			_RandomAccessIter __last,
			_Compare __comp) {
				__unguarded_insertion_sort_aux(__first, __last, __comp);
			}

			template <class _RandomAccessIter, class _Compare>
				void __final_insertion_sort(_RandomAccessIter __first, 
				_RandomAccessIter __last, _Compare __comp) {
					//if (__last - __first > __stl_threshold) {
					//	__insertion_sort(__first, __first + __stl_threshold, __comp);
					//	__unguarded_insertion_sort(__first + __stl_threshold, __last, __comp);
					//}
					//else
						__insertion_sort(__first, __last, __comp);
				}

				template <class _RandomAccessIter, class _Compare>
				void insertion_sort(_RandomAccessIter __first, 
					_RandomAccessIter __last, _Compare __comp) {
						__final_insertion_sort( __first, __last, __comp );
				}

				template <class _RandomAccessIter>
				void insertion_sort(_RandomAccessIter __first, _RandomAccessIter __last) 
				{
					__final_insertion_sort( __first, __last, less() );
				}
/*
				template <class _RandomAccessIter, class _Size, class _Compare>
					void __introsort_loop(_RandomAccessIter __first,
					_RandomAccessIter __last,
					_Size __depth_limit, _Compare __comp)
				{
					while (__last - __first > __stl_threshold) {
						if (__depth_limit == 0) {
							partial_sort(__first, __last, __last, __comp);
							return;
						}
						--__depth_limit;
						_RandomAccessIter __cut =
							__unguarded_partition(__first, __last,
							_Tp(__median(*__first,
							*(__first + (__last - __first)/2),
							*(__last - 1), __comp)),
							__comp);
						__introsort_loop(__cut, __last, __depth_limit, __comp);
						__last = __cut;
					}
				}
*/
/*				template <class _RandomAccessIter>
					void sort(_RandomAccessIter __first, _RandomAccessIter __last) {
							if (__first != __last) {
								__introsort_loop(__first, __last,
									__lg(__last - __first) * 2, __less(_STLP_VALUE_TYPE(__first, _RandomAccessIter)) );
								__final_insertion_sort(__first, __last, __less(_STLP_VALUE_TYPE(__first, _RandomAccessIter)));
							}
					}*/

template<class T, class TComp>
inline void JoinSortStage( int step, const T *src, T *pDst, int nCount, TComp compare )
{
	int i,n1,n2,step2,dest,numSteps;
	step2 = step * 2;
	if ( step*2 > nCount )
	{
		numSteps = nCount - step;
		for ( int k = 0; k < step; ++k )
			pDst[ nCount - step + k ] = src[ nCount - step + k ];
//		memcpy( pDst + nCount - step, pSrc + nCount - step, step * sizeof(pSrc[0]) );
	} else {
		numSteps = step;
	}
	numSteps = min( step, nCount-step );
	for ( i = 0; i < numSteps; i++ )
	{
		n1 = i;
		n2 = i+step;
		dest = i;
#ifndef NI_PLATF_LINUX
#pragma warning( push )
#pragma warning( disable: 4127 ) // 4127: conditional expression is constant
#endif
		while ( 1 )
		{
			if ( !compare( *src[n1], *src[n2] ) )
			{
				pDst[dest] = src[n2];
				n2 += step2;
				dest += step;
				if ( n2>= nCount ) {
					while ( n1 < nCount )
					{
						pDst[dest] = src[n1];
						n1 += step2;
						dest += step;
					}
					break;
				}
			} else {
				pDst[dest] = src[n1];
				n1 += step2;
				dest += step;
				if ( n1>= nCount ) {
					while ( n2 < nCount )
					{
						pDst[dest] = src[n2];
						n2 += step2;
						dest += step;
					}
					break;
				}
			}
		}
#ifndef NI_PLATF_LINUX
#pragma warning( pop )
#endif
	}
}

template<class T, class T1>
inline void SortReorder( T pRes, T *sorted, int nSize, T1 a )
{
  ((void)a);
	T1 *pData = (T1*)new char[ sizeof(T1) * nSize ];
	for ( int k = 0; k < nSize; ++k )
		new( &pData[k]) T1( *sorted[k] );
	for ( int k = 0; k < nSize; ++k )
		*pRes++ = pData[k];
	_Destroy( pData, pData + nSize );
	delete[] ((char*)pData);
}

template <class T, class _Compare>
void sort(T __first, T __last, _Compare __comp) 
{
	if ( __first == __last )
		return;
	int nElems = distance( __first, __last );
	if ( nElems <= 1 )
		return;
	T *data = new T[ nElems ], *tmpData = new T[ nElems ], **pSort, **pSortDst;
	{
		T *pDest = data;
		for ( T p = __first; p != __last; ++p )
			*pDest++ = p;
	}

	pSort = &data; 
	pSortDst = &tmpData;
	int nStep = 0x40000000;
	while ( nStep >= nElems ) nStep >>= 1; // determine initial step for join sort

	while ( nStep > 0 )
	{
		JoinSortStage( nStep, *pSort, *pSortDst, nElems, __comp );
		nStep >>= 1;
		swap( pSort, pSortDst );
	}
	SortReorder( __first, *pSort, nElems, *__first );
	delete[] data;
	delete[] tmpData;
}

template <class _RandomAccessIter>
	void sort(_RandomAccessIter __first, _RandomAccessIter __last) 
{
	sort( __first, __last, less() );
}


template<class _RandomAccessIter, class _Compare>
  void merge_sort(_RandomAccessIter __first, _RandomAccessIter __last, _Compare __comp)
{
  if ( __first == __last )
		return;

	int nElems = distance( __first, __last );
	if ( nElems <= 1 )
		return;

  _RandomAccessIter __middle = __first + nElems / 2;
  merge_sort(__first, __middle, __comp);
  merge_sort(__middle, __last, __comp);
  std::inplace_merge(__first, __middle, __last, __comp);
}
 
template<class _RandomAccessIter>
  void merge_sort(_RandomAccessIter __first, _RandomAccessIter __last)
{
  merge_sort(__first, __last, less());
}

/*
													template <class _RandomAccessIter>
														void sort(_RandomAccessIter __first, _RandomAccessIter __last);
													template <class _RandomAccessIter, class _Compare>
														void sort(_RandomAccessIter __first, _RandomAccessIter __last, _Compare __comp);

													// stable_sort() and its auxiliary functions.
													template <class _RandomAccessIter>
														void stable_sort(_RandomAccessIter __first,
														_RandomAccessIter __last);

													template <class _RandomAccessIter, class _Compare>
														void stable_sort(_RandomAccessIter __first,
														_RandomAccessIter __last, _Compare __comp);

													// partial_sort, partial_sort_copy, and auxiliary functions.

													template <class _RandomAccessIter>
														void 
														partial_sort(_RandomAccessIter __first,_RandomAccessIter __middle, _RandomAccessIter __last);

													template <class _RandomAccessIter, class _Compare>
														void 
														partial_sort(_RandomAccessIter __first,_RandomAccessIter __middle, 
														_RandomAccessIter __last, _Compare __comp);

													template <class _InputIter, class _RandomAccessIter>
														_RandomAccessIter
														partial_sort_copy(_InputIter __first, _InputIter __last,
														_RandomAccessIter __result_first, _RandomAccessIter __result_last);

													template <class _InputIter, class _RandomAccessIter, class _Compare>
														_RandomAccessIter
														partial_sort_copy(_InputIter __first, _InputIter __last,
														_RandomAccessIter __result_first,
														_RandomAccessIter __result_last, _Compare __comp);

													// nth_element() and its auxiliary functions.	

													template <class _RandomAccessIter>
														void nth_element(_RandomAccessIter __first, _RandomAccessIter __nth,
														_RandomAccessIter __last);

													template <class _RandomAccessIter, class _Compare>
														void nth_element(_RandomAccessIter __first, _RandomAccessIter __nth,
														_RandomAccessIter __last, _Compare __comp);

													// Binary search (lower_bound, upper_bound, equal_range, binary_search).

													template <class _ForwardIter, class _Tp>
														inline _ForwardIter lower_bound(_ForwardIter __first, _ForwardIter __last,
														const _Tp& __val) {
																return __lower_bound(__first, __last, __val, less<_Tp>(), _STLP_DISTANCE_TYPE(__first, _ForwardIter));
														}

														template <class _ForwardIter, class _Tp, class _Compare>
															inline _ForwardIter lower_bound(_ForwardIter __first, _ForwardIter __last,
															const _Tp& __val, _Compare __comp) {
																_STLP_DEBUG_CHECK(__check_range(__first, __last))
																	return __lower_bound(__first, __last, __val, __comp, _STLP_DISTANCE_TYPE(__first, _ForwardIter));
															}

															template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
																_ForwardIter __upper_bound(_ForwardIter __first, _ForwardIter __last,
																const _Tp& __val, _Compare __comp, _Distance*);

															template <class _ForwardIter, class _Tp>
																																		inline _ForwardIter upper_bound(_ForwardIter __first, _ForwardIter __last,
	const _Tp& __val) {
		_STLP_DEBUG_CHECK(__check_range(__first, __last))
			return __upper_bound(__first, __last, __val, less<_Tp>(), 
			_STLP_DISTANCE_TYPE(__first, _ForwardIter));
	}

	template <class _ForwardIter, class _Tp, class _Compare>
		inline _ForwardIter upper_bound(_ForwardIter __first, _ForwardIter __last,
		const _Tp& __val, _Compare __comp) {
			_STLP_DEBUG_CHECK(__check_range(__first, __last))
				return __upper_bound(__first, __last, __val, __comp,
				_STLP_DISTANCE_TYPE(__first, _ForwardIter));
		}

		template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
			pair<_ForwardIter, _ForwardIter>
			__equal_range(_ForwardIter __first, _ForwardIter __last, const _Tp& __val,
			_Compare __comp, _Distance*);

		template <class _ForwardIter, class _Tp>
			inline pair<_ForwardIter, _ForwardIter>
			equal_range(_ForwardIter __first, _ForwardIter __last, const _Tp& __val) {
				_STLP_DEBUG_CHECK(__check_range(__first, __last))
					return __equal_range(__first, __last, __val,	less<_Tp>(),
					_STLP_DISTANCE_TYPE(__first, _ForwardIter));
			}

			template <class _ForwardIter, class _Tp, class _Compare>
				inline pair<_ForwardIter, _ForwardIter>
				equal_range(_ForwardIter __first, _ForwardIter __last, const _Tp& __val,
				_Compare __comp) {
						return __equal_range(__first, __last, __val, __comp,
						_STLP_DISTANCE_TYPE(__first, _ForwardIter));
				} 

				template <class _ForwardIter, class _Tp>
					inline bool binary_search(_ForwardIter __first, _ForwardIter __last,
					const _Tp& __val) {
							_ForwardIter __i = __lower_bound(__first, __last, __val, less<_Tp>(), _STLP_DISTANCE_TYPE(__first, _ForwardIter));
						return __i != __last && !(__val < *__i);
					}

					template <class _ForwardIter, class _Tp, class _Compare>
						inline bool binary_search(_ForwardIter __first, _ForwardIter __last,
						const _Tp& __val,
						_Compare __comp) {
							_STLP_DEBUG_CHECK(__check_range(__first, __last))
								_ForwardIter __i = __lower_bound(__first, __last, __val, __comp, _STLP_DISTANCE_TYPE(__first, _ForwardIter));
							return __i != __last && !__comp(__val, *__i);
						}

						// merge, with and without an explicitly supplied comparison function.

						template <class _InputIter1, class _InputIter2, class _OutputIter>
							_OutputIter merge(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result);

						template <class _InputIter1, class _InputIter2, class _OutputIter,
						class _Compare>
							_OutputIter merge(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result, _Compare __comp);


						// inplace_merge and its auxiliary functions. 


						template <class _BidirectionalIter>
							void inplace_merge(_BidirectionalIter __first,
							_BidirectionalIter __middle,
							_BidirectionalIter __last) ;

						template <class _BidirectionalIter, class _Compare>
							void inplace_merge(_BidirectionalIter __first,
							_BidirectionalIter __middle,
							_BidirectionalIter __last, _Compare __comp);

						// Set algorithms: includes, set_union, set_intersection, set_difference,
						// set_symmetric_difference.	All of these algorithms have the precondition
						// that their input ranges are sorted and the postcondition that their output
						// ranges are sorted.

						template <class _InputIter1, class _InputIter2>
							bool includes(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2);

						template <class _InputIter1, class _InputIter2, class _Compare>
							bool includes(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2, _Compare __comp);

						template <class _InputIter1, class _InputIter2, class _OutputIter>
							_OutputIter set_union(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result);

						template <class _InputIter1, class _InputIter2, class _OutputIter,
						class _Compare>
							_OutputIter set_union(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result, _Compare __comp);

						template <class _InputIter1, class _InputIter2, class _OutputIter>
							_OutputIter set_intersection(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result);

						template <class _InputIter1, class _InputIter2, class _OutputIter,
						class _Compare>
							_OutputIter set_intersection(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result, _Compare __comp);



						template <class _InputIter1, class _InputIter2, class _OutputIter>
							_OutputIter set_difference(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result);

						template <class _InputIter1, class _InputIter2, class _OutputIter, 
						class _Compare>
							_OutputIter set_difference(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2, 
							_OutputIter __result, _Compare __comp);

						template <class _InputIter1, class _InputIter2, class _OutputIter>
							_OutputIter 
							set_symmetric_difference(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result);


						template <class _InputIter1, class _InputIter2, class _OutputIter,
						class _Compare>
							_OutputIter 
							set_symmetric_difference(_InputIter1 __first1, _InputIter1 __last1,
							_InputIter2 __first2, _InputIter2 __last2,
							_OutputIter __result,
							_Compare __comp);


						// min_element and max_element, with and without an explicitly supplied
						// comparison function.

						template <class _ForwardIter>
							_ForwardIter max_element(_ForwardIter __first, _ForwardIter __last);
						template <class _ForwardIter, class _Compare>
							_ForwardIter max_element(_ForwardIter __first, _ForwardIter __last,
							_Compare __comp);

						template <class _ForwardIter>
							_ForwardIter min_element(_ForwardIter __first, _ForwardIter __last);

						template <class _ForwardIter, class _Compare>
							_ForwardIter min_element(_ForwardIter __first, _ForwardIter __last,
							_Compare __comp);

						// next_permutation and prev_permutation, with and without an explicitly 
						// supplied comparison function.

						template <class _BidirectionalIter>
							bool next_permutation(_BidirectionalIter __first, _BidirectionalIter __last);

						template <class _BidirectionalIter, class _Compare>
							bool next_permutation(_BidirectionalIter __first, _BidirectionalIter __last,
							_Compare __comp);


						template <class _BidirectionalIter>
							bool prev_permutation(_BidirectionalIter __first, _BidirectionalIter __last);


						template <class _BidirectionalIter, class _Compare>
							bool prev_permutation(_BidirectionalIter __first, _BidirectionalIter __last,
							_Compare __comp);

# ifndef _STLP_NO_EXTENSIONS

						// is_heap, a predicate testing whether or not a range is
						// a heap.	This function is an extension, not part of the C++
						// standard.

						template <class _RandomAccessIter>
							bool is_heap(_RandomAccessIter __first, _RandomAccessIter __last);

						template <class _RandomAccessIter, class _StrictWeakOrdering>
							bool is_heap(_RandomAccessIter __first, _RandomAccessIter __last,
							_StrictWeakOrdering __comp);


						// is_sorted, a predicated testing whether a range is sorted in
						// nondescending order.	This is an extension, not part of the C++
						// standard.
						template <class _ForwardIter, class _StrictWeakOrdering>
							bool __is_sorted(_ForwardIter __first, _ForwardIter __last,
							_StrictWeakOrdering __comp);

						template <class _ForwardIter>
							inline bool is_sorted(_ForwardIter __first, _ForwardIter __last) {
								return __is_sorted(__first, __last, __less(_STLP_VALUE_TYPE(__first, _ForwardIter)));
							}

							template <class _ForwardIter, class _StrictWeakOrdering>
								inline bool is_sorted(_ForwardIter __first, _ForwardIter __last,
								_StrictWeakOrdering __comp) {
									return __is_sorted(__first, __last, __comp);
								}
# endif

// Local Variables:
// mode:C++
// End:
*/
}
#endif //NALGOBASE_H__
