/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
** = LIBRARY
**    
**
** = FILENAME
**    MessageBlockFactory_T.h
**
** = DESCRIPTION
**
** = AUTHOR
**    Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_MESSAGEBLOCKFACTORY_H 
#define TERABIT_MESSAGEBLOCKFACTORY_H

#include "IOTERABIT_Export.h"

#include "ace/pre.h"


#include "ace/Synch.h"
#include "ace/Message_Block.h"
//#include "ace/Message_Queue_T.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


namespace Terabit {

/*
 *
 *
 */

class IOTERABIT_Export MessageBlockFactory
{
public:
    enum 
    {
        FLG_MB_SHARED = (ACE_Message_Block::USER_FLAGS << 1)
    };

    virtual ~MessageBlockFactory (void) 
    {}

    virtual ACE_Message_Block *alloc_msg (size_t length) = 0;
    virtual ACE_Message_Block *alloc_msg (size_t length, unsigned long long tag)
    {
      ACE_ASSERT(0);
      return 0;
    };
    virtual void free_msg (ACE_Message_Block * mb) = 0;
};

/*
 *
 *
 */
template <ACE_SYNCH_DECL>
class MessageBlockFactory_T :
    public MessageBlockFactory
{
public:
    enum
    {
       DEF_MSG_SIZE    = 4096,
       DEF_CACHE_SIZE  = 4,
       MAX_CACHE_SIZE  = -1
    };

    MessageBlockFactory_T (
        size_t               initial_cache_size,
        size_t               def_msg_size = DEF_MSG_SIZE,
        size_t               limit = (size_t)MAX_CACHE_SIZE,
        MessageBlockFactory *parent = 0);

    virtual ~MessageBlockFactory_T (void);


    virtual ACE_Message_Block *alloc_msg (size_t length);
    virtual ACE_Message_Block *alloc_msg (size_t length, unsigned long long tag);
    virtual void free_msg (ACE_Message_Block * mb);

    void clear ();

    MessageBlockFactory* get_parent () const;
    MessageBlockFactory* set_parent (MessageBlockFactory* new_parent);

private:
    ACE_SYNCH_MUTEX       mtx_;
    size_t                def_msg_size_;
    size_t                limit_;
    size_t                count_;
    ACE_Message_Block    *mq_;
    MessageBlockFactory  *parent_;
};

//=================================================================
//
//=================================================================

template <ACE_SYNCH_DECL> 
MessageBlockFactory_T<ACE_SYNCH_USE>::MessageBlockFactory_T
     (size_t               initial_cache_size,
      size_t               def_msg_size,
      size_t               limit,
      MessageBlockFactory *parent)
:  mtx_          ()
,  def_msg_size_ (def_msg_size)
,  limit_        (limit)
,  count_        (0)
,  mq_           (0)
,  parent_       (parent)
{
   
    if (initial_cache_size > this->limit_)
    {
        initial_cache_size = this->limit_;
    }

    for (size_t i=0; i < initial_cache_size; ++i)
    {
       ACE_Message_Block *mb = this->alloc_msg (def_msg_size_);
       this->free_msg (mb);
    }
}

template <ACE_SYNCH_DECL> 
MessageBlockFactory_T<ACE_SYNCH_USE>::~MessageBlockFactory_T ()
{
    this->clear ();
}

template <ACE_SYNCH_DECL> 
MessageBlockFactory* 
MessageBlockFactory_T<ACE_SYNCH_USE>::get_parent () const
{
    return this->parent_;
}

template <ACE_SYNCH_DECL> 
MessageBlockFactory* 
MessageBlockFactory_T<ACE_SYNCH_USE>::set_parent (
                        MessageBlockFactory* new_parent)
{
    ACE_ASSERT (this->count_ == 0);
    MessageBlockFactory* ret = this->parent_;
    this->parent_ = new_parent;
    return ret;
}

template <ACE_SYNCH_DECL> 
void
MessageBlockFactory_T<ACE_SYNCH_USE>::clear ()
{
    ACE_Message_Block *mb;
    {
        ACE_GUARD (ACE_SYNCH_MUTEX, guard, this->mtx_);
        mb = this->mq_;
        this->mq_ = 0;
        this->count_ = 0;
    }

    while (mb != 0)
    {
        ACE_Message_Block *tmp = mb;
        mb = tmp->cont ();
        tmp->cont (0);
        if (this->parent_)
        {
            this->parent_->free_msg (tmp);
        }
        else 
        {
            tmp->release ();
        }
    }
}

template <ACE_SYNCH_DECL> 
ACE_Message_Block *
MessageBlockFactory_T<ACE_SYNCH_USE>::alloc_msg (size_t length)
{
    ACE_Message_Block *mb = 0;
    {
        ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, guard, this->mtx_, 0);
        if (this->count_ > 0)
        {
            mb = this->mq_;
            if (mb->size () < length &&
                mb->size (length) < 0)
            {
                mb = 0;
            }
            else
            {
                --this->count_;
                this->mq_ = mb->cont ();
                mb->cont (0);
            }
        }
    }
    
