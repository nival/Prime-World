#pragma once

#include "../System/Singleton4DLL.h"

namespace NScene
{

class SceneObject;
_interface IScene;

//////////////////////////////////////////////////////////////////////////
struct SceneObjectsPoolDeletePolicy { static void Delete(SceneObject* pSceneObject); };
typedef AutoPtr<SceneObject, SceneObjectsPoolDeletePolicy> SceneObjectRef;

class SceneObjectsPool : public Singleton4DLL<SceneObjectsPool>
{
public:
	SceneObjectsPool();
	~SceneObjectsPool();

	void Reserve( IScene* pScene, NDb::Ptr<NDb::DBSceneObject> const& pDBObj, int amount, const nstl::string& nodeName );
	SceneObjectRef Retrieve( IScene* pScene, NDb::Ptr<NDb::DBSceneObject> const& pDBObj, const nstl::string& nodeName );
	
	void DumpInfo() const;

private:
	struct ObjectsPool
  {
    ObjectsPool(NDb::Ptr<NDb::DBSceneObject> const& pDesc) : pDesc(pDesc), totalObjectsCreated(0) {}
    list<SceneObject*>          pool;
    NDb::Ptr<NDb::DBSceneObject>  pDesc;
    int totalObjectsCreated;
  };

	typedef nstl::hash_map<DWORD, ObjectsPool*> PoolsMap;
	PoolsMap poolsMap;

	friend struct SceneObjectsPoolDeletePolicy;
	void ReleaseObject(SceneObject* pSceneObject);
	ObjectsPool* GetPool(NDb::Ptr<NDb::DBSceneObject> const& pDBObj);
	static void DumpImpl( const ObjectsPool* p );
};

}
