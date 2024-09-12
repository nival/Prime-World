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

  class CommonCombatController : public UI::IFSCommandListner, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( CommonCombatController, UI::IFSCommandListner, BaseObjectST );

  public:
    CommonCombatController( UI::FlashContainer2* flashContainer,AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler);

    // from UI::IFSCommandListner
    virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  private:
    Weak<UI::FlashContainer2> flashWnd;
    Weak<AdventureFlashInterface> flashInterface;
    Weak<IUIEventHandler> eventHandler;
  };

} //namespace NGameX
