#include "stdafx.h"

#include "SceneObjectsPool.h"
#include "SceneObjectCreation.h"
#include "../System/InlineProfiler.h"


SINGLETON4DLL_DEF( NScene::SceneObjectsPool )

static int g_bDebugPools = 0;
REGISTER_DEV_VAR("scene_objects_pools_debug", g_bDebugPools, STORAGE_NONE);

namespace NScene
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectsPoolDeletePolicy::Delete(SceneObject* pSceneObject)
{
  //TODO SE: check we can avoid this check 
  if ( SceneObjectsPool* pool = SceneObjectsPool::Get() )
    pool->ReleaseObject(pSceneObject);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObjectsPool::SceneObjectsPool()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectsPool::DumpImpl( const ObjectsPool* p )
{
  systemLog( NLogg::LEVEL_DEBUG ) << "Scene Objects Pools Dump: id='" << p->pDesc->GetDBID().GetFileName() << "', amount = " << p->pool.size() << ", created = " <<  p->totalObjectsCreated << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObjectsPool::DumpInfo() const
{
  PoolsMap::const_iterator it;
  
  for( it = poolsMap.begin(); it != poolsMap.end(); ++it )
    DumpImpl( it->second );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneObjectsPool::~SceneObjectsPool()
{
  while( !poolsMap.empty() )
  {
    PoolsMap::iterator iPool = poolsMap.begin();
    ObjectsPool* pool = (iPool->second);
    
    if (g_bDebugPools)
      DumpImpl(pool); 
    
    while( !pool->pool.empty() )
    {
      delete pool->pool.back();
      pool->pool.pop_back();
    }
    pool->pool.clear();
    delete pool;
    poolsMap.erase(iPool);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectsPool::Reserve( IScene* pScene, NDb::Ptr<NDb::DBSceneObject> const& pDBObj, int amount, const nstl::string& nodeName )
{
  NI_PROFILE_FUNCTION

  if ( pDBObj.IsEmpty() )
    return;

  NI_VERIFY( amount > 0, "Wrong amount of instances for reserve!", return; );
  
  PushDXPoolGuard dxPool("SOBJs");
  ObjectsPool* pool = GetPool(pDBObj);
  NI_ASSERT( pool, "Invalid pool!" );

  for ( int i = 0; i < amount; ++i )
  {
    const DWORD dwDBHash = reinterpret_cast<const DWORD>( pDBObj.GetPtr() );
    AutoPtr<SceneObject> ptr = CreateSceneObject( pScene, *pDBObj.GetPtr(), nodeName );
    ptr->dwDBHash = dwDBHash;
    pool->pool.push_back( Release(ptr) );
    ++pool->totalObjectsCreated;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObjectRef SceneObjectsPool::Retrieve( IScene* pScene, NDb::Ptr<NDb::DBSceneObject> const& pDBObj, const nstl::string& nodeName )
{
  NI_PROFILE_FUNCTION

  if ( pDBObj.IsEmpty() )
    return SceneObjectRef(NULL);

  PushDXPoolGuard dxPool("SOBJs");
  ObjectsPool* pool = GetPool(pDBObj);

  NI_ASSERT( pool, "Invalid pool!" );
  if ( pool->pool.empty() )
  {
    NI_PROFILE_HEAVY_BLOCK( "CreateSceneObject" );
    const DWORD dwDBHash = reinterpret_cast<const DWORD>( pDBObj.GetPtr() );
    AutoPtr<SceneObject> ptr = CreateSceneObject( pScene, *pDBObj.GetPtr(), nodeName );
    ptr->dwDBHash = dwDBHash;
    pool->pool.push_back( Release(ptr) );
    ++pool->totalObjectsCreated;
  }

  SceneObjectRef ptr = SceneObjectRef( pool->pool.back() );
  pool->pool.pop_back();
	ptr->SetNodeName( nodeName );
  ptr->Reinit();
  return ptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObjectsPool::ObjectsPool* SceneObjectsPool::GetPool(NDb::Ptr<NDb::DBSceneObject> const& pDBObj)
{
  const DWORD dwDBHash = reinterpret_cast<const DWORD>( pDBObj.GetPtr() );
  NI_ASSERT(dwDBHash != 0xffffffff, "Bad DBID hash!");
  PoolsMap::iterator it = poolsMap.find(dwDBHash);
  return (it == poolsMap.end()) ? (poolsMap[dwDBHash] = new ObjectsPool(pDBObj) ) : (it->second);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectsPool::ReleaseObject(SceneObject* pSceneObject)
{
  NI_VERIFY( pSceneObject, "Invalid scene object!", return; );
  
  if ( pSceneObject->dwDBHash != 0xffffffff )
  {
    // clean up
    pSceneObject->Deinit();
    pSceneObject->RemoveFromScene();
    pSceneObject->ownerID = -1;
    pSceneObject->SetUpdateHook(0);
    // add to pool
    PoolsMap::iterator it = poolsMap.find(pSceneObject->dwDBHash);
    ObjectsPool* pool = (it == poolsMap.end()) ?  NULL : poolsMap.find(pSceneObject->dwDBHash)->second;
    NI_VERIFY(pool, "!!!Memory leak!!! Invalid pool id (dwDBHash) in SceneObject!", return; );
    pool->pool.push_back(pSceneObject);
  }
  else
  {
    delete pSceneObject;
  }
}

static bool DumpSceneObjectsInfo(const char *name, const vector<wstring>& params)
{
  NScene::SceneObjectsPool::Get()->DumpInfo();
  return true;
}

REGISTER_DEV_CMD( debug_dump_sceneobjects_info, DumpSceneObjectsInfo );


} //namespace NScene
