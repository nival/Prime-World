#include "stdafx.h"
#include "ClientControlUser.h"
#include "ClientControlLoginSvc.h"
#include "ClientControlRemote.h"
#include "Network/SessionKeyRegisterIface.h"
#include "System/Lifehacks.h"
#include "System/InlineProfiler.h"
#include "ClientControlLog.h"


namespace clientCtl
{

UserCtx::UserCtx( IConfigProvider * _config, Transport::TClientId _uid, Transport::TUserSid _userSid, LoginSvc * _svc, IUserPresenceCallback * _callback, timer::Time _now ) :
config( _config ),
uid( _uid ),
userSid( _userSid ),
loginSvcId( _svc->SvcId() ),
callback( _callback ),
state( EUserState::Active ),
loginSvc( _svc ),
timeout( _config->Cfg()->userOperationTimeout ),
linkCheckTimer( 0.1 )
{
  timeout.Stop();
}



bool UserCtx::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  if ( timeout.Running() && timeout.Poll() )
  {
    CLIENTCTL_LOG_ERR( "User state timed out. uid=%d, svcid=%s, st=%d", uid, loginSvcId.c_str(), (int)State() );
    return false;
  }

  if ( !loginSvc.Valid() )
  {
    CLIENTCTL_LOG_ERR( "User login svc removed. uid=%d, svcid=%s, st=%d", uid, loginSvcId.c_str(), (int)State() );
    return false;
  }

  if ( linkCheckTimer.Poll() )
  {
    linkCheckTimer.Restart();

    if ( callback->GetStatus() != rpc::Connected )
    {
      CLIENTCTL_LOG_ERR( "Lost connection to user callback. uid=%d, svcid=%s, st=%d", uid, loginSvcId.c_str(), (int)State() );
      return false;
    }
  }

  if ( !PollReentering() )
    return false;

  return true;
}



void UserCtx::WaitPreviousUsers( UserCtx * _prevUser )
{
  NI_VERIFY( state == EUserState::Active, "", return );

  if ( !_prevUser->prevInstances.empty() )
  {
    CLIENTCTL_LOG_DBG( "Adding previous user instances. uid=%d, svcid=%s, st=%d, number=%d", uid, loginSvcId.c_str(), (int)State(), _prevUser->prevInstances.size() );
    prevInstances = _prevUser->prevInstances;
  }

  prevInstances.push_back( _prevUser );

  Switch( EUserState::Reentering );
  timeout.Restart();
}



void UserCtx::Kick()
{
  prevInstances.clear();

  if ( ( state == EUserState::Active ) || ( state == EUserState::Reentering ) )
    callback->KickUser();

  Switch( EUserState::KickingForGood );
  timeout.Restart();
}



bool UserCtx::PollReentering()
{
  NI_PROFILE_FUNCTION;

  if ( state != EUserState::Reentering )
    return true;

  for ( UserList::iterator it = prevInstances.begin(); it != prevInstances.end(); )
    if ( it->Valid() )
      ++it;
    else
      it = lifehack::StlErase( prevInstances, it );

  if ( prevInstances.empty() )
  {
    CLIENTCTL_LOG_MSG( "All previous user instances kicked, letting user in. uid=%d, svcid=%s", uid, loginSvcId.c_str() );

    callback->LetUserIn();
    Switch( EUserState::Active );
  }

  return true;
}



void UserCtx::Switch( EUserState::Enum _st )
{
  state = _st;

  timeout.Stop();
}

} //namespace clientCtl
