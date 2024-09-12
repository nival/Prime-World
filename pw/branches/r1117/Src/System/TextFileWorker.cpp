#include "stdafx.h"
#include "TextFileWorker.h"
#include "System/InlineProfiler.h"
#include "System/FileSystem/FileUtils.h"
#include "System/LogHelpers.h"
#include "System/LogFileName.h"

namespace NLogg
{

TextFileWorkerThread::TextFileWorkerThread( const char * _suffix, size_t _bufferLimit, const char* _folder ) :
bufferLimit( _bufferLimit ),
suffix( _suffix ? _suffix : "" ),
justStarted( true ), reopenFile( false ),
evtNewMessage( false, true ),
threadsafeSkippedMessages( 0 ), skippedMessages( 0 ),
lastRotationHour( 0 ), lastRotationDay( 0 ),
handle( BAD_FILE_VALUE ),
folder( _folder ? _folder : "" )
{
  inputBuffer.reserve( bufferLimit );
  workingBuffer.reserve( bufferLimit );
}



TextFileWorkerThread::~TextFileWorkerThread()
{
  CloseLogFile();
}



void TextFileWorkerThread::PushMessage( const char * text )
{
  NI_PROFILE_HEAVY_FUNCTION;

  {
    const size_t len = strlen( text );

    threading::MutexLock guard( mutex );

    if ( (size_t)inputBuffer.size() + len >= bufferLimit )
    {
      ++threadsafeSkippedMessages;
      return;
    }

    size_t from = inputBuffer.size();
    inputBuffer.resize( from + len, 0 );

    if ( len )
      memcpy( &inputBuffer[0] + from, text, len );
  }

  evtNewMessage.Set();
}



string TextFileWorkerThread::Filename()
{
  threading::MutexLock guard( mutex );

  return fileName;
}



void TextFileWorkerThread::Work( volatile bool & isRunning )
{
  NI_PROFILE_THREAD_NAMED( "LogFileWorker" );

  OpenLogFile();

  while ( isRunning )
  {
    {
      NI_PROFILE_BLOCK( "Wait" );
      evtNewMessage.Wait( 250 );
    }

    Swap();
    UpdateFile();
    Write();

    if ( reopenFile )
      OpenLogFile();
  }
}



void TextFileWorkerThread::Write()
{
  NI_PROFILE_FUNCTION;

  if ( !workingBuffer.empty() )
    WriteData( &workingBuffer[0], workingBuffer.size() );

  if ( skippedMessages )
    WriteText( NI_STRFMT( "ATTENTION: Log messages were skipped! number=%d\r\n", skippedMessages ) );
  skippedMessages = 0;
}



void TextFileWorkerThread::Swap()
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock guard( mutex );

  if ( handle != BAD_FILE_VALUE )
  {
    inputBuffer.swap( workingBuffer );
    inputBuffer.clear();

    skippedMessages += threadsafeSkippedMessages;
    threadsafeSkippedMessages = 0;
  }
}



void TextFileWorkerThread::CloseLogFile()
{
  if ( handle != BAD_FILE_VALUE )
#if defined( NV_WIN_PLATFORM )
    CloseHandle( handle );
#elif defined( NV_LINUX_PLATFORM )
    close( handle );
#endif

  handle = BAD_FILE_VALUE;
}



void TextFileWorkerThread::OpenLogFile()
{
  NI_PROFILE_FUNCTION;

  CloseLogFile();

  if ( suffix.empty() )
    return;

  string fname;
  for ( int i = 0; i < 100; ++i )
  {
    string sfx = suffix;
    if ( i )
      sfx += NI_STRFMT( "(%d)", i );

    fname = NDebug::GenerateDebugFileName( sfx.c_str(), "txt", folder.empty() ? 0 : folder.c_str() );

    handle = (FILE_HANDLE)NFile::CreateFileWithDir( fname.c_str() );
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

  reopenFile = false;

  {
    threading::MutexLock guard( mutex );
    fileName = fname;
  }
}



void TextFileWorkerThread::UpdateFile()
{
  //FIXME: Accessing integer field in parallel
  int rotationPeriod = CDumper::RotationPeriod();
  if ( rotationPeriod <= 0 )
    return;

  timer::DecodedTime t;
  timer::UtcDecodedTime( t );

  int rotationHour = ( t.wHour / rotationPeriod ) * rotationPeriod;

  if ( justStarted )
  {
    lastRotationHour = rotationHour;
    lastRotationDay = t.wDay;
    justStarted = false;
    return;
  }

  if ( ( t.wDay == lastRotationDay ) && ( rotationHour == lastRotationHour ) )
    return;

  lastRotationHour = rotationHour;
  lastRotationDay = t.wDay;

  reopenFile = true;
}



void TextFileWorkerThread::WriteText( const char * text )
{
  WriteData( text, strlen( text ) );
}



void TextFileWorkerThread::WriteData( const void * data, size_t size )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( handle == BAD_FILE_VALUE )
    return;

#if defined( NV_WIN_PLATFORM )
  DWORD dummy = 0;
  WriteFile( handle, data, (DWORD)size, &dummy, 0 );
#elif defined( NV_LINUX_PLATFORM )
  write( handle, data, size );
#endif
}

} //namespace NLogg
