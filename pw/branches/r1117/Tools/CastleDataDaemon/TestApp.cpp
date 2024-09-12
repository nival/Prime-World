#include <stdio.h>
#include <windows.h>
#include <shlobj.h>
#include <conio.h>

#define MY_EXPORT_API __cdecl

static const char * ModuleName = "CastleDataDaemon.dll";

static const char * Name_CastleDataDaemonStart = "CastleDataDaemonStart";
static const char * Name_CastleDataDaemonStop = "CastleDataDaemonStop";
static const char * Name_CastleDataDaemonClose = "CastleDataDaemonClose";

typedef void * MY_EXPORT_API  TStartCall( const wchar_t *, unsigned, unsigned );
typedef int MY_EXPORT_API     TStopCall( void * );
typedef void MY_EXPORT_API    TCloseCall( void * );

static TStartCall *   s_StartFunc;
static TStopCall *    s_StopFunc;
static TCloseCall *   s_CloseCall;


int main( int argc, char ** argv )
{
  HMODULE hdll = LoadLibrary( ModuleName );
  if ( !hdll )
  {
    printf( "Could not load '%s'. error=%d\n", ModuleName, GetLastError() );
    return 1;
  }

  WCHAR path[MAX_PATH];
  SHGetFolderPathW( NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, path );
  wcscat( path, L"\\My Games\\Prime World" );

  s_StartFunc = ( TStartCall * )GetProcAddress( hdll, Name_CastleDataDaemonStart );
  s_StopFunc = ( TStopCall * )GetProcAddress( hdll, Name_CastleDataDaemonStop );
  s_CloseCall = ( TCloseCall * )GetProcAddress( hdll, Name_CastleDataDaemonClose );

  printf( "Starting...\n" );
  printf( "Working path: '%S'\n", path );
  printf( "Ptrs: start=%08x, stop=%08x, close=%08x\n", s_StartFunc, s_StopFunc, s_CloseCall );

  void * handle = (*s_StartFunc)( path, 1024 * 256, 4 );
  
  printf( "Press any key to stop...\n" );
  _getch();

  printf( "Stopping...\n" );

  for( ;; )
  {
    int stopResult = (*s_StopFunc)( handle );
    if ( stopResult )
      break;
  }

  printf( "Closing...\n" );
  (*s_CloseCall)( handle );

  FreeLibrary( hdll );
  
  return 0;
}
