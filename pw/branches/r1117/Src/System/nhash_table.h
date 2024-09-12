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

#pragma once

#include "nvector.h"
#include "nalgobase.h"
#include "npair.h"

namespace nstl
{
/*
# ifndef _STLP_INTERNAL_VECTOR_H
#	include <stl/_vector.h>
# endif

# ifndef _STLP_INTERNAL_ITERATOR_H
#	include <stl/_iterator.h>
# endif

# ifndef _STLP_INTERNAL_FUNCTION_H
#	include <stl/_function_base.h>
# endif

# ifndef _STLP_INTERNAL_ALGOBASE_H
#	include <stl/_algobase.h>
# endif

# ifndef _STLP_HASH_FUN_H
#	include <stl/_hash_fun.h>
# endif
*/
// Hashtable class, used to implement the hashed associative containers
// hash_set, hash_map, hash_multiset, and hash_multimap.

//#ifdef _STLP_DEBUG
//#	define hashtable __WORKAROUND_DBG_RENAME(hashtable)
//#endif

template <class _Val>
struct _Hashtable_node
{
	typedef _Hashtable_node<_Val> _Self;
	_Self* _M_next;
	_Val _M_val;

	_Hashtable_node() {}
	_Hashtable_node( const _Val &a ) : _M_val(a) {}
private:
	_Hashtable_node<_Val> &operator=( const _Hashtable_node<_Val> & ) {}
//	__TRIVIAL_STUFF(_Hashtable_node)
};	

// some compilers require the names of template parameters to be the same
template <class _Val, class _Key, class _HF>
class hashtable;

/*template <class _Val, class _Key, class _HF>
struct _Hashtable_iterator
{
};
*/

template <class _Val, class _Key, class _HF, class _Node, class TRes>
struct _Ht_it// : public _Hashtable_iterator< _Val, _Key,_HF>
{
	typedef hashtable<_Val,_Key,_HF> _Hashtable;
	//typedef _Hashtable_node<_Val> _Node;

	_Node* _M_cur;
	const _Hashtable* _M_ht;

//	_Hashtable_iterator(_Node* __n, _Hashtable* __tab) 
		//: _M_cur(__n), _M_ht(__tab) {}
		//_Hashtable_iterator() {}

		_Node* _M_skip_to_next()
		{
			uint __bucket = _M_ht->_M_bkt_num(_M_cur->_M_val);
			uint __h_sz;
			__h_sz = this->_M_ht->bucket_count();

			_Node* __i=0;
			while (__i==0 && ++__bucket < __h_sz)
				__i = (_Node*)_M_ht->_M_buckets[__bucket];
			return __i;
		}
	
	//typedef _Hashtable_iterator<_Val,_Key,_HF> _Base;

	//	typedef _Ht_iterator<_Val, _Nonconst_traits<_Val>,_Key,_HF> iterator;
	//	typedef _Ht_iterator<_Val, _Const_traits<_Val>,_Key,_HF> const_iterator;
	typedef _Ht_it<_Val, _Key,_HF, _Node, TRes> _Self;

	//typedef hashtable<_Val,_Key,_HF> _Hashtable;
	//typedef _Hashtable_node<_Val> _Node;

	//typedef _Val value_type;
//	typedef forward_iterator_tag iterator_category;
 // typedef ptrdiff_t difference_type;
//	typedef uint int;
	//typedef typename _Traits::reference reference;
	//typedef typename _Traits::pointer	 pointer;

	_Ht_it(_Node* _p, const _Hashtable* _t) : _M_cur(_p), _M_ht(_t) {}
	_Ht_it() {}
	template<class TN1, class TR1>
		_Ht_it( const _Ht_it<_Val,_Key,_HF, TN1, TR1> &a ) : _M_cur(a._M_cur), _M_ht(a._M_ht) { }
//	_Ht_it(const _Ht_it<_Val,_Key,_HF>& __it) : 
 //	 _Hashtable_iterator<_Val,_Key,_HF>(__it) {}

	TRes& operator*() const { 
			return this->_M_cur->_M_val; 
	}
	TRes* operator->() const { return &_M_cur->_M_val; }
	//_STLP_DEFINE_ARROW_OPERATOR

