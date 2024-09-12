#ifndef RDPTESTSERVER_H_INCLUDED
#define RDPTESTSERVER_H_INCLUDED

#include "Network/RUDP/IRdp.h"
#include <list>


class TestGame;
class TestClientContext;

class TestServer : public ni_udp::IRdpListenContextCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestServer, ni_udp::IRdpListenContextCallback, BaseObjectMT );
public:
  TestServer( ni_udp::IRdp * _rdp, int _avgGameDuration );

  bool Init( int _listenMux );
  bool Poll( timer::Time _now );
  void NewPlayer( TestClientContext * _ctx );

private:
  typedef std::list<StrongMT<TestClientContext>> Clients;
  typedef std::list<StrongMT<TestGame>> Games;

  StrongMT<ni_udp::IRdp>  rdp;
  StrongMT<ni_udp::IRdpListenContext> listenCtx;
  Clients clients;
  Games games;
  WeakMT<TestGame> newGame;

  threading::Mutex newClientsMutex;
  Clients newClients;
  int nextInstanceIdx;
  int nextUid;
  int nextGameId;
  int avgGameDuration;

  threading::Mutex newPlayersMutex;
  Clients newPlayers;

  threading::Mutex timeMutex;
  timer::Time now;

  timer::Time SafeNow();

  virtual ni_udp::IRdpConnectionCallback * OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr );

  void AddPlayerToGame( TestClientContext * _ctx, timer::Time _now );
};

#endif //RDPTESTSERVER_H_INCLUDED
