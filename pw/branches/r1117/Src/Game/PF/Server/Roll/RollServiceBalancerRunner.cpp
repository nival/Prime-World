#include "stdafx.h"
#include "RollServiceBalancerRunner.h"
#include "RollServiceBalancer.h"
#include "RPC/GateKeeper.h"
#include "RPC/LocalEntityFactory.h"
#include "RollTypes.h"
#include "LRollBalancer.auto.h"
#include "LRollInstance.auto.h"

namespace roll
{

BalancerSvc::BalancerSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  RegisterBackendAttach<IBalancer, LIBalancer>();

  balancer = new Balancer;
  RegisterBackendObject<IBalancer>( balancer, serviceIds::BalancerInterface, "cMj4tyeV3JCHOnN" );
}



void BalancerSvc::Poll( timer::Time _now )
{
  balancer->Poll();
}



void BalancerSvc::OnConfigReload()
{
  balancer->ReloadConfig();
}

} //namespace roll
