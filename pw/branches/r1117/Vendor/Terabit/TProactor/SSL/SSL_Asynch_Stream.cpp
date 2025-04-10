// -*- C++ -*-

#include "TProactor/SSL/SSL_Asynch_Stream.h"

ACE_RCSID (ACE_SSL,
           SSL_Asynch_Stream,
           "SSL_Asynch_Stream.cpp,v 1.9 2003/04/16 07:16:40 ossama Exp")

// This only works on platforms with Asynchronous IO support.
#if OPENSSL_VERSION_NUMBER > 0x0090581fL && ((defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS)) || (defined (ACE_HAS_AIO_EMULATION)))

#if defined (ACE_WIN32)
# define ERR_CANCELED ERROR_OPERATION_ABORTED
#else
# define ERR_CANCELED ECANCELED
#endif  /* ACE_WIN32 */

#include "ace/OS_NS_errno.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_socket.h"

#include "TProactor/Proactor.h"

#include <openssl/err.h>

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// ************************************************************

typedef ACE_Reverse_Lock<ACE_SYNCH_MUTEX> REVERSE_MUTEX;

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Reverse_Lock<ACE_SYNCH_MUTEX>;
template class ACE_Guard<ACE_Reverse_Lock<ACE_SYNCH_MUTEX> >;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Reverse_Lock<ACE_SYNCH_MUTEX>
#pragma instantiate ACE_Guard<ACE_Reverse_Lock<ACE_SYNCH_MUTEX> >

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */



// ************************************************************
//  TRB_SSL_Asynch_Stream Constructor / Desctructor
// ************************************************************
TRB_SSL_Asynch_Stream::TRB_SSL_Asynch_Stream (
  TRB_SSL_Asynch_Stream::Stream_Type type,
  ACE_SSL_Context * context)
  : type_         (type),
    handle_       (ACE_INVALID_HANDLE),
    owner_        (0),
    proactor_     (0),
    ext_read_result_  (0,0,0,0,0,0,0,0,0),
    num_ext_reads_    (0),
    ext_write_result_ (0,0,0,0,0,0,0,0,0),
    num_ext_writes_   (0),
    flags_        (0),
    ssl_          (0),
    bio_          (0),
    bio_istream_  (),
    bio_inp_msg_  (),
    bio_inp_errno_(0),
    bio_inp_flag_ (0),
    bio_ostream_  (),
    bio_out_msg_  (),
    bio_out_errno_(0),
    bio_out_flag_ (0),
    mutex_        ()
{
  ACE_TRACE ("TRB_SSL_Asynch_Stream::TRB_SSL_Asynch_Stream");
  // was honestly copied from ACE_SSL_SOCK_Stream :)

  ACE_SSL_Context * ctx =
    (context == 0 ? ACE_SSL_Context::instance () : context);

  this->ssl_ = ::SSL_new (ctx->context ());

  if (this->ssl_ == 0)
    ACE_ERROR
      ((LM_ERROR,
        ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream %p\n"),
        ACE_TEXT ("- cannot allocate new SSL structure")
     ));

  ::SSL_set_verify (this->ssl_,
                    ctx->default_verify_mode (),
                    0);
}

TRB_SSL_Asynch_Stream::~TRB_SSL_Asynch_Stream (void)
{
  ACE_TRACE ("TRB_SSL_Asynch_Stream::~TRB_SSL_Asynch_Stream");

  {
    ACE_MT (ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_));

    ACE_ASSERT (this->pending_BIO_count() == 0);

    // It is safe to delete stream if all notifications are received,
    // i.e., state is SF_DELETE_ENABLE or if proactor event loop is
    // done.
    if (ACE_BIT_ENABLED (this->flags_, SF_STREAM_OPEN))  // open
      {
        if (ACE_BIT_DISABLED (this->flags_, SF_DELETE_ENABLE))
          {
            ACE_ASSERT (0); 
            ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT("(%t) TRB_SSL_Asynch_Stream::DTOR-")
                    ACE_TEXT("possible access violation ")
                    ACE_TEXT("if proactor still handles events\n")));
          }
      }

    this->close_handle ();

    ::SSL_free (this->ssl_);
    this->ssl_ = 0;
  }

  // Was honestly copied from ACE_SSL_SOCK_Stream :)

  // @@ Question: should we reference count the Context object or
  // leave that to the application developer? We do not reference
  // count reactors (for example) and following some simple rules
  // seems to work fine!
}

