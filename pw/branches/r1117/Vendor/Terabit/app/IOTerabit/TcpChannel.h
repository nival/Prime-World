/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file TcpChannel.h
**   
**  
**  @author Alexander Libman <libman@terabit.com.au>
**  
**
**
**********************************************************************/
#ifndef TERABIT_TCPCHANNEL_H 
#define TERABIT_TCPCHANNEL_H 

#include "IOTerabit/IOTERABIT_Export.h"
#include "IOTerabit/AsynchChannel.h"
#include "TProactor/Monitor_T.h"

namespace Terabit {

// *************************************************************
//   TcpChannel 
// *************************************************************

class IOTERABIT_Export TcpChannel : 
    public AsynchChannel 
{
public:
    TcpChannel  (int id);
    TcpChannel  (int id, unsigned int mb_cache_limit);
    virtual ~TcpChannel (void);

private:

    virtual int  open_impl (ACE_HANDLE handle, bool flg_server);
    virtual int  close_impl ();
    virtual int  start_read_impl (ACE_Message_Block& mb, size_t nbytes);
    virtual int  start_write_impl (ACE_Message_Block& mb, size_t nbytes);
    virtual bool has_specific_events ();
    virtual int  reset_impl ();

    TRB_Asynch_Read_Stream   reader_;
    TRB_Asynch_Write_Stream  writer_;
};

// *************************************************************
//   TcpChannelFactory 
// *************************************************************

class IOTERABIT_Export TcpChannelFactory : 
    public AsynchChannelFactory
{
public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;


    TcpChannelFactory (unsigned int  min_cache_size = 0,
                       unsigned int  max_cache_size = (size_t) -1);
    virtual ~TcpChannelFactory ();


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


#endif // TERABIT_TCPCHANNEL_H
