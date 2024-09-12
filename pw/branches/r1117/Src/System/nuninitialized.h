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

#ifndef NUNINITIALIZED_H__
#define NUNINITIALIZED_H__

//#include "ntype_traits.h"
#include "nalgobase.h"

//#ifdef WIN32
//  #include <new>
//#else
#if defined( NV_WIN_PLATFORM )
  #include "../MemoryLib/newdelete.h"
#endif

namespace nstl
{
	template <class _Tp>
		inline void _Destroy(_Tp* __pointer) {
			((void)(__pointer));
			__pointer->~_Tp();
		}

		template <class _T1, class _T2>
			inline void _Construct(_T1* __p, const _T2& __val) {
				new(__p) _T1(__val);
			}

			template <class _T1>
				inline void _Construct(_T1* __p) {
					new(__p) _T1;
				}

				template <class _ForwardIterator>
					inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
						for ( ; __first != __last; ++__first)
							nstl::_Destroy(&*__first);
					}

	template <class _T1, class _T2>
	inline void construct(_T1* __p, const _T2& __val) {_Construct(__p, __val); }
	template <class _T1>
	inline void construct(_T1* __p) { _Construct(__p); }

/*# ifndef _NSTL_CSTRING
#	include <cstring>
# endif

# ifndef _NSTL_INTERNAL_ALGOBASE_H
#	include <stl/_algobase.h>
# endif

# ifndef _NSTL_INTERNAL_CONSTRUCT_H
#	include <stl/_construct.h>
# endif
*/

//_NSTL_BEGIN_NAMESPACE

// uninitialized_copy

// Valid if copy construction is equivalent to assignment, and if the
//	destructor is trivial.

template <class _InputIter, class _ForwardIter>
inline _ForwardIter
uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result) {
	_ForwardIter __cur = __result;
	for ( ; __first != __last; ++__first, ++__cur)
		nstl::_Construct(&*__cur, *__first);
	return __cur;
}

// Valid if copy construction is equivalent to assignment, and if the
// destructor is trivial.
template <class _ForwardIter, class _Tp>
inline void uninitialized_fill(_ForwardIter __first, _ForwardIter __last,	const _Tp& __x) {
	_ForwardIter __cur = __first;
	for ( ; __cur != __last; ++__cur)
		_Construct(&*__cur, __x);
}

// Valid if copy construction is equivalent to assignment, and if the
//	destructor is trivial.
template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter 
uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x) {
	_ForwardIter __cur = __first;
	for ( ; __n > 0; --__n, ++__cur)
		nstl::_Construct(&*__cur, __x);
	return __cur;
}

template <class _ForwardIter, class _Size>
inline _ForwardIter 
uninitialized_fill_n(_ForwardIter __first, _Size __n) {
	_ForwardIter __cur = __first;
	for ( ; __n > 0; --__n, ++__cur)
		_Construct(&*__cur);
	return __cur;
}

// Extensions: __uninitialized_copy_copy, __uninitialized_copy_fill, 
// __uninitialized_fill_copy.

// __uninitialized_copy_copy
// Copies [first1, last1) into [result, result + (last1 - first1)), and
//	copies [first2, last2) into
//	[result, result + (last1 - first1) + (last2 - first2)).
/*
template <class _InputIter1, class _InputIter2, class _ForwardIter>
inline _ForwardIter
__uninitialized_copy_copy(_InputIter1 __first1, _InputIter1 __last1,
													_InputIter2 __first2, _InputIter2 __last2,
													_ForwardIter __result, __true_type)
{
	return __uninitialized_copy(__first2, __last2, 
															__uninitialized_copy(__first1, __last1, __result, __true_type()), __true_type());
}

template <class _InputIter1, class _InputIter2, class _ForwardIter>
inline _ForwardIter
__uninitialized_copy_copy(_InputIter1 __first1, _InputIter1 __last1,
													_InputIter2 __first2, _InputIter2 __last2,
													_ForwardIter __result, __false_type)
{
	_ForwardIter __mid = __uninitialized_copy(__first1, __last1, __result, NSTL_IS_POD_ITER(__result, _ForwardIter));
	return __uninitialized_copy(__first2, __last2, __mid , NSTL_IS_POD_ITER(__result, _ForwardIter));
}

// __uninitialized_fill_copy
// Fills [result, mid) with x, and copies [first, last) into
//	[mid, mid + (last - first)).
template <class _ForwardIter, class _Tp, class _InputIter>
inline _ForwardIter 
__uninitialized_fill_copy(_ForwardIter __result, _ForwardIter __mid, const _Tp& __x,
													_InputIter __first, _InputIter __last)
{
	typedef typename __type_traits<_Tp>::is_POD_type _I_POD;
	__uninitialized_fill(__result, __mid, __x, _I_POD());
	return __uninitialized_copy(__first, __last, __mid, _I_POD());
}

// __uninitialized_copy_fill
// Copies [first1, last1) into [first2, first2 + (last1 - first1)), and
//	fills [first2 + (last1 - first1), last2) with x.
template <class _InputIter, class _ForwardIter, class _Tp>
inline void
__uninitialized_copy_fill(_InputIter __first1, _InputIter __last1,
													_ForwardIter __first2, _ForwardIter __last2,
													const _Tp& __x)
{
	typedef typename __type_traits<_Tp>::is_POD_type _I_POD;
	_ForwardIter __mid2 = __uninitialized_copy(__first1, __last1, __first2, _I_POD());
	__uninitialized_fill(__mid2, __last2, __x, _I_POD());
}
*/

template <> inline void _Destroy<int>( int*) {}
template <> inline void _Construct( int* __p, const int& __val ) { *__p = __val; }
template <> inline void _Construct( int* __p ) {((void)(__p));}
template <> inline void _Destroy( int *__first, int*__last ) {((void)(__first));((void)(__last));}
template <> inline int *uninitialized_copy( int *__first, int *__last, int *__result ) 
{
	while ( __first != __last )
		*__result++ = *__first++;
	return __result;
}
template <> inline int *uninitialized_fill_n( int *__first, int __n, const int& __x) {
	while ( __n-- > 0 )
		*__first++ = __x;
	return __first;
}

template <> inline void _Destroy<float>( float*) {}
template <> inline void _Construct( float* __p, const float& __val ) { *__p = __val; }
template <> inline void _Construct( float* __p ) {((void)(__p));}
template <> inline void _Destroy( float *__first, float*__last ) {((void)(__first));((void)(__last));}
template <> inline float *uninitialized_copy( float *__first, float *__last, float *__result ) 
{
	while ( __first != __last )
		*__result++ = *__first++;
	return __result;
}
template <> inline float *uninitialized_fill_n( float *__first, float __n, const float& __x) {
	while ( __n-- > 0 )
		*__first++ = __x;
	return __first;
}

}

#endif //NUNINITIALIZED_H__
