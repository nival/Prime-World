//!Component( "System/Timer" )
//!Component( "System/Dumpers" )
//!Component( "System/Streams" )
//!Component( "Vendor/zlib" )
//!Component( "System/Threading" )
//!Component( "Network/RealDriver" )

#include <cxxtest/TestSuite.h>
#include "stdafx.h"
#include "System/HPTimer.h"
#include "System/ThreadHelpers.h"
#include "System/fixedString.h"
#include "System/CompletionPort.h"
#include "Address.h"
#include "zlib.h"



typedef FixedString<256> TBuf;

struct NetworkIOCPRequest : public threading::IOCPRequest
{
  enum EType
  {
    Initialize = threading::IOCPRequest::FirstClientRequest, 
    SendRequest,
    DataSent,
    DataReceived,
  };
  NetworkIOCPRequest() : inUse(false) {}
  NetworkIOCPRequest( EType type ) : inUse(false) { requestType = (IOCPRequest::ERequest)type; }

  void SetRequestType( EType type )
  {
    requestType = (IOCPRequest::ERequest)type;
  }
  bool inUse;
  TBuf buffer;
  WSABUF wsaBuffer;
};


class TCPConnection : public threading::IOCPClient
{
public:
  static NetworkIOCPRequest initRequest;

  TCPConnection( threading::IOCPSheduler* _pOwner, const char* ip  ) : pOwner(_pOwner) 
  {
    sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED );
    Network::Address address( ip );
    int result = ::connect( sock, address, sizeof( SOCKADDR_IN ) );
    if( result == SOCKET_ERROR )
    {
      result = WSAGetLastError();
      NI_VERIFY( result == WSAEWOULDBLOCK, NStr::StrFmt( "Can't connect to url %s. Error %d", ip, result ), sock = 0 );
    }
    pOwner->PostRequest( this, &initRequest );
  }

  TCPConnection( threading::IOCPSheduler* _pOwner, SOCKET _sock  ) : pOwner(_pOwner) 
  {
    sock = _sock;
    pOwner->PostRequest( this, &initRequest );
  }

  void Send( const TBuf& buf )
  {
    threading::MutexLock lock( locker );
    sendBuffers.push_back( buf );
    pOwner->PostRequest( this, &hasDataRequest );
  }

  bool Receive( TBuf& buf )
  {
    threading::MutexLock lock( locker );
    if ( recvBuffers.empty() )
      return false;
    buf = recvBuffers.front();
    recvBuffers.pop_front();
    return true;
  }

  virtual HANDLE GetAssociatedHandle() { return (HANDLE)sock; }
  virtual void ProcessRequest( threading::IOCPSheduler* sheuduler, threading::IOCPRequest* _req, DWORD numBytes )
  {
    NetworkIOCPRequest* req = static_cast<NetworkIOCPRequest*>(_req);

    switch( (int)req->requestType )
    {
    case NetworkIOCPRequest::Initialize:
      {
        threading::MutexLock lock( locker );
        hasDataRequest.SetRequestType( NetworkIOCPRequest::SendRequest );
        sendReq.SetRequestType( NetworkIOCPRequest::DataSent );
        recvReq.SetRequestType( NetworkIOCPRequest::DataReceived );
        DoReceive();
        if ( !sendBuffers.empty() )
          DoSend();
        break;
      }
    case NetworkIOCPRequest::SendRequest:
      {
        threading::MutexLock lock( locker );
        if ( sendReq.inUse )
          break;
        if ( sendBuffers.empty() )
          break;
        DoSend();

        break;
      }
    case NetworkIOCPRequest::DataSent:
      {
        threading::MutexLock lock( locker );
        sendReq.inUse = false;
        if ( sendBuffers.empty() )
          break;
        pOwner->PostRequest( this, &hasDataRequest );
        break;
      }
    case NetworkIOCPRequest::DataReceived:
      {
        threading::MutexLock lock( locker );
        DoDataReceived();

        DoReceive();
        break;
      }
    }
  }
  virtual void ProcessError( DWORD errorCode, threading::IOCPRequest* req ) {}
  void DoReceive() 
  {
    recvReq.inUse = true;
    recvReq.wsaBuffer.buf = recvReq.buffer;
    recvReq.wsaBuffer.len = 256;
    ULONG			ulFlags = 0;
    WSARecv( sock, &recvReq.wsaBuffer, 1, 0, &ulFlags, &recvReq, 0 );
  }
  void DoDataReceived() 
  {
    recvBuffers.push_back( recvReq.buffer );
    recvReq.inUse = false;
  }
  void DoSend() 
  {
    sendReq.inUse = true;
    sendReq.SetRequestType( NetworkIOCPRequest::DataSent );
    sendReq.buffer = sendBuffers.front();
    sendBuffers.pop_front();
    sendReq.wsaBuffer.buf = sendReq.buffer;
    sendReq.wsaBuffer.len = strlen( sendReq.buffer ) + 1;
    DWORD dwSendNumBytes = 0;
    WSASend( sock, &sendReq.wsaBuffer, 1, &dwSendNumBytes , 0, &sendReq, 0 );
  }
  //WSAWaitForMultipleEvents

  SOCKET sock;

  NetworkIOCPRequest hasDataRequest;

  list<TBuf> sendBuffers;
  NetworkIOCPRequest sendReq;
  list<TBuf> recvBuffers;
  NetworkIOCPRequest recvReq;
  threading::Mutex locker;
  threading::IOCPSheduler* pOwner;
};

