#include "stdafx.h"

#include "UnitInfoNew.h"
#include "PFHero.h"

#include "AdventureFlashInterface.h"
#include "../UI/FlashContainer2.h"

#include "UIEventHandler.h"

#include "FlashFSCommands.h"

#include "HeroRankCalculator.h"
#include "DBHeroRanks.h"

#include "ClientVisibilityHelper.h"

namespace NGameX
{

HeroInfoNew::HeroInfoNew( AdventureFlashInterface* _flashInterface, NWorld::PFBaseHero const* _hero, bool _isEnemy, HeroRankCalculator * heroRankCalculator, bool isPremium, string & flagIcon, wstring & flagTooltip)
  : flashInterface (_flashInterface)
  , hero(_hero)
  , isEnemy(_isEnemy)
  , isCameraLocked(false)
{
  NI_VERIFY(IsValid(hero), "invalid hero", return);
  
  memset(&currentParams, 0,sizeof(HeroInfoParams));

  if (!IsValid(flashInterface))
    return;

  const char * texturePath =  hero->GetUiAvatarImage()? hero->GetUiAvatarImage()->textureFileName.c_str() : "";

  const NDb::Rank & rank = heroRankCalculator->GetRank(hero->GetRaiting());

  NDb::EFaction originalFaction = hero->GetOriginalFaction();
  if ( hero->GetFaction() == NDb::FACTION_NEUTRAL )
    originalFaction = NDb::FACTION_NEUTRAL;

  const float rating = hero->GetRaiting();
  const int heroId = hero->GetPlayerId();

  flashInterface->SetHeroIdentity(
    hero->GetPlayerName(),
    hero->GetDescription(),
    heroId,
    texturePath,
    (hero->GetZZimaSex() == ZZSEX_MALE),
    isEnemy,
    hero->GetPlayer()->IsBot(),
    hero->GetForce(true),
    hero->GetFaction(),
    originalFaction,
    rating,
    heroRankCalculator->GetRankIcon(originalFaction, rank),
    heroRankCalculator->GetRankName(originalFaction, rank),
    isPremium,
    hero->GetPartyId(),
    flagIcon,
    flagTooltip,
    hero->GetAnimatedAvatar(),
    hero->GetLeagueIndex(),
    hero->GetOwnLeaguePlace(),
    hero->GetLeaguePlaces());
  flashInterface->SetHeroChatMuted(
    heroId,
    hero->GetPlayer()->IsChatMuted());

  if (hero->HasCustomEnergy())
  {
    const NDb::Ptr<NDb::HeroResource>& dbHeroResource = hero->GetDbHero()->uniqueResource;

    flashInterface->SetHeroCustomEnergy(
      heroId,
      dbHeroResource->name.GetText(),
      dbHeroResource->uiManaBarColor.Dummy);
  }
}

void HeroInfoNew::Update()
{
  if ( !IsValid(hero) || !IsValid(flashInterface))
    return;

  Recrypt( currentParams );

  HeroInfoParams heroParams;
  heroParams.level = hero->GetNaftaLevel();
  heroParams.curHealth = Round (hero->GetHealth());
  heroParams.maxHealth =  Round (hero->GetMaxHealth());
  heroParams.healthRegen = hero->GetLifeRegenTotal();
  heroParams.ultimateCoolDown = hero->GetUltimateCD();

  if (hero->HasCustomEnergy())
  {
    heroParams.curMana = hero->IsDead() ? 0 : Round(hero->GetCustomEnergyValue());
    heroParams.maxMana = Round (hero->GetCustomEnergyMaximum());
    heroParams.manaRegen = hero->GetCustomEnergyRegeneration();
  }
  else
  {
    heroParams.curMana =  hero->IsDead() ? 0 : Round (hero->GetMana());
    heroParams.maxMana =  Round (hero->GetMaxMana());
    heroParams.manaRegen = hero->GetEnergyRegenTotal();
  }

  heroParams.isVisible = ClientVisibilityHelper::IsVisibleForPlayer(hero);
  heroParams.isPickable = !hero->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPICK);
  heroParams.timeToRessurect = hero->GetRespawnDelay();
  heroParams.channgeling = hero->GetChannellingProgress();

  if (!hero->IsDead()&&hero->GetHealth()<1)
    heroParams.curHealth = 1;

  if (heroParams == currentParams)
    return;

  const bool attachMode = NGlobal::GetVar( "lock_camera" ).Get<bool>();
  heroParams.isCameraLocked = attachMode;

  //camera tricks
  //hero is dead now
  if(heroParams.curHealth < EPS_VALUE && currentParams.curHealth > EPS_VALUE)
  {
    heroParams.isCameraLocked = false;
    //save camera status before dead
    isCameraLocked = attachMode;
  }
  //hero respawned
  else  if(heroParams.curHealth > EPS_VALUE && currentParams.curHealth < EPS_VALUE)
  {
    //restore camera status
    heroParams.isCameraLocked = isCameraLocked;
  }

  currentParams = heroParams;
  flashInterface->SetHeroParams(hero->GetPlayerId(), currentParams);

}

SelectionInfo::SelectionInfo( UI::FlashContainer2* _wnd, AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler )
 : flashInterface (_flashInterface)
 , eventHandler(_eventHandler)
{
   memset(&currentParams, 0,sizeof(HeroInfoParams));

   using namespace FlashFSCommands;

   _wnd->AddFSListner(ConvertToString(SelectionClicked), this);
   _wnd->AddFSListner(ConvertToString(SelectionDoubleClicked), this);
}

void SelectionInfo::SetUnit( NWorld::PFBaseUnit const* _unit, bool _isEnemy )
{
  if ( !IsValid(flashInterface) )
    return;

  isEnemy = _isEnemy;
  unit = _unit;

  unitAsHero = dynamic_cast<NWorld::PFBaseHero const *> (unit.GetPtr());

  const char* const texturePath =  IsValid(unit) ? unit->GetUiAvatarImage()->textureFileName.c_str() : "";

  // friendly clone should be always recognized as a simple unit, not a hero of the team
  if (IsValid(unitAsHero))
    flashInterface->SetSelectionInfoIcon(texturePath, (unitAsHero->IsClone() && !isEnemy) ? -1 : unitAsHero->GetPlayerId(), (unitAsHero->GetZZimaSex() == ZZSEX_MALE), unitAsHero->GetAnimatedAvatar());
  else
    flashInterface->SetSelectionInfoIcon(texturePath, -1, false, false);

  if (!IsValid(unit))
    memset(&currentParams, 0,sizeof(HeroInfoParams));

  Update();
}

void SelectionInfo::Update()
{
  if (!IsValid(unit))
    return;

  Recrypt( currentParams );

  HeroInfoParams newUnitParams;

  if (IsValid(unitAsHero))
  {
    newUnitParams.level = unit->GetNaftaLevel();

    newUnitParams.curHealth = Round (unit->GetHealth());
    newUnitParams.maxHealth = Round (unit->GetMaxHealth());
    newUnitParams.healthRegen = unit->GetLifeRegenTotal();

    if (unitAsHero->HasCustomEnergy())
    {
      newUnitParams.curMana = unit->IsDead() ? 0 : Round(unitAsHero->GetCustomEnergyValue());
      newUnitParams.maxMana = Round(unitAsHero->GetCustomEnergyMaximum());
      newUnitParams.manaRegen = unitAsHero->GetCustomEnergyRegeneration();
    }
    else
    {
      newUnitParams.curMana = Round (unit->IsDead() ? 0: unit->GetMana());
      newUnitParams.maxMana = Round (unit->GetMaxMana());
      newUnitParams.manaRegen = unit->GetEnergyRegenTotal();
    }

    newUnitParams.channgeling = unit->GetChannellingProgress();
  }
  else
  {
    newUnitParams.level = unit->GetStatValue( NDb::STAT_LEVEL );
    newUnitParams.curHealth =  Round (unit->GetHealth());
    newUnitParams.curMana =  Round (unit->IsDead()? 0: unit->GetMana());
    newUnitParams.maxHealth =  Round (unit->GetMaxHealth());
    newUnitParams.maxMana =  Round (unit->GetMaxMana());
    newUnitParams.channgeling = unit->GetChannellingProgress();
    newUnitParams.healthRegen = unit->GetLifeRegenTotal();
    newUnitParams.manaRegen = unit->GetEnergyRegenTotal();
  }

  if (!unit->IsDead()&&unit->GetHealth()<1)
    newUnitParams.curHealth = 1;
    
  if (newUnitParams == currentParams)
    return;

  currentParams = newUnitParams;

  // show player name only for heroes and true clones
  const wstring & descTitle = IsValid(unitAsHero) && unitAsHero->GetPlayerId() > -1 ? unitAsHero->GetPlayerName() : unit->GetDescription();

  bool looksLikeEnemy = isEnemy;

  // HACK: стоит выделить в контроллер представления
  if (ClientVisibilityHelper::IsSpectatorMode())
  {
    switch (unit->GetFaction())
    {
    case NDb::FACTION_FREEZE:
      looksLikeEnemy = false;
      break;
    case NDb::FACTION_BURN:
      looksLikeEnemy = true;
      break;
    default:
      break;
    }
  }

  const int heroId = unit->IsHero() ? unit->GetPlayerId() : -1;

  flashInterface->SetSelectionParams(descTitle, newUnitParams, looksLikeEnemy, heroId);
}

void SelectionInfo::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  if (!IsValid(eventHandler) || !IsValid(unit))
    return;

  using namespace FlashFSCommands;

 if (Equals(SelectionClicked, listenerID))
   eventHandler->OnUnitAvatarMouseClick(unit, UI::EMButton::Left);
 else if (Equals(SelectionDoubleClicked, listenerID))
   eventHandler->OnUnitAvatarMouseDblClick(unit, UI::EMButton::Left);
}
}

NI_DEFINE_REFCOUNT( NGameX::HeroInfoNew )
NI_DEFINE_REFCOUNT( NGameX::SelectionInfo )
