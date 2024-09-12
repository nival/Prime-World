#include "stdafx.h"
#include "TraceGenSceneComponent.h"

#include "../Render/debugrenderer.h"
#include "../Terrain/Terrain.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Scene/WaterSceneComponent.h"
#include "EffectsPool.h"

#define TRACE_SCENEOBJ_ID 0x80000001

// Effect suppression tuning variables
static float g_nearRange = 1.f;
REGISTER_DEV_VAR( "eff_sup_near_range", g_nearRange, STORAGE_NONE );

static float g_farRange = 4.f;
REGISTER_DEV_VAR( "eff_sup_far_range", g_farRange, STORAGE_NONE );

static float g_maxSuppression = 0.6f;
REGISTER_DEV_VAR( "eff_sup_max_sup", g_maxSuppression, STORAGE_NONE );

NDebug::DebugVar<unsigned int> g_traceCount( "TraceCount", "Statistics" );

namespace
{

  inline bool RandomEvent(float probability)
  {
    return (NRandom::Random(0.f, 1.f) < probability);
  }

  float CalculateSpawnProbability(int effectId, CVec3 const &pos, NScene::IScene *pScene)
  {
    struct SuppressionFunc : public IObjectFunctor, public NonCopyable
    {
      int effectId;
      CVec3 const &pos;
      float suppression;

      SuppressionFunc(int effectId, CVec3 const &pos) : effectId(effectId), pos(pos), suppression(0.f) {}

      void operator()(RenderableSceneObj &obj)
      {
        NScene::SceneObject *so = dynamic_cast<NScene::SceneObject*>(&obj);

        if ( so && (so->GetOwnerID() == TRACE_SCENEOBJ_ID) )
        {
          float distance = fabs(so->GetPosition().pos - pos);
          suppression += g_maxSuppression * Clamp((g_farRange - distance) / (g_farRange - g_nearRange), 0.f, 1.f);
        }
      }
    } f(effectId, pos);

    // calculate suppression
    Render::AABB rangeBox(pos, CVec3(0.5f * g_farRange, 0.5f * g_farRange, 50.f));
    pScene->GetRenderScene()->ForAllObjectsInBBox(f, rangeBox);

    return Clamp(1.f - f.suppression, 0.f, 1.f);
  }
}

