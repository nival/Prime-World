#include <stdio.h>
#include <assert.h>
#include <process.h>
#include <windows.h>
#include "worker.h"

static void WorkerThread( void * arg )
{
  ThreadContext * ctx = (ThreadContext *)arg;
  ctx->Work();
}



#define MY_EXPORT __declspec(dllexport)
#define MY_EXPORT_API __cdecl

extern "C"
{

MY_EXPORT void * MY_EXPORT_API CastleDataDaemonStart( const wchar_t * _userDirectory, unsigned _maxFileSize, unsigned _maxFilesPerSecond )
{
  //printf( "CastleDataDaemonStart!\n" );

  ThreadContext * ctx = new ThreadContext( _userDirectory, _maxFileSize, _maxFilesPerSecond );

  _beginthread( &WorkerThread, 0, ctx );

  return ctx;
}


MY_EXPORT int MY_EXPORT_API CastleDataDaemonStop( void * arg )
{
  //printf( "CastleDataDaemonStop!\n" );

  ThreadContext * ctx = (ThreadContext *)arg;

  ctx->Stop();
  return ctx->StillRunning() ? 0 : 1;
}


MY_EXPORT void MY_EXPORT_API CastleDataDaemonClose( void * arg )
{
  //printf( "CastleDataDaemonClose!\n" );

  ThreadContext * ctx = (ThreadContext *)arg;

  assert( ctx->Stopping() );
  assert( !ctx->StillRunning() );

  if ( !ctx->StillRunning() )
    delete ctx;
}

}

