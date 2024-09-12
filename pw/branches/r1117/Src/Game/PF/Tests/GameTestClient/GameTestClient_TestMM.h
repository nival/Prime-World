#pragma once

#include "GameTestClient_GS.h"

#include <MatchMaking/MatchMakingClient.h>
#include <MatchMaking/MatchMakingManager.h>
#include <MatchMaking/MatchMakingSession.h>
#include <MatchMaking/LMatchMakingClient.auto.h>
#include <MatchMaking/RMatchMakingManager.auto.h>
#include <MatchMaking/MatchMakingSessionIface.h>

namespace gtc
{

class GameClientWrapper;

class Client_TestMm : public Client_GS, public MatchMaking::IClientNotifier
{
  NI_DECLARE_REFCOUNT_CLASS_1( Client_TestMm, Client_GS );

public:
  Client_TestMm( const TestClientBaseParams & _params );

  ~Client_TestMm();

private:
  //test mm
  StrongMT<MatchMaking::RManager> mmm_;
  StrongMT<MatchMaking::ISession> mms_;
  StrongMT<MatchMaking::Client>  mmc_;
  MatchMaking::ClientId mmcid_;

  virtual StepResult MainStep();
  
  int checkSessionStarted();
  int checkJoinGameSession();

  //  matchmaking
  int startReqMatchMakingManager();
  int checkReqMatchMakingManager();
  int startReqMatchMaking();
  int checkReqMatchMaking();
  int checkMatchMakingCompleted();
  int PlayerReadyToPlay();
  int checkGameSessionStarted();
  void OnSetMatchMakingManagerObject(MatchMaking::RManager* mo);
  void OnRegisterMatchMaking(MatchMaking::ClientId cid);

  // MatchMaking::IClientNotifier
  virtual void MatchMakingCompleted(int res, MatchMaking::SessionId sid, MatchMaking::ISession* session);
  virtual void OnSessionStarted(Peered::IGameServer* gsrv);
};

} //namespace gtc
