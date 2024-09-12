#ifndef _SYSTEM_SERING_H_
#define _SYSTEM_SERING_H_
/**
  @file

  @brief ring::Ring
*/
#include <stddef.h>
#include "Basic.h"
#include "Pointers/Pointers.h"
#include "Pointers/Strong.h"
#include "Pointers/Weak.h"

/// This namespace contains ring implementation
namespace ring
{
/// @brief Ring part
template <class T>
  struct PartT
{
  typedef T Element; ///< Class of elements included into a ring

  T * prev; ///< previous object in the ring
  T * next; ///< next object in the ring

  /// Default ctor
  PartT() : prev(0), next(0) {}

  /**
    @internal

    @brief Utility ctor

    @note It shouldn't be here, but as friend templates are
      rather tricky beasts, I do provide it. Please, don't
      use it directly, unless you know what are you doing.

    @param p Pointer to initialize prev and next
  */
  PartT(T * p) : prev(p), next(p) {}

  /**
    @brief Is part linked into a ring?

    @return true iff is linked
  */
  bool isLinked() const
  {
    return (prev != 0) || (next != 0);
  }

private:
  // Non-copyable!
  /// @internal
  PartT(PartT const &);
  /// @internal
  PartT& operator = (PartT const &);
  // Non-serializable
  // @internal 
  int operator& ( IBinSaver& ) { return 0; }
};

// For possible future use
template <class T>
struct DefaultSmartPtrPolicy
{
	static void AddRef(T * /*obj*/, void *) {}
	static void Release(T * /*obj*/, void *) {}
	typedef T* Pointer;
	
	enum { SerializeByPointer = 0 };
};

// For possible future use
struct CObjectBasePolicy
{
	static void AddRef(CObjectBase * obj, void *pPart) { TRACK_ADDOBJ(obj, pPart); obj->AddObj(); }
	static void Release(CObjectBase * obj, void *pPart) { TRACK_DECOBJ(obj, pPart); obj->ReleaseObj(); }
	enum { SerializeByPointer = 1 };
};

template <class T>
struct CObjectBasePolicyWithPtr : public CObjectBasePolicy
{
	typedef CObj<T> Pointer;
};

// For possible future use
struct CPtrBasePolicy
{
	static void AddRef(CObjectBase * obj, void *pPart) {  TRACK_ADDPTR(obj, pPart); obj->AddRef(); }
	static void Release(CObjectBase * obj, void *pPart) { TRACK_DECPTR(obj, pPart); obj->ReleaseRef(); }
	enum { SerializeByPointer = 1 };
};

template <class T>
struct CPtrBasePolicyWithPtr : public CPtrBasePolicy
{
	typedef CPtr<T> Pointer;
};


//Single-threaded strong pointers version
template <class T>
struct StrongSTPolicy
{
	typedef Strong<T> Pointer;
  static void AddRef( BaseObjectST * obj, void * pPart ) { TRACK_ADDOBJ( obj, pPart ); obj->StrongAddRef(); }
	static void Release( BaseObjectST * obj, void * pPart ) { TRACK_DECOBJ( obj, pPart ); obj->StrongRelease(); }
	enum { SerializeByPointer = 1 };
};



//Single-threaded strong pointers version
template <class T>
struct WeakSTPolicy
{
	typedef Weak<T> Pointer;
  enum { SerializeByPointer = 1 };

  static void AddRef( BaseObjectST * obj, void * pPart )
  {
    if (obj)
    {
      TRACK_ADDOBJ( obj, pPart );
      WeakPointerProxyST * proxy = obj ? ni_detail::AcquireWeakProxy<WeakPointerProxyST>( obj ) : 0;
      proxy->WeakAddRef();
    }
  }

