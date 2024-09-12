//!Component("System/Random")
//!Component("System/Threading")
//!Component("System/Streams")

//#define TS_CLASSIC_QUEUE
#pragma  warning( disable : 4345 )
#include "stdafx.h"
#include "TSList.h"
#include "Win32Random.h"
#include "ThreadHelpers.h"
#include "TSPool.h"
#include "sleep.h"
#include "cxxtest/TestSuite.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TSPoolTests : public CxxTest::TestSuite
{
public:
  static TSPool<MemoryStream> tsPool; 
  static byte *sampleData;
  static int processedCount;

  static threading::Mutex lock;
  static SPSCQueue<MemoryStream*> tsq;

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
      int count = 0;
      while( isRunning )
      {
        MemoryStream* pS = tsPool.Alloc();
        TS_ASSERT( pS );
        TS_ASSERT( pS->GetSize() == 0 );
        int size = NWin32Random::Random( 4, 256 );
        pS->Write( sampleData, size );
        nival::sleep( 0 );
        TS_ASSERT( pS->GetSize() == size );
        pS->SetSize( 0 );
        tsPool.Release( pS );
        pS = 0;
        ++count;
      }
      processedCount += count;
      return 0;
    }
  };

  struct ProducerThread
  {
    threading::ProcessingThread<ProducerThread> *pThread;

    ProducerThread() 
    {
      pThread = new threading::ProcessingThread<ProducerThread>( *this );
    }
    ~ProducerThread() 
    {
      pThread->Stop( true, 1000 );
      delete pThread;
    }

    DWORD Process( volatile bool& isRunning )
    {
      int count = 0;
      while( isRunning )
      {
        MemoryStream* pS = tsPool.Alloc();
        TS_ASSERT( pS );
        TS_ASSERT( pS->GetSize() == 0 );
        int size = NWin32Random::Random( 4, 256 );
        pS->Write( sampleData, size );

        lock.Lock();
        tsq.Enqueue( pS );
        lock.Unlock();
      }
      processedCount += count;
      return 0;
    }
  };

  struct ConsumerThread
  {
    threading::ProcessingThread<ConsumerThread> *pThread;

    ConsumerThread() 
    {
      pThread = new threading::ProcessingThread<ConsumerThread>( *this );
    }
    ~ConsumerThread() 
    {
      pThread->Stop( true, 1000 );
      delete pThread;
    }

    DWORD Process( volatile bool& isRunning )
    {
      int count = 0;
      while( isRunning )
      {
        MemoryStream* pS = 0;
        lock.Lock();
        while( tsq.Dequeue( pS ) )
        {
          lock.Unlock();
          pS->SetSize( 0 );
          tsPool.Release( pS );
          ++count;
          lock.Lock();
        }

        lock.Unlock();
      }
      processedCount += count;
      return 0;
    }
  };

  void BasicTestRound()
  {
    vector<TestThread*> threads;

    processedCount = 0;
    int numThreads = 4;
    for ( int i = 0; i < numThreads; ++i )
    {
      threads.push_back( new TestThread() );
    }

    nival::sleep( 1000 );

    for ( int i = 0; i < numThreads; ++i )
    {
      delete threads[i];
    }
    //TS_OUTPUT( NStr::StrFmt( "Processed: %d streams per second\n", processedCount ) );
  }

  void ProducerConsumerTestRound()
  {
    vector<TestThread*> threads;

    processedCount = 0;
    ProducerThread* prod = new ProducerThread();
    ConsumerThread* cons = new ConsumerThread();

    nival::sleep( 1000 );

    delete prod;
    delete cons;
    //TS_OUTPUT( NStr::StrFmt( "Processed: %d streams per second\n", processedCount ) );
  }

  void TestTSList()
  {
    sampleData = new byte[ 512 ];
    for( int i = 0; i < 512; ++i )
      sampleData[i] = i & 0xff;

    for( int i = 0; i < 5; ++i )
    {

      BasicTestRound();
      tsPool.~TSPool<MemoryStream>();
      new (&tsPool) TSPool<MemoryStream>();
    }

    delete[] sampleData; 
  }

  void TestTSList2()
  {
    sampleData = new byte[ 512 ];
    for( int i = 0; i < 512; ++i )
      sampleData[i] = i & 0xff;

    for( int i = 0; i < 5; ++i )
    {

      ProducerConsumerTestRound();
      tsq.~SPSCQueue<MemoryStream*>();
      new(&tsq) SPSCQueue<MemoryStream*>();
      tsPool.~TSPool<MemoryStream>();
      new (&tsPool) TSPool<MemoryStream>();
    }

    delete[] sampleData; 
  }

};

TSPool<MemoryStream> TSPoolTests::tsPool;
byte* TSPoolTests::sampleData = 0;
int TSPoolTests::processedCount = 0;
SPSCQueue<MemoryStream*> TSPoolTests::tsq( 4096 );
threading::Mutex TSPoolTests::lock;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

