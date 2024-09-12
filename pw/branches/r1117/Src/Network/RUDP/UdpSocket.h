#ifndef RUDP_UDPSOCKET_H_INCLUDED
#define RUDP_UDPSOCKET_H_INCLUDED

#include "UdpAddr.h"

namespace ni_udp
{

class UdpSocket : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( UdpSocket, BaseObjectMT );

public:
  static void GlobalInit();
  static void GlobalShutdown();

  struct Options
  {
    enum ECreateOptions
    {
      BlockingMode = 1,
      ReUseAddr = 2
    };
    unsigned  flags;
    unsigned  sendBuffer;
    unsigned  recvBuffer;

    explicit Options( unsigned _flags, unsigned _sendBufSz = 0, unsigned _recvBufSz = 0 ) :
    flags( _flags ),
    sendBuffer( _sendBufSz ),
    recvBuffer( _recvBufSz )
    {}
  };

  static SOCKET CreateSocket( const NetAddr & _bindAddr, const Options & _options );

  UdpSocket( SOCKET _s, const NetAddr & _bindAddr );
  ~UdpSocket();

  void Close();

  bool SocketIsValid() const;
  const NetAddr & BindAddr() const { return bindAddr; }
  SOCKET AccessHandle() const { return sock; }

  void SendDatagram( const NetAddr & _destAddr, const void * _data, size_t _size );

private:
  const NetAddr                 bindAddr;
  SOCKET                        sock;
};

} //namespace ni_udp

#endif //RUDP_UDPSOCKET_H_INCLUDED
