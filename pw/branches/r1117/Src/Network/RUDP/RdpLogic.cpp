#include "stdafx.h"
#include "RdpLogic.h"
#include "RdpProto.h"
#include "RdpPacket.h"
#include "RdpListenContext.h"
#include "RdpConnection.h"
#include "RdpWriter.h"
#include "RdpStats.h"
#include "System/NiTimer.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"
#include "System/InlineProfiler.h"

NI_DEFINE_REFCOUNT( ni_udp::RdpConnStats );
NI_DEFINE_REFCOUNT( ni_udp::IRdpPacketAllocator );

namespace ni_udp
{

RdpLogic::RdpLogic( const RdpOptions & _opt, ni_rnd::IGenerator * _rnd, timer::ITimer * _clock ) :
rnd( _rnd ),
clock( _clock ),
now( _clock->Now() ),
tempDbgNextDump( 30.0 ),
tempDbgDgSent( 0 ), tempDbgDgRecv( 0 ), tempDbgWarn( 0 ), tempDbgErr( 0 ), tempDbgRetr( 0 ), tempDbgDelivered( 0 ),
tempDbgPollHisto( lifehack::EasyVector<double>( 0.0, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0 ) ),
tempDbgSleepHisto( lifehack::EasyVector<double>( 0.0, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0 ) )
{
  globalStats = new RdpStats;
  ctx.options = new RdpOptionsObject( _opt );
  ctx.stats = new RdpConnStats( globalStats );

  const unsigned windowLimit = proto::SeqIndexClamp / 3;
  if ( ctx.options->cc.maxWindowSize > windowLimit )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogMajorEvents ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "RDP max window size capped. cap=%d, requested_size=%d", windowLimit, ctx.options->cc.maxWindowSize );
    ctx.options->cc.maxWindowSize = windowLimit;
  }

  incomingPackets.reserve( _opt.incomingBufferPreallocate );
  incomingPacketsBuffer.reserve( _opt.incomingBufferPreallocate );
}



RdpLogic::~RdpLogic()
{
  for ( IncomingPackets::iterator it = incomingPackets.begin(); it != incomingPackets.end(); ++it )
    if ( it->data )
    {
      ctx.allocator->DeallocatePkt( it->data );
      it->data = 0;
    }
  incomingPackets.clear();

  for ( IncomingPackets::iterator it = incomingPacketsBuffer.begin(); it != incomingPacketsBuffer.end(); ++it )
    if ( it->data )
    {
      ctx.allocator->DeallocatePkt( it->data );
      it->data = 0;
    }
  incomingPacketsBuffer.clear();
}



void RdpLogic::Setup( ISocket * _socket, IRdpPacketAllocator * _pktAllocator )
{
  socket = _socket;
  localAddr = socket->LocalAddr();

  ctx.allocator = _pktAllocator;

  ephemeralMuxes = new RdpEphemeralMuxes( ctx.options, rnd );

  ctx.writer = new RdpWriter( socket, ctx.stats );
}



void RdpLogic::Cleanup()
{
  if ( socket )
    socket->Close();
  socket = 0;
}



void RdpLogic::Work( volatile bool & isRunning )
{
  NI_PROFILE_THREAD;

  while ( isRunning )
  {
    ParallelPoll();
  }
}

inline LONG TempDbgGetDelta( volatile LONG _val, LONG & _var )
{
  LONG val = _val;
  LONG delta = val - _var;
  _var = val;
  return delta;
}

