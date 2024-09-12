#include "stdafx.h"

#include "../System/Asserts.h"
#include "../Terrain/Terrain.h"
#include "SHGridCalculator.h"
#include "StaticSceneComponent.h"
#include "SceneObject.h"
#include "LightingScene.h"

namespace NScene
{

namespace
{

struct CollectObjectsFunc : public IObjectFunctor
{
  set<RenderableSceneObj*> objects;

  void operator()(RenderableSceneObj &obj)
  {
    objects.insert(&obj);
  }
};

struct CollectTerrainElementsFunc : public NonCopyable
{
  set<Terrain::TerrainElementId> elements;

  void operator()(Terrain::TerrainElementInfo const &info)
  {
    elements.insert(info.id);
  }
};

}

LightingScene::LightingScene( CPtr<IScene> scene, CPtr<Terrain::Terrain> terrain )
: m_scene(scene)
, m_terrain(terrain)
, m_bImmediateUpdate(false)
{
  NI_ASSERT(m_scene->GetGridConstants().valid, "Terrain must be initialized beforehand");
  Render::AABB aabb(0.5f * scene->GetGridConstants().worldSize, 0.5f * scene->GetGridConstants().worldSize);
  Render::GetLightsManager()->SetBounds(aabb);
}

void LightingScene::UpdateLighting()
{
  CollectObjectsFunc          cof;
  CollectTerrainElementsFunc  ctef;

  // gather all objects & terrain elements
  m_scene->GetRenderScene()->ForAllObjects(cof);
  m_terrain->GetElementManager().ForAllElementInfos(ctef);

  CalculateLighting(ctef.elements, cof.objects);
}

bool LightingScene::UpdateLighting(Render::AABB const& aabb)
{
  CollectObjectsFunc          cof;
  CollectTerrainElementsFunc  ctef;

  // gather objects & terrain elements that WILL BE affected by this light
  m_scene->GetRenderScene()->ForAllObjectsInBBox(cof, aabb);
  m_terrain->GetElementManager().ForAllElementInfosAABB(ctef, aabb);

  CalculateLighting(ctef.elements, cof.objects);

  // we can make immediate SH recalculation in this case (it's fast)
  NScene::SHGridCalculator::RecalculateSceneSH(m_scene->GetSHGrid(), *this, &aabb);
  UpdateSH(cof.objects);

  return true;
}

bool LightingScene::UpdateLighting(Render::AABB const& aabbFrom, Render::AABB const& aabbTo)
{
  // if bboxes intersect then build one united region
  if (aabbFrom.IsIntersectedBy(aabbTo))
  {
    Render::AABB region = aabbFrom;
    region.AddPoint(aabbTo.center - aabbTo.halfSize);
    region.AddPoint(aabbTo.center + aabbTo.halfSize);
    UpdateLighting(region);
  }
  else
  {
    // call recalculation for each region separately
    UpdateLighting(aabbFrom);
    UpdateLighting(aabbTo);
  }

  return true;
}

Render::PointLight *LightingScene::CreateLight()
{
  Render::PointLight *light = Render::GetLightsManager()->CreateLight();
  if (m_bImmediateUpdate)
    UpdateLighting(light->GetWorldAABB());

  return light;
}

void LightingScene::DeleteLight(Render::PointLight *light)
{
  NI_ASSERT(light, "Invalid pointer");
  Render::AABB aabb = light->m_lastUsedAABB;

  Render::GetLightsManager()->DeleteLight(light);

  if (m_bImmediateUpdate)
    UpdateLighting(aabb);
}

void LightingScene::UpdateLight(Render::PointLight *light)
{
  Render::GetLightsManager()->UpdateLight(light);

  if (m_bImmediateUpdate)
  {
    UpdateLighting(light->m_lastUsedAABB, light->GetWorldAABB());
    
    // save AABB as last used
    light->m_lastUsedAABB = light->GetWorldAABB(); 
  }
}

void LightingScene::UpdateObject(SceneObject *pObj)
{
  if (!m_bImmediateUpdate)
  {
    return;
  }

  CalculateLighting(*pObj);
}

void LightingScene::UpdateSH(set<RenderableSceneObj*> const &objects)
{
  set<RenderableSceneObj*>::iterator objIt = objects.begin();
  for (; objIt != objects.end(); ++objIt)
  {
    NScene::SceneObject *so = dynamic_cast<NScene::SceneObject*>( *objIt );
    if (so)
    {
      so->UpdateSH();
    }
  }
}

void LightingScene::CalculateLighting(set<Terrain::TerrainElementId> const &elements, set<RenderableSceneObj*> const &objects)
{
  // recalculate lighting for terrain elements
  m_terrain->GetGeometryManager().SetLightingScene(this);
  
  set<Terrain::TerrainElementId>::iterator teIt = elements.begin();
  for (; teIt != elements.end(); ++teIt)
  {
    m_terrain->GetGeometryManager().InvalidateElement(*teIt, Terrain::INVALID_LIGHTING);
  }

  // recalculate lighting for objects
  set<RenderableSceneObj*>::iterator objIt = objects.begin();
  for (; objIt != objects.end(); ++objIt)
  {
    NScene::SceneObject *so = dynamic_cast<NScene::SceneObject*>( *objIt );
    if (so)
    {
      CalculateLighting(*so);
    }
  }
}

}	// namespace EditorNative
