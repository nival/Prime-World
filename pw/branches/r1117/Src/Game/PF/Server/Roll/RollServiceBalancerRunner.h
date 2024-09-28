#ifndef ROLLSERVICEBALANCERRUNNER_H_INCLUDED
#define ROLLSERVICEBALANCERRUNNER_H_INCLUDED

#include "ServerAppBase/NivalService.h"

namespace roll
{

class Balancer;

class BalancerSvc : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( BalancerSvc, Transport::BaseService );

public:
  BalancerSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );

  virtual void Poll( timer::Time _now );
  virtual void OnConfigReload();

private:
  StrongMT<Balancer>                balancer;
};

} //namespace roll

#endif //ROLLSERVICEBALANCERRUNNER_H_INCLUDED