int
TRB_SSL_Asynch_Stream::supported_operations (void) const
{
  return (TRB_Asynch_Result::OP_READ_STREAM |
          TRB_Asynch_Result::OP_WRITE_STREAM);
}

int
TRB_SSL_Asynch_Stream::close_handle (void)
{
  if (this->handle_ != ACE_INVALID_HANDLE &&
      this->owner_ != 0)
    {
      ACE_OS::closesocket(this->handle_);
    }
  this->handle_ = ACE_INVALID_HANDLE; 

  return 0;
}

// ************************************************************
//  close ()
//  returns :
//  0  - Stream is in the state SF_DELETE_ENABLE,
//       so  it is safe to delete stream
//  -1 - Stream has pending AIO requests,
//       close should be repeated later one more
// ************************************************************

int
TRB_SSL_Asynch_Stream::close (void)
{
  ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

  if (ACE_BIT_DISABLED (this->flags_ ,SF_STREAM_OPEN))  
    {
      ACE_SET_BITS (this->flags_, SF_DELETE_ENABLE);
    }

  if (ACE_BIT_ENABLED (this->flags_ , SF_DELETE_ENABLE))
    return 0;

  ACE_SET_BITS (this->flags_, SF_REQ_SHUTDOWN);

  this->do_SSL_state_machine (0); // use post completion

  return -1;
}

// ************************************************************
//  Asynch_Operation interface
//    cancel
// ************************************************************
int
TRB_SSL_Asynch_Stream::cancel (void)
{
  ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

  if (ACE_BIT_DISABLED (this->flags_ ,SF_STREAM_OPEN))  
    {
      ACE_SET_BITS (this->flags_, SF_DELETE_ENABLE);
    }

  if (ACE_BIT_ENABLED (this->flags_ , SF_DELETE_ENABLE))
    return 1;   //   AIO_ALLDONE

  ACE_SET_BITS (this->flags_, SF_REQ_SHUTDOWN);

  this->bio_cancel ();

  this->do_SSL_state_machine (0); // use post completion

  // attempt to cancel external, i.e. bio_ssl read/write
  int rc_r_ext = notify_read (0, 0, ERR_CANCELED);
  int rc_w_ext = notify_write (0, 0, ERR_CANCELED);

  if (rc_r_ext < 0  || rc_w_ext < 0)
    return -1;  // at least one error

  if (rc_r_ext == 1 && rc_w_ext == 1)
    return 1;  // AIO_ALLDONE

  if (rc_r_ext == 2 || rc_w_ext == 2)
    return 2;  // AIO_NOT_CANCELED , at least one not canceled

  return 0;    // AIO_CANCELED, at least will be one notification
}