    if (mb == 0)
    {
        if (this->parent_)
        {
            mb = this->parent_->alloc_msg (length);
        }
        else
        {
            ACE_NEW_RETURN (mb, ACE_Message_Block (length), 0);

            // allow message block to cache
            mb->clr_flags(FLG_MB_SHARED);
        }
    }

    if (mb != 0)
    {
        mb->reset ();
    }
    return mb;
}

template <ACE_SYNCH_DECL> 
ACE_Message_Block *
MessageBlockFactory_T<ACE_SYNCH_USE>::alloc_msg (size_t length, unsigned long long tag)
{
  //  метод должен вызываться только с наличием переопределенного аллокатора (т.е. parent_ != 0)
  //  если вызывается с нулевым parent_, то значит соединение уже закрыто
  //  ( parent_ обнуляется в AsynchChannel::check_closure() : this->mb_cache_.set_parent (0); )
  if (!this->parent_)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT ("(%t) %s : parent_ must not be null here. Return zero as result of allocation"), __FUNCTION__));
    return 0;
  }

  ACE_ASSERT(0 == this->count_);

  ACE_Message_Block *mb = 0;
  {
    ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, guard, this->mtx_, 0);
    if (this->count_ > 0)
    {
      mb = this->mq_;
      if (mb->size () < length &&
        mb->size (length) < 0)
      {
        mb = 0;
      }
      else
      {
        --this->count_;
        this->mq_ = mb->cont ();
        mb->cont (0);
      }
    }
  }

  if (mb == 0)
  {
    if (this->parent_)
    {
      mb = this->parent_->alloc_msg (length, tag);
    }
    else
    {
      ACE_NEW_RETURN (mb, ACE_Message_Block (length), 0);

      // allow message block to cache
      mb->clr_flags(FLG_MB_SHARED);
    }
  }

  if (mb != 0)
  {
    mb->reset ();
  }
  return mb;
}

template <ACE_SYNCH_DECL> 
void
MessageBlockFactory_T<ACE_SYNCH_USE>::free_msg (ACE_Message_Block * mb)
{
    {
        ACE_GUARD (ACE_SYNCH_MUTEX, guard, this->mtx_);
        while (mb != 0 && this->count_ < this->limit_)
        {
            ACE_Message_Block *tmp = mb;
            mb = tmp->cont ();

            if (ACE_BIT_ENABLED(tmp->flags (),FLG_MB_SHARED))
            {
                // do not cache shared message block
                tmp->cont (0);
                ACE_Message_Block::release(tmp);
            }
            else
            {
                ++this->count_;
                tmp->cont (this->mq_);
                this->mq_ = tmp;
            }
        }
    }

    if (mb != 0)
    {
        if (this->parent_ != 0)
        {
            this->parent_->free_msg (mb);
        }
        else
        {
            mb->release(mb);
        }
    }
}

}  //namespace Terabit 


#include "ace/post.h"
    
#endif // TERABIT_MESSAGEBLOCKFACTORY_H
