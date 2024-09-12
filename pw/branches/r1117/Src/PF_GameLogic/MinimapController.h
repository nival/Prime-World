#pragma once

#include "../UI/FSCommandListner.h"

namespace UI
{
  class FlashContainer2;
}


namespace NGameX
{

class AdventureFlashInterface;
_interface IUIEventHandler;

class MinimapController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( MinimapController, UI::IFSCommandListner, BaseObjectST );

public:
  MinimapController(UI::FlashContainer2 * wnd, AdventureFlashInterface * _flashInterface,  IUIEventHandler * _eventHandler);
  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  void Init();

private:
  Weak<IUIEventHandler>   eventHandler;
  Weak<AdventureFlashInterface> flashInterface;
};

}