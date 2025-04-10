/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
** = LIBRARY
**    
**
** = FILENAME
**
** = DESCRIPTION
**
** = AUTHOR
**    Alexander Libman <libman@terabit.com.au>**  
**
**********************************************************************/
#ifndef TERABIT_REFCOUNT_T_H 
#define TERABIT_REFCOUNT_T_H 

#include /**/ "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "ace/Synch_T.h"

#include <algorithm>
#include <cassert>
#include <typeinfo>


namespace Terabit {


template <typename REFCOUNT> class RefCountPtr_T;

/**
  * @class RefCount_T
  * @brief template class - MT safe reference count
  *        base class for intrusively ref. counted objects.
  *        It has three states:
  *        0     - object just created and ready to use
  *        N > 0 - object is kept by N references
  *        -1    - object is disposed
  */
template <class LOCK, class TYPE>
class RefCount_T  
{
public:
    typedef LOCK  Mutex;
    typedef TYPE  Type;

    template <typename REFCOUNT> friend class RefCountPtr_T;

    class Guard;
    class SaveGuard;

    friend class Guard;


    RefCount_T (TYPE val = 0);
    
    TYPE    set (TYPE val=0);
    TYPE    value ();

    class Guard 
    {
    public:
        friend class SaveGuard;

        Guard  (RefCount_T<LOCK,TYPE> & ref_count);
        ~Guard ();

    private: 
        void  acquire ();
        void  release ();
        // copy operations are prohibited
        Guard (const Guard & other);
        Guard& operator= (const Guard & other);
   
        RefCount_T<LOCK,TYPE> & ref_count_;
        bool                    locked_;
    };

    class SaveGuard
    {
    public:
        enum Action { ACQUIRE, RELEASE };

        SaveGuard (Guard & guard, Action action);
        ~SaveGuard();

    private:
        // copy operations are prohibited
        SaveGuard (const SaveGuard & other);
        SaveGuard& operator= (const SaveGuard & other);
    
        Guard &  guard_;
        bool     old_state_;
    };

protected:
    virtual ~RefCount_T();

private:    
    // called when reference count drops to 0 value
    virtual void free () = 0;

 
    ///  not copyable
    RefCount_T (const RefCount_T<LOCK,TYPE> & other);
    RefCount_T & operator= (const RefCount_T<LOCK,TYPE> & other);

    
    TYPE      add_ref ();
    TYPE      dec_ref ();

    TYPE      add_ref_i ();
    TYPE      dec_ref_i ();

    LOCK      lock_;
    TYPE      count_;
};

//=========================================================
//
//=========================================================

template <class LOCK, class TYPE>
inline 
RefCount_T<LOCK,TYPE>::RefCount_T (TYPE value)
: lock_  ()
, count_ (value)
{
}

template <class LOCK, class TYPE>
inline 
RefCount_T<LOCK,TYPE>::~RefCount_T () 
{
    assert (count_ <= 0);
}

template <class LOCK, class TYPE>
inline TYPE
RefCount_T<LOCK,TYPE>::add_ref ()
{
    Guard guard(*this);
    return add_ref_i ();
}

template <class LOCK, class TYPE>
inline TYPE
RefCount_T<LOCK,TYPE>::add_ref_i ()
{
    assert (this->count_ >= 0);
    return ++this->count_;
}

template <class LOCK, class TYPE>
inline TYPE
RefCount_T<LOCK,TYPE>::dec_ref ()
{
    TYPE rc;
    {
        Guard guard(*this);
        rc = dec_ref_i ();

        if (rc != 0)
            return rc;

        rc = -1;
    }

    this->free ();
    return rc;
}

template <class LOCK, class TYPE>
inline TYPE
RefCount_T<LOCK,TYPE>::dec_ref_i ()
{
    assert (this->count_ > 0);
    return  --this->count_;
}

template <class LOCK, class TYPE>
inline TYPE
RefCount_T<LOCK,TYPE>::set (TYPE value)
{
    Guard guard(*this);
    assert (this->count_ <= 0);
    this->count_ = value;
    return this->count_;
}


template <class LOCK, class TYPE>
inline TYPE
RefCount_T<LOCK,TYPE>::value ()
{
    Guard guard(*this);
    return this->count_;
}

//=========================================================
//
//=========================================================

template <class LOCK, class TYPE>
inline 
RefCount_T<LOCK,TYPE>::Guard::Guard (RefCount_T<LOCK,TYPE> & ref_count)
: ref_count_ (ref_count)
, locked_    (false)
{
    this->acquire ();
}

template <class LOCK, class TYPE>
inline 
RefCount_T<LOCK,TYPE>::Guard::~Guard ()
{
    this->release();
}
template <class LOCK, class TYPE>
inline void
RefCount_T<LOCK,TYPE>::Guard::acquire()
{
    if (!this->locked_)
    {
        ref_count_.lock_.acquire();
        this->locked_ = true;
    }
}

template <class LOCK, class TYPE>
inline void
RefCount_T<LOCK,TYPE>::Guard::release()
{
    if (this->locked_)
    {
        ref_count_.lock_.release();
        this->locked_ = false;
    }
}

//=========================================================
//
//=========================================================

template <class LOCK, class TYPE>
inline
RefCount_T<LOCK,TYPE>::SaveGuard::SaveGuard (Guard & guard,
                                             Action action)
: guard_     (guard)
, old_state_ (guard.locked_)
{
    if (action == ACQUIRE)
        guard_.acquire ();
    else
        guard_.release ();
}

template <class LOCK, class TYPE>
inline
RefCount_T<LOCK,TYPE>::SaveGuard::~SaveGuard ()
{
    if (old_state_)
        guard_.acquire ();
    else
        guard_.release ();
}

/**
  * @class RefCountPtr_T
  * @brief template class - smart reference counted pointer
  *        to the RefCount_T objects
  *
  *
  */
template <typename REFCOUNT>
class RefCountPtr_T
{
public :
 
