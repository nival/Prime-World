#pragma once

#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/CollisionHull.h"

#include "../PF_Core/ColorModificationChannel.h"

#include "PFClientSceneObjectsHolders.h"
#include "PFLogicObject.h"

#include "ClientVisibilityFlags.hpp"

#include "System/StarForce/HiddenVars.h"

namespace NGameX
{

class ISceneObjectsHolder;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientLogicObject : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_WORLD( PFClientLogicObject, NWorld::PFLogicObject );
public:
  struct CreatePars;

  bool IsVisible() const { return bVisible; }
  bool IsVisibleForEnemy( int faction ) const 
  { 
    if (const NWorld::PFLogicObject *pObject = WorldObject()) 
      return pObject->IsVisibleForEnemy( faction ); 
    return true; 
  }
 
  // ~~ overrides ~~
  virtual void OnWorldObjectDie();

  void ClearColorModifications();
  bool TryCreateStandaloneEffect();
  void CreateStandaloneEffect();
  virtual void SetVisibility(bool bVisible) { SetVisibilityAsBuilding(bVisible); }
  virtual void RevalidateVisibility() { SetVisibility(bVisible); }
  virtual void RenderDebug() {}
  virtual void MultiplyTemporaryScale(float scale) { scaleTemporary *= scale; }
  virtual void MultiplyAnimSpeed( float scale ) { }

  virtual float GetTimeDead() const { return 0.0f; } // for creatures dead bodies

  virtual void UpdateVisibility();

	// static methods
  AutoPtr<NScene::SceneObject>  MakeSceneObject(const NDb::DBSceneObject& dbSceneObject, const Placement& pl, const nstl::string& nodeName);

  // Additional methods
  void MakeTargetingPos(CVec3 &pos);
  virtual void SetRotation(CQuat const &quat);
  
  virtual PF_Core::ColorModificationChannel* CreateColorModificationChannel(PF_Core::ColorModificationPriority priority, bool fullRecolor = false );
  virtual void RemoveColorModificationChannel(PF_Core::ColorModificationChannel* pChannel);
  
  void ModifyOpacity(float opacity) const { NScene::ModifySceneObjectOpacity(*GetSceneObject(), opacity); }
  void ForcePlacement(Placement const& placement){ SetPlacement(placement); }

  NScene::SceneObject* GetSceneObject()const;
	const nstl::string& GetNodeName() const;

  virtual void EnableById( string id, bool bEnable );
  virtual void ProcessExternalEvent( const char* externalEvent ) { GetSceneObject()->ProcessExternalEvent( externalEvent ); }

  NScene::CollisionHull * GetCollisionHull() const { return GetSceneObject() ? GetSceneObject()->GetCollision() : NULL; }
  
  // ~~ !!Not to use in world objects!! ~~
  float GetSize() const { return unitSize; }
  const Placement& GetPosition() const { return (GetSceneObject() != NULL)?GetSceneObject()->GetPosition():NULLPLACEMENT; }

protected:
  PFClientLogicObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp);
  PFClientLogicObject(); // @BVS@TODO: Remove this ctor when CObj/Cptr permits

  virtual ~PFClientLogicObject();
  virtual void OnDestroyContents();

  // From IUpdateable
  virtual void Update( float timeDiff );

  void SetPlacement(const Placement& placement);
  void UpdatePlacement(Placement& placement);

  void SetVisibilityAsBuilding(bool bVisible);
  void SetVisibilityAsObject(bool bVisible);

  inline bool DoSetVisible(const bool value);
  inline bool DoCheckVisible(const bool value) const;

  AutoPtr<ISceneObjectsHolder>  pSceneObjectsHolder;

  NScene::IScene*               pScene;
  float                         unitSize;
  CVec3                         scalePermanent;
  float                         scaleTemporary;

  Protection::HiddenVar<bool, 33>::T bVisible;

  friend struct PFClientLogicObjectAttacherPolicy;
private:
  bool                                        colorChanged;
  nstl::vector<CObj<PF_Core::ColorModificationChannel>> colorModifications;
  nstl::vector<CObj<PF_Core::ColorModificationChannel>> fullColorModifications;

  void                               ProcessColorModifications();
  void                               ProcessColorModifications( vector<CObj<PF_Core::ColorModificationChannel>>& colorModifications, bool fullCM = false );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PFClientLogicObject::CreatePars : public NonCopyable
{
	CreatePars(NScene::IScene* pScene, const nstl::string& nodeName, NDb::Ptr<NDb::DBSceneObject> const& sceneObject, NDb::Ptr<NDb::CollisionGeometry> const& pCollision) : pScene(pScene), sceneObject(sceneObject), pCollision(pCollision), placement(NULL), nodeName(nodeName) {}
  CreatePars(NScene::IScene* pScene, const nstl::string& nodeName, NDb::Ptr<NDb::DBSceneObject> const& sceneObject) : sceneObject(sceneObject), pScene(pScene), placement(NULL), nodeName(nodeName) {}
  CreatePars(NScene::IScene* pScene, const nstl::string& nodeName, NDb::Ptr<NDb::GameObject> const& gameObject);
  CreatePars(NScene::IScene* pScene, const nstl::string& nodeName, NDb::AdvMapObject const& advMapObject);

  NScene::IScene*                   pScene;
  NDb::Ptr<NDb::DBSceneObject>      sceneObject;
  NDb::Ptr<NDb::CollisionGeometry>  pCollision;
  CPlacement const                 *placement;
	nstl::string											nodeName;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientSingleStateObject : public PFClientLogicObject
{
  CLIENT_OBJECT_METHODS(0xF624CC0, PFClientSingleStateObject, NWorld::PFLogicObject);
public:
  PFClientSingleStateObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NDb::GameObject* gameObject = 0 );
  PFClientSingleStateObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NGameX::PFClientLogicObject* unitClientObject );
  void OnMove( const CVec3& position );
  void RemoveCollision();
protected:
  explicit PFClientSingleStateObject() {}
private:
  void InitInternal(Placement& place, const PF_Core::WorldObjectRef &pWO, const CreatePars &cp);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PFClientLogicObjectAttacherPolicy
{
	typedef PFClientLogicObject Object;
	static void Render(PFClientLogicObject* pO, class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants)
	{
	}
	static void Update(PFClientLogicObject* pO, const Placement &pl, float timeDiff) 
	{ 
		pO->SetPlacement(pl); 
	}
	static void RetrieveWorldAABB(PFClientLogicObject* pO, Render::AABB &aabb) { aabb = pO->GetSceneObject()->GetWorldAABB(); }
	static void Reinit(PFClientLogicObject* pO) { pO->GetSceneObject()->Reinit(); }
	static void Deinit(PFClientLogicObject* pO) { pO->GetSceneObject()->Deinit(); }
};

inline bool PFClientLogicObject::DoSetVisible(const bool value)
{
  const int storageValue = value;

  if (bVisible == storageValue)
    return false;

  bVisible = storageValue;

  return true;
}

inline bool PFClientLogicObject::DoCheckVisible(const bool value) const
{
  const int storageValue = value;

  return (bVisible == storageValue);
}

}