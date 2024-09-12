#include "stdafx.h"

#include "MulticastTestSvc.h"
#include "MulticastTestRunner.h"
#include <Network/ClusterConfiguration.h>
#include "MulticastTestNaming.h"

namespace MulticastTest
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServiceRunner::ServiceRunner()
{
  interfaces.push_back( MulticastTest::ServiceClass );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServiceRunner::StartInstance( const Transport::TServiceId & serviceId, Transport::ITransportSystem * transport, 
                                  Network::INetworkDriver* _netdrv, Coordinator::ICoordinatorClient * coordClient )
{
  coordClient->MakeFullServiceName(serviceId);

  systemLog( NLogg::LEVEL_MESSAGE ) << "MulticastTest: start service" << endl;
  svc_ = new MulticastTest::Service(transport, serviceId);
  svc_->Start( "MulticastTest" );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServiceRunner::StopInstance( const Transport::TServiceId & serviceId )
{
  systemLog( NLogg::LEVEL_MESSAGE ) << "ClusterAdmin: stop service" << endl;
  svc_ = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServiceRunner::SetOptions( const set<string>& options )
{
}

}
