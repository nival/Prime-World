#pragma once

#include "System/EnumToString.h"
#include "TestSocialTransport.h"
#include "IGameTestClient.h"
#include <list>

namespace GtcSocial
{

namespace ESocClSt {
  enum Enum {
    None,
    Start,
    WaitingAddAck,
    WaitingGame, //in line
    WaitingGameAccept,
    GuardLobby,
    GuardLobbyReady,
    PreparedToGame,
    PreparedToGameAndPopped,
    InGame,
    LeavingGame,
    WaitingGameFinish, //As a leaver
    Cancelling,
    Finished,
    Failed,
    TimedOut
  };

  inline bool Terminal( Enum e ) {
    return ( e == Finished ) || ( e == Failed ) || ( e == TimedOut ); }

  NI_ENUM_DECL_STD;
}


namespace EReqSt = socialLobby::ERequestStatus;

class SocialClient : public BaseObjectMT, public ITransportClientCallback
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocialClient, BaseObjectMT, ITransportClientCallback );

public:
  SocialClient( const SSocialConfig & socConfig, ITransport * testSocialTransport, const socialLobby::SMatchmakingRequest & reqData );
  ~SocialClient();

  ESocClSt::Enum State() const { return state; }
  void Poll();

  void PoppedToPvX( gtc::IGameTestClient * _cl );
  void PvXClientTerminated();

  const socialLobby::SMatchmakingRequest & Request() const { return req; }
  const string & SessionKey() const { return sessionKey; }
  lobby::TSocialGameId GameId() const { return _acceptedGameId; }
  const socialLobby::SGameResults & GameResults() const { return gameResults; }

  struct StateTiming {
    ESocClSt::Enum  state;
    timer::Time     timing;
    StateTiming( ESocClSt::Enum _st, timer::Time _t ) : state( _st ), timing( _t ) {}
  };

  typedef std::list<StateTiming> StatesTiming;

  const StatesTiming & StatesTimingLog() const { return statesTimingLog; }
  void ClearStatesTimingLog() { statesTimingLog.clear(); }

private:
  const SSocialConfig _socConfig;
  StrongMT<ITransportClient> _socTransportClient;
  socialLobby::SMatchmakingRequest  req;
  NCore::PlayerInfo playerData;
  bool            added;

  ESocClSt::Enum  state;
  timer::Time     stateTimeoutMoment;
  timer::Time     stateStartTime;
  ESocClSt::Enum  timedOutState;
  timer::Time     nextPingTime;

  string          sessionKey;
  lobby::TSocialGameId _acceptedGameId;
  lobby::TSocialGameId _guardReadyGameId;
  socialLobby::SGameResults gameResults;
  WeakMT<gtc::IGameTestClient> pvxClient;

  StatesTiming    statesTimingLog;

  class States;
  class Pings;

  void ChangeState( ESocClSt::Enum _st, timer::Time _timeout = 0 );
  void AddRequest();
  virtual void OnAddRequest(); //ITransportClientCallback

  void Ping( timer::Time t );
  virtual void OnPing( const socialLobby::SMatchmakingStatus & ping ); //ITransportClientCallback

  void GameFinished( const socialLobby::SGameResults & results );
  void Cancel();
  void Accept( lobby::TSocialGameId gameId );
  void GuardReady( lobby::TSocialGameId gameId );
  void Leave();
  void TerminatePvx();

  bool EnsurePing( const socialLobby::SMatchmakingStatus & ping, const Pings & pings );
  bool EnsureState( const char * _msg, const States & states );
  void Msg( const char * _fmt, ... );
  void Error( const char * _fmt, ... );
  void Fail( const char * _fmt, ... );
};

} //namespace GtcSocial
