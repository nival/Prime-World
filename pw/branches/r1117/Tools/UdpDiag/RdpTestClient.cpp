#include "RdpTestClient.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "RdpTransport/RdpSocketFactory.h"
#include "System/RandomInterfaceImpl.h"
#include "System/NiTimer.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"


TestRdpClient::TestRdpClient( const RdpTestSettings & _sett, int _id ) :
TestRdpContext( _sett, _id )
{
}



bool TestRdpClient::ConnectTo( TestRdpTransport * _transport, const char * _serverAddr )
{
  transport = _transport;

  ni_udp::NetAddr remoteAddr( _serverAddr );
  conn = transport->rdp->Connect( remoteAddr, 10, this );

  if ( !conn )
  {
    ErrorTrace( "Failed to start connection" );
    transport = 0;
    return false;
  }

  return true;
}




void TestRdpClient::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  TestRdpContext::OnConnectionEstablished( _conn );

  NI_ASSERT( conn && transport, "" );
  Init( conn, transport );
  LimitLifetime();
}
