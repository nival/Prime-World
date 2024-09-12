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
 *   You should not attempt to use it directly.
 */

#pragma once

#include "ntree.h"
#include "nalgobase.h"
#include "nvector.h"

//#define map __WORKAROUND_RENAME(map)
//#define multimap __WORKAROUND_RENAME(multimap)

namespace nstl
{

template <class _Key, class _Tp, class _Compare = less >
class map {
public:

// typedefs:

    typedef _Key                                    key_type;
    typedef _Tp                                  data_type;
    typedef _Tp                                  mapped_type;
    typedef pair<const _Key, _Tp> value_type;
    typedef _Compare                            key_compare;
        
    class value_compare/*
        : public binary_function<value_type, value_type, bool>*/ {
    friend class map<_Key,_Tp,_Compare/*,_Alloc*/>;
    protected :
        _Compare _M_comp;
        value_compare(_Compare __c) : _M_comp(__c) {}
    public:
        bool operator()(const value_type& __x, const value_type& __y) const {
            return _M_comp(__x.first, __y.first);
        }
    };

private:

    typedef _Rb_tree<key_type, value_type, 
                                     _Select1st<value_type>, key_compare/*, _Alloc*/> _Rep_type;
    _Rep_type _M_t; // red-black tree representing map
public:
    typedef typename _Rep_type::pointer pointer;
    typedef typename _Rep_type::const_pointer const_pointer;
    typedef typename _Rep_type::reference reference;
    typedef typename _Rep_type::const_reference const_reference;
    typedef typename _Rep_type::iterator iterator;
    typedef typename _Rep_type::const_iterator const_iterator;
//  typedef typename _Rep_type::reverse_iterator reverse_iterator;
//  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
//  typedef typename _Rep_type::size_type size_type;
    //typedef typename _Rep_type::difference_type difference_type;
    //typedef typename _Rep_type::allocator_type allocator_type;

    // allocation/deallocation

    map() : _M_t(_Compare()/*, allocator_type()*/) {}
    explicit map(const _Compare& __comp/*,
                             const allocator_type& __a = allocator_type()*/)
        : _M_t(__comp/*, __a*/) {}

    map(const value_type* __first, const value_type* __last)
        : _M_t(_Compare()/*, allocator_type()*/)
        { _M_t.insert_unique(__first, __last); }

    map(const value_type* __first,
            const value_type* __last, const _Compare& __comp/*,
            const allocator_type& __a = allocator_type()*/)
        : _M_t(__comp/*, __a*/) { _M_t.insert_unique(__first, __last); }

    map(const_iterator __first, const_iterator __last)
        : _M_t(_Compare()/*, allocator_type()*/) 
        { _M_t.insert_unique(__first, __last); }

    map(const_iterator __first, const_iterator __last, const _Compare& __comp/*,
            const allocator_type& __a = allocator_type()*/)
        : _M_t(__comp/*, __a*/) { _M_t.insert_unique(__first, __last); }

    map(const map<_Key,_Tp,_Compare/*,_Alloc*/>& __x) : _M_t(__x._M_t) {}
    map<_Key,_Tp,_Compare/*,_Alloc*/>&
    operator=(const map<_Key, _Tp, _Compare/*, _Alloc*/>& __x)
    {
        _M_t = __x._M_t;
        return *this; 
    }

    // accessors:

    key_compare key_comp() const { return _M_t.key_comp(); }
    value_compare value_comp() const { return value_compare(_M_t.key_comp()); }
    //allocator_type get_allocator() const { return _M_t.get_allocator(); }

    iterator begin() { return _M_t.begin(); }
    const_iterator begin() const { return _M_t.begin(); }
    iterator end() { return _M_t.end(); }
    const_iterator end() const { return _M_t.end(); }
//  reverse_iterator rbegin() { return _M_t.rbegin(); }
//  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
//  reverse_iterator rend() { return _M_t.rend(); }
//  const_reverse_iterator rend() const { return _M_t.rend(); }
    bool empty() const { return _M_t.empty(); }
    int size() const { return _M_t.size(); }
    int max_size() const { return _M_t.max_size(); }
    _Tp& operator[](const key_type& __k) {
        iterator __i = lower_bound(__k);
        // __i->first is greater than or equivalent to __k.
        if (__i == end() || key_comp()(__k, (*__i).first))
            __i = insert(__i, value_type(__k, _Tp() ));
        return (*__i).second;
    }
    void swap(map<_Key,_Tp,_Compare/*,_Alloc*/>& __x) { _M_t.swap(__x._M_t); }

