#ifndef RDPTESTSVCLIENTCTX_H_INCLUDED
#define RDPTESTSVCLIENTCTX_H_INCLUDED

#include "Network/RUDP/IRdp.h"
#include "RdpTestBase.h"
#include <list>


class TestGame;
class TestServer;

class TestClientContext : public ni_udp::IRdpConnectionCallback, public RdpTestObject
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestClientContext, ni_udp::IRdpConnectionCallback, RdpTestObject );
public:
  TestClientContext( TestServer * _srv, ni_udp::IRdpConnection * _conn, timer::Time _now, int _instanceIdx, int _uid );

  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn ) {}
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

  void AddToGame( TestGame * _game );
  void SendStartGame( int _gameId );

  bool Poll( timer::Time _now );
  void GameStep( int _stepIndex );
  void FinishGame( int _stepIndex );

private:
  threading::Mutex                  mutex;
  StrongMT<ni_udp::IRdpConnection>  conn;
  WeakMT<TestGame>                  game;
  WeakMT<TestServer>                server;

  void ProcessHandshake( const void * _data, size_t _size );
  void ProcessClientStep( const void * _data, size_t _size );
};

#endif //RDPTESTSVCLIENTCTX_H_INCLUDED
