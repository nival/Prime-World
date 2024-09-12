//!Component("System/Random")
//!Component('System/Threading')
#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "Win32Random.h"
#include "sleep.h"
#include "Thread.h"
#include "ThreadHelpers.h"


class ThreadTestSuite : public CxxTest::TestSuite 
{
public:
  struct TestThread
  {
    threading::ProcessingThread<TestThread> *pThread;

    TestThread() 
    {
      pThread = new threading::ProcessingThread<TestThread>( *this );
    }
    ~TestThread() 
    {
      pThread->Stop( true, 1000 );
      delete pThread;
    }

    DWORD Process( volatile bool& isRunning )
    {
      while( isRunning )
      {
        int size = NWin32Random::Random( 4, 256 );
        size++;
        nival::sleep( 100 );
      }
      return 0;
    }

  };

    void testAddition( void )
    {
      TestThread();
      nival::sleep(350);
    }
};
