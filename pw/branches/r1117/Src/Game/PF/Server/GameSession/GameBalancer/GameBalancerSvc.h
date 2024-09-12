#pragma once

#include "ServerAppBase/NivalService.h"
#include "GameBalancer/GameBalancerImpl.h"

namespace GameBalancer
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
  StrongMT<BalancerImpl> impl;
};

}
