#pragma once

#include "MinigameLobbyScreenLogic.h"

namespace UI
{
  class Button;
}

namespace NDb
{
  enum EBoostType;
}

namespace PF_Minigames
{

class EaselNotifier;
class Minigames;
class Easel;
class EaselMinigame;
_interface IPriestessProxy;
class LuxBoostNameMapProxy;
class EaselTutorial;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselScreenLogicLobby : public MinigameLobbyScreenLogic
{
	NI_DECLARE_REFCOUNT_CLASS_1( EaselScreenLogicLobby, MinigameLobbyScreenLogic );
  DECLARE_LUA_TYPEINFO( EaselScreenLogicLobby );

public:

	EaselScreenLogicLobby();
  virtual ~EaselScreenLogicLobby();

	void Init( PF_Minigames::Minigames* minigames, int _maxLevel );
  void InitLayout();
  void Uninit();

  void SetMaxLevel(int _maxLevel);
  void UpdateLobby();

  // function called from lua
	virtual void ExitGame();

  void Start();
  bool IsPaintLocked(int id);

  bool IsCanBuyBoostsRegen();

  const char * CurrentLevelAward() const;

  void OnLevelChanged();
 
  void OnRegenerateClicked();
  
  void UpdateBoostsImages();
  
  int GetLevelForPaintID( int paintId );

  virtual void Step( float deltaTime );
  
  DEFINE_LUA_PROPERTY( paintId, int, paintId );
  DEFINE_LUA_PROPERTY( currentLevel, int, currentLevel );
  DEFINE_LUA_READONLY_PROPERTY( maxLevel, int, maxLevel );

private:

  typedef map<NDb::EBoostType, Strong<PF_Minigames::LuxBoostNameMapProxy> > BoostsNameMaps;
  // operational flag
  bool fIsInit;

  int paintId;
  int currentLevel;
  int maxLevel;

  Weak<UI::Window> levelSelectorWindow;
  Weak<UI::Window> paintSelectorWindow;
  
  // regenerate button base tooltip
  wstring          regenTooltip;
  Weak<UI::Button> ptrRegenBtn;

  // minigames object
  CPtr<EaselMinigame>  easelMinigame;
  CPtr<Easel>  localEasel;

  // priestess proxy object
  CPtr<IPriestessProxy> priestessProxy;

  //Namemaps for used boosts
  BoostsNameMaps  boostsNamemaps;
};

} // namespace PF_Minigames
