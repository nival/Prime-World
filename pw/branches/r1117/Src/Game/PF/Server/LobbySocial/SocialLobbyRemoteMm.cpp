#include "stdafx.h"
#include "SocialLobbyRemoteMm.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyMaps.h"
#include "Server/LiveMMaking/ILiveMMaking.h"
#include "Server/LiveMMaking/ILiveMMakingClient.h"
#include "Db/DBServer.auto.h"
#include "SocialLobbyLog.h"

namespace socialLobby
{

RemoteMmLogic::RemoteMmLogic( Config * _cfg, const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _remote, mmaking::ILiveMMakingClient * _mmClient, const string & _mapId, timer::Time _now ) :
TSimpleFSM( RemoteMmState::Init, _now ),
config( _cfg ),
svcId( _svcId ),
mapId( _mapId ),
remote( _remote ),
mmClient( _mmClient )
{
}



bool RemoteMmLogic::Poll( timer::Time _now )
{
  if ( !TSimpleFSM::Poll( _now ) )
  {
    SOCLOBBY_LOG_ERR( "Remote MM logic timed out. svcid=%s, state=%d", svcId.c_str(), (int)State() );
    return false;
  }

  switch ( State() )
  {
    case RemoteMmState::Init:
    {
      StrongMT<mmaking::ILiveMMakingClient> lockedClient = mmClient.Lock();
      NI_VERIFY( lockedClient, "", ChangeState( RemoteMmState::ToRemove ) );

      ChangeState( RemoteMmState::SettingUp, config->mmLogicSetupTimeout );
      remote->SetupLogic( mapId, lockedClient );
      return true;
    }

    case RemoteMmState::SettingUp:
      return true;

    case RemoteMmState::Active:
      if ( remote->GetStatus() != rpc::Connected ) {
        SOCLOBBY_LOG_ERR( "Lost connection to MM logic. svcid=%s", svcId.c_str() );
        return false;
      }
      return true;

    case RemoteMmState::ToRemove:
      return false;

    default:
      return true;
  }
}



void RemoteMmLogic::SetupResult( bool _result )
{
  if ( State() != RemoteMmState::SettingUp ) {
    SOCLOBBY_LOG_ERR( "Wrong MM logic state for setup result. svcid=%s, state=%d", svcId.c_str(), (int)State() );
    ChangeState( RemoteMmState::ToRemove ); 
    return;
  }

  if ( !_result ) {
    SOCLOBBY_LOG_ERR( "MM logic setup failed! svcid=%s", svcId.c_str() );
    ChangeState( RemoteMmState::ToRemove );
    return;
  }

  ChangeState( RemoteMmState::Active );
}










MmLogix::MmLogix( Config * _cfg, IMaps * _maps, mmaking::ILiveMMakingClient * _mmClient ) :
config( _cfg ),
maps( _maps ),
mmClient( _mmClient ),
now( 0 )
{
}



void MmLogix::SetupResult( const Transport::TServiceId & _svcId, bool _result )
{
  SOCLOBBY_LOG_MSG( "MM logic setup result. svcid=%s, result=%d", _svcId.c_str(), _result );

  for ( TLogics::iterator it = logics.begin(); it != logics.end(); ++it )
    if ( it->second->SvcId() == _svcId ) {
      it->second->SetupResult( _result );
      return;
    }

  SOCLOBBY_LOG_ERR( "MM logic setup result for unknown svcid! svcid=%s", _svcId.c_str() );
}



string MmLogix::FindUnassignedGameMode( mmaking::EServiceGameModes::Enum _modes ) const
{
  for ( size_t i = 0; i < maps->Size(); ++i )
  {
    NDb::Ptr<NDb::AdvMapDescription> dbmap = maps->GetMap( i );

    switch ( _modes )
    {
      default:
      case mmaking::EServiceGameModes::Any:
        break;

      case mmaking::EServiceGameModes::ProductionOnly:
        if ( !dbmap->productionMode )
          continue;
        break;

      case mmaking::EServiceGameModes::DevelopmentOnly:
        if ( dbmap->productionMode )
          continue;
        break;
    }

    string key = maps->GetMapId( i );

    TLogics::const_iterator it = logics.find( key );
    if ( it == logics.end() )
      return key;
  }

  return string();
}



void MmLogix::AssignGameMode( const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _logic, const string & _mapId )
{
  SOCLOBBY_LOG_MSG( "Assigning MM logic. svcid=%s, map=%s", _svcId.c_str(), _mapId );

  Strong<RemoteMmLogic> logic = new RemoteMmLogic( config, _svcId, _logic, mmClient.Lock(), _mapId, now );
  Strong<RemoteMmLogic> & slot = logics[_mapId];
  NI_ASSERT( !slot.Valid(), NI_STRFMT( "Overriding MM logic slot. svcid=%s, map=%s", _svcId.c_str(), _mapId ) );
  slot = logic;
}



void MmLogix::RegisterMmLogic( const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _logic, mmaking::EServiceGameModes::Enum _gameModes )
{
  SOCLOBBY_LOG_MSG( "New MM logic. svcid=%s, modes=%s", _svcId.c_str(), mmaking::EServiceGameModes::ToString( _gameModes ) );

  string mapId = FindUnassignedGameMode( _gameModes );

  if ( !mapId.empty() ) {
    AssignGameMode( _svcId, _logic, mapId );
    return;
  }

  SOCLOBBY_LOG_MSG( "All appropriate game modes are assigned. Putting MM logic on hold. svcid=%s", _svcId.c_str() );
  unassigned[_svcId] = UnassignedLogic( _logic, _gameModes );
}



RemoteMmLogic * MmLogix::GetMmLogic( const string & mapId ) const
{
  string key = mmaking::PrepareGameModeName( mapId );

  TLogics::const_iterator it = logics.find( key );
  if ( it == logics.end() )
    return 0;

  return it->second;
}



void MmLogix::Poll( timer::Time _now )
{
  now = _now;

  for ( TUnassignedLogics::iterator it = unassigned.begin(); it != unassigned.end(); )
    if ( it->second.logic->GetStatus() == rpc::Connected )
      ++it;
    else
    {
      SOCLOBBY_LOG_ERR( "Lost connection to unassigned MM logic! svcid=%s", it->first.c_str() );
      it = unassigned.erase( it );
    }

  for ( TLogics::iterator it = logics.begin(); it != logics.end(); )
    if ( it->second->Poll( now ) )
      ++it;
    else
    {
      Strong<RemoteMmLogic> logic = it->second;
      SOCLOBBY_LOG_MSG( "Removing MM logic. svcid=%s", it->first.c_str() );
      it = logics.erase( it );

      for ( TUnassignedLogics::iterator it2 = unassigned.begin(); it2 != unassigned.end(); ++it2 )
      {
        Transport::TServiceId svcId = it2->first;
        UnassignedLogic un = it2->second;

        string mapId = FindUnassignedGameMode( un.modes );
        if ( !mapId.empty() )
        {
          SOCLOBBY_LOG_MSG( "Using unassigned MM logic. svcid=%s", svcId.c_str() );
          AssignGameMode( svcId, un.logic, mapId );
          unassigned.erase( it2 );
          return;
        }
      }
    }
}

} //namespace socialLobby
