#include "StdAfx.h"
#include "LoadingStatusHandler.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Network/LoginTypes.h"
#include "Game/PF/Client/LobbyPvx/LobbyClientBase.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/DBStats.h"
#include "LoadingFlashInterface.h"

namespace
{

  struct SErrorText
  {
    int           code;
    const char *  text;
  };

  static SErrorText s_loginCodes[] = 
  {
    { Login::ELoginResult::NoResult,        "connecting" },
    { Login::ELoginResult::NoConnection,    "noConnection" },
    { Login::ELoginResult::Refused,         "refused" },
    { Login::ELoginResult::AlreadyIn,       "alreadyIn" },
    { Login::ELoginResult::ServerError,     "serverError" },
    { Login::ELoginResult::ClientOutdated,  "clientOutdated" },
    { Login::ELoginResult::ServerOutdated,  "serverOutdated" },
    { Login::ELoginResult::UndefinedSex,    "undefinedSex" },
    { Login::ELoginResult::AccessDenied,    "accessDenied" },
    { 0, 0 },
  };


  static SErrorText s_statisticsCodes[] = 
  {
    { Game::EGameStatStatus::None,          "stat_waiting" },
    { Game::EGameStatStatus::Waiting,       "stat_waiting" },
    { Game::EGameStatStatus::Failed,        "stat_failed" },
    { Game::EGameStatStatus::Disabled,      "stat_disabled" },
    { 0, 0 },
  };


  static SErrorText s_lobbyCodes[] = 
  {
    { lobby::EClientStatus::Initial,                   "lobby_initial" },
    { lobby::EClientStatus::Error,                     "lobby_error" },
    { lobby::EClientStatus::Disconnected,              "lobby_disconnected" },
    { lobby::EClientStatus::WaitingEntrance,           "lobby_conencting" },
    { lobby::EClientStatus::RequestingServerInstance,  "lobby_waitingServer" },
    { lobby::EClientStatus::WaitingAccounting,         "lobby_accounting" },
    { lobby::EClientStatus::Connected,                 "lobby_ok" },
    { 0, 0 },
  };



  static SErrorText s_inGameCodes[] = 
  {
    { lobby::EOperationResult::Ok,                     "inGame_ok" },
    { lobby::EOperationResult::InProgress,             "inGame_enteringGame" },
    { lobby::EOperationResult::InternalError,          "inGame_serverError" },
    { lobby::EOperationResult::NoFreeSlot,             "inGame_noGame" },
    { lobby::EOperationResult::GameNotFound,           "inGame_noGame" },
    { lobby::EOperationResult::GameStarted,            "inGame_alreadyInGame" },
    { lobby::EOperationResult::AlreadyInGame,          "inGame_alreadyInGame" },
    { lobby::EOperationResult::RevisionDiffers,        "inGame_wrongRevision" },
    { lobby::EOperationResult::RestrictedAccess,       "inGame_accessDenied" },
    { 0, 0 },
  };


  static SErrorText s_replayCodes[] = 
  {
    { Game::EReplayStatus::Failure,                     "replay_failure" },
    { Game::EReplayStatus::WrongFormat,                 "replay_wrongFormat" },
    { Game::EReplayStatus::WrongVersion,                "replay_wrongVersion" },
    { 0, 0 },
  };


  static const char * GetText( int code, SErrorText * table, const char * defaultText )
  {
    for ( SErrorText * p = table; p->text; ++p )
      if ( p->code == code )
        return p->text;
    return defaultText;
  }

}

namespace NGameX
{


 

  LoadingStatusHandler::LoadingStatusHandler( const NDb::DBUIData * _uiData )
    : uiData (_uiData)
  {
    
  }



  void LoadingStatusHandler::SetFlashInterface( Game::LoadingFlashInterface * _flashInterface )
  {
    flashInterface = _flashInterface;

    flashInterface->SetLoadingStatusText(L"");

    if (pendingStatus.size()>0)
      SetStatusText(pendingStatus.c_str());
  }

  static const char * s_defaultStatus = "defaultError";

  void LoadingStatusHandler::OnLoginStatus( Login::ELoginResult::Enum loginStatus )
  {
    SetStatusText( GetText( loginStatus, s_loginCodes, s_defaultStatus ) );
  }

  void LoadingStatusHandler::OnGameStatStatus( Game::EGameStatStatus::Enum gameStatStatus )
  {
    SetStatusText( GetText( gameStatStatus, s_statisticsCodes, s_defaultStatus ) );
  }



  void LoadingStatusHandler::OnLobbyStatus( lobby::EClientStatus::Enum lobbyStatus )
  {
    SetStatusText( GetText( lobbyStatus, s_lobbyCodes, s_defaultStatus ) );
  }



  void LoadingStatusHandler::OnLobbyInGameStatus( lobby::EOperationResult::Enum inGameStatus )
  {
    SetStatusText( GetText( inGameStatus, s_inGameCodes, s_defaultStatus ) );
  }


  void LoadingStatusHandler::OnReplayStatus( Game::EReplayStatus::Enum replayStatus )
  {
    SetStatusText( GetText( replayStatus, s_replayCodes, s_defaultStatus ) );
  }


  void LoadingStatusHandler::SetStatusText( const char * textId )
  {
    if (!uiData)
      return;

    if (!flashInterface)
    {
      pendingStatus = textId;
      return;
    }

    if ( lastStatus == textId )
      return;

    lastStatus = textId;

    wstring text = FindLocalizedString(textId);
    if ( text.empty() && textId[0] )
      text = NStr::StrFmtW( L"{%S}", textId );

    DevTrace( "Login screen status '%s', converted to '%s'", textId, NStr::ToMBCS( text ).c_str() );

    
    flashInterface->SetLoadingStatusText(text);
  }

  nstl::wstring LoadingStatusHandler::FindLocalizedString( const char * textId )
  {
    for (int i = 0; i< uiData->loadingScreenStatuses.size(); i++)
    {
      const NDb::StringTextRefPair & status = uiData->loadingScreenStatuses[i];
      if (status.key == textId)
        return status.text.GetText();
    }

    return wstring();
  }
}


NI_DEFINE_REFCOUNT( NGameX::LoadingStatusHandler );