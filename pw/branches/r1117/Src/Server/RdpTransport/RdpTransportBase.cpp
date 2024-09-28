#include "stdafx.h"
#include "RdpTransportBase.h"
#include "RdpTransportChannel.h"
#include "RdpTransportListener.h"
#include "RdpTransportMsg.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "Network/RUDP/IRdp.h"
#include "System/RandomInterfaceImpl.h"
#include "RdpSocketFactory.h"
#include "System/NiTimer.h"
#include "System/SafeTextFormatStl.h"


namespace rdp_transport
{

static int s_sockServerPriority = 1;
REGISTER_VAR( "rdp_sock_server_priority", s_sockServerPriority, STORAGE_NONE );

static int s_rdpLogicPriority = 1;
REGISTER_VAR( "rdp_logic_priority", s_rdpLogicPriority, STORAGE_NONE );

static int s_sockBufferSize = 65536;
REGISTER_VAR( "rdp_sock_buffer_size", s_sockBufferSize, STORAGE_NONE );


PrimaryBase::PrimaryBase( Transport::MessageFactory * _msgFact, Transport::IAddressTranslator * _at, const ni_udp::NetAddr & _defaultSocketAddr, const char * _dbgRole ) :
Transport::TransportSystemBase(),
msgFactory( _msgFact ),
defaultSocketAddr( _defaultSocketAddr ),
dbgRole( _dbgRole )
{
  commonCtx.allocator = new HeapAllocator;
  commonCtx.schedule = new Schedule;
  commonCtx.msgFactory = _msgFact;

  SetAddressTranslator( _at );
}



PrimaryBase::~PrimaryBase()
{
}



Network::NetAddress PrimaryBase::AllocateServerAddress( const Network::NetAddress & _ip )
{
  //just ignore "_ip"

  threading::MutexLock lock( mutex );

  StrongMT<Slot> slot;

  if ( defaultSlot )
    slot = defaultSlot;
  else
    slot = NewSlot( defaultSocketAddr, true );

  NI_VERIFY( slot, "", return 0 );

  NI_ASSERT( slot->nextSrviceMux <= LastAutoMux, "Out of free server muxes" );

  NI_ASSERT( slot->nextSrviceMux < LastAutoMux, "Out of free server muxes" );
  int mux = slot->nextSrviceMux++;

  Network::NetAddress result( FormatAddr( slot->addr, mux ) );

  DebugTrace( "Server address allocated. addr=%s, role=%s", result, dbgRole.c_str() );
  return result;
}



StrongMT<PrimaryBase::Slot> PrimaryBase::NewSlot( const ni_udp::NetAddr & _sockAddr, bool _searchPort )
{
  StrongMT<ni_udp::ISocketServer> sockSrv = new ni_udp::BlockingUdpSocketServer( s_sockServerPriority, s_sockBufferSize );

  StrongMT<SocketFactory> sockFact = new SocketFactory( sockSrv, _sockAddr, _searchPort ? 128 : 0, 0 );

  ni_udp::RdpOptions opts;
  ImplSetupRdpOptions( opts );

  Strong<ni_rnd::Factory> rndFact = new ni_rnd::Factory;

  StrongMT<ni_udp::IRdp> rdp = ni_udp::NewRdpInstance();
  if ( !rdp->Init( sockFact, opts, rndFact->Produce( (unsigned)timer::GetTicks() ), new timer::RealTimer ) )
    return 0;

  StrongMT<Slot> slot = new Slot( FirstAutoMux );
  slot->addr = sockFact->Addr();
  slot->sockSrv = sockSrv;
  slot->rdp = rdp;

  slots[sockFact->Addr()] = slot;

  if ( !defaultSlot )
    defaultSlot = slot;

  return slot;
}



StrongMT<Transport::IChannel> PrimaryBase::OpenChannelDirect( const Transport::Address & address, const Transport::TLoginData & loginData, const Network::NetAddress & netAddress, unsigned int pingperiod, unsigned int to )
{
  if ( netAddress.empty() )
      return 0;

  ni_udp::NetAddr parsed;
  unsigned mux = 0;
  if ( !ParseAddress( parsed, mux, netAddress.c_str() ) )
    return 0;

  NI_VERIFY( parsed.Port(), "", return 0 );

  if ( !mux )
    mux = DefaultMux;

  threading::MutexLock lock( mutex );

  if ( !defaultSlot )
    NewSlot( defaultSocketAddr, true );
  NI_VERIFY( defaultSlot, "", return 0 );

  StrongMT<Channel> chan = ImplCreateOutgoingChannel( parsed, address, loginData );
  if ( !chan->InitAsActive( defaultSlot->rdp, parsed, mux ) )
    return 0;

  MessageTrace( "Connecting to service. dest=%s, src=%s, dest_addr=%s, src_addr=%s", address.target.c_str(), address.source.c_str(), FormatAddr( parsed, mux ), defaultSlot->addr );

  return chan.Get();
}



StrongMT<Transport::IChannelListener> PrimaryBase::CreateChannelListenerDirect( Transport::TServiceId const & interfaceId, const string & listenAddress )
{
  if ( listenAddress.empty() )
      return 0;

  ni_udp::NetAddr parsed;
  unsigned mux = 0;
  if ( !ParseAddress( parsed, mux, listenAddress.c_str() ) )
    return 0;

  NI_VERIFY( parsed.Port(), "", return 0 );

  if ( !mux )
    mux = DefaultMux;

  StrongMT<Slot> slot;
  {
    threading::MutexLock lock( mutex );

    Slots::iterator it = slots.find( parsed );
    if ( it == slots.end() )
      slot = NewSlot( parsed, false );
    else
      slot = it->second;

    NI_VERIFY( slot, "", return 0 );
  }

  StrongMT<Listener> listener = ImplCreateChannelListener( interfaceId );
  NI_VERIFY( listener, "", return 0 );

  StrongMT<ni_udp::IRdpListenContext> listenCtx = slot->rdp->Listen( mux, listener );
  if ( !listenCtx )
    return 0;

  if ( !listener->Init( listenCtx ) )
    return 0;

  MessageTrace( "Service is listening. svcid=%s, addr=%s, role=%s", interfaceId.c_str(), FormatAddr( slot->addr, mux ), dbgRole );
  return listener.Get();
}



StrongMT<Transport::IMulticastChannel> PrimaryBase::OpenMulticastChannel( Transport::Address const & _taddr, unsigned int _pingperiod, unsigned int _opentimeout )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



StrongMT<Transport::IMulticastChannel> PrimaryBase::OpenMulticastChannelDirect( Transport::Address const & _taddr, Network::NetAddress const & _netaddr, unsigned int _pingperiod, unsigned int _opentimeout )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



StrongMT<Transport::IChannelListener> PrimaryBase::GetDefaultChannelListener() const
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



void PrimaryBase::ImplSetupRdpOptions( ni_udp::RdpOptions & _opt )
{
  _opt = ni_udp::RdpOptions();
}



StrongMT<Listener> PrimaryBase::ImplCreateChannelListener( Transport::TServiceId const & _interfaceId )
{
  return new Listener( _interfaceId, commonCtx );
}



StrongMT<Channel> PrimaryBase::ImplCreateOutgoingChannel( const ni_udp::NetAddr & _rdpRemoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData )
{
  return new Channel( EChanRole::Active, _rdpRemoteAddr, _transpAddress, _loginData, commonCtx );
}

} //namespace rdp_transport
