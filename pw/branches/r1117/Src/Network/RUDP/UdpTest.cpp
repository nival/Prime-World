#include "stdafx.h"
#include "SockSrvWinsockAsync.h"
#include "SockSrvWinsockBlocking.h"
#include "UdpSocket.h"
#include "System/ThreadNames.h"
#include "System/CmdLineLite.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"
#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include <System/DebugTraceDumper.h>
#include "System/InlineProfiler.h"
#ifdef NI_ENABLE_INLINE_PROFILER
#include <conio.h>
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"
#endif //NI_ENABLE_INLINE_PROFILER
#include <map>
#include "Version.h"


struct Header
{
  enum Type { Ping, Ack };

  unsigned  type;
  unsigned  index;
  unsigned  xor;
};


class Callback : public ni_udp::ISocketCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Callback, ni_udp::ISocketCallback, BaseObjectMT);

public:
  Callback() :
  dgIndex( 0 ),
  failures( 0 ),
  start( timer::Now() ),
  acks( 0 ),
  rttSum( 0 )
  {
  }

  virtual void OnDatagram( ni_udp::ISocket * _socket, const ni_udp::NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime )
  {
    if ( _size < sizeof( Header ) )
    {
      ErrorTrace( "Datagram is too small. size=%d", _size );
      ++failures;
      return;
    }

    const Header * h = (const Header * )_data;
    const unsigned short * data = (const unsigned short *)(h + 1);
    const int dataSize = ( _size - sizeof( Header ) ) / sizeof( const unsigned short );
    if ( _size != sizeof( Header ) + dataSize * sizeof( const unsigned short ) )
    {
      ErrorTrace( "Wrong datagram size. size=%d", _size );
      ++failures;
      return;
    }

    unsigned xor = 0;
    for ( int i = 0; i < dataSize; ++i )
      xor += data[i] * i;

    MessageTrace( "Got datagram. type=%d, idx=%d, size=%d, recv_time=%.1f, xor=%d(%d), total=%d, failed=%d", h->type, h->index, _size, _absRecvTime * 1e3, h->xor, xor, dgIndex, failures );

    ++dgIndex;
    if ( h->xor != xor )
    {
      MessageTrace( "Xor check failed. idx=%d, failed=%d", h->index, failures );
      ++failures;
      return;
    }
   
    if ( h->type == Header::Ping )
    {
      MessageTrace( "Sending ACK. idx=%d, addr=%s", h->index, _remoteAddr );
      Header ack;
      ack.type = Header::Ack;
      ack.index = h->index;
      ack.xor = 0;
      _socket->SendDatagram( _remoteAddr, &ack, sizeof( ack ) );
    }
    else if ( h->type == Header::Ack )
    {
      threading::MutexLock lock( mtx );

      WaitList::iterator it = waitList.find( h->index );
      if ( it == waitList.end() )
        ErrorTrace( "Unknown ACK. idx=%d", h->index );
      else
      {
        timer::Time rtt = timer::Now() - it->second;
        ++acks;

        MessageTrace( "Got ACK. idx=%d, RTT=%.1f", h->index, 1e3 * rtt );
        rttSum += rtt;
        waitList.erase( it );
      }
    }
  }

  virtual void OnWritable( ni_udp::ISocket * _socket )
  {
  }

  void WaitPktAck( unsigned idx )
  {
    NI_PROFILE_HEAVY_FUNCTION;

    threading::MutexLock lock( mtx );

    waitList[idx] = timer::Now();
  }

  void Dump( timer::Time elapsed )
  {
    threading::MutexLock lock( mtx );

    unsigned total = acks + waitList.size();

    timer::Time avgRtt = rttSum;
    if ( acks )
      avgRtt /= acks;

    if ( total )
    {
      MessageTrace( 
        "Satistics:\n"
        "Time elapsed: %.1f\n"
        "Total: %d (%.1fk/sec)\n"
        "Acked: %d (%.2f%%)\n"
        "Not acked: %d (%.2f%%)\n"
        "RTT avg: %.1fms\n"
        "Failed: %d",
        elapsed,
        total, 1e-3 * total / elapsed,
        acks, 1e2 * acks / total,
        waitList.size(), 1e2 * waitList.size() / total,
        1e3 * avgRtt,
        failures );
    }
  }

private:
  typedef std::map<unsigned, timer::Time> WaitList;

  int               dgIndex, failures;
  timer::Time       start;
  threading::Mutex  mtx;
  WaitList          waitList;
  unsigned          acks;
  timer::Time       rttSum;
};




