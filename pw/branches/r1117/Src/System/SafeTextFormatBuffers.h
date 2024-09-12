#ifndef SAFETEXTFORMATBUFFERS_H_INCLUDED
#define SAFETEXTFORMATBUFFERS_H_INCLUDED

#include "SafeTextFormat.h"

namespace text
{

class ExternalBuffer : public IBuffer
{
public:
  ExternalBuffer( char * _buffer, size_t _size ) :
  buffer( _buffer ), bufferSize( _size ), length( 0 )
  {
    if ( bufferSize ) buffer[0] = 0;
  }

  template <size_t N>
  explicit ExternalBuffer( char (&_buffer)[N] ) :
  buffer( _buffer ), bufferSize( N ), length( 0 )
  {
    if ( bufferSize ) buffer[0] = 0;
  }

  virtual size_t Length() const { return length; }

  virtual size_t SpaceLeft() const { return bufferSize - 1 - length; }

  virtual size_t Write( char c, size_t count ) {
    size_t i = 0;
    for ( ; ( i < count ) && ( length + 1 < bufferSize ); ++i )
      buffer[length++] = c;
    return i;
  }

  virtual size_t Write( const char * bytes, size_t size ) {
    size_t sz = Min( size, bufferSize - 1 - length );
    memcpy( buffer + length, bytes, sz );
    length += sz;
    return sz;
  }

  virtual size_t Finish() {
    buffer[length] = 0;
    return length + 1;
  }

  virtual const char * c_str() const { return buffer; }

private:
  char *  buffer;
  size_t  bufferSize;
  size_t  length;
};




template <size_t N>
class StaticBuffer : public ExternalBuffer
{
public:
  StaticBuffer() :
  ExternalBuffer( stBuffer, N ) {}

private:
  char stBuffer[N];
};



template<class TStlString>
class TStlBuffer : public IBuffer
{
public:
  explicit TStlBuffer( size_t _reserve = 0 )
  {
    str.reserve(_reserve );
  }

  virtual size_t Length() const { return str.length(); }

  virtual size_t SpaceLeft() const {
    return 256u * 1024u * 1024u; //FIXME
  }

  virtual size_t Write( char c, size_t count ) {
    str.append( count, c );
    return count;
  }

  virtual size_t Write( const char * bytes, size_t size ) {
    str.append( bytes, bytes + size );
    return size;
  }

  virtual size_t Finish() { return str.length() + 1; }

  virtual const char * c_str() const { return str.c_str(); }

private:
  TStlString str;
};








template<size_t SZ>
class PrintfFormatterStaticBuffer : public text::PrintfFormatterBufferPtr
{
public:
  PrintfFormatterStaticBuffer()
  {
    SetFormatBuffer( &buffer );
  }

protected:
  text::StaticBuffer<SZ> & Buffer() { return buffer; }
  const text::StaticBuffer<SZ> & Buffer() const { return buffer; }

private:
  text::StaticBuffer<SZ> buffer;
};


} //namespace text

#endif //SAFETEXTFORMATBUFFERS_H_INCLUDED
