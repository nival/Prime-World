#pragma once

#include "DBRender.h"
#include "../Scene/VoxelGridObj.h"

namespace Render
{

class PointLight : public NScene::VoxelGridObj
{
private:
  Render::AABB  m_aabb;
  CVec3         m_location;
  float         m_range;

public:
  Render::AABB          m_lastUsedAABB;
  NDb::Attenuation      m_attenuationType;
  HDRColor              m_diffuseColor;
  float                 m_diffuseIntensity;
  NDb::PointLightFlags  m_flags;
  
  //////////////////////////////////////////////////////////
  // VoxelGridObj methods
  virtual const Render::AABB &GetWorldAABB(void) const { return m_aabb; }

  //////////////////////////////////////////////////////////
  PointLight()
    : m_attenuationType(NDb::ATTENUATION_NONE)
    , m_flags(NDb::POINTLIGHTFLAGS_NONE)
  {
    SetLocation(CVec3(0.f, 0.f, 0.f));
    SetRange(0.f);
    m_lastUsedAABB = m_aabb;
    m_diffuseColor = HDRColor(1.f, 1.f, 1.f, 1.f);
    m_diffuseIntensity = 1.f;
  }

  CVec3 const &GetLocation() const { return m_location; }
  void SetLocation(CVec3 const &location)
  {
    m_location = location;
    m_aabb.center = m_location;
  }

  float GetRange() const { return m_range; }
  void SetRange(float range)
  {
    m_range = range;
    m_aabb.halfSize = CVec3(m_range, m_range, m_range);
  }

  float GetAttenuation(float distance) const
  {
    if (m_range == 0.f || distance > m_range)
    {
      return 0.f;
    }

    float d = distance / m_range;

    switch (m_attenuationType)
    {
      case NDb::ATTENUATION_NONE:   return 1.f;
      case NDb::ATTENUATION_LINEAR: return 1.f - d;
      case NDb::ATTENUATION_FAST:   return (1.f - d) * (1.f - d);
      case NDb::ATTENUATION_SLOW:   return 1.f - d * d;
      case NDb::ATTENUATION_NORMAL: return 1.f + 2.f * d * d * d - 3.f * d * d;
    }

    return 0.f;
  }
};

inline static NDb::PointLightFlags GetPointLightFlagsForLightEnvironment(const NDb::ELightEnvironment lightEnvironment)
{
  switch (lightEnvironment)
  {
  case NDb::LIGHTENVIRONMENT_DAY:
    return NDb::POINTLIGHTFLAGS_DAY;
  case NDb::LIGHTENVIRONMENT_NIGHT:
    return NDb::POINTLIGHTFLAGS_NIGHT;
  default:
    return NDb::POINTLIGHTFLAGS_NONE;
  }
}

struct PointLightsCollector : public NonCopyable
{
  vector<const Render::PointLight*> lights;

  explicit PointLightsCollector(const NDb::PointLightFlags lightFlags = NDb::POINTLIGHTFLAGS_NONE)
    : lightFlags(lightFlags)
    , lights()
  {
  }

  explicit PointLightsCollector(const NDb::ELightEnvironment lightEnvironmentSelector)
    : lightFlags(GetPointLightFlagsForLightEnvironment(lightEnvironmentSelector))
    , lights()
  {
  }

  void operator()(const Render::PointLight& light)
  {
    if (light.m_flags & lightFlags)
      lights.push_back(&light);
  }

  NScene::VoxelGridObj::RenderGroups getRenderGroup() const { return Render::PointLight::SGetRenderGroup(); }
private:
  const NDb::PointLightFlags lightFlags;
};

}