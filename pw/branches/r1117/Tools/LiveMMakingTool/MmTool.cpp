#include <stdlib.h>
#include <stdio.h>
#include <io.h>

#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include "System/AssertDumper.h"
#include "System/DebugTraceDumper.h"
#include "System/FileSystem/WinFileSystem.h"
#include "System/ConfigFiles.h"
#include "System/FileSystem/FileUtils.h"
#include "System/CmdLineLite.h"
#include "System/CrashRptWrapper.h"

#include "Db/DBServer.auto.h"

#include "MmScriptPlayer.h"
#include "MmLogPlayback.h"
#include "MmLogScaner.h"
#include "JsonLogParser.h"

#include "Version.h"

#ifdef NI_ENABLE_INLINE_PROFILER
#include <conio.h>
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"
#endif //NI_ENABLE_INLINE_PROFILER

#pragma warning( disable : 4996 ) //warning C4996: This function or variable may be unsafe


static bool LoadFile( string & buf, const char * name ) {
  FILE * f = fopen( name, "rb" );
  if ( f )
  {
    size_t sz = _filelength( _fileno( f ) );
    if ( sz )
    {
      buf.resize( sz, ' ' );
      if ( fread( &buf[0], 1, sz, f ) == sz )
      {
        fclose( f );
        return true;
      }
    }
    fclose( f );
  }
  
  ErrorTrace( "\"%s\" not found OR empty!\n", name );
  return false;
}



static bool PlayScript( const char * filename, mm_test::MmData * mmData, const mm_test::StatisticsSettings & statSett, bool mockMm, bool outputStatistics )
{
  string text;
  if ( !LoadFile( text, filename ) )
    return false;

  Strong<mm_test::ScriptPlayer> player = new mm_test::ScriptPlayer( mmData, statSett, mockMm );
  simple_parser::Context ctx( text.c_str() );
  if ( player->Parse( ctx ) )
  {
    player->StartPlayback( timer::Now() );
    while( true )
    {
      if ( !player->PollPlayback( timer::Now() ) )
      {
        MessageTrace( "Simulation finished!" );
        Sleep( 300 ); //Let the matchmaking finish spamming
        if ( outputStatistics )
        {
          player->Stat()->Postprocess();
          player->Stat()->Output();
        }
        break;
      }
      Sleep( 100 );
    }

    bool res = player->TestPassedOk();
    player = NULL;
    return res;
  }
  else
  {
    string errorPtr( ctx.errorPtr ? ctx.errorPtr : "<null>" );
    if ( errorPtr.size() > 128 ) {
      errorPtr.resize( 128 );
      errorPtr += "...";
    }
    ErrorTrace( "Parse error \"%s\": %s", ctx.errorMsg.c_str(), errorPtr.c_str() );
    return false;
  }
}



static int RunAutoTest( const char * path, mm_test::MmData * mmData, const mm_test::StatisticsSettings & statSett )
{
  list<string> filenames;

  NFile::GetDirectoryFiles( path, "*.txt", &filenames, true );

  int errorCounter = 0, total = filenames.size();

  for ( int idx = 0; !filenames.empty(); ++idx )
  {
    MessageTrace( "Playing script %d of %d, \"%s\"...", idx + 1, total, filenames.front() );

    if ( PlayScript( filenames.front().c_str(), mmData, statSett, false, false ) )
      MessageTrace( "Test passed ok!" );
    else
    {
      ++errorCounter;
      MessageTrace( "Test failed, script \"%s\"", filenames.front() );
    }

    filenames.pop_front();
  }

  if ( errorCounter )
    ErrorTrace( "%d tests failed of %d", errorCounter, total );
  else
    MessageTrace( "All %d tests ok", total );

  return errorCounter;
}



static void ProcessTextLog( const char * filename, mm_test::ELogVersion::Enum logVersion, mm_test::ILogParserCb * cb )
{
  if ( NStr::FindFirstI( filename, ".json" )!= NULL )
  {
    mm_test::JsonLogParser p( cb, logVersion );
    if ( !p.AddFile( filename ) )
      return;
  }
  else
  {
    mm_test::LogParser p( cb, logVersion );
    try {
      p.AddFile( filename );
    }
    catch ( const mm_test::LogParser::Excep & ex ) {
      ErrorTrace( "%s: %s, text:\n%s", ex.File(), ex.Reason(), ex.TextSample() );
      return;
    }
  }

  cb->Finish();
  cb->Output();
}



