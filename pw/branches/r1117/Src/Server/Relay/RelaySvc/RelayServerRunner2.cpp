#include "stdafx.h"
#include "Network/stdafx.h"
#include "RelayServer2.h"
#include "Coordinator/Interface.h"
#include "RelayServer2Cfg.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FilePath.h"
#include "RelayServerRunner2.h"
#include "Network/ClusterConfiguration.h"
#include "RelaySvcNaming.h"

namespace Relay
{

RelayServerRunner2::RelayServerRunner2()
{
  svcrole = RelayServer2Cfg::GetSvcRole().c_str();
}



RelayServerRunner2::~RelayServerRunner2()
{
  instances.clear();
}



void RelayServerRunner2::StartInstance( const Transport::ServiceParams & _params )
{
  NI_ASSERT( instances.size() == 0, "" );

  systemLog( NLogg::LEVEL_MESSAGE ) << "RelayServer2 : StartInstance" << endl;

  Transport::TServiceId frontendIface;
  int serviceIdx = Transport::GetServerIndex( _params.serviceId );
  Transport::GenerateServiceName( Transport::ENetInterface::FrontEnd, serviceIdx, &frontendIface );

  Transport::TServiceId backendIface;
  Transport::GenerateServiceName( Transport::TServiceId("relay_backend"), serviceIdx, &backendIface );

  StrongMT<Transport::IAddressTranslator> backendTranslator = _params.coordClient->GetBackendAddressTranslator();
  Network::NetAddress backendAddr = _params.backendTransport->AllocateServerAddress( backendTranslator->GetServerIp() );
  backendTranslator->DefineRoute( backendIface, backendAddr );

  StrongMT<Transport::ITransportSystem> frontendTrpt = _params.frontendTransport ? _params.frontendTransport : _params.backendTransport;
  StrongMT<Transport::IAddressTranslator> frontendTranslator = _params.coordClient->GetFrontendAddressTranslator();
  Network::NetAddress frontendAddr = frontendTrpt->AllocateServerAddress( frontendTranslator->GetServerIp() );
  frontendTranslator->DefineRoute( _params.serviceId, frontendAddr );

  Transport::CustomServiceParams customParams( "" );
  StrongMT<RelayServer2> svc = new RelayServer2( _params, customParams, frontendIface, backendIface );

  instances[_params.serviceId] = new threading::JobThread( svc, backendIface.c_str() );
}



void RelayServerRunner2::StopInstance( const Transport::TServiceId & serviceId )
{
  systemLog( NLogg::LEVEL_MESSAGE ) << "RelayServer2 : StopInstance" << endl;

  TServerInstances::iterator it = instances.find( serviceId );

  NI_VERIFY( it != instances.end(), "Stopping nonexistent service", return );

  instances.erase( it );
}



void RelayServerRunner2::SoftStopInstance( Transport::TServiceId const & _svcid )
{
  MessageTrace( "Relay service soft stop not supported. svcid=%s", _svcid.c_str() );
}

} //namespace Relay
