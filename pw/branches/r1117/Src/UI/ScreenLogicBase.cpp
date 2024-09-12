#include "Stdafx.h"
#include "ScreenLogicBase.h"

#include "User.h"
#include "Window.h"
#include "Resolution.h"
#include "Render/DebugRenderer.h"
#include "Render/TextureManager.h"
#include "Sound/EventScene.h"
#include "System/MainFrame.h"
#include "NameMappedWindow.h"
#include "DebugDraw.h"
#include "WindowPointJob.h"
#include "System/InlineProfiler.h"


namespace UI
{


static int UI_DRAGTRACE_MINDIST = 4;
static int UI_DRAGTRACE_MAXDIST = 0;



BEGIN_LUA_TYPEINFO_NOBASE( ScreenLogicBase )
  LUA_METHOD( QuitApplication )
  LUA_METHOD( StartDrag )
  LUA_METHOD( Drop )
  LUA_METHOD( CancelDrag )
  LUA_METHOD( ModifyDragLimits )
END_LUA_TYPEINFO( ScreenLogicBase )


NAMEMAP_BEGIN( ScreenLogicBase )
NAMEMAP_END




ScreenLogicBase::ScreenLogicBase() :
tooltipStart( "win_right_button_down" ), isMouseEnabled(false)
{
  handlers.AddSystemHandler( "win_mouse_move",          &ScreenLogicBase::ProcessMsg_MouseMove );
  handlers.AddSystemHandler( "win_mouse_out",           &ScreenLogicBase::ProcessMsg_MouseOut );
  handlers.AddSystemHandler( "win_mouse_disabled",      &ScreenLogicBase::ProcessMsg_MouseDisabled );

  handlers.AddSystemHandler( "win_left_button_down",    &ScreenLogicBase::ProcessMouseDown, EMButton::Left );
  handlers.AddSystemHandler( "win_left_button_up",      &ScreenLogicBase::ProcessMouseUp, EMButton::Left );
  handlers.AddSystemHandler( "win_left_button_dblclk",  &ScreenLogicBase::ProcessMouseDblClick, EMButton::Left );

  handlers.AddSystemHandler( "win_right_button_down",   &ScreenLogicBase::ProcessMouseDown, EMButton::Right );
  handlers.AddSystemHandler( "win_right_button_up",     &ScreenLogicBase::ProcessMouseUp, EMButton::Right );
  handlers.AddSystemHandler( "win_right_button_dblclk", &ScreenLogicBase::ProcessMouseDblClick, EMButton::Right );

  handlers.AddSystemHandler( "win_mouse_wheel_up",      &ScreenLogicBase::ProcessMsg_MouseWheelUp );
  handlers.AddSystemHandler( "win_mouse_wheel_down",    &ScreenLogicBase::ProcessMsg_MouseWheelDown );

  handlers.AddSystemHandler( "win_char",                &ScreenLogicBase::ProcessMsg_KeyboardEvent, EKeyboardInputEvent::Char );
  handlers.AddSystemHandler( "win_key_down",            &ScreenLogicBase::ProcessMsg_KeyboardEvent, EKeyboardInputEvent::KeyDown );
  handlers.AddSystemHandler( "win_key_up",              &ScreenLogicBase::ProcessMsg_KeyboardEvent, EKeyboardInputEvent::KeyUp );

  handlers.AddActivationHandler( "draganddrop_cancel",  &ScreenLogicBase::ProcessMsg_DragAndDropCancel );
}



ScreenLogicBase::~ScreenLogicBase()
{
  Render::UnloadTexturePool( this );
}



Window * ScreenLogicBase::HelpProcessMouseMsg( const Input::SSysParams & sysParams, WindowPointJob * job, bool ignoreRectIfCaptured )
{
  Point coords = ExtractMsgCoords( sysParams );
  job->SetPoint( coords );

  //Check for mouse capture and drag'n'drop target
  Weak<Window> captureTarget = user->GetCaptureTraget();

  if( !captureTarget )
    captureTarget = user->GetDragWindow();

  if( captureTarget )
  {
    if( captureTarget->IsFullyVisible() && captureTarget->IsFullyEnabled())
    {
      job->SetCaptureTarget( captureTarget, ignoreRectIfCaptured );
    }
    else
      user->SetMouseCapture( 0 );
  }

  return pBaseWindow->Traverse( job );
}


bool ScreenLogicBase::ProcessMouseDown( const Input::SSysParams & sysParams, const EMButton::Enum & mbutton )
{
  NI_ASSERT( user, "" );

  //window callback 
  struct Job : public WindowPointJob {
    EMButton::Enum mbutt;
    Job( EMButton::Enum _mbutton ) : WindowPointJob(), mbutt( _mbutton ) {}
    virtual bool Act( Window * target )
    {
      bool processed = target->EventMouseDown( mbutt, point );
      if ( Debug::MouseTraceEnabled() )
        Debug::AddRect( target->winRect, processed ? Debug::Color( 0, 255, 0 ) : Debug::Color( 255, 0, 255 ), 1.0f );
      return processed;
    }
  } job( mbutton );

  Window * wnd = HelpProcessMouseMsg( sysParams, &job, false );

  return wnd ? true : false;
}


bool ScreenLogicBase::ProcessMouseUp( const Input::SSysParams & sysParams, const EMButton::Enum & mbutton )
{
  NI_ASSERT( user, "" );

  //window callback 
  struct Job : public WindowPointJob {
    EMButton::Enum mbutt;
    Job( EMButton::Enum _mbutton ) : mbutt( _mbutton ) {}
    virtual bool Act( Window * target )
    {
      return target->EventMouseUp( mbutt );
    }
  } job( mbutton );

  Window * wnd = HelpProcessMouseMsg( sysParams, &job, true );

  return wnd ? true : false;
}



bool ScreenLogicBase::ProcessMouseDblClick( const Input::SSysParams & sysParams, const EMButton::Enum & mbutton )
{
  //Хороший шмать копипаста из ProcessMouseDown и ProcessMouseUp, различается только вызываемой функцией и булевым флагом
  //@iA@TODO: При дальнейшем наращивании кода можно будет засунуть все в функцию, принимающую указатель на метод класса... или шаблон
  NI_ASSERT( user, "" );

  struct Job : public WindowPointJob {
    EMButton::Enum mbutt;
    Job( EMButton::Enum _mbutton ) : mbutt( _mbutton ) {}
    virtual bool Act( Window * target )
    {
      return target->EventDoubleClick( mbutt, point );
    }
  } job( mbutton );

  Window * wnd = HelpProcessMouseMsg( sysParams, &job, false );

  return wnd ? true : false;
}



bool ScreenLogicBase::ProcessMsg_MouseMove( const Input::SSysParams & sysParams )
{
  NI_PROFILE_FUNCTION

  NI_ASSERT( user, "" );

  lastMousePosition.x = sysParams.GetMouseX();
  lastMousePosition.y = sysParams.GetMouseY();
  isMouseEnabled = true;
  
  //DebugTrace( "MouseMove: %d, %d", sysParams.GetMouseX(), sysParams.GetMouseY() );

  //window callback 
  struct Job : public WindowPointJob {
    virtual bool Act( Window * target )
    {
      if ( target->EventMouseMove( point ) )
      {
        if ( Debug::MouseTraceEnabled() )
          Debug::AddRect( target->winRect, Debug::Color( 255, 0, 0 ) );
        return true;
      }
      if ( Debug::MouseTraceEnabled() )
        Debug::AddRect( target->winRect, Debug::Color( 0, 0, 255 ) );
      return false;
    }
  } job;

  Window * wnd = HelpProcessMouseMsg( sysParams, &job, false );

  windowRegardlessMousePosition = lastMousePosition = ExtractMsgCoords( sysParams );

  if( wnd )
  {
    user->UpdateMouseOver( wnd, lastMousePosition );
  }

  return wnd ? true : false;
}

bool ScreenLogicBase::ProcessMsg_MouseOut( const Input::SSysParams & sysParams )
{
  NI_ASSERT( user, "" );
  
  windowRegardlessMousePosition = ExtractMsgCoords( sysParams );
  isMouseEnabled = true;
  //DebugTrace( "MouseOut: %d, %d", sysParams.GetMouseX(), sysParams.GetMouseY() );
  
  return false;
}

bool ScreenLogicBase::ProcessMsg_MouseDisabled( const Input::SSysParams & sysParams )
{
  NI_ASSERT( user, "" );
  isMouseEnabled = false;
  //DebugTrace( "MouseDisabled: %d, %d", sysParams.GetMouseX(), sysParams.GetMouseY() );

  return false;
}

bool ScreenLogicBase::ProcessMsg_MouseWheelUp( const Input::SSysParams & sysParams )
{
  NI_ASSERT( user, "" );
  Weak<Window> overWnd = user->GetMouseOverWindow();
  
  return overWnd ? overWnd->EventScroll( -1 ) : false;
}



bool ScreenLogicBase::ProcessMsg_MouseWheelDown( const Input::SSysParams & sysParams )
{
  NI_ASSERT( user, "" );
  Weak<Window> overWnd = user->GetMouseOverWindow();
  
  return overWnd ? overWnd->EventScroll( +1 ) : false;
}



bool ScreenLogicBase::ProcessMsg_KeyboardEvent( const Input::SSysParams & params, const EKeyboardInputEvent::Enum & event )
{
  NI_ASSERT( user, "" );
  Weak<Window> focus = user->GetKeyboardFocus();

  if( !focus )
    return false;

  if( !focus->IsFullyVisible() )
    return false;

  switch ( event )
  {
    case EKeyboardInputEvent::Char:
      return focus->EventChar( params.first );

    case EKeyboardInputEvent::KeyDown:
      return focus->EventKeyPressed( params.first, true );

    case EKeyboardInputEvent::KeyUp:
      return focus->EventKeyPressed( params.first, false );

    default:
      return false;
  }
}



bool ScreenLogicBase::ProcessMsg_DragAndDropCancel()
{
  NI_ASSERT( user, "" );
  if ( user->GetDragAndDropId().empty() )
    return false;

  user->CancelDrag();
  return true;
}



bool ScreenLogicBase::ProcessBind( const Input::Event & event )
{
  NI_PROFILE_FUNCTION

  if ( pBaseWindow )
    if ( event.Type() == Input::EEventType::Activation )
      if ( pBaseWindow->EventActivationBind( event.Command()->Name() ) )
        return true;

  bool processed = false;
  for ( TBinds::iterator it = binds.begin(); it != binds.end(); ++it )
  {
    SBind & bind = it->second;
    if ( bind.bind.ProcessEvent( event ) )
    {
      float fDelta = bind.bind.RetrieveDelta();

      for ( int s = 0; s < bind.subscribers.size(); ++s )
      {
        SBindSubscriber & bsub = bind.subscribers[s];
        if ( !bsub.pWindow )
        {
          bind.subscribers.erase( bind.subscribers.begin() + s );
          --s;
          continue;
        }

        if ( HandleBindSubscriber( bsub, it->first, fDelta ) )
          processed = true;

        bsub.repeatTimeLeft = bsub.repeatStartTime;
      }
    }
  }
  return processed;
}



void ScreenLogicBase::ProcessBinds( DWORD deltaTime )
{
  for ( TBinds::iterator it = binds.begin(); it != binds.end(); ++it )
  {
    SBind & bind = it->second;

    if ( !bind.bind.IsActiveNow() )
      continue;

    for ( int s = 0; s < bind.subscribers.size(); ++s )
    {
      SBindSubscriber & bsub = bind.subscribers[s];
      if ( !bsub.pWindow )
      {
        bind.subscribers.erase( bind.subscribers.begin() + s );
        --s;
        continue;
      }

      if ( bsub.repeatTimeValue == 0 )
        continue;

      if ( bsub.repeatTimeLeft > deltaTime )
      {
        bsub.repeatTimeLeft -= deltaTime;
        continue;
      }

      HandleBindSubscriber( bsub, it->first, 0 );

      const DWORD timeOverflow = deltaTime - bsub.repeatTimeLeft;
      if ( timeOverflow > bsub.repeatTimeValue )
        bsub.repeatTimeLeft = 0;
      else
        bsub.repeatTimeLeft = bsub.repeatTimeValue - timeOverflow;
    }
  }
}



bool ScreenLogicBase::ProcessTooltip( const Input::Event & event )
{
  NI_ASSERT( user, "" );
 
  if ( tooltipStart.ProcessEvent( event ) )
  {
    Point coords = ExtractMsgCoords( event.SysParams() );
    user->ForceTooltip( coords );
  }

  return false;
}



bool ScreenLogicBase::ProcessMessage( const Input::Event & event )
{
  NI_PROFILE_FUNCTION

  if ( !pBaseWindow )
    return false;

  bool processed( false );

  if ( !processed )
    processed = ProcessTooltip( event );

  if ( !processed )
    processed = ProcessBind( event );

  if ( !processed )
    processed = handlers.ProcessEvent( event, this );

  return processed;
}



void ScreenLogicBase::StepWindows( float deltaTime )
{
  if ( !pBaseWindow )
    return;

  if ( deltaTime > 0 )
  {
    pBaseWindow->StepInternal( deltaTime );

    ProcessBinds( (DWORD)( deltaTime * 1e3f ) );
  }
}



void NewFrameForAllObjectViewProviders();

void ScreenLogicBase::RenderWindows()
{
  NI_PROFILE_FUNCTION_MEM

  if ( !pBaseWindow )
    return;

  NewFrameForAllObjectViewProviders();

  CheckResolution();

  if ( pBaseWindow->IsVisible() )
  {
    NI_ASSERT( user, "" );
    Window * dragWindow = user->GetDragWindow() ? user->GetDragWindow() : 0;

    if( !dragWindow )
      pBaseWindow->RenderInternal( dragWindow );
    else
    {
      //TODO: do no double rendering if 'dragWindow' is not from this logic
      pBaseWindow->RenderInternal( dragWindow, Window::ESpecialMode::Exclude );
      pBaseWindow->RenderInternal( dragWindow, Window::ESpecialMode::DrawOnlySpecial );
    }
  }
}



void ScreenLogicBase::OnScreenFocus(bool focus)
{
  if ( !pBaseWindow )
    return;

  pBaseWindow->EventScreenFocus( focus );
}



void ScreenLogicBase::CaptureMouse( Window * window )
{
  user->SetMouseCapture( window );
}



void ScreenLogicBase::ReleaseMouse()
{
  user->SetMouseCapture( 0 );
}



void ScreenLogicBase::CheckResolution()
{
  if ( !pBaseWindow )
    return;

  const Point & screenResolution = UI::GetScreenResolution();
  const Point & uiResolution = UI::GetUIScreenResolution();

  bool resEqual = ( fabs( screenResolution.x - resolution.x ) < FLT_EPSILON ) &&
                  ( fabs( screenResolution.y - resolution.y ) < FLT_EPSILON ); 

  if ( resEqual || fabs( screenResolution.x ) < FLT_EPSILON || fabs( screenResolution.y ) < FLT_EPSILON )
    return;

  resolution = screenResolution;
  pBaseWindow->SetSize( uiResolution.x, uiResolution.y, true );

  OnScreenResolutionChanged();
}



bool ScreenLogicBase::LoadScreenLayout( const string & screenId )
{
  NI_PROFILE_FUNCTION_MEM

  PushDXPoolGuard dxPool("UI");

  NI_ASSERT( user, "" );

  NDb::Ptr<NDb::UIBaseLayout> pLayout = GetScreenLayout( screenId );
  NI_VERIFY( pLayout, NStr::StrFmt( "Screen layout %s not found", screenId ), return false);
  NI_DATA_ASSERT( pLayout->location == Point( 0, 0 ), NStr::StrFmt( "Invalid screen '%s' layout location (%i, %i)", screenId.c_str(), pLayout->location.x, pLayout->location.y ) );
  NI_DATA_ASSERT( pLayout->size == Point( UI_RESOLUTION_WIDTH, UI_RESOLUTION_HEIGHT ), NStr::StrFmt( "Invalid screen '%s' layout size %ix%i", screenId.c_str(), pLayout->size.x, pLayout->size.y ) );
  NI_DATA_ASSERT( pLayout->hAlign == NDb::UIELEMENTHALIGN_LEFT && pLayout->vAlign == NDb::UIELEMENTVALIGN_TOP, NStr::StrFmt( "Invalid screen '%s' layout alignment, must be Left-Top", screenId.c_str() ) );

  pBaseWindow = CreateUIWindow( pLayout, 0, this, 0, 0, true );
  pBaseWindow->SetSize( GetUIScreenResolution().x, GetUIScreenResolution().y, false );

  // this function for derived classes.
  // Maybe derived class wants to do something after we have loaded the screen layout.
  if ( pBaseWindow )
  {
    OnLoadedScreenLayout();
    pBaseWindow->CallHandler( "OnLoadedScreenLayout" );

    NSoundScene::EventStart( pBaseWindow->GetWindowLayout()->soundShow );
  }

  return pBaseWindow;
}



void ScreenLogicBase::SetKeyboardFocus( Window * window  )
{
  if ( user )
    user->SetKeyboardFocus( window );
}



bool ScreenLogicBase::HasKeyboardFocus( const Window * window ) const
{
  if( !window )
    return false;

  if( !window->IsFullyVisible() || !window->IsFullyEnabled() )
    return false;

  NI_ASSERT( user, "" );
  return ( user->GetKeyboardFocus() == window );
}



bool ScreenLogicBase::GetCursor( string * id, const Point & screenCoords ) const
{
  NI_ASSERT( user, "" );

  //window callback 
  struct Job : public WindowPointJob {
    string * cursorId;
    Job( string * id, const Point & coords ) : WindowPointJob( coords ), cursorId( id ) {}
    virtual bool Act( Window * target )
    {
      return target->GetCursor( cursorId, point );
    }
  } job( id, screenCoords );

  Window * wnd = pBaseWindow->Traverse( &job );

  return wnd ? true : false;
}



void ScreenLogicBase::SetBind( const char * _bind, Window * window, const char * scriptFunction, DWORD repeatStartDelay, DWORD repeatDelay )
{
  if ( !window )
    return;

  TBinds::const_iterator it = binds.find( _bind );
  if ( it == binds.end() )
    binds[ _bind ] = SBind( _bind );

  SBind & bind = binds[ _bind ];

  vector<SBindSubscriber> & subs = bind.subscribers;
  for ( int i = 0;i < subs.size(); ++i )
  {
    if ( subs[i].pWindow == window )
    {
      subs[i].scriptFunction = scriptFunction;
      subs[i].repeatStartTime = repeatStartDelay;
      subs[i].repeatTimeValue = repeatDelay;
      if ( subs[i].repeatTimeLeft > repeatDelay )
        subs[i].repeatTimeLeft = repeatDelay;
      return;
    }
  }

  subs.push_back();
  SBindSubscriber & snew = subs.back();
  snew.pWindow = window;
  snew.scriptFunction = scriptFunction;
  snew.repeatStartTime = repeatStartDelay;
  snew.repeatTimeLeft = repeatDelay;
  snew.repeatTimeValue = repeatDelay;
}



bool ScreenLogicBase::CheckBind( const char * _bind )
{
  TBinds::const_iterator it = binds.find( _bind );
  if ( it == binds.end() )
    binds[ _bind ] = SBind( _bind );

  return binds[ _bind ].bind.IsActiveNow();
}



bool ScreenLogicBase::HandleBindSubscriber( const SBindSubscriber & subscriber, const string & bind, float fDelta )
{
  if ( !subscriber.pWindow )
    return false;
  return subscriber.pWindow->EventBind( bind, subscriber.scriptFunction, fDelta );
}



void ScreenLogicBase::AddNameSubMap( const char * name, NNameMap::IMap * submap )
{
  submaps[name] = submap;
}



void ScreenLogicBase::RegisterNameMapWindow( NNameMap::IMap * nmap, UI::Window * wnd )
{
  nameMappedWindows[nmap].insert( wnd );
  assignedNameMaps[wnd].insert( nmap );

  //TODO: Periodically clean dead windows and namemaps from these maps
}



void ScreenLogicBase::UnregisterWindowFromNameMaps( UI::Window * wnd )
{
  Weak<Window> wndPtr = wnd;

  TAssignedNameMaps::iterator nmaps = assignedNameMaps.find( wndPtr );
  if ( nmaps == assignedNameMaps.end() )
    return;

  for ( TNameMapsSet::iterator nmapIt = nmaps->second.begin(); nmapIt != nmaps->second.end(); ++nmapIt )
  {
    if ( !( *nmapIt ) )
      continue;
    NNameMap::IMap * nmap = *nmapIt;

    TNameMappedWindows::iterator wndsIt = nameMappedWindows.find( nmap );
    if ( wndsIt == nameMappedWindows.end() )
      continue;

    wndsIt->second.erase( wndPtr );
  }
}



void ScreenLogicBase::UpdateWindowsByNameMap( NNameMap::IMap * nmap )
{
  TNameMappedWindows::iterator mapIt = nameMappedWindows.find( nmap );
  if ( mapIt != nameMappedWindows.end() )
  {
    TWindowsSet & windows = mapIt->second;
    for ( TWindowsSet::iterator it = windows.begin(); it != windows.end(); ++it )
    {
      Window * wnd = *it;
      if ( !wnd )
        continue;
      NameMappedWindow * img = dynamic_cast<NameMappedWindow *>( wnd );
      if( img )
        img->OnNameMapChanged();
    }
  }
}



NNameMap::Map * ScreenLogicBase::ResolveNameMap( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  string key( name, length );
  TSubmaps::iterator it = submaps.find( key );
  if ( it != submaps.end() ) 
    return it->second;

  return 0;
}



void ScreenLogicBase::QuitApplication()
{
  NMainFrame::Exit();
}


void ScreenLogicBase::QuitApplicationEx( const nstl::string& exitCode )
{
  NMainFrame::Exit( exitCode );
}


bool ScreenLogicBase::StartDrag( Window * target, const char * id, int offsX, int offsY )
{
  NI_ASSERT( user, "" );
  return user->StartDrag( target, id, offsX, offsY );
}



void ScreenLogicBase::Drop( bool restoreLocation )
{
  NI_ASSERT( user, "" );
  user->Drop( restoreLocation );
}



void ScreenLogicBase::CancelDrag()
{
  NI_ASSERT( user, "" );
  user->CancelDrag();
}



void ScreenLogicBase::ModifyDragLimits( Rect limits )
{
  NI_ASSERT( user, "" );
  user->ModifyDragLimits( limits );
}



Window * ScreenLogicBase::ImplFindDropTarget( const Point & mouseCoords, const char * id, Window * dragTarget )
{
  NI_ASSERT( user, "" );

  //window callback 
  struct Job : public WindowPointJob {
    const char * id;
    Window * dragTarget;
    Job( const Point & coords, const char * _id, Window * _dragTarget ) : WindowPointJob( coords ), id( _id ), dragTarget( _dragTarget )
    {
      SetIgnoreWindow( dragTarget );
    }
    virtual EWindowJobCode::Enum BeforeChildren( Window * target )
    {
      return WindowPointJob::BeforeChildren( target );
    }
    virtual bool Act( Window * target )
    {
      bool processed = target->EventDropTest( id, dragTarget );
      if ( Debug::MouseTraceEnabled() )
        Debug::AddRect( target->winRect, processed ? Debug::Color( 255, 0, 255 ) : Debug::Color( 255, 255, 0 ) );
      return processed;
    }
  } job( mouseCoords, id, dragTarget );

  return pBaseWindow->Traverse( &job );
}

} //namespace UI

NI_DEFINE_REFCOUNT( UI::ScreenLogicBase );


using namespace UI;
REGISTER_VAR( "ui_dragtrace_mindist", UI_DRAGTRACE_MINDIST, STORAGE_NONE );
REGISTER_VAR( "ui_dragtrace_maxdist", UI_DRAGTRACE_MAXDIST, STORAGE_NONE );
