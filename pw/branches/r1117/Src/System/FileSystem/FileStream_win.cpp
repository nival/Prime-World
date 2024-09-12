#include "stdafx.h"

#include "FileStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileStream::FileStream( const string &fileName, EFileAccess _access, EFileOpen _open, bool bAutoMap)
	: Stream(), pBuffer( 0 ), fileSize( 0 ), offset( 0 ),hFile(BAD_FILE_VALUE), hMapping(BAD_FILE_VALUE)
{
  int openFlags = 0;
  switch(_open)
  {
    case FILEOPEN_CREATE_NEW   :  openFlags = CREATE_ALWAYS; break;
    case FILEOPEN_OPEN_ALWAYS  :  openFlags = OPEN_ALWAYS  ; break;
    case FILEOPEN_OPEN_EXISTING:  openFlags = OPEN_EXISTING; break;
    default: NI_ALWAYS_ASSERT("Wrong open mode");
  }
	const int accessFlags = ( ( _access == FILEACCESS_WRITE || _access == FILEACCESS_READ_WRITE ) ? GENERIC_WRITE : 0 ) | GENERIC_READ;

	hFile = ::CreateFileA( fileName.c_str(), accessFlags, FILE_SHARE_READ, 0, openFlags, FILE_ATTRIBUTE_NORMAL, 0 );
	if ( hFile != BAD_FILE_VALUE )
	{
		if ( _access == FILEACCESS_READ || _access == FILEACCESS_READ_WRITE )
			SetCanRead( true );
		if ( _access == FILEACCESS_WRITE || _access == FILEACCESS_READ_WRITE )
			SetCanWrite( true );

		SetCanSeek( true );
		SetBroken( false );

		fileSize = ::GetFileSize( hFile, 0 );

    if(bAutoMap)
    {
		  MapFile();
    }
	}
  else
  {
    DebugTrace("Failed to open file %s with error %d.", fileName.c_str(), GetLastError());
  }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::MapFile()
{
	if ( GetSize() > 0 )
	{
		const DWORD protectFalgs = ( CanWrite() ?	PAGE_READWRITE : PAGE_READONLY ) | SEC_COMMIT;
		hMapping = CreateFileMapping( hFile, 0, protectFalgs, 0, 0, 0 );
		if ( !hMapping )
		{
			Close();
			return;
		}
		pBuffer = (char*)MapViewOfFile( hMapping, CanWrite() ? FILE_MAP_ALL_ACCESS : FILE_MAP_READ, 0, 0, 0 );
		if ( !pBuffer )
			Close();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::UnMapFile()
{
	if ( pBuffer )
	{
		UnmapViewOfFile( pBuffer );
		pBuffer = 0;
	}
	if ( hMapping )
	{
		CloseHandle( hMapping );
		hMapping = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileStream::Close()
{
	UnMapFile();
	if ( hFile != BAD_FILE_VALUE )
	{
		CloseHandle( hFile );
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
	SetFilePointer( hFile, size, 0, FILE_BEGIN );
	SetEndOfFile( hFile );
	fileSize = ::GetFileSize( hFile, 0 );
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