  static void Release( BaseObjectST * obj, void * pPart )
  {
    if (obj)
    {
      TRACK_DECOBJ( obj, pPart );
      WeakPointerProxyST * proxy = obj ? ni_detail::AcquireWeakProxy<WeakPointerProxyST>( obj ) : 0;
      proxy->WeakRelease();
    }
  }
};

/**
  @brief %Ring template

  @attention One shouldn't use Ring template directly but rather use
    seDECLARE_RING or seDECLARE_RING_CLASS macros

  @param T type of objects included into a ring
  @param C class that performs conversions between pointers
    to part and the object itself. This class should support
    to static methods:

    @li Part& C::part(T * obj) --- get object's part
    @li T * C::obj(Part * part) --- get object from part (hacky stuff, see self for more info)

  Smart guys like us may ask why AMuh uses such a marvelous macro and didn't
  code plain'n'nice member-pointer parametrized template. The answer is simple: vc7.0 bugs
  with member-pointer parametrized templates.
*/
template <class T, class C, class REF_POLICY>
class Ring
{
public:
  typedef T Element; ///< Class of elements included into a ring
  typedef PartT<T> Part; ///< Associated Part class

  /// Default ctor
  Ring() : m_part(self())
  {
  }

  /**
    @brief Add an object into a ring

    @param obj Object to add

    @see remove
  */
  void add(T * obj)
  {
    insertAfter(obj, self());
  }

  /**
    @brief Add an object into a ring after given one

    @param obj Object to add
    @param after Object in ring to add after

    @see remove
  */
  void addAfter(T * obj, T * after)
  {
    insertAfter(obj, after);
  }

  /**
  @brief Add an object to the end of ring

  @param obj Object to add

  @see remove
  */
  void addFirst(T * obj)
  {
    insertBefore(obj, first());
  }
  /**
    @brief Add an object to the end of ring

    @param obj Object to add

    @see remove
  */
  void addLast(T * obj)
  {
    insertBefore(obj, self());
  }

  /**
    @brief Insert an object into a ring after the given one

    @param obj Object to insert into a ring
    @param after An object to insert obj after
  */
  static
  void insertAfter(T * obj, T * after)
  {
    NI_VERIFY_TRACE(obj, "ring::insertAfter: Null obj!", return);
    NI_VERIFY_TRACE(after, "ring::insertAfter: Null after!", return);

    bool addRef = true;
    Part &objPart = part(obj);
    if ( objPart.isLinked() )
    {
      NI_ALWAYS_ASSERT_TRACE("obj is already inlcuded into some ring!");
      T * const prev = objPart.prev;
      T * const next = objPart.next;
      part(prev).next = next;
      part(next).prev = prev;
      objPart.next = objPart.prev = 0;
      addRef = false;
    }

    Part &afterPart = part(after);
    NI_ASSERT_TRACE(afterPart.isLinked(), "after isn't included into some ring!");

    objPart.prev = after; part(afterPart.next).prev = obj;
    objPart.next = afterPart.next; afterPart.next = obj;

    NI_ASSERT_TRACE(objPart.isLinked(), "should be linked now");

    if (addRef)
      REF_POLICY::AddRef(obj, &objPart);
  }

  /**
    @brief Insert an object into a ring before the given one

    @param obj Object to insert into a ring
    @param before An object to insert obj before
  */
  static
  void insertBefore(T * obj, T * before)
  {
    NI_VERIFY_TRACE(obj, "ring::insertBefore: Null obj!", return);
    NI_VERIFY_TRACE(before, "ring::insertBefore: Null before!", return);

    bool addRef = true;
    Part &objPart = part(obj);
    if ( objPart.isLinked() )
    {
      NI_ALWAYS_ASSERT_TRACE("obj is already inlcuded into some ring!");
      T * const prev = objPart.prev;
      T * const next = objPart.next;
      part(prev).next = next;
      part(next).prev = prev;
      objPart.next = objPart.prev = 0;
      addRef = false;
    }

    Part &beforePart = part(before);
    NI_ASSERT_TRACE(beforePart.isLinked(), "before isn't included into some ring!");

    objPart.next = before; part(beforePart.prev).next = obj;
    objPart.prev = beforePart.prev; beforePart.prev = obj;

    NI_ASSERT_TRACE(objPart.isLinked(), "should be linked now");

    if (addRef)
      REF_POLICY::AddRef(obj, &objPart);
  }

