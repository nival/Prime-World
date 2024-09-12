#pragma once

#include "MinigameScreen.h"

#include "ClinicResultsScreenLogic.h"
#include "ClinicUIDesc.h"

namespace NDb
{
		struct MinigameUIStylesDesc;
}

namespace PF_Minigames
{

class Minigames;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicResultsScreen : public MinigameScreen
{
	NI_DECLARE_REFCOUNT_CLASS_1( ClinicResultsScreen, MinigameScreen );

public:
  ClinicResultsScreen();
  virtual ~ClinicResultsScreen();

	void InitResults(const ClinicCreepsUIDesc & _creeps, const ClinicLevelUIDesc & _levelUIDesc, const NDb::DBMinigame_Clinic * _pDBDesc);

  virtual bool Init( UI::User * uiUser );

  bool IsModal() const { return true; }
  bool IsTransparent() const { return false; }

  bool MsgOnLMouseDown( const Input::SSysParams & );

protected:
	ClinicCreepsUIDesc creeps;
  ClinicLevelUIDesc levelUIDesc;
	const NDb::DBMinigame_Clinic * pDBDesc;

	Strong<UI::ClinicResultsScreenLogic> logic;
};

} // namespace PF_Minigames
