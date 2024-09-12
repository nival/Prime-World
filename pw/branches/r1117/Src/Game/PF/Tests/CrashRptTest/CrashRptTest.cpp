#include "System/CrashRptWrapper.h"
#include "System/CmdLineLite.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"
#include <time.h>

static int DoTheStackOverflow( int depth, char * ptr, int size )
{
  if ( !depth )
    return 0;

  int sum = 0;
  for( int i = 0; i < size; ++i )
    sum += ptr[i];
  char buf[4096];
  memset( buf, 0, 4096 );
  sum += DoTheStackOverflow( depth - 1, buf, 4096 );
  return sum;
}



static void DoTheGPF( FILE * logf ) {
  int * nullPtr = 0;
  fprintf( logf, "Writing address 0x%08x...\n", (int)nullPtr ); //Block compiler optimizations
  fflush( logf );
  printf( "Writing address 0x%08x...\n", (int)nullPtr );
  *nullPtr = 0;
}


static void DivideByZero( FILE * logf ) {
  //Block compiler optimizations
  int zero = strtol( "0", 0, 10 );
  fprintf( logf, "Dividing by %d...\n", zero );
  fflush( logf );
  printf( "Dividing by %d...\n", zero );
  fprintf( logf, "Result: %d", (int)logf / zero );
}


static void CrashFun( const char * type, FILE * logf )
{
  if ( !_stricmp( type, "gpf" ) )
    DoTheGPF( logf );
  else if ( !_stricmp( type, "zero") )
    DivideByZero( logf );
  else if ( !_stricmp( type, "stack") ) {
    fprintf( logf, "Flooding stack...\n" );
    fflush( logf );
    printf( "Flooding stack...\n" );
    fprintf( logf, "Result: %d", DoTheStackOverflow( 1024 * 1024 * 1024, 0, 0 ) );
  }
  else {
    printf( "Unknwon crash type '%s'\n", type );
    fprintf( logf, "Unknwon crash type '%s'\n", type );
  }
}



int main( int argc, char * argv[] )
{
  printf( "CrashRpt test tool\n\n" );

  CmdLineLite::Instance().Init( argc, argv );

  const char * defaultUrl = "http://SITE.com/upload/";

  const char * type = CmdLineLite::Instance().GetStringKey( "-type", 0 );
  if ( !type ) {
    printf(
      "Command-line options:\n"
      "  -type <gpf|zero|stack>\n"
      "    Set crash type. GPF is the default.\n"
      "Optional command-line switches:\n"
      "  -url <URL>\n"
      "    Set the URL of the crash report server.\n"
      "    Default is %s\n"
      "  -manual\n"
      "    DO NOT send report automatically, show GUI window instead.\n"
      "  -project <Project Name>\n"
      "    Set Crash Reporting project name, 'Test' is default.\n"
      "  -dev\n"
      "    Logging send report progress"
      "  -send_recent_reports\n"
      "    Try to send queued reports"
      "\n",
      defaultUrl
      );
    printf( "ERROR: Crash type is not set!\n" );
    return 0;
  }

  time_t t = 0;
  time( &t );

  const tm * lt = localtime( &t );
  string logname = NI_STRFMT( "TestLogFile-%02d%02d%02d-%02d%02f%02d.txt", 1900 + lt->tm_year, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec );
  FILE * f = fopen( logname.c_str(), "wt" );
  if ( !f ) {
    printf( "ERROR: Could not create log file '%s'", logname.c_str() );
    return 0;
  }

  fprintf( f, "Starting crashrpt test...\n" );

  const char * url = CmdLineLite::Instance().GetStringKey( "-url", defaultUrl );
  const bool nogui = !CmdLineLite::Instance().IsKeyDefined( "-manual" );
  const bool dev = CmdLineLite::Instance().IsKeyDefined( "-dev" );
  const char * project = CmdLineLite::Instance().GetStringKey( "-project", "Test" );
  const bool sendRecentReports = CmdLineLite::Instance().IsKeyDefined( "-send_recent_reports" );

  fprintf( f, "URL: %s\n", url );
  fprintf( f, "Project: %s\n", project );
  fprintf( f, "Type: %s\n", type );
  fprintf( f, "Send report without GUI: %s\n", nogui ? "yes" : "no" );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), project, "private", 0, 0, 0, 0 );

  CrashRptWrapper::InstallForProcess( url, true, nogui, project, 0, dev, sendRecentReports );
  CrashRptWrapper::AddFileToReport( logname.c_str(), "Test Log File" );
  CrashRptWrapper::AddTagToReport( "TestTag", "Test tag value" );

  fflush( f );
  fflush( stdout );

  CrashFun( type, f );

  fclose( f );

  CrashRptWrapper::UninstallFromProcess();
  return 0;
}
