/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
** = LIBRARY
**    
**
** = FILENAME
**    RefCntProtocol.h
**
** = DESCRIPTION
**
** = AUTHOR
**    Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_REFCNTPROTOCOL_H 
#define TERABIT_REFCNTPROTOCOL_H

#include "IOTerabit/IOTERABIT_Export.h"
#include "IOTerabit/Protocol.h"
#include "IOTerabit/AsynchChannel.h"
#include "IOTerabit/RefCount_T.h"

namespace Terabit {

/**
  * @class RefCntProtocol
  * @brief interface that defines the contract between Channel object and
  * concrete protocol handlers. 
  *
  * RefCntProtocol is resposible for message parsing and processing.
  * Usually is implemeneted as an event-driven state machine.
  * Once a concrete RefCntProtocol implementation has been developed,
  * it will work with any type of Channel object.
  *
  */
class IOTERABIT_Export RefCntProtocol : 
    public RefCount ,
    public Protocol
{

public:

    RefCntProtocol (ProtocolFactory & factory); 
    virtual ~RefCntProtocol (void);

    int  enable_read ();
    int  disable_read ();
    int  enable_write_notifications ();
    int  disable_write_notifications ();
    int  write (const iovec *iov, int iov_cnt);
    int  write (const char *data, size_t datalen);
    int  close (); 


    virtual int  on_channel_up   (AsynchChannel *channel) = 0;
    virtual void on_channel_done (AsynchChannel *channel) = 0;
    virtual void on_reset () = 0;

private:

    /// @brief original RefCount::destroy method is overriden. 
    /// to delegate destruction to the factory
    virtual void free  ();


    virtual void reset ();


    /** @brief Called  when a new connection is attached to the protocol
    *
    *  this is the first method that is called after 
    *  the RefCntProtocol object has been constructed. 
    *  It can be considered to be the state machine 
    *  initialization function.
    *  @retval >= 0   success, for server side channels
    *                 it returns how many bytes has been consumed
    *                 from the 'data'. The returned value should be
    *                 equal or less than 'length'. 
    *  @retval <  0   failure and on_channel_closed () will 
    *                 be called next
    */
    virtual int on_channel_opened (AsynchChannel *channel);
 
    /** @brief Called  when a connection is detached from the protocol
    *
    *  The last method that is called by framework.
    *  It is called when framework detects that attatched Channel 
    *  is about to be destroyed or the connection is broken and
    *  it no longer makes sense to work with it. 
    *  After this method is called, 
    *  RefCntProtocol should never use this AsynchChannel object. 
    *  This can be considered part of the transition to the final state,
    *  and it can be called at any point in time.
    */
    virtual void on_channel_closed (AsynchChannel *channel);

    /** @brief  Called when read operation is finished
    *
    *  this method is called when a previously started 
    *  asynchronous read operation is finished.
    *  @param data   address of buffer containing data
    *  @param length the length of data
    *  @retval >= 0   success, it returns how many bytes has been 
    *                 consumed from the 'data' buffer.  The returned
    *                 value should be equal or less than 'length'. 
    *  @retval <  0   failure and on_channel_closed () will 
    *                 be called next
    */
    virtual int on_read_completed (AsynchChannel *channel,
                                   const char    *data,
                                   size_t         length) = 0;

    /** @brief  Called all queued write operations are finished,
    *          i.e. output queue is empty and there is no more
    *          pending write operation. 
    *  This method is called only if AsynchChannel works in
    *  mode MODE_WRITE_NOTIFICATIONS. See
    *  AsynchChannel::enable_write_notifications ()
    *  AsynchChannel::disable_write_notifications ()
    */
    //virtual int on_write_completed (AsynchChannel *channel);

    /** @brief  Called when timer is expired
    *  
    *  this method is called when previously started
    *  asynchronous timer is expired. 
    *  @param arg  has the same value that was passed
    *              to the AsynchChannel::start_timer () call.
    *
    *  @retval >= 0   success, continue state machine
    *  @retval <  0   failure and on_channel_closed () will 
    *                 be called next
    *
    *  The default implementation returns 0.
    */
    //virtual int on_timeout (AsynchChannel *channel,
    //                        const void    *arg);

    /** @brief   Called when inactivity timeout is expired
    *
    *  the "health-check" method that is periodically called
    *  on expiration of framework's "watch dog" interval.
    *  @param last_op_time contains the time of completion
    *                      of the last I/O operation on the channel.
    *
    *  @retval >= 0   success, continue state machine
    *  @retval <  0   failure and on_channel_closed () will 
    *                 be called next
    *
    *  The default implementation returns 0.
    */
    //virtual int check_activity (AsynchChannel         *channel,
    //                            const ACE_Time_Value&  last_op_time);

private:
    AsynchChannel *channel_;
    RefCountPtr    self_;
};
typedef RefCountPtr_T<RefCntProtocol>  RefCntProtocolPtr;

//==============================================================
//
//==============================================================
inline int
RefCntProtocol::enable_read ()
{
    RefCountGuard guard (*this);
    return channel_ ?  channel_->enable_read () : -1;
}

inline int  
RefCntProtocol::disable_read ()
{
    RefCountGuard guard (*this);
    return channel_ ?  channel_->disable_read () : -1;
}

inline int
RefCntProtocol::enable_write_notifications ()
{
    RefCountGuard guard (*this);
    return channel_ ?  channel_->enable_write_notifications () : -1;
}

inline int
RefCntProtocol::disable_write_notifications ()
{
    RefCountGuard guard (*this);
    return channel_ ?  channel_->disable_write_notifications () : -1;
}

inline int 
RefCntProtocol::write (const iovec *iov, int iov_cnt)
{
    RefCountGuard guard (*this);
    return channel_ ?  channel_->start_write (iov, iov_cnt) : -1;
}

inline int  
RefCntProtocol::write (const char *data, size_t datalen)
{
    RefCountGuard guard (*this);
    return channel_ ?  channel_->start_write (data, datalen) : -1;
}

typedef RefCountPtr_T<RefCntProtocol>   RefCntProtocolPtr;


}  //namespace Terabit 


#endif // TERABIT_REFCNTPROTOCOL_H 
