/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PFClientNatureMap.h"
#include "../Terrain/Terrain.h"
#include "AdventureScreen.h"
#include "../Render/debugrenderer.h"

/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////

using namespace Render;

static bool g_pickAttackSpace = false;

namespace NGameX
{

  /////////////////////////////////////////////////////////////////////////////////
  // Methods
  /////////////////////////////////////////////////////////////////////////////////

PFClientNatureMap::PFClientNatureMap(const PF_Core::WorldObjectRef &pWorldObject) 
: PFClientObjectBase(pWorldObject)
{
  Subscribe();
}

Render::Texture2DRef PFClientNatureMap::GetTexture() /*const*/
{
  if (NWorld::PFWorldNatureMap const* pNatureMap = WorldObject())
    if (NWorld::PFWorld const* pWorld = pNatureMap->GetWorld())
      if (Terrain::Terrain* pTerrain = pWorld->GetScene()->GetTerrain())
        if (Terrain::NatureMapVisual* pMap = static_cast<Terrain::NatureMapVisual*>(&pTerrain->GetNatureMap()))
          return Render::Texture2DRef(pMap->GetTerrainMask());

  return Render::Texture2DRef();
}

void PFClientNatureMap::Update(float /*dt*/)
{
  if (g_pickAttackSpace)
    if (NWorld::PFWorldNatureMap const* pNatureMap = WorldObject())
      if (NWorld::PFWorld const* pWorld = pNatureMap->GetWorld())
        if (Terrain::Terrain* pTerrain = pWorld->GetScene()->GetTerrain())
          if (Terrain::NatureMapVisual* pMap = static_cast<Terrain::NatureMapVisual*>(&pTerrain->GetNatureMap()))
          {
            CRay const& cursorRay = NGameX::AdventureScreen::Instance()->GetCursorRay();
            CVec2 xzWorldPoint(cursorRay.ptOrigin.AsVec2D() + cursorRay.ptDir.AsVec2D() * (0.0f - cursorRay.ptOrigin.z) / cursorRay.ptDir.z);
            pMap->SetDebugPosition(xzWorldPoint);
          }
}

} // namespace

REGISTER_DEV_VAR( "nattackpick", g_pickAttackSpace, STORAGE_NONE );
