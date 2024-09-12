#include "stdafx.h"
#include "BinChunkLoaderImpl.h"
#include "Progress.h"
#include "Commands.h"
#include "MemoryStream.h"
#include "AddressOf.h"

static int NUM_STEPS = 100;


static unsigned long ReadLength( Stream &pStream )
{
  nival::uint32_t result = 0;
  pStream.Read( &result, 1 );
  if ( result & 1 )
    pStream.Read( ((char*)&result)+1, sizeof( result ) - 1 );

  result >>= 1;
  return static_cast< unsigned long >( result );
}



bool BinChunkLoaderImpl::ReadShortChunkSave( Stream *pFile, chunk_id &dwID, MemoryStream *pChunk )
{
  if ( pFile->GetPosition() == pFile->GetSize() )
    return false;

  pFile->Read( &dwID, sizeof( dwID ) );
  const unsigned long length = ReadLength( *pFile );

  NI_VERIFY( length < 0x00FFFFFF, "attempt to load too large chunk", return false );

  pChunk->Seek( 0,SEEKORIGIN_BEGIN );
  pChunk->SetSize( length );
  pChunk->CopyFrom( pFile, length );

  if ( pProgress )
  {
    while ( nLastStep + nStepSize < pFile->GetPosition() )
    {
      NProgressHook::Step( pProgress );
      nLastStep += nStepSize;
    }
  }

  return pFile->IsOk();
}



bool BinChunkLoaderImpl::GetShortChunkSave( Stream *pFile, chunk_id dwID, MemoryStream *pChunk, int baseSeek )
{
  chunk_id dwRid;
  pFile->Seek( baseSeek, SEEKORIGIN_BEGIN );
  while( ReadShortChunkSave( pFile, dwRid, pChunk ) )
  {
    if ( dwRid == dwID )
      return true;
  }

  pChunk->SetSize( 0 );
  return false;
}



bool BinChunkLoaderImpl::GetShortChunk( CChunkLevel *pSrc, chunk_id dwID, CChunkLevel *pResult, int nNumber )
{
  ASSERT( dwID != 0xff );

  int nPos = pSrc->nLastPos; // search from last found position
  int nCounter = nNumber;
  if ( pSrc->idLastChunk == dwID )
  {
    if ( nNumber == pSrc->nLastNumber + 1 )
      nCounter = 1;
    else
    {
      // not sequential access, fall back to linear search
      pSrc->ClearCache();
      return GetShortChunk( pSrc, dwID, pResult, nNumber );
    }
  }
  else 
  {
    if ( nNumber != 0 )
    {
      if ( pSrc->nLastPos != 0 )
      {
        pSrc->ClearCache();
        return GetShortChunk( pSrc, dwID, pResult, nNumber );
      }
    }
    else
      nCounter = 1;
  }
  while ( ReadShortChunk( *pSrc, nPos, pResult ) )
  {
    if ( pResult->idChunk == dwID )
    {
      if ( nCounter == 1 )
      {
        pSrc->idLastChunk = dwID;
        pSrc->nLastPos = nPos;
        pSrc->nLastNumber = nNumber;
        return true;
      }
      nCounter--;
    }
  }

  if ( pSrc->nLastPos == 0 )
    return false;
  // search from start
  pSrc->ClearCache();
  return GetShortChunk( pSrc, dwID, pResult, nNumber );
}



void BinChunkLoaderImpl::DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
{
  CChunkLevel &last = chunks.back();

  CChunkLevel res;
  if ( GetShortChunk( &last, idChunk, &res, nChunkNumber ) )
  {
    NI_ASSERT( res.nLength == nSize, "Invalid chunk size" );
    memcpy( pData, data.GetBuffer() + res.nStart, nSize );
  }
  else
    memset( pData, 0, nSize );
}



void BinChunkLoaderImpl::RawData( void *pData, int nSize )
{
  CChunkLevel &res = chunks.back();
  NI_ASSERT( res.nLength == nSize, "Invalid chunk size" );
  memcpy( pData, data.GetBuffer() + res.nStart, nSize );
}



