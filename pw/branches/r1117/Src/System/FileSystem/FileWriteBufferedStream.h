#pragma once

#include <System/config.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is a simple buffered file writer stream, intended to be used for sequential data dumping.
// Most of its methods work on a buffer and dumping to file done by explicit call to Flush method. 
// The buffer will grow dynamically, if needed, and may be preallocated using Reserve method or via 
// appropriate constructor. The file also may be preallocated.
class FileWriteBufferedStream : public Stream, public CObjectBase
{
  OBJECT_METHODS( 0x22847380, FileWriteBufferedStream );

protected:

#if defined( NV_WIN_PLATFORM )
  HANDLE        file;
#elif defined( NV_LINUX_PLATFORM )
  int           file;
#endif // defined( NV_WIN_PLATFORM )
  string        fileName;
  char *        buffer;
  int           size;
  int           position;
  int           creationMode;

  FileWriteBufferedStream();

  void InitInternal();
  virtual void OpenInternal(const string & _fileName);

  void SeekInternal( const int offset ) { position = offset; }
  void SetSizeInternal( const int _size );

  virtual char * AllocateBuffer( const int _size );
  virtual void FreeBuffer( char ** buffer );

  int ReadInternal( void *pData, const int length );
  int WriteInternal( const void *pData, const int length );

public:

  FileWriteBufferedStream(const string & _fileName);
  FileWriteBufferedStream(const string & _fileName, const int _bufferSize, const int _fileSize);
  virtual ~FileWriteBufferedStream();

  virtual void Open(const string & _fileName);

  void SetCreationMode(const int _creationMode) { creationMode = _creationMode; }

  void SetFilePosition(long posLow, long posHigh, unsigned long moveFrom);

  void SetFileSize(const int _size);
  void SetEndOfFile();

  int GetSize() const { return size; }
  int GetPosition() const { return position; }

  const char *GetBuffer() const { return buffer; };
  void ReserveBuffer( const int _size );

  virtual void Close();

  void Flush();
};
