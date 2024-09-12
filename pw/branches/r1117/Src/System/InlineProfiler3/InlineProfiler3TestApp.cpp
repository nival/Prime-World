#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "System/InlineProfiler.h"
#include "System/HPTimer.h"
#include "System/JobThread.h"
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"

#include "System/DebugTraceDumper.h"
#include "System/ServerStdOutDumper.h"
#include "System/ThreadNames.h"

int FooWithAllocs()
{
  NI_PROFILE_HEAVY_FUNCTION;

  string buf;
  buf = "InlineProfiler3 InlineProfiler3";
  return buf.length();
}



int Foo1( bool sleep )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( sleep )
    Sleep( 1 );

  int sum = 0;
  for ( int i = 0; i < 10000; ++i )
    sum += rand();

  sum += FooWithAllocs();

  return sum;
}



int Foo2( bool sleep )
{
  NI_PROFILE_FUNCTION_MEM;

  int sum = 0;
  for ( int i = 0; i < 50; ++i )
    sum += Foo1( sleep );
  return sum;
}



void Foo3( bool canExitByKeyb )
{
  int sum = 0;
  while( true )
  {
    {
      NI_PROFILE_BLOCK_MEM( "Main" );

      {
        NI_PROFILE_BLOCK( "Int" );
        Sleep( 10 );
      }

      sum += Foo2( true );

      Sleep( 10 );
    }
    {
      NI_PROFILE_BLOCK( "Main2" );
      Sleep( 1 );
    }

    Sleep( 50 );

    if ( canExitByKeyb && _kbhit() )
    {
      char c = _getch();
      if ( c == 'q' )
      {
        printf( "Exiting...\n" );
        break;
      }
      else
        _ungetch( c );
    }
  }
}




class QuickTestThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( QuickTestThread, threading::IThreadJob, BaseObjectMT );

public:
  QuickTestThread() {}

  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    {
      NI_PROFILE_BLOCK_MEM( "QuickThreadMain" );
      printf( "Quick thread started! Counting to ten...\n" );
      for ( int i = 0; i < 10; ++i )
      {
        NI_PROFILE_BLOCK( "QuickThreadInner" );
        printf( "Quick thread: %i\n", i );
        Sleep( 1 );
      }
    }
  }
};




void MainThreadFoo()
{
  //CObj<threading::JobThread> quickThread;
  StrongMT<threading::JobThread> quickThread;

  int sum = 0;
  while( true )
  {
    {
      NI_PROFILE_BLOCK_MEM( "Main" );

      {
        NI_PROFILE_BLOCK( "Int" );
        Sleep( 10 );
      }

      sum += Foo2( true );

      Sleep( 10 );
    }

    Sleep( 50 );

    if ( _kbhit() )
    {
      char c = _getch();
      if ( c == 'p' )
      {
        printf( "Showing UI...\n", sum );
        profiler3ui::Show( NULL );
      }
      else if ( c == 's' )
      {
        printf( "Starting quick thread...\n" );
        quickThread = new threading::JobThread( new QuickTestThread, "QuickThread" );
      }
      else
        _ungetch( c );
    }
  }
}


class TestThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestThread, threading::IThreadJob, BaseObjectMT );

public:
  TestThread( char _canExitByKeyb ) :
  canExitByKeyb( _canExitByKeyb ) {}

  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    Foo3( canExitByKeyb );
  }

private:
  char  canExitByKeyb;
};



int main( int argc, const char ** argv )
{
  threading::SetDebugThreadName( "Main" );

  NLogg::CDebugTraceDumper debugTraceDumper( &GetSystemLog() );
  NLogg::CServerStdOutDumper stdOutDumper( &GetSystemLog(), NLogg::LEVEL_DEBUG );

  profiler3::GetControl()->Setup( profiler3::SSettings() ); //Using default settings...

  NI_PROFILE_THREAD;

  profiler3ui::Init();

  //list<CObj<threading::JobThread> > threads;
  list<StrongMT<threading::JobThread> > threads;
  for ( int i = 0; i < 3; ++i )
    threads.push_back( new threading::JobThread( new TestThread( !i ), NStr::StrFmt( "TestThread%d", i ) ) );

  MainThreadFoo();

  profiler3ui::Shutdown();

  return 0;
}
