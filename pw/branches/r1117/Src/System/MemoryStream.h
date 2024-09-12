#ifndef MEMORYSTREAM_H__
#define MEMORYSTREAM_H__

#include "Stream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MemoryStream : public Stream, public CObjectBase
{
	OBJECT_METHODS( 0x1E4A8B45, MemoryStream );

	char *pBuffer;
	int offset;
	int realSize;
	int bufferSize;

protected:
  typedef char * (MemoryStream::*AllocBuff)(size_t nSize ); 
  typedef void   (MemoryStream::*FreeBuff )(char  *&pBuffer ); 
	void SeekInternal( const int offset );
	void SetSizeInternal( const int size );
  void SetSizeInternal( const int size, AllocBuff fAllocPtr, FreeBuff fFreePtr);

	int ReadInternal( void *pData, const int length );
	int WriteInternal( const void *pData, const int length );

  virtual char * AllocateBuffer(size_t nSize);
  virtual void   FreeBuffer    (char   *&pBuffer);
  int GetBufferSize() const {return bufferSize;}
  static int GetNewSize( const int oldSize, const int newSize );

public:
	MemoryStream();
	MemoryStream( const int initialSize);
	MemoryStream( const MemoryStream& );
  virtual ~MemoryStream();

	MemoryStream& operator = ( const MemoryStream& );

	virtual bool operator == ( const MemoryStream& ) const;
	virtual bool operator != ( const MemoryStream& ) const;

	MemoryStream * operator & ()
	{
		return this;
	}

	MemoryStream const * operator & () const
	{
		return this;
	}

	int GetSize() const { return realSize; }
	int GetPosition() const { return offset; }

	const char *GetBuffer() const { return pBuffer; }
	char *GetBuffer() { return pBuffer; }

	virtual void Close();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif   //MEMORYSTREAM_H__

