#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/UserManagerSvc.h"
#include "UserManagerSvc/LUserManagerIface.auto.h"
#include "UserManagerSvc/LUserNotificationIface.auto.h"
#include "UserManagerSvc/UserManagerCfg.h"
#include "UserManagerSvc/UserManagerNaming.h"
#include "Coordinator/Interface.h"
#include "RelayBalancer/RelayBalancerNaming.h"
#include "RelayBalancer/LRelayBalancerIface.auto.h"

namespace UserManager
{

namespace Instrumentation
{
  extern NDebug::DebugVar<int> activeUsers;
}

Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  relayBalancerIface_ = new rpc::IfaceRequester<Relay::RIBalancer>;
  relayBalancerIface_->init( BackendGk(), Relay::Balancer::ServiceClass, Relay::Balancer::ServiceRpcIface, &GetSystemLog(), UMLOG );

  RegisterBackendAttach<Relay::IBalancerCallback, Relay::LIBalancerCallback>();

  impl = new UserManagerImpl( relayBalancerIface_, this );
  RegisterBackendObject<IUserManager>( impl, UserManager::ServiceRpcIface );
  RegisterBackendAttach<IUserManager, LIUserManager>();

  RegisterBackendObject<IUserNotificationPublisher>( impl, UserManager::UserPublisherRpcIface );
  RegisterBackendAttach<IUserNotificationPublisher, LIUserNotificationPublisher>();

  //  register monitoring
  RegisterPerfCounter( "CCU", (NDebug::IDebugVar*)(&Instrumentation::activeUsers) );
}



Service::~Service()
{
  UnregisterPerfCounter("CCU");

  if ( impl )
  {
    UnregisterBackendObject<IUserNotificationPublisher>( impl );
    UnregisterBackendObject<IUserManager>( impl );
  }
  impl = 0;

  relayBalancerIface_ = 0;
}



void Service::Poll( timer::Time _now )
{
  relayBalancerIface_->step();
  impl->Step();
}

} //namespace UserManager
