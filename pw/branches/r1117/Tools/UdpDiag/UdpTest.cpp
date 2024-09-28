#include "UdpTest.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"
#include "System/LogFileName.h"


UdpTestBase::UdpTestBase( const char * _bindAddr, int _bufferSize )
{
  sockServer = new ni_udp::BlockingUdpSocketServer( 0, _bufferSize );
  socket = sockServer->Open( this, ni_udp::NetAddr( _bindAddr ), 0 );

  if ( socket )
    MessageTrace( "Socket opened. addr=%s", socket->LocalAddr() );
  else
    ErrorTrace( "Failed to open socket. addr=%s", _bindAddr );
}
