#ifndef DEFAULTSCREENBASE_H_INCLUDED
#define DEFAULTSCREENBASE_H_INCLUDED

#include "Client/ScreenBase.h"
#include "NivalInput/BindsContainer.h"

namespace UI
{
  class ScreenLogicBase;
  class Window;
};



namespace NMainLoop
{


class DefaultScreenBase : public NMainLoop::IScreenBase, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( DefaultScreenBase, IScreenBase, BaseObjectST );

public:
  DefaultScreenBase() : isScreenFocused(false), showOnlyOnTop(false) {}
  virtual ~DefaultScreenBase() {}

  //NMainLoop::IScreenBase:
  virtual bool Init( UI::User * uiUser );

  virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::Normal; }

  virtual bool IsInited() const { return true; }
  
  virtual bool IsModal() const { return false; }
  virtual bool IsTransparent() const { return false; }
  
  virtual bool OnBeforeClose();
  virtual void OnBeforeAddTopScreen( IScreenBase *pTopScreen ) {}
  virtual void OnBecameFront();
  virtual void OnNewFront(IScreenBase * pNewFrontScreen);

  virtual void Step( bool bAppActive );
  virtual void CommonStep( bool bAppActive ) {}

  virtual void Draw( bool bAppActive );

  virtual bool ProcessUIEvent( const Input::Event & message );
  virtual bool ProcessSceneEvent( const Input::Event & message );

  // Allow screen to change cursor
  virtual bool GetCursor( string * id, const UI::Point & screenCoords ) const;

  virtual UI::Window * FindDropTarget( const UI::Point & mouseCoords, const char * id, UI::Window * dragTarget );

  //service functions
  void CloseThisScreen();

  void SetLogic(UI::ScreenLogicBase * pLogic) { basicLogic = pLogic; }
  UI::ScreenLogicBase * GetLogic() { return basicLogic; }

  bool IsScreenFocused() const { return isScreenFocused; }
  void SetShowOnlyOnTop(bool hide) { showOnlyOnTop = hide; } //Only for screen's priority layer

  UI::Window * GetMainWindow();
  void ShowMainWindow( bool show );

protected:
  Input::BindsContainer eventsUI;
  Input::BindsContainer eventsScene;

private:
  Strong<UI::ScreenLogicBase> basicLogic;
  bool isScreenFocused; //is on top of the screens layer?
  bool showOnlyOnTop;
};

} // namespace NMainLoop

#endif //DEFAULTSCREENBASE_H_INCLUDED
