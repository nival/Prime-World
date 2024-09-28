//!Component( "Network/NetworkAddress" )
//!Component( "Network/FreePortsFinder" )
//!Component( "Vendor/zlib" )
//!Component( "Network/SSLEncoder" )

#include <cxxtest/TestSuite.h>
#include "stdafx.h"
#include "Address.h"
#include "FreePortsFinder.h"
#include "NetworkBuffers.h"
#include "SSLEncoder.h"
#include "StreamAllocator.h"
#include "zlib.h"

#define WAIT( X )                         \
{ int guard = 100;                        \
  while( !(X) && --guard > 0 ) Sleep(10); \
}

#include <openssl/rsa.h>       
#include <openSSL/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

// RSA 2048 certificate (self-signed) and private key
static const char test_cert[] = 
"-----BEGIN CERTIFICATE-----\n"
"TEST CERTIFICATE\n"
"-----END CERTIFICATE-----\n";
static const char test_key[] = 
"-----BEGIN RSA PRIVATE KEY-----\n"
"TEST\n"
"-----END RSA PRIVATE KEY-----\n";

SSL_CTX* CreateTestContext( bool loadCert )
{
  SSL_METHOD* meth = SSLv3_method();
  SSL_CTX* ctx = SSL_CTX_new( meth );

  if ( loadCert )
  {
    BIO *mem = BIO_new_mem_buf( (void*)test_cert, -1);
    X509* x = PEM_read_bio_X509( mem, 0, 0, 0 );

    if ( SSL_CTX_use_certificate( ctx, x ) <= 0 )
    {
      ERR_print_errors_fp( stderr );
      return 0;
    }
    if ( x ) 
      X509_free( x );
    if ( mem ) 
      BIO_free( mem );

    mem = BIO_new_mem_buf( (void*)test_key, -1);
    EVP_PKEY* k = PEM_read_bio_PrivateKey( mem, 0, 0, 0 );

    if (SSL_CTX_use_PrivateKey( ctx, k ) <= 0) {
      ERR_print_errors_fp(stderr);
      return 0;
    }

    if ( k ) 
      EVP_PKEY_free( k );
    if ( mem ) 
      BIO_free( mem );

    if (!SSL_CTX_check_private_key(ctx)) {
      fprintf( stderr, "Private key does not match the certificate public key\n" );
      return 0;
    }
  }

  return ctx;
}

struct OpenSSLTest: public CxxTest::TestSuite 
{
  void TestSSLTransceiver()
  {
    Network::SSLEncoder sock1, sock2;

    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    SSL_CTX* ctx1 = CreateTestContext( true );
    SSL_CTX* ctx2 = CreateTestContext( false );

    sock1.Init( ctx1, true );
    sock2.Init( ctx2, false );

    byte buf1[4096];

    while( sock1.GetState() == Network::SSLEncoder::S_CONNECTING 
      || sock2.GetState() == Network::SSLEncoder::S_CONNECTING )
    {
      BIOExchange(sock1, sock2, buf1);
      //printf( "%s \t %s\n", SSL_state_string_long(sock1.ssl), SSL_state_string_long(sock2.ssl) );
    }
    TS_ASSERT( sock1.GetState() == Network::SSLEncoder::S_CONNECTED );
    TS_ASSERT( sock2.GetState() == Network::SSLEncoder::S_CONNECTED );
    //printf ("SSL connection using %s\n", SSL_get_cipher( sock1.ssl ) );

    byte testStr[] = "12345";
    sock1.WriteAppData( (byte*)testStr, 6 );
    sock2.WriteAppData( (byte*)testStr, 5 );
    int red1, red2 = 0;
    do 
    {
      BIOExchange(sock1, sock2, buf1);
      red1 = sock2.ReadAppData( buf1, 1000 );
      red2 = sock1.ReadAppData( buf1 + 1000, 1000 );
    } while ( red1 == 0 && red2 == 0 );
    TS_ASSERT_EQUALS( red1, 6 );
    TS_ASSERT( 0 == memcmp( testStr, buf1, 6 ) );
    TS_ASSERT_EQUALS( red2, 5 );
    TS_ASSERT( 0 == memcmp( testStr, buf1 + 1000, 5 ) );
    
  }

  void BIOExchange( Network::SSLEncoder &sock1, Network::SSLEncoder &sock2, byte * buf1 )
  {
    sock1.Step();
    sock2.Step();
    byte* pB;
    int sz, sz2;

    while( sock1.GetNetBytesOut() > 0 )
    {
      sock1.GetNetDataOut( &pB, &sz );
      memcpy( buf1, pB, sz );
      sock1.CommitNetBufferOut( sz );

      sock2.GetNetBufferIn( &pB, &sz2 );
      memcpy( pB, buf1, sz );
      sock2.CommitNetBufferIn( sz );
    }

    while( sock2.GetNetBytesOut() > 0 )
    {
      sock2.GetNetDataOut( &pB, &sz );
      memcpy( buf1, pB, sz );
      sock2.CommitNetBufferOut( sz );

      sock1.GetNetBufferIn( &pB, &sz2 );
      memcpy( pB, buf1, sz );
      sock1.CommitNetBufferIn( sz );
    }
  }

};

