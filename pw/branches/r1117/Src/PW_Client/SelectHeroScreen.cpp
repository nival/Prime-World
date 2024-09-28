#include "stdafx.h"
#include "SelectHeroScreen.h"

#include "Core/CoreFSM.h"
#include "PW_Client/GameContext.h"
#include "SelectHeroScreenLogic.h"
#include "Client/MainTimer.h"
#include "System/InlineProfiler.h"

namespace NGameX
{  

SelectHeroScreen::SelectHeroScreen( Game::IGameContextUiInterface * _ctx ) :
gameCtx( _ctx )
{   
}



bool SelectHeroScreen::Init( UI::User * uiUser )
{ 
  NI_PROFILE_FUNCTION

  logic = new UI::SelectHeroScreenLogic;
  SetLogic( logic );
  logic->SetUser( uiUser );

  if ( logic != NULL )
  {  
    logic->SetOwner( this );
    logic->LoadScreenLayout( "LobbyScreen" );

    logic->DebugDisplayPlayers( debugPlayerStatus );
  }
  else
    return false;

  return true; 
}   



void SelectHeroScreen::CommonStep( bool bAppActive )
{
  DefaultScreenBase::CommonStep( bAppActive );

  float dt = NMainLoop::GetTimeDelta();
  bool update = false;
  for( map<int, float>::iterator it = debugHiliteTimes.begin(), next = it; it != debugHiliteTimes.end(); it = next )
  {
    next = it;
    ++next;

    it->second -= dt;
    if( it->second < 0 )
    {
      update = true;
      debugHiliteTimes.erase( it );
    }
  }

  if ( update )
  {
    DebugFormatPlayerInfo();
    logic->DebugDisplayPlayers( debugPlayerStatus );
  }
}



void SelectHeroScreen::UpdatePlayers( const vector<wstring> & lines, const vector<int> & linesIds, const set<int> & hiliteIds )
{
  const float HILITE_TIME = 3.0f;

  debugPlayerLines = lines;
  debugPlayerIds = linesIds;

  for( set<int>::const_iterator it = hiliteIds.begin(); it != hiliteIds.end(); ++it )
    debugHiliteTimes[ *it ] = HILITE_TIME;

  DebugFormatPlayerInfo();

  if ( IsValid ( logic ) )
    logic->DebugDisplayPlayers ( debugPlayerStatus );
}



void SelectHeroScreen::DebugFormatPlayerInfo()
{
  if ( debugPlayerLines.size() != debugPlayerIds.size() )
    return;

  debugPlayerStatus = L"<style:gray>";

  for( int i = 0; i < debugPlayerLines.size(); ++i )
  {
    if ( i )
      debugPlayerStatus += L"<br>";

    bool hilite = debugHiliteTimes.find( debugPlayerIds[i] ) != debugHiliteTimes.end();
    if ( hilite )
      debugPlayerStatus += L"<style:red>";

    debugPlayerStatus += debugPlayerLines[i];

    if ( hilite )
      debugPlayerStatus += L"</style>";
  }
}

}//end of namespace
