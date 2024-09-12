#include "stdafx.h"
#include "EffectGenSceneComponent.h"

#include "../System/RandomGen.h"
#include "../System/FastMath.h"
#include "../Render/debugrenderer.h"
#include "../Terrain/Terrain.h"
#include "EffectsPool.h"

namespace PF_Core
{

EffectGenSceneComponent::EffectGenSceneComponent( const NDb::EffectGenSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
	: SceneComponent(pObject, pObj, pos)
	, pDBObj(pObject)
  , pEffect(new EffectSelector(pDBObj->effect))
  , pScene(NULL)
  , timeToNextSpawn(0.f)
  , nextEffectIdx(0)
{
  localAABB.Set(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

  if (IsValid(pDBObj->posRandomizer))
  {
    NDb::RectangleRandomizer const *pRect = dynamic_cast<NDb::RectangleRandomizer const *>(pDBObj->posRandomizer.GetPtr());
    if (pRect)
    {
      localAABB.Set(pRect->min.x, pRect->max.x, pRect->min.y, pRect->max.y, -10.f, 10.f);
    }

    NDb::CircleRandomizer const *pCirc = dynamic_cast<NDb::CircleRandomizer const *>(pDBObj->posRandomizer.GetPtr());
    if (pCirc)
    {
      localAABB.Set(-pCirc->radius, pCirc->radius, -pCirc->radius, pCirc->radius, -10.f, 10.f);
    }
  }
  
  if( NGlobal::GetVar("precache_resource").GetInt64() && IsValid(pDBObj->effect) )
  {
    for (int i = 0; i < pDBObj->effect->effects.size(); ++i)
    {
      if (const NDb::BasicEffectStandalone * dbEffect = pDBObj->effect->effects[i].GetRawResourcePtr())
      {
        if (dbEffect->NeedReload())
        {
          NDb::Precache<NDb::BasicEffectStandalone>(dbEffect->GetDBID(), 20, true);
        }
      }
    }
  }
}

void EffectGenSceneComponent::OnAfterAdded(NScene::SceneObject *pObject)
{
  pScene = pObject->GetScene();
}

void EffectGenSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  // remember current scene
  pScene = pars.pScene;

  switch (pDBObj->generationPolicy)
  {
    case NDb::EFFECTGENPOLICY_START:
    {
      SpawnEffect();
	    // Disable this component
	    DisableStrong(true);
      break;
    }
    case NDb::EFFECTGENPOLICY_REGULAR:
    {
      timeToNextSpawn -= timeDiff;
      
      if (timeToNextSpawn < 0.f)
      {
        SpawnEffect();
        timeToNextSpawn = NRandom::Random(pDBObj->minPeriod, pDBObj->maxPeriod);
      }
      break;
    }
  }

  // update AABB
  {
    // Make result matrix
	  Matrix43 resultmatrix;
	  worldPlacement.GetMatrix( &resultmatrix );

    // Transform local AABB to global one
	  worldAABB.Transform( resultmatrix, localAABB );
    NI_ASSERT(worldAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );

	  // Update object's AABB
	  pars.objectAABB.Grow(worldAABB);
    NI_ASSERT(pars.objectAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );
  }
}

void EffectGenSceneComponent::RenderToQueue( class Render::BatchQueue& /*queue*/, const struct Render::SceneConstants& /*sceneConstants*/ )
{
  if (NScene::Need2DrawEntitiesWithoutVisual())
  {
    DebugRender();
  }
}

void EffectGenSceneComponent::DebugRender()
{
  using namespace Render;

  Color c(0xFF00FFFFUL);

  Matrix43 m;
  worldPlacement.GetMatrix(&m);

  if (IsValid(pDBObj->posRandomizer))
  {
    NDb::RectangleRandomizer const *pRect = dynamic_cast<NDb::RectangleRandomizer const *>(pDBObj->posRandomizer.GetPtr());
    NDb::CircleRandomizer const *pCirc = dynamic_cast<NDb::CircleRandomizer const *>(pDBObj->posRandomizer.GetPtr());

    if (pRect)
    {
      CVec3 p[4];

      p[0].x = pRect->min.x;   p[0].y = pRect->min.y;
      p[1].x = pRect->max.x;   p[1].y = pRect->min.y;
      p[2].x = pRect->max.x;   p[2].y = pRect->max.y;
      p[3].x = pRect->min.x;   p[3].y = pRect->max.y;

      for (int i = 0; i < 4; ++i)
      {
        p[i] = Transform(p[i], m);
      }

      DebugRenderer::DrawLine3D(p[0], p[1], c, c, true);
      DebugRenderer::DrawLine3D(p[1], p[2], c, c, true);
      DebugRenderer::DrawLine3D(p[2], p[3], c, c, true);
      DebugRenderer::DrawLine3D(p[3], p[0], c, c, true);
    }
    else if (pCirc)
    {
      DebugRenderer::DrawCircle3D(worldPlacement.pos, pCirc->radius, 24, c, true);
    }
  }
  else
  {
    DebugRenderer::DrawCross3D( m, 1.f, 1.f, c, true );
  }
}

void EffectGenSceneComponent::Deinit()
{
  if ( pDBObj->generationPolicy == NDb::EFFECTGENPOLICY_DEATH )
  {
    SpawnEffect();
  }
}

void EffectGenSceneComponent::SpawnEffect()
{
  if (!pScene || !IsValid(pDBObj->effect) || pDBObj->effect->effects.size() == 0)
  {
    return;
  }

  Placement place = worldPlacement;

  // randomize position
  if (IsValid(pDBObj->posRandomizer))
  {
    NDb::RectangleRandomizer const *pRect = dynamic_cast<NDb::RectangleRandomizer const *>(pDBObj->posRandomizer.GetPtr());
    if (pRect)
    {
      place.pos.x += NRandom::Random(pRect->min.x, pRect->max.x);
      place.pos.y += NRandom::Random(pRect->min.y, pRect->max.y);
    }

    NDb::CircleRandomizer const *pCirc = dynamic_cast<NDb::CircleRandomizer const *>(pDBObj->posRandomizer.GetPtr());
    if (pCirc)
    {
      float angle = NRandom::Random(FP_2PI);
      float r = NRandom::Random(pCirc->radius);

      place.pos.x += r * NMath::Cos(angle);
      place.pos.y += r * NMath::Sin(angle);
    }
  }

  // align position
  if ( pDBObj->alignment == NDb::EFFECTALIGNMENT_GROUND )
  {
    place.pos.z = pDBObj->offset;

    float h = 0.f;
    pScene->GetHeightsController().GetHeight(place.pos.x, place.pos.y, 1, &h, 0);
    place.pos.z += h;
  }

  // randomize direction
  if ( pDBObj->randomizeDirection )
  {
    place.rot = CQuat( NRandom::Random(FP_2PI), 0.f, 0.f );
  }

  CObj<BasicEffectStandalone> pE = EffectsPool::Get()->Retrieve<BasicEffectStandalone>( pEffect->GetNextEffect() );
  pE->SetPosition(place);
  pE->AddToScene(pScene);
}

void EffectGenSceneComponent::Attach( SceneComponent* toadd )
{
  if ( !toadd )
    return;

  SceneComponent* it = toadd;
  do 
  {
    it->SetJointIdx( -1 );
    if ( it->GetLocatorName().length() && !pDBObj.IsEmpty() && !pDBObj->locatorList.IsEmpty() )
    {
      for ( int i = 0; i < pDBObj->locatorList->locators.size(); i++ )
      {
        if ( pDBObj->locatorList->locators[i].name == it->GetLocatorName() )
        {
          const NDb::Locator& locator = pDBObj->locatorList->locators[i];
          const Placement& offset = locator.offset2.GetPlace();
          it->SetLocatorPos( offset.pos, offset.rot, offset.scale );
          it->SetLocatorName( it->GetLocatorName(), pDBObj->locatorList->locators[i].flags );
          break;
        }
      }
    }
    it = it->GetBrother();
  } while ( it && it != toadd );

  SceneComponent::Attach( toadd );
}

}

