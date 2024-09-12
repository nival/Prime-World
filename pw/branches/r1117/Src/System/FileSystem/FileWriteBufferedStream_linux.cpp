#include "stdafx.h"
#include "FileWriteBufferedStream.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteBufferedStream::FileWriteBufferedStream()
: file(-1)
, buffer(0)
, size(0)
, position(0)
//, creationMode(OPEN_ALWAYS)
, creationMode(O_CREAT | O_WRONLY)
{
  InitInternal();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteBufferedStream::FileWriteBufferedStream(const string & _fileName)
: buffer(0)
, size(0)
, position(0)
//, creationMode(OPEN_ALWAYS)
, creationMode(O_CREAT | O_WRONLY)
{
  InitInternal();
  Open(_fileName);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteBufferedStream::FileWriteBufferedStream(const string & _fileName, const int _bufferSize, const int _fileSize)
: buffer(0)
, size(0)
, position(0)
//, creationMode(OPEN_ALWAYS)
, creationMode(O_CREAT | O_WRONLY)
{
  InitInternal();
  Open(_fileName);
  ReserveBuffer(_bufferSize);
  SetFileSize(_fileSize);
  //SetFilePosition(0, 0, FILE_BEGIN);
  SetFilePosition(0, 0, SEEK_SET);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileWriteBufferedStream::~FileWriteBufferedStream()
{
  SetEndOfFile(); // Truncate file for the case, when was preallocated more than written
  Close();
  FreeBuffer( &buffer );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteBufferedStream::InitInternal()
{
  SetCanSeek( true );
  SetCanWrite( true );
  SetCanRead( false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteBufferedStream::Open(const string & _fileName)
{
  OpenInternal(_fileName);

  //if (file != INVALID_HANDLE_VALUE)
  if (file != -1)
  {
    SetBroken( false );
  }
  else
  {
    //DebugTrace("Failed to open file %s with error %d.", _fileName.c_str(), GetLastError());
    DebugTrace("Failed to open file %s with error %d.", _fileName.c_str(), errno);
  }

  fileName = _fileName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Opens file for synchronous write
void FileWriteBufferedStream::OpenInternal(const string & _fileName)
{
  //file = CreateFileA(_fileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, creationMode, 
                      //FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH, NULL);
  file = ::open( _fileName.c_str(), creationMode );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FileWriteBufferedStream::ReadInternal( void *pData, const int length ) 
{ 
  NI_ALWAYS_ASSERT( "Read is not supported on a writing stream!" );
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Allocates/reallocates the buffer
void FileWriteBufferedStream::SetSizeInternal( const int _size )
{
  char * newBuffer = 0;

  if (_size > 0)
  {
    // Alloc
    newBuffer = AllocateBuffer( _size );

    if (newBuffer && buffer && position > 0)
    {
      // Realloc
      int copySize = Min( position, _size );
      memcpy( newBuffer, buffer, copySize );
      position = copySize;
    }
  }

  // Free old buffer
  FreeBuffer( &buffer );

  buffer = newBuffer;
  size = ( buffer ) ? ( _size ) : ( 0 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * FileWriteBufferedStream::AllocateBuffer( const int _size )
{
  return new char[_size];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteBufferedStream::FreeBuffer( char ** _buffer )
{
  delete [] *_buffer;
  *_buffer = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Writes data to the buffer
int FileWriteBufferedStream::WriteInternal( const void *pData, const int length )
{
  NI_VERIFY( size - position >= length, "Buffer underrun!", return 0; );

  memcpy( &buffer[position], pData, length );
  position += length;

  return length;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteBufferedStream::SetFilePosition(long posLow, long, unsigned long moveFrom)
{
  //NI_VERIFY(file != INVALID_HANDLE_VALUE, "File isn't open!", return; );
  NI_VERIFY(file != -1, "File isn't open!", return; );

  //DWORD retVal = SetFilePointer( file, posLow, &posHigh, moveFrom);
  int retVal = ::lseek( file, posLow, moveFrom );
  //NI_VERIFY( retVal != INVALID_SET_FILE_POINTER, 
                //NI_STRFMT("Failed to set file pointer with error %d.", GetLastError()), SetBroken( true ); );
  NI_VERIFY( retVal != -1, 
                NI_STRFMT("Failed to set file pointer with error %d.", errno), SetBroken( true ); );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Resizes the file
void FileWriteBufferedStream::SetFileSize(const int _size)
{
  //SetFilePosition(_size, NULL, FILE_BEGIN);
  SetFilePosition(_size, 0, SEEK_SET);
  SetEndOfFile();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Truncates file by setting the current file position to be the end of the file
void FileWriteBufferedStream::SetEndOfFile()
{
  //NI_VERIFY(file != INVALID_HANDLE_VALUE, "File isn't open!", return; );
  NI_VERIFY(file != -1, "File isn't open!", return; );

  //BOOL retVal = ::SetEndOfFile(file);
  const off_t filePos = ::lseek( file, 0, SEEK_CUR );
  const int retVal = ::ftruncate( file, filePos );
  //NI_VERIFY(retVal != FALSE, "Failed to set end of file!", SetBroken( true ); );
  NI_VERIFY(retVal != -1, "Failed to set end of file!", SetBroken( true ); );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reserves buffer of a specific size
void FileWriteBufferedStream::ReserveBuffer( const int _size )
{
  SetSize(_size);
  Seek(0, SEEKORIGIN_BEGIN);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileWriteBufferedStream::Close()
{
  //CloseHandle( file );
  ::close( file );
  //file = INVALID_HANDLE_VALUE;
  file = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Flush data to the file synchronously
void FileWriteBufferedStream::Flush()
{
  //NI_VERIFY(file != INVALID_HANDLE_VALUE, "File isn't open!", return; );
  NI_VERIFY(file != -1, "File isn't open!", return; );

  if (position == 0 || size == 0)
    return;

  //DWORD dwBytesWritten;
  //BOOL res = WriteFile( file, buffer, position, &dwBytesWritten, NULL);
  ssize_t bytesWritten = ::write( file, buffer, position );

  //NI_VERIFY( res != FALSE && (int)dwBytesWritten == position, "File write failed!", SetBroken( true ); );
  NI_VERIFY( (int)bytesWritten == position, "File write failed!", SetBroken( true ); );

  position = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( FileWriteBufferedStream );