	_Self& operator++() {
		_Node* __n = this->_M_cur->_M_next;
		this->_M_cur =	(__n !=0 ? __n : this->_M_skip_to_next());
		return *this;
	}
	inline	_Self operator++(int) {
		 _Self __tmp = *this;
		++*this;
		return __tmp;
	}
};

template <class _Val, class _Key, class _HF, class TN1, class TR1, class TN2, class TR2>
inline bool 
operator==(const _Ht_it<_Val, _Key,_HF,TN1,TR1>& __x, 
		 const _Ht_it<_Val,_Key,_HF, TN2, TR2>& __y) { 
	return __x._M_cur == __y._M_cur; 
}

template <class _Val, class _Key, class _HF, class TN1, class TR1, class TN2, class TR2>
inline bool 
operator!=(const _Ht_it<_Val,_Key,_HF,TN1,TR1>& __x, 
		 const _Ht_it<_Val,_Key,_HF, TN2, TR2>& __y) { 
	return __x._M_cur != __y._M_cur; 
}

		 /*
# ifdef _STLP_USE_OLD_HP_ITERATOR_QUERIES
template <class _Val, class _Traits, class _Key, class _HF>
inline _Val* value_type(const _Ht_iterator<_Val, _Traits,_Key,_HF>&) { return (_Val*) 0; }
template <class _Val, class _Traits, class _Key, class _HF>
inline forward_iterator_tag iterator_category(const _Ht_iterator<_Val, _Traits,_Key,_HF>&) { return forward_iterator_tag(); }
template <class _Val, class _Traits, class _Key, class _HF>
inline ptrdiff_t* distance_type(const _Ht_iterator<_Val,_Traits,_Key,_HF>&) { return (ptrdiff_t*) 0; }
#endif
*/

#define __stl_num_primes	30
template <class _Tp>
class _Stl_prime {
public:
	static const uint _M_list[__stl_num_primes];
};
template <class _Tp>
const uint _Stl_prime<_Tp>::_M_list[__stl_num_primes] = 
{ 
13ul, 29ul,
53ul,				 97ul,				 193ul,			 389ul,			 769ul,			
1543ul,			 3079ul,			 6151ul,			12289ul,		 24593ul,		
49157ul,			98317ul,			196613ul,		393241ul,		786433ul,	 
1572869ul,		3145739ul,		6291469ul,	 12582917ul,	25165843ul, 
50331653ul,	 100663319ul,	201326611ul, 402653189ul, 805306457ul,
1610612741ul, 3221225473ul, 4294967291ul	
};


typedef _Stl_prime<bool> _Stl_prime_type;


// Hashtables handle allocators a bit differently than other containers
//	do.	If we're using standard-conforming allocators, then a hashtable
//	unconditionally has a member variable to hold its allocator, even if
//	it so happens that all instances of the allocator type are identical.
// This is because, for hashtables, this extra storage is negligible.	
//	Additionally, a base class wouldn't serve any other purposes; it 
//	wouldn't, for example, simplify the exception-handling code.
template <class _Val, class _Key, class _HF>
class hashtable {
	typedef hashtable<_Val, _Key, _HF> _Self;
	static inline const _Key& _M_get_key( const _Val &a ) { return a.first; }
public:
	typedef _Key key_type;
	typedef _Val value_type;
	typedef _HF hasher;
	//typedef _EqK key_equal;

	//typedef uint						int;
//	typedef ptrdiff_t				 difference_type;
	typedef value_type*			 pointer;
	typedef const value_type* const_pointer;
	typedef value_type&			 reference;
	typedef const value_type& const_reference;
//	typedef forward_iterator_tag _Iterator_category;

