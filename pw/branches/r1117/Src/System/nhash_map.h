#ifndef _NHASH_MAP_H_
#define _NHASH_MAP_H_

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

#include "nhash_table.h"
#include "nhash_fun.h"
#include "nhash_fun2.h"
#include "helpdebugmacroses.h"

namespace nstl
{

//# define	hash_map			__WORKAROUND_RENAME(hash_map)
//# define	hash_multimap __WORKAROUND_RENAME(hash_multimap)

//#	define _STLP_KEY_PAIR pair< const _Key, _Tp >
/*
#	define _STLP_HASHTABLE hashtable \
			< pair < const _Key, _Tp >, _Key, _HashFcn, \
			_STLP_SELECT1ST( _STLP_KEY_PAIR,	_Key ), _EqualKey, _Alloc >
*/

template <class _Key, class _Tp, class _HashFcn = hash<_Key> >
class hash_map
{
private:
	typedef hashtable<pair < const _Key, _Tp >, _Key, _HashFcn> _Ht;
	typedef hash_map<_Key, _Tp, _HashFcn> _Self;
public:
	typedef typename _Ht::key_type key_type;
	//typedef _Tp data_type;
	//typedef _Tp mapped_type;
	//typedef typename _Ht::value_type _value_type;
	typedef typename _Ht::value_type value_type;
	typedef typename _Ht::hasher hasher;
	//typedef typename _Ht::key_equal key_equal;
	
//	typedef typename _Ht::int int;
//	typedef typename _Ht::difference_type difference_type;
	typedef typename _Ht::pointer pointer;
	typedef typename _Ht::const_pointer const_pointer;
	typedef typename _Ht::reference reference;
	typedef typename _Ht::const_reference const_reference;

	typedef typename _Ht::iterator iterator;
	typedef typename _Ht::const_iterator const_iterator;

//	typedef typename _Ht::allocator_type allocator_type;

	//hasher hash_funct() const { return _M_ht.hash_funct(); }
	//key_equal key_eq() const { return _M_ht.key_eq(); }
	//allocator_type get_allocator() const { return _M_ht.get_allocator(); }

private:
	_Ht _M_ht;
public:
	LOOK_FUNC

#ifdef _NSTL_HELP_DEBUG
	#define INST_LOOK_AT InstantiateLookAt();
	_Tp& LookAt( _Key &key )
	{
		return (*this)[key];
	}

	_Tp& LookAt( _Key *pKey )
	{
		return (*this)[*pKey];
	}

	void InstantiateLookAt()
	{
		if ( false )
		{
			BYTE cDumb;
			LookAt( reinterpret_cast<_Key&>( cDumb ) );
			LookAt( reinterpret_cast<_Key*>( 0 ) );
		}
	}
#else
	#define INST_LOOK_AT
#endif // _NSTL_HELP_DEBUG

	hash_map() : _M_ht(10, hasher()) { LOOK_INIT( *this ); INST_LOOK_AT }
	explicit hash_map(int __n)
		: _M_ht(__n, hasher()) { LOOK_INIT( *this ); INST_LOOK_AT }
	hash_map(int __n, const hasher& __hf)
		: _M_ht(__n, __hf) { LOOK_INIT( *this ); INST_LOOK_AT }

	template <class _InputIterator>
	hash_map(_InputIterator __f, _InputIterator __l)
		: _M_ht(10, hasher())
		{ _M_ht.insert_unique(__f, __l); LOOK_INIT( *this ); INST_LOOK_AT }
	template <class _InputIterator>
	hash_map(_InputIterator __f, _InputIterator __l, int __n)
		: _M_ht(__n, hasher())
		{ _M_ht.insert_unique(__f, __l); LOOK_INIT( *this ); INST_LOOK_AT }
	template <class _InputIterator>
	hash_map(_InputIterator __f, _InputIterator __l, int __n,
					 const hasher& __hf)
		: _M_ht(__n, __hf)
		{ _M_ht.insert_unique(__f, __l); LOOK_INIT( *this ); INST_LOOK_AT }

public:
	int size() const { return _M_ht.size(); }
	//int max_size() const { return _M_ht.max_size(); }
	bool empty() const { return _M_ht.empty(); }
	void swap(_Self& __hs) { _M_ht.swap(__hs._M_ht); }
	iterator begin() { return _M_ht.begin(); }
	iterator end() { return _M_ht.end(); }
	const_iterator begin() const { return _M_ht.begin(); }
	const_iterator end() const { return _M_ht.end(); }

public:
	pair<iterator,bool> insert(const value_type& __obj)
		{ return _M_ht.insert_unique(__obj); }
	template <class _InputIterator>
	void insert(_InputIterator __f, _InputIterator __l)
		{ _M_ht.insert_unique(__f,__l); }
	pair<iterator,bool> insert_noresize(const value_type& __obj)
		{ return _M_ht.insert_unique_noresize(__obj); }		

  // additional usability methods
  iterator insert(const key_type& key)
  {
    this->operator[](key) = _Tp();
    return find(key);
  }

  bool insertUnique(const key_type& __key, const _Tp& __obj)
  {
    iterator it = find(__key);
    if (it == end())
    {
      _M_ht._M_insert(value_type(__key, __obj));
      return true;
    }
    return false;
  }

