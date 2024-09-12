#include "stdafx.h"
#include "GameTestClient_TestMM.h"
#include <HybridServer/LPeered.auto.h>

namespace gtc
{


Client_TestMm::Client_TestMm( const TestClientBaseParams & _params ) :
Client_GS( _params ),
mmcid_(MatchMaking::INVALID_CLIENT_ID)
{
}



Client_TestMm::~Client_TestMm()
{
  mmc_ = 0;
  mms_ = 0;
  mmm_ = 0;
}



StepResult Client_TestMm::MainStep()
{
  NI_PROFILE_FUNCTION;

  StepResult result = Client_GS::MainStep();
  if ( !result.Ok() || result.Handled() )
    return result;

  switch ( stage_ )
  {
    default:
      return StepResult( false, true );

    case Stage::LOGIN_FINISHED:
      return StepResult( true, startReqMatchMakingManager() != Result::FAIL );

    case Stage::REQ_MATCH_MAKING_MANAGER_STARTED:
      return StepResult( true, Result::FAIL != checkReqMatchMakingManager() );

    case Stage::REQ_MATCH_MAKING_MANAGER_FINISHED:
      return StepResult( true, Result::FAIL != startReqMatchMaking() );

    case Stage::REQ_MATCH_MAKING_STARTED:
      return StepResult( true, Result::FAIL != checkReqMatchMaking() );

    case Stage::REQ_MATCH_MAKING_FINISHED:
      return StepResult( true, Result::FAIL != checkMatchMakingCompleted() );

    case Stage::MATCH_MAKING_COMPLETED:
      return StepResult( true, Result::FAIL != PlayerReadyToPlay() );

    case Stage::PLAYER_READY_TO_PLAY:
      return StepResult( true, Result::FAIL != checkSessionStarted() );
  } //case ends
}



int Client_TestMm::checkSessionStarted()
{
  NI_PROFILE_FUNCTION;

  lastresult_ = Result::IN_PROGRESS;
  return lastresult_;
}



int Client_TestMm::checkJoinGameSession()
{
  NI_PROFILE_FUNCTION;
  return lastresult_;
}



int Client_TestMm::startReqMatchMakingManager()
{
  NI_PROFILE_FUNCTION;

  StrongMT<rpc::Node> rpcNode = gateKeeper_->RequestNode(MatchMakingSvc);
  while (rpcNode && !rpcNode->IsConnected())
  {
    gateKeeper_->Poll();
    ::Sleep(5);
  }
  if (rpcNode)
  {
    rpcNode->Query<MatchMaking::RManager>(MatchMakingManagerObjPath, this, &Client_TestMm::OnSetMatchMakingManagerObject);
    lastresult_ = Result::IN_PROGRESS;
  }
  else
  {
    lastresult_ = Result::FAIL;
  }
  stage_ = Stage::REQ_MATCH_MAKING_MANAGER_STARTED;

  return lastresult_;
}



int Client_TestMm::checkReqMatchMakingManager()
{
  NI_PROFILE_FUNCTION;
  return lastresult_;
}



void Client_TestMm::OnSetMatchMakingManagerObject(MatchMaking::RManager* mo)
{
  if (mo)
  {
    mmm_ = mo;
    lastresult_ = Result::SUCCESS;
  }
  else
    lastresult_ = Result::FAIL;

  stage_ = Stage::REQ_MATCH_MAKING_MANAGER_FINISHED;
}



int Client_TestMm::startReqMatchMaking()
{
  NI_PROFILE_FUNCTION;

  mmc_ = new MatchMaking::Client(static_cast<MatchMaking::IClientNotifier*>(this), transport_->GetUserId());
  factory_->RegisterAttach<MatchMaking::IClient, MatchMaking::LIClient>();

  mmm_->RequestMatchMaking(RemotePtr<MatchMaking::RIClient>(mmc_), this, &Client_TestMm::OnRegisterMatchMaking);

  stage_ = Stage::REQ_MATCH_MAKING_STARTED;
  lastresult_ = Result::IN_PROGRESS;
  return lastresult_;
}



int Client_TestMm::checkReqMatchMaking()
{
  NI_PROFILE_FUNCTION;
  return lastresult_;
}



void Client_TestMm::OnRegisterMatchMaking(MatchMaking::ClientId cid)
{
  systemLog(NLogg::LEVEL_MESSAGE) << "OnRegisterMatchMaking(user=" << userId_ << " mmcid=" << cid << " )" << endl;

  if (MatchMaking::INVALID_CLIENT_ID != cid)
  {
    mmcid_ = cid;
    lastresult_ = Result::SUCCESS;
  }
  else
    lastresult_ = Result::FAIL;

  stage_ = Stage::REQ_MATCH_MAKING_FINISHED;
}



int Client_TestMm::checkMatchMakingCompleted()
{
  NI_PROFILE_FUNCTION;

  if (lastresult_ != Result::IN_PROGRESS)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << "checkMatchMakingCompleted(user=" << userId_ << " mmcid=" << mmcid_ << " )" << endl;
    lastresult_ = Result::IN_PROGRESS;
  }

  return lastresult_;
}



int Client_TestMm::checkGameSessionStarted()
{
  NI_PROFILE_FUNCTION;
  return lastresult_;
}



int Client_TestMm::PlayerReadyToPlay()
{
  NI_PROFILE_FUNCTION;

  mms_->PlayerReady(mmcid_);
  stage_ = Stage::PLAYER_READY_TO_PLAY;
  lastresult_ = Result::SUCCESS;
  return lastresult_;
}



void Client_TestMm::MatchMakingCompleted(int res, MatchMaking::SessionId sid, MatchMaking::ISession* session)
{
  systemLog(NLogg::LEVEL_MESSAGE) << "MatchMakingCompleted(user=" << userId_ << " res=" << res << 
    " session=" << sid << " )" << endl;
  if (0 == res && 0 != session)
  {
    mms_ = session;
    lastresult_ = Result::SUCCESS;
  }
  else
  {
    lastresult_ = Result::FAIL;
  }

  stage_ = Stage::MATCH_MAKING_COMPLETED;
}



void Client_TestMm::OnSessionStarted( Peered::IGameServer * gsrv )
{
  StartGame( gsrv );
  mms_ = 0;
}

} //namespace gtc

NI_DEFINE_REFCOUNT( gtc::Client_TestMm );
