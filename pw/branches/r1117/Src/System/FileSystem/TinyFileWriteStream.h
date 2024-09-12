#pragma once
#include "FileSystem.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ѕроста€ обЄртка над сишными fopen/ fwrite
// ѕонадобилась в св€зи с тем, что FileStream работает очень медленно при 
// простой последовательной записи
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TinyFileWriteStream: public Stream, public CObjectBase
{
  OBJECT_BASIC_METHODS( TinyFileWriteStream );
 
public: 
  enum OpenFlags
  {
    TEXT   = 0 << 0,
    BINARY = 1 << 0
  };
  
public:
  explicit TinyFileWriteStream( const string & fileName, int flags = BINARY );
  ~TinyFileWriteStream() { Close(); }

  virtual int GetSize() const;
  virtual int GetPosition() const;

  virtual const char * GetBuffer() const;

  virtual void Close();

protected:
  virtual void SeekInternal( const int offset );
  virtual void SetSizeInternal( const int size );

  virtual int ReadInternal( void *pData, const int length );
  virtual int WriteInternal( const void *pData, const int length );

private:
  TinyFileWriteStream(): hFile(0) { SetBroken( true ); }

private:
  FILE *hFile;
};
