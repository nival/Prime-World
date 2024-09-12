#pragma once

#pragma warning( push )
#pragma warning( disable : 4996)
#include <IOTerabit/TcpChannel.h>
#include <TProactor/Monitor_T.h>
#pragma warning( pop )

namespace naio
{
  class BaseProtocol;

  // *************************************************************
  //   Channel 
  // *************************************************************
  class Channel : public Terabit::TcpChannel
  {
  public:
    Channel  (int id);
    virtual ~Channel (void);

  public:
    //  AsynchChannel interface
    int  activate_protocol (Terabit::Protocol     *protocol,
                            const char   *data,
                            size_t        datalen);

    // 
    virtual void handle_user_operation(const TRB_Asynch_User_Result& result);

  protected:
    naio::BaseProtocol* protocol_;
  };

  // *************************************************************
  //   ChannelFactory 
  // *************************************************************

  template<typename ChannelType>
  class ChannelFactory : public Terabit::AsynchChannelFactory
  {
  public:
      typedef ACE_SYNCH_MUTEX              Mutex;
      typedef ACE_SYNCH_CONDITION          Condition;
      typedef Monitor_T<Mutex,Condition>   Monitor;
      typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
      typedef Guard_Monitor::Save_Guard    Save_Guard;


      ChannelFactory (unsigned int  min_cache_size = 0,
                         unsigned int  max_cache_size = (size_t) -1);
      virtual ~ChannelFactory ();


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
  };

  template <typename ChannelType>
  ChannelFactory<ChannelType>::ChannelFactory (unsigned int  min_cache_size,
                                               unsigned int  max_cache_size)
    : AsynchChannelFactory ()
    , monitor_             ()
    , free_list_           ()
    , min_free_channels_   (0)
    , max_free_channels_   (0)
    , num_channels_        (0)
    , next_id_             (0)
  {
    this->set_pool_size (min_cache_size, max_cache_size);
  }

  template <typename ChannelType>
  ChannelFactory<ChannelType>::~ChannelFactory ()
  {
    Guard_Monitor guard (monitor_);
    this->del_channels (free_list_.size ());
    ACE_ASSERT (this->num_channels_ == 0);
  }

  template <typename ChannelType>
  void
  ChannelFactory<ChannelType>::add_channels (unsigned int count)
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
  ChannelFactory<ChannelType>::del_channels (unsigned int count)
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
  ChannelFactory<ChannelType>::set_pool_size (unsigned int min_cache_size, 
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
  ChannelFactory<ChannelType>::create_channel()
  {
    Terabit::AsynchChannel *channel = 0;
    int            id = 0;
    {
      Guard_Monitor guard (monitor_);

      channel = this->free_list_.pop_front ();
      if (channel != 0)
      {
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
    return channel;
  }

  template <typename ChannelType>
  void
  ChannelFactory<ChannelType>::destroy_channel (Terabit::AsynchChannel *channel)
  {
    if (!channel)
    {
      return;
    }

    channel->reset ();

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
