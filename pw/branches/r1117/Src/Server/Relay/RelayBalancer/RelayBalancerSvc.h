#pragma once

#include "ServerAppBase/NivalService.h"
#include "RelayBalancer/RelayBalancerImpl.h"
#include "RelayBalancer/RelayBalancerSettings.h"

namespace Relay
{

namespace Balancer
{

class Service : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( Service, Transport::BaseService );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~Service();

public:
  virtual void OnConfigReload();

protected:
  virtual void Poll( timer::Time _now );

private:
  StrongMT<BalancerImpl> impl;
  Settings settings_;
  volatile bool reloadCfgFlag_;
};

} //namespace Balancer

} //namespace Relay
