#ifndef _INTRUSIVE_PTR_H_
#define _INTRUSIVE_PTR_H_

#include "Swap.h"

/**
  @brief Default reference management policy class

  @note And an exemplar as well :)

  This class should manage reference counting
  for pointers. The class should implement
  two static methods: DefaultRefPolicy::addRef
  and DefaultRefPolicy::release that add and release
  a reference correspondingly.

  @note Pointers are guaranteed to be not NULL!

  @param T Type to manage pointers to
*/
struct DefaultRefPolicy
{
  template <class T>
  static void OnCreate(T * p, bool shouldAdd = true)
  {}

  /**
    @brief Add a reference
    @param p Pointer to add a reference
  */
  template <class T>
  static void addRef(T * p)
  {
    NI_ASSERT(p != 0, "Invalid object");
    p->AddRef();
  }

  /**
    @brief Release
    @param p Pointer to release
  */
  template <class T>
  static void release(T * p)
  {
		NI_ASSERT(p != 0, "Invalid object");
    p->Release();
  }
};

/**
  @brief Intrusive reference counting smart pointer class

  Heavily modeled after boost::intrusive_ptr, but with the same
  Alexandrescu fixes.

  Actually, this class can make several nice tricks as well (see
  boost::intrusive_ptr doc for more info).

  @param T Type to manage pointers to
  @param REF_POLICY Reference management policy
*/
template<class T, class REF_POLICY = DefaultRefPolicy>
  class IntrusivePtr
{
public:
  typedef T Element; ///< The pointed type

  /// Default ctor
  IntrusivePtr() : m_ptr(0)
  {
  }

  /**
    @brief Ctor

    @note Note a standard bug:

      @code
        IntrusivePtr<Foo> createFoo()
        {
          return IntrusivePtr<Foo>(new Foo());
        }
      @endcode

    The problem is simple: newly created insance of Foo is twice
    reference counted: in its ctor and in IntrusivePtr ctor. Of course,
    IntrusivePtr dtor will release one reference, but the reference of Foo
    ctor is lost!

    Therefore, when creating IntrusivePtr with new, one should code like follows:

      @code
        IntrusivePtr<Foo> createFoo()
        {
          return IntrusivePtr<Foo>(new Foo(), false); // Don't reference count twice!
        }
      @endcode

    There is a useful macro (#seINSTANTIATE_REF) introduced to require minimal 
    effort in avoiding the problem. Instead of writing createFoo() function
    you can use this macro.

      @code
        ls::IntrusivePtr<Foo> x;
        // ...
        x = lsINSTANTIATE_REF(Foo, ());
      @endcode

    @param p Pointer to manage
    @param shouldAdd Should add a reference to a object or not (defaults to true)
  */
  explicit IntrusivePtr(T * p, bool shouldAdd = true) : m_ptr(p)
  {
    addRef(shouldAdd);
    REF_POLICY::OnCreate(p, shouldAdd);
  }

  /**
    @brief Copy ctor

    @param sp %IntrusivePtr to construct from
  */
  IntrusivePtr(IntrusivePtr const &sp) : m_ptr(Get(sp))
  {
    addRef();
    REF_POLICY::OnCreate(m_ptr, true);
  }

  /// Dtor
  ~IntrusivePtr()
  {
    release();
  }

  /**
    @brief Assignment

    @param rhs %IntrusivePtr to assign from
  */
  IntrusivePtr& operator = (IntrusivePtr const &rhs)
  {
    IntrusivePtr copy(rhs);
    Swap(copy, *this);
    return *this;
  }

  /**
    @brief Plain pointer assignment

    @param rhs Pointer to assign from
  */
  IntrusivePtr& operator = (T * rhs)
  {
    IntrusivePtr copy(rhs);
    Swap(copy, *this);
    return *this;
  }


  /**
    @brief Plain pointer assignment without add-ref'ing (take ownership)

    WARNING - it is not acceptable Attach() pointer owned by something

    @param rhs Pointer to assign from
  */
  IntrusivePtr& Attach(T * rhs)
  {
    release();
    m_ptr = rhs;
    REF_POLICY::OnCreate(rhs, false);
    return *this;
  }


  /**
    @brief Give ownership of owned pointer

    @return formerly owned pointer
  */
  T* Detach()
  {
    T* const ret = m_ptr;
    m_ptr = 0;
    return ret;
  }