    // insert/erase

    pair<iterator,bool> insert(const value_type& __x) 
        { return _M_t.insert_unique(__x); }
    iterator insert(iterator position, const value_type& __x)
        { return _M_t.insert_unique(position, __x); }
    void insert(const value_type* __first, const value_type* __last) {
        _M_t.insert_unique(__first, __last);
    }
    void insert(const_iterator __first, const_iterator __last) {
        _M_t.insert_unique(__first, __last);
    }

    iterator erase(iterator __position) {
      iterator __next = __position;
      ++__next;
      _M_t.erase(__position);
      return __next;
    }

    int erase(const key_type& __x) { return _M_t.erase(__x); }
    void erase(iterator __first, iterator __last)
        { _M_t.erase(__first, __last); }
    void clear() { _M_t.clear(); }

    // map operations:

    iterator find(const key_type& __x) { return _M_t.find(__x); }
    const_iterator find(const key_type& __x) const { return _M_t.find(__x); }
    int count(const key_type& __x) const { 
        return _M_t.find(__x) == _M_t.end() ? 0 : 1;
    }
    iterator lower_bound(const key_type& __x) {return _M_t.lower_bound(__x); }
    const_iterator lower_bound(const key_type& __x) const {
        return _M_t.lower_bound(__x); 
    }
    iterator upper_bound(const key_type& __x) {return _M_t.upper_bound(__x); }
    const_iterator upper_bound(const key_type& __x) const {
        return _M_t.upper_bound(__x); 
    }
    
    pair<iterator,iterator> equal_range(const key_type& __x) {
        return _M_t.equal_range(__x);
    }
    pair<const_iterator,const_iterator> equal_range(const key_type& __x) const {
        return _M_t.equal_range(__x);
    }
    
    // additional usability methods
    iterator insert(const _Key& key)
    {
        this->operator[](key) = _Tp();
        return find(key);
    }
    
};

template <class _Key, class _Tp, class _Compare = less >
class multimap
{
  typedef multimap<_Key, _Tp, _Compare> _Self;
public:

  // typedefs:

  typedef _Key                  key_type;
  typedef _Tp                   data_type;
  typedef _Tp                   mapped_type;
  typedef pair<const _Key, _Tp> value_type;
  typedef _Compare              key_compare;

  class value_compare : public binary_function<value_type, value_type, bool> {
    friend class multimap<_Key,_Tp,_Compare>;
  protected:
    //comp is a Standard name (23.3.2), do no make it STLport naming convention compliant.
    _Compare comp;
    value_compare(_Compare __c) : comp(__c) {}
  public:
    bool operator()(const value_type& __x, const value_type& __y) const
    { return comp(__x.first, __y.first); }
  };

public:
  //Following typedef have to be public for __move_traits specialization.
  typedef _Rb_tree<key_type, value_type, _Select1st<value_type>, key_compare> _Rep_type;

  typedef typename _Rep_type::pointer pointer;
  typedef typename _Rep_type::const_pointer const_pointer;
  typedef typename _Rep_type::reference reference;
  typedef typename _Rep_type::const_reference const_reference;
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  //typedef typename _Rep_type::reverse_iterator reverse_iterator;
  //typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef int size_type;
  //typedef typename _Rep_type::difference_type difference_type;
  //typedef typename _Rep_type::allocator_type allocator_type;

private:
  _Rep_type _M_t;  // red-black tree representing multimap

public:
  // allocation/deallocation
  multimap() : _M_t(_Compare()) { }
  explicit multimap(const _Compare& __comp)
    : _M_t(__comp) { }


  template <class _InputIterator>
  multimap(_InputIterator __first, _InputIterator __last)
    : _M_t(_Compare())
  { _M_t.insert_equal(__first, __last); }
  

  template <class _InputIterator>
  multimap(_InputIterator __first, _InputIterator __last,
    const _Compare& __comp)
    : _M_t(__comp) { _M_t.insert_equal(__first, __last); }

