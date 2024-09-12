#pragma once

#include "MinigameScreen.h"

#include "ClinicShopScreenLogic.h"

namespace NScene
{
	_interface IScene;
}

namespace PF_Minigames
{

class MinigameWorldObject;
class MinigameCameraController;
class Clinic;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicShopScreen : public MinigameScreen
{
	NI_DECLARE_REFCOUNT_CLASS_1( ClinicShopScreen, MinigameScreen );

public:
	ClinicShopScreen();
	virtual ~ClinicShopScreen();

	void Set(Minigames * _minigames);

	virtual bool Init( UI::User * uiUser );

	virtual bool IsModal() const { return true; }
	virtual bool IsTransparent() const { return true; }

	virtual bool ProcessUIEvent(const Input::Event & message);
  virtual bool ProcessSceneEvent(const Input::Event & message);

private:
	// mouse handlers
  bool MsgOnMousemove( const Input::SSysParams & sysParams );
	bool MsgOnLMouseDown( const Input::SSysParams & sysParams );
  bool MsgOnMouseWheel( const Input::SSysParams & sysParams );
  bool MsgOnEscapeKey();

	Strong<UI::ClinicShopScreenLogic> logic;

	CPtr<Minigames> minigames;
  CPtr<PF_Minigames::Clinic> clinic;
};

} // namespace PF_Minigames
