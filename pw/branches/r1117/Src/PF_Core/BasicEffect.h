#pragma once

#include "../System/RandomGen.h"
#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectCreation.h"

#include "ObjectsPool.h"
#include "ClientObject.h"
#include "DBEffect.h"

namespace NDb
{
  enum EFaction;
}

namespace NScene 
{ 
	_interface IScene; 
	class SceneComponent;
  class AnimatedSceneComponent;
}

namespace PF_Core
{

class BasicEffect;

struct ISceneComponentProcessor : public NScene::FullTraverser
{
	virtual void operator()(NScene::SceneComponent *pComp) = 0;
};

struct IEffectEnableConditionCallback : public IObjectBase
{
  virtual bool CheckEffectEnabled(const BasicEffect &effect) = 0;
};

// Calls pEnableCallback to check effect's enabling condition
struct EffectEnabledBase
{
  EffectEnabledBase() : pEnableCallback(0) {}

  virtual void SetEnableCallback(IEffectEnableConditionCallback* pCallback)
  {
    pEnableCallback = pCallback;
  }
  
  bool IsEffectEnabled(const BasicEffect &effect)
  {
    if(IsValid(pEnableCallback))
    {
      return pEnableCallback->CheckEffectEnabled(effect);
    }
    else
    {
      return true;
    }
  }

private:
  CPtr<IEffectEnableConditionCallback> pEnableCallback;

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicEffect : public ObjectInPool, public EffectEnabledBase
{
	OBJECT_BASIC_METHODS( BasicEffect )

public:

  BasicEffect() : deathType(NDb::EFFECTDEATHTYPE_MANUAL), timePassed(0.0f), lifeTime(0.f), bDying(false), isDead(false) {}
  BasicEffect(const NDb::EffectBase &dbEffect)
    : pDBObj(&dbEffect)
    , timePassed(0.0f)
    , bDying(false)
    , deathType(dbEffect.deathType)
    , lifeTime(dbEffect.lifeTime)
    , isDead(false)
    , isInterrupted(false)
  {}

	bool IsActive() const { return !IsInPool(); }

  virtual void SetDeathType(NDb::EEffectDeathType deathType_, float lifeTime_ = 0.f);

	virtual void Init();
	virtual void Update(float timeDelta);
	virtual void DieImmediate();

  virtual void Die();

	virtual void Apply(CPtr<ClientObjectBase> const &/*pUnit*/) { NI_ALWAYS_ASSERT("Method unsupported for this type of effect"); }
  virtual void Apply(CPtr<ClientObjectBase> const &pObject, NDb::EFaction) { Apply( pObject ); } // use for cases that requires faction for visibility evaluation

  virtual bool Ready2Die() { return false; }
  virtual void OnUncontrolledDyingEvent() {}

  virtual void SetPosition(const Placement &placement) {}
  virtual void SetRotation(const CQuat &rot) {}

  virtual void AddLocator(const Placement &placement) {}
  virtual void SetHeightAboveLocator( float height ) {}

  virtual void ForAllMaterials(Render::IMaterialProcessor &/*proc*/) {}

  virtual void ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add);
  void SetOpacity(float opacity);

  NDb::EEffectDeathType GetDeathType() const { return deathType; }
  bool IsDead() const { return isDead; }

  const NDb::EffectBase* GetDBDesc() const { return pDBObj; }

  virtual void SetActiveStateName(const string& name) {}

  float GetLifeTime() const { return lifeTime; }
  void SetInterrupted( bool interrupted );
  bool IsInterrupted();
protected:
  NDb::Ptr<NDb::EffectBase> pDBObj;
  NDb::EEffectDeathType     deathType;
	float     lifeTime;
  float     timePassed;
  bool      bDying;
  bool      isDead;
  bool      isInterrupted;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneComponentsEffect : public BasicEffect
{
	OBJECT_BASIC_METHODS( SceneComponentsEffect )
public: 
	SceneComponentsEffect(const NDb::EffectBase &dbEffect) : BasicEffect(dbEffect) {}
	SceneComponentsEffect() {}

	virtual void Init();
  virtual void Update(float timeDelta);
  virtual void SetDeathType(NDb::EEffectDeathType deathType_, float lifeTime_ = 0.f);

  virtual void ForAllRootSceneComponents(ISceneComponentProcessor & /*proc*/) {}
  virtual void ForAllSceneComponents(ISceneComponentProcessor & /*proc*/) {}
	virtual bool Ready2Die();
  virtual void OnUncontrolledDyingEvent();
	virtual void Die();
  virtual void ForAllMaterials(Render::IMaterialProcessor &proc);
  virtual void ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add);

