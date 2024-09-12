#include "System/FileSystem/FileUtils.h"
#include "System/FileSystem/FilePath.h"
#include "System/LogFileName.h"
#include "System/CrashRptWrapper.h"
#include "System/CmdLineLite.h"
#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include "System/AssertDumper.h"
#include "System/DebugTraceDumper.h"
#include "RdpTestServer.h"
#include "UdpTestServer.h"
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



inline void RunUdpServer( const char * serverBindAddr )
{
  MessageTrace( "Starting UDP diag server..." );
  int bufferSz = CmdLineLite::Instance().GetIntKey( "-buffer", 65536 );
  StrongMT<Server> srv = new Server( serverBindAddr, bufferSz );
  Sleep( INFINITE );
}



inline void RunRdpServer( const char * serverBindAddr )
{
  MessageTrace( "Starting RDP server. bind_addr=%s", serverBindAddr );

  int bufferSz = CmdLineLite::Instance().GetIntKey( "-buffer", 65536 );

  StrongMT<TestRdpTransport> rdp = new TestRdpTransport;
  if ( !rdp->Init( serverBindAddr, false, bufferSz ) )
    return;

  RdpTestSettings sett;

  StrongMT<TestRdpServer> srv = new TestRdpServer( rdp, sett );

  while ( true )
  {
    srv->Poll();
    Sleep( 50 );

    if ( StopByKeyb() )
      break;
  }
}




void main( int argc, char ** args )
{
  CmdLineLite::Instance().Init( argc, args );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "UdpDiagServer", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdOutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );
  StrongMT<NLogg::BasicTextFileDumper> textFileDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "udpdiagserver" );
  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );

  ni_detail::InitPointersStatics();

  NFile::InitBaseDir();
  NProfile::Init( "UdpDiag" );

  CrashRptWrapper::InstallForProcess( "http://b283.SITE/upload/", true, false, "UdpDiagServer" );
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

  if ( const char * serverBindAddr  = CmdLineLite::Instance().GetStringKey( "-server" ) )
    RunUdpServer( serverBindAddr );
  else if ( const char * serverBindAddr  = CmdLineLite::Instance().GetStringKey( "-rdp_server" ) )
    RunRdpServer( serverBindAddr );
  else
    MessageTrace( 
      "Usage:\n"
      "  -server <addr>\n"
      "  -rdp_server <addr>\n"
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
