/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Proactor.h
 *
 *  Proactor.h,v 4.82 2002/05/28 11:08:38 dhinton Exp
 *
 *  @author Irfan Pyarali <irfan@cs.wustl.edu>
 *  @author Tim Harrison <harrison@cs.wustl.edu>
 *  @author Alexander Babu Arulanthu <alex@cs.wustl.edu>
 *  @author Alexander Libman <alibman@ihug.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_PROACTOR_H 
#define TPROACTOR_PROACTOR_H 

#include "ace/pre.h"
#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if ((defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)))
// This only works on Win32 platforms and on Unix platforms supporting
// POSIX aio calls.

#  include "TProactor/Asynch_IO.h"
#  include "TProactor/Proactor_Impl.h"
#  include "ace/Thread_Manager.h"
#  include "ace/Timer_Queue.h"
#  include "ace/Timer_List.h"
#  include "ace/Timer_Heap.h"
#  include "ace/Timer_Wheel.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// Forward declarations.
//class TRB_Proactor_Impl;
class TRB_Proactor_Timer_Handler;

/**
 * @class TRB_Proactor_Handle_Timeout_Upcall
 *
 * @brief Functor for <ACE_Timer_Queue>.
 *
 * This class implements the functor required by the Timer
 * Queue to call <handle_timeout> on TRB_Handlers.
 */


class TPROACTOR_Export TRB_Proactor_Handle_Timeout_Upcall
{

  /// Type def for the timer queue.
  typedef ACE_Timer_Queue_T<TRB_Handler *,
                            TRB_Proactor_Handle_Timeout_Upcall,
                            ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_QUEUE;

  /// The main Proactor class has special permissions.
  friend class TRB_Proactor;

public:
  /// Constructor.
  TRB_Proactor_Handle_Timeout_Upcall (void);

  /// This method is called when a timer is registered.
  int registration (TIMER_QUEUE &timer_queue,
                    TRB_Handler *handler,
                    const void *arg);

  /// This method is called before the timer expires.
  int preinvoke (TIMER_QUEUE &timer_queue,
                 TRB_Handler *handler,
                 const void *arg,
                 int recurring_timer,
                 const ACE_Time_Value &cur_time,
                 const void *&upcall_act);

  /// This method is called when the timer expires.
  int timeout (TIMER_QUEUE &timer_queue,
               TRB_Handler *handler,
               const void *arg,
               int recurring_timer,
               const ACE_Time_Value &cur_time);

  /// This method is called after the timer expires.
  int postinvoke (TIMER_QUEUE &timer_queue,
                  TRB_Handler *handler,
                  const void *arg,
                  int recurring_timer,
                  const ACE_Time_Value &cur_time,
                  const void *upcall_act);

  /// This method is called when a handler is canceled.
  int cancel_type (TIMER_QUEUE &timer_queue,
                   TRB_Handler *handler,
                   int dont_call_handle_close,
                   int &requires_reference_counting);

  /// This method is called when a timer is canceled.
  int cancel_timer (TIMER_QUEUE &timer_queue,
                    TRB_Handler *handler,
                    int dont_call_handle_close,
                    int requires_reference_counting);

  /// This method is called when the timer queue is destroyed and the
  /// timer is still contained in it.
  int deletion (TIMER_QUEUE &timer_queue,
                TRB_Handler *handler,
                const void *arg);

protected:
  /// Set the proactor. This will fail, if one is already set!
  int proactor (TRB_Proactor &proactor);

  /// Handle to the proactor. This is needed for posting a timer result
  /// to the Proactor's completion queue.
  TRB_Proactor *proactor_;
};


/**
 * @class TRB_Proactor
 *
 * @brief A manager for asynchronous event demultiplexing.
 *
 * See the Proactor pattern description at
 * http://www.cs.wustl.edu/~schmidt/proactor.ps.gz for more
 * details.
 */
class TPROACTOR_Export TRB_Proactor
{
  // = Here are the private typedefs that the <TRB_Proactor> uses.

