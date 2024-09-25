/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Asynch_Acceptor2.h
 *
 *  Asynch_Acceptor2.h,v 4.34 2002/09/24 06:29:41 jwillemsen Exp
 *
 *  @author Irfan Pyarali (irfan@cs.wustl.edu)
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_ASYNCH_ACCEPTOR2_H 
#define TPROACTOR_ASYNCH_ACCEPTOR2_H 
#include "ace/pre.h"

#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (ACE_WIN32) || defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
// This only works on platforms that support async i/o.

#include "ace/Default_Constants.h"
#include "TProactor/Asynch_IO.h"
#include "ace/Message_Block.h"

#include "TProactor/Monitor_T.h"
#include "ace/Synch_T.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


/**
 * @class TRB_Asynch_Acceptor2
 *
 * @brief This class is an example of the Acceptor Pattern.  This class
 * will accept new connections and create new HANDLER to handle
 * the new connections.
 *
 * Unlike the <ACE_Acceptor>, however, this class is designed to
 * be used asynchronously.
 */
template <class HANDLER>
class TRB_Asynch_Acceptor2 : public TRB_Handler
{
public:
  typedef typename HANDLER::ADDRESS  ADDRESS;

  typedef ACE_SYNCH_MUTEX            Mutex;
  typedef ACE_SYNCH_CONDITION        Condition;
  typedef Monitor_T<Mutex,Condition> Monitor;
  typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
  typedef Guard_Monitor::Save_Guard  Save_Guard;


  /// A do nothing constructor.
  TRB_Asynch_Acceptor2 (void);

  /// Virtual destruction
  virtual ~TRB_Asynch_Acceptor2 (void);

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
   * @param pass_addresses Optional, a non-zero value indicates that
   *                the local and peer addresses should be passed to the
   *                associated @c TRB_Service_Handler::addresses() method
   *                after any call to @c validate_new_connection() and prior
   *                to the @c open() hook method call.
   * @param backlog Optional, defaulting to @c ACE_DEFAULT_BACKLOG (which
   *                can be adjusted in your platform's @c config.h file).
   *                Specifies the listening backlog for the listening socket.
   * @param reuse_addr Optional, indicates whether the @c SO_REUSEADDR
   *                option is set on the listening socket or not.
   * @param proactor Optional, pointer to the @c TRB_Proactor to use for
   *                demultiplexing asynchronous accepts. If 0, the
   *                process's singleton @c TRB_Proactor is used.
   * @param validate_new_connection Optional, if non-zero, this object's
   *                @c validate_connection() method is called after
   *                the accept completes, but before the service handler's
   *                @c open() hook method is called. If @c
   *                validate_connection() returns -1, the newly-accepted
   *                socket is immediately closed, and the @c addresses()
   *                method is not called.
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
  virtual int open (const ADDRESS& address,
                    size_t bytes_to_read = 0,
                    int pass_addresses = 0,
                    int backlog = ACE_DEFAULT_BACKLOG,
                    int reuse_addr = 1,
                    TRB_Proactor *proactor = 0,
                    int validate_new_connection = 0,
                    int reissue_accept = 1,
                    int number_of_initial_accepts = -1);

  /// Get the underlying handle.
  virtual ACE_HANDLE get_handle (void) const;

  

  /// This initiates a new asynchronous accept operation.
  /**
   * You need only call this method if the @a reissue_accept argument
   * passed to @c open() was 0.
   */
  virtual int accept (size_t bytes_to_read = 0, const void *act = 0);

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

  /**
   * Template method to validate peer before service is opened.
   * This method is called after a new connection is accepted if the
   * @a validate_connection argument to @c open() was non-zero or
   * the @c validate_new_connection() method is called to turn this
   * feature on.  The default implementation returns 0.  Users can
   * reimplement this method to perform validation of the peer
   * using it's address, running an authentication procedure (such as
   * SSL) or anything else necessary or desireable. The return value
   * from this method determines whether or not ACE will continue
   * opening the service or abort the connection.
   *
   * @param result    Result of the connection acceptance.
   * @param remote    Peer's address.
   * @param local     Local address connection was accepted at.
   *
   * @retval  -1  TRB_Asynch_Acceptor2 will close the connection, and
   *              the service will not be opened.
   * @retval  0   Service opening will proceeed.
   */
  virtual int validate_connection (const TRB_Asynch_Accept::Result& result,
                                   const ADDRESS& remote,
                                   const ADDRESS& local) = 0;

  //
  // These are low level tweaking methods
  //

  /// Get flag that indicates if parsing and passing of addresses to
  /// the service_handler is necessary.
  virtual int pass_addresses (void) const;

  /// Set flag that indicates if parsing and passing of addresses to
  /// the service_handler is necessary.
  virtual void pass_addresses (int new_value);

  /// Get flag that indicates if address validation is required.
  virtual int validate_new_connection (void) const;

  /// Set flag that indicates if address validation is required.
  virtual void validate_new_connection (int new_value);

  /// Get flag that indicates if a new accept should be reissued when a accept
  /// completes.
  virtual int reissue_accept (void) const;

  /// Set flag that indicates if a new accept should be reissued when a accept
  /// completes.
  virtual void reissue_accept (int new_value);

  /// Get bytes to be read with the <accept> call.
  virtual size_t bytes_to_read (void) const;

  /// Set bytes to be read with the <accept> call.
  virtual void bytes_to_read (size_t new_value);

protected:

  /// This is called when an outstanding accept completes.
  virtual void handle_accept (const TRB_Asynch_Accept::Result &result);

  /// Return the listen handle.
  ACE_HANDLE handle (void) const;
  /// Set the listen handle.
  void handle (ACE_HANDLE h);

 
  /// Return the asynch accept object.
  /// TRB_Asynch_Accept &asynch_accept (void);

  /**
   * This is the template method used to create new handler.
   * Subclasses must overwrite this method if a new handler creation
   * strategy is required.
   */
  virtual HANDLER *make_handler (void);
  virtual HANDLER *make_handler (const void * act);

private:
  int accept_i (size_t         bytes_to_read, 
                const void    *act,
                Guard_Monitor& guard);
  

  const ADDRESS& get_completion_address (const ADDRESS&  default_addr,
                                         const ACE_Addr& addr);

  // make sure we have  correct address type
  // and can  detect family 
  const ADDRESS   default_addr_;

  ADDRESS   listen_addr_;

  /// Monitor to protect state
  mutable Monitor monitor_;

  /// flag to cancel 
  bool flg_cancel_;

  /// The number of pending asynchronous accepts
  int pending_count_;

  /// Handle used to listen for new connections.
  ACE_HANDLE listen_handle_;

  /// <Asynch_Accept> used to make life easier :-)
  TRB_Asynch_Accept asynch_accept_;

  /// Flag that indicates if parsing of addresses is necessary.
  int pass_addresses_;

  /// Flag that indicates if address validation is required.
  int validate_new_connection_;

  /// Flag that indicates if a new accept should be reissued when a
  /// accept completes.
  int reissue_accept_;

  /// Bytes to be read with the <accept> call.
  size_t bytes_to_read_;
  
  ACE_Message_Block dummy_msg_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "TProactor/Asynch_Acceptor2.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Asynch_Acceptor2.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif /* ACE_WIN32 || ACE_HAS_AIO_CALLS */
#include "ace/post.h"
#endif //TPROACTOR_ASYNCH_ACCEPTOR2_H 
