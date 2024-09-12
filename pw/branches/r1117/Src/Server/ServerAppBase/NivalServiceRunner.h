#ifndef NIVALSERVICERUNNER_H_INCLUDED
#define NIVALSERVICERUNNER_H_INCLUDED

#include "ServerRunner.h"
#include "System/JobThread.h"
#include "NivalService.h"

namespace Transport
{

class BaseService;

class BaseServiceRunner : public Transport::IServerRunner, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( BaseServiceRunner, BaseObjectMT );

public:
  BaseServiceRunner();

  ~BaseServiceRunner() { thread = 0; }

  virtual void StartInstance( const ServiceParams & _params );
  virtual void StopInstance( const Transport::TServiceId& serviceId );
  virtual void SoftStopInstance( const TServiceId & serviceId );
  virtual void OnConfigReload();

protected:
  virtual BaseService * CreateServiceObject( const ServiceParams & _svcParams ) = 0;

private:
  StrongMT<threading::JobThread>    thread;
  StrongMT<BaseService>             serviceInstance;
};



template <class TServiceInstance>
class ServiceRunner : public BaseServiceRunner
{
  NI_DECLARE_REFCOUNT_CLASS_1( ServiceRunner, BaseServiceRunner );

public:
  ServiceRunner( const CustomServiceParams & _customParams ) :
  haveCustomParams( true ),
  customParams( _customParams )
  {}

  ServiceRunner() :
  haveCustomParams( false ),
  customParams( "" )
  {}

protected:
  virtual BaseService * CreateServiceObject( const ServiceParams & _svcParams )
  {
    if ( haveCustomParams )
      return new TServiceInstance( _svcParams, customParams );
    else
      return new TServiceInstance( _svcParams, CustomServiceParams() );
  }

private:
  const bool haveCustomParams;
  const CustomServiceParams customParams;
};

} //namespace Transport

#endif //NIVALSERVICERUNNER_H_INCLUDED
