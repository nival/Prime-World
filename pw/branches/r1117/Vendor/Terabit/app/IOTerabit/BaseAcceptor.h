/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    BaseAcceptor.h
 *
 *  BaseAcceptor.h
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TERABIT_BASEACCEPTOR_H 
#define TERABIT_BASEACCEPTOR_H 

#include "IOTERABIT_Export.h"

#include "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "ace/Default_Constants.h"
#include "TProactor/Asynch_IO.h"
#include "TProactor/Monitor_T.h"


#include "ace/Synch_T.h"
#include "ace/Message_Block.h"
#include "ace/INET_Addr.h"

#include "IOTerabit/MessageBlockFactory.h"

namespace Terabit {

/**
 * @class BaseAcceptor
 *
 * @brief This class is an example of the Acceptor Pattern.  This class
 * will accept new connections and create new HANDLER to handle
 * the new connections.
 *
 * Unlike the <ACE_Acceptor>, however, this class is designed to
 * be used asynchronously.
 */

class IOTERABIT_Export BaseAcceptor :  public TRB_Handler
{
public:
    typedef ACE_SYNCH_MUTEX            Mutex;
    typedef ACE_SYNCH_CONDITION        Condition;
    typedef Monitor_T<Mutex,Condition> Monitor;
    typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
    typedef Guard_Monitor::Save_Guard  Save_Guard;


    enum State
    {
        ST_INIT   = 0x0000,   // BEFORE OPEN
        ST_ACTIVE = 0x0001,   // OPERATIONAL
        ST_CANCEL = 0x0002,   // IN CANCEL
        ST_CLOSED = 0x0004    // CLOSED
    };



    /// A do nothing constructor.
    BaseAcceptor (void);

    /// Virtual destruction
    virtual ~BaseAcceptor (void);

    /**
    * @c open starts one or more asynchronous accept requests on a
    * @a address. Each accept operation may optionally read an
    * initial buffer from the new connection when accepted.
    *
    * @param address The address to listen/accept connections on.
    *                If the address does not specify a port, a random
    *                port is selected and bound.
    * @param bytes_to_read Optional, specifies the maximum number of bytes
    *                to read with the accept. The buffer for the initial
    *                data is allocated internally and passed to the
    *                @c TRB_Service_Handler::open() hook method. It is
    *                legitimate only during the @c open() method and must
    *                be copied if required after @c open() returns.
    *                This pre-read function works only on Windows.
    *                to the @c open() hook method call.
    * @param backlog Optional, defaulting to @c ACE_DEFAULT_BACKLOG (which
    *                can be adjusted in your platform's @c config.h file).
    *                Specifies the listening backlog for the listening socket.
    * @param reuse_addr Optional, indicates whether the @c SO_REUSEADDR
    *                option is set on the listening socket or not.
    * @param proactor Optional, pointer to the @c TRB_Proactor to use for
    *                demultiplexing asynchronous accepts. If 0, the
    *                process's singleton @c TRB_Proactor is used.
    * @param reissue_accept Optional, if non-zero (the default), a new
    *                asynchronous accept operation is started after each
    *                completion, whether the completion is for success or
    *                failure, and whether or not a successfully-accepted
    *                connection is subsequently refused.
    * @param number_of_initial_accepts Optional, the number of asynchronous
    *                accepts that are started immediately. If -1 (the
    *                default), the value of @a backlog is used.
    *
    * @note On Windows, the peer address is only available at the time
    *       the connection is accepted.  Therefore, if you require the peer
    *       address on Windows, do not rely on the
    *       @c ACE_SOCK::get_remote_addr() method - it won't work. You must
    *       supply a non-zero value for @a pass_addresses and obtain the
    *       peer address in the @c TRB_Service_Handler::addresses() method.
    *
    * @see ACE_INET_Addr
    * @see TRB_Service_Handler
    */
    virtual int open (const ACE_Addr& address,
                      size_t bytes_to_read = 0,
                      int backlog = ACE_DEFAULT_BACKLOG,
                      int reuse_addr = 1,
                      TRB_Proactor *proactor = 0,
                      int reissue_accept = 1,
                      int number_of_initial_accepts = -1);



