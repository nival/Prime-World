#include "stdafx.h"
#include "RdpTransport.h"
#include "RdpTransportChannel.h"
#include "RdpTransportListener.h"
#include "RdpTransportMsg.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "Network/RUDP/IRdp.h"
#include "System/SafeTextFormatStl.h"


namespace rdp_transport
{


static float backendChannelHandshakeTimeout = 10.0f;
REGISTER_VAR( "rdp_backend_handshake_timeout", backendChannelHandshakeTimeout, STORAGE_NONE );

static unsigned s_rdpLogEevents = ni_udp::RdpOptions::LogMajorEvents | ni_udp::RdpOptions::LogWarnings | ni_udp::RdpOptions::LogErrors;
REGISTER_VAR( "rdp_backend_log_events", s_rdpLogEevents, STORAGE_NONE );



BackendTransport::BackendTransport( Transport::MessageFactory * _msgFact, Transport::IAddressTranslator * _at, const ni_udp::NetAddr & _defaultSocketAddr, const char * _dbgRole ) :
PrimaryBase( _msgFact, _at, _defaultSocketAddr, _dbgRole )
{
}



void BackendTransport::ImplSetupRdpOptions( ni_udp::RdpOptions & _opt )
{
  PrimaryBase::ImplSetupRdpOptions( _opt );
  _opt.logEvents = s_rdpLogEevents;
}



StrongMT<Listener> BackendTransport::ImplCreateChannelListener( Transport::TServiceId const & _interfaceId )
{
  return new BackendListener( _interfaceId, CmmnCtx() );
}



StrongMT<Channel> BackendTransport::ImplCreateOutgoingChannel( const ni_udp::NetAddr & _rdpRemoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData )
{
  return new OutgoingBackendChannel( _rdpRemoteAddr, _transpAddress, _loginData, CmmnCtx() );
}





BackendListener::BackendListener( const Transport::TServiceId & _svcid, const CommonCtx & _commonCtx ) :
Listener( _svcid, _commonCtx, backendChannelHandshakeTimeout )
{
}



StrongMT<Channel> BackendListener::NewIncomingChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _ta )
{
  return new IncomingBackendChannel( _remoteAddr, _ta, Transport::TLoginData() /*TODO*/, CmnCtx() );
}









IncomingBackendChannel::IncomingBackendChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx ) :
Channel( EChanRole::ReactiveDelayed, _remoteAddr, _transpAddress, _loginData, _ctx )
{
}



void IncomingBackendChannel::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  Network::ConnectionState::Enum st = GetStatus();

  if ( st == Network::ConnectionState::Connected )
  {
    Channel::OnDatagram( _conn, _data, _size, _absRecvTime );
    return;
  }
  
  if ( st != Network::ConnectionState::Connecting )
    return;

  if ( _size == sizeof( Transport::TServiceId ) )
  {
    const Transport::TServiceId & remoteSvcId = *(const Transport::TServiceId *)_data;
    MessageTrace( "Recieved remote backend service id. src=%s, target=%s, remote=%s", remoteSvcId.c_str(), transportAddress.target.c_str(), RemoteAddr()  );
    transportAddress.source = remoteSvcId;
    DelayedAccept();
  }
  else
  {
    ErrorTrace( "Broken datagram from backend connection. target=%s, remote=%s, size=%d", transportAddress.target.c_str(), RemoteAddr(), _size );
    CloseDelayedChannel( "broken_datagram" );
  }
}




OutgoingBackendChannel::OutgoingBackendChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx ) :
Channel( EChanRole::Active, _remoteAddr, _transpAddress, _loginData, _ctx )
{}



void OutgoingBackendChannel::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  NI_ASSERT( RdpConnection()->Status() == ni_udp::EConnStatus::Ready, "" );

  DebugTrace( "Established outgoing connection. Sending source service id. src=%s, target=%s", transportAddress.source.c_str(), transportAddress.target.c_str() );

  Transport::TServiceId srcSvcId = transportAddress.source;
  RdpConnection()->SendDatagram( &srcSvcId, sizeof( srcSvcId ) );

  Channel::OnConnectionEstablished( _conn );
}

} //namespace rdp_transport
