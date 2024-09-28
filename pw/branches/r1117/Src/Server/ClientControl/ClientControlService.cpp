#include "stdafx.h"
#include "ClientControlService.h"
#include "ClientControlLogic.h"
#include "ClientControlTypes.h"
#include "LClientControlInterface.auto.h"
#include "Network/LSessionKeyRegisterIface.auto.h"
#include "System/InlineProfiler.h"
#include "ClientControlLog.h"


namespace clientCtl
{

static NDebug::DebugVar<int> s_CcuCounter( "ActiveUsers", "UserManager" );


InstanceSvc::InstanceSvc( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams ),
prevReportedCcu( 0 )
{
  RegisterBackendAttach<IInterface, LIInterface>();
  RegisterBackendAttach<Login::ISessionKeyRegister, Login::LISessionKeyRegister>();
  RegisterBackendAttach<Login::IAddSessionKeyCallback, Login::LIAddSessionKeyCallback>();
  config = CreateConfigFromStatics();

  logic = new Logic( config, Now() );

  RegisterFrontendObject<IInterface>( logic, serviceIds::Gate );

  RegisterPerfCounter( "CCU", &s_CcuCounter );
}



InstanceSvc::~InstanceSvc()
{
  UnregisterPerfCounter( "CCU" );
}



void InstanceSvc::Poll( timer::Time _now )
{
  unsigned ccu = 0;
  logic->Poll( _now, ccu );

  if ( ccu != prevReportedCcu )
  {
    prevReportedCcu = ccu;
    s_CcuCounter.SetValue( (int)ccu );
  }
}



void InstanceSvc::OnConfigReload()
{
  config->ReloadConfig();
}

} //namespace clientCtl
