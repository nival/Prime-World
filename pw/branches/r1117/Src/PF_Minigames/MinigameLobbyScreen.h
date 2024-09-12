#pragma once

#include "MinigameScreen.h"

#include "MinigameLobbyScreenLogic.h"

namespace PF_Minigames
{

class Minigames;

namespace ELobbyScreenState
{
  enum Enum { Starting, Normal, Exiting, Finished };
}



class MinigameLobbyScreen : public MinigameScreen
{
  NI_DECLARE_REFCOUNT_CLASS_1( MinigameLobbyScreen, MinigameScreen );

public:
  MinigameLobbyScreen();
  virtual ~MinigameLobbyScreen();

  ELobbyScreenState::Enum State() const { return state; }
  void SetState( ELobbyScreenState::Enum st ){ state = st; }

  void SetMinigames( PF_Minigames::Minigames * _minigames ) { minigames = _minigames; }
  PF_Minigames::Minigames * GetMinigames() { return minigames; }

  void SetLobbyLogic( MinigameLobbyScreenLogic * _logic ) { lobbyLogic = _logic; }

  virtual bool Init( UI::User * uiUser );

  virtual bool IsModal() const { return false; }
  virtual bool IsTransparent() const { return true; }

  //We need block all bind events to adventure screen
  virtual bool ProcessUIEvent( const Input::Event & event );

  //We need block all 3D input to AdventureScreen
  virtual bool ProcessSceneEvent( const Input::Event & event ) { return true; }

  virtual void OnBecameFront();

private:
  ELobbyScreenState::Enum state;
  CPtr<Minigames> minigames;
  Strong<MinigameLobbyScreenLogic> lobbyLogic;
};

} // namespace PF_Minigames
