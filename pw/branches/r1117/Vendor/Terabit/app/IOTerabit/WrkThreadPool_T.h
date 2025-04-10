/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
** = AUTHOR
**   Alexander Libman <libman@terabit.com.au>
**
**
**
**********************************************************************/

#ifndef TERABIT_WRKTHREADPOOL_H
#define TERABIT_WRKTHREADPOOL_H

#include "TProactor/Single_List_T.h"
#include "IOTerabit/BaseThreadPool.h"
#include "IOTerabit/ProducerConsumerQueue_T.h"


namespace Terabit {



/**
 * @class WrkThreadPool_T
 * WrkThreadPool_T worker thread pool
 *
 */


template <typename T>
class WrkThreadPool_T : public BaseThreadPool
{
public:
    class Item :  public LinkS_T <Item>
    {
    public:
        T t_;   
    };

    typedef Single_Queue_T < Item >   ItemQueue;

    typedef ProducerConsumerQueue_T < Item *, 
                                      ItemQueue > JobQueue;

    WrkThreadPool_T (const ACE_TCHAR *name,
                     size_t           low_mark = -1,
                     size_t           high_mark = -1);

    virtual ~WrkThreadPool_T();

    bool   put (T &t);
    void   purge ();

    void   set_cache_size (unsigned int min_items, 
                           unsigned int max_items);

protected:
    virtual int enable_event_loop (void);
    virtual int disable_event_loop (void);
    virtual int run_event_loop (u_int thr_num);


private:
    Item * allocate_item ();
    void   free_item (Item *);

    void add_cache_items (unsigned int count);
    void del_cache_items (unsigned int count);

    JobQueue      job_queue_;
    ItemQueue     free_list_;
    unsigned int  min_free_items_;
    unsigned int  max_free_items_;

};

template <typename T>
WrkThreadPool_T<T>::WrkThreadPool_T (const ACE_TCHAR *name,
                                 size_t           low_mark,
                                 size_t           high_mark)
: BaseThreadPool    (name)
, job_queue_        (low_mark, high_mark, 0)
, free_list_        ()
, min_free_items_   ()
, max_free_items_   ()
{
    this->set_cache_size (low_mark, high_mark);
}

template <typename T>
WrkThreadPool_T<T>::~WrkThreadPool_T (void)
{
    this->stop ();
    this->purge();
}

template <typename T>
int
WrkThreadPool_T<T>::enable_event_loop(void)
{
    job_queue_.activate (JobQueue::READABLE | JobQueue::WRITABLE);
    return 0;
}

template <typename T>
int
WrkThreadPool_T<T>::disable_event_loop(void)
{
    job_queue_.deactivate (JobQueue::READABLE | JobQueue::WRITABLE);
    return 0;
}

template <typename T>
int
WrkThreadPool_T<T>::run_event_loop(u_int /*thr_num*/)
{
    Item *item = 0;

    while (job_queue_.get(item))
    {
        item->t_.execute ();
        this->free_item (item);
        item = 0;
    }
    return 0;
}

template <typename T>
bool
WrkThreadPool_T<T>::put (T &t)
{
    Item *item = this->allocate_item ();
    if (item == 0)
    {
        return false;
    }

    item->t_.set (t);
    bool rc = job_queue_.put (item);
    if (!rc)
    {
        t.set (item->t_);
        this->free_item (item);
    }
    return rc;
}

template <typename T>
void
WrkThreadPool_T<T>::purge ()
{
    Item *item = 0;

    while (job_queue_.pop(item))
    {
        item->t_.cancel ();
        this->free_item (item);
        item = 0;
    }
}

template <typename T>
void
WrkThreadPool_T<T>::add_cache_items (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        Item *item = 0;
        ACE_NEW_NORETURN (item, Item ());
        if (item == 0)
        {
            break;
        }
        this->free_list_.push_front (item);
    }
}

template <typename T>
void
WrkThreadPool_T<T>::del_cache_items (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        Item *item = this->free_list_.pop_front ();
        if (item == 0)
        {
            break;
        }
        delete item;
    }
}

template <typename T>
void
WrkThreadPool_T<T>::set_cache_size (unsigned int min_items, 
                                    unsigned int max_items)
{
   Guard_Monitor guard (this->get_monitor ());

   if (min_items > 1024)
   {
       min_items = 1024;
   }

   if (max_items < min_items)
   {
       max_items = min_items;
   }

   this->min_free_items_ = min_items;
   this->max_free_items_ = max_items;
   
   unsigned int num_free = free_list_.size ();
   if (num_free < this->min_free_items_ )
   {
       add_cache_items (this->min_free_items_ - num_free);
   }
   else if (num_free > this->max_free_items_ )
   {
       del_cache_items (num_free - this->max_free_items_);
   }
}
    

template <typename T>
typename WrkThreadPool_T<T>::Item *
WrkThreadPool_T<T>::allocate_item()
{
    Item *item = 0;
    {
        Guard_Monitor guard (this->get_monitor ());

        item = this->free_list_.pop_front ();
        if (item != 0)
        {
            return item;
        }
    }

    ACE_NEW_NORETURN (item, Item());
    return item;
}

template <typename T>
void 
WrkThreadPool_T<T>::free_item (Item * item) 
{ 
    if (!item)
    {
        return;
    }

    item->t_.reset ();
    {
        Guard_Monitor guard (this->get_monitor ());
        if (this->free_list_.size () < this->max_free_items_)
        {
            this->free_list_.push_front (item);
            return;
        }
    }
    delete item;
}


}  //namespace Terabit 

#endif  // TERABIT_WRKHREADPOOL_H

