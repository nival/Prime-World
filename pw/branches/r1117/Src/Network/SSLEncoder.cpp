#include "stdafx.h"
#include "SSLEncoder.h"
#include <openssl/rsa.h>
#include <openssl/err.h>

namespace Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SSLEncoder::SSLEncoder() : ssl( 0 )
    , internalBio( 0 )
    , networkBio( 0 )
    , state( S_CLOSED )
    , buf( 0 )
  {

  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SSLEncoder::Init( SSL_CTX* sslInitCtx, bool _isServer, int _bufferSize /*= 17*1024 */ )
  {
    isServer = _isServer;
    bufferSize = _bufferSize;
    buf = new byte[ bufferSize ];

    SSL_CTX_set_mode( sslInitCtx, SSL_MODE_ENABLE_PARTIAL_WRITE );
    ssl = SSL_new( sslInitCtx );

    if ( !BIO_new_bio_pair( &internalBio, bufferSize, &networkBio, bufferSize ) )
      return;

    SSL_set_bio( ssl, internalBio, internalBio );

    state = S_CONNECTING;
    Step();
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int SSLEncoder::CheckReturn( int res )
  {
    if ( res > 0 )
    {
    }
    else if ( res == 0 )
    {
      res = -1;
      Close();
    }
    else 
    {
      int err = SSL_get_error( ssl, res );
      if ( err != SSL_ERROR_WANT_READ 
        && err != SSL_ERROR_WANT_WRITE )
      {
        ERR_print_errors_fp( stderr );
        Close();
      }
      else
        res = 0;
    }
    return res;
  }

#define FREE_AND_NIL( meth, arg ) \
  if ( arg )                      \
  { meth( arg ); arg = 0; }   

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SSLEncoder::Close()
  {
//    FREE_AND_NIL( BIO_free, internalBio );
    FREE_AND_NIL( BIO_free, networkBio );
    FREE_AND_NIL( SSL_free, ssl );
    FREE_AND_NIL( delete, buf );
    state = S_CLOSED;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}