#pragma once

#include "GameTestClientBase.h"
#include "System/RandomGenerator.h"
#include <HybridServer/Peered.h>
#include <Server/AppFramework/Interfaces.h>
#include "Game/PF/Client/GameChatClient/GameChatClient.h"

namespace gtc
{

class GameClientWrapper;

class Client_GS : public TestClientBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( Client_GS, TestClientBase );

public:
  Client_GS( const TestClientBaseParams & _params );

  ~Client_GS();

  void SetupGameFinish( int _durationInSeconds );
  void SetupGameFinishClientStats( const Peered::ClientStartInfo & clientStartInfo );

private:
  StrongMT<GameClientWrapper> gameClientWrapper;

  //GS
  StrongMT<Peered::IGameServer> gamesrv_;
  int sessionClientIdx_;
  Peered::TSessionId serverId_;
  int initialStep_;
  int currentStep_;
  int sendStep_;  //  на каком последнем степе послали данные серверу
  int confirmFrequency;
  NRandom::RandomGenerator packetSizeRandom, dataRandom;
  int chatSendStep;

  NHPTimer::FTime startLoadMapTime_;

  //Game finish info
  int             gameDurationSteps;
  StatisticService::RPC::SessionClientResults gameFinishData;
  timer::Time     pvxTerminationTime;

  AppFramework::InstanceStatistics stats;
  AppFramework::InstanceStatistics queueTimeStats;

  StrongMT<Transport::IChannel> inputChannel;

  StrongMT<gamechat::IClient>          chatClient;

protected:
  virtual StepResult MainStep();
  virtual void TerminatePvx(); 

  StepResult PollGame();

  void PollMulticast();

  int checkSessionStarted();
  int startJoinGameSession();
  int checkJoinGameSession();

  int LoadMapSimulate();

  void StartGame( Peered::IGameServer * gsrv );
  int ClientReadyToPlay();
  int checkGameSessionStarted();
  void UpdateStepStatistics(int step);
  void UpdateQueueTimeStatistics(int step, const Transport::MessageMiscInfo& miscInfo);

  //Peered::IGameClient mirror, called throgh GameClientWrapper
  friend GameClientWrapper;
  virtual void Start(const Peered::ClientStartInfo& clientStartInfo);
  virtual void Step(int step, const nstl::vector<rpc::MemoryBlock>& commands,
    const nstl::vector<Peered::BriefClientInfo>& statuses, const nstl::vector<Peered::GapInfo>& clientGaps,
    const Transport::MessageMiscInfo & miscInfo);
  virtual void StepBatch(const nstl::vector<Peered::ClientStepData>& stepData);
  void Step2(const rpc::MemoryBlock& stepData);
  virtual void ApplySnapshot(int step, uint worldCrc, const nstl::vector<Peered::BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData);
  virtual void OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& async);
  virtual void OnStart(int step);
  virtual void OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& clientStatuses);
};

} //namespace gtc