	hasher hash_funct() const { return _M_hash; }

public:
	typedef _Hashtable_node<_Val> _Node;

private:
	//_STLP_FORCE_ALLOCATORS(_Val, _All)
	//typedef typename _Alloc_traits<_Node, _All>::allocator_type _M_node_allocator_type;
	//typedef typename _Alloc_traits<void*, _All>::allocator_type _M_node_ptr_allocator_type;
	typedef vector<_Node*> _BucketVector;
public:
//	typedef typename _Alloc_traits<_Val,_All>::allocator_type allocator_type;
//	allocator_type get_allocator() const { 
		//return _STLP_CONVERT_ALLOCATOR((const _M_node_allocator_type&)_M_num_elements, _Val); 
	//}
private:
	hasher								_M_hash;
	//_ExK									_M_get_key;
	_BucketVector				 _M_buckets;
	int _M_num_elements;
	int nInitialBucketCount;
	//_STLP_alloc_proxy<int, _Node, _M_node_allocator_type>	_M_num_elements;
	const _Node* _M_get_bucket(uint __n) const { return _M_buckets[__n]; }

public:
	//template <class _Val, class _Key, class _HF, class _Node, class TRes>
	//struct _Ht_it// : public _Hashtable_iterator< _Val, _Key,_HF>
	//	;
	typedef _Ht_it<_Val,_Key,_HF,_Node,_Val> iterator;
	typedef _Ht_it<_Val,_Key,_HF,const _Node,const _Val> const_iterator;
	//typedef _Const_traits<_Val> __const_val_traits;
	//typedef _Nonconst_traits<_Val> __nonconst_val_traits;
	//typedef _Ht_iterator<_Val, __const_val_traits,_Key,_HF,_ExK,_EqK, _All> const_iterator;
	//typedef _Ht_iterator<_Val, __nonconst_val_traits,_Key,_HF> iterator;
	
	#ifdef WIN32
	  friend iterator;
	  friend const_iterator;
	#else
	  friend class _Ht_it<_Val,_Key,_HF,_Node,_Val>;
	  friend class _Ht_it<_Val,_Key,_HF,const _Node,const _Val>;
  #endif	  
	
	
	//friend struct _Hashtable_iterator<_Val,_Key,_HF>;
	//friend struct _Ht_iterator<_Val, _Nonconst_traits<_Val>,_Key,_HF>;
	//friend struct _Ht_iterator<_Val, _Const_traits<_Val>,_Key,_HF,_ExK,_EqK, _All>;

public:
	hashtable(int __n, const _HF&	__hf)
		:
			_M_hash(__hf),
			_M_num_elements(0)
	{
		_M_initialize_buckets(__n);
	}

	hashtable(const _Self& __ht)
		:
			_M_hash(__ht._M_hash),
			_M_num_elements(0)
	{
		_M_copy_from(__ht);
	}

	_Self& operator= (const _Self& __ht)
	{
		if (&__ht != this) {
			clear();
			_M_hash = __ht._M_hash;
			_M_copy_from(__ht);
		}
		return *this;
	}

	~hashtable() { clear(); }

	int size() const { return _M_num_elements; }
//	int max_size() const { return int(-1); }
	bool empty() const { return size() == 0; }

	void swap(_Self& __ht)
	{
		nstl::swap(_M_hash, __ht._M_hash);
		_M_buckets.swap(__ht._M_buckets);
		nstl::swap(_M_num_elements, __ht._M_num_elements);
	}

	iterator begin()
	{ 
		for (int __n = 0; __n < _M_buckets.size(); ++__n)
			if (_M_buckets[__n])
				return iterator(_M_buckets[__n], this);
		return end();
	}

	iterator end() { return iterator((_Node*)0, this); }

	const_iterator begin() const
	{
		for (int __n = 0; __n < _M_buckets.size(); ++__n)
			if (_M_buckets[__n])
				return const_iterator(_M_buckets[__n], this);
		return end();
	}

	const_iterator end() const { return const_iterator((_Node*)0, this); }

	static bool inline _M_equal (const hashtable<_Val, _Key, _HF>&,
			const hashtable<_Val, _Key, _HF>&);

public:

	int bucket_count() const { return _M_buckets.size(); }

	//int max_bucket_count() const
	 // { return _Stl_prime_type::_M_list[(int)__stl_num_primes - 1]; } 

	int elems_in_bucket(int __bucket) const
	{
		int __result = 0;
		for (_Node* __cur = _M_buckets[__bucket]; __cur; __cur = __cur->_M_next)
			__result += 1;
		return __result;
	}

	pair<iterator, bool> insert_unique(const value_type& __obj)
	{
		resize(_M_num_elements + 1);
		return insert_unique_noresize(__obj);
	}

	iterator insert_equal(const value_type& __obj)
	{
		resize(_M_num_elements + 1);
		return insert_equal_noresize(__obj);
	}

