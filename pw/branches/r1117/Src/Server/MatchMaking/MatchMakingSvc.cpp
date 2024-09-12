#include "stdafx.h"

#include "MatchMakingManager.h"
#include "HybridServer/HybridServerDispencer.h"
#include "HybridServer/RGameServerDispenserIface.auto.h"
#include "MatchMaking/LMatchMakingSessionIface.auto.h"
#include "Server/GameSession/GameBalancer/LGameBalancerIface.auto.h"
#include "Server/LobbyPvx/LISessionHybridLink.auto.h"
#include "MatchMakingSvc.h"
#include "HybridServer/HybridServerNaming.h"
#include "Server/GameSession/GameBalancer/GameBalancerTypes.h"
#include "Matchmaking/MatchMakingNaming.h"
#include "Matchmaking/MatchMakingSvcCfg.h"
#include "Server/Statistic/StatClientHttpDispatcher.h"

namespace MatchMaking
{

Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  RegisterFrontendAttach<MatchMaking::ISession, MatchMaking::LISession>();
  RegisterBackendAttach<GameBalancer::IBalancerCallback, GameBalancer::LIBalancerCallback>();
  RegisterBackendAttach<lobby::ISessionHybridLink, lobby::LISessionHybridLink>();

  if (Cfg::StatisticModeOn())
  {
    StrongMT<StatisticService::ClientHttpDispatcher> statClDispatcher = new StatisticService::ClientHttpDispatcher;
    statIface_ = new StatisticService::GameStatClient( statClDispatcher, 0 );
  }

  manager = new MatchMaking::Manager(statIface_);
  RegisterFrontendObject<MatchMaking::Manager>(manager, MatchMaking::ManagerIfaceId);

  balancerRequester = new rpc::IfaceRequester<GameBalancer::RIBalancer>;
  int rc = balancerRequester->init( BackendGk(), GameBalancer::ServiceClass, GameBalancer::ServiceRpcIface, 
                                   &GetSystemLog(), MatchMaking::TMMLOG, manager.Get());
  if (rc < 0)
  {
    LOG_C(TMMLOG).Trace("Can't init balancer rpc requester");
  }
}



Service::~Service()
{
  balancerRequester = 0;
  statIface_ = 0;
  manager = 0;
}



void Service::Poll( timer::Time _now )
{
  balancerRequester->step();

  if( manager )
    manager->Step();
}

} // namespace MatchMaking
