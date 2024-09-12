

#include <stdlib.h>
#include <typeinfo>
#include "./TypeProxy.h"

#include "../../System/nlist.h"
#include "../../System/nstring.h"
#include "../../System/nvector.h"
using namespace nstl;
#include "../../System/StrProc.h"
#include "../../System/Logger.h"
#include "../../System/LoggerStream.h"
#include "../../System/SystemLog.h"

#include "../../System/nalgobase.h"

#include "../../System/MemoryStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int GetNewSize( const int oldSize, const int newSize )
{
	if ( newSize < oldSize )
	{
		if ( oldSize > newSize + 8192 )
			return newSize;
		else
			return oldSize;
	}
	else
	{
		for( int i = 0, diff = 4; i < 64; ++i, diff = ( diff * 3 ) / 2 )
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
		(::memcmp( pBuffer, other.pBuffer, realSize ) == 0);
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
void MemoryStream::SetSizeInternal( const int size )
{
	const int newSize = GetNewSize( realSize, size );
	if ( newSize == realSize )
	{
		realSize = size;
		return;
	}

	const int copySize = nstl::min<int>(realSize, size);

	char *pNewBuffer = size != 0 ? new char[newSize] : 0;
	NI_VERIFY( size == 0 || pNewBuffer, "Memory allocation failed", return );

	if ( copySize > 0 )
		memcpy( pNewBuffer, pBuffer, copySize );

	if ( pBuffer != 0 )
	{
		delete[] pBuffer;
		pBuffer = 0;
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
	memcpy( pBuffer + offset, pData, length );
	offset += length;
	return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemoryStream::Close()
{
	if ( pBuffer )
		delete[] pBuffer;
	pBuffer = 0;
	offset = 0;
	realSize = 0;
	bufferSize = 0;

	SetBroken( true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
