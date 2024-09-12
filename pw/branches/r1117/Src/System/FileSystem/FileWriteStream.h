#pragma once
#include "FileStream.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileStream with memory map writing capabilities that goes outof file bounds
class FileWriteStream : public FileStream
{
	OBJECT_METHODS(0x0E62CBC0, FileWriteStream);

	FileWriteStream(): FileStream(), nMaxImageSize(0) {}

  void MapEmptyFile();
  void ResizeImage(unsigned long nNewSize);
  void UnMapFile();

protected:
	void SeekInternal( const int offset );
	void SetSizeInternal( const int size );

	int ReadInternal( void *pData, const int length );
	int WriteInternal( const void *pData, const int length );

  unsigned long nMaxImageSize;
  unsigned long nMapStartOffset;
  unsigned long nMapWindowSize;
  static unsigned long nAllocationGranularity;

public:
	FileWriteStream(string const &fileName, EFileAccess access, EFileOpen options );
	~FileWriteStream() { Close(); }
	void Close();
};
