#include "stdafx.h"

#include "DefaultScreenBase.h"
#include "Core/CoreFSM.h"
#include "ScreenCommands.h"
#include "MainTimer.h"
#include "Sound/EventScene.h"
#include "UI/Window.h"
#include "System/InlineProfiler.h"

namespace NMainLoop
{

void DefaultScreenBase::OnBecameFront()
{
}



bool DefaultScreenBase::Init( UI::User * uiUser )
{
  return true;
}



bool DefaultScreenBase::OnBeforeClose()
{
  if ( basicLogic && basicLogic->GetBaseWindow() && basicLogic->GetBaseWindow()->GetWindowLayout() )
    NSoundScene::EventStart( basicLogic->GetBaseWindow()->GetWindowLayout()->soundHide );

  return true;
}



void DefaultScreenBase::OnNewFront(IScreenBase * pNewFrontScreen)
{
  if ( !pNewFrontScreen )
    return;

  if ( pNewFrontScreen->GetScreenLayer() != GetScreenLayer() )
    return;

  bool newFocus = (pNewFrontScreen == this);

  if ( isScreenFocused != newFocus )
  {
    isScreenFocused = newFocus;
    if( basicLogic )
    {
      basicLogic->OnScreenFocus( isScreenFocused );

      if ( showOnlyOnTop )
        basicLogic->GetBaseWindow()->Show( isScreenFocused );
    }
  }
}



void DefaultScreenBase::Step( bool bAppActive )
{
	if( basicLogic )
  {
    float dt = NMainLoop::GetTimeDelta();
    basicLogic->Step( dt );
		basicLogic->StepWindows( dt );
  }
}



void DefaultScreenBase::Draw( bool bAppActive )
{
  if ( basicLogic && ( !showOnlyOnTop || isScreenFocused ) )
    basicLogic->RenderWindows();
}



bool DefaultScreenBase::ProcessUIEvent( const Input::Event & message )
{
  NI_PROFILE_FUNCTION

  if ( showOnlyOnTop && !isScreenFocused )
    return false;

  if ( basicLogic && basicLogic->ProcessMessage( message ) )
    return true;

  if ( eventsUI.ProcessEvent( message, this ) )
     return true;

  return false;
}



bool DefaultScreenBase::ProcessSceneEvent( const Input::Event & message )
{
  NI_PROFILE_FUNCTION

  if( showOnlyOnTop && !isScreenFocused )
    return false;

  if ( eventsScene.ProcessEvent( message, this ) )
     return true;

  return false;
}



bool DefaultScreenBase::GetCursor( string * id, const UI::Point & screenCoords ) const
{
  return basicLogic ? basicLogic->GetCursor( id, screenCoords ) : false;
}



UI::Window * DefaultScreenBase::FindDropTarget( const UI::Point & mouseCoords, const char * id, UI::Window * dragTarget )
{
  return basicLogic ? basicLogic->ImplFindDropTarget( mouseCoords, id, dragTarget ) : 0;
}



void DefaultScreenBase::CloseThisScreen()
{
  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( this ) );
}



UI::Window * DefaultScreenBase::GetMainWindow()
{
  if ( basicLogic )
    return basicLogic->GetBaseWindow();
  return 0;
}



void DefaultScreenBase::ShowMainWindow( bool show )
{
  UI::Window * wnd = GetMainWindow();
  if ( wnd )
    wnd->Show( show );
}

} // namespace NMainLoop

NI_DEFINE_REFCOUNT( NMainLoop::IScreenBase )
NI_DEFINE_REFCOUNT( NMainLoop::DefaultScreenBase )
