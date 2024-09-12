#pragma once

namespace Login
{
  namespace ELoginResult
  {
    enum Enum;
  }
}

namespace NDb
{
  struct DBUIData;
}

namespace lobby
{
  namespace EClientStatus { enum Enum; }
  namespace EOperationResult { enum Enum; }
}

namespace Game
{
  class LoadingFlashInterface;

  namespace EGameStatStatus
  {
    enum Enum
    {
      None,
      Waiting,
      Ready,
      Failed,
      Disabled
    };
  }

  namespace EReplayStatus
  {
    enum Enum
    {
      Failure,
      WrongFormat,
      WrongVersion
    };
  }
}

namespace NGameX
{

  class LoadingStatusHandler : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoadingStatusHandler, BaseObjectST)
public:
  LoadingStatusHandler(const NDb::DBUIData * _uiData);

  void SetFlashInterface(Game::LoadingFlashInterface * _flashInterface);
  void OnLoginStatus( Login::ELoginResult::Enum loginStatus );
  void OnGameStatStatus( Game::EGameStatStatus::Enum gameStatStatus );
  void OnLobbyStatus( lobby::EClientStatus::Enum lobbyStatus );
  void OnLobbyInGameStatus( lobby::EOperationResult::Enum inGameStatus );
  void OnReplayStatus( Game::EReplayStatus::Enum replayStatus );

private:
  void SetStatusText( const char * textId );
  wstring FindLocalizedString( const char * textId );

  Weak<Game::LoadingFlashInterface> flashInterface;
  NDb::Ptr<NDb::DBUIData>         uiData;
  string                            lastStatus;
  string                            pendingStatus;
};

}