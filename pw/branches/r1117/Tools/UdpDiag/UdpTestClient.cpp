#include "UdpTestClient.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"
#include "System/LogFileName.h"


UdpTestClient::UdpTestClient( const char * _bindAddr, const char * _targetAddr, unsigned _pingRate, unsigned _pingSize, timer::Time _timeout, timer::Time _dumpPeriod, int _bufferSize ) :
UdpTestBase( _bindAddr, _bufferSize ),
target( _targetAddr ),
rate( _pingRate ),
pingSize( _pingSize ),
timeout( _timeout ),
nextPing( 0 ),
nextPingIndex( 1 ),
nextTimeoutsPoll( 0 ),
nextDump( timer::Now() + _dumpPeriod ),
dumpPeriod( _dumpPeriod ),
lostPings( 0 ), okPings( 0 ),
dumpHisto( lifehack::EasyVector<double>( 0.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0, 1000.0, 10000.0 ) ),
csvFile( 0 ),
nextCpuMeasure( 0 ), cpuQuery( NULL ), cpuTotal( NULL ),
cpuLoadSum( 0 ), cpuLoadCounter( 0 )
{
  buffer.resize( Max( _pingSize, sizeof( int ) ), 0 );

  const char * Msg = "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog";
  memcpy( &buffer[0] + 4, Msg, Min( _pingSize - 4, strlen( Msg ) ) );

  string csvfname = NDebug::GenerateDebugFileName( "udp_report", "csv", "logs" );
  csvFile = fopen( csvfname.c_str(), "wt" );

  if ( csvFile ) {
    fprintf( csvFile, "Time;Loss;Cpu;PingMin;PingAvg;PingMax" );
    for ( size_t i = 0; i < dumpHisto.Size(); ++i )
      fprintf( csvFile, ";[%.0f-%0.f]", dumpHisto.GetBand( i ).lowerBound, dumpHisto.GetBand( i ).upperBound );
    fprintf( csvFile, "\n" );
    fflush( csvFile );
  }

  PdhOpenQuery( NULL, NULL, &cpuQuery );
  PdhAddCounter( cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal );
  PdhCollectQueryData( cpuQuery );
}



UdpTestClient::~UdpTestClient()
{
  if ( csvFile )
    fclose( csvFile );
  csvFile = 0;
}



void UdpTestClient::Poll()
{
  Sleep( 1 );

  timer::Time t = timer::Now();
  if ( t < nextPing )
    return;

  nextPing += 1.0 / rate;

  MessageTrace( "Sending ping. index=%d", nextPingIndex );
  Strong<Ping> ping = new Ping;
  ping->index = nextPingIndex++;
  ping->time = t;

  *((int*)&buffer[0] ) = ping->index;

  {
    threading::MutexLock lock( mutex );
    pings[ping->index] = ping;
  }
  socket->SendDatagram( target, &buffer[0], buffer.size() );

  if ( t > nextTimeoutsPoll )
    PollTimeouts( t );

  if ( t > nextDump )
    PollDump( t );

  if ( t > nextCpuMeasure )
    PollCpuUsage( t );
}



void UdpTestClient::PollTimeouts( timer::Time _now )
{
  nextTimeoutsPoll = _now + 0.1;

  threading::MutexLock lock( mutex );

  for ( ActivePings::iterator it = pings.begin(); it != pings.end(); ++it )
    if ( _now > ( it->second->time + timeout ) )
    {
      WarningTrace( "Ping timed out. index=%d", it->second->index );
      it->second->time = -1;
      hist.push_back( it->second );
      it = lifehack::StlErase( pings, it );
      ++lostPings;
    }
}



void UdpTestClient::PollDump( timer::Time _now )
{
  nextDump = _now + dumpPeriod;

  threading::MutexLock lock( mutex );

  int loss = ( 100 * lostPings ) / Max( 1, lostPings + okPings );
  if ( cpuLoadCounter )
    cpuLoadSum /= cpuLoadCounter;

  MessageTrace( "Report. loss=%d%%, cpu=%.1f, histo=%d", loss, cpuLoadSum, dumpHisto );

  if ( csvFile )
  {
    fprintf( csvFile, "%.0f;%d;%.0f;%.0f;%.0f;%.0f", 
      _now,
      loss,
      cpuLoadSum,
      dumpHisto.GetTotal().minValue,
      dumpHisto.GetTotal().avg,
      dumpHisto.GetTotal().maxValue );

    for ( size_t i = 0; i < dumpHisto.Size(); ++i )
      fprintf( csvFile, ";%u", dumpHisto.GetBand( i ).hits );
    fprintf( csvFile, "\n" );

    fflush( csvFile );
  }

  okPings = 0;
  lostPings = 0;
  cpuLoadSum = 0;
  cpuLoadCounter = 0;
  dumpHisto.ResetData();
}



void UdpTestClient::PollCpuUsage( timer::Time _now )
{
  nextCpuMeasure = _now + 1.0;

  PdhCollectQueryData( cpuQuery );
  PDH_FMT_COUNTERVALUE counterVal;
  PdhGetFormattedCounterValue( cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal );

  cpuLoadSum += counterVal.doubleValue;
  ++cpuLoadCounter;
}



void UdpTestClient::Finish()
{
  CustomHistogram H( lifehack::EasyVector<double>( 0.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0, 1000.0, 10000.0 ) );

  threading::MutexLock lock( mutex );

  if ( !hist.size() )
  {
    MessageTrace( "No data!" );
    return;
  }

  int lost = 0;
  for ( PingsHist::iterator it = hist.begin(); it != hist.end(); ++it )
  {
    Ping * p = *it;
    if ( p->time < 0 )
      ++lost;
    else
      H.AddData( p->time * 1e3 );
  }

  MessageTrace( "Packet loss: %d%%", ( 100 * lost ) / hist.size() );
  MessageTrace( "RTT histogram: %.1f", H );

  if ( csvFile )
    fclose( csvFile );
  csvFile = 0;
}



void UdpTestClient::OnDatagram( ni_udp::ISocket * _socket, const ni_udp::NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime )
{
  if ( _size < sizeof( int ) )
  {
    WarningTrace( "Datagram too small! size=%d, remote=%s", _size, _remoteAddr );
    return;
  }

  timer::Time t = timer::Now();

  int index = *(int *)_data;
  MessageTrace( "Incoming packet. index=%d, size=%d, remote=%s", index, _size, _remoteAddr );

  timer::Time rtt = -1;
  {
    threading::MutexLock lock( mutex );
    ActivePings::iterator it = pings.find( index );
    if ( it != pings.end() )
    {
      rtt = t - it->second->time;
      it->second->time = rtt;
      hist.push_back( it->second );
      pings.erase( it );

      ++okPings;
      dumpHisto.AddData( rtt * 1e3 );
    }
  }

  if ( rtt >= 0 )
    MessageTrace( "Got ping. index=%d, rtt=%.2f, remote=%s", index, rtt * 1e3, _remoteAddr );
  else
    ErrorTrace( "Unknown packet. index=%d, remote=%s", index, _remoteAddr );
}
