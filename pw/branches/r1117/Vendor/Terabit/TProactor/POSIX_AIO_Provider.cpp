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
// $Id:  $

#include "TProactor/POSIX_AIO_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "ace/ACE.h"
#include "ace/Log_Msg.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX AIO Provider
 *****************************************************************
 */
TRB_POSIX_AIO_Provider::TRB_POSIX_AIO_Provider
    (const TRB_POSIX_AIO_Config &  config)
: config_ (config)
{
}

TRB_POSIX_AIO_Provider::~TRB_POSIX_AIO_Provider ()
{
}  

/**
 *****************************************************************
 *  TRB_POSIX_AIO_Provider::Notification_Pipe
 *****************************************************************
 */
TRB_POSIX_AIO_Provider::Notification_Pipe::Notification_Pipe 
    (bool flg_nonblock)
: pipe_         ()
//, message_block_(read_buffer_, sizeof(read_buffer_))
{
    this->open (flg_nonblock);
}

TRB_POSIX_AIO_Provider::Notification_Pipe::~Notification_Pipe ()
{
    this->close ();
}

int 
TRB_POSIX_AIO_Provider::Notification_Pipe::close ()
{
    this->pipe_.close ();
    return 0;
}

int 
TRB_POSIX_AIO_Provider::Notification_Pipe::open (bool flg_nonblock)
{
    // Open the pipe.
    int rc = this->pipe_.open ();
    if (rc < 0)
        return -1;

    // Set always  write side in NONBLOCK mode
    rc = ACE::set_flags (this->pipe_.write_handle (), ACE_NONBLOCK);
    if (rc < 0)
        return -1;

    if (flg_nonblock)
    {
        // Set read side in NONBLOCK mode
        rc = ACE::set_flags (this->pipe_.read_handle (), ACE_NONBLOCK);
    }
    else
    {
        // Set read side in BLOCK mode
        rc = ACE::clr_flags (this->pipe_.read_handle (), ACE_NONBLOCK);
    }
    return rc;
}


int 
TRB_POSIX_AIO_Provider::Notification_Pipe::notify ()
{
    char char_send = 0;
    int  rc = ACE::send (this->pipe_.write_handle(),
                        &char_send,
                        sizeof (char_send));

    if (rc < 0)
    {
        if (errno != EWOULDBLOCK)
        {
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT("(%P|%t) TRB_POSIX_AIO_Provider::Notification_Pipe::%p\n"),
                ACE_LIB_TEXT("notify failed")),
                -1);
        }
        return 0;
    }
    return rc;
}

int 
TRB_POSIX_AIO_Provider::Notification_Pipe::read ()
{
    int rc;

    do {
        rc = ACE_OS::read (this->read_handle(),
                           read_buffer_,
                           sizeof(read_buffer_));

    } while (rc == sizeof(read_buffer_));

    if (rc >= 0)
    {
        return rc;
    }

    if (errno != EWOULDBLOCK)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT("(%P|%t) TRB_POSIX_AIO_rovider::Notification_Pipe::%p\n"),
            ACE_LIB_TEXT("read failed")),
            -1);
    }

    return 0;
}

/*
 ***************************************************************
 *  TRB_POSIX_AIO_Provider::Notification_Result
 ***************************************************************
 */
TRB_POSIX_AIO_Provider::Notification_Result::Notification_Result
    (TRB_POSIX_AIO_Provider::Notification_Pipe & notify_pipe)
: TRB_POSIX_Asynch_Read_Stream_Result 
    (0,       // allocator
     0,       // area
     TRB_Asynch_Read_Stream_Result // original result
       (&notify_pipe,                            // TRB_Hanlder
        notify_pipe.read_handle(),               // ACE_HANDLE
        notify_pipe.read_buffer(),               // message_block
        notify_pipe.read_buffer_size (),         // bytes_to_read
        0,                                       // act,
        0,                                       // completion key
        0,                                       // priority,
        0,                                       // signal_number
        0),                                      // scatter flags
     0)      //  POSIX_Proactor *                                      

{
   //notify_pipe.message_block ().reset ();
}
    
TRB_POSIX_AIO_Provider::Notification_Result::~Notification_Result()
{
}



ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
