#include "stdafx.h"
#include "NewLobbyClientPW.h"
#include "PF_GameLogic/MapCollection.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/AdventureScreen.h"
#include "Client/ScreenCommands.h"

#include "SelectGameModeScreen.h"
#include "SelectHeroScreen.h"
#include "FastReconnectCtxPW.h"


namespace lobby
{

ClientPW::ClientPW( Transport::TClientId _clientId, bool _socialMode, Game::IGameContextUiInterface * _gameCtx, FastReconnectCtxPW * _fastReconnectCtx ) :
ClientBase( _clientId, _socialMode ),
gameCtx( _gameCtx ),
fastReconnectCtxPw( _fastReconnectCtx )
{
}



void ClientPW::OnStatusChange( EClientStatus::Enum newStatus )
{
  ClientBase::OnStatusChange( newStatus );

  if ( newStatus == EClientStatus::Connected )
  {
    if ( fastReconnectCtxPw )
      mapCollection = fastReconnectCtxPw->Maps();
    else
    {
      StrongMT<NWorld::PWMapCollection> maps = new NWorld::PWMapCollection;
      maps->ScanForMaps();
      mapCollection = maps;
    }

    if ( !InSocialMode() )
      GotoFirstLobbyScreen();
  }
  else if ( newStatus == EClientStatus::InCustomLobby )
  {
    RemoveFirstLobbyScreen();

    if ( !fastReconnectCtxPw ) {
      heroScreen = new NGameX::SelectHeroScreen( gameCtx.Lock() );
      NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( heroScreen ) );
    }
  }
  else if ( newStatus == EClientStatus::InGameSession )
  {
    RemoveFirstLobbyScreen(); // Needed here for custom game reconnect, where we skip InCustomLobby

    if ( heroScreen )
      NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( heroScreen ) );
  }
}



void ClientPW::OnLobbyDataChange()
{
  ClientBase::OnLobbyDataChange();

  if ( Status() == EClientStatus::InCustomLobby )
  {
    set<int> empty;
    UpdateCustomLobbyPlayers( empty );
  }
}



void ClientPW::CreateGame( const char * mapId, int maxPlayers, int autostartPlayers /*= -1*/ )
{
  StrongMT<NWorld::IMapLoader> mapLoader = mapCollection->CreateMapLoader( mapId );
  NI_DATA_VERIFY( mapLoader, NStr::StrFmt( "Could not load map '%s'", mapId ), return );

  ClientBase::CreateGame( mapId, maxPlayers, mapLoader->GetMaxPlayersPerTeam(), autostartPlayers );
}



void ClientPW::GotoFirstLobbyScreen()
{
  if ( fastReconnectCtxPw )
    return;

  //Lobby server requested Player interface, we ready to show GUI
  lobbyScreen = new NGameX::SelectGameModeScreen( gameCtx.Lock() );

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( lobbyScreen ) );
}



void ClientPW::RemoveFirstLobbyScreen()
{
  if ( lobbyScreen )
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( lobbyScreen ) );
}



void ClientPW::UpdateCustomLobbyPlayers( const set<int> & hilitePlayers )
{
  if ( !heroScreen )
    return;

  vector<wstring> lines;
  vector<int> linesIds;

  for( int i = 0; i < 2; ++i )
  {
    ETeam::Enum team = i ? ETeam::Team2 : ETeam::Team1;

    lines.push_back( i ? L"Team two:" : L"Team one:" );
    linesIds.push_back( -1 );
    for ( int j = 0; j < GameLineup().size(); ++j )
    {
      const SGameMember & memb = GameLineup()[j];
      if( memb.context.team != team )
        continue;
      
      const bool ready = ( ReadyPlayers().find( memb.user.userId ) != ReadyPlayers().end() );

      wstring line = NStr::StrFmtW( L"<space:2>%s (%d) as %s (%s), %s",
        memb.user.nickname.c_str(),
        memb.user.userId,
        NStr::ToUnicode( memb.context.hero ).c_str(),
        memb.context.original_team == lobby::ETeam::Team2 ? L"Adornia" : L"Doct",
        ready ? L"<style:green>ready</style>" : L"<style:money>not ready</style>" );

      lines.push_back( line );
      linesIds.push_back( memb.user.userId );
    }
  }

  heroScreen->UpdatePlayers( lines, linesIds, hilitePlayers );
}

void ClientPW::Award( const vector<roll::SAwardInfo> & _awards )
{
  if (advScreen)
    advScreen->AwardUser(_awards);
}

void ClientPW::CleanUIScreens()
{
  RemoveFirstLobbyScreen();
}


} //namespace lobby
