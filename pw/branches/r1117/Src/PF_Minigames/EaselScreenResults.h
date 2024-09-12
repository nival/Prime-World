#pragma once

#include "MinigameScreen.h"
#include "../Scene/Camera.h"

namespace PF_Minigames
{

#pragma region ForwardDeclarations

class Minigames;
class EaselScreenLogicResults;

#pragma endregion ForwardDeclarations

class Easel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// easel game results screen
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselScreenResults : public MinigameScreen
{
	NI_DECLARE_REFCOUNT_CLASS_1( EaselScreenResults, MinigameScreen );

public:
	EaselScreenResults();
	virtual ~EaselScreenResults();

  EaselScreenLogicResults * GetLogic() const { return logic; }

	// only one association allowed. will fail otherwise
	void AssociateWithMinigames(Minigames& minigames);

	//IScreenBase
	virtual bool Init( UI::User * uiUser );
	virtual bool IsInited() const { return true; }
	virtual bool IsModal() const	{ return false; }
	virtual bool IsTransparent() const { return true; }
	virtual bool OnBeforeClose();

  virtual void OnNewFront(IScreenBase * pNewFrontScreen);

	virtual bool ProcessUIEvent( const Input::Event & message );

private:

  // event processing functions
	bool ProcessEaselEvent( const Input::Event & message );

	//
	Strong<EaselScreenLogicResults> logic;

	CPtr<Minigames> associatedMinigames;

  NScene::SCameraPosition lastCamera;

	CPtr<Easel> localEasel;
};

} //namespace PF_Minigames
