#pragma once

#include "../Client/ScreenUILogicBase.h"
#include "ClinicUIDesc.h"

namespace PF_Minigames
{
	class Clinic;
	class ClinicResultsScreen;
}

namespace NDb
{
		struct MinigameUIStylesDesc;
		struct DBMinigame_Clinic;
}

namespace UI
{

class ClinicResultsScreenLogic : public ClientScreenUILogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClinicResultsScreenLogic, ClientScreenUILogicBase );
  DECLARE_LUA_TYPEINFO( ClinicResultsScreenLogic );

public:
	ClinicResultsScreenLogic() :
  pDesc(0),
  updateStart(0),
  lastGoldValue(-1), lastSplashValue(0)
  {}

	void OnLeftClick();
  void InitLayout(const PF_Minigames::ClinicCreepsUIDesc & creeps, const PF_Minigames::ClinicLevelUIDesc & _levelUIDesc, const NDb::DBMinigame_Clinic * _pDBDesc);
  void Step( float deltaTime );

  ///Lua///
	void Exit();

private:
  typedef list<Weak<UI::Window>>  TWndList;
  typedef map<float, int>         TGoldAnim; // time -> gold value

	const NDb::DBMinigame_Clinic *  pDesc;
  PF_Minigames::ClinicLevelUIDesc levelUIDesc;
  TWndList                        windowsToShow;
  TGoldAnim                       goldAnim;
  float                           updateStart;
  int                             lastGoldValue;
  int                             lastSplashValue;

  string CreepWndName(int index) { return NStr::StrFmt("Creep%02x", index); }
  void AddGoldAnim(float time, int deltaGold);
  void AddCreatures(const PF_Minigames::ClinicCreepsUIDesc & creeps, float * pShowTime);
	void UpdateMedal(float * pShowTime);
	void UpdateText(bool bWon);
  void UpdateGold(float time);
	const NDb::MinigameUIStylesDesc & GetUIDB() const;
};

}