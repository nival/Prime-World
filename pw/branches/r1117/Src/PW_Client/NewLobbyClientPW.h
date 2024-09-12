#ifndef NEWLOBBYCLIENTPW_H_INCLUDED
#define NEWLOBBYCLIENTPW_H_INCLUDED

#include "Client/LobbyPvx/LobbyClientBase.h"
#include "IGameContext.h"

namespace NGameX
{
  class AdventureScreen;
  class SelectGameModeScreen;
  class SelectHeroScreen;
}


namespace NWorld
{
  class IMapCollection;
}


namespace lobby
{

class GameClientPW;
class FastReconnectCtxPW;


class ClientPW : public ClientBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClientPW, ClientBase );
public:
  ClientPW( Transport::TClientId _clientId, bool _socialMode, Game::IGameContextUiInterface * _gameCtx, FastReconnectCtxPW * _fastReconnectCtx );

  void SetAdvScreen( NGameX::AdventureScreen * screen ) { advScreen = screen; }
  NWorld::IMapCollection * Maps() { return mapCollection; }

  void CreateGame( const char * mapId, int maxPlayers, int autostartPlayers = -1 );

  void GotoFirstLobbyScreen();
  void CleanUIScreens();

protected:
  //ClientBase
  virtual void OnStatusChange( EClientStatus::Enum newStatus );
  virtual void OnLobbyDataChange();

  virtual void Award( const vector<roll::SAwardInfo> & _awards );

private:
  WeakMT<Game::IGameContextUiInterface> gameCtx;
  StrongMT<NWorld::IMapCollection>      mapCollection;
  Weak<NGameX::AdventureScreen>         advScreen;
  Weak<NGameX::SelectGameModeScreen>    lobbyScreen;
  Weak<NGameX::SelectHeroScreen>        heroScreen;
  StrongMT<FastReconnectCtxPW>          fastReconnectCtxPw;

  void RemoveFirstLobbyScreen();
  void UpdateCustomLobbyPlayers( const set<int> & hilitePlayers );
};

} //namespace lobby

#endif //NEWLOBBYCLIENTPW_H_INCLUDED
