#include "stdafx.h"

#if defined( NV_WIN_PLATFORM )
#include "../System/SyncProcessorState.h"
#endif

#include "DbResourceCache.h"
#include "IDbTypesRegistrator.h"
#include "XmlSaver.h"
#include "System/StrUtils.h"
#include "System/FileSystem/FileSystemChangesProcessor.h"

#include "System/InlineProfiler.h"


namespace NDb
{

static int g_logResourceLoads = 0;
REGISTER_DEV_VAR( "log_resource_loads", g_logResourceLoads, STORAGE_NONE );
static int g_logResourceRemoves = 0;
REGISTER_DEV_VAR( "log_resource_removes", g_logResourceRemoves, STORAGE_NONE );

#ifndef _SHIPPING
static nstl::map<string, int> g_debugLoadCounters;
void DebugLogResourceLoad(const DBID & dbid)
{
  if (g_logResourceLoads)
  {
    string resourceName = NStr::StrFmt("%s (%s)", dbid.GetFileName().c_str(), dbid.GetId().c_str());
    nstl::map<string, int>::iterator itLoadCounter = g_debugLoadCounters.find(resourceName);
    if (itLoadCounter == g_debugLoadCounters.end())
    {
      g_debugLoadCounters[resourceName] = 1;
      DebugTrace("Loading %s", resourceName.c_str());
    }
    else
    {
      ++itLoadCounter->second;
      DebugTrace("Reloading: %d %s", itLoadCounter->second, resourceName.c_str());
    }
  }
}
void DebugLogResourceRemove(const DBID & dbid)
{
  if (g_logResourceRemoves)
  {
    string resourceName = NStr::StrFmt("%s (%s)", dbid.GetFileName().c_str(), dbid.GetId().c_str());
    DebugTrace("Removing: %s", resourceName.c_str());
  }
}
#define DEBUG_LOG_RESOURCE_LOAD(dbid) DebugLogResourceLoad(dbid);
#define DEBUG_LOG_RESOURCE_REMOVE(dbid) DebugLogResourceRemove(dbid);
#else
#define DEBUG_LOG_RESOURCE_LOAD(dbid)
#define DEBUG_LOG_RESOURCE_REMOVE(dbid)
#endif

NDebug::DebugVar<int> db_ResourcesReadFromStream( "Resources read", "DB" );
static NDebug::DebugVar<int> db_ResourcesGotFromCache( "Resources from cache", "DB" );
static NDebug::DebugVar<int> db_ResourcesTracked( "Resources tracked", "DB" );

static NDebug::PerformanceDebugVar db_XmlParseOnlyTime( "XmlParseOnlyTime", "DB", 0, 10, false );
static NDebug::PerformanceDebugVar db_XmlSerializeOnlyTime( "XmlSerializeOnlyTime", "DB", 0, 10, false );

static CObj<DbResourceCache> pResourceCache;


DbResourceCache &GetDbResourceCache()
{
	if ( pResourceCache == 0 )
	{
		static DbResourceCache dbResourceCache;
		return dbResourceCache;
	}
	else
	{
		return *pResourceCache;
	}
}



void SetResourceCache( DbResourceCache *pCache )
{
  if ( pResourceCache && !pCache )
  {
    pResourceCache->DumpResources();
    pResourceCache->Clear();
  }
  pResourceCache = pCache;
}



class PrecacheResourceReader : public ::IResourceReader
{
public:
  PrecacheResourceReader( DbResourceCache* _pCache, int _depth ) : pCache( _pCache ), depth( _depth ), initialDepth( _depth ) {}
  virtual NDb::Ptr<NDb::DbResource> Read( const NDb::DBID& dbid, IXmlSaver& saver )
  {
    Ptr<DbResource> pRes;
    if ( dbid.IsInlined() )
    {
      pRes = pCache->Get( dbid, &saver, true );
    }
    else
    {
      --depth;
      pRes = pCache->Get( dbid, &saver, depth > 0 );
      ++depth;
    }
    return pRes;
  }
  virtual void Write( const DBID& dbid, const DbResource* pResource, IXmlSaver& saver )
  {
    saver.SetHrefIdAttributes( pResource->GetDBID().GetFileName(), pResource->GetDBID().GetId() );
    if ( pResource->GetDBID().IsInlined() )
    {
      saver.StartChunk( pResource->GetObjectTypeName(), 0 );
      saver.AddPolymorphicBase( 0, const_cast<DbResource *>( pResource ) );
      saver.FinishChunk();
    }
  }
  virtual bool NeedPrecacheTexts() { return depth > 0; }
  virtual bool LoadResources() { return true; }

private:
  DbResourceCache* pCache;
  int depth;
  int initialDepth;
};


class PrecacheResourceReaderForce : public ::IResourceReader
{
public:
  PrecacheResourceReaderForce( DbResourceCache* _pCache, int _depth ) : pCache( _pCache ), depth( _depth ), initialDepth( _depth ) {}
  virtual NDb::Ptr<NDb::DbResource> Read( const NDb::DBID& dbid, IXmlSaver& saver )
  {
    Ptr<DbResource> pRes;

    --depth;
    pRes = pCache->GetForce( dbid, &saver, depth > 0 );
    ++depth;
    
    return pRes;
  }
  virtual void Write( const DBID& dbid, const DbResource* pResource, IXmlSaver& saver )
  {
    saver.SetHrefIdAttributes( pResource->GetDBID().GetFileName(), pResource->GetDBID().GetId() );
    if ( pResource->GetDBID().IsInlined() )
    {
      saver.StartChunk( pResource->GetObjectTypeName(), 0 );
      saver.AddPolymorphicBase( 0, const_cast<DbResource *>( pResource ) );
      saver.FinishChunk();
    }
  }
  virtual bool NeedPrecacheTexts() { return depth > 0; }
  virtual bool LoadResources() { return true; }

private:
  DbResourceCache* pCache;
  int depth;
  int initialDepth;
};



DbResourceCache::DbResourceCache( IFileSystem* _fileSystem )
: fileSystem( _fileSystem )
, changesProcessor( 0 )
, assertionLoadingFiles( false )
{

}

void DbResourceCache::SetFileSystemChangesProcessor( FileSystemChangesProcessor* _changesProcessor )
{
  threading::MutexLock lock( mutex );

  if( changesProcessor )
  {
    FileWatchMethodFunctor<NDb::DbResourceCache> temp( this, &NDb::DbResourceCache::OnFileChanged );
    changesProcessor->UnregisterFileWatchByExtension( ".xdb", &temp );
  }
  changesProcessor = _changesProcessor;
  if( changesProcessor )
  {
    changesProcessor->RegisterFileWatchByExtension( ".xdb", new FileWatchMethodFunctor<NDb::DbResourceCache>( this, &NDb::DbResourceCache::OnFileChanged ) );
  }
}



void DbResourceCache::OnFileChanged( const string& fileName )
{
  systemLog( NLogg::LEVEL_DEBUG ) << "Resource changed: " << fileName << " , reloading" << endl;
  ResetFile( fileName );
}



DbResourceCache::~DbResourceCache()
{
  DumpResources();
	Clear();
}



Ptr<DbResource> DbResourceCache::Create( const DBID &dbid, const char *typeName )
{
  threading::MutexLock lock( mutex );

  DbResource *pResult = GetFromCache( dbid );
  if ( !pResult )
    return pResult;

	pResult = GetDbTypesRegistrator().Create( dbid, typeName, true );
	if ( pResult )
		SetToCache( dbid, pResult );

	return pResult;
}



void DbResourceCache::Reset( const DBID &dbid )
{
  threading::MutexLock lock( mutex );

  TResources::iterator it = resources.find( dbid.GetFileName() );

  if ( it != resources.end() )
    it->second.SetOutdated( this );
}



void DbResourceCache::ReleaseResourceRef( DbResource* resource )
{
  NI_ASSERT( resource, "" );
  NI_ASSERT( resource->refCount > 0, "" );

  threading::MutexLock lock( mutex );

  LONG current = nival::interlocked_decrement( resource->refCount );
  if ( !current )
	{
		GetDbResourceCache().Remove( resource );
		resource->DeleteThis();
	}
}



void DbResourceCache::Remove( DbResource* resource )
{
  if ( !resource )
    return;

  if( resource->outdated )
  {
    DbResource *cachedResource = GetFromCache( resource->dbid );
    if ( cachedResource != resource )
      return;
  }

  {
    TResources::iterator it = resources.find( resource->dbid.GetFileName() );
    if ( it != resources.end() )
    {
      DEBUG_LOG_RESOURCE_REMOVE(resource->dbid);
      if ( it->second.RemoveResource( resource->dbid.GetId() ) )
        resources.erase( it );
    }
  }

  {
    TNotifiers::iterator it = notifiers.find( resource->GetDBID() );
    if( it != notifiers.end() )
    {
      notifiers.erase( it );
      db_ResourcesTracked.DecValue( 1 );
    }
  }
}



void DbResourceCache::ResetFile( const string& _fileName )
{
  threading::MutexLock lock( mutex );

  string fileName = _fileName;
  FixFileNameForDBID( &fileName );
  
  TResources::iterator it = resources.find( fileName );
  if ( it == resources.end() )
    return;

  it->second.SetOutdated( this );
}



void DbResourceCache::SetNeedReload( const DBID &dbid )
{
  threading::MutexLock lock( mutex );

  DbResource *pResource = GetFromCache( dbid );
  if ( !pResource )
    return;

  pResource->loaded = false;
  pResource->AddRef();

  TDBResourceNotifier* pNotifier = GetChangeNotifier( dbid );
  if ( pNotifier )
  {
    pNotifier->Notify( dbid );
  }

  pResource->ReleaseRef();
}



void DbResourceCache::Clear()
{
  threading::MutexLock lock( mutex );

  //for ( TResources::iterator it = resources.begin(); it != resources.end(); ++it )
  //  it->second.Clear();
	resources.clear();
}

bool DbResourceCache::EnableAssertionLoadingFiles( bool enable/*=true */ )
{
  bool oldValue = assertionLoadingFiles;

#ifndef _SHIPPING
  assertionLoadingFiles = enable;
#else
  (void)enable;
#endif

  return oldValue;
}

Ptr<DbResource> DbResourceCache::Get( const DBID &dbid, IXmlSaver *_pSaver, bool fullRead )
{
  NI_PROFILE_FUNCTION_MEM

  threading::MutexLock lock( mutex );

  DbResource* resource = GetFromCache( dbid );

  NI_ASSERT( 
    !assertionLoadingFiles || ( resource != 0 && !resource->NeedReload() ), 
    NStr::StrFmt( "Not recommended loading resource \"%s\" after game starting", dbid.GetFileName().c_str() ) 
  );

  if ( resource )
  {
    if ( !fullRead || !resource->NeedReload() )
    {
      db_ResourcesGotFromCache.AddValue( 1 );
      return resource;
    }
  }

  return Read( dbid, _pSaver, fullRead, false );
}

Ptr<DbResource> DbResourceCache::GetForce( const DBID &dbid, IXmlSaver *_pSaver, bool fullRead )
{
  NI_PROFILE_FUNCTION_MEM

    threading::MutexLock lock( mutex );

  DbResource* resource = GetFromCache( dbid );

  if ( resource )
  {
    if( fullRead || resource->NeedReload() )
      return Read( dbid, _pSaver, fullRead, false );

    db_ResourcesGotFromCache.AddValue( 1 );
    return resource;
  }

  return Read( dbid, _pSaver, fullRead, false );
}


void DbResourceCache::SetResourceLoaded( DbResource* pResource, bool loaded )
{
  pResource->loaded = loaded;
}



void DbResourceCache::SetResourceOutdated( DbResource* pResource )
{
  pResource->outdated = true;
  pResource->AddRef();

  TDBResourceNotifier* pNotifier = GetChangeNotifier( pResource->GetDBID() );
  if ( pNotifier )
  {
    pNotifier->Notify( pResource->GetDBID() );
  }

  pResource->ReleaseRef();
}



void DbResourceCache::SetToCache( const DBID &dbid, DbResource *resource )
{
  SResourcesBunch& bunch = resources[ dbid.GetFileName() ];
  if ( !dbid.IsInlined() )
  {
    NI_ASSERT(!bunch.mainRes || bunch.mainRes->outdated || bunch.mainRes == resource, "Reassigning main resource pointer!");
    bunch.mainRes = resource;
  }
  else
  {
    SResourcesBunch::TInlinedMap::iterator it = bunch.NeedInlinedMap().find(dbid.GetId());
    if (it != bunch.NeedInlinedMap().end())
    {
      NI_ASSERT(it->second == 0 || it->second->outdated || it->second == resource, "Reassigning inlined resource pointer!");
      it->second = resource;
    }
    else
    {
      bunch.NeedInlinedMap()[ dbid.GetId() ] = resource;
    }
  }
}



DbResource * DbResourceCache::GetFromCache( const DBID &dbid )
{
  NI_PROFILE_FUNCTION

  TResources::iterator it = resources.find( dbid.GetFileName() );

  if ( it == resources.end() )
    return 0;

  if ( !dbid.IsInlined() )
  {
    return it->second.mainRes;
  }
  else
    return it->second.GetInlined( dbid.GetId() );
}



TDBResourceNotifier* DbResourceCache::GetChangeNotifier( const DBID &dbid )
{
  threading::MutexLock lock( mutex );

  TNotifiers::iterator it = notifiers.find( dbid );
  if ( it == notifiers.end() )
    return 0;
  return &(it->second);
}



TDBResourceNotifier& DbResourceCache::NeedChangeNotifier( const DBID &dbid )
{
  threading::MutexLock lock( mutex );

  TNotifiers::iterator it = notifiers.find( dbid );
  if ( it == notifiers.end() )
  {
    db_ResourcesTracked.AddValue( 1 );
    return  notifiers.insert( TNotifiers::value_type( dbid, TDBResourceNotifier() ) ).first->second;
  }

  return it->second;
}



DbResource* DbResourceCache::SResourcesBunch::GetInlined( const string& id )
{
  if ( !inlinedResources )
    return 0;

  SResourcesBunch::TInlinedMap::iterator it = inlinedResources->find( id );
  if ( it == inlinedResources->end() )
    return 0;

  return it->second;
}



void DbResourceCache::SResourcesBunch::SetOutdated( DbResourceCache* pOwner )
{
  if ( mainRes )
    pOwner->SetResourceOutdated( mainRes );

  if ( inlinedResources )
  {
    for ( SResourcesBunch::TInlinedMap::iterator it = inlinedResources->begin(); it != inlinedResources->end() ; ++it )
    {
      pOwner->SetResourceOutdated( it->second );
    }
  }
}



bool DbResourceCache::SResourcesBunch::RemoveResource( const string& id )
{
  if ( id.empty() )
    mainRes = 0;
  else if ( inlinedResources )
  {
    SResourcesBunch::TInlinedMap::iterator it = inlinedResources->find( id );
    if ( it != inlinedResources->end() )
      inlinedResources->erase( it );
  }

  return  !mainRes && ( !inlinedResources || inlinedResources->empty() );
}


void DbResourceCache::SResourcesBunch::Clear()
{
  if ( mainRes )
  {
    delete mainRes;
    mainRes = 0;
  }

  if ( inlinedResources )
  {
    for ( SResourcesBunch::TInlinedMap::iterator it = inlinedResources->begin(); it != inlinedResources->end(); ++it )
      delete it->second;
    delete inlinedResources;
    inlinedResources = 0;
  }
}


DbResource *DbResourceCache::Read( const DBID &dbid, IXmlSaver *_pSaver, const bool fullRead, const bool forceUseParamSaver )
{
  NI_PROFILE_FUNCTION

  DbResource *pResultFromCache = GetFromCache( dbid );
  DbResource *pResult = pResultFromCache;
  if ( pResult )
  {
    if ( pResult->outdated )
      pResult = 0;
  }

  PrecacheResourceReader resourceHandler( this, 1 );

  CObj<IXmlSaver> pSaver = _pSaver;

  if ( !IsValid( pSaver ) && dbid.IsInlined() )
  {
    //NI_ALWAYS_ASSERT( NI_STRFMT( "Cannot get inlined resource \"%s\" without saver", GetFormattedDbId( dbid ).c_str() ) );
    PrecacheForce(dbid, 20);
    return GetFromCache( dbid );
  }

  if ( !dbid.IsInlined() && !forceUseParamSaver )
  {
    Stream *pStream = 0;
    {
      pStream = fileSystem->OpenFile( dbid.GetFileName(), FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      NI_VERIFY( pStream && pStream->IsOk(), NI_STRFMT( "DbResourceCache::Get: Cannot open file \"%s\"", dbid.GetFileName().c_str() ), return 0 );
    }

    db_XmlParseOnlyTime.Start( false );
    pSaver = CreateXmlSaver( pStream, true, _pSaver ? _pSaver->GetResourceReader() : &resourceHandler );
    pSaver->SetSourceFileName( dbid.GetFileName() );
  }
  else
    db_XmlParseOnlyTime.Start( false );

  //NI_VERIFY( IsValid( pSaver ), NI_STRFMT( "Cannot create saver for file \"%s\"", dbid.GetFileName().c_str() ), return 0 );

  const string typeName = pSaver->GetTypeOfNextElement();
  if( !pResult )
  {
    NDb::DbTypesRegistrator& registrator = GetDbTypesRegistrator();
    pResult = registrator.Create( dbid, typeName.c_str(), fullRead );
  }
  else if ( fullRead )
  {
    pResult->loaded = true;
  }

  db_XmlParseOnlyTime.Stop();
  if ( !pResult )
  {
    return 0;
  }

  pResult->outdated = false;

  if (pResult != pResultFromCache)
  {
    SetToCache( dbid, pResult );
  }

  if ( fullRead )
  {
    db_ResourcesReadFromStream.AddValue( 1 );

    DEBUG_LOG_RESOURCE_LOAD(dbid);

    const bool inlined = dbid.IsInlined();
    string wasId;
    if ( inlined )
    {
      wasId = pSaver->GetSourceId();
      pSaver->SetSourceId( dbid.GetId() );
    }
    db_XmlSerializeOnlyTime.Start( false );
#if defined( NV_WIN_PLATFORM )
    SyncProcessorState();
#endif
    pSaver->StartChunk( typeName.c_str(), 0 );
    pSaver->AddPolymorphicBase( 0, pResult );
    pSaver->FinishChunk();
    db_XmlSerializeOnlyTime.Stop();

    if ( inlined )
    {
      pSaver->SetSourceId( wasId );
    }

  }

  return pResult;
}



Ptr<DbResource> DbResourceCache::Precache( const DBID& dbid, const int depth )
{
  threading::MutexLock lock( mutex );

  NI_PROFILE_FUNCTION

  NI_VERIFY( !dbid.IsInlined(), NI_STRFMT( "Cannot precache inlined resource \"%s:%s\"", dbid.GetFileName().c_str(), dbid.GetId().c_str() ), return 0 );

  CObj<Stream> pStream = fileSystem->OpenFile( dbid.GetFileName(), FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_VERIFY( pStream && pStream->IsOk(), NI_STRFMT( "DbResourceCache::Precache: Cannot open file \"%s\"", dbid.GetFileName().c_str() ), return 0 );

  PrecacheResourceReader resReader( this, depth );

  CObj<IXmlSaver> pSaver = CreateXmlSaver( pStream, true, &resReader );
  pSaver->SetSourceFileName( dbid.GetFileName() );
  const string typeName = pSaver->GetTypeOfNextElement();
  
  DbResource* pResult = GetFromCache( dbid );
  if ( !pResult )
  {
    pResult = GetDbTypesRegistrator().Create( dbid, typeName.c_str(), true );
  }

  if ( pResult )
  {
    DEBUG_LOG_RESOURCE_LOAD(dbid);

#if defined( NV_WIN_PLATFORM )
    SyncProcessorState();
#endif
    pSaver->StartChunk( typeName.c_str(), 0 );
    pSaver->AddPolymorphicBase( 0, pResult );
    pSaver->FinishChunk();

    SetToCache( dbid, pResult );
  }

  return pResult;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция  кеширует ресурс с заданной глубиной принудительно
// Глубина считается и для inlined ресурсов тоже.
/////////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<DbResource> DbResourceCache::PrecacheForce( const DBID& _dbid, const int depth )
{
  threading::MutexLock lock( mutex );

  const DBID dbid = DBID( _dbid.GetFileName() );

  CObj<Stream> pStream = fileSystem->OpenFile( dbid.GetFileName(), FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  NI_VERIFY( pStream && pStream->IsOk(), NI_STRFMT( "DbResourceCache::Precache: Cannot open file \"%s\"", dbid.GetFileName().c_str() ), return 0 );

  PrecacheResourceReaderForce resReader( this, depth );

  CObj<IXmlSaver> pSaver = CreateXmlSaver( pStream, true, &resReader );
  pSaver->SetSourceFileName( dbid.GetFileName() );
  const string typeName = pSaver->GetTypeOfNextElement();
  
  DbResource* pResult = GetFromCache( dbid );
  if ( !pResult )
  {
    pResult = GetDbTypesRegistrator().Create( dbid, typeName.c_str(), true );
  }

  if ( pResult )
  {
    DEBUG_LOG_RESOURCE_LOAD(dbid);

#if defined( NV_WIN_PLATFORM )
    SyncProcessorState();
#endif
    pSaver->StartChunk( typeName.c_str(), 0 );
    pSaver->AddPolymorphicBase( 0, pResult );
    pSaver->FinishChunk();

    SetToCache( dbid, pResult );
  }

  return pResult;
}



class DummyXMLWriter : public IXmlSaver
{
  OBJECT_BASIC_METHODS( DummyXMLWriter )
private:
  DummyXMLWriter() : pResourceHandler(0) {}
  IResourceReader* pResourceHandler;
  string emptyString;
  bool precacheTexts;

  virtual bool DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber ) { return true; }
  virtual bool DataChunk( const chunk_id idChunk, int *pnData, int nChunkNumber ) { return true; }
  virtual bool DataChunk( const chunk_id idChunk, float *pfData, int nChunkNumber ) { return true; }
  virtual bool DataChunk( const chunk_id idChunk, bool *pData, int nChunkNumber ) { return true; }
#ifdef WIN32
  virtual bool DataChunk( const chunk_id idChunk, GUID *pgData, int nChunkNumber ) { return true; }
#endif
  virtual bool DataChunkFilePath( NFile::CFilePath *pFilePath ) { return true; }
  virtual bool DataChunkTextRef( CTextRef *pTextRef )
  {
    if ( precacheTexts )
    {
    }
    return true;
  }
  virtual bool DataChunkString( string &data ) { return true; }
  virtual bool DataChunkString( wstring &data ) { return true; }
  virtual EReadResult GetCurrentReadResult() const { return IXmlSaver::RR_ADD; }
public:

  virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber ) { return true; }
  virtual int CountChunks() { return 0; }
  virtual void FinishChunk() {}

  virtual void SetSourceFileName( const string & fileName ) {}
  virtual const string & GetSourceFileName() const { return emptyString; }
  virtual void SetSourceId( const string & id ) {}
  virtual const string & GetSourceId() const { return emptyString; }
  virtual void SetHrefIdAttributes( const string &href, const string &id ){}
  virtual const string GetTypeOfNextElement() const { return string(); }

  virtual const bool IsComplexNextElement() const { return false; }

  virtual const bool HasHRefAttr() const { return false; }
  virtual const string GetHRefAttrValue() const { return string(); }
  virtual const bool HasIdAttr() const { return false; }
  virtual const string GetIdAttrValue() const { return string(); }
  virtual const bool HasAnimatedAttr() const { return false; }
  virtual const bool HasParentAttr() const { return false; }
  virtual const string GetParentAttrValue() const { return string(); }
  virtual const string GetStateNameAttrValue() const { return string(); }

  virtual bool IsReading() const { return false; }
  DummyXMLWriter( IResourceReader* _pResourceHandler ) : pResourceHandler( _pResourceHandler ) {}
  virtual IResourceReader* GetResourceReader() const { return pResourceHandler; }
};



class TraverseResourceReader : public ::IResourceReader
{
public:
  TraverseResourceReader( int _depth, IResourcesProcessor* _proc ) : depth( _depth ), proc( _proc ) {}
  virtual NDb::Ptr<NDb::DbResource> Read( const NDb::DBID& dbid, IXmlSaver& saver ) { NI_ALWAYS_ASSERT( "Should not be called" ); return 0; }
  virtual void Write( const DBID& dbid, const NDb::DbResource* pResource, IXmlSaver& saver )
  {
    if ( !pResource )
      return;

    if ( !proc->Call( dbid, pResource ) )
      return;

    --depth;
    if ( depth > 0 )
    {
      //CObj<DummyXMLWriter> writer = new DummyXMLWriter( this );
      saver.StartChunk( pResource->GetObjectTypeName(), 0 );
      saver.AddPolymorphicBase( 0, (NDb::DbResource*)pResource );
      saver.FinishChunk();
    }
    else
    {
      NI_ALWAYS_ASSERT( "Not enough depth to precache resources");
    }
    ++depth;
  }
  virtual bool NeedPrecacheTexts() { return false; }
  virtual bool LoadResources() { return proc->LoadResources(); }

private:
  IResourcesProcessor* proc;
  int depth;
};

void DbResourceCache::Traverse( const DbResource *pResource, const int depth, IResourcesProcessor* proc )
{
  TraverseResourceReader traverser( depth, proc );
  CObj<DummyXMLWriter> writer = new DummyXMLWriter( &traverser );

  if ( !proc->Call( pResource->dbid, pResource ) )
    return;

  writer->AddPolymorphicBase( 0, (NDb::DbResource*)pResource );
}



DbResourceCache* CreateGameResourceCache( IFileSystem* fileSystem, FileSystemChangesProcessor* changesProcessor )
{
  DbResourceCache* cache = new DbResourceCache( fileSystem );
  cache->SetFileSystemChangesProcessor( changesProcessor );
  return cache;
}

} //namespace NDb
