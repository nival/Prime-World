#include "stdafx.h"
#include "NivalServiceRunner.h"
#include "System/InlineProfiler.h"

namespace Transport
{

BaseServiceRunner::BaseServiceRunner()
{
}



void BaseServiceRunner::StartInstance( const Transport::ServiceParams & _params )
{
  MessageTrace( "Starting service '%s'", _params.serviceId.c_str() );

  serviceInstance = CreateServiceObject( _params );
  thread = new threading::JobThread( serviceInstance, _params.serviceId.c_str() );

  MessageTrace( "Service '%s' started", _params.serviceId.c_str() );
}



void BaseServiceRunner::StopInstance( const Transport::TServiceId& serviceId )
{
  serviceInstance = 0;
  thread = 0;
}



void BaseServiceRunner::SoftStopInstance( const TServiceId & serviceId )
{
  if ( serviceInstance )
    serviceInstance->StopSoftly();
}



void BaseServiceRunner::OnConfigReload()
{
  if ( serviceInstance )
    serviceInstance->ReloadConfig();
}

} //namespace Transport
