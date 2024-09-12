#ifndef RDPTRANSPORTUTILS_H_INCLUDED
#define RDPTRANSPORTUTILS_H_INCLUDED

#include "Network/PacketDispatcher.h"

class Schedule;

namespace Transport
{
  class MessageFactory;
}

namespace ni_udp
{
  struct NetAddr;
  class IRdpConnection;
}

namespace rdp_transport
{


bool RdpTransportEnabled();

const static unsigned FirstAutoMux = 100;
const static unsigned LastAutoMux = 10000;
const static unsigned DefaultMux = 10;


class IMessageAllocator;

struct CommonCtx
{
  StrongMT<IMessageAllocator>   allocator;
  StrongMT<Schedule>            schedule;
  Transport::MessageFactory *   msgFactory;

  CommonCtx() :
  msgFactory( 0 )
  {}
};


string FormatAddr( const ni_udp::NetAddr & _addr, unsigned _mux );
bool ParseAddress( ni_udp::NetAddr & _addr, unsigned & _mux, const char * _str );




class PacketWriter : public Network::IPacketHandler, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( PacketWriter, Network::IPacketHandler, BaseObjectMT );

public:
  PacketWriter( ni_udp::IRdpConnection * _conn );

  template <class TPkt>
  void Send( const TPkt & pkt ) {
    Network::PacketDispatcher::SerializePacket<TPkt>( this, pkt );
  }

protected:
  virtual bool Handle( const void * _data, size_t _size );
  virtual bool Valid();

private:
  StrongMT<ni_udp::IRdpConnection> conn;
};

} //namesapce rdp_transport

#endif //RDPTRANSPORTUTILS_H_INCLUDED