NetworkIOCPRequest TCPConnection::initRequest = NetworkIOCPRequest( NetworkIOCPRequest::Initialize ); 

class TCPListenThread : public threading::Thread
{
  SOCKET sock;
  HANDLE sockEvent;
  threading::IOCPSheduler* pOwner;
public:
  list<TCPConnection*> newConns;
  threading::Mutex newConnsLock;

  TCPListenThread( threading::IOCPSheduler* _pOwner, const char* ip ) : pOwner(_pOwner )
  {
    sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED );
    Network::Address address( ip );

    sockEvent = WSACreateEvent();
    WSAEventSelect( sock, sockEvent, FD_ACCEPT );

    ::bind( sock, address, sizeof( SOCKADDR_IN ) );
    ::listen( sock, 5 );

    Resume();
  }
  ~TCPListenThread()
  {
    Stop( true );
  }

  virtual unsigned Work() 
  {
    while( isRunning )
    {
      DWORD dwRet;
      dwRet = WSAWaitForMultipleEvents( 1, &sockEvent, 0, 100, 0 );

      if ( !isRunning )
        break;

      WSANETWORKEVENTS events;
      WSAEnumNetworkEvents( sock, sockEvent, &events );


      if ( ( events.lNetworkEvents & FD_ACCEPT ) == 0 )
        continue;

      if ( events.iErrorCode[FD_ACCEPT_BIT] == 0 )
      {
        //SOCKADDR_IN	SockAddr;
        int nLen = sizeof(SOCKADDR_IN);
        SOCKET clientSocket = WSAAccept(sock, 0, &nLen, 0, 0 );

        newConnsLock.Lock();
        TCPConnection *pConn = new TCPConnection( pOwner, clientSocket );
        pOwner->RegisterClient( pConn );
        newConns.push_back( pConn );
        newConnsLock.Unlock();
      }
    }
    return 0;
  }
};


struct IOCPSuite : public CxxTest::TestSuite 
{
  struct MockIOCPRequest : public threading::IOCPRequest
  {
    enum
    {
      Test = threading::IOCPRequest::FirstClientRequest,

    };
    MockIOCPRequest() : data(0) { requestType = (threading::IOCPRequest::ERequest)MockIOCPRequest::Test; }
    int data;
  };
  class MockIOCPClient : public threading::IOCPClient
  {
  public:
    MockIOCPClient() : data(0) {}
    int data;
    threading::Mutex locker;

    virtual HANDLE GetAssociatedHandle() { return 0; }
    virtual void ProcessRequest( threading::IOCPSheduler* sheuduler, threading::IOCPRequest* _req, DWORD numBytes )
    {
      MockIOCPRequest* req = static_cast<MockIOCPRequest*>(_req);
      if ( req->requestType == MockIOCPRequest::Test )
      {
        locker.Lock();
        data += req->data;
        locker.Unlock();
        delete req;
      }
    }
    virtual void ProcessError( DWORD errorCode, threading::IOCPRequest* req ) {}
  };

  void TestSinglePacket()
  {
    threading::IOCPSheduler sh( 1, 1 );
    MockIOCPClient c1;
    sh.RegisterClient( &c1 );

    MockIOCPRequest* r = new MockIOCPRequest();
    r->data = 10;

    sh.PostRequest( &c1, r );

    int guard = 100;
    while( c1.data == 0 && --guard > 0 )
    {
      Sleep( 10 );
    }
    TS_ASSERT( c1.data == 10 );
    sh.Terminate();
  }

  void TestMultiPacket()
  {
    threading::IOCPSheduler sh( 10, 2 );
    MockIOCPClient c1;
    sh.RegisterClient( &c1 );

    {
      MockIOCPRequest* r1 = new MockIOCPRequest();
      r1->requestType = (threading::IOCPRequest::ERequest)MockIOCPRequest::Test;
      r1->data = 10;
      MockIOCPRequest* r2 = new MockIOCPRequest();
      r2->requestType = (threading::IOCPRequest::ERequest)MockIOCPRequest::Test;
      r2->data = 20;

      sh.PostRequest( &c1, r1 );
      sh.PostRequest( &c1, r2 );
    }

    int guard = 100;
    while( c1.data != 30 && --guard > 0 )
    {
      Sleep( 10 );
    }
    TS_ASSERT( c1.data == 30 );
    sh.Terminate();
  }

};


struct IOCPSocketsTest : public CxxTest::TestSuite 
{
  void setUpSuite()
  {
    WSADATA dummy;
    WSAStartup( MAKEWORD( 2, 2 ), &dummy );
  }
  void tearDownSuite()
  {
    WSACleanup();
  }

  void TestConnect()
  {
    threading::IOCPSheduler sh( 2, 2 );
    TCPListenThread listener( &sh, "127.0.0.1:6700" );
    TCPConnection c( &sh, "127.0.0.1:6700" );
    TCPConnection* s = 0;
    while( 1 )
    {
      Sleep( 10 );
      threading::MutexLock( listener.newConnsLock );
      if( listener.newConns.empty() )
        continue;
      s = listener.newConns.front();
      listener.newConns.pop_front();
      break;
    }

    TS_ASSERT( s != 0 );

    c.Send( "abcdef" );

    TBuf buf;
    while( !s->Receive( buf ) )
    {
      Sleep( 10 );
    }
    TS_ASSERT_EQUALS( buf, "abcdef" );
    sh.Terminate();
    delete s;
  }

};



