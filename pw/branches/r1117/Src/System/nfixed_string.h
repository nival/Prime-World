#ifndef NFIXED_STRING_H__
#define NFIXED_STRING_H__

#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif

#include "nstring.h"

namespace nstl
{

// TODO: traits?

// An abstract interface required to hide actual capacity
template <class _Tp>
class fixed_string_base
{
public:
  typedef _Tp               value_type;
  typedef int               size_type;

  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;

  typedef value_type*       iterator;
  typedef const value_type* const_iterator;

  virtual void Assign(basic_string<_Tp> const & s) = 0;
  virtual void Assign(fixed_string_base<_Tp> const& s) = 0;
  virtual void Assign(const_pointer const s) = 0;
  virtual void Assign(const_pointer const s, size_type const n) = 0;
  virtual void Assign(const_pointer const first, const_pointer const last) = 0;

  virtual void Resize(size_type const size) = 0;

  virtual pointer GetData() = 0;
  virtual const_pointer GetData() const = 0;

  virtual size_type GetCapacity() const = 0;
  virtual size_type GetLength() const = 0;
  // NOTE: size in bytes !!!
  virtual size_type GetSize() const = 0;
  // NOTE: storage size in bytes !!!
  virtual size_type GetStorageSize() const = 0;

  operator basic_string<_Tp>() const
  {
    return basic_string<_Tp>(GetData(), GetData() + GetLength());
  }
protected:
  fixed_string_base() {}
  ~fixed_string_base() {}
private:
  fixed_string_base(const fixed_string_base&);
  fixed_string_base& operator=(const fixed_string_base&);
};

// _LengthLowerBound is a minimum desired length, instance will be able to hold this number of characters.
// Also there will be a null terminator and padding.
template <class _Tp, size_t _LengthLowerBound>
class fixed_string
  : public fixed_string_base<_Tp>
{
  enum
  {
    _Alignment = 4,
    // simple bits trick to align some value to the given boundary
    // the value to be aligned is (_LengthLowerBound + 1) - desired length and null terminator
    _AlignedStorageLength = (size_t(_LengthLowerBound) + 1U + size_t(_Alignment) - 1U) & ~(size_t(_Alignment) - 1U),
    _MinStorageLength = _Alignment,
  };

  enum
  {
    StorageLength = _AlignedStorageLength < _MinStorageLength ? _MinStorageLength : _AlignedStorageLength,
    MaxLength = StorageLength - 1,
  };
public:
  typedef _Tp               value_type;
  typedef int               size_type;

  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;

  typedef value_type*       iterator;
  typedef const value_type* const_iterator;

  fixed_string()
  {
    _M_default_initialize();
    _M_terminate_string();
  }

  fixed_string(const_pointer const first, const_pointer const last)
  {
    _M_range_initialize(first, last);
    _M_terminate_string();
  }

  fixed_string(const_pointer const s)
  {
    _M_range_initialize(s, s + __strlen(s));
    _M_terminate_string();
  }

  fixed_string(const_pointer const s, size_type const n)
  {
    _M_range_initialize(s, s + n);
    _M_terminate_string();
  }

  fixed_string(basic_string<_Tp> const & s)
  {
    _M_range_initialize(s.begin(), s.end());
    _M_terminate_string();
  }

  fixed_string(fixed_string const & s)
  {
    _M_range_initialize(s.begin(), s.end());
    _M_terminate_string();
  }

  template <size_t _N>
  fixed_string(fixed_string<_Tp, _N> const & s)
  {
    _M_range_initialize(s.begin(), s.end());
    _M_terminate_string();
  }

  bool empty() const
  {
    return m_start == m_finish;
  }

  size_type length() const
 {
    return size_type(m_finish - m_start);
  }

  // NOTE: size in bytes !!!
  // TODO: nstl's string makes size() equivalent to length()
  size_type size() const
  {
    return size_type(sizeof(_Tp)) * length();
  }

  // NOTE: storage size in bytes !!!
  // TODO: nstl's string makes size() equivalent to length()
  size_type storage_size() const
  {
    return size_type(sizeof(_Tp)) * size_type(StorageLength);
  }

  size_type capacity() const
  {
    // NOTE: MaxLength is guaranteed to be non-negative
    return size_type(MaxLength);
  }

  const_pointer c_str() const
  {
    return m_start;
  }

  pointer data()
  {
    return m_data;
  }

  const_pointer data() const
  {
    return m_data;
  }

  iterator begin() { return m_start; }
  iterator end() { return m_finish; }

  const_iterator begin() const { return m_start; }
  const_iterator end() const { return m_finish; }

  fixed_string& operator=(basic_string<_Tp> const & s)
  {
    _M_range_initialize(s.begin(), s.end());
    _M_terminate_string();
    return *this;
  }

  fixed_string& operator=(fixed_string const & s)
  {
    if (m_data != s.m_data)
    {
      _M_range_initialize(s.begin(), s.end());
      _M_terminate_string();
    }
    return *this;
  }

  template <size_t _N>
  fixed_string& operator=(fixed_string<_Tp, _N> const & s)
  {
    _M_range_initialize(s.begin(), s.end());
    _M_terminate_string();
    return *this;
  }

  fixed_string& operator=(const _Tp* const s)
  {
    _M_range_initialize(s, s + __strlen(s));
    _M_terminate_string();
    return *this;
  }

  value_type& operator[](const size_type n)
  {
    ASSERT(n < capacity());
    return m_data[n];
  }

  const value_type& operator[](const size_type n) const
  {
    ASSERT(n < capacity());
    return m_data[n];
  }

  operator basic_string<_Tp>() const
  {
    return basic_string<_Tp>(begin(), end());
  }
private:
  template <class _InputIter>
  void _M_range_initialize(_InputIter __f, _InputIter __l) 
  {
    const size_type n = min(size_type(__l - __f), capacity());

    m_start = m_data;
    m_finish = copy(__f, __f + n, m_start);
  }

  void _M_default_initialize()
  {
    m_start = m_data;
    m_finish = m_start;
  }

  void _M_terminate_string()
  {
    ASSERT(length() <= capacity());
    *m_finish = 0;
  }

  virtual void Assign(basic_string<_Tp> const & s)
  {
    _M_range_initialize(s.begin(), s.end());
    _M_terminate_string();
  }

  virtual void Assign(fixed_string_base<_Tp> const& s)
  {
    const_pointer first = s.GetData();
    const_pointer last = first + s.GetLength();

    if (m_data == first)
      return;

    _M_range_initialize(first, last);
    _M_terminate_string();
  }

  virtual void Assign(const_pointer const s)
  {
    _M_range_initialize(s, s + __strlen(s));
    _M_terminate_string();
  }

  virtual void Assign(const_pointer const s, size_type const n)
  {
    _M_range_initialize(s, s + n);
    _M_terminate_string();
  }

  virtual void Assign(const_pointer const first, const_pointer const last)
  {
    _M_range_initialize(first, last);
    _M_terminate_string();
  }

  virtual void Resize(size_type const size)
  {
    const size_type n = max(0, min(size, capacity()));

    m_start = m_data;
    m_finish = m_start + n;

    _M_terminate_string();
  }

  virtual pointer GetData()
  {
    return m_data;
  }

  virtual const_pointer GetData() const
  {
    return m_data;
  }

  virtual size_type GetCapacity() const
  {
    return capacity();
  }

  virtual size_type GetLength() const
  {
    return length();
  }

  virtual size_type GetSize() const
  {
    return size();
  }

  virtual size_type GetStorageSize() const
  {
    return storage_size();
  }

  _Tp   m_data[StorageLength];
  _Tp*  m_start;
  _Tp*  m_finish;
};

template <size_t N>
struct hash< nstl::fixed_string<char, N> >
{
  unsigned int operator()(const nstl::fixed_string<char, N>& s) const
  {
    return nstl::__stl_hash_string(s.c_str());
  }

  unsigned int operator()(const char *s) const
  {
    return nstl::__stl_hash_string(s);
  }
};

template <size_t N>
struct hash< nstl::fixed_string<wchar_t, N> >
{
  unsigned int operator()(const nstl::fixed_string<wchar_t, N>& s) const
  {
    unsigned int r = 0;
    for (int k = 0, len = s.length(); k < len; ++k)
      r = 5 * r + ((int)s[k]);
    return r;
  }
};

} // namespace nstl

#endif  //NFIXED_STRING_H__
