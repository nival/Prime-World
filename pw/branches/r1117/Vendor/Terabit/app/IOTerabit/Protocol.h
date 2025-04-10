/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
** = LIBRARY
**    
**
** = FILENAME
**    Protocol.h
**
** = DESCRIPTION
**
** = AUTHOR
**    Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_PROTOCOL_H 
#define TERABIT_PROTOCOL_H

#include "IOTerabit/IOTERABIT_Export.h"
#include "TProactor/Double_List_T.h"
#include "TProactor/Monitor_T.h"
#include "ace/SString.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL
class ACE_Addr;
ACE_END_VERSIONED_NAMESPACE_DECL

namespace Terabit {

class AsynchChannel;
class ProtocolFactory;
class MessageBlockFactory;


/**
  * @class Protocol
  * @brief interface that defines the contract between Channel object and
  * concrete protocol handlers. 
  *
  * Protocol is resposible for message parsing and processing.
  * Usually is implemeneted as an event-driven state machine.
  * Once a concrete Protocol implementation has been developed,
  * it will work with any type of Channel object.
  *
  */
class IOTERABIT_Export Protocol : 
    public LinkD_T<Protocol>
{
    friend class AsynchChannel;

public:

    Protocol (ProtocolFactory & factory); 
    virtual ~Protocol (void);

    int  get_log_level (void) const;

    ProtocolFactory&      get_protocol_factory() const;

    virtual MessageBlockFactory  *get_message_block_factory() const;



    virtual void reset () = 0;

private:




    /** @brief Called  when a new connection is attached to the protocol
    *
    *  this is the first method that is called after 
    *  the Protocol object has been constructed. 
    *  It can be considered to be the state machine 
    *  initialization function.
    *  @retval >= 0   success, 
    *  @retval <  0   failure and on_channel_closed () will 
    *                 be called next
    */
    virtual int on_channel_opened (AsynchChannel *channel) = 0;

    /** @brief Called  when a connection is detached from the protocol
    *
    *  The last method that is called by framework.
    *  It is called when framework detects that attatched Channel 
    *  is about to be destroyed or the connection is broken and
    *  it no longer makes sense to work with it. 
    *  After this method is called, 
    *  Protocol should never use this AsynchChannel object. 
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
    virtual int on_write_completed (AsynchChannel *channel);

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
    virtual int on_timeout (AsynchChannel *channel,
                            const void    *arg);

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
    virtual int check_activity (AsynchChannel         *channel,
                                const ACE_Time_Value&  last_op_time);


    ProtocolFactory & factory_;

};


/**
* @interface ProtocolFactory
* @brief ProtocolFactory is abstact interace 
*        designed for creation of Protocol objects 
*
*/
class IOTERABIT_Export ProtocolFactory 
{

public:

    ProtocolFactory (const ACE_TCHAR *name,
                     int              logLevel = 2);
    virtual ~ProtocolFactory ();


    const ACE_TCHAR *get_name (void) const;

    int    get_log_level (void) const;
    void   set_log_level (int level);


    /** @brief   Called by framework when new incoming connection
    *  is successfully accepted or outgoing connection is 
    *  successfully established.
    */
    virtual Protocol *create_protocol (const void *act) = 0;

    /** @brief   Called by framework when Protocol is no longer
    *  used
    */
    virtual void destroy_protocol  (Protocol *protocol) = 0;

    virtual int  validate_connection (bool  success,
                                      const ACE_Addr& remote,
                                      const ACE_Addr& local,
                                      const void *act) = 0;

    virtual MessageBlockFactory * get_message_block_factory () = 0;


private:
    ACE_TString  name_;
    int          log_level_;

}; 

//=====================================================================
//
//=====================================================================
inline ProtocolFactory & 
Protocol::get_protocol_factory() const 
{ 
    return factory_; 
}

inline int 
Protocol::get_log_level() const 
{ 
    return factory_.get_log_level (); 
}

inline const ACE_TCHAR *
ProtocolFactory::get_name () const
{
    return this->name_.c_str ();
}

inline int 
ProtocolFactory::get_log_level() const 
{ 
    return this->log_level_;
}

inline void 
ProtocolFactory::set_log_level(int level) 
{ 
    this->log_level_ = level;
}

}  //namespace Terabit 


#endif // TERABIT_PROTOCOL_H 
