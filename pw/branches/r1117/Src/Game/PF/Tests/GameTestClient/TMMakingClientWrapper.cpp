#include "stdafx.h"
#include "System/InlineProfiler.h"
#include "TMMakingClientWrapper.h"
#include <MatchMaking/LMatchMakingClient.auto.h>

Transport::TServiceId const MatchMakingSvc = "matchmaking";
static char const * MatchMakingManagerObjPath = "matchmaking.manager";

namespace GameTestClient2
{
  TMMakingClientWrapper::TMMakingClientWrapper(StrongMT<rpc::GateKeeperClient> gateKeeper, 
    StrongMT<ITMMakingClientWrapperCb> const & cb)
    :cb_(cb),
    factory_(0),
    mmcid_(MatchMaking::INVALID_CLIENT_ID),
    gateKeeper_(gateKeeper)
  {
    NI_ASSERT(cb_ != 0, "Callback must be initialized");
  }

  TMMakingClientWrapper::~TMMakingClientWrapper()
  {
  }

  int TMMakingClientWrapper::startReqMatchMakingManager()
  {
    NI_PROFILE_FUNCTION;

    Result::Enum rc = Result::FAIL;

    StrongMT<rpc::Node> rpcNode = gateKeeper_->RequestNode(MatchMakingSvc);
    while (rpcNode && !rpcNode->IsConnected())
    {
      gateKeeper_->Poll();
      ::Sleep(5);
    }
    if (rpcNode)
    {
      rpcNode->Query<MatchMaking::RManager>(MatchMakingManagerObjPath, this, &TMMakingClientWrapper::OnSetMatchMakingManagerObject);
      rc = Result::IN_PROGRESS;
    }

    return rc;
  }

  void TMMakingClientWrapper::OnSetMatchMakingManagerObject(MatchMaking::RManager* mo)
  {
    if (mo)
      mmm_ = mo;

    cb_->OnMatchMakingManagerReceived((mo != 0 ? Result::SUCCESS : Result::FAIL));
  }

  int TMMakingClientWrapper::startReqMatchMaking()
  {
    NI_PROFILE_FUNCTION;

    mmc_ = new MatchMaking::Client(static_cast<MatchMaking::IClientNotifier*>(this), gateKeeper_->GetClientId());
    if (!factory_)
      factory_ = new rpc::LocalEntityFactory( gateKeeper_->GetGate() );

    factory_->RegisterAttach<MatchMaking::IClient, MatchMaking::LIClient>();
    mmm_->RequestMatchMaking(RemotePtr<MatchMaking::RIClient>(mmc_), this, &TMMakingClientWrapper::OnRegisterMatchMaking);
    return Result::IN_PROGRESS;
  }

  void TMMakingClientWrapper::OnRegisterMatchMaking(MatchMaking::ClientId cid)
  {
    LOG_M(0) << "OnRegisterMatchMaking(user=" << gateKeeper_->GetClientId() << " mmcid=" << cid << " )" << endl;

    NI_ASSERT(mmcid_ == MatchMaking::INVALID_CLIENT_ID, "");
    mmcid_ = cid;
    cb_->OnRegisterMatchMaking(cid != MatchMaking::INVALID_CLIENT_ID ? Result::SUCCESS : Result::FAIL);
  }

  void TMMakingClientWrapper::MatchMakingCompleted(int res, MatchMaking::SessionId sid, MatchMaking::ISession* session)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << "MatchMakingCompleted(user=" << gateKeeper_->GetClientId() << " res=" << res << 
      " session=" << sid << " )" << endl;
    if (0 == res && 0 != session)
    {
      mms_ = session;
    }

    cb_->OnMatchMakingCompleted(mms_ != 0 ? Result::SUCCESS : Result::FAIL, sid);
  }

  int TMMakingClientWrapper::PlayerReadyToPlay()
  {
    NI_PROFILE_FUNCTION;

    mms_->PlayerReady(mmcid_);
    return Result::SUCCESS;
  }

  void TMMakingClientWrapper::OnSessionStarted(Peered::IGameServer* gsrv)
  {
    cb_->OnSessionStarted(gsrv);
  }
}
