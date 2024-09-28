#pragma once

#include "ServerAppBase/NivalService.h"


namespace Monitoring
{

class MonitorCore;
class MonitorImpl;
class ThriftModule;

class Service : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( Service, Transport::BaseService );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~Service();

  virtual void Poll( timer::Time _now );

private:
  StrongMT<MonitorCore> moncore;
  StrongMT<MonitorImpl> monitor;
  StrongMT<ThriftModule>  thriftModule;
  StrongMT<ThriftModule>  thriftModule4MonConsole;
};

}
