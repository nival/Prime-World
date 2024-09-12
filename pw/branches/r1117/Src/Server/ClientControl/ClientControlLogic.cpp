#include "stdafx.h"
#include "ClientControlLogic.h"
#include "ClientControlLoginSvc.h"
#include "ClientControlUser.h"
#include "ClientControlRemote.h"
#include "System/Lifehacks.h"
#include "System/InlineProfiler.h"
#include "ClientControlLog.h"


NI_DEFINE_REFCOUNT( clientCtl::IInterface );
NI_DEFINE_REFCOUNT( clientCtl::IInterfaceAccessor );


namespace clientCtl
{

Logic::Logic( IConfigProvider * _config, timer::Time _now ) :
config( _config ),
now( _now ),
dbgDumpTimeout( 10.0 )
{
}



void Logic::Poll( timer::Time _now, unsigned & _ccu )
{
  NI_PROFILE_FUNCTION;

  now = _now;

  PollLoginSvc();
  PollUsers();
  PollDisconnectedUsers();
  PollDebug();

  _ccu = users.size();
}



void Logic::PollLoginSvc()
{
  NI_PROFILE_FUNCTION;

  for ( TLogins::iterator it = logins.begin(); it != logins.end(); )
    if ( !it->second->Poll( now ) )
    {
      CLIENTCTL_LOG_DBG( "Removing login svc descriptor. svcid=%s", it->second->SvcId().c_str() );
      it = lifehack::StlErase( logins, it );
    }
    else
      ++it;
}



void Logic::PollUsers()
{
  NI_PROFILE_FUNCTION;

  for ( TUsers::iterator it = users.begin(); it != users.end(); )
  {
    UserCtx * ctx = it->second;

    if ( ctx->Poll( now ) )
      ++it;
    else
    {
      CLIENTCTL_LOG_DBG( "Deleting user. uid=%d, svcid=%d", ctx->Uid(), ctx->LoginSvcId().c_str() );
      it = lifehack::StlErase( users, it );
    }
  }
}



void Logic::PollDisconnectedUsers()
{
  NI_PROFILE_FUNCTION;

  for ( TUserList::iterator it = disconnectingUsers.begin(); it != disconnectingUsers.end(); )
  {
    UserCtx * ctx = *it;

    if ( ctx->Poll( now ) )
      ++it;
    else
    {
      CLIENTCTL_LOG_DBG( "Deleting disconnected user. uid=%d, svcid=%d", ctx->Uid(), ctx->LoginSvcId().c_str() );
      it = lifehack::StlErase( disconnectingUsers, it );
    }
  }
}



void Logic::PollDebug()
{
  if ( !dbgDumpTimeout.Poll() )
    return;

  dbgDumpTimeout.Restart();

  unsigned loginLoad = 0;
  for ( TLogins::iterator it = logins.begin(); it != logins.end(); ++it )
  {
    Strong<LoginSvc> login = it->second;
    loginLoad += login->Load();
  }

  CLIENTCTL_LOG_MSG( "Current load dump. ccu=%d, disconnecting=%d, login_number=%u, login_total_users=%u", users.size(), disconnectingUsers.size(), logins.size(), loginLoad );
}



void Logic::RegisterLoginSvc( const Transport::TServiceId & _svcid, Login::ISessionKeyRegister* _sessionKeyInterface )
{
  NI_PROFILE_FUNCTION;

  Strong<LoginSvc> & slot = logins[_svcid];

  if ( slot.Valid() )
    CLIENTCTL_LOG_WRN( "Login service replaced. svcid=%s", _svcid.c_str() );
  else
    CLIENTCTL_LOG_MSG( "Login service added. svcid=%s", _svcid.c_str() );

  slot = new LoginSvc( config, _svcid, _sessionKeyInterface, now );
}



void Logic::UpdateLoginSvc( const Transport::TServiceId & _svcid, int _state, unsigned _load )
{
  NI_PROFILE_FUNCTION;

  TLogins::iterator it = logins.find( _svcid );
  if ( it == logins.end() )
  {
    CLIENTCTL_LOG_ERR( "Unknown login service to update. svcid=%s", _svcid.c_str() );
    return;
  }

  it->second->Update( (ELoginSvcState::Enum)_state, _load );
}



void Logic::AllocateLoginSvc( int _alllocId, ILoginSvcAllocationCallback * _callback )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _callback, "", return );

  Strong<LoginSvc> best;

  for ( TLogins::iterator it = logins.begin(); it != logins.end(); ++it )
  {
    Strong<LoginSvc> login = it->second;
    if ( login->State() != ELoginSvcState::Online )
      continue;

    if ( !best || ( login->Load() < best->Load() ) )
      best = login;
  }

  if ( !best )
  {
    CLIENTCTL_LOG_WRN( "Cannot allocate login service. alloc_id=%d", _alllocId );
    _callback->LoginSvcAllocationFailed( _alllocId );
    return;
  }

  best->IncLoad( 1 );

  CLIENTCTL_LOG_MSG( "Login service allocated. alloc_id=%d, svcid=%s, load=%d", _alllocId, best->SvcId().c_str(), best->Load() );

  _callback->LoginSvcAllocated( _alllocId, best->SvcId(), best->Remote() );
}



