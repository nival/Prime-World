#include "stdafx.h"

#include "UI/Button.h"
#include "UI/RadioPanel.h"

#include "SelectHeroScreen.h"
#include "Render/TextureManager.h"

#include "SelectHeroScreenLogic.h"
#include "NewLobbyClientPW.h"


namespace UI
{

#pragma warning(push)
#pragma warning(disable:4686)
BEGIN_LUA_TYPEINFO( SelectHeroScreenLogic, ClientScreenUILogicBase )
  LUA_METHOD( SelectHero )
  LUA_METHOD( PlayerReady )
  LUA_METHOD( ChangeTeam )
  LUA_METHOD( ChangeFaction )
  LUA_METHOD( SetDeveloperParty )
END_LUA_TYPEINFO( SelectHeroScreenLogic )
#pragma warning(pop)
  

void SelectHeroScreenLogic::SelectHero( const char * heroId )
{
  if ( StrongMT<Game::IGameContextUiInterface> locked = screen->GameCtx().Lock() )
    locked->ChangeCustomGameSettings( lobby::ETeam::None, lobby::ETeam::None, heroId );
}



void SelectHeroScreenLogic::PlayerReady()
{ 
  if ( StrongMT<Game::IGameContextUiInterface> locked = screen->GameCtx().Lock() )
    locked->SetReady( lobby::EGameMemberReadiness::Ready ); //TODO: lobby::EGameMemberReadiness::ReadyForAnything
}



void SelectHeroScreenLogic::ChangeTeam( int team )
{
  if ( StrongMT<Game::IGameContextUiInterface> locked = screen->GameCtx().Lock() )
    locked->ChangeCustomGameSettings( team == 0 ? lobby::ETeam::Team1 : lobby::ETeam::Team2, lobby::ETeam::None, string() );
}

void SelectHeroScreenLogic::ChangeFaction( int faction )
{
  if ( StrongMT<Game::IGameContextUiInterface> locked = screen->GameCtx().Lock() )
    locked->ChangeCustomGameSettings( lobby::ETeam::None, faction == 0 ? lobby::ETeam::Team1 : lobby::ETeam::Team2, string() );
}

void SelectHeroScreenLogic::SetDeveloperParty(int party)
{
  if ( StrongMT<Game::IGameContextUiInterface> locked = screen->GameCtx().Lock() )
    locked->SetDeveloperParty(party);
}

void SelectHeroScreenLogic::DebugDisplayPlayers ( const wstring & status )
{
  UI::ImageLabel * pDesc = UI::GetChildChecked < UI::ImageLabel > ( pBaseWindow, "DebugPlayers", true );
  if ( pDesc )
    pDesc->SetCaptionTextW ( status.c_str() );
}

}//end of namespace

