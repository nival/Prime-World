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
//
// = LIBRARY
//    
//
// = FILENAME
//    TRB_Asynch_RW_Stream.h
//
// = DESCRIPTION
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================
#ifndef ASYNCH_RW_H
#define ASYNCH_RW_H

#include "TProactor/Asynch_IO.h"
#include "ace/OS_NS_sys_socket.h"

template <class READER, class WRITER>
class TRB_Asynch_RW 
{
public:
  typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;

  /// A do nothing constructor.
  TRB_Asynch_RW (bool flg_socket);

  /// Destructor
  virtual ~TRB_Asynch_RW (void);

  virtual int open (TRB_Handler &handler,
            ACE_HANDLE handle = ACE_INVALID_HANDLE,
            const void *completion_key = 0,
            TRB_Proactor *proactor = 0,
            bool pass_ownership=0);

  virtual int cancel (void);
  int close  (void);
  int cancel_and_close (void);

  bool should_finish (void) const { return flg_cancel_ ;}

  ACE_HANDLE get_handle () const { return handle_; }
  //void  set_handle (ACE_HANDLE h) { handle_ = h; }

  
  READER &  reader (void) { return rs_;}
  WRITER &  writer (void) { return ws_;}

 
protected:

  /// Implementation class that all methods will be forwarded to.
  ACE_HANDLE handle_;
  bool flg_owner_; 
  bool flg_cancel_;
  bool flg_socket_;

  const void * completion_key_;
  READER rs_;
  WRITER ws_;

};

// ********************************************************************

template <class READER, class WRITER, class TRANSMIT>
class TRB_Asynch_RWT_Stream : public TRB_Asynch_RW<READER, WRITER>
{
public:
  typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;

  typedef typename TRANSMIT::Header_And_Trailer Header_And_Trailer;
    
  /// A do nothing constructor.
  TRB_Asynch_RWT_Stream (void) : TRB_Asynch_RW<READER, WRITER>(true) {;}

  /// Destructor
  virtual ~TRB_Asynch_RWT_Stream (void) {;}

  virtual int open (TRB_Handler &handler,
            ACE_HANDLE handle = ACE_INVALID_HANDLE,
            const void *completion_key = 0,
            TRB_Proactor *proactor = 0,
            bool pass_ownership=0);

  virtual int cancel (void);

