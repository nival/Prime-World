#include "stdafx.h"
#include "LobbySocialProxy.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "Server/LobbySocial/ISocialLobbyPvxSvc.h"
#include "LobbyConfig.h"
#include "LobbyLog.h"


namespace lobby
{

SocialLobbyProxy::SocialLobbyProxy( IConfigProvider * _cfg, rpc::GateKeeper * _gk, socialLobby::IPvxSvc * _pvxInterface, const Transport::TServiceId & _serviceId ) :
config( _cfg ),
pvxInterface( _pvxInterface ),
serviceId( _serviceId ),
now( 0 ),
nextLoadNotify( 0 ),
resendPvxSettings( false )
{
  remote = new rpc::IfaceRequester<socialLobby::RIPvxInterface>;
  remote->init( _gk, socialLobby::serviceIds::Service, socialLobby::serviceIds::PvxInterface );
}



socialLobby::RIPvxInterface * SocialLobbyProxy::GetRemotePtr()
{
  if ( remote->isopen() )
    if ( remote->iface() )
      return remote->iface();
  return 0;
}



bool SocialLobbyProxy::PvXPreparedForUser( socialLobby::TUserIdPvX _userId, const string & _key )
{
  if ( socialLobby::RIPvxInterface * ptr = GetRemotePtr() )
    ptr->PvXPreparedForUser( _userId, _key, this, &SocialLobbyProxy::TmpDummyCallback, (const char * )"PvXPreparedForUser" );
  return true;
}



bool SocialLobbyProxy::UserEnteredPvX( socialLobby::TUserIdPvX _userId )
{
  if ( socialLobby::RIPvxInterface * ptr = GetRemotePtr() )
    ptr->UserEnteredPvX( _userId, this, &SocialLobbyProxy::TmpDummyCallback, (const char * )"UserEnteredPvX" );
  return true;
}



bool SocialLobbyProxy::UserDroppedFromPvX( socialLobby::TUserIdPvX _userId, bool _intentional )
{
  if ( socialLobby::RIPvxInterface * ptr = GetRemotePtr() )
    ptr->UserDroppedFromPvX( _userId, _intentional, this, &SocialLobbyProxy::TmpDummyCallback, (const char * )"UserDroppedFromPvX" );
  return true;
}



bool SocialLobbyProxy::GameFinished( TSocialGameId _gameId, ETeam::Enum _winner )
{
  gameFinishEvents.push_back( new GameFinishEvent( _gameId, _winner, GameFinishEvent::State::OnPause, now, now, config->Cfg()->gameFinishDeliveryWait ) );
  return true;
}



void SocialLobbyProxy::OnConfigReload()
{
  resendPvxSettings = true;
}



void SocialLobbyProxy::Poll( timer::Time _now, unsigned _load )
{
  now = _now;

  remote->step();

  switch ( remote->PopNewState() )
  {
    case rpc::IfaceRequesterState::OPENED:
      LOBBY_LOG_MSG( "Got connection to social lobby" );
      nextLoadNotify = 0;
      SendPvxInstance();
      break;

    case rpc::IfaceRequesterState::CLOSED:
      LOBBY_LOG_WRN( "Connection to social lobby closed!" );
      break;

    default:
      break;
  }

  if ( remote->isopen() )
    if ( resendPvxSettings )
      SendPvxSettings();

  if ( remote->isopen() && ( _now > nextLoadNotify ) )
  {
    nextLoadNotify = _now + config->Cfg()->loadNotifyPeriod;
    LOBBY_LOG_MSG( "Sending load notify. loc=%s, svcid=%s, load=%u", config->Cfg()->myExternalLocation, serviceId.c_str(), _load );
    remote->iface()->PvxInstanceLoadNotify( config->Cfg()->myExternalLocation, serviceId, _load );
  }

  for ( GameFinishEvents::iterator it = gameFinishEvents.begin(); it != gameFinishEvents.end(); )
  {
    GameFinishEvents::iterator curr = it;
    ++it;

    StrongMT<GameFinishEvent> evt = *curr;

    if ( now > evt->start + config->Cfg()->gameFinishDeliveryTimeout )
    {
      LOBBY_LOG_ERR( "Game finish event delivery timed out. game_id=%s, evt_state=%d", FmtGameId( evt->gameId ), (int)evt->state );
      gameFinishEvents.erase( curr );
      continue;
    }

    switch ( evt->state )
    {
      default:
      case GameFinishEvent::State::Successfull:
        gameFinishEvents.erase( curr );
        break;

      case GameFinishEvent::State::WaitingAck:
        break;

      case GameFinishEvent::State::RetryFailed:
        evt->state = GameFinishEvent::State::OnPause;
        evt->nextSendAttempt = now + evt->currentPause;
        evt->currentPause *= 2.0;
        break;

      case GameFinishEvent::State::OnPause:
      {
        if ( now < evt->nextSendAttempt )
          break;

        if ( socialLobby::RIPvxInterface * ptr = GetRemotePtr() )
        {
          LOBBY_LOG_MSG( "Sending game finish message. game_id=%s", FmtGameId( evt->gameId ) );
          ptr->GameFinished( evt->gameId, evt->winner, evt.Get(), &GameFinishEvent::RpcCallResult, (int)0, config->Cfg()->gameFinishDeliveryWait );
          evt->state = GameFinishEvent::State::WaitingAck;
        }
        else
        {
          LOBBY_LOG_WRN( "Connection to social lobby is dead, game finish event is on hold. game_id=%s", FmtGameId( evt->gameId ) );
          evt->state = GameFinishEvent::State::RetryFailed;
          break;
        }
      }
    }
  }
}



void SocialLobbyProxy::GameFinishEvent::RpcCallResult( bool _result, int, rpc::CallStatus _st )
{
  if ( _st == rpc::CallSuccessful )
  {
    LOBBY_LOG_MSG( "Game finish event sent. game_id=%s, evt_state=%d", FmtGameId( gameId ), (int)state );
    state = State::Successfull;
  }
  else
  {
    LOBBY_LOG_ERR( "Game finish event RPC fail. game_id=%s, rpc_st=%d, evt_state=%d", FmtGameId( gameId ), (int)_st, (int)state );
    state = State::RetryFailed;
  }
}



void SocialLobbyProxy::ParseClusterSettings( socialLobby::PvxClusterSettings & _sett )
{
  _sett.capacity = config->Cfg()->loadCapacity;

  _sett.specialMode = (socialLobby::EPvxLobbyInstanceMode::Enum)config->Cfg()->developerBalanceMode;
  if ( ( _sett.specialMode != socialLobby::EPvxLobbyInstanceMode::Normal ) && ( _sett.specialMode != socialLobby::EPvxLobbyInstanceMode::ForcePartial ) &&
                                                                              ( _sett.specialMode != socialLobby::EPvxLobbyInstanceMode::ForceFullGames ) )
    _sett.specialMode = socialLobby::EPvxLobbyInstanceMode::Normal;

  _sett.specialList.clear();
  _sett.specialList.reserve( 16 );

  for ( const char * str = config->Cfg()->developerBalanceUids.c_str(); *str; )
  {
    int offs = 0, uid = 0;
    int count = sscanf( str, _sett.specialList.empty() ? "%d%n" : ",%d%n", &uid, &offs );
    if ( ( count != 1 ) || !offs )
    {
      LOBBY_LOG_ERR( "Wrong developer balance list. list='%s'", config->Cfg()->developerBalanceUids );
      break;
    }

    str += offs;

    _sett.specialList.push_back( uid );
  }
}



void SocialLobbyProxy::SendPvxInstance()
{
  socialLobby::PvxClusterSettings sett;
  ParseClusterSettings( sett );

  LOBBY_LOG_MSG( "Registering PVX instance. loc=%s, svcid=%s, capacity=%u, dev_mode=%d, dev_list=%s", config->Cfg()->myExternalLocation, serviceId.c_str(), sett.capacity, (int)sett.specialMode, sett.specialList );

  NI_VERIFY( remote->iface(), "", return );
  remote->iface()->PvxInstance( pvxInterface, config->Cfg()->myExternalLocation, serviceId, sett,
    this, &SocialLobbyProxy::TmpDummyCallback, (const char *)"PvxInstance" );
}



void SocialLobbyProxy::SendPvxSettings()
{
  socialLobby::PvxClusterSettings sett;
  ParseClusterSettings( sett );

  LOBBY_LOG_MSG( "Sending PVX instance settings. loc=%s, svcid=%s, capacity=%u, dev_mode=%d, dev_list=%s", config->Cfg()->myExternalLocation, serviceId.c_str(), sett.capacity, (int)sett.specialMode, sett.specialList );

  NI_VERIFY( remote->iface(), "", return );
  remote->iface()->UpdatePvxSettings( config->Cfg()->myExternalLocation, serviceId, sett,
    this, &SocialLobbyProxy::TmpDummyCallback, (const char *)"UpdatePvxSettings" );

  resendPvxSettings = false;
}



void SocialLobbyProxy::TmpDummyCallback( bool okay, const char * methodName, rpc::CallStatus st )
{
  LOBBY_LOG_MSG( "Social lobby ack: method=%s, okay=%d, rpc_status=%d", methodName, okay, (int)st );
  //NI_ASSERT( okay, "" );
}

} //namespace lobby
