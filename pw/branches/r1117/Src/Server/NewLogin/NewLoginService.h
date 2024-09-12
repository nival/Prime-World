#ifndef NEWLOGINSERVICE_H_INCLUDED
#define NEWLOGINSERVICE_H_INCLUDED

#include "ServerAppBase/NivalService.h"
#include "NewLoginConfig.h"
#include "System/NiTimer.h"


namespace newLogin
{

class Logic;
class ClientAuth;
class ClientCtrlAccessor;
class SvcLinkDict;

class InstanceSvc : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( InstanceSvc, Transport::BaseService );

public:
  InstanceSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~InstanceSvc();

  virtual void Poll( timer::Time _now );
  virtual void OnSoftStop();
  virtual void OnConfigReload();

private:
  bool                          active;
  bool                          softStopped;
  StrongMT<IConfigProvider>     config;
  StrongMT<Logic>               logic;
  StrongMT<ClientAuth>          auth;
  StrongMT<ClientCtrlAccessor>  clientControl;
  StrongMT<SvcLinkDict>         svcLinkDict;
  timer::Timer                  loadNotifyTimer;
};

} //namespace newLogin

#endif //NEWLOGINSERVICE_H_INCLUDED