  virtual NScene::SceneComponent *GetRootComponent() const { return NULL; }
  NScene::AnimatedSceneComponent *GetAnimRoot() const;

private:
  NDb::BasicEffect const &GetDBEffect() const { return *static_cast<NDb::BasicEffect const*>(pDBObj.GetPtr()); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class DB_EFFECT, class EFFECT = BasicEffect> 
class EffectDBLinker : public EFFECT
{
public:
	EffectDBLinker() {}
	EffectDBLinker(const NDb::EffectBase &dbEffect) : EFFECT(dbEffect)
	{
		// Try to cast applicator
		NI_ASSERT(dynamic_cast<DB_EFFECT const*>(pDBObj.GetPtr()) != 0, "Invalid DB applicator");
	}

	DB_EFFECT const &GetDBEffect() const { return *static_cast<DB_EFFECT const*>(pDBObj.GetPtr()); }

	typedef EffectDBLinker<DB_EFFECT, EFFECT> EffectBase;
	typedef DB_EFFECT DBType;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicEffectStandalone : public EffectDBLinker<NDb::BasicEffectStandalone, SceneComponentsEffect>
{
	OBJECT_METHODS( 0x9E691380, BasicEffectStandalone )
public:
	BasicEffectStandalone(const NDb::EffectBase &dbEffect);
	BasicEffectStandalone() {}
	void Init();

	void AddToScene(NScene::IScene *pScene);

  virtual void SetPosition(const Placement &placement);
  virtual void SetRotation(const CQuat &rot);

  virtual NScene::SceneComponent *GetRootComponent() const { return GetSceneObject()->GetRootComponent(); }
  virtual void ForAllRootSceneComponents(ISceneComponentProcessor &proc);
  virtual void ForAllSceneComponents(ISceneComponentProcessor &proc);

	virtual void Update(float timeDelta);

	virtual void Die();
  virtual void DieImmediate();
  virtual void Apply(CPtr<ClientObjectBase> const &pUnit);
  virtual void Apply( const NScene::SceneObject* pSO);
	virtual bool Ready2Die();
	virtual void OnUncontrolledDyingEvent();
  void SwitchEffect( const NDb::Ptr<NDb::EffectBase>& newEffect );
  void SetSceneObject( NScene::SceneObject* so )
  {
    Reset( pObject, so );
  }

	NScene::SceneObject *GetSceneObject() const { return Get(pObject); }

protected:
	NScene::SceneObjectRef pObject;
  float opacity;
  bool isSwitched;
  NDb::Ptr<NDb::EffectBase> originalDB;
};

struct LocatorInfo
{
  NDb::Locator locator;
  NScene::SceneComponent *pSC;
};

class LocatorInfoFunc : public NScene::IParseLocatorFunc
{
public:
	LocatorInfoFunc( nstl::vector<LocatorInfo> &locators ) : locators(locators) {}

  void operator()( NDb::Locator const &locator, NScene::SceneComponent *pSC )
	{
    LocatorInfo info;
    info.locator = locator;
    info.pSC = pSC;
    locators.push_back( info );
	}

protected:
	nstl::vector<LocatorInfo> &locators;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicEffectAttached : public EffectDBLinker<NDb::BasicEffectAttached, SceneComponentsEffect>
{
  nstl::vector<LocatorInfo> locators;

	OBJECT_METHODS( 0x9E691381, BasicEffectAttached )
public:
	BasicEffectAttached(const NDb::EffectBase &dbEffect);
  BasicEffectAttached() : pSceneObject() {}

  void CreateRootComponent();
  void Init();

	void SetScale(float scale);

	virtual void Apply(CPtr<ClientObjectBase> const &pUnit);
	void Attach(NScene::SceneObject *pObj);

  virtual NScene::SceneComponent *GetRootComponent() const { return root; }
  virtual void DieImmediate();
	virtual bool Ready2Die();
	virtual void ForAllRootSceneComponents(ISceneComponentProcessor &proc);
  virtual void ForAllSceneComponents(ISceneComponentProcessor &proc);

  virtual void SetPosition(const Placement &placement);
  virtual void SetRotation(const CQuat &rot);
  virtual void Die();
  virtual void AddLocator(const Placement &placement);
  virtual void SetHeightAboveLocator( float height );
	virtual void OnUncontrolledDyingEvent();

  NScene::SceneObject *GetSceneObject() const { return pSceneObject; }

  void Hide(bool hide);

protected:
  void SwapHierarchy(BasicEffectStandalone &standalone);

	NScene::SceneObject *pSceneObject; // Scene object we've attached to
	CObj<NScene::SceneComponent> root;
  bool bAuxRoot; // was root component created by effect as an auxiliary parent
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EffectSelector
{
public:
  EffectSelector(NDb::Ptr<NDb::EffectSelector> pDBObj) : pDBObj(pDBObj), nextEffectIdx(0)
  {
  }

  NDb::Ptr<NDb::BasicEffectStandalone> GetNextEffect()
  {
    if ( !IsValid( pDBObj ) || pDBObj->effects.size() == 0 )
    {
      return NDb::Ptr<NDb::BasicEffectStandalone>(NULL);
    }

    int idx = 0;
    switch (pDBObj->selectionPolicy)
    {
      case NDb::EFFECTSELECTIONPOLICY_RANDOM:
      {
        idx = NRandom::Random( pDBObj->effects.size() );
        break;
      }
      case NDb::EFFECTSELECTIONPOLICY_SEQUENTIAL:
      {
        idx = nextEffectIdx++;
        if (nextEffectIdx >= pDBObj->effects.size())
        {
          nextEffectIdx = 0;
        }
        break;
      }
    }

    return pDBObj->effects[idx];
  }

protected:
  NDb::Ptr<NDb::EffectSelector> pDBObj;
  int nextEffectIdx;
};

}
