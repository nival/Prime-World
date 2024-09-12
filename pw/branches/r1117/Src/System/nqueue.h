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

#ifndef __NSTL_QUEUE_H__
#define __NSTL_QUEUE_H__

#pragma once

#ifdef WIN32
  #pragma warning ( disable : 4180 )
#endif  

#ifndef __NSTL_HEAP_H__
#include "nheap.h"
#endif // __NSTL_HEAP_H__

namespace nstl
{

template <class _Tp, class _Sequence = vector<_Tp>, class _Compare = less >
class priority_queue 
{
public:
  typedef _Tp     value_type;
//  typedef typename _Sequence::size_type      size_type;
  typedef         _Sequence                 container_type;

  typedef typename _Sequence::reference      reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  _Sequence c;
  _Compare comp;
public:
  int operator&( IBinSaver &f ) { f.Add( 1, &c ); return 0; }
  priority_queue() : c() {}
  explicit priority_queue(const _Compare& __x) :  c(), comp(__x) {}
  priority_queue(const _Compare& __x, const _Sequence& __s) 
    : c(__s), comp(__x)
    { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last) 
    : c(__first, __last) { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first, 
                 _InputIterator __last, const _Compare& __x)
    : c(__first, __last), comp(__x)
    { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last,
                 const _Compare& __x, const _Sequence& __s)
  : c(__s), comp(__x)
  { 
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), comp);
  }

  bool empty() const { return c.empty(); }
  //size_type size() const { return c.size(); }
  int size() const { return c.size(); }
  const_reference top() const { return c.front(); }
  void push(const value_type& __x) 
  {
    c.push_back(__x); 
    push_heap(c.begin(), c.end(), comp);
  }
  void pop() 
  {
    pop_heap(c.begin(), c.end(), comp);
    c.pop_back();
  }
  void reserve( int count )
  {
    c.reserve( count );
  }
  void clear() { c.clear(); }
};


template <class _Tp, int capacity >
class circular_queue 
{
public:
  typedef _Tp     value_type;

private:
  value_type data[capacity];
  int front;
  int rear;

public:
  circular_queue()
    : front(0), rear(0)
  {
  }

  void push( const value_type& val )
  {
    int nextRear = ( rear + 1 ) % capacity;

    NI_VERIFY( nextRear != front, "Queue overflow", return );

    data[rear] = val;
    rear = nextRear;
  }

  void pop()
  {
    NI_VERIFY( front != rear, "Queue underflow", return );
    front = (front + 1 ) % capacity;
  }

  void clear()
  {
    front = rear = 0;
  }

  bool empty() const 
  { 
    return front == rear; 
  }
  int size() const
  {
    int dif = rear - front;
    if ( dif < 0 )
      dif += capacity;
    return dif;
  }
  bool full() const 
  { 
    return front == ( rear + 1 ) % capacity; 
  }
  const value_type& top() const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
    return data[front];
  }
};


template <class _Tp, size_t capacity >
class circular_buffer1 
{
public:
  typedef _Tp     value_type;

private:
  value_type data[capacity];
  int front;
  int rear;

public:
  circular_buffer1()
    : front(0), rear(0)
  {
  }

  void push( const value_type& val )
  {
    int nextRear = ( rear + 1 ) % capacity;

    if ( nextRear == front )
      pop();

    data[rear] = val;
    rear = nextRear;
  }

  void pop()
  {
    NI_VERIFY( front != rear, "Queue underflow", return );
    front = ( front + 1 ) % capacity;
  }

  void clear()
  {
    front = rear = 0;
  }

  bool empty() const 
  { 
    return front == rear; 
  }
  int size() const
  {
    return (rear - front + capacity) % capacity; // almost equal to "rear - front"
  }
  bool full() const 
  { 
    return front == ( rear + 1 ) % capacity; 
  }

  const value_type& top() const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
    return data[front];
  }

  const value_type& back() const
  {
    NI_ASSERT( !empty(), "Queue underflow" );
		return data[(rear - 1 + capacity) % capacity]; // previous (= data[rear-1] in most cases)
  }

  value_type& back()
  {
    NI_ASSERT( !empty(), "Queue underflow" );
    return data[(rear - 1 + capacity) % capacity]; // previous (= data[rear-1] in most cases)
  }

	int fit_index(int &pos) const
	{
		if ( pos < 0 )
			pos = 0;
		if ( size() <= pos )
			pos = size() - 1;
		return pos;
	}

  const value_type& top( int pos ) const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
		NI_ASSERT( 0 <= pos && pos < size(), "Index is out of bounds" );
    int dif = ( front + pos ) % capacity;
    return data[dif];
  }

  const value_type& back( int pos ) const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
		NI_ASSERT( 0 <= pos && pos < size(), "Index is out of bounds" );
		int dif = (rear - 1 - pos + capacity) % capacity; // almost equal to "(rear-1) - pos"
    return data[dif];
  }

	// direct access to underlying data structure, need for fast algorithms
	int raw_top_index() const { return front; }
	int raw_rear_index() const { return rear; }
	value_type* raw_data() { return data; }
};

} // end of namespace nstl

#endif // __NSTL_QUEUE_H__
