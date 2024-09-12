#ifndef UDPTESTSERVER_H_INCLUDED
#define UDPTESTSERVER_H_INCLUDED

#include "UdpTest.h"


class Server : public UdpTestBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( Server, UdpTestBase );
public:
  Server( const char * _bindAddr, int _bufferSize ) :
  UdpTestBase( _bindAddr, _bufferSize )
  {
  }

private:
  virtual void  OnDatagram( ni_udp::ISocket * _socket, const ni_udp::NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime );
};
#endif //UDPTESTSERVER_H_INCLUDED
