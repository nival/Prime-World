#include "stdafx.h"
#include "PersistEvents.h"
#include "system/math/md4.h"
#include "system/filesystem/fileutils.h"

namespace persistentEvents
{

const static unsigned MSecBits = 6;
const static unsigned MaxIndex = 1u << ( 32 - MSecBits );
const static unsigned MaxMSec = ( 1u << MSecBits ) - 1;

const static unsigned MSecMask = ( ( 1u << MSecBits ) - 1 ) << ( 32 - MSecBits );
const static unsigned IndexMask = MaxIndex - 1;


const static char * Salt = "Path not found"; //Security through conspiracy


Events::Events( const char * path ) :
_path( path ),
_startTimeSec( 0 ), _indexMask( 0 ),
_nextIdx( 0 )
{
  _startTimeSec = GetTimestamp();

  unsigned ticks = GetTickCount();
  unsigned msec = ( ( ticks % 1000 ) * MaxMSec / 1000 );

  _indexMask = msec << ( 32 - MSecBits );

  if ( !_path.empty() ) {
    char c = _path[_path.length() - 1];
    if ( c  == '\\' || c == '/' )
      _path.pop_back();
  }
}



Events::~Events()
{
}



void Events::CheckUnfinishedSessions()
{
  vector<Event> events;
  CollectEventsImpl( events, EEvent::None );

  for ( vector<Event>::const_iterator it = events.begin(); it != events.end(); ++it )
    if ( it->code == EEvent::ClientLaunched ) {
      EraseEvent( *it );
      WriteEvent( EEvent::ClientCrash, 0, it->eventTimestamp );
    }
}



void Events::Open()
{
  if ( _launchEvent.code != EEvent::None )
    return;

  _launchEvent = WriteEvent( EEvent::ClientLaunched, 0 );
}



void Events::Close()
{
  if ( _launchEvent.code == EEvent::None )
    return;

  EraseEvent( _launchEvent );

  _launchEvent = Event();
}



Event Events::WriteEvent( EEvent::Enum event, TAuxParam auxParam )
{
  return WriteEvent( event, auxParam, GetTimestamp() );
}



Event Events::WriteEvent( EEvent::Enum event, TAuxParam auxParam, unsigned timestamp )
{
  NI_ASSERT( _nextIdx < MaxIndex, "" );

  Event evt;
  evt.id = GenerateId();
  evt.code = event;
  evt.aux = auxParam;
  evt.eventTimestamp = timestamp;

  string key = EventKey( evt );

  string filename = GenerateFilename( evt.id );

  FILE * f = fopen( filename.c_str(), "wt" );
  if ( !f ) {
    ErrorTrace( "could not write to '%s'", filename );
    return evt;
  }

  fprintf( f, "%08x %08x %08x %016llx %08x %s", evt.id.timestamp, evt.id.index, (unsigned)evt.code, evt.aux, evt.eventTimestamp, key.c_str() );

  fclose( f );
  return evt;
}



void Events::CollectEvents( vector<Event> & buffer )
{
  CollectEventsImpl( buffer, EEvent::ClientLaunched );
}



void Events::CollectEventsImpl( vector<Event> & buffer, EEvent::Enum ignoreEventType )
{
  list<string> names;
  NFile::GetDirectoryFiles( ( _path + "\\" ).c_str(), "*.pwevt", &names, false );

  buffer.reserve( names.size() );

  for ( list<string>::iterator it = names.begin(); it != names.end(); ++it ) {
    FILE * f = fopen( it->c_str(), "at+" );
    if ( f ) {
      Event evt;
      char key[33] = "";
      unsigned code = 0;
      bool eraseEvent = false;
      if ( fscanf( f, "%x %x %x %llx %x %32[0-9a-z]", &evt.id.timestamp, &evt.id.index, &code, &evt.aux, &evt.eventTimestamp, key ) == 6 )
      {
        if ( ( ignoreEventType == EEvent::None ) || ( ignoreEventType != (EEvent::Enum)code ) ) {
          evt.code = (EEvent::Enum)code;
          string checkKey = EventKey( evt );
          if ( stricmp( checkKey.c_str(), key ) == 0 )
            buffer.push_back( evt );
          else
          {
            WarningTrace( "Wrong persistent event %x%x check key!", evt.id.timestamp, evt.id.index );\
            eraseEvent = true;
          }
        }
      }
      fclose( f );
      if (eraseEvent)
        EraseEvent( evt );
    }
  }
}



void Events::EraseEvents( const vector<Event> & events )
{
  for ( vector<Event>::const_iterator it = events.begin(); it != events.end(); ++it )
    EraseEvent( *it );
}



void Events::EraseEvent( const Event & event )
{
  string filename = GenerateFilename( event.id );
  SetFileAttributes( filename.c_str(), FILE_ATTRIBUTE_NORMAL );
  DeleteFileA( filename.c_str() );
}



string Events::GenerateFilename( const EventId & id )
{
  return NI_STRFMT( "%s\\Event_%08x_%08x.pwevt", _path, id.timestamp, id.index );
}



EventId Events::GenerateId()
{
  EventId id;
  id.timestamp = _startTimeSec;
  id.index = _nextIdx++;
  id.index |= _indexMask;
  return id;
}



string Events::EventKey( const Event & event )
{
  math::MD5Generator md5;
  md5.Start();
  md5.Update( (const byte *)Salt, strlen( Salt ) );
  md5.AddObject( event );
  md5.Update( (const byte *)Salt, strlen( Salt ) );
  md5.Stop();

  return md5.Get().ToString();
}



unsigned Events::GetTimestamp()
{
  __time32_t ts = 0;
  _time32( &ts );
  return ts;
}



static StrongMT<Events> s_singleton;

void CreateSingleton( const char * path ) { s_singleton = new Events( path ); }

void CleanupSingleton() { s_singleton = 0; }

Events * GetSingleton() { return s_singleton; }

} //namespace persistentEvents
