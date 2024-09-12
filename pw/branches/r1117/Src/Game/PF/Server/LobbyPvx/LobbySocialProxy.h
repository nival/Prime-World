#ifndef LOBBYSOCIALPROXY_H_INCLUDED
#define LOBBYSOCIALPROXY_H_INCLUDED

#include "rpc/IfaceRequester.h"
#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "LobbyConfig.h"
#include <list>

namespace socialLobby
{
  class IPvxSvc;
  class RIPvxInterface;
}

namespace lobby
{

class ServerNode;

class SocialLobbyProxy : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( SocialLobbyProxy, BaseObjectMT );
public:
  SocialLobbyProxy( IConfigProvider * _cfg, rpc::GateKeeper * _gk, socialLobby::IPvxSvc * _pvxInterface, const Transport::TServiceId & _serviceId );

  socialLobby::RIPvxInterface * GetRemotePtr();

  //mirror of socialLobby::RIPvxInterface
  bool PvXPreparedForUser( socialLobby::TUserIdPvX _userId, const string & _key );
  bool UserEnteredPvX( socialLobby::TUserIdPvX _userId );
  bool UserDroppedFromPvX( socialLobby::TUserIdPvX _userId, bool _intentional );
  bool GameFinished( TSocialGameId _gameId, ETeam::Enum _winner );

  void OnConfigReload();

  void Poll( timer::Time _now, unsigned _load );

private:
  struct GameFinishEvent : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( GameFinishEvent, BaseObjectMT );
  public:
    struct State { enum Enum { WaitingAck, Successfull, OnPause, RetryFailed }; };
    TSocialGameId       gameId;
    ETeam::Enum         winner;
    State::Enum         state;
    timer::Time         start, currentPause, nextSendAttempt;

    GameFinishEvent( TSocialGameId _gameId, ETeam::Enum _winner, State::Enum _state, timer::Time _now, timer::Time _nextSendAttempt, timer::Time _initialPause ) :
    gameId( _gameId ),
    winner( _winner ),
    state( _state ),
    start( _now ),
    currentPause( _initialPause ),
    nextSendAttempt( _nextSendAttempt )
    {}

    void RpcCallResult( bool _result, int, rpc::CallStatus _st );
  };

  typedef std::list<StrongMT<GameFinishEvent> > GameFinishEvents;

  const Transport::TServiceId       serviceId;
  StrongMT<IConfigProvider>         config;
  timer::Time                       now;
  StrongMT<rpc::IfaceRequester<socialLobby::RIPvxInterface> > remote;
  StrongMT<socialLobby::IPvxSvc>    pvxInterface;
  timer::Time                       nextLoadNotify;
  bool                              resendPvxSettings;
  GameFinishEvents                  gameFinishEvents;

  void ParseClusterSettings( socialLobby::PvxClusterSettings & _sett );
  void SendPvxInstance();
  void SendPvxSettings();
  void TmpDummyCallback( bool okay, const char * methodName, rpc::CallStatus st );
};

} //namespace lobby

#endif //LOBBYSOCIALPROXY_H_INCLUDED
