#include "stdafx.h"
#include <System/config.h>
#include <fstream>
#include "FileStream_stdlib.h"

#if defined( NV_WIN_PLATFORM )
	#include <io.h>
#endif


StdLibFileStream::StdLibFileStream( const string & fileName, EFileAccess _access, EFileOpen _open, bool bAutoMap ) :
Stream(),
pos( 0 )
{
  NI_VERIFY( _open == FILEOPEN_OPEN_EXISTING, "", return );
  NI_VERIFY( _access == FILEACCESS_READ, "", return );

  std::ifstream file( fileName.c_str(), std::ios::binary );
  if ( !file.is_open() )
  {
    DebugTrace( "Failed to open file %s", fileName.c_str() );
    return;
  }

  file.seekg( 0, std::ios::end );
  size_t size = file.tellg();
  file.seekg( 0, std::ios::beg );

  buffer.resize( size );

  if ( size )
  {
    file.read( reinterpret_cast< char * >(&buffer[ 0 ]), size );
    if ( file.fail() )
    {
      DebugTrace( "Failed to read file %s", fileName.c_str() );
      return;
    }
  }

  file.close();

  SetCanRead( true );
  SetCanWrite( false );
  SetCanSeek( true );
  SetBroken( false );
}



void StdLibFileStream::SeekInternal( const int _offset )
{
  NI_VERIFY( _offset >= 0 && _offset <= buffer.size(), "", return );
  pos = _offset;
}



void StdLibFileStream::SetSizeInternal( const int size )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
}



int StdLibFileStream::ReadInternal( void * pData, const int length )
{
  NI_ASSERT( length >= 0 && length <= buffer.size(), "" );
  NI_ASSERT( pos + (size_t)length <= (size_t)buffer.size(), "" );

	memcpy( pData, &buffer[0] + pos, length );
	pos += length;
	return length;
}



int StdLibFileStream::WriteInternal( const void *pData, const int length )
{
	NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}

REGISTER_SAVELOAD_CLASS( StdLibFileStream );