void RdpLogic::ParallelPoll()
{
  NI_PROFILE_FUNCTION;

  timer::Time beforeSleep = clock->Now();

  {
    NI_PROFILE_HEAVY_BLOCK( "Sleep" );
    threading::Sleep( 1 );
  }

  timer::Time _now = clock->Now();
  tempDbgSleepHisto.AddData( 1e3 * ( _now - beforeSleep ) );

  if ( _now > tempDbgNextDump )
  {
    tempDbgNextDump = _now + 30.0;

    LONG dgSent = TempDbgGetDelta( ctx.stats->packetsWritten, tempDbgDgSent );
    LONG dgRecv = TempDbgGetDelta( ctx.stats->packetsRecieved, tempDbgDgRecv );
    LONG warn = TempDbgGetDelta( ctx.stats->warnings, tempDbgWarn );
    LONG err = TempDbgGetDelta( ctx.stats->errors, tempDbgErr );
    LONG retran = TempDbgGetDelta( ctx.stats->retransmits, tempDbgRetr );
    LONG delivered = TempDbgGetDelta( ctx.stats->datagramsDelivered, tempDbgDelivered );

    const LONG total = delivered + retran;
    double lossEst = total ? ( 100.0 * retran / total ) : 0;

    MessageTrace( "RDP perfomance debug. dg_sent=%d, dg_recv=%d, warn=%d, err=%d, retr=%d, loss=%.1f", dgSent, dgRecv, warn, err, retran, lossEst );
    MessageTrace( "RDP perfomance debug. polls=%g", tempDbgPollHisto );
    MessageTrace( "RDP perfomance debug. sleep=%g", tempDbgSleepHisto );

    tempDbgPollHisto.ResetData();
    tempDbgSleepHisto.ResetData();
  }

  {
    threading::MutexLock lock( mutex );
    now = _now;
  }

  ParseIncomingPackets();

  {
    threading::MutexLock lock( mutex );
    PollConnections();
    PollListenContexts();
  }

  tempDbgPollHisto.AddData( 1e3 * ( clock->Now() - _now ) );
}



IRdpListenContext * RdpLogic::StartListen( unsigned _mux, IRdpListenContextCallback * _cb )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _cb, "", return 0 );

  threading::MutexLock lock( mutex );

  StrongMT<RdpListenContext> & listenCtx = listenContexts[_mux];

  if ( listenCtx )
  {
    ErrorTrace( "Address is already listening. addr=%s, mux=%d", localAddr, _mux );
    return 0;
  }

  if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
    MessageTrace( "New listen context. addr=%s, mux=%d", localAddr, _mux );

  listenCtx = new RdpListenContext( this, ctx, _mux, _cb );

  return new RdpListenContextProxy( listenCtx );
}



void RdpLogic::StopListen( RdpListenContext * _listenCtx )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  ListenContexts::iterator it = listenContexts.find( _listenCtx->Mux() );
  if( it != listenContexts.end() )
    listenContexts.erase( it );
}



void RdpLogic::IncomingHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx, IRdpListenContextCallback * _listenCallback )
{
  NI_PROFILE_FUNCTION;

  if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
    MessageTrace( "New incoming connection. local=%s, descr=%s, seq=%d", localAddr, _descr, _seqIdx );

  threading::MutexLock lock( mutex );

  StrongMT<RdpConnection> & conn = connections[_descr];
  if ( conn.Valid() )
  {
    ErrorTrace( "Duplicated connection descriptor for incoming connections. descr=%s", _descr );
    NI_ALWAYS_ASSERT( "" ); //internal error
    return;
  }

  conn = new RdpConnection( now, ctx, _descr );
  StrongMT<RdpConnectionProxy> proxy = new RdpConnectionProxy( conn );

  conn->SetupAsReactiveSide1( proxy, _seqIdx );

  if ( StrongMT<IRdpConnectionCallback> callback = _listenCallback->OnConnectionEstablished( proxy, _descr.remote ) )
  {
    conn->SetupAsReactiveSide2( callback );
    if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
      MessageTrace( "Incoming connection successfully initialized. local=%s, descr=%s, seq=%d", localAddr, _descr, _seqIdx );
    return;
  }
  else
    ErrorTrace( "Listen context callback returned null. descr=%s", _descr );

  conn->Close();
}



