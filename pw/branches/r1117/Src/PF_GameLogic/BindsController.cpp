#include "StdAfx.h"
#include "BindsController.h"
#include "NivalInput/Binds.h"
#include "AdventureScreen.h"

namespace NGameX
{
  BindsController::BindsController()
    : currentEnabledFlags(0)
  {
  }

  void BindsController::SetEnabled(BindType type, bool enableBinds) 
  {
    if (IsFlagEnabled(type) == enableBinds)
      currentEnabledFlags ^= type;

    if (Input::Binds* const binds = Input::BindsManager::Instance()->GetBinds())
    {
      if (currentEnabledFlags != None)
      {
        binds->DeactivateSection("adventure_screen");
        binds->DeactivateSection("minigame");
      }
      else
      {
        if (NGameX::AdventureScreen::Instance()->IsPlayingMinigame())
          binds->ActivateSection("minigame");
        else
          binds->ActivateSection("adventure_screen");
      }
    }
  }

  bool BindsController::IsFlagEnabled(BindType type)
  {
    return ((currentEnabledFlags & type) == type);
  }
}