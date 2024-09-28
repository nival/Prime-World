#pragma once
#ifndef LIGHTSMANAGER_H_INCLUDED
#define LIGHTSMANAGER_H_INCLUDED

#include "aabb.h"
#include "light.h"
#include "../System/AutoPtr.h"
#include "../System/nvector.h"
#include "../Scene/CollectionVG.h"

namespace Render
{

class LightsData
{
private:
#pragma pack(push,1)
  // shader constants
  struct Element
  {
    CVec3 pos;
    float factor;
    HDRColor color;
  };
#pragma pack(pop)
  
  vector<Element> elements;

public:
  void Initialize();
  void Terminate();

  UINT Fill(AABB const& aabb);  // returns number of point lights
  void Setup() const;
};

class LightsManager
{
public:
  LightsManager()
    : lightsDataFilterFlags(NDb::POINTLIGHTFLAGS_NONE)
  {
  }

  virtual ~LightsManager() { DeleteAllLights(); }

  void SetBounds(Render::AABB const& aabb);

  Render::PointLight *CreateLight();
  Render::PointLight *CreateLight(NDb::PointLightInfo const& lightInfo);
  void CreateLights(vector<NDb::PointLightInfo> const& lightInfos);
  void UpdateLight(Render::PointLight *light);
  void DeleteLight(Render::PointLight *light);
  void DeleteAllLights();

  template <class FUNC> void ForLightsAffectingBBox(Render::AABB const &aabb, FUNC &f) const
  {
    if (m_lightsVG)
      m_lightsVG->process(f, aabb);
  }

  void SetLightsDataFilterFlags(const NDb::PointLightFlags flags) { lightsDataFilterFlags = flags; }
  NDb::PointLightFlags GetLightsDataFilterFlags() const { return lightsDataFilterFlags; }
private:
  vector<Render::PointLight*> m_lights;
  AutoPtr<NScene::CollectionVG<Render::PointLight>> m_lightsVG;

  NDb::PointLightFlags lightsDataFilterFlags;
};

} // namespace Render

#endif // LIGHTSMANAGER_H_INCLUDED