void Logic::UserEnters( const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid, IUserPresenceCallback * _callback )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _callback, "", return );

  TLogins::iterator loginIt = logins.find( _loginSvcId );
  if ( loginIt == logins.end() )
  {
    CLIENTCTL_LOG_ERR( "Unknown login service to enter by user. uid=%d, svcid=%s", _uid, _loginSvcId.c_str() );
    _callback->DenyUser();
    return;
  }
  LoginSvc * svc = loginIt->second;

  UserCtx * prevCtx = 0;

  TUsers::iterator userIt = users.find( _uid );
  if ( userIt != users.end() )
  {
    prevCtx = userIt->second;

    CLIENTCTL_LOG_WRN( "User already in cluster, kicking previous instances. uid=%d, svcid=%s, prev_svcid=%s", _uid, _loginSvcId.c_str(), prevCtx->LoginSvcId().c_str() );

    disconnectingUsers.push_back( prevCtx );
    users.erase( userIt );
  }

  CLIENTCTL_LOG_MSG( "New user on login service. uid=%d, svcid=%d", _uid, _loginSvcId.c_str() );
  Strong<UserCtx> ctx = new UserCtx( config, _uid, _usid, svc, _callback, now );
  users[_uid] = ctx;

  if ( prevCtx )
  {
    ctx->WaitPreviousUsers( prevCtx );
    prevCtx->Kick();
  }
  else
    _callback->LetUserIn();
}



void Logic::UserLeft( const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid )
{
  NI_PROFILE_FUNCTION;

  NI_ASSERT( _uid, "" );

  CLIENTCTL_LOG_MSG( "User left login service. uid=%d, usid=%d, svcid=%s", _uid, _usid, _loginSvcId.c_str() );

  TUsers::iterator it = users.find( _uid );
  if ( it != users.end() )
  {
    UserCtx * user = it->second;
    if ( ( _usid == user->UserSid() ) && ( _loginSvcId == user->LoginSvcId() ) )
    {
      CLIENTCTL_LOG_DBG( "Removing user. uid=%d, usid=%d, svcid=%s, st=%d", _uid, _usid, _loginSvcId.c_str(), (int)user->State() );
      users.erase( it );
    }
  }

  for ( TUserList::iterator it = disconnectingUsers.begin(); it != disconnectingUsers.end(); )
  {
    UserCtx * user = *it;
    if ( ( user->Uid() == _uid ) && ( user->UserSid() == _usid ) && ( user->LoginSvcId() == _loginSvcId ) )
    {
      CLIENTCTL_LOG_MSG( "Removing disconnecting user. uid=%d, usid=%d, svcid=%s, st=%d", _uid, _usid, _loginSvcId.c_str(), (int)user->State() );
      it = lifehack::StlErase( disconnectingUsers, it );
    }
    else
      ++it;
  }
}



void Logic::KickUser( Transport::TClientId _uid )
{
  NI_PROFILE_FUNCTION;

  TUsers::iterator it = users.find( _uid );
  if ( it == users.end() )
  {
    CLIENTCTL_LOG_ERR( "Unknown user to kick. uid=%d", _uid );
    return;
  }

  UserCtx * ctx = it->second;

  CLIENTCTL_LOG_MSG( "Kicking user by uid. uid=%d, usid=%d, svcid=%s, st=%d", _uid, ctx->UserSid(), ctx->LoginSvcId().c_str(), (int)ctx->State() );

  ctx->Kick();
  
  disconnectingUsers.push_back( ctx );
  users.erase( it );
}

} //namespace clientCtl
