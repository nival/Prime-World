#include "stdafx.h"
#include "MMakingLog.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"


NI_DEFINE_REFCOUNT( mmaking::Loger );

namespace mmaking
{

Loger::Loger( const char * suffix, const char * header ) :
m_suffix( suffix ? suffix : "" ),
m_logHeader( header ),
m_file( INVALID_HANDLE_VALUE ),
m_debugOutput( true ),
m_level( ELogLevel::Normal ),
m_simTime( 0 ),
m_prevDay( 0 ),
m_logTime( true )
{
  timer::DecodedTime t;
  timer::UtcDecodedTime( t );
  m_prevDay = t.wDay;

  OpenFile();

  if ( !m_logHeader.empty() )
    Write( m_logHeader.c_str() );
}



Loger::~Loger()
{
  CloseFile();
}



bool Loger::Poll( timer::Time simulationTime )
{
  threading::MutexLock lock( m_mutex );
  m_simTime = simulationTime;

  timer::DecodedTime t;
  timer::UtcDecodedTime( t );

  if ( m_prevDay != t.wDay )
  {
    m_prevDay = t.wDay;

    CloseFile();
    OpenFile();
    if ( !m_logHeader.empty() )
      Write( m_logHeader.c_str() );
    return true;
  }
  else
    return false;
}



void Loger::Log( ELogLevel::Enum level, const char * fmt, ... )
{
  if ( level > m_level )
    return;

  va_list args;
  va_start( args, fmt );
  char buf[8192];
  vsprintf_s( buf, fmt, args );
  va_end( args);
  Write( buf );
}



void Loger::OpenFile()
{
  if ( m_suffix.empty() )
    return;

  for ( int i = 0; i < 100; ++i )
  {
    string sfx = m_suffix;
    if ( i )
      sfx += NI_STRFMT( "(%d)", i );

    string filename = NDebug::GenerateDebugFileName( sfx.c_str(), "txt" );
    NStr::TrimLeft( filename, "/\\" );

    m_file = (HANDLE)NFile::CreateFileWithDir( filename.c_str() );
    if ( m_file != INVALID_HANDLE_VALUE )
    {
      int tzOffs = timer::TimeZoneOffsetInMinutes();
      char buf[256] = "";
      sprintf( buf, "Local time: %+d:%02d UTC\r\nProcessId: %d\r\n", tzOffs / 60, abs( tzOffs ) % 60, GetCurrentProcessId() );

      DWORD dummy = 0;
      WriteFile( m_file, buf, strlen( buf ), &dummy, 0 );
      return;
    }
  }
}



void Loger::CloseFile()
{
  if ( m_file != INVALID_HANDLE_VALUE )
    CloseHandle( m_file );
  m_file = INVALID_HANDLE_VALUE;
}



void Loger::Write( const char * text )
{
  threading::MutexLock lock( m_mutex );

  DWORD written = 0;

  if (m_logTime)
  {
    timer::DecodedTime now;
    timer::UtcDecodedTime( now );

    char timeBuf[128] = "";
    sprintf_s( timeBuf, 128, "%02u/%02u %02u:%02u:%02u.%02u %-7.1f ", now.wDay, now.wMonth, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds / 10, m_simTime );
    if ( m_file != INVALID_HANDLE_VALUE )
      WriteFile( m_file, timeBuf, strlen( timeBuf ), (DWORD*)&written, 0 );

    if ( m_debugOutput )
      OutputDebugString( timeBuf );
  }

  if ( m_file != INVALID_HANDLE_VALUE )
    WriteFile( m_file, text, strlen( text ), (DWORD*)&written, 0 );
  
  if ( m_debugOutput )
    OutputDebugString( text );

  const char * end = "\r\n";
  if ( m_file != INVALID_HANDLE_VALUE )
    WriteFile( m_file, end, strlen( end ), (DWORD*)&written, 0 );

  if ( m_debugOutput )
    OutputDebugString( end );
}


} //namespace mmaking
