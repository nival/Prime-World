#include "stdafx.h"

#include "CommonCombatController.h"
#include "AdventureFlashInterface.h"
#include "../ui/FlashContainer2.h"
#include "UIEventHandler.h"
#include "FlashFSCommands.h"

namespace NGameX
{
CommonCombatController::CommonCombatController( UI::FlashContainer2* flashContainer,AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler )
: flashInterface(_flashInterface)
, eventHandler(_eventHandler)
, flashWnd(flashContainer)
{
  using namespace FlashFSCommands;

  if (!flashInterface || !eventHandler || !flashWnd)
    return;

  flashWnd->AddFSListner(ConvertToString(ResetTargetState), this);
}


void CommonCombatController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  using namespace FlashFSCommands;

  switch (ConvertToFSCommand(listenerID))
  {
  case ResetTargetState:
    {

      if (!eventHandler)
        break;
      
      eventHandler->ResetTargetState();

      break;
    }
  }
}

}

NI_DEFINE_REFCOUNT( NGameX::CommonCombatController )