#include "stdafx.h"
#include "SockSrvLocal.h"
#include "System/NiTimer.h"
#include "System/InlineProfiler.h"


namespace ni_udp
{

LocalSocketServer::LocalSocketServer( timer::ITimer * _clock, bool _verbose ) :
verbose( _verbose ),
defaultDelay( 0.1 ),
clock( _clock ),
random( 100500 ),
packetLossProbability( 0 )
{}



StrongMT<ISocket> LocalSocketServer::Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData )
{
  threading::MutexLock lock( mainMutex );

  WeakMT<LocalSocket> & s = sockets[_bindAddr];

  StrongMT<LocalSocket> locked = s.Lock();
  NI_ASSERT( !locked.Valid(), "" );

  DebugTrace( "Opening local socket. addr=%d, aux=%d", _bindAddr, _auxData );

  StrongMT<LocalSocket> sock = new LocalSocket( clock, this, _bindAddr, _cb, _auxData, verbose );
  s = sock;
  return sock.Get();
}



void LocalSocketServer::Poll()
{
  NI_PROFILE_FUNCTION;

  DatagramBuffer buffer;
  {
    NI_PROFILE_BLOCK( "Swap" );
    threading::MutexLock lock( incomingMutex );
    incomingBuffer.swap( buffer );
  }

  threading::MutexLock lock( mainMutex );

  while ( !buffer.empty() )
  {
    NI_PROFILE_BLOCK( "Datagram processing" );
    const NetAddr & _destAddr = buffer.front().first;
    StrongMT<LocalDatagram> dg = buffer.front().second;

    Sockets::iterator it = sockets.find( _destAddr );
    if ( it != sockets.end() )
      if ( StrongMT<LocalSocket> locked = it->second.Lock() )
        locked->Post( dg );

    buffer.pop_front();
  }

  for ( Sockets::iterator it = sockets.begin(); it != sockets.end(); )
    if ( StrongMT<LocalSocket> locked = it->second.Lock() )
    {
      locked->Poll();
      ++it;
    }
    else
      it = sockets.erase( it );
}



void LocalSocketServer::Post( const NetAddr & _destAddr, LocalDatagram * _dg )
{
  threading::MutexLock lock( incomingMutex );

  timer::Time delay = 0;

  if ( !DistortDatagram( delay ) )
    return;

  _dg->SetDeliveryTime( clock->Now() + delay );

  incomingBuffer.push_back( DatagramBuffer::value_type( _destAddr, _dg ) );
}



bool LocalSocketServer::DistortDatagram( timer::Time & _delay )
{
  _delay = defaultDelay;

  for ( DelayPattern::iterator it = delayPattern.begin(); it != delayPattern.end(); )
  {
    if ( it->first > 0 )
    {
      --(it->first);
      ++it;
      continue;
    }

    if ( !it->first )
    {
      DebugTrace( "OOPS! Delaying packet. delay=%.2f", it->second );
      _delay += it->second;
    }
    
    it = delayPattern.erase( it );
  }

  if ( !lossPatern.empty() )
  {
    int deliverOk = lossPatern.front();
    lossPatern.pop_front();
    if ( !deliverOk )
    {
      DebugTrace( "OOPS! Packet is lost" );
      return false;
    }
  }

  if ( packetLossProbability > 0 )
  {
    int r = random.Next( 0, 10000 );
    if ( r < packetLossProbability )
    {
      DebugTrace( "OOPS! Packet is lost" );
      return false;
    }
  }

  return true;
}



void LocalSocketServer::AddIncomingLossPattern( const char * _pattern )
{
  threading::MutexLock lock( incomingMutex );

  for ( const char * p = _pattern; *p; ++p )
    if ( *p == '0' )
      lossPatern.push_back( 0 );
    else if ( *p == '1' )
      lossPatern.push_back( 1 );
    else
      NI_ALWAYS_ASSERT( "" );
}



