#include "stdafx.h"
#include "BinChunkSaverImpl.h"
#include <string>


static void WriteLength( Stream &pStream, const unsigned long length )
{
  nival::uint32_t temp = static_cast< nival::uint32_t >( length );
  temp <<= 1;
  if ( temp > 0xFF )
  {
    temp |= 1;
    pStream.Write( &temp, sizeof( temp ) );
  }
  else
    pStream.Write( &temp, 1 );
}



static bool WriteShortChunkSave( Stream *pFile, IBinSaver::chunk_id dwID, MemoryStream *pChunk )
{
  pFile->Write( &dwID, sizeof( dwID ) );
  WriteLength( *pFile, pChunk->GetSize() );
  pChunk->Seek( 0, SEEKORIGIN_BEGIN );
  pFile->CopyFrom( pChunk );

  return true;
}


#ifdef _DEBUG
static void CheckUnitializedData( const void *_pData, const int length )
{
  const char *pData = (const char *)_pData;
  for ( int i = 0; i < length; ++i )
  {
    NI_VERIFY( pData[i] != 0xcd && pData[i] != 0xad && pData[i] != 0xfd, "Unitialized data found", return );
  }
}
#endif



bool BinChunkSaverImpl::WriteShortChunk( CChunkLevel *pDest, chunk_id dwID, const void *pData, const int nLength )
{
#ifdef _DEBUG
  CheckUnitializedData( pData, nLength );
#endif

  const int oldPos = data.Seek( pDest->nStart + pDest->nLength, SEEKORIGIN_BEGIN );
  data.Write( &dwID, sizeof( dwID ) );
  WriteLength( data, nLength );

  //NI_ASSERT( data.GetBuffer() + data.GetPosition() != pData, "Data Trying copy to itself" ); //looks like this is valid situation
  if ( data.GetBuffer() + data.GetPosition() != pData )
    data.Write( pData, nLength );
  else
    pDest->nLength += nLength;

  pDest->nLength += data.GetPosition() - oldPos;
  return true;
}



// BinChunkSaverImpl main methods
void BinChunkSaverImpl::DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
{
  CChunkLevel &last = chunks.back();

#ifdef _DEBUG
  NI_ASSERT( CountShortChunks( last, idChunk ) == nChunkNumber - 1, NI_STRFMT( "Invalid chunk count %d != %d", CountShortChunks( last, idChunk ), nChunkNumber - 1 ) );
#endif		
  WriteShortChunk( &last, idChunk, (const char*)pData, nSize );
}



void BinChunkSaverImpl::WriteRawData( const void *pData, int nSize )
{
#ifdef _DEBUG
  CheckUnitializedData( pData, nSize );
#endif

  CChunkLevel &res = chunks.back();
  data.Seek( res.nStart, SEEKORIGIN_BEGIN );
  res.nLength += data.Write( pData, nSize );
}



void BinChunkSaverImpl::RawData( void *pData, int nSize )
{
  WriteRawData( pData, nSize );
}



void BinChunkSaverImpl::DataChunkString( string &str )
{
  WriteRawData( str.data(), str.size() );
}



void BinChunkSaverImpl::DataChunkString( wstring &str )
{
  // FIXME: In Linux sizeof( wchar_t ) == 4, not 2
#if defined ( NV_WIN_PLATFORM )
  WriteRawData( str.data(), str.size() * 2 );
#elif defined( NV_LINUX_PLATFORM )
  const size_t dataSize = str.size() * 2;
  std::basic_string< nival::uint16_t > tmp( str.length(), 0 );
  std::copy( str.begin(), str.end(), tmp.begin() );
  WriteRawData( &tmp[ 0 ], dataSize );
#endif
}



