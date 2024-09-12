#pragma once
#include "FileSystem.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StdLibFileStream : public Stream, public CObjectBase
{
  OBJECT_BASIC_METHODS( StdLibFileStream );

public:
	StdLibFileStream( const string & fileName, EFileAccess access, EFileOpen options, bool bAutoMap = true );
	~StdLibFileStream() { Close(); }

  virtual int GetSize() const { return buffer.size(); }
	virtual int GetPosition() const { return pos; }

  virtual const char * GetBuffer() const { return buffer.empty() ? 0 : (const char * )&buffer[0]; }

  virtual void Close() { buffer.clear(); }

  void MapFile() {}
  void UnMapFile() {}

protected:
  StdLibFileStream() : Stream(), pos( 0 ) {}
  
  virtual void SeekInternal( const int offset );
	virtual void SetSizeInternal( const int size );

	virtual int ReadInternal( void *pData, const int length );
	virtual int WriteInternal( const void *pData, const int length );

private:
  typedef unsigned char TByte;

  size_t          pos;
  vector<TByte>   buffer;
};
