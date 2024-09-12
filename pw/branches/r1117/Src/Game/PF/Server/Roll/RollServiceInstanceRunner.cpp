#include "stdafx.h"
#include "RollServiceInstanceRunner.h"
#include "RollServiceInstance.h"
#include "RPC/GateKeeper.h"
#include "RPC/LocalEntityFactory.h"
#include "LRollInstance.auto.h"
#include "System/TextFileDumper.h"
#include "RollLog.h"

namespace roll
{

InstanceSvc::InstanceSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  RegisterBackendAttach<IInstance, LIInstance>();

  instance = new Instance( BackendGk(), SvcId(), this );
}



void InstanceSvc::Poll( timer::Time _now )
{
  instance->Poll();
}



void InstanceSvc::OnConfigReload()
{
  instance->OnConfigReload();
}

} //namespace roll
