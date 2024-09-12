#include "stdafx.h"

#include "ClinicLobbyScreenLogic.h"
#include "ClinicLobbyScreen.h"
#include "ClinicScreen.h"
#include "ClinicShopScreen.h"

#include "Clinic.h"
#include "MinigameCommands.h"
#include "Minigames.h"
#include "MinigamesMain.h"
#include "MinigameCameraController.h"

#include "../Client/ScreenCommands.h"
#include "../UI/ImageLabel.h"

namespace UI
{

static bool gAllLevelsOpen = false;
REGISTER_DEV_VAR( "clinic_all_levels_open", gAllLevelsOpen,  STORAGE_NONE );


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( ClinicLobbyScreenLogic, PF_Minigames::MinigameLobbyScreenLogic )
  LUA_METHOD( Start )
  LUA_METHOD( OpenShop )
  LUA_METHOD( SwitchToNextLevel )
  LUA_METHOD( SwitchToPrevLevel )
  LUA_METHOD( Exit )
END_LUA_TYPEINFO( ClinicLobbyScreenLogic )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::InitLayout( PF_Minigames::Minigames* _minigames )
{
	minigames = _minigames;

	clinic = minigames->GetNativeMinigame<PF_Minigames::Clinic>( "Clinic" );
	NI_VERIFY(IsValid(clinic), "", return);

  _minigames->GetCameraController()->ChangeCamera( clinic->GetClinicDesc()->cameraOptions );
  _minigames->GetCameraController()->ApplyResolutionModifcators();

  SetSelectedLevel( clinic->GetNextLevel() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::SetSelectedLevel( int newSel )
{
  NI_VERIFY(IsValid(clinic), "", return);

  int levelsNum = clinic->GetLevelNumber();

  if(newSel < 0)
    return;
  if(newSel >= levelsNum)
    return;
  selectedLevel = newSel;

  UI::ImageLabel * pDescWnd = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "LevelDescription", true );
  UI::Window * pStartButt = UI::GetChildChecked<UI::Window>( pBaseWindow, "StartButton", true );
  UI::Window * pPrevButt = UI::GetChildChecked<UI::Window>( pBaseWindow, "PrevLevel", true );
  UI::Window * pNextButt = UI::GetChildChecked<UI::Window>( pBaseWindow, "NextLevel", true );

  UI::ImageLabel * pNameDone = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "LevelNameDone", true );
  UI::ImageLabel * pNameDisabled = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "LevelNameDisabled", true );
  UI::ImageLabel * pNameActive = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "LevelNameActive", true );

  UI::ImageLabel * pMedalGold = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "MedalGold", true );
  UI::ImageLabel * pMedalSilver = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "MedalSilver", true );

  NI_VERIFY(pStartButt && pDescWnd && pPrevButt && pNextButt && pNameDone && pNameDisabled && pNameActive && pMedalGold && pMedalSilver,
     "Some of the lobby screen controls is missing", return);

  PF_Minigames::ClinicLevelUIDesc desc;
	clinic->GetLevelUIDesc(&desc, selectedLevel);

  pDescWnd->SetCaptionTextW(desc.desc);
  pStartButt->Enable(desc.available || gAllLevelsOpen);
  pPrevButt->Enable(selectedLevel > 0);
  pNextButt->Enable(selectedLevel < levelsNum - 1);

  if(!desc.available)
  {
    pNameDone->Show(false);
    pNameDisabled->Show(true);
    pNameDisabled->SetCaptionTextW(desc.name);
    pNameActive->Show(false);
  }
  else if(desc.bestStatus == PF_Minigames::EClinicLevelStatus::Incomplete)
  {
    pNameDone->Show(false);
    pNameDisabled->Show(false);
    pNameActive->Show(true);
    pNameActive->SetCaptionTextW(desc.name);
  }
  else //complete levels
  {
    pNameDone->Show(true);
    pNameDone->SetCaptionTextW(desc.name);
    pNameDisabled->Show(false);
    pNameActive->Show(false);
  }

  bool showGold = (desc.bestStatus == PF_Minigames::EClinicLevelStatus::GoldMedal);
  bool showSilver = (desc.bestStatus == PF_Minigames::EClinicLevelStatus::SilverMedal);
  pMedalGold->Show(showGold);
  pMedalSilver->Show(showSilver);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::Start()
{
	Weak<PF_Minigames::ClinicScreen> clinicScreen = new PF_Minigames::ClinicScreen();
  clinicScreen->Set(minigames, selectedLevel);
	NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( clinicScreen ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::OpenShop()
{
	PF_Minigames::ClinicShopScreen * shopScreen = new PF_Minigames::ClinicShopScreen();
	shopScreen->Set(minigames);
	NScreenCommands::PushCommand(NScreenCommands::CreatePushScreenCommand(shopScreen));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::SwitchToNextLevel()
{
  SetSelectedLevel( selectedLevel + 1 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::SwitchToPrevLevel()
{
  SetSelectedLevel( selectedLevel - 1 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::Exit()
{
  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( "ClinicLobbyScreen" ) );

  MinigameLobbyScreenLogic::ExitLobby();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicLobbyScreenLogic::RefreshNextLevel()
{
  NI_VERIFY( IsValid( clinic ), "", return );
  SetSelectedLevel( clinic->GetNextLevel() );
}

}
