/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**
** = FILENAME
**    AsynchChannel.h
**
** = DESCRIPTION
**
** = AUTHOR
**    Alexander Libman <libman@terabit.com.au>
**
**********************************************************************/

#ifndef TERABIT_ASYNCHCHANNEL_H
#define TERABIT_ASYNCHCHANNEL_H

#include "IOTerabit/IOTERABIT_Export.h"

#include "TProactor/Asynch_IO.h"
#include "TProactor/Double_List_T.h"

#include "IOTerabit/RefCount_T.h"
#include "IOTerabit/MessageBlockFactory.h"

#include "ace/OS_NS_sys_time.h"


namespace Terabit {

class AsynchChannelList;
class AsynchChannelFactory;
class ChannelManager;
class Protocol;


/**
 * @interface AsynchChannel
 * @brief AsynchChannel is abstact interace 
 *        It defines the generic behavior of connection handler
 *        
 *        AsynchChannel implementations are created by AsynchChannelFactory
 *        each time when incoming connection is accepted or
 *        outgoing connection is established.
 *
 * AsynchChannel
 * @li  works in tandem with Protocol object, 
 *      that allows to separate message parsing and processing
 *      from technical details of programming underneath stream 
 *      (which can be TCP stream, SSL stream or other source),
 *      dealing with timers, etc.
 * @li  provides initiation and queueing of Asynchronous operations 
 *      (read/write/timer)
 * @li  handles completion of Asynchronous operations, 
 *      takes approriate actions in case of I/O errors and
 *      notifies Protocol object about completions. 
 * @li  provides serialization of all read, write, timer and 
 *      "health-check" callback notifications to Protocol object.
 * @li  provides connection info, logging I/O activities 
 *      and facility of tracing of raw stream data
 *
 *
 */

class IOTERABIT_Export AsynchChannel : 
    public RefCount,
    public TRB_Handler,
    public MessageBlockFactory,
    public LinkD_T <AsynchChannel> 

{
public :

    typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;

    friend class ChannelManager;
    friend class AsynchChannelList;
    
    enum State
    {
        ST_INIT   = 0x0000,   // BEFORE OPEN
        ST_ACTIVE = 0x0001,   // OPERATIONAL
        ST_CANCEL = 0x0002,   // IN CANCEL
        ST_CLOSED = 0x0004    // CLOSED
    };
   
    enum ErrFlags 
    {
        ERR_NONE     = 0x0000,
        ERR_EOF      = 0x0001,  // READ - END OF FILE/STREAM
        ERR_READ     = 0x0002,  // READ ERROR
        ERR_WRITE    = 0x0004,  // WRITE ERROR
        ERR_TIMEOUT  = 0x0008,  // TIMEOUT ERROR
        ERR_ALLOC    = 0x0010,  // NO MEMORY FOR OPERATION
        ERR_PROTOCOL = 0x0020   // PROTOCOL RETURNED ERROR
    };

    enum PendingFlags
    {
        FLG_PENDING_READ   = 0x0001,  // Outstanding read  active
        FLG_PENDING_WRITE  = 0x0002,  // Outstanding write active
        FLG_PENDING_TIMER  = 0x0004,  // Outstanding timer active
        FLG_PENDING_MASK   = 0x000F   // Any outstanding mask
    };

    enum CallbackFlags
    {
        FLG_CALLBACK_READ  = 0x0001,  // Read completion is active
        FLG_CALLBACK_WRITE = 0x0002,  // Write completion is active
        FLG_CALLBACK_TIMER = 0x0004,  // Timer completion is active
        FLG_CALLBACK_CHECK = 0x0008,  // Check is active
        FLG_CALLBACK_OPEN  = 0x0010,  // We are opening protol
        FLG_CALLBACK_CLOSE = 0x0020,  // We are closing protol
        FLG_CALLBACK_MASK  = 0x00FF   
    };

    enum ModeFlags
    {
        MODE_SERVER         = 0x0001,  // Server or client
        MODE_AUTO_READ      = 0x0002,  // Read mode in ON
        MODE_HALF_DUPLEX    = 0x0004,  // Read only when write is empty
        MODE_NOTIFY_WRITE   = 0x0008   // Write notifications is ON
    };

    enum 
    {
        DEFAULT_READ_SIZE  = 4096,
        DEFAULT_WRITE_SIZE = DEFAULT_READ_SIZE
    };

        

    struct IOTERABIT_Export Info 
    {
    public:
        unsigned int    id_;            // Channel id, assigned once and forever
        unsigned long   total_snd_;     // Total bytes successfully sent
        unsigned long   total_rcv_;     // Total bytes successfully received
        unsigned long   total_w_;       // Number of performed write operations
        unsigned long   total_r_;       // Number of performed read operations
        State           state_;         // Channel main state (see State)
        int             err_flags_;     // Error state (see ErrFlags)
        unsigned long   error_;         // OS error that prevents other operations
        int             io_flags_;      // pending flags 
        int             cb_flags_;      // callback flags
        int             mode_flags_;    // mode flags: auto read, etc
        size_t          read_size_;     // auto-read size
        long            timer_id_;      // active timer id or -1 if no timer
        ACE_Time_Value  last_op_time_;  // time of last activity
        TRB_Sock_Addr   remote_addr_;   // remote peer address
        TRB_Sock_Addr   local_addr_;    // local address


        Info (unsigned int id = (unsigned int) -1);

        void print (const ACE_TCHAR *txt);
        void reset ();
    };


public:
    AsynchChannel  (unsigned int id);
    AsynchChannel (unsigned int id, unsigned int mb_cache_limit);
    virtual ~AsynchChannel (void);

    /// get associated channel manager
    ChannelManager  *get_manager (void) const ;

    /// get channel id. Channel id is assigned by AsynchChannelFactory
    /// during channel construstion for the whole channel lifetime.
    unsigned int     get_id (void) const ;

    /// @brief return info. see struct Infp
    void  get_info(Info & info);


    /// @brief set read chunk size.
    void   set_read_size (size_t size);

    /// @brief get read chunk size.
    size_t get_read_size () const;

    /// @brief get mode flags. return combination of bits 
    ///
    int   get_mode_flags () const;

    /// @retval true  if channel was created as result of accept operation
    /// @retval false if channel was created as result of connect operation
    bool  is_server () const;

    /// returns the address of remote peer
    const ACE_Addr & remote_addr () const;

    /// return the local address
    const ACE_Addr & local_addr () const;

    /// This method is called to pass the new connection's addresses.
    /// called by ChannelAcceptor/ChannelConnector
    virtual void addresses (const ACE_Addr & remote,
                            const ACE_Addr & local);

    /// open channel, called by ChannelAcceptor/ChannelConnector
    /// @param handle     descriptor of  newly accepted/connected socket
    /// @param flg_server true if socket was accepted (server mode)
    ///                   false if socket was connected (client mode)
    /// @retval  0   success, ownership of handle is taken
    /// @retval  <0  errors, ownership of handle has not been taken
    int  open (ACE_HANDLE               handle,
               bool                     flg_server);


    /// link channel to protocol and activate it
    /// @param protocol   the protocol instance created for this channel
    /// @param data       address of the initial block of  read data 
    ///                   (always zero for client mode)
    /// @param datalength length of the initial block of  read data 
    ///                   (always zero for client mode)
    /// @retval  0   success, ownership of handle is taken
    /// @retval  <0  errors, ownership of handle has not been taken
    int  activate_protocol (Protocol     *protocol,
                            const char   *data,
                            size_t        datalen);

    /// this method is called to force cancellation of all outstanding 
    /// requests and close the channel.
    ///  @retval ST_CANCEL if cancellation has been initiated and
    ///          will be finished later. Upon finish the associated 
    ///          Protocol will be notified via
    ///          Protocol::on_channel_closed () callback.
    ///
    ///  @retval ST_CLOSED if cancellation is done. 
    ///          if @parameter flg_callback is false,
    ///          the associated Protocol will not be notified
    ///          Protocol::on_channel_closed () callback.
    State  close (bool flg_callback = true);


    /// enable auto read mode
    int   enable_read ();

    /// disable auto read mode
    int   disable_read ();

    /// set duplex mode
    int  set_duplex_mode (bool full_duplex);

    /// enable write notifications when all queued data is written
    int   enable_write_notifications ();

    /// disable write notifications
    int   disable_write_notifications ();

    /// initiate writev operation or queue the data to the output
    /// queue. The data will be copied, so on return the original
    /// data are no longer used by channel.
    //  @param iov     vector of buffers
    //  @param iovcnt  number elements in the vector.
    /// @retval 0   success
    /// @retval < 0 error, channel will be closed
    int   start_write  (const iovec *iov, int iov_cnt);
               
    /// initiate write operation or queue the data to the output
    /// queue. The data will be copied, so on return the original
    /// data are no longer used by channel.
    /// @param data    address of data to wrie
    /// @param datalen length to write
    /// used by channel.
    /// @retval 0   success
    /// @retval < 0 error, channel will be closed
    int   start_write  (const char *data, size_t datalen);


    /// initiate write operation or queue the data to the output
    /// queue. The onwership of message block will be taken by 
    /// this channel regardles of return code. Therefore, the message
    /// block should be obtained via AsynchChannel::alloc_msg() method.
    /// @retval 0   success
    /// @retval < 0 error, channel will be closed
    int   start_write  (ACE_Message_Block& mb);

    /// the same as previous + output param - length of bytes in internal queue
    int   start_write  (ACE_Message_Block& mb, 
      unsigned int& qlen, unsigned int& qlen_in_bytes);

    //typedef void (*FN_MB_DELETER)(ACE_Message_Block *mb);
    //int   start_write (ACE_Message_Block& mb, FN_MB_DELETER fn);

    /// start one-shot timer. It allowed to have only one pending timer
    /// channel. 
    /// @param interval  timer interval value
    /// @param arg       user data ,will be returned to the protocol 
    ///                  on timer expriration
    /// @retval timer id (success) or -1 (failure)
    long  start_timer  (const ACE_Time_Value&  interval,
                        const void            *arg);

    /// cancel pending timer
    int   cancel_timer ();

    //
    // MessageBlockFactory interface
    //
    virtual ACE_Message_Block *alloc_msg (size_t length);
    virtual ACE_Message_Block *alloc_msg (size_t length, unsigned long long tag);
    virtual void free_msg (ACE_Message_Block * mb);

    // TRB_Handler interface
    // These methods are called by the framework.
    // Do not call them direcly!
   
    /// This is called by Proactor when asynchronous <read> operation completes.
    virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

    /// This is by Proactor called when an asynchronous <write>  completes.
    virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

    /// This is by Proactor called when an asynchronous <write>  completes.
    virtual void handle_time_out (const ACE_Time_Value&  interval,
                                  const void             *arg);


    void reset ();

private:
    // this method is periodically called by ChannelManager
    // when timeout is expired
    void  check_activity ();

   // RefCount inteface
    virtual void free ();
    
    // must be implented in derived classes: TcpChannel, SSLChannel, etc
    virtual int  reset_impl () = 0;
    virtual int  open_impl (ACE_HANDLE handle, bool flg_server) = 0;
    virtual int  close_impl () = 0;
    virtual int  start_read_impl (ACE_Message_Block& mb, size_t nbytes) = 0;
    virtual int  start_write_impl (ACE_Message_Block& mb, size_t nbytes) = 0;
    virtual bool has_specific_events () = 0;

 
    void   set_manager (ChannelManager *manager);
    void   update_last_time (void);

    State  initiate_close (int err_flags, u_long error);
    State  check_closure (bool flg_callback, RefCountGuard& guard);
    int    start_write_internal (ACE_Message_Block& mb, size_t length);
    int    start_read_internal  ();
    int    cancel_timer_internal ();
    
 
    void   trace_read_completion  (const TRB_Asynch_Read_Stream::Result &result);
    void   trace_write_completion (const TRB_Asynch_Write_Stream::Result &result);
    void   trace_buffers(const Buffer_Info& buf_info,
                         size_t xfer_bytes,
                         bool   flg_read);

    bool build_write_chain (const iovec *iov, int iov_cnt);
    ACE_Message_Block * get_write_chain (size_t& length);
    ACE_Message_Block * get_last_wr_mb (unsigned int& qlen, unsigned int& qlen_in_bytes);


    // members
    
    Double_List_T <AsynchChannel>::iterator  itr_;

    ChannelManager     *manager_;
    Info                info_;
    RefCountPtr         self_;
    Protocol           *protocol_;
    ACE_Message_Block   rd_mb_;
    ACE_Message_Block  *wr_mq_;
    MessageBlockFactory_T<ACE_NULL_SYNCH>  mb_cache_;

    // TODO:
    //Buffer_Info         wr_buf_info_;
};

typedef RefCountPtr_T < AsynchChannel > AsynchChannelPtr;


/**
 * @class AsynchChannelList
 * @brief an intrusive conttainer for fast, excpetion safe
 *        insertion and deletion of AsynchChannels
 *
 */
class  IOTERABIT_Export AsynchChannelList :
    public Double_List_T <AsynchChannel>
{
public:
    typedef 
    Double_List_T <AsynchChannel>::iterator
    iterator;

    AsynchChannelList ();
    ~AsynchChannelList ();

    bool insert_channel (AsynchChannel *channel);
    bool remove_channel (AsynchChannel *channel);
};
       

/**
 * @interface AsynchChannelFactory
 * @brief AsynchChannelFactory is abstact interace 
 *        designed for creation of Channel objects 
 *
 */
class IOTERABIT_Export AsynchChannelFactory 
{