  typedef ACE_Timer_Queue_Iterator_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_QUEUE_ITERATOR;
  typedef ACE_Timer_List_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_LIST;
  typedef ACE_Timer_List_Iterator_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_LIST_ITERATOR;
  typedef ACE_Timer_Heap_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_HEAP;
  typedef ACE_Timer_Heap_Iterator_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_HEAP_ITERATOR;
  typedef ACE_Timer_Wheel_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_WHEEL;
  typedef ACE_Timer_Wheel_Iterator_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_WHEEL_ITERATOR;

  // = Friendship.

  /// Timer handler runs a thread and manages the timers, on behalf of
  /// the Proactor.
  friend class TRB_Proactor_Timer_Handler;

public:
  /// Public type.
  typedef ACE_Timer_Queue_T<TRB_Handler *,
    TRB_Proactor_Handle_Timeout_Upcall,
    ACE_SYNCH_RECURSIVE_MUTEX>
  TIMER_QUEUE;

  /**
   * Constructor. If <implementation> is 0, the correct implementation
   * object will be created. <delete_implementation> flag determines
   * whether the implementation object should be deleted by the
   * Proactor or not. If <tq> is 0, a new TIMER_QUEUE is created.
   */
  TRB_Proactor (TRB_Proactor_Impl *implementation = 0,
                int delete_implementation = 0,
                TIMER_QUEUE *tq = 0);

  /// Virtual destruction.
  virtual ~TRB_Proactor (void);

  /// Get pointer to a process-wide <TRB_Proactor>.  <threads> should
  /// be part of another method.
  static TRB_Proactor *instance (size_t threads = 0);

  /// Set pointer to a process-wide <TRB_Proactor> and return existing
  /// pointer.
  static TRB_Proactor *instance (TRB_Proactor * proactor,
                                 int delete_proactor = 0);

  /// Delete the dynamically allocated Singleton.
  static void close_singleton (void);

  /// Cleanup method, used by the <ACE_Object_Manager> to destroy the
  /// singleton.
  static void cleanup (void *instance, void *arg);

  /// Name of dll in which the singleton instance lives.
  static const ACE_TCHAR *dll_name (void);

  /// Name of component--TRB_Proactor in this case.
  static const ACE_TCHAR *name (void);

  // = Proactor event loop management methods.

  /// Run the event loop until the <TRB_Proactor::handle_events> method
  /// returns -1 or the <end_event_loop> method is invoked.
  static int run_event_loop (void);

  /**
   * Run the event loop until the <TRB_Proactor::handle_events> method
   * returns -1, the <end_event_loop> method is invoked, or the
   * <ACE_Time_Value> expires.
   */
  static int run_event_loop (ACE_Time_Value &tv);

  /**
   * Instruct the <TRB_Proactor::instance> to terminate its event
   * loop.
   * This method wakes up all the threads blocked on waiting for
   * completions and end the event loop.
   */
  static int end_event_loop (void);

  /**
   * Resets the <TRB_Proactor::end_event_loop_> static so that the
   * <run_event_loop> method can be restarted.
   */
  static int reset_event_loop (void);

  /**
   * The singleton proactor is used by the <ACE_Service_Config>.
   * Therefore, we must check for the reconfiguration request and
   * handle it after handling an event.
   */
  static int check_reconfiguration (TRB_Proactor *);

  /// Report if the <TRB_Proactor::instance> event loop is finished.
  static int event_loop_done (void);

  /// Close the associated @c TRB_Proactor_Impl implementation object.
  /**
   * If @arg delete_implementation was specified to the @c open() method,
   * the implementation object is also deleted.
   */
  int close (void);

   /**
   * You can add a hook to various run_event methods and the hook will
   * be called after handling every proactor event.  If this function
   * returns 0, proactor_run_event_loop will check for the return value of
   * handle_events.  If it is -1, the the proactor_run_event_loop will return
   * (pre-maturely.)
   */
  typedef int (*PROACTOR_EVENT_HOOK)(TRB_Proactor *);

  // These methods work with an instance of a proactor.
  /**
   * Run the event loop until the
   * <TRB_Proactor::handle_events>
   * method returns -1 or the <end_proactor_event_loop> method is invoked.
   */
  int proactor_run_event_loop (PROACTOR_EVENT_HOOK = 0);

