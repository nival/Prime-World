#ifndef FILEWRITEASYNCHRONOUSSTREAM_H_3F
#define FILEWRITEASYNCHRONOUSSTREAM_H_3F

#include <System/config.h>

#include "FileWriteBufferedStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is an asynchronous, unbuffered stream (ubuffered here = no OS intermediate buffer), 
// which purpose is fast periodical dump of information. The information is collected in internal 
// dynamic buffer and when it is flushed – only sector aligned part is dumped asynchronously to 
// the disk. Any subsequent operation on stream must be performed after call to the FinishFlush method,
// otherwise data may be lost. Preallocating of the file is essential for this stream to perform well.
class FileWriteAsynchronousStream : public FileWriteBufferedStream
{
  OBJECT_METHODS( 0x22849440, FileWriteAsynchronousStream );

protected:

  unsigned int sectorSize;
  uint64 filePosition;
#ifdef WIN32
  OVERLAPPED overlapped;
#endif
  int tailPosition;
  bool writeStarted;

  virtual void OpenInternal(const string & _fileName);

  virtual char * AllocateBuffer( const int _size );
  virtual void FreeBuffer( char ** buffer );

public:

  FileWriteAsynchronousStream();
  FileWriteAsynchronousStream(const string &fileName);
  FileWriteAsynchronousStream(const string & _fileName, const int _bufferSize, const int _fileSize);
  virtual ~FileWriteAsynchronousStream();

  void Flush();
  void FlushAll();
  void FinishFlush();

  static unsigned int GetSectorSize(const string & path);
  unsigned int RoundDownToSectorSize(unsigned int _size);
};


#endif //#define FILEWRITEASYNCHRONOUSSTREAM_H_3F