// ************************************************************
//  Asynch_Operation interface
//    open
// ************************************************************
int
TRB_SSL_Asynch_Stream::open (TRB_Handler & handler,
                             ACE_HANDLE handle,
                             const void * completion_key,
                             TRB_Proactor * proactor,
                             int pass_ownership)
{
  ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));
  
  if (handle == ACE_INVALID_HANDLE)
    ACE_ERROR_RETURN
      ((LM_ERROR,
        ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream::open()")
        ACE_TEXT (" - invalid handle")),
       -1);

  if (ACE_BIT_ENABLED(this->flags_ ,SF_STREAM_OPEN) ||
      (this->flags_ != 0) ||
      (this->ssl_ == 0) )
  {
    ACE_ERROR
      ((LM_ERROR,
      ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream::open() : ")
        ACE_TEXT (" already opened or request to cancel")
        ACE_TEXT (" or no SSL structure")));

    if (pass_ownership != 0)
        ACE_OS::closesocket(handle);

    return -1;
  }


  this->handler_ = &handler;
  this->handle_  = handle;
  this->owner_   = pass_ownership;

  // Get a proactor for/from the user.
  this->proactor_    = proactor;
  if (this->proactor_ == 0)
    this->proactor_ = handler.proactor ();

  // Open internal input stream
  if (this->bio_istream_.open (*this,   // real callbacks to this
                               handle,
                               completion_key,
                               this->proactor_) != 0)
    return -1;

  // Open internal output stream
  if (this->bio_ostream_.open (*this,  // real callbacks to this
                               handle,
                               completion_key,
                               this->proactor_) != 0)
    return -1;

  this->bio_ = ::BIO_new_TRB_Asynch (this);

  if (this->bio_ == 0)
    ACE_ERROR_RETURN
      ((LM_ERROR,
        ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream::open()")
        ACE_TEXT (" - cannot allocate BIO structure")),
       -1);

  ::SSL_set_bio (this->ssl_ , this->bio_ , this->bio_);

  switch (this->type_)
    {
    case ST_CLIENT:
      ::SSL_set_connect_state (this->ssl_);
      break;

    case ST_SERVER:
      ::SSL_set_accept_state (this->ssl_);
      break;

    default:
      ACE_ERROR_RETURN
        ((LM_ERROR,
          ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream::open()")
          ACE_TEXT (" - invalid stream type")),
         -1);
    }


  ACE_SET_BITS (this->flags_, SF_STREAM_OPEN);

  this->do_SSL_state_machine (0); // use post completion

  return 0;
}

//void
//TRB_SSL_Asynch_Stream::open (ACE_HANDLE new_handle,
//                             ACE_Message_Block &block)
//{
//  TRB_Service_Handler::open (new_handle,
//                             block);
//}

// ************************************************************
//  Asynch_Operation interface
//    read
// ************************************************************
int
TRB_SSL_Asynch_Stream::read (ACE_Message_Block & message_block,
                             size_t bytes_to_read,
                             const void * act,
                             int priority,
                             int signal_number)
{
  ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

  if (ACE_BIT_DISABLED (this->flags_ ,SF_STREAM_OPEN))  
    return -1;  // not open

  if (ACE_BIT_ENABLED (this->flags_ , SF_REQ_SHUTDOWN)) 
    return -1;   // too late , ssl is closing or closed 

  // only one read operation is allowed now
  // later it will be possible to make a queue

  if (this->num_ext_reads_ != 0)
    return -1;

  new (&this->ext_read_result_) 
    TRB_Asynch_Read_Stream_Result (this->handler_,
                                   this->handle_,
                                   message_block,
                                   bytes_to_read,
                                   act,
                                   this->completion_key (),
                                   priority,
                                   signal_number,
                                   0);  // scatter flags

  ++this->num_ext_reads_;

  this->do_SSL_state_machine (0); // use post completion

  return 0;
}

// ************************************************************
//  Asynch_Operation interface
//    write
// ************************************************************
int
TRB_SSL_Asynch_Stream::write (ACE_Message_Block & message_block,
                              size_t bytes_to_write,
                              const void * act,
                              int priority,
                              int signal_number)
{
  ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

  if (ACE_BIT_DISABLED (this->flags_ ,SF_STREAM_OPEN))  
    return -1;  // not open

  if (ACE_BIT_ENABLED (this->flags_ , SF_REQ_SHUTDOWN)) 
    return -1;   // too late , ssl is closing or closed 

  // only one read operation is allowed now
  // later it will be possible to make a queue

  if (this->num_ext_writes_ != 0)
    return -1;

  new (&this->ext_write_result_) 
    TRB_Asynch_Write_Stream_Result (this->handler_,
                                   this->handle_,
                                   message_block,
                                   bytes_to_write,
                                   act,
                                   this->completion_key (),
                                   priority,
                                   signal_number,
                                   0);  // scatter flags

  ++this->num_ext_writes_;

  this->do_SSL_state_machine (0); // use post completion

  return 0;
}

