//!Component('System/SyncPrimitives')
//!Component('System/Threading')
//!Component("System/Crc32Utils")
//!Component('System/Random')
//!Component('System/InlineProfiler')

#include "stdafx.h"

#include "MultiReaderLock.h"
#include "RandomGenerator.h"
#include "Crc32Checksum.h"
#include "JobThread.h"
#include "sleep.h"
#include "cxxtest/TestSuite.h"


class Test_MultiReaderLock :  public CxxTest::TestSuite
{
public:
  struct SSharedObject
  {
    vector<byte>  bytes;
    unsigned long crc;

    threading::MultiReaderLock multilock;
    threading::Mutex mutex;

    SSharedObject() : crc( 0 ) {}

    void RollData( NRandom::RandomGenerator & rnd ) {
      int size = rnd.Next( 500, 5000 );
      bytes.clear();
      bytes.resize( size );
      for ( int i = 0; i < bytes.size(); ++i )
        bytes[i] = rnd.Next( 256 ) & 0xff;
    }

    unsigned long CalcCrc() const {
      if ( bytes.empty() )
        return 0;

      Crc32Checksum crc;
      crc.Add( &bytes[0], bytes.size() );
      return crc.Get();
    }
  };


  class Job : public threading::IThreadJob, public BaseObjectMT {
    vector<SSharedObject> & _data;
    bool _useMutex;
    int _index;

  public:
    NI_DECLARE_REFCOUNT_CLASS_2( Job, threading::IThreadJob, BaseObjectMT );

    Job( vector<SSharedObject> & data, bool useMutex, int index ) : _data( data ), _useMutex( useMutex ), _index( index ) {}

    virtual void Work( volatile bool & isRunning ) {
      timer::Time start = timer::Now();
      //printf( "%.2f: Thread %d started\n", start, _index );

      NRandom::RandomGenerator rnd( _index * 11 );

      QWORD reads = 0, writes = 0;
      while ( isRunning )
      {
        int objectIdx = rnd.Next( _data.size() );
        SSharedObject & object = _data[objectIdx];

        if ( rnd.Roll( 99 ) ) {
          ReadCase( object );
          ++reads;
        }
        else {
          WriteCase( object, rnd );
          ++writes;
        }
      }

      timer::Time finish = timer::Now();
      printf( "%.2f: Thread %d results: %.1fk reads/second, %.1fk writes/second \n",
        finish - start, _index, reads * 1e-3 / ( finish - start ), writes * 1e-3 / ( finish - start )  );
    }


    void ReadCase( const SSharedObject & object ) {
      if ( _useMutex )
        object.mutex.Lock();
      else
        object.multilock.LockForRead();

      unsigned long calculatedCrc = object.CalcCrc();
      unsigned long storedCrc = object.crc;

      if ( _useMutex )
        object.mutex.Unlock();
      else
        object.multilock.UnlockAfterRead();

      TS_ASSERT_EQUALS( calculatedCrc, storedCrc );
    }


    void WriteCase( SSharedObject & object, NRandom::RandomGenerator & rnd ) {
      if ( _useMutex )
        object.mutex.Lock();
      else
        object.multilock.LockForWrite();

      object.RollData( rnd );
      object.crc = object.CalcCrc();

      if ( _useMutex )
        object.mutex.Unlock();
      else
        object.multilock.UnlockAfterWrite();
    }
  };


  void RunLoadTest( int mseconds, int threadNumber, int dataObjectNumber, bool useMutexes )
  {
    printf( "\nRunning mini load-test for %.1f second(s)...\n", mseconds * 1e-3 );
    printf(
      "Using %s\n"
      "Threads: %d\n"
      "Data objects:%d\n",
      useMutexes ? "mutexes" : "multilocks", threadNumber, dataObjectNumber );

    vector<SSharedObject> data( dataObjectNumber );

    NRandom::RandomGenerator rnd( 100500 );
    for ( int i = 0; i < data.size(); ++i ) {
      data[i].RollData( rnd );
      data[i].crc = data[i].CalcCrc();
    }

    vector<StrongMT<threading::JobThread> > threads( threadNumber );

    for ( int i = 0; i < threads.size(); ++i )
      threads[i] = new threading::JobThread( new Job( data, useMutexes, i ), "TestJob" );

    nival::sleep( mseconds );

    for ( int i = 0; i < threads.size(); ++i )
      threads[i]->AsyncStop();

    threads.clear();
  }

  const static int mseconds = 4500;

  void test_mutexes_many_slots()      { RunLoadTest( mseconds, 4, 50, true ); }
  void test_multilocks_many_slots()   { RunLoadTest( mseconds, 4, 50, false ); }

  void test_mutexes_few_slots()       { RunLoadTest( mseconds, 4, 8, true ); }
  void test_multilocks_few_slots()    { RunLoadTest( mseconds, 4, 8, false ); }

  void test_mutexes_little_slots()    { RunLoadTest( mseconds, 4, 2, true ); }
  void test_multilocks_little_slots() { RunLoadTest( mseconds, 4, 2, false ); }
};
