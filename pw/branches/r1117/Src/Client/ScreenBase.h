#ifndef SCREENBASE_H_INCLUDED
#define SCREENBASE_H_INCLUDED

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../UI/Defines.h"
#include "../System/UpdateProcessor.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Input
{
  class Event;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
  class Window;
  class User;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainLoop
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsAppActive();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EScreenLayer
{
  enum Enum 
  {
    Lowest = 0,
    BelowNormal,  
    Normal,       // normal interfaces with scene etc.
    Topmost,      // permanent top-level windows ( chat etc. )
    AboveTopmost, // temorary top level windows ( chat/group invites, modal dialogs... ) 
    Highest,      // reserved for system screens ( tooltips, messages, console )
  };
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IScreenBase : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IScreenBase, IBaseInterfaceST );

  // called before screen added to screens stack
  virtual bool Init( UI::User * uiUser ) = 0;

  // PushScreenCommand arranges screen on top of screens with same priority
  virtual EScreenLayer::Enum GetScreenLayer() const = 0;

  // if screen says false on it it doesn't receive Step and events even if on top
  virtual bool IsInited() const = 0;

  // modal screens don't pass steps and events through themselves
  virtual bool IsModal() const = 0;

  // transparent screens pass draw through themselves
  virtual bool IsTransparent() const = 0;

  // next Step and CommonStep will be last for this screen, unless it returns false
  virtual bool OnBeforeClose() = 0;

  // at next step this screen will be hidden by topmost screen
  virtual void OnBeforeAddTopScreen( IScreenBase *pTopScreen ) = 0;

  // called when this screen becames topmost (within its layer of priority)
  virtual void OnBecameFront() = 0;

  // called when another screen becames topmost within its layer of priority
  // but this notifies _all_ screens regardless of their priority
  virtual void OnNewFront(IScreenBase * pNewFrontScreen) = 0;

  // this function called only for top screens until modal one
  virtual void Step( bool bAppActive ) = 0;

  // this function called for all screens (after Step called for top screen)
  virtual void CommonStep( bool bAppActive ) = 0;

  // this function called only for most top
  virtual void Draw( bool bAppActive ) = 0;

  // should return true if screen doesn't want this event to go any further (was processed or just filtered)
  virtual bool ProcessUIEvent( const Input::Event & event ) = 0;
  virtual bool ProcessSceneEvent( const Input::Event & event ) = 0;

  // Allow screen to change cursor
  virtual bool GetCursor( string * id, const UI::Point & screenCoords ) const = 0;

  // Update drag&drop target.. This is a strut to bypass multiple "Root Windows" per screen
  virtual UI::Window * FindDropTarget( const UI::Point & screenCoords, const char * id, UI::Window * dragTarget ) = 0;
};

} //namespace NMainLoop

#endif //SCREENBASE_H_INCLUDED
