#include "RdpTestServer.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "RdpTransport/RdpSocketFactory.h"
#include "System/RandomInterfaceImpl.h"
#include "System/NiTimer.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"


TestRdpServer::TestRdpServer( TestRdpTransport * _transport, const RdpTestSettings & _sett ) :
settings( _sett ),
nextId( 1 )
{
  transport = _transport;
  
  listener = transport->rdp->Listen( 10, this );
  if ( !listener )
  {
    ErrorTrace( "Failed to listen" );
    transport = 0;
    return;
  }

  MessageTrace( "Server is listening. addr=%s", transport->bindAddr );
}



ni_udp::IRdpConnectionCallback * TestRdpServer::OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr )
{
  threading::MutexLock lock( mutex );

  StrongMT<TestRdpServerContext> ctx = new TestRdpServerContext( settings, ++nextId );
  ctx->Init( _conn, transport );

  MessageTrace( "New context. id=%d", ctx->Id() );

  contexts.push_back( ctx );

  return ctx;
}



void TestRdpServer::Poll()
{
  threading::MutexLock lock( mutex );

  for ( Contexts::iterator it = contexts.begin(); it != contexts.end(); )
  {
    StrongMT<TestRdpServerContext> ctx = *it;

    TestRdpContext::EStatus::Enum st = ctx->Poll();
    if ( ( st == TestRdpContext::EStatus::Finished ) || ( st == TestRdpContext::EStatus::Failed ) )
    {
      MessageTrace( "Removing context. id=%d, status=%s", ctx->Id(), ( st == TestRdpContext::EStatus::Failed ) ? "failed" : "finished" );
      it = lifehack::StlErase( contexts, it );
      return;
    }
    else
      ++it;
  }
}