  /**
   * Run the event loop until the <TRB_Proactor::handle_events>
   * method returns -1, the
   * <end_proactor_event_loop> method is invoked,
   * or the <ACE_Time_Value>
   * expires.
   */
  int proactor_run_event_loop (ACE_Time_Value &tv,
                                       PROACTOR_EVENT_HOOK = 0);

  /**
   * Instruct the TRB_Proactor to terminate its event loop
   * and notifies the TRB_Proactor so that it can wake up
   * and close down gracefully.
   */
  int proactor_end_event_loop (void);

  /// Report if the TRB_Proactor event loop is finished.
  int proactor_event_loop_done (void);

  /// Resets the <TRB_Proactor::end_event_loop_> static so that the
  /// <run_event_loop> method can be restarted.
  int proactor_reset_event_loop (void);


  /// This method adds the <handle> to the I/O completion port. This
  /// function is a no-op function for Unix systems and returns 0;
  int register_handle (ACE_HANDLE handle,
             const void *completion_key,
             int operations);

  // = Timer management.
  /**
   * Schedule a <handler> that will expire after <time>.  If it
   * expires then <act> is passed in as the value to the <handler>'s
   * <handle_timeout> callback method.  This method returns a
   * <timer_id>. This <timer_id> can be used to cancel a timer before
   * it expires.  The cancellation ensures that <timer_ids> are unique
   * up to values of greater than 2 billion timers.  As long as timers
   * don't stay around longer than this there should be no problems
   * with accidentally deleting the wrong timer.  Returns -1 on
   * failure (which is guaranteed never to be a valid <timer_id>).
   */
  long schedule_timer (TRB_Handler &handler,
             const void *act,
             const ACE_Time_Value &time);

  long schedule_repeating_timer (TRB_Handler &handler,
           const void *act,
           const ACE_Time_Value &interval);

  // Same as above except <interval> it is used to reschedule the
  // <handler> automatically.

  /// This combines the above two methods into one. Mostly for backward
  /// compatibility.
  long schedule_timer (TRB_Handler &handler,
             const void *act,
             const ACE_Time_Value &time,
             const ACE_Time_Value &interval);

  /// Cancel all timers associated with this <handler>.  Returns number
  /// of timers cancelled.
  int cancel_timer (TRB_Handler &handler,
          int dont_call_handle_close = 1);

  /**
   * Cancel the single <TRB_Handler> that matches the <timer_id> value
   * (which was returned from the <schedule> method).  If <act> is
   * non-NULL then it will be set to point to the ``magic cookie''
   * argument passed in when the <Handler> was registered.  This makes
   * it possible to free up the memory and avoid memory leaks.
   * Returns 1 if cancellation succeeded and 0 if the <timer_id>
   * wasn't found.
   */
  int cancel_timer (long timer_id,
          const void **act = 0,
          int dont_call_handle_close = 1);

  
  /**
   * Dispatch a single set of events, waiting up to a specified time limit
   * if necessary.
   * @param wait_time the time to wait for an event to occur. This is
   * a relative time. On successful return, the time is updated to
   * reflect the amount of time spent waiting for event(s) to occur.
   * @return Returns 0 if no events occur before the wait_time expires.
   * Returns 1 when a completion is dispatched. On error, returns -1
   * and sets errno accordingly.
   */
  int handle_events (ACE_Time_Value &wait_time);

  /**
   * Block indefinitely until at least one event is dispatched.
   * @return Returns 1 when a completion is dispatched. On error, returns -1
   * and sets errno accordingly.
   */
  int handle_events (void);


  /// Get timer queue.
  TIMER_QUEUE *timer_queue (void) const;

  /// Set timer queue.
  void timer_queue (TIMER_QUEUE *timer_queue);

  /**
   * Get the event handle.
   * It is a no-op in POSIX platforms and it returns
   * ACE_INVALID_HANDLE.
   */
  ACE_HANDLE get_handle (void) const;

  /// Get the implementation class.
  TRB_Proactor_Impl *implementation (void) const;

  // = Factory methods for the operations

  template <class BASE_RESULT>
  int start (const BASE_RESULT & result);

  /**
   * Post a result to the completion port of the Proactor.
   * The real completion result will be created by Proactor,
   * so original result is used to copy all required information
   * into real(implementation) result
   */
  template <class BASE_RESULT>
  int post_completion (const BASE_RESULT & result);


