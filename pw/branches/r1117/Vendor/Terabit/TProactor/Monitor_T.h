/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
** @author Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_MONITOR_T_H
#define TERABIT_MONITOR_T_H

#include /**/ "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/OS_NS_sys_time.h"
#include "ace/Time_Value.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// **********************************************************
//
//
// **********************************************************

template <typename MTX, typename COND>
class Monitor_T
{
public:
    typedef MTX  Mutex;
    typedef COND Condition;
    typedef Monitor_T<MTX, COND> Monitor;

    Monitor_T (): mtx_ (), cond_(mtx_) {}
    ~Monitor_T () {}

    int acquire ()     { return mtx_.acquire();}
    int release ()     { return mtx_.release();}

    int signal ()      { return cond_.signal();}
    int broadcast()    { return cond_.broadcast();} 
    int wait ()        { return cond_.wait(); }
    int wait (ACE_Time_Value * tv, bool flgAbsTime) ;
   
    
private: 
    // copy operations are prohibited
    Monitor_T (const Monitor_T<MTX,COND> & other);
    Monitor_T& operator=(const Monitor_T<MTX,COND> & other);

    Mutex     mtx_;
    Condition cond_;
};

template <typename MTX, typename COND>
inline int
Monitor_T<MTX,COND>::wait (ACE_Time_Value * tv, bool flgAbsTime)
{
    if (!tv)
        return cond_.wait();

    if (flgAbsTime)
        return cond_.wait(tv);

    ACE_Time_Value abs_time = ACE_OS::gettimeofday ();
    abs_time += (*tv);

    return cond_.wait (&abs_time);
}



// **********************************************************
//
//
// **********************************************************

template <typename MON>
class Guard_Monitor_T
{
public:

    typedef typename MON::Mutex     Mutex;
    typedef typename MON::Condition Condition;
    typedef typename MON::Monitor   Monitor;
    typedef Guard_Monitor_T < MON > Guard_Monitor;
    
    Guard_Monitor_T (MON & monitor, bool flgLock = true);
    ~Guard_Monitor_T ();

    bool  locked () const { return locked_; }

    void  acquire   ();
    void  release   ();

    void  signal    ();
    void  broadcast ();
    int   wait      ();
    int   wait      (ACE_Time_Value * tv, bool flgAbsTime);
    
    template <class FUNC>
    void  waitFor (FUNC f);

    class Save_Guard
    {
    public:
        enum Action{ ACQUIRE, RELEASE };

        Save_Guard (Guard_Monitor_T <MON> & guard, Action action);
        ~Save_Guard();

    private:
        // copy operations are prohibited
        Save_Guard (const Save_Guard & other);
        Save_Guard& operator=(const Save_Guard & other);
    
        Guard_Monitor_T<MON> &  guard_;
        bool                    state_;
    };

private: 
    // copy operations are prohibited
    Guard_Monitor_T (const Guard_Monitor_T<MON> & other);
    Guard_Monitor_T& operator= (const Guard_Monitor_T<MON> & other);
   
    Monitor & monitor_;
    bool      locked_;
};
//================================================================
//
//================================================================
template <typename MON> 
inline
Guard_Monitor_T<MON>::Save_Guard::Save_Guard(Guard_Monitor_T<MON> & guard,
                                             Action action)
: guard_ (guard)
, state_ (guard.locked())
{
    if (action == ACQUIRE)
        guard_.acquire ();
    else
        guard_.release ();
}

template <typename MON> 
inline
Guard_Monitor_T<MON>::Save_Guard::~Save_Guard()
{
    if (state_ == guard_.locked())
        return;

    if (state_)
        guard_.acquire ();
    else
        guard_.release ();
}

//================================================================
//
//================================================================
template <typename MON> 
inline
Guard_Monitor_T<MON>::Guard_Monitor_T (MON & monitor, bool flgLock)
: monitor_(monitor)
, locked_ (false)
{
    if (flgLock)
        this->acquire ();
}

template <typename MON>
inline
Guard_Monitor_T<MON>::~Guard_Monitor_T ()
{
    this->release();
}

template <typename MON>
inline void
Guard_Monitor_T<MON>::acquire()
{
    if (!this->locked_)
    {
        monitor_.acquire();
        this->locked_ = true;
    }
}

template <typename MON>
inline void
Guard_Monitor_T<MON>::release()
{
    if (this->locked_)
    {
        monitor_.release();
        this->locked_ = false;
    }
}
template <typename MON>
inline void
Guard_Monitor_T<MON>::signal()
{
    monitor_.signal ();
}

template <typename MON>
inline void
Guard_Monitor_T<MON>::broadcast()
{
    monitor_.broadcast ();
}

template <typename MON>
inline int
Guard_Monitor_T<MON>::wait()
{
    ACE_ASSERT (this->locked_);
    return monitor_.wait ();
}

template <typename MON>
inline int
Guard_Monitor_T<MON>::wait(ACE_Time_Value * tv, bool flgAbsTime)
{
    ACE_ASSERT (this->locked_);
    return monitor_.wait (tv, flgAbsTime);
}

template <typename MON>
template <typename FUNC>
inline void
Guard_Monitor_T<MON>::waitFor (FUNC f)
{
    Save_Guard saver(*this, Save_Guard::ACQUIRE);

    while (! f())
    {
       monitor_.wait ();
    }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* TERABIT_MONITOR_T_H */

