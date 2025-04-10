/* -*- C++ -*- */
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

/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    TRB_Asynch_File_Transmitter.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_ASYNCH_FILE_TRANSMITTER_H 
#define TRB_ASYNCH_FILE_TRANSMITTER_H 

#include /**/ "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if (defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))

# include "TProactor/Asynch_IO_Impl.h"
# include "ace/Message_Block.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class TRB_Asynch_File_Transmitter
 *
 * @brief Auxillary handler for doing <Asynch_Transmit_File> on 
 * the systems that do not support Transmit_File operation.
 *  <TRB_POSIX_Asynch_Transmit_File> internally uses this.
 *
 * This is a helper class for implementing
 * <TRB_POSIX_Asynch_Transmit_File> in Unix systems.
 */
class TPROACTOR_Export TRB_Asynch_File_Transmitter :
  public TRB_Handler
{
public:
  class Callback 
  {
  public:
     virtual void on_complete (TRB_Asynch_File_Transmitter& transmitter) = 0;
     virtual ~Callback () {}
  };

  /// Constructor. Result pointer will have all the information to do
  /// the file transmission (socket, file, application handler, bytes
  /// to write).
  TRB_Asynch_File_Transmitter (Callback & cb,
       const TRB_Asynch_Transmit_File_Result& original);

  /// Destructor.
  virtual ~TRB_Asynch_File_Transmitter (void);

  /// Do the transmission. All the info to do the transmission is in
  /// the <result> member.
  /// returns : 
  ///  -1 done with errors
  ///   0 AIO started
  ///   1 all is done OK, nothing more to do 
  int transmit (void);

  TRB_Asynch_Transmit_File_Result & get_original_result ();

private:
  /// This is called when asynchronous writes from the socket complete.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

  /// This is called when asynchronous reads from the file complete.
  virtual void handle_read_file (const TRB_Asynch_Read_File::Result &result);

  int  check_params ();
  


  /// returns : 
  ///  -1 done with errors
  ///   0 AIO started
  ///   1 all is done OK, nothing more to do 
  int  transmit_header  ();
  int  transmit_trailer ();
  int  initiate_read_file (void);
  int  initiate_write_stream (ACE_Message_Block& mb,
                              size_t             bytes_read,
                              const void        *act);

  void set_completion (u_long error);


  /// The callback object
  Callback& cb_;
  
  /// The asynch result pointer made from the initial transmit file
  /// request.
  TRB_Asynch_Transmit_File_Result original_;

  /// Message bloack used to do the transmission.
  ACE_Message_Block mb_;

  enum ACT
  {
    HEADER_ACT  = 1,
    DATA_ACT    = 2,
    TRAILER_ACT = 3
  };


  /// Current offset of the file being transmitted.
  size_t file_offset_;

  /// Total size of the file.
  size_t remain_bytes_;
  
  /// Number of bytes transferred on the stream.
  size_t bytes_transferred_;

  /// To read from the file to be transmitted.
  TRB_Asynch_Read_File rf_;

  /// Write stream to write the header, trailer and the data.
  TRB_Asynch_Write_Stream ws_;
};

inline void
TRB_Asynch_File_Transmitter::set_completion(u_long error)
{
  this->original_.set_completion (this->bytes_transferred_, error);
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_WIN32 || ACE_HAS_AIO_CALLS*/
#include "ace/post.h"
#endif // TRB_ASYNCH_FILE_TRANSMITTER_H 
