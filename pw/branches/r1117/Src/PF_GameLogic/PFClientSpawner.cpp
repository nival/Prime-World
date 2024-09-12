/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PFClientSpawner.h"
#include "Minimap.h"
#include "ClientVisibilityHelper.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientNeutralCreepSpawner::PFClientNeutralCreepSpawner(const PF_Core::WorldObjectRef &pWO)
  : PFClientObjectBase(pWO)
  , pDBDesc()
  , position(VNULL3)
  , showMinimapIcon(false)
  , visibleLastFrame(false)
  , sharedVision(false)
  , sharedVisionShowMinimapIcon(false)
{
  if (NWorld::PFNeutralCreepSpawner const * pSpawner = WorldObject())
  {
    pDBDesc = pSpawner->GetDBDesc();
    position = pSpawner->GetSpawnPosition().pos;

    // Subscribe only if needed to show icons, because it is 
    // currently the only functionality of spawner's client object
    if (IsValid(pDBDesc) && pDBDesc->showMinimapIcon)
    {
      Subscribe();
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientNeutralCreepSpawner::Update(float timeDelta)
{
  UpdateVisibility();
  UpdateMinimap();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientNeutralCreepSpawner::UpdateVisibility()
{
  const NWorld::PFNeutralCreepSpawner* const pSpawner = WorldObject();

  if (!IsValid(pSpawner))
    return;

  // TODO: !!!
  sharedVision = ClientVisibilityHelper::IsSharedVisionMode();

  if (sharedVision)
  {
    const int count = pSpawner->GetSpawnedCreepsCount();

    sharedVisionShowMinimapIcon = (count > 0);
  }
  else
  {
    typedef NWorld::PFNeutralCreepSpawner::TCreeps TCreeps;

    // Check if we can see some creeps which belong to this spawner
    bool visibleThisFrame = false;

    const TCreeps& creeps = pSpawner->GetCreeps();

    TCreeps::const_iterator it = creeps.begin();
    TCreeps::const_iterator it_end = creeps.end();
    for(; it != it_end; ++it)
    {
      if (ClientVisibilityHelper::IsPointVisible((*it)->GetPos()))
      {
        visibleThisFrame = true;
        break;
      }
    }

    const int count = pSpawner->GetSpawnedCreepsCount();

    if (count > 0)
    {
      // Always show icon if there are creeps alive
      showMinimapIcon = true;
    }
    else
    {
      // If we reached spawn point for the first time and it's empty we need to disable minimap icon
      const bool spawnPointVisible = ClientVisibilityHelper::IsPointVisible(position.AsVec2D());

      if (spawnPointVisible || (visibleLastFrame && !visibleThisFrame))
      {
        showMinimapIcon = false;
      }
    }

    visibleLastFrame = visibleThisFrame;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientNeutralCreepSpawner::UpdateMinimap() const
{
  static DI_WEAK(Minimap) minimap;

  const bool shouldShowMinimapIcon = sharedVision
    ? sharedVisionShowMinimapIcon
    : showMinimapIcon;

  if (!shouldShowMinimapIcon)
    return;

  if (!IsValid(minimap))
    return;

  if (!IsValid(pDBDesc))
    return;

  minimap->AddObject(NDb::UNITTYPE_BUILDING, NDb::FACTION_NEUTRAL, position, pDBDesc->minimapIcon);
}

} // namespace NGameX
