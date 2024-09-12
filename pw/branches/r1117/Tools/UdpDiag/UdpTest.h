#ifndef UDPTEST_H_INCLUDED
#define UDPTEST_H_INCLUDED

#include "Network/RUDP/ISockSrv.h"
#include "System/Histogram.h"
#include <map>
#include <vector>
#include <list>
#include <Pdh.h>


namespace ni_udp
{
  class ISocketServer;
  class ISocket;
}


class UdpTestBase : public ni_udp::ISocketCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( UdpTestBase, ni_udp::ISocketCallback, BaseObjectMT );
public:
  UdpTestBase( const char * _bindAddr, int _bufferSize );

protected:
  StrongMT<ni_udp::ISocketServer> sockServer;
  StrongMT<ni_udp::ISocket> socket;
};

#endif //UDPTEST_H_INCLUDED