// ************************************************************
//  Main SSL engine
// ************************************************************
int
TRB_SSL_Asynch_Stream::do_SSL_state_machine (int flg_cb)
{
  // this protected member should be called
  // with locked mutex_

  int retval = this->do_SSL_handshake ();

  if (retval == 0)          // handshake in progress ?
    return 0;

  if (retval < 0)
    ACE_SET_BITS(this->flags_, SF_REQ_SHUTDOWN);


  if (this->do_SSL_read (flg_cb) < 0)  // execute user read request
     ACE_SET_BITS(this->flags_, SF_REQ_SHUTDOWN);

   if (this->do_SSL_write (flg_cb) < 0 )  // execute user write request
      ACE_SET_BITS(this->flags_, SF_REQ_SHUTDOWN);

  if (ACE_BIT_DISABLED (this->flags_ , SF_REQ_SHUTDOWN))
    return 0;

  this->do_SSL_shutdown (flg_cb);

  this->notify_close ();

  return 0;
}

// ************************************************************
// do_SSL_shutdown
// return code:
// 1   SSL shutdown is finished already, success
// 0   SSL shutdown in progress
// -1  failure
// ************************************************************
int
TRB_SSL_Asynch_Stream::do_SSL_shutdown (int flg_cb)
{
  if (ACE_BIT_ENABLED (this->flags_, SF_SHUTDOWN_DONE))
    return 1;  // already done

  ACE_SET_BITS (this->flags_, SF_REQ_SHUTDOWN);

  // if we have any uncompleted user requests
  // than cancel its
  this->notify_read  (flg_cb, 0, ERR_CANCELED);
  this->notify_write (flg_cb, 0, ERR_CANCELED);

  int retval = ::SSL_shutdown (this->ssl_);

  int status = ::SSL_get_error (this->ssl_, retval);

  switch (status)
    {
    case SSL_ERROR_NONE:
    case SSL_ERROR_ZERO_RETURN:
    case SSL_ERROR_SYSCALL:
      retval = 1;
      break;

    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
    case SSL_ERROR_WANT_CONNECT:
    //   case SSL_ERROR_WANT_ACCEPT:
    case SSL_ERROR_WANT_X509_LOOKUP:
      return 0;

    default:
      this->print_error (status,
                         ACE_TEXT ("Shutdown error"));
      retval = -1;
      break;
    }

  ACE_SET_BITS (this->flags_, SF_SHUTDOWN_DONE);

  return retval;
}

// ************************************************************
// Do SSL handshake if necessary
// return code:
// 1   SSL handshake is finished already, success
// 0   SSL handshake in progress
// -1  failure
// ************************************************************
int
TRB_SSL_Asynch_Stream::do_SSL_handshake (void)
{
  if (SSL_is_init_finished (this->ssl_))
    return 1;

  if (ACE_BIT_ENABLED (this->flags_, SF_REQ_SHUTDOWN))
    return -1;

  int retval = -1;

  switch (this->type_)
    {
    case ST_CLIENT:
      retval = ::SSL_connect (this->ssl_);
      break;

    case ST_SERVER:
      retval = ::SSL_accept (this->ssl_);
      break;

    default:
      ACE_ERROR_RETURN
        ((LM_ERROR,
          ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("- invalid stream type")),
         -1);
    }

  int status = ::SSL_get_error (this->ssl_, retval);

  switch (status)
    {
    case SSL_ERROR_NONE:
      break;

    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
    case SSL_ERROR_WANT_CONNECT:
    //case SSL_ERROR_WANT_ACCEPT:
    case SSL_ERROR_WANT_X509_LOOKUP:
      return 0;

    case SSL_ERROR_ZERO_RETURN:
    case SSL_ERROR_SYSCALL:
    default:
      this->print_error (status,
                         ACE_TEXT ("Handshake error"));
      return -1;
    }

  return 1;
}