  int read (const Buffer_Info& buf_info,
            size_t num_bytes_to_read,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int write (const Buffer_Info& buf_info,
            size_t num_bytes_to_write,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int transmit (ACE_HANDLE file,
                ACE_Message_Block * header = 0,
                ACE_Message_Block * trailer = 0,
                size_t bytes_to_write = 0,
                unsigned long offset = 0,
                unsigned long offset_high = 0,
                size_t bytes_per_send = 0,
                unsigned long flags = 0,
                const void *act = 0,
                int priority = 0,
                int signal_number = ACE_SIGRTMIN);

protected:  
  TRANSMIT ts_;  
  Header_And_Trailer header_and_trailer_;
};

// ********************************************************************

template <class READER, class WRITER>
class TRB_Asynch_RW_File : public TRB_Asynch_RW<READER, WRITER>
{
public:
  typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;

  /// A do nothing constructor.
  TRB_Asynch_RW_File (void) : TRB_Asynch_RW<READER, WRITER>(false) {;}

  /// Destructor
  virtual ~TRB_Asynch_RW_File (void) {;}

  int read (const Buffer_Info& buf_info,
            size_t num_bytes_to_read,
            size_t offset_low,
            size_t offset_high,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);

  int write (const Buffer_Info& buf_info,
            size_t num_bytes_to_write,
            size_t offset_low,
            size_t offset_high,
            const void *act = 0,
            int priority = 0,
            int signal_number = ACE_SIGRTMIN);
  

};
// ********************************************************************
template <class READER, class WRITER>
class TRB_Asynch_RW_Dgram :  public TRB_Asynch_RW<READER, WRITER>
{
public:
  typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;
  
  /// A do nothing constructor.
  TRB_Asynch_RW_Dgram (void) : TRB_Asynch_RW<READER, WRITER>(true) {;}

  /// Destructor
  virtual ~TRB_Asynch_RW_Dgram (void) {;}

  ssize_t recv  (const Buffer_Info&   buf_info,  
                 size_t &             number_of_bytes_recvd,  
                 int                  flags,  
                 int                  protocol_family = PF_INET,  
                 const void *         act = 0,
                 int                  priority = 0,  
                 int                  signal_number = ACE_SIGRTMIN);

  ssize_t send  (const Buffer_Info&  buf_info,
                 size_t &            number_of_bytes_sent,  
                 int                 flags,  
                 const ACE_Addr &    remote_addr,  
                 const void *        act = 0,  
                 int                 priority = 0,  
                 int                 signal_number = ACE_SIGRTMIN);  
 

};

//----------------------------------------------------------
//   Implementations
//----------------------------------------------------------

template <class READER, class WRITER>
TRB_Asynch_RW<READER, WRITER>::TRB_Asynch_RW (bool flg_socket)
: handle_         (ACE_INVALID_HANDLE)
, flg_owner_      (false)
, flg_cancel_     (false)
, flg_socket_     (flg_socket)
, completion_key_ (0)
, rs_             () 
, ws_             ()
{
  ;
}

template <class READER, class WRITER>
TRB_Asynch_RW<READER, WRITER>::~TRB_Asynch_RW (void)
{
  this->close();
}

template <class READER, class WRITER> int
TRB_Asynch_RW<READER, WRITER>::close(void)
{

  if (this->handle_ != ACE_INVALID_HANDLE && this->flg_owner_ )
  {
      if (flg_socket_)
         ACE_OS::closesocket (this->handle_);
      else
          ACE_OS::close (this->handle_);
  }

  this->handle_ = ACE_INVALID_HANDLE;

  return 0;
}

template <class READER, class WRITER> int
TRB_Asynch_RW<READER, WRITER>::cancel(void)
{
  if (!this->flg_cancel_)
    {
      this->flg_cancel_ = true;
    
      if (this->handle_ != ACE_INVALID_HANDLE) 
        {
           this->rs_.cancel ();
           this->ws_.cancel ();
        }
    }

  return 0;
}

template <class READER, class WRITER> int
TRB_Asynch_RW<READER, WRITER>::cancel_and_close(void)
{
  this->cancel();
  return this->close();
}

template <class READER, class WRITER> int
TRB_Asynch_RW<READER, WRITER>::open 
         (TRB_Handler &handler,
          ACE_HANDLE handle, 
          const void *completion_key,
          TRB_Proactor *proactor,
          bool pass_ownership)
{

  if (this->handle_ != ACE_INVALID_HANDLE || this->flg_cancel_)
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

template <class READER, class WRITER, class TRANSMIT> int
TRB_Asynch_RWT_Stream<READER, WRITER, TRANSMIT>::cancel(void)
{
  if (!this->flg_cancel_)
    {
      this->flg_cancel_ = true;
    
      if (this->handle_ != ACE_INVALID_HANDLE) 
        {
           this->rs_.cancel ();
           this->ws_.cancel ();
           this->ts_.cancel ();
        }
    }

  return 0;
}


template <class READER, class WRITER, class TRANSMIT> int
TRB_Asynch_RWT_Stream<READER, WRITER, TRANSMIT>::open 
         (TRB_Handler &handler,
          ACE_HANDLE handle, 
          const void *completion_key,
          TRB_Proactor *proactor,
          bool pass_ownership)
{

  if (this->handle_ != ACE_INVALID_HANDLE || this->flg_cancel_)
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

  if (this->ts_.open(handler,
                     handle,
                     completion_key,
                     proactor) < 0)
  
    return -1;

  return 0;
}

template <class READER, class WRITER, class TRANSMIT> int
TRB_Asynch_RWT_Stream<READER, WRITER, TRANSMIT>::read (const Buffer_Info& buf_info,
                            size_t num_bytes_to_read,
                            const void *act,
                            int priority,
                            int signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
    return -1;

  return this->reader().read (buf_info,
                              num_bytes_to_read,
                              act,
                              priority,
                              signal_number);
}
 
template <class READER, class WRITER, class TRANSMIT> int
TRB_Asynch_RWT_Stream<READER, WRITER, TRANSMIT>::write (const Buffer_Info& buf_info,
                             size_t num_bytes_to_write,
                             const void *act,
                             int priority,
                             int signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
    return -1;

  return this->writer().write (buf_info,
                               num_bytes_to_write,
                               act,
                               priority,
                               signal_number);
}

template <class READER, class WRITER, class TRANSMIT> int
TRB_Asynch_RWT_Stream<READER, WRITER, TRANSMIT>::transmit (ACE_HANDLE file,
                ACE_Message_Block * header,
                ACE_Message_Block * trailer,
                size_t bytes_to_write,
                unsigned long offset,
                unsigned long offset_high,
                size_t bytes_per_send,
                unsigned long flags,
                const void *act,
                int priority,
                int signal_number)

{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
    return -1;

  size_t len_hdr   = header ? header->length () : 0;
  size_t len_trail = trailer ? trailer->length () : 0;

  this->header_and_trailer_.header_and_trailer (header,
                                                len_hdr,
                                                trailer,
                                                len_trail);
  

  return ts_.transmit_file (file,
                & header_and_trailer_,
                bytes_to_write,
                offset,
                offset_high,
                bytes_per_send,
                flags,
                act,
                priority,
                signal_number);
}

// ****************************************************************

template <class READER, class WRITER> int
TRB_Asynch_RW_File<READER, WRITER>::read (const Buffer_Info& buf_info,
                            size_t num_bytes_to_read,
                            size_t offset_low,
                            size_t offset_high,
                            const void *act,
                            int priority,
                            int signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
    return -1;

  return this->reader().read (buf_info,
                              num_bytes_to_read,
                              offset_low,
                              offset_high,
                              act,
                              priority,
                              signal_number);
}
 
template <class READER, class WRITER> int
TRB_Asynch_RW_File<READER, WRITER>::write (const Buffer_Info& buf_info,
                             size_t num_bytes_to_write,
                             size_t offset_low,
                             size_t offset_high,
                             const void *act,
                             int priority,
                             int signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
    return -1;

  return this->writer().write (buf_info,
                               num_bytes_to_write,
                               offset_low,
                               offset_high,
                               act,
                               priority,
                               signal_number);
}
// ****************************************************************

template <class READER, class WRITER> ssize_t
TRB_Asynch_RW_Dgram<READER, WRITER>::recv (const Buffer_Info& buf_info,  
                 size_t &             number_of_bytes_recvd,  
                 int                  flags,  
                 int                  protocol_family,
                 const void *         act,
                 int                  priority,
                 int                  signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
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
TRB_Asynch_RW_Dgram<READER, WRITER>::send  (const Buffer_Info& buf_info, 
                 size_t &            number_of_bytes_sent,  
                 int                 flags,  
                 const ACE_Addr &    remote_addr,  
                 const void *        act,  
                 int                 priority,  
                 int                 signal_number)
{
  if (this->handle_ == ACE_INVALID_HANDLE || this->flg_cancel_ )
    return -1;

  return this->writer().send  (buf_info,
                               number_of_bytes_sent,  
                               flags,  
                               remote_addr,  
                               act,  
                               priority,  
                               signal_number);
}
// *************************************************************

typedef TRB_Asynch_RWT_Stream<TRB_Asynch_Read_Stream,
                             TRB_Asynch_Write_Stream,
                             TRB_Asynch_Transmit_File> 
        Asynch_RWT_Stream;

typedef TRB_Asynch_RW_Dgram<TRB_Asynch_Read_Dgram,TRB_Asynch_Write_Dgram> 
        Asynch_RW_Dgram;

typedef TRB_Asynch_RW_File<TRB_Asynch_Read_File,TRB_Asynch_Write_File> 
        Asynch_RW_File;



#endif //ASYNCH_RW_H
