#ifndef ACE_SSL_ACCEPTOR_CPP
#define ACE_SSL_ACCEPTOR_CPP

#include "ace/ACE.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "SSL_Acceptor.h"


ACE_RCSID (ace,
           SSL_Acceptor,
           "SSL_Acceptor.cpp")

ACE_ALLOC_HOOK_DEFINE(ACE_SSL_Acceptor)



template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1>
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::ACE_SSL_Acceptor (ACE_Reactor *reactor,
                                                              int use_select)
  : ACE_Acceptor<SVC_HANDLER,ACE_PEER_ACCEPTOR_2> (reactor, use_select)
{
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1>
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::ACE_SSL_Acceptor
  (const ACE_PEER_ACCEPTOR_ADDR &addr,
   ACE_Reactor *reactor,
   int flags,
   int use_select,
   int reuse_addr)
  : ACE_Acceptor<SVC_HANDLER,ACE_PEER_ACCEPTOR_2> (reactor, use_select)
{
  ACE_TRACE ("ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::ACE_SSL_Acceptor");

  if (this->open (addr,
                  reactor,
                  flags,
                  use_select,
                  reuse_addr) == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_LIB_TEXT ("%p\n"),
                ACE_LIB_TEXT ("ACE_SSL_Acceptor::ACE_SSL_Acceptor")));
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1>
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::~ACE_SSL_Acceptor (void)
{
  ACE_TRACE ("ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::~ACE_SSL_Acceptor");
  this->handle_close ();
}


template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::info (ACE_TCHAR **strp,
                                                      size_t length) const
{
  ACE_TRACE ("ACE_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::info");
  ACE_TCHAR buf[BUFSIZ];
  ACE_TCHAR addr_str[BUFSIZ];
  ACE_PEER_ACCEPTOR_ADDR addr;

  if (this->acceptor ().get_local_addr (addr) == -1)
    return -1;
  else if (addr.addr_to_string (addr_str, sizeof addr_str) == -1)
    return -1;

  ACE_OS::sprintf (buf,
                   ACE_LIB_TEXT ("%s\t %s %s"),
                   ACE_LIB_TEXT ("ACE_SSL_Acceptor"),
                   addr_str,
                   ACE_LIB_TEXT ("# SSL_acceptor factory\n"));

  if (*strp == 0 && (*strp = ACE_OS::strdup (buf)) == 0)
    return -1;
  else
    ACE_OS::strsncpy (*strp, buf, length);
  return ACE_static_cast (int, ACE_OS::strlen (buf));
}


// Template Method that makes a SVC_HANDLER (using the appropriate
// creation strategy), accept the connection into the SVC_HANDLER, and
// then activate the SVC_HANDLER.

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::handle_input (ACE_HANDLE listener)
{
  ACE_TRACE ("ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::handle_input");
  ACE_Handle_Set conn_handle;

  // Default is "timeout (0, 0)," which means "poll."
  ACE_Time_Value timeout;
#  if defined (ACE_WIN64)
  // This arg is ignored on Windows and causes pointer truncation
  // warnings on 64-bit compiles.
  int select_width = 0;
#  else
  int select_width = int (listener) + 1;
#  endif /* ACE_WIN64 */

  do
    {
      // Create a service handler, using the appropriate creation
      // strategy.

      SVC_HANDLER *svc_handler = 0;

      if (this->make_svc_handler (svc_handler) == -1)
        {
          if (ACE::debug () > 0)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_LIB_TEXT ("%p\n"),
                        ACE_LIB_TEXT ("make_svc_handler")));
          return 0;
        }
      // Accept connection into the Svc_Handler.

      else if (this->accept_svc_handler (svc_handler) == -1)
        {
          // Note that <accept_svc_handler> closes the <svc_handler>
          // on failure.
          if (ACE::debug () > 0)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_LIB_TEXT ("%p\n"),
                        ACE_LIB_TEXT ("accept_svc_handler")));
          return 0;
        }

      // Activate the <svc_handler> using the designated concurrency
      // strategy (note that this method becomes responsible for
      // handling errors and freeing up the memory if things go
      // awry...).
      else if (this->make_and_activate_ssl_handler (svc_handler) == -1)
        {
          // Note that <activate_svc_handler> closes the <svc_handler>
          // on failure.

          if (ACE::debug () > 0)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_LIB_TEXT ("%p\n"),
                        ACE_LIB_TEXT ("make_and_activate_ssl_handler")));
          return 0;
        }

      conn_handle.set_bit (listener);
    }

  // Now, check to see if there is another connection pending and
  // break out of the loop if there is none.
  while (this->use_select_
         && ACE_OS::select (select_width,
                            conn_handle,
                            0,
                            0,
                            &timeout) == 1);
  return 0;
}



