#pragma once

#include "Swap.h"

// Default deletion policy
struct DefaultDeletePolicy
{
  template <typename T>
  static void Delete(T *p) { delete p; }
};

/**
  @internal

  @brief Wrapper class (modeled after std::auto_ptr_ref)

  Why do we need it? It's a really complicated question. I'll just
  give you the URL: http://groups-beta.google.com/group/comp.lang.c++.moderated/browse_thread/thread/44b72df836d414bd/277aef1b98e43afc
  or search the Web for std::auto_ptr_ref rationale.

  A wrapper class to provide AutoPtr with reference semantics.

  @param T Manager type;
 */
template<typename T, typename DEL_POLICY = DefaultDeletePolicy>
  struct AutoPtrRef
{
  T* ptr; ///< @internal
  /// @internal
  explicit AutoPtrRef(T * p): ptr(p) {}
};

/**
  @brief A clone (almost exact) of std::auto_ptr

  Instances of this class owns a pointer they hold.

  @attention Copying transfers ownership to the destination and the source
    instance doesn't own an instance any more! Example:

    @code
      Foo * const p = new Foo(); // Just an illustration, correct usage: AutoPtr<Foo> p0(new Foo())
      AutoPtr<Foo> p0(p);
      AutoPtr<Foo> p1;
      // p0 == p, p1 == NULL
      p1 = p0;
      // p0 == NULL (!), p1 = p
    @endcode

  @attention Each allocated object should be owned by one (or none) instance of AutoPtr,
    the following code will most probably crash:

    @code
      Foo * const p = new Foo();
      {
        AutoPtr<Foo> p0(p); // Now p0 owns p
        AutoPtr<Foo> p1(p); // BAD! Now p1 owns p too!
      } // Here comes the problem: both p0 and p1 will delete p!
    @endcode

  @attention Do not use AutoPtr in containers!

  @note One can use AutoPtr to indicate ownership. For example, it's nice
    to write functions that return pointers in the following way:

    @code
      AutoPtr<Foo> CreateFoo()
      {
        return AutoPtr<Foo>(new Foo());
      }
    @endcode

  The bonus is simple: created instance of Foo is guaranteed to be destroyed.
  If the caller needs the pointer, he'll manager to get it

  In the same way, if one sees the following function declaration:

  @code
    void xyzzy(AutoPtr<Foo> ptr);
  @endcode

  he instantly understands that function will delete ptr in the end.

  @param T Type of pointer

  @note The main difference between AutoPtr and stl::auto_ptr is absence of
    class members like stl::auto_ptr::get, etc. I follow Andrei Alexandrescu ideas here.

  @note There are a lot of cases when instead of AutoPtr one's better off with ScopedPtr

  @attention Do not use with smart pointer to manage arrays! Use ScopedArray instead.

  @see ls::ScopedPtr, se::ScopedArray
*/
template<typename T, typename DEL_POLICY = DefaultDeletePolicy>
  class AutoPtr
{
public:
  typedef T Element; ///< The pointed type

  /**
    @brief Default ctor

    @param p Pointer (defaults to NULL).
  */
  explicit
  AutoPtr(T * p = 0) : m_ptr(p) {}

  /**
    @brief Copy ctor

    @param sp %AutoPtr to construct from

    @attention Destructive copy! a losts ownership and gets reseted!
  */
  AutoPtr(AutoPtr &sp) : m_ptr(Release(sp)) {}

  /**
    @brief Construct from %AutoPtr of lsffernet, but related class

    @param sp %AutoPtr to construct from

    @attention Destructive copy! @em sp losts ownership and gets reseted!
  */
  template<typename U>
    AutoPtr(AutoPtr<U> &sp) : m_ptr(Release(sp)) {}

  /**
    @brief Assignment

    @param rhs %AutoPtr to copy from

    @attention Destructive copy! rhs losts ownership and gets reseted!
  */
  AutoPtr& operator = (AutoPtr &rhs)
  {
    Reset(*this, Release(rhs)); // Note: this == &rhs is unnecessary as Reset will manage it
    return *this;
  }