//Must be called under a mutex
unsigned RdpLogic::ReallocateLocalEphemeralMux( const ConnDescriptor & _descr )
{
  NI_PROFILE_FUNCTION;

  Connections::const_iterator it = connections.find( _descr );
  if ( it == connections.end() )
  {
    WarningTrace( "Unknown connection descriptor to relocate. local_addr=%s, descr=%s", localAddr, _descr );
    return 0;
  }

  StrongMT<RdpConnection> conn = it->second;

  unsigned newMux = ephemeralMuxes->AllocateMux( now );
  if ( !newMux )
    return 0;

  ephemeralMuxes->FreeMux( conn->ConnDescr().localMux, now + ctx.options->shutdownTimeWait );

  conn->ChangeLocalMuxUnsafe( newMux );

  StrongMT<RdpConnection> & newSlot = connections[conn->ConnDescr()];
  NI_ASSERT( !newSlot.Valid(), "" );
  newSlot = conn;

  connections.erase( it );

  return newMux;
}



IRdpConnection * RdpLogic::StartConnection( const NetAddr & _remoteAddr, unsigned _mux, IRdpConnectionCallback * _cb )
{
  NI_PROFILE_FUNCTION;

  if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
    MessageTrace( "Starting outgoing connection. local=%s, remote=%s, mux=%d", localAddr, _remoteAddr, _mux );

  threading::MutexLock lock( mutex );

  unsigned ephemeralMux = ephemeralMuxes->AllocateMux( now );
  if ( !ephemeralMux )
  {
    ErrorTrace( "Out of ephemeral mux! local=%s, remote=%s, mux=%d", localAddr, _remoteAddr, _mux );
    return 0;
  }

  if ( listenContexts.find( ephemeralMux ) != listenContexts.end() )
  {
    ErrorTrace( "Ephemeral mux is already listening. local=%s, remote=%s, mux=%d", localAddr, _remoteAddr, ephemeralMux );
    return 0;
  }

  ConnDescriptor descr( _remoteAddr, ephemeralMux, _mux );

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "New connection details. local_addr=%s, descr=%s", localAddr, descr );

  StrongMT<RdpConnection> & conn = connections[descr];

  if ( conn.Valid() )
  {
    ErrorTrace( "Duplicate outgoing connection descriptor. local_addr=%s, descr=%s", localAddr, descr );
    return 0;
  }

  conn = new RdpConnection( now, ctx, descr );
  
  RdpConnectionProxy * proxy = new RdpConnectionProxy( conn );

  conn->SetupAsActiveSide( proxy, _cb, new RdpActiveHandshake( ctx, descr, conn, rnd->Next( proto::SeqIndexClamp ), now ) );

  return proxy;
}



void RdpLogic::PollConnections()
{
  NI_PROFILE_FUNCTION;

  for ( Connections::iterator it = connections.begin(); it != connections.end(); )
  {
    RdpConnection * conn = it->second;
    if ( conn->Poll( now ) )
      ++it;
    else
    {
      if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
        MessageTrace( "Connection removed. local_addr=%s, descr=%s", localAddr, conn->ConnDescr() );

      if ( conn->ActiveSide() )
      {
        unsigned ephemeralMux = conn->ConnDescr().localMux;
        ephemeralMuxes->FreeMux( ephemeralMux, now + ctx.options->shutdownTimeWait );
      }
      it = connections.erase( it );
    }
  }
}



void RdpLogic::PollListenContexts()
{
  NI_PROFILE_FUNCTION;

  for ( ListenContexts::iterator it = listenContexts.begin(); it != listenContexts.end(); )
  {
    StrongMT<RdpListenContext> ctx = it->second;
    if ( ctx->Poll( now ) )
      ++it;
    else
      it = listenContexts.erase( it );
  }
}



