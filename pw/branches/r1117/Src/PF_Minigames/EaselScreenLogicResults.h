#pragma once

#include "Client/ScreenUILogicBase.h"
#include "UI/ImageLabel.h"
#include "UI/RadioButton.h"

namespace NWorld
{
  class PFBaseHero;
}

namespace PF_Minigames
{

class EaselNotifier;
class Minigames;
class Easel;
class EaselMinigame;
class EaselTutorial;

class EaselResultsPlayerNMap;

class EaselScreenLogicResults : public UI::ClientScreenUILogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( EaselScreenLogicResults, UI::ClientScreenUILogicBase );
  DECLARE_LUA_TYPEINFO( EaselScreenLogicResults );

public:
	EaselScreenLogicResults();

	void Init( PF_Minigames::Minigames* minigames );
  void OnLoadedScreenLayout();

  void Step( float deltaTime );

  //Lua
  void SelectHero( int index );
	void TransferScroll();
  void DiscardScroll();

  DEFINE_LUA_READONLY_PROPERTY( paintId, int, paintId );

private:
  enum EStatus { eStatusEmpty, eStatusNoValidTargets, eStatusWaitForTransfer, eStatusTransferFailure };

  //Lua-properties:
  float                           waitTime;
  int                             paintId;

  // minigames object
  CPtr<PF_Minigames::Minigames>   associatedMinigames;
  CPtr<Easel>                     localEasel;
  CPtr<EaselMinigame>             easelMinigameClient;

  EStatus                         uiStatus;
  float                           statusAutoClearTimeLeft;

  vector<Weak<UI::RadioButton>>   heroesButtons;
  Weak<UI::Window>                transferButton;
  Weak<UI::Window>                discardButton;
  Weak<UI::Window>                noValidTargetsText;
  Weak<UI::Window>                waitText;
  Weak<UI::Window>                failureText;

  Weak<UI::Window>                inputBlocker;

  vector<CPtr<NWorld::PFBaseHero>> currentTargets;
  CPtr<NWorld::PFBaseHero>        selectedTarget;

  list<Strong<EaselResultsPlayerNMap>> playerNameMaps;

  float                           timeToTargetsUpdate;

  void GetDropTargets();

  void SetupScrollIcon();
  void SetupRewardLayouts();
  void SetupTransferTargets();

  void SetStatus( EStatus st, float autoClearPeriod = 0 );
  void UpdateStatusWindows();
  
  enum ETransferWndStatus { eTransferNone, eTransferWating, eTransferFailed };
  void UpdateTransferWindows( ETransferWndStatus status );
  void UpdateSelection();

  void FinishWithThis();
};

} // namespace PF_Minigames
