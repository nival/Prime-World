#pragma once

#include "MinigameScreenLogic.h"

namespace UI
{
  class Button;
  class ProgressBar;
  class Window;
  class ImageLabel;
  class FlashContainer2;
}

namespace Render
{
  class BaseMaterial;
}

namespace NDb
{
  enum EBoostType;
}

namespace PF_Minigames
{

class LuxBoost;
class LuxBoostNameMapProxy;
class EaselNotifier;
class Minigames;
class LuxGameLogic;

class EaselScreen;

const int EASEL_BOOSTS_NUM         = 3; //5; // max amount of boosts

class EaselScreenLogic;
class EaselMinigame;



//////////////////////////////////////////////////////////////////////////
//
// main Easel game screen logic class
//
//////////////////////////////////////////////////////////////////////////
class EaselScreenLogic : public MinigameScreenLogic
{
  NI_DECLARE_REFCOUNT_CLASS_1( EaselScreenLogic, MinigameScreenLogic );
  DECLARE_LUA_TYPEINFO( EaselScreenLogic );

public:
	EaselScreenLogic();
  virtual ~EaselScreenLogic();

  virtual void ExitGame();

  // used from screen object
	void Init( PF_Minigames::Minigames* minigames, EaselScreen * _screen );
  void InitBoosts();
  void Uninit();

  // common step processing (used to show boosts cooldown)
  void ProcessStep();

  // boosts management functions
  void FireBoostByButtIndex( int index, bool heroic );

  //Lua functions to translate mouse input from Lua/UI
  //Unsued for now and on
  //TODO: Remove them
  void OnMouseMove( int x, int y );
  void OnLMouseDown();
  void OnRMouseDown();

private:

  struct BoostBtnCommonData
  {
    bool              used;
    bool              forbidden;
    CPtr<LuxBoost>    wpBoost;

    BoostBtnCommonData() : used( false ), forbidden( false ) {}
  };

  struct BoostBtnData : public BoostBtnCommonData
  {
    BoostBtnData() {}

    Weak<UI::Button>        button;
    Weak<UI::ImageLabel>    priceWnd;
    Weak<UI::ProgressBar>   progressBar;
    Strong<PF_Minigames::LuxBoostNameMapProxy>  nameMap;

    Render::BaseMaterial * GetButtonMaterial();
  };

  typedef nstl::vector<BoostBtnData> BoostButtons;

  Weak<EaselScreen>  screen;

  // operational flag
  bool fIsInit;

  // boosts container 
  BoostButtons boostButtonsInGame;

  void UpdateInGameButtonStates();    // boost buttons update ops

  void InitInGameBoostButtonsContainer();

  // boost button layout layout helper method
  void SetupBoostBtnLayout( UI::Window * _baseWindow, BoostBtnData& _data, LuxBoost* _boost, const char * _layoutStr, const char * bindName );

  CPtr<EaselMinigame> easelMinigame;
  CPtr<LuxGameLogic> gameLogic;
};

}