void RdpLogic::OnDatagram( ISocket * _socket, const NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  NI_PROFILE_FUNCTION;

  ctx.stats->Inc( &RdpStats::bytesRecieved, _size );
  ctx.stats->Inc( &RdpStats::packetsRecieved );

  if ( _size < sizeof ( proto::Header ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogMajorEvents ) || ( ctx.options->logEvents & RdpOptions::LogErrors ) )
      ErrorTrace( "Datagram is too small. size=%d, remote=%s", _size, _remoteAddr );
    ctx.stats->Inc( &RdpStats::errors );
    return;
  }

  const proto::Header * hdr = (const proto::Header * )_data;

  const proto::EPktType::Enum pktType = (proto::EPktType::Enum)hdr->type;
  ConnDescriptor descr( _remoteAddr, hdr->destMux, hdr->sourceMux );

  if ( ctx.options->logEvents & RdpOptions::LogPackets )
    MessageTrace( "Recieved packet. local_addr=%s, descr=%s, size=%d, type=%d, seq=%d, remote=%s", localAddr, descr, _size, PktTypeToString( pktType ), hdr->index, descr.remote );

  {
    threading::MutexLock lock( incomingMutex );

    if ( incomingPackets.size() >= ctx.options->incomingBufferHardlimit )
    {
      CriticalTrace( "Incoming buffer overflow. size=%d, limit=%d", incomingPackets.size(), ctx.options->incomingBufferHardlimit );
      ctx.stats->Inc( &RdpStats::errors );
      return;
    }

    incomingPackets.push_back( IncomingPkt( pktType, hdr->index, descr ) );

    if ( ( pktType == proto::EPktType::Datagram ) || ( pktType == proto::EPktType::DatagramChunk ) || ( pktType == proto::EPktType::DatagramRaw ) || ( pktType == proto::EPktType::Shutdown ) )
    {
      const void * payload = hdr + 1;
      size_t payloadSize = _size - sizeof( *hdr );

      StrongMT<RdpPacket> newPkt = ctx.allocator->AllocatePkt( payloadSize );
      newPkt->Setup( pktType, hdr->sourceMux, hdr->destMux, hdr->index, payload, payloadSize );
      newPkt->SetAbsReceiveTime( _absRecvTime );
      incomingPackets.back().data = newPkt;
    }
  }
}



void RdpLogic::ParseIncomingPackets()
{
  NI_PROFILE_FUNCTION;

  NI_ASSERT( incomingPacketsBuffer.empty(), "" );

  {
    threading::MutexLock lock( incomingMutex );
    incomingPackets.swap( incomingPacketsBuffer );
  }

  threading::MutexLock lock( mutex );

  for ( size_t i = 0; i < incomingPacketsBuffer.size(); ++i )
  {
    IncomingPkt & slot = incomingPacketsBuffer[i];

    ParsePacket( slot );

    if ( slot.data )
    {
      ctx.allocator->DeallocatePkt( slot.data );
      slot.data = 0;
    }
  }

  incomingPacketsBuffer.clear();
}



