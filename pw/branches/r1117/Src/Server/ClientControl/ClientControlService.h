#ifndef CLIENTCONTROLSERVICE_H_INCLUDED
#define CLIENTCONTROLSERVICE_H_INCLUDED

#include "ServerAppBase/NivalService.h"
#include "ClientControlConfig.h"


namespace clientCtl
{

class Logic;

class InstanceSvc : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( InstanceSvc, Transport::BaseService );

public:
  InstanceSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~InstanceSvc();

  virtual void Poll( timer::Time _now );
  virtual void OnConfigReload();

private:
  StrongMT<IConfigProvider>   config;
  StrongMT<Logic>             logic;
  unsigned                    prevReportedCcu;
};

} //namespace clientCtl

#endif //CLIENTCONTROLSERVICE_H_INCLUDED