static void ScanLog( const char * filename, mm_test::ELogVersion::Enum logVersion, mm_test::MmData * mmData, const mm_test::StatisticsSettings & statSett, const mm_test::VisualizationSettings & visSett )
{
  MessageTrace( "Scanning log \"%s\"...", filename );

  Strong<mm_test::ILogParserCb> cb = new mm_test::LogScanner( mmData, statSett, visSett );
  ProcessTextLog( filename, logVersion, cb );
}





static void LogPlayback( const char * filename, mm_test::ELogVersion::Enum logVersion, mm_test::MmData * mmData, const mm_test::StatisticsSettings & statSett, const mm_test::VisualizationSettings & visSett )
{
  MessageTrace( "Playing back log \"%s\"...", filename );

  Strong<mm_test::ILogParserCb> cb = new mm_test::LogPlaybackCallback( mmData, statSett, visSett );
  ProcessTextLog( filename, logVersion, cb );
}



int main( int argc, char ** args )
{
  CmdLineLite::Instance().Init( argc, args );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "LiveMMakingTool", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdOutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );
  StrongMT<NLogg::BasicTextFileDumper> textFileDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "mmtool" );
  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );

  ni_detail::InitPointersStatics();

  NFile::InitBaseDir();
  NProfile::Init( "Matchmaking test" );
  RootFileSystem::RegisterFileSystem( new WinFileSystem( NFile::GetBaseDir() + "Data", false ) );
  NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );

  NGlobal::ExecuteConfig( "server.cfg", NProfile::FOLDER_GLOBAL );
  NGlobal::ExecuteConfig( "pvx_srv_livemmaking.cfg", NProfile::FOLDER_GLOBAL );
  NGlobal::ExecuteConfig( "pvx_srv_social_lobby.cfg", NProfile::FOLDER_GLOBAL );

  CrashRptWrapper::InstallForProcess( "http://b283.SITE/upload/", true, false, "LiveMmTool" );
  CrashRptWrapper::AddFileToReport( textFileDumper->FileName().c_str(), "Log File" );

  NDb::SessionRoot::InitRoot( NDb::Get<NDb::SessionRoot>( NDb::DBID( "Session.ROOT" ) ) );

#ifdef NI_ENABLE_INLINE_PROFILER
  const bool profilerOn = CmdLineLite::Instance().IsKeyDefined( "-profile" );
  
  profiler3::GetControl()->Setup( profiler3::SSettings() );
  NI_PROFILE_THREAD_NAMED( "Main" );
  profiler3ui::Init();
  if ( profilerOn )
    profiler3ui::Show( NULL );