void RdpLogic::ParsePacket( const IncomingPkt & _slot )
{
  NI_PROFILE_FUNCTION;

  const proto::EPktType::Enum pktType = _slot.pktType;
  const unsigned seqIdx = _slot.seqIndex;
  const ConnDescriptor & descr = _slot.descr;

  if ( ctx.options->logEvents & RdpOptions::LogPackets )
    MessageTrace( "Processing packet. local_addr=%s, descr=%s, type=%d, size=%d, seq=%d", localAddr, descr, PktTypeToString( pktType ), _slot.data ? _slot.data->Size() : 0, seqIdx );

  switch( pktType )
  {
    case proto::EPktType::HandshakeInit:
      on_HandshakeInit( descr, seqIdx );
      break;

    case proto::EPktType::HandshakeInitAck:
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        if ( conn->on_pkt_InitAck( seqIdx ) )
          break;
      if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "INIT_ACK ignored. local_addr=%s, descr=%s, seq=%d", localAddr, descr, seqIdx );
      break;

    case proto::EPktType::HandshakeAck:
      if ( StrongMT<RdpListenContext> listenCtx = FindListenCtxNoLock( descr ) )
        listenCtx->on_pkt_HandshakeAck( descr, seqIdx );
      break;

    case proto::EPktType::HandshakeRefused:
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        if ( conn->on_pkt_Refused( seqIdx ) )
          break;
      if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "REFUSED ignored. local_addr=%s, descr=%s, seq=%d", localAddr, descr, seqIdx );
      break;

    case proto::EPktType::RetryHandshake:
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        if ( conn->on_pkt_RetryHandshake( seqIdx, this ) )
          break;
      if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "RETRY_HS ignored. local_addr=%s, descr=%s, seq=%d", localAddr, descr, seqIdx );
      break;

    case proto::EPktType::DatagramRaw:
      NI_VERIFY( _slot.data, "", break );
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        conn->on_pkt_DatagramRaw( _slot.data );
      break;

    case proto::EPktType::Datagram:
    case proto::EPktType::DatagramChunk:
    case proto::EPktType::Shutdown:
      NI_VERIFY( _slot.data, "", break );
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        conn->on_pkt_Datagram( _slot.data );
      break;

    case proto::EPktType::DatagramAck:
    case proto::EPktType::ShutdownAck:
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        conn->on_pkt_DatagramAck( seqIdx, pktType );
      break;

    case proto::EPktType::Ping:
    case proto::EPktType::Pong:
      if ( StrongMT<RdpConnection> conn = FindConnNoLock( descr ) )
        conn->on_pkt_Ping( seqIdx, pktType );
      break;

    default:
      if ( ( ctx.options->logEvents & RdpOptions::LogPackets ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "Unknown packet type. type=%d, remote=%s", (int)pktType, descr.remote );
      ctx.stats->Inc( &RdpStats::warnings );
  }
}



void RdpLogic::on_HandshakeInit( const ConnDescriptor & _descr, unsigned _seqIdx )
{
  NI_PROFILE_FUNCTION;

  if ( ctx.options->logEvents & RdpOptions::LogPackets )
    MessageTrace( "Recieved INIT. local_addr=%s, descr=%s, seq=%d", localAddr, _descr, _seqIdx );

  Connections::iterator connIt = connections.find( _descr );
  if ( connIt != connections.end() )
  {
    ctx.stats->Inc( &RdpStats::warnings );
    WarningTrace( "Duplicate incoming connection descriptor. local_addr=%s, descr=%s", localAddr, _descr );
    ctx.writer->Send( _descr, proto::EPktType::RetryHandshake, _seqIdx );
    return;
  }

  if ( RdpListenContext * listenCtx = RdpLogic::FindListenCtxNoLock( _descr ) )
    listenCtx->on_pkt_HandshakeInit( _descr, _seqIdx );
  else
  {
    if ( ctx.options->logEvents & RdpOptions::LogHandshake )
      MessageTrace( "No listeners for incoming connection request. descr=%s, seq=%d", _descr, _seqIdx );
    ctx.writer->Send( _descr, proto::EPktType::HandshakeRefused, _seqIdx );
  }
}



RdpConnection * RdpLogic::FindConnNoLock( const ConnDescriptor & _descr ) const
{
  NI_PROFILE_HEAVY_FUNCTION;

  Connections::const_iterator it = connections.find( _descr );
  if ( it == connections.end() )
  {
    WarningTrace( "Unknown connection descriptor. local_addr=%s, descr=%s", localAddr, _descr );
    return 0;
  }

  return it->second;
}



RdpListenContext * RdpLogic::FindListenCtxNoLock( const ConnDescriptor & _descr ) const
{
  NI_PROFILE_HEAVY_FUNCTION;

  ListenContexts::const_iterator it = listenContexts.find( _descr.localMux );
  if ( it == listenContexts.end() )
  {
    WarningTrace( "Unknown mux index. local_addr=%s, descr=%s", localAddr, _descr );
    return 0;
  }

  return it->second;
}

} //namespace ni_udp
