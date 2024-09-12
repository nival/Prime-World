#pragma once

#include "MinigameLobbyScreen.h"
#include "ClinicLobbyScreenLogic.h"

namespace PF_Minigames
{

class Minigames;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicLobbyScreen : public PF_Minigames::MinigameLobbyScreen
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClinicLobbyScreen, PF_Minigames::MinigameLobbyScreen );

public:
  ClinicLobbyScreen();
  virtual ~ClinicLobbyScreen();

  virtual bool Init( UI::User * uiUser );
  virtual bool IsModal() const { return false; }
  virtual bool IsTransparent() const { return true; }
  virtual void OnBecameFront();

  void CloseScreen();

private:
	Strong<UI::ClinicLobbyScreenLogic> logic;
};

} // namespace PF_Minigames