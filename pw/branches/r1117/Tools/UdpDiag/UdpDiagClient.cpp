#include "System/FileSystem/FileUtils.h"
#include "System/FileSystem/FilePath.h"
#include "System/LogFileName.h"
#include "System/CrashRptWrapper.h"
#include "System/CmdLineLite.h"
#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include "System/AssertDumper.h"
#include "System/DebugTraceDumper.h"
#include "RdpTestClient.h"
#include "UdpTestClient.h"
#include "Network/RUDP/UdpSocket.h"
#include "System/Lifehacks.h"
#include <conio.h>
#include "Version.h"



inline bool StopByKeyb()
{
  if ( kbhit() )
  {
    char c = getch();
    if ( c == 'x' || c == 'X' )
      return true;
  }

  return false;
}


inline void RunUdpClients( const char * clientDestAddr )
{
  const char * clBindAddr = CmdLineLite::Instance().GetStringKey( "-bind", "45000" );
  int rate = CmdLineLite::Instance().GetIntKey( "-rate", 10 );
  int pingSize = CmdLineLite::Instance().GetIntKey( "-size", 50 );
  timer::Time timeout = CmdLineLite::Instance().GetIntKey( "-timeout", 10 );
  timer::Time dumpperiod = CmdLineLite::Instance().GetIntKey( "-dump_period", 60 );
  int bufferSz = CmdLineLite::Instance().GetIntKey( "-buffer", 65536 );
  MessageTrace( "Starting UDP diag client. target=%s, rate=%d, size=%d, timeout=%.1f", clBindAddr, rate, pingSize, timeout );
  StrongMT<UdpTestClient> cl = new UdpTestClient( clBindAddr, clientDestAddr, rate, pingSize, timeout, dumpperiod, bufferSz );
  while ( true )
  {
    if ( StopByKeyb() )
      break;

    cl->Poll();
  }
  cl->Finish();
}



typedef std::list< StrongMT<TestRdpClient> > RdpTestClients;

inline void RunRdpClients( const char * serverAddr )
{
  RdpTestSettings settings;

  const char * bindAddr = CmdLineLite::Instance().GetStringKey( "-bind", "45000" );
  int clientsNum = CmdLineLite::Instance().GetIntKey( "-number", 1 );
  int transportNum = CmdLineLite::Instance().GetIntKey( "-transports", 1 );
  int bufferSz = CmdLineLite::Instance().GetIntKey( "-buffer", 65536 );
  settings.minSendPeriod = CmdLineLite::Instance().GetFloatKey( "-waitmin", 1.0f );
  settings.maxSendPeriod = CmdLineLite::Instance().GetFloatKey( "-waitmax", 10.0f );
  settings.helloBurstLength = CmdLineLite::Instance().GetIntKey( "-burstlen", 3 );
  settings.minLifetime = CmdLineLite::Instance().GetFloatKey( "-lifetimemin", 45.0f );
  settings.maxLifetime = CmdLineLite::Instance().GetFloatKey( "-lifetimemax", 75.0f );

  MessageTrace( "Starting RDP clients. bind_addr=%s, server=%s, clients=%d, transports", bindAddr, serverAddr, clientsNum, transportNum );

  std::vector< StrongMT<TestRdpTransport> > transports;
  size_t nextTransport = 0;
  transports.reserve( transportNum );
  for ( int i = 0; i < transportNum; ++i )
  {
    transports.push_back( new TestRdpTransport );
    if ( !transports.back()->Init( bindAddr, true, bufferSz ) )
      return;
  }

  NI_VERIFY( !transports.empty(), "", return );

  timer::Time nextSpawn = 0;

  RdpTestClients clients;
  int clientId = 1;
  int failed = 0, finished = 0;

  while ( true )
  {
    Sleep( 10 );

    for ( RdpTestClients::iterator it = clients.begin(); it != clients.end(); )
    {
      TestRdpContext::EStatus::Enum st = (*it)->Poll();

      if ( ( st == TestRdpContext::EStatus::Finished ) || ( st == TestRdpContext::EStatus::Failed ) )
      {
        it = lifehack::StlErase( clients, it );

        if ( st == TestRdpContext::EStatus::Finished )
          ++finished;
        else
          ++failed;

        int total = finished + failed + clients.size();
        double succ = total ? ( 1e2 * finished / total ) : 0;
        MessageTrace( "Client removed. finished=%d, failed=%d, in_progress=%d, success=%.1f%%", finished, failed, clients.size(), succ );
      }
      else
        ++it;
    }

    if ( (int)clients.size() < clientsNum )
    {
      timer::Time t = timer::Now();
      if ( t > nextSpawn )
      {
        nextSpawn = t + 0.1;

        MessageTrace( "Adding client." );

        StrongMT<TestRdpClient> c = new TestRdpClient( settings, clientId++ );

        c->ConnectTo( transports[nextTransport], serverAddr );
        nextTransport = ( nextTransport + 1 ) % transports.size();

        clients.push_back( c );
      }
    }

    if ( StopByKeyb() )
      break;
  }
}




void main( int argc, char ** args )
{
  CmdLineLite::Instance().Init( argc, args );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "UdpDiagClient", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdOutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );
  StrongMT<NLogg::BasicTextFileDumper> textFileDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "udpdiagclient" );
  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );

  ni_detail::InitPointersStatics();

  NFile::InitBaseDir();
  NProfile::Init( "UdpDiag" );

  CrashRptWrapper::InstallForProcess( "http://b283.SITE/upload/", true, false, "UdpDiagClient" );
  CrashRptWrapper::AddFileToReport( textFileDumper->FileName().c_str(), "Log File" );


#ifdef NI_ENABLE_INLINE_PROFILER
  const bool profilerOn = CmdLineLite::Instance().IsKeyDefined( "-profile" );

  profiler3::GetControl()->Setup( profiler3::SSettings() );
  NI_PROFILE_THREAD_NAMED( "Main" );
  profiler3ui::Init();
  if ( profilerOn )
    profiler3ui::Show( NULL );
#endif //NI_ENABLE_INLINE_PROFILER

  ni_udp::UdpSocket::GlobalInit();

  if ( const char * clientDestAddr  = CmdLineLite::Instance().GetStringKey( "-client" ) )
    RunUdpClients( clientDestAddr );
  else if ( const char * clientDestAddr  = CmdLineLite::Instance().GetStringKey( "-rdp_client" ) )
    RunRdpClients( clientDestAddr );
  else
    MessageTrace( 
      "Usage:\n"
      "  -server <addr>\n"
      "  -client <addr>\n"
      "  -rdp_server <addr>\n"
      "  -rdp_client <addr>\n"
      "  -bind <addr>\n"
      "  -buffer N\n"
      "  -rate N\n"
      "  -size N\n"
      "  -timeout N\n"
      "  -dump_period N\n"
      );

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
}