// ************************************************************
// Perform SSL_read call if necessary and notify user
// ************************************************************
int
TRB_SSL_Asynch_Stream::do_SSL_read (int flg_cb)
{
  if (this->num_ext_reads_ == 0)  // nothing to do
    return 0;

  if (ACE_BIT_ENABLED (this->flags_, SF_REQ_SHUTDOWN))
    {
      this->notify_read (flg_cb, 0, ERR_CANCELED);
      return -1;
    }

  ACE_Message_Block & mb = this->ext_read_result_.message_block ();
  size_t       bytes_req = this->ext_read_result_.bytes_requested ();

  ::ERR_clear_error ();
  const int bytes_trn = ::SSL_read (this->ssl_,
                                    mb.wr_ptr (),
                                    bytes_req);

  int status = ::SSL_get_error (this->ssl_, bytes_trn);

  switch (status)
    {
    case SSL_ERROR_NONE:
      this->notify_read (flg_cb, bytes_trn, 0);
      return 1;

    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      return 0;

    case SSL_ERROR_ZERO_RETURN:
      this->notify_read (flg_cb, 0, 0);
      return 1;

    case SSL_ERROR_SYSCALL:
      if (bytes_trn == 0)
        {
          this->notify_read (flg_cb, 0, 0);
          return 1;
        }
      // If not an EOF, then fall through to "default" case.

    default:
      break;
    }

 this->print_error (status,
                    ACE_TEXT ("SSL_read error"));
 this->notify_read (flg_cb, 0, ERR_CANCELED);

 return -1;
}

// ************************************************************
// Perform SSL_write call if necessary  and notify user
// ************************************************************
int
TRB_SSL_Asynch_Stream::do_SSL_write (int flg_cb)
{
  if (this->num_ext_writes_ == 0)  // nothing to do
    return 0;

  if (ACE_BIT_ENABLED (this->flags_, SF_REQ_SHUTDOWN))
    {
      this->notify_write (flg_cb, 0, ERR_CANCELED);
      return -1;
    }

  ACE_Message_Block & mb = this->ext_write_result_.message_block ();
  size_t       bytes_req = this->ext_write_result_.bytes_requested ();
  
  ::ERR_clear_error ();
  const int bytes_trn = ::SSL_write (this->ssl_,
                                     mb.rd_ptr (),
                                     bytes_req);

  int status = ::SSL_get_error (this->ssl_, bytes_trn);

  switch (status)
    {
    case SSL_ERROR_NONE:
      this->notify_write (flg_cb, bytes_trn, 0);
      return 1;

    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      return 0;

    case SSL_ERROR_ZERO_RETURN:
      this->notify_write (flg_cb, bytes_trn, 0);
      return 1;

    case SSL_ERROR_SYSCALL:
    default:
      break;
    }

 this->print_error (status,
                    ACE_TEXT ("SSL_write error"));
 this->notify_write(flg_cb, 0, ERR_CANCELED);

 return -1;
}

// ************************************************************
//  notify external user handler that
//  it is now to safe destroy stream
//  Return code  looks like cancel() return code
//  0  - notified               NOTIFIED
//  1  - nothing to notify      ALLDONE
//  2  - unable to notify       NOT NOTIFIED
// ************************************************************
int
TRB_SSL_Asynch_Stream::notify_close (void)
{
  if (ACE_BIT_ENABLED (this->flags_, SF_CLOSE_NTF_SENT))
    return 1;   // already sent

  if (ACE_BIT_DISABLED (this->flags_, SF_SHUTDOWN_DONE))  
    return 2;    // too early, we will do later only after shutdown

  this->bio_cancel ();

  if (this->pending_BIO_count () != 0)   // wait for all internal IO
    return 2;   // too early , we will do later

  
  if (this->proactor_ == 0)
    return 2;

  // create result for future notification
  TRB_Wakeup_Completion close_result (this,
                                      0,  // act
                                      this->completion_key (),
                                      0,  // priotity
                                      0); // signal_number

  int retval = this->proactor_->post_completion (close_result);
  
 
  if (retval >= 0)
   {
     ACE_SET_BITS (this->flags_, SF_CLOSE_NTF_SENT);
     return 0;
   }

  return 2;
}

// ************************************************************
//  notify external user handler about user write completion
//  Return code  looks like cancel() return code
//  0  - notified               NOTIFIED/CANCELED
//  1  - nothing to notify      ALLDONE
//  2  - unable to notify       NOT NOTIFIED/CANCELED
// ************************************************************

