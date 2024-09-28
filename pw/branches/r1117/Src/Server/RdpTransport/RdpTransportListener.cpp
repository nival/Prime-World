#include "stdafx.h"
#include "RdpTransportListener.h"


namespace rdp_transport
{

Listener::Listener( const Transport::TServiceId & _svcid, const CommonCtx & _commonCtx, timer::Time _delayedAcceptTimeout ) :
serviceId( _svcid ),
commonCtx( _commonCtx ),
delayedAcceptTimeout( _delayedAcceptTimeout )
{
}



Listener::~Listener()
{
}



bool Listener::Init( ni_udp::IRdpListenContext * _listenCtx )
{
  listenCtx = _listenCtx;
  return true;
}



StrongMT<Channel> Listener::NewIncomingChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _ta )
{
  return new Channel( EChanRole::ReactiveDelayed, _remoteAddr, _ta, Transport::TLoginData() /*TODO*/, commonCtx );
}



void Listener::PushNewChannel( Transport::IChannel * _chan )
{
  threading::MutexLock lock( mutex );
  newChannels.push_back( _chan );
}



void Listener::GetNewConnections( Transport::TChannels * pConnections )
{
  threading::MutexLock lock( mutex );
  pConnections->swap( newChannels );
}



ni_udp::IRdpConnectionCallback * Listener::OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr )
{
  Transport::Address ta;
  ta.target = serviceId.c_str();

  StrongMT<Channel> chan = NewIncomingChannel( _remoteAddr, ta );

  MessageTrace( "Rdp Listener: Incoming channel created. svcid=%s, remote=%s", serviceId.c_str(), _remoteAddr );

  if ( delayedAcceptTimeout > 0 )
  {
    chan->InitAsReactive( _conn, this, delayedAcceptTimeout );

    threading::MutexLock lock( mutex );
    delayedAcceptChannels.insert( chan );
  }
  else
  {
    chan->InitAsReactive( _conn, 0, 0 );
    PushNewChannel( chan );
  }

  return chan;
}



void Listener::DelayedChannelAcceptFailed( Channel * _chan )
{
  WarningTrace( "Rdp Listener: Delayed channel accept failed. uid=%d, remote=%s", _chan->GetAddress().client, _chan->RemoteAddr() );

  threading::MutexLock lock( mutex );
  delayedAcceptChannels.erase( _chan );
}



void Listener::AcceptDelayedChannel( Channel * _chan )
{
  DebugTrace( "Rdp Listener: Delayed channel accepted. uid=%d, remote=%s", _chan->GetAddress().client, _chan->RemoteAddr() );

  StrongMT<Channel> keeper = _chan;

  {
    threading::MutexLock lock( mutex );
    delayedAcceptChannels.erase( _chan );
  }

  PushNewChannel( _chan );
}

} //namespace rdp_transport
