#ifndef FILEPILESTREAM_H_INCLUDED
#define FILEPILESTREAM_H_INCLUDED

#include "System/Stream.h"
#include "FilePileFormat.h"

namespace fileSystem
{

class FilePileStream : public Stream, public CObjectBase
{
  OBJECT_BASIC_METHODS( FilePileStream );

  FilePileStream() : refPointer( 0 ), refSize( 0 ), cursor( 0 ) {}

public:
  FilePileStream( vector<Byte> & _buffer ) :
  refPointer( 0 ), refSize( 0 ), cursor( 0 )
  {
    SetCanSeek( true );
    SetCanWrite( false );
    SetCanRead( true );
    SetBroken( false );

    buffer.swap( _buffer );
  }

  //direct pointer to preloaded pack-file
  FilePileStream( Byte * _refPointer, UInt32 _refSize ) :
  refPointer( _refPointer ), refSize( _refSize ), cursor( 0 )
  {}

  virtual void SeekInternal( const int offset )
  {
    NI_VERIFY( offset >= 0 && offset <= GetSize(), "", return );
    cursor = offset;
  }

  virtual void SetSizeInternal( const int size ) { NI_ALWAYS_ASSERT( "Not supported" ); }

  virtual int ReadInternal( void * pData, const int length )
  {
    NI_VERIFY( cursor + length <= GetSize(), "", return 0 );
    memcpy( pData, GetBuffer() + cursor, length );
    cursor += length;
    return length;
  }

  virtual int WriteInternal( const void *pData, const int length ) { NI_ALWAYS_ASSERT( "Not supported" ); return 0; }

  virtual int GetSize() const { return refPointer ? refSize : buffer.size(); }
  virtual int GetPosition() const { return cursor; }

  virtual const char * GetBuffer() const
  {
    if ( refPointer )
      return (const char *)refPointer;

    return buffer.empty() ? 0 : (const char *)&buffer[0];
  }

  virtual void Close() {}

private:
  vector<Byte>    buffer;
  Byte *          refPointer;
  int             refSize;
  int             cursor;
};

} //namespace fileSystem

#endif //FILEPILESTREAM_H_INCLUDED
