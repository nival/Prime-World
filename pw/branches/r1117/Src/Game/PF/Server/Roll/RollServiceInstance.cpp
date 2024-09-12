#include "stdafx.h"
#include "RollServiceInstance.h"
#include "RollClient.h"
#include "RRollBalancer.auto.h"
#include "RollConfig.h"
#include "RollJob.h"
#include "RollSeClient.h"
#include "Db/DBServer.auto.h"
#include "PF_GameLogic/PFResourcesCollection.h"
#include "RollLog.h"


NI_DEFINE_REFCOUNT( roll::IInstance );

namespace roll
{

Instance::Instance( rpc::GateKeeper * gk, const Transport::TServiceId & _serviceId, InstanceSvc* _instanceSvc ) :
serviceId( _serviceId ),
gateKeeper( gk ),
lastLoadSent( 0 ),
lastConnectedTime( timer::Now() ),
instanceSvc(_instanceSvc)
{
  config = CreateConfigFromStatics();

  logic = new DropNRoll( config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, new NWorld::PFResourcesCollection() );

  balancer = new rpc::IfaceRequester<RIBalancer>("cMj4tyeV3JCHOnN");
  balancer->init( gateKeeper, serviceIds::BalancerService, roll::serviceIds::BalancerInterface);

  seClient = new SeClientWorker( config );
  seClientThread = new threading::JobThread( seClient, "SeClient" );
}



void Instance::Poll()
{
  balancer->step();

  if ( balancer->PopNewState() == rpc::IfaceRequesterState::OPENED )
    ROLL_LOG_MSG( "Connected to roll balancer" );

  timer::Time t = timer::Now();

  logic->Poll( t );

  StrongMT<RollConfig> cfg = config->Cfg();

  if ( !balancer->isopen() )
  {
    if ( t > lastConnectedTime + cfg->instanceConnectionTimeout )
    {
      ROLL_LOG_ERR( "Roll instance cannot connect to balancer! timeout=%.1f", cfg->instanceConnectionTimeout );
      lastConnectedTime = t;
    }
    return;
  }

  lastConnectedTime = t;

  if ( t > lastLoadSent + cfg->loadNotifyPeriod ) {
    lastLoadSent = t;

    balancer->iface()->LoadNotify( RemotePtr<roll::RIInstance>( this ), serviceId.c_str(), (int)jobs.size() );
  }

  for ( Jobs::iterator it = jobs.begin(); it != jobs.end(); ) {
    StrongMT<BaseJob> job = *it;
    if ( !job->Poll() )
      it = jobs.erase( it );
    else
      ++it;
  }
}



void Instance::OnConfigReload()
{
  config->ReloadConfig();
}



void Instance::Roll( IClient * client, const SPreGameData & _preGame, const SPostGameData & _postGame )
{
  if ( !balancer->isopen() )
    ROLL_LOG_ERR( "Offline roll instance is receiving jobs" );

  string uids;
  for ( int i = 0; i < _preGame.users.size(); ++i )
    uids += NI_STRFMT( "%s%d", ( i > 0 ? ", " : "" ), _preGame.users[i].clientId );
  ROLL_LOG_MSG( "New roll request. roll_id=%016x, mode=%s(%d), uids=[%s], queue=%d", _preGame.socialLobbyGameId, EMode::ToString( _preGame.mode ), (int)_preGame.mode, uids, jobs.size() );

  StrongMT<BaseJob> job = new SessionRollJob( logic, client, seClient, _preGame, _postGame, this );

  jobs.push_back( job );
}



void Instance::ForgeRoll( IClient* client, const SForgeRollData & data )
{
  ROLL_LOG_MSG( "Forge roll requested. uid=%d, roll_id=%016x", data.uid, data.rollId );

  StrongMT<BaseJob> job = new ForgeRollJob( logic, client, seClient, data );

  jobs.push_back( job );
}

} //namespace roll
