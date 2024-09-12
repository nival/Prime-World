#include "stdafx.h"
#include "NewLoginUserCtx.h"
#include "ClientAuthInterface.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "Network/PacketDispatcher.h"
#include "NewLoginUserSvcLink.h"
#include "NewLoginSvcLinkInterface.h"
#include "ClientControl/ClientControlInterface.h"
#include "System/InlineProfiler.h"
#include "NewLoginLog.h"
#define SMAX_SIZE 300 //ограничение на количество символов в строке логина 


namespace newLogin
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

UserCtx::UserCtx( IConfigProvider * _config, IClientAuth * _auth, ni_udp::IRdpConnection * _conn, clientCtl::IInterfaceAccessor * _clientCtl, ISvcLinkDict * _svcLinkDict, timer::Time _now, const ni_udp::NetAddr & _remoteAddr, const Transport::TServiceId & _svcId, Transport::TUserSid _userSid ) :
remoteAddr( _remoteAddr ),
serviceId( _svcId ),
userSid( _userSid ),
config( _config ),
auth( _auth ),
conn( _conn ),
clientControl( _clientCtl ),
svcLinkDict( _svcLinkDict ),
state( EState::WaitingHello ),
usid( 0 ),
timeout( _config->Cfg()->helloWaitTimeout, this, &UserCtx::OnTimeout ),
emptyLinksTimeout( _config->Cfg()->emptyLinksTimeout, this, &UserCtx::OnEmptyLinksTimeout )
{
  //NUM_TASK добавил ограничители аллокации 
  containerSizeLimit = sizeof(char) * SMAX_SIZE;
  totalSizeLimit = 2 * sizeof(int) + 3 * containerSizeLimit;;
  
  emptyLinksTimeout.Stop();

  dispatcher = new Network::PacketDispatcher;
  dispatcher->AddHandler( this, &UserCtx::OnHello );
  dispatcher->AddHandler( this, &UserCtx::OnServiceRequest );
  
  writer = new rdp_transport::PacketWriter( conn );
}



void UserCtx::Switch( EState::Enum _st )
{
  if ( state != EState::Closed )
  {
    state = _st;

    timeout.Stop();
  }
}



UserCtx::EState::Enum UserCtx::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  timeout.Poll();

  PollSvcLinks( _now );

  switch ( state )
  {
    default:
      break;

    case EState::KickingUser:
    {
      if ( svcLinks.empty() )
      {
        NI_ASSERT( Uid(), "" );
        NEWLOGIN_LOG_MSG( "User kicked from all services. uid=%d, usid=%d", Uid(), userSid );
        if ( Uid() )
          if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
            cc->UserLeft( serviceId, Uid(), userSid );
        Close();
      }
      break;
    }
  }

  return state;
}



void UserCtx::PollSvcLinks( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  for ( SvcLinks::iterator it = svcLinks.begin(); it != svcLinks.end(); )
    if ( (*it)->Poll( _now ) )
      ++it;
    else
    {
      UserSvcLink * link = *it;
      NEWLOGIN_LOG_MSG( "Removing service connection. uid=%d, usid=%d, svc_id=%s, req_id=%d", Uid(), userSid, link->Data().svcId.c_str(), link->Data().requestId );
      it = svcLinks.erase( it );
    }

  if ( state == EState::Active)
  {
    if ( !svcLinks.empty() && emptyLinksTimeout.Running() )
    {
      NEWLOGIN_LOG_DBG( "There are active service requests, stopping timer. uid=%d, usid=%d", Uid(), userSid );
      emptyLinksTimeout.Stop();
    }
    else if ( svcLinks.empty() && !emptyLinksTimeout.Running() )
    {
      NEWLOGIN_LOG_DBG( "No active service requests, starting timer. uid=%d, usid=%d", Uid(), userSid );
      emptyLinksTimeout.Restart();
    }
  }

  emptyLinksTimeout.Poll();
}



void UserCtx::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
}



void UserCtx::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  NEWLOGIN_LOG_MSG( "Connection closed. login=%s, uid=%u, usid=%d, ip=%s", loginHello.login, Uid(), userSid, remoteAddr );

  threading::MutexLock lock( mutex );

  if ( Uid() )
    if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
      cc->UserLeft( serviceId, Uid(), userSid );

  conn = 0;

  Close();
}



void UserCtx::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  NEWLOGIN_LOG_ERR( "Connection failed. login=%s, uid=%u, usid=%d, ip=%s", loginHello.login, Uid(), userSid, remoteAddr );

  threading::MutexLock lock( mutex );

  if ( Uid() )
    if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
      cc->UserLeft( serviceId, Uid(), userSid );

  conn = 0;

  Close();
}



void UserCtx::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( !dispatcher->Dispatch( _data, _size ) )
  {
    NEWLOGIN_LOG_ERR( "Broken datagram. login=%s, uid=%u, usid=%d, ip=%s", loginHello.login, Uid(), userSid, remoteAddr );

    if ( Uid() )
      if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
        cc->UserLeft( serviceId, Uid(), userSid );

    Close();
  }
}



void UserCtx::LetUserIn()
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( state != EState::WaitingClientCtrl )
  {
    NEWLOGIN_LOG_ERR( "Got unexpected client control welcome. login=%s, state=%d, uid=%d, usid=%d", loginHello.login, (int)state, Uid(), userSid );
    Close();
    return;
  }

  NEWLOGIN_LOG_MSG( "Client control welcomes. login=%s, uid=%d, usid=%d", loginHello.login, Uid(), userSid );

  NI_ASSERT( loginReply.code == Login::ELoginResult::Success, "" );
  writer->Send( loginReply );

  Switch( EState::Active );
}



void UserCtx::DenyUser()
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( state != EState::WaitingClientCtrl )
  {
    NEWLOGIN_LOG_ERR( "Got unexpected client control denial. login=%s, state=%d, uid=%d, usid=%d", loginHello.login, (int)state, Uid(), userSid );
    Close();
    return;
  }

  NEWLOGIN_LOG_WRN( "Client control denied user. login=%s, uid=%d, usid=%d", loginHello.login, Uid(), userSid );

  SendFailReply( Login::ELoginResult::Refused );
  Close();
}



void UserCtx::KickUser()
{
  NI_PROFILE_FUNCTION;

  NEWLOGIN_LOG_MSG( "Kicking user. uid=%d, usid=%d, svc_links=%d", Uid(), userSid, svcLinks.size() );

  threading::MutexLock lock( mutex );

  if ( ( state == EState::Closed ) || ( state == EState::KickingUser ) )
  {
    NEWLOGIN_LOG_WRN( "Cannot kick user, wrong state. uid=%d, usid=%d, state=%d", Uid(), userSid, (int)state );
    if ( state == EState::Closed )
      if ( Uid() )
        if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
          cc->UserLeft( serviceId, Uid(), userSid );
    return;
  }

  for ( SvcLinks::iterator it = svcLinks.begin(); it != svcLinks.end(); ++it )
    if ( StrongMT<UserSvcLink> link = *it )
      link->KickUser();

  Switch( EState::KickingUser );
  timeout.Restart( config->Cfg()->processingTimeout );
}



void UserCtx::OnHello( const LoginHello & _hello )
{
  NI_PROFILE_FUNCTION;

  if ( state != EState::WaitingHello )
  {
    NEWLOGIN_LOG_WRN( "Got unexpected user hello. login=%s, usid=%d, state=%d, key=%s, key0=%s", _hello.login, userSid, (int)state, _hello.sessionkey, loginHello.sessionkey );
    Close();
    return;
  }

  NEWLOGIN_LOG_MSG( "Got user hello. login=%s, usid=%d, key=%s, proto_ver=%d, revision=%d, ip=%s", _hello.login, userSid, _hello.sessionkey, _hello.protocolVersion, _hello.clientRevision, remoteAddr );

  loginHello = _hello;

  auth->AuthorizeClient( loginReply, loginHello );

  if ( loginReply.code != Login::ELoginResult::Success )
  {
    NEWLOGIN_LOG_WRN( "Auth failed. Closing user context. login=%s, usid=%d, code=%s (%d)", _hello.login, userSid, Login::ELoginResult::ToString( loginReply.code ), (int)loginReply.code );
    writer->Send( loginReply );
    Close();
    return;
  }

  StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl();
  if ( !cc )
  {
    NEWLOGIN_LOG_ERR( "No connection to client control service. Closing user context. login=%s, uid=%d, usid=%d", _hello.login, Uid(), userSid );
    SendFailReply( Login::ELoginResult::ServerError );
    Close();
    return;
  }

  NEWLOGIN_LOG_DBG( "Requesting client control. login=%s, uid=%u, usid=%d, ip=%s", _hello.login, Uid(), userSid, remoteAddr );

  cc->UserEnters( serviceId, Uid(), userSid, this );

  Switch( EState::WaitingClientCtrl );
  timeout.Restart( config->Cfg()->processingTimeout );

  return;
}



void UserCtx::OnServiceRequest( const ServiceRequest & _req )
{
  NI_PROFILE_FUNCTION;

  if ( state != EState::Active )
  {
    NEWLOGIN_LOG_WRN( "Got unexpected service request. uid=%d, usid=%d, login=%s, svc_id=%s, req_id=%d, state=%d", Uid(), userSid, loginHello.login, _req.svcId.c_str(), _req.requestId, (int)state );
    if ( state != EState::KickingUser )
      Close();
    return;
  }

  NEWLOGIN_LOG_MSG( "User requested service connection. uid=%d, usid=%d, svc_id=%s, req_id=%d", Uid(), userSid, _req.svcId.c_str(), _req.requestId );

  const unsigned linksLimit = config->Cfg()->svcLinksLimit;
  if ( linksLimit && ( svcLinks.size() >= linksLimit ) )
  {
    NEWLOGIN_LOG_WRN( "Service request limit reached. uid=%d, usid=%d, svc_id=%s, limit=%u", Uid(), userSid, _req.svcId.c_str(), linksLimit );
    UserSvcLink::SendReply( writer, _req, ESvcConnectionResult::OutOfSvcResources, "", "" );
    Close();
    return;
  }

  StrongMT<ISvcLinkDict> lockedDict = svcLinkDict.Lock();
  if ( !lockedDict )
  {
    NEWLOGIN_LOG_ERR( "Service request failed. uid=%d, usid=%d, svc_id=%s", Uid(), userSid, _req.svcId.c_str() );
    UserSvcLink::SendReply( writer, _req, ESvcConnectionResult::ServerFault, "", "" );
    Close();
    return;
  }

  StrongMT<ISvcLink> svcLink = lockedDict->GetSvcLink( _req.svcId );
  if ( !svcLink )
  {
    NEWLOGIN_LOG_WRN( "Cannot connect to service. uid=%d, usid=%d, svc_id=%s", Uid(), userSid, _req.svcId.c_str() );
    UserSvcLink::SendReply( writer, _req, ESvcConnectionResult::UnknownSvc, "", "" );
    return;
  }

  StrongMT<UserSvcLink> link = new UserSvcLink( config, svcLink, writer, _req, Uid(), loginHello.login );
  svcLinks.push_back( link );
}



void UserCtx::OnTimeout()
{
  NI_PROFILE_FUNCTION;

  if ( state == EState::WaitingClientCtrl )
  {
    NEWLOGIN_LOG_ERR( "Client Control reply timed out. uid=%d, usid=%d, login=%s, key=%s", Uid(), userSid, loginHello.login, loginHello.sessionkey );
    SendFailReply( Login::ELoginResult::ServerError );
  }
  else
  {
    NEWLOGIN_LOG_ERR( "State timed out. uid=%d, usid=%d, login=%s, key=%s", Uid(), userSid, loginHello.login, loginHello.sessionkey );
    SendFailReply( Login::ELoginResult::ServerError );
  }

  Close();
}



void UserCtx::OnEmptyLinksTimeout()
{
  NI_PROFILE_FUNCTION;

  NEWLOGIN_LOG_ERR( "No service links established for too long. uid=%u, usid=%d, login=%s, ip=%s", Uid(), userSid, loginHello.login, remoteAddr );

  if ( StrongMT<clientCtl::IInterface> cc = clientControl->GetClientControl() )
    cc->UserLeft( serviceId, Uid(), userSid );

  Close();
}



void UserCtx::SendFailReply( Login::ELoginResult::Enum _code )
{
  if ( !writer || !conn )
    return;

  LoginReply reply;
  reply.code = _code;
  writer->Send( reply );
}



void UserCtx::Close()
{
  if ( conn )
  {
    conn->Close();
    conn = 0;
  }
  writer = 0;

  Switch( EState::Closed );
}

} //namespace newLogin
