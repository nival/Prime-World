#ifndef NETWORKBUFFERS_H_AEB58EA1_5795_4
#define NETWORKBUFFERS_H_AEB58EA1_5795_4
#include "System/BipBuffer.h"
#include "../System/Thread.h"
#include "zlib.h"

namespace Network
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct GatherMessageBuffer
{
private:
  enum { HEAD_SIZE = sizeof(ushort), MESSAGE_SIZE_MAX = (ushort)(~(ushort)0) };
  BipBuffer buffer;
  volatile int writeBufferSize;
public:
  GatherMessageBuffer( int size )
  {
    writeBufferSize = 0;
    buffer.AllocateBuffer( size );
  }

  void Clear() 
  {  
    buffer.Clear();
  }
  int GetDataSize() const
  {
    return buffer.GetCommittedSize();
  }
  int GetTotalSize() const
  {
    return buffer.GetBufferSize();
  }

  void IncreaseSize( int desiredIncrease )
  {
    NI_ASSERT( writeBufferSize <= 0, "Has unsent data on resize" );

    int newBufSize = buffer.GetBufferSize() + desiredIncrease * 3 / 2;
    buffer.ResizeBuffer( newBufSize );
  }

  //Producer end 
  bool AddMessage( byte* data, int _size )
  {
    NI_ASSERT( _size <= MESSAGE_SIZE_MAX, "Mesaage too long" );

    int size = _size + HEAD_SIZE;
    int reserved = 0;
    byte* toWrite = buffer.Reserve( size, reserved );

    if( reserved < size )
    {
      buffer.Commit(0);
      return false;
    }

    *(ushort*)toWrite = _size;
    memcpy( toWrite + HEAD_SIZE, data, _size );

    buffer.Commit( size );
    return true;
  }

  //Consumer end 
  bool GetData( byte** data, int* size )
  {
    *data = buffer.GetContiguousBlock( *size );
    writeBufferSize = *size;
    return *data;
  }

  //Consumer end 
  bool HasData() const
  {
    int sz;
    return buffer.GetContiguousBlock( sz ) != 0;
  }

  //Consumer end 
  void ReleaseData( int size )
  {
    buffer.DecommitBlock( size );
    writeBufferSize -= size;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ScatterMessageBuffer
{
private:
  enum { HEAD_SIZE = sizeof(ushort), MESSAGE_SIZE_MAX = (ushort)(~(ushort)0) };

  BipBuffer buffer;
  int writeChunk;
  int lastMessageSize;
  vector<byte> largeMsgBuffer;
  int largeMsgSizeLeft; 
  mutable threading::Mutex bufferlock;

  enum EReadState
  {
    S_HEAD,
    S_DATA,
    S_LARGE_START,
    S_LARGE_NEXT,
  };
  EReadState readState;
  int nextMessageSize;
  int nextMessagePos;

  int CopyToLargeBuffer( int blockSize, byte* data )
  {
    bufferlock.Lock();

    int copySize = Min( blockSize, largeMsgSizeLeft );
    byte* copyTo = largeMsgBuffer.end();
    largeMsgBuffer.resize( largeMsgBuffer.size() + copySize );
    memcpy( copyTo, data, copySize );
    largeMsgSizeLeft -= copySize;
    bufferlock.Unlock();
    return copySize;
  }

public:
  ScatterMessageBuffer( int size, int _writeChunk )
  {
    buffer.AllocateBuffer( size );
    writeChunk = _writeChunk;
    lastMessageSize = 0;

    largeMsgSizeLeft = 0;

    readState = S_HEAD;
    nextMessageSize = 0;
  }

  void Clear() 
  {  
    bufferlock.Lock();
    buffer.Clear();
    bufferlock.Unlock();
  }
  int GetDataSize()
  {
    return buffer.GetCommittedSize();
  }

  bool HasSpaceToWrite() const 
  {
    return buffer.GetFreeSpace() > 0;
  }
  //Producer end 
  bool GetWriteBuffer( byte** data, int* size )
  {
    bufferlock.Lock();
    *data = buffer.Reserve( writeChunk, *size );
    bufferlock.Unlock();
    return *data;
  }
  //Producer end 
  void CommitWriteBuffer( int size )
  {
    bufferlock.Lock();
    buffer.Commit( size );
    bufferlock.Unlock();
  }

  //Consumer end 
  int ReadNextMessageSize()
  {
    if ( readState == S_HEAD )
    {
      nextMessageSize = 0;

      if ( buffer.GetCommittedSize() < HEAD_SIZE )
        return false;

      byte msgHead[HEAD_SIZE];

      // read head 
      bufferlock.Lock();

      int blockSize;
      byte* block = buffer.GetContiguousBlock( blockSize ); 
      int copied = Min( blockSize, (int)HEAD_SIZE );
      memcpy( msgHead, block, copied );
      buffer.DecommitBlock( copied );
      block = buffer.GetContiguousBlock( blockSize );
      if ( copied < HEAD_SIZE )
      {
        memcpy( msgHead + copied, block, HEAD_SIZE - copied );
        buffer.DecommitBlock( HEAD_SIZE - copied );
        block = buffer.GetContiguousBlock( blockSize );
      }
      bufferlock.Unlock();

      nextMessageSize = *(ushort*)msgHead;
      nextMessagePos = 0;

      readState = S_DATA;
    }

    return nextMessageSize;
  }

  bool CopyMessage( byte* buf, int size )
  {
    NI_VERIFY( readState != S_HEAD, "message not ready", return false );
    NI_VERIFY( size == nextMessageSize, "Buffer size invalid", return false );

    if ( readState == S_DATA )
    {
      bufferlock.Lock();

      int blockSize = 0;
      byte* block = buffer.GetContiguousBlock( blockSize );
      int toCopy = Min( blockSize, nextMessageSize - nextMessagePos );

      memcpy( buf + nextMessagePos, block, toCopy );
      nextMessagePos += toCopy;
      buffer.DecommitBlock( toCopy );

      bufferlock.Unlock();
      if ( nextMessagePos >= nextMessageSize )
        readState = S_HEAD;
    }

    return readState == S_HEAD;
  }

  //Consumer end 
  bool GetMessage( byte** data, int* size )
  {
    int blockSize;
    byte* block = buffer.GetContiguousBlock( blockSize ); 
    if ( blockSize <= 0 )
      return false;

    if ( readState == S_HEAD )
    {
      if ( buffer.GetCommittedSize() < HEAD_SIZE )
        return false;

      byte msgHead[HEAD_SIZE];

      // read head 
      int copied = Min( blockSize, (int)HEAD_SIZE );
      memcpy( msgHead, block, copied );
      buffer.DecommitBlock( copied );
      block = buffer.GetContiguousBlock( blockSize );
      if ( copied < HEAD_SIZE )
      {
        memcpy( msgHead + copied, block, HEAD_SIZE - copied );
        buffer.DecommitBlock( HEAD_SIZE - copied );
        block = buffer.GetContiguousBlock( blockSize );
      }
      nextMessageSize = *(ushort*)msgHead;
      if ( nextMessageSize >= buffer.GetBufferSize() - 4 )
        readState = S_LARGE_START;
      else
        readState = S_DATA;
    }

    if ( readState == S_DATA )
    {
      int totalSize = buffer.GetCommittedSize();


      if ( totalSize >= nextMessageSize ) // whole message received
      {
        bufferlock.Lock();
        block = buffer.GetContiguousBlock( blockSize );
        *data = block;
        *size = nextMessageSize;

        lastMessageSize = *size;
        bufferlock.Unlock();
        readState = S_HEAD;
        return true;
      }
    }
    else  if ( readState == S_LARGE_START )
    {
      bufferlock.Lock();
      largeMsgBuffer.resize( 0 );
      largeMsgBuffer.reserve( nextMessageSize );
      largeMsgSizeLeft = nextMessageSize;
      CopyToLargeBuffer( blockSize, block );
      buffer.DecommitBlock( blockSize );
      bufferlock.Unlock();
      readState = S_LARGE_NEXT;
    }
    else if( readState == S_LARGE_NEXT )
    {
      bufferlock.Lock();
      int copied = CopyToLargeBuffer( blockSize, block );
      buffer.DecommitBlock( copied );
      bufferlock.Unlock();

      if ( largeMsgSizeLeft == 0 )
      {
        *size = largeMsgBuffer.size();
        *data = largeMsgBuffer.begin();
        lastMessageSize = *size;
        readState = S_HEAD; 
        return true;
      }
    }
    return false;
  }

  void ReleaseMessage()
  {
    NI_ASSERT( lastMessageSize != 0, "ReleaseMessage called without call to GetMessage" );
    bufferlock.Lock();
    if ( !largeMsgBuffer.empty() )
      largeMsgBuffer.resize( 0 );
    else
      buffer.DecommitBlock( lastMessageSize );
    lastMessageSize = 0;
    bufferlock.Unlock();
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ZlibComressor
{
  ZlibComressor()
    : bufSize(0)
    , buffer(0)
    , flush(Z_FINISH)
    , inSize(0)
  {
    strm.avail_in = 0;
    strm.avail_out = 0;
    strm.next_in = 0;
    strm.next_out = 0;
    strm.opaque = 0;
  }

  ~ZlibComressor()
  {
    if ( strm.opaque )
      deflateEnd( &strm );
    strm.opaque = 0;
    delete[] buffer;
  }

  static voidpf AllocFunc(voidpf opaque, uInt items, uInt size)
  {
    return new uchar[items * size];
  }

  static void   FreeFunc(voidpf opaque, voidpf address)
  {
    delete [] static_cast< uchar* >( address );
  }

  void Init( int internalBufferSize, bool compress )
  {
    bufSize = internalBufferSize * 1.001f + 12;
    buffer = new byte[ bufSize ];

    strm.zalloc = AllocFunc;
    strm.zfree = FreeFunc;
    strm.opaque = (voidpf)1;
    ret = deflateInit(&strm, compress ? Z_DEFAULT_COMPRESSION : Z_NO_COMPRESSION);
    strm.avail_in = 0;
    strm.avail_out = 0;
    strm.next_out = buffer;
    strm.avail_out = bufSize;
    inSize = 0;
    flush = Z_NO_FLUSH;
  }

  void Flush()
  {
    flush = Z_SYNC_FLUSH;
    Process();
  }
  void Close()
  {
    flush = Z_FINISH;
    Process();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SetDataIn( byte* data, int size )
  {
    NI_ASSERT( GetDataInProcessed() == inSize, "In buffer is not compressed yet" )
      NI_ASSERT( flush != Z_FINISH, "Adding data after close" )

      if ( flush == Z_SYNC_FLUSH )
        flush = Z_NO_FLUSH;

    strm.next_in = data;
    strm.avail_in = size;
    inSize = size;
    Process();
  }
  int GetDataInProcessed() const
  {
    return inSize - strm.avail_in;
  }
  void ProcessedDataIn()
  {
    strm.avail_in = 0;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void GetDataOut( byte** data, int* size )
  {
    Process();
    *data = buffer;
    *size = bufSize - strm.avail_out;
  }

  int GetOutDataSize() const
  {
    return  bufSize - strm.avail_out;
  }

  void ProcessedDataOut()
  {
    strm.next_out = buffer;
    strm.avail_out = bufSize;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

  void Process()
  {
    if ( strm.avail_out == 0 )
      return;

    if ( flush == Z_SYNC_FLUSH && strm.avail_in == 0 && ret == Z_BUF_ERROR )
      return;

    ret = deflate(&strm, flush); 
    if ( ret == Z_STREAM_END )
      deflateEnd( &strm );
  }

  byte* buffer;
  int bufSize;
  int flush;
  z_stream strm;
  int ret;
  int inSize;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ZlibDecomressor
{
  ZlibDecomressor()
    : bufSize(0)
    , buffer(0)
    , flush(Z_FINISH)
  {
    strm.avail_in = 0;
    strm.avail_out = 0;
    strm.next_in = 0;
    strm.next_out = 0;
    strm.opaque = 0;
  }

  ~ZlibDecomressor()
  {
    if ( strm.opaque )
      inflateEnd( &strm );
    strm.opaque = 0;

    delete[] buffer;
  }

  static voidpf AllocFunc(voidpf opaque, uInt items, uInt size)
  {
    return new uchar[items * size];
  }

  static void   FreeFunc(voidpf opaque, voidpf address)
  {
    delete [] static_cast< uchar* >( address );
  }

  void Init( int internalBufferSize )
  {
    bufSize = internalBufferSize * 1.001f + 12;
    buffer = new byte[ bufSize ];

    strm.zalloc = AllocFunc;
    strm.zfree = FreeFunc;
    strm.opaque = (voidpf)1;
    ret = inflateInit( &strm );
    strm.next_in = buffer;
    strm.avail_in = 0;
    strm.next_out = 0;
    strm.avail_out = 0;
    flush = Z_NO_FLUSH;
  }

  void Close()
  {
    flush = Z_FINISH;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void GetBufferIn( byte** data, int* size )
  {
    *data = strm.next_in + strm.avail_in;
    *size = buffer + bufSize - strm.next_in - strm.avail_in;
  }
  int GetBufferInSize() const 
  {
    return buffer + bufSize - strm.next_in - strm.avail_in;
  }
  void CommitBufferIn( int actualSize )
  {
    NI_ASSERT( actualSize <= GetBufferInSize(), "Error: no buffer" );
    strm.avail_in = strm.avail_in + actualSize;
    Process();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void SetBufferOut( byte* data, int size )
  {
    outDataSize = size;
    strm.next_out = data;
    strm.avail_out = size;
    Process();
  }
  int GetReadyOutData()
  {
    int ready = outDataSize - strm.avail_out;
    strm.next_out = 0;
    strm.avail_out = 0;
    outDataSize = 0;
    return ready;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

  void Process()
  {
    if ( strm.avail_out == 0 )
      return;

    ret = inflate(&strm, flush); 

    if ( ret == Z_STREAM_END )
      inflateEnd( &strm );

    if ( ret < 0 )

    NI_ASSERT( ret != Z_MEM_ERROR, "ZLib memory allocation error" );
    NI_ASSERT( ret >= 0 || ret == Z_BUF_ERROR, NI_STRFMT( "Decompression error: %d", ret ) );

    if ( strm.avail_in == 0 )
      strm.next_in = buffer;
  }

  byte* buffer;
  int bufSize;
  int outDataSize;
  int flush;
  z_stream strm;
  int ret;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif //#define NETWORKBUFFERS_H_AEB58EA1_5795_4