  multimap(const_iterator __first, const_iterator __last)
    : _M_t(_Compare())
  { _M_t.insert_equal(__first, __last); }
  multimap(const_iterator __first, const_iterator __last,
    const _Compare& __comp)
    : _M_t(__comp) { _M_t.insert_equal(__first, __last); }

  multimap(const _Self& __x) : _M_t(__x._M_t) {}


  _Self& operator=(const _Self& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  // accessors:

  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return value_compare(_M_t.key_comp()); }

  iterator begin() { return _M_t.begin(); }
  const_iterator begin() const { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator end() const { return _M_t.end(); }
  //reverse_iterator rbegin() { return _M_t.rbegin(); }
  //const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  //reverse_iterator rend() { return _M_t.rend(); }
  //const_reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  void swap(_Self& __x) { _M_t.swap(__x._M_t); }

  // insert/erase
  iterator insert(const value_type& __x) { return _M_t.insert_equal(__x); }
  iterator insert(iterator __pos, const value_type& __x) { return _M_t.insert_equal(__pos, __x); }

  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last)
  { _M_t.insert_equal(__first, __last); }

  void erase(iterator __pos) { _M_t.erase(__pos); }
  size_type erase(const key_type& __x) { return _M_t.erase(__x); }
  void erase(iterator __first, iterator __last) { _M_t.erase(__first, __last); }
  void clear() { _M_t.clear(); }

  // multimap operations:

  
    iterator find(const key_type& __x) { return _M_t.find(__x); }
  
    const_iterator find(const key_type& __x) const { return _M_t.find(__x); }
  
    size_type count(const key_type& __x) const { return _M_t.count(__x); }
  
    iterator lower_bound(const key_type& __x) { return _M_t.lower_bound(__x); }
  
    const_iterator lower_bound(const key_type& __x) const { return _M_t.lower_bound(__x); }
  
    iterator upper_bound(const key_type& __x) { return _M_t.upper_bound(__x); }
  
    const_iterator upper_bound(const key_type& __x) const { return _M_t.upper_bound(__x); }
  
    pair<iterator,iterator> equal_range(const key_type& __x)
  { return _M_t.equal_range(__x); }
  
    pair<const_iterator,const_iterator> equal_range(const key_type& __x) const
  { return _M_t.equal_range(__x); }
};

template<class _Key, class _Tp, class _Compare>
inline bool operator==(const map<_Key, _Tp, _Compare>& __x,
                                  const map<_Key, _Tp, _Compare>& __y) {
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template<class _Key, class _Tp, class _Compare>
inline bool operator==(const multimap<_Key, _Tp, _Compare>& __x,
                                  const multimap<_Key, _Tp, _Compare>& __y) {
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template<class _Key, class _Tp, class _Compare>
inline bool operator!=(const map<_Key, _Tp, _Compare>& __x,
                                  const map<_Key, _Tp, _Compare>& __y) {
  return !( __x == __y );
}

template<class _Key, class _Tp, class _Compare>
inline bool operator!=(const multimap<_Key, _Tp, _Compare>& __x,
                                  const multimap<_Key, _Tp, _Compare>& __y) {
  return !( __x == __y );
}

/*# define _STLP_TEMPLATE_HEADER template <class _Key, class _Tp, class _Compare, class _Alloc>

# define _STLP_TEMPLATE_CONTAINER map<_Key,_Tp,_Compare,_Alloc>

// fbp : if this template header gets protected against your will, report it !
# include <stl/_relops_cont.h>

# undef _STLP_TEMPLATE_CONTAINER
# define _STLP_TEMPLATE_CONTAINER multimap<_Key,_Tp,_Compare,_Alloc>

// fbp : if this template header gets protected against your will, report it !
# include <stl/_relops_cont.h>

# undef _STLP_TEMPLATE_CONTAINER
# undef _STLP_TEMPLATE_HEADER*/

}

// do a cleanup
/*# undef map
#   undef multimap
// provide a way to access full funclionality 
# define __map__    __FULL_NAME(map)
# define __multimap__   __FULL_NAME(multimap)

# ifdef _STLP_USE_WRAPPER_FOR_ALLOC_PARAM
# include <stl/wrappers/_map.h>
# endif

#endif  _STLP_INTERNAL_MAP_H */

// Local Variables:
// mode:C++
// End:

