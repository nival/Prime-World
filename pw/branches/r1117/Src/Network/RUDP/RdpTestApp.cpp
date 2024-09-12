#include "stdafx.h"
#include "SockSrvWinsockBlocking.h"
#include "UdpSocket.h"
#include "System/NiTimer.h"
#include "System/RandomInterfaceImpl.h"
#include "System/ThreadNames.h"
#include "System/CmdLineLite.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"
#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include <System/DebugTraceDumper.h>
#include "System/CrashRptWrapper.h"
#include "System/InlineProfiler.h"
#ifdef NI_ENABLE_INLINE_PROFILER
#include <conio.h>
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"
#endif //NI_ENABLE_INLINE_PROFILER
#include <map>
#include "Version.h"
#include "RdpTestServer.h"
#include "RdpTestClient.h"
#include "SockSrvLocal.h"


class LocalSockSrvPoller : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalSockSrvPoller, threading::IThreadJob, BaseObjectMT );
public:
  LocalSockSrvPoller( ni_udp::LocalSocketServer * _sockSrv ) :
  sockSrv( _sockSrv )
  {}

  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    while ( isRunning )
    {
      sockSrv->Poll();
      Sleep( 1 );
    }
  }

private:
  StrongMT<ni_udp::LocalSocketServer> sockSrv;
};



typedef std::list<StrongMT<RdpTestClient>> Clients;

static StrongMT<ni_udp::ISocketServer>  s_sockSrv;
static StrongMT<threading::JobThread>   s_sockSrvPoller;
static StrongMT<ni_udp::IRdp>           s_rdp;
static StrongMT<TestServer>             s_server;
static Clients                          s_clients;
static int                              s_clientsToStart;
static int                              s_nextClientInstIdx;
static timer::Time                      s_nextClientSpawn;


static void CreateLocalSocketServer()
{
  int packetLoss = CmdLineLite::Instance().GetIntKey( "-pkt_loss", 0 );

  StrongMT<ni_udp::LocalSocketServer> localSockSrv = new ni_udp::LocalSocketServer( new timer::RealTimer );
  localSockSrv->SetDefaultDelay( 0 );

  if ( packetLoss )
    localSockSrv->SetRandomPacketLoss( packetLoss * 1e-2 );

  s_sockSrvPoller = new threading::JobThread( new LocalSockSrvPoller( localSockSrv ), "LocalSocketServer" );

  s_sockSrv = localSockSrv;
}



static void CreateUdpSocketServer()
{
  StrongMT<ni_udp::BlockingUdpSocketServer> ss = new ni_udp::BlockingUdpSocketServer( 1, 65536 );
  s_sockSrv = ss;
}



class SocketFactory : public ni_udp::IRdpSocketFactory, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocketFactory, ni_udp::IRdpSocketFactory, BaseObjectMT );
public:
  SocketFactory( ni_udp::ISocketServer * _sockSrv, const char * _addr, unsigned _basePort ) :
  sockSrv( _sockSrv ),
  addr( _addr ), port( _basePort )
  {}

  virtual StrongMT<ni_udp::ISocket> OpenSocket( ni_udp::ISocketCallback * _cb )
  {
    return sockSrv->Open( _cb, ni_udp::NetAddr( addr.c_str(), port ), 0 );
  }

private:
  StrongMT<ni_udp::ISocketServer> sockSrv;
  std::string addr;
  unsigned port;
};



static bool StartTransport()
{
  if ( CmdLineLite::Instance().IsKeyDefined( "-local" ) )
    CreateLocalSocketServer();
  else
    CreateUdpSocketServer();

  s_rdp = ni_udp::NewRdpInstance();

  const char * addr = CmdLineLite::Instance().GetStringKey( "-addr", "localhost" );
  unsigned port = CmdLineLite::Instance().GetIntKey( "-port", 27000 );

  StrongMT<SocketFactory> sockFact = new SocketFactory( s_sockSrv, addr, port );

  ni_udp::RdpOptions opt;

  MessageTrace( "Starting RDP. addr=%s, port=%d", addr, port );

  Strong<ni_rnd::Factory> rndFact = new ni_rnd::Factory;

  if ( !s_rdp->Init( sockFact, opt, rndFact->Produce( (unsigned)timer::GetTicks() ), new timer::RealTimer ) )
    return false;

  return true;
}



static bool StartServer( int _avgGameDuration, int _listenMuxIdx )
{
  NI_VERIFY( s_rdp, "", return false );

  MessageTrace( "Starting server..." );

  s_server = new TestServer( s_rdp, 10 * _avgGameDuration );
  if ( !s_server->Init( _listenMuxIdx ) )
    return false;
  return true;
}