	template<class _KT>
	iterator find(const _KT& __key) { return _M_ht.find(__key); }

	template<class _KT>
	const_iterator find(const _KT& __key) const { return _M_ht.find(__key); }

	_Tp& operator[](const key_type& __key) {
		iterator __it = _M_ht.find(__key);
		iterator __itEnd = _M_ht.end();
		return (__it == __itEnd ? 
			_M_ht._M_insert(value_type(__key, _Tp())).second : 
			(*__it).second );
	}

  _Tp const& operator[](const key_type& __key) const {
    const_iterator __it = _M_ht.find(__key);
    const_iterator __itEnd = _M_ht.end();
    NI_VERIFY(__it != __itEnd, "Attempt to fetch unexistent element", return (*(_M_ht.begin())).second;);
    return (*__it).second;
  }

	int count(const key_type& __key) const { return _M_ht.count(__key); }
	
	pair<iterator, iterator> equal_range(const key_type& __key)
		{ return _M_ht.equal_range(__key); }
	pair<const_iterator, const_iterator>
	equal_range(const key_type& __key) const
		{ return _M_ht.equal_range(__key); }

	int erase(const key_type& __key) { return _M_ht.erase(__key); }
	
  iterator erase(iterator __it) {
    iterator __next = __it;
    ++__next;
    _M_ht.erase(__it);
    return __next;
  }

	void erase(iterator __f, iterator __l) { _M_ht.erase(__f, __l); }
	void clear() { _M_ht.clear(); }

	void resize(int __hint) { _M_ht.resize(__hint); }
	int bucket_count() const { return _M_ht.bucket_count(); }
	void set_bucket_count( int _n ) { _M_ht.resize( _n ); }
	//int max_bucket_count() const { return _M_ht.max_bucket_count(); }
	//int elems_in_bucket(int __n) const
	//	{ return _M_ht.elems_in_bucket(__n); }
	static bool _M_equal (const _Self& __x, const _Self& __y) {
		return _Ht::_M_equal(__x._M_ht,__y._M_ht);
	}
};


template <class _Key, class _Tp, class _HashFcn>
inline bool 
operator==(const hash_map<_Key,_Tp,_HashFcn>& __hm1,
					 const hash_map<_Key,_Tp,_HashFcn>& __hm2)
{
	return hash_map<_Key,_Tp,_HashFcn>::_M_equal(__hm1, __hm2);
}

template <class _Key, class _Tp, class _HashFcn>
inline bool 
operator!=(const hash_map<_Key,_Tp,_HashFcn>& __hm1,
					 const hash_map<_Key,_Tp,_HashFcn>& __hm2)
{
	return !(__hm1==__hm2);
}


template <class _Key, class _Tp, class _HashFcn>
inline void	
swap(hash_map<_Key,_Tp,_HashFcn>& __hm1,
		 hash_map<_Key,_Tp,_HashFcn>& __hm2)
{
	__hm1.swap(__hm2);
}




// Specialization of insert_iterator so that it will work for hash_map
// and hash_multimap.
/*
#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION

template <class _Key, class _Tp, class _HashFn,	class _EqKey, class _Alloc>
class insert_iterator<hash_map<_Key, _Tp, _HashFn, _EqKey, _Alloc> > {
protected:
	typedef hash_map<_Key, _Tp, _HashFn, _EqKey, _Alloc> _Container;
	_Container* container;
public:
	typedef _Container					container_type;
	typedef output_iterator_tag iterator_category;
	typedef void								value_type;
	typedef void								difference_type;
	typedef void								pointer;
	typedef void								reference;

	insert_iterator(_Container& __x) : container(&__x) {}
	insert_iterator(_Container& __x, typename _Container::iterator)
		: container(&__x) {}
	insert_iterator<_Container>&
	operator=(const typename _Container::value_type& __val) { 
		container->insert(__val);
		return *this;
	}
	insert_iterator<_Container>& operator*() { return *this; }
	insert_iterator<_Container>& operator++() { return *this; }
	insert_iterator<_Container>& operator++(int) { return *this; }
};

template <class _Key, class _Tp, class _HashFn,	class _EqKey, class _Alloc>
class insert_iterator<hash_multimap<_Key, _Tp, _HashFn, _EqKey, _Alloc> > {
protected:
	typedef hash_multimap<_Key, _Tp, _HashFn, _EqKey, _Alloc> _Container;
	_Container* container;
	typename _Container::iterator iter;
public:
	typedef _Container					container_type;
	typedef output_iterator_tag iterator_category;
	typedef void								value_type;
	typedef void								difference_type;
	typedef void								pointer;
	typedef void								reference;

	insert_iterator(_Container& __x) : container(&__x) {}
	insert_iterator(_Container& __x, typename _Container::iterator)
		: container(&__x) {}
	insert_iterator<_Container>&
	operator=(const typename _Container::value_type& __val) { 
		container->insert(__val);
		return *this;
	}
	insert_iterator<_Container>& operator*() { return *this; }
	insert_iterator<_Container>& operator++() { return *this; }
	insert_iterator<_Container>& operator++(int) { return *this; }
};

#endif // _STLP_CLASS_PARTIAL_SPECIALIZATION 
*/


}

#endif

