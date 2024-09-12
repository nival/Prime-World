#include "RdpTest.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "RdpTransport/RdpSocketFactory.h"
#include "System/RandomInterfaceImpl.h"
#include "System/NiTimer.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"


bool TestRdpTransport::Init( const char * _bindAddr, bool _randomizePort, unsigned _buffer )
{
  bindAddr.Set( _bindAddr );

  Strong<ni_rnd::IFactory> rndFact = new ni_rnd::Factory( true );
  Strong<ni_rnd::IGenerator> rndTmp = rndFact->Produce( (unsigned)timer::GetTicks() );

  sockServer = new ni_udp::BlockingUdpSocketServer( +1, _buffer );

  StrongMT<rdp_transport::SocketFactory> sockFact = new rdp_transport::SocketFactory( sockServer, bindAddr, 1000, _randomizePort ? rndTmp : 0 );

  ni_udp::RdpOptions opts;
  opts.logEvents = ni_udp::RdpOptions::LogAllEvents;

  rdp = ni_udp::NewRdpInstance();

  if ( !rdp->Init( sockFact, opts, rndTmp, new timer::RealTimer ) )
  {
    ErrorTrace( "failed to initialize RDP" );
    rdp = 0;
    sockServer = 0;
    return false;
  }

  rnd = rndTmp;

  return true;
}









TestRdpContext::TestRdpContext( const RdpTestSettings & _sett, int _id ) :
settings( _sett ),
id( _id ),
status( EStatus::Starting ),
outgoingBurstIndex( 0 ),
incomingBurstIndex( 0 ), incomingBurstTotal( 0 ),
nextPingTime( -1 ),
nextPingIndex( 0 ),
startTime( 0 ),
lifetime( 0 )
{
}



void TestRdpContext::Init( ni_udp::IRdpConnection * _conn, TestRdpTransport * _transport )
{
  threading::MutexLock lock( mutex );

  SwitchUnsafe( EStatus::Working );

  startTime = timer::Now();

  conn = _conn;
  transport = _transport;

  nextPingTime = timer::Now() + transport->rnd->NextFloat( settings.minSendPeriod, settings.maxSendPeriod );
  nextPingIndex = 1;

  outgoingBurstIndex = 1;

  sendBuffer.resize( sizeof( RdpTestMsg::Ping ) + settings.maxDataSize );
  RdpTestMsg::Ping * msg = (RdpTestMsg::Ping *)&sendBuffer[0];
  *msg = RdpTestMsg::Ping( false );
  for ( size_t i = 0; i + 4 <= settings.maxDataSize; i += 4 )
    *(unsigned*)( (byte*)( msg + 1 ) + i ) = transport->rnd->Next();

}



void TestRdpContext::LimitLifetime()
{
  NI_VERIFY( transport->rnd, "", return );
  lifetime = transport->rnd->NextFloat( settings.minLifetime, settings.maxLifetime );
}



void TestRdpContext::SwitchUnsafe( EStatus::Enum _st )
{
  status = _st;
}



void TestRdpContext::Fail()
{
  if ( conn )
    conn->Close();

  SwitchUnsafe( EStatus::Failed );
}



void TestRdpContext::SendSingleBurstMsg()
{
  RdpTestMsg::HelloBurst msg;
  msg.index = outgoingBurstIndex;
  msg.total = settings.helloBurstLength;

  ++outgoingBurstIndex;

  conn->SendDatagram( &msg, sizeof( msg ) );
}



void TestRdpContext::SendSinglePingMsg( timer::Time _now )
{
  size_t dataSize = transport->rnd->Next( settings.maxDataSize );

  int index = nextPingIndex++;

  NI_ASSERT( sizeof( RdpTestMsg::Ping ) + dataSize <= sendBuffer.size(), "" );

  RdpTestMsg::Ping * msg = (RdpTestMsg::Ping *)&sendBuffer[0];
  msg->index = index;
  msg->sum = 0;
  msg->factor = 1;
  const byte * data = (const byte *)( msg + 1 );
  for( size_t i = 0; i < dataSize; ++i )
  {
    byte b = data[i];
    msg->sum += (unsigned)b;
    msg->factor = msg->factor ^ ( (unsigned)b + i );
  }

  MessageTrace( "Sending ping. id=%d, index=%d, size=%d, sum=%d, factor=%d", id, index, dataSize, msg->sum, msg->factor );

  conn->SendDatagram( msg, sizeof( RdpTestMsg::Ping ) + dataSize );

  pingLog[index] = _now;
}



TestRdpContext::EStatus::Enum TestRdpContext::Poll()
{
  threading::MutexLock lock( mutex );

  timer::Time now = timer::Now();

  if ( ( status != EStatus::Finished ) && ( status != EStatus::Failed ) )
  {
    if ( lifetime )
      if ( now > startTime + lifetime )
      {
        MessageTrace( "Lifetime ended. id=%d", id );

        if ( status == EStatus::Working )
        {
          if ( conn )
            conn->Close();
          SwitchUnsafe( EStatus::Finished );
        }
        else
          Fail();
      }
  }

  if ( status == EStatus::Working )
  {
    timer::Time now = timer::Now();

    if ( outgoingBurstIndex <= settings.helloBurstLength )
      SendSingleBurstMsg();

    if ( now > nextPingTime )
    {
      nextPingTime = timer::Now() + transport->rnd->NextFloat( settings.minSendPeriod, settings.maxSendPeriod );
      SendSinglePingMsg( now );
    }
  }

  return status;
}



