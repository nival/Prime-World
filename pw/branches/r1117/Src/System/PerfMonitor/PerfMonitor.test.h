//!Component('System/PerfMonitor')

#include <System/stdafx.h>

#include "PerfMonitor.h"
#include "System/ThreadHelpers.h"
#include "System/DebugVar.h"
#include "System/sleep.h"
#include "cxxtest/TestSuite.h"

class TestPerfMonitor : public CxxTest::TestSuite
{
public:
  //void TestProcessorsCount()
  //{
  //  PerfMonitor::PerfMonitor perfMon( 2000 );
  //  TS_ASSERT_EQUALS( perfMon.GetCoresCount(), 3 );
  //}

  class LoadThread : public threading::Thread
  {
  public:
    LoadThread() : threading::Thread()  {}
  protected:
    virtual unsigned Work()
    {
      while( isRunning )
      {
        ;
      }
      return 0;
    }

  };

  void TestCPUUsage()
  {
#if defined( NV_WIN_PLATFORM )
    LoadThread loadThread;
    loadThread.Resume();

    PerfMonitor::PerfMonitor perfMon( 100 );
    
    for ( int i = 0; i < 5; ++i )
    {
      nival::sleep( 100 );

      float percent = perfMon.GetCPUUsagePercent();
      float cores = perfMon.GetUsedCores();
      //printf( "CPU usage: %f %% ( %f cores ) \n", percent, cores );
      if ( cores > 0 )
      {
        TS_ASSERT_DELTA( cores, 1.f, 0.1f );
        TS_ASSERT_DELTA( percent/ 100.f, cores / perfMon.GetCoresCount(), 0.1f ); 
      }
      
    }
    loadThread.Stop( true );
    nival::sleep( 50 );
#endif
  }

  void TestDebugVar()
  {
#if defined( NV_WIN_PLATFORM )
    LoadThread loadThread;
    loadThread.Resume();

    PerfMonitor::PerfMonitor perfMon( 100, "", "Perf_CPU" );

    for ( int i = 0; i < 5; ++i )
    {
      nival::sleep( 100 );

      //printf( "CPU usage: %f %% ( %f cores ) \n", perfMon.GetCPUUsagePercent(), perfMon.GetUsedCores() );
      if ( perfMon.GetUsedCores() > 0 )
      {
        NDebug::IDebugVar* dv = NDebug::FindDebugVar( L"Perf_CPU" );
        TS_ASSERT ( dv );
        TS_ASSERT_DELTA( ((NDebug::DebugVar<float>*)dv)->GetValue(), perfMon.GetCPUUsagePercent(), 5.f );
      }

    }
    loadThread.Stop( true );
    nival::sleep( 50 );
#endif
  }

};

