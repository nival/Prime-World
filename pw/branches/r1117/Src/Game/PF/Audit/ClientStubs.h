#pragma once
#include "PF_GameLogic/PFChest.h"
#include "PF_GameLogic/PFUniTarget.h"

namespace PF_Core
{
	class BasicEffect;
  class LightningEffect;
}

namespace NWorld
{
  class PFWorldObjectBase;
  class PFBaseUnit;
  class PFBaseHero;
  class PFChest;
  class Target;
  enum  EEmotion;
}

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////
class BaseClientObjectStub : public NWorld::PFClientObjectBase
{
public:
  BaseClientObjectStub() {}
  BaseClientObjectStub(const CPtr<PF_Core::WorldObjectBase> &pWO) : PFClientObjectBase(pWO) {}

  void SetVisibility(bool) {}
  void OnMove(const CVec3&) {}
  void Update(float) {}
  void OnDamage(float, float) {}
	void OnHide(bool) {}
  void OnAttack(float, CVec3 const&, bool) {}
  void OnMiss() {}
  void OnLevelUp(int level) {}
  void RenderDebug() {}
  void OnBecameLocal(bool) {}
  void OnDeath() {}
  void Show(bool b = true) {}
  void OnResurrect() {}
	void OnUseMagic(int id, NWorld::Target const& target, float timeOffset, unsigned flags) {}
  void OnAwardedForKill(CPtr<NWorld::PFBaseUnit> const&, const float) {}
	void OnAddGold(CPtr<NWorld::PFBaseUnit> const&, const float) {}
  void PlayAskSound(int) {}
  void SetRotation(CQuat const&) {}
	void Recolor(float) {}
	void ResetColor() {}
  void ModifyColor(const Render::HDRColor&, const Render::HDRColor &) const {}
  void ModifyColor(const Render::HDRColor &) const {}
  void DropTree(const CVec3&, const CPtr<NWorld::PFBaseUnit> &) {}
  void RestoreTree() {}
  void ModifyOpacity(float) const {}
  void SetNatureType(int) {}
  void OnMoveTo(const CVec3&, bool /*animate*/ = true ) {}
  void OnTeleportTo(CVec3 const&) {}
  void OnAttachTo(CPtr<NWorld::PFBaseHero> const&) {}
  void OnDetach() {}
  void OnStop() {}
  void SetMoveSpeed(float) {}
  void SetAttackSpeed(float) {}
  void Perish() {}
  void Resurrect() {}
  void StartFallThrough(float) {}
  void OnEmote(NDb::EEmotion) {}
	void SetTileRegion(const CTRect<int> &) {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientLogicObject : public BaseClientObjectStub
{
public:
  struct CreatePars : public NonCopyable
  {
  public:
    CreatePars(const NDb::Unit &unit, NDb::AnimSet const* pAnimSet, NDb::AnimSet const* pAnimSitSet, NScene::IScene *pS)  {}
    CreatePars(const NDb::Unit &unit, NDb::AnimSet const* pAnimSet, NScene::IScene *pS)  {}
    CreatePars(const NDb::BaseHero &unit, NDb::AnimSet const* pAnimSet, NScene::IScene *pS, NDb::EFaction faction) {}
    CreatePars(const NDb::BaseHero &unit, NDb::AnimSet const* pBaseAnimSet, NDb::AnimSet const* pSitAnimSet, NScene::IScene *pS, NDb::EFaction faction) {}
    CreatePars(NDb::Ptr<NDb::DBSceneObject> const& sceneObject, NDb::AnimSet const* pAnimSet, NScene::IScene *pS) {}
    CreatePars(NScene::IScene*, NDb::Ptr<NDb::DBSceneObject> const&, NDb::Ptr<NDb::CollisionGeometry> const&){}
    CreatePars(NScene::IScene*, NDb::Ptr<NDb::DBSceneObject> const&) {}
    CreatePars(NScene::IScene*, NDb::Ptr<NDb::GameObject> const&) {}
		CreatePars(NScene::IScene*, NDb::AdvMapObject const& ) {}
    CreatePars(const NDb::Unit&, NScene::IScene *pS) {}
  };
  PFClientLogicObject() {}
  PFClientLogicObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp) : BaseClientObjectStub(pWO) {}

  //TODO: Fix build audit
  void UpdateVisibility() {}
  float GetTimeDead() const { return 0.0f; }
};

//////////////////////////////////////////////////////////////////////////
class PFClientSingleStateObject : public PFClientLogicObject
{
  CLIENT_OBJECT_METHODS(0xF624CC0, PFClientSingleStateObject, NWorld::PFLogicObject);
public:
  PFClientSingleStateObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp) : PFClientLogicObject(pWO, cp) {}
  PFClientSingleStateObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NGameX::PFClientLogicObject* unitClientObject ) : PFClientLogicObject(pWO, cp) {}
  void OnMove(const CVec3&) {}
  void RemoveCollision() {}
