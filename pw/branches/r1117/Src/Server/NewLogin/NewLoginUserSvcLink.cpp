#include "stdafx.h"
#include "NewLoginUserSvcLink.h"
#include "NewLoginSvcLinkInterface.h"
#include "RdpTransport/RdpFrontendAgentInterface.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "System/Math/MD4.h"
#include "System/InlineProfiler.h"
#include "NewLoginLog.h"


namespace newLogin
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

UserSvcLink::UserSvcLink( IConfigProvider * _config, ISvcLink * _link, rdp_transport::PacketWriter * _writer, const ServiceRequest & _data, Transport::TClientId _uid, const string & _login ) :
data( _data ),
uid( _uid ),
login( _login ),
state( EState::WaitingSvcLink ),
link( _link ),
writer( _writer ),
timeout( _config->Cfg()->processingTimeout, this, &UserSvcLink::OnTimeout )
{
}



void UserSvcLink::Switch( EState::Enum _st )
{
  if ( state != EState::Closed )
  {
    state = _st;
    timeout.Stop();
  }
}



bool UserSvcLink::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  timeout.Poll();

  switch ( state )
  {
    default:
      NI_ALWAYS_ASSERT( "" );
      Close();
      break;

    case EState::WaitingSvcLink:
    {
      NI_PROFILE_BLOCK( "WaitingSvcLink" );

      StrongMT<ISvcLink> locked = link.Lock();
      if ( !locked )
      {
        Close();
        break;
      }

      if ( !locked->Ready() )
        break;

      StrongMT<rdp_transport::IFrontendAgent> faa = locked->Get();
      NI_VERIFY( faa, "", Close(); break; );

      SetupKey();
      frontendAddr = locked->FrontendSvcAddr();

      NEWLOGIN_LOG_MSG( "Preparing service for user. uid=%d, svc_id=%s, key=%s", uid, data.svcId.c_str(), key );

      faa->PrepareUser( uid, login, key, this );

      Switch( EState::PreparingUser );
      timeout.Restart();
      break;
    }

    case EState::PreparingUser:
    case EState::WaitingSvcAck:
    case EState::Active:
    case EState::KickingUser:
    case EState::Closed:
      break;
  }

  return ( state != EState::Closed );
}



void UserSvcLink::KickUser()
{
  NEWLOGIN_LOG_MSG( "Kicking from service. uid=%d, svc_id=%s, state=%d", uid, data.svcId.c_str(), (int)state );

  if ( ( state != EState::Closed ) )
    if ( StrongMT<ISvcLink> locked = link.Lock() )
      if ( StrongMT<rdp_transport::IFrontendAgent> faa = locked->Get() )
      {
        faa->KickUser( uid );

        Switch( EState::KickingUser );
        timeout.Restart();
        return;
      }

  NEWLOGIN_LOG_ERR( "Failed to kick user from service. uid=%d, svc_id=%s, state=%d", uid, data.svcId.c_str(), (int)state );
  Close();
}



void UserSvcLink::UserPrepared( Transport::TClientId _uid )
{
  NEWLOGIN_LOG_MSG( "Remote service prepared for user. uid=%d, svc_id=%s, req_id=%d", uid, data.svcId.c_str(), data.requestId );

  NI_VERIFY( uid == _uid, "", return );

  if ( state != EState::PreparingUser )
  {
    NEWLOGIN_LOG_WRN( "Service link is in wrong state. uid=%d, svc_id=%s, req_id=%d, state=%d", uid, data.svcId.c_str(), data.requestId, (int)state );
    return;
  }

  SendReply( writer, data, ESvcConnectionResult::Ok, frontendAddr.c_str(), key.c_str() );

  Switch( EState::WaitingSvcAck );
  timeout.Restart();
}



void UserSvcLink::UserConnected( Transport::TClientId _uid )
{
  NEWLOGIN_LOG_MSG( "User connected to remote service. uid=%d, svc_id=%s, req_id=%d", uid, data.svcId.c_str(), data.requestId );

  NI_VERIFY( uid == _uid, "", return );

  if ( state != EState::WaitingSvcAck )
  {
    NEWLOGIN_LOG_WRN( "Service link is in wrong state. uid=%d, svc_id=%s, req_id=%d, state=%d", uid, data.svcId.c_str(), data.requestId, (int)state );
    return;
  }

  Switch( EState::Active );
}



void UserSvcLink::UserTimedOut( Transport::TClientId _uid )
{
  NEWLOGIN_LOG_WRN( "User did not make it to remote service. uid=%d, svc_id=%s, req_id=%d", uid, data.svcId.c_str(), data.requestId );

  NI_VERIFY( uid == _uid, "", return );

  if ( state != EState::WaitingSvcAck )
  {
    NEWLOGIN_LOG_WRN( "Service link is in wrong state. uid=%d, svc_id=%s, req_id=%d, state=%d", uid, data.svcId.c_str(), data.requestId, (int)state );
    return;
  }

  Close();
}



void UserSvcLink::UserKicked( Transport::TClientId _uid )
{
  NEWLOGIN_LOG_MSG( "User kicked from service. uid=%d, svc_id=%s, req_id=%d", uid, data.svcId.c_str(), data.requestId );

  NI_VERIFY( uid == _uid, "", return );

  if ( state != EState::Closed )
    Close();
}



void UserSvcLink::UserDropped( Transport::TClientId _uid )
{
  NEWLOGIN_LOG_MSG( "User dropped from service. uid=%d, svc_id=%s, req_id=%d", uid, data.svcId.c_str(), data.requestId );

  NI_VERIFY( uid == _uid, "", return );

  if ( state != EState::Closed )
    Close();
}



void UserSvcLink::OnTimeout()
{
  NEWLOGIN_LOG_WRN( "Service link operation timed out. uid=%d, svc_id=%s, req_id=%d, state=%d", uid, data.svcId.c_str(), data.requestId, (int)state );

  Close();
}



void UserSvcLink::Close()
{
  Switch( EState::Closed );
  link = 0;
}



void UserSvcLink::SetupKey()
{
  const char * Salt = "Chocolate Salty Balls";

  //TODO: Make it more durable
  math::MD5Generator md5;
  md5.Start();
  md5.Update( (const byte *)Salt, strlen( Salt ) );
  md5.AddObject( timer::GetTicks() );
  md5.AddObject( uid );
  md5.Update( (const byte *)Salt, strlen( Salt ) );
  md5.Stop();

  key = md5.Get().ToString();
}



void UserSvcLink::SendReply( rdp_transport::PacketWriter * _writer, const ServiceRequest & _req, ESvcConnectionResult::Enum _code, const char * _addr, const char * _key )
{
  ServiceReqReply reply;
  reply.code = _code;
  reply.requestId = _req.requestId;
  reply.svcId = _req.svcId;
  reply.externalAddress = _addr;
  reply.key = _key;
  _writer->Send( reply );
}

} //namespace newLogin