int
TRB_SSL_Asynch_Stream::notify_read (int flg_cb,
                                    int bytes_transferred,
                                    int error)
{
  if (num_ext_reads_ == 0) //nothing to notify
    return 1;

  ext_read_result_.set_completion (bytes_transferred, error);

  // make a copy - it is cheap
  // we should be ready to accept new reads when callback is active
  TRB_Asynch_Read_Stream_Result user_result (this->ext_read_result_);

  --this->num_ext_reads_;

  // This is dangerous 
  //if (flg_cb)
  //  {
  //    REVERSE_MUTEX anti_mutex (this->mutex_);
  //    ACE_MT (ACE_GUARD_RETURN (REVERSE_MUTEX, ace_mon, anti_mutex, 2));
  //    
  //    // Call completion hook
  //    user_result.dispatch ();
  //    return 0;  // success
  //  }

  int retval = this->proactor_->post_completion (user_result);

  if (retval == 0)
    {
      return 0;  // success
    }

  return 2; // unable to notify
}

// ************************************************************
//  notify external user handler about user write completion
//  Return code  looks like cancel() return code
//  0  - notified               NOTIFIED/CANCELED
//  1  - nothing to notify      ALLDONE
//  2  - unable to notify       NOT NOTIFIED/CANCELED
// ************************************************************

int
TRB_SSL_Asynch_Stream::notify_write (int flg_cb,
                                     int bytes_transferred,
                                     int error)
{
  if (num_ext_writes_ == 0) //nothing to notify
    return 1;

  ext_write_result_.set_completion (bytes_transferred, error);

  // make a copy - it is cheap
  // we should be able to accept new writes
  TRB_Asynch_Write_Stream_Result user_result (this->ext_write_result_);

  --this->num_ext_writes_;

  // This is dangerous 
  //if (flg_cb)
  //  {
  //    REVERSE_MUTEX anti_mutex (this->mutex_);
  //    ACE_MT (ACE_GUARD_RETURN (REVERSE_MUTEX, ace_mon, anti_mutex, 2));
  //    
  //    // Call completion hook
  //    user_result.dispatch ();
  //    return 0;  // success
  //  }

  int retval = this->proactor_->post_completion (user_result);

  if (retval >= 0)
    {
      return 0;  // success
    }

  return 2; // unable to notify
}

// ************************************************************
// Print SSL errors
// ************************************************************
void
TRB_SSL_Asynch_Stream::print_error (int err_ssl,
                                    const ACE_TCHAR * pText)
{
  ACE_DEBUG ((LM_DEBUG,
              "(%t) SSL-error:%d %s\n" ,
              err_ssl,
              pText));

#if OPENSSL_VERSION_NUMBER >= 0x0090601fL
  // OpenSSL < 0.9.6a doesn't have ERR_error_string_n() function.
  unsigned long lerr = 0;
  char buf[1024];

  while ((lerr = ERR_get_error()) != 0)
    {
      ERR_error_string_n (lerr, buf, sizeof buf);

      ACE_DEBUG ((LM_DEBUG, "(%t) %s\n", buf));
    }
#endif  /* OPENSSL_VERSION_NUMBER */
}

