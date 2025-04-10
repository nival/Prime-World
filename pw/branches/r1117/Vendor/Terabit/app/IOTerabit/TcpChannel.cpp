/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file TcpChannel.cpp
**   
**  
**  @author Alexander Libman <libman@terabit.com.au>
**  
**
**
**********************************************************************/

#include "IOTerabit/TcpChannel.h"
#include "ace/OS_NS_sys_socket.h"

namespace Terabit {

// ***************************************************
// TcpChannel
// ***************************************************
TcpChannel::TcpChannel (int id)
: AsynchChannel (id)
{
}

TcpChannel::TcpChannel (int id, unsigned int mb_cache_limit)
: AsynchChannel (id, mb_cache_limit)
{
}

TcpChannel::~TcpChannel (void)
{
}

bool
TcpChannel::has_specific_events ()
{
    // no extra pending events
    return false;
}

int
TcpChannel::close_impl ()
{
    ACE_HANDLE handle = this->handle ();
    if (handle != ACE_INVALID_HANDLE)
    {
        this->reader_.cancel ();
        this->writer_.cancel ();

        this->reader_.close ();
        this->writer_.close ();

        ACE_OS::closesocket (handle);

        this->handle (ACE_INVALID_HANDLE);
    }
    return 0;
}


int
TcpChannel::open_impl (ACE_HANDLE handle, bool flg_server)
{
    ACE_UNUSED_ARG (flg_server);
    TRB_Proactor *proactor = this->proactor ();

    ACE_ASSERT (this->handle () == ACE_INVALID_HANDLE);
    ACE_ASSERT (proactor != 0);
    
    // take ownership
    this->handle (handle);
 
    if (this->reader_.open(*this, handle, 0, proactor) ==0  &&
        this->writer_.open(*this, handle, 0, proactor) ==0)
    {
        return 0;
    }
    
    return -1;
}

int
TcpChannel::start_read_impl (ACE_Message_Block& mb, size_t nbytes)
{
    if (mb.cont () == 0)
    {
        return this->reader_.read (mb, nbytes);
    }
    return this->reader_.readv (mb, nbytes);
}

int
TcpChannel::start_write_impl (ACE_Message_Block& mb, size_t nbytes)
{
    if (mb.cont () == 0)
    {
        return this->writer_.write_n(mb, nbytes);
    }
    return this->writer_.writev_n (mb, nbytes);
}

int
TcpChannel::reset_impl ()
{
    ACE_ASSERT (this->handle () == ACE_INVALID_HANDLE);
    return 0;
}

// *************************************************************
//   TcpChannelFactory 
// *************************************************************
TcpChannelFactory::TcpChannelFactory (unsigned int  min_cache_size,
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

TcpChannelFactory::~TcpChannelFactory ()
{
    Guard_Monitor guard (monitor_);
    this->del_channels (free_list_.size ());
    ACE_ASSERT (this->num_channels_ == 0);
}

void
TcpChannelFactory::add_channels (unsigned int count)
{
    for (unsigned int i=0; i < count; ++i)
    {
        AsynchChannel *channel = 0;
        ACE_NEW_NORETURN (channel, TcpChannel(next_id_++));
        if (channel == 0)
        {
            break;
        }
        ++this->num_channels_;
        this->free_list_.push_front (channel);
    }
}

void
TcpChannelFactory::del_channels (unsigned int count)
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
TcpChannelFactory::set_pool_size (unsigned int min_cache_size, 
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
TcpChannelFactory::create_channel()
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

    ACE_NEW_NORETURN (channel, TcpChannel(id));
    if (channel == 0)
    {
        Guard_Monitor guard (monitor_);
        --this->num_channels_;
    }
    return channel;
}
     
void 
TcpChannelFactory::destroy_channel (AsynchChannel *channel)
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

