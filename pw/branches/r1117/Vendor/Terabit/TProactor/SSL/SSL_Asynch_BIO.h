// -*- C++ -*-

//=============================================================================
/**
 *  @file   SSL_Asynch_BIO.h
 *
 *  SSL_Asynch_BIO.h,v 1.3 2001/07/14 06:13:45 othman Exp
 *
 *  @author Alexander Libman <alibman@baltimore.com>
 *  @author Ossama Othman <ossama@uci.edu>
 *
 */
//=============================================================================

#ifndef TPROACTOR_SSL_ASYNCH_BIO_H 
#define TPROACTOR_SSL_ASYNCH_BIO_H 

#include "ace/pre.h"

#include "TProactor/SSL/TPROACTOR_SSL_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <openssl/bio.h>

#if OPENSSL_VERSION_NUMBER > 0x0090581fL && ((defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS)) || (defined (ACE_HAS_AIO_EMULATION)))

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @name OpenSSL BIO Helper Methods for use with ACE's Asynchronous
 *       SSL I/O support.
 */
//@{
extern "C"
{
  int  TRB_Asynch_BIO_write (BIO *pBIO, const char *buf, int len);
  int  TRB_Asynch_BIO_read  (BIO *pBIO, char *buf, int len);
  int  TRB_Asynch_BIO_puts  (BIO *pBIO, const char *str);
  long TRB_Asynch_BIO_ctrl  (BIO *pBIO, int cmd, long arg1, void *arg2);
  int  TRB_Asynch_BIO_new   (BIO *pBIO);
  int  TRB_Asynch_BIO_free  (BIO *pBIO);
}
//@}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif  /* OPENSSL_VERSION_NUMBER > 0x0090581fL (ACE_WIN32 ||
           ACE_HAS_AIO_CALLS) */

#include "ace/post.h"

#endif //TPROACTOR_SSL_ASYNCH_BIO_H 