    /// This initiates a new asynchronous accept operation.
    /**
    * You need only call this method if the @a reissue_accept argument
    * passed to @c open() was 0.
    */
    virtual int accept (size_t bytes_to_read = 0);

    /**
    * Cancels all pending accepts operations issued by this object.
    * and close the listen handle
    *
    * @note On Windows, the only one way to cancel all pending
    *  accept operations is to close listen handel. Windows call
    *  CancelIO cancels only operations initiated by the calling 
    *  thread, which is not helpfull.
    * @note On UNIX, it is safe to close listen handle only after
    *  cancellation. TProcator will take care about all pending
    *  accepts .
    * So the portable solution is to do cancel-and-close, which is
    * actually done in current implementation.
    */
    virtual int cancel (void);

    /**
    * Waits for cancellations of all pending accepts operations
    * issued by this object. This method must be called to ensure
    * that no more asychronous callbacks is expected and it is
    * safe to delete this object.
    */
    void wait (void);

    int get_pending_count (void) const;

    State get_state ();


    /// Get flag that indicates if a new accept should be reissued when a accept
    /// completes.
    int reissue_accept (void) const;

    /// Set flag that indicates if a new accept should be reissued when a accept
    /// completes.
    void reissue_accept (int new_value);

    /// Get bytes to be read with the <accept> call.
    size_t bytes_to_read (void) const;

    /// Set bytes to be read with the <accept> call.
    void bytes_to_read (size_t new_value);

    /// Return the listen handle.
    virtual ACE_HANDLE handle (void) const;

    /// Set the listen handle - dummy function,
    /// prohibit setting listen handle
    virtual void handle (ACE_HANDLE h);

 
private:
    /// This is called when an outstanding accept completes.
    virtual void handle_accept (const TRB_Asynch_Accept::Result &result);

private:
    /**
    * This is the template method used to create new handler.
    * Subclasses must overwrite this method if a new handler creation
    * strategy is required.
    * @retval  -1  BaseAcceptor will close the connection, and
    *              the service will not be opened.
    * @retval  0   Service opening will proceeed.
    */
    virtual int  on_accept_completed (const TRB_Asynch_Accept::Result &result) = 0;

    int accept_i (size_t         bytes_to_read, 
                  Guard_Monitor& guard);



    /// Monitor to protect state
    mutable Monitor monitor_;

    /// state  
    State  state_;
    
    /// The number of pending asynchronous accepts
    int pending_count_;

    /// Handle used to listen for new connections.
    ACE_HANDLE listen_handle_;

    /// <Asynch_Accept> used to make life easier :-)
    TRB_Asynch_Accept asynch_accept_;

    /// Flag that indicates if a new accept should be reissued when a
    /// accept completes.
    int reissue_accept_;

    /// Bytes to be read with the <accept> call.
    size_t bytes_to_read_;

    ///
    long   seq_num_;

    MessageBlockFactory_T<ACE_NULL_SYNCH> mb_factory_;
};


inline BaseAcceptor::State
BaseAcceptor::get_state ()
{
    Guard_Monitor guard (monitor_);
    return this->state_;
}

inline ACE_HANDLE
BaseAcceptor::handle (void) const
{
    return this->listen_handle_;
}

inline void
BaseAcceptor::handle (ACE_HANDLE h)
{
    ACE_UNUSED_ARG (h);
    // prohibit substitution !!!
    //TRB_Handler::handle (h);
}


inline int
BaseAcceptor::reissue_accept (void) const
{
    return this->reissue_accept_;
}

inline void
BaseAcceptor::reissue_accept (int new_value)
{
    this->reissue_accept_ = new_value;
}

inline size_t
BaseAcceptor::bytes_to_read (void) const
{
  return this->bytes_to_read_;
}

inline void
BaseAcceptor::bytes_to_read (size_t new_value)
{
  this->bytes_to_read_ = new_value;
}

}  //namespace Terabit 

#include "ace/post.h"
#endif // TERABIT_BASEACCEPTOR_H 