struct BufferCompressorTest : public CxxTest::TestSuite 
{

  byte data[8192];
  byte* buf;
  int size;
  byte* buf2;
  int size2;
  byte outData[8192];

  void setUp()
  {
    for ( int i = 0; i < 8192; i++ )
      data[i] = (i << 3) % 256;
     // data[i] =  ( rand() >> 4 ) % 256;

  }

  void testNoCompression()
  {
    Network::ZlibComressor c;
    Network::ZlibDecomressor d;

    c.Init( 512, true );
    d.Init( 512 );


    for ( int i = 0; i < 1000; ++i )
    {
      c.SetDataIn( data, 100 );
      TS_ASSERT( c.GetDataInProcessed() == 100 );
      c.SetDataIn( data + 100, 100 );
      TS_ASSERT( c.GetDataInProcessed() == 100 );
      c.SetDataIn( data + 200, 56 );
      TS_ASSERT( c.GetDataInProcessed() == 56 );

      c.Flush();

      c.GetDataOut( &buf, &size );
      d.GetBufferIn( &buf2, &size2 );

      memcpy( buf2, buf, size );

      c.ProcessedDataOut();
      d.CommitBufferIn( size );

      d.SetBufferOut( outData, 2048 );
      size2 = d.GetReadyOutData();

      TS_ASSERT_EQUALS( size2, 256 );
      TS_ASSERT_SAME_DATA( data, outData, 256 );
    }
  }
  void testLongMessage()
  {
    byte tempBuf[10240];
    int tempSz = 0;
    Network::ZlibComressor c;
    Network::ZlibDecomressor d;

    c.Init( 512, true );
    d.Init( 512 );

    int pos = 0;
    while( 1 )
    {
      c.SetDataIn( data + pos, 8192 - pos );
      pos += c.GetDataInProcessed(); 
      c.ProcessedDataIn();

      c.Flush();

      c.GetDataOut( &buf, &size );
      memcpy( tempBuf + tempSz, buf, size );
      tempSz += size;
      c.ProcessedDataOut();
      if( size == 0 )
        break;
    }
       
    pos = 0;
    int outPos = 0;
    while( outPos < 8192 )
    {
      d.GetBufferIn( &buf, &size );
      int res = (tempSz - pos) < 30 ? tempSz - pos : (tempSz - pos) / 2;
      res = Min( res, size );

      memcpy( buf, tempBuf + pos, res );
      pos += res;
      d.CommitBufferIn( res );

      int sz = Min( 8192 - outPos, 1000 );
      d.SetBufferOut( outData + outPos, sz );

      res = d.GetReadyOutData();
      outPos += res;
    }

    TS_ASSERT_EQUALS( outPos, 8192 );
    TS_ASSERT_SAME_DATA( data, outData, 8192 );
  }

};



struct GatherBufferTest : public CxxTest::TestSuite 
{
  byte data[256];
  byte* result;
  int resultSize;

  void setUp()
  {
    for ( int i = 0; i < 256; i++ )
      data[i] = i;
  }

  void testGatherBuffer()
  {
    Network::GatherMessageBuffer buf( 100 );

    buf.AddMessage( data, 52 );

    byte* result = 0;
    int resultSize = 0;

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 54 );
    TS_ASSERT_EQUALS( *(ushort*)result, 52 );

    buf.ReleaseData( 54 );

    TS_ASSERT( !buf.GetData( &result, &resultSize ) );