void LocalSocketServer::AddPacketDelay( int _pktIdx, timer::Time _addDelay )
{
  threading::MutexLock lock( incomingMutex );

  for ( DelayPattern::iterator it = delayPattern.begin(); it != delayPattern.end(); ++it )
    if ( it->first == _pktIdx )
    {
      it->second += _addDelay;
      return;
    }

  delayPattern.push_back( std::pair<int, timer::Time>( _pktIdx, _addDelay ) );
}



void LocalSocketServer::SetRandomPacketLoss( float _percent )
{
  threading::MutexLock lock( incomingMutex );

  packetLossProbability = 10000.0 * _percent * 1e-2;
}











LocalSocket::LocalSocket( timer::ITimer * _clock, LocalSocketServer * _sv, const NetAddr & _bindAddr, ISocketCallback * _cb, TAuxData _auxData, bool _verbose ) :
verbose( _verbose ),
bindAddr( _bindAddr ),
auxData( _auxData ),
clock( _clock ),
opened( true ),
server( _sv ),
callback( _cb ),
lastStatReport( _clock->Now() ),
statSamplesCount( 0 ),
queLenSum( 0 ),
maxQueLen( 0 ),
totalPackets( 0 )
{
}



LocalSocket::~LocalSocket()
{
}



ESocketStatus::Enum LocalSocket::Status()
{
  threading::MutexLock lock( mutex );
  return opened ? ESocketStatus::Ready : ESocketStatus::Closed;
}



void LocalSocket::Close()
{
  threading::MutexLock lock( mutex );
  opened = false;
}



void LocalSocket::SendDatagram( const NetAddr & _destAddr, const void * _data, size_t _size )
{
  StrongMT<LocalSocketServer> srv = server.Lock();
  if ( !srv )
    return;

  if ( verbose )
    DebugTrace( "Sending datagram. dest_addr=%d, size=%d, aux=%d", _destAddr, _size, auxData );

  StrongMT<LocalDatagram> dg = new LocalDatagram( _data, _size, bindAddr );
  srv->Post( _destAddr, dg );
}



bool LocalSocket::Poll()
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  StatReport();

  timer::Time now = clock->Now();

  for ( PostQueue::iterator it = queue.begin(); it != queue.end(); )
  {
    StrongMT<LocalDatagram> dg = *it;
    if ( now >= dg->DeliveryTime() )
    {
      if ( StrongMT<ISocketCallback> cb = callback.Lock() )
      {
        if ( verbose )
          DebugTrace( "Delivering datagram. src_addr=%d, dest_addr=%d, size=%d, aux=%d", dg->SrcAddr(), bindAddr, dg->Size(), auxData );
        cb->OnDatagram( this, dg->SrcAddr(), dg->Bytes(), dg->Size(), now );
      }
      it = queue.erase( it );
    }
    else
      ++it;
  }

  return opened;
}



void LocalSocket::Post( LocalDatagram * _dg )
{
  threading::MutexLock lock( mutex );

  if ( verbose )
    DebugTrace( "Datagram queued. src_addr=%d, dest_addr=%d, size=%d, aux=%d", _dg->SrcAddr(), bindAddr, _dg->Size(), auxData );
  queue.push_back( _dg );

  ++totalPackets;
}



void LocalSocket::StatReport()
{
  queLenSum += queue.size();
  maxQueLen = Max( maxQueLen, queue.size() );
  ++statSamplesCount;

  if ( clock->Now() < lastStatReport + 5.0 )
    return;

  timer::Time now = clock->Now();

  timer::Time delta = now - lastStatReport;
  lastStatReport = now;

  float avgQue = queLenSum / statSamplesCount;
  float pktPerSec = totalPackets / delta * 1e-3;

  DebugTrace( "Local socket statistics. addr=%s, avg_que=%.1f, max_que=%d, pkt_per_sec=%.2fk", bindAddr, avgQue, maxQueLen, pktPerSec );

  statSamplesCount = 0;
  queLenSum = 0;
  maxQueLen = 0;
  totalPackets = 0;
}

} //namespace ni_udp
