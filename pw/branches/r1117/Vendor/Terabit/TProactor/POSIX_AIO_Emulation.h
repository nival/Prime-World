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

//==========================================================================
/**
 *
 *  @file    POSIX_AIO_Emulation.h
 *  $Id: $
 * 
 *  @author Alexander Libman <alibman@terabit.com.au>
 */
//==========================================================================

#ifndef TRB_POSIX_AIO_EMULATION_H 
#define TRB_POSIX_AIO_EMULATION_H 

#include "ace/pre.h"

#if defined (ACE_HAS_AIO_EMULATION)

#include <errno.h>
#include "ace/OS_NS_signal.h"

#ifdef	__cplusplus
extern "C" {
#endif


typedef struct aiocb 
{
	int 		    aio_fildes;

#if	defined(__STDC__)
	volatile void	*aio_buf;	    /* buffer location */
#else
	void		    *aio_buf;		/* buffer location */
#endif

	size_t 		    aio_nbytes;		/* length of transfer */
	off_t 		    aio_offset;	    /* file offset */
	int		        aio_reqprio;    /* request priority offset */
	struct sigevent	aio_sigevent;	/* signal number and offset */
	int 		    aio_lio_opcode;	/* listio operation */
    ssize_t         aio_return;     /* return code of i/o          */
    int             aio_errno;      /* Error number, or EINPROG    */
	int 		    aio_state;		/* state flag for List I/O */
	int		        aio__pad[1];	/* extension padding */

} aiocb_t;

/*
 * return values for aiocancel()
 */
#define	AIO_CANCELED	0
#define	AIO_ALLDONE	    1
#define	AIO_NOTCANCELED	2

/*
 * mode values for lio_listio()
 */
#define	LIO_NOWAIT	0
#define	LIO_WAIT	1


/*
 * listio operation codes
 */

#define	LIO_NOP		0
#define	LIO_READ	0x01	/* Must match value of FREAD in sys/file.h */
#define	LIO_WRITE	0x02	/* Must match value of FWRITE in sys/file.h */

/*
 * function prototypes
 */


static int	aio_read(aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

static int	aio_write(aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

static int	lio_listio(int, aiocb_t *const[], int, struct sigevent *)
{
	errno = ENOSYS;
    return -1;
}

static int	aio_error(const aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

static ssize_t	aio_return(const aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

static int	aio_cancel(int, aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}

static int	aio_suspend(const aiocb_t *const[], int,
	            const struct timespec *)
{
	errno = ENOSYS;
    return -1;
}

static int	aio_fsync(int, aiocb_t *)
{
	errno = ENOSYS;
    return -1;
}



#ifdef	__cplusplus
}
#endif


#endif /* ACE_HAS_AIO_EMULATION */

#include "ace/post.h"

#endif //TRB_POSIX_AIO_EMULATION_H 
