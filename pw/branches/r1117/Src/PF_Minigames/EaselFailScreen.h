#pragma once

#include "MinigameScreen.h"
#include "../Scene/Camera.h"

namespace PF_Minigames
{
#pragma region ForwardDeclarations

  class Minigames;
  class EaselFailScreenLogic;

#pragma endregion ForwardDeclarations

  class Easel;

//////////////////////////////////////////////////////////////////////////
//
// easel level fail screen
//
//////////////////////////////////////////////////////////////////////////
class EaselFailScreen : public MinigameScreen
{
  NI_DECLARE_REFCOUNT_CLASS_1( EaselFailScreen, MinigameScreen );

public:
  EaselFailScreen();
  virtual ~EaselFailScreen();

  // only one association allowed. will fail otherwise
  void AssociateWithMinigames(Minigames& minigames);

  EaselFailScreenLogic * GetLogic() const { return logic; }

  // IScreenBase
  virtual bool Init( UI::User * uiUser );
  virtual bool IsInited() const { return true; }
  virtual bool IsModal() const	{ return false; }
  virtual bool IsTransparent() const { return true; }
  virtual bool OnBeforeClose();

  virtual void OnBecameFront();
  virtual void OnNewFront(IScreenBase * pNewFrontScreen);

  virtual bool ProcessUIEvent( const Input::Event & message );

private:
  Strong<EaselFailScreenLogic> logic;

  CPtr<Minigames> associatedMinigames;
  CPtr<Easel> localEasel;

  NScene::SCameraPosition lastCamera;  

protected:
};

}