  /**
  @brief Plain pointer comparison

  @param rhs %IntrusivePtr to compare with 
  */
  bool operator == (IntrusivePtr const& rhs) const
  {
    return m_ptr == rhs.m_ptr;
  }

  /**
  @brief Plain pointer comparison

  @param rhs %IntrusivePtr to compare with 
  */
  bool operator != (IntrusivePtr const& rhs) const
  {
    return m_ptr != rhs.m_ptr;
  }

  /**
    @brief Construct from %IntrusivePtr of different, but related class

    @param sp %IntrusivePtr to construct from
  */
  template <class U, class ANOTHER_POLICY>
    IntrusivePtr(IntrusivePtr<U, ANOTHER_POLICY> const &sp) : m_ptr(Get(sp))
  {
    addRef();
    REF_POLICY::OnCreate(m_ptr, true);
  }

  /**
    @brief Assignment from %IntrusivePtr of differnet, but related class

    @param rhs %IntrusivePtr to construct from
  */
  template <class U, class ANOTHER_POLICY>
    IntrusivePtr& operator = (IntrusivePtr<U, ANOTHER_POLICY> const &rhs)
  {
    IntrusivePtr copy(rhs);
    Swap(copy, *this);
    return *this;
  }

  /**
    @brief Dereferencing

    @return A reference to the pointed object

    @attention Watch NULL
  */
  T& operator * () const
  {
		NI_ASSERT(m_ptr != 0, "IntrusivePtr is NULL");
    return *m_ptr;
  }

  /**
    @brief Dereferencing

    @return A pointer to the pointed object

    @attention Watch NULL
  */
  T * operator-> () const
  {
		NI_ASSERT(m_ptr != 0, "IntrusivePtr is NULL");
    return m_ptr;
  }

  /**
    @brief Casting to bool
  */
	operator bool() const
	{
		return m_ptr != 0;
	}

  template <typename T_, class U>
  friend typename IntrusivePtr<T_,U>::Element * Get(IntrusivePtr<T_,U> const &sp);
  
  template<class T_, class U>
  friend void Swap(IntrusivePtr<T_,U> &lhs, IntrusivePtr<T_,U> &rhs);

  bool operator != (T const *p) const {return m_ptr != p;}
  bool operator == (T const *p) const {return m_ptr == p;}

private:
  /**
    @internal

    @brief Add a reference to managed pointer

    @param shouldAdd Should add a reference (defaults to true)
  */
  void addRef(bool shouldAdd = true)
  {
    if ((m_ptr != 0) && shouldAdd)
    {
      REF_POLICY::addRef(m_ptr);
    }
  }

  /**
    @internal

    @brief Release manager pointer
  */
  void release()
  {
    if (m_ptr != 0)
    {
      REF_POLICY::release(m_ptr);
    }
  }

  T * m_ptr; ///< Managed pointer
};


template <typename T, class U>
inline typename IntrusivePtr<T,U>::Element * Get(IntrusivePtr<T,U> const &sp)
{
  return sp.m_ptr;
}

/**
  @brief Swap instances of IntrusivePtr

  @param lhs lhs
  @param rhs rhs
*/
template<class T, class U>
inline void Swap(IntrusivePtr<T,U> &lhs, IntrusivePtr<T,U> &rhs)
{
  Swap(lhs.m_ptr, rhs.m_ptr);
}

/**
  @brief    Create an instance of a reference counted class.

  This macro is introduced to require minimal effort in 
  using %IntrusivePtr's. 
  See @link ls::IntrusivePtr::IntrusivePtr(T*, bool) IntrusivePtr constructor@endlink
  documentation for more details on the problem.

  With help of the macro you will write
    @code
      ls::IntrusivePtr<Foo> x;
      // ...
      x = lsINSTANTIATE_REF(Foo, ());
    @endcode
  instead of 
    @code
      ls::IntrusivePtr<Foo> x;
      // ...
      x = ls::IntrusivePtr<Foo>(seNEW(seMNGI_SYSTEM, Foo()), false);
    @endcode

  @param    cls      name of class
  @param    params   constructor parameters surrounded by parens 
                     or parens alone in case of default constructor

  @author   Paul
*/

#endif // _INTRUSIVE_PTR_H_