// ************************************************************
//  BIO helper functions
//  SSL library will ask BIO to do raw I/O
//  BIO will call us to do this
// ************************************************************
int
TRB_SSL_Asynch_Stream::ssl_bio_read (char * buf,
                                     size_t len,
                                     int & errval)
{
  // We do not have to acquire mutex
  // as we called already with locked mutex
  // from do_SSL_state_machine()

  errval = 0;

  size_t cur_len = this->bio_inp_msg_.length ();

  if (cur_len > 0) // there are more data buffered
    {
      const char * rd_ptr = this->bio_inp_msg_.rd_ptr ();

      if (cur_len > len)
        cur_len = len;

      ACE_OS::memcpy (buf, rd_ptr, cur_len);

      this->bio_inp_msg_.rd_ptr (cur_len); // go ahead

      return cur_len;
    }

  if (this->handle_ == ACE_INVALID_HANDLE ||
      ACE_BIT_ENABLED (this->bio_inp_flag_, BF_CANCEL))
    {
      errval = ERR_CANCELED;
      return -1;
    }

  if (this->bio_inp_errno_ != 0)     // if was error - it is permanent !
    {
      errval = this->bio_inp_errno_;
      ACE_ASSERT(errval != EINPROGRESS);
      this->bio_cancel ();
      return -1;
    }

  if (ACE_BIT_ENABLED (this->bio_inp_flag_, BF_EOS))  // End of stream
    {
      return 0;  
    }

  if (ACE_BIT_ENABLED (this->bio_inp_flag_ , BF_AIO))  // we are busy
    {
      errval = EINPROGRESS;          // SSL will try later
      return -1;
    }

  if (len < 16384)
    len = 16384;

  if (this->bio_inp_msg_.size (len) != 0)
    {
      ACE_ERROR
        ((LM_ERROR,
          ACE_TEXT ("(%t) %N:%l TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("error in ACE_Message_Block::size() ")
          ));

      errval = ENOMEM;
      this->bio_cancel ();
      return -1;
    }

  this->bio_inp_msg_.reset ();

  if (this->bio_istream_.read (
        bio_inp_msg_,  // message block
        len,           // priority
        0,             // act
        0,             // priority
        ACE_SIGRTMIN   // default signal
        ) == -1)
    {
      ACE_ERROR
        ((LM_ERROR,
          ACE_TEXT ("(%t) %N:%l TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("attempt BIO read failed")
          ));

      this->bio_cancel ();
      errval = ERR_CANCELED;  //EINVAL;
      return -1;     
    }

  ACE_SET_BITS (this->bio_inp_flag_, BF_AIO);  // AIO is active
  errval = EINPROGRESS;          // SSL will try later
  return -1;
}


int
TRB_SSL_Asynch_Stream::ssl_bio_write (const char * buf,
                                      size_t len,
                                      int & errval)
{
  // We do not have to acquire mutex
  // as we called already with locked mutex
  // from do_SSL_state_machine

  errval = 0;

  if (this->handle_ == ACE_INVALID_HANDLE ||
      ACE_BIT_ENABLED (this->bio_out_flag_, BF_CANCEL))
    {
      errval = ERR_CANCELED;
      return -1;
    }

  if (this->bio_out_errno_ != 0)      // no recovery
    {
      errval = this->bio_out_errno_;
      ACE_ASSERT(errval != EINPROGRESS);
      this->bio_cancel ();
      return -1;
    }

  if (ACE_BIT_ENABLED (this->bio_out_flag_, BF_AIO))  // sorry, we are busy
    {
      errval = EINPROGRESS;   // try later
      return -1;
    }

  if (this->bio_out_msg_.size (len) != 0)
    {
      ACE_ERROR
        ((LM_ERROR,
          ACE_TEXT ("(%t) %N:%l TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("error in ACE_Message_Block::size() ")
          ));

      errval = ENOMEM;
      this->bio_cancel ();
      return -1;
    }

  this->bio_out_msg_.reset ();
  
  if (this->bio_out_msg_.copy (buf, len) == -1)
    {
      ACE_ERROR
        ((LM_ERROR,
          ACE_TEXT ("(%t) %N:%l TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("error in ACE_Message_Block::copy() ")
          ));

      this->bio_cancel ();
      errval = ENOMEM;
      return -1;
    }


  if (this->bio_ostream_.write (
        this->bio_out_msg_, // message block
        len,          // priority
        0,            // act
        0,            // priority
        ACE_SIGRTMIN  // default signal
        ) == -1)
    {
      ACE_ERROR
        ((LM_ERROR,
          ACE_TEXT ("(%t) %N:%l TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("attempt BIO write failed")
          ));

      this->bio_cancel ();
      errval = ERR_CANCELED;  //EINVAL;
      return -1;           
    }

  ACE_SET_BITS (this->bio_out_flag_, BF_AIO);  // AIO is active
  errval = 0;                                  // Ok, go ahead

  return len;
}

void 
TRB_SSL_Asynch_Stream::bio_cancel ()
{
  // attempt to cancel internal, i.e. user's read/write
  // do it only once !!!
  if (ACE_BIT_DISABLED (this->bio_inp_flag_ , BF_CANCEL ))
    {
       this->bio_istream_.cancel ();
       this->bio_istream_.close ();
       ACE_SET_BITS (this->bio_inp_flag_ , BF_CANCEL);
    }

  if (ACE_BIT_DISABLED (this->bio_out_flag_ , BF_CANCEL ))
    {
       this->bio_ostream_.cancel ();
       this->bio_ostream_.close ();
       ACE_SET_BITS (this->bio_out_flag_ , BF_CANCEL);
    }

  this->close_handle ();
}

// ************************************************************
//  Internal IO handlers
//  virtual from TRB_Service_Handler
// ************************************************************
void
TRB_SSL_Asynch_Stream::handle_write_stream (
  const TRB_Asynch_Write_Stream::Result &result)
{
  ACE_MT (ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_));

  ACE_CLR_BITS (this->bio_out_flag_, BF_AIO);

  ACE_Message_Block & mb = result.message_block ();

  size_t bytes_req = result.bytes_to_write ();
  size_t bytes_trn = result.bytes_transferred ();
  u_long errval    = result.error ();
  size_t len       = bytes_req - bytes_trn;

  if (errval != 0)                    // error ?
    {
      this->bio_out_errno_ = errval;  // save error code
      this->bio_cancel ();
    }
  else if (len > 0)                   // TCP/IP overloaded ?
    {                                 // continue, rd_ptr at right place
      if (this->bio_ostream_.write (
            mb,          // message block
            len,         // priority
            0,           // act
            0,           // priority
            ACE_SIGRTMIN // default signal
            ) == 0)
        {
          ACE_SET_BITS (this->bio_out_flag_, BF_AIO);
          return;
        }

      ACE_ERROR
        ((LM_ERROR,
          ACE_TEXT ("(%t) TRB_SSL_Asynch_Stream %p\n"),
          ACE_TEXT ("attempt BIO write failed")
          ));

      this->bio_cancel ();
      this->bio_out_errno_ = ERR_CANCELED;
    }

  this->do_SSL_state_machine (1); //use direct call

  return;
}

void
TRB_SSL_Asynch_Stream::handle_read_stream (
  const TRB_Asynch_Read_Stream::Result &result)
{
  ACE_MT (ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_));

  ACE_CLR_BITS (this->bio_inp_flag_, BF_AIO);

  size_t bytes_trn = result.bytes_transferred ();
  u_long errval    = result.error ();

  if (errval != 0)                                 // error ?
    {
     this->bio_inp_errno_ = errval;                // save error code
     this->bio_cancel ();
    }
  else if (bytes_trn == 0)                         // end of stream ?
    {
      ACE_SET_BITS (this->bio_inp_flag_, BF_EOS);  // set flag EOS
      this->bio_cancel ();
    }

  this->do_SSL_state_machine (1); // use direct call

  return;
}

void
TRB_SSL_Asynch_Stream::handle_wakeup (void)
{
  TRB_Handler * user_handler = 0;

  {
    ACE_MT (ACE_GUARD (ACE_SYNCH_MUTEX, ace_mon, this->mutex_));

    ACE_SET_BITS (this->flags_, SF_DELETE_ENABLE);

    user_handler = this->handler_;
  }

  if (user_handler != 0)
    user_handler->handle_wakeup();
}

int
TRB_SSL_Asynch_Stream::pending_BIO_count (void)
{
  int ret = 0;

  if (ACE_BIT_ENABLED (this->bio_inp_flag_ , BF_AIO))
    ++ret;

  if (ACE_BIT_ENABLED (this->bio_out_flag_ , BF_AIO))
    ++ret;

  return ret;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif  /* OPENSSL_VERSION_NUMBER > 0x0090581fL && (ACE_WIN32 ||
           ACE_HAS_AIO_CALLS) */
