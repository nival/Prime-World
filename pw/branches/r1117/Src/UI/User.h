#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "Defines.h"
#include "NivalInput/InputCommandRef.h"


namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ScreenLogicBase;
class Window;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class User : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( User, BaseObjectST )

public:
  User();

  //Обработка EventMouseOver() и тултипов
  void UpdateMouseMove( const Point & mouseCoords );
  void UpdateMouseOver( Window * newOverWindow, const Point & mousePos );
  Weak<Window> GetMouseOverWindow() const { return mouseOverWindow; }

  const Point & LastMouseCoords() const { return lastMouseCoords; }

  //Клавиатурный фокус
  void SetKeyboardFocus( Window * newFocusWindow );
  Weak<Window> GetKeyboardFocus() const { return keyboardFocus; }

  void Step( float deltaTime );
  void StartEvent( const Input::Event & event );
  void EndEvent( const Input::Event & event );

  //Принудительно показать тултип
  void ForceTooltip( const Point & mouseCoords );

  void SetMouseCapture( Window * target );
  Weak<Window> GetCaptureTraget() const { return mouseCaptureTarget; }

  bool StartDrag( Window * target, const char * id, int offsX, int offsY );
  void Drop( bool restoreLocation );
  void CancelDrag();
  void ModifyDragLimits( const Rect & limits ); //Passing Rect by value due to Lua-binding limitations

  const string & GetDragAndDropId() { return dragAndDropId; }
  Window * GetDragWindow() { return dragTarget; }

  void ImplUpdateDragAndDrop( Window * _dropTarget );

private:
  Input::CommandReference mouseMoveEventBind, mouseOutEventBind;

  Point           lastMouseCoords, lastQuantizedMouseCoords;

  bool            mouseOverWindowUpdated;
  Weak<Window>    mouseOverWindow;
  float           mouseOverTime;

  bool            tooltipShown;

  Weak<Window>    keyboardFocus;

  Weak<Window>    mouseCaptureTarget;

  // Drag and Drop
  string          dragAndDropId;
  Weak<Window>    dragTarget;
  Weak<Window>    dropTarget;
  bool            dropTargetIsValid;
  Rect            dragLimits;
  Point           dndTargetOriginalPos;
  Point           dragOffset;
  Point           lastDragPos;

  void ResetTooltipMouse();
  void RestoreDNDLocation();
  void ResetDragAndDrop();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //USER_H_INCLUDED
