/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
** = LIBRARY
**    
**
** = FILENAME
**    ProtocolFactory_T.h
**
** = DESCRIPTION
**
** = AUTHOR
**    Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_PROTOCOLFACTORY_T_H 
#define TERABIT_PROTOCOLFACTORY_T_H 

#include "IOTerabit/Protocol.h"
#include "IOTerabit/MessageBlockFactory.h"

namespace Terabit {

/**
 * @class ProtocolFactory_T
 * @brief template class provides simple implementation
 * of ProtocolFactory for protocols T 
 *
 */

template <class PROTOCOL>
class  ProtocolFactory_T : public ProtocolFactory
{
public:
    typedef typename PROTOCOL::Protocol  Protocol;
    typedef Double_List_T < Protocol >   ProtocolList;

    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;

   

    ProtocolFactory_T (const ACE_TCHAR *name,
                       int              log_level = 2,
                       unsigned int     min_cache_size = 0, 
                       unsigned int     max_cache_size = (size_t)-1);
   
    virtual ~ProtocolFactory_T ();
   
    // ProtocolFactory interface
    virtual Protocol * create_protocol(const void *act);

    virtual void destroy_protocol (Protocol * protocol); 

    virtual int  validate_connection (bool  success,
                                      const ACE_Addr &remote,
                                      const ACE_Addr &local,
                                      const void *act);

    virtual MessageBlockFactory * get_message_block_factory ();


    void   set_pool_size (unsigned int min_cache_size, 
                          unsigned int max_cache_size);
    
private:
    void   add_protocols (unsigned int count);
    void   del_protocols (unsigned int count); 

    
    Monitor             monitor_;
    ProtocolList        free_list_;
    unsigned int        min_free_protocols_; // min number of protocols in the pool
    unsigned int        max_free_protocols_; // max number of protocols in the pool
    unsigned int        num_protocols_;      // current number active and free protocols
    MessageBlockFactory_T<ACE_MT_SYNCH> mb_factory_;
};

template <class PROTOCOL>
ProtocolFactory_T<PROTOCOL>::ProtocolFactory_T
                (const ACE_TCHAR *name, 
                 int              log_level,
                 unsigned int     min_cache_size, 
                 unsigned int     max_cache_size)
: ProtocolFactory     (name, log_level) 
, monitor_            ()
, free_list_          ()
, min_free_protocols_ (0)
, max_free_protocols_ (0)
, num_protocols_      (0)
, mb_factory_         (128, // initial number of message blocks
                       (size_t)MessageBlockFactory_T<ACE_MT_SYNCH>::DEF_MSG_SIZE,
                       (size_t)MessageBlockFactory_T<ACE_MT_SYNCH>::MAX_CACHE_SIZE,
                       0)
{
    this->set_pool_size (min_cache_size, max_cache_size);
}

template <class PROTOCOL>
ProtocolFactory_T<PROTOCOL>::~ProtocolFactory_T ()
{
    Guard_Monitor guard (monitor_);
    this->del_protocols (free_list_.size ());
    ACE_ASSERT (this->num_protocols_ == 0);
}

template <class PROTOCOL>
void
ProtocolFactory_T<PROTOCOL>::add_protocols (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        Protocol *protocol = 0;
        ACE_NEW_NORETURN (protocol, PROTOCOL(*this));
        if (protocol == 0)
        {
            break;
        }
        ++this->num_protocols_;
        this->free_list_.push_front (protocol);
    }
}

template <class PROTOCOL>
void
ProtocolFactory_T<PROTOCOL>::del_protocols (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        Protocol *protocol = this->free_list_.pop_front ();
        if (protocol == 0)
        {
            break;
        }
        --this->num_protocols_;
        delete protocol;
    }
}

template <class PROTOCOL>
void
ProtocolFactory_T<PROTOCOL>::set_pool_size (unsigned int min_cache_size, 
                                            unsigned int max_cache_size)
{
   Guard_Monitor guard (monitor_);

   if (min_cache_size > 1024)
   {
       min_cache_size = 1024;
   }

   if (min_cache_size > max_cache_size)
   {
       max_cache_size = min_cache_size;
   }
   

   this->min_free_protocols_ = min_cache_size;
   this->max_free_protocols_ = max_cache_size;
   
   unsigned int num_free = free_list_.size ();
   if (num_free < this->min_free_protocols_ )
   {
       add_protocols (this->min_free_protocols_ - num_free);
   }
   else if (num_free > this->max_free_protocols_ )
   {
       del_protocols (num_free - this->max_free_protocols_);
   }
}
    
template <class PROTOCOL>
MessageBlockFactory *
ProtocolFactory_T<PROTOCOL>::get_message_block_factory ()
{
    return &this->mb_factory_;
}


template <class PROTOCOL>
typename PROTOCOL::Protocol *
ProtocolFactory_T<PROTOCOL>::create_protocol(const void * /*act*/)
{
    Protocol *protocol = 0;
    {
        Guard_Monitor guard (monitor_);

        protocol = this->free_list_.pop_front ();
        if (protocol != 0)
        {
            return protocol;
        }
        ++this->num_protocols_;
    }

    ACE_NEW_NORETURN (protocol, PROTOCOL(*this));
    if (protocol == 0)
    {
        Guard_Monitor guard (monitor_);
        --this->num_protocols_;
    }
    return protocol;
}

template <class PROTOCOL>
void 
ProtocolFactory_T<PROTOCOL>::destroy_protocol (Protocol * protocol) 
{ 
    if (!protocol)
    {
        return;
    }

    protocol->reset ();
    {
        Guard_Monitor guard (monitor_);
        ACE_ASSERT (this->num_protocols_ != 0);
        if (this->free_list_.size () < this->max_free_protocols_)
        {
            this->free_list_.push_front (protocol);
            return;
        }
        --this->num_protocols_;
    }
    delete protocol;
}

template <class PROTOCOL>
int
ProtocolFactory_T<PROTOCOL>::validate_connection (
                     bool             /*success*/,
                     const ACE_Addr & /*remote*/,
                     const ACE_Addr & /*local*/,
                     const void *     /*act*/)
{
     return 0;
}

}  //namespace Terabit 


#endif // TERABIT_PROTOCOLFACTORY_T_H 

