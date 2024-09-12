#include "stdafx.h"

#include "UnitNameMap.h"
#include "PrecompiledTooltips.h"

#include "PFTalent.h"
#include "PFBuildings.h"
#include "PFMinigamePlace.h"
#include "PFChest.h"
#include "PFGlyph.h"
#include "PFHero.h"
#include "PFMaleHero.h"
#include "PFCreep.h"

#include "DieTimer.h"
#include "PlayerData.h"

namespace NGameX
{

NAMEMAP_BEGIN(TupleUnit<NWorld::PFAbilityData>)
  NAMEMAP_CUSTOM_SUBMAP(ability, const_cast<NWorld::PFAbilityData*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFTalent>)
  NAMEMAP_CUSTOM_SUBMAP(talent, const_cast<NWorld::PFTalent*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFBuilding>)
  NAMEMAP_CUSTOM_SUBMAP(building, const_cast<NWorld::PFBuilding*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFMinigamePlace>)
  NAMEMAP_CUSTOM_SUBMAP(building, const_cast<NWorld::PFMinigamePlace*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFBaseCreep>)
  NAMEMAP_CUSTOM_SUBMAP(creep, const_cast<NWorld::PFBaseCreep*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFBaseHero>)
  NAMEMAP_CUSTOM_SUBMAP(hero, const_cast<NWorld::PFBaseHero*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFBaseMaleHero>)
  NAMEMAP_CUSTOM_SUBMAP(male, const_cast<NWorld::PFBaseMaleHero*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFBaseUnit>)
  NAMEMAP_CUSTOM_SUBMAP(unit, const_cast<NWorld::PFBaseUnit*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFConsumable>)
  NAMEMAP_CUSTOM_SUBMAP(consumable, const_cast<NWorld::PFConsumable*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFConsumableChest>)
  NAMEMAP_CUSTOM_SUBMAP(chest, const_cast<NWorld::PFConsumableChest*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFGlyph>)
  NAMEMAP_CUSTOM_SUBMAP(glyph, const_cast<NWorld::PFGlyph*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<NWorld::PFNatureGlyph>)
  NAMEMAP_CUSTOM_SUBMAP(glyph, const_cast<NWorld::PFNatureGlyph*>(pObject), pObject)
NAMEMAP_END

NAMEMAP_BEGIN(TupleUnit<PlayerData>)
  NAMEMAP_CUSTOM_SUBMAP(playerData, const_cast<PlayerData*>(pObject), pObject)
NAMEMAP_END

// -----------------------------------------------------------

NAMEMAP_BEGIN(SingleValueNameMapInt)
  NAMEMAP_VAR_RO(value)
NAMEMAP_END

NAMEMAP_BEGIN(SingleValueNameMapFloat)
  NAMEMAP_VAR_RO(value)
NAMEMAP_END

NAMEMAP_BEGIN(SingleValueNameMapWstring)
  NAMEMAP_VAR_RO(value)
NAMEMAP_END


// -----------------------------------------------------------
NAMEMAP_BEGIN(WindowNameMap)
  NAMEMAP_INCLUDE(m_pNameMap)
NAMEMAP_END

WindowNameMap::WindowNameMap(Weak<UI::Window> const &pBaseWindow, bool assignToInvisiable) : m_baseWindow(pBaseWindow), m_pNameMap(NULL)
{
  if (IsValid(m_baseWindow))
    assignMeToWindows(m_baseWindow, assignToInvisiable);
}

void WindowNameMap::UpdateWindows(UnitNameMap *pMap)
{
  m_pNameMap = pMap;

  updateWindowsRecursive(m_baseWindow);

  m_pNameMap = NULL;
}

void WindowNameMap::assignMeToWindows(UI::Window *pRoot, bool assignToInvisible)
{
  NI_VERIFY(NULL != pRoot, "NULL pointer to window", return);

  UI::ImageLabel *pLabel = dynamic_cast<UI::ImageLabel*>(pRoot);
  if (pLabel && (pLabel->IsVisible() || assignToInvisible))
  {
    pLabel->AssignNameMap( this );
  }

  for (int i = 0, count = pRoot->GetChildrenCount(); i < count; ++i)
  {
    UI::Window *pChild = pRoot->GetChild(i);
    if (pChild && (pChild->IsVisible() || assignToInvisible))
      assignMeToWindows(pChild, assignToInvisible);
  }
}

void WindowNameMap::updateWindowsRecursive(UI::Window *pRoot)
{
  NI_VERIFY(NULL != pRoot, "NULL pointer to window", return);

  UI::ImageLabel *pLabel = dynamic_cast<UI::ImageLabel*>(pRoot);
  if (pLabel && this == pLabel->GetNameMap())
  {
    pLabel->ForceTextUpdate(UI::ETextUpdateMode::KeepNamemaps);
    pLabel->ForceUpdate();
  }

  for (int i = 0, count = pRoot->GetChildrenCount(); i < count; ++i)
  {
    UI::Window *pChild = pRoot->GetChild(i);
    if (pChild && pChild->IsVisible())
      updateWindowsRecursive(pChild);
  }
}

}