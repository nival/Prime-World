#include "stdafx.h"

#include "ServerAppBase.h"
#include "NivalServer.h"
#include "System/FileSystem/FilePath.h"
#include "System/FileSystem/WinFileSystem.h"
#include "System/LogFileName.h"
#include "System/LogMover.h"
#include "System/DarkSide.h"
#if defined( NV_WIN_PLATFORM )
#include "System/BSUtil.h"
#endif
#include "System/ConfigFiles.h"
#include "System/Signals.h"
#include "HybridServer/HybridServerNaming.h"

#include "libdb/Db.h"

#include "ServerCfg.h"
#include "Db/DBServer.auto.h"


namespace
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugVarCallback( const wchar_t* screen, const wchar_t* name, const NDebug::IDebugVar* var, void* pData )
{
  static wchar_t value[128];
  var->FormatValue( value, sizeof( value ) / sizeof( wchar_t ) );

  if ( NStr::SearchFirst( NStr::ToMBCS( name ).c_str(), " to:", NStr::SASCIICharsComparer() ) >= 0 )
    return;

  systemLog( NLogg::LEVEL_MESSAGE ) << wstring(name) << ": " << wstring(value) << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintNetStats()
{
  //systemLog( NLogg::LEVEL_MESSAGE ) << endl;
  //int nScreen = 0;
  //while ( wcscmp( NDebug::GetDebugScreenName( nScreen ), L"Net" ) != 0 ) 
  //  ++nScreen;

  //NDebug::ProcessScreenDebugVars( nScreen, PrintDebugVarCallback, 0 );
}

static const int timerInterval = 100;

} // nameless namespace

namespace Transport 
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerAppBase::ServerAppBase() :
stepsCounter( 0 )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerAppBase::~ServerAppBase()
{

}



int ServerAppBase::Step(int delta) 
{ 
  if ( server && server->ShowNetStatistics() )
  {
    if( ( stepsCounter++ % 20 ) == 0 )
    {
      NDebug::ResetDebugVarsOnFrame( 20 * timerInterval / 1000.f );
      PrintNetStats();
    }
  }
  return timerInterval;
}



int ServerAppBase::GetId() const
{
  return DarkSide::ptr2int< int >( this );
}


// попробуем сгенерить вменяемое имя для текстового лога (т.е. включить в него инфу по запускаемым сервисам)
inline string MakeLogFileNameSuffix( int argc, char * argv[] )
{
  string logName;

  logName.reserve( 256 );
  for ( int i = 1; i < argc; ++i )
  {
    string arg = argv[i];
    NStr::ToLower( &arg );

    if ( !arg.empty() && isalpha( arg[0] ) )
    {
      string tmp( arg );
      for ( int i = 0; i < tmp.size(); ++i )
        if ( ( tmp[i] != '_' ) && !isalpha( tmp[i] ) ) {
          tmp.resize( i );
          break;
        }
      if ( tmp.empty() )
        continue;

      if ( !logName.empty() )
        logName += '_';

      logName += tmp;
    }
  }

  if ( logName.empty() )
    logName = "all";

  logName += "-output";

  return logName;
}



inline bool CheckForSyncLogger( int argc, char * argv[] )
{
  for ( int i = 1; i < argc; ++i )
    if ( NStr::ICmp( argv[i], "--sync_log_writer" ) == 0 )
      return true;
  return false;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ServerAppBase::OnInit(int argc, char* argv[])
{
  Signals::CatchAbort();

  NFile::InitBaseDir();

  GetSystemLog().SetDefaultMinLevelFilter( NLogg::LEVEL_DEBUG );

  NLogg::LogMover::GetInstance().Init( argc, argv ); // разбираем ком.строку, составляем список лог-файлов (_до_ создания новых)

  NLogg::BasicTextFileDumper::Setup( CheckForSyncLogger( argc, argv ), 1024 * 1024 );

  stdoutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );

  string logName = MakeLogFileNameSuffix( argc, argv );
  textLogDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), logName.c_str() );

#if defined( NV_WIN_PLATFORM )
  if ( IsDebuggerPresent() )
    debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );
#endif

  systemLog( NLogg::LEVEL_MESSAGE ) << "Universal server";
  systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: UniServerApp [coordinator] [login] [relay] [chat] [lobby] [matchmaking] [hybridserver] [clusteradmin] [-netStat]";
  systemLog( NLogg::LEVEL_MESSAGE ) << "Should be started in <project>/Bin/ or <project>/ServerBin/ directory";

  NProfile::Init( "" );
  NGlobal::ExecuteConfig( "server.cfg", NProfile::FOLDER_GLOBAL );
  RootFileSystem::RegisterFileSystem( new WinFileSystem( NFile::GetBaseDir() + "Data", false ) );

  NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );

  NDb::SessionRoot::InitRoot( NDb::Get<NDb::SessionRoot>( NDb::DBID( "Session.ROOT" ) ) );

  NLogg::LogMover::GetInstance().Move( "" ); // переносим всё подряд; // .Move( NDebug::ClusterName() ) чтобы переносить только логи, СОДЕРЖАЩИЕ НАШЕ ИМЯ КЛАСТЕРА

  stepsCounter = 0;

  server = new NivalServer;

  if ( !OnInitServerFactory( server ) )
    return false;

  if ( !server->Startup( argc, argv ) )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Server startup is FAILED" << endl; 
    return false;
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ServerAppBase::OnRun()
{
  systemLog( NLogg::LEVEL_MESSAGE ) << "Server(s) started."<< endl;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ServerAppBase::OnExit()
{
  if ( server )
    server->Shutdown();

  //Network::IConnection::DumpCompressionStatistics();

  NDb::SessionRoot::InitRoot( 0 );

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace TransportFDebugVarReporter

