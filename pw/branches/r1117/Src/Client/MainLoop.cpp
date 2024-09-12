#include "StdAfx.h"

#include "MainLoop.h"
#include "ScreenBase.h"
#include "ScreenCommands.h"
#include "../Core/CoreFSM.h"

#include "../System/meminfo.h"
#include "../System/Commands.h"
#include "../System/ConfigFiles.h"

#include "Console.h"

#include "Messages.h"
#include "MainTimer.h"

#include "Tooltips.h"
#include "TooltipsScreen.h"

#include "../UI/Root.h"
#include "../UI/User.h"
#include "../UI/DebugVarsRender.h"
#include "../UI/DebugDraw.h"
#include "../UI/FrameTimeRender.h"

#include "../Client/CommandBinds.h"

#include "../System/InlineProfiler.h"

#include "../Render/renderer.h"


namespace NMainLoop
{

static TScreenList g_screens;
TScreenList &GetScreens()
{
	return g_screens;
}



void CreateSystemScreens()
{
  Console::CreateScreen();
  TooltipsScreen::CreateScreen();
}



static void UpdateScreensFrontness();
static bool ProcessScreensEvents( bool uiEvents, const Input::Event & events );
static void ProcessScreensCursor();
static void ProcessScreensDnd();
static void DrawScreens(bool bAppActive);


bool Step( bool bAppActive, vector<Input::Event>& inputEvents )
{
  NI_PROFILE_FUNCTION

  //DEBUGVAR_TIMER( StepTime );
  // main time delta clock

  // step game state machine
  NCore::GetGlobalGameFSM()->Step(NMainLoop::GetTimeDelta() * 1000.0f); // @BVS@TIME

  //обработка команд на добавление/удаление и прочее про интерфейсы, позвать методы OnBefore*
  NScreenCommands::AnalizeScreenCmds();

  UI::NewFrame( GetTime() * 1000.0f ); //IREF //@BVS@TIME

  {
    //TODO: turn this into a function
    NI_PROFILE_BLOCK( "ScreensEvents" );

    while ( inputEvents.size() )
    {
      const Input::Event & event = inputEvents[0];

      if ( CommandBinds::ProcessEvent( event ) )
      {
        inputEvents.erase( inputEvents.begin() );
        continue;
      }

      //TODO: Ѕыло бы куда удобнее, если бы все окна от всех экранов складывались под единым родительским окном.
      //“огда обработка сообщений, mouseCapture, mouseMove & mouseOver, drag&drop была бы заметно очевидней,
      //и не надо было бы протаскивать все эти механизмы через NMainLoop и IScreenBase

      UI::GetUser()->StartEvent( event );
      if ( !ProcessScreensEvents( true, event ) )
        ProcessScreensEvents( false, event );
      UI::GetUser()->EndEvent( event );
      inputEvents.erase( inputEvents.begin() );
    }
  }

  {
    //TODO: turn this into a function
    NI_PROFILE_BLOCK( "ScreensMaintenance" );

    ProcessScreensCursor();
    ProcessScreensDnd();
    UpdateScreensFrontness();
  }


  //Call all ze steps
  NGlobal::CmdListManager::Instance()->Step();

  UI::GetUser()->Step( NMainLoop::GetTimeDelta() );

  UI::Debug::Step( NMainLoop::GetTimeDelta() );

  {
    //TODO: turn this into a function
    NI_PROFILE_BLOCK( "ScreensSteps" );

    {
      bool isScreenActive = true, isScreenVisible = true;
      for( TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it )
      {
        (*it)->Step( bAppActive );

        if ( (*it)->IsModal() )
          isScreenActive = false;

        if ( !(*it)->IsTransparent() )
          isScreenVisible = false;
      }
    }

    for( TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it )
      (*it)->CommonStep( bAppActive );
  }

	//здесь собственно выполнение команд
  NScreenCommands::ProcessScreenCmds();

  //@iA@FIXME: ¬нимание! DrawScreens складывает геометрию UI и _обычные_ указатели на материалы во внутренние буферы UIRenderer-а
  //≈сли между DrawScreens() и собственно отправкой геометрии в DX вызвать Window::Step() или NScreenCommands::ProcessScreenCmds(),
  //то там вместе с окнами/экранами могут быть удалены материалы, указатели на которые остались в UIRenderer-е..
  //—о всеми вытекающими при попытке отрендерить эту геометрию

  //ќтправка UI-геометрии в очередь рендера
  if ( !Render::GetRenderer()->DeviceIsLost() )
  {
    Render::GetUIRenderer()->BeginQueue();

    DrawScreens( bAppActive );

    UI::PresentFrame( GetTime() * 1000.0f, bAppActive ); //IREF //@BVS@TIME
    Render::GetUIRenderer()->EndQueue();
  }

  return !g_screens.empty();
}


void AddTooltip( const wstring & text, const UI::STooltipDesc & desc )
{
  TooltipsScreen::Instance()->AddTooltip( text, desc );
}


typedef map<EScreenLayer::Enum, pair<bool, IScreenBase *> > TLastFrontScreens;
static TLastFrontScreens g_lastFrontScreens;


static void UpdateScreensFrontness()
{
  //Update last front screen for each layer
  for(TLastFrontScreens::iterator it = g_lastFrontScreens.begin(); it != g_lastFrontScreens.end(); ++it)
    it->second.first = false;
  for( TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it )
  {
    if( !*it )
      continue;

    IScreenBase * pScreen = *it, * pPrevScreen = NULL;
    EScreenLayer::Enum layer = pScreen->GetScreenLayer();

    TLastFrontScreens::iterator check = g_lastFrontScreens.find(layer);
    if(check != g_lastFrontScreens.end())
    {
      if(check->second.first)
        continue;
      pPrevScreen = check->second.second;
    }

    if(pScreen != pPrevScreen)
    {
      //notify new front screen about his frontness
      pScreen->OnBecameFront();
      //notify all screens about new front
      for( TScreenList::iterator scr = g_screens.begin(); scr != g_screens.end(); ++scr )
        if( *scr )
          (*scr)->OnNewFront(pScreen);
    }

    g_lastFrontScreens[layer] = pair<bool, IScreenBase *>(true, pScreen);
  }
}


static bool ProcessScreensEvents( bool uiEvents, const Input::Event & events )
{
  NI_PROFILE_FUNCTION

  for( TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it )
  {
    IScreenBase * screen = *it;

    if(!screen->IsInited())
      continue;

    if ( uiEvents ? screen->ProcessUIEvent( events ) : screen->ProcessSceneEvent( events ) )
      return true;

    if(screen->IsModal())
      return false;
  }

  return false;
}


static void ProcessScreensCursor()
{
  string cursorId = "ui_normal";

  for( TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it )
  {
    IScreenBase * screen = *it;

    if( !screen->IsInited() )
      continue;

    if( screen->GetCursor( &cursorId, UI::GetUser()->LastMouseCoords() ) )
    {
      UI::SetCursor( cursorId );
      break;
    }

    if( screen->IsModal() )
      break;
  }
}



static void ProcessScreensDnd()
{
  const string & dndId = UI::GetUser()->GetDragAndDropId();
  UI::Window * dragWnd = UI::GetUser()->GetDragWindow();

  if ( dndId.empty() || !dragWnd )
  {
    UI::GetUser()->ImplUpdateDragAndDrop( 0 ); //Called here to cleanup some internal D'n'D states
    return;
  }

  UI::Window * target = 0;
  for( TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it )
  {
    IScreenBase * screen = *it;

    if( !screen->IsInited() )
      continue;

    target = screen->FindDropTarget( UI::GetUser()->LastMouseCoords(), dndId.c_str(), dragWnd );
    if( target )
      break;

    if( screen->IsModal() )
      break;
  }

  UI::GetUser()->ImplUpdateDragAndDrop( target );
}



static void DrawScreens(bool bAppActive)
{
  NI_PROFILE_FUNCTION

  static vector<NMainLoop::IScreenBase *> drawList;

  drawList.clear();
  drawList.reserve( g_screens.size() );

  for(TScreenList::iterator it = g_screens.begin(); it != g_screens.end(); ++it)
  {
    NMainLoop::IScreenBase * pScreen = *it;
    bool transparent = pScreen->IsTransparent();

    if(pScreen->IsInited())
      drawList.push_back( pScreen );

    if(pScreen->IsInited() && !transparent)
      break;
  }

  for( int i = 0; i < drawList.size(); ++i )
    drawList[ drawList.size() - 1 - i ]->Draw( bAppActive );
}

} //namespace NMainLoop

