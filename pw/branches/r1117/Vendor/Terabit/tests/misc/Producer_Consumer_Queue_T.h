#ifndef PRODUCER_CONSUMER_QUEUE_T_H
#define PRODUCER_CONSUMER_QUEUE_T_H

#if defined (_MSC_VER)
#pragma once
#endif

#include <list>
#include "ace/Synch.h"
#include "ace/Time_Value.h"


/** @class Producer_Consumer_Queue_T
 *  @author Alexander Libman 
 *
 *  @brief Template implementation of generic queue 
 *  for Producer-Consumer model.
 *
 *  
 * The queue consists of a container of objects, mutex , two conditional variables
 * and two limit numbers HIGHWATERMARK and LOWWATERMARK.
 * Main methods are put() and get()
 *
 * @li Container is collection of objects of type OBJECT.
 * Type OBJECT is a template parameter.

 * @li Container type is defined by template parameter CONTAINTER.
 * It can be any STL container that supports push_back(), front() and pop_front()
 * methods. There is a special conatiner DummyContainer<OBJECT>, which is doing
 * nothing for test purposes. This is default type.
 * You can use also std::deque<OBJECT>, std::list<OBJECT>,etc.
 * 
 *
 * @li Mutex is used to protect operations with container and it is required 
 * for wait operation on conditional variables. mutex type is template parameter
 * MUTEX
 * 
 * @li Condition type is defined by template parameter CONDITION.
 * @li The first condition cond_empty_ signals consumers when 
 * there are waiting consumers and container becomes not empty.
 *
 * @li The second condition cond_full_ signals producers when 
 * there are waiting producers and container becomes not full.
 * When the number of messages in the queue reaches HIGHWATERMARK
 * level, producers will be blocked on put() operation.
 * When the number of messages in the queue goes down from HIGHWATERMARK
 * below LOWWATERMARK level, producers will be woken up.
 *
 * @par There are two strategies how to wakeup waiting producers/consumers:
 * @li Strategy 1: once broadcast all waiters and reset overflow/underflow count
 * @li Strategy 2: notify one waiter and decremenet overflow/underflow count
 * 
 * Compile with macro BROADCAST_STRATEGY  to select Strategy 1
 *
 */

template < class OBJECT,
           class CONTAINER = std::list<OBJECT>,
           class MUTEX = ACE_SYNCH_MUTEX, 
           class CONDITION = ACE_SYNCH_CONDITION >
class Producer_Consumer_Queue_T
{

public:
    static const size_t  DEFAULT_HIGH_MARK = 1024*16;
    static const size_t  DEFAULT_LOW_MARK  = 1024;

    enum ActiveFlags 
    {
        READABLE = 0x0001,
        WRITABLE = 0x0002
    };

    /** @Constructor
     *  @param low_mark  defines how many objects can remain in the queue
     *  when it is considered not full
     *  @param high_mark  defines how many objects we can put into the queue
     *  before it is considered  full
     */
    Producer_Consumer_Queue_T (size_t low_mark  = DEFAULT_LOW_MARK, 
                size_t high_mark = DEFAULT_HIGH_MARK,
                int active_flags = READABLE |WRITABLE);

    /// Destructor
    virtual ~Producer_Consumer_Queue_T ()
    {}

    /** @brief  stop/deactivate queue
     *
     *  this method prevents all insertions into queue
     *  and wakeups all waiters (both Producers and Consumers)
     *  to notify about request to stop
     */
    int   deactivate (int flags);

    int   activate (int flags);

    int   get_active_flags () const;
    bool  is_readable () const;
    bool  is_writable () const;

    size_t size  () const;
    bool   empty () const { return (size () == 0);}
    

    /** @brief Put object into the queue (Producer side)
     *  
     * Method can block user if queue is full
     * @retval true  we have successfuly put the object
     * @retval false request to stop work was issued
     */
    bool  put  (const OBJECT & obj, const ACE_Time_Value * tv=0);

    /** @brief Get object from the queue (Consumer side)
     *  
     * Method can block user if queue is empty
     * @retval true we have got an object
     * @retval false request to stop work was issued
     */
    bool  get  (OBJECT & obj, const ACE_Time_Value * tv=0); 

    bool  pop  (OBJECT & obj); 

    /// Get total number of "Put" operations for this queue
    size_t get_total_get () const { return total_get_items_;}

    /// Get total number of "Get" operations for this queue
    size_t get_total_put () const { return total_put_items_;}

    /// Get total number of signals sent to producers
    size_t get_num_full_signals () const { return num_full_signals_;}

    /// Get total number of signals sent to consumers
    size_t get_num_empty_signals () const { return num_empty_signals_;}


private:
    
    /// Private method - called to wake up waiting consumer
    void notify_consumer ();

    /// Private method - called to wake up blocking producer
    void notify_producer ();

    /// noncopyable class
    Producer_Consumer_Queue_T (const Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION> & other);
    Producer_Consumer_Queue_T& operator=(const Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION> & other);


    /// Mutex to protect integrity of queue 
    mutable MUTEX   mtx_;

    /// condition - signalled when queue becomes not empty
    CONDITION       cond_empty_;

    /// how many times cond_empty_ has been signalled
    size_t          num_empty_signals_;

    /// condition - signalled when queue becomes not full
    CONDITION       cond_full_;

    /// how many times cond_full_ has been signalled
    size_t          num_full_signals_;

    /// FIFO for consumer-producer
    CONTAINER       queue_;              

    /// current number of items in queue
    size_t          num_items_;          

