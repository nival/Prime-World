#pragma once

#include "MinigameScreen.h"
#include "../Scene/Camera.h"

namespace PF_Minigames
{

#pragma region ForwardDeclarations

class Minigames;
class EaselScreenLogic;

#pragma endregion ForwardDeclarations

class Easel;
class EaselMinigame;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main easel game screen
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselScreen : public MinigameScreen
{
	NI_DECLARE_REFCOUNT_CLASS_1( EaselScreen, MinigameScreen );

public:
	EaselScreen();
	virtual ~EaselScreen();

  const Strong<EaselScreenLogic>& GetLogic() const { return logic; }

	// only one association allowed. will fail otherwise
	void AssociateWithMinigames(Minigames& minigames);

  void AllowLMBClick(bool _fAllow) { fIsLMBAllowed = _fAllow; }
  void AllowRMBClick(bool _fAllow) { fIsRMBAllowed = _fAllow; }

  //IScreenBase
	virtual bool Init( UI::User * uiUser );
	virtual bool IsModal() const	{ return false; }
	virtual bool IsTransparent() const { return true; }
	virtual bool OnBeforeClose();

  virtual void Step( bool bAppActive );

  //These are no more event handlers, they are now called from UI/Lua
  void OnMouseMove( const UI::Point & point );
  void OnLMouseDown();
  void OnRMouseDown();
  void OnSkipMovie();

private:
   // mouse handlers
  bool MsgOnMouseMove( const Input::SSysParams & params );
  bool MsgOnLMouseDown( const Input::SSysParams & ) { OnLMouseDown(); return false; }
  bool MsgOnRMouseDown( const Input::SSysParams & ) { OnRMouseDown(); return false; }
  bool MsgOnLDoubleclick( const Input::SSysParams & ) { OnLMouseDown(); return false; }
  bool MsgOnSkipMovie() { OnSkipMovie(); return false; }

  bool fIsLMBAllowed;
  bool fIsRMBAllowed;
	
	Strong<EaselScreenLogic> logic;

	CPtr<Minigames> associatedMinigames;

  NScene::SCameraPosition lastCamera;

  CPtr<EaselMinigame> easelMinigame;

	CPtr<Easel> localEasel;
};

}