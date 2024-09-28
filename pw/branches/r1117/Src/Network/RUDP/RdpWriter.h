#ifndef RUDP_RDPWRITER_H_INCLUDED
#define RUDP_RDPWRITER_H_INCLUDED

#include "RdpConnDescriptor.h"
#include "RdpProto.h"

namespace ni_udp
{

struct ConnDescriptor;
class RdpConnStats;

class RdpWriter : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpWriter, BaseObjectMT );

public:
  RdpWriter( ISocket * _socket, RdpConnStats * _stats );

  void Send( const ConnDescriptor & _descr, proto::EPktType::Enum _type, unsigned _index );
  void SendRaw( const NetAddr & _destAddr, const void * _data, size_t _size );

private:
  StrongMT<ISocket>       socket;
  StrongMT<RdpConnStats>  stats;
};

} //namespace ni_udp

#endif //RUDP_RDPWRITER_H_INCLUDED
