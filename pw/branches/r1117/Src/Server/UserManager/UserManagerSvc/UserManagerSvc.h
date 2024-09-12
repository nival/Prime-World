#pragma once

#include "ServerAppBase/NivalService.h"
#include "UserManagerSvc/UserManagerImpl.h"
#include "RPC/IfaceRequester.h"
#include "RelayBalancer/RRelayBalancerIface.auto.h"

namespace UserManager
{

class Service : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( Service, Transport::BaseService );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~Service();

protected:
  virtual void Poll( timer::Time _now );

private:
  StrongMT<UserManagerImpl> impl;
  StrongMT<rpc::IfaceRequester<Relay::RIBalancer> > relayBalancerIface_;
};

FORCE_INIT_FACTORY( UserEnvInfo );
FORCE_INIT_FACTORY( UserInfo );
FORCE_INIT_FACTORY( UserSessionInfo );
FORCE_INIT_FACTORY( RelayInfo );
FORCE_INIT_FACTORY( PartialReconnectInfo );

} //namespace UserManager
