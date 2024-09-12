#include "stdafx.h"
#include "WorldChecker.h"
#include "../PF_Core/WorldObject.h"
#include "PFWorld.h"
#include "PointersHolder.h"
#include "zlib.h"

#include "System/InlineProfiler.h"

static int debugWcOn = 0;
REGISTER_DEV_VAR( "debug_wc_on", debugWcOn, STORAGE_NONE );

#ifndef _SHIPPING
#define DEBUG_WC( ... ) if ( debugWcOn ) DebugTrace( __VA_ARGS__ );
#else
#define DEBUG_WC( ... )
#endif

namespace
{
static int g_compressWorldData = 1;
static const int bufferSize = 1<<24; // 16Mb buffer
}


namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::Save() const
{
  NI_VERIFY( world, "Invalid world!", return );

 if ( saveCompressThread )
   saveCompressThread = 0;

  StrongMT<NWorld::SaveCompressThreadJob> saveCompressJob = new NWorld::SaveCompressThreadJob( true );

  SaveWithoutCompression( *saveCompressJob->GetSourceStream() );

  saveCompressThread = new threading::JobThread( saveCompressJob, "SaveCompressing" );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::Save( Stream & worldData ) const
{
  NI_PROFILE_FUNCTION

  MemoryStream worldDataTemp;

  Stream & worldDataDest = (g_compressWorldData)?(worldDataTemp):(worldData);

  worldDataDest.SetSize( bufferSize );

  SaveIds( worldDataDest );
  SaveObjects( worldDataDest );
  SaveWorld( worldDataDest );

  if (g_compressWorldData)
  {
    Compress( worldData, worldDataTemp );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::SaveWithoutCompression( Stream & worldData ) const
{
  worldData.SetSize( bufferSize );

  SaveIds( worldData );
  SaveObjects( worldData );
  SaveWorld( worldData );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::SaveWorldObject( int id, PF_Core::WorldObjectBase* object, IBinSaver * _saver  ) const
{
  int typeID = NObjectFactory::GetObjectTypeID( object );

  NI_ASSERT_TRACE( object->GetObjectId() != -1, NStr::StrFmt("Bad objectID! (tn=%s)", object->GetObjectTypeName() ) );
  NI_VERIFY_TRACE( typeID != -1, NStr::StrFmt("Bad typeID! (oid=%d tn=%s)", id, object->GetObjectTypeName() ), return; );

  _saver->Add( 0, &typeID );
  object->operator &( *_saver );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::SaveWorld( Stream & st ) const
{
  NI_PROFILE_FUNCTION

  CObj<IBinSaver> pSaver = CreateChunklessSaver( &st, world, false );

  world->operator &( *pSaver );

  pSaver = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::SaveIds( Stream & st ) const
{
  NI_PROFILE_FUNCTION

  nstl::vector<int> ids;
  nstl::vector<int> typeIDs;

  CObj<IBinSaver> pSaver = CreateChunklessSaver( &st, world, false );

  for ( PF_Core::World::TObjects::iterator it = world->objects.begin(); 
          it != world->objects.end(); ++it )
  {
    ids.push_back( it->first );
    int typeID = NObjectFactory::GetObjectTypeID( it->second );
    typeIDs.push_back( typeID );
    DEBUG_WC("SObj: oid=%d tid=%d tn=%s", it->first, typeID, it->second->GetObjectTypeName());
  }

  for ( PF_Core::World::TWeakObjects::iterator it = world->weakObjects.begin(); 
          it != world->weakObjects.end(); ++it )
  {
    ids.push_back( it->first );

    int typeID = -1;

    if (IsValid(it->second))
      typeID = NObjectFactory::GetObjectTypeID( it->second );
    else
      NI_ALWAYS_ASSERT_TRACE(NStr::StrFmt("Invalid weak object pointer! (oid=%d)", it->first));

    typeIDs.push_back( typeID );
    DEBUG_WC("WObj: oid=%d tid=%d tn=%s", it->first, typeID, it->second->GetObjectTypeName());
  }

  pSaver->Add( 2, &ids );
  pSaver->Add( 3, &typeIDs );

  pSaver = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::SaveObjects( Stream & st ) const
{
  NI_PROFILE_FUNCTION

  CObj<IBinSaver> pSaver = CreateChunklessSaver( &st, world, false );

  for ( PF_Core::World::TObjects::iterator it = world->objects.begin(), itEnd = world->objects.end(); 
          it != itEnd; ++it )
  {
    SaveWorldObject( it->first, it->second, pSaver );
  }

  for ( PF_Core::World::TWeakObjects::iterator it = world->weakObjects.begin(), itEnd = world->weakObjects.end(); 
          it != itEnd; ++it )
  {
    if (IsValid(it->second) )
    {
      SaveWorldObject( it->first, it->second, pSaver );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::Load()
{
  MemoryStream worldData( bufferSize );

  LoadFromFile( worldData );
  Load( worldData );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::Load( Stream & worldData )
{
  NI_VERIFY( world, "Invalid world!", return );

  MemoryStream worldDataUncompressed;

  if (g_compressWorldData)
  {
    worldDataUncompressed.SetSize( bufferSize );
    Uncompress( worldDataUncompressed, worldData );
  }
  
  Stream & worldDataSrc = (g_compressWorldData)?(worldDataUncompressed):(worldData);

  worldDataSrc.Seek(0, SEEKORIGIN_BEGIN);

  LoadIds( worldDataSrc );
  LoadWorld( worldDataSrc );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::LoadWorld( Stream & st )
{
  CObj<IBinSaver> pLoader = CreateChunklessSaver( &st, pd, true );

  world->SetObjectRegistrationLocked(true);
  world->operator &( *pLoader );
  world->SetObjectRegistrationLocked(false);

  pLoader = 0;
  pd = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::LoadIds( Stream & st )
{
  nstl::vector<int> ids;
  nstl::vector<int> typeIDs;

  CObj<IBinSaver> pLoader = CreateChunklessSaver( &st, world, true );
  pLoader->Add( 2, &ids );
  pLoader->Add( 3, &typeIDs );
  pLoader = 0;

  pd = new PointersHolder( world, ids.size() );
  for ( int i = 0; i < ids.size(); i++ )
  {
    int id = ids[i];
    int typeID = typeIDs[i];
    DEBUG_WC("Obj: oid=%d tid=%d", ids[i], typeIDs[i]);
    NI_VERIFY_TRACE(typeID != -1, NStr::StrFmt("Bad type ID! (tid=%d)", typeID), continue);

    if ( PF_Core::WorldObjectBase* obj = world->GetObjectById(id) )
      pd->Add( obj, id );
    else
      pd->Add( NObjectFactory::MakeObject( typeID ), id );
  }

  for ( int i = 0; i < ids.size(); i++ )
  {
    int id = ids[i];
    if (typeIDs[i] != -1)
    {
      LoadWorldObject( id, st);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObjectBase* WorldChecker::LoadWorldObject( int id, Stream & st )
{
  CObj<IBinSaver> pLoader = CreateChunklessSaver( &st, pd, true );

  CObjectBase* obj = pd->GetObject( id );
  NI_VERIFY_TRACE( obj, NStr::StrFmt("Object not found! (oid=%d)", id), pLoader = 0; return 0; )

  int typeID = 0;
  pLoader->Add( 0, &typeID );
  int objTypeID = NObjectFactory::GetObjectTypeID(obj);
  NI_ASSERT_TRACE( typeID == objTypeID, NStr::StrFmt("Bad typeID! (oid=%d tid=%d objTid=%d)", id, typeID, objTypeID));

  DEBUG_WC("Obj: oid=%d tn=%s", id, obj->GetObjectTypeName());

  obj->operator &( *pLoader );

  pLoader = 0;

  return obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::Compress( Stream & stDst, const Stream & stSrc ) const
{
  NI_PROFILE_FUNCTION

  stDst.SetSize(compressBound(stSrc.GetPosition()));
  uLongf compressedSize = stDst.GetSize();

  int error = compress2( (Bytef*)stDst.GetBuffer(), &compressedSize, 
    (Bytef*)stSrc.GetBuffer(), stSrc.GetPosition(), Z_BEST_COMPRESSION );

  NI_VERIFY_TRACE( error == Z_OK, "Failed to compress world data!", return );
  NI_VERIFY_TRACE( compressedSize > 0, "Wrong compresseed world data size!", return );

  stDst.Seek( compressedSize, SEEKORIGIN_BEGIN );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::Uncompress( Stream & stDst, const Stream & stSrc ) const
{
  uLongf uncompressedSize = stDst.GetSize();

  int error = uncompress( (Bytef*)stDst.GetBuffer(), &uncompressedSize,
    (Bytef*)stSrc.GetBuffer(), stSrc.GetPosition() );

  NI_VERIFY_TRACE( error == Z_OK, "Failed to uncompress world data!", return );
  NI_VERIFY_TRACE( uncompressedSize > 0, "Wrong uncompresseed world data size!", return );

  stDst.Seek( uncompressedSize, SEEKORIGIN_BEGIN );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::SaveToFile( Stream & st ) const
{
  NI_PROFILE_FUNCTION

  FILE* f;
  fopen_s( &f, "world.bin", "wb" );
  fwrite( st.GetBuffer() , 1 , st.GetPosition() , f );
  fclose( f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WorldChecker::LoadFromFile( Stream & st )
{
  st.Seek(0, SEEKORIGIN_BEGIN);

  FILE* f;
  fopen_s( &f, "world.bin", "rb" );
  int readSize = fread( (void*)st.GetBuffer(), 1, st.GetSize(), f );
  fclose(f);

  st.Seek(readSize, SEEKORIGIN_BEGIN);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SaveCompressThreadJob::SaveCompressThreadJob( bool _saveToFile ) :
  saveToFile( _saveToFile )
{
  sourceStream = new MemoryStream();
  destStream = new MemoryStream();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveCompressThreadJob::Work( volatile bool & isRunning )
{
  NI_PROFILE_THREAD;

  destStream->SetSize(compressBound(sourceStream->GetPosition()));
  uLongf compressedSize = destStream->GetSize();

  int error = compress2( (Bytef*)destStream->GetBuffer(), &compressedSize, 
    (Bytef*)sourceStream->GetBuffer(), sourceStream->GetPosition(), Z_BEST_COMPRESSION );

  NI_VERIFY_TRACE( error == Z_OK, "Failed to compress world data!", return );
  NI_VERIFY_TRACE( compressedSize > 0, "Wrong compresseed world data size!", return );

  destStream->Seek( compressedSize, SEEKORIGIN_BEGIN );

  if ( saveToFile )
  {
    FILE* f;
    fopen_s( &f, "world.bin", "wb" );
    fwrite( destStream->GetBuffer() , 1 , destStream->GetPosition() , f );
    fclose( f );
  }
}


} // namespace NWorld

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR( "compress_world_data", g_compressWorldData, STORAGE_NONE )
