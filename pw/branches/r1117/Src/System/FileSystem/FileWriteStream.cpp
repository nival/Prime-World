#include "stdafx.h"
#include "FileWriteStream.h"

unsigned long FileWriteStream::nAllocationGranularity = 0;

#if defined( NV_WIN_PLATFORM )

FileWriteStream::FileWriteStream(string const &fileName, EFileAccess _access, EFileOpen _open )
: FileStream(fileName, _access, _open, false), nMaxImageSize(FileStream::GetSize()), nMapStartOffset(0), nMapWindowSize(1024 * 1024)
{
  if(nAllocationGranularity == 0)
  {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    nAllocationGranularity = si.dwAllocationGranularity;
  }
  if(GetSize() == 0 && (_open == FILEOPEN_CREATE_NEW || _open == FILEOPEN_OPEN_ALWAYS) && ( _access == FILEACCESS_WRITE || _access == FILEACCESS_READ_WRITE ))
  {
    nMaxImageSize = 1024 * 1024; // 1 megabytes is ok
    //we need to create mapping
    MapEmptyFile();
  }
  else if(GetSize() > 0 && _access != FILEACCESS_READ)
  {
    //set size 1 Mb ahead
    nMaxImageSize = max(GetSize() * 2, GetSize() + 1024 * 1024);
    nMapStartOffset = GetSize() - (GetSize() % nAllocationGranularity);
    MapEmptyFile();
    Seek(0, SEEKORIGIN_END);
  }
  else
  {
    MapFile();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteStream::MapEmptyFile()
{
	const DWORD protectFalgs = (CanWrite() ?	PAGE_READWRITE: PAGE_READONLY) | SEC_COMMIT;
	hMapping = CreateFileMapping(hFile, NULL, protectFalgs, 0, nMaxImageSize, 0);
	if(hMapping == NULL)
	{
    DebugTrace("Failed to create mapping of size %d with error %d.", nMaxImageSize, GetLastError());
		Close();
		return;
	}
	pBuffer = (char *)MapViewOfFile(hMapping, CanWrite() ? FILE_MAP_ALL_ACCESS: FILE_MAP_READ, 0, nMapStartOffset, nMapWindowSize);
	if(pBuffer == NULL)
  {
    DebugTrace("Failed to map file at offset %d of window size %d with error %d.", nMapStartOffset, nMapWindowSize, GetLastError());
		Close();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteStream::UnMapFile()
{
  FileStream::UnMapFile();
  //set correct EOF
  SetFilePointer(hFile, GetSize(), NULL, FILE_BEGIN);
  SetEndOfFile(hFile);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteStream::Close()
{
	UnMapFile();
	if(hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle( hFile );
		hFile = INVALID_HANDLE_VALUE;
	}
	SetBroken(true);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteStream::SeekInternal(const int _offset)
{
  NI_VERIFY((_offset - nMapStartOffset) >= 0 && (_offset - nMapStartOffset) < nMapWindowSize, "Seek outside of window", return;);
  FileStream::SeekInternal(_offset);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteStream::ResizeImage(unsigned long nNewSize)
{
  //close mapping
  UnMapFile();
  //set new boundary
  nMaxImageSize = nNewSize;
  //call API
  MapEmptyFile();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteStream::SetSizeInternal(const int size)
{
  NI_ASSERT(size > 0, "Size should not be zero");
  NI_VERIFY((size - nMapStartOffset) >= 0 && (size - nMapStartOffset) < nMapWindowSize, "Size outside of window", return;);
  fileSize = size;
  if((int)nMaxImageSize < (fileSize + nMapWindowSize / 4))
  {
    nMapStartOffset += nMapWindowSize / 2;
    //shift window and go
    ResizeImage(nMapStartOffset + nMapWindowSize);
  }
  NI_ASSERT((unsigned)fileSize <= nMaxImageSize, "Should be so.");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FileWriteStream::ReadInternal(void *pData, const int length)
{
  NI_VERIFY((offset - nMapStartOffset) >= 0 && (offset - nMapStartOffset) < nMapWindowSize, "Read out of the read window", return 0;);

  memcpy( pData, pBuffer + offset - nMapStartOffset, length);
  offset += length;
  return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FileWriteStream::WriteInternal(const void *pData, const int length)
{
  if(hMapping == NULL || pBuffer == NULL)
    return 0;
  if(length > 0)
  {
    NI_VERIFY((offset - nMapStartOffset) >= 0 && (offset - nMapStartOffset) < nMapWindowSize, "Write out of the write window", return 0;);
    memcpy( pBuffer + offset - nMapStartOffset, pData, length);
    offset += length;
    return length;
  }
  else
  {
    return 0;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS(FileWriteStream);

#elif defined( NV_LINUX_PLATFORM )

	#include <fcntl.h>
	#include <errno.h>
	#include <sys/mman.h>

	FileWriteStream::FileWriteStream( string const &fileName, EFileAccess _access, EFileOpen _open ):
		FileStream( fileName, _access, _open, false ),
		nMaxImageSize( FileStream::GetSize() ),
		nMapStartOffset( 0 ),
		nMapWindowSize( 1024 * 1024 )
	{
		if (0 == nAllocationGranularity )
			nAllocationGranularity = sysconf( _SC_PAGE_SIZE );

		if ( GetSize() == 0 && ( FILEOPEN_CREATE_NEW == _open || FILEOPEN_OPEN_ALWAYS == _open ) && ( FILEACCESS_WRITE == _access || FILEACCESS_READ_WRITE == _access )) {

			nMaxImageSize = 1024 * 1024; // 1 megabytes is ok
			// we need to create mapping
			MapEmptyFile();

		} else if ( GetSize() > 0 && FILEACCESS_READ != _access ) {

			// set size 1 Mb ahead
			nMaxImageSize = std::max< unsigned long >( GetSize() * 2, GetSize() + 1024 * 1024 );
			nMapStartOffset = GetSize() - ( GetSize() % nAllocationGranularity );
			MapEmptyFile();
			Seek( 0, SEEKORIGIN_END );

		} else
			MapFile();
	}

	void FileWriteStream::MapEmptyFile()
	{
		pBuffer = reinterpret_cast< char * >( mmap( NULL, nMapWindowSize, ( CanWrite() ? PROT_READ | PROT_WRITE : PROT_READ ), MAP_SHARED, hFile, nMapStartOffset ) );
		if ( MAP_FAILED == pBuffer ) {

			DebugTrace( "Failed to map file at offset %d of window size %d with error %d.", nMapStartOffset, nMapWindowSize, errno );

			pBuffer = NULL;
			Close();

		}
	}

	void FileWriteStream::UnMapFile()
	{
		FileStream::UnMapFile();

		if ( BAD_FILE_VALUE != hFile ) {

			ftruncate( hFile, GetSize() );
			lseek( hFile, GetSize(), SEEK_SET );

		}
	}

	void FileWriteStream::SeekInternal(const int _offset)
	{
	  NI_VERIFY((_offset - nMapStartOffset) >= 0 && (_offset - nMapStartOffset) < nMapWindowSize, "Seek outside of window", return;);
	  FileStream::SeekInternal(_offset);
	}

	void FileWriteStream::ResizeImage(unsigned long nNewSize)
	{
	  //close mapping
	  UnMapFile();
	  //set new boundary
	  nMaxImageSize = nNewSize;
	  //call API
	  MapEmptyFile();
	}

	void FileWriteStream::SetSizeInternal(const int size)
	{
	  NI_ASSERT(size > 0, "Size should not be zero");
	  NI_VERIFY((size - nMapStartOffset) >= 0 && (size - nMapStartOffset) < nMapWindowSize, "Size outside of window", return;);
	  fileSize = size;
	  if((int)nMaxImageSize < (fileSize + nMapWindowSize / 4))
	  {
		nMapStartOffset += nMapWindowSize / 2;
		//shift window and go
		ResizeImage(nMapStartOffset + nMapWindowSize);
	  }
	  NI_ASSERT((unsigned)fileSize <= nMaxImageSize, "Should be so.");
	}

	int FileWriteStream::ReadInternal(void *pData, const int length)
	{
	  NI_VERIFY((offset - nMapStartOffset) >= 0 && (offset - nMapStartOffset) < nMapWindowSize, "Read out of the read window", return 0;);

	  memcpy( pData, pBuffer + offset - nMapStartOffset, length);
	  offset += length;
	  return length;
	}

	int FileWriteStream::WriteInternal( const void *pData, const int length )
	{
		if ( NULL == pBuffer )
			return 0;

		if ( length > 0 ) {

			NI_VERIFY((offset - nMapStartOffset) >= 0 && (offset - nMapStartOffset) < nMapWindowSize, "Write out of the write window", return 0; );
			memcpy( pBuffer + offset - nMapStartOffset, pData, length);
			offset += length;

			return length;

		}

		return 0;
	}

	void FileWriteStream::Close()
	{
		FileStream::Close();
	}

	REGISTER_SAVELOAD_CLASS(FileWriteStream);

#endif

