#include "stdafx.h"
#include "FileWriteBufferedStream.h"
#include "FileWriteAsynchronousStream.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/hdreg.h>
#include <sys/ioctl.h>

#if defined( NV_LINUX_PLATFORM )

namespace
{
  const int COMMON_SECTOR_SIZE = 512;

  inline uint LODWORD(uint64 dw)
  {
    return (uint)(dw & 0xFFFFFFFF);
  }

  inline uint HIDWORD(uint64 dw)
  {
    return (uint)(((dw & 0xFFFFFFFF00000000) >> 32) & 0xFFFFFFFF);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteAsynchronousStream::FileWriteAsynchronousStream()
: FileWriteBufferedStream()
, sectorSize(0)
, filePosition(0)
, tailPosition(0)
, writeStarted(false)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteAsynchronousStream::FileWriteAsynchronousStream(const string & _fileName)
: FileWriteBufferedStream()
, sectorSize(0)
, filePosition(0)
, tailPosition(0)
, writeStarted(false)
{
  Open(_fileName);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteAsynchronousStream::FileWriteAsynchronousStream(const string & _fileName, const int _bufferSize, const int _fileSize)
: FileWriteBufferedStream()
, sectorSize(0)
, filePosition(0)
, tailPosition(0)
, writeStarted(false)
{
  Open(_fileName);
  ReserveBuffer(_bufferSize);
  SetFileSize(_fileSize);
  SetFilePosition(0, 0, SEEK_SET);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteAsynchronousStream::~FileWriteAsynchronousStream()
{
  FinishFlush(); // Wait for flush operation to complete, if any in progress
  FlushAll();    // Dump all the information currently in the buffer
  FreeBuffer( &buffer );     // Free virtual buffer here, otherwise parent class will try to do it with regular delete

  // Note: the file will be truncated and the handle will be closed by the parent class' destructor
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteAsynchronousStream::OpenInternal(const string & _fileName)
{
/* 
  file = CreateFileA(_fileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, creationMode, 
                      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED 
                        | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH, NULL);
  if (file != -1)
    sectorSize = GetSectorSize(_fileName);
*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * FileWriteAsynchronousStream::AllocateBuffer( const int _size )
{
  // VirtualAlloc will round up the _size
  //return (char *)VirtualAlloc( 0, _size, MEM_COMMIT, PAGE_READWRITE );
  return (char *)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteAsynchronousStream::FreeBuffer( char ** _buffer )
{
  if (*_buffer)
  {
   // VirtualFree(*_buffer, 0, MEM_RELEASE);
    *_buffer = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Flush the all the data, including analighned part (flushed synchronously)
void FileWriteAsynchronousStream::FlushAll()
{
  Flush();  // Flush if we have enough data for unbuffered chunk
  FinishFlush();
  Close();  // Close file, open for asynchronous, unbuffered write

  FileWriteBufferedStream::OpenInternal(fileName);  // Open file for synchronous write
  FileWriteBufferedStream::SetFilePosition(LODWORD(filePosition), HIDWORD(filePosition), SEEK_SET);
  filePosition += position;            // Update file position with synchronous data size
  FileWriteBufferedStream::Flush();    // Flush the tail of te buffer synchronously
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteAsynchronousStream::Flush()
{
  NI_VERIFY(file != -1, "File isn't open!", return; );

  if (position == 0 || size == 0)
    return;
/*
  int sizeToWrite = RoundDownToSectorSize(position);
  if (sizeToWrite == 0)
    return;

  // Prepare overlaped struture
  memset(&overlapped, 0, sizeof(OVERLAPPED));
  overlapped.Offset     = LODWORD(filePosition);
  overlapped.OffsetHigh = HIDWORD(filePosition);

  filePosition += sizeToWrite;
  tailPosition = ((position - sizeToWrite) > 0) ? (sizeToWrite) : (0);

  BOOL retVal = WriteFile(file, buffer, sizeToWrite, NULL, &overlapped);
  DWORD dwErr = GetLastError();
  NI_VERIFY(retVal != 0 || dwErr == ERROR_IO_PENDING, NI_STRFMT("Overlapped write failed with error: %d!", dwErr), SetBroken( true ); return; );
  writeStarted = true;
*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Waits for flush operation to finish and moves data tail to the start of the buffer
void FileWriteAsynchronousStream::FinishFlush()
{/*
  if (writeStarted)
  {
    DWORD numberOfBytesTransferred;
    BOOL retVal = GetOverlappedResult(file, &overlapped, &numberOfBytesTransferred , TRUE);

    NI_VERIFY(retVal != 0, NI_STRFMT("Wait for overlapped write failed with error %d.", GetLastError()), SetBroken( true ); return; );
    
    writeStarted = false;

    // Move tail to the buffer's start
    if (tailPosition > 0)
    {
      int tailSize = position - tailPosition;
      memmove( buffer, buffer + tailPosition, tailSize );
      position = tailSize;
      tailPosition = 0;
    }
    else
    {
      position = 0;
    }
  }
  */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function retreives disk sector size by given full path. 
// Note: it doesn't support relative paths (refactor?)
unsigned int FileWriteAsynchronousStream::GetSectorSize(const string & path)
{
  return COMMON_SECTOR_SIZE;
  /*

  NI_VERIFY(path.length() >= 3, "Full path should have drive!", return COMMON_SECTOR_SIZE; );

  NI_VERIFY(path[1] == ':' && (path[2] == '\\' || path[2] == '/'), "Incorrect path given!", return COMMON_SECTOR_SIZE;);

  string disk(path);
  disk = disk.substr(0, 3);

  DWORD dwSectPerClust, dwBytesPerSect,  dwFreeClusters, dwTotalClusters;
  BOOL result = GetDiskFreeSpaceA(disk.c_str(), &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);

  NI_ASSERT(result != FALSE, NI_STRFMT("Function GetDiskFreeSpace returned error %d.", errno));

  return result;
  */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculates the closest size, whicj is multiple of sector size, but less than the given size
unsigned int FileWriteAsynchronousStream::RoundDownToSectorSize(unsigned int _size)
{
  unsigned int mask = ~(sectorSize - 1);

  if((_size & (sectorSize - 1)) != 0)
  {
    return (_size) & mask;
  }

  return _size;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( FileWriteAsynchronousStream );

#endif // defined( NV_WIN_PLATFORM )