  /**
    @brief Remove an object from a ring

    @param obj Object to remove

    @see add
  */
  static
  void remove(T * obj)
  {
    NI_VERIFY_TRACE(obj, "ring::remove: Null obj!", return);

    Part &p = part(obj);
    NI_VERIFY_TRACE(p.isLinked(), "isn't included into some ring!", return);

    T * const prev = p.prev;
    NI_VERIFY_TRACE(prev != 0, "invariant", return);

    T * const next = p.next;
    NI_VERIFY_TRACE(next != 0, "invariant", return);

    part(prev).next = next;
    part(next).prev = prev;
    p.next = p.prev = 0;

    //cosmic rays assert
    //NI_ASSERT(!p.isLinked(), "look like equal operation doesn't work quite well");

		REF_POLICY::Release(obj, &p);
  }

  /**
    @brief Remove object if it is in ring else do nothing

    @param obj Object to remove

    @see Remove
  */
  static
  void safeRemove(T *obj)
  {
    NI_VERIFY_TRACE(obj, "invariant", return);
    if(part(obj).isLinked())
    {
      remove(obj);
    }
  }

  /**
    @brief Get first object in ring

    This method returns pointer to first
    object in the ring or last() if ring is empty

    This method is used for iteration through the ring. The standard
    code could look like:
    @code
      Foo * const last = ring.last();
      for (Foo * current = ring.first(); current != last; current = Ring::next(current))
      {
        // Do something with current
      }
    @endcode

    @return Pointer to first object or last() if ring is empty
  */
  T * first() const
  {
    NI_ASSERT_TRACE(m_part.isLinked(), "invariant");
    return m_part.next;
  }

  /**
  @brief Get back object in ring

  This method returns pointer to first
  object in the ring or last() if ring is empty

  This method is used to get last element of ring:
  @code
  Foo * last = ring.back();
  @endcode

  @return Pointer to back object or last() if ring is empty
  */
  T * back() const
  {
    NI_ASSERT_TRACE(m_part.isLinked(), "invariant");
    return m_part.prev;
  }

  /**
    @brief Iterator terminator

    This method returns a pointer to object @em beyond
    last in the ring (name is saved for historical reasons).

    @attention Don't try to access any members of object returned by last()---
      most probably it would lead to nice late-night debugging!

    @return Pointer beyond last element of ring

    @see first
  */
  T * last() const
  {
    return self();
  }

  /**
    @brief Is a ring empty?

    @return true if ring is empty
  */
  bool empty() const
  {
    return first() == last();
  }

  /**
    @brief next element in the ring

    Finds out next element in the ring.

    @note Sure, the object should be included into some ring!

    @param obj An object
    @return Object next to obj

    @see prev
  */
  static
  T * next(T * obj)
  {
    return obj ? part(obj).next : 0;
  };

  static
  T const* next(T const* obj)
  {
    return const_cast<T const*>(obj ? part(obj).next : 0);
  };

  /**
    @brief Previous element in the ring

    Finds out previous element in the ring.

    @note Sure, the object should be included into some ring!

    @param obj An object
    @return Object previous to obj

    @see next
  */
  static
  T * prev(T * obj)
  {
    return part(obj).prev;
  }

  static
  T const * prev(T const * obj)
  {
    return const_cast<T const*>(part(obj).prev);
  }

  /**
    @brief Ring reset

    Resets ring to initial state, setting all parts to initial state too.
  */
  void reset()
  {
    T * const lst = last();
    T * cur = first();
    while (cur != lst)
    {
      T * const nxt = next(cur);
      part(cur).next = part(cur).prev = NULL;
      cur = nxt;
    }
    m_part.prev = m_part.next = self();
  }

  /**
    @brief Ring repair

    Repairs ring if it has a hole (one or more elements with NULL prev or/and next pointers).
    If there are several holes - elements betwen them will be lost.
  */
  void repair()
  {
    T * const lst = last();
    T * cur = first();
    T * lastGoodElement = self();
    while (cur != lst)
    {
      T * const nxt = next(cur);
      if (nxt && prev(cur))
      {
        lastGoodElement = cur;
        cur = nxt;
      }
      else
      {
        break;
      }
    }
    
    if (cur == lst)
      return;

    T * frontLast = lastGoodElement;

    cur = lst;
    lastGoodElement = self();
    do
    {
      T * const prv = prev(cur);
      if (prv && next(cur))
      {
        lastGoodElement = cur;
        cur = prv;
      }
      else
      {
        break;
      }
    } while (cur != frontLast);

    T * backLast = lastGoodElement;

    part(frontLast).next = backLast;
    part(backLast).prev = frontLast;
  }

