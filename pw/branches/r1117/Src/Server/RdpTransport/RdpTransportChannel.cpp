#include "stdafx.h"
#include "RdpTransportChannel.h"
#include "RdpTransportMsg.h"
#include "Network/Message.h"
#include "Network/TransportUtils.h"

namespace rdp_transport
{


static bool dumpPackets = false;
REGISTER_VAR( "rdp_dump_packets", dumpPackets, STORAGE_NONE );


Channel::Channel( EChanRole::Enum _role, const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx ) :
role( _role ),
remoteAddr( _remoteAddr ),
transportAddress( _transpAddress ),
loginData( _loginData ),
commonCtx( _ctx ),
state( Network::ConnectionState::Initialized )
{
}



Channel::~Channel()
{
}



bool Channel::InitAsActive( ni_udp::IRdp * _rdp, const ni_udp::NetAddr & _remoteAddr, unsigned _remoteMux )
{
  NI_ASSERT( ( role == EChanRole::Active ) || ( role == EChanRole::ActiveDelayed ), "" );

  connection = _rdp->Connect( _remoteAddr, _remoteMux, this );
  OnRdpConnectionChange();
  if ( !connection )
    return false;

  state = Network::ConnectionState::Connecting;
  return true;
}



bool Channel::InitAsReactive( ni_udp::IRdpConnection * _conn, IDelayedAcceptCallback * _delayedAcceptCb, timer::Time _delay )
{
  connection = _conn;
  OnRdpConnectionChange();

  if ( _delayedAcceptCb )
  {
    NI_ASSERT( role == EChanRole::ReactiveDelayed, "" );
    state = Network::ConnectionState::Connecting;
    delayedAcceptCb = _delayedAcceptCb;
    commonCtx.schedule->Add( this, &Channel::OnDelayedAcceptTimeout, timer::Now() + _delay, 0 );
  }
  else
  {
    NI_ASSERT( role == EChanRole::Reactive, "" );
    state = Network::ConnectionState::Connected;
  }

  return true;
}



void Channel::PostponeMsg( const byte * _data, int _size )
{
  threading::MutexLock lock( generalMutex );
  TryPostponeMsg( _data, _size, true );
}



void Channel::OnDelayedAcceptTimeout( TScheduleAuxParam )
{
  threading::MutexLock lock( generalMutex );

  if ( !connection )
    return;

  if ( state != Network::ConnectionState::Connecting )
    return;

  ErrorTrace( "RdpChannel: Delayed accept connection timed out. src=%s, tgt=%s, uid=%d, remote=%s", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

  CloseDelayedChannel( "timeout" );
}



Network::ConnectionState::Enum Channel::GetStatus() const
{
  threading::MutexLock lock( generalMutex );

  if ( !connection )
    return Network::ConnectionState::Invalid;
  return state;
}



void Channel::Close()
{
  if( connection )
    connection->Close();

  ClearInBuffers();
  ClearOutBuffers();
}



void Channel::SendMsg( Transport::MessageBase * pMessage )
{
  byte buffer[MAX_MSG_SIZE];

  size_t size = NivalSerialize( buffer, MAX_MSG_SIZE, pMessage );
  
  NI_VERIFY( size, "", return );
  SendRaw( buffer, size );
}



Transport::MessageBase * Channel::ReceiveMsg()
{
  {
    threading::MutexLock lock( generalMutex );
    if ( state != Network::ConnectionState::Connected )
      return 0;
  }

  StrongMT<Message> msg;
  {
    threading::MutexLock lock( incomingMutex );
    if ( !incoming.empty() )
    {
      msg = incoming.front();
      incoming.pop_front();
    }
  }
  if ( !msg )
    return 0;

  Transport::MessageBase * tmsg = 0;

  FixedMemoryStream strm( msg->Data(), msg->Size() );
  int msgtype = -1;
  if ( Transport::ReadMessageType( &strm, msgtype ) )
  {
    Transport::UnpackResult::Enum unpackrc = Transport::UnpackMessage( msgtype, commonCtx.msgFactory, &strm, 65536, tmsg );
    if (unpackrc < 0)
    {
      ErrorTrace( "RdpChannel: Deserialization error. rc=%d msgtype=%d tgt=%s", (int)unpackrc, msgtype, transportAddress.target.c_str() );
      return 0;
    }
  }
  else
  {
    ErrorTrace( "RdpChannel: Can't read message type. tgt=%s", transportAddress.target.c_str() );
    return 0;
  }

  return tmsg;
}



Transport::MessageBase * Channel::PeekMsg()
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



void Channel::SendRaw( const byte * _data, int _size )
{
  if ( dumpPackets )
    MessageTrace( "RdpChannel: SendRaw. size=%s, src=%s, tgt=%s, uid=%d, remote=%s", _size, transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

  //FIXME: locking mutex at every channel write is no good
  threading::MutexLock lock( generalMutex );

  NI_VERIFY( connection, "", return );

  if ( ( state != Network::ConnectionState::Connected ) && ( state != Network::ConnectionState::Connecting ) )
    return;

  bool pending = ( state == Network::ConnectionState::Connecting );

  if ( !TryPostponeMsg( _data, _size, pending ) )
    connection->SendDatagram( _data, _size );
}



bool Channel::TryPostponeMsg( const byte * _data, int _size, bool _force )
{
  //TODO: Limit outgoing queue

  if ( _force || !outgoing.empty() )
  {
    StrongMT<Message> msg = commonCtx.allocator->AllocateMsg( _size );
    msg->FillUp( _data, _size, Transport::MessageMiscInfo() );

    outgoing.push_back( msg );
    return true;
  }

  return false;
}



bool Channel::ReceiveRaw( vector<byte> * data )
{
  Transport::MessageMiscInfo miscInfo;
  return ReceiveRaw( data, miscInfo );
}



bool Channel::ReceiveRaw( vector<byte> * data, Transport::MessageMiscInfo & _miscInfo )
{
  {
    threading::MutexLock lock( generalMutex );
    if ( state != Network::ConnectionState::Connected )
      return 0;
  }

  StrongMT<Message> msg;
  {
    threading::MutexLock lock( incomingMutex );
    if ( !incoming.empty() )
    {
      msg = incoming.front();
      incoming.pop_front();
    }
  }
  if ( !msg )
    return false;

  data->resize( msg->Size() );
  if ( msg->Size() )
    memcpy( &(*data)[0], msg->Data(), msg->Size() );

  _miscInfo = msg->MiscInfo();

  if ( dumpPackets )
    MessageTrace( "RdpChannel: ReceiveRaw. size=%s, src=%s, tgt=%s, uid=%d, remote=%s", msg->Size(), transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

  return true;
}



bool Channel::PeekRaw( vector<byte> * data )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return false;
}



Transport::Ping Channel::GetPingTime() const
{
  threading::MutexLock lock( generalMutex );

  if ( connection )
  {
    Transport::Ping result;
    int idx;
    result.value = (int)(1e3 * connection->AvgRtt( &idx ) );
    result.count = idx;
    return result;
  }

  return -1;
}



void Channel::FillDebugString( string & _outStr )
{
  threading::MutexLock lock( generalMutex );

  if ( connection )
    connection->FillDebugString( _outStr );
}



void Channel::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  threading::MutexLock lock( generalMutex );

  MessageTrace( "RdpChannel: Channel connection established. src=%s, tgt=%s, uid=%d, remote=%s", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

  NI_VERIFY( state == Network::ConnectionState::Connecting, "", return );

  if ( ( role != EChanRole::ReactiveDelayed ) && ( role != EChanRole::ActiveDelayed ) )
  {
    state = Network::ConnectionState::Connected;
    FlushOutgoingDataUnsafe();
  }
}



void Channel::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  {
    threading::MutexLock lock( generalMutex );

    MessageTrace( "RdpChannel: Channel closed. src=%s, tgt=%s, uid=%d, remote=%s", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

    state = Network::ConnectionState::Closed;
    outgoing.clear();
  }

  ClearInBuffers();
}



void Channel::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  {
    threading::MutexLock lock( generalMutex );

    MessageTrace( "RdpChannel: Channel failed. src=%s, tgt=%s, uid=%d, remote=%s", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

    state = Network::ConnectionState::Closed;
    outgoing.clear();
  }

  ClearInBuffers();
}



void Channel::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  NHPTimer::STime now;
  NHPTimer::GetTime( now );

  Transport::MessageMiscInfo misci;
  misci.queueAbsTime = now;
  misci.recvAbsTime = _absRecvTime;

  StrongMT<Message> msg = commonCtx.allocator->AllocateMsg( _size );
  msg->FillUp( _data, _size, misci );

  threading::MutexLock lock( incomingMutex );
  incoming.push_back( msg );
}



void Channel::DelayedAccept()
{
  threading::MutexLock lock( generalMutex );

  MessageTrace( "RdpChannel: Delayed channel accepted. src=%s, tgt=%s, uid=%d, remote=%s", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

  NI_VERIFY( role == EChanRole::ReactiveDelayed, "", return );
  NI_VERIFY( state == Network::ConnectionState::Connecting, "", return );

  if ( StrongMT<IDelayedAcceptCallback> locked = delayedAcceptCb.Lock() )
    locked->AcceptDelayedChannel( this );
  delayedAcceptCb = 0;

  state = Network::ConnectionState::Connected;

  FlushOutgoingDataUnsafe();
}



void Channel::CloseDelayedChannel( const char * _dbgReason )
{
  {
    threading::MutexLock lock( generalMutex );

    MessageTrace( "RdpChannel: Closing delayed channel. src=%s, tgt=%s, uid=%d, remote=%s, reason=%s, st=%d", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr, _dbgReason, (int)state );

    NI_VERIFY( role == EChanRole::ReactiveDelayed, "", return );

    state = Network::ConnectionState::Closed;

    if ( connection )
      connection->Close();

    outgoing.clear();

    StrongMT<IDelayedAcceptCallback> locked = delayedAcceptCb.Lock();
    if ( locked )
      locked->DelayedChannelAcceptFailed( this );
    delayedAcceptCb = 0;
  }

  ClearInBuffers();
}



void Channel::DelayedActiveConnectionEstablished()
{
  threading::MutexLock lock( generalMutex );

  MessageTrace( "RdpChannel: Delayed active channel established. src=%s, tgt=%s, uid=%d, remote=%s", transportAddress.source.c_str(), transportAddress.target.c_str(), transportAddress.client, remoteAddr );

  NI_VERIFY( role == EChanRole::ActiveDelayed, "", return );
  NI_VERIFY( state == Network::ConnectionState::Connecting, "", return );

  state = Network::ConnectionState::Connected;

  FlushOutgoingDataUnsafe();
}



void Channel::ClearInBuffers()
{
  threading::MutexLock lock( incomingMutex );
  incoming.clear();
}



void Channel::ClearOutBuffers()
{
  threading::MutexLock lock( generalMutex );
  outgoing.clear();
}



void Channel::FlushOutgoingDataUnsafe()
{
  while ( !outgoing.empty() )
  {
    StrongMT<Message> msg = outgoing.front();
    outgoing.pop_front();
    connection->SendDatagram( msg->Data(), msg->Size() );
  }
}



size_t Channel::NivalSerialize( void * buffer, size_t bufSize, Transport::MessageBase * tmsg )
{
  FixedMemoryStream strm( buffer, bufSize );

  int msgType = tmsg->GetTypeId();
  strm.Write( (void*)&msgType, sizeof( int ) );
  ChunklessSaver saver( &strm, 0, false );
  (*tmsg) & saver;
  return (size_t)strm.GetPosition();
}

} //namesapce rdp_transport
