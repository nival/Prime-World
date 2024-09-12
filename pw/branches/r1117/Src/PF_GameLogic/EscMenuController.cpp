#include "StdAfx.h"
#include "EscMenuController.h"

#include "AdventureFlashInterface.h"
#include "UIEventHandler.h"
#include "FlashFSCommands.h"

#include "../ui/FlashContainer2.h"
#include "GameMenuInterfaces.h"

namespace NGameX
{
EscMenuController::EscMenuController( UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler)
: eventHandler(_eventHandler)
, flashInterface(_flashInterface)
, gameMenuMinigameInterface(0)
{
  using namespace FlashFSCommands;

  flashContainer->AddFSListner(ConvertToString(EscMenuAbortLevel), this);
  flashContainer->AddFSListner(ConvertToString(EscMenuExitGame), this);
  flashContainer->AddFSListner(ConvertToString(MinigameMenuClosed), this);
  flashContainer->AddFSListner(ConvertToString(MinigameMenuOpened), this);
  flashContainer->AddFSListner(ConvertToString(DisableHotkeys), this);
  flashContainer->AddFSListner(ConvertToString(ReturnToLobby), this);
  flashContainer->AddFSListner(ConvertToString(SkipTutorial), this);
  flashContainer->AddFSListner(ConvertToString(EscMenuContinue), this);
  flashContainer->AddFSListner(ConvertToString(EscMenuShow), this);
}

void EscMenuController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  if (!IsValid(eventHandler))
    return;


  switch (ConvertToFSCommand(listenerID))
  {
  case EscMenuExitGame:
    {
      eventHandler->ExitGame( false );
      break;
    }
  case ReturnToLobby:
    {
      eventHandler->ExitGame( true );
      break;
    }
  case SkipTutorial:
    {
      eventHandler->SkipTutorial();
      break;
    }
  case DisableHotkeys:
    {
      int disable;
      sscanf_s(args,"%d",&disable);
      eventHandler->DisableHotkeys(disable);
      break;
    }
  case EscMenuAbortLevel:
    {
      if (IsValid(gameMenuMinigameInterface))
        gameMenuMinigameInterface->AbortMinigameLevel();
      break;
    }
  case MinigameMenuClosed:
    {
      if (IsValid(gameMenuMinigameInterface))
        gameMenuMinigameInterface->GameMenuClosed();
      break;
    }
  case MinigameMenuOpened:
    {
      if (IsValid(gameMenuMinigameInterface))
        gameMenuMinigameInterface->OnGameMenuPopup();
      break;
    }
  case EscMenuContinue:
    {
      eventHandler->ContinueGame();
      break;
    }
  case EscMenuShow:
    {
      eventHandler->OnEscMenuShow();
      break;
    }
 
  default:
    {
      NI_ALWAYS_ASSERT("something bad happened to the event listener")
    }
  }
}
}