#include "stdafx.h"

#include "SyncTextFileDumper.h"
#include "LogHelpers.h"
#include "FileSystem/FileUtils.h"
#include "LogFileName.h"
#include "System/InlineProfiler.h"


namespace NLogg
{

class SyncTextFileDumper::TestFileRotorThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestFileRotorThread, threading::IThreadJob, BaseObjectMT );

public:
  TestFileRotorThread( SyncTextFileDumper * dumper ) :
  _dumper( dumper ),
  _start( true ),
  _lastRotationHour( 0 ), _lastRotationDay( 0 )
  {
  }


private:
  SyncTextFileDumper *  _dumper;
  bool                  _start;
  int                   _lastRotationHour, _lastRotationDay;

  virtual void Work( volatile bool & isRunning ) {
    while ( isRunning ) {
      threading::Sleep( 300 );

      //FIXME: Accessing integer field in parallel
      int rotationPeriod = RotationPeriod();
      if ( rotationPeriod <= 0 )
        continue;

      timer::DecodedTime t;
      timer::UtcDecodedTime( t );

      int rotationHour = ( t.wHour / rotationPeriod ) * rotationPeriod;

      if ( _start ) {
        _lastRotationHour = rotationHour;
        _lastRotationDay = t.wDay;
        _start = false;
        continue;
      }

      if ( ( t.wDay == _lastRotationDay ) && ( rotationHour == _lastRotationHour ) )
        continue;

      _lastRotationHour = rotationHour;
      _lastRotationDay = t.wDay;

      _dumper->RotateLogParallel();
    }
  }
};






SyncTextFileDumper::SyncTextFileDumper( CLogger * pDefaultLogger, const char * _suffix, const char* _folder ) :
BasicTextFileDumper( pDefaultLogger, "text" ),
suffix( _suffix ? _suffix : "" ),
folder( _folder ? _folder : "" ),
handle( BAD_FILE_VALUE )
{
  if ( _suffix )
    OpenLogFile();

  thread = new threading::JobThread( new TestFileRotorThread( this ), "TextLogRotor", 3000, 65536 );
}



SyncTextFileDumper::~SyncTextFileDumper()
{
  thread = 0;

  CloseLogFile();
}



void SyncTextFileDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::ReadLockGuard readGuard( multiLock );

  NI_PROFILE_HEAVY_BLOCK("After lock");

  if ( handle == BAD_FILE_VALUE )
    return;

  NI_PROFILE_HEAVY_BLOCK("WriteFile");
#if defined( NV_WIN_PLATFORM )
  DWORD dummy = 0;
  WriteFile( handle, headerAndText, strlen( headerAndText ), &dummy, 0 );
#elif defined( NV_LINUX_PLATFORM )
  write( handle, headerAndText, strlen( headerAndText ) );
#endif
}



string SyncTextFileDumper::FileName() const
{
  threading::ReadLockGuard guard( multiLock );
  return logFileName;
}



void SyncTextFileDumper::CloseLogFile()
{
  if ( handle != BAD_FILE_VALUE )
#if defined( NV_WIN_PLATFORM )
    CloseHandle( handle );
#elif defined( NV_LINUX_PLATFORM )
    close( handle );
#endif

  handle = BAD_FILE_VALUE;
}



void SyncTextFileDumper::OpenLogFile()
{
  CloseLogFile();

  for ( int i = 0; i < 100; ++i ) {
    string sfx = suffix;
    if ( i )
      sfx += NI_STRFMT( "(%d)", i );

    logFileName = NDebug::GenerateDebugFileName( sfx.c_str(), "txt", folder.empty() ? 0 : folder.c_str() );

    handle = (FILE_HANDLE)NFile::CreateFileWithDir( logFileName.c_str() );
    if ( handle != BAD_FILE_VALUE )
      break;
  }
  if ( handle == BAD_FILE_VALUE )
      return;

#if defined( NV_WIN_PLATFORM )
  SetFilePointer( handle, 0, 0, FILE_END );
#elif defined( NV_LINUX_PLATFORM )
  lseek( handle, 0, SEEK_END );
#endif

  int tzOffs = timer::TimeZoneOffsetInMinutes();
  char buf[256] = "";
#if defined( NV_WIN_PLATFORM )
  sprintf( buf, "Local time: %+d:%02d UTC\r\nProcessId: %d\r\n", tzOffs / 60, abs( tzOffs ) % 60, GetCurrentProcessId() );
#elif defined( NV_LINUX_PLATFORM )
  snprintf( buf, sizeof( buf ),
    "Local time: %+d:%02d UTC\r\nProcessId: %d\r\n", tzOffs / 60, abs( tzOffs ) % 60, getpid() );
#endif

#if defined( NV_WIN_PLATFORM )
  DWORD dummy = 0;
  WriteFile( handle, buf, strlen( buf ), &dummy, 0 );
#elif defined( NV_LINUX_PLATFORM )
  write( handle, buf, strlen( buf ) );
#endif
}



void SyncTextFileDumper::RotateLogParallel()
{
  threading::WriteLockGuard guard( multiLock );

  if ( logFileName.empty() )
    return;

  OpenLogFile();
}

} //namespace NLogg
