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
 *  @file ARWConnection.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "ARWConnection.h"


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TRB_Asynch_RW<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;
template class TRB_Asynch_RW_Stream<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TRB_Asynch_RW<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>
#pragma instantiate TRB_Asynch_RW_Stream<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


// ***************************************************
//
// ***************************************************
ARWConnection::ARWConnection ()
  : PConnection ()
{
}

ARWConnection::~ARWConnection (void)
{
}

void
ARWConnection::cancel ()
{
  this->stream_.cancel_and_close();
}

int 
ARWConnection::is_safe_to_delete (void) 
{
  return !this->has_pending_io();
}

void
ARWConnection::on_open (ACE_HANDLE handle)
{
  if (this->stream_.open (*this, 
                          handle,
                          0, // completion key,
                          this->task().get_proactor(this->index()),
                          1) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%t) %s %p\n"),
                  this->get_name(),
                  ACE_TEXT ("TRB_Asynch_RW_Stream::open")));

       return;
    }
}


int
ARWConnection::start_asynch_read (ACE_Message_Block &mb, size_t bytes)
{
    return this->stream_.read (mb, bytes);
}
int
ARWConnection::start_asynch_write (ACE_Message_Block &mb, size_t bytes)
{
    return this->stream_.write (mb, bytes);
}

