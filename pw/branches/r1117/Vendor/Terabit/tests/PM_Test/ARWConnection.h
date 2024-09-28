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
 *  @file ARWConnection.h
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================
#ifndef ARW_CONNECTION_H 
#define ARW_CONNECTION_H 

#include "Asynch_RW.h"
#include "PConnection.h"



// *************************************************************
//   ARWConnection 
// *************************************************************

class ARWConnection : public PConnection 
{
public:
  ARWConnection  (void);
  ~ARWConnection (void);

  // Virtual from PConnection
  virtual const ACE_TCHAR * get_name (void) const 
    {
       return ACE_TEXT("ARWConnection");
    }

  virtual void cancel ();
  
  virtual int  is_safe_to_delete (void);

  virtual void on_open (ACE_HANDLE handle);

  virtual int  start_asynch_read (ACE_Message_Block &mb, size_t bytes);
    
  virtual int  start_asynch_write (ACE_Message_Block &mb, size_t bytes);

private:

  Asynch_RW_Stream  stream_;
};


#endif /* ARW_CONNECTION_H */
