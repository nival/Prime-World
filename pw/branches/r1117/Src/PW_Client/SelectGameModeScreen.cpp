#include "stdafx.h"
#include "SelectGameModeScreen.h"

#include "Core/CoreFSM.h"
#include "SelectGameModeLogic.h"
#include "PF_GameLogic/GameMaps.h"
#include "NewLobbyClientPW.h"

#include "System/InlineProfiler.h"


namespace NGameX
{


SelectGameModeScreen::SelectGameModeScreen( Game::IGameContextUiInterface * _ctx ) :
gameCtx( _ctx )
{ 
}



bool SelectGameModeScreen::Init( UI::User * uiUser )
{ 
  NI_PROFILE_FUNCTION

  logic = new UI::SelectGameModeLogic;
  SetLogic( logic );
  logic->SetUser( uiUser );
  logic->SetScreen( this );
  logic->LoadScreenLayout( "Lobby_SelectGameMode" );

  {
    NI_PROFILE_BLOCK( "Maps" )
    StrongMT<Game::IGameContextUiInterface> locked = gameCtx.Lock();
    if ( !locked )
      return false;

    NWorld::IMapCollection * maps = locked->Maps();
    NDb::Ptr<NDb::MapList> pMapList = NDb::Get<NDb::MapList>( NDb::DBID( "\\Tech\\Default\\_.MAPLST.xdb" ) );

    NI_VERIFY( IsValid( pMapList ), "\\Tech\\Default\\_.MAPLST does not exist", return false )

    maps->InitCustomList(pMapList);

    for ( int i = 0; i < pMapList->maps.size(); ++i )
      logic->AddMapEntry( i, maps->CustomDescId( i ), maps->CustomTitle( i ), maps->CustomDescription( i ) );
  }

  if ( StrongMT<Game::IGameContextUiInterface> cl = gameCtx.Lock() )
    cl->RefreshGamesList();

  return true; 
} 



void SelectGameModeScreen::Step( bool bAppActive )
{
  StrongMT<Game::IGameContextUiInterface> locked = gameCtx.Lock();
  if ( !locked || !logic )
    return;

  lobby::TDevGamesList infos;
  locked->PopGameList( infos );

  for( lobby::TDevGamesList::iterator it = infos.begin(); it != infos.end(); ++it )
    logic->UpdateSessionInfo( *it );

  lobby::EOperationResult::Enum joinResult = locked->LastLobbyOperationResult();
  if ( joinResult != lobby::EOperationResult::InProgress )
    logic->UpdateJoinResult( joinResult );

  DefaultScreenBase::Step( bAppActive );
}

} //namespace NGameX
