/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file SslChannel.cpp
**   
**  
**  @author Alexander Libman <libman@terabit.com.au>
**  
**
**
**********************************************************************/

#include "IOTerabit/SSL/SslChannel.h"
#include "ace/OS_NS_sys_socket.h"

namespace Terabit {

// ***************************************************
// SslChannel
// ***************************************************
SslChannel::SslChannel (int id)
: AsynchChannel (id)
, ssl_stream_   (0)
{
}

SslChannel::~SslChannel (void)
{
    ACE_ASSERT (this->ssl_stream_ == 0);
}

bool
SslChannel::has_specific_events ()
{
    // no extra pending events
    return (this->ssl_stream_ != 0);
}

void
SslChannel::handle_wakeup ()
{
    RefCountPtr tmp (0);
    {
        RefCountGuard guard (*this);

        this->handle (ACE_INVALID_HANDLE);
        this->reset_impl ();
    }

    this->close ();
}

int
SslChannel::close_impl ()
{
    if (this->ssl_stream_ != 0)
    {
        this->ssl_stream_->cancel ();
        this->handle (ACE_INVALID_HANDLE);
    }
    return 0;
}


int
SslChannel::open_impl (ACE_HANDLE handle, bool flg_server)
{
    TRB_Proactor *proactor = this->proactor ();

    ACE_ASSERT (this->ssl_stream_ == 0);
    ACE_ASSERT (this->handle () == ACE_INVALID_HANDLE);
    ACE_ASSERT (proactor != 0);
    
    // take ownership
    this->handle (handle);

    TRB_SSL_Asynch_Stream::Stream_Type type = flg_server ?
        TRB_SSL_Asynch_Stream::ST_SERVER :
        TRB_SSL_Asynch_Stream::ST_CLIENT;
 
    ACE_NEW_NORETURN (this->ssl_stream_, 
                      TRB_SSL_Asynch_Stream (type));


    if (this->ssl_stream_ == 0) 
    {
        ACE_OS::closesocket (handle);
        return -1;
    }

    if (this->ssl_stream_->open(*this, 
                                handle,
                                0,
                                proactor,
                                1) == 0)
    {
        return 0;
    }
    
    delete this->ssl_stream_;
    this->ssl_stream_ = 0;
    return -1;
}

int
SslChannel::start_read_impl (ACE_Message_Block& mb, size_t nbytes)
{
    if (this->ssl_stream_ != 0)
    {
        return this->ssl_stream_->read (mb, nbytes);
    }
    return -1;
}

int
SslChannel::start_write_impl (ACE_Message_Block& mb, size_t nbytes)
{
    if (this->ssl_stream_ != 0)
    {
        return this->ssl_stream_->write (mb, nbytes);
    }
    return -1;
}

int
SslChannel::reset_impl ()
{
    ACE_ASSERT (this->handle () == ACE_INVALID_HANDLE);
    delete this->ssl_stream_;
    this->ssl_stream_ = 0;
    return 0;
}

// *************************************************************
//   SslChannelFactory 
// *************************************************************
SslChannelFactory::SslChannelFactory (unsigned int  min_cache_size,
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

SslChannelFactory::~SslChannelFactory ()
{
    Guard_Monitor guard (monitor_);
    this->del_channels (free_list_.size ());
    ACE_ASSERT (this->num_channels_ == 0);
}

void
SslChannelFactory::add_channels (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        AsynchChannel *channel = 0;
        ACE_NEW_NORETURN (channel, SslChannel(next_id_++));
        if (channel == 0)
        {
            break;
        }
        ++this->num_channels_;
        this->free_list_.push_front (channel);
    }
}

void
SslChannelFactory::del_channels (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        AsynchChannel *channel = this->free_list_.pop_front ();
        if (channel == 0)
        {
            break;
        }
        --this->num_channels_;
        delete channel;
    }
}

void
SslChannelFactory::set_pool_size (unsigned int min_cache_size, 
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

AsynchChannel *
SslChannelFactory::create_channel()
{
    AsynchChannel *channel = 0;
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

    ACE_NEW_NORETURN (channel, SslChannel(id));
    if (channel == 0)
    {
        Guard_Monitor guard (monitor_);
        --this->num_channels_;
    }
    return channel;
}
     
void 
SslChannelFactory::destroy_channel (AsynchChannel *channel)
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

}  //namespace Terabit 

