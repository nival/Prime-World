#ifndef _SCOPED_PTR_H_
#define _SCOPED_PTR_H_

#include "Swap.h"

/**
  @brief A clone (almost exact) of boost::scoped_ptr

  Instances of this class owns a pointer they hold. The ownership is retained
  while ScopedPtr is alive (but you can use Release(ScopedPtr<T>&) and
  Reset(ScopedPtr<T>&, ScopedPtr<T>::Element *) to bypass this limitation).

  If one needs more control, he can use AutoPtr

  @note The main difference between ScopedPtr and boost::scoped_ptr is absence of
    class members like boost::scoped_ptr::get, etc. I follow Andrei Alexandrescu ideas here.

  @attention Do not use with smart pointer to manage arrays! Use ScopedArray instead.

  @see ls::AutoPtr, ls::ScopedArray
*/
template<class T>
  class ScopedPtr
{
public:
  typedef T Element; ///< The pointed type

  /**
    @brief Default ctor

    @param p Pointer (defaults to NULL).
  */
  explicit
  ScopedPtr(T * p = 0) : m_ptr(p) {}

  /// Dtor
  ~ScopedPtr()
  {
    if (m_ptr != 0) // Note: as our memory management prohibits delete 0, we have to check here
    {
      delete m_ptr;
    }
  }

  /**
    @brief Dereferencing

    @return A reference to the pointed object

    @attention Watch NULL
  */
  T & operator *() const
  {
		NI_ASSERT(m_ptr != 0, "NULL scoped ptr");
    return *m_ptr;
  }

  /**
    @brief Dereferencing

    @return A pointer to the pointed object

    @attention Watch NULL
  */
  T * operator-> () const
  {
    NI_ASSERT(m_ptr != 0, "NULL scoped ptr");
    return m_ptr;
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
  ScopedPtr(ScopedPtr const &);
  /// @internal
  ScopedPtr& operator = (ScopedPtr const &);
};

/**
  @brief Hook to bypass smart pointerness (const version)

  @return The pointer stored in smart pointer
*/
template <typename T>
  typename ScopedPtr<T>::Element * Get(ScopedPtr<T> const &sp)
{
  return sp.__gEt__();
}

/**
  @brief Swap instances of ScopedPtr

  @param lhs lhs
  @param rhs rhs
*/
template<class T>
  void Swap(ScopedPtr<T> &lhs, ScopedPtr<T> &rhs)
{
  if (&lhs != &rhs)
  {
    Swap(lhs.__gEt__(), rhs.__gEt__());
  }
}

/**
  @brief Release smart pointer

  This method fetches actual pointer under ScopedPtr and
  sets @em sp to 0

  @param sp Smart pointer to work on

  @return  Actual pointer of @em sp
*/
template <typename T>
  typename ScopedPtr<T>::Element * Release(ScopedPtr<T> &sp)
{
  typename ScopedPtr<T>::Element * &spPtr = sp.__gEt__();
  typename ScopedPtr<T>::Element * const v = spPtr;
  spPtr = 0;
  return v;
}

/**
  @brief Delete managed object and set to new value

  @param sp Smart pointer to work on
  @param p A pointer to set (defaults to NULL).
*/
template <typename T>
  void Reset(ScopedPtr<T> &sp, typename ScopedPtr<T>::Element * p = 0)
{
  ScopedPtr<T> temp(p);
  Swap<T>(sp, temp);
}

#endif