	pair<iterator, bool> insert_unique_noresize(const value_type& __obj)
	{
		const int __n = _M_bkt_num(__obj);
		_Node* __first = _M_buckets[__n];

		for (_Node* __cur = __first; __cur; __cur = __cur->_M_next) 
			if ((_M_get_key(__cur->_M_val) ==	_M_get_key(__obj)))
				return pair<iterator, bool>(iterator(__cur, this), false);

		_Node* __tmp = _M_new_node(__obj);
		__tmp->_M_next = __first;
		_M_buckets[__n] = __tmp;
		++_M_num_elements;
		return pair<iterator, bool>(iterator(__tmp, this), true);
	}
	iterator insert_equal_noresize(const value_type& __obj)
	{
		const int __n = _M_bkt_num(__obj);
		_Node* __first = _M_buckets[__n];

		for (_Node* __cur = __first; __cur; __cur = __cur->_M_next) 
			if ((_M_get_key(__cur->_M_val) == _M_get_key(__obj))) {
				_Node* __tmp = _M_new_node(__obj);
				__tmp->_M_next = __cur->_M_next;
				__cur->_M_next = __tmp;
				++_M_num_elements;
				return iterator(__tmp, this);
			}

			_Node* __tmp = _M_new_node(__obj);
			__tmp->_M_next = __first;
			_M_buckets[__n] = __tmp;
			++_M_num_elements;
			return iterator(__tmp, this);
	}
 
	template <class _InputIterator>
	void insert_unique(_InputIterator __f, _InputIterator __l)
	{
		for ( ; __f != __l; ++__f)
			insert_unique(*__f);
	}

	template <class _InputIterator>
	void insert_equal(_InputIterator __f, _InputIterator __l)
	{
		for ( ; __f != __l; ++__f)
			insert_equal(*__f);
	}


	reference find_or_insert(const value_type& __obj)
	{
		_Node* __first = _M_find(_M_get_key(__obj));
		if (__first)
			return __first->_M_val;
		else
			return _M_insert(__obj);
	}

private:
	template <class _KT> 
	 _Node* _M_find(const _KT& __key) const
	{
		int __n = (int)( ((unsigned int)_M_hash(__key)) % _M_buckets.size() );
		_Node* __first;
		for ( __first = _M_buckets[__n];
					__first && !(_M_get_key(__first->_M_val) ==	__key);
					__first = __first->_M_next)
			{}
		return __first;
	} 

public:
	template <class _KT> 
	iterator find(const _KT& __key) 
	{
		return iterator(_M_find(__key), this);
	} 

	template <class _KT> 
	const_iterator find(const _KT& __key) const
	{
		return const_iterator(_M_find(__key), this);
	} 

	int count(const key_type& __key) const
	{
		const int __n = _M_bkt_num_key(__key);
		int __result = 0;

		for (const _Node* __cur = _M_buckets[__n]; __cur; __cur = __cur->_M_next)
			if ((_M_get_key(__cur->_M_val) ==	__key))
				++__result;
		return __result;
	}

	pair<iterator, iterator> 
	equal_range(const key_type& __key)
	{
		typedef pair<iterator, iterator> _Pii;
		const int __n = _M_bkt_num_key(__key);

		for (_Node* __first = _M_buckets[__n]; __first; __first = __first->_M_next)
			if ((_M_get_key(__first->_M_val) == __key)) {
				for (_Node* __cur = __first->_M_next; __cur; __cur = __cur->_M_next)
					if (!(_M_get_key(__cur->_M_val) == __key))
						return _Pii(iterator(__first, this), iterator(__cur, this));
				for (int __m = __n + 1; __m < _M_buckets.size(); ++__m)
					if (_M_buckets[__m])
						return _Pii(iterator(__first, this),
						iterator(_M_buckets[__m], this));
				return _Pii(iterator(__first, this), end());
			}
			return _Pii(end(), end());
	}

	pair<const_iterator, const_iterator> 
	equal_range(const key_type& __key) const
	{
		typedef pair<const_iterator, const_iterator> _Pii;
		const int __n = _M_bkt_num_key(__key);

		for (const _Node* __first = _M_buckets[__n] ;
			__first; 
			__first = __first->_M_next) {
				if ((_M_get_key(__first->_M_val) == __key)) {
					for (const _Node* __cur = __first->_M_next;
						__cur;
						__cur = __cur->_M_next)
						if (!(_M_get_key(__cur->_M_val) == __key))
							return _Pii(const_iterator(__first, this),
							const_iterator(__cur, this));
					for (int __m = __n + 1; __m < _M_buckets.size(); ++__m)
						if (_M_buckets[__m])
							return _Pii(const_iterator(__first, this),
							const_iterator(_M_buckets[__m], this));
					return _Pii(const_iterator(__first, this), end());
				}
			}
			return _Pii(end(), end());
	}

