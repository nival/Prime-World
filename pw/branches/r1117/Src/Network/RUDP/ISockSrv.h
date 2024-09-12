#ifndef RUDP_ISOCKSRV_H_INCLUDED
#define RUDP_ISOCKSRV_H_INCLUDED

#include "UdpAddr.h"


namespace ni_udp
{

namespace ESocketStatus
{
  enum Enum { Ready, Closed, Failure };
}


typedef unsigned TAuxData;


class ISocket;
class ISocketCallback;

class ISocketServer : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISocketServer, IBaseInterfaceMT );

public:
  virtual StrongMT<ISocket> Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData ) = 0;
};





class ISocket : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISocket, IBaseInterfaceMT );

public:
  virtual ESocketStatus::Enum   Status() = 0;
  virtual TAuxData              AuxData() const = 0;
  virtual const NetAddr &       LocalAddr() const = 0;
  virtual void                  SendDatagram( const NetAddr & _destAddr, const void * _data, size_t _size ) = 0;
  virtual void                  Close() = 0;
};





class ISocketCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISocketCallback, IBaseInterfaceMT );

public:
  virtual void  OnDatagram( ISocket * _socket, const NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime ) = 0;
};

} //namespace ni_udp

#endif //RUDP_ISOCKSRV_H_INCLUDED
