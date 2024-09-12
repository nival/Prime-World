#pragma once

#include <System/Basic.h>
#include <Server/RPC/GateKeeper.h>
#include <Server/rpc/LocalEntityFactory.h>
#include <Network/ClientTransportSystemIntf.h>
#include <Game/PF/Tests/GTCBase/Result.h>
#include <MatchMaking/MatchMakingClient.h>
#include <MatchMaking/RMatchMakingManager.auto.h>

namespace Peered
{
  struct IGameServer;
}

namespace GameTestClient2
{
  class ITMMakingClientWrapperCb : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( ITMMakingClientWrapperCb, IBaseInterfaceMT );
  public:
    virtual void OnMatchMakingManagerReceived(Result::Enum rc) = 0;
    virtual void OnRegisterMatchMaking(Result::Enum rc) = 0;
    virtual void OnMatchMakingCompleted(Result::Enum rc, MatchMaking::SessionId sid) = 0;
    virtual void OnSessionStarted(Peered::IGameServer* gsrv) = 0;
  };

  class TMMakingClientWrapper : public MatchMaking::IClientNotifier, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( TMMakingClientWrapper, BaseObjectMT );

  public:
    TMMakingClientWrapper(StrongMT<rpc::GateKeeperClient> gateKeeper, 
      StrongMT<ITMMakingClientWrapperCb> const & cb);
    ~TMMakingClientWrapper();

  public:
    int startReqMatchMakingManager();
    int startReqMatchMaking();
    int PlayerReadyToPlay();
    int startJoinGameSession();
    int LoadMapSimulate();
    int ClientReadyToPlay();

    //  IClientNotifier
    virtual void MatchMakingCompleted(int res, MatchMaking::SessionId sid, MatchMaking::ISession* session);
    virtual void OnSessionStarted(Peered::IGameServer* gsrv);

    void OnSetMatchMakingManagerObject(MatchMaking::RManager* mo);
    void OnRegisterMatchMaking(MatchMaking::ClientId cid);

  private:
    StrongMT<rpc::GateKeeperClient> gateKeeper_;
    rpc::LocalEntityFactory* factory_;
    StrongMT<MatchMaking::RManager> mmm_;
    StrongMT<MatchMaking::ISession> mms_;
    StrongMT<MatchMaking::Client>  mmc_;
    MatchMaking::ClientId mmcid_;
    StrongMT<ITMMakingClientWrapperCb> cb_;
  };
}
