#pragma once
#ifndef _CRC32CHECKSUM_COPY_H_
#define _CRC32CHECKSUM_COPY_H_

#include "Crc32ChecksumFast.h"

class PodBuffer
{
public:
  typedef unsigned char Byte;
  
public:
  explicit PodBuffer(size_t _capacity = 0): pBuf(0), size(0), capacity(0)
  { 
    prepeareForSize(_capacity);
  }
  
  ~PodBuffer()
  {
    operator delete(pBuf);
  }
  
  void Add( const Byte *pData, size_t length )
  {
    prepeareForSize( length );
    memcpy( pBuf + size, pData, length );
    size += length;
  }
  
  void Reset()
  {
    size = 0;
  }
  
  size_t GetSize() const { return size; }
  Byte *GetStart() const { return pBuf;}
  
private:
  void prepeareForSize( size_t length )
  {
    if( length > capacity - size )
    {
      const size_t newCapacity = max( size * 2, size + length );
      
      Byte *const pNewBuf = static_cast<Byte *>(operator new(newCapacity));
      memcpy( pNewBuf, pBuf, size );
      
      operator delete(pBuf);
      pBuf = pNewBuf;
      capacity = newCapacity;
    }
  }

private:
  PodBuffer &operator=( const PodBuffer & );
  PodBuffer( const PodBuffer & ); 
  
private:
  Byte *pBuf;
  size_t size;
  size_t capacity;
};


class Crc32ChecksumCopy
{
public:
  typedef unsigned int Word;
  typedef unsigned char Byte;

  Crc32ChecksumCopy(): buff(4000000)
  { 
    
  }
  
  void Reset()
  {
    buff.Reset();
  }
    
  void Add( const Byte *pBuffer, Word length )
  {  
    buff.Add( pBuffer, length );
  }
      
  // object by reference
  template <class T> void Add(const T &object)
  {
    return Add( &object );
  }

  // object by pointer
  template <class T> void Add(const T *object)
  {
    return Add(static_cast<const Byte *>(static_cast<const void *>(object) ), sizeof(*object) );
  }
  
  // retrieve the result
  Word Get() const
  {      
    Crc32ChecksumFast crc;
  
    crc.Add( buff.GetStart(), buff.GetSize() );
    
    return crc.Get();
  }
  
  unsigned int GetBytesHashed() const
  {
    return buff.GetSize();
  }

private:
  PodBuffer buff;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* _CRC32CHECKSUM_H_ */
