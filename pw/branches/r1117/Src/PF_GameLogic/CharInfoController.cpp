#include "StdAfx.h"
#include "CharInfoController.h"

#include "../System/InlineProfiler.h"

#include "../UI/FlashContainer2.h"
//#include "../UI/ImageLabel.h"

#include "AdventureTooltip.h"
#include "PrecompiledTooltips.h"
#include "FlashFSCommands.h"

#include "AdventureScreen.h"
#include "AdventureFlashInterface.h"

#include "PFBaseUnit.h"
#include "PFMaleHero.h"
#include "PFTalent.h"
#include "DBStats.h"
#include "UnitNameMap.h"


namespace NGameX
{

CharInfoController::CharInfoController( UI::FlashContainer2* flashContainer, UI::ImageLabel* tooltipWnd, NDb::Ptr<NDb::DBUIData> _uiData,
                                        AdventureFlashInterface* _flashInterface, CharType::ECharType _charType )
  : flashInterface( _flashInterface )
  , charType( _charType )
  , flashWnd( flashContainer )
  , uiData( _uiData )
  , isUnitVisible( false )
  , isStatsActive( false )
  , isTalentsActive( false )
{
  tooltip = new AdventureTooltip( tooltipWnd );

  level = curHealth = maxHealth = curMana = maxMana = 0;

  //base stats
  baseStats.reserve( 9 );
  BaseStatParams statParams;
  
  statParams.statID = NDb::STAT_ATTACKSPEED;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_MOVESPEED;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_STRENGTH;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_INTELLECT;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_DEXTERITY;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_STAMINA;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_WILL;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_LIFE;
  baseStats.push_back( statParams );

  statParams.statID = NDb::STAT_ENERGY;
  baseStats.push_back( statParams );

  //derivative stats
  derivativeStats.reserve( 7 );
  DerivativeStatsParams derStatParams;

  derStatParams.statID = NDb::DERIVATIVESTAT_DAMAGEMIN;
  derivativeStats.push_back( derStatParams );

  derStatParams.statID = NDb::DERIVATIVESTAT_DAMAGEMAX;
  derivativeStats.push_back( derStatParams );

  derStatParams.statID = NDb::DERIVATIVESTAT_CRITCHANCE;
  derivativeStats.push_back( derStatParams );

  derStatParams.statID = NDb::DERIVATIVESTAT_ATTACKSPERSECOND;
  derStatParams.multiplier = 100;
  derivativeStats.push_back( derStatParams );

  derStatParams.statID = NDb::DERIVATIVESTAT_PENETRATIONTOTAL;
  derStatParams.multiplier = 100;
  derivativeStats.push_back( derStatParams );

  derStatParams.statID = NDb::DERIVATIVESTAT_SPIRITDEFENCE;
  derStatParams.multiplier = 100;
  derivativeStats.push_back( derStatParams );

  derStatParams.statID = NDb::DERIVATIVESTAT_BODYDEFENCE;
  derStatParams.multiplier = 100;
  derivativeStats.push_back( derStatParams );
}

CharInfoController::~CharInfoController()
{
  if ( isStatsActive )
  {
    ActivateStats( false );
  }
  if ( isTalentsActive )
  {
    ActivateTalents( false );
  }
}

void CharInfoController::SetUnit( const NWorld::PFBaseUnit* _unit )
{
  SetUnit( _unit, true );
}

void CharInfoController::SetUnit( const NWorld::PFBaseUnit* _unit, bool isVisible )
{
  if ( !flashInterface )
  {
    return;
  }
  
  pUnit = _unit;

  if ( !IsValid( pUnit ) )
  {
    return;
  }

  if ( pUnit->IsHero() )
  {
    pHero = static_cast<const NWorld::PFBaseHero*>( pUnit.GetPtr() );

    int numLevels = NDb::KnownEnum<NDb::ETalentLevel>::sizeOf;
    int numSlots  = NDb::KnownEnum<NDb::ETalentSlot>::sizeOf;
    bool shouldFill = talents.empty();

    for ( int level = 0; level < numLevels; ++level )
    {
      for ( int slot = 0; slot < numSlots; ++slot )
      {
        if ( shouldFill )
        {
          TalentParams talent;
          talent.level = level;
          talent.slot = slot;
          talents.push_back( talent );
        }
      }
    }
  }

  //update stats and tooltips
  UpdateInfo( isVisible );
  ShouldUpdateParams(); //update data
  CacheTooltips();
  isUnitVisible = isVisible;
}

void CharInfoController::CacheTooltips()
{
  for ( int i = 0; i < baseStats.size(); ++i )
  {
    BaseStatParams &baseStat = baseStats[i];
    baseTooltips[baseStat.statID] = CalculateBaseTooltip( baseStat.statID );
  }

  for ( int i = 0; i < derivativeStats.size(); ++i )
  {
    DerivativeStatsParams& derivativeStat = derivativeStats[i];
    derivativeTooltips[derivativeStat.statID] = CalculateDerivativeTooltip( derivativeStat.statID );
  }

  for ( int i = 0; i < talents.size(); ++i )
  {
    TalentParams& talent = talents[i];
    talent.tooltip = CalculateTalentTooltip( talent.slot, talent.level );
  }
}

void CharInfoController::Update( int mouseX, int mouseY, bool isVisible )
{
  NI_PROFILE_FUNCTION;

  if ( !IsValid( flashInterface )|| !IsValid( pUnit ) )
  {
    return;
  }

  //cache tooltips if we lost sight for the unit
  if ( isUnitVisible && !isVisible )
  {
    CacheTooltips();
  }

  bool unitParamsChanged = false;

  //update params only in case of visibility
  if ( isVisible )
  {
    UpdateInfo();
    unitParamsChanged = ShouldUpdateParams();
  }

  bool isHero = pUnit->IsHero();
  int heroId = isHero ? pHero->GetPlayerId() : -1;

  //update if active and params changed or update when unit visibility changed
  if ( unitParamsChanged || ( isUnitVisible != isVisible ) )
  {
    if ( isStatsActive )
    {
      flashInterface->SetCharStatUnitParams( charType == CharType::Selection,heroId, level, curHealth, maxHealth, curMana, maxMana, isVisible );
    }
  }

  isUnitVisible = isVisible;

  if ( tooltip->IsVisible() )
  {
    tooltip->SetLocation( mouseX, mouseY );
  }
}


void CharInfoController::UpdateInfo( bool bUpdateTalensState /*= true*/ )
{
  const bool customEnergy = pUnit->IsHero() && pHero->HasCustomEnergy();

  for ( int i = 0; i < baseStats.size(); ++i ) 
  {
    BaseStatParams& baseStat = baseStats[i];

    bool recommend = true;

    int baseValue;
    int addition;

    switch (baseStat.statID)
    {
    case NDb::STAT_ENERGY:
      if (customEnergy)
      {
        recommend = false;
        baseValue = Round(pHero->GetCustomEnergyValue());
        addition = 0;
        break;
      }
      // fall through
    default:
      {
        const NWorld::StatValueWithModifiers* value = pUnit->GetStat( baseStat.statID );

        baseValue = Round( value->GetUnmodifiedValue() );
        addition = Round( value->GetValue() ) - baseValue;
      }
    }

    if ((baseStat.baseValue == baseValue) && (baseStat.addition == addition))
      continue;

    baseStat.baseValue = baseValue;
    baseStat.addition = addition;

    if ( isStatsActive )
    {
      const bool isImportant = recommend && (pUnit->IsHero() ? pHero->IsRecommended(baseStat.statID) : false);

      flashInterface->SetBaseStat( charType == CharType::Selection, baseStat.statID, baseStat.baseValue, baseStat.addition, isImportant );
    }
  }

  RecryptImpl();
  
  for ( int i = 0; i < derivativeStats.size(); ++i ) 
  {
    DerivativeStatsParams& stat = derivativeStats[i];
    int value = Round( pUnit->GetStatValue( stat.statID ) * stat.multiplier );
    if ( value != stat.value )
    {
      stat.value = value;
      if ( isStatsActive )
      {
        flashInterface->SetDerivativeStat( charType == CharType::Selection, stat.statID, stat.value );
      }
    }
  }

  if ( bUpdateTalensState && ( charType == CharType::Selection ) && pUnit->IsHero() )
  {
    for ( int i = 0; i < talents.size(); ++i ) 
    {
      TalentParams& talent = talents[i];
      NWorld::PFTalent* pTalent = pHero->GetTalent( talent.level, talent.slot );
      bool isBought = pTalent ? pTalent->IsActivated() : false;

      if ( talent.isBought != isBought )
      {
        talent.isBought = isBought;
        if ( isTalentsActive )
        {
          TalentUIState::ETalentUIState talentState = isBought ? TalentUIState::Bought : TalentUIState::NotEnoughDevPoints;
          flashInterface->SetSelectionTalentState( talent.slot, talent.level, talentState );
        }
      }
    }
  }
}

bool CharInfoController::ShouldUpdateParams()
{
  const bool hero = pUnit->IsHero();
  const bool customEnergy = hero && pHero->HasCustomEnergy();

  int newLevel = hero ? pUnit->GetNaftaLevel() : pUnit->GetStatValue( NDb::STAT_LEVEL );
  int newCurHealth;
  int newCurMana;
  int newMaxHealth = Round( pUnit->GetMaxHealth() );
  int newMaxMana;

  if (pUnit->IsDead())
  {
    newCurHealth = 0;
    newCurMana = 0;
  }
  else
  {
    if (pUnit->GetHealth() > 1.f)
      newCurHealth = Round(pUnit->GetHealth());
    else
      newCurHealth = 1;

    if (customEnergy)
      newCurMana = Round(pHero->GetCustomEnergyValue());
    else
      newCurMana = Round(pUnit->GetMana());
  }

  {
    if (customEnergy)
      newMaxMana = Round(pHero->GetCustomEnergyMaximum());
    else
      newMaxMana = Round(pUnit->GetMaxMana());
  }

  if ( ( level != newLevel ) || ( curHealth != newCurHealth ) || ( maxHealth!= newMaxHealth ) || ( curMana != newCurMana ) || ( maxMana != newMaxMana ) )
  {
    level     = newLevel; 
    curHealth = newCurHealth;
    maxHealth = newMaxHealth;
    curMana   = newCurMana;
    maxMana   = newMaxMana;

    return true;
  }

  return false;
}

void CharInfoController::ActivateStats( bool activate )
{
  using namespace FlashFSCommands;

  NI_PROFILE_FUNCTION;

  if ( isStatsActive == activate )
  {
    return;
  }

  isStatsActive = activate;

  if ( activate )
  {
    //add listeners
    flashWnd->AddFSListner( ConvertToString( charType == CharType::OurHero ? BaseStatTooltip : SelectionBaseStatTooltip ), this );
    flashWnd->AddFSListner( ConvertToString( charType == CharType::OurHero ? DerivativeStatTooltip: SelectionDerivativeStatTooltip ), this );

    if ( !IsValid( pUnit ) )
    {
      return;
    }

    //update unit description
    bool isHero = pUnit->IsHero();

    const NDb::Texture* dbTexture = pUnit->GetUiAvatarImage();
    const char* texturePath = dbTexture? dbTexture->textureFileName.c_str() : "";
    int heroId = isHero ? pHero->GetPlayerId() : -1;
    const wstring& descTitle = isHero ? pHero->GetPlayerName() : pUnit->GetDescription();

    NDb::EFaction origFaction = pUnit->GetOriginalFaction();
    if ( isHero && pUnit->GetFaction() == NDb::FACTION_NEUTRAL )
      origFaction = NDb::FACTION_NEUTRAL;

    flashInterface->SetCharStatUnit( charType == CharType::Selection, heroId, texturePath, descTitle, origFaction, pUnit->GetNativeDamageType() );
    flashInterface->SetCharStatUnitParams( charType == CharType::Selection,heroId, level, curHealth, maxHealth, curMana, maxMana, isUnitVisible );

    const bool customEnergy = isHero && pHero->HasCustomEnergy();

    //fill base stats
    for ( int i = 0; i < baseStats.size(); ++i ) 
    {
      BaseStatParams& baseStat = baseStats[i];

      bool recommend = (baseStat.statID != NDb::STAT_ENERGY || !customEnergy);
      bool isImportant = recommend && (isHero ? pHero->IsRecommended(baseStat.statID): false);

      flashInterface->SetBaseStat( charType == CharType::Selection, baseStat.statID, baseStat.baseValue, baseStat.addition, isImportant );
    }

    //fill derivative stats
    for ( int i = 0; i < derivativeStats.size(); i++ )
    {
      DerivativeStatsParams& stat = derivativeStats[i];
      flashInterface->SetDerivativeStat( charType == CharType::Selection, stat.statID, stat.value );
    }
  }
  else
  {
    flashWnd->RemoveFSListner( ConvertToString( charType == CharType::OurHero ? BaseStatTooltip : SelectionBaseStatTooltip ) );
    flashWnd->RemoveFSListner( ConvertToString( charType == CharType::OurHero ? DerivativeStatTooltip: SelectionDerivativeStatTooltip ) );
    tooltip->Show( false );
  }
}

void CharInfoController::ActivateTalents( bool activate )
{
  using namespace FlashFSCommands;

  NI_PROFILE_FUNCTION;

  if ( isTalentsActive == activate )
  {
    return;
  }

  isTalentsActive = activate;

  if ( activate )
  {
    //add listeners
    flashWnd->AddFSListner( ConvertToString( SelectionTalentToolTip ), this );

    if ( !IsValid( pUnit ) || ( charType != CharType::Selection ) || ( pUnit->DbUnitDesc()->GetObjectTypeID() != NDb::Hero::typeId ) )
    {
      return;
    }

    //fill talents
    flashInterface->SetSelectionTalentBarUnitID ( pHero->GetPlayerId() );
    for ( int i = 0; i < talents.size(); ++i ) 
    {
      TalentParams& talent = talents[i];
      NWorld::PFTalent* pTalent = pHero->GetTalent( talent.level, talent.slot );

      const char* talentIcon = pTalent ? pTalent->GetTalentDesc()->image->textureFileName.c_str(): "";
      bool isTalentActive = pTalent ? pTalent->IsActive() : false;
      TalentUIState::ETalentUIState talentState = talent.isBought ? TalentUIState::Bought : TalentUIState::NotEnoughDevPoints;

      int upgradeLevel = 0;

      if (NDb::Ptr<NDb::Talent> dbTalent = pTalent? pTalent->GetTalentDesc() : 0 )
        upgradeLevel = dbTalent->upgradeLevel;

      flashInterface->SetSelectionTalentIcon( talent.slot, talent.level, talentIcon, isTalentActive, upgradeLevel );
      flashInterface->SetSelectionTalentState( talent.slot, talent.level, talentState );
    }
  }
  else
  {
    flashWnd->RemoveFSListner( ConvertToString( SelectionTalentToolTip ) );
  }
}

wstring CharInfoController::CalculateBaseTooltip( NDb::EStat baseID ) const
{
  wstring text;

  PrecompiledTooltip precompiledTooltip;

  switch (baseID)
  {
  case NDb::STAT_ENERGY:
    {
      const bool customEnergy = pUnit->IsHero() && pHero->HasCustomEnergy();

      if (customEnergy)
      {
        const NDb::Ptr<NDb::HeroResource>& uniqueResource = pHero->GetDbHero()->uniqueResource;

        precompiledTooltip.Init(pHero, uniqueResource->tooltip.GetText());

        break;
      }
    }
    // fall through
  default:
    {
      const vector<CTextRef>& baseStatTooltips = uiData->charStatTooltips.baseStatTooltips;

      NI_VERIFY( ( baseID >= 0 ) && ( baseID < baseStatTooltips.size() ), "wrong id from flash", return text );

      precompiledTooltip.Init( pUnit, baseStatTooltips[baseID].GetText() );
    }
  }

  precompiledTooltip.MakeText( text );

  return text;
}

wstring CharInfoController::CalculateDerivativeTooltip( NDb::EDerivativeStat derivativeID ) const
{
  const vector<CTextRef>& derivativeStatTooltips = uiData->charStatTooltips.derivativeStatTooltips;

  wstring text;
  NI_VERIFY( ( derivativeID >= 0 ) && ( derivativeID < derivativeStatTooltips.size() ), "wrong id from flash", return text );

  PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init( pUnit, derivativeStatTooltips[derivativeID].GetText() );

  precompiledTooltip.MakeText( text );
  return text;
}

wstring CharInfoController::CalculateTalentTooltip( int slot, int level ) const
{
  wstring text;

  bool isHero = pUnit->IsHero();
  const NWorld::PFBaseMaleHero* pMaleHero = isHero ? static_cast<const NWorld::PFBaseMaleHero*>( pHero.GetPtr() ) : 0;
  NWorld::PFTalent* pTalent = isHero ? pHero->GetTalent( level, slot ) : 0;
  if ( !pTalent )
  {
    return text;
  }

  NI_VERIFY( pTalent->GetTalentDesc(), "Wrong DB ptr", return text );

  typedef NMeta::MakeTypeList<NWorld::PFTalent, NWorld::PFBaseMaleHero>::Result myList;
  UnitInfoNameMap<myList> myMap;

  Field<NWorld::PFTalent>(myMap).pObject       = pTalent;
  Field<NWorld::PFBaseMaleHero>(myMap).pObject = pMaleHero;

  SConstUISubst subst;
  subst.Add( L"commonDescription", pTalent->GetTalentDesc()->commonDescription.GetText() );
  PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init( &myMap, pTalent->GetTalentDesc()->description.GetText(), &subst );

  precompiledTooltip.MakeText( text );

  return text;
}

int CharInfoController::FindTalent( int slot, int level )
{
  for ( int i = 0; i < talents.size(); ++i )
  {
    if ( ( talents[i].level == level ) && ( talents[i].slot == slot ) )
    {
      return i;
    }
  }

  return -1;
}


void CharInfoController::OnFSCommand( UI::FlashContainer2* wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  if ( !IsValid( uiData ) || !IsValid( pUnit ) )
  {
	if (tooltip->IsVisible())
		tooltip->Show(false);

    return;
  }
  int show = 0;  
  int statId = 0;  
  sscanf_s( args, "%d %d", &show, &statId );

  if ( !show )
  {
    tooltip->Show( false );
    return;
  }

  wstring tooltipText;

  if ( Equals( BaseStatTooltip, listenerID ) || Equals( SelectionBaseStatTooltip, listenerID ) )
  {
    tooltipText = isUnitVisible ? CalculateBaseTooltip( (NDb::EStat)statId ) : baseTooltips[(NDb::EStat)statId];
  }
  else if ( Equals( DerivativeStatTooltip, listenerID ) || Equals( SelectionDerivativeStatTooltip, listenerID ) )
  {
    tooltipText = isUnitVisible ? CalculateDerivativeTooltip( (NDb::EDerivativeStat)statId ) : derivativeTooltips[(NDb::EDerivativeStat)statId];
  }
  else if ( Equals( SelectionTalentToolTip, listenerID ) )
  {
    int column = 0;
    int raw = 0;

    sscanf_s( args, "%d %d %d", &show, &column, &raw );

    if ( isUnitVisible )
    {
      tooltipText = CalculateTalentTooltip( column, raw );
    }
    else
    {
      int talentIndex = FindTalent( column, raw );
      NI_VERIFY( talentIndex >= 0, NStr::StrFmt( "Talent in (%d, %d) not found!", column, raw ), talentIndex = 0 );
      tooltipText = talents[talentIndex].tooltip;
    }
  }
  else
  {
    NI_ALWAYS_ASSERT("something bad happened to the CharInfoController listener")
  }
 
  tooltip->SetText( tooltipText, uiData->tooltipDownScaleLimit );
  tooltip->Show( tooltipText.size() > 0 );
}

}

NI_DEFINE_REFCOUNT( NGameX::CharInfoController )
