#include "stdafx.h"
#include "PFClientLogicObject.h"
#include "PFClientSceneObjectsHolders.h"
#include "../Scene/SceneObjectCreation.h"
#include "../System/InlineProfiler.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleSceneObjectHolder::SingleSceneObjectHolder( NScene::IScene* pScene, int _worldObjectId, const Placement& place, 
																								 NDb::Ptr<NDb::DBSceneObject> const& _dbObject, 
																								 const NDb::Ptr<NDb::CollisionGeometry>& _dbCol, const nstl::string& nodeName )
: pScene(pScene)
, enabled(true)
, visible(true)
, updatePriority(NScene::UPDATEPRIORITY_NORMAL)
, dbObject( _dbObject )
, worldObjectId( _worldObjectId )
, dbCollision( _dbCol )
, nodeName( nodeName )
{
  if ( dbObject )
  {
    NI_PROFILE_FUNCTION

    sceneObject = NScene::SceneObjectsPool::Get()->Retrieve( pScene, dbObject, nodeName ); //NScene::CreateSceneObject(pScene, *dbObject);

    sceneObject->SetOwnerID(worldObjectId);
    sceneObject->SetPlacement(place);
    sceneObject->UpdateForced(); // recalculate AABB

    sceneObject->AddToScene(pScene, updatePriority);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleSceneObjectHolder::Enable( bool bEnable, bool /*forced*/ )
{
  if (bEnable != enabled)
  {
    enabled = bEnable;
    if (sceneObject)
    {
      if (enabled)
        sceneObject->AddToScene(pScene, updatePriority);
      else
        sceneObject->RemoveFromScene();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleSceneObjectHolder::SetVisibility( bool bEnable )
{
  if (bEnable != visible)
  {
    visible = bEnable;
    if (sceneObject)
    {
      sceneObject->EnableRender(visible);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleSceneObjectHolder::Reset()
{
  ::Reset(sceneObject, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleSceneObjectHolder::SetUpdatePriority(NScene::UpdatePriority priority)
{
  if (updatePriority != priority)
  {
    updatePriority = priority;

    if (enabled)
    {
      NScene::IScene *pScene = sceneObject->GetScene();
      sceneObject->RemoveFromScene();
      sceneObject->AddToScene(pScene, updatePriority);

      if (!visible)
      {
        sceneObject->EnableRender(false);
      }
    }
  }
}

void SingleSceneObjectHolder::Recreate( const Placement& place, const nstl::string& nodeName )
{
  if ( dbObject )
  {
    sceneObject = NScene::SceneObjectsPool::Get()->Retrieve( pScene, dbObject, nodeName ); //NScene::CreateSceneObject(pScene, *dbObject);
    sceneObject->SetOwnerID(worldObjectId);
    sceneObject->SetPlacement(place);
    sceneObject->UpdateForced(); // recalculate AABB

    sceneObject->AddToScene(pScene, updatePriority);

    if (!visible)
    {
      sceneObject->EnableRender(false);
    }
  }
}

const NDb::CollisionGeometry* SingleSceneObjectHolder::GetCollision() const
{
  return dbCollision.GetPtr();
}

const NDb::DBSceneObject* SingleSceneObjectHolder::GetDBObject() const
{
	return dbObject.GetPtr();
}

void SingleSceneObjectHolder::SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc )
{
  dbObject = sceneObjectDesc;
}

} //namespace NGameX