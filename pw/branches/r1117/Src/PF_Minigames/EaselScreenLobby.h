#pragma once

#include "MinigameLobbyScreen.h"
#include "../Scene/Camera.h"

namespace PF_Minigames
{

#pragma region ForwardDeclarations

class Minigames;
class EaselScreenLogicLobby;

#pragma endregion ForwardDeclarations

class Easel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// easel lobby game screen
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselScreenLobby : public MinigameLobbyScreen
{
  NI_DECLARE_REFCOUNT_CLASS_1( EaselScreenLobby, MinigameLobbyScreen );

public:
	EaselScreenLobby();
	virtual ~EaselScreenLobby();

  EaselScreenLogicLobby * GetLogic() const { return logic; }

	// only one association allowed. will fail otherwise
	void AssociateWithMinigames(Minigames& minigames);
  
  void SetMaxLevel( int _maxLevel );
  void UpdateLobby();
  
  

  //IScreenBase
	virtual bool Init( UI::User * uiUser );
	virtual bool IsInited() const { return true; }
	virtual bool IsModal() const	{ return false; }
	virtual bool IsTransparent() const { return true; }
	virtual bool OnBeforeClose();

  virtual void OnBecameFront();
  virtual void OnNewFront( IScreenBase * pNewFrontScreen );

	virtual bool ProcessUIEvent( const Input::Event & message );

  
private:
	bool ProcessEaselEvent( const Input::Event & message );

	//
	Strong<EaselScreenLogicLobby> logic;

	CPtr<Minigames> associatedMinigames;

  NScene::SCameraPosition lastCamera;

	CPtr<Easel> localEasel;
  int maxLevel;
};

}