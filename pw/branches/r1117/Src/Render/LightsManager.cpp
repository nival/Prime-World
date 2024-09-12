#include "stdafx.h"
#include "LightsManager.h"
#include "GlobalMasks.h"

namespace Render
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightsData::Initialize()
{
}

void LightsData::Terminate()
{
  elements.clear();
}

UINT LightsData::Fill(AABB const& aabb)
{
  // collect lights affecting this object
  PointLightsCollector clf(GetLightsManager()->GetLightsDataFilterFlags());

  GetLightsManager()->ForLightsAffectingBBox( aabb, clf );

  // fill array with attenuations
  typedef pair<Render::PointLight const *, float> LightInfo;
  vector<LightInfo> sorted(clf.lights.size());
  for (int i = 0, n = sorted.size(); i < n; i++)
  {
    Render::PointLight const* pLight = clf.lights[i];
    CVec3 vDistance = pLight->GetLocation() - aabb.center;
    float radius = Max(aabb.halfSize.x, Max(aabb.halfSize.y, aabb.halfSize.z));
    float distance = Max(0.0f, vDistance.Length() - radius);

    sorted[i].first = pLight;
    sorted[i].second = pLight->GetAttenuation(distance);
  }

  // sort by attenuation
  struct {
    bool operator()(LightInfo const& a, LightInfo const& b) {
      return a.second > b.second;
    }
  } lightIsCloser;
  nstl::sort(sorted.begin(), sorted.end(), lightIsCloser); // this must be slow, use insertion sort [2/25/2010 smirnov]

  // copy light parameters
  UINT lightsCount = Min(sorted.size(), POINTLIGHTSCOUNT);
  vector<Element>(lightsCount).swap(elements);
  for (UINT i = 0; i < lightsCount; i++)
  {
    PointLight const* pLight = sorted[i].first;
    float range = pLight->GetRange();

    Element& data = elements[i];
    data.pos = pLight->GetLocation();
    data.factor = (pLight->m_attenuationType == NDb::ATTENUATION_NONE || range <= 0) ? 0.0f : 1.0f / (range * range);
    data.color = pLight->m_diffuseColor * pLight->m_diffuseIntensity;
  }
  return lightsCount;
}

void LightsData::Setup() const
{
  // ensure there will be no problems with shader constants
  NI_STATIC_ASSERT(sizeof(Element) == 2 * sizeof(CVec4), LIGHT_DATA_SIZE_MISMATCH);
  NI_STATIC_ASSERT(sizeof(CVec4) == 4 * sizeof(float), CVEC4_SIZE_IS_STRANGE);

  if( elements.empty() )
    return;

  GetRenderer()->SetPixelShaderConstants(POINTLIGHTSDATA, 2 * elements.size(), &elements[0]);

  int k = 0;
  UINT regIdx = POINTLIGHTFACTOR;
  const int pointLightsCount = min(POINTLIGHTSCOUNT, elements.size());
  for(int i = 0; i < POINTLIGHTSCOUNT; i += 4)
  {
    CVec4 factors;
    int numElements = min(4, pointLightsCount - i);
    for(int j = 0; j < numElements; ++j)
      factors[j] = elements[k++].factor;

    GetRenderer()->SetPixelShaderConstantsVector4(regIdx++, factors);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightsManager::SetBounds(Render::AABB const& aabb)
{
  int nVoxelsX = 5, nVoxelsY = 5;
  Reset(m_lightsVG, new NScene::CollectionVG<Render::PointLight>(aabb, nVoxelsX, nVoxelsY, nVoxelsX * nVoxelsY));
  // re-add lights if any
  for (int i = 0, n = m_lights.size(); i < n; i++)
    m_lightsVG->add(m_lights[i]);
}

Render::PointLight* LightsManager::CreateLight()
{
  NI_VERIFY(m_lightsVG, "Dynamic lights voxel grid is not properly initialized", return NULL);
  Render::PointLight *light = new Render::PointLight;
  m_lights.push_back(light);
  m_lightsVG->add(light);
  return light;
}

Render::PointLight* LightsManager::CreateLight(NDb::PointLightInfo const& lightInfo)
{
  NI_VERIFY(m_lightsVG, "Dynamic lights voxel grid is not properly initialized", return NULL);
  Render::PointLight *light = new Render::PointLight;
  light->SetLocation(lightInfo.location);
  light->SetRange(lightInfo.range);
  light->m_lastUsedAABB = light->GetWorldAABB();
  light->m_attenuationType = lightInfo.attenuation;
  light->m_diffuseColor = lightInfo.diffuse;
  light->m_diffuseIntensity = lightInfo.diffuseIntensity;
  light->m_flags = lightInfo.flags;

  m_lights.push_back(light);
  m_lightsVG->add(light);
  return light;
}

void LightsManager::CreateLights(vector<NDb::PointLightInfo> const& lightInfos)
{
  m_lights.reserve(m_lights.size() + lightInfos.size());
  for (int i = 0, n = lightInfos.size(); i < n; i++)
    CreateLight(lightInfos[i]);
}

void LightsManager::DeleteLight(Render::PointLight *light)
{
  NI_ASSERT(light, "Invalid pointer");
  if (m_lightsVG)
    m_lightsVG->remove(light);

  vector<Render::PointLight*>::iterator it = m_lights.begin();
  bool bFound = false;
  for (; it != m_lights.end(); ++it)
  {
    if (*it == light)
    {
      delete light;
      m_lights.erase(it);
      bFound = true;
      break;
    }
  }

  NI_ASSERT(bFound, "Trying to delete non-existing light");
}

void LightsManager::DeleteAllLights()
{
  for (int i = 0; i < m_lights.size(); ++i)
  {
    if (m_lightsVG)
      m_lightsVG->remove(m_lights[i]);
    delete m_lights[i];
  }

  m_lights.clear();
}

void LightsManager::UpdateLight(Render::PointLight *light)
{
  NI_ASSERT(light, "Invalid pointer");
  light->move();
}

} // namespace Render

// end of LightsManager.cpp
