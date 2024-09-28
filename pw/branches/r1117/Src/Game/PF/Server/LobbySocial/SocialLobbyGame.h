#ifndef SOCIALLOBBYGAME_H_INCLUDED
#define SOCIALLOBBYGAME_H_INCLUDED

#include "SocialLobbyTypes.h"
#include <set>

namespace NDb
{
  struct AdvMapDescription;
  struct RollSettings;
}

namespace socialLobby
{

class Config;
class IControl;
class IPvxSvcWrapper;
class UserContext;
class Party;
class IGameStatistics;


namespace EGameState
{
  enum Enum { Accepting, PreGameLobby, PvXReady, PvX, Cleared };
}


class Game : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Game, BaseObjectST );

public:
  Game( Config * _cfg, lobby::TSocialGameId _id, const mmaking::SGame & _data, const NDb::AdvMapDescription * _map, const NDb::RollSettings * _rollSett, bool _customGame, timer::Time _now, IGameStatistics * _statistics, IControl * _control );

  EGameState::Enum State() const { return state; }

  void Poll( timer::Time _now );

  void AddParty( Party * _party );

  lobby::TSocialGameId Id() const { return id; }
  const char * StrId() const { return strId.c_str(); }

  const mmaking::SGame & Data() const { return data; }
  timer::Time CreationTime() const { return creationTime; }
  Strong<IPvxSvcWrapper> PvxService() const { return pvxService.Get(); }

  int TotalPlayersCount() const { return totalPlayers; }
  int PartiesCount() const { return parties.size(); }
  Party * GetParty( int _idx ) const { NI_VERIFY( _idx >= 0 && _idx < parties.size(), "", return 0 ); return parties[_idx]; }

  bool FindMemberByPvx( Strong<UserContext> & _ctx, Strong<Party> & _party, TUserIdPvX _pvxUserId );

  void AcceptGame( UserContext * _ctx );
  void GuardReady( UserContext * _ctx );

  void RemoveUser( UserContext * _ctxToKill );

  void RollBackGameRequests( UserContext * _exceptThis );
  void OutputPing( SMatchmakingStatus & _ping, TUserIdPvX _pvxid );

  bool CanBeASpectator() const;
  void AddSpectator( UserContext * _spect );

private:
  typedef std::set<Weak<UserContext>>  TWeakRequestSet;

  const lobby::TSocialGameId id;
  const string              strId;
  const timer::Time         creationTime;
  bool                      customGame;
  Strong<Config>            config;
  WeakMT<IControl>          control;
  EGameState::Enum          state;
  timer::Time               now;
  vector<Weak<Party>>       parties;
  mmaking::SGame            data;
  NDb::Ptr<NDb::AdvMapDescription> map;
  NDb::Ptr<NDb::RollSettings> rollSett;
  int                       totalPlayers;
  int                       acceptedCount; //Precalculated value based on 'members'
  timer::Time               preGameLobbyStartTime;
  bool                      hadPreGameLobby;
  Weak<IPvxSvcWrapper>      pvxService;
  TWeakRequestSet           spectators;

  StrongMT<IGameStatistics> statistics;

  void Clear();
  void ChangeState( EGameState::Enum st ) { state = st; }
  void ToPvx();
  void AcceptTimedOut();
  void PreGameLobbyTimedOut();
  bool SetupGameForPvx( PvxGameDetails & _pvxDetails );
  bool AddRatingDeltasToPvxInfo( PvxGameDetails & _pvxDetails );
  void StartPreGameLobby();
  void LogGame( bool success, UserContext * cancelledCtx );
  void PingDebugInfo( SMatchmakingStatus & ping );
  void RemoveAllRequests();
};

} //namespace socialLobby

#endif //SOCIALLOBBYGAME_H_INCLUDED
