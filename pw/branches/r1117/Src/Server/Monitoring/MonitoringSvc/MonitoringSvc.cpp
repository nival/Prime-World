#include "stdafx.h"
#include "MonitoringSvc/MonitoringSvc.h"
#include "MonitoringSvc/MonitoringImpl.h"
#include "MonitoringSvc/MonitorCore.h"
#include "MonitoringSvc/ThriftModule.h"
#include "Coordinator/LServiceAppearanceNotifierIface.auto.h"
#include "MonitoringSvc/MonitoringNaming.h"
#include "MonitoringSvc/MonitoringCfg.h"

namespace Monitoring
{


Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  moncore = new MonitorCore;
  moncore->Open( BackendGk() );

  RegisterBackendAttach<Coordinator::IServiceAppearanceSubscriber, Coordinator::LIServiceAppearanceSubscriber>();

  monitor = new MonitorImpl( BackendGk(), moncore );
  RegisterBackendObject<IMonitor>( monitor.Get(), ServiceRpcIface );

  ThriftModuleCfg cfg;
  cfg.port = Cfg::GetThriftIfacePort();
  cfg.mc = moncore;

  thriftModule = new ThriftModule;
  if (thriftModule->open(cfg) < 0)
  {
    LOG_E(MONLOG).Trace("Can't open thrift module: port=%d", cfg.port);
  }

  cfg.port = Cfg::GetConsoleThriftIfacePort();
  thriftModule4MonConsole = new ThriftModule;
  if (thriftModule4MonConsole->open(cfg) < 0)
  {
    LOG_E(MONLOG).Trace("Can't open thrift module for console: port=%d", cfg.port);
  }
}



Service::~Service()
{
  thriftModule4MonConsole->close();
  thriftModule->close();
  UnregisterBackendObject( monitor.Get() );
}



void Service::Poll( timer::Time _now )
{
  moncore->Step();
  monitor->Step();
}

}
