#include "stdafx.h"
#include "RdpTransportFrontendChannel.h"

namespace rdp_transport
{

FrontendChannel::FrontendChannel( const ni_udp::NetAddr & _remoteAddr, Transport::IFrontendTransportAuth * _auth, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx ) :
Channel( EChanRole::ReactiveDelayed, _remoteAddr, _transpAddress, _loginData, _ctx ),
auth( _auth )
{
}



void FrontendChannel::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  Network::ConnectionState::Enum st = GetStatus();

  if ( st == Network::ConnectionState::Connected )
  {
    Channel::OnDatagram( _conn, _data, _size, _absRecvTime );
    return;
  }
  else if ( st != Network::ConnectionState::Connecting )
    return;

  StrongMT<Network::PacketDispatcher> keeper;
  {
    threading::MutexLock lock( authMutex );
    keeper = dispatcher;
  }
  NI_VERIFY( keeper, "", return );

  if ( !keeper->Dispatch( _data, _size ) )
  {
    ErrorTrace( "Broken datagram from frontend connection. remote=%s", RemoteAddr() );
    CloseDelayedChannel( "broken_datagram" );
  }
}



void FrontendChannel::KickUser( Transport::TClientId )
{
  CloseDelayedChannel( "kick" );
}



void FrontendChannel::OnRdpConnectionChange()
{
  threading::MutexLock lock( authMutex );

  dispatcher = new Network::PacketDispatcher;
  dispatcher->AddHandler( this, &FrontendChannel::OnHello );

  writer = new rdp_transport::PacketWriter( RdpConnection() );
}



void FrontendChannel::OnHello( const newLogin::FrontendHello & _hello )
{
  MessageTrace( "Authorizing frontend user. uid=%d, key=%s", _hello.uid, _hello.key );

  {
    threading::MutexLock lock( authMutex );

    NI_VERIFY( writer, "", return );

    if ( !auth->AuthorizeUser( _hello.uid, _hello.key, this ) )
    {
      newLogin::FrontendHelloReply reply;
      reply.code = newLogin::ESvcConnectionResult::WrongFrontendKey;
      writer->Send( reply );
      CloseDelayedChannel( "auth_failed" );
      return;
    }

    transportAddress.client = _hello.uid;

    newLogin::FrontendHelloReply reply;
    reply.code = newLogin::ESvcConnectionResult::Ok;
    writer->Send( reply );

    dispatcher = 0;
    writer = 0;
  }

  DelayedAccept();
}

} //namesapce rdp_transport