  /**
    @brief Clear ring using clear functor

    @param e is a functor which must contain void operator()(T *p)
  */
  template<class ERASER>
  void clear(const ERASER &e)
  {
    T * const lst = last();
    T *       cur = first();
    while (cur != lst)
    {
      T * const nxt = next(cur);
      e(cur);
      cur = nxt;
    }
    m_part.prev = m_part.next = self();
  }

  /**
    @brief Get a fake "self" pointer

    @attention Hacky part!

    As I link not parts but instances, I have the following problem: former
    Lock should be of type T. Of course, it's possible to create such a kind
    of instance, but it doesn't smell nice. To bypass this problem I use the
    following hack: I just create a pointer to fake "instance" of T and use
    this pointer in ring. Sorry, guys, but I found no better way. But this
    hack is at least as safe as previous implementation.

    @return "Fake" pointer to lock-object
  */
  T * self() const
  {
    T * const obj = C::obj(&m_part);
    NI_ASSERT_TRACE(&C::part(obj) == &m_part, "sanity check");
    return obj;
  }

private:
  Part m_part; ///< Lock-part of ring

  /**
    @brief Get part of object

    @note utility functions

    @param obj Object to find part of
    @return Reference to part of obj
  */
  static
  Part& part(T * obj)
  {
    NI_ASSERT_TRACE(obj != 0, "NULL isn't allowed");
    return C::part(obj);
  }
  static
  Part& part(T const* obj)
  {
    NI_ASSERT_TRACE(obj != 0, "NULL isn't allowed");
    return C::part(const_cast<T *>(obj));
  }

