#ifndef SSLSOCKETWRAPPER_H_3F827782_F06D
#define SSLSOCKETWRAPPER_H_3F827782_F06D

#include <openssl/ossl_typ.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
namespace Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct SSLEncoder
  {
    enum EState
    {
      S_CONNECTING,
      S_CONNECTED,
      S_CLOSED,
    };

    SSLEncoder();

    ~SSLEncoder()
    {
      Close();
    }

    void Init( SSL_CTX* sslInitCtx, bool isServer, int bufferSize = 17*1024 );
    void Close();

    void Step()
    {
      if ( state == S_CONNECTING )
      {
        int res = isServer ? SSL_accept( ssl ) : SSL_connect( ssl );

        if ( res > 0 )
          state = S_CONNECTED;

        CheckReturn( res );
      }
    }

    EState GetState()
    {
      return state;
    }

    // network end
    int GetNetBytesIn()
    {
      return BIO_get_write_guarantee( networkBio );
    }
    void GetNetBufferIn( byte** data, int* size )
    {
      *data = buf;
      *size = Min( BIO_get_write_guarantee( networkBio ), bufferSize );
    }
    void CommitNetBufferIn( int actualSize )
    {
      /*int res = */BIO_write( networkBio, buf, actualSize );
    }
    int GetNetBytesOut() const
    {
      return BIO_ctrl_pending( networkBio );
    }
    void GetNetDataOut( byte** data, int* size )
    {
      *size = BIO_nread0( networkBio, (char**)data );
      //CheckReturn( *size );
    }
    void CommitNetBufferOut( int actualSize )
    {
      char* dummy;
      /*int res = */BIO_nread( networkBio, &dummy, actualSize );
    }

    // application end
    int WriteAppData( const byte* data, int size )
    {
      int res = SSL_write( ssl, data, size );
      return CheckReturn( res );
    }

    int ReadAppData( byte* data, int size )
    {
      int res = SSL_read( ssl, data, size );
      return CheckReturn( res );
    }

  private:
    int bufferSize;
    SSL* ssl;
    BIO* internalBio;
    BIO* networkBio;
    bool isServer;
    byte* buf;
    EState state;

    int CheckReturn( int res );
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif //#define SSLSOCKETWRAPPER_H_3F827782_F06D
