#pragma once

#include "../UI/FSCommandListner.h"
#include "AdventureFlashInterface.h"
#include "System/StarForce/HiddenVars.h"

namespace NWorld
{
  class PFBaseUnit;
  class PFBaseHero;
}

namespace CharType
{
  enum ECharType
  {
    OurHero = 0,
    Selection = 1
  };
}

namespace NDb
{
  enum EStat;
  enum EDerivativeStat;
  struct DBUIData;
}

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}


namespace NGameX
{

class AdventureFlashInterface;
class AdventureTooltip;
struct HeroInfoParams;

class CharInfoController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( CharInfoController, UI::IFSCommandListner, BaseObjectST );

public:
  CharInfoController( UI::FlashContainer2* flashContainer, UI::ImageLabel* tooltipWnd, NDb::Ptr<NDb::DBUIData> _uiData,
                      AdventureFlashInterface* _flashInterface, CharType::ECharType _charType );
  ~CharInfoController();

  bool IsStatsActive() const { return isStatsActive; }
  bool IsTalentsActive() const { return isTalentsActive; }
  void ActivateStats( bool activate );
  void ActivateTalents( bool activate );

  void Update( int mouseX, int mouseY, bool isVisible );

  const NWorld::PFBaseUnit* GetUnit() const { return pUnit; }
  void SetUnit( const NWorld::PFBaseUnit* _unit, bool isVisible );
  void SetUnit( const NWorld::PFBaseUnit* _unit );

  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* wnd, const char* listenerID, const char* args, const wchar_t * argsW   );
  
private:
  struct BaseStatParams
  {
    NDb::EStat statID;
    int baseValue;
    int addition;

    BaseStatParams()
    {
      baseValue = addition = -1;
    }
  };

  struct DerivativeStatsParams
  {
    NDb::EDerivativeStat statID;
    int value;
    int multiplier;

    DerivativeStatsParams()
    {
      value = -1;
      multiplier = 1;
    }
  };

  struct TalentParams
  {
    int level;
    int slot;
    bool isBought;
    wstring tooltip;

    TalentParams()
    {
      level = slot = 0;
      isBought = false;
    }
  };

  wstring CalculateBaseTooltip( NDb::EStat baseID ) const;
  wstring CalculateDerivativeTooltip( NDb::EDerivativeStat derivativeID ) const;
  wstring CalculateTalentTooltip( int slot, int level ) const;

  int FindTalent( int slot, int level );

  void UpdateInfo( bool bUpdateTalensState = true );
  bool ShouldUpdateParams();
  void CacheTooltips();

  bool isStatsActive;
  bool isTalentsActive;

  NDb::Ptr<NDb::DBUIData> uiData;
  Weak<UI::FlashContainer2> flashWnd;

  CObj<AdventureTooltip> tooltip;
  ConstPtr<NWorld::PFBaseUnit> pUnit;
  ConstPtr<NWorld::PFBaseHero> pHero;
  Weak<AdventureFlashInterface> flashInterface;
  CharType::ECharType charType;

  vector<BaseStatParams>        baseStats;
  vector<DerivativeStatsParams> derivativeStats;
  vector<TalentParams>          talents;

  map<NDb::EDerivativeStat, wstring> derivativeTooltips;
  map<NDb::EStat, wstring>           baseTooltips;

  //unit params
  Protection::HiddenVar<int, 19>::T level;
  Protection::HiddenVar<int, 20>::T curHealth;
  Protection::HiddenVar<int, 21>::T maxHealth;
  Protection::HiddenVar<int, 22>::T curMana;
  Protection::HiddenVar<int, 23>::T maxMana;

  bool isUnitVisible;
  
private:
  void RecryptImpl()
  {
    Recrypt( level );
    Recrypt( curHealth );
    Recrypt( maxHealth );
    Recrypt( curMana );
    Recrypt( maxMana );
  }
};

}