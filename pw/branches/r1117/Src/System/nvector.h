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
#ifndef NVECTOR_H__
#define NVECTOR_H__

#ifndef NI_PLATF_LINUX
#pragma warning( disable : 4244 )
#else
#ifndef assert
#include <cassert>
#endif
#endif
//#include "ntype_traits.h"
#include "nuninitialized.h"
#include "helpdebugmacroses.h"
//#include "niterator_base.h"
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

namespace nstl
{

template<class _Arg1,class _Arg2,class _Result>
struct binary_function
{	
  typedef _Arg1   first_argument_type;
  typedef _Arg2   second_argument_type;
  typedef _Result result_type;
};

template<class _Type>
class greater_pred : public nstl::binary_function<_Type,_Type,bool>
{
public:
  bool operator()(const _Type& lhs,const _Type& rhs) const
  {
    if(lhs < rhs)
      return true;
    else
      return false;
  }
};

template<class _Type>
class less_pred: public nstl::binary_function<_Type,_Type,bool>
{
public:
  bool operator()(const _Type& lhs,_Type& rhs) const 
  {
    if(lhs > rhs)
      return true;
    else
      return false;
  }
};

template <class _Tp >
class vector
{
private:
    _Tp* _M_start;
    _Tp* _M_finish;
    _Tp* _M_end_of_storage;
    _Tp* alloc( int __n ) { return (_Tp*) new char[ __n * sizeof(_Tp) ]; }
    void (free)( _Tp *p ) { delete[] ((char*)p); }
public:
    typedef _Tp value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

public:
    typedef value_type& reference;
    typedef const value_type& const_reference;
//  typedef ptrdiff_t difference_type;
//  typedef _Alloc allocator_type;

protected:
//  typedef typename    __type_traits<_Tp>::has_trivial_assignment_operator _TrivialAss;
//  typedef typename    __type_traits<_Tp>::has_trivial_assignment_operator _IsPODType;

    // handles insertions on overflow
    template<class T1>
    void _M_insert_overflow( pointer __position, const T1& __x,
                int __fill_len, bool __atend = false) {
        const int __old_size = size();
        const int __len = __old_size + (max)(__old_size, __fill_len);

        pointer __new_start = alloc( __len );//this->_M_end_of_storage.allocate(__len);
        pointer __new_finish = __new_start;
        __new_finish = nstl::uninitialized_copy(this->_M_start, __position, __new_start);
        // handle insertion
        __new_finish = nstl::uninitialized_fill_n(__new_finish, __fill_len, __x);
        if (!__atend)
            // copy remainder
            __new_finish = nstl::uninitialized_copy(__position, this->_M_finish, __new_finish);
        _M_clear();
        _M_set(__new_start, __new_finish, __new_start + __len);
    }

    // handles insertions on overflow
    void _M_insert_overflow1(pointer __position,
        int __fill_len, bool __atend = false) {
            const int __old_size = size();
            const int __len = __old_size + (max)(__old_size, __fill_len);

            pointer __new_start = alloc( __len );//this->_M_end_of_storage.allocate(__len);
            pointer __new_finish = __new_start;
            __new_finish = nstl::uninitialized_copy(this->_M_start, __position, __new_start);
            // handle insertion
            __new_finish = nstl::uninitialized_fill_n(__new_finish, __fill_len);
            if (!__atend)
                // copy remainder
                __new_finish = nstl::uninitialized_copy(__position, this->_M_finish, __new_finish);
            _M_clear();
            _M_set(__new_start, __new_finish, __new_start + __len);
        }

/*  void _M_range_check(int __n) const {
        if (__n >= int(this->_M_finish-this->_M_start))
            __stl_throw_out_of_range("vector");
    }*/

public:
    LOOK_FUNC

#ifdef _NSTL_HELP_DEBUG
    #define INST_LOOK_AT InstantiateLookAt();

    value_type& LookAt( int idx )
    {
        return (*this)[idx];
    }
    void InstantiateLookAt()
    {
        if ( false )
            LookAt( 0 );
    }
#else
    #define INST_LOOK_AT
#endif // _NSTL_HELP_DEBUG


