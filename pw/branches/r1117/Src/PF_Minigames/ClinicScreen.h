#pragma once

#include "MinigameScreen.h"

#include "ClinicScreenLogic.h"

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
class ClinicScreen : public MinigameScreen
{
	NI_DECLARE_REFCOUNT_CLASS_1( ClinicScreen, MinigameScreen );

public:
	ClinicScreen();
	virtual ~ClinicScreen();

	void Set(Minigames * _minigames, int _levelID);

	virtual bool Init( UI::User * uiUser );

	virtual bool IsModal() const { return false; }
	virtual bool IsTransparent() const { return true; }

  virtual void Step( bool bAppActive );
	virtual bool ProcessUIEvent( const Input::Event & message );
  virtual bool ProcessSceneEvent( const Input::Event & message );

  virtual bool GetCursor( string * id, const UI::Point & screenCoords ) const;

	UI::ClinicScreenLogic* GetLogic() const { return logic; }

private:
	// mouse handlers
	bool MsgOnMouseMove( const Input::SSysParams & sysParams );
	bool MsgOnLMouseDown( const Input::SSysParams & );
  bool MsgOnRMouseDown( const Input::SSysParams & );

  bool MsgOnEscapeKey();

	Strong<UI::ClinicScreenLogic> logic;
	CPtr<Minigames> minigames;
	int levelID; 
};

} // namespace PF_Minigames
