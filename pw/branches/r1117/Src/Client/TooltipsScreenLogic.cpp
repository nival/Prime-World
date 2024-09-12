#include "stdafx.h"
#include "TooltipsScreenLogic.h"
#include "Tooltips.h"

#include "../UI/Window.h"
#include "../UI/Cursor.h"
#include "../UI/Resolution.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ScriptHandlers
{
  static const char *   ShowTooltip = "CppShowTooltip";
  static const char *   HideTooltip = "CppHideTooltip";
  static const char *   CheckTooltip = "CppCheckTooltip";
} //ScriptHandlers


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( TooltipsScreenLogic, ScreenLogicBase )
END_LUA_TYPEINFO( TooltipsScreenLogic )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TooltipsScreenLogic::TooltipsScreenLogic()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TooltipsScreenLogic::AddTooltip( const wstring & text, const UI::STooltipDesc & desc )
{
  NI_ASSERT( desc.targetWindow, "" );

  CVec2 uiScale( (float)GetUIScreenResolution().x / GetScreenResolution().x, (float)GetUIScreenResolution().y / GetScreenResolution().y );

  Point cursorSize( (int)( NCursor::GetCurrentSize().x * uiScale.x + 0.5f ), (int)( NCursor::GetCurrentSize().y * uiScale.y + 0.5f ) );
  Point cursorSpot( (int)( NCursor::GetCurrentHotSpot().x * uiScale.x + 0.5f ), (int)( NCursor::GetCurrentHotSpot().y * uiScale.y + 0.5f ) );

  pBaseWindow->CallHandler( ScriptHandlers::ShowTooltip, text, desc.mousePos, desc.targetWindow.Get(), cursorSize, cursorSpot );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TooltipsScreenLogic::HideTooltip()
{
  if ( pBaseWindow )
    pBaseWindow->CallHandler( ScriptHandlers::HideTooltip );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TooltipsScreenLogic::CheckTooltip()
{
  if ( pBaseWindow )
    pBaseWindow->CallHandler( ScriptHandlers::CheckTooltip );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TooltipsScreenLogic::SetCurrentScreen( NMainLoop::IScreenBase *pScreen )
{
  if ( currentTopScreen == pScreen )
    return;

  HideTooltip();
  currentTopScreen = pScreen;
}

} //namespace UI