  // Non-copyable!
  /// @internal
  Ring(Ring const &);
  /// @internal
  Ring& operator = (Ring const &);
};

/**
  @brief Ring class declaration macro

  This macro declares in the current scope @em ringCls class
  that links object by field @em field

  Example of usage:

  @code
  class MyClass
  {
    seDECLARE_RING_CLASS(MyClass, m_myClassPart, MyClassRingClass)
    // Declare actual part
    MyClassRingClass::Part m_myClassPart;
  };
  @endcode

  or, more compactly:
  @code
  class MyClass
  {
    seDECLARE_RING_CLASS(MyClass, m_part, Ring)
    // Declare actual part
    Ring::Part m_part;
  };
  @endcode

  Note that one can define ring @em outside of class (of course,
  in this case @em field should be accessible), but it's not
  recommended.

  @attention The only recommended way to use rings! As implementation
    isn't stable yet, one's better off with using this macro unless really
    needed and you can invest your time to understand all the details.

  @param cls Class to define ring for
  @param field Name of field to link by
  @param ringCls Name of class for ring

  @note ringCls names should be unique inside of the scope

  @see seDECLARE_RING
*/

#if defined(NI_PLATF_LINUX)

#define seDECLARE_RING_CLASS_BASE(cls, field, ringCls, refPolicy) \
template <typename A> struct ring ## _ ## ringCls ## _; \
typedef ::ring::Ring<cls, ring ## _ ## ringCls ## _<int>, refPolicy > ringCls; \
template <typename A> struct ring ## _ ## ringCls ## _ { \
	static typename ringCls::Part& part(cls * obj) { return obj->field; } \
	static cls * obj(typename ringCls::Part const * _part_) { \
	typename ringCls::Part cls::* field##_offset = &cls::field;\
	return reinterpret_cast<cls*>(reinterpret_cast<unsigned char *>(const_cast<typename ringCls::Part *>(_part_)) - *(unsigned char **)(&(field##_offset))/*offsetof(cls, field)*/); \
	} \
};

#else

#if _MSC_VER >= 1400

#define seDECLARE_RING_CLASS_BASE(cls, field, ringCls, refPolicy) \
template <typename A> struct ring ## _ ## ringCls ## _; \
typedef ::ring::Ring<cls, ring ## _ ## ringCls ## _<int>, refPolicy > ringCls;\
template <typename A> struct ring ## _ ## ringCls ## _ { \
	static typename ringCls::Part& part(cls * obj) { return obj->field; } \
	static cls * obj(typename ringCls::Part const * part) { \
	return reinterpret_cast<cls*>((unsigned char*)(part) - offsetof(cls, field)); \
	} \
};

#else

#define seDECLARE_RING_CLASS_BASE(cls, field, ringCls, refPolicy) \
struct ring ## _ ## ringCls ## _; \
typedef ::ring::Ring<cls, ring ## _ ## ringCls ## _, refPolicy> ringCls; \
struct ring ## _ ## ringCls ## _ { \
	static ringCls::Part& part(cls * obj) { return obj->field; } \
	static cls * obj(ringCls::Part const * part) { \
	return reinterpret_cast<cls*>((unsigned char*)(part) - offsetof(cls, field)); \
	} \
};

#endif

#endif

#define seDECLARE_RING_CLASS(cls, field, ringCls) seDECLARE_RING_CLASS_BASE(cls, field, ringCls, ring::DefaultSmartPtrPolicy<cls>)
#define seDECLARE_COBJRING_CLASS(cls, field, ringCls) seDECLARE_RING_CLASS_BASE(cls, field, ringCls, ring::CObjectBasePolicyWithPtr<cls>)
#define seDECLARE_CPTRRING_CLASS(cls, field, ringCls) seDECLARE_RING_CLASS_BASE(cls, field, ringCls, ring::CPtrBasePolicyWithPtr<cls>)

#define seDECLARE_STRONG_RING_CLASS(cls, field, ringCls) seDECLARE_RING_CLASS_BASE(cls, field, ringCls, ring::StrongSTPolicy<cls>)
#define seDECLARE_WEAK_RING_CLASS(cls, field, ringCls) seDECLARE_RING_CLASS_BASE(cls, field, ringCls, ring::WeakSTPolicy<cls>)

/**
  @brief Ring class and part declaration macro

  This macro declares in the current scope @em ringCls class
  that links object by field @em field and the part itself

  Example of usage:

  @code
  class MyClass
  {
    seDECLARE_RING(MyClass, m_myClassPart, MyClassRingClass)
  };
  @endcode

  or, more compactly:
  @code
  class MyClass
  {
    seDECLARE_RING(MyClass, m_part, Ring)
  };
  @endcode

  @note This macro should be used @em inside of class being ringed

  @attention The only recommended way to use rings! As implementation
    isn't stable yet, one's better off with using this macro unless really
    needed and you can invest your time to undertsand all the details.

  @param cls Class to define ring for
  @param field Name of field to link by
  @param ringCls Name of class for ring

  @note ringCls names should be unique inside of the same class

  @see seDECLARE_RING_CLASS
*/
#if defined(NI_PLATF_LINUX)

#define seDECLARE_RING(cls, field, ringCls) \
  seDECLARE_RING_CLASS(cls, field, ringCls); \
  ringCls::Part field;

#define seDECLARE_COBJRING(cls, field, ringCls) \
	seDECLARE_COBJRING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_CPTRRING(cls, field, ringCls) \
	seDECLARE_CPTRRING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_STRONG_RING(cls, field, ringCls) \
	seDECLARE_STRONG_RING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_WEAK_RING(cls, field, ringCls) \
	seDECLARE_WEAK_RING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_RING_T(cls, field, ringCls) \
  seDECLARE_RING_CLASS(cls, field, ringCls); \
  typename ringCls::Part field;

#else
#if _MSC_VER >= 1400

#define seDECLARE_RING(cls, field, ringCls) \
  seDECLARE_RING_CLASS(cls, field, ringCls); \
  ringCls::Part field;

#define seDECLARE_COBJRING(cls, field, ringCls) \
	seDECLARE_COBJRING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_CPTRRING(cls, field, ringCls) \
	seDECLARE_CPTRRING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_STRONG_RING(cls, field, ringCls) \
	seDECLARE_STRONG_RING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_WEAK_RING(cls, field, ringCls) \
	seDECLARE_WEAK_RING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_RING_T(cls, field, ringCls) \
  seDECLARE_RING_CLASS(cls, field, ringCls); \
  typename ringCls::Part field;

#else

#define seDECLARE_RING(cls, field, ringCls) \
  seDECLARE_RING_CLASS(cls, field, ringCls); \
  ringCls::Part field;

#define seDECLARE_COBJRING(cls, field, ringCls) \
	seDECLARE_COBJRING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_CPTRRING(cls, field, ringCls) \
	seDECLARE_CPTRRING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_STRONG_RING(cls, field, ringCls) \
	seDECLARE_STRONG_RING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_WEAK_RING(cls, field, ringCls) \
	seDECLARE_WEAK_RING_CLASS(cls, field, ringCls); \
	ringCls::Part field;

#define seDECLARE_RING_T(cls, field, ringCls) seDECLARE_RING(cls, field, ringCls)

#endif // end if _MSC_VER >= 1400

#endif // end if defined(NI_PLATF_LINUX)
/**
  @brief Ring range

  Range is a convenient tool to iterate through the whole ring.
  The usage is quite simple: to iterate through the ring once
  one had to write the code like follows:

  @code
    Foo * const last = ring.last();
    for (Foo * c = ring.first(); c != last; c = RingClassName::next(c))
    {
      doSomething(c->field);
    }
  @endcode

  And one may forget to prefetch last element of the ring that would lead
  to performance penalty.

  With ranage the same code can be written much shotter and cleaner:

  @code
    for (ring::Range<RingClassName> r(ring); r; ++r)
    {
      doSomething(r->field);
    }
  @endcode

  The code generated by the vc 7.0 is identical

  @note Don't use ranges when removing elements from the ring!

  @param RING Ring class to iterate through
*/
template <class RING, bool FORWARD = true>
  class Range
{
public:
  /**
    @brief Ctor

    @param ring Ring to iterate through
  */
  Range(RING const &ring)
  {
    Set(ring);
  }

