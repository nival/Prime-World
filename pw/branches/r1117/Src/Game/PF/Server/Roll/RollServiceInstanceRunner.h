#ifndef ROLLSERVICEINSTANCERUNNER_H_INCLUDED
#define ROLLSERVICEINSTANCERUNNER_H_INCLUDED

#include "ServerAppBase/NivalService.h"


namespace roll
{

class Instance;

class InstanceSvc : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( InstanceSvc, Transport::BaseService );

public:
  InstanceSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );

  virtual void Poll( timer::Time _now );
  virtual void OnConfigReload();

private:
  StrongMT<Instance>  instance;
};

} //namespace roll

#endif //ROLLSERVICEINSTANCERUNNER_H_INCLUDED
