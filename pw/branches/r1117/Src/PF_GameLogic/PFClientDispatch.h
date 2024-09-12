#pragma once

#include "../PF_Core/BasicEffect.h"
#include "PFDispatchStrike1.h"
#include "PFClientObjectBase.h"
#include "VisibilityHelper.h"

namespace NGameX
{
  struct PFDispatchEffectHolder;

  typedef nstl::vector<NDb::Ptr<NDb::EffectBase>> EffectListEntries;
  typedef nstl::vector<PFDispatchEffectHolder> EffectsBucket;


  struct PFDispatchEffectHolder
  {
  public:
    PFDispatchEffectHolder():effect_(NULL), arrived_(false){}
    explicit PFDispatchEffectHolder(CObj<PF_Core::BasicEffectStandalone> effect): effect_(effect), arrived_(false){}

    ~PFDispatchEffectHolder(){ effect_ = NULL; }

    PF_Core::BasicEffectStandalone* GetEffect(){return effect_;}
    PF_Core::BasicEffectStandalone* GetEffect() const {return effect_;}

    void SetPosition(const Placement &position){effect_->SetPosition(position);}
    void SetArrived(bool arrived){arrived_ = arrived;}
    void SetEffect(CObj<PF_Core::BasicEffectStandalone> effect){effect_ = effect; arrived_ = false;}

    bool IsArrived(){return arrived_;}
    bool IsArrived() const {return arrived_;}

    //int effAddr(){return (int)effect_.GetPtr();}

    bool HasValidEffectObj(){ 
      return IsValid(effect_);
    }

    NScene::SceneObject *GetSceneObject() const
    {
      if (!effect_)
      {
        return NULL;
      }
      return effect_->GetSceneObject();
    }

  private:
    CObj<PF_Core::BasicEffectStandalone> effect_;
    bool arrived_;
  };


//-------------------------------------------------------------------------------------------
class PFDispatchUniformLinearMove : public NWorld::PFClientObjectBase, public PF_Core::IUpdateableAfterScene, public VisibilityHelper
{
	CLIENT_OBJECT_METHODS(0xE7A701BE, PFDispatchUniformLinearMove, NWorld::PFDispatchUniformLinearMove)

public:
	explicit PFDispatchUniformLinearMove() {}
	PFDispatchUniformLinearMove(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene, bool bAlignToAxis, float startDelay);

	virtual void OnWorldObjectDie();

	virtual void Update(float timeDelta);
	virtual void UpdateAfterScene(float timeDelta);

  virtual NScene::SceneObject *GetSceneObject() const
  {
    if (pEffects.size() == 0)
      return NULL;

    EffectsBucket::const_iterator ef = pEffects.begin();

    while(ef != pEffects.end())
    {
      if(IsValid(ef->GetEffect()) && !ef->GetEffect()->IsDead())
        return ef->GetSceneObject();

      ef++;
    }

    return NULL;
  }

  virtual NScene::SceneObject *GetSceneObject(const PF_Core::BasicEffectStandalone *pEffect) const
  {
    if (!pEffect)
    {
      return NULL;
    }
    return pEffect->GetSceneObject();
  }


  float GetCurYaw() const { return curYaw; }

  const EffectsBucket &GetEffects() const { return pEffects; }
  const int GetEffectsCount() const { return pEffects.size(); }

  // force dispatch to arrive at final destination immediately (as time-FF)
  void ForceFinish();

	bool IsStarted()
	{
		return bStarted;
	}

  virtual void OnArrive();
  //virtual void OnArrive(PFDispatchEffectHolder &effect);

private:
  static float GetTerrainHeight( NScene::IScene* scene, const CVec2& pos );
  void UpdateDesiredAngles();

  bool PredictTerrain( CVec3& target, CVec3& effectsMaxAABBZ);
  void UpdateTarget();

  bool GetStartPos( CVec3& result, Matrix43& matrix ) const;
  //void UpdateEffect( const Placement &pl, PFDispatchEffectHolder &effect );

  void CalcEffectsMaxAABBZ();
  void CalcEffectsMaxPositionZ();

  CVec3 MakeTargetingPos()
  {
    CVec3 pos = WorldObject()->GetTarget().MakeTargetingPos( WorldObject()->GetDB().toLocator.c_str() );
    if ( WorldObject()->GetDB().toLocator.empty() || WorldObject()->GetTarget().IsPosition() )
    {
      pScene->GetHeightsController().GetHeight( pos.x, pos.y, 1, &pos.z, 0 );
    }
    pos.z += WorldObject()->GetDB().height;
    return pos;
  }