void SendPackets( ni_udp::ISocket * sock, Callback * callback, int rate )
{
  const char * sendTo = CmdLineLite::Instance().GetStringKey( "-sendto", "127.0.0.1" );
  int sendPort = CmdLineLite::Instance().GetIntKey( "-sendport", 27000 );

  int sleep = CmdLineLite::Instance().GetIntKey( "-sleep", 0 );

  int size = CmdLineLite::Instance().GetIntKey( "-size", 1024 );
  size = Clamp( size, (int)sizeof( Header ), 65536 - 256 );
  size = size / sizeof( unsigned short ) * sizeof( unsigned short );

  int duration = CmdLineLite::Instance().GetIntKey( "-duration", 3 );

  ni_udp::NetAddr to( sendTo, sendPort );

  MessageTrace( "Sending packets. rate=%d, duration=%d, size=%d, dest=%s", 
    rate, duration, size, to );

  char buf[65536];
  int index = 0;
  timer::Time start = timer::Now();
  timer::Time nextSend = start;
  timer::Time timeIncrement = 1.0 / (timer::Time)rate;
  while ( timer::Now() < start + duration )
  {
    NI_PROFILE_BLOCK( "Batch" );

    int limit = 0;
    while ( ( timer::Now() > nextSend ) && ( limit < 100 ) )
    {
      NI_PROFILE_BLOCK( "Datagram" );

      ++limit;

      nextSend += timeIncrement;

      Header * h = (Header * )buf;
      unsigned short * data = (unsigned short * )(h + 1);
      int dataDim = ( size - sizeof( Header ) ) / sizeof( unsigned short );

      h->type = Header::Ping;
      h->index = index++;
      h->xor = 0;

      for ( int k = 0; k < dataDim; ++k )
      {
        data[k] = (unsigned short)rand();
        h->xor += (unsigned)data[k] * k;
      }

      DebugTrace( "Sending datagram. " );

      callback->WaitPktAck( h->index );
      sock->SendDatagram( to, buf, sizeof( Header ) + dataDim * sizeof( unsigned short ) );
    }

    if ( sleep )
    {
      NI_PROFILE_BLOCK( "Sleep" );
      Sleep( sleep );
    }
  }
  timer::Time elapsed = timer::Now() - start;

  Sleep( 1000 );
  callback->Dump( elapsed );
}




void TestItself()
{
  StrongMT<ni_udp::ISocketServer> srv;

  if ( CmdLineLite::Instance().IsKeyDefined( "-blocking" ) )
    srv = new ni_udp::BlockingUdpSocketServer( 1, 65536 );
  else
    srv = new ni_udp::AsyncUdpSocketServer;

  StrongMT<Callback> cb = new Callback;
  
  const char * bindAddr = CmdLineLite::Instance().GetStringKey( "-bind", "127.0.0.1" );
  int bindPort = CmdLineLite::Instance().GetIntKey( "-bindport", 27000 );

  StrongMT<ni_udp::ISocket> sock = srv->Open( cb, ni_udp::NetAddr( bindAddr, bindPort ), 0 );
  NI_VERIFY( sock, "", return );

  if ( sock->Status() != ni_udp::ESocketStatus::Ready )
    return;

  if ( int rate = CmdLineLite::Instance().GetIntKey( "-rate", 0 ) )
    SendPackets( sock, cb, rate );
  else
    Sleep( INFINITE );
}




int main( int argc, const char **argv )
{
  threading::SetDebugThreadName( "Main" );

  CmdLineLite::Instance().Init( argc, argv );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "UdtTest", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdoutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );

  StrongMT<NLogg::BasicTextFileDumper> textLogDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "test" );

  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper;
  if ( IsDebuggerPresent() )
    debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );

#ifdef NI_ENABLE_INLINE_PROFILER
  const bool profilerOn = CmdLineLite::Instance().IsKeyDefined( "-profile" );

  profiler3::GetControl()->Setup( profiler3::SSettings() );
  NI_PROFILE_THREAD_NAMED( "Main" );
  profiler3ui::Init();
  if ( profilerOn )
    profiler3ui::Show( NULL );
#endif //NI_ENABLE_INLINE_PROFILER


  ni_udp::UdpSocket::GlobalInit();
  
  MessageTrace( "UDP test" );

  TestItself();

  ni_udp::UdpSocket::GlobalShutdown();

#ifdef NI_ENABLE_INLINE_PROFILER
  if ( profilerOn ) {
    MessageTrace( "Press any key to continue..." );
    _getch();
  }
#endif //NI_ENABLE_INLINE_PROFILER

#ifdef NI_ENABLE_INLINE_PROFILER
  profiler3ui::Shutdown();
#endif //NI_ENABLE_INLINE_PROFILER

  GetSystemLog().ClearAllDumpers();

  return 0;
}