void BinChunkLoaderImpl::DataChunkString( string &str )
{
  CChunkLevel &res = chunks.back();
  const char *pStr = (const char*)( data.GetBuffer() + res.nStart );
  str.assign( pStr, res.nLength );
}



void BinChunkLoaderImpl::DataChunkString( wstring &str )
{
  CChunkLevel &res = chunks.back();
#if defined ( NV_WIN_PLATFORM )
  const wchar_t *pStr = (wchar_t*) ( data.GetBuffer() + res.nStart );
  str.assign( pStr, res.nLength / 2 );
#elif defined( NV_LINUX_PLATFORM )
  nival::uint16_t * pStr = ( nival::uint16_t * ) ( data.GetBuffer() + res.nStart );
  str.resize( res.nLength / 2 );
  std::copy( pStr, pStr + res.nLength / 2, str.begin() );
#endif
}



void BinChunkLoaderImpl::DataChunkString( nstl::fixed_string_base<char> &str )
{
  nival::int16_t nSize;
  nival::int16_t nLength;

  const int chunkSize = sizeof(nSize) + sizeof(nLength) + str.GetStorageSize();

  CChunkLevel &res = chunks.back();

  NI_VERIFY( chunkSize == res.nLength, "Invalid chunk size", return );

  const unsigned char* const p = reinterpret_cast<const unsigned char*>(data.GetBuffer() + res.nStart);

  nSize = reinterpret_cast<const nival::uint16_t*>(p)[0];
  nLength = reinterpret_cast<const nival::uint16_t*>(p)[1];

  NI_VERIFY( str.GetStorageSize() == int(nSize), "Invalid serialized string", return );

  const char* const first = reinterpret_cast<const char*>(p + sizeof(nSize) + sizeof(nLength));
  const char* const last = first + nLength;

  str.Assign( first, last );

  NI_VERIFY( str.GetLength() == int(nLength), "Invalid serialized string", return );
}



void BinChunkLoaderImpl::DataChunkString( nstl::fixed_string_base<wchar_t> &str )
{
  nival::int16_t nSize;
  nival::int16_t nLength;

  const int chunkSize = sizeof(nSize) + sizeof(nLength) + str.GetStorageSize();

  CChunkLevel &res = chunks.back();

  NI_VERIFY( chunkSize == res.nLength, "Invalid chunk size", return );

  const unsigned char* const p = reinterpret_cast<const unsigned char*>(data.GetBuffer() + res.nStart);

  nSize = reinterpret_cast<const nival::uint16_t*>(p)[0];
  nLength = reinterpret_cast<const nival::uint16_t*>(p)[1];

  NI_VERIFY( str.GetStorageSize() == int(nSize), "Invalid serialized string", return );

  const wchar_t* const first = reinterpret_cast<const wchar_t*>(p + sizeof(nSize) + sizeof(nLength));
  const wchar_t* const last = first + nLength;

  str.Assign( first, last );

  NI_VERIFY( str.GetLength() == int(nLength), "Invalid serialized string", return );
}



void BinChunkLoaderImpl::StoreObject( CObjectBase *pObject )
{
  NI_ALWAYS_ASSERT( "Wrong serializer" );
}



CObjectBase* BinChunkLoaderImpl::LoadObject()
{
  void * ptrBits = 0;
  RawData( &ptrBits, 4 );
  if ( ptrBits != 0 )
  {
    TObjectsToRestore::iterator pFound = objectsToRestore.find( ptrBits );

    // here we are in problem - stored object does not exist
    // actually i think we got to throw the exception
    NI_VERIFY( pFound != objectsToRestore.end(), "Stored object does not exist", return 0 );
    NI_VERIFY( pFound->second.cobj, "Stored object is of wrong pointer type", return 0 );
    return pFound->second.cobj;
  }
  return 0;
}



void BinChunkLoaderImpl::StoreObjectST( BaseObjectST * object )
{
  NI_ALWAYS_ASSERT( "Wrong serializer" );
}



