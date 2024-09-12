#include "stdafx.h"
#include "ClusterAdminSvc.h"
#include "Coordinator/RCoordinatorServerIface.auto.h"
#include "Coordinator/LServiceAppearanceNotifierIface.auto.h"
#include "ClusterAdminNaming.h"
#include "ClusterAdminImpl.h"
#include "ThriftModule.h"

static int s_adminThriftIfacePort = 8704;
static int s_adminConsoleThriftIfacePort = 8708;

REGISTER_VAR("admin_thrift_iface_port", s_adminThriftIfacePort, STORAGE_GLOBAL);
REGISTER_VAR("admin_console_thrift_iface_port", s_adminConsoleThriftIfacePort, STORAGE_GLOBAL);

namespace ClusterAdmin
{


Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  RegisterBackendAttach<Coordinator::IServiceAppearanceSubscriber, Coordinator::LIServiceAppearanceSubscriber>();

  impl = new ClusterAdminImpl( BackendGk(), CoordClient() );

  RegisterBackendObject<IClusterAdmin>( impl, ClusterAdmin::ServiceIfaceId );

  {
    ThriftModuleCfg cfg;
    cfg.port = s_adminThriftIfacePort;
    cfg.impl = impl;

    thriftModule = new ThriftModule;
    if (thriftModule->open(cfg) < 0)
    {
      LOG_E(CALOG).Trace("Can't open thrift module: port=%d", cfg.port);
    }
  }

  {
    ThriftModuleCfg cfg;
    cfg.port = s_adminConsoleThriftIfacePort;
    cfg.impl = impl;

    thriftModule4Console = new ThriftModule;
    if (thriftModule4Console->open(cfg) < 0)
    {
      LOG_E(CALOG).Trace("Can't open console thrift module: port=%d", cfg.port);
    }
  }
}



Service::~Service()
{
  if (thriftModule4Console)
    thriftModule4Console->close();

  if (thriftModule)
    thriftModule->close();

  if ( impl )
    UnregisterBackendObject( impl.Get() );
}



void Service::Poll( timer::Time _now )
{
  impl->Step();
}

}
