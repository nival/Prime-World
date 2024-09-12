#include "stdafx.h"
#include "LiveMMakingSvcRunner.h"
#include "LiveMMakingSvc.h"
#include "LILiveMMaking.auto.h"
#include "LiveMMakingConfigVars.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "rpc/IfaceRequester.h"
#include "RPC/GateKeeper.h"
#include "Server/RPC/LocalEntityFactory.h"
#include "Monitoring/PerfCounterProvider/PerfCounterProvider.h"
#include "System/InlineProfiler.h"


namespace socialLobby
{
  class RISocialInterface;
}



namespace mmaking
{

Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams ),
gameModes( EServiceGameModes::Any )
{
  Transport::TServerCmdLine::const_iterator it = ServerCmdLine().find( "mm_modes" );
  if ( it != ServerCmdLine().end() )
    if ( it->second == "any" )
      gameModes = EServiceGameModes::Any;
    else if ( it->second == "prod" )
      gameModes = EServiceGameModes::ProductionOnly;
    else if ( it->second == "dev" )
      gameModes = EServiceGameModes::DevelopmentOnly;
    else
      WarningTrace( "Wrong 'mm_modes' command line option format (%s)", it->second );

  RegisterBackendAttach<ILiveMMaking, LILiveMMaking>();

  remoteSocLobby = new rpc::IfaceRequester<socialLobby::RISocialInterface>;
  remoteSocLobby->init( BackendGk(), socialLobby::serviceIds::Service, socialLobby::serviceIds::SocialInterface );
}



Service::~Service()
{
}



void Service::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  if ( svc )
  {
    svc->Poll();

    threading::MutexLock lock( configReloadMutex );
    if ( reloadedConfigFlag )
      svc->OnConfigReload( );
    reloadedConfigFlag = false;
  }

  remoteSocLobby->step();
  rpc::IfaceRequesterState::Enum newState = remoteSocLobby->PopNewState();
  if ( newState == rpc::IfaceRequesterState::OPENED )
  {
    MessageTrace( "Got connection to social lobby, starting MM service as '%s'...", SvcId().c_str() );

    svc = new LiveMMaking( SvcId() );

    remoteSocLobby->iface()->RegisterMmLogic( SvcId(), svc, gameModes );
  }
}



void Service::OnConfigReload()
{
  threading::MutexLock lock( configReloadMutex );
  reloadedConfigFlag = true;
}

} //namespace mmaking