    buf.AddMessage( data, 52 );
    buf.AddMessage( data, 44 );
    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 100 );
    buf.ReleaseData( 54 );
    TS_ASSERT( buf.AddMessage( data, 40 ) );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 46 );
    TS_ASSERT_EQUALS( *(ushort*)result, 44 );
    buf.ReleaseData( 10 );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 36 );
    buf.ReleaseData( resultSize );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 42 );
    TS_ASSERT_EQUALS( *(ushort*)result, 40 );
    buf.ReleaseData( resultSize );
  }

  void testBufferResize1()
  {
    Network::GatherMessageBuffer buf( 100 );

    buf.AddMessage( data, 52 );
    buf.AddMessage( data, 44 );

    TS_ASSERT( !buf.AddMessage( data, 42 ) );

    buf.IncreaseSize( 40 );

    TS_ASSERT( buf.AddMessage( data, 42 ) );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 144 );
    buf.ReleaseData( 144 );
  }

  void testBufferResize2()
  {
    Network::GatherMessageBuffer buf( 100 );

    buf.AddMessage( data, 52 );
    buf.AddMessage( data, 44 );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 100 );
    TS_ASSERT_EQUALS( *(ushort*)result, 52 );
    buf.ReleaseData( 100 );

    buf.IncreaseSize( 42 );
    TS_ASSERT( buf.AddMessage( data, 42 ) );


    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 44 );
    TS_ASSERT_EQUALS( *(ushort*)result, 42 );
    buf.ReleaseData( 44 );
  }

  void testBufferResize3()
  {
    Network::GatherMessageBuffer buf( 100 );

    buf.AddMessage( data, 52 );
    buf.AddMessage( data, 44 );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 100 );
    TS_ASSERT_EQUALS( *(ushort*)result, 52 );
    buf.ReleaseData( 54 );

    TS_ASSERT( buf.AddMessage( data, 42 ) );
    TS_ASSERT( !buf.AddMessage( data, 42 ) );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 46 );
    TS_ASSERT_EQUALS( *(ushort*)result, 44 );
    buf.ReleaseData( resultSize );

    buf.IncreaseSize( 40 );
    TS_ASSERT( buf.AddMessage( data, 42 ) );

    TS_ASSERT( buf.GetData( &result, &resultSize ) );
    TS_ASSERT_EQUALS( resultSize, 88 );
    TS_ASSERT_EQUALS( *(ushort*)result, 42 );
    buf.ReleaseData( resultSize );
  }

};

struct ScatterBufferTest : public CxxTest::TestSuite 
{
  struct Msg
  {
    ushort sz;
    byte data[256];
    Msg()
    {
      sz = 0;
      for ( int i = 0; i < 256; i++ )
        data[i] = i;
    }
  };

  void testScatterBuffer()
  {
    Network::ScatterMessageBuffer buf( 100, 50 );

    byte* msg = 0;
    int msgSize = 0;
    TS_ASSERT( !buf.GetMessage( &msg, &msgSize ) );

    Msg m;
    m.sz = 32;

    byte* writeBuf = 0;
    int writeSz = 0;
    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    memcpy( writeBuf, &m, 34 );
    buf.CommitWriteBuffer( 34 );

    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 32 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();

    m.sz = 82;
    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    memcpy( writeBuf, &m, 50 );
    buf.CommitWriteBuffer( 50 );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    memcpy( writeBuf, ((byte*)&m) + 50, 10 );
    buf.CommitWriteBuffer( 10 );

    TS_ASSERT( !buf.GetMessage( &msg, &msgSize ) );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 40 );
    memcpy( writeBuf, ((byte*)&m) + 60, 24 );
    m.sz = 14;
    memcpy( writeBuf + 24, &m, 16 );

    buf.CommitWriteBuffer( 40 );

    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 82 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();
    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 14 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();
  }

  void testScatterBufferLarge1()
  {
    Network::ScatterMessageBuffer buf( 50, 50 );

    byte* msg = 0;
    int msgSize = 0;

    byte* writeBuf = 0;
    int writeSz = 0;

    Msg m;
    m.sz = 50;

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 50 );
    memcpy( writeBuf, &m, 50 );
    buf.CommitWriteBuffer( 50 );

    TS_ASSERT( !buf.GetMessage( &msg, &msgSize ) );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 50 );
    memcpy( writeBuf, ((byte*)&m) + 50, 4 );
    buf.CommitWriteBuffer( 4 );

    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 50 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();
  }

  void testScatterBufferOverrun()
  {
    Network::ScatterMessageBuffer buf( 50, 50 );

    byte* msg = 0;
    int msgSize = 0;

    byte* writeBuf = 0;
    int writeSz = 0;

    Msg m;
    m.sz = 28;
    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    memcpy( writeBuf, &m, m.sz + 2 );
    buf.CommitWriteBuffer( m.sz + 2 );


    m.sz = 16;
    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    memcpy( writeBuf, &m, m.sz + 2 );
    buf.CommitWriteBuffer( m.sz + 2 );


    m.sz = 22;
    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 2 );
    memcpy( writeBuf, &m, 2 );
    buf.CommitWriteBuffer( 2 );

    TS_ASSERT( !buf.GetWriteBuffer( &writeBuf, &writeSz ) );

    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 28 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 30 );
    memcpy( writeBuf, ((byte*)&m) + 2, m.sz + 2 );
    buf.CommitWriteBuffer( m.sz + 2 );

    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 16 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();

    TS_ASSERT( buf.GetMessage( &msg, &msgSize ) );
    TS_ASSERT_EQUALS( msgSize, 22 );
    TS_ASSERT_EQUALS( *(int*)msg, 0x03020100 );
    buf.ReleaseMessage();
  }
};


