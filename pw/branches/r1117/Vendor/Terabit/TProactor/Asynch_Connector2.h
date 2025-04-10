/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Asynch_Connector2.h
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_ASYNCH_CONNECTOR2_H 
#define TPROACTOR_ASYNCH_CONNECTOR2_H 
#include "ace/pre.h"

#include "ace/config-all.h"

#if defined (ACE_WIN32) || defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
// This only works on platforms that support async i/o.

#include "TProactor/Asynch_IO.h"
#include "ace/INET_Addr.h"

#include "TProactor/Monitor_T.h"
#include "ace/Synch_T.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


// Forward declarations
class ACE_Message_Block;

/**
 * @class TRB_Asynch_Connector2
 *
 * @brief This class is an example of the Connector pattern.  This class
 * will establish new connections and create new HANDLER objects to handle
 * the new connections.
 *
 * Unlike the ACE_Connector, however, this class is designed to
 * be used asynchronously with the ACE Proactor framework.
 */

template <class HANDLER>
class TRB_Asynch_Connector2 : public TRB_Handler
{
public:
  typedef typename HANDLER::ADDRESS  ADDRESS;

  typedef ACE_SYNCH_MUTEX            Mutex;
  typedef ACE_SYNCH_CONDITION        Condition;
  typedef Monitor_T<Mutex,Condition> Monitor;
  typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
  typedef Guard_Monitor::Save_Guard  Save_Guard;


  /// A do nothing constructor.
  TRB_Asynch_Connector2 (void);

  /// Virtual destruction
  virtual ~TRB_Asynch_Connector2 (void);

  /**
   * This opens asynch connector
   */
  virtual int open (int pass_addresses = 0,
                    TRB_Proactor *proactor = 0,
                    int validate_new_connection = 1);

  /// This initiates a new asynchronous connect
  virtual int connect (const ADDRESS& remote_sap,
                       const ACE_Addr &local_sap = 
                             ACE_Addr::sap_any,
                       int reuse_addr = 1,
                       const void *act = 0);

  /**
   * Cancels all pending connects operations issued by this object.
   * and close the listen handle
   *
   * @note On Windows, the only one way to cancel all pending
   *  connect operations is to close listen handel. Windows call
   *  CancelIO cancels only operations initiated by the calling 
   *  thread, which is not helpfull.
   * @note On UNIX, it is safe to close listen handle only after
   *  cancellation. TProcator will take care about all pending
   *  connects .
   * So the portable solution is to do cancel-and-close, which is
   * actually done in current implementation.
   */
  virtual int cancel (void);

  /**
   * Waits for cancellations of all pending connects operations
   * issued by this object. This method must be called to ensure
   * that no more asychronous callbacks is expected and it is
   * safe to delete this object.
   */
  void wait (void);

  int get_pending_count (void) const;


  /**
   * Template method to validate peer before service is opened.
   * This method is called when the connection attempt completes,
   * whether it succeeded or failed, if the @a validate_connection
   * argument to @c open() was non-zero or the @c validate_new_connection()
   * method is called to turn this feature on.  The default implementation
   * returns 0.  Users can (and probably should) reimplement this method
   * to learn about the success or failure of the connection attempt.
   * If the connection completed successfully, this method can be used to
   * perform validation of the peer using it's address, running an
   * authentication procedure (such as SSL) or anything else necessary or
   * desireable. The return value from this method determines whether or
   * not ACE will continue opening the service or abort the connection.
   *
   * @param result  Result of the connection acceptance. Use
   *                result.success() to determine success or failure of
   *                the connection attempt.
   * @param remote  Peer's address. If the connection failed, this object
   *                is undefined.
   * @param local   Local address connection was completed from. If the
   *                connection failed, this object is undefined.
   *
   * @retval  -1  TRB_Asynch_Connector2 will close the connection, and
   *              the service will not be opened.
   * @retval  0   Service opening will proceeed.
   * @return  Return value is ignored if the connection attempt failed.
   */
  virtual int validate_connection (const TRB_Asynch_Connect::Result& result,
                                   const ADDRESS& remote,
                                   const ADDRESS& local)=0;


  //
  // These are low level tweaking methods
  //

  /// Set and get flag that indicates if parsing and passing of
  /// addresses to the service_handler is necessary.
  virtual int  pass_addresses (void) const;
  virtual void pass_addresses (int new_value);

  /// Set and get flag that indicates if address validation is
  /// required.
  virtual int  validate_new_connection (void) const;
  virtual void validate_new_connection (int new_value);

protected:

  /// This is called when an outstanding accept completes.
  virtual void handle_connect (const TRB_Asynch_Connect::Result &result);


  /**
   * This is the template method used to create new handler.
   * Subclasses must overwrite this method if a new handler creation
   * strategy is required.
   */
  virtual HANDLER *make_handler (void);
  virtual HANDLER *make_handler (const void * act);

private:
  const ADDRESS& get_completion_address (const ADDRESS&  default_addr,
                                         const ACE_Addr& addr);

  // make sure we have  correct address type
  // and can  detect family 
  const ADDRESS   default_addr_;


  /// Monitor to protect state
  mutable Monitor monitor_;

  /// flag to cancel 
  bool flg_cancel_;

  /// The number of pending asynchronous accepts
  int pending_count_;


  /// Asynch_Connect used to make life easier :-)
  TRB_Asynch_Connect asynch_connect_;

  /// Flag that indicates if parsing of addresses is necessary.
  int pass_addresses_;

  /// Flag that indicates if address validation is required.
  int validate_new_connection_;

};

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "TProactor/Asynch_Connector2.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Asynch_Connector2.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif /* ACE_WIN32 || ACE_HAS_AIO_CALLS */
#include "ace/post.h"
#endif //TPROACTOR_ASYNCH_CONNECTOR2_H 
