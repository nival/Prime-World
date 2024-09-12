#include "stdafx.h"
#include "RdpFrontendAgent.h"
#include "RdpFrontendAgentRemote.h"
#include "System/InlineProfiler.h"

NI_DEFINE_REFCOUNT( rdp_transport::IFrontendAgent );

namespace rdp_transport
{

static float userContextTimeout = 20.0f;
REGISTER_VAR( "rdp_frontend_user_timeout",    userContextTimeout, STORAGE_NONE );


const char * IFrontendAgent::InterfaceId = "frontendAgent";


FrontendAgent::FrontendAgent( timer::Time _now ) :
now( _now )
{
}



void FrontendAgent::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  now = _now;

  for ( Users::iterator it = users.begin(); it != users.end(); )
  {
    UserCtx * ctx = it->second;

    if ( ctx->authorized )
    {
      if ( !ctx->kickCallback.Lock().Valid() )
      {
        Transport::TClientId uid = it->first;
        MessageTrace( "FrontendAgent: Lost connection to user. uid=%d", uid );
        ctx->callback->UserDropped( uid );

        it = users.erase( it );
        continue;
      }
    }
    else if ( _now > ctx->created + userContextTimeout )
    {
      Transport::TClientId uid = it->first;
      ErrorTrace( "FrontendAgent: Frontend user timed out. uid=%d, timeout=%.1f", uid, userContextTimeout );
      ctx->callback->UserTimedOut( uid );

      it = users.erase( it );
      continue;
    }

    ++it;
  }
}



void FrontendAgent::PrepareUser( Transport::TClientId _uid, const string & _login, const string & _key, IFrontendAgentRemote * _callback )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  Strong<UserCtx> & ctx = users[_uid];

  if ( ctx.Valid() )
    ErrorTrace( "FrontendAgent: Dublicate user. uid=%d, login=%s, key=%s, prev_key=%s", _uid, _login, _key, ctx->key );
  else
    MessageTrace( "FrontendAgent: Adding user key. uid=%d, login=%s, key=%s", _uid, _login, _key );

  ctx = new UserCtx( _callback, _login, _key, now );

  _callback->UserPrepared( _uid );
}



void FrontendAgent::KickUser( Transport::TClientId _uid )
{
  NI_PROFILE_FUNCTION;

  MessageTrace( "FrontendAgent: Kicking user. uid=%d", _uid );

  threading::MutexLock lock( mutex );

  Users::iterator it = users.find( _uid );
  if ( it == users.end() )
  {
    ErrorTrace( "FrontendAgent: Unknown user to kick. uid=%d", _uid );
    return;
  }

  Strong<UserCtx> ctx = it->second;
  
  users.erase( it );

  StrongMT<Transport::IFrontendTransportKickCallback> lockedKickCb = ctx->kickCallback.Lock();
  if ( lockedKickCb )
    lockedKickCb->KickUser( _uid );
  else
    WarningTrace( "FrontendAgent: User dropped prior kicking. uid=%d", _uid );

  ctx->callback->UserKicked( _uid );
}



bool FrontendAgent::AuthorizeUser( Transport::TClientId _uid, const string & _key, Transport::IFrontendTransportKickCallback * _cb )
{
  NI_PROFILE_FUNCTION;

  MessageTrace( "FrontendAgent: Authorizing user. uid=%d", _uid );

  threading::MutexLock lock( mutex );

  Users::iterator it = users.find( _uid );

  if ( it == users.end() )
  {
    ErrorTrace( "FrontendAgent: Unknown user. uid=%d", _uid );
    return false;
  }

  Strong<UserCtx> ctx = it->second;

  if ( _key != ctx->key )
  {
    ErrorTrace( "FrontendAgent: Wrong key. uid=%d, key=%s, user_key=%s", _uid, ctx->key, _key );
    return false;
  }

  ctx->authorized = true;
  ctx->kickCallback = _cb;

  MessageTrace( "FrontendAgent: User authorized ok. uid=%d", _uid );

  ctx->callback->UserConnected( _uid );
  return true;
}



bool FrontendAgent::GetActiveUserLogin( Transport::TClientId _uid, string & _login )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  Users::iterator it = users.find( _uid );

  if ( it == users.end() )
    return false;

  UserCtx * ctx = it->second;

  _login = ctx->login;
  return true;
}

}; //namespace rdp_transport
