/* -*- C++ -*- */
// POSIX_Proactor.cpp,v 4.55 2002/12/21 23:29:24 shuston Exp

#include "TProactor/POSIX_Proactor.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

# if defined (ACE_HAS_SYSINFO)
#   include /**/ <sys/systeminfo.h>
# endif /* ACE_HAS_SYS_INFO */

#include "TProactor/Asynch_File_Transmitter.h"

#include "ace/Log_Msg.h"


# if defined (sun)
#   include "ace/OS_NS_strings.h"
# endif /* sun */

//#include "ace/OS_NS_sys_socket.h"
#include "ace/OS_NS_signal.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// *********************************************************************
//
// *********************************************************************
int 
TRB_POSIX_Proactor::get_os_id(void)
{
  int os_id = OS_UNDEFINED;

#if defined(sun)

  os_id = OS_SUN; // set family

  char Buf [32];

  ::memset(Buf,0,sizeof(Buf));

  ACE_OS::sysinfo (SI_RELEASE , Buf, sizeof(Buf)-1);

  if (ACE_OS_String::strcasecmp (Buf , "5.6") == 0)
    os_id = OS_SUN_56;
  else if (ACE_OS_String::strcasecmp (Buf , "5.7") == 0)
    os_id = OS_SUN_57;
  else if (ACE_OS_String::strcasecmp (Buf , "5.8") == 0)
    os_id = OS_SUN_58;
  else if (ACE_OS_String::strcasecmp (Buf , "5.9") == 0)
    os_id = OS_SUN_59;
  else if (ACE_OS_String::strcasecmp (Buf , "5.10") == 0)
    os_id = OS_SUN_510;
  else if (ACE_OS_String::strcasecmp (Buf , "5.11") == 0)
    os_id = OS_SUN_511;

#elif defined(HPUX)

  os_id = OS_HPUX;   // set family

#elif defined(__sgi)

  os_id = OS_IRIX;   // set family

#elif defined(__OpenBSD)

  os_id = OS_OPENBSD; // set family

  // do the same

//#else defined (LINUX, __FreeBSD__ ...)
//setup here os_id_
#endif

  return os_id;
}

// *********************************************************************
//
// *********************************************************************
TRB_POSIX_Proactor::TRB_POSIX_Proactor (const TRB_POSIX_AIO_Config & prime_processor_cfg,
                                        const TRB_POSIX_AIO_Config & second_processor_cfg)
: TRB_Proactor_Impl ()
, os_id_            (TRB_POSIX_Proactor::get_os_id())
, flg_open_         (0)
, flg_disable_start_(0)
, mutex_            ()
, prime_config_     (prime_processor_cfg)
, second_config_    (second_processor_cfg)
, dispatcher_       (prime_config_, second_config_)
, prime_processor_  (0)
, second_processor_ (0)
, allocator11_ (MAX_POSIX_RESULT1_SIZE)   // read  stream results
, allocator12_ (MAX_POSIX_RESULT1_SIZE)   // write stream results
, allocator2_  (MAX_POSIX_RESULT2_SIZE)   // accept connect dgram results
, allocator3_  (MAX_POSIX_RESULT3_SIZE)   // timer and other fake results
{
    if (this->open() !=0)
    {
        this->close();
    }
}

TRB_POSIX_Proactor::TRB_POSIX_Proactor (size_t max_op,
                                        int sig_num,
                                        int leader_type)
: TRB_Proactor_Impl ()
, os_id_            (TRB_POSIX_Proactor::get_os_id())
, flg_open_         (0)
, flg_disable_start_(0)
, mutex_            ()
, prime_config_     (max_op,
                     (leader_type != 0)
                     ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                     : TRB_POSIX_AIO_Config::PCT_SHARED,
                     TRB_POSIX_AIO_Config::PVT_SELECT 
                    )
, second_config_    (max_op,
                     TRB_POSIX_AIO_Config::PCT_NONE
                    ) 
, dispatcher_       (prime_config_, second_config_)
, prime_processor_  (0)
, second_processor_ (0)
, allocator11_ (MAX_POSIX_RESULT1_SIZE)   // read  stream results
, allocator12_ (MAX_POSIX_RESULT1_SIZE)   // write stream results
, allocator2_  (MAX_POSIX_RESULT2_SIZE)   // accept connect dgram results
, allocator3_  (MAX_POSIX_RESULT3_SIZE)   // timer and other fake results
{
  ACE_UNUSED_ARG (sig_num);

    if (this->open()!=0)
    {
        this->close();
    }
}

TRB_POSIX_Proactor::~TRB_POSIX_Proactor (void)
{
    this->close ();
}

TRB_POSIX_Proactor::Proactor_Type 
TRB_POSIX_Proactor::get_impl_type (void)
{
  return static_cast<Proactor_Type> 
           (this->prime_config_.provider_type ());
} 

ACE_HANDLE
TRB_POSIX_Proactor::get_handle (void) const
{
   return ACE_INVALID_HANDLE;
}
int
TRB_POSIX_Proactor::open (void)
{
    ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

    ACE_DEBUG((LM_DEBUG,
        ACE_LIB_TEXT("=======Prime AIO Processor Configuration\n")));
    this->prime_config_.dump();

    ACE_DEBUG((LM_DEBUG,
        ACE_LIB_TEXT("=======Second AIO Processor Configuration\n")));
    this->second_config_.dump();

    ACE_DEBUG((LM_DEBUG,
        ACE_LIB_TEXT("===========================================\n")));

    if (this->flg_open_ != 0)
        return 0;

    //
    this->prime_processor_ = 
        this->prime_config_.create_processor (this->dispatcher_);

    if (this->prime_processor_ != 0)
    {

        if (this->prime_processor_->init () != 0)
            return -1;

        if (this->dispatcher_.add_processor (prime_processor_) != 0)
            return -1;
    }

    this->second_processor_ = 
        this->second_config_.create_processor (this->dispatcher_);

    if (this->second_processor_ != 0)
    {
        if (this->second_processor_->init () != 0)
            return -1;

        if (this->dispatcher_.add_processor (second_processor_) != 0)
            return -1;
    }

    if (this->prime_processor_ && this->prime_processor_->start () != 0)
        return -1;

    if (this->second_processor_ && this->second_processor_->start () != 0)
        return -1;

    ++this->flg_open_;

    return 0;
}

int
TRB_POSIX_Proactor::close (void)
{

    ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

    this->cancel_all_aio ();
    this->dispatcher_.close ();

    if (this->second_processor_ != 0)
    {
        this->second_processor_->stop ();
        this->second_processor_->fini ();
    
        delete this->second_processor_;
        this->second_processor_ = 0;
    }

    if (this->prime_processor_ != 0)
    {
        this->prime_processor_->stop ();
        this->prime_processor_->fini ();
    
        delete this->prime_processor_;
        this->prime_processor_ = 0;
    }

    this->flg_open_ =0;
    return 0;
}


TRB_POSIX_AIO_Processor *
TRB_POSIX_Proactor::find_processor (int operations)
{
  if (this->prime_processor_ != 0 &&
      ACE_BIT_CMP_MASK(this->prime_processor_->get_supported_operations_mask(),
                        operations,
                        operations))
    {
      return this->prime_processor_ ;
    }

  if (this->second_processor_ != 0 &&
      ACE_BIT_CMP_MASK(this->second_processor_->get_supported_operations_mask(),
                        operations,
                        operations))
    {
      return this->second_processor_ ;
    }
  return 0;
}

int
TRB_POSIX_Proactor::register_handle (ACE_HANDLE  handle,
                                     const void *completion_key,
                                     int         operations)
{
  TRB_POSIX_AIO_Processor * aio_processor = 
    this->find_processor(operations);

  if (aio_processor != 0)
     return aio_processor->register_handle (handle, 
                                            completion_key,
                                            operations);

  if (ACE_BIT_ENABLED(operations, TRB_Asynch_Result::OP_READ_MASK |
                                  TRB_Asynch_Result::OP_WRITE_MASK))
    {
      return -1;  // we need provider for these operations
    } 

  return 0;
}

int
TRB_POSIX_Proactor::unregister_handle (ACE_HANDLE handle)
{
    if (this->prime_processor_ != 0)
        this->prime_processor_->unregister_handle (handle);

    if (this->second_processor_ != 0)
        this->second_processor_->unregister_handle (handle);

    return 0;
}
// *****************************************************************************
//
// *****************************************************************************
int 
TRB_POSIX_Proactor::get_max_result_size (void) const
{
  return MAX_POSIX_RESULT_SIZE;
}

template <class POSIX_RESULT>
POSIX_RESULT * 
create_posix_result (const typename POSIX_RESULT::User_Result &  result, 
                     ACE_Allocator  *allocator,
                     TRB_POSIX_Proactor *posix_proactor)
{
  POSIX_RESULT *posix_result = 0;

  //TRB_Handler *handler = result.get_handler ();

  //ACE_Allocator * user_allocator = 0;

  //if (handler)
  //  {
  //    user_allocator = handler->allocator ();
  //    if (user_allocator)
  //      allocator = user_allocator;
  //  }
  
  void *area = allocator->malloc(sizeof(POSIX_RESULT));

  ACE_NEW_MALLOC_RETURN 
        (posix_result,
         static_cast<POSIX_RESULT *> (area),
         POSIX_RESULT(allocator, area, result, posix_proactor),
         0);

  return posix_result;
}

