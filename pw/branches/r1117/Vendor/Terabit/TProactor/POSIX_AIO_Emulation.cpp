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

#include "TProactor/POSIX_AIO_Emulation.h"


#if defined(ACE_HAS_AIO_EMULATION)

#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

int	aio_read(aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

int	aio_write(aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

int	lio_listio(int, aiocb_t *const[], int, struct sigevent *)
{
	errno = ENOSYS;
    return -1;
}

int	aio_error(const aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

ssize_t	aio_return(const aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

int	aio_cancel(int, aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

int	aio_suspend(const aiocb_t *const[], int,
	            const struct timespec *)
{
	errno = ENOSYS;
    return -1;
}

int	aio_fsync(int, aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}


#ifdef __cplusplus
}  //extern "C" {
#endif


#endif /* ACE_HAS_AIO_EMULATION */
