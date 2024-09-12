#include "stdafx.h"
#include "MemoryStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MemoryStream::GetNewSize( const int oldSize, const int newSize )
{
	if ( newSize < oldSize )
	{
		//if ( oldSize > newSize * 2 )
		//	return newSize;
		//else
			return oldSize;
	}
	else
	{
    int diff = Max( oldSize / 2, 8 );

		for( int i = 0; i < 64; ++i, diff = ( diff * 3 ) / 2 )
		{
			if ( oldSize + diff > newSize )
				return oldSize + diff;
		}

		return newSize;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryStream::MemoryStream() : Stream(), pBuffer( 0 ), offset( 0 ), realSize( 0 ), bufferSize( 0 )
{
	SetCanSeek( true );
	SetCanWrite( true );
	SetCanRead( true );
	SetBroken( false );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryStream::MemoryStream( const int initialSize ) : Stream(), pBuffer( 0 ), offset( 0 ), realSize( 0 ), bufferSize( 0 )
{
	SetCanSeek( true );
	SetCanWrite( true );
	SetCanRead( true );
	SetBroken( false );

	SetSizeInternal( initialSize );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryStream::MemoryStream( const MemoryStream& other )
{
	pBuffer = 0;
	offset = 0;
	realSize = 0;
	bufferSize = 0;

	SetCanSeek( true );
	SetCanWrite( true );
	SetCanRead( true );
	SetBroken( false );

	const int length = other.GetSize();
	const char *pBuffer = other.GetBuffer();
	if ( length > 0 && pBuffer )
	{
		Write( pBuffer, length );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryStream::~MemoryStream()
{
  Close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryStream& MemoryStream::operator = ( const MemoryStream& other )
{
	if( *this != other )
	{
		Close();

		const int length = other.GetSize();
		const char *pBuffer = other.GetBuffer();
		if ( length > 0 && pBuffer )
		{
			SetCanSeek( true );
			SetCanWrite( true );
			SetCanRead( true );
			SetBroken( false );
			Write( pBuffer, length );
		}
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MemoryStream::operator == ( const MemoryStream& other ) const
{
	return offset == other.offset && realSize == other.realSize && bufferSize == other.bufferSize &&
		(0 == ::memcmp( pBuffer, other.pBuffer, realSize ));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MemoryStream::operator != ( const MemoryStream& other ) const
{
	return !(*this == other);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemoryStream::SeekInternal( const int _offset )
{
	offset = _offset;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * MemoryStream::AllocateBuffer(size_t nSize)
{
  return new char[nSize];
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void   MemoryStream::FreeBuffer    (char   *&pBuffer)
{
  delete[] pBuffer;
  pBuffer = NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemoryStream::SetSizeInternal( const int size )
{
	SetSizeInternal(size, &MemoryStream::AllocateBuffer, &MemoryStream::FreeBuffer);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemoryStream::SetSizeInternal( const int size, AllocBuff fAllocPtr, FreeBuff fFreePtr)
{
  const int newSize = GetNewSize( bufferSize, size );
  if ( newSize == bufferSize )
  {
    realSize = size;
    return;
  }

  const int copySize = Min( realSize, size );

  char *pNewBuffer = size != 0 ? (this->*fAllocPtr)(newSize) : 0;
  NI_VERIFY( size == 0 || pNewBuffer, "Memory allocation failed", return );

  if ( copySize > 0 )
    memcpy( pNewBuffer, pBuffer, copySize );

  if ( pBuffer != 0 )
  {
    (this->*fFreePtr)(pBuffer);
  }

  pBuffer = pNewBuffer;
  realSize = size;
  bufferSize = newSize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MemoryStream::ReadInternal( void *pData, const int length )
{
	memcpy( pData, pBuffer + offset, length );
	offset += length;
	return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MemoryStream::WriteInternal( const void *pData, const int length )
{
  NI_ASSERT( offset + length <= bufferSize, "Stream overflow" );
	memmove( pBuffer + offset, pData, length );
	offset += length;
	return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemoryStream::Close()
{
  FreeBuffer(pBuffer);
	offset = 0;
	realSize = 0;
	bufferSize = 0;

	SetBroken( true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( MemoryStream );

