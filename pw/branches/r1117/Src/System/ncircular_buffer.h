#include <algorithm>

#ifndef NCIRCULLAR_BUFFER_H__
#define NCIRCULLAR_BUFFER_H__

namespace nstl
{

template <typename T, typename A = std::allocator<T> >
class circular_buffer
{
public:
typedef T                                            value_type;
typedef A                                            allocator_type;
typedef typename allocator_type::size_type           size_type;
typedef typename allocator_type::difference_type     difference_type;
typedef typename allocator_type::reference           reference;
typedef typename allocator_type::const_reference     const_reference;
typedef typename allocator_type::pointer             pointer;
typedef typename allocator_type::const_pointer       const_pointer;
class                                                iterator;

explicit circular_buffer(size_type capacity,
                        const allocator_type &a = allocator_type());
~circular_buffer();
allocator_type get_allocator() const;

size_type size() const;
size_type max_size() const;
bool      empty() const;

size_type capacity() const;

reference       front();
const_reference front() const;
reference       back();
const_reference back() const;
reference       operator[](size_type n);
const_reference operator[](size_type n) const;
reference       at(size_type n);
const_reference at(size_type n) const;

iterator begin();
iterator end();

bool push_back(value_type *v);
bool push_back(const value_type &v);
void pop_front();
void clear();

private:
size_type       m_capacity;
allocator_type  m_allocator;
pointer         m_buffer;
pointer         m_front;
pointer         m_back; // points to next unused item

typedef circular_buffer<T> class_type;

circular_buffer(const class_type &);
class_type &operator=(const class_type &);

value_type *wrap(value_type *ptr) const
{
   NI_ASSERT(ptr < m_buffer + m_capacity*2, "Logic");
   NI_ASSERT(ptr > m_buffer - m_capacity, "Logic");
   if (ptr >= m_buffer+m_capacity)
       return ptr-m_capacity;
   else if (ptr < m_buffer)
       return ptr+m_capacity;
   else
       return ptr;
}
};

template <typename T, typename A>
inline
circular_buffer<T,A>::circular_buffer
    (size_type capacity, const allocator_type &allocator)
: m_capacity(capacity),
m_allocator(allocator),
m_buffer(m_allocator.allocate(capacity)),
m_front(0),
m_back(m_buffer)
{
assert(capacity > 0);
}

template <typename T, typename A>
inline
circular_buffer<T,A>::~circular_buffer()
{
clear(); // deallocates all objects
m_allocator.deallocate(m_buffer, m_capacity);
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::allocator_type
circular_buffer<T,A>::get_allocator() const
{
return m_allocator;
}


template <typename T, typename A>
inline
typename circular_buffer<T,A>::size_type circular_buffer<T,A>::capacity() const
{
return m_capacity;
}

template <typename T, typename A>
inline
bool circular_buffer<T,A>::empty() const
{
return !m_front;
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::size_type circular_buffer<T,A>::size() const
{
return !m_front ? 0
               : (m_back > m_front ? m_back : m_back+m_capacity) - m_front;
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::size_type circular_buffer<T,A>::max_size() const
{
return m_allocator.max_size();
}

template <typename T, typename A>
inline
bool circular_buffer<T,A>::push_back(const value_type &value)
{
  if (m_front && m_front == m_back)
     m_allocator.destroy(m_back);

  m_allocator.construct(m_back, value);

  value_type *const next = wrap(m_back+1);
  if (!m_front)
  {
     // first entry in the buffer
     m_front = m_back;
     m_back = next;
     return true;
  }
  else if (m_front == m_back)
  {
     // buffer is full already, throw something away
     m_front = m_back = next;
     return false;
  }
  else
  {
     m_back = next;
     return true;
  }
}

template <typename T, typename A>
inline
bool circular_buffer<T,A>::push_back(value_type *v)
{
  if (m_front && m_front == m_back)
    m_allocator.destroy(m_back);

  m_back = v;

  value_type *const next = wrap(m_back+1);
  if (!m_front)
  {
    // first entry in the buffer
    m_front = m_back;
    m_back = next;
    return true;
  }
  else if (m_front == m_back)
  {
    // buffer is full already, throw something away
    m_front = m_back = next;
    return false;
  }
  else
  {
    m_back = next;
    return true;
  }
}


template <typename T, typename A>
inline
typename circular_buffer<T,A>::reference circular_buffer<T,A>::front()
{
assert(m_front);
return *m_front;
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::const_reference circular_buffer<T,A>::front() const
{
assert(m_front);
return *m_front;
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::reference circular_buffer<T,A>::back()
{
assert(m_front);
return *wrap(m_back-1);
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::const_reference circular_buffer<T,A>::back() const
{
assert(m_front);
return *wrap(m_back-1);
}

template <typename T, typename A>
inline
void circular_buffer<T,A>::pop_front()
{
assert(m_front);

m_allocator.destroy(m_front);
value_type *const next = wrap(m_front+1);
if (next == m_back)
   m_front = 0;
else
   m_front = next;
}

template <typename T, typename A>
inline
void circular_buffer<T,A>::clear()
{
if (m_front)
{
   do
   {
       m_allocator.destroy(m_front);
       m_front = wrap(m_front+1);
   }
   while (m_front != m_back);
}
m_front = 0;
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::reference circular_buffer<T,A>::operator[]
(size_type n)
{
return *wrap(m_front+n);
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::const_reference circular_buffer<T,A>::operator[]
(size_type n) const
{
return *wrap(m_front+n);
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::reference circular_buffer<T,A>::at(size_type n)
{
  NI_ASSERT(n < size(), "Parameter out of range");
  return (*this)[n];
}

template <typename T, typename A>
inline
typename circular_buffer<T,A>::const_reference circular_buffer<T,A>::at
    (size_type n) const
{
  NI_ASSERT(n < size(), "Parameter out of range");
  return (*this)[n];
}

template <typename T, typename A>
class circular_buffer<T,A>::iterator
: public std::iterator<std::random_access_iterator_tag,
                      value_type,
                      size_type,
                      pointer,
                      reference>
{
public:
typedef circular_buffer<T>             parent_type;
typedef typename parent_type::iterator self_type;

iterator(parent_type &parent, size_type index)
   : parent(parent), index(index) {}

self_type &operator++()
{
   ++index;
   return *this;
}
self_type operator++(int) // postincrement
{
   self_type old(*this);
   operator++();
   return old;
}
self_type &operator--()
{
   --index;
   return *this;
}
self_type operator--(int) // postdecrement
{
   self_type old(*this);
   operator--();
   return old;
}

reference operator*() { return parent[index]; }
pointer operator->()  { return &(parent[index]); }

bool operator==(const self_type &other) const
   { return &parent == &other.parent && index == other.index; }
bool operator!=(const self_type &other) const
   { return !(other == *this); }

private:
parent_type &parent;
size_type    index;
};

template <typename T, typename A>
typename circular_buffer<T,A>::iterator circular_buffer<T,A>::begin()
{
return iterator(*this, 0);
}

template <typename T, typename A>
typename circular_buffer<T,A>::iterator circular_buffer<T,A>::end()
{
return iterator(*this, size());
}
}

#endif // NCIRCULLAR_BUFFER_H__