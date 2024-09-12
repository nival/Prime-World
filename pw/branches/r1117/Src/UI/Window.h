#pragma once


#include "Root.h"
#include "ImageComponent.h"
#include "ScreenLogicBase.h"
#include "Scripts.h"
#include "LuaEventResult.h"

#include "../Scripts/LuaSubclass.h"

#include "../libdb/ClonedPtr.h"


namespace EditorNative
{
  class WindowContact;
};


namespace NNameMap
{
  _interface IMap;
};


namespace UI
{


struct UIMessage
{
  string msg;
  string s;
  float n;

  UIMessage(): n(0) {}
  UIMessage( const char * _msg ): msg(_msg), n(0) {}
  UIMessage( const char * _msg, const char * _s, double _n = 0 ): msg(_msg), s(_s), n(_n) {}
};



namespace E3DWindowMode
{
  enum Enum
  {
    Nope,
    World,
    Billboard,
    AxisBillboard,
    DepthOnly,
  };
};



// For editor use mainly
namespace EVisibilityOverride
{
  enum Enum
  {
    Nope,
    ForceVisible,
    ForceInvisible
  };
};



namespace EWindowJobCode
{
  enum Enum { Ok, ReturnThis, ReturnNull };
};


_interface IWindowJob
{
  virtual EWindowJobCode::Enum BeforeChildren( Window * target ) = 0;
  virtual EWindowJobCode::Enum AfterChildren( Window * target ) = 0;
};




Window * CreateUIWindow( const NDb::UILayout * newDbLayout, const char * stateName, ScreenLogicBase * context, Window * parent, const char * nameOverride, bool doPostInit );



class Window : public BaseObjectST, public Lua::LuaSubclass
{
  NI_DECLARE_REFCOUNT_CLASS_2( Window, BaseObjectST, Lua::LuaSubclass );

  friend class ScreenLogicBase;
  friend class User;
  friend class EditorNative::WindowContact;

  friend Window * UI::CreateUIWindow( const NDb::UILayout * newDbLayout, const char * stateName, ScreenLogicBase * context, Window * parent, const char * nameOverride, bool doPostInit );

  // ---------------------------------------------
  //  construction
  // ---------------------------------------------
public:
  DECLARE_LUA_TYPEINFO( Window );

	Window();

  // ---------------------------------------------
  //  main
  // ---------------------------------------------
  void LoadLayout( const NDb::ClonedPtr<NDb::UILayout> &newLayout );

private:
  static Window * CreateUIWindowImpl( const NDb::ClonedPtr<NDb::UILayout> &newLayout, ScreenLogicBase * pContext );
  void LoadChildrenImpl();
  void PostInit();

private:
  NDb::ClonedPtr<NDb::UILayout> layout;
  string currentState;

#ifndef _SHIPPING
  string debugWindowName; //Only to simplify debugging UI
#endif //_SHIPPING

protected:
  template< class TLayout > 
  TLayout * GetLayoutClone( bool safe = true )
  {
    NI_ASSERT( !layout.IsEmpty(), "UI::Window::LoadLayout should be called first!" );

    TLayout * ptr = dynamic_cast<TLayout *>( layout.GetPtr() );
    NI_ASSERT( ptr || !safe, "Wrong layout type" );
    return ptr;
  }

  template< class TLayout > 
  const TLayout * GetLayoutClone( bool safe = true ) const
  {
    NI_ASSERT( !layout.IsEmpty(), "UI::Window::LoadLayout should be called first!" );

    const TLayout * ptr = dynamic_cast<const TLayout *>( layout.GetPtr() );
    NI_ASSERT( ptr || !safe, "Wrong layout type" );
    return ptr;
  }

public:
  const NDb::UILayout * GetWindowLayout( bool safe = true ) const { NI_ASSERT( layout || !safe, "" ); return layout; }
  const NDb::DBID & GetWindowLayoutDBID() const { return layout.GetSourcePtr()->GetDBID(); }

  const string& GetWindowName() const { return layout->name; }
	const NDb::EUIElementVAlign GetVAlign() const { return layout->vAlign; }
	const NDb::EUIElementHAlign GetHAlign() const { return layout->hAlign; }

private:
  bool toRemove;
  EVisibilityOverride::Enum visibilityOverride;

public:
	bool IsVisible() const;
	bool IsEnabled() const { return layout->enabled; }
  bool IsFullyVisible() const; //checks parent windows too
  bool IsFullyEnabled() const;

  void OverrideVisibility( EVisibilityOverride::Enum value ) { visibilityOverride = value; }

  void Enable( bool _enable );
	void ShowSilence( bool _show );
  void Show( bool _show );
  void PlayActivationSound();

	void SetTransparent( bool _transparent ) { layout->transparent = _transparent; }
	void SetCropping( bool _needCrop ) { layout->needCrop = _needCrop; }

  void SetState( const char * stateId );
  const string& GetState();

  // ---------------------------------------------
  //  position and size
  // ---------------------------------------------
private:
  enum ERecalcRectsReason { eRecalcByPos, eRecalcBySize, eRecalcByParent, eRecalcByChildrenShift };

  Rect winRect;
  Rect cropRect;
  Point childrenShift;

  E3DWindowMode::Enum mode3d;
  SHMatrix transform; //World matrix corrected to fit/align Window to required 3D rectangle
  SHMatrix transformRotated; // 'transform' rotated to achieve billboard effect
  CVec3 worldPosition; //Original world position
  CTPoint<float> win3DScale;
  float depthBias;

private:
  void ProcessWindowCoords( LinearCoord & resultOffs, LinearCoord & resultSize, NDb::EUIElementHAlign align, ERecalcRectsReason reason,
    LinearCoord prevOffs, LinearCoord newOffs, LinearCoord prevSize, LinearCoord newSize, LinearCoord prevParentSize, LinearCoord newParentSize );
  bool ChangeOffsetAndSize( ERecalcRectsReason reason, const Point & newOffs, const Point & newSize, const Point & prevParentSize, const Point & newParentSize );
  void RecalcRects( ERecalcRectsReason reason, const Point & newOffs, const Point & newSize, const Point & prevParentSize, const Point & newParentSize, const Rect & newParentWinRect, const Rect & parentCropRect, const Point & additionalOffs, bool forceNotify );
  void RecalcThisWindowRects( ERecalcRectsReason reason, const Point & newOffs, const Point & newSize, bool forceNotify  );
  void RecalcThisWindowRects( ERecalcRectsReason reason ) { RecalcThisWindowRects( reason, layout->location, layout->size, false ); }

public:
  const Rect & GetWindowRect() const { return winRect; }
  const Rect & GetCropRect() const { return cropRect; }

  void SetChildrenShift( LinearCoord dx, LinearCoord dy );
  const Point & GetChildrenShift() const { return childrenShift; }
  bool Is3D() const { return mode3d != E3DWindowMode::Nope; }
  //align обозначает точку на окне (в долях окна), которой оно будет "прикреплено" к точке в 3D
  void SetWorldPosition( const SHMatrix & position, const CVec2 & worldSize, const CVec2 & align = CVec2(0.5f, 0.5f), float _depthBias = 0.0f, E3DWindowMode::Enum mode = E3DWindowMode::World );
  void Stop3D();


protected:
  virtual void OnMovedSized() {}
  virtual void OnMovedSizedChild( Window *child ) {}

public:
  bool ConvertCoordinates( Point * coords );

public:
	const Point & GetPos() const { return layout->location; }
	const Point & GetSize() const { return layout->size; }

public:
  void SetLocation( LinearCoord x, LinearCoord y );
  void SetSize( LinearCoord width, LinearCoord height, bool forceNotify );

  // ---------------------------------------------
  //  opacity
  // ---------------------------------------------
private:
  int opacity;
  int resultOpacity; //Multiplied by parent windows opacity
  void UpdateOpacity();

public:
  int GetOpacity() { return resultOpacity; }
  void SetOpacity( float _opacity );

  // ---------------------------------------------
  //  hierarchy of windows
  // ---------------------------------------------
private:
  Weak<Window> parent;
  Weak<ScreenLogicBase>  context;
  typedef nstl::vector<Strong<Window>> TChildsArray;
  TChildsArray childs;

protected:
  bool RemoveSelf();
  virtual void OnAddChild( Window * child ) {}
  virtual void OnRemoveChild( Window * child ) {}

public:
  Window *GetBase();
  Window *GetParent() const { return parent; }
  Window *GetBaseParent();

  int GetChildrenCount() const { return childs.size(); }
  Window *GetChild( int index ) { NI_VERIFY( index >= 0 && index < childs.size(), "Index out of bounds", return 0 ); return childs[index]; }
  Window *GetChild( const char * name );
  Window *GetChildByMask( const char * name );
  Window* GetChildByName( const char * name ) { return GetChild(name); }
  Window* FindChild( const char * name ); //Recursive
  Window * Traverse( IWindowJob * job );

  const NDb::UILayout * GetRelatedLayout( const char * relatedLayout );
  Window * CreateChild( const char * name, const char * relatedLayout, LinearCoord x, LinearCoord y, LinearCoord w, LinearCoord h, int hAlign, int vAlign );
  void AddChild( Window * child );
  bool RemoveChild( const char * name );
  bool Close();

  void  SetContext( ScreenLogicBase * _context) { context = _context; }
  ScreenLogicBase* GetContext() const { NI_ASSERT( context, "" ); return context; }

private:
  bool needOrderReSort;
  float sortOrder;

public:
  void SetSortOrder( float order );
  float GetSortOrder() const { return sortOrder; }

  // ---------------------------------------------
  //  render and update
  // ---------------------------------------------
private:
  bool refreshNeeded;

  void StepInternal( float deltaTime );
  void CheckTimeTrigger( float deltaTime );
  void SortPriority();

protected:
  void Invalidate() { refreshNeeded = true; OnInvalidate(); } //Will call OnRefresh() next frame

  virtual void OnDataChanged();
  virtual void OnRefresh( float deltaTime ) {}
  virtual void OnInvalidate() {}
  virtual void Step( float deltaTime ) {} // regular update on each frame
  virtual void Render() {}

private:
  struct ESpecialMode { enum Enum { None, Exclude, DrawOnlySpecial }; };
  virtual void RenderInternal( Window * specialWindow, ESpecialMode::Enum mode = ESpecialMode::None );

public:
  void ForceUpdate() { OnRefresh(0); }

private:
  void RefreshAll( float deltaTime );
  void RecreateChildren();

public:
  void RefreshExternally();
  void InvalidateAll();

  // ---------------------------------------------
  //  cursor
  // ---------------------------------------------
public:
  bool GetCursor( string * name, const Point & screenCoords ) const;

protected:
  virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;

private:
  string cursorOverride;
public:
  void SetCursor( const char * cursorId ) { cursorOverride = cursorId; }

  // ---------------------------------------------
  //  events & focuses
  // ---------------------------------------------
public:
  bool IsInsideWindow( const Point & point ) const;
  void SetFocus( bool focus );
  bool IsFocused() const;

protected:
  virtual bool TestOpaque( int x, int y ) const { return true; }

  bool IsDraggable() const;

  virtual void OnInit();
  virtual void OnInitAfterChildrenCreated();
  virtual void OnEnable( bool _enable ) {}
  virtual void OnShow( bool _show ) {}
  virtual bool OnMouseMove( const Point & mouse ); //Внимание! Если окно возвращает false из OnMouseMove(), то оно не получит OnMouseOver()
  virtual void OnMouseOver( bool over, const Point & mouse );
  virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
  virtual bool OnMouseUp( EMButton::Enum mbutton );
  virtual bool OnDoubleClick( EMButton::Enum mbutton, const Point & point );
  virtual bool OnKeyboardFocus( bool gotFocus ) { return true; }
  virtual bool OnChar( int ch ) { return true; }
  virtual bool OnKeyPressed( int code, bool down ) { return true; }
  virtual bool OnScroll( int delta ) { return true; }
  //FIXME: obsolette, but used in EditBox
  virtual bool OnBind( const string & bind, float fDelta, bool *pResult ) { return false; }
  virtual bool OnActivationBind( const string & commandName ) { return false; }
  virtual void OnTimeTrigger() {}
  virtual void OnScreenFocus( bool focus ) {} //Вызывается только для базового окна экрана
  virtual void OnAction( EMButton::Enum mbutton ) {}

  virtual bool OnStartDrag( const char * id ) { return true; }
  virtual bool OnDropTest( const char * id, Window * dragTarget ) { return false; }
  virtual bool OnDropTarget( const char * id, bool entering, Window * dropTarget ) { return true; }
  virtual void OnDragMove( const char * id ) {}
  virtual void OnDrop( const char * id, Window * target ) {}
  virtual void OnCancelDrag( const char * id ) {}

private:
  void EventMouseOver( bool over, const Point & mouse );
  bool EventMouseMove( const Point & mouse );
  bool EventMouseDown( EMButton::Enum mbutton, const Point & point );
  bool EventMouseUp( EMButton::Enum mbutton );
  bool EventDoubleClick( EMButton::Enum mbutton, const Point & point );
  bool EventKeyboardFocus( bool gotFocus );
  bool EventChar( int ch );
  bool EventKeyPressed( int code, bool down );
  bool EventScroll( int delta );
  //FIXME: obsolette, but used in EditBox
  bool EventBind( const string & bind, const string & scriptFunction, float fDelta );
  bool EventActivationBind( const string & commandName );
  void EventTime( const string & scriptFunction );
  void EventTooltip( const Point & coords );
  void EventScreenFocus( bool focus );

protected:
  void EventAction( EMButton::Enum mbutton );

private:
  bool EventStartDrag( const char * id );
  bool EventDropTest( const char * id, Window * dragTarget );
  bool EventDropTarget( const char * id, bool entering, Window * dropTarget );
  void EventDragMove( const char * id );
  void EventDrop( const char * id, Window * target );
  void EventCancelDrag( const char * id );

  // ---------------------------------------------
  //  binds
  // ---------------------------------------------
private:
  bool bindResult;

public:
  void SetBind( const char * bind, const char * scriptFunction );
  void SetRepeatBind( const char * bind, const char * scriptFunction, int repeatStartDelay, int repeatDelay );

  // ---------------------------------------------
  //  time event
  // ---------------------------------------------
private:
  bool timeTriggerActive;
  float timeTriggerTimeLeft;
  string timeTriggerScriptFunction;

public:
  void SetTimeTrigger( float duration ); //Calls OnTimeTrigger() on time needed
  void SetScriptTimeTrigger( float duration, const char * scriptFunction ); //Calls specified script function on time

  // ---------------------------------------------
  //  messages
  // ---------------------------------------------
  typedef bool (Window::*TCPPMessageHandler)(Window *wndFrom, const UIMessage & msg);

  typedef hash_map<string, string> TScriptMsgHandlers;
  typedef hash_map<string, TCPPMessageHandler> TCPPMsgHandlers;

  TScriptMsgHandlers msgScriptHandlers;
  TCPPMsgHandlers msgCPPHandlers;
  bool ProcessMsgInt( Window * wndFrom, const UIMessage & msg, Window *exclude, bool forAll );
  bool SendMsgInt( Window * wndFrom, const UIMessage & msg, Window *exclude, bool forAll );

protected:
  virtual void EventMsg( const string & msg, const string & s, float n ) {}
  void SetMsgHandlerInt( const char * msg, const char * scriptFunction );

public:
  void SetCPPMsgHandler( const char * msg, TCPPMessageHandler handlerFunction );
  void SetMsgHandler( const char * msg, const char * scriptFunction );
  bool FireCustomUserMessage( const string & msg );
  void SendMsg( Window * wndFrom, const char * msg, const char * s = "", float n = 0 );
  void SendMsgAll( Window * wndFrom, const char * msg, const char * s = "", float n = 0 );

  // ---------------------------------------------
  //  commands
  // ---------------------------------------------
public:
  void PostCommand( const string & cmd );
  void PostCommandWide( const wstring & cmd );
  string GetConsoleVariable( const char * );

  // ---------------------------------------------
  //  texts and tooltip
  // ---------------------------------------------
private:
  wstring tooltipText;
public:
  wstring GetRelatedText( const char * id );
  void SetTooltipTextW( const wstring & text );
  wstring const &GetTooltipText() const { return tooltipText; }

  // ---------------------------------------------
  //  Text processing
  // ---------------------------------------------
  void AssignNameMap( NNameMap::IMap * nmap ) { nameMap = nmap; }
  NNameMap::IMap * GetNameMap() const { return nameMap; }

  Window * GetNameMapRedirect() const { return nameMapRedirect; }
  void RedirectNameMap( Window * window ) { nameMapRedirect = window; }

private:
  Weak<NNameMap::IMap>  nameMap;
  Weak<Window>          nameMapRedirect;
  
public:
  Point ScreenToLocal( const Point & screenPos );
  Point LocalToScreen( const Point & localPos );

public:
  float CallLuaSortCompareFunction( const char * scriptFunction, const char * s1, const char * s2 );

  DEFINE_LUA_READONLY_PROPERTY(name, string, layout->name);
  DEFINE_LUA_READONLY_PROPERTY(x,    int,    layout->location.x);
  DEFINE_LUA_READONLY_PROPERTY(y,    int,    layout->location.y);
  DEFINE_LUA_READONLY_PROPERTY(w,    int,    layout->size.x);
  DEFINE_LUA_READONLY_PROPERTY(h,    int,    layout->size.y);
  DEFINE_LUA_READONLY_PROPERTY(sx,   int,    winRect.x1);
  DEFINE_LUA_READONLY_PROPERTY(sy,   int,    winRect.y1);
  DEFINE_LUA_READONLY_PROPERTY(sw,   int,    winRect.GetSizeX());
  DEFINE_LUA_READONLY_PROPERTY(sh,   int,    winRect.GetSizeY());
  DEFINE_LUA_READONLY_PROPERTY(state,string, currentState);
};



int GetIndexFromString( const char * str );



typedef Window * ( TWindowConstructor )( void );
void RegisterControlConstructor( const string & typeName, TWindowConstructor * pConstructor );


template<class TResult>
static TResult *GetChildChecked( Window * parent, const char * name, bool recursive )
{
  NI_VERIFY( parent, "Parent not defined", return 0 );

  Window * wnd = recursive ? parent->FindChild( name ) : parent->GetChild( name );
  if( !wnd )
    return 0;

  TResult * result = dynamic_cast<TResult*>( wnd );
  NI_VERIFY( result, NStr::StrFmt( "Child window \"%s\" has invalid type", name ), return 0 );
  return result;
}

} //namespace UI




#define REGISTER_CONTROLTYPE( layoutType, controlType ) \
static Window * ConstructControl_##controlType##() \
{ \
  return new controlType; \
} \
static struct SHandlerRegister_##controlType \
{ \
  SHandlerRegister_##controlType() \
  { \
    RegisterControlConstructor( layoutType::GetTypeName(), &ConstructControl_##controlType ); \
  } \
} HandlerRegistrator_##controlType;

