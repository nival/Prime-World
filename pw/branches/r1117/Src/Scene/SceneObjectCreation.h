#pragma once

#include "SceneComponent.h"
#include "SceneObject.h"

#include "StaticSceneComponent.h"

namespace NScene
{

class CollisionHull;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct IParseLocatorFunc : public NonCopyable
{
	virtual void operator() (NDb::Locator const &locator, SceneComponent *pSC) = 0;
};

struct DummyParseLocatorFunc : public IParseLocatorFunc
{
	void operator() (NDb::Locator const &locator, SceneComponent *pSC) {}
};

class ObjAddLocatorFunc : public IParseLocatorFunc
{
public:
	ObjAddLocatorFunc(SceneObject &_obj) : obj(_obj) {}

	void operator() (NDb::Locator const &locator, SceneComponent *pSC)
	{
		obj.AddLocator(locator, pSC);
	}

protected:
	SceneObject &obj;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This struct must be in-sync with StoreColorsTraverser from \EditorNative\EditorScene.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct LoadColorsTraverser : public FullTraverser, NonCopyable
{
  NScene::MeshVertexColorsManager &man;
  int curStaticComponentIdx;

  LoadColorsTraverser(MeshVertexColorsManager &man) : man(man), curStaticComponentIdx(0) {}

  void operator() (SceneComponent *sc)
  {
    if( StaticSceneComponent *ssc = dynamic_cast<StaticSceneComponent*>(sc) )
      ssc->LoadVertexColors(man, curStaticComponentIdx++);
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HierarchyCreator : public NonCopyable
{
	IParseLocatorFunc       &lf;
  bool isStaticAndAnimatedOnly;
	const nstl::string& nodeName;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	HierarchyCreator(IParseLocatorFunc &lf_, const nstl::string& nodeName, bool isStaticAndAnimatedOnly = false) 
    : lf(lf_), nodeName(nodeName), isStaticAndAnimatedOnly(isStaticAndAnimatedOnly) {}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CObj<StaticSceneComponent> Create( const NDb::DBStaticSceneComponent* pDBComponent, const NDb::AttachedSceneComponent* pAttached, 
																				 		const Placement& transform );

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<CObj<SceneComponent>> ParseAttachedSceneComponents( const vector<NDb::AttachedSceneComponent> &attached, bool isEditor = false );
	vector<CObj<SceneComponent>> ParseAttachedSceneComponent( const NDb::AttachedSceneComponent* pVisual, bool isEditor = false );
	vector<CObj<SceneComponent>> ParseAttachedSceneComponent( const NDb::DBSceneComponent* pVisual, bool isEditor = false );
	vector<CObj<SceneComponent>> ParseSceneComponent( const NDb::DBSceneComponent* pVisual, bool isEditor = false );

	const nstl::string& GetNodeName() const
	{
		return nodeName;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class OBJ, class DB_OBJ>
CObj<SceneComponent> CreateSceneComponent(const DB_OBJ &dbObj, HierarchyCreator &creator, 
																									const NDb::AttachedSceneComponent* pAttached, const Placement& transform)
{
	return new OBJ( &dbObj, pAttached, transform );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <> inline 
CObj<SceneComponent> CreateSceneComponent<StaticSceneComponent>(const NDb::DBStaticSceneComponent &dbObj, HierarchyCreator &creator, 
																																				const NDb::AttachedSceneComponent* pAttached, const Placement& transform)
{
  return creator.Create( &dbObj, pAttached, transform ).GetPtr();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CObj<SceneComponent> CreateAnimatedSceneComponent(const NDb::DBAnimatedSceneComponent &dbObj, HierarchyCreator &creator, 
                                                          const NDb::AttachedSceneComponent* pAttached, const Placement& transform);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Old stuff
vector<CObj<SceneComponent>> ParseAnimated( const NDb::Skeleton* pVisual );
vector<CObj<SceneComponent>> ParseStaticMesh( const NDb::StaticMesh* pVisual );
vector<CObj<SceneComponent>> ParseEffect( const NDb::Effect* pVisual, const Placement& offset );

// New parse stuff
vector<CObj<SceneComponent>> ParseSceneObject( const NDb::DBSceneObject* pVisual, IParseLocatorFunc &lf, const nstl::string& nodeName, bool isEditor = false, bool isStaticAndAnimatedOnly = false );
vector<CObj<SceneComponent>> ParseSceneComponent( const NDb::DBSceneComponent* pVisual, IParseLocatorFunc &lf, bool isEditor = false );

// Creation stuff
void AppendComponentsToSceneObject( SceneObject &object, const NDb::DBSceneComponent &sceneComponent );
AutoPtr<NScene::SceneObject> CreateSceneObject( IScene *pScene, const NDb::DBSceneObject &sceneObject, const nstl::string& nodeName );
AutoPtr<NScene::SceneObject> CreateSceneObject( IScene *pScene, const NDb::DBSceneComponent &sceneComponent );

// Collision hull stuff
void EstimateSceneObjectHullAABB( SceneObject &so, Render::AABB &aabb );
CollisionHull* MakeCollisionHullForObject( SceneObject &so, const NDb::CollisionGeometry* pCollGeo );
CollisionHull* MakeSmallCollisionHullForObject( SceneObject &so, const NDb::CollisionGeometry* pCollGeo );

}
