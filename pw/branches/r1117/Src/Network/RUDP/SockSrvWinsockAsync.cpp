#include "stdafx.h"
#include "SockSrvWinsockAsync.h"
#include "System/InlineProfiler.h"
#include <map>


namespace ni_udp
{

class AsyncUdpSocketServerWorker : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( AsyncUdpSocketServerWorker, threading::IThreadJob, BaseObjectMT );

public:
  AsyncUdpSocketServerWorker()
  {
  }

  void AddSocket( AsyncUdpSocket * _s )
  {
    threading::MutexLock lock( mtx );

    sockets[_s->AccessHandle()] = _s;
  }

private:
  //threading::IThreadJob
  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    const int BufSz = 65536;
    char buf[BufSz];

    while ( isRunning )
    {
      NI_PROFILE_BLOCK( "Select loop" );

      fd_set readfds;
      FD_ZERO( &readfds );

      {
        NI_PROFILE_BLOCK( "fd_set build" );

        threading::MutexLock lock( mtx );

        NI_VERIFY( sockets.size() <= FD_SETSIZE, "", continue );

        for ( Sockets::iterator it = sockets.begin(); it != sockets.end(); )
          if ( StrongMT<AsyncUdpSocket> locked = it->second.Lock() )
          {
            readfds.fd_array[readfds.fd_count++] = it->first;
            ++it;
          }
          else
            it = sockets.erase( it );
      }

      if ( !readfds.fd_count )
      {
        NI_PROFILE_BLOCK( "Idle" );
        Sleep( 10 );
        continue;
      }

      TIMEVAL tmv;
      memset( &tmv, 0, sizeof( tmv ) );
      tmv.tv_usec = 100000;
      int selResult = ::select( 0, &readfds, 0, 0, &tmv );
      if ( selResult == SOCKET_ERROR )
      {
        ErrorTrace( "Select failed. code=%s", WSAGetLastError() );
        continue;
      }

      if ( selResult > 0 )
      {
        NI_PROFILE_BLOCK( "readfds" );

        threading::MutexLock lock( mtx );

        for ( unsigned i = 0; i < readfds.fd_count; ++i )
        {
          SOCKET s = readfds.fd_array[i];

          Sockets::iterator it = sockets.find( s );
          NI_VERIFY( it != sockets.end(), "Selected unknown socket", continue );
          StrongMT<AsyncUdpSocket> locked = it->second.Lock();
          if ( !locked )
          {
            WarningTrace( "Got datagram for deleted socket. sock=%d", s );
            sockets.erase( it );
            continue;
          }

          StrongMT<ISocketCallback> cb = locked->LockCallback();
          if ( !cb )
          {
            WarningTrace( "Got datagram for socket without callback. sock=%d", s );
            sockets.erase( it );
            continue;
          }

          sockaddr from;
          int fromLen = sizeof( from );
          memset( &from, 0, fromLen );

          NI_PROFILE_BLOCK( "recvfrom" );
          int recvRes = ::recvfrom( s, buf, BufSz, 0, &from, &fromLen );
          if ( ( recvRes != 0 ) && ( recvRes != SOCKET_ERROR ) && ( fromLen == sizeof( sockaddr_in ) ) )
          {
            sockaddr_in & remoteAddr = (sockaddr_in &)from;
            cb->OnDatagram( locked, NetAddr( remoteAddr ), buf, recvRes, timer::Now() );
          }
          else if ( recvRes != 0 )
          {
            int code = WSAGetLastError();
            if ( code != WSAECONNRESET ) //WSAECONNRESET means that previous sendto resulted in "ICMP Port Unreachable"
              ErrorTrace( "Recieve error. code=%d, addr_len=%d", code, fromLen ); //Another error
          }
        }
      }
    }
  }

  typedef std::map<SOCKET, WeakMT<AsyncUdpSocket>>  Sockets;

  threading::Mutex  mtx;
  Sockets           sockets;
};









AsyncUdpSocketServer::AsyncUdpSocketServer()
{
  worker = new AsyncUdpSocketServerWorker;
  thread = new threading::JobThread( worker, "UdpWinSock" );
}



StrongMT<ISocket> AsyncUdpSocketServer::Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData )
{
  SOCKET s = UdpSocket::CreateSocket( _bindAddr, UdpSocket::Options( 0 ) );
  if ( s == INVALID_SOCKET )
    return 0;

  AsyncUdpSocket * sock = new AsyncUdpSocket( _cb, _bindAddr, s, _auxData );
  worker->AddSocket( sock );

  MessageTrace( "Socket opened. addr=%s, sock=%d", _bindAddr, s );

  return sock;
}

} //namespace ni_udp
