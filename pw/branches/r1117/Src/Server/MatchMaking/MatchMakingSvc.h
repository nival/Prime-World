#pragma once

#include "ServerAppBase/NivalService.h"
#include "MatchMakingManager.h"
#include <Server/GameSession/GameBalancer/RGameBalancerIface.auto.h>

namespace HybridServer
{
  class RIGameServerDispenser;
}

namespace MatchMaking
{

class Service : public Transport::BaseService
{
public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~Service();

  virtual void Poll( timer::Time _now );

private:
  StrongMT<MatchMaking::Manager>  manager;
  StrongMT<rpc::IfaceRequester<GameBalancer::RIBalancer> > balancerRequester;
  StrongMT<StatisticService::GameStatClient> statIface_;
};

}