    /// current number of consumer waiters
    size_t          nc_waiters_; 
    
    /// current number of producer waiters
    size_t          np_waiters_;         

    /// total items that were sent
    size_t          total_put_items_;

    /// total items that were extracted
    size_t          total_get_items_;    

    /// low water-mark limit to resume producers
    size_t          low_mark_;           

    /// hogh water-mark limit to suspend producers
    size_t          high_mark_;          

    /// overflow count - number produsers to wakeup
    size_t          count_overflow_;

    /// underflow count - number consumers to wakeup
    size_t          count_underflow_;

    /// flags to stop
    int            active_flags_;        
};

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION >
inline 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::Producer_Consumer_Queue_T (size_t low_mark,
                                                           size_t high_mark,
                                                           int    active_flags)
: mtx_               ()
, cond_empty_        (mtx_)
, num_empty_signals_ (0)
, cond_full_         (mtx_)
, num_full_signals_  (0)
, queue_             ()
, num_items_         (0)
, nc_waiters_        (0)
, np_waiters_        (0)
, total_put_items_   (0)
, total_get_items_   (0)
, low_mark_          (low_mark)
, high_mark_         (high_mark)
, count_overflow_    (0)
, count_underflow_   (0)
, active_flags_      (active_flags)
{
    if (low_mark_ > high_mark_)
    {
        low_mark_ = high_mark_;
    }
}
template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline size_t
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::size() const
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, 0);
    return num_items_;
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline int
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::get_active_flags () const
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, 0);
    return active_flags_;
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline bool 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::is_readable () const
{
    return ACE_BIT_ENABLED (get_active_flags (), READABLE);
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline bool 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::is_writable () const
{
    return ACE_BIT_ENABLED (get_active_flags (), WRITABLE);
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline int
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::activate (int flags)
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, 0);
    ACE_SET_BITS (active_flags_ , flags);

    cond_empty_.broadcast();
    cond_full_.broadcast ();

    return active_flags_;
}


template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline int
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::deactivate(int flags)
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, 0);
    ACE_CLR_BITS (active_flags_ , flags);

    cond_empty_.broadcast();
    cond_full_.broadcast ();

    return active_flags_;
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline bool 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::pop(OBJECT & obj)
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, false);

    if (num_items_ != 0)  
    {
        obj = queue_.front();
        queue_.pop_front();
        --num_items_;
        ++total_get_items_;

        notify_producer ();
        return true;
    }
    
    return false;
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline bool 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::get(OBJECT & obj,
                                                   const ACE_Time_Value * tv)
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, false);

    int rc = 0;

    while (rc==0 && ACE_BIT_ENABLED(active_flags_, READABLE))
    {
        if (num_items_ != 0)  
        {
            obj = queue_.front();
            queue_.pop_front();
            --num_items_;
            ++total_get_items_;

            notify_producer ();
            return true;
        }

        ++count_underflow_ ; 
        ++nc_waiters_;
        rc = cond_empty_.wait(mtx_, tv);
        --nc_waiters_;
    }

    if (rc == 0)
    {
        notify_producer ();
    }
    else
    {
        --count_underflow_ ; 
    }
        
    return false;
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline void 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::notify_producer ()
{
    if ((count_overflow_ != 0) && (num_items_ <= low_mark_))
    {
        // we are below LOWWATERMARK now
        if (np_waiters_ !=0)
        {
            // and there are some waiting producers 

            ++num_full_signals_;

#if defined (BROADCAST_STRATEGY)
            // Stategy 1:
            // if there were overflow,  
            // reset overflow count and broadcast all producers
            // 
            count_overflow_ = 0;
            cond_full_.broadcast();
#else

            // Strategy 2:
            // decrement overflow count and wakeup one producer
            //
            --count_overflow_;
            cond_full_.signal();
#endif
        }
    }
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline bool 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::put(const OBJECT & obj, 
                                                   const ACE_Time_Value *tv)
{
    ACE_GUARD_RETURN (MUTEX, guard, mtx_, false);

    int rc = 0;

    while (rc==0 && ACE_BIT_ENABLED (active_flags_, WRITABLE))
    {
        if (num_items_ <= high_mark_)
        {
            queue_.push_back (obj);
            ++num_items_;
            ++total_put_items_;

            notify_consumer();
            return true;
        }

        ++count_overflow_;
        ++np_waiters_;
        rc = cond_full_.wait (mtx_, tv);
        --np_waiters_;
    }

    if (rc == 0)
    {
        notify_consumer ();
    }
    else
    {
        --count_overflow_;
    }
    return false;
}

template <class OBJECT, class CONTAINER, class MUTEX, class CONDITION>
inline void 
Producer_Consumer_Queue_T <OBJECT,CONTAINER,MUTEX,CONDITION>::notify_consumer()
{
    if ((count_underflow_ != 0) && (num_items_ != 0))
    {
        // we have some messages in queue
        // now check if we have any waiters

        if (nc_waiters_ !=0)
        {
            // and there are some waiting consumers
            ++num_empty_signals_;
         
#if defined(BROADCAST_STRATEGY)
            // Stategy 1:
            // if there were underflow,  
            // reset underflow count and broadcast all consumers
            // 
            count_underflow_ = 0;
            cond_empty_.broadcast();
#else
            // Strategy 2:
            // decrement underflow count and wakeup one consumer
            //
            --count_underflow_;
             cond_empty_.signal();
#endif
        }
    }
}

#endif // PRODUCER_CONSUMER_QUEUE_T_H
