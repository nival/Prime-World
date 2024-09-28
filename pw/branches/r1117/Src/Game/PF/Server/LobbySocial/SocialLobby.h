#ifndef SOCIALLOBBY_H_INCLUDED
#define SOCIALLOBBY_H_INCLUDED

#include "ISocialLobby.h"
#include "ISocialLobbyPvxAck.h"
#include "Server/LiveMMaking/ILiveMMaking.h"
#include "Server/LiveMMaking/ILiveMMakingClient.h"
#include "System/PersistentId.h"
#include "SocialLobbyCtrl.h"
#include "SocialLobbyStatistics.h"
#include "ServerAppBase/PerfCounters.h"
#include <set>
#include <list>
#include <map>

namespace NDb
{
  struct RollSettings;
}


namespace socialLobby
{

class Config;
class UserContext;
class Game;
class Party;
class IPvxAcknowledge;
class MmLogix;
class PvxServices;
class IMaps;
class ClientRevisions;


class SocialLobby : public mmaking::ILiveMMakingClient, public ISocialInterface, public IPvxInterface, public IControl, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_5( SocialLobby, mmaking::ILiveMMakingClient, ISocialInterface, IPvxInterface, IControl, BaseObjectMT );
  RPC_REDEFINE_ID();

public:
  SocialLobby( Config * _cfg, IGameStatistics * _statistics, IPvxAcknowledge * _pvxAck, IMaps * _maps, const NDb::RollSettings * _rollSett, Transport::IPerfCounters * _perfCounters );

  void UpdateConfigByValue( Config * _cfg );

  void Poll( timer::Time realTime );

protected:
  //mmaking::ILiveMMakingClient
  virtual void MmLogicSetupResult( const Transport::TServiceId & _svcId, bool _result );
  virtual void GameMatchmaked( const mmaking::SGame & _game );
  virtual void GameMatchmakedForReconnect( const mmaking::SReconnectSlot & _slot );
  virtual void MmResultAddRequest( mmaking::TRequestUId _requestUId, bool _ok );
  virtual void MmResultRemoveRequest( mmaking::TRequestUId _requestUId, bool _ok );
  virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok );
  virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok );
  virtual void MmDebugStatus( const char * _status );

  //ISocialInterface
  virtual void            RegisterMmLogic( const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _logic, int _gameModes );
  virtual void            AddRequest( const SMatchmakingRequest & _reqData, INotify * _callback );
  virtual void            Spectate( const SMatchmakingRequestCore & _reqData, TUId _targetUid, NI_LPTR INotify * _callback );
  virtual void            GetRequest( TUId _uid, INotify * _callback );
  virtual SServerStatus   GetServerStatus();


  //IPvxInterface
  virtual bool            PvxInstance( IPvxSvc * _pvx, const string & _clusterId, const Transport::TServiceId & _svcId, const PvxClusterSettings& _settings );
  virtual bool            UpdatePvxSettings( const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings );
  virtual void            PvxInstanceLoadNotify( const string& _clusterId, const Transport::TServiceId& _svcId, unsigned _load );
  virtual bool            PvXPreparedForUser( TUserIdPvX _userId, const string & _key );
  virtual bool            UserEnteredPvX( TUserIdPvX _userId );
  virtual bool            UserDroppedFromPvX( TUserIdPvX _userId, bool _intentional );
  virtual bool            GameFinished( lobby::TSocialGameId _gameId, int /*lobby::ETeam::Enum*/ _winner );

  //IControl
  virtual RemoteMmLogic *             GetMmLogic( const string & mapId ) const;
  virtual Strong<IPvxSvcWrapper>      AllocatePvxSvc( const string & _clusterId, unsigned _loadIncrement );
  virtual string                      DetermineClusterForGame( const mmaking::SGame & _game ) const;
  virtual StrongMT<IPvxAcknowledge>   GetPvxAcknowledge() { return pvxAck.Lock(); }
  virtual void                        RemoveUserContext( UserContext * _ctx, bool _logStatistics );
  virtual int                         MapClientRevision( int srcRev );

private:
  typedef std::map<TUId, Strong<UserContext>>  TRequestMap;
  typedef std::map<TUserIdPvX, Strong<UserContext>>  TRequestMapPvx;
  typedef std::map<lobby::TSocialGameId, Strong<Game>>  TGames;
  typedef std::list<Weak<UserContext>>  TWeakRequestList;
  typedef std::map<TPartyId, Weak<Party>>  TParties;
  typedef std::map<mmaking::TRequestUId, Weak<Party>>  TPartiesByMmRequest;

  Strong<Config>      config;

  mmaking::TRequestUId  nextMmRequestId;
  Strong<MmLogix>     mmLogix;
  Strong<IMaps>       maps;
  NDb::Ptr<NDb::RollSettings> rollSett;

  nival::PersistentId persistentIdGenerator;

  TRequestMap         requests;
  TRequestMapPvx      requestsForPvx; //TEMP
  TParties            parties;
  TPartiesByMmRequest partiesByMmReq;

  TGames              games;

  Strong<PvxServices> pvxServices;

  StrongMT<IGameStatistics> statistics;
  WeakMT<IPvxAcknowledge> pvxAck; //TODO: store this by strong pointer

  timer::Time         now;

  StrongMT<ClientRevisions> clientRevisions;

  list<timer::Time>   lastGameWaitTimes;
  timer::Time         lastGameGathered;

  map< int, map< int, map<int, list<timer::Time>>> >   lastGameWaitTimesByMode;
  map< int, map< int, map<int, timer::Time>>>         lastGameGatheredByMode;

  string              mmDebugStatus;

  WeakMT<Transport::IPerfCounters> perfCounters;

  const string SocialLobby::GetModeKey(const int i);
  void ProcessConfiguration();

  bool CheckRequestDuplication( UserContext * _newCtx );
  void RemoveRequest( UserContext * _ctx, bool clearGameOfRequest );

  struct EFindReason {
    enum Enum { Get, PvxReady, EnteredPvx, DroppedFromPvx };
    static const char * ToString( Enum e );
  };
  UserContext * FindContextSafe( TUId _uid, EFindReason::Enum _reason );
  UserContext * FindContextSafePvx( TUserIdPvX _userid, EFindReason::Enum _reason );
  UserContext * GetContextInLobby( TUId _uid, EFindReason::Enum _reason );
  UserContext * GetContextInLobbyPvx( TUserIdPvX _userid, EFindReason::Enum _reason );

  UserContext * FindSpectatorTarget( const SMatchmakingRequestCore & _reqData, TUId _targetUid );
  bool CreateCustomGame( Party * _party );
  void CreateGame( const mmaking::SGame & _mmData );
  void MoveGame( TGames & from, TGames & to, lobby::TSocialGameId gameId );
  void PollRequests();
  void PollParties();
  void PollGames();
  void PollMmLogic();
  void GatherMmStatistics( const mmaking::SGame & _mmData );

  void LogCancelledToStatistics( UserContext * _ctx );
  void GetServerStatusEx(SServerStatus& st); 

  //friend void GatherMmStatisticsByMode( SocialLobby&, const mmaking::SGame & _mmData );
};


} //namespace socialLobby



#endif //SOCIALLOBBY_H_INCLUDED