	int erase(const key_type& __key)
	{
		const int __n = _M_bkt_num_key(__key);
		_Node* __first = _M_buckets[__n];
		int __erased = 0;

		if (__first) {
			_Node* __cur = __first;
			_Node* __next = __cur->_M_next;
			while (__next) {
				if ((_M_get_key(__next->_M_val) == __key)) {
					__cur->_M_next = __next->_M_next;
					_M_delete_node(__next);
					__next = __cur->_M_next;
					++__erased;
					--_M_num_elements;
				}
				else {
					__cur = __next;
					__next = __cur->_M_next;
				}
			}
			if ((_M_get_key(__first->_M_val) == __key)) {
				_M_buckets[__n] = __first->_M_next;
				_M_delete_node(__first);
				++__erased;
				--_M_num_elements;
			}
		}
		return __erased;
	}
	void erase(const const_iterator& __it) 
	{
		const _Node* __p = __it._M_cur;
		if (__p) {
			const int __n = _M_bkt_num(__p->_M_val);
			_Node* __cur = _M_buckets[__n];

			if (__cur == __p) {
				_M_buckets[__n] = __cur->_M_next;
				_M_delete_node(__cur);
				--_M_num_elements;
			}
			else {
				_Node* __next = __cur->_M_next;
				while (__next) {
					if (__next == __p) {
						__cur->_M_next = __next->_M_next;
						_M_delete_node(__next);
						--_M_num_elements;
						break;
					}
					else {
						__cur = __next;
						__next = __cur->_M_next;
					}
				}
			}
		}
	}

	//	void erase(const const_iterator& __first, const const_iterator __last) {
	//		 erase((const iterator&)__first, (const iterator&)__last);
	//	}
	void erase(const_iterator __first, const_iterator __last);
	void resize(int __num_elements_hint);
	void clear();

public:
	// this is for hash_map::operator[]
	reference _M_insert(const value_type& __obj)
	{
		resize(_M_num_elements + 1);

		int __n = _M_bkt_num(__obj);
		_Node* __first = _M_buckets[__n];

		_Node* __tmp = _M_new_node(__obj);
		__tmp->_M_next = __first;
		_M_buckets[__n] = __tmp;
		++_M_num_elements;
		return __tmp->_M_val;
	}

private:

	int _M_next_size(int __n) const;

	void _M_initialize_buckets(int __n)
	{
		nInitialBucketCount = __n;
		const int __n_buckets = _M_next_size(__n);
		_M_buckets.reserve(__n_buckets);
		_M_buckets.insert(_M_buckets.end(), __n_buckets, (_Node*) 0);
		_M_num_elements = 0;
	}

	int _M_bkt_num_key(const key_type& __key) const
	{
		return _M_bkt_num_key(__key, _M_buckets.size());
	}

	int _M_bkt_num(const value_type& __obj) const
	{
		return _M_bkt_num_key(_M_get_key(__obj));
	}

	int _M_bkt_num_key(const key_type& __key, uint __n) const
	{
		return (int)(((unsigned int) _M_hash(__key) ) % __n );
	}

	int _M_bkt_num(const value_type& __obj, uint __n) const
	{
		return _M_bkt_num_key(_M_get_key(__obj), __n);
	}

	_Node* _M_new_node(const value_type& _obj)
	{
		_Node* __n = new _Node(_obj);//_M_num_elements.allocate(1);
		__n->_M_next = 0;
		//_Construct(&__n->_M_val, __obj);
		return __n;
	}
	
	void _M_delete_node(_Node* __n)
	{
		delete __n;
		//_Destroy(&__n->_M_val);
		//_M_num_elements.deallocate(__n, 1);
	}

	void _M_erase_bucket(const int __n, _Node* __first, _Node* __last);
	void _M_erase_bucket(const int __n, _Node* __last);