void TestRdpContext::OnConnectionEstablished( ni_udp::IRdpConnection * _conn )
{
  MessageTrace( "Connection established. id=%d", id );
}



void TestRdpContext::OnConnectionClosed( ni_udp::IRdpConnection * _conn )
{
  MessageTrace( "Connection closed. id=%d", id );

  threading::MutexLock lock( mutex );

  SwitchUnsafe( EStatus::Finished );
}



void TestRdpContext::OnConnectionFailed( ni_udp::IRdpConnection * _conn )
{
  MessageTrace( "Connection failed. id=%d", id );

  threading::MutexLock lock( mutex );

  SwitchUnsafe( EStatus::Failed );
}



void TestRdpContext::OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  MessageTrace( "Datagram. id=%d, size=%d, recv_rm=%.2f", id, _size, 1e3 * _absRecvTime );

  threading::MutexLock lock( mutex );

  if ( status != EStatus::Working )
  {
    ErrorTrace( "Unexpected datagram. id=%d. status=%d", id, (int)status );
    Fail();
    return;
  }

  if ( _size < sizeof( RdpTestMsg::Header ) )
  {
    ErrorTrace( "Small datagram. id=%d, size=%d", id, _size );
    Fail();
    return;
  }

  const RdpTestMsg::Header * hdr = (RdpTestMsg::Header *)_data;

  if ( hdr->openMarker != RdpTestMsg::Header::OpenMarker )
  {
    ErrorTrace( "Wrong datagram hdr. id=%d, size=%d", id, _size );
    Fail();
    return;
  }

  MessageTrace( "Message type. id=%d, type=%d, idx=%d", id, hdr->type, hdr->index );

  if ( !OnMessage( hdr, _size ) )
  {
    ErrorTrace( "Context failed. id=%d", id );
    Fail();
  }
}



bool TestRdpContext::OnMessage( const RdpTestMsg::Header * _hdr, size_t _size )
{
  if ( _hdr->type == RdpTestMsg::TypePing )
  {
    if ( incomingBurstIndex < incomingBurstTotal )
    {
      ErrorTrace( "Ping before last hello burst msg. id=%d, index=%d/%d", id, incomingBurstIndex, incomingBurstTotal );
      return false;
    }

    RdpTestMsg::Ping * msg = (RdpTestMsg::Ping *)_hdr;
    const byte * data = (const byte * )( msg + 1 );
    size_t size = _size - sizeof( RdpTestMsg::Ping );

    MessageTrace( "Got ping. id=%d, index=%d, size=%d, sum=%d, factor=%d", id, msg->index, size, msg->sum, msg->factor );

    unsigned sum = 0, factor = 1;
    for( size_t i = 0; i < size; ++i )
    {
      byte b = data[i];
      sum += (unsigned)b;
      factor = factor ^ ( (unsigned)b + i );
    }

    if ( ( sum != msg->sum ) || ( factor != msg->factor ) )
    {
      ErrorTrace( "Data checksum failed. id=%d, index=%d", id, msg->index );
      return false;
    }

    RdpTestMsg::Ping pong( true );
    pong.index = msg->index;

    conn->SendDatagram( &pong, sizeof( pong ) );
    return true;
  }
  else if ( _hdr->type == RdpTestMsg::TypePong )
  {
    if ( incomingBurstIndex < incomingBurstTotal )
    {
      ErrorTrace( "Ping before last hello burst msg. id=%d, index=%d/%d", id, incomingBurstIndex, incomingBurstTotal );
      return false;
    }

    RdpTestMsg::Ping * msg = (RdpTestMsg::Ping *)_hdr;

    PingLog::iterator it = pingLog.find( msg->index );
    if ( it == pingLog.end() )
    {
      ErrorTrace( "Unknown ping id=%d, index=%d", id, msg->index );
      return false;
    }

    MessageTrace( "Got pong. id=%d, index=%d, rtt=%.1f", id, msg->index, 1e3 * ( timer::Now() - it->second ) );
    pingLog.erase( it );
    return true;
  }
  else if ( _hdr->type == RdpTestMsg::TypeBurst )
  {
    RdpTestMsg::HelloBurst * msg = (RdpTestMsg::HelloBurst *)_hdr;

    if ( !incomingBurstTotal )
    {
      MessageTrace( "Got first hello burst msg. id=%d, total=%d", id, msg->total );
      incomingBurstTotal = msg->total;
      incomingBurstIndex = 1;
    }

    if ( msg->index != incomingBurstIndex )
    {
      ErrorTrace( "Wrong hello burst msg index. id=%d, index=%d(%d)/%d", id, msg->index, incomingBurstIndex, incomingBurstTotal );
      return false;
    }

    if ( incomingBurstIndex > incomingBurstTotal )
    {
      ErrorTrace( "Too many hello burst msg. id=%d, index=%d/%d", id, incomingBurstIndex, incomingBurstTotal );
      return false;
    }

    MessageTrace( "Hello burst msg. id=%d, index=%d, total=%d", id, incomingBurstIndex, incomingBurstTotal );
    ++incomingBurstIndex;
    return true;
  }

  return false;
}
