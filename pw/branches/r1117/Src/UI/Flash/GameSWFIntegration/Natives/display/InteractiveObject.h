#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "DisplayObject.h"
#include "UI/Defines.h"


namespace avmplus
{
class ScriptObject;
class ContextMenuObject;
class InteractiveObjectClass;


class InteractiveObjectObject: public DisplayObjectObject
{
public:
  InteractiveObjectObject(InteractiveObjectClass * classType);
  InteractiveObjectObject(VTable* ivtable, ScriptObject* prototype);
  ~InteractiveObjectObject(void);

  // AS3 methods

  void set_focusRect(AvmBox _focusRect);
  AvmBox get_focusRect();

  void set_mouseEnabled(bool enabled) { mouseEnabled = enabled; }
  bool get_mouseEnabled() { return mouseEnabled; }

  void set_doubleClickEnabled(bool enabled) { doubleClickEnabled = enabled; }
  bool get_doubleClickEnabled() { return doubleClickEnabled; }

  void set_tabEnabled(bool enabled) { tabEnabled = enabled; }
  bool get_tabEnabled() { return tabEnabled; }

  void set_tabIndex(int index) { tabIndex = index; }
  int get_tabIndex() { return tabIndex; }

  void set_contextMenu(ContextMenuObject* cm);
  ContextMenuObject* get_contextMenu();

  void set_accessibilityImplementation(ScriptObject/*AccessibilityImplementation*/ * value);
  ScriptObject/*AccessibilityImplementation*/ * get_accessibilityImplementation();

  // own methods
public:
  virtual void OnFocusLoss( InteractiveObjectObject * nextFocused ) {}
  virtual bool OnFocusGain( InteractiveObjectObject * prevFocused ) { return false; }
  virtual void OnChar( int ch ) {}
  virtual void OnKeyPressed( int code, bool down ) {}

  virtual DisplayObjectObject* GetTopMostObject( const flash::SWF_POINT & point );

  virtual bool IsInteractive() const { return true; }

private:
  void Initialize();

  bool mouseEnabled;
  bool doubleClickEnabled;
  bool tabEnabled; // [TODO] implement functionality
  int tabIndex; // [TODO] implement functionality

  AvmBox  focusRect;

  DRCWB( ContextMenuObject* ) contextMenu;

  DECLARE_SLOTS_InteractiveObjectObject;
};


DECLARE_AS_CLASS(InteractiveObjectClass,DisplayObjectClass, InteractiveObjectObject)
}