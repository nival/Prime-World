#ifndef DBRESOURCECACHE_H_1C158D7B_8186
#define DBRESOURCECACHE_H_1C158D7B_8186

#include "Db.h"
#include "../System/Notifier.h"
#include "../System/Thread.h"


namespace NDb
{

class DbResourceCache : public CObjectBase
{
public:
  DbResourceCache( IFileSystem* fileSystem = 0);
	virtual ~DbResourceCache();
  void SetFileSystemChangesProcessor( FileSystemChangesProcessor* _changesProcessor );

  void DumpResources();

  Ptr<DbResource> Get( const DBID &dbid, IXmlSaver *_pSaver, bool fullRead );
  Ptr<DbResource> GetForce( const DBID &dbid, IXmlSaver *_pSaver, bool fullRead );
  virtual Ptr<DbResource> Create( const DBID &dbid, const char *typeName );
  virtual Ptr<DbResource> Precache( const DBID& dbid, const int depth );
  Ptr<DbResource> PrecacheForce( const DBID& _dbid, const int depth );
  static void Traverse( const DbResource *pResource, const int depth, IResourcesProcessor* proc );

	void Reset( const DBID &dbid );
  void SetNeedReload( const DBID &dbid );

  void ResetFile( const string& fileName );
  void ReleaseResourceRef( DbResource* resource );
	void Clear();
  bool EnableAssertionLoadingFiles( bool enable=true );
  bool IsAssertionLoadingFiles() const { return assertionLoadingFiles; }

  TDBResourceNotifier* GetChangeNotifier( const DBID &dbid );
  TDBResourceNotifier& NeedChangeNotifier( const DBID &dbid );

protected:
  virtual DbResource *Read( const DBID &dbid, IXmlSaver *_pSaver, const bool fullRead, const bool forceUseParamSaver );

  void SetToCache( const DBID &dbid, DbResource *resource );
  DbResource *GetFromCache( const DBID &dbid ); 

  static void SetResourceLoaded( DbResource* pResource, bool loaded );
  void SetResourceOutdated( DbResource* pResource );

  void OnFileChanged( const string& fileName );

private:
  bool VerifyLeakedResource( DbResource* resource, int internalLinks );
  void Remove( DbResource* resource );

  threading::Mutex  mutex;
  
  struct SResourcesBunch
  {
    typedef hash_map<string, DbResource*> TInlinedMap;

    SResourcesBunch() : mainRes(0), inlinedResources(0) {}
    ~SResourcesBunch()
    {
      if ( inlinedResources )
        delete inlinedResources;
    }

    TInlinedMap& NeedInlinedMap() 
    {
      if( !inlinedResources )
        inlinedResources = new TInlinedMap();
      return *inlinedResources;
    }
    DbResource* GetInlined( const string& id );
    bool RemoveResource( const string& id );
    void SetOutdated( DbResourceCache* pOwner );
    void Clear();

    DbResource* mainRes;
    TInlinedMap* inlinedResources;
  };

  typedef hash_map<string, SResourcesBunch> TResources;
  TResources resources;

  typedef hash_map<DBID,TDBResourceNotifier> TNotifiers;
  TNotifiers notifiers;

  CObj<IFileSystem> fileSystem;
  FileSystemChangesProcessor* changesProcessor;

  bool assertionLoadingFiles;

  OBJECT_BASIC_METHODS( DbResourceCache )
};

extern NDebug::DebugVar<int> db_ResourcesReadFromStream;
DbResourceCache &GetDbResourceCache();

}	// namespace NDb

#endif //#define DBRESOURCECACHE_H_1C158D7B_8186
