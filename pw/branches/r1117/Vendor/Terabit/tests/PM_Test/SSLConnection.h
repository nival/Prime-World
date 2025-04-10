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
 *  @file Receiver.h
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================
#ifndef SSL_CONNECTION_H
#define SSL_CONNECTION_H

#include "PConnection.h"
#include "Asynch_RW.h"



#include "ace/SSL/sslconf.h"
#include "TProactor/SSL/SSL_Asynch_Stream.h"
#include "openssl/rand.h"



// *************************************************************
//   Receiver SSL
// *************************************************************

class SSLConnection : public PConnection 
{
public:
  SSLConnection  (void);
  ~SSLConnection (void);

  // Virtual from PConnection
  virtual const ACE_TCHAR * get_name (void) const 
    {
       return ACE_TEXT("Receiver");
    }

  virtual void cancel ();
  
  virtual int  is_safe_to_delete (void);

  virtual void on_open (ACE_HANDLE handle);

  virtual int  start_asynch_read (ACE_Message_Block &mb, size_t bytes);
    
  virtual int  start_asynch_write (ACE_Message_Block &mb, size_t bytes);

  /// This is called after all I/O is done and
  /// it is safe to self-destroy 
  virtual void handle_wakeup ();

private:

  TRB_SSL_Asynch_Stream stream_;
  int flg_cancel_;
  int flg_safe_delete_;
};

#endif  /* SSL_CONNECTION_H */

