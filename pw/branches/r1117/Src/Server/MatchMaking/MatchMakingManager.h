#pragma once

#include <RPC/RPC.h>
#include "MatchMakingTypes.h"
#include "RMatchMakingClient.auto.h"
#include "System/IDGenerator.h"
#include "MatchMakingClientCtx.h"
#include "MatchMakingTypes.h"
#include "MatchMakingGameSvcMngrGetter.h"
#include "Game/PF/HybridServer/RGameServerDispenserIface.auto.h"
#include "Server/GameSession/GameBalancer/RGameBalancerIface.auto.h"
#include "RPC/IfaceRequester.h"
#include "Server/Statistic/GameStatClient.h"

namespace GameBalancer
{
  class IBalancer;
}

namespace MatchMaking
{
  class Session;

  REMOTE class Manager : public rpc::IfaceRequesterCallback<GameBalancer::RIBalancer>, 
                         public BaseObjectMT, 
                         public IManagerNotifier
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Manager, rpc::IfaceRequesterCallback<GameBalancer::RIBalancer>, BaseObjectMT );
    RPC_ID();

  public:

    Manager(StatisticService::GameStatClient * statIface);
    ~Manager();

    REMOTE ClientId RequestMatchMaking(MatchMaking::RIClient* pclient);
    REMOTE void CancelMatchMaking(ClientId const & cid);

    void Step();

    virtual void OnGameSessionStarted(Session const * s);

  private:
    StrongMT<ClientCtx> RegisterClient_(MatchMaking::RIClient* pclient);
    void UnregistedClient_(ClientId const & cid);
    ClientId GenerateClientId_();
    void FreeClientId_(ClientId const & cid);

    StrongMT<Session> CreateSession_(unsigned int numberOfPlayers);
    SessionId GenerateSessionId_();
    void FreeSessionId_(SessionId const & sid);

    //  IfaceRequesterCallback<GameBalancer::RIBalancer>
    void onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<GameBalancer::RIBalancer> > const & ifacereq);

  private:
    typedef nstl::map<ClientId, StrongMT<ClientCtx> > ClientCtxMapT;
    ClientCtxMapT clients_;

    typedef nstl::list<StrongMT<ClientCtx> > RequestQueueT;
    RequestQueueT requests_;

    typedef nstl::map<SessionId, StrongMT<Session> > SessionsT;
    SessionsT sessions_;

    IDGenerator clientIdGen_;
    IDGenerator sessionIdGen_;

    StrongMT<GameBalancer::RIBalancer> gameBalancer_;
    StrongMT<StatisticService::GameStatClient> statIface_;
  };

  inline
  ClientId Manager::GenerateClientId_()
  {
    if (!clientIdGen_.HasFreeID())
      return INVALID_CLIENT_ID;

    return clientIdGen_.Generate();
  }

  inline
  void Manager::FreeClientId_(ClientId const & cid)
  {
    clientIdGen_.Release(cid);
  }

  inline
  SessionId Manager::GenerateSessionId_()
  {
    if (!sessionIdGen_.HasFreeID())
      return INVALID_SESSION_ID;

    return sessionIdGen_.Generate();
  }

  inline
  void Manager::FreeSessionId_(SessionId const & sid)
  {
    sessionIdGen_.Release(sid);
  }
}