  /**
    @brief Assignment from %AutoPtr of differnet, but related class

    @param rhs %AutoPtr to copy from

    @attention Destructive copy! rhs losts ownership and gets reseted!
  */
  template<typename U, typename DP>
    AutoPtr& operator = (AutoPtr<U, DP> &rhs)
  {
    Reset(*this, Release(rhs)); // Note: this == &rhs is unecessary as of different types
    return *this;
  }

  /// Dtor
  ~AutoPtr()
  {
    if (m_ptr != 0) // Note: as our memory management prohibits delete 0, we have to check here
    {
			DEL_POLICY::Delete(m_ptr);
    }
  }

  /**
    @brief Dereferencing

    @return A reference to the pointed object

    @attention Watch NULL
  */
  T& operator * () const
  {
    NI_ASSERT(m_ptr != 0, "NULL auto ptr");
    return *m_ptr;
  }

  /**
    @brief Dereferencing

    @return A pointer to the pointed object

    @attention Watch NULL
  */
  T * operator-> () const
  {
		NI_ASSERT(m_ptr != 0, "NULL auto ptr");
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

  /// @internal
  AutoPtr(AutoPtrRef<T, DEL_POLICY> ref) : m_ptr(ref.ptr) {}

  /// @internal
  AutoPtr& operator = (AutoPtrRef<T, DEL_POLICY> ref)
  {
    Reset(*this, ref.ptr);
    return *this;
  }

  /// @internal
  template<typename U, typename DEL_POLICY1>
    operator AutoPtrRef<U, DEL_POLICY1>()
  {
    return AutoPtrRef<U, DEL_POLICY1>(Release(*this));
  }

  /// @internal
  template<typename U, typename DP>
    operator AutoPtr<U, DP>()
  {
    return AutoPtr<U>(Release(*this));
  }

private:
  T * m_ptr; ///< Managed pointer
};

/**
  @brief Hook to bypass smart pointerness

  @return The reference to pointer stored in smart pointer
*/
template <typename T, typename DEL_POLICY>
  typename AutoPtr<T, DEL_POLICY>::Element *& Get(AutoPtr<T, DEL_POLICY> &sp)
{
  return sp.__gEt__();
}

/**
  @brief Hook to bypass smart pointerness (const version)

  @return The pointer stored in smart pointer
*/
template <typename T, typename DEL_POLICY>
  typename AutoPtr<T, DEL_POLICY>::Element * Get(AutoPtr<T, DEL_POLICY> const &sp)
{
  return sp.__gEt__();
}

/**
  @brief Swap instances of AutoPtr

  @param lhs lhs
  @param rhs rhs
*/
template<class T, typename DEL_POLICY>
  void Swap(AutoPtr<T, DEL_POLICY> &lhs, AutoPtr<T, DEL_POLICY> &rhs)
{
  if (&lhs != &rhs)
  {
    Swap(Get(lhs), Get(rhs));
  }
}

/**
  @brief Release smart pointer

  This method fetches actual pointer under AutoPtr and
  sets @em sp to 0

  @param sp Smart pointer to work on

  @return  Actual pointer of @em sp
*/
template <typename T, typename DEL_POLICY2>
typename AutoPtr<T, DEL_POLICY2>::Element * Release(AutoPtr<T, DEL_POLICY2> &sp)
{
  typename AutoPtr<T, DEL_POLICY2>::Element * &spPtr = Get(sp);
  typename AutoPtr<T, DEL_POLICY2>::Element * const v = spPtr;
  spPtr = 0;
  return v;
}

/**
  @brief Delete managed object and set to new value

  @param sp Smart pointer to work on
  @param p A pointer to set (defaults to NULL).
*/
template <typename T, typename DEL_POLICY3>
  void Reset(AutoPtr<T, DEL_POLICY3> &sp, typename AutoPtr<T, DEL_POLICY3>::Element * p = 0)
{
  AutoPtr<T, DEL_POLICY3> temp(p);
  Swap(sp, temp);
}