    friend class ChannelManager;
    friend class AsynchChannel;

protected:
    AsynchChannelFactory () {} 
    virtual ~AsynchChannelFactory () {}


    /// @brief get channel
    ///
    /// This method is called by framework when 
    /// incoming connection is accepted <Acceptor> case or
    /// outgoing connection is established <Connector> case.
    /// @fn create_connection
    /// @return a pointer to created <AsynchChannel> implementation

    virtual AsynchChannel*  create_channel()=0;


    /// @brief free channel
    ///
    /// This method is called by framework when it detects 
    /// that <AsynchChannel> object is no longer used and should be destroyed
    virtual void destroy_channel (AsynchChannel *channel) = 0;


};

//==========================================================================
//
//==========================================================================

inline ChannelManager * 
AsynchChannel::get_manager (void) const
{
    return this->manager_;
}

inline unsigned int
AsynchChannel::get_id () const
{
    return this->info_.id_;
}

inline void
AsynchChannel::update_last_time ()
{
    this->info_.last_op_time_ = ACE_OS::gettimeofday ();
}

inline const ACE_Addr & 
AsynchChannel::remote_addr () const
{
    return this->info_.remote_addr_.get_ace_addr ();
}

inline const ACE_Addr & 
AsynchChannel::local_addr () const
{
    return this->info_.local_addr_.get_ace_addr ();
}

inline size_t
AsynchChannel::get_read_size (void) const
{
    return this->info_.read_size_;
}

inline void 
AsynchChannel::set_read_size (size_t size)
{
    this->info_.read_size_ = size;
}

inline int
AsynchChannel::get_mode_flags () const
{
    return this->info_.mode_flags_;
}

inline bool
AsynchChannel::is_server () const
{
    return ACE_BIT_ENABLED (this->info_.mode_flags_,
                            MODE_SERVER);
}

}  //namespace Terabit 

#endif // TERABIT_ASYNCHCHANNEL_H
