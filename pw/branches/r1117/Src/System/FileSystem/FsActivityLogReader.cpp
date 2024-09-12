#include "stdafx.h"

#include "FsActivityLogReader.h"

#pragma warning( disable : 4996 ) //warning C4996: 'fopen': This function or variable may be unsafe

//NI_DEFINE_REFCOUNT( fileSystem::ActivityLogReader );

namespace fileSystem
{

bool ActivityLogReader::Load( const char * _filename )
{
  FILE * f = fopen( _filename, "rt" );
  NI_VERIFY( f, NStr::StrFmt( "Could not open file system activity log file '%s'", _filename ), return false );

  log.clear();
  log.reserve( 1024 );

  while ( true )
  {
    //Skip new/empty lines
    for( char buf[16] = ""; fscanf( f, "%15[\r\n]s", buf ) > 0; )
      ;

    char line[1024] = "";
    int lineCheck = fscanf( f, "%1023[^\r\n]s", line );
    if ( lineCheck != 1 )
      break;

    char op[32] = "", tmpFilename[1024] = "";
    float time = 0;
    unsigned size = 0;

    //FXIME: file names should not contain spaces!
    int elements = sscanf( line, "%s %f %u %s", op, &time, &size, tmpFilename );
    NI_VERIFY( elements == 4, "Wrong log format!", fclose(f); return false );
    
    SLogEntry entry;

    if ( !NStr::ICmp( op, "getinfo" ) )
      entry.type = eGetFileInfo;
    else if ( !NStr::ICmp( op, "openfile" ) )
      entry.type = eOpenFile;
    else if ( !NStr::ICmp( op, "getdirs" ) )
      entry.type = eGetDirectories;
    else if ( !NStr::ICmp( op, "getfiles" ) )
      entry.type = eGetFiles;
    else
    {
      NI_ALWAYS_ASSERT( "Invalid file operation" );
      fclose( f );
      return false;
    }

    entry.time = time;
    entry.size = size;
    entry.filename = tmpFilename;

    log.push_back( entry );
  }

  fclose( f );
  f = 0;

  filename = _filename;
  return true;
}

} //namespace fileSystem