    iterator begin()                         { return this->_M_start; }
    const_iterator begin() const { return this->_M_start; }
    iterator end()                           { return this->_M_finish; }
    const_iterator end() const   { return this->_M_finish; }

    //reverse_iterator rbegin()                         { return reverse_iterator(end()); }
    //const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    //reverse_iterator rend()                               { return reverse_iterator(begin()); }
    //const_reverse_iterator rend() const       { return const_reverse_iterator(begin()); }

    int size() const                { return int(this->_M_finish - this->_M_start); }
    int max_size() const        { return int(-1) / sizeof(_Tp); }
    int capacity() const        { return int(this->_M_end_of_storage - this->_M_start); }
    bool empty() const                      { return this->_M_start == this->_M_finish; }

#if defined( NV_WIN_PLATFORM )
    __forceinline
#endif
    reference operator[](int __n)
    {
#ifdef _DEBUG
      assert(__n >= 0 && __n < size() );
#endif
        return *(begin() + __n);
    }

#if defined( NV_WIN_PLATFORM )
        __forceinline
#endif
    const_reference operator[](int __n) const
    {
#ifdef _DEBUG
      assert(__n >= 0 && __n < size() );
#endif
        return *(begin() + __n);
    }

    reference front()                        { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back()                            { return *(end() - 1); }
    const_reference back() const    { return *(end() - 1); }

    //reference at(int __n) { _M_range_check(__n); return (*this)[__n]; }
    //const_reference at(int __n) const { _M_range_check(__n); return (*this)[__n]; }

    const_reference at_safe( int __n, const _Tp& __val ) const
    {
        if ( __n < 0 || __n >= size() )
            return __val;
        return (*this)[__n];
    }

    explicit vector()
        : _M_start(0), _M_finish(0), _M_end_of_storage(0)
        { LOOK_INIT( *this ); INST_LOOK_AT }

    vector(int __n, const _Tp& __val )
    {
        _M_start = alloc(__n);//_M_end_of_storage.allocate(__n);
        _M_end_of_storage = _M_start + __n;
        this->_M_finish = nstl::uninitialized_fill_n(this->_M_start, __n, __val);

        LOOK_INIT( *this );
        INST_LOOK_AT
    }

    explicit vector(int __n)
     {
         _M_start = alloc(__n);//_M_end_of_storage.allocate(__n);
         _M_end_of_storage = _M_start + __n;
        _M_finish = nstl::uninitialized_fill_n(this->_M_start, __n);

        LOOK_INIT( *this );
        INST_LOOK_AT
    }

    vector(const vector<_Tp>& __x)
    {
        _M_start = alloc(__x.size());//_M_end_of_storage.allocate(__n);
        _M_end_of_storage = _M_start + __x.size();
        this->_M_finish = nstl::uninitialized_copy((const_pointer)__x._M_start,
                                                                                     (const_pointer)__x._M_finish, this->_M_start);

        LOOK_INIT( *this );
        INST_LOOK_AT
    }

    // Check whether it's an integral type. If so, it's not an iterator.
    template <class _InputIterator>
    vector(_InputIterator __first, _InputIterator __last) : _M_start(0), _M_finish(0), _M_end_of_storage(0)
    {
        for ( ; __first != __last; ++__first)
            push_back(*__first);
        //_M_range_initialize(__first, __last, input_iterator_tag() );//_NSTL_ITERATOR_CATEGORY(__first, _InputIterator));

        LOOK_INIT( *this );
        INST_LOOK_AT
    }


    ~vector()
    {
        nstl::_Destroy(this->_M_start, this->_M_finish);
        if (_M_start !=0)
            (free)( _M_start );//_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
    }

    vector<_Tp>& operator=(const vector<_Tp>& __x);

    void reserve(int __n);

    // assign(), a generalized assignment member function.  Two
    // versions: one that takes a count, and one that takes a range.
    // The range version is a member template, so we dispatch on whether
    // or not the type is an integer.

    void assign(int __n, const _Tp& __val) { _M_fill_assign(__n, __val); }
    void _M_fill_assign(int __n, const _Tp& __val);


    //template <class _InputIterator>
    //void assign(_InputIterator __first, _InputIterator __last) {
    //  for ( ; __first != __last; ++__first)
    //      push_back(*__first);
    //}

    template<class T1>
    _Tp& push_back(const T1& __x) {
        if (this->_M_finish != this->_M_end_of_storage) {
            nstl::_Construct(this->_M_finish, __x);
            ++this->_M_finish;
        }
        else
            _M_insert_overflow(this->_M_finish, __x, 1UL, true);
        return this->_M_finish[-1];
    }

    void swap(vector<_Tp>& __x) {
        nstl::swap(this->_M_start, __x._M_start);
        nstl::swap(this->_M_finish, __x._M_finish);
        nstl::swap(this->_M_end_of_storage, __x._M_end_of_storage);
    }

    iterator insert(iterator __position, const _Tp& __x) {
        int __n = __position - begin();
        if (this->_M_finish != this->_M_end_of_storage) {
            if (__position == end()) {
                _Construct(this->_M_finish, __x);
                ++this->_M_finish;
            } else {
                _Construct(this->_M_finish, *(this->_M_finish - 1));
                ++this->_M_finish;
                _Tp __x_copy = __x;
                copy_backward(__position, this->_M_finish - 2, this->_M_finish - 1);
                *__position = __x_copy;
            }
        }
        else
            _M_insert_overflow(__position, __x, 1UL);
        return begin() + __n;
    }

    _Tp& push_back() { return push_back(_Tp()); }
    iterator insert(iterator __position) { return insert(__position, _Tp()); }

    void _M_fill_insert (iterator __pos, int __n, const _Tp& __x);
    void _M_fill_insert (iterator __pos, int __n);

            // Check whether it's an integral type. If so, it's not an iterator.
            template <class _InputIterator>
                void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
                    //typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
                _M_range_insert(__pos, __first, __last );//, input_iterator_tag() );//_NSTL_ITERATOR_CATEGORY(__first, _InputIterator));
                }

