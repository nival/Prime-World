#include "StdAfx.h"
#include "MinimapController.h"
#include "UIEventHandler.h"
#include "FlashFSCommands.h"
#include "AdventureFlashInterface.h"

#include "../UI/FlashContainer2.h"
#include "../UI/Defines.h"


namespace 
{
  static bool lockCamera = true;
  REGISTER_VAR( "lock_camera", lockCamera, STORAGE_USER );
}


namespace NGameX
{

MinimapController::MinimapController( UI::FlashContainer2 * wnd,  AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler )
: eventHandler(_eventHandler)
, flashInterface(_flashInterface)
{
  using namespace FlashFSCommands;
  wnd->AddFSListner(ConvertToString(MinimapMouseOver), this);
  wnd->AddFSListner(ConvertToString(MinimapMouseDown), this);
  wnd->AddFSListner(ConvertToString(SignalMouseClick), this);
  wnd->AddFSListner(ConvertToString(MinimapActionMove), this);
  wnd->AddFSListner(ConvertToString(MinimapMouseUp), this);
  wnd->AddFSListner(ConvertToString(CameraMouseClick), this);
}

void MinimapController::Init()
{
  eventHandler->LockCamera(lockCamera);
}

void MinimapController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  if (!IsValid(eventHandler))
    return;
    
  switch (ConvertToFSCommand(listenerID))
  {
  case MinimapMouseOver:
    {
      int mouseIn = 0;
      float x, y;
      sscanf_s(args,"%d %f %f", &mouseIn, &x, &y);
      eventHandler->MinimapOver(mouseIn, x, y);

      break;
    }
  case MinimapMouseDown:
    {
      int isLeft; 
      float x, y;
      sscanf_s(args,"%d %f %f", &isLeft, &x, &y);
      const UI::EMButton::Enum action = isLeft? UI::EMButton::Left: UI::EMButton::Right;
      eventHandler->MinimapActionBegin(action, x, y);

      break;
    }
  case MinimapMouseUp:
    {
      int isLeft; 
      float x, y;
      sscanf_s(args,"%d %f %f", &isLeft, &x, &y);
      const UI::EMButton::Enum action = isLeft? UI::EMButton::Left: UI::EMButton::Right;
      eventHandler->MinimapActionEnd(action, x, y);
      break;
    }
  case SignalMouseClick:
    {
      eventHandler->MinimapSignalBtnActionEnd();
      break;
    }
  case MinimapActionMove:
    {
      float x, y;
      sscanf_s(args,"%f %f", &x, &y);
      eventHandler->MinimapActionMove(x, y);
      break;
    }
  case CameraMouseClick:
    {
      int lock;
      sscanf_s(args,"%d", &lock);
      lockCamera = lock;
      eventHandler->LockCamera(lockCamera );
      break;
    }

  default:
    {
      NI_ALWAYS_ASSERT("something bad happened to the event listener")
    }
  }

}
}

NI_DEFINE_REFCOUNT(NGameX::MinimapController)