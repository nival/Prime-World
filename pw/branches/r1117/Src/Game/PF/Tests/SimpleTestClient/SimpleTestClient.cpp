#include "stdafx.h"

#include "ForgeRollTest.h"
#include "CensorshipTest.h"
#include "GStatTest.h"

#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include <System/DebugTraceDumper.h>
#include "System/FileSystem/FileUtils.h"
#include "System/LogFileName.h"
#include "System/BSUtil.h"
#include "System/CrashRptWrapper.h"
#include "System/CmdLineLite.h"
#include "System/ConfigFiles.h"

#include "Version.h"
#include "System/InlineProfiler.h"


void Test()
{
  if ( forge_roll_test::Test() )
    return;
  
  if ( censorship_test::Test() )
    return;

  if ( gstat_test::Test() )
    return;

  ErrorTrace( "Nothing to test!" );
}



int main( int argc, char * argv[] )
{
  setlocale( LC_ALL, "Russian" );

  CmdLineLite::Instance().Init( argc, argv );

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "SimpleTestClient", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdoutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );

  StrongMT<NLogg::BasicTextFileDumper> textLogDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "test" );

  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper;
  if ( IsDebuggerPresent() )
    debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );

  NProfile::Init( "" );
  NGlobal::ExecuteConfig( "server.cfg", NProfile::FOLDER_GLOBAL );

  Test();

  GetSystemLog().ClearAllDumpers();

  return 0;
}
