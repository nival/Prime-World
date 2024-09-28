#include "stdafx.h"

#include "LightningEffect.h"

namespace PF_Core
{

void LightningEffect::ForAllMaterials(Render::IMaterialProcessor &proc)
{
  if (lfx.GetMaterial())
  {
    proc(*lfx.GetMaterial());
  }
}

void LightningEffect::Object::Update(float timeDelta, bool isForcedUpdate )
{
  CVec3 p[2];

  if ( owner->GetPositionGeneratorBegin() &&
       owner->GetPositionGeneratorEnd() &&
       owner->GetPositionGeneratorBegin()->GetPos(p[0]) &&
       owner->GetPositionGeneratorEnd()->GetPos(p[1]) )
  {
    aabb.Calculate(2, p, sizeof(CVec3));

	  owner->lfx.SetWorldMatrix(IDENTITY_MATRIX);
    owner->lfx.Update(p[0], p[1], timeDelta);
		move();
  }
  else
  {
    // avoid assert in Scene::AddSceneObject
    aabb.Set(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
  }
}

void LightningEffect::Object::Render(Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter /*= NDb::GROUPFLAGS_ALL*/)
{
  CVec3 beginP, endP;

  // skip when casting shadows
  if (!(groupFlagsFilter & NScene::SceneComponent::GROUPFLAGS_CASTSHADOW))
    return;

  if ( owner->GetPositionGeneratorBegin() &&
       owner->GetPositionGeneratorEnd() )
  {
/*
    // Debug render
    if ( owner->GetPositionGeneratorBegin()->GetPos(beginP) &&
         owner->GetPositionGeneratorEnd()->GetPos(endP) )
    {
      Render::Color color(127, 127, 255, 255);
      Render::DebugRenderer::DrawLine3D(beginP, endP, color, color, true);
    }
*/
    if ( !owner->GetPositionGeneratorBegin()->IsPosVisible() && !owner->GetPositionGeneratorEnd()->IsPosVisible() )
      return;
		owner->lfx.RenderToQueue(queue);
  }
}

void LightningEffect::Init()
{
  BasicEffect::Init();
  Reset(sceneObj, new Object(this));

  lfx.SetMaterial(GetDBEffect().component->material.GetPtr());
  lfx.SetParameters(GetDBEffect().component->fxParams);
}

void LightningEffect::ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)
{
	LightningFX::Params params(lfx.GetParameters());
	params.color.Mad(GetDBEffect().component->fxParams.color, mul, add);
	lfx.SetParameters(params);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ClientObjPositionGenerator : public PositionGenerator
{
  ClientObjPositionGenerator(CPtr<ClientObjectBase> const &obj, const char *locator, bool checkVisibility )
    : obj(obj), locator(locator), checkVisibility(checkVisibility) {}

  virtual bool GetPos(CVec3 &pos) const
  {
    if ( !IsValid(obj) || !obj->GetSceneObject() )
      return false;

    NScene::SceneObject* pSO = obj->GetSceneObject();
    NScene::Locator const *pLocator = pSO->FindLocator( locator );
    if (pLocator)
    {
      pSO->CalculateLocatorWorldPosition(*pLocator, pos);
    }
    else
    {
      pos = pSO->GetPosition().pos;
    }
    return true; 
  }

  virtual bool IsPosVisible() const
  {
    if ( !checkVisibility )
      return true;

    if ( !IsValid(obj) || !obj->GetSceneObject() )
      return false;
    NScene::SceneObject *scObj = obj->GetSceneObject();
    return scObj->getVoxelGrid();
    //return scObj->IsRendered();
  }

protected:
  CPtr<ClientObjectBase> obj;
  const char *locator;
  bool checkVisibility;
};

void LightningEffect::Apply(CPtr<ClientObjectBase> const &pBeginObj, CPtr<ClientObjectBase> const &pEndObj)
{
  if ( !IsValid(pBeginObj) || !pBeginObj->GetSceneObject() || !pBeginObj->GetSceneObject()->IsInScene() || !IsValid(pEndObj) )
    return;

  SetPositionGeneratorBegin(new ClientObjPositionGenerator( pBeginObj, GetDBEffect().component->fromLocator.c_str(), GetDBEffect().controlledVisibility ));
  SetPositionGeneratorEnd(new ClientObjPositionGenerator( pEndObj, GetDBEffect().component->toLocator.c_str(), GetDBEffect().controlledVisibility ));

  if (Get(sceneObj))
  {
    AddToScene( pBeginObj->GetSceneObject()->GetScene() );
  }
}
}
