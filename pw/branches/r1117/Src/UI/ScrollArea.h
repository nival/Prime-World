#pragma once
#include "Window.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ScrollArea : public Window
{
  NI_DECLARE_REFCOUNT_CLASS_1( ScrollArea, Window );

public:
  ScrollArea();

  virtual void OnAddChild( Window *child );
  virtual void OnInit();
  virtual void EventMsg( const string & msg, const string & s, float n );

  float GetScrollX();
  float GetScrollY();

  void SetScroll( float sx, float sy );

  void SetHandleMsgForXScroll( string msgName );
  void SetHandleMsgForYScroll( string msgName );

  int GetScrollXSize() { return XLimits().outMax - XLimits().outMin + GetSize().x; }
  int GetScrollYSize() { return YLimits().outMax - YLimits().outMin + GetSize().y; }

  void SetScrollXLimits( float inMin, float inMax, int outMin, int outMax );
  void SetScrollYLimits( float inMin, float inMax, int outMin, int outMax );

  DECLARE_LUA_TYPEINFO(ScrollArea);

private:
  float scrollX, scrollY;

  NDb::UIScrollAreaLayout * GetScrollAreaLayout() { return GetLayoutClone<NDb::UIScrollAreaLayout>(); }

  virtual void OnScrollUpdated() {}
  void UpdateScrollAndShift( bool scrollLimitsChanged );

protected:
  //just a shortcuts
  NDb::UIScrollLimits & XLimits() { return GetScrollAreaLayout()->scrollXLimits; }
  NDb::UIScrollLimits & YLimits() { return GetScrollAreaLayout()->scrollYLimits; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace UI