void BinChunkSaverImpl::DataChunkString( nstl::fixed_string_base<char> &str )
{
  const nival::int16_t nSize = str.GetStorageSize();
  const nival::int16_t nLength = str.GetLength();

  NI_VERIFY( str.GetStorageSize() == int(nSize), "Invalid serialized string", return );
  NI_VERIFY( str.GetLength() == int(nLength), "Invalid serialized string", return );

  CChunkLevel &res = chunks.back();

  data.Seek( res.nStart, SEEKORIGIN_BEGIN );

  res.nLength += data.Write( &nSize, sizeof(nSize) );
  res.nLength += data.Write( &nLength, sizeof(nLength) );
  res.nLength += data.Write( str.GetData(), str.GetStorageSize() );
}



void BinChunkSaverImpl::DataChunkString( nstl::fixed_string_base<wchar_t> &str )
{
  const nival::int16_t nSize = str.GetStorageSize();
  const nival::int16_t nLength = str.GetLength();

  NI_VERIFY( str.GetStorageSize() == int(nSize), "Invalid serialized string", return );
  NI_VERIFY( str.GetLength() == int(nLength), "Invalid serialized string", return );

  CChunkLevel &res = chunks.back();

  data.Seek( res.nStart, SEEKORIGIN_BEGIN );

  res.nLength += data.Write( &nSize, sizeof(nSize) );
  res.nLength += data.Write( &nLength, sizeof(nLength) );
  res.nLength += data.Write( str.GetData(), str.GetStorageSize() );
}



void BinChunkSaverImpl::StoreObject( CObjectBase * pObject )
{
  if ( pObject )
  {
    NI_ASSERT( NObjectFactory::GetObjectTypeID( pObject ) != -1, NI_STRFMT( "trying to save unregistered object \"%s\"", typeid(*pObject).name() ) );
  }	
  if ( pObject != 0 && storedObjects.find( pObject ) == storedObjects.end() )
  {
    toStore.push_back( SObjectToStore() );
    toStore.back().type = IsValid( pObject ) ? Ptr_ValidCObj : Ptr_InvalidCObj;
    toStore.back().cobj = pObject;
    storedObjects.insert( pObject );
  }
  RawData( &pObject, 4 );
}



CObjectBase* BinChunkSaverImpl::LoadObject()
{
  NI_ALWAYS_ASSERT( "Wrong serializer" );
  return 0;
}



void BinChunkSaverImpl::StoreObjectST( BaseObjectST * object )
{
  if ( object )
    NI_ASSERT( object->PersistentClassId(), NI_STRFMT( "Trying to serialize unserializable (%s)", object->ClassName() ) );

  if ( object && storedObjects.find( object ) == storedObjects.end() )
  {
    toStore.push_back( SObjectToStore() );
    toStore.back().type = Ptr_StrongST;
    toStore.back().baseSt = object;
    storedObjects.insert( object );
  }
  RawData( &object, sizeof( object ) );
}



BaseObjectST * BinChunkSaverImpl::LoadObjectST()
{
  NI_ALWAYS_ASSERT( "Wrong serializer" );
  return 0;
}



void BinChunkSaverImpl::StoreObjectMT( BaseObjectMT * object )
{
  if ( object )
    NI_ASSERT( object->PersistentClassId(), NI_STRFMT( "Trying to serialize unserializable (%s)", object->ClassName() ) );

  if ( object && storedObjects.find( object ) == storedObjects.end() )
  {
    toStore.push_back( SObjectToStore() );
    toStore.back().type = Ptr_StrongMT;
    toStore.back().baseMt = object;
    storedObjects.insert( object );
  }
  RawData( &object, sizeof( object ) );
}



BaseObjectMT * BinChunkSaverImpl::LoadObjectMT()
{
  NI_ALWAYS_ASSERT( "Wrong serializer" );
  return 0;
}



bool BinChunkSaverImpl::StartChunk( const chunk_id idChunk, int nChunkNumber, int cType )
{
  //do not start chank of "special" type
  if (CHUNK_FORCESTR == cType) 
    return false;

  CChunkLevel &last = chunks.back();
  chunks.push_back();
#ifdef _DEBUG
  NI_ASSERT( CountShortChunks( last, idChunk ) == nChunkNumber - 1, NI_STRFMT( "Invalid chunk count %d != %d", CountShortChunks( last, idChunk ), nChunkNumber - 1 ) );
#endif
  CChunkLevel &newChunk = chunks.back();
  newChunk.idChunk = idChunk;
  newChunk.nStart = last.nStart + last.nLength + sizeof( chunk_id ) + 4;
  return true;
}



void BinChunkSaverImpl::FinishChunk()
{
  TChunksIterator it = --chunks.end();
  TChunksIterator it1 = it;
  --it1;

  WriteShortChunk( &(*it1), it->idChunk, data.GetBuffer() + it->nStart, it->nLength );
  chunks.pop_back();
  AlignDataFileSize();
}



void BinChunkSaverImpl::AlignDataFileSize()
{
  CChunkLevel &last = chunks.back();
  data.SetSize( last.nStart + last.nLength );
}



int BinChunkSaverImpl::CountChunks( const chunk_id idChunk )
{
  return CountShortChunks( chunks.back(), idChunk );
}



void BinChunkSaverImpl::Start()
{
  chunks.clear();
  obj.SetSize( 0 );
  data.SetSize( 0 );
  chunks.push_back();
}



void BinChunkSaverImpl::Finish()
{
  NI_ASSERT( chunks.size() == 1, "Invalid amount of chunks" );

  AlignDataFileSize();

  // save version
  MemoryStream versionStream;
  versionStream.Write( &version, sizeof( version ) );
  WriteShortChunkSave( pResult, 4, &versionStream );

  // Write static data
  WriteShortChunkSave( pResult, 1, &data );

  // store referenced objects
  data.SetSize( 0 );
  chunks.back().Clear();
  for ( int nObject = 1; !toStore.empty(); ++nObject )
  {
    SObjectToStore object = toStore.front();
    toStore.pop_front();

    void * pObject = 0;
    unsigned char valid = Ptr_InvalidCObj;
    int nTypeID = 0;

    if ( object.cobj )
    {
      // save object type and its server pointer
      valid = IsValid( object.cobj ) ? Ptr_ValidCObj : Ptr_InvalidCObj;
      nTypeID = NObjectFactory::GetObjectTypeID( object.cobj );
      pObject = object.cobj;
      NI_VERIFY( nTypeID != -1, NI_STRFMT( "Found unregistred object with type %s", typeid( *object.cobj ).name() ), continue );
      NI_ASSERT( object.cobj->GetObjCount() > 0 || object.cobj->GetRefCount() > 0,  NI_STRFMT("Serializing object with type %s without owner. This object will not be corectly restored from save.", object.cobj->GetObjectTypeName()));
    }
    else if ( object.baseSt )
    {
      valid = Ptr_StrongST;
      nTypeID = object.baseSt->PersistentClassId();
      pObject = object.baseSt;
    }
    else if ( object.baseMt )
    {
      valid = Ptr_StrongMT;
      nTypeID = object.baseMt->PersistentClassId();
      pObject = object.baseMt;
    }
    else
      NI_ALWAYS_ASSERT( "Wrong object to save" );

    obj.Write( &nTypeID, 4 );
    obj.Write( &pObject, 4 );
    obj.Write( &valid, 1 );

    StartChunk( (chunk_id) 1, nObject, CHUNK_DATA );
    DataChunk( 0, &pObject, 4, 1 );
    //
    if ( StartChunk( 1, 1, CHUNK_COBJECTBASE ) )
    {
      if ( object.cobj )
        object.cobj->operator & ( *this );
      else if ( object.baseSt )
        static_cast<SerializableObject *>( object.baseSt )->operator & ( *this );
      else if ( object.baseMt )
        static_cast<SerializableObject *>( object.baseMt )->operator & ( *this );
      FinishChunk();
    }
    FinishChunk();
  }
  WriteShortChunkSave( pResult, 0, &obj );
  AlignDataFileSize();
  WriteShortChunkSave( pResult, 2, &data );

  ClearBase();

  storedObjects.clear();
  toStore.clear();
}
