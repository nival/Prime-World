/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    SUN_Proactor.h
 *
 *  SUN_Proactor.h,v 4.15 2002/12/21 23:29:24 shuston Exp
 *
 *  @author Alexander Libman <alibman@baltimore.com>
 */
//=============================================================================

#ifndef TPROACTOR_SUN_PROACTOR_H 
#define TPROACTOR_SUN_PROACTOR_H 

#include "TProactor/POSIX_Proactor.h"

#if defined (ACE_HAS_AIO_CALLS) || defined (ACE_HAS_AIO_EMULATION)
// defined(sun)

/**
 * @class TRB_SUN_Proactor
 *
 * @brief Implementation of the fast and reliable Proactor
 * for SunOS 5.6, 5.7, etc.
 *
 * This proactor, based on <TRB_POSIX_AIOCB_Proactor>,
 * works with Sun native interface for aio calls.
 * POSIX_API          Native SUN_API
 * aio_read           aioread
 * aio_write          aiowrite
 * aio_suspend        aiowait
 * aio_error          aio_result_t.errno
 * aio_return         aio_result_t.return
 * On Solaris, the Sun <aio*()> native implementation is more
 * reliable and efficient than POSIX <aio_*()> implementation.
 * There is a problem of lost RT signals with POSIX, if we start
 * more than SIGQUEUEMAX asynchronous operations at the same
 * time.
 * The Sun <aiocb> it is not the standard POSX <aiocb>, instead,
 * it has the following structure:
 * typedef struct aiocb
 * {
 * int    aio_fildes;     File descriptor
 * void   *aio_buf;       buffer location
 * size_t       aio_nbytes;     length of transfer
 * off_t        aio_offset;     file offset
 * int          aio_reqprio;    request priority offset
 * sigevent     aio_sigevent;   signal number and offset
 * int    aio_lio_opcode; listio operation
 * aio_result_t aio_resultp;    results
 * int    aio_state;      state flag for List I/O
 * int    aio__pad[1];    extension padding
 * };
 */

#endif /* ACE_HAS_AIO_CALLS || ACE_HAS_AIO_EMULATION */
#endif //TPROACTOR_SUN_PROACTOR_H 