	void _M_copy_from(const _Self& __ht);
};

template <class _Val, class _Key, class _HF>
inline bool operator==(const hashtable<_Val,_Key,_HF>& __ht1,
											 const hashtable<_Val,_Key,_HF>& __ht2)
{
	return hashtable<_Val,_Key,_HF>::_M_equal( __ht1, __ht2 );
}

template <class _Val, class _Key, class _HF>
inline void swap(hashtable<_Val, _Key, _HF>& __ht1,
								 hashtable<_Val, _Key, _HF>& __ht2) {
	__ht1.swap(__ht2);
}






// fbp: these defines are for outline methods definitions.
// needed to definitions to be portable. Should not be used in method bodies.

/*
# if defined ( _STLP_NESTED_TYPE_PARAM_BUG )
#	define __int__			 uint
#	define int					 uint
#	define value_type			_Val
#	define key_type				_Key
#	define _Node					 _Hashtable_node<_Val>
#	define __reference__			 _Val&

#	define __iterator__				_Ht_iterator<_Val, _Nonconst_traits<_Val>, _Key, _HF>
#	define __const_iterator__	_Ht_iterator<_Val, _Const_traits<_Val>, _Key, _HF>
# else
#	define __int__				_STLP_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF>::int
#	define __reference__				_STLP_TYPENAME_ON_RETURN_TYPE	hashtable<_Val, _Key, _HF>::reference
#	define __iterator__				 _STLP_TYPENAME_ON_RETURN_TYPE hashtable<_Val, _Key, _HF>::iterator
# endif
*/

/*
template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
					class _All>
_Hashtable_node<_Val>*
_Hashtable_iterator<_Val,_Key,_HF>::_M_skip_to_next() {
	uint __bucket = _M_ht->_M_bkt_num(_M_cur->_M_val);
	uint __h_sz;
	__h_sz = this->_M_ht->bucket_count();

	_Node* __i=0;
	while (__i==0 && ++__bucket < __h_sz)
		__i = (_Node*)_M_ht->_M_buckets[__bucket];
	return __i;
}
*/
template <class _Val, class _Key, class _HF>
int
hashtable<_Val,_Key,_HF>::_M_next_size(int __n) const		{ 
	const int* __first = (const int*)_Stl_prime_type::_M_list;
	const int* __last =	(const int*)_Stl_prime_type::_M_list + (int)__stl_num_primes;
	const int* pos = __lower_bound(__first, __last, __n, less(), (int*)0);
	return (pos == __last ? *(__last - 1) : *pos);
}

template <class _Val, class _Key, class _HF>
bool 
hashtable<_Val,_Key,_HF>::_M_equal(
							const hashtable<_Val,_Key,_HF>& __ht1,
							const hashtable<_Val,_Key,_HF>& __ht2)
{
	//	typedef _Hashtable_node<_Val> _Node;
	if (__ht1.bucket_count() != __ht2.bucket_count())
		return false;
	for (uint __n = 0; __n < __ht1.bucket_count(); ++__n) {
		const _Node* __cur1 = __ht1._M_get_bucket(__n);
		const _Node* __cur2 = __ht2._M_get_bucket(__n);
		for ( ; __cur1 && __cur2 && __cur1->_M_val == __cur2->_M_val;
					__cur1 = __cur1->_M_next, __cur2 = __cur2->_M_next)
			{}
		if (__cur1 || __cur2)
			return false;
	}
	return true;
}	


template <class _Val, class _Key, class _HF>
void hashtable<_Val,_Key,_HF>
	::erase(const_iterator _c_first, const_iterator _c_last)
{
	iterator& __first = (iterator&)_c_first;
	iterator& __last = (iterator&)_c_last;
	int __f_bucket = __first._M_cur ? 
		_M_bkt_num(__first._M_cur->_M_val) : _M_buckets.size();
	int __l_bucket = __last._M_cur ? 
		_M_bkt_num(__last._M_cur->_M_val) : _M_buckets.size();
	if (__first._M_cur == __last._M_cur)
		return;
	else if (__f_bucket == __l_bucket)
		_M_erase_bucket(__f_bucket, __first._M_cur, __last._M_cur);
	else {
		_M_erase_bucket(__f_bucket, __first._M_cur, 0);
		for (int __n = __f_bucket + 1; __n < __l_bucket; ++__n)
			_M_erase_bucket(__n, 0);
		if (__l_bucket != _M_buckets.size())
			_M_erase_bucket(__l_bucket, __last._M_cur);
	}
}

template <class _Val, class _Key, class _HF>
void hashtable<_Val,_Key,_HF>
	::resize(int __num_elements_hint)
{
	const int __old_n = _M_buckets.size();
	if (__num_elements_hint > __old_n) {
		const int __n = _M_next_size(__num_elements_hint);
		if (__n > __old_n) {
			_BucketVector __tmp(__n, (_Node*)(0));
				for (int __bucket = 0; __bucket < __old_n; ++__bucket) {
					_Node* __first = _M_buckets[__bucket];
					while (__first) {
						int __new_bucket = _M_bkt_num(__first->_M_val, __n);
						_M_buckets[__bucket] = __first->_M_next;
						__first->_M_next = (_Node*)__tmp[__new_bucket];
						__tmp[__new_bucket] = __first;
						__first = _M_buckets[__bucket];					
					}
				}
				_M_buckets.swap(__tmp);
		}
	}
}

template <class _Val, class _Key, class _HF>
void hashtable<_Val,_Key,_HF>
	::_M_erase_bucket(const int __n, _Node* __first, _Node* __last)
{
	_Node* __cur = _M_buckets[__n];
	if (__cur == __first)
		_M_erase_bucket(__n, __last);
	else {
		_Node* __next;
		for (__next = __cur->_M_next; 
				 __next != __first; 
				 __cur = __next, __next = __cur->_M_next)
			;
		while (__next != __last) {
			__cur->_M_next = __next->_M_next;
			_M_delete_node(__next);
			__next = __cur->_M_next;
			--_M_num_elements;
		}
	}
}

template <class _Val, class _Key, class _HF>
void hashtable<_Val,_Key,_HF>
	::_M_erase_bucket(const int __n, _Node* __last)
{
	_Node* __cur = _M_buckets[__n];
	while (__cur && __cur != __last) {
		_Node* __next = __cur->_M_next;
		_M_delete_node(__cur);
		__cur = __next;
		_M_buckets[__n] = __cur;
		--_M_num_elements;
	}
}

template <class _Val, class _Key, class _HF>
void hashtable<_Val,_Key,_HF>::clear()
{
	for (int __i = 0; __i < _M_buckets.size(); ++__i) {
		_Node* __cur = _M_buckets[__i];
		while (__cur != 0) {
			_Node* __next = __cur->_M_next;
			_M_delete_node(__cur);
			__cur = __next;
		}
		_M_buckets[__i] = 0;
	}

	const int __n_buckets = _M_next_size(nInitialBucketCount);
	if ( _M_buckets.size() != __n_buckets )
	{
		_M_buckets.resize( __n_buckets );
		//_M_buckets.clear();
		//_M_initialize_buckets( nInitialBucketCount );
	}

	_M_num_elements = 0;
}

		
template <class _Val, class _Key, class _HF>
void hashtable<_Val,_Key,_HF>
	::_M_copy_from(const hashtable<_Val,_Key,_HF>& __ht)
{
	nInitialBucketCount = 0;
	_M_buckets.clear();
	_M_buckets.reserve(__ht._M_buckets.size());
	_M_buckets.insert(_M_buckets.end(), __ht._M_buckets.size(), (_Node*) 0);
	for (int __i = 0; __i < __ht._M_buckets.size(); ++__i) {
		const _Node* __cur = (_Node*)__ht._M_buckets[__i];
		if (__cur) {
			_Node* __xcopy = _M_new_node(__cur->_M_val);
			_M_buckets[__i] = __xcopy;

			for (_Node* __next = __cur->_M_next; 
						__next; 
						__cur = __next, __next = __cur->_M_next) {
				__xcopy->_M_next = _M_new_node(__next->_M_val);
				__xcopy = __xcopy->_M_next;
			}
		}
	}
	_M_num_elements = __ht._M_num_elements;
}
/*
# undef __iterator__ 
# undef const_iterator
# undef __int__
# undef __reference__
# undef int			 
# undef value_type			
# undef key_type				
# undef _Node						
# undef hashtable
*/
# undef __stl_num_primes



}