template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::make_and_activate_ssl_handler (SVC_HANDLER * svc_handler)
{
  ACE_TRACE ("ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::make_and_activate_ssl_handler");

  SSL_SVC_HANDLER<SVC_HANDLER,ACE_PEER_ACCEPTOR_2> * ssl_handler = 0;
  
  //ACE_NEW_NORETURN (ssl_handler,
  //                  SSL_SVC_HANDLER<SVC_HANDLER,ACE_PEER_ACCEPTOR_2>(this, svc_handler));

  ssl_handler = new  SSL_SVC_HANDLER<SVC_HANDLER,ACE_PEER_ACCEPTOR_2> (this, svc_handler);



  if (ssl_handler == 0)
    {
      svc_handler->close (0);
      return -1;
    }

  if (ssl_handler->open() == -1)
    {
      delete ssl_handler;
      return -1;
    }

  return 0;
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::deferred_activate (SVC_HANDLER * svc_handler)
{
  return this->activate_svc_handler(svc_handler);
}

//////////////////////////////////////////////////////////////////////////
//
//                    SSL_SVC_HANDLER
//  Performs event-driven SSL handshake
//
//////////////////////////////////////////////////////////////////////////

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> 
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::SSL_SVC_HANDLER (ACE_SSL_Acceptor<SVC_HANDLER, ACE_PEER_ACCEPTOR_2> * acceptor,
                                 SVC_HANDLER * svc_handler)
  : acceptor_   (acceptor),
    svc_handler_(svc_handler),
    success_    (0),
    mask_       (0)
//    flags_      (flags)
{
  ACE_ASSERT (svc_handler != 0);

  this->reactor (acceptor->reactor ());
  svc_handler_->reactor (this->reactor());

}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> 
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::~SSL_SVC_HANDLER()
{
  this->reactor(0);

  if (this->success_)
    this->acceptor_->deferred_activate (this->svc_handler_);
  else
    this->svc_handler_->close ();
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::open()
{
  ACE_HANDLE h =this->svc_handler_->peer().peer().get_handle();

  this->svc_handler_->peer().set_handle (h);


  if (this->svc_handler_->peer ().enable (ACE_NONBLOCK) == -1)
    return -1;

  this->mask_ = ACE_Event_Handler::READ_MASK|
                ACE_Event_Handler::WRITE_MASK;
    
  return this->reactor()->register_handler (this, mask_);
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::handle_output(ACE_HANDLE fd)
{
  return this->handle_input (fd);
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::handle_input (ACE_HANDLE fd)
{
  int rc = this->do_ssl_handshake();

  switch (rc)
    {
    case 0: // all done
      this->success_ = 1;
      return -1;

    case 1: // SSL_WANT_READ
      return this->set_mask (ACE_Event_Handler::READ_MASK);

    case 2: // SSL_WANT_WRITE
      return this->set_mask (ACE_Event_Handler::WRITE_MASK);

    default: // handshake error
      break;
    }

  return -1;
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
  this->reactor()->remove_handler(this,
                                  ACE_Event_Handler::ALL_EVENTS_MASK |
                                  ACE_Event_Handler::DONT_CALL);  // Don't call handle_close


  delete this;
  return 0;
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::set_mask(ACE_Reactor_Mask new_mask)
{
  if (!ACE_BIT_CMP_MASK(this->mask_, new_mask, new_mask))
    {
      if (this->reactor()->schedule_wakeup  (this, new_mask) == -1)
        return -1;
    }

  ACE_Reactor_Mask off_mask = this->mask_ & ~new_mask;

  if (off_mask != ACE_Event_Handler::NULL_MASK)
    {
      if (this->reactor()->cancel_wakeup  (this, off_mask) == -1)
        return -1;
    }

  this->mask_ = new_mask;

  return 0;
}

template <class SVC_HANDLER, ACE_PEER_ACCEPTOR_1> int
SSL_SVC_HANDLER<SVC_HANDLER, ACE_PEER_ACCEPTOR_2>::do_ssl_handshake()
{
  SSL *ssl = this->svc_handler_->peer().ssl ();

  if (SSL_is_init_finished (ssl))
    return 0;

  if (!SSL_in_accept_init (ssl))
    ::SSL_set_accept_state (ssl);


  int status =::SSL_accept (ssl);

  switch (::SSL_get_error (ssl, status))
    {
        case SSL_ERROR_NONE:
          return 0;                    // Done

        case SSL_ERROR_WANT_WRITE:
          return 2;

        case SSL_ERROR_WANT_READ:
          return 1;

        case SSL_ERROR_ZERO_RETURN:
          return -1;

        case SSL_ERROR_SYSCALL:
          if (ACE_OS::set_errno_to_last_error () == EWOULDBLOCK)
            {
              if (SSL_want_write (ssl))
                return 2;
              else if (SSL_want_read (ssl))
                return 1;
            }
          ACE_SSL_Context::report_error ();
          break;

        default:
          ACE_SSL_Context::report_error ();
          break;
    }

  return -1;
}

#endif /* ACE_SSL_ACCEPTOR_CPP */
