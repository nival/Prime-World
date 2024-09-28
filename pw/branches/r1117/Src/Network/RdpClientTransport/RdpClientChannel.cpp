#include "stdafx.h"
#include "RdpClientChannel.h"

namespace rdp_transport
{

static float defaultTimeout = 15.0f;
REGISTER_VAR( "login_chann_timeout", defaultTimeout, STORAGE_NONE );


#pragma warning( disable: 4355 ) //'this' : used in base member initializer list


ClientChannel::ClientChannel( ni_udp::IRdp * _rdp, const CommonCtx & _ctx, const Transport::Address & _ta, int _requestId ) :
Channel( EChanRole::ActiveDelayed, ni_udp::NetAddr(), _ta, Transport::TLoginData(), _ctx ),
rdp( _rdp ),
requestId( _requestId ),
state( EClientChanState::WaitingSvcAddr ),
timeout( defaultTimeout, this, &ClientChannel::OnTimeout )
{
}



void ClientChannel::OnSvcRequestReply( const newLogin::ServiceReqReply & _reply )
{
  MessageTrace( "ClientChannel: Connection details arrived. code=%s(%d), svcid=%s, req_id=%d, addr=%s", newLogin::ESvcConnectionResult::ToString( _reply.code ), (int)_reply.code, _reply.svcId.c_str(), _reply.requestId, _reply.externalAddress );

  threading::MutexLock lock( mutex );

  if ( ( _reply.svcId != GetAddress().target ) || ( _reply.requestId != requestId ) )
  {
    ErrorTrace( "ClientChannel: Wrong connection details, expected. svcid=%s, req_id=%d", GetAddress().target.c_str(), requestId );
    CloseClientChannel();
    return;
  }

  if ( state != EClientChanState::WaitingSvcAddr )
  {
    ErrorTrace( "ClientChannel: Unexpected connection details. svcid=%s, req_id=%d", GetAddress().target.c_str(), requestId );
    CloseClientChannel();
    return;
  }

  svcReqReply = _reply;

  if ( _reply.code != newLogin::ESvcConnectionResult::Ok )
  {
    ErrorTrace( "ClientChannel: Server refused connection to service. svcid=%s, req_id=%d, code=%d", GetAddress().target.c_str(), requestId, (int)svcReqReply.code );
    CloseClientChannel();
    return;
  }

  ni_udp::NetAddr svcAddr;
  unsigned mux = 0;
  if ( !ParseAddress( svcAddr, mux, _reply.externalAddress.c_str() ) )
  {
    ErrorTrace( "ClientChannel: Cannot parse service address. svcid=%s, addr=%s, req_id=%d", GetAddress().target.c_str(), svcAddr, requestId );
    CloseClientChannel();
    return;
  }

  MessageTrace( "ClientChannel: Connecting to sevice. svcid=%s, addr=%s, mux=%u, req_id=%d", _reply.svcId.c_str(), svcAddr, mux, requestId );

  if ( !InitAsActive( rdp, svcAddr, mux ) )
  {
    ErrorTrace( "ClientChannel: Cannot start connection to service. svcid=%s, addr=%s, req_id=%d", GetAddress().target.c_str(), svcAddr, requestId );
    CloseClientChannel();
    return;
  }

  Switch( EClientChanState::ConnectingToSvc );
  timeout.Restart( defaultTimeout );
}



void ClientChannel::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  MessageTrace( "ClientChannel: Connection established. svcid=%s, req_id=%d", GetAddress().target.c_str(), requestId );

  Channel::OnConnectionEstablished( _conn );

  threading::MutexLock lock( mutex );

  if ( state != EClientChanState::ConnectingToSvc )
  {
    ErrorTrace( "ClientChannel: Unexpected connection: svcid=%s, req_id=%d", GetAddress().target.c_str(), requestId );
    CloseClientChannel();
    return;
  }

  NI_VERIFY( RdpConnection(), "", return );

  dispatcher = new Network::PacketDispatcher;
  dispatcher->AddHandler( this, &ClientChannel::OnHelloReply );

  writer = new rdp_transport::PacketWriter( RdpConnection() );

  newLogin::FrontendHello hello;
  hello.uid = GetAddress().client;
  hello.key = svcReqReply.key;
  writer->Send( hello );

  Switch( EClientChanState::WaitingSvcAck );
  timeout.Restart( defaultTimeout );
}



void ClientChannel::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  Channel::OnConnectionClosed( _conn );

  threading::MutexLock lock( mutex );

  ErrorTrace( "ClientChannel: Connection to service closed. svcid=%s", GetAddress().target.c_str() );
  CloseClientChannel();
}



