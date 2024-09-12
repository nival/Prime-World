#include "stdafx.h"
#include "ClientAuth.h"
#include "System/SafeTextFormatStl.h"
#include "System/SafeTextFormatNstl.h"

NI_DEFINE_REFCOUNT( newLogin::IClientAuth );


namespace newLogin
{

ClientAuth::ClientAuth( IConfigProvider * _config, timer::Time _now ) :
config( _config ),
now( _now ),
nextDevUserId( 0 )
{
}



void ClientAuth::Poll( timer::Time _now )
{
  threading::MutexLock lock( mutex );

  now = _now;

  for ( Keys::iterator it = keys.begin(); it != keys.end(); )
    if ( now < it->second.expireTime )
      ++it;
    else
    {
      SessionKey & slot = it->second;
      if ( slot.usage )
        DebugTrace( "Removing session key. uid=%d, key=%s, used=%d", slot.uid, it->first, slot.usage );
      else
        WarningTrace( "Removing unused session key. uid=%d, key=%s", slot.uid, it->first );

      it = keys.erase( it );
    }
}



void ClientAuth::SetLoginAddress( const char * _addr )
{
  threading::MutexLock lock( mutex );

  loginAddress = _addr;
}



void ClientAuth::AddSessionKey( const nstl::string &_sessionKey, const Transport::TServiceId &_sessionPath, const nstl::string &_login, Cluster::TUserId _userid, Cluster::TGameId _gameid, Login::IAddSessionKeyCallback* _pcb )
{
  threading::MutexLock lock( mutex );

  std::string key( _sessionKey.c_str() );

  if ( keys.find( key ) != keys.end() )
    ErrorTrace( "Duplicate session key. uid=%d, key=%s", _userid, _sessionKey );

  SessionKey & slot = keys[key];

  slot.uid = _userid;
  slot.expireTime = now + config->Cfg()->sessionKeyExpire;
  slot.welcomeSvcId = _sessionPath;

  MessageTrace( "Session key added. uid=%d, key=%s, welcome=%s, total_keys=%d", _userid, _sessionKey, _sessionPath.c_str(), keys.size() );

  if ( _pcb )
    _pcb->OnAddSessionKey( 0, loginAddress, _userid );
}



void ClientAuth::AuthorizeClient( LoginReply & _reply, const LoginHello & _hello )
{
  threading::MutexLock lock( mutex );

  if ( _hello.sessionkey.empty() )
  {
    DevAuth( _reply, _hello );
    return;
  }

  std::string key( _hello.sessionkey.c_str() );

  Keys::iterator it = keys.find( key );
  if ( it == keys.end() )
  {
    WarningTrace( "Unknown session key. key=%s", key.c_str() );
    _reply.code = Login::ELoginResult::Refused;
    return;
  }

  SessionKey & slot = it->second;

  _reply.code = Login::ELoginResult::Success;
  _reply.uid = slot.uid;
  _reply.welcomingSvcId = slot.welcomeSvcId.c_str();

  ++slot.usage;

  MessageTrace( "Client authorized. key=%s, uid=%d, used=%d", key, _reply.uid, slot.usage );
}



void ClientAuth::DevAuth( LoginReply & _reply, const LoginHello & _hello )
{
  unsigned firstDevUid = config->Cfg()->firstDevUid;

  if ( !firstDevUid )
  {
    _reply.code = Login::ELoginResult::AccessDenied;
    WarningTrace( "Dev mode authorization refused. login=%s", _hello.login );
    return;
  }

  if ( _hello.login.empty() )
  {
    _reply.code = Login::ELoginResult::Refused;
    WarningTrace( "Dev mode authorization refused, login is empty" );
    return;
  }

  _reply.code = Login::ELoginResult::Success;
  _reply.uid = 0;

  if ( !nextDevUserId )
    nextDevUserId = firstDevUid;

  if ( !RestoreDevAuth( _reply, _hello ) )
    _reply.uid = nextDevUserId++;

  MessageTrace( "Dev mode authorization ok. login=%s, uid=%d", _hello.login, _reply.uid );
}



bool ClientAuth::RestoreDevAuth( LoginReply & _reply, const LoginHello & _hello )
{
  if ( _hello.login[0] != '_' )
    return false;

  std::string login( _hello.login.c_str() );
  DevLoginHistory::iterator it = devLoginHistory.find( login );
  if ( it != devLoginHistory.end() )
  {
    _reply.uid = it->second;
    DebugTrace( "Restored dev mode uid. login=%s, uid=%d", _hello.login, _reply.uid );
  }
  else
  {
    CleanupDevLoginHistory();

    _reply.uid = nextDevUserId++;
    devLoginHistory[login] = _reply.uid;
  }
  return true;
}



void ClientAuth::CleanupDevLoginHistory()
{
  const size_t HistoryCap = 100;

  while ( devLoginHistory.size() >= HistoryCap )
    devLoginHistory.erase( devLoginHistory.begin() );
}

} //namespace newLogin
