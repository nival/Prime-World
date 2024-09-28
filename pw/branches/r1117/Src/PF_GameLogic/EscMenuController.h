#pragma once

#include "../UI/FSCommandListner.h"


namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}


namespace NGameX
{
  class AdventureFlashInterface;
  _interface IUIEventHandler;
  _interface IGameMenuMinigameActions;

  class EscMenuController : public UI::IFSCommandListner, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( EscMenuController, UI::IFSCommandListner, BaseObjectST );

  public:
    EscMenuController(UI::FlashContainer2* flashContainer, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler);

    void SetMenuMinigameInterface(IGameMenuMinigameActions * _gameMenuMinigameInterface) {gameMenuMinigameInterface = _gameMenuMinigameInterface;}

    // from UI::IFSCommandListner
    virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  private:
    Weak<AdventureFlashInterface>          flashInterface;
    Weak<IUIEventHandler>         eventHandler;
    CPtr<IGameMenuMinigameActions> gameMenuMinigameInterface;
  };

} //namespace NGameX
