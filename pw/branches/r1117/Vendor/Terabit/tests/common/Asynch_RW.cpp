/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

// ============================================================================
/**
 *  @file TRB_Asynch_RW.cpp
 *
 *  TRB_Asynch_RW.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================
#ifndef ASYNCH_RW_C
#define ASYNCH_RW_C

#include "Asynch_RW.h"

//----------------------------------------------------------
#include "ace/Version.h"

#if ((ACE_MAJOR_VERSION == 5) && (ACE_MINOR_VERSION ==3))

#include "ace/OS.h"

#else // Assume ACE 5.4.x

#include "ace/OS_NS_sys_socket.h"

#endif // ((ACE_MAJOR_VERSION == 5) && (ACE_MINOR_VERSION ==3))
//----------------------------------------------------------


template <class READER, class WRITER>
TRB_Asynch_RW_T<READER, WRITER>::TRB_Asynch_RW_T (void)
  : handle_ (ACE_INVALID_HANDLE),
    flg_owner_(0),
    flg_cancel_(0),
    completion_key_(0),
    rs_(),
    ws_()
{
  ;
}

template <class READER, class WRITER>
TRB_Asynch_RW_T<READER, WRITER>::~TRB_Asynch_RW_T (void)
{
  this->close();
}

template <class READER, class WRITER> int
TRB_Asynch_RW_T<READER, WRITER>::close(void)
{

  if (this->handle_ != ACE_INVALID_HANDLE && this->flg_owner_ != 0)
    ACE_OS::closesocket (this->handle_);

  this->handle_ = ACE_INVALID_HANDLE;

  return 0;
}

template <class READER, class WRITER> int
TRB_Asynch_RW_T<READER, WRITER>::cancel(void)
{
  if (this->flg_cancel_ == 0)
    {
      this->flg_cancel_ = 1;
    
      if (this->handle_ != ACE_INVALID_HANDLE) 
        {
           this->rs_.cancel ();
           this->ws_.cancel ();
        }
    }

  return 0;
}

template <class READER, class WRITER> int
TRB_Asynch_RW_T<READER, WRITER>::cancel_and_close(void)
{
  this->cancel();
  return this->close();
}

template <class READER, class WRITER> int
TRB_Asynch_RW_T<READER, WRITER>::open 
         (TRB_Handler &handler,
          ACE_HANDLE handle, 
          const void *completion_key,
          TRB_Proactor *proactor,
          int pass_ownership)
{

  if (this->handle_ != ACE_INVALID_HANDLE || this->flg_cancel_ != 0)
    return -1;

  this->handle_ = handle;
  this->completion_key_ = completion_key;
  this->flg_owner_ = pass_ownership;

  if (this->rs_.open(handler,
                     handle,
                     completion_key,
                     proactor) < 0)
  
    return -1;

  if (this->ws_.open(handler,
                     handle,
                     completion_key,
                     proactor) < 0)
  
    return -1;

  return 0;
}

// ****************************************************************

template <class READER, class WRITER> int
TRB_Asynch_RW_Stream_T<READER, WRITER>::read (const Buffer_Info& buf_info,
                            size_t num_bytes_to_read,
                            const void *act,
                            int priority,
                            int signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ != 0)
    return -1;

  return this->reader().read (buf_info,
                              num_bytes_to_read,
                              act,
                              priority,
                              signal_number);
}
 
template <class READER, class WRITER> int
TRB_Asynch_RW_Stream_T<READER, WRITER>::write (const Buffer_Info& buf_info,
                             size_t num_bytes_to_write,
                             const void *act,
                             int priority,
                             int signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE ||  this->flg_cancel_ != 0)
    return -1;

  return this->writer().write (buf_info,
                               num_bytes_to_write,
                               act,
                               priority,
                               signal_number);
}

// ****************************************************************

template <class READER, class WRITER> ssize_t
TRB_Asynch_RW_Dgram_T<READER, WRITER>::recv (const Buffer_Info& buf_info,  
                 size_t &             number_of_bytes_recvd,  
                 int                  flags,  
                 int                  protocol_family,
                 const void *         act,
                 int                  priority,
                 int                  signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE ||  this->flg_cancel_ != 0)
    return -1;

  return this->reader().recv (buf_info,
                              number_of_bytes_recvd,  
                              flags,  
                              protocol_family,
                              act,
                              priority,
                              signal_number);
}
 

template <class READER, class WRITER> ssize_t
TRB_Asynch_RW_Dgram_T<READER, WRITER>::send  (const Buffer_Info& buf_info,
                 size_t &            number_of_bytes_sent,  
                 int                 flags,  
                 const ACE_Addr &    remote_addr,  
                 const void *        act,  
                 int                 priority,  
                 int                 signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE ||  this->flg_cancel_ != 0)
    return -1;

  return this->writer().send  (buf_info,
                               number_of_bytes_sent,  
                               flags,  
                               remote_addr,  
                               act,  
                               priority,  
                               signal_number);
}


#endif //ASYNCH_RW_C


