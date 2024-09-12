#pragma once

#include "Defines.h"

#include "Scripts/ScriptMacroses.h"

#include "Scripts/LuaSubclass.h"

#include "NivalInput/InputCommandRef.h"
#include "NivalInput/BindsContainer.h"

#include "System/NameMap.h"


namespace NScript
{
class VariantValue;
}

namespace UI
{

class Window;
class User;
class WindowPointJob;

namespace EMButton { enum Enum; }

namespace EKeyboardInputEvent { enum Enum { Char, KeyDown, KeyUp }; }



class ScreenLogicBase : public BaseObjectST, public Lua::LuaSubclass, public NNameMap::IMap
{
  NI_DECLARE_REFCOUNT_CLASS_3( ScreenLogicBase, BaseObjectST, Lua::LuaSubclass, NNameMap::IMap )
  NAMEMAP_DECLARE

public:
  DECLARE_LUA_TYPEINFO( ScreenLogicBase );

  ScreenLogicBase();
  ~ScreenLogicBase();

  void SetUser( User * _user ) { user = _user; }
  User * User() const { NI_ASSERT( user, "" ); return user; }
  bool LoadScreenLayout( const string & screenId );
  bool ProcessMessage( const Input::Event & event );
  void StepWindows( float deltaTime );

  Window * GetBaseWindow() { return pBaseWindow; }

  void OnScreenFocus( bool focus );

  //@iA@TODO: Возможно, понадобится событие на потерю capture
  void CaptureMouse( Window * window );
  void ReleaseMouse();

  //virtual methods
  virtual void    Step( float deltaTime ) {}
  virtual void    RenderWindows(); //@iA@TODO: сделать эту функцию НЕвирутальной

  virtual bool    HasKeyboardFocus( const Window * window ) const;
  virtual void    SetKeyboardFocus( Window * window );

  virtual bool    GetCursor( string * id, const Point & screenCoords ) const;
  const Point&    GetLastMousePosition() const { return lastMousePosition; }
  const Point&    GetWindowRegardlessMousePosition() const { return windowRegardlessMousePosition; }
  bool            IsMouseEnabled() const { return isMouseEnabled; }

  virtual void    OnScreenResolutionChanged() {}

  virtual void    SetBind( const char * _bind, Window * window, const char * scriptFunction, DWORD repeatStartDelay, DWORD repeatDelay );
  virtual bool    CheckBind( const char * _bind );

  virtual void    CreateTextTooltip( const wstring & text, const UI::STooltipDesc & desc ) {}

  virtual void    OnLoadedScreenLayout() {}

  void            AddNameSubMap( const char * name, NNameMap::IMap * submap );
  void            RegisterNameMapWindow( NNameMap::IMap * nmap, UI::Window * wnd );
  void            UnregisterWindowFromNameMaps( UI::Window * wnd );
  void            UpdateWindowsByNameMap( NNameMap::IMap * nmap );

  //NNameMap::IMap
  virtual NNameMap::Map * ResolveNameMap( const char * name, int length, const char * args, int argsLength, void * prms, bool readonly );

  void QuitApplication(); //Lua
  void QuitApplicationEx( const nstl::string& exitCode );

  // Drag & Drop
  bool StartDrag( Window * target, const char * id, int offsX, int offsY );
  void Drop( bool restoreLocation );
  void CancelDrag();
  void ModifyDragLimits( Rect limits ); //Passing Rect by value due to Lua-binding limitations

  Window * ImplFindDropTarget( const Point & mouseCoords, const char * id, Window * dragTarget );

  template<class TWnd>
  TWnd * GetUISubWindow( Window * parent, const char * name, bool recursive = true, bool doAssert = true ) {
    if ( !parent )
      return 0;
    Window * wnd = recursive ? parent->FindChild( name ) : parent->GetChild( name );
    if ( !wnd ) {
      if ( doAssert )
        NI_ALWAYS_ASSERT( NStr::StrFmt( "UI layout '%s' not found in resource '%s'", name, parent->GetWindowLayoutDBID().GetFileName().c_str() ) );
      return 0;
    }
    TWnd * result = dynamic_cast<TWnd *>( wnd );
    NI_ASSERT( result, NStr::StrFmt( "UI layout '%s' from resource '%s' has invalid type", name, parent->GetWindowLayoutDBID().GetFileName().c_str() ) );
    return result;
  }

  template<class TWnd>
  TWnd * GetUIWindow( const char * name, bool recursive = true, bool doAssert = true ) {
    return GetUISubWindow<TWnd>( pBaseWindow, name, recursive, doAssert );
  }

  // Messages handling
private:
  Window * HelpProcessMouseMsg( const Input::SSysParams & sysParams, WindowPointJob * job, bool ignoreRectIfCaptured );

  bool ProcessMouseDown( const Input::SSysParams & sysParams, const EMButton::Enum & mbutton );
  bool ProcessMouseUp( const Input::SSysParams & sysParams, const EMButton::Enum & mbutton );
  bool ProcessMouseDblClick( const Input::SSysParams & sysParams, const EMButton::Enum & mbutton );

  //Events callbacks
  bool ProcessMsg_MouseMove( const Input::SSysParams & params );
  bool ProcessMsg_MouseOut( const Input::SSysParams & params );
  bool ProcessMsg_MouseDisabled( const Input::SSysParams & params );
  
  bool ProcessMsg_MouseWheelUp( const Input::SSysParams & params );
  bool ProcessMsg_MouseWheelDown( const Input::SSysParams & params );

  bool ProcessMsg_KeyboardEvent( const Input::SSysParams & params, const EKeyboardInputEvent::Enum & event );
  bool ProcessMsg_DragAndDropCancel();

  bool ProcessBind( const Input::Event & event );
  void ProcessBinds( DWORD deltaTime );

  bool ProcessTooltip( const Input::Event & event );

private:
  Weak<UI::User>  user;
  Point resolution;

  void CheckResolution();

protected:
  Strong<Window> pBaseWindow;
  Input::BindsContainer handlers;

  Point lastMousePosition;
  Point windowRegardlessMousePosition;
  bool isMouseEnabled;
  // Binds
private:
  enum { DEFAULT_BIND_REPEAT_RATE = 20 };

  struct SBindSubscriber
  {
    Weak<Window> pWindow;
    string scriptFunction;
    DWORD repeatStartTime;
    DWORD repeatTimeValue;

    DWORD repeatTimeLeft;

    SBindSubscriber() :
    repeatStartTime( 0 ),
    repeatTimeValue( 1000 / DEFAULT_BIND_REPEAT_RATE ),
    repeatTimeLeft( 0 )
    {}
  };

  bool HandleBindSubscriber( const SBindSubscriber & subscriber, const string & bind, float fDelta );

  struct SBind
  {
    Input::CommandReference bind;
    vector<SBindSubscriber> subscribers;

    SBind(): bind( "" ) {}
    SBind( const char * _bind ): bind( _bind ) {}
  };

  typedef hash_map<string, SBind> TBinds;
  TBinds binds;

  Input::CommandReference tooltipStart;

  typedef map<string, Weak<NNameMap::IMap>> TSubmaps;
  TSubmaps submaps;

  typedef set<Weak<Window>>  TWindowsSet;
  typedef set<Weak<NNameMap::IMap>>  TNameMapsSet;

  typedef map<Weak<NNameMap::IMap>, TWindowsSet>  TNameMappedWindows;
  typedef map<Weak<Window>, TNameMapsSet>  TAssignedNameMaps;

  TNameMappedWindows  nameMappedWindows; //Used to map changed name-maps into associated windows
  TAssignedNameMaps  assignedNameMaps; //Used to effectively clean up 'nameMappedWindows' from given window
};

}
