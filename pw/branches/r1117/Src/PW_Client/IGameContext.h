#ifndef IGAMECONTEXT_H_INCLUDED
#define IGAMECONTEXT_H_INCLUDED

#include "Server/LobbyPvx/CommonTypes.h"
#include "PF_GameLogic/GameMaps.h"
#include "Network/LoginTypes.h"


namespace StatisticService
{
  class GameStatistics;
}

namespace Game
{

_interface IGameContextUiInterface : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IGameContextUiInterface, IBaseInterfaceMT );

  virtual bool          LoginInProgress() const = 0;
  virtual void          SetDeveloperSex( lobby::ESex::Enum _sex ) = 0;
  virtual void          ConnectToCluster( const string & login, const string & password, Login::LoginType::Enum _loginType = Login::LoginType::ORDINARY ) = 0;

  virtual NWorld::IMapCollection * Maps() = 0;
  virtual void          RefreshGamesList() = 0;
  virtual void          PopGameList( lobby::TDevGamesList & buffer ) = 0;
  virtual lobby::EOperationResult::Enum LastLobbyOperationResult() const = 0;
  virtual void          CreateGame( const char * mapId, int maxPlayers ) = 0;
  virtual void          JoinGame( int gameId ) = 0;
  virtual void          Reconnect( int gameId, int team, const string & heroId ) = 0;
  virtual void          Spectate( int gameId ) = 0;

  virtual void          ChangeCustomGameSettings( lobby::ETeam::Enum team, lobby::ETeam::Enum faction, const string & heroId ) = 0;
  virtual void          SetReady( lobby::EGameMemberReadiness::Enum readiness ) = 0;

  virtual void          SetDeveloperParty(int party) = 0;
};



_interface IGameContext : public IGameContextUiInterface
{
  NI_DECLARE_CLASS_1( IGameContext, IGameContextUiInterface );

  virtual void Start() = 0;
  virtual int  Poll( float dt ) = 0; // returns number of commands in buffer
  virtual void Shutdown() = 0;
  virtual void OnAltTab(bool isActive) = 0;
  virtual StatisticService::GameStatistics * GameStatLogic() = 0;
};

} //namespace Game

#endif //IGAMECONTEXT_H_INCLUDED
