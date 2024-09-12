//!Component("System/Random")
//!Component("System/Threading")
#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "TSList.h"
#include "Win32Random.h"
#include "sleep.h"
#include "Thread.h"
#include "ThreadHelpers.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define THREAD_BEGIN( className )                                                 \
struct className                                                                  \
{                                                                                 \
  threading::ProcessingThread<className> *pThread;                                \
  className() { pThread = new threading::ProcessingThread<className>( *this ); }  \
  ~className() { pThread->Stop( true, 1000 ); delete pThread; }                   \
  DWORD Process( volatile bool& isRunning )                                 \
  {

#define THREAD_END      \
    }                   \
};

class TSListTests : public CxxTest::TestSuite
{
public:
  static int bytesProduced;
  static int bytesConsumed;
  static byte *sampleData;

  static SPSCQueue<int> queue2; 
  static SPSCQueue<CObj<Stream>, Stream*> queue3; 

  THREAD_BEGIN( ProducerThread2 )
    while( isRunning )
    {
      int n = NWin32Random::Random( 10, 512 );
      queue2.Enqueue( n );
      ++bytesProduced;
    }
    return 0;
  THREAD_END;
  THREAD_BEGIN( ConsumerThread2 )
    while( isRunning )
    {
      int n = -1;
      while ( queue2.Dequeue( n ) )
      {
        //TS_ASSERT_LESS_THAN_EQUALS( n, 512 );
        TS_ASSERT( n <= 512 );
        //TS_ASSERT_LESS_THAN_EQUALS( 10, n );
        TS_ASSERT( 10 <= n );
        ++bytesConsumed;
      }
    }
    return 0;
  THREAD_END;

  void TestTSList2()
  {
    for( int i = 0; i < 5; ++i )
    {

      bytesProduced = 0;
      bytesConsumed = 0;

      ProducerThread2* prod = new ProducerThread2;
      ConsumerThread2* cons = new ConsumerThread2;

      nival::sleep( 1000 );

      delete prod;
      delete cons;

      TS_ASSERT_EQUALS( bytesProduced, bytesConsumed );
    }
  }


  THREAD_BEGIN( ProducerThread3 )
      while( isRunning )
      {
        int size = NWin32Random::Random( 4, 256 );
      Stream* pS = new MemoryStream( size );
        pS->Write( sampleData, size );
        bytesProduced += size;

      queue3.Enqueue( pS );
        pS = 0;
      }
      return 0;
  THREAD_END;
  THREAD_BEGIN( ConsumerThread3 )
      while( isRunning )
      {
          CObj<Stream> pS;
      while( queue3.Dequeue( pS ) )
          {
          TS_ASSERT( memcmp( pS->GetBuffer(), sampleData, pS->GetSize() ) == 0 );
          bytesConsumed += pS->GetSize();

         // int* pObjCount = (int*)(pS.GetPtr()) + 2;
         // TS_ASSERT_EQUALS( 1, *pObjCount );
        pS = 0;
        }
      }
      return 0;
  THREAD_END;

  void TestTSList3()
  {
    sampleData = new byte[ 512 ];
    for( int i = 0; i < 512; ++i )
      sampleData[i] = i & 0xff;

    for( int i = 0; i < 5; ++i )
  {

    bytesProduced = 0;
    bytesConsumed = 0;

      ProducerThread3* prod = new ProducerThread3;
      ConsumerThread3* cons = new ConsumerThread3;

      nival::sleep( 1000 );

    delete prod;
    delete cons;

    TS_ASSERT_EQUALS( bytesProduced, bytesConsumed );
    }

    delete[] sampleData;
  }


};

int TSListTests::bytesProduced = 0;
int TSListTests::bytesConsumed = 0;
byte *TSListTests::sampleData = 0;
SPSCQueue<int> TSListTests::queue2; 
SPSCQueue<CObj<Stream>, Stream*> TSListTests::queue3(1024); 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

