#include "stdafx.h"

#include "Stream.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Stream::Seek( int offset, ESeekOrigin seekOrigin )
{
	NI_VERIFY( CanSeek(), "Cannot seek on this stream", return 0 );
	int newOffset = 0;

	switch( seekOrigin )
	{
		case SEEKORIGIN_BEGIN:
			newOffset = offset;
			break;
		case SEEKORIGIN_OFFSET:
			newOffset = offset + GetPosition();
			break;
		case SEEKORIGIN_END:
			newOffset = GetSize() - offset;
			break;
		default:
			return GetPosition();
	}

	if ( newOffset > GetSize() )
		SetSizeInternal( newOffset );
		
	NI_VERIFY( 0 <= newOffset && newOffset <= GetSize(), NI_STRFMT( "Cannot seek on stream (offset = %d, size = %d)", newOffset, GetSize() ), return GetPosition() );
	SeekInternal( newOffset );
	return GetPosition();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Stream::SetSize( const int size )
{
	if ( size == GetSize() )
		return GetSize();

	NI_VERIFY( CanWrite() && CanSeek(), "Cannot change size for this stream", return 0 );
	const int oldPos = GetPosition();
	SetSizeInternal( size );
	if ( oldPos >= GetSize() )
		Seek( GetSize(), SEEKORIGIN_BEGIN );

	return GetSize();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Stream::Read( void *pData, const int length )
{
	NI_VERIFY( CanRead(), NI_STRFMT( "Cannot read from this stream, flags = 0x%02X", flags ), return 0 );
	return ReadInternal( pData, Min( length, GetSize() - GetPosition() ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Stream::Write( const void *pData, const int length )
{
	NI_VERIFY( CanWrite(), NI_STRFMT( "Cannot write to this tream, flags = 0x%02X", flags ), return 0 );
	if ( GetPosition() + length > GetSize() )
		SetSize( GetPosition() + length );

	return WriteInternal( pData, Min( length, GetSize() - GetPosition() ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Stream::CopyFrom( Stream *pStream )
{
	if ( !IsValid( pStream ) || pStream->GetSize() == 0 )
		return;

	CopyFrom( pStream, pStream->GetSize() - pStream->GetPosition() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Stream::CopyFrom( Stream *pStream, const int _length )
{
	if ( !IsValid( pStream ) )
		return;

	const int length = Min( _length, pStream->GetSize() - pStream->GetPosition() );
	if ( length <= 0 )
		return;

	const char *pBuffer = pStream->GetBuffer();
	if ( pBuffer )
	{
		pBuffer += pStream->GetPosition();
		Write( pBuffer, length );
		pStream->Seek( length, SEEKORIGIN_OFFSET );
	}
	else
	{
		//FIXME - copy via new buffer
		NI_ALWAYS_ASSERT( "Cannot get direct buffer from stream" );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Stream::ReadString( string &res, int nMaxSize )
{
	res.clear();
	if ( !CanRead() || GetPosition() == GetSize() )
		return false;

	const int length = GetSize() - GetPosition() + 1;
	char *buffer = new char[ length ];
	Read( &buffer[0], 1 );
		
	int i = 0;
	while ( buffer[i] != '\r' && buffer[i] != '\n' && i < length )
	{
		++i;
		Read( &buffer[i], 1 );
	}

	if ( i != 0 )
		res.assign( &buffer[0], i - 1 );

	delete[] buffer;
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( Stream );
