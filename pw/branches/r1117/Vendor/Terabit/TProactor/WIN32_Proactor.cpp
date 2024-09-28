// WIN32_Proactor.cpp,v 4.30 2002/10/05 00:25:54 shuston Exp

// ACE_RCSID(ace, Proactor, "WIN32_Proactor.cpp,v 4.30 2002/10/05 00:25:54 shuston Exp")

#include "TProactor/WIN32_Proactor.h"

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE))
// WIN implemenatation of the Proactor.

#include "ace/Log_Msg.h"
#include "ace/Object_Manager.h"
#include "ace/OS_NS_errno.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_sys_socket.h"

#include "ace/ACE.h"
#include "ace/Countdown_Time.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// *********************************************************************
//
// *********************************************************************

TRB_WIN32_Proactor::TRB_WIN32_Proactor (size_t number_of_threads,
                                        int used_with_reactor_event_loop)
: TRB_Proactor_Impl ()
, completion_port_ (0) // This *MUST* be 0, *NOT* ACE_INVALID_HANDLE !!!
, number_of_threads_ (number_of_threads)
, used_with_reactor_event_loop_ (used_with_reactor_event_loop)
, allocator11_ (MAX_WIN32_RESULT1_SIZE)   // read  stream results
, allocator12_ (MAX_WIN32_RESULT1_SIZE)   // write stream results
, allocator2_  (MAX_WIN32_RESULT2_SIZE)   // accept connect dgram results
, allocator3_  (MAX_WIN32_RESULT3_SIZE)   // timer and other fake results
, pending_connects_mutex_ ()
, pending_connects_ ()

{
  ACE_DEBUG((LM_DEBUG, ACE_TEXT ("(%t)%T %s"), __FUNCTION__));

  // Create the completion port.
  this->completion_port_ = ::CreateIoCompletionPort (INVALID_HANDLE_VALUE,
                                                     0,
                                                     0,
                                                     this->number_of_threads_);
  if (this->completion_port_ == 0)
    ACE_ERROR ((LM_ERROR,
                ACE_LIB_TEXT ("TRB_WIN32_Proactor %p\n"),
                ACE_LIB_TEXT ("CreateIoCompletionPort")));

}

TRB_WIN32_Proactor::~TRB_WIN32_Proactor (void)
{
  this->close ();
}


size_t
TRB_WIN32_Proactor::number_of_threads (void) const
{
  return static_cast<size_t> (this->number_of_threads_);
}

void
TRB_WIN32_Proactor::number_of_threads (size_t threads)
{
  this->number_of_threads_ = static_cast<DWORD> (threads);
}

ACE_HANDLE
TRB_WIN32_Proactor::get_handle (void) const
{
  if (this->used_with_reactor_event_loop_)
    return this->event_.handle ();
  else
    return 0;
}

int
TRB_WIN32_Proactor::close (void)
{
  int rc = 0;
  // Close the completion port
  if (this->completion_port_ != 0)
    {
      // To avoid memory leaks we should delete all results from queue.

      for (;;)
        {
          ACE_OVERLAPPED *overlapped = 0;
          u_long bytes_transferred = 0;
          ULONG_PTR completion_key = 0;

          // Get the next asynchronous operation that completes
          BOOL res = ::GetQueuedCompletionStatus
            (this->completion_port_,
             &bytes_transferred,
             &completion_key,
             &overlapped,
             0);  // poll

          if (overlapped == 0)
            break;

          // Narrow the result.
          TRB_WIN32_Asynch_Result * win32_result = 
            static_cast<TRB_WIN32_Asynch_Result *> (overlapped);

          TRB_WIN32_Asynch_Result::release(win32_result);
        }

      rc = ACE_OS::close (this->completion_port_);
      this->completion_port_ = 0;
    }

  return rc;
}


int
TRB_WIN32_Proactor::unregister_handle (ACE_HANDLE handle)
{
  ACE_UNUSED_ARG (handle);
  return 0;
}

int
TRB_WIN32_Proactor::register_handle (ACE_HANDLE handle,
                                     const void *completion_key,
                                     int operations)
{
  ACE_UNUSED_ARG (operations);

  ULONG_PTR comp_key (reinterpret_cast<ULONG_PTR> (completion_key));

  // No locking is needed here as no state changes.
  ACE_HANDLE cp = ::CreateIoCompletionPort (handle,
                                            this->completion_port_,
                                            comp_key,
                                            this->number_of_threads_);
  if (cp == 0)
    {
      ACE_OS::set_errno_to_last_error ();
      // If errno == ERROR_INVALID_PARAMETER, then this handle was
      // already registered.
      if (errno != ERROR_INVALID_PARAMETER)
        {
          if (ACE::debug ())
            {
              ACE_DEBUG ((LM_ERROR,
                          ACE_LIB_TEXT ("%p\n"),
                          ACE_LIB_TEXT ("CreateIoCompletionPort")));
            }
          return -1;
        }
    }
  return 0;
}

