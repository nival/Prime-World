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
 *  @file SSLConnection.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "SSLConnection.h"



// ***************************************************
//
// ***************************************************
SSLConnection::SSLConnection ()
: PConnection         (),
  stream_          (TRB_SSL_Asynch_Stream::ST_SERVER),
  flg_cancel_      (0),
  flg_safe_delete_ (1)

{
}

SSLConnection::~SSLConnection (void)
{
}

void
SSLConnection::cancel ()
{
  this->flg_cancel_ = 1;
  this->stream_.cancel ();

}

int 
SSLConnection::is_safe_to_delete (void)
{
  if (this->has_pending_io ())
    return 0;

  if (flg_safe_delete_)
    return 1;

  this->stream_.close();
  return 0;
}

void
SSLConnection::on_open (ACE_HANDLE handle)
{
  this->flg_safe_delete_ = 0;

  if (this->stream_.open (*this,
                           handle,
                           0, // completion key,
                           this->task().get_proactor(this->index()),
                           1 ) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%%s p\n"),
                this->get_name(),
                ACE_TEXT ("TRB_SSL_Asynch_Stream::open")));

      this->stream_.close();
    }
}


int
SSLConnection::start_asynch_read (ACE_Message_Block &mb, size_t bytes)
{
    return this->stream_.read (mb, bytes);
}
int
SSLConnection::start_asynch_write (ACE_Message_Block &mb, size_t bytes)
{
    return this->stream_.write (mb, bytes);
}

void
SSLConnection::handle_wakeup ()
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex() );

    this->flg_safe_delete_ = 1;
      
    if (!this->is_safe_to_delete())
      return;
  }
  this->manager()->destroy_connection(this);
}
