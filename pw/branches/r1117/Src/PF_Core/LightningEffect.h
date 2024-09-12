#pragma once

#include "../Scene/SceneObject.h"
#include "../Scene/LightningFX.h"
#include "../Render/debugrenderer.h"

#include "BasicEffect.h"

namespace PF_Core
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PositionGenerator
{
  virtual ~PositionGenerator() {}
  virtual bool GetPos(CVec3 &pos) const = 0;
  virtual bool IsPosVisible() const
  {
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct StaticPositionGenerator : public PositionGenerator
{
  StaticPositionGenerator(CVec3 const &pos) : pos(pos) {}

  virtual bool GetPos(CVec3 &pos_) const
  {
    pos_ = pos;
    return true; 
  }

protected:
  CVec3 pos;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LightningEffect : public EffectDBLinker<NDb::LightningEffect>
{
public:
  
  __declspec(align(16))
  class Object : public NScene::SceneObjectBase
  {
  public:
    DECLARE_NEWDELETE_ALIGN16(Object);

    Object(LightningEffect *owner) : owner(owner)
    {
      aabb.Init2Empty();
    }

    virtual const Render::AABB &GetWorldAABB() const { return aabb; }

    virtual void Update(float timeDelta, bool isForcedUpdate = false);

    virtual void Render(Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL);

    virtual void DebugDraw( Render::IDebugRender* ) {}

  protected:
    Render::AABB  aabb;
    LightningEffect *owner;
  };

  
  
  LightningEffect(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect), pEnableCallback(0) {}

  void Init();

  void DieImmediate()
  {
    sceneObj->RemoveFromScene();
    Reset(begin);
    Reset(end);
    BasicEffect::DieImmediate();
  }

  PositionGenerator *GetPositionGeneratorBegin() const { return Get(begin); }
  PositionGenerator *GetPositionGeneratorEnd() const { return Get(end); }

  void SetPositionGeneratorBegin(PositionGenerator *g) { Reset(begin, g); }
  void SetPositionGeneratorEnd(PositionGenerator *g)   { Reset(end, g); }

  void AddToScene(NScene::IScene *pScene)
  {
    NI_ASSERT( GetPositionGeneratorBegin() && GetPositionGeneratorEnd(), "Both position generators for lightning should be set" );
    sceneObj->Update(0.0f);
    sceneObj->AddToScene(pScene, NScene::UPDATEPRIORITY_LOW);
  }

  void Apply(CPtr<ClientObjectBase> const &pBeginObj, CPtr<ClientObjectBase> const &pEndObj);

  virtual void ForAllMaterials(Render::IMaterialProcessor &proc);
	virtual void ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add);

  virtual void SetEnableCallback(PF_Core::IEffectEnableConditionCallback *pCallback) { pEnableCallback = pCallback; }

protected:
	ScopedPtr<PositionGenerator>  begin;
  ScopedPtr<PositionGenerator>  end;
  ScopedPtr<Object> sceneObj;
  CPtr<PF_Core::IEffectEnableConditionCallback> pEnableCallback;

  LightningFX lfx;
};

}