                template <class _InputIterator>
                    void _M_range_insert(iterator __pos,
                    _InputIterator __first,
                    _InputIterator __last )
                    //  const input_iterator_tag &) {
                {
                        for ( ; __first != __last; ++__first) {
                            __pos = insert(__pos, *__first);
                            ++__pos;
                        }
                    }

/*                  template <class _ForwardIterator>
                        void _M_range_insert(iterator __position,
                        _ForwardIterator __first,
                        _ForwardIterator __last,
                        const forward_iterator_tag &)

    {
        if (__first != __last) {
            int __n = distance(__first, __last);

            if (int(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
                const int __elems_after = this->_M_finish - __position;
                pointer __old_finish = this->_M_finish;
                if (__elems_after > __n) {
                    nstl::uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
                    this->_M_finish += __n;
                    __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
                    copy(__first, __last, __position);
                }
                else {
                    _ForwardIterator __mid = __first;
                    advance(__mid, __elems_after);
                    nstl::uninitialized_copy(__mid, __last, this->_M_finish, _IsPODType());
                    this->_M_finish += __n - __elems_after;
                    nstl::uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
                    this->_M_finish += __elems_after;
                    copy(__first, __mid, __position);
                } // elems_after
            }
            else {
                const int __old_size = size();
                const int __len = __old_size + (max)(__old_size, __n);
                pointer __new_start = alloc( __len );//this->_M_end_of_storage.allocate(__len);
                pointer __new_finish = __new_start;
                __new_finish = nstl::uninitialized_copy(this->_M_start, __position, __new_start, _IsPODType());
                __new_finish = nstl::uninitialized_copy(__first, __last, __new_finish, _IsPODType());
                __new_finish = nstl::uninitialized_copy(__position, this->_M_finish, __new_finish, _IsPODType());
                _M_clear();
                _M_set(__new_start, __new_finish, __new_start + __len);
            }
        }
    }*/
    void insert (iterator __pos, int __n, const _Tp& __x) { _M_fill_insert(__pos, __n, __x); }
    //void insert (iterator __pos, int __n) { _M_fill_insert(__pos, __n); }