BaseObjectST * BinChunkLoaderImpl::LoadObjectST()
{
  void * ptrBits = 0;
  RawData( &ptrBits, 4 );
  if ( ptrBits )
  {
    TObjectsToRestore::iterator pFound = objectsToRestore.find( ptrBits );
    NI_VERIFY( pFound != objectsToRestore.end(), "Stored object was not properly serialized", return 0 );
    NI_ASSERT( pFound->second.baseSt, "Stored object is of wrong pointer type" );
    return pFound->second.baseSt;
  }
  return 0;
}



void BinChunkLoaderImpl::StoreObjectMT( BaseObjectMT * pObject )
{
  NI_ALWAYS_ASSERT( "Wrong serializer" );
}



BaseObjectMT * BinChunkLoaderImpl::LoadObjectMT()
{
  void * ptrBits = 0;
  RawData( &ptrBits, 4 );
  if ( ptrBits )
  {
    TObjectsToRestore::iterator pFound = objectsToRestore.find( ptrBits );
    NI_VERIFY( pFound != objectsToRestore.end(), "Stored object was not properly serialized", return 0 );
    NI_ASSERT( pFound->second.baseMt, "Stored object is of wrong pointer type" );
    return pFound->second.baseMt;
  }
  return 0;
}



bool BinChunkLoaderImpl::StartChunk( const chunk_id idChunk, int nChunkNumber, int cType )
{
  //do not start chank of "special" type
  if (CHUNK_FORCESTR == cType) 
    return false;

  CChunkLevel &last = chunks.back();
  chunks.push_back();

  bool bRes = GetShortChunk( &last, idChunk, &(chunks.back()), nChunkNumber );
  if ( !bRes )
    chunks.pop_back();
  return bRes;
}



void BinChunkLoaderImpl::FinishChunk()
{
  chunks.pop_back();
}



void BinChunkLoaderImpl::AlignDataFileSize()
{
  CChunkLevel &last = chunks.back();
  data.SetSize( last.nStart + last.nLength );
}



int BinChunkLoaderImpl::CountChunks( const chunk_id idChunk )
{
  return CountShortChunks( chunks.back(), idChunk );
}



#if defined( _DEBUG ) && !defined( FAST_DEBUG )

// checks if there are any unsaved fields
template <class T>
void PerformNivalOldschoolCheck( const T & object )
{
  static vector<const std::type_info*> ignores;
  bool bPerformCheck = true;
  const std::type_info & ti = typeid( object );
  for ( int k = 0; k < ignores.size(); ++k )
  {
    if ( ti == *ignores[k] )
      bPerformCheck = false;
  }
  if ( bPerformCheck )
  {
    bool bFound = false;
    const int nSize = sizeof( object );
    const BYTE *pObjAsArray = (const BYTE*)( nival::getaddressof( object ) );
    for ( int i = 0; i < nSize; ++i )
    {
      if ( pObjAsArray[i] == 0xcd )
      {
        bFound = true;
        break;
      }
    }
    NI_ASSERT( !bFound, "some fields are not saved" );
    if ( bFound )
      ignores.push_back( &ti );
  }
}

#else

template <class T>
void PerformNivalOldschoolCheck( const T & object ) {}

#endif


