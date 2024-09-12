#ifndef _REFCNT_OBJECT_H_
#define _REFCNT_OBJECT_H_

#if 0
// **********************************************************
// includes

// **********************************************************
// class

/**
  @brief Implement reference counting

  This class implements reference counter. All objects that wants to use
  reference counter technique should inherit from this class. 

  When class instance is used #addRef() method should be called. 
  Killing of the instance should be performed via #release() method call.

  <B>@anchor refcntobj_using_example Example of usage</B>
  Suppose we have class seSomeClass and we want it to support reference counter.
  To do this we need to inherit it from seRefCountObject. Suppose also we have
  class seSomeClassUser with field m_pSome and method 
  seSomeClassUser::setSome(seSomeClass *pSome). Lets look into this method.
  @code
   seVoid seSomeClassUser::setSome(seSomeClass *pSome)
   {
     // Kill previous class instance
     if (m_pSome != NULL)
       m_pSome->release();
     // Copy pointer
     m_pSome = pSome;
     // Increase reference counter
     if (m_pSome != NULL)
       m_pSome->addRef();
   }
  @endcode
  In this case seSomeClassUser is responsible for the m_pSome deletion.
  So the usage of this method can be:
  @code
   seSomeClassUser *pUser;
   seSomeClass     *pSome;
   ...
   // Read some 
   ...
   // Set 'some' to the 'user'
   pUser->setSome(pSome);
   // Release pSome pointer. We don't needed it - object will be killed
   // on seSomeClassUser deletion.
   pSome->release(); 
   pSome = NULL;
   ...
  @endcode
 */
class RefCountObject
{
protected:
  mutable volatile LONG m_nRefCount;

public:
  /// Default constructor
  RefCountObject(): m_nRefCount(1) {}

protected:
  virtual ~RefCountObject() 
  {
    // Check not referenced or not manual delete
    //NI_ASSERT(m_nRefCount == 0, "Invalid reference count at delition stage");
		// @BVS@HACKED FOR NOW
  }

public:
  /**
   * @brief   Add reference to <I>this</I>.
   * @author  BVS
   */
  void AddRef() const
  {
    InterlockedIncrement( &m_nRefCount );
  }

  /**
   * @brief   Release this
   *
   * This method decreases reference counter and releases <I>this</I> 
   * if this counter becomes zero.
   *
   * @note : condition changed to m_nRefCount == 0
   *  to escape double deletion problem. Sure, it can arise only
   *  in multi-threading environment and should be handled
   *  more carefully, so regard it as multi-threading for poors :)
   *
   *  The order (first decrement, then ASSERT) was changed intentionally
   *  to ease debugging (otherwise ASSERT may not alarm dangerous cases:
   *  concurrent threads might pass the check and decrement the counter later)
   *
   * @author  BVS
   */
  void Release() const
  {
    LONG count = InterlockedDecrement( &m_nRefCount );
    NI_ASSERT( count >= 0, "According to ref counting this object is already deleted");
    if ( !count )
    {
      delete this;
    }
  }

  /**
   * @brief   Release this as field of a class
   *
   * This method decreases reference counter, but not releases <I>this</I> 
   *
   * @author  BVS
   */
  void ReleaseAsField()
  {
		NI_ASSERT(m_nRefCount >= 0, "According to ref counting this object is already deleted");
    m_nRefCount--;
  }

  /**
   * @brief   Get number of references on object
   *
   * @return  Return number of references
   * @author  Moroz
   */
  int getRefCount() const { return m_nRefCount; }
};

/**
  @brief    Safety add reference to the object
  @see      safeRelease
  @todo     This method must be removed 
*/
inline void SafeAddRef(RefCountObject const *o)
{
  if (o != NULL)
    o->AddRef();
}

/**
  @brief    Safety release the object
  @see      safeAddRef
  @todo     This method must be removed 
*/
inline void SafeRelease(RefCountObject const *o)
{
  if (o != NULL)
    o->Release();
}

#endif //if 0

#endif // _REFCNT_OBJECT_H_

