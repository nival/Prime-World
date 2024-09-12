#pragma once

#include "Scene.h"
#include "SceneObject.h"
#include "RenderableScene.h"
#include "../Terrain/Terrain.h"
#include "../Render/light.h"

namespace NScene
{

class LightingScene
{
private:
	CPtr<IScene> m_scene;
  CPtr<Terrain::Terrain> m_terrain;
  bool m_bImmediateUpdate;

public:
  LightingScene( CPtr<IScene> scene, CPtr<Terrain::Terrain> terrain );
  ~LightingScene() {}

  Render::PointLight *CreateLight();
  void UpdateLight(Render::PointLight *light);
  void DeleteLight(Render::PointLight *light);

  bool IsImmediateUpdateOn() const { return m_bImmediateUpdate; }
  void SetImmediateUpdate(bool bOn)
  {
    m_bImmediateUpdate = bOn;
    if (m_bImmediateUpdate)
    {
      UpdateLighting();
    }
  }

  void UpdateObject(SceneObject *pObj);

  void CalculateLighting(SceneObject &obj)
  {
    const IRenderableScene* const scene = m_scene->GetRenderScene();

    obj.CalculateLightingEx(scene->GetSceneConstants(NDb::LIGHTENVIRONMENT_DAY), NDb::LIGHTENVIRONMENT_DAY);
    obj.CalculateLightingEx(scene->GetSceneConstants(NDb::LIGHTENVIRONMENT_NIGHT), NDb::LIGHTENVIRONMENT_NIGHT);
  }

  void ResetTerrain()
  {
    m_terrain = m_scene->GetTerrain();
  }

  /////////////////////////////////////////////////////////////////////
  // interface for light-calculators

  const Render::SceneConstants& GetSceneConstants(const NDb::ELightEnvironment selector) const
  {
    const IRenderableScene* const scene = m_scene->GetRenderScene();

    return scene->GetSceneConstants(selector);
  }

  const Render::SceneConstants& GetSceneConstants() const
  {
    return GetSceneConstants(NDb::LIGHTENVIRONMENT_DAY);
  }

private:

  void UpdateLighting();
  bool UpdateLighting(Render::AABB const& aabb);
  bool UpdateLighting(Render::AABB const& aabbFrom, Render::AABB const& aabbTo);
  void UpdateSH(set<RenderableSceneObj*> const &objects);
  void CalculateLighting(set<Terrain::TerrainElementId> const &elements, set<RenderableSceneObj*> const &objects);
};

}	// namespace EditorNative
