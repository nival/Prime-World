#include "stdafx.h"
#include "BinChunkSerializerBase.h"
#include "Progress.h"
#include "Commands.h"
#include "MemoryStream.h"


void BinChunkSaverBase::CChunkLevel::ClearCache() 
{ 
  idLastChunk = (chunk_id)0xff;
  nLastPos = 0;
}



void BinChunkSaverBase::CChunkLevel::Clear() 
{
  idChunk = (chunk_id)0xff; 
  nStart = 0; 
  nLength = 0; 
  ClearCache(); 
}



void BinChunkSaverBase::ClearBase()
{
  chunks.clear();
  obj.SetSize( 0 );
  data.SetSize( 0 );
}



static unsigned long ReadLength( Stream &pStream )
{
  nival::uint32_t result = 0;
	pStream.Read( &result, 1 );
	if ( result & 1 )
		pStream.Read( ((char*)&result)+1, sizeof( result ) - 1 );

	result >>= 1;
	return static_cast< unsigned long >( result );
}



// chunks operations with ChunkLevels
bool BinChunkSaverBase::ReadShortChunk( const CChunkLevel &src, int &nPos, CChunkLevel *pResult )
{
	if ( nPos + 2 > src.nLength )
		return false;

	const int oldPos = data.Seek( src.nStart + nPos, SEEKORIGIN_BEGIN );
	data.Read( &pResult->idChunk, sizeof( pResult->idChunk ) );
	const unsigned long length = ReadLength( data );

	nPos += ( data.GetPosition() - oldPos );

	if ( nPos + (int)length > src.nLength )
		return false;

	pResult->nStart = src.nStart + nPos;
	pResult->nLength = length;
	nPos += length;
	return true;
}



int BinChunkSaverBase::CountShortChunks( const CChunkLevel &src, chunk_id dwID )
{
	int nPos = 0, nRes = 0;
	CChunkLevel temp;
	while ( ReadShortChunk( src, nPos, &temp ) )
	{
		if ( temp.idChunk == dwID )
			nRes++;
	}
	return nRes;
}



int BinChunkSaverBase::CountChunks( const chunk_id idChunk )
{
	return CountShortChunks( chunks.back(), idChunk );
}
