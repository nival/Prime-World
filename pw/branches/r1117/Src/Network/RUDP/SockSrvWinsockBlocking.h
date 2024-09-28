#ifndef RUDP_SOCKSRVWINSOCKBLOCKING_H_INCLUDED
#define RUDP_SOCKSRVWINSOCKBLOCKING_H_INCLUDED

#include "ISockSrv.h"
#include "System/JobThread.h"
#include "UdpSocket.h"
#include <map>


namespace ni_udp
{

class BlockingUdpSocketServerWorker;
class BlockingUdpSocketServer : public ISocketServer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( BlockingUdpSocketServer, ISocketServer, BaseObjectMT );

public:
  BlockingUdpSocketServer( int _threadPriority, int _bufferSize );

  virtual StrongMT<ISocket> Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData );

private:
  const int threadPriority;
  const int bufferSize;
};



class BlockingUdpSocket : public ISocket, public UdpSocket
{
  NI_DECLARE_REFCOUNT_CLASS_2( BlockingUdpSocket, ISocket, UdpSocket );

public:
  BlockingUdpSocket( ISocketCallback * _cb, const NetAddr & _bindAddr, SOCKET _s, TAuxData _auxData, unsigned _priority );
  ~BlockingUdpSocket();

  virtual ESocketStatus::Enum   Status();
  virtual TAuxData              AuxData() const { return auxData; }
  virtual const NetAddr &       LocalAddr() const { return UdpSocket::BindAddr(); }
  virtual void                  SendDatagram( const NetAddr & _destAddr, const void * _data, size_t _size );
  virtual void                  Close();

  bool ListenSocket();

private:
  WeakMT<ISocketCallback>         callback;
  const TAuxData                  auxData;
  StrongMT<threading::JobThread>  workerThread;

  timer::Time                     tempDbgNextDump, tempDbgRecvTime, tempDbgDeliverTime;
  unsigned                        tempDbgRecvNum;
  volatile LONG                   tempDbgSendNum, tempDbgSendTime;
};

} //namespace ni_udp

#endif //RUDP_SOCKSRVWINSOCKBLOCKING_H_INCLUDED
