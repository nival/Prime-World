#pragma once

#include "MinigameLobbyScreenLogic.h"

namespace PF_Minigames
{
class ClinicLobbyScreen;
class Clinic;
class Minigames;
}

namespace UI
{

class ClinicLobbyScreenLogic : public PF_Minigames::MinigameLobbyScreenLogic
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClinicLobbyScreenLogic, PF_Minigames::MinigameLobbyScreenLogic );

public:
  DECLARE_LUA_TYPEINFO( ClinicLobbyScreenLogic );

  ClinicLobbyScreenLogic() : selectedLevel(-1) {}

  void InitLayout( PF_Minigames::Minigames* _minigames );
  void SetSelectedLevel( int newSel );

  ///Lua///
  void Start();
  void OpenShop();
  void SwitchToNextLevel();
  void SwitchToPrevLevel();
  void Exit();
  void RefreshNextLevel();

private:
  CPtr<PF_Minigames::Clinic> clinic;
  CPtr<PF_Minigames::Minigames> minigames;
  int selectedLevel;
};

} //namespace UI