protected:
  explicit PFClientSingleStateObject() {}
};


//////////////////////////////////////////////////////////////////////////
class PFClientMultiStateObject : public PFClientLogicObject
{
  CLIENT_OBJECT_METHODS(0xF624DC0, PFClientMultiStateObject, NWorld::PFLogicObject);
public:
  PFClientMultiStateObject(const PF_Core::WorldObjectRef &pWO, NScene::IScene* pScene, NDb::AdvMapObject const& advMapObject) : PFClientLogicObject(pWO, CreatePars(pScene, advMapObject)) {}
  void OnMove(const CVec3&) {}
  void RemoveCollision() {}
protected:
  explicit PFClientMultiStateObject() {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientChest : public PFClientSingleStateObject
{
  CLIENT_OBJECT_WORLD( PFClientChest, NWorld::PFPickupableObjectBase )
public:
  PFClientChest(const PF_Core::WorldObjectRef &, const CreatePars &) {}

  virtual void Update( float timeDiff ) {};
};

//////////////////////////////////////////////////////////////////////////
class PFClientGlyph : public PFClientSingleStateObject
{
  CLIENT_OBJECT_WORLD( PFClientGlyph, NWorld::PFPickupableObjectBase )
public:
  PFClientGlyph(const PF_Core::WorldObjectRef &pWO, const CreatePars& cp, const Render::HDRColor& color) {}
  PFClientGlyph(const PF_Core::WorldObjectRef &, const CreatePars &) {}

  virtual void Update( float timeDiff ) {};
};

//////////////////////////////////////////////////////////////////////////
class PFClientBaseUnit : public PFClientLogicObject
{
  CLIENT_OBJECT_WORLD( PFClientBaseUnit, NWorld::PFLogicObject )
public:
  PFClientBaseUnit() {}
  PFClientBaseUnit(PF_Core::WorldObjectRef pWO, const CreatePars &cp) : PFClientLogicObject(pWO, cp) {}
  void OnUnitDie() {}
  void OnBecameIdle() {}
  void OnStartedFighting() {}
  void OnFinishedFighting() {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientBaseMovingUnit : public PFClientBaseUnit
{
public:
  PFClientBaseMovingUnit() {}
  PFClientBaseMovingUnit(PF_Core::WorldObjectRef pWO, const CreatePars &cp) : PFClientBaseUnit(pWO, cp) {}
  void OnFarTargetChanged( CVec3 const&  ) {}
  void LookTo(CVec3 const&, bool = false) {}
  void OnMoveFailed() {}
};

//////////////////////////////////////////////////////////////////////////
class PFAnimController
{
public:
  PFAnimController() {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientCreature : public PFClientBaseMovingUnit, public PFAnimController
{
  CLIENT_OBJECT_WORLD( PFClientCreature, PF_Core::WorldObjectBase )
public:
  PFClientCreature() {}
  PFClientCreature(PF_Core::WorldObjectRef const& pWO, const CreatePars &cp) {}

  int  ReplaceAnimSet( NDb::Ptr<NDb::AnimSet> pSet ) { return -1; }
  bool RollbackAnimSet( int setId )                  { return false; }
  int  ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool affectAllSets)  { return -1; }
  bool RollbackAnimation( NDb::EAnimStates state, int id, bool upper)                               { return false; }

	void CreateStandaloneEffect() {}
};

//////////////////////////////////////////////////////////////////////////
class PFBaseClientHero : public PFClientCreature
{
  CLIENT_OBJECT_METHODS( 0xF63FCC0, PFBaseClientHero, NWorld::PFLogicObject )
public:
  PFBaseClientHero() {}
  PFBaseClientHero(PF_Core::WorldObjectRef pWO, const CreatePars &cp) : PFClientCreature(pWO, cp) {}
};

class PFClientMaleHero : public PFBaseClientHero
{
  CLIENT_OBJECT_METHODS( 0x2C59BC81, PFClientMaleHero, NWorld::PFLogicObject )
public:
  explicit PFClientMaleHero() {}
  PFClientMaleHero(PF_Core::WorldObjectRef pWO, const CreatePars &cp) : PFBaseClientHero(pWO, cp) {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientPriestess : public PFClientCreature
{
  CLIENT_OBJECT_METHODS( 0xC566BC80, PFClientPriestess, NWorld::PFLogicObject )
public:
  PFClientPriestess() {}
  PFClientPriestess(PF_Core::WorldObjectRef pWO, const CreatePars &cp) : PFClientCreature(pWO, cp) {}
  void OnMount( CPtr<NWorld::PFBaseHero>  const& pHero ) {}
  void OnUnmount( ) {}
};

//////////////////////////////////////////////////////////////////////////
class PFBuilding : public PFClientBaseUnit
{
  CLIENT_OBJECT_METHODS( 0xF63FC40, PFBuilding, NWorld::PFLogicObject );
public:
  PFBuilding() {}
  PFBuilding(PF_Core::WorldObjectRef pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene) : PFClientBaseUnit(pWO, CreatePars(pScene, mapObject.gameObject) ) {}
};

//////////////////////////////////////////////////////////////////////////
class PFCreep : public PFClientCreature
{
  CLIENT_OBJECT_METHODS( 0xF63FC41, PFCreep, NWorld::PFLogicObject );
public:
  PFCreep() {}
  PFCreep(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp) : PFClientCreature(pWO, cp) {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientTree : public PFClientLogicObject
{
  CLIENT_OBJECT_METHODS( 0xF63FC80, PFClientTree, NWorld::PFLogicObject );
public:
  PFClientTree() {}
  PFClientTree(const PF_Core::WorldObjectRef &pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene_) : PFClientLogicObject( pWO, CreatePars(pScene_, mapObject.gameObject) ) {}
};

//////////////////////////////////////////////////////////////////////////
class PFTower : public PFBuilding
{
  CLIENT_OBJECT_METHODS( 0xF63FC81, PFTower, NWorld::PFLogicObject )
public:
  PFTower() {}
  PFTower(PF_Core::WorldObjectRef pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene) : PFBuilding(pWO, mapObject, pScene) {}

  void OnRotationChanged( float angle, bool forced = false ) {}
};

//////////////////////////////////////////////////////////////////////////
//class PFClientMinigamePlace : public PFBuilding
//{
//  CLIENT_OBJECT_METHODS( 0xF63FCC1, PFClientMinigamePlace, NWorld::PFLogicObject )
//public:
//  PFClientMinigamePlace() {}
//  PFClientMinigamePlace(PF_Core::WorldObjectRef pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene) : PFBuilding(pWO, mapObject, pScene) {}
//};

//////////////////////////////////////////////////////////////////////////
class PFClientNatureMap : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS(0xF63FCC2, PFClientNatureMap, NWorld::PFWorldObjectBase )
public:
  explicit PFClientNatureMap() {}
  PFClientNatureMap(const PF_Core::WorldObjectRef &pWO) : PFClientObjectBase(pWO) {}
  void OnCreate(int texSideX, int texSideY) {}
  void OnStep() {}
  void SwitchDebugDrawLines() {}
};

//////////////////////////////////////////////////////////////////////////
class VisibilityMapClient : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS( 0xF63FCC2, VisibilityMapClient, PF_Core::WorldObjectBase )
public:
  VisibilityMapClient() {}
  VisibilityMapClient(const PF_Core::WorldObjectRef &pWO) : PFClientObjectBase(pWO) {}
  void OnCreate(int texSideX, int texSideY, const CVec3 &worldSize, Render::HDRColor &color) {}
  void OnStep() {}
};

//////////////////////////////////////////////////////////////////////////
class PFClientSimpleObject : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS( 0xF640B00, PFClientSimpleObject, PF_Core::WorldObjectBase )
public:
  explicit PFClientSimpleObject() {}
  PFClientSimpleObject(PF_Core::WorldObjectRef pWO, NDb::AdvMapObject const& dbObject, NScene::IScene* pScene) : PFClientObjectBase(pWO) {}
};

//////////////////////////////////////////////////////////////////////////
class PFDispatchUniformLinearMove : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS( 0xF640B01, PFDispatchUniformLinearMove, PF_Core::WorldObjectBase );
public:
  PFDispatchUniformLinearMove() {}
  PFDispatchUniformLinearMove(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene, bool bAlignToAxis) {}
};

//////////////////////////////////////////////////////////////////////////
class PFDispatchByTime : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS( 0xF640B02, PFDispatchByTime, PF_Core::WorldObjectBase );
public:
  PFDispatchByTime() {}
  PFDispatchByTime(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene) : NWorld::PFClientObjectBase(pWO) {}
};

//////////////////////////////////////////////////////////////////////////
inline void PFDispatchPlayApplyEffect(CPtr<NWorld::PFDispatch>, NWorld::PFWorld*, NWorld::Target const&) {}

inline void CreateEffect(CObj<PF_Core::BasicEffect> &pEffect, const NDb::Ptr<NDb::EffectBase> effect, CPtr<NWorld::PFBaseUnit> pSender, CPtr<NWorld::PFBaseUnit> pTarget) {}
inline void PlayEffect(CPtr<NWorld::PFBaseUnit> , const NDb::Ptr<NDb::EffectBase>, CPtr<NWorld::PFBaseUnit> , const char *locatorName = 0 ) {}
inline void KillEffect(CObj<PF_Core::BasicEffect> &, bool waitTillAnimationFinish = false) {}

inline CObj<PF_Core::LightningEffect> CreateLightningEffect(const NDb::Ptr<NDb::LightningEffect> pEffect) { return CObj<PF_Core::LightningEffect>(NULL); }

} //namespace NGameX