namespace PF_Core
{

Trace::Trace(const NDb::Trace *pDBObj, const string *locator)
  : pDBObj(pDBObj)
  , locator(locator)
  , pTerrainEffects(new ScopedPtr<EffectSelector>[ NDb::KnownEnum<NDb::ENatureType>::SizeOf() ])
{
  Reset(pWaterEffect, new EffectSelector(pDBObj->waterTrace));
  for (int i = 0; i < NDb::KnownEnum<NDb::ENatureType>::SizeOf(); ++i)
  {
    Reset( pTerrainEffects[i], new EffectSelector(pDBObj->terrainTrace[i]) );
  }
}

void Trace::SpawnEffect(TraceGenSceneComponent *pOwner, NScene::IScene *pScene)
{
  NDb::Ptr<NDb::BasicEffectStandalone> pEffect;
  
  // init placement with scene component placement
  Placement place = pOwner->GetWorldPlacement();
  
  // use locator if specified
  if (locator && pOwner->GetSceneObject())
  {
    NScene::Locator const *l = pOwner->GetSceneObject()->FindLocator(locator->c_str());

    if (l)
    {
      pOwner->GetSceneObject()->CalculateLocatorWorldPosition(*l, place.pos);
      place.scale.Mul(place.scale, l->locator.offset2.GetPlace().scale);
    }
  }

  // align position to ground
  if (pScene && pScene->GetTerrain())
  {
    pScene->GetTerrain()->GetHeight(place.pos.x, place.pos.y, &place.pos.z);
  }

  // check if we are in water
  struct WaterSCFinder : public NScene::WaterSceneComponent::WaterSCFunc
  {
    Render::AABB  search;
    NScene::WaterSceneComponent *found;
    float level;

    WaterSCFinder(CVec3 const &pos) : found(NULL), level(-99999.0f)
    {
      // build vertical stick-like bbox to test for intersection
      search.center = pos;
      search.halfSize = CVec3(0.f, 0.f, 100.f);
    }

    void operator() (NScene::WaterSceneComponent &wsc)
    {
      if ( wsc.GetWorldAABB().IsIntersectedBy(search) && wsc.GetWaterMesh()->GetLevel() > level )
      {
        found = &wsc;
        level = wsc.GetWaterMesh()->GetLevel();
      }
    }
  };

  WaterSCFinder f(place.pos);
  NScene::WaterSceneComponent::ForAllWaterSC(f);
  
  
  // are we in water ?
  if (f.found && pScene->IsPosInWater(place.pos.AsVec2D()))
  {
    pEffect = pWaterEffect->GetNextEffect();
    
    // align to water surface
    place.pos.z = f.found->GetWaterMesh()->GetLevel();
  }
  else
  {
    // select effect to generate
    int nature = NDb::NATURETYPE_N;
    if (pScene && pScene->GetTerrain())
    {
      nature = pScene->GetTerrain()->GetNatureMap().GetNature( place.pos.x, place.pos.y );
    }
    if ( nature > 2 || nature < 0 )
      nature = NDb::NATURETYPE_N;
    pEffect = pTerrainEffects[ nature ]->GetNextEffect();
  }

  if (IsValid(pEffect))
  {
/*
    // apply crowdness filter
    if (!RandomEvent(CalculateSpawnProbability( pEffect->GetObjectTypeID() & 0x7FFFFFFF,  place.pos, pScene )))
    {
      return;
    }
*/
    CObj<BasicEffectStandalone> pE = EffectsPool::Get()->Retrieve<BasicEffectStandalone>( pEffect );

    // use ownerId field to identify that this scene object represents trace effect
    pE->GetSceneObject()->SetOwnerID( TRACE_SCENEOBJ_ID );

    g_traceCount.AddValue(1);

    pE->SetPosition(place);
    pE->AddToScene(pScene);
  }
}

TraceGenSceneComponent::TraceGenSceneComponent( const NDb::TraceGenSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
	: SceneComponent(pObject, pObj, pos)
  , pDBObj(pObject)
  , pSceneObject(0)
  , forbidGenerateCounter(0)
{
  if ( IsValid(pDBObj->defaultTraces) )
  {
    Reset(defaultTrace, new Trace(pDBObj->defaultTraces, &pDBObj->defaultLocatorName));
  }
}

TraceGenSceneComponent::~TraceGenSceneComponent()
{
  map<int, Trace*>::iterator it;

  for (it = traceByAnim.begin(); it != traceByAnim.end(); ++it)
  {
    delete it->second;
  }
}

void TraceGenSceneComponent::OnAfterAdded(NScene::SceneObject *pObject)
{
  pSceneObject = pObject;

  if ( !pSceneObject )
    return;

  NScene::AnimatedSceneComponent *pAnimSC = dynamic_cast<NScene::AnimatedSceneComponent*>( pSceneObject->GetRootComponent() );

  if ( !pAnimSC )
    return;

  for (int i = 0; i < pDBObj->traceByAnim.size(); ++i)
  {
    const NDb::TraceInfo &ti = pDBObj->traceByAnim[i];

    if ( IsValid(ti.traces) )
    {
      int nodeID = pAnimSC->GetAG(true)->GetNodeIDByNameSlowQuite( ti.nodeName.c_str() );

      if ( nodeID != DIANGR_NO_SUCH_ELEMENT )
        traceByAnim[nodeID] = new Trace(ti.traces, &ti.locatorName);
    }
  }
}

void TraceGenSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  if (pars.pScene && pars.isClientVisible )
  {
    const bool hidden = IsHide();
    const bool forbidden = (forbidGenerateCounter != 0);
    if (!hidden && !forbidden)
      Generate(pars.pScene);
  }
  // Disable this component
  DisableStrong(true);
}

void TraceGenSceneComponent::RenderToQueue( class Render::BatchQueue& /*queue*/, const struct Render::SceneConstants& /*sceneConstants*/ )
{
  if (NScene::Need2DrawEntitiesWithoutVisual())
  {
    DebugRender();
  }
}

void TraceGenSceneComponent::DebugRender()
{
  using namespace Render;

  Matrix43 m;
  worldPlacement.GetMatrix(&m);
  DebugRenderer::DrawCross3D( m, 1.f, 1.f, Color(0xFFFF0000UL), true );
}

void TraceGenSceneComponent::Generate(NScene::IScene *pScene)
{
  Trace *t = Get(defaultTrace);

  // find appropriate trace for current animation
  if (pSceneObject)
  {
    NScene::AnimatedSceneComponent *pAnimSC = dynamic_cast<NScene::AnimatedSceneComponent*>( pSceneObject->GetRootComponent() );

    if (pAnimSC)
    {
      int node = pAnimSC->GetAG(true)->GetNearestNode();

      // this happens eventually on start when component gets updated otherwise that by events (sad but true)
      // we don't want to generate any traces in this case
      if (node == DIANGR_NO_SUCH_ELEMENT)
        return;

      map<int, Trace*>::iterator it = traceByAnim.find( node );

      if (it != traceByAnim.end())
      {
        t = it->second;
      }
    }
  }

  if (t)
  {
    t->SpawnEffect(this, pScene);
  }
}

}