    void pop_back() {
        --this->_M_finish;
        _Destroy(this->_M_finish);
    }
    iterator erase(iterator __position) {
        if (__position + 1 != end())
            copy( __position + 1, this->_M_finish, __position);
        --this->_M_finish;
        _Destroy(this->_M_finish);
        return __position;
    }
    iterator erase(iterator __first, iterator __last) {
        pointer __i = nstl::copy(__last, this->_M_finish, __first);
        nstl::_Destroy(__i, this->_M_finish);
        this->_M_finish = __i;
        return __first;
    }

    void resize(int __new_size, const _Tp& __x) {
        if (__new_size < size())
            erase(begin() + __new_size, end());
        else
            _M_fill_insert(end(), __new_size - size(), __x);
    }
    void resize(int __new_size) {
        if (__new_size < size())
            erase(begin() + __new_size, end());
        else
            _M_fill_insert( end(), __new_size - size());
    }
    void clear() {
        resize(0);
    }
    void _clear() {
        _Destroy(this->_M_start, this->_M_finish);
        if (_M_start !=0)
            (free)( _M_start );//_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
        _M_start = 0;
        _M_finish = 0;
        _M_end_of_storage = 0;
    }
    
    // additional usability method
    inline void eraseByIndex(int index) {
        erase(begin()+index);
    }

  iterator find(const _Tp& value)
  {
    for (iterator it=begin();it!=end();++it) {
      if (*it == value) {
        return it;
      }
    }
    return end();
  }

  const_iterator find(const _Tp& value) const
  {
    for (const_iterator it=begin();it!=end();++it) {
      if (*it == value) {
        return it;
      }
    }
    return end();
  }

	inline void remove(const _Tp& value)
	{
		for (iterator it=begin();it!=end();++it) {
			if (*it == value) {
				erase(it);
				return;
			}
		}
	}

protected:

    void _M_clear() {
        //      if (this->_M_start) {
        nstl::_Destroy(this->_M_start, this->_M_finish);
        (free)( _M_start );//this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
        _M_start = 0;
        //      }
    }

    void _M_set(pointer __s, pointer __f, pointer __e) {
        this->_M_start = __s;
        this->_M_finish = __f;
        this->_M_end_of_storage = __e;
    }

