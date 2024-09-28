#include "stdafx.h"
#include "SocialLobby.h"
#include "SocialLobbyService.h"
#include "RPC/GateKeeper.h"
#include "RPC/LocalEntityFactory.h"

#include "LISocialLobby.auto.h"
#include "LISocialLobbyUserCtx.auto.h"
#include "LISocialLobbyPvxAck.auto.h"
#include "SocialLobbyMaps.h"
#include "SocialLobbyConfig.h"

#include "Server/LiveMMaking/RILiveMMaking.auto.h"
#include "Server/LiveMMaking/RILiveMMakingClient.auto.h"
#include "Server/LiveMMaking/LILiveMMakingClient.auto.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatClientHttpDispatcher.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "SocialLobbyLog.h"

#include "Db/DBServer.auto.h"


namespace socialLobby
{

static int s_devLobbyStartId = 1000;
static string s_externalAddr = string();

REGISTER_VAR( "soclobby_dev_start_id", s_devLobbyStartId, STORAGE_NONE );
REGISTER_VAR( "soclobby_ext_addr", s_externalAddr, STORAGE_NONE );


class DevSocLobby : public socialLobby::IDevSocLobby, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( DevSocLobby, socialLobby::IDevSocLobby, BaseObjectMT );
public:
  DevSocLobby( socialLobby::TUId _startUId ) : startUId( _startUId ) {}

private:
  socialLobby::TUId startUId;

  //socialLobby::IDevSocLobby
  virtual socialLobby::SDevUidRange AcquireUIdRange( int count ) {
    socialLobby::SDevUidRange result( startUId, startUId + count );
    startUId += count;
    SOCLOBBY_LOG_MSG( "Reserved developer id range: [%lld, %lld]", result.from, result.to );
    return result;
  }
};



class SocialStatisticsWrapper : public socialLobby::IGameStatistics, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocialStatisticsWrapper, socialLobby::IGameStatistics, BaseObjectMT );
public:
  SocialStatisticsWrapper( StatisticService::GameStatClient * _stat ) : statistics( _stat ) {}

  virtual void LogMMakingCancelled( const StatisticService::RPC::MMakingCanceled & _data ) {
    statistics->Message( _data );
  }

  virtual void LogMMakingGame( const StatisticService::RPC::MMakingGame & _game ) {
    statistics->Message( _game );
  }

private:
  StrongMT<StatisticService::GameStatClient> statistics;
};




Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
BaseService( _svcParams, _customParams )
{
  if ( !s_externalAddr.empty() )
  {
    SOCLOBBY_LOG_MSG( "Opening external gate for pvx lobby. ext_addr=%s", s_externalAddr );

    extClusterGateKeeper = new rpc::GateKeeper( BackendTransport(), SvcId(), Transport::autoAssignClientId, 0, s_externalAddr );
    Reset( extClusterRpcFactory, new rpc::LocalEntityFactory( extClusterGateKeeper->GetGate() ) );
  }

  RegisterBackendAttach<mmaking::ILiveMMakingClient, mmaking::LILiveMMakingClient>();
  RegisterBackendAttach<socialLobby::ISocialInterface, socialLobby::LISocialInterface>();
  RegisterBackendAttach<socialLobby::IUserContext, socialLobby::LIUserContext>();

  if ( extClusterRpcFactory )
  {
    extClusterRpcFactory->RegisterAttach<socialLobby::IPvxInterface, socialLobby::LIPvxInterface>();
    extClusterRpcFactory->RegisterAttach<socialLobby::IPvxAcknowledge, socialLobby::LIPvxAcknowledge>();
  }

  RegisterBackendAttach<socialLobby::IPvxAcknowledge, socialLobby::LIPvxAcknowledge>();
  RegisterBackendAttach<socialLobby::IPvxInterface, socialLobby::LIPvxInterface>();

  //statistics
  StrongMT<StatisticService::ClientHttpDispatcher> statClDispatcher = new StatisticService::ClientHttpDispatcher;
  statistics = new StatisticService::GameStatClient( statClDispatcher, 0 );

  //main logic
  Strong<Config> config = CreateConfigFromStatics();

  NDb::Ptr<NDb::RollSettings> rollSett = NDb::SessionRoot::GetRoot()->rollSettings;
  logic = new SocialLobby( config, new SocialStatisticsWrapper( statistics ), this, LoadMaps(), rollSett, this );
  RegisterBackendObject<socialLobby::ISocialInterface>( logic.Get(), serviceIds::SocialInterface );

  if ( extClusterGateKeeper )
    extClusterGateKeeper->GetGate()->RegisterObject<socialLobby::IPvxInterface>( logic.Get(), serviceIds::PvxInterface );
  else
    RegisterBackendObject<socialLobby::IPvxInterface>( logic, serviceIds::PvxInterface );

  //development interface
  if ( s_devLobbyStartId )
  {
    SOCLOBBY_LOG_MSG( "Opening developer interface. start_uid=%d", s_devLobbyStartId );
    devSocLobby = new DevSocLobby( s_devLobbyStartId );
    RegisterFrontendObject<socialLobby::IDevSocLobby>( devSocLobby.Get(), serviceIds::DevEntrance );
  }
}



Service::~Service()
{
  Reset( extClusterRpcFactory, 0 );

  UnregisterBackendObject<socialLobby::ISocialInterface>( logic );

  if ( extClusterGateKeeper )
    extClusterGateKeeper->GetGate()->UnregisterObject<socialLobby::IPvxInterface>( logic.Get() );
  else
    UnregisterBackendObject<socialLobby::IPvxInterface>( logic.Get() );

  if ( devSocLobby )
    UnregisterBackendObject( devSocLobby.Get() );
}



void Service::OnConfigReload()
{
  if ( !logic )
    return;

  Strong<Config> config = CreateConfigFromStatics();
  logic->UpdateConfigByValue( config );
}



void Service::Poll( timer::Time _now )
{
  logic->Poll( _now );

  if ( extClusterGateKeeper )
    extClusterGateKeeper->Poll();
}



void Service::NewGameAck( lobby::TSocialGameId _gameId )
{
  SOCLOBBY_LOG_MSG( "NewGameAck, game=%s", lobby::FmtSocGameId( _gameId ) );
  //TODO
}



void Service::NewReconnectingUserAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId )
{
  SOCLOBBY_LOG_MSG( "NewReconnectingUserAck, game=%s, user=pu%d", lobby::FmtSocGameId( _gameId ), (int)_userId );
  //TODO
}



void Service::NewSpectatorAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId )
{
  SOCLOBBY_LOG_MSG( "NewSpectatorAck, game=%s, user=pu%d", lobby::FmtSocGameId( _gameId ), (int)_userId );
  //TODO
}


void Service::UserLeftTheGameInCastleAck( lobby::TSocialGameId _gameId, TUserIdPvX _userId )
{
  SOCLOBBY_LOG_MSG( "UserLeftTheGameInCastleAck, game=%s, user=pu%d", lobby::FmtSocGameId( _gameId ), (int)_userId );
  //TODO
}

} //namespace socialLobby
