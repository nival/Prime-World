/**
  FileStream implementation in Linux
  @TODO: наделать кроссплатформенных юниттестов, особенно для file mappings
 */

#include "stdafx.h"
#include "Asserts.h"
#include "FileStream.h"
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileStream::FileStream( const string &fileName, EFileAccess _access, EFileOpen _open, bool bAutoMap)
	: Stream(), pBuffer( 0 ), fileSize( 0 ), offset( 0 ),hFile(BAD_FILE_VALUE), hMapping(BAD_FILE_VALUE)
{
  int openFlags = 0;
  switch(_open)
  {
    // case FILEOPEN_CREATE_NEW   :  openFlags = CREATE_ALWAYS; break;
    case FILEOPEN_CREATE_NEW   :  openFlags |= O_CREAT | O_TRUNC; break;
    // case FILEOPEN_OPEN_ALWAYS  :  openFlags = OPEN_ALWAYS  ; break;
    case FILEOPEN_OPEN_ALWAYS  :  openFlags |= O_CREAT; break;
    // case FILEOPEN_OPEN_EXISTING:  openFlags = OPEN_EXISTING; break;
    case FILEOPEN_OPEN_EXISTING:  openFlags = 0; break;
    default: NI_ALWAYS_ASSERT("Wrong open mode");
  }
	// const int accessFlags = ( ( _access == FILEACCESS_WRITE || _access == FILEACCESS_READ_WRITE ) ? GENERIC_WRITE : 0 ) | GENERIC_READ;
  switch ( _access )
  {
    case FILEACCESS_READ:            openFlags |= O_RDONLY; break;
    case FILEACCESS_WRITE:           openFlags |= O_RDWR; break;
    case FILEACCESS_READ_WRITE:      openFlags |= O_RDWR; break;
    default:                         NI_ALWAYS_ASSERT("Wrong access mode");
  }

	// hFile = ::CreateFileA( fileName.c_str(), accessFlags, FILE_SHARE_READ, 0, openFlags, FILE_ATTRIBUTE_NORMAL, 0 );
  hFile = ::open( fileName.c_str(), openFlags, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH );
	if ( hFile != BAD_FILE_VALUE )
	{
		if ( _access == FILEACCESS_READ || _access == FILEACCESS_READ_WRITE )
			SetCanRead( true );
		if ( _access == FILEACCESS_WRITE || _access == FILEACCESS_READ_WRITE )
			SetCanWrite( true );

		SetCanSeek( true );
		SetBroken( false );

		// fileSize = ::GetFileSize( hFile, 0 );
    struct stat statbuf = { 0 };
    NI_VERIFY_NO_RET( ::fstat( hFile, &statbuf ) != -1, "fstat error" );
    fileSize = statbuf.st_size;

    if(bAutoMap)
    {
		  MapFile();
    }
	}
  else
  {
    // DebugTrace("Failed to open file %s with error %d.", fileName.c_str(), GetLastError());
    DebugTrace("Failed to open file %s with error %d.", fileName.c_str(), errno);
  }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::MapFile()
{
	if ( GetSize() > 0 )
	{
		// const DWORD protectFalgs = ( CanWrite() ?	PAGE_READWRITE : PAGE_READONLY ) | SEC_COMMIT;
		// hMapping = CreateFileMapping( hFile, 0, protectFalgs, 0, 0, 0 );
    const int protectFlags = CanWrite() ?	PROT_WRITE | PROT_READ : PROT_READ;
    pBuffer = static_cast< char * >( ::mmap( 0, GetSize(), protectFlags, MAP_SHARED, hFile, 0 ) );
		//if ( !hMapping )
    if ( pBuffer == MAP_FAILED )
		{
      pBuffer = 0;
			//Close();
			return;
		}
		//pBuffer = (char*)MapViewOfFile( hMapping, CanWrite() ? FILE_MAP_ALL_ACCESS : FILE_MAP_READ, 0, 0, 0 );
		//if ( !pBuffer )
			//Close();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::UnMapFile()
{
	if ( pBuffer )
	{
		// UnmapViewOfFile( pBuffer );
    if( munmap( pBuffer, GetSize() ) != 0 )
    {
      DebugTrace("munmap error %d.", errno);
    }
		pBuffer = 0;
	}
	//if ( hMapping )
	//{
		//CloseHandle( hMapping );
		//hMapping = 0;
	//}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::Close()
{
	UnMapFile();
	if ( hFile != BAD_FILE_VALUE )
	{
		// CloseHandle( hFile );
    close( hFile );
		hFile = BAD_FILE_VALUE;
	}
	SetBroken( true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::SeekInternal( const int _offset )
{
	offset = _offset;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::SetSizeInternal( const int size )
{
	UnMapFile();
	// SetFilePointer( hFile, size, 0, FILE_BEGIN );
	// SetEndOfFile( hFile );
  NI_VERIFY_NO_RET( ftruncate( hFile, size ) == 0, "ftruncate error" );
	// fileSize = ::GetFileSize( hFile, 0 );
  struct stat statbuf = { 0 };
  NI_VERIFY_NO_RET( ::fstat( hFile, &statbuf ) != -1, "fstat error" );
  fileSize = statbuf.st_size;
	MapFile();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FileStream::ReadInternal( void *pData, const int length )
{
  memcpy( pData, pBuffer + offset, length );
  offset += length;
  return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FileStream::WriteInternal( const void *pData, const int length )
{
  memmove( pBuffer + offset, pData, length );
  offset += length;
  return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( FileStream );