#ifndef RUDP_SOCKSRVWINSOCKASYNC_H_INCLUDED
#define RUDP_SOCKSRVWINSOCKASYNC_H_INCLUDED

#include "ISockSrv.h"
#include "System/JobThread.h"
#include "UdpSocket.h"


namespace ni_udp
{

class AsyncUdpSocketServerWorker;
class AsyncUdpSocketServer : public ISocketServer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( AsyncUdpSocketServer, ISocketServer, BaseObjectMT );

public:
  AsyncUdpSocketServer();

  virtual StrongMT<ISocket> Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData );

private:
  StrongMT<AsyncUdpSocketServerWorker> worker;
  StrongMT<threading::JobThread>    thread;
};



class AsyncUdpSocket : public ISocket, public UdpSocket
{
  NI_DECLARE_REFCOUNT_CLASS_2( AsyncUdpSocket, ISocket, UdpSocket );

public:
  AsyncUdpSocket();
  AsyncUdpSocket( ISocketCallback * _cb, const NetAddr & _bindAddr, SOCKET _s, TAuxData _auxData ) :
  UdpSocket( _s, _bindAddr),
  callback( _cb ),
  auxData( _auxData )
  {}

  virtual ESocketStatus::Enum   Status() { return UdpSocket::SocketIsValid() ? ESocketStatus::Ready : ESocketStatus::Failure; }
  virtual TAuxData              AuxData() const { return auxData; }
  virtual const NetAddr &       LocalAddr() const { return UdpSocket::BindAddr(); }
  virtual void                  SendDatagram( const NetAddr & _destAddr, const void * _data, size_t _size ) { UdpSocket::SendDatagram( _destAddr, _data, _size ); }
  virtual void                  Close() { /*TBD*/ }

  StrongMT<ISocketCallback> LockCallback() { return callback.Lock(); }

private:
  WeakMT<ISocketCallback>       callback;
  const TAuxData                auxData;
};

} //namespace ni_udp

#endif //RUDP_SOCKSRVWINSOCKASYNC_H_INCLUDED
