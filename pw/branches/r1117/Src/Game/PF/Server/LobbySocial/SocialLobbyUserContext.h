#ifndef SOCIALLOBBYUSERCONTEXT_H_INCLUDED
#define SOCIALLOBBYUSERCONTEXT_H_INCLUDED

#include "SocialLobbyTypes.h"
#include "SocialLobbyStatistics.h"

namespace socialLobby
{

class IUserContext;

//TODO: Move this to some place
template <typename Type>
struct ValuesSetChecker
{
  ValuesSetChecker( Type v ) : value( v ), result( false ) {}
  operator bool () const { return result; }
  ValuesSetChecker & operator | ( Type v ) { if ( value == v ) result = true; return *this; }

private:
  Type  value;
  bool  result;
};

template <typename Type>
inline ValuesSetChecker<Type> StateIsOneOf( Type v ) { ValuesSetChecker<Type>( v ); }



/*
States table (outdated!):
| Ping            | Game.pulledToLobby | SessionKey |
-----------------------------------------------------
| -               | -                  |            |
| InLine          | -                  |            |
| WaitingAccept   | false              |            |
| Accepted        | false              |            |
| WaitingInLobby  | true               | yes        |
| InGame          | true               |            |
| AcceptTimedOut  | -                  |            |
| GameFinished    | -                  |            |
*/


class Config;
class Game;
class Party;
class IControl;
class INotify;



class UserContext : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( UserContext, BaseObjectST );

public:
  UserContext( Config * _cfg, const SMatchmakingRequest & _data, timer::Time _now, IControl * _control, INotify * _notify );

  IUserContext * RpcInterface() const { return rpcWrapper; }

  ValuesSetChecker<ERequestStatus::Enum> StatusIs() { return ValuesSetChecker<ERequestStatus::Enum>( status ); }

  ERequestStatus::Enum Status() const { return status; }
  const SMatchmakingRequest & Data() const { return data; }
  const char * FmtId() const { return dbgFormattedId.c_str(); }

  StrongMT<INotify> & GetNotify() { return notify; }
  void OverrideNotify( INotify * _notify );

  Game * GetGame() const { return game; }
  void SetGame( Game * g ) { game = g; }

  void SetParty( Party * p ) { party = p; }
  Party * GetParty() const { return party; }

  void ClearPlayerDetails() { playerDetails = NCore::PlayerInfo(); }
  const NCore::PlayerInfo & PlayerDetails() const { return playerDetails; }

  void SetPreGameLobbyReadiness( bool ready );
  bool PreGameLobbyReadiness() const { return preGameLobbyReadiness; }
  timer::Time PreGameLobbyReadyTime() const { return preGameLobbyReadyTime; }

  void Poll( timer::Time _now );

  void ChangeStatus( ERequestStatus::Enum _newStatus );

  void AbandonGame( timer::Time _now );

  void SetPvxDropTime( timer::Time t ) { pvxDropTime = t; }

  void Modify() { modified = true; }

  void PvxPrepared( const string & key );
  void SetupGameResultForCompletion( lobby::ETeam::Enum _winner, lobby::TSocialGameId _dbgGameId, const mmaking::SGame & _mmData );
  void SetupCancelledStatistics( StatisticService::RPC::MMakingCanceled & _statData, timer::Time _now, int _partySize );

  void CancelPartyRequest() { CancelRequest( ECancelMode::Party ); }

  static int CountLoseStreak( const string & winLoseHistory );

private:
  class RpcWrapper;

  Strong<Config>            config;
  SMatchmakingRequest       data;
  const timer::Time         creationTime;
  WeakMT<IControl>          control;
  StrongMT<INotify>         notify;
  StrongMT<IUserContext>    rpcWrapper;
  ERequestStatus::Enum      status;
  timer::Time               now;
  Weak<Game>                game;
  NCore::PlayerInfo         playerDetails;
  SGameResults              gameResults;
  string                    mixedSessionLogin;
  timer::Time               pvxDropTime;
  timer::Time               currentStatusExpires;
  timer::Time               connectionLostExpires;

  Strong<Party>             party;

  string                    dbgFormattedId;
  bool                      preGameLobbyReadiness;
  timer::Time               preGameLobbyReadyTime;

  bool                      modified;

  struct ECancelMode { enum Enum { Normal, Party, Emergency }; };
  //IUserContext mirror
  void AcceptGameSession( const SPlayerData & _playerData );
  void ChangeGuardHero( const SPlayerData & _playerData );
  void GuardReady();
  void ReconnectToGame();
  void LeaveGame();
  void CancelRequest( ECancelMode::Enum mode );

  void OutputPing();
  void LogPing( const SMatchmakingStatus & _ping );
};



} //namespace socialLobby

#endif //SOCIALLOBBYUSERCONTEXT_H_INCLUDED