static void SpawnClients( timer::Time _now, int _avgGameDuration, int _randomDisconnectProb )
{
  NI_PROFILE_FUNCTION;

  if ( (int)s_clients.size() >= s_clientsToStart )
    return;

  if ( _now < s_nextClientSpawn )
    return;

  timer::Time disconnectTime = -1.0;
  if ( rand() % 101 <= _randomDisconnectProb )
    disconnectTime = _avgGameDuration * ( rand() / (float)RAND_MAX );

  s_nextClientSpawn = _now + ( rand() % 100 ) * 1e-3;

  ni_udp::NetAddr serverAddr( CmdLineLite::Instance().GetStringKey( "-remote_addr", "localhost" ), CmdLineLite::Instance().GetIntKey( "-remote_port", 27000 ) );
  MessageTrace( "Starting test client. server_addr=%s", serverAddr );

  StrongMT<RdpTestClient> cl = new RdpTestClient( s_rdp, _now, ++s_nextClientInstIdx, disconnectTime );
  if ( cl->Init( serverAddr, 100 ) )
    s_clients.push_back( cl );
}



static void DebugSleep( int sleep )
{
  timer::Time t0 = timer::Now();

  while ( true )
  {
    Sleep( sleep );

    timer::Time t = timer::Now();
    DebugTrace( "Sleep debug: t=%.2f, dt=%.2f", 1e3 * t, 1e3 * ( t - t0 ) );
    t0 = t;
  }
}



static void RunTest()
{
  if ( int sleepDbg = CmdLineLite::Instance().GetIntKey( "-debug_sleep", 0 ) )
    DebugSleep( sleepDbg );

  if ( !StartTransport() )
    return;

  const int avgGameDuration = CmdLineLite::Instance().GetIntKey( "-gameduration", 300 );
  const int randomDisconnectProb = CmdLineLite::Instance().GetIntKey( "-disconnects", 0 );

  if ( CmdLineLite::Instance().IsKeyDefined( "-server" ) )
    if ( !StartServer( avgGameDuration, 100 ) )
      return;

  s_clientsToStart = CmdLineLite::Instance().GetIntKey( "-clients", 0 );

  if ( s_clientsToStart )
    MessageTrace( "Starting %d clients...", s_clientsToStart );

  while ( s_server || !s_clients.empty() || !s_nextClientInstIdx )
  {
    Sleep( 1 );

    NI_PROFILE_BLOCK( "Main Loop" );

    timer::Time now = timer::Now();

    SpawnClients( now, avgGameDuration, randomDisconnectProb );

    if ( s_server )
      if( !s_server->Poll( now ) )
        s_server = 0;

    for ( Clients::iterator it = s_clients.begin(); it != s_clients.end(); )
    {
      if ( (*it)->Poll( now ) )
        ++it;
      else
      {
        MessageTrace( "Removing client instance. inst=%d, uid=%d", (*it)->InstIdx(), (*it)->Uid() );
        it = s_clients.erase( it );
      }
    }
  }

  s_rdp = 0;
  s_sockSrvPoller = 0;
  s_sockSrv = 0;
}



class LogTraceWrapper
{
public: 
  LogTraceWrapper() {}

  void operator() ( int i ) { 
    MessageTrace("(%d)", i);
  }
};

class LogHandle
{
public:
  LogHandle() {}

  LogTraceWrapper Error;
};



int main( int argc, const char **argv )
{
  LogHandle logHandle;
  logHandle.Error( 33 );

  threading::SetDebugThreadName( "Main" );

  CmdLineLite::Instance().Init( argc, argv );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "UdtTest", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdoutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );

  NLogg::CDumper::SetRotationPeriod( 1 );
  StrongMT<NLogg::BasicTextFileDumper> textLogDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "test" );

  //StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper;
  //if ( IsDebuggerPresent() )
  //  debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );

  Sleep( 100 ); //UGLY: Let text file dumpers to create their files
  CrashRptWrapper::InstallForProcess( "http://SITE.com/upload/", true, false, "GameTestClient" );
  CrashRptWrapper::AddFileToReport( textLogDumper->FileName().c_str(), "Log File" );

#ifdef NI_ENABLE_INLINE_PROFILER
  const bool profilerOn = CmdLineLite::Instance().IsKeyDefined( "-profile" );

  profiler3::GetControl()->Setup( profiler3::SSettings() );
  NI_PROFILE_THREAD_NAMED( "Main" );
  profiler3ui::Init();
  if ( profilerOn )
    profiler3ui::Show( NULL );
#endif //NI_ENABLE_INLINE_PROFILER


  ni_udp::UdpSocket::GlobalInit();
  
  MessageTrace( "RDP test" );

  RunTest();

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

  CrashRptWrapper::UninstallFromProcess();

  return 0;
}