    template <class _ForwardIterator>
        pointer _M_allocate_and_copy(int __n, _ForwardIterator __first,
        _ForwardIterator __last)
    {
        pointer __result = alloc( __n );//this->_M_end_of_storage.allocate(__n);
        nstl::uninitialized_copy(__first, __last, __result);
        return __result;
    }


/*  template <class _InputIterator>
        void
        _M_range_initialize(_InputIterator __first,
        _InputIterator __last, const input_iterator_tag &) {
        }
        */
        // This function is only called by the constructor.
/*      template <class _ForwardIterator>
            void _M_range_initialize(_ForwardIterator __first,
            _ForwardIterator __last, const forward_iterator_tag &) {
                int __n = distance(__first, __last);
                this->_M_start = alloc( __n );//this->_M_end_of_storage.allocate(__n);
                this->_M_end_of_storage._M_data = this->_M_start + __n;
                this->_M_finish = nstl::uninitialized_copy(__first, __last, this->_M_start, _IsPODType());
            }*/

};


template <class _Tp>
void
inline
vector<_Tp>::reserve(int __n) {
    if (capacity() < __n) {
        const int __old_size = size();
        pointer __tmp;
        if (this->_M_start) {
            __tmp = _M_allocate_and_copy(__n, this->_M_start, this->_M_finish);
            _M_clear();
        } else {
            __tmp = alloc( __n );//this->_M_end_of_storage.allocate(__n);
        }
        _M_set(__tmp, __tmp + __old_size, __tmp + __n);
    }
}

template <class _Tp>
void
inline
vector<_Tp>::_M_fill_insert(
    iterator __position,
    int __n, const _Tp& __x) {
        if (__n != 0) {
            if (int(this->_M_end_of_storage - this->_M_finish) >= __n) {
                _Tp __x_copy = __x;
                const int __elems_after = this->_M_finish - __position;
                pointer __old_finish = this->_M_finish;
                if (__elems_after > __n) {
                    nstl::uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish);
                    this->_M_finish += __n;
                    nstl::copy_backward(__position, __old_finish - __n, __old_finish);
                    nstl::fill(__position, __position + __n, __x_copy);
                }
                else {
                    nstl::uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
                    this->_M_finish += __n - __elems_after;
                    nstl::uninitialized_copy(__position, __old_finish, this->_M_finish);
                    this->_M_finish += __elems_after;
                    nstl::fill(__position, __old_finish, __x_copy);
                }
            }
            else
                _M_insert_overflow(__position, __x, __n);
        }
    }

    template <class _Tp>
        void
        inline
        vector<_Tp>::_M_fill_insert(
        iterator __position,
        int __n) {
            if (__n != 0) {
                if (int(this->_M_end_of_storage - this->_M_finish) >= __n) {
                    const int __elems_after = this->_M_finish - __position;
                    pointer __old_finish = this->_M_finish;
                    if (__elems_after > __n) {
                        nstl::uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish);
                        this->_M_finish += __n;
                        nstl::copy_backward(__position, __old_finish - __n, __old_finish);
                        nstl::fill(__position, __position + __n, _Tp());
                    }
                    else {
                        nstl::uninitialized_fill_n(this->_M_finish, __n - __elems_after);
                        this->_M_finish += __n - __elems_after;
                        nstl::uninitialized_copy(__position, __old_finish, this->_M_finish);
                        this->_M_finish += __elems_after;
                        nstl::fill(__position, __old_finish, _Tp());
                    }
                }
                else
                    _M_insert_overflow1(__position, __n);
            }
        }

        template <class _Tp>
            inline
            vector<_Tp>&
            vector<_Tp>::operator=(const vector<_Tp>& __x)
        {
            if (&__x != this) {
                const int __xlen = __x.size();
                if (__xlen > capacity()) {
                    pointer __tmp = _M_allocate_and_copy(__xlen, (const_pointer)__x._M_start+0, (const_pointer)__x._M_finish+0);
                    _M_clear();
                    this->_M_start = __tmp;
                    this->_M_end_of_storage = this->_M_start + __xlen;
                }
                else if (size() >= __xlen) {
                    pointer __i = copy((const_pointer)__x._M_start+0, (const_pointer)__x._M_finish+0, (pointer)this->_M_start);
                    _Destroy(__i, this->_M_finish);
                }
                else {
                    copy((const_pointer)__x._M_start, (const_pointer)__x._M_start + size(), (pointer)this->_M_start);
                    nstl::uninitialized_copy((const_pointer)__x._M_start + size(), (const_pointer)__x._M_finish+0, this->_M_finish);
                }
                this->_M_finish = this->_M_start + __xlen;
            }
            return *this;
        }

        template <class _Tp>
            inline
void vector<_Tp>::_M_fill_assign(int __n, const _Tp& __val) {
                if (__n > capacity()) {
                    vector<_Tp> __tmp(__n, __val);
                    __tmp.swap(*this);
                }
                else if (__n > size()) {
                    fill(begin(), end(), __val);
                    this->_M_finish = nstl::uninitialized_fill_n(this->_M_finish, __n - size(), __val);
                }
                else
                    erase(nstl::fill_n(begin(), __n, __val), end());
            }


template <class _Tp>
inline bool operator==(const vector<_Tp>& __x, const vector<_Tp>& __y) {
    return __x.size() == __y.size() &&
        equal(__x.begin(), __x.end(), __y.begin());
}

template <class T>
inline bool operator!=( const vector<T> &a, const vector<T> &b) {
    return !(a==b);
}

template<class T>
inline void swap( vector<T> &_Left, vector<T> &_Right )
{
    _Left.swap( _Right );
}

}

#endif //NVECTOR_H__