	CPtr<NScene::IScene> pScene;
  EffectsBucket pEffects;

	CVec3 dest;
  CVec3 prevDest;
  CVec3 maxAABBZ;
  CVec3 maxPosZ;

  float curYaw, curPitch, desiredYaw, desiredPitch;
  bool bAlignToAxis;
  float startDelay;
  CVec2 curWorldPos;
  float speedModifier;

  NDb::EDispatchFlyMode flyMode;

  // current client object position
  CVec3 currentPos;
  Matrix43 startMatrix;
  float travelledDistance;
  bool bStarted;
  bool bArrived;

  // curve parameters
  float targetClientFinalDist;
  float targetHeight;
  float curHeight;
  float curveTg;

  bool isUnitBeforeMount;

	void Start();
  void RetrieveTargetCoords();
  void InitCurve();
  void StepCurve(float deltaX);
};

//-------------------------------------------------------------------------------------------
class PFDispatchByTime : public NWorld::PFClientObjectBase, public VisibilityHelper, public PF_Core::IEffectEnableConditionCallback
{
	CLIENT_OBJECT_METHODS(0xA7A2C19E, PFDispatchByTime, NWorld::PFDispatchByTime)
public:
	explicit PFDispatchByTime() {}
	PFDispatchByTime(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene);

  void Start();
  void StartInternal(NDb::EffectBase const *dispatchEffect, const NWorld::PFDispatchByTime *pWorldObject);

	virtual void OnWorldObjectDie();
	virtual void Update(float timeDelta);

  virtual NScene::SceneObject *GetSceneObject(PF_Core::BasicEffectStandalone *pEffect) const
  {
    if (!pEffect)
    {
      return NULL;
    }
    return pEffect->GetSceneObject();
  }

  virtual NScene::SceneObject *GetSceneObject() const
  {
    if (pEffects.size() == 0)
      return NULL;

    EffectsBucket::const_iterator ef = pEffects.begin();

    while(ef != pEffects.end())
    {
      if(!ef->GetEffect()->IsDead())
        return GetSceneObject(ef->GetEffect());
    }

    return NULL;
  }

  virtual void operator()(const PF_Core::BasicEffect &effect);

  virtual bool CheckEffectEnabled( const PF_Core::BasicEffect &effect );

private:
	CPtr<NScene::IScene> pScene;
  EffectsBucket pEffects;


};

//-------------------------------------------------------------------------------------------
class PFDispatchWithLink : public PFDispatchUniformLinearMove
{
  CLIENT_OBJECT_METHODS(0xA073D380, PFDispatchWithLink, NWorld::PFDispatchWithLink)
public:
  explicit PFDispatchWithLink() {}
  PFDispatchWithLink(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene, bool bAlignToAxis, float startDelay);
  ~PFDispatchWithLink();

private:
  vector<CObj<PF_Core::BasicEffect>> lightningLinks;
};

//-------------------------------------------------------------------------------------------
class PFDispatchRockmanMace : public PFDispatchWithLink
{
  CLIENT_OBJECT_METHODS(0xA073CA81, PFDispatchRockmanMace, NWorld::PFDispatchRockmanMace)
public:
  explicit PFDispatchRockmanMace() {}
  PFDispatchRockmanMace(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene, bool bAlignToAxis, float startDelay)
     : PFDispatchWithLink(pWO, pScene, bAlignToAxis, startDelay) {}

protected:
  virtual void OnArrive() {}
};

//-------------------------------------------------------------------------------------------

void PFDispatchPlayApplyEffect(CPtr<NWorld::PFDispatch> dispatch, NWorld::PFWorld *pWorld, NWorld::Target const &target);
void PFDispatchPlayEffect(NDb::EffectBase const *applyEffect, float height, CPtr<NWorld::PFDispatch> dispatch, NWorld::PFWorld *pWorld, NWorld::Target const &target);
void PFDispatchPlayEffectCollection(NDb::EffectBase const *applyEffect, float height, CPtr<NWorld::PFDispatch> dispatch, NWorld::PFWorld *pWorld, NWorld::Target const &target);

bool IsEffectEnabled(NDb::Ptr<NDb::EffectBase> effect, const NWorld::PFDispatch* dispatch);

}

