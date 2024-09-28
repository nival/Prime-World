/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file SslChannel.h
**   
**  
**  @author Alexander Libman <libman@terabit.com.au>
**  
**
**
**********************************************************************/
#ifndef TERABIT_SSLCHANNEL_H 
#define TERABIT_SSLCHANNEL_H 

#include "IOTerabit/SSL/IOTERABIT_SSL_Export.h"
#include "IOTerabit/AsynchChannel.h"
#include "TProactor/Monitor_T.h"
#include "TProactor/SSL/SSL_Asynch_Stream.h"


namespace Terabit {

// *************************************************************
//   SslChannel 
// *************************************************************

class IOTERABIT_SSL_Export SslChannel : 
    public AsynchChannel 
{
public:
    SslChannel  (int id);
    virtual ~SslChannel (void);

private:
    virtual void handle_wakeup ();


    virtual int  open_impl (ACE_HANDLE handle, bool flg_server);
    virtual int  close_impl ();
    virtual int  start_read_impl (ACE_Message_Block& mb, size_t nbytes);
    virtual int  start_write_impl (ACE_Message_Block& mb, size_t nbytes);
    virtual bool has_specific_events ();
    virtual int  reset_impl ();

    TRB_SSL_Asynch_Stream   *ssl_stream_;
};

// *************************************************************
//   SslChannelFactory 
// *************************************************************

class IOTERABIT_SSL_Export SslChannelFactory : 
    public AsynchChannelFactory
{
public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;


    SslChannelFactory (unsigned int  min_cache_size = 0,
                       unsigned int  max_cache_size = (size_t) -1);
    virtual ~SslChannelFactory ();


    virtual AsynchChannel*  create_channel();
    virtual void destroy_channel (AsynchChannel *channel);


    void   set_pool_size (unsigned int min_cache_size, 
                          unsigned int max_cache_size);
    
private:
    void   add_channels (unsigned int count);
    void   del_channels (unsigned int count); 

    Monitor             monitor_;
    AsynchChannelList   free_list_;         // pool of free channel for reuse
    unsigned int        min_free_channels_; // min number of channels in the pool
    unsigned int        max_free_channels_; // max number of channels in the pool
    unsigned int        num_channels_;      // current number active and free channels
    unsigned int        next_id_;           // next channel id to assign 


};

}  //namespace Terabit 


#endif // TERABIT_SSLCHANNEL_H
