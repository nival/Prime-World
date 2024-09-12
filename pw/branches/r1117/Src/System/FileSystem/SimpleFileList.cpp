#include "stdafx.h"
#include "SimpleFileList.h"

#pragma warning( disable : 4996 ) //warning C4996: 'fopen': This function or variable may be unsafe

NI_DEFINE_REFCOUNT( fileSystem::SimpleFileList );

namespace fileSystem
{

bool SimpleFileList::Load( const char * filename )
{
  FILE * f = fopen( filename, "rt" );
  NI_VERIFY( f, NStr::StrFmt( "Could not open file list '%s'", filename ), return false );

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

    log.push_back( line );
  }

  fclose( f );
  f = 0;
  SimpleFileList::filename = filename;
  return true;
}

} //namespace fileSystem
