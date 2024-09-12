//!Component("System/Logging")
//!Component("System/SystemLog")
//!Component("System/Dumpers")
//!Component("System/ServerDumpers")
//!Component("System/LogFileName")
//!Component("System/FileSystem/FileUtils")

#include "../stdafx.h"
#include "../Logger.h"
#include "../ServerStdOutDumper.h"
#include "../DebugTraceDumper.h"
//#include "../ServerTextFileDumper.h"
#include "../LogFileName.h"
#include "../FileSystem/FileUtils.h"

#include "cxxtest/TestSuite.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Test_ChannelLogging: public CxxTest::TestSuite
{
public:
  void setUp()
  {
    //printf("\nTest_ChannelLogging start\n");
  }

  void tearDown()
  {
    //printf("\nTest_ChannelLogging finish\n");
  }

  void test_1()
  {
    using namespace NLogg;

    CChannelLogger chanLogger( "CHAN_ONE" );

    CServerStdOutDumper* _stdoutDumper = new CServerStdOutDumper( &chanLogger ) ;
    //CServerTextFileDumper* _textLogDumper = new CServerTextFileDumper( &chanLogger ) ;
    CDebugTraceDumper* _debugTraceDumper = new CDebugTraceDumper( &chanLogger ) ;

    NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "PW_TEST", "product", 0, 0, 0, 0);
    //_textLogDumper->SetFileName("Chan_log");

    chanLogger.AddChannel("CHAN_1"); // default dumpers
    //chanLogger.DUMP_CHANNELS();

    //chanLogger.AddChannel("CHAN_2", *_textLogDumper );
    //chanLogger.DUMP_CHANNELS();

    chanLogger.SetDefaultMinLevelFilter( LEVEL_ASSERT ); // by default accept "asserts & criticals" only

    chanLogger.AddChannel("CHAN_3", *_stdoutDumper, *_debugTraceDumper); // should inherit "critical-only"
    //chanLogger.DUMP_CHANNELS();

    chanLogger.RemoveChannel("CHAN_2");
    //chanLogger.DUMP_CHANNELS();

    chanLogger.TEST_LOG(__FILE__, __LINE__, LEVEL_ASSERT, "msg_1", "CHAN_1");
    chanLogger.TEST_LOG(__FILE__, __LINE__, LEVEL_ASSERT, "msg_2", "CHAN_2");
    chanLogger.TEST_LOG(__FILE__, __LINE__, LEVEL_DEBUG,  "msg_3: NON-CRIT (FAIL!)", "CHAN_3");
    chanLogger.TEST_LOG(__FILE__, __LINE__, LEVEL_ASSERT, "msg_3", "CHAN_3");
    chanLogger.TEST_LOG(__FILE__, __LINE__, LEVEL_ASSERT, "msg_158", "CHAN_158");
    chanLogger.TEST_LOG(__FILE__, __LINE__, LEVEL_ASSERT, "msg_ALL");

    //NI_ASSERT();
    delete _stdoutDumper;
    //delete _textLogDumper;
    delete _debugTraceDumper;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Test_2_GlobalLogging()
  {
    printf("\nTEST 2: global\n");

    ScopedPtr<NLogg::CServerStdOutDumper> g_stdoutDumper;
    //ScopedPtr<NLogg::CServerTextFileDumper> g_textLogDumper;
    ScopedPtr<NLogg::CDebugTraceDumper> g_debugTraceDumper;

    Reset( g_stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
    //Reset( g_textLogDumper, new NLogg::CServerTextFileDumper( &GetSystemLog() ) );
    Reset( g_debugTraceDumper, new NLogg::CDebugTraceDumper( &GetSystemLog() ) );

    //g_textLogDumper->SetFileName("Chan_Global");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // DAN TEST: create channels with different dumper sets
    GetSystemLog().AddChannel("CHAN_1", *g_stdoutDumper, *g_debugTraceDumper );
    //GetSystemLog().AddChannel("CHAN_2", *g_textLogDumper, *g_debugTraceDumper );
    // this channel will only take ASSERT and higher severity:
    GetSystemLog().AddChannel("CHAN_CRIT", *g_stdoutDumper, NLogg::GetFromMinLevelMask(NLogg::LEVEL_MESSAGE));
      
    LOG_D("CHAN_1").Trace("test channel 1");
    LOG_D("CHAN_2") << "test channel 2";
    LOG_D("CHAN_UNK") << "test channel UNKNOWN (FAIL!)";
    LOG_D("CHAN_CRIT") << "test channel crit: NON-CRITICAL msg (FAIL!)";
    LOG_M("CHAN_CRIT") << "test channel crit: critical msg";
    //LOG_DEFAULT_D().Trace("test channel ALL");

    GetSystemLog().SetChannelMinLevelFilter("CHAN_CRIT", NLogg::LEVEL_DEBUG); // DEBUG & higher
    LOG_D("CHAN_CRIT").Trace("test channel crit: filter off debug msg (ok now)");

    // set string header to "severity only"
    //GetSystemLog().SetHeaderFormat( NLogg::CLoggerBuffer::LOGHEAD_SEVERITY );
    //LOG_DEFAULT_D().Trace("(format = severity only)");

    // back to default format:  "(thread) time [channel] severity " 
    GetSystemLog().SetHeaderFormat( );
    //LOG_DEFAULT_D().Trace("(format = default)");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Test_3_LocalLogging()
  {
    printf("\nTEST 3: local\n");

    // NLogg::CLoggerStream is deprecated!
    
    /*
    NLogg::CLoggerStream *logStream = new NLogg::CLoggerStream( 0, "ChanHybrid", NLogg::LEVEL_MESSAGE );
    if( !logStream )
      return;

    ScopedPtr<NLogg::CServerStdOutDumper> g_stdoutDumper;
    //ScopedPtr<NLogg::CServerTextFileDumper> g_textLogDumper;
    ScopedPtr<NLogg::CDebugTraceDumper> g_debugTraceDumper;

    Reset( g_stdoutDumper, new NLogg::CServerStdOutDumper( logStream ) );
    //Reset( g_textLogDumper, new NLogg::CServerTextFileDumper( logStream ) );
    Reset( g_debugTraceDumper, new NLogg::CDebugTraceDumper( logStream ) );
   
    //g_textLogDumper->SetFileName( "Chan_Local" );

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // DAN TEST: create channels with different dumper sets
    logStream->AddChannel( "CHAN_1", *g_stdoutDumper, *g_debugTraceDumper );
    //logStream->AddChannel( "CHAN_2", *g_textLogDumper, *g_debugTraceDumper );

    logStream->SetDefaultMinLevelFilter( NLogg::LEVEL_MESSAGE ); // MESSAGE & higher
    // this channel should only take ASSERT and higher severity (inherited from default filter):
    logStream->AddChannel( "CHAN_CRIT", *g_stdoutDumper );
      
    LOGL_D( logStream, "CHAN_1" ).Trace("test channel 1");
    LOGL_D( logStream, "CHAN_2" ) << "test channel 2";
    LOGL_D( logStream, "CHAN_UNK" ) << "test channel UNKNOWN (FAIL!)";
    LOGL_D( logStream, "CHAN_CRIT" ) << "test channel crit: NON-CRITICAL msg (FAIL!)";
    LOGL_M( logStream, "CHAN_CRIT" ) << "test channel crit: critical msg";
    LOGL_DEFAULT_D( logStream ).Trace("test channel ALL");

    logStream->SetChannelMinLevelFilter( "CHAN_CRIT", NLogg::LEVEL_DEBUG ); // DEBUG & higher
    LOGL_D( logStream, "CHAN_CRIT" ).Trace("test channel crit: filter off debug msg (ok now)");

    // set string header to "severity only"
    logStream->SetHeaderFormat( NLogg::CLoggerBuffer::LOGHEAD_SEVERITY );
    LOGL_DEFAULT_D( logStream ).Trace("(format = severity only)");

    // back to default format:  "(thread) time [channel] severity " 
    logStream->SetHeaderFormat( );
    LOGL_DEFAULT_D( logStream ).Trace("(format = default)");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    delete logStream;
    */
  }


  void None()
  {
    TS_ASSERT(0);
    printf("ASSERT: NEVER CALLED\n");
  }
};

