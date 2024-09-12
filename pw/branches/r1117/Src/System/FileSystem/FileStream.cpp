#include "stdafx.h"
#include "FileStream.h"

#if defined( NV_WIN_PLATFORM )

	FileStream::FileStream( const string &fileName, EFileAccess _access, EFileOpen _open, bool bAutoMap ):
		pBuffer( 0 ), fileSize( 0 ), offset( 0 ), hFile( BAD_FILE_VALUE ), hMapping( BAD_FILE_VALUE )
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

		hFile = ::CreateFile( fileName.c_str(), accessFlags, FILE_SHARE_READ, 0, openFlags, FILE_ATTRIBUTE_NORMAL, 0 );
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
		memcpy( pBuffer + offset, pData, length );
		offset += length;
		return length;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	REGISTER_SAVELOAD_CLASS( FileStream );

#elif defined( NV_LINUX_PLATFORM )

	#include <fcntl.h>
	#include <errno.h>
	#include <sys/mman.h>

	namespace filesystem {

		inline uint64_t get_file_size( int fd )
		{
			struct stat fs;
			return fstat( fd, &fs ) == 0 ? fs.st_size : 0;
		}

	}

	FileStream::FileStream( string const &fileName, EFileAccess _access, EFileOpen _open, bool bAutoMap ):
		pBuffer( 0 ), fileSize( 0 ), offset( 0 ), hFile( BAD_FILE_VALUE ), hMapping( BAD_FILE_VALUE )
	{
		int flags = ( FILEACCESS_WRITE == _access || FILEACCESS_READ_WRITE == _access ) ? O_RDWR : O_RDONLY;

		switch ( _open ) {

		case FILEOPEN_CREATE_NEW:
			flags |= O_CREAT | O_TRUNC;
			break;

		case FILEOPEN_OPEN_ALWAYS:
			flags |= O_CREAT;
			break;

		}

		hFile = open( fileName.c_str(), flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
		if ( BAD_FILE_VALUE != hFile ) {

			if ( FILEACCESS_READ == _access || FILEACCESS_READ_WRITE == _access )
				SetCanRead( true );

			if ( FILEACCESS_WRITE == _access || FILEACCESS_READ_WRITE == _access )
				SetCanWrite( true );

			SetCanSeek( true );
			SetBroken( false );

			fileSize = filesystem::get_file_size( hFile );

			if ( bAutoMap )
				MapFile();

		} else
			DebugTrace( "Failed to open file %s with error %d.", fileName.c_str(), errno );
	}

	void FileStream::MapFile()
	{
		if ( GetSize() > 0 && BAD_FILE_VALUE != hFile ) {

			UnMapFile();

			pBuffer = reinterpret_cast< char * >( mmap( NULL, GetSize(), ( CanWrite() ? PROT_READ | PROT_WRITE : PROT_READ ), MAP_SHARED, hFile, 0 ) );
			if ( MAP_FAILED == pBuffer ) {

				pBuffer = NULL;
				Close();

			}

		}
	}

	void FileStream::UnMapFile()
	{
		if ( pBuffer ) {

			munmap( pBuffer, GetSize() );
			pBuffer = NULL;

		}
	}

	void FileStream::Close()
	{
		UnMapFile();

		if ( BAD_FILE_VALUE != hFile ) {

			close( hFile );
			hFile = BAD_FILE_VALUE;

		}

		SetBroken( true );
	}

	void FileStream::SeekInternal( const int _offset )
	{
		offset = _offset;
	}

	void FileStream::SetSizeInternal( const int size )
	{
		UnMapFile();

		if ( BAD_FILE_VALUE != hFile ) {

			ftruncate( hFile, size );
			lseek( hFile, size, SEEK_SET );

			fileSize = filesystem::get_file_size( hFile );

		}

		MapFile();
	}

	int FileStream::ReadInternal( void *pData, const int length )
	{
		memcpy( pData, pBuffer + offset, length );
		offset += length;
		return length;
	}

	int FileStream::WriteInternal( const void *pData, const int length )
	{
		memcpy( pBuffer + offset, pData, length );
		offset += length;
		return length;
	}

	REGISTER_SAVELOAD_CLASS( FileStream );

#endif

