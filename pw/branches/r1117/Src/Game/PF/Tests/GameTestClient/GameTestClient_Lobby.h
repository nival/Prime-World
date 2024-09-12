#pragma once

#include "GameTestClient_GS.h"
#include "Client/LobbyPvx/LobbyClientBase.h"

namespace gtc
{

class GameClientWrapper;

class Client_Lobby : public Client_GS
{
  NI_DECLARE_REFCOUNT_CLASS_1( Client_Lobby, Client_GS );

public:
  Client_Lobby( const TestClientBaseParams & _params );

  ~Client_Lobby();

private:
  StrongMT<lobby::ClientBase>  lobbyClient;

  virtual StepResult MainStep();

  int startLobbyClient();
  int waitLobbyClient();
  void stepLobbyClient();
};

} //namespace gtc