  /**
   * Post <how_many> completions to the completion port so that all
   * threads can wake up. This is used in conjunction with the
   * <run_event_loop>.
   */
  static int post_wakeup_completions (int how_many);

  /**
   * Post <how_many> completions to the completion port so that all
   * threads can wake up. This is used in conjunction with the
   * <run_event_loop>. Default implementation is provided.
   */
  int proactor_post_wakeup_completions (int how_many);

  int cancel_aio (ACE_HANDLE h);
  int cancel_aio (TRB_Handler * handler);
  int cancel_all_aio (void);
                                                       

protected:

  /// Set the implementation class.
  void implementation (TRB_Proactor_Impl *implementation);

  /// Delegation/implementation class that all methods will be
  /// forwarded to.
  TRB_Proactor_Impl *implementation_;

  /// Flag used to indicate whether we are responsible for cleaning up
  /// the implementation instance.
  int delete_implementation_;

  /// Pointer to a process-wide <TRB_Proactor>.
  static TRB_Proactor *proactor_;

  /// Must delete the <proactor_> if non-0.
  static int delete_proactor_;

  /// Handles timeout events.
  TRB_Proactor_Timer_Handler *timer_handler_;

  /// This will manage the thread in the Timer_Handler.
  ACE_Thread_Manager thr_mgr_;

  /// Timer Queue.
  TIMER_QUEUE *timer_queue_;

  /// Flag on whether to delete the timer queue.
  int delete_timer_queue_;

  /// Terminate the proactor event loop.
  sig_atomic_t end_event_loop_;

  /// Number of threads in the event loop.
  sig_atomic_t event_loop_thread_count_;

  /// Mutex to protect work with lists.
  ACE_SYNCH_MUTEX mutex_;


private:
  /// Deny access since member-wise won't work...
  TRB_Proactor (const TRB_Proactor &);
  TRB_Proactor &operator= (const TRB_Proactor &);
};

template <class BASE_RESULT>
int
TRB_Proactor::start (const BASE_RESULT & result)
{
  // for performance do not check 
  //if (this->implementation () == 0)
  //  return 0;
  TRB_Asynch_Result_Impl * result_impl =
    this->implementation ()->create_result_impl (result);

  if (result_impl == 0)
    return -1;

  return result_impl->start ();
}

template <class BASE_RESULT>
int
TRB_Proactor::post_completion (const BASE_RESULT & result)
{
  // for performance do not check 
  //if (this->implementation () == 0)
  //  return 0;
  TRB_Asynch_Result_Impl * result_impl =
    this->implementation ()->create_result_impl (result);

  if (result_impl == 0)
    return -1;

  return result_impl->post ();
}

ACE_END_VERSIONED_NAMESPACE_DECL

#  if defined (__ACE_INLINE__)
#    include "TProactor/Proactor.inl"
#  endif /* __ACE_INLINE__ */

#else /* NOT WIN32 or POSIX with AIO features. */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class ACE_Time_Value;

class TPROACTOR_Export TRB_Proactor
{
public:
  class Timer_Queue {};
  TRB_Proactor (size_t /* number_of_threads */ = 0,
    Timer_Queue * /* tq */ = 0) {}
  virtual int handle_events (void) { return -1; }
  virtual int handle_events (ACE_Time_Value &) { return -1; }

  /// Placeholder to enable compilation on non-Win32 platforms
  static TRB_Proactor *instance (size_t threads = 0);

  /// Placeholder to enable compilation on non-Win32 platforms
  static TRB_Proactor *instance (TRB_Proactor *);

  /// Placeholder to enable compilation on non-Win32 platforms
  static void close_singleton (void);

  /// Placeholder to enable compilation on non-Win32 platforms
  static int run_event_loop (void);

  /// Placeholder to enable compilation on non-Win32 platforms
  static int run_event_loop (ACE_Time_Value &tv);

  /// Placeholder to enable compilation on non-Win32 platforms
  static int end_event_loop (void);

  /// Placeholder to enable compilation on non-Win32 platforms
  static sig_atomic_t event_loop_done (void);
};

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 && !ACE_HAS_WINCE || ACE_HAS_AIO_CALLS*/

#include "ace/post.h"

#endif //TPROACTOR_PROACTOR_H 
