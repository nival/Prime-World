#include "stdafx.h"
#include "Rdp.h"
#include "RdpLogic.h"
#include "RdpPacket.h"
#include "RdpPacketPool.h"


namespace ni_udp
{

RdpOptions::RdpOptions() :
firstEphemeralMux( 32768 ),
lastEphemeralMux( 65535 ),
handshakeTotalTimeout( 10.0f ),
handshakeRetryTimeout( 3.0f ),
handshakeMaxTries( 3 ),
shutdownTimeWait( 10.0f ),
initInPacketsQueue( 384 ),
initOutPacketsQueue( 512 ),
maxInQueuePackets( 1024 ),
maxInQueueSize( 128 * 1024 ),
maxOutQueuePackets( 4096 ),
maxOutQueueSize( 2 * 1024 * 1024 ),
maxDataSegment( 512 ),
retransmitLimit( 10 ),
pingPeriod( 15.0f ),
logEvents( LogAllEvents ),
incomingBufferPreallocate( 1024 ),
incomingBufferHardlimit( 65536 ),
outgoingBufferPreallocate( 1024 ),
outgoingBufferHardlimit( 65536 ),
usePoolAllocator( true ),
logicThreadPriority( 1 ) //THREAD_PRIORITY_ABOVE_NORMAL
{
}



RdpCcOptions::RdpCcOptions() :
historyLen( 7 ),
initWindowSize( 2 ), maxWindowSize( 256 ),
windowSizeInc( 1 ), windowSizeDec( 4 ),
initRetransmitTime( 0.3f ), maxRetransmitTime( 4.0f ),
rttoAdditiveMargin( 0.01f ), rttoMultiplicativeMargin( 1.2f ),
rttoFactor( 0.075f )
{
}




IRdp * NewRdpInstance()
{
  return new Rdp( false );
}




Rdp::Rdp( bool _unitTestMode ) :
unitTestMode( _unitTestMode )
{
}



Rdp::~Rdp()
{
  if ( workerThread )
    MessageTrace( "Stopping RDP thread. thread_id=%u", workerThread->Id() );
  workerThread = 0;

  //Force correct socket object cleanup / thread stop
  if ( logic )
    logic->Cleanup();
  logic = 0;
}



void Rdp::UnitTestPoll()
{
  logic->ParallelPoll();
}



bool Rdp::Init( IRdpSocketFactory * _socketFactory, const RdpOptions & _opt, ni_rnd::IGenerator * _rnd, timer::ITimer * _clock )
{
  NI_VERIFY( !workerThread && !logic, "", return false );

  StrongMT<RdpLogic> l = new RdpLogic( _opt, _rnd, _clock );

  StrongMT<ISocket> sock = _socketFactory->OpenSocket( l );
  if ( !sock )
    return false;

  StrongMT<IRdpPacketAllocator> allocator;
  if ( _opt.usePoolAllocator )
  {
    PacketPoolAllocator * poolAllctr = new PacketPoolAllocator;
    poolAllctr->CreatePool( 16, 256 );
    poolAllctr->CreatePool( 32, 256 );
    poolAllctr->CreatePool( 64, 256 );
    poolAllctr->CreatePool( 128, 256 );
    poolAllctr->CreatePool( 256, 256 );
    poolAllctr->CreatePool( 1024, 128 );
    poolAllctr->CreatePool( 4096, 128 );
    allocator = poolAllctr;
  }
  else
    allocator = new HeapPacketAllocator;
  l->Setup( sock, allocator );

  if ( !unitTestMode )
  {
    workerThread = new threading::JobThread( l, "RdpLogic" );
    workerThread->SetPriority( _opt.logicThreadPriority );
  }

  logic = l;

  return true;
}



IRdpConnection * Rdp::Connect( const NetAddr & _remote, unsigned _mux, IRdpConnectionCallback * _cb )
{
  return logic->StartConnection( _remote, _mux, _cb );
}



IRdpListenContext * Rdp::Listen( unsigned _mux, IRdpListenContextCallback * _cb )
{
  return logic->StartListen( _mux, _cb );
}

} //namespace ni_udp
