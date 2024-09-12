#ifndef _SCOOPED_ARRAY_H_
#define _SCOOPED_ARRAY_H_

#include "Swap.h"

/**
  @brief A clone (almost exact) of boost::scoped_array

  Instances of this class owns a pointer they hold. The ownership is retained
  while ScopedArray is alive (but you can use Release(ScopedArray<T>&) and
  Reset(ScopedArray<T>&, ScopedArray<T>::Element*) to bypass this limitation).

  @note The main difference between ScopedArray and boost::scoped_array is absence of
    class members like boost::scoped_array::get, etc. I follow Andrei Alexandrescu ideas here.

  @attention Do not use with smart pointer to manage pointers to scalar objects!
    Use ScopedPtr or AutoPtr instead.

  @see ls::AutoPtr, ls::ScopedPtr
*/
template<class T>
  class ScopedArray
{
public:
  typedef T Element; ///< The pointed type

  /**
    @brief Default ctor

    @param p Pointer (defaults to NULL).
  */
  explicit
  ScopedArray(T * p = 0) : m_ptr(p) {}

  /// Dtor
  ~ScopedArray()
  {
    if (m_ptr != 0) // Note: as our memory management prohibits delete 0, we have to check here
    {
      delete [] m_ptr;
    }
  }

  /**
    @brief Dereferencing

    @return A reference to the pointed object

    @attention Watch NULL
  */
  T& operator[] (::ptrdiff_t i) const
  {
    NI_ASSERT(m_ptr != 0, "ScopedArray is NULL");
		NI_ASSERT(i >= 0, "ScopedArray: out of index range");
    return m_ptr[i];
  }

  /**
  @brief Casting to bool
  */
  operator bool() const
  {
    return m_ptr != 0;
  }



  /**
    @internal

    @brief Hook to bypass smart pointerness

    @attention Intentionally with mangled name---never
      use it directly. I introduce this member as
      a lot of compilers don't support correctly
      template friends! In the perferct world
      this method will disappear

    @return The reference to pointer stored in smart pointer
  */
  T * & __gEt__() { return m_ptr; }

  /**
    @internal

    @brief Hook to bypass smart pointerness (const version)

    @attention Intentionally with mangled name---never
      use it directly. I introduce this member as
      a lot of compilers don't support correctly
      template friends! In the perferct world
      this method will disappear

    @return The pointer stored in smart pointer
  */
  T * __gEt__() const { return m_ptr; }

private:
  T * m_ptr; ///< Managed pointer

  // Non-copyable
  /// @internal
  ScopedArray(ScopedArray const &);
  /// @internal
  ScopedArray& operator = (ScopedArray const &);
};

/**
  @brief Hook to bypass smart pointerness (const version)

  @return The reference to pointer stored in smart pointer
*/
template <typename T>
  typename ScopedArray<T>::Element * Get(ScopedArray<T> const &sp)
{
  return sp.__gEt__();
}

/**
  @brief Swap instances of ScopedArray

  @param lhs lhs
  @param rhs rhs
*/
template<class T>
  void Swap(ScopedArray<T> &lhs, ScopedArray<T> &rhs)
{
  if (&lhs != &rhs)
  {
    Swap(lhs.__gEt__(), rhs.__gEt__());
  }
}

/**
  @brief Release smart pointer

  This method fetches actual pointer under ScopedArray and
  sets @em sp to 0

  @param sp Smart pointer to work on

  @return  Actual pointer of @em sp
*/
template <typename T>
  typename ScopedArray<T>::Element * Release(ScopedArray<T> &sp)
{
  typename ScopedArray<T>::Element * &spPtr = sp.__gEt__();
  typename ScopedArray<T>::Element * const v = spPtr;
  spPtr = 0;
  return v;
}

/**
  @brief Delete managed object and set to new value

  @param sp Smart pointer to work on
  @param p A pointer to set (defaults to NULL).
*/
#ifndef NI_PLATF_LINUX
  #pragma warning(push)
  #pragma warning(disable: 4239)
#endif
template <typename T>
  void Reset(ScopedArray<T> &sp, typename ScopedArray<T>::Element * p = 0)
{
  ScopedArray<T> temp(p);
  Swap(sp, temp);
}
#ifndef NI_PLATF_LINUX
  #pragma warning(pop)
#endif

#endif		// _SCOOPED_ARRAY_H_