#endif //NI_ENABLE_INLINE_PROFILER

  mm_test::ELogVersion::Enum logVersion = mm_test::ELogVersion::trunk;
  const char * logVer = CmdLineLite::Instance().GetStringKey( "-logver", "trunk" );
  if ( !stricmp( logVer, "82x" ) )
    logVersion = mm_test::ELogVersion::v82x;
  else if ( !stricmp( logVer, "902" ) )
    logVersion = mm_test::ELogVersion::v902;
  else if ( !stricmp( logVer, "903" ) )
    logVersion = mm_test::ELogVersion::v903;
  else if ( !stricmp( logVer, "911" ) )
    logVersion = mm_test::ELogVersion::v911;
  else if ( !stricmp( logVer, "914" ) )
    logVersion = mm_test::ELogVersion::v914;
  else if ( !stricmp( logVer, "923" ) )
    logVersion = mm_test::ELogVersion::v923;
  else if ( !stricmp( logVer, "932" ) )
    logVersion = mm_test::ELogVersion::v932;
  else if ( !stricmp( logVer, "940" ) )
    logVersion = mm_test::ELogVersion::v940;
  else if ( !stricmp( logVer, "941" ) )
    logVersion = mm_test::ELogVersion::v941;
  else if ( !stricmp( logVer, "942" ) )
    logVersion = mm_test::ELogVersion::v942;
  else if ( !stricmp( logVer, "trunk" ) )
    logVersion = mm_test::ELogVersion::trunk;
  else
    ErrorTrace( "Unknown log version '%s'!", logVer );

  mm_test::StatisticsSettings statSett;

  statSett.imgWidth = CmdLineLite::Instance().GetIntKey( "-imgwidth", statSett.imgWidth );
  statSett.imgHeight = CmdLineLite::Instance().GetIntKey( "-imgheight", statSett.imgHeight );
  statSett.timeStep = 1e-3 * CmdLineLite::Instance().GetIntKey( "-timestepms", (int)( statSett.timeStep * 1e3 ) );
  statSett.waitLimit = CmdLineLite::Instance().GetIntKey( "-waitlimit", (int)statSett.waitLimit );

  mm_test::VisualizationSettings visSett;
  visSett.minRating = CmdLineLite::Instance().GetIntKey( "-ratingmin", visSett.minRating );
  visSett.maxRating = CmdLineLite::Instance().GetIntKey( "-ratingmax", visSett.maxRating );
  visSett.step = 1e-3 * CmdLineLite::Instance().GetIntKey( "-visstep", (int)( visSett.step * 1e3 ) );
  visSett.height = CmdLineLite::Instance().GetIntKey( "-vismapheight", visSett.height );

  vector<int> scales;
  if ( CmdLineLite::Instance().GetIntKeys( scales, "-visratingscale" ) )
    visSett.scalesSteps = scales;

  MessageTrace(
    "Statistics and simulation settings:\n"
    "  Log version: %s\n"
    "  Simulation time step: %.2f\n"
    "  Hystogram image size: %d x %d\n"
    "  Wait limit: %.0f",
    mm_test::ELogVersion::ToString( logVersion ),
    statSett.timeStep,
    statSett.imgWidth, statSett.imgHeight,
    statSett.waitLimit );

  MessageTrace( 
    "Overview visualization settings:\n"
    "  Rating range: [%d, %d]\n"
    "  Pixel size, sec: %.2f\n"
    "  Rating scale steps: %s\n"
    "  Image height: %d",
    visSett.minRating, visSett.maxRating,
    visSett.step,
    visSett.scalesSteps,
    visSett.height );

  int systemResult = 0;

  Strong<mm_test::MmDataLoader> mmDataLoader = new mm_test::MmDataLoader;
  Strong<mm_test::MmData> mmData = mmDataLoader->Load( CmdLineLite::Instance().GetStringKey( "-map", 0 ) );

  if ( const char * scriptName = CmdLineLite::Instance().GetStringKey( "-playscript" ) )
    PlayScript( scriptName, mmData, statSett, CmdLineLite::Instance().IsKeyDefined( "-mock" ), true );
  if ( const char * autotestPath = CmdLineLite::Instance().GetStringKey( "-autotest" ) )
    systemResult = RunAutoTest( autotestPath, mmData, statSett );
  else if ( const char * logName = CmdLineLite::Instance().GetStringKey( "-scanlog" ) )
    ScanLog( logName, logVersion, mmData, statSett, visSett );
  else if ( const char * logName = CmdLineLite::Instance().GetStringKey( "-playlog" ) )
    LogPlayback( logName, logVersion, mmData, statSett, visSett );
  else
  {
    MessageTrace(
      "Avalable keys:\n"
      "Working mode control:\n"
      "  -playscript script_file.txt\n"
      "  -autotest script_folder\n"
      "  -scanlog log_file.txt\n"
      "  -playlog log_file.txt\n"
      "  -logver [trunk|82x]\n"
      "  -mock\n"
      "  -profile enables pauses to enable profiler\n"
      "Simulation settings:\n"
      "  -waitlimit <wait limit>\n"
      "  -timestepms <simulation time step in ms>\n"
      "Statistics settings:\n"
      "  -ratinglow <low rating range>\n"
      "  -ratinghigh <high rating range>\n"
      "  -imgwidth <image width>\n"
      "  -imgheight <image width>\n"
      "Overview map settings:\n"
      "  -ratingmin <min rating>\n"
      "  -ratingmax <max rating>\n"
      "  -visstep <one visualization pixel cost, ms>\n"
      "  -vismapheight <map image height>\n"
      "  -visratingstep <add another rating scale step>" );
  }

#ifdef NI_ENABLE_INLINE_PROFILER
  if ( profilerOn ) {
    MessageTrace( "Press any key to continue..." );
    _getch();
  }
#endif //NI_ENABLE_INLINE_PROFILER

#ifdef NI_ENABLE_INLINE_PROFILER
  profiler3ui::Shutdown();
#endif //NI_ENABLE_INLINE_PROFILER

  NDb::SessionRoot::InitRoot( 0 );

  GetSystemLog().ClearAllDumpers();

  CrashRptWrapper::UninstallFromProcess();

  return systemResult;
}
