#include "stdafx.h"
#include "CoordinatorClient.h"
#include "CoordinatorClientRunner.h"
#include "CoordinatorClientNaming.h"
#include "System/sleep.h"

namespace Coordinator
{

CoordinatorClientRunner::CoordinatorClientRunner( const Transport::TServiceId & _svcpath, Network::INetworkDriver * _netDriver )
{
  client = new CoordinatorClient( _svcpath, _netDriver );
}



void CoordinatorClientRunner::Open( Transport::ITransportSystem * _backendTransport, Transport::ITransportSystem * _frontendTransport, const Network::NetAddress & _coordinatorAddress, const nstl::string & _source )
{
  client->GetInterface()->AddExplicitRoute( Transport::ENetInterface::Coordinator, Coordinator::SvcNetAddresses( _coordinatorAddress, Network::NetAddress() ) );

  Transport::TServiceId sourceFixed( ( coordClientNamePrefix + _source ).c_str() ); // представляемся служебным псевдонимом "_с[oordinator]c[lient]_services..."

  gk = new rpc::GateKeeper( _backendTransport, sourceFixed, Transport::autoAssignClientId, 0 );
  client->Open( _backendTransport, _frontendTransport, gk );
}



void CoordinatorClientRunner::Work( volatile bool & _isRunning )
{
  NI_PROFILE_THREAD;

  while ( _isRunning )
  {
    gk->Poll();
    client->step();
    nival::sleep( 10 );
  }
}

} //namespace Coordinator
