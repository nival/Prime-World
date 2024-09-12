#pragma once

#include "stdafx.h"

#include "StatusEffect.h"

using namespace NScene;

namespace PF_Core
{

void StatusEffect::Attach(NScene::SceneObject *pObj)
{
  Attach(pObj, GetDBEffect().slot);
}

void StatusEffect::Attach(NScene::SceneObject *pObj, NDb::EStatusEffectSlot slot)
{
  if (GetDBEffect().slot == NDb::STATUSEFFECTSLOT_GENERAL)
  {
    BasicEffectAttached::Attach(pObj);
    return;
  }

  const char *locatorName = NDb::EnumToString(GetDBEffect().slot);
  const NScene::SceneObject::Locator *pL = pObj->FindLocator(locatorName);
  if (!pL)
  {
    // Message
    const char *rootCompName = pObj->GetRootComponent()->GetId().empty() ? "unknown" : pObj->GetRootComponent()->GetId().c_str();
    systemLog( NLogg::LEVEL_MESSAGE ) << "Locator: " << locatorName << " is not found in Scene Object with root component " 
      << rootCompName << " DBID: " << NDb::GetFormattedDbId( pObj->GetRootComponent()->GetDBID() ).c_str() << endl;
    pL = pObj->FindLocator(NDb::EnumToString(NDb::STATUSEFFECTSLOT_ABOVE));
    if (!pL)
    {
      BasicEffectAttached::Attach(pObj);
      return;
    }
  }

  AttachToLocator(pObj, locatorName);
}

} //namespace PF_Core

BASIC_REGISTER_CLASS( PF_Core::StatusEffect);
