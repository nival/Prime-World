#include "stdafx.h"

#include "DbResourceCache.h"

namespace NDb
{

class LinksCounter : public IResourcesProcessor
{
public:
  virtual bool Call( const DBID& dbid, const NDb::DbResource* resource )
  {
    if ( !resource )
      return false;

    if ( dbid == skipDbid )
    {
      if ( skipDBIDVisited )
        return false;
      skipDBIDVisited = true;
      return true;
    }

    hash_map<DBID, int>::iterator pos = resources.find( dbid );
    if ( pos == resources.end() )
      resources.insert( make_pair<DBID, int>( dbid, 1 ) );
    else
      ++pos->second;
    return dbid.IsInlined();
  }

  virtual bool LoadResources() { return false; }

  void SkipDBID( const DBID& dbid )
  {
    skipDbid = dbid;
    skipDBIDVisited = false;
  }

  int GetLinksCount( const DBID& resource ) const
  {
    hash_map<DBID, int>::const_iterator pos = resources.find( resource );
    if ( pos == resources.end() )
      return 0;

    return pos->second;
  }

private:
  hash_map<DBID, int> resources;
  DBID skipDbid;
  bool skipDBIDVisited;
};

bool DbResourceCache::VerifyLeakedResource( DbResource* resource, int internalLinks )
{
  if ( !resource )
    return true;
  if ( resource->refCount == internalLinks )
    return true;

  char msg[512];
  NStr::Printf( msg, sizeof(msg) - 1, "%s, %d links (%d external)\n", GetFormattedDbId( resource->GetDBID() ).c_str(), resource->refCount, resource->refCount - internalLinks );
  NStr::SysLog(msg);
  return false;
}

void DbResourceCache::DumpResources()
{
  // Этот код не нужен, тк после появления циклических ссылок у нас все ресурсы "текут" и тут выводится полотно информации
  /*threading::MutexLock lock( mutex );

	if ( resources.empty() )
		return;

  LinksCounter counter;

  for ( TResources::const_iterator resource = resources.begin(); resource != resources.end(); ++resource )
  {
    if ( resource->second.mainRes )
    {
      counter.SkipDBID( resource->second.mainRes->GetDBID() );

      Traverse( resource->second.mainRes, INT_MAX, &counter );
    }
  }

  vector<DBID> erase;
  for ( TResources::const_iterator resource = resources.begin(); resource != resources.end(); ++resource )
  {
    if ( resource->second.mainRes )
    {
      if ( VerifyLeakedResource( resource->second.mainRes, counter.GetLinksCount( resource->second.mainRes->GetDBID() ) ) )
        erase.push_back( resource->second.mainRes->GetDBID() );
    }

    if ( resource->second.inlinedResources )
    {
      for ( SResourcesBunch::TInlinedMap::const_iterator inlined = resource->second.inlinedResources->begin(); inlined != resource->second.inlinedResources->end(); ++inlined )
      {
        VerifyLeakedResource( inlined->second, counter.GetLinksCount( inlined->second->GetDBID() ) );
      }
    }
  }

  for( vector<DBID>::const_iterator it = erase.begin(); it != erase.end(); ++it )
  {
    DbResource* res = GetFromCache( *it );
    if ( res )
    {
      Ptr<DbResource> ptr( res );
      res->DestroyContents();
    }
  }*/
}

} //namespace NDb
