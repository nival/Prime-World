#pragma once

namespace UI
{
  namespace EMButton
  {
    enum Enum;
  }
}

namespace NWorld
{
  class PFAbilityData;
  class PFBaseUnit;
}

namespace NGameX
{

_interface IUIEventHandler : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IUIEventHandler, IBaseInterfaceST );

  virtual bool OnTalentSetButtonClick(int level, int slot) = 0;
  virtual bool OnPortalClick() = 0;
  virtual bool OnUnitAvatarMouseClick(NWorld::PFBaseUnit *pUnit, int action) = 0;
  virtual bool OnUnitAvatarMouseDblClick(NWorld::PFBaseUnit *pUnit, int action) = 0;
  virtual void CancelObservingObject() = 0;
  virtual bool StartSpectate( const int& playerIdx ) = 0;
  virtual bool StartSpectateById( const int& playerId ) = 0;

  //minimap
  virtual void MinimapActionBegin(UI::EMButton::Enum action, float x, float y) = 0;
  virtual void MinimapActionMove(float x, float y) = 0;
  virtual void MinimapActionEnd(UI::EMButton::Enum action, float x, float y) = 0;
  virtual void MinimapOver(bool over, float x, float y) = 0;
  virtual void MinimapSignalBtnActionEnd() =0 ;
  virtual void LockCamera(bool lock) = 0;

  //shop
  virtual bool OnShopButtonClick(int item) = 0;

  //inventory
  virtual void OnItemButtonClick(int item) = 0;

  //itemtooltips
  virtual void TargetZoneTooltip(NWorld::PFAbilityData const *pAbilityData) = 0;

  //esc menu
  virtual void ExitGame( bool returnToCastle ) = 0;
  virtual void SkipTutorial() = 0;
  virtual void DisableHotkeys(bool disable) = 0;

  virtual void ResetTargetState() = 0;
  
  virtual void ContinueGame() = 0;
  virtual void OnEscMenuShow() = 0;

  virtual void ShareFinalStatistics()= 0;

  virtual void PlaySameTeam(const bool agreed) = 0;
};

}