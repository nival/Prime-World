#include "stdafx.h"
#include "RdpLoginClient.h"
#include "Server/RdpTransport/RdpTransportUtils.h"
#include "Network/PacketDispatcher.h"
#include "RdpClientChannel.h"


static float operationTimeout = 30.0f;
REGISTER_VAR( "login_timeout", operationTimeout, STORAGE_NONE );


namespace rdp_transport
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

LoginClient::LoginClient( ni_udp::IRdp * _rdp, const ni_udp::NetAddr & _loginSvcAddr, unsigned _loginSvcMux, const nstl::string & _login, const nstl::string & _password, const nstl::string & _sessionKey ) :
state( ELoginClientState::Connecting ),
login( _login ),
password( _password ),
sessionKey( _sessionKey ),
loginSvcAddr( _loginSvcAddr ),
rdp( _rdp ),
timeout( operationTimeout, this, &LoginClient::OnTimeout ),
nextChanReqId( 1 )
{
  dispatcher = new Network::PacketDispatcher;
  dispatcher->AddHandler( this, &LoginClient::OnHelloReply );
  dispatcher->AddHandler( this, &LoginClient::OnSvcReqReply );

  connection = rdp->Connect( _loginSvcAddr, _loginSvcMux, this );

  writer = new PacketWriter( connection );
}



void LoginClient::ParallelPoll( timer::Time _now )
{
  threading::MutexLock lock( mutex );

  timeout.Poll();

  for ( TChannelsByReqId::iterator it = channelsByReqId.begin(); it != channelsByReqId.end(); )
  {
    ClientChannel * chan = it->second;

    if ( chan->Poll( _now ) )
      ++it;
    else
    {
      MessageTrace( "LoginClient: Stopping channel poll. svcid=%s, req_id=%d", chan->GetAddress().target.c_str(), chan->RequestId() );
      it = channelsByReqId.erase( it );
    }
  }
}



ELoginClientState::Enum LoginClient::State()
{
  threading::MutexLock lock( mutex );
  return state;
}



void LoginClient::Switch( ELoginClientState::Enum _st )
{
  state = _st;
}



void LoginClient::Fail( Login::ELoginResult::Enum _result )
{
  if ( state == ELoginClientState::Failed )
    return;

  Switch( ELoginClientState::Failed );
  loginSvcReply.code = _result;

  connection = 0;
}



newLogin::LoginReply LoginClient::LoginSvcReply() const
{
  threading::MutexLock lock( mutex );
  return loginSvcReply;
}



StrongMT<Transport::IChannel> LoginClient::NewSvcChannel( const CommonCtx & _ctx, const Transport::TServiceId & _svcId )
{
  threading::MutexLock lock( mutex );

  NI_VERIFY( state == ELoginClientState::Ready, "", return 0 );

  int reqId = nextChanReqId++;

  MessageTrace( "LoginClient: Creating outgoing service channel. svcid=%s, req_id=%d", _svcId.c_str(), reqId );
  Transport::Address ta( Transport::TServiceId(), _svcId, loginSvcReply.uid );
  StrongMT<ClientChannel> chan = new ClientChannel( rdp, _ctx, ta, reqId );
  
  StrongMT<ClientChannel> & slot = channelsByReqId[reqId];
  NI_ASSERT( !slot.Valid(), "" );
  slot = chan;

  newLogin::ServiceRequest svcReq;
  svcReq.requestId = reqId;
  svcReq.svcId = _svcId;
  writer->Send( svcReq );

  return chan.Get();
}



void LoginClient::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  threading::MutexLock lock( mutex );

  if ( state == ELoginClientState::Failed )
    return;

  if ( state != ELoginClientState::Connecting )
  {
    ErrorTrace( "LoginClient: Unexpected connection. st=%d", (int)state );
    Fail( Login::ELoginResult::NoResult );
    return;
  }

  newLogin::LoginHello hello;
  hello.clientRevision = 0; //TODO
  hello.protocolVersion = 0; //TODO
  hello.login = login;
  hello.password = password;
  hello.sessionkey = sessionKey;

  writer->Send( hello );

  Switch( ELoginClientState::WaitingReply );
}



void LoginClient::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  MessageTrace( "LoginClient: Connection closed" );

  threading::MutexLock lock( mutex );

  Fail( Login::ELoginResult::NoConnection );
}



void LoginClient::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  ErrorTrace( "LoginClient: Connection failed" );

  threading::MutexLock lock( mutex );
  Fail( Login::ELoginResult::NoConnection );
}



void LoginClient::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  threading::MutexLock lock( mutex );

  if ( state == ELoginClientState::Failed )
    return;

  if ( !dispatcher->Dispatch( _data, _size ) )
  {
    ErrorTrace( "LoginClient: Broken datagram" );
    Fail( Login::ELoginResult::ServerOutdated );
    return;
  }
}



void LoginClient::OnHelloReply( const newLogin::LoginReply & _reply )
{
  MessageTrace( "LoginClient: Got login reply. code=%s(%d), uid=%d, welcome=%s", Login::ELoginResult::ToString( _reply.code ), (int)_reply.code, _reply.uid, _reply.welcomingSvcId );

  if ( state == ELoginClientState::Failed )
    return;

  if ( state != ELoginClientState::WaitingReply )
  {
    Fail( Login::ELoginResult::NoResult );
    return;
  }

  loginSvcReply = _reply;
  if ( loginSvcReply.code != Login::ELoginResult::Success )
  {
    WarningTrace( "LoginClient: Login failed!" );
    Fail( loginSvcReply.code );
    return;
  }

  Switch( ELoginClientState::Ready );
  timeout.Stop();
}



void LoginClient::OnTimeout()
{
  threading::MutexLock lock( mutex );

  ErrorTrace( "LoginClient: Operation timed out. state=%d", (int)state );
  Fail( Login::ELoginResult::AsyncTimeout );
}



void LoginClient::OnSvcReqReply( const newLogin::ServiceReqReply  & _reply )
{
  MessageTrace( "LoginClient: Got svc reqest reply. svcid=%s, req_id=%d, code=%d, addr=%s", _reply.svcId.c_str(), _reply.requestId, (int)_reply.code, _reply.externalAddress );

  if ( state != ELoginClientState::Ready )
  {
    ErrorTrace( "LoginClient: Unexpected svc reqest reply. svcid=%s, req_id=%d, state=%d", _reply.svcId.c_str(), _reply.requestId, (int)state );
    return;
  }

  TChannelsByReqId::iterator it = channelsByReqId.find( _reply.requestId );
  if ( it == channelsByReqId.end() )
  {
    WarningTrace( "LoginClient: Svc reqest reply for unknown request id. svcid=%s, req_id=%d", _reply.svcId.c_str(), _reply.requestId );
    return;
  }

  ClientChannel * chan = it->second;
  chan->OnSvcRequestReply( _reply );
}

} //namespace rdp_transport
