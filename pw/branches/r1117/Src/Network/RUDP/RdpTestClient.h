#ifndef RDPTESTCLIENT_H_INCLUDED
#define RDPTESTCLIENT_H_INCLUDED

#include "Network/RUDP/IRdp.h"
#include "RdpTestBase.h"


class RdpTestClient : public ni_udp::IRdpConnectionCallback, public RdpTestObject
{
  NI_DECLARE_REFCOUNT_CLASS_2( RdpTestClient, ni_udp::IRdpConnectionCallback, RdpTestObject );

public:
  RdpTestClient( ni_udp::IRdp * _rdp, timer::Time _now, int _instanceIdx, timer::Time _spontaneousDisconnectTime );

  bool Init( const ni_udp::NetAddr & _serverIpAddr, int _serverMuxIdx );

  //IRdpConnectionCallback
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

  bool Poll( timer::Time _now );

private:
  StrongMT<ni_udp::IRdp>    rdp;
  threading::Mutex          mutex;
  StrongMT<ni_udp::IRdpConnection>  conn;
  timer::Time               stepTime;
  int                       gameId;
  int                       stepIndex;
  bool                      stepNeedsTobeSent;
  const timer::Time         spontaneousDisconnectTime;

  void ProcessHandshake( const void * _data, size_t _size );
  void ProcessCommand( const void * _data, size_t _size );

  void ProcessStart( int _gameid );
  void ProcessStep( int _step );
  void ProcessFinish( int _step );
};

#endif //RDPTESTCLIENT_H_INCLUDED
