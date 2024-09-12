#pragma once

#include <IOTerabit/TcpChannel.h>
#include "TProactor/Monitor_T.h"

namespace Relay
{

class BaseProtocol;

// *************************************************************
//   BaseChannel 
// *************************************************************
class BaseChannel : public Terabit::TcpChannel
{
public:
    BaseChannel  (int id);
    virtual ~BaseChannel (void);

public:
  //  AsynchChannel interface
  int  activate_protocol (Terabit::Protocol     *protocol,
    const char   *data,
    size_t        datalen);

  // TRB_Handler interface
  virtual void handle_user_operation(const TRB_Asynch_User_Result& result);

protected:
  BaseProtocol* protocol_;
};

// *************************************************************
//   BaseChannelFactory 
// *************************************************************

template<typename ChannelType>
class BaseChannelFactory : public Terabit::AsynchChannelFactory
{
public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;


    BaseChannelFactory (unsigned int  min_cache_size = 0,
                       unsigned int  max_cache_size = (size_t) -1);
    virtual ~BaseChannelFactory ();


    virtual Terabit::AsynchChannel*  create_channel();
    virtual void destroy_channel (Terabit::AsynchChannel *channel);


    void   set_pool_size (unsigned int min_cache_size, 
                          unsigned int max_cache_size);
    
protected:
    void   add_channels (unsigned int count);
    void   del_channels (unsigned int count); 

    Monitor             monitor_;
    Terabit::AsynchChannelList   free_list_;         // pool of free channel for reuse
    unsigned int        min_free_channels_; // min number of channels in the pool
    unsigned int        max_free_channels_; // max number of channels in the pool
    unsigned int        num_channels_;      // current number active and free channels
    unsigned int        next_id_;           // next channel id to assign 

    unsigned int        count_; //  count of allocated channel
};

template <typename ChannelType>
BaseChannelFactory<ChannelType>::BaseChannelFactory (unsigned int  min_cache_size,
                                        unsigned int  max_cache_size)
                                        : AsynchChannelFactory ()
                                        , monitor_             ()
                                        , free_list_           ()
                                        , min_free_channels_   (0)
                                        , max_free_channels_   (0)
                                        , num_channels_        (0)
                                        , next_id_             (0)
                                        , count_               (0)
{
  this->set_pool_size (min_cache_size, max_cache_size);
}

template <typename ChannelType>
BaseChannelFactory<ChannelType>::~BaseChannelFactory ()
{
  Guard_Monitor guard (monitor_);
  this->del_channels (free_list_.size ());
  ACE_ASSERT (this->num_channels_ == 0);
}

template <typename ChannelType>
void
BaseChannelFactory<ChannelType>::add_channels (unsigned int count)
{
  for (unsigned int i=0; i < count; ++i)
  {
    Terabit::AsynchChannel *channel = 0;
    ACE_NEW_NORETURN (channel, ChannelType(next_id_++));
    if (channel == 0)
    {
      break;
    }
    ++this->num_channels_;
    this->free_list_.push_front (channel);
  }
}

template <typename ChannelType>
void
BaseChannelFactory<ChannelType>::del_channels (unsigned int count)
{
  for (unsigned int i=0; i < count; ++i)
  {
    Terabit::AsynchChannel *channel = this->free_list_.pop_front ();
    if (channel == 0)
    {
      break;
    }
    --this->num_channels_;
    delete channel;
  }
}

template <typename ChannelType>
void
BaseChannelFactory<ChannelType>::set_pool_size (unsigned int min_cache_size, 
                                   unsigned int max_cache_size)
{
  Guard_Monitor guard (monitor_);
  if (min_cache_size > 1024)
  {
    min_cache_size = 1024;
  }

  if (max_cache_size < min_cache_size)
  {
    max_cache_size = min_cache_size;
  }

  this->min_free_channels_ = min_cache_size;
  this->max_free_channels_ = max_cache_size;

  unsigned int num_free = free_list_.size ();
  if (num_free < this->min_free_channels_ )
  {
    add_channels (this->min_free_channels_ - num_free);
  }
  else if (num_free > this->max_free_channels_ )
  {
    del_channels (num_free - this->max_free_channels_);
  }
}

template <typename ChannelType>
Terabit::AsynchChannel *
BaseChannelFactory<ChannelType>::create_channel()
{
  Terabit::AsynchChannel *channel = 0;
  int            id = 0;
  {
    Guard_Monitor guard (monitor_);

    channel = this->free_list_.pop_front ();
    if (channel != 0)
    {
      ++count_;
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(ch=%d count_=%d)"), __FUNCTION__, channel->get_id(), count_));
      return channel;
    }
    id = next_id_++;
    ++this->num_channels_;
  }

  ACE_NEW_NORETURN (channel, ChannelType(id));
  if (channel == 0)
  {
    Guard_Monitor guard (monitor_);
    --this->num_channels_;
  }
  else
  {
    ++count_;
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. New connection allocated(ch=%d count_=%d)"), __FUNCTION__, channel->get_id(), count_));
  }

  return channel;
}

template <typename ChannelType>
void
BaseChannelFactory<ChannelType>::destroy_channel (Terabit::AsynchChannel *channel)
{
  if (!channel)
  {
    return;
  }

  channel->reset ();
  --count_;
  ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(ch=%d count_=%d)"), __FUNCTION__, channel->get_id(), count_));

  {
    Guard_Monitor guard (monitor_);
    ACE_ASSERT (this->num_channels_ != 0);
    if (this->free_list_.size () < this->max_free_channels_)
    {
      this->free_list_.push_front (channel);
      return;
    }
    --this->num_channels_;
  }
  delete channel;
}

}
