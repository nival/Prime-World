#include "stdafx.h"
#include "SockSrvWinsockBlocking.h"
#include "System/InlineProfiler.h"


namespace ni_udp
{

class BlockingUdpSocketServerWorker : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( BlockingUdpSocketServerWorker, threading::IThreadJob, BaseObjectMT );

public:
  BlockingUdpSocketServerWorker( BlockingUdpSocket * _sock ) :
  owner( _sock )
  {
  }

private:
  //threading::IThreadJob
  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    while ( isRunning )
    {
      NI_PROFILE_BLOCK( "Worker Loop" );

      if ( !owner->ListenSocket() )
        break;
    }
  }

  BlockingUdpSocket * owner;
};









BlockingUdpSocketServer::BlockingUdpSocketServer( int _threadPriority, int _bufferSize ) :
threadPriority( _threadPriority ),
bufferSize( _bufferSize )
{
}



StrongMT<ISocket> BlockingUdpSocketServer::Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData )
{
  SOCKET s = UdpSocket::CreateSocket( _bindAddr, UdpSocket::Options( UdpSocket::Options::BlockingMode, bufferSize, bufferSize ) );
  if ( s == INVALID_SOCKET )
    return 0;

  StrongMT<BlockingUdpSocket> sock = new BlockingUdpSocket( _cb, _bindAddr, s, _auxData, threadPriority );

  MessageTrace( "Socket opened. addr=%s, sock=%d", _bindAddr, s );

  return sock.Get();
}









BlockingUdpSocket::BlockingUdpSocket( ISocketCallback * _cb, const NetAddr & _bindAddr, SOCKET _s, TAuxData _auxData, unsigned _priority ) :
UdpSocket( _s, _bindAddr),
callback( _cb ),
auxData( _auxData ),
tempDbgNextDump( 0 ), tempDbgRecvTime( 0 ), tempDbgDeliverTime( 0 ),
tempDbgRecvNum( 0 ),
tempDbgSendNum( 0 ), tempDbgSendTime( 0 )
{
  workerThread = new threading::JobThread( new BlockingUdpSocketServerWorker( this ), "UdpWorkerBlocking" );
  workerThread->SetPriority( _priority );
}



BlockingUdpSocket::~BlockingUdpSocket()
{
  workerThread = 0;
}



ESocketStatus::Enum BlockingUdpSocket::Status()
{
  return UdpSocket::SocketIsValid() ? ESocketStatus::Ready : ESocketStatus::Failure;
}



void BlockingUdpSocket::SendDatagram( const NetAddr & _destAddr, const void * _data, size_t _size )
{
  timer::Time now = timer::Now();

  UdpSocket::SendDatagram( _destAddr, _data, _size );

  timer::Time delta = timer::Now() - now;
  LONG deltaLong = delta * 1e7;

  InterlockedIncrement( &tempDbgSendNum );
  InterlockedExchangeAdd( &tempDbgSendTime, deltaLong );
}



void BlockingUdpSocket::Close()
{
  workerThread->AsyncStop();
  workerThread->Wait( 3000 );

  //We DO NOT close socket object. It can be used by some parallel thread
}



bool BlockingUdpSocket::ListenSocket()
{
  NI_PROFILE_FUNCTION;

  timer::Time now = timer::Now();

  const int BufSz = 65536;
  char buf[BufSz];

  sockaddr from;
  int fromLen = sizeof( from );
  memset( &from, 0, fromLen );

  int recvRes = 0;
  {
    NI_PROFILE_BLOCK( "recvfrom" );
    recvRes = ::recvfrom( AccessHandle(), buf, BufSz, 0, &from, &fromLen );
  }

  timer::Time dbgRecvEnd = timer::Now();
  tempDbgRecvTime += dbgRecvEnd - now;

  if ( ( recvRes != 0 ) && ( recvRes != SOCKET_ERROR ) && ( fromLen == sizeof( sockaddr_in ) ) )
  {
    NI_PROFILE_BLOCK( "OnDatagram callback" );
    sockaddr_in & remoteAddr = (sockaddr_in &)from;

    StrongMT<ISocketCallback> cb = callback.Lock();
    if ( cb )
      cb->OnDatagram( this, NetAddr( remoteAddr ), buf, recvRes, dbgRecvEnd );
  }

  tempDbgDeliverTime += timer::Now() - dbgRecvEnd;
  ++tempDbgRecvNum;

  if ( now > tempDbgNextDump )
  {
    timer::Time elapsed = 30.0 + ( now - tempDbgNextDump );
    tempDbgNextDump = now + 30.0;

    double sendTime = (LONG)tempDbgSendTime * 1e-7;
    MessageTrace( "UDP socket perfomance debug. addr=%s, recv=%u, recv_tm=%.2f, deliver_tm=%.2f, send=%d, send_tm=%.2f", 
      BindAddr(),
      tempDbgRecvNum, 100.0 * tempDbgRecvTime / elapsed, 100.0 * tempDbgDeliverTime / elapsed,
      (LONG)tempDbgSendNum, 100.0 * sendTime / elapsed );

    tempDbgRecvTime = 0;
    tempDbgDeliverTime = 0;
    tempDbgRecvNum = 0;
    tempDbgSendNum = 0;
    tempDbgSendTime = 0;
  }

  return true;
}

} //namespace ni_udp
