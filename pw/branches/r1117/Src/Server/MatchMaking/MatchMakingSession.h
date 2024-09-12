#pragma once
#include <Server/RPC/RPC.h>
#include "MatchMakingTypes.h"
#include "HybridServer/RPeered.auto.h"
#include "Server/GameSession/GameBalancer/GameBalancerIface.h"
#include "Server/GameSession/GameBalancer/RGameBalancerIface.auto.h"
#include "MatchMakingSessionIface.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/LobbyPvx/RISessionHybridLink.auto.h"

namespace MatchMaking
{
  class RClient;
  class ClientCtx;
  class IGameSvcMngrGetter;
  class IManagerNotifier;
  class SessionHybridLink;

  class Session : public ISession, public GameBalancer::IBalancerCallback, public lobby::ISessionHybridLink, public HybridServer::IGameServerDispenserCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS( Session )
      NI_DECLARE_BASE( ISession )
      NI_DECLARE_BASE( GameBalancer::IBalancerCallback )
      NI_DECLARE_BASE( lobby::ISessionHybridLink )
      NI_DECLARE_BASE( HybridServer::IGameServerDispenserCallback )
      NI_DECLARE_BASE( BaseObjectMT )
    NI_DECLARE_END;

  public:
    Session();
    Session(SessionId const & sid, unsigned int numberOfPlayers,
      StrongMT<GameBalancer::RIBalancer> const & balancer, IManagerNotifier* mn, 
      StatisticService::GameStatClient * statistics );
    ~Session();

  public:
    //  MatchMaking::ISession
    void PlayerReady(MatchMaking::ClientId cid);

    //  GameBalancer::IBalancerCallback
    virtual void OnGameSvcAllocated(Peered::TSessionId userctx, uint allocid, HybridServer::IGameServerDispenser* gs);

    bool AddPlayer(StrongMT<MatchMaking::ClientCtx> const & pctx);

    SessionId sessionid() const;

    bool checkGameFinished();
    void sendSessionFinish();

  private:
    //ISessionHybridLink
    virtual void OnGameFinish( Peered::TSessionId _sessionId, int gameResultType, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics>& clientsStatistics ) {}
    virtual void OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, /*ECheatType*/ int _cheatType, const char * _clientIp ) {}
    virtual void OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo>& clientIds) {}

    //  IBalancerCallback
    void onAllocateGameSvc(int result);

    //HybridServer::IGameServerDispenserCallback
    virtual void GameServerAllocated( Peered::RIGameServer * _clientsInterface, Peered::RIGameServerInternal * _internalInterface, const Peered::SInstanceId& _instId );

    void OnStatisticsSessionNotify( bool result );

    GameBalancer::IBalancerCallback* GetBalancer() { return this; }

  private:
    typedef nstl::vector<StrongMT<ClientCtx>> PlayersT;
    PlayersT players_;

    SessionId sid_;
    int numberOfPlayers_;
    bool allPlayersReady_;

    IManagerNotifier*    managerNotifier_;

    StrongMT<GameBalancer::RIBalancer> balancer_;
    StrongMT<HybridServer::RIGameServerDispenser> gsDispenser_;
    StrongMT<Peered::RIGameServer> gameServer;
    StrongMT<Peered::RIGameServerInternal> gameServerInternal;
    StrongMT<SessionHybridLink> hybridLink;

    StrongMT<StatisticService::GameStatClient> statwr_;
  };

  inline
  SessionId Session::sessionid() const
  {
    return sid_;
  }

}