  /**
    @brief Setter

    @param ring Ring to iterate through
  */
  void Set(RING const &ring)
  {
    m_current = FORWARD ? ring.first() : RING::prev(ring.last());
    m_last    = ring.last();
  }

  typedef typename RING::Element Value; ///< Shortcut

  /**
    @brief Checks validity of current element

    @return true if all pointer of current element are not NULL
  */
  bool IsValid() const
  {
    return m_current && RING::next(m_current) && RING::prev(m_current);
  }

  /**
    @brief Dereference

    @return Reference to the current object
  */
  Value& operator * () const
  {
    return *m_current;
  }

  /**
    @brief Dereference

    @return Pointer to the current object
  */
  Value * operator -> () const
  {
    return m_current;
  }

  /**
    @brief Move to the next element of ring

    @return Self-reference
  */
  Range& operator ++ ()
  {
    m_current = FORWARD ? RING::next(m_current) : RING::prev(m_current);
    return *this;
  }

  /**
    @brief Is the range finished

    @return true iff isn't finished
  */
  operator bool() const
  {
    return (m_current != m_last);
  }

private:
  Value * m_current; ///< Current element of the range
  Value * m_last; ///< Last element of the range
};

// Removes all elements from a ring
template <class T>
void Clear(T &r)
{
  for (ring::Range<T> it(r); it;)
  {
    if (it.IsValid())
    {
      typename T::Element *p = &(*it);
      ++it;
      T::remove(p);
    }
    else
    {
      NI_ALWAYS_ASSERT_TRACE("ring::Clear: ring is broken!");
      r.repair();
      it.Set(r);
    }
  }
}

// For all elements in ring
template <class T, class F>
void ForAll(T &r, F &f)
{
  for (ring::Range<T> it(r), itPrev(r); it;)
  {
    if (it.IsValid())
    {
      typename T::Element *p = &(*it);
      itPrev = it;
      ++it;
      f(p);
    }
    else
    {
      NI_ALWAYS_ASSERT_TRACE("ring::ForAll: ring is broken!");
      r.repair();
      if (itPrev.IsValid())
      {
        it = itPrev;
        ++it;
      }
      else
        it.Set(r);
    }
  }
}

// Eraser to be used with Ring::clear()
template <class T>
struct DeleteEraser
{
	void operator()(T *p) const { delete p; }
};

} //end namespace ring

#endif   // _SYSTEM_SERING_H_
