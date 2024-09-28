#ifndef RDPSOCKETFACTORY_H_INCLUDED
#define RDPSOCKETFACTORY_H_INCLUDED

#include "Network/RUDP/IRdp.h"
#include "System/RandomInterface.h"


namespace rdp_transport
{

class SocketFactory : public ni_udp::IRdpSocketFactory, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocketFactory, ni_udp::IRdpSocketFactory, BaseObjectMT );
public:
  SocketFactory( ni_udp::ISocketServer * _sockSrv, const ni_udp::NetAddr & _baseAddr, unsigned _portSearchRange, ni_rnd::IGenerator * _portRandomizer ) :
  sockSrv( _sockSrv ),
  addr( _baseAddr ),
  portSearchRange( _portSearchRange ),
  portRandomizer( _portRandomizer )
  {}

  const ni_udp::NetAddr & Addr() const { return addr; }

  virtual StrongMT<ni_udp::ISocket> OpenSocket( ni_udp::ISocketCallback * _cb )
  {
    if ( StrongMT<ni_udp::ISocket> s = sockSrv->Open( _cb, addr, 0 ) )
      return s;

    unsigned basePort = addr.Port();

    if ( portRandomizer )
    {
      unsigned tries = portSearchRange / 10;
      tries = Max( tries, 1u );

      for ( unsigned i = 0; i < tries; ++i )
      {
        addr.SetPort( basePort + (unsigned)portRandomizer->Next( portSearchRange ) );
        if ( StrongMT<ni_udp::ISocket> s = sockSrv->Open( _cb, addr, 0 ) )
          return s;
      }
    }

    for ( unsigned i = 1; i <= portSearchRange; ++i )
    {
      unsigned port = addr.Port() + 1;
      if ( port >= basePort + portSearchRange )
        port = basePort;
      addr.SetPort( port );

      if ( StrongMT<ni_udp::ISocket> s = sockSrv->Open( _cb, addr, 0 ) )
        return s;
    }

    return 0;
  }

private:
  const unsigned portSearchRange;
  Strong<ni_rnd::IGenerator> portRandomizer;
  StrongMT<ni_udp::ISocketServer> sockSrv;
  ni_udp::NetAddr addr;
};

} //namespace rdp_transport

#endif //RDPSOCKETFACTORY_H_INCLUDED