struct ScatterBufferTestNew : public CxxTest::TestSuite 
{
  byte result[256];
  int resultSize;

  struct Msg
  {
    ushort sz;
    byte data[256];
    Msg()
    {
      sz = 0;
      for ( int i = 0; i < 256; i++ )
        data[i] = i;
    }
  };
  Msg m;
  byte* writeBuf;
  int writeSz;

  void CheckResult( int size, bool partial = false )
  {
    TS_ASSERT_SAME_DATA( result, m.data, size );

    if ( !partial )
      for ( int i = 0; i < 256; i++ )
        result[i] = 255;
  }

  
  void setUp()
  {
    writeBuf = 0;
    writeSz = 0;
    m = Msg();
  }

  void testPartialRead()
  {
    Network::ScatterMessageBuffer buf( 50, 50 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 0 );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    m.sz = 32;
    memcpy( writeBuf, &m, 34 );
    buf.CommitWriteBuffer( 34 );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 16 );
    m.sz = 46;
    memcpy( writeBuf, &m, 16 );
    buf.CommitWriteBuffer( 16 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 32 );
    TS_ASSERT( buf.CopyMessage( result, resultSize ) );
    CheckResult( 32 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 46 );
    TS_ASSERT( !buf.CopyMessage( result, resultSize ) );
    CheckResult( 14, true );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 50 );
    memcpy( writeBuf, ((byte*)&m) + 16 , 32 );
    buf.CommitWriteBuffer( 32 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 46 );
    TS_ASSERT( buf.CopyMessage( result, resultSize ) );
    CheckResult( 46 );
  }
  void testLargeMessage()
  {
    Network::ScatterMessageBuffer buf( 50, 50 );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    m.sz = 52;
    memcpy( writeBuf, &m, 50 );
    buf.CommitWriteBuffer( 50 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 52 );
    TS_ASSERT( !buf.CopyMessage( result, resultSize ) );
    CheckResult( 48, true );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 50 );
    memcpy( writeBuf, ((byte*)&m) + 50, 4 );
    buf.CommitWriteBuffer( 4 );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 46 );
    memcpy( writeBuf, &m, 46 );
    buf.CommitWriteBuffer( 46 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 52 );
    TS_ASSERT( buf.CopyMessage( result, resultSize ) );
    CheckResult( 52 );

    resultSize = buf.ReadNextMessageSize();
    TS_ASSERT_EQUALS( resultSize, 52 );
    TS_ASSERT( !buf.CopyMessage( result, resultSize ) );
    CheckResult( 44, true );

    TS_ASSERT( buf.GetWriteBuffer( &writeBuf, &writeSz ) );
    TS_ASSERT_EQUALS( writeSz, 50 );
    memcpy( writeBuf, ((byte*)&m) + 46, 8 );
    buf.CommitWriteBuffer( 8 );

    TS_ASSERT( buf.CopyMessage( result, resultSize ) );
    CheckResult( 52 );
  }
};



struct TestNetworkAddress : public CxxTest::TestSuite 
{
	void testAddresses()
	{
		TS_ASSERT_EQUALS( Network::Address(), Network::Address( unsigned long( 0 ), 0 ) );
		TS_ASSERT_DIFFERS( Network::Address( 6, 45 ), Network::Address( 7, 45 ) );
		TS_ASSERT_EQUALS( Network::Address( "127.0.0.1", 1024 ), Network::Address( "127.0.0.1", 1024 ) );
		TS_ASSERT_DIFFERS( Network::Address( "127.0.0.1", 1024 ), Network::Address( "127.0.0.1", 1025 ) );
		TS_ASSERT_DIFFERS( Network::Address( "127.0.0.1", 1024 ), Network::Address( "127.0.0.2", 1024 ) );

		Network::Address address;
		address.Set( "12.0.0.0", 2 );
		TS_ASSERT_DIFFERS( address, Network::Address( "127.0.0.1", 2 ) );
		TS_ASSERT_DIFFERS( address, Network::Address( "12.0.0.1", 2 ) );
		address.SetPort( Network::Address::PORT( 4 ) );
		TS_ASSERT_DIFFERS( address, Network::Address( "12.0.0.0", 2 ) );
		TS_ASSERT_EQUALS( address, Network::Address( "12.0.0.0", 4 ) );
	}

	void testAddressesNameResolver()
	{
    WSADATA wsaData = { 0 };
    ::WSAStartup( MAKEWORD( 2, 2), &wsaData );
		Network::Address address;
		TS_ASSERT( address.Set( "localhost", 2222 ) );
    ::WSACleanup();
	}
};



