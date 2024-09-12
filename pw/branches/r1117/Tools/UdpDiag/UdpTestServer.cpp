#include "UdpTestServer.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"
#include "System/LogFileName.h"


void Server::OnDatagram( ni_udp::ISocket * _socket, const ni_udp::NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  if ( _size < sizeof( int ) )
  {
    WarningTrace( "Datagram too small! size=%d, remote=%s", _size, _remoteAddr );
    return;
  }

  int index = *(int *)_data;
  MessageTrace( "Incoming packet. index=%d, size=%d, remote=%s", index, _size, _remoteAddr );

  _socket->SendDatagram( _remoteAddr, _data, _size );
}
