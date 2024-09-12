#pragma once
#include "Window.h"
#include "ScrollArea.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
const int DEFAULT_BUTTON_REPEAT_RATE = 10;
const int DEFAULT_BUTTON_REPEAT_WAIT = 500;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ScrollBar : public Window
{
  NI_DECLARE_REFCOUNT_CLASS_1( ScrollBar, Window );

public:
  ScrollBar();

  void AttachScrollArea( ScrollArea* area );
  void UpdateScrollParameters();

  void SetButtonStep( int step );

  int GetNumPositions();
  void SetNumPositions( int _numPositions );

  int GetScrollPosition() { return position; }
  void SetScrollPosition( int pos );

  float GetScrollValue();
  void SetScrollValue( float x );

  DECLARE_LUA_TYPEINFO(ScrollBar);

private:
  NDb::UIScrollBarLayout * GetScrollBarLayout() { return GetLayoutClone<NDb::UIScrollBarLayout>(); }
  const NDb::UIScrollBarLayout * GetScrollBarLayout() const { return GetLayoutClone<NDb::UIScrollBarLayout>(); }

  // Images
  //@iA@TODO: сделать динамическое обновление стилей ImageComponent по Layout
  ImageComponent FirstButton;
  ImageComponent LeverArea;
  ImageComponent Lever;
  ImageComponent SecondButton;

  bool needUpdate;
  bool needForcedUpdate;

  // Sounds
  //NDb::DBFMODEventDesc eventButtonClick;
  //NDb::DBFMODEventDesc eventLeverJump;
  //NDb::DBFMODEventDesc eventLeverDrag;
  string eventButtonClick;
  string eventLeverJump;
  string eventLeverDrag;

  // General
  Weak<ScrollArea> attachedScrollArea;

  // Elements ( buttons and lever )
  enum EElement
  {
    ELEMENT_NONE,
    ELEMENT_FIRSTBUTTON,
    ELEMENT_LEVER,
    ELEMENT_SECONDBUTTON,
    ELEMENT_ITEMS_COUNT
  };

  int leverSize;
  int firstButtonSize;
  int secondButtonSize;

  struct SElementState
  {
    NDb::EUIScrollBarElementStyle value;
    NDb::EUIScrollBarElementStyle oldValue;
    SElementState()
      : value( NDb::UISCROLLBARELEMENTSTYLE_NORMAL )
      , oldValue( (NDb::EUIScrollBarElementStyle)-1 )
    {}
    void Updated()
    {
      oldValue = NDb::EUIScrollBarElementStyle( -1 );
    }
    bool Changed()
    {
      if ( value == oldValue )
        return false;
      oldValue = value;
      return true;
    }
  };

  SElementState firstButtonState;
  SElementState secondButtonState;
  SElementState leverState;

  SElementState *pFocusElementState;
  Point actionPos;
  bool actionPosTrace;

  // Position
  static const int nondiscreteNumPositions = 65536;
  int numPositions;
  int buttonStep;
  int position;

  int leverDragBase;

  int buttonRepeatRate;
  DWORD buttonRepeatWait;
  int buttonRepeatSide;

  // Helpers
  bool IsHorizontal() const { return GetScrollBarLayout()->scrollBarType == NDb::UISCROLLBARTYPE_HORIZONTAL; }
  int GetTotalSizeInt() const;
  int GetLeverCoordinateInt() const;
  EElement GetElementInt( int coordinate ) const;
  EElement GetElementByCoordsInt( const Point & screenCoords ) const;
  EElement GetElementFromElementStateInt( SElementState *pState );
  SElementState *GetElementStateInt( EElement element );
  void ModifyElementStateStyleInt( SElementState & elementState, NDb::EUIScrollBarElementStyle style, bool add );
  
  void SetElementImageMaterialInt( ImageComponent & image, const vector<NDb::Ptr<NDb::BaseUIMaterial>> & styles, NDb::EUIScrollBarElementStyle style );

  void ButtonStepInt( bool inc );
  void SetScrollPositionInt( int x, int y, int delta );

  // Events
  virtual void OnInit();
  virtual void OnDataChanged() { Window::OnDataChanged(); needForcedUpdate = true; }
  virtual void OnRefresh( float deltaTime );
  virtual void Render();

  virtual void OnEnable( bool _enable );

  virtual bool OnMouseMove( const Point & mouse );
  virtual void OnMouseOver( bool over, const Point & mouse );

  virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
  virtual bool OnMouseUp( EMButton::Enum mbutton );
  virtual bool OnScroll( int delta );

  virtual void OnTimeTrigger();

  virtual void OnMovedSized() { needUpdate = true; Window::OnMovedSized(); }

  virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace UI
