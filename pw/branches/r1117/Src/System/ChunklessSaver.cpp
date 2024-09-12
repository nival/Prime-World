#include "stdafx.h"
#include "ChunklessSaver.h"
#include <string>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
//#define CHECK_CHUNK_ORDER
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define READ_VERIFY( dst, size, doOnErr )                           \
{ SIZE_VERIFY(size, doOnErr; )                                      \
  if ( size != pResult->Read( dst, size ) )                         \
  { SetError(BINSAVER_ERR_READ_FAILED); { doOnErr; } }              \
}            
  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::CheckChunk( const chunk_id idChunk, int nChunkNumber )
{
#ifdef CHECK_CHUNK_ORDER
  if ( IsReading() )
  {
    chunk_id id;
    int nChunk;
    pResult->Read( &id, 1 );
    pResult->Read( &nChunk, 4 );
    NI_ASSERT( id == idChunk && nChunk == nChunkNumber, "serialization order differs in read/write" );
  }
  else
  {
    if ( !pResult )
      return;
    pResult->Write( &idChunk, 1 );
    pResult->Write( &nChunkNumber, 4 );
  }
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
{
  CheckChunk( idChunk, nChunkNumber );
  if ( IsReading() )
    READ_VERIFY( pData, nSize, return; )
  else
  {
    if ( !pResult )
      return;
    pResult->Write( pData, nSize );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::DataChunkString( string &data )
{
#if defined ( NV_WIN_PLATFORM )
  int nSize;
#elif defined( NV_LINUX_PLATFORM )
  nival::int32_t nSize;
#endif
  if ( IsReading() )
  {
    READ_VERIFY( &nSize, 4, return; );
    CONTAINER_SIZE_VERIFY( nSize, return; );
    data.resize( nSize );
    NI_ASSERT( nSize >= 0, "Invalid serialized string" );
    if ( nSize != 0 )
      READ_VERIFY( &data[0], nSize, return; )
  }
  else
  {
    if ( !pResult )
      return;
    nSize = data.size();
    pResult->Write( &nSize, 4 );
    if ( !data.empty() )
      pResult->Write( &data[0], nSize );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::DataChunkString( wstring &data )
{
#if defined ( NV_WIN_PLATFORM )
  int nSize;
#elif defined( NV_LINUX_PLATFORM )
  nival::int32_t nSize;
#endif
  if ( IsReading() )
  {
    READ_VERIFY( &nSize, 4, return; );
    CONTAINER_SIZE_VERIFY( nSize, return; );
    data.resize( nSize );

    if ( nSize != 0 )
    {
#if defined( NV_WIN_PLATFORM )
      READ_VERIFY( &data[ 0 ], nSize * 2, return; )
#elif defined( NV_LINUX_PLATFORM )
      std::basic_string< nival::uint16_t > sp( nSize, 0 );
      READ_VERIFY( &sp[ 0 ], nSize * 2, return; )
      std::copy( sp.begin(), sp.end(), data.begin() );
#endif
    }
  }
  else
  {
    if ( !pResult )
      return;
    nSize = data.size();
    pResult->Write( &nSize, 4 );

    if ( !data.empty() )
    {
#if defined( NV_WIN_PLATFORM )
      pResult->Write( &data[ 0 ], nSize * 2 );
#elif defined( NV_LINUX_PLATFORM )
      std::basic_string< nival::uint16_t > sp( nSize, 0 );
      std::copy( data.begin(), data.end(), sp.begin() );
      pResult->Write( &sp[ 0 ], nSize * 2 );
#endif
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::DataChunkString( nstl::fixed_string_base<char> &data )
{
  nival::int16_t nSize;
  nival::int16_t nLength;

  if ( IsReading() )
  {
    READ_VERIFY( &nSize, sizeof(nSize), return );
    READ_VERIFY( &nLength, sizeof(nLength), return );

    CONTAINER_SIZE_VERIFY( nSize, return );

    data.Resize(nLength);

    // kinda overflow check
    NI_VERIFY( data.GetStorageSize() == int(nSize), "Invalid serialized string", return );
    NI_VERIFY( data.GetLength() == int(nLength), "Invalid serialized string", return );

    if ( nSize > 0 )
      READ_VERIFY( data.GetData(), nSize, return )
  }
  else
  {
    if ( !pResult )
      return;

    nSize = nival::int16_t(data.GetStorageSize());
    nLength = nival::int16_t(data.GetLength());

    // kinda overflow check
    NI_VERIFY( data.GetStorageSize() == int(nSize), "Invalid serialized string", return );
    NI_VERIFY( data.GetLength() == int(nLength), "Invalid serialized string", return );

    pResult->Write( &nSize, sizeof(nSize) );
    pResult->Write( &nLength, sizeof(nLength) );

    // TODO: verify write?
    if ( nSize > 0 )
      pResult->Write( data.GetData(), nSize );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::DataChunkString( nstl::fixed_string_base<wchar_t> &data )
{
  nival::int16_t nSize;
  nival::int16_t nLength;

  if ( IsReading() )
  {
    READ_VERIFY( &nSize, sizeof(nSize), return );
    READ_VERIFY( &nLength, sizeof(nLength), return );

    CONTAINER_SIZE_VERIFY( nSize, return );

    data.Resize(nLength);

    // kinda overflow check
    NI_VERIFY( data.GetStorageSize() == int(nSize), "Invalid serialized string", return );
    NI_VERIFY( data.GetLength() == int(nLength), "Invalid serialized string", return );

    if ( nSize > 0 )
      READ_VERIFY( data.GetData(), nSize, return )
  }
  else
  {
    if ( !pResult )
      return;

    nSize = nival::int16_t(data.GetStorageSize());
    nLength = nival::int16_t(data.GetLength());

    // kinda overflow check
    NI_VERIFY( data.GetStorageSize() == int(nSize), "Invalid serialized string", return );
    NI_VERIFY( data.GetLength() == int(nLength), "Invalid serialized string", return );

    pResult->Write( &nSize, sizeof(nSize) );
    pResult->Write( &nLength, sizeof(nLength) );

    // TODO: verify write?
    if ( nSize > 0 )
      pResult->Write( data.GetData(), nSize );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChunklessSaver::StoreObject( CObjectBase *pObject )
{
  NI_VERIFY( IsValid( pPointerHolder ), "Invalid pointer holder", return );

  int nID = pPointerHolder->GetObjectID( pObject );
  if ( pResult )
    pResult->Write( &nID, 4 );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObjectBase* ChunklessSaver::LoadObject()
{
  NI_VERIFY( IsValid( pPointerHolder ), "Invalid pointer holder", return 0 );

  int nID;
  READ_VERIFY( &nID, 4, return 0; )
  CObjectBase *pResult = pPointerHolder->GetObject( nID );
  return pResult;
}



void ChunklessSaver::StoreObjectST( BaseObjectST * object )
{
  NI_VERIFY( IsValid( pPointerHolder ), "", return );
  int id = pPointerHolder->GetObjectIdST( object );
  if ( pResult )
    pResult->Write( &id, 4 );
}



BaseObjectST * ChunklessSaver::LoadObjectST()
{
  NI_VERIFY( IsValid( pPointerHolder ), "", return 0 );
  int id = 0;
  READ_VERIFY( &id, 4, return 0; )
  BaseObjectST * object = pPointerHolder->GetObjectST( id );
  return object;
}



void ChunklessSaver::StoreObjectMT( BaseObjectMT * object )
{
  NI_VERIFY( IsValid( pPointerHolder ), "", return );
  int id = pPointerHolder->GetObjectIdMT( object );
  if ( pResult )
    pResult->Write( &id, 4 );
}



BaseObjectMT * ChunklessSaver::LoadObjectMT()
{
  NI_VERIFY( IsValid( pPointerHolder ), "", return 0 );
  int id = 0;
  READ_VERIFY( &id, 4, return 0; )
  BaseObjectMT * object = pPointerHolder->GetObjectMT( id );
  return object;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBinSaver *CreateChunklessSaver( Stream *pStream, IPointerHolder *pPointerHolder, bool reading, uint containerSizeLimit, uint totalSizeLimit )
{
  return new ChunklessSaver( pStream, pPointerHolder, reading, containerSizeLimit, totalSizeLimit );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( IPointerHolder )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
