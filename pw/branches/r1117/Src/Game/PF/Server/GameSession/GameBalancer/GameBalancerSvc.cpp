#include "stdafx.h"
#include "GameBalancer/GameBalancerTypes.h"
#include "GameBalancer/GameBalancerSvc.h"
#include "GameBalancer/LGameBalancerIface.auto.h"
#include "GameBalancer/GameBalancerCfg.h"
#include "HybridServer/LGameServerAllocatorIface.auto.h"
#include "Coordinator/LServiceAppearanceNotifierIface.auto.h"


namespace GameBalancer
{

Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  RegisterBackendAttach<Coordinator::IServiceAppearanceSubscriber, Coordinator::LIServiceAppearanceSubscriber>();

  impl = new BalancerImpl( Cfg::GetGameSoftLimit(), Cfg::GetGameHardLimit(), BackendGk(), CoordClient()->GetBackendAddressTranslator() );
  RegisterBackendObject<IBalancer>( impl, ServiceRpcIface );

  RegisterBackendAttach<GameBalancer::IBalancer, GameBalancer::LIBalancer>();
  RegisterBackendAttach<HybridServer::IGameServerAllocatorNotify, HybridServer::LIGameServerAllocatorNotify>();
}



Service::~Service()
{
  UnregisterBackendObject<IBalancer>( impl );
}



void Service::Poll( timer::Time _now )
{
  impl->Step();
}

}