// *****************************************************************************
// Create Result implementation
// *****************************************************************************
TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Read_Stream_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Read_Stream_Result>
                          (result,
                           &this->allocator11_,
                           this);

}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Write_Stream_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Write_Stream_Result>
                          (result,
                           &this->allocator12_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Read_Dgram_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Read_Dgram_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Write_Dgram_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Write_Dgram_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Connect_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Connect_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Accept_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Accept_Result>
                          (result,
                           &this->allocator2_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Transmit_File_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_Transmit_File_Result>
                          (result,
                           &this->allocator3_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_Timer & result)
{
   return create_posix_result<TRB_POSIX_Asynch_Timer>
                          (result,
                           &this->allocator3_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Wakeup_Completion & result)
{
  return create_posix_result<TRB_POSIX_Wakeup_Completion>
                          (result,
                           &this->allocator3_,
                           this);
}

TRB_Asynch_Result_Impl *
TRB_POSIX_Proactor::create_result_impl (const TRB_Asynch_User_Result & result)
{
  return create_posix_result<TRB_POSIX_Asynch_User_Result>
                          (result,
                           &this->allocator3_,
                           this);
}


// *****************************************************************************
// AIO post completion (fake result initiator)
// *****************************************************************************
int
TRB_POSIX_Proactor::post (TRB_POSIX_Asynch_Result *posix_result)
{
  //ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

  //if (this->flg_open_ == 0)
  //      return -1;

  if (posix_result == 0)
    return -1;

  TRB_Asynch_Result & user_result = posix_result->get_original_result ();
  
  user_result.set_op_flags (TRB_Asynch_Result::FLG_FAKE_RESULT);

  this->dispatcher_.add_completion (posix_result);
  return 0;
}

// *****************************************************************************
// AIO initiator
// *****************************************************************************
int
TRB_POSIX_Proactor::start (TRB_POSIX_Asynch_Result *posix_result)
{
  if (posix_result == 0)
    return -1;

  TRB_Asynch_Result & user_result = posix_result->get_original_result ();
  
  user_result.clr_op_flags (TRB_Asynch_Result::FLG_FAKE_RESULT);

  int op = user_result.op_code ();
  
  
  int rc = -1;

  if (this->flg_open_ != 0 && this->flg_disable_start_ == 0)
    {
      TRB_POSIX_AIO_Processor * processor = 
        this->find_processor (op);
        
      if (processor != 0)
        {
          rc = processor->start_aio (posix_result);
        }
    }

  return rc;
}

int
TRB_POSIX_Proactor::cancel_all_aio (void)
{
  ACE_TRACE ("TRB_POSIX_Proactor::cancel_aio");

  if (this->flg_open_ == 0)
    return -1;

  this->flg_disable_start_ = 1;

  int rc1 = 1;  // ALL DONE
  int rc2 = 1;  // ALL DONE

  if (this->prime_processor_ != 0)
    rc1 =  this->prime_processor_->cancel_all ();

  if (this->second_processor_ != 0)
    rc2 =  this->second_processor_->cancel_all ();
  // ALLDONE 1
  // CANCELLED 0
  // NOT CANCELLED 2
  // ERROR  -1

  return rc1 > rc2 ? rc1 : rc2;  
}

int
TRB_POSIX_Proactor::cancel_aio (ACE_HANDLE handle)
{
  ACE_TRACE ("TRB_POSIX_Proactor::cancel_aio");

  if (this->flg_open_ == 0)
    return -1;

  int rc1 = 1;  // ALL DONE
  int rc2 = 1;  // ALL DONE

  if (this->prime_processor_ != 0)
    rc1 =  this->prime_processor_->cancel_aio (handle);

  if (this->second_processor_ != 0)
    rc2 =  this->second_processor_->cancel_aio (handle);

  return rc1 > rc2 ? rc1 : rc2;  
}

int
TRB_POSIX_Proactor::cancel_aio (TRB_Handler * handler)
{
  ACE_TRACE ("TRB_POSIX_Proactor::cancel_aio");

  if (this->flg_open_ == 0)
    return -1;

  int rc1 = 1;  // ALL DONE
  int rc2 = 1;  // ALL DONE

  if (this->prime_processor_ != 0)
    rc1 =  this->prime_processor_->cancel_aio (handler);

  if (this->second_processor_ != 0)
    rc2 =  this->second_processor_->cancel_aio (handler);

  return rc1 > rc2 ? rc1 : rc2;  
}

int
TRB_POSIX_Proactor::handle_events (ACE_Time_Value &wait_time)
{
  return this->handle_events_i (&wait_time);
}

int
TRB_POSIX_Proactor::handle_events (void)
{
  return this->handle_events_i (0);
}

int
TRB_POSIX_Proactor::handle_events_i (ACE_Time_Value *timeout)
{
    ACE_TRACE ("TRB_POSIX_Proactor::handle_events_i");

    if (this->flg_open_ == 0)
        return -1;

    return this->dispatcher_.handle_events (timeout);
}


// *********************************************************************
//
// **********************************************************************

TRB_POSIX_AIOCB_Proactor::TRB_POSIX_AIOCB_Proactor (size_t max_op, 
                                                    int sig_num,
                                                    int leader_type)
: TRB_POSIX_Proactor 
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_POSIX_AIOCB
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_DEDICATED,
                           TRB_POSIX_AIO_Config::PVT_SELECT
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_POSIX_SIG_Proactor::TRB_POSIX_SIG_Proactor (size_t max_op,
                                                int sig_num,
                                                int leader_type)
: TRB_POSIX_Proactor 
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_POSIX_SIG
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_DEDICATED,
                           TRB_POSIX_AIO_Config::PVT_SELECT
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_POSIX_CB_Proactor::TRB_POSIX_CB_Proactor (size_t max_op,
                                              int sig_num,
                                              int leader_type)
: TRB_POSIX_Proactor 
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_POSIX_CB
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_DEDICATED,
                           TRB_POSIX_AIO_Config::PVT_SELECT
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_SUN_Proactor::TRB_SUN_Proactor (size_t max_op,
                                    int sig_num,
                                    int leader_type)
: TRB_POSIX_Proactor 
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_SUN_AIO
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_DEDICATED,
                           TRB_POSIX_AIO_Config::PVT_SELECT
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_LINUX_Proactor::TRB_LINUX_Proactor (size_t max_op,
                                        int sig_num,
                                        int leader_type)
: TRB_POSIX_Proactor 
    (TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_DEDICATED,
                           TRB_POSIX_AIO_Config::PVT_LINUX_NAIO
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_EPOLL
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}
// *********************************************************************
//
// **********************************************************************

TRB_Select_Proactor::TRB_Select_Proactor (size_t max_op, 
                                          int sig_num,
                                          int leader_type)
: TRB_POSIX_Proactor 
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_SELECT
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_Poll_Proactor::TRB_Poll_Proactor (size_t max_op, 
                                      int sig_num,
                                      int leader_type)
: TRB_POSIX_Proactor
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_POLL
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_Dev_Poll_Proactor::TRB_Dev_Poll_Proactor (size_t max_op, 
                                              int sig_num,
                                              int leader_type)
: TRB_POSIX_Proactor
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_DEVPOLL
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}

TRB_Event_Poll_Proactor::TRB_Event_Poll_Proactor (size_t max_op, 
                                              int sig_num,
                                              int leader_type)
: TRB_POSIX_Proactor
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_EPOLL
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}


TRB_SUN_Port_Proactor::TRB_SUN_Port_Proactor (size_t max_op, 
                                              int sig_num,
                                              int leader_type)
: TRB_POSIX_Proactor
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_SUNPORT
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}


TRB_Kqueue_Proactor::TRB_Kqueue_Proactor (size_t max_op, 
                                          int sig_num,
                                          int leader_type)
: TRB_POSIX_Proactor
    (TRB_POSIX_AIO_Config (max_op,
                           (leader_type != 0)
                           ? TRB_POSIX_AIO_Config::PCT_DEDICATED
                           : TRB_POSIX_AIO_Config::PCT_SHARED,
                           TRB_POSIX_AIO_Config::PVT_KQUEUE
                          ),
     TRB_POSIX_AIO_Config (max_op,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
  ACE_UNUSED_ARG (sig_num);
}




TRB_Dummy_Proactor::TRB_Dummy_Proactor ()
: TRB_POSIX_Proactor
    (TRB_POSIX_AIO_Config (0,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          ),
     TRB_POSIX_AIO_Config (0,
                           TRB_POSIX_AIO_Config::PCT_NONE,
                           TRB_POSIX_AIO_Config::PVT_NONE
                          )
    )
{
}

// *****************************************************************


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