void ClientChannel::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  Channel::OnConnectionFailed( _conn );

  threading::MutexLock lock( mutex );

  ErrorTrace( "ClientChannel: Connection to service failed. svcid=%s", GetAddress().target.c_str() );
  CloseClientChannel();
}



void ClientChannel::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  EClientChanState::Enum st = EClientChanState::Closed;

  {
    threading::MutexLock lock( mutex );
    if ( state == EClientChanState::WaitingSvcAck )
    {
      NI_VERIFY( dispatcher, "", return );
      StrongMT<Network::PacketDispatcher> keeper = dispatcher;
      if ( !keeper->Dispatch( _data, _size ) )
      {
        ErrorTrace( "ClientChannel: Broken datagram from svc connection. svcid=%s, req_id=%d, size=%d", GetAddress().target.c_str(), requestId, _size );
        CloseClientChannel();
        return;
      }
    }
    else if ( state == EClientChanState::Active )
    {
      st = state;
    }
    else
    {
      ErrorTrace( "ClientChannel: Unexpected datagram in channel. svcid=%s, req_id=%d, size=%d", GetAddress().target.c_str(), requestId, _size );
      CloseClientChannel();
      return;
    }
  }

  if ( st == EClientChanState::Active )
    Channel::OnDatagram( _conn, _data, _size, _absRecvTime );
}



Network::ConnectionState::Enum ClientChannel::GetStatus() const
{
  threading::MutexLock lock( mutex );
  
  switch ( state )
  {
    case EClientChanState::WaitingSvcAddr:
    case EClientChanState::ConnectingToSvc:
    case EClientChanState::WaitingSvcAck:
      return Network::ConnectionState::Connecting;

    case EClientChanState::Closed:
      return Network::ConnectionState::Closed;

    case EClientChanState::Active:
      if ( Channel::GetStatus() == Network::ConnectionState::Connected )
        return Network::ConnectionState::Connected;
      else
        return Network::ConnectionState::Closed;

    default:
      return Network::ConnectionState::Invalid;
  }
}



void ClientChannel::SendRaw( const byte * _data, int _size )
{
  EClientChanState::Enum st = EClientChanState::Closed;
  {
    threading::MutexLock lock( mutex );
    st = state;
  }

  if ( st == EClientChanState::Closed )
  {
    ErrorTrace( "ClientChannel: Trying to write to closed channel. svcid=%s, state=%d", GetAddress().target.c_str(), (int)st );
    return;
  }

  if ( st == EClientChanState::Active )
    Channel::SendRaw( _data, _size );
  else
    PostponeMsg( _data, _size );
}



bool ClientChannel::Poll( timer::Time _now )
{
  threading::MutexLock lock( mutex );

  timeout.Poll();

  bool noMorePolling = ( state == EClientChanState::Active ) && ( state == EClientChanState::Closed );
  return !noMorePolling;
}



void ClientChannel::Switch( EClientChanState::Enum _st )
{
  state = _st;
  timeout.Stop();
}



void ClientChannel::OnTimeout()
{
  ErrorTrace( "ClientChannel: State timed out. svcid=%s, req_id=%d, state=%d", GetAddress().target.c_str(), requestId, (int)state );
  CloseClientChannel();
}



void ClientChannel::OnHelloReply( const newLogin::FrontendHelloReply & _reply )
{
  MessageTrace( "ClientChannel: Got service ack. svcid=%s, req_id=%d, code=%s(%d), state=%d", GetAddress().target.c_str(), requestId, newLogin::ESvcConnectionResult::ToString( _reply.code ), (int)_reply.code, (int)state );

  if ( state != EClientChanState::WaitingSvcAck )
  {
    ErrorTrace( "ClientChannel: Unexpected service ack. svcid=%s, req_id=%d, state=%d", GetAddress().target.c_str(), requestId, (int)state );
    CloseClientChannel();
    return;
  }

  if ( _reply.code != newLogin::ESvcConnectionResult::Ok )
  {
    ErrorTrace( "ClientChannel: Service refused connection. svcid=%s, req_id=%d, code=%d", GetAddress().target.c_str(), requestId, (int)svcReqReply.code );
    CloseClientChannel();
    return;
  }

  dispatcher = 0;
  writer = 0;

  Switch( EClientChanState::Active );

  DelayedActiveConnectionEstablished();
}



void ClientChannel::CloseClientChannel()
{
  Close();

  Switch( EClientChanState::Closed );
}

} //namesapce rdp_transport
