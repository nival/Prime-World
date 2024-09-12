#pragma once

#include "GameTestClient_GS.h"
#include "Server/Roll/RRollBalancer.auto.h"
#include "Server/Roll/RRollInstance.auto.h"
#include "Server/Roll/RollClient.h"
#include "rpc/IfaceRequester.h"

#include <list>

namespace gtc
{

class Client_Roll : public TestClientBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( Client_Roll, TestClientBase );

public:
  Client_Roll( const TestClientBaseParams & _params );

private:
  struct RollClientCb;

  struct ERollTestStage
  {
    enum Enum { Init, WaitingBalancer, WaitingInstance, WaitingRoll, Finished };
  };

  ERollTestStage::Enum  stage;
  StrongMT<rpc::IfaceRequester<roll::RIBalancer>>  balancer;
  StrongMT<roll::RIInstance>  rollInstance;
  StrongMT<RollClientCb>  clientCb;

  virtual StepResult MainStep();

  bool StepRollTest();

  ERollTestStage::Enum RollStage() const { return stage; }
  void ChangeRollStage( ERollTestStage::Enum st ) {
    stage = st;
  }

  void OnInstanceAllocation( roll::RIInstance * inst );

  void OnRollResults( const vector<roll::SUserAward> & _award );
  void OnRollFailed();

  void GenerateRollData( roll::SPreGameData & preGame, roll::SPostGameData & postGame );
};

} //namespace gtc