    RefCountPtr_T (REFCOUNT * p = 0)
    : p_ (p)
    {
        if (p_)
            p_->add_ref();
    }
        
    RefCountPtr_T (const RefCountPtr_T & other )
    : p_ (other.p_ )
    {
        if (p_)
            p_->add_ref();
    }

    template <class SUB_REFCOUNT>
    RefCountPtr_T (const RefCountPtr_T<SUB_REFCOUNT> & other )
    : p_ (other.get())
    {
        if (p_)
            p_->add_ref();
    }
    

    virtual ~RefCountPtr_T()
    {
        if (p_ != 0)
            p_->dec_ref ();
    }

    void swap (RefCountPtr_T<REFCOUNT> & other )
    {
        std::swap(p_, other.p_ );
    }


    bool operator==(REFCOUNT * p) const { return p_ == p; }
    bool operator!=(REFCOUNT * p) const { return p_ != p; }


    RefCountPtr_T<REFCOUNT> & operator=(REFCOUNT * p)
    {
        RefCountPtr_T tmp(p);
        tmp.swap(*this);
        return *this;
    }

    RefCountPtr_T<REFCOUNT> &  operator=(const RefCountPtr_T<REFCOUNT> & other) 
    {
        RefCountPtr_T tmp(other);
        tmp.swap(*this);
        return *this;
    }

    template <class SUB_REFCOUNT>
    RefCountPtr_T<REFCOUNT> &  operator=(const RefCountPtr_T<SUB_REFCOUNT> & other) 
    {
        RefCountPtr_T tmp(other);
        tmp.swap(*this);
        return *this;
    }


    REFCOUNT * get ()       const { return p_; }
    REFCOUNT * operator->() const { return p_; }
    REFCOUNT & operator* () const { return *p_; }

    operator REFCOUNT *       () const { return p_; }
    operator const REFCOUNT * () const { return p_; }

    operator bool () const { return p_ != 0; }
    bool operator !() const     { return p_ == 0; }

private:
    REFCOUNT * p_;
};

template <class R1, class R2>
bool operator==(const RefCountPtr_T<R1> & r1, const RefCountPtr_T<R2> & r2)
{
    return r1.get() == r2.get();
}

template <class R1, class R2>
bool operator!=(const RefCountPtr_T<R1> & r1, const RefCountPtr_T<R2> & r2)
{
    return r1.get() != r2.get();
}

//----------------------------------------------------------
//
//----------------------------------------------------------
typedef RefCount_T<ACE_SYNCH_MUTEX,long>  RefCount;
typedef RefCountPtr_T<RefCount>           RefCountPtr;
typedef RefCount::Guard                   RefCountGuard;
typedef RefCount::SaveGuard               RefCountSaveGuard;

}  //namespace Terabit 



#include /**/ "ace/post.h"
#endif /* TERABIT_REFCOUNT_T_H */