// *****************************************************************************
//
// *****************************************************************************
int 
TRB_WIN32_Proactor::get_max_result_size (void) const
{
  return MAX_WIN32_RESULT_SIZE;
}

template <class WIN32_RESULT>
WIN32_RESULT * 
create_win32_result (const typename WIN32_RESULT::User_Result &  result, 
                     ACE_Allocator  *allocator,
                     TRB_WIN32_Proactor *win32_proactor)
{
  WIN32_RESULT *win32_result = 0;

  TRB_Handler *handler = result.get_handler ();

  ACE_Allocator * user_allocator = 0;

  //if (handler)
  //  {
  //    user_allocator = handler->allocator ();
  //    if (user_allocator)
  //      allocator = user_allocator;
  //  }
  
  void *area = allocator->malloc(sizeof(WIN32_RESULT));

  ACE_NEW_MALLOC_RETURN 
        (win32_result,
         static_cast<WIN32_RESULT *> (area),
         WIN32_RESULT(allocator, area, result, win32_proactor),
         0);

  return win32_result;
}

// *****************************************************************************
// Create Result implementation
// *****************************************************************************
TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Read_Stream_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Read_Stream_Result>
                          (result,
                           &this->allocator11_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Write_Stream_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Write_Stream_Result>
                          (result,
                           &this->allocator12_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Read_Dgram_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Read_Dgram_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Write_Dgram_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Write_Dgram_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Connect_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Connect_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Accept_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Accept_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Transmit_File_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_Transmit_File_Result>
                          (result,
                           &this->allocator3_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_Timer & result)
{
   return create_win32_result<TRB_WIN32_Asynch_Timer>
                          (result,
                           &this->allocator3_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Wakeup_Completion & result)
{
  return create_win32_result<TRB_WIN32_Wakeup_Completion>
                          (result,
                           &this->allocator3_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_WIN32_Proactor::create_result_impl (const TRB_Asynch_User_Result & result)
{
  return create_win32_result<TRB_WIN32_Asynch_User_Result>
                          (result,
                           &this->allocator3_,
                           this);
}

// *****************************************************************************
// AIO post completion (fake result initiator)
// *****************************************************************************
int
TRB_WIN32_Proactor::post (TRB_WIN32_Asynch_Result *win32_result)
{
  if (win32_result == 0)
    return -1;

  TRB_Asynch_Result & user_result = win32_result->get_original_result ();
  
  user_result.set_op_flags (TRB_Asynch_Result::FLG_FAKE_RESULT);

  ULONG_PTR comp_key = reinterpret_cast<ULONG_PTR> (user_result.completion_key());

  // Post a completion
  if (::PostQueuedCompletionStatus (this->completion_port_,           // completion port
                                    user_result.bytes_transferred (), // xfer count
                                    comp_key,                         // completion key
                                    win32_result                      // overlapped
                                ) == FALSE)
    {
       //if (ACE::debug ())
        {
          ACE_DEBUG ((LM_ERROR,
                      ACE_LIB_TEXT ("%p\n"),
                      ACE_LIB_TEXT ("PostQueuedCompletionStatus failed")));
        }

      //!!!! TRB_Asynch_Result_Impl will call free ()!!!! 
      //TRB_WIN32_Asynch_Result::release (win32_result);
      
      return -1;
    }

  // Grab the event associated with the Proactor
  HANDLE handle = this->get_handle ();
  // If Proactor event is valid, signal it
  if (handle != ACE_INVALID_HANDLE && handle != 0)
    {
      ACE_OS::event_signal (&handle);
    }

  return 0;
}


// ********************************************************************
//  handling events
// ********************************************************************
int
TRB_WIN32_Proactor::handle_signal (int, siginfo_t *, ucontext_t *)
{
  // Perform a non-blocking "poll" for all the I/O events that have
  // completed in the I/O completion queue.

  int result = 0;

  for (ACE_Time_Value timeout (0, 0);
       ;
       )
    {
      result = this->handle_events (timeout);

      if (result != 1)
        break;
    }

  // If our handle_events failed, we'll report a failure to the
  // Reactor.
  return result == -1 ? -1 : 0;
}

int
TRB_WIN32_Proactor::handle_close (ACE_HANDLE handle,
                                  ACE_Reactor_Mask close_mask)
{
  ACE_UNUSED_ARG (close_mask);
  ACE_UNUSED_ARG (handle);

  return this->close ();
}


int
TRB_WIN32_Proactor::handle_events (ACE_Time_Value &wait_time)
{
  // Decrement <wait_time> with the amount of time spent in the method
  ACE_Countdown_Time countdown (&wait_time);
  return this->handle_events (wait_time.msec ());
}

int
TRB_WIN32_Proactor::handle_events (void)
{
  return this->handle_events (ACE_INFINITE);
}

int
TRB_WIN32_Proactor::handle_events (unsigned long milli_seconds)
{
  ACE_OVERLAPPED *overlapped = 0;
  u_long bytes_transferred = 0;
  u_long error = 0;
  ULONG_PTR completion_key = 0;

  // Get the next asynchronous operation that completes
  BOOL rc = ::GetQueuedCompletionStatus (this->completion_port_,
                                         &bytes_transferred,
                                         &completion_key,
                                         &overlapped,
                                         milli_seconds);
  if (rc == FALSE && overlapped == 0)
    {
      ACE_OS::set_errno_to_last_error ();

      switch (errno)
        {
        case WAIT_TIMEOUT:
          errno = ETIME;
          return 0;

        case ERROR_SUCCESS:
          // Calling GetQueuedCompletionStatus with timeout value 0
          // returns FALSE with extended errno "ERROR_SUCCESS" errno =
          // ETIME; ?? I don't know if this has to be done !!
          return 0;

        default:
          break;
        }
        
        //if (ACE::debug ())
          {
            ACE_DEBUG ((LM_ERROR, ACE_LIB_TEXT ("(%t)%T GetQueuedCompletionStatus error=%d\n"),
                        errno));
          }

        return -1;
    }

 
  // Narrow the result.
  TRB_WIN32_Asynch_Result * win32_result = 
      static_cast<TRB_WIN32_Asynch_Result *> (overlapped);

  if (win32_result == 0)
    return 0;

  if (rc == FALSE)
  {
    error = ACE_OS::set_errno_to_last_error ();
    
    //Wine реализация GetQueuedCompletionStatus при закрытии соединения
    //возвращает понятный код 64, а затем, более странный код 233  
    //(ERROR_PIPE_NOT_CONNECTED). Хуже того, при получения кода 233 значение 
    //overlapped указывает на некорректный объект, вызов виртуального 
    //метода которого, приводит к падению.
    //Поэтому в качестве workaround будем отдельно обрабатывать код 233 
    //под Wine 
    #ifdef WINE_VERSION_WORKAROUND
      if( error == 233 )
        return 0;
    #endif
  }

  win32_result->complete (bytes_transferred,
                          reinterpret_cast<const void*> (completion_key),
                          error);

  win32_result->dispatch ();
  return 1;
}


int
TRB_WIN32_Proactor::cancel_aio (ACE_HANDLE h)
{
#if (defined (ACE_HAS_WINNT4) && (ACE_HAS_WINNT4 != 0)) \
    && (   (defined (_MSC_VER) && (_MSC_VER > 1020)) \
        || (defined (__BORLANDC__) && (__BORLANDC__ >= 0x530)))
  // All I/O operations that are canceled will complete with the error
  // ERROR_OPERATION_ABORTED. All completion notifications for the I/O
  // operations will occur normally.

  // @@ This API returns 0 on failure. So, I am returning -1 in that
  //    case. Is that right? (Alex).

  int result = (int) ::CancelIo (h);

  if (result == 0)
    // Couldnt cancel the operations.
    return 2;

  // result is non-zero. All the operations are cancelled then.
  return 0;

#else /* Not ACE_HAS_WINNT4 && ACE_HAS_WINNT4!=0 && _MSC... */
  ACE_NOTSUP_RETURN (-1);
#endif /* ACE_HAS_AIO_CALLS */
}

int
TRB_WIN32_Proactor::cancel_aio (TRB_Handler * handler)
{
  //return this->cancel_aio (handler->handle());
  std::set<TRB_WIN32_Asynch_Connect_Result*>::iterator it1 =
      this->pending_connects_.begin ();

  std::set<TRB_WIN32_Asynch_Connect_Result*>::iterator it2 =
      this->pending_connects_.end ();

  for (; it1 != it2; ++ it1)
    {
      TRB_WIN32_Asynch_Connect_Result *result = (*it1);
      TRB_Asynch_Result & original = result->get_original_result ();

      if (original.get_handler () == handler &&
          ACE_BIT_ENABLED(original.op_flags(), TRB_Asynch_Result::FLG_NEW_HANDLE))
        {
            ACE_OS::closesocket (original.handle ());
            original.set_handle(ACE_INVALID_HANDLE);
        }
    }

  return 0;
}

int
TRB_WIN32_Proactor::cancel_all_aio (void)
{
  // Couldnt cancel the operations.
  return 2;
}

void
TRB_WIN32_Proactor::add_connect(TRB_WIN32_Asynch_Connect_Result *result)
{
    ACE_GUARD (ACE_SYNCH_MUTEX, guard, this->pending_connects_mutex_);
    this->pending_connects_.insert (result);
}

void
TRB_WIN32_Proactor::remove_connect(TRB_WIN32_Asynch_Connect_Result *result)
{
    ACE_GUARD (ACE_SYNCH_MUTEX, guard, this->pending_connects_mutex_);
    this->pending_connects_.erase (result);
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 */