void BinChunkLoaderImpl::Start()
{
  //Stream &res = *pResult;
  const int baseSeek = pResult->GetPosition();
  //
  chunks.clear();
  obj.SetSize( 0 );
  data.SetSize( 0 );
  chunks.push_back();

  NProgressHook::SetNumSteps( pProgress, 2 );
  LOCK_RANGE( pProgress, 1 );

  NProgressHook::SetNumSteps( pProgress, NUM_STEPS );
  nStepSize = pResult->GetSize() / NUM_STEPS;
  nLastStep = 0;

  MemoryStream versionStream;
  GetShortChunkSave( pResult, 4, &versionStream, baseSeek );
  version = 0;
  if ( versionStream.GetSize() == sizeof( version ) )
  {
    versionStream.Seek( 0, SEEKORIGIN_BEGIN );
    versionStream.Read( &version, sizeof( version ) );
  }

  GetShortChunkSave( pResult, 0, &obj, baseSeek );
  obj.Seek( 0, SEEKORIGIN_BEGIN );
  GetShortChunkSave( pResult, 2, &data, baseSeek );
  data.Seek( 0, SEEKORIGIN_BEGIN );

  chunks.back().nLength = data.GetSize();
  // create all objects from obj
  while ( obj.GetPosition() < obj.GetSize() )
  {
    int nTypeID = 0;
    void *ptrBits = 0;
    TByte ptrType = Ptr_InvalidCObj;
    obj.Read( &nTypeID, 4 );
    obj.Read( &ptrBits, 4 );
    obj.Read( &ptrType, 1 );

    if ( ptrType == Ptr_InvalidCObj )
    {
      //nothing to do
    }
    else if ( ptrType == Ptr_ValidCObj )
    {
      CObjectBase * object = NObjectFactory::MakeObject( nTypeID );
      NI_VERIFY( object, NI_STRFMT( "Can't create object of type 0x%.8x", nTypeID ), continue );
      objectsToRestore[ptrBits].cobj = object;
    }
    else if ( ( ptrType == Ptr_StrongST ) || ( ptrType == Ptr_StrongMT ) )
    {
      if ( ptrBits )
      {
        SerializableBase * newObj = ni_detail::ProduceObject( (ni_detail::ClassTypeId)nTypeID );
        NI_VERIFY( newObj, NI_STRFMT( "Can't create object of type 0x%.8x", nTypeID ), continue );

        if ( ptrType == Ptr_StrongST )
        {
          BaseObjectST * object = nival_cast<BaseObjectST>( newObj );
          NI_ASSERT( object, "" );
          objectsToRestore[ptrBits].baseSt = object;
        }
        else if ( ptrType == Ptr_StrongMT )
        {
          BaseObjectMT * object = nival_cast<BaseObjectMT>( newObj );
          NI_ASSERT( object, "" );
          objectsToRestore[ptrBits].baseMt = object;
        }
      }
    }
    else
    {
      NI_ALWAYS_ASSERT( NI_STRFMT( "Inconsistent pointer serialization code %d", (int)ptrType ) );
      continue;
    }
  }
  UNLOCK_RANGE( pProgress );

  LOCK_RANGE( pProgress, 1 );
  // read information about every created object
  const int nCount = CountShortChunks( chunks.back(), (chunk_id)1 );
  NProgressHook::SetNumSteps( pProgress, nCount );
  for ( int i = 0; i < nCount; i++ )
  {
    void * ptrBits = 0;

    StartChunk( (chunk_id) 1, i + 1, CHUNK_DATA );
    DataChunk( 0, &ptrBits, 4, 1 );

    SObjectToRestore object = objectsToRestore[ptrBits];
    if ( StartChunk( 1, 1, CHUNK_COBJECTBASE ) )
    {
      if ( object.cobj )
      {
        NI_ASSERT( object.cobj->GetCRCMark() == 0, "Object should be fresh one." );
        object.cobj->operator & ( *this );
        //mark object as already read
        object.cobj->SetCrcMark( 1 );
        PerformNivalOldschoolCheck( *object.cobj );
      }
      else if ( object.baseSt )
      {
        SerializableObject * serbase = object.baseSt; //resolve ambiguity
        serbase->operator & ( *this );
        PerformNivalOldschoolCheck( *object.baseSt );
      }
      else if ( object.baseMt )
      {
        SerializableObject * serbase = object.baseMt; //resolve ambiguity
        serbase->operator & ( *this );
        PerformNivalOldschoolCheck( *object.baseMt );
      }
      FinishChunk();
    }
    FinishChunk();

    NProgressHook::Step( pProgress );
  }
  UNLOCK_RANGE( pProgress );

  // read main objects data
  chunks.back().Clear();
  GetShortChunkSave( pResult, 1, &data, baseSeek );
  chunks.back().nLength = data.GetSize();
}



void BinChunkLoaderImpl::Finish()
{
  NI_ASSERT( chunks.size() == 1, "Invalid amount of chunks" );

  ClearBase();
  objectsToRestore.clear();
}
