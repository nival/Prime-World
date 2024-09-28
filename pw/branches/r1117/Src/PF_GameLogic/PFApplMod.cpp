#include "stdafx.h"
#include "PFBaseUnit.h"
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "PFLogicDebug.h"
#include "PFBaseAttackData.h"
#include "PFDispatchFactory.h"
#include "PFCreep.h"
#include "PFMaleHero.h"
#include "PFSummoned.h"
#include "PFTargetSelector.h"
#include "../Core/Scheduler.h"
#include "PF_Core/ScaleColorEffect.h"
#include "PF_Core/TraceGenSceneComponent.h"
#include "PFEffectSwitcher.h"
#include "PFNeutralCreep.h"
#include "AdventureScreen.h"
#include "PFTalent.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreep.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

#include "PFApplMod.h"
#include "PFApplInstant.h"

#include "PFPredefinedUnitVariables.h"
#include "PFTriggerApplicator.h"

#include "ClientVisibilityHelper.h"

#include "libdb/ClonedPtr.h"

namespace NWorld
{

const char* PFApplTargetsCounter::targetsCountVariableName = "targetsCount";


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplStatMod::Start()
{
  string const& name = GetDB().modifier.variable;
  if( name.empty() )
  {
    pStat = pReceiver->GetStat(GetDB().modifier.stat);
    NI_ASSERT(pStat, NStr::StrFmt("Stat %s not found in unit of type %s", 
      EnumToString(GetDB().modifier.stat), EnumToString(pReceiver->GetUnitType() ) ) );
  }
  else
  {
    pStat = pReceiver->GetVariableVWM(name.c_str() );
    NI_ASSERT(pStat, NStr::StrFmt("Variable %s not found in unit of type %s", 
      name.c_str(), EnumToString(pReceiver->GetUnitType() ) ) );
  }

  if ( GetDB().dontUpdate )
  {
    mul = RetrieveParam(GetDB().modifier.multValue);
    add = RetrieveParam(GetDB().modifier.addValue);
    const nstl::string& statModName = GetStatModName();
    if ( !statModName.empty() )
      statModConstant = GetConstant( statModName.c_str(), pOwner, pReceiver );
  }

  if (PFApplBuff::Start())
    return true;

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatMod::Enable()
{
  PFApplBuff::Enable();
  NI_ASSERT(IsValid(pReceiver), "Unit should be valid");
  if (!pStat)
    return;

  if ( !GetDB().dontUpdate )
  {
    mul = RetrieveParam(GetDB().modifier.multValue);
    add = RetrieveParam(GetDB().modifier.addValue);
  }

  modifierID = pStat->AddModifier( mul, add, GetAbilityOwner()->GetObjectId(), GetDB().modifier.topModifier, GetDB().constraint );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatMod::Disable()
{
  if (!pStat)
    return;
  
	NI_ASSERT(modifierID >= 0, "Modifier should be valid");
  pStat->RemoveModifier( modifierID );
  modifierID = INVALID_MODIFIER_ID;

  PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplStatMod::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  if (PFApplBuff::Step(dtInSeconds))
    return true;

  if (!pStat || !IsEnabled())
    return false;

	NI_ASSERT(modifierID >= 0, "Modifier should be valid");

  // Update parameters
  if ( !GetDB().dontUpdate )
  {
    NWorld::ValueWithModifiers::Modifier const * mod = pStat->Retrieve(modifierID);
    float oldMul = 0.0f;
    float oldAdd = 0.0f;

    if (mod)
    {
      oldMul = mod->mulValue;
      oldAdd = mod->addValue;
    }

    const float mul = RetrieveParam(GetDB().modifier.multValue);
    const float add = RetrieveParam(GetDB().modifier.addValue);

    pStat->UpdateModifier( modifierID, mul, add );

    if (oldMul != mul || oldAdd != add)
    {
      SetChanged(true);

      if (IsValid(pParent))
      {
        pParent->SetChanged(true);
      }
    }
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatMod::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFApplBuff::DumpInfo(logger);

  if (!pStat || modifierID == INVALID_MODIFIER_ID)
  {
    LogLogicInfo(logger)("      disabled\n");
    return;
  }

  const ValueWithModifiers::Modifier* pModifier = pStat->Retrieve(modifierID);
  LogLogicInfo(logger)("      stat: %s mul: %3.2f add: %3.2f\n", NDb::EnumToString(GetDB().modifier.stat), pModifier->mulValue, pModifier->addValue );
}

void PFApplStatMod::Reset()
{
	PFApplBuff::Reset();
	if ( !pReceiver )
		return;
	string const& name = GetDB().modifier.variable;
	if( name.empty() )
	{
		pStat = pReceiver->GetStat(GetDB().modifier.stat);
		NI_ASSERT(pStat, NStr::StrFmt("Stat %s not found in unit of type %s", 
			EnumToString(GetDB().modifier.stat), EnumToString(pReceiver->GetUnitType() ) ) );
	}
	else
	{
    pStat = pReceiver->SearchVariableVWM( name.c_str() );
	}
}

float PFApplStatMod::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "statMod") == 0 )
  {
    if (!pStat)
      return 0.0f;

    if (modifierID != INVALID_MODIFIER_ID)
      return pStat->GetAbsModification( modifierID );
  }

  return 0.f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function gets the absolute value of the modification the applicator make
float PFApplStatMod::GetAbsModification()
{
  if (!pStat)
    return 0.0f;

  if ( !GetDB().dontUpdate )
  {
    mul = RetrieveParam(GetDB().modifier.multValue);
    add = RetrieveParam(GetDB().modifier.addValue);
  }

  int tempModifierID;

  // If the modifier already applied - remove it
  if (modifierID != INVALID_MODIFIER_ID)
  {
    pStat->RemoveModifier( modifierID );
  }

  float valueBefore;
  float valueAfter;

  // Get value before, apply the modifier and get the value after
  valueBefore = pStat->GetValue();
  tempModifierID = pStat->AddModifier( mul, add, GetAbilityOwner()->GetObjectId(), GetDB().modifier.topModifier );
  valueAfter = pStat->GetValue();

  // If the modifier was applied - save new identifier, otherwise - remove the temporoory modifier
  if (modifierID != INVALID_MODIFIER_ID)
  {
    modifierID = tempModifierID;
  }
  else
  {
    pStat->RemoveModifier( tempModifierID );
  }

  // Return the absolute modification
  return abs(valueAfter - valueBefore);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string const& PFApplStatMod::GetStatModName() const
{
  return GetDB().statModName;
}

bool PFApplStatMod::GetStatModConstant( float& value ) const
{
  if ( GetDB().dontUpdate && !GetStatModName().empty() )
  {
    value = statModConstant;
    return true;
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplPermanentStatMod::Start()
{
	if (PFBaseApplicator::Start())
		return true;

	float mul = RetrieveParam(GetDB().modifier.multValue);
	float add = RetrieveParam(GetDB().modifier.addValue);

  string const& name = GetDB().modifier.variable;
  ValueWithModifiers *pStat = name.empty() ? pReceiver->GetStat(GetDB().modifier.stat) :
    pReceiver->GetVariableVWM(name.c_str() );
	if (pStat)
	{
		pStat->SetBaseValue(mul * pStat->GetBaseValue() + add); // Base value, not Core!

    if( GetDB().LoggingEvent >= 0 ) // logging enabled
    {
      StatisticService::RPC::SessionEventInfo params;
      params.strParam2.assign( NStr::StrFmtW(L"x=%d, y=%d", (int)pReceiver->GetPosition().AsVec2D().x, (int)pReceiver->GetPosition().AsVec2D().y ) );

      NGameX::AdventureScreen::Instance()->LogWorldSessionEvent( (SessionEventType::EventType)GetDB().LoggingEvent, params );
    }
	}

	return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplPermanentStatMod::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFBaseApplicator::DumpInfo(logger);

	float mul = RetrieveParam(GetDB().modifier.multValue);
	float add = RetrieveParam(GetDB().modifier.addValue);
	LogLogicInfo(logger)("      stat: %s mul: %3.2f add: %3.2f\n", NDb::EnumToString(GetDB().modifier.stat), mul, add );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAbilityMod::Start()
{
  NI_VERIFY( IsValid(pReceiver), "Receiver must be valid!", return true );
  
  pHero = dynamic_cast<PFBaseHero*>(pReceiver.GetPtr());

  if ( !IsValid(pHero) )
    return true; // this applicator works only on heroes

  // get modifier variables
  if ( (GetDB().targetAbilities & NDb::ABILITYIDFLAGS_TALENTS) && GetDB().talents.empty() && pOwner->GetFaction() == pHero->GetFaction() )
  {
    if ( GetDB().mode == NDb::ABILITYMODMODE_COOLDOWN )
    {
      pTalCdAddVar = pHero->GetVariableVWM( UnitVariables::szTalentsCdAdd );
      pTalCdMulVar = pHero->GetVariableVWM( UnitVariables::szTalentsCdMul );
      pTalCdMulVar->SetBaseValue( 1.0f );
    }
    else if ( GetDB().mode == NDb::ABILITYMODMODE_MANACOST )
    {
      pTalMcAddVar = pHero->GetVariableVWM( UnitVariables::szTalentsMcAdd );
      pTalMcMulVar = pHero->GetVariableVWM( UnitVariables::szTalentsMcMul );
      pTalMcMulVar->SetBaseValue( 1.0f );
    }
  }

  if (PFApplBuff::Start())
    return true;

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityMod::CheckCachedValues()
{
  NI_ASSERT(IsValid(pHero), "Unit should be valid");

  float mul = RetrieveParam(GetDB().multValue);
  float add = RetrieveParam(GetDB().addValue);

  if ( cachedMul != mul || cachedAdd != add )
  {
    cachedMul = mul;
    cachedAdd = add;
    pHero->RecacheAbilitiesModifiers();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAbilityMod::IsApplicable(NDb::EAbilityModMode mode, NDb::EAbilityTypeId abilityType, NDb::Ptr<NDb::Ability> const& dbAbility)
{
  NDb::AbilityModApplicator const & dbDesc = GetDB();
  
  if ( dbDesc.mode != mode )
    return false;

  if ( abilityType == NDb::ABILITYTYPEID_TALENT && (dbDesc.targetAbilities & NDb::ABILITYIDFLAGS_TALENTS)
      && !PFAbilityData::IsAbilitySuitable( dbAbility, dbDesc.talents, dbDesc.useListAs ) )
  {
    return false;
  }

  if ( (dbDesc.targetAbilities == NDb::ABILITYIDFLAGS_SPECIFIC) && dbAbility && (dbDesc.specificAbility == dbAbility)
      || (abilityType != NDb::ABILITYTYPEID_SPECIAL) && (dbDesc.targetAbilities&(1<<abilityType)) )
  {
    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityMod::AddModifier(float& add, float& mul, NDb::EAbilityModMode mode, NDb::EAbilityTypeId abilityType, NDb::Ptr<NDb::Ability> const& dbAbility )
{
  if (IsApplicable(mode, abilityType, dbAbility) && mode != NDb::ABILITYMODMODE_STATE)
  {
    add += cachedAdd;
    mul *= cachedMul;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityMod::Enable()
{
  if ( !IsValid(pHero) )
    return; // this applicator works only on heroes

  PFApplBuff::Enable();
  
  // Attach to Hero
  pHero->AddAbilityModifier(this);
  CheckCachedValues();

  // write modifier variables
  if ( pTalCdAddVar )
  {
    talCdAddModifierId = pTalCdAddVar->AddModifier( 1.0f, cachedAdd, GetAbilityOwner()->GetObjectId() );
    talCdMulModifierId = pTalCdMulVar->AddModifier( cachedMul, 0.0f, GetAbilityOwner()->GetObjectId() );
  }
  else if ( pTalMcAddVar )
  {
    talMcAddModifierId = pTalMcAddVar->AddModifier( 1.0f, cachedAdd, GetAbilityOwner()->GetObjectId() );
    talMcMulModifierId = pTalMcMulVar->AddModifier( cachedMul, 0.0f, GetAbilityOwner()->GetObjectId() );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityMod::Disable()
{
  if ( !IsValid(pHero) )
    return; // this applicator works only on heroes

  // Remove self from receivers ring
  pHero->RemoveAbilityModifier(this);
  PFApplBuff::Disable();

  if ( pTalCdAddVar )
  {
    pTalCdAddVar->RemoveModifier( talCdAddModifierId );
    pTalCdMulVar->RemoveModifier( talCdMulModifierId );
  }
  else if ( pTalMcAddVar )
  {
    pTalMcAddVar->RemoveModifier( talMcAddModifierId );
    pTalMcMulVar->RemoveModifier( talMcMulModifierId );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAbilityMod::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION
  
  if (PFApplBuff::Step(dtInSeconds))
    return true;

  if ( IsEnabled() )
  {
    CheckCachedValues();

    if ( pTalCdAddVar )
    {
      pTalCdAddVar->UpdateModifierAdd( talCdAddModifierId, cachedAdd );
      pTalCdMulVar->UpdateModifierMul( talCdMulModifierId, cachedMul );
    }
    else if ( pTalMcAddVar )
    {
      pTalMcAddVar->UpdateModifierAdd( talMcAddModifierId, cachedAdd );
      pTalMcMulVar->UpdateModifierMul( talMcMulModifierId, cachedMul );
    }
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityMod::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFApplBuff::DumpInfo(logger);
  LogLogicInfo(logger)("mode: %s targets: %i spec: %s, mul: %3.2f add: %3.2f\n", NDb::EnumToString(GetDB().mode), (int)GetDB().targetAbilities, 
    ( GetDB().specificAbility ? NDb::GetFormattedDbId(GetDB().specificAbility->GetDBID()).c_str() : "[NONE]" ), cachedMul, cachedAdd);
}

void PFApplAbilityMod::Reset()
{
	PFApplBuff::Reset();
	NI_VERIFY( IsValid(pReceiver), "Receiver must be valid!", return );
	if ( !IsValid(pHero) )
		return; // this applicator works only on heroes

	pTalCdAddVar = 0;
	pTalCdMulVar = 0;
	pTalMcAddVar = 0;
	pTalMcMulVar = 0;

	// get modifier variables
	if ( (GetDB().targetAbilities & NDb::ABILITYIDFLAGS_TALENTS) && GetDB().talents.empty() && pOwner->GetFaction() == pHero->GetFaction() )
	{
		if ( GetDB().mode == NDb::ABILITYMODMODE_COOLDOWN )
		{
			pTalCdAddVar = pHero->SearchVariableVWM( UnitVariables::szTalentsCdAdd );
			pTalCdMulVar = pHero->SearchVariableVWM( UnitVariables::szTalentsCdMul );
      if (pTalCdMulVar)
        pTalCdMulVar->SetBaseValue( 1.0f );
		}
		else if ( GetDB().mode == NDb::ABILITYMODMODE_MANACOST )
		{
			pTalMcAddVar = pHero->SearchVariableVWM( UnitVariables::szTalentsMcAdd );
			pTalMcMulVar = pHero->SearchVariableVWM( UnitVariables::szTalentsMcMul );
      if (pTalMcMulVar)
        pTalMcMulVar->SetBaseValue( 1.0f );
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityUpgrade::Enable()
{
  if ( GetDB().flags & NDb::ABILITYUPGRADEMODE_CHANGEICON )
  {
    //TODO: Поменять иконку на глиф NUM_TASK
  }

  if ( IsValid(pReceiver) )
    pReceiver->AddAbilityUpgradeApplicator(this);
  PFApplBuff::Enable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityUpgrade::Disable()
{
  if ( GetDB().flags & NDb::ABILITYUPGRADEMODE_CHANGEICON )
  {
    //TODO: Поменять иконку на обычный талант NUM_TASK
  }

  if ( IsValid(pReceiver) )
    pReceiver->RemoveAbilityUpgradeApplicator(this);
  PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityUpgrade::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFApplBuff::DumpInfo(logger);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAbilityUpgrade::UpgradeAbilityApplicators( CPtr<PFAbilityData> const& abilityData, vector<NDb::Ptr<NDb::BaseApplicator>>& applicators, vector<NDb::Ptr<NDb::BaseApplicator>>& persistentApplicators, bool& useOriginal )
{
  if ( !CheckAppliesCount() )
    return;

  NDb::AbilityUpgradeApplicator const& dbDesc = GetDB();
  NDb::EAbilityTypeId const& abilityType = abilityData->GetAbilityTypeId();

  if ( dbDesc.targetAbility != abilityType )
  {
    if ( !( ( dbDesc.targetAbility == NDb::ABILITYTYPEID_TALENTFROMLIST ) && ( abilityType == NDb::ABILITYTYPEID_TALENT ) ) )
    {
      return;
    }
  }

  const NDb::Ability* pAbilityDesc = abilityData->GetDBDesc();
  CPtr<PFAbilityData> pAbilityData = pAbility->GetData();

  if ( dbDesc.targetAbility == NDb::ABILITYTYPEID_TALENTFROMLIST )
  {
    if ( !PFAbilityData::IsAbilitySuitable( pAbilityDesc, dbDesc.talents, dbDesc.useListAs ) )
    {
      return;
    }

    // NUM_TASK
    if (dbDesc.flags & NDb::ABILITYUPGRADEMODE_APPLYONCEPERCAST)
    {
      // NOTE: ability type was verified earlier
      const PFTalent* const talent = static_cast<PFTalent*>(abilityData.GetPtr());

      const int talentObjectId = talent->GetObjectId();
      const int talentLastUseStep = talent->GetLastUseStep();

      ValueWithModifiers* const vwm = pReceiver->GetVariableVWM(GetTalentLastUseStepVariableName(talentObjectId));

      if (!(vwm->GetBaseValue() < static_cast<float>(talentLastUseStep)))
        return;

      vwm->SetBaseValue(static_cast<float>(talentLastUseStep));
    }
    //
  }

  // check cooldown and take mana if flags
  if ( (dbDesc.flags & NDb::ABILITYUPGRADEMODE_USEABILITYCOOLDOWN) && !pAbilityData->IsReady() )
    return;
  if ( (dbDesc.flags & NDb::ABILITYUPGRADEMODE_USEABILITYMANA) && !pAbilityData->IsEnoughMana() )
    return;

  // restart cooldown and take mana if flags.
  if (dbDesc.flags & NDb::ABILITYUPGRADEMODE_USEABILITYCOOLDOWN)
    pAbilityData->RecalculateAndRestartCooldown();
  if (dbDesc.flags & NDb::ABILITYUPGRADEMODE_USEABILITYMANA)
    pAbilityData->SpendMana();
    
  // upgrade ability
  applicators.insert( applicators.end(), dbDesc.applicators.begin(), dbDesc.applicators.end() );
  persistentApplicators.insert( persistentApplicators.end(), dbDesc.persistentApplicators.begin(), dbDesc.persistentApplicators.end() );
  if ( dbDesc.flags & NDb::ABILITYUPGRADEMODE_USEGLYPH )
  {
    int glyphNumber = GetParentAppl()->GetVariable( PFEventProcessorPickupGlyph::glyphNumberVariableName );

    if(glyphNumber < 0) 
      NI_ALWAYS_ASSERT("glyphNumber < 0");

    const NDb::AdvMapSettings* desc = IsValid(GetWorld()->GetMapDescription()->mapSettings) ? GetWorld()->GetMapDescription()->mapSettings 
                                                                                            : GetWorld()->GetMapDescription()->map->mapSettings;
    if ( desc && IsValid(desc->overrideGlyphSettings) )
    {
      NI_ASSERT( glyphNumber < desc->overrideGlyphSettings->glyphs->glyphs.size(), "Behaviour should present");
      GetAbilityOwner()->UseExternalAbility( desc->overrideGlyphSettings->glyphs->glyphs[glyphNumber].glyph.GetPtr(), Target(GetAbilityOwner()) );
    }
    else
    {
      NDb::Ptr<NDb::SessionRoot> pRoot = NDb::SessionRoot::GetRoot();
      NDb::Ptr<NDb::GlyphsDB> pDBGlyphs = pRoot->logicRoot->glyphsDB;
      NI_ASSERT( glyphNumber < pDBGlyphs->glyphs.size(), "Behaviour should present");
      GetAbilityOwner()->UseExternalAbility( pDBGlyphs->glyphs[glyphNumber].glyph.GetPtr(), Target(GetAbilityOwner()) );
    }
  }  
  if (dbDesc.flags & NDb::ABILITYUPGRADEMODE_DONTUSEORIGINAL)
    useOriginal = false;

  // NUM_TASK
  if (dbDesc.flags & NDb::ABILITYUPGRADEMODE_APPLYONCEPERCASTPERTARGET)
  {
    // NOTE: ability type was verified earlier
    const PFTalent* const talent = static_cast<PFTalent*>(abilityData.GetPtr());

    bool ok = false;

    for (int i = 0, count = applicators.size(); i < count; ++i)
    {
      NDb::Ptr<NDb::BaseApplicator>& applr = applicators[i];

      if (applr->GetObjectTypeID() != NDb::AbilityUpgradeTechApplicator::typeId)
        continue;

      NDb::ClonedPtr<NDb::AbilityUpgradeTechApplicator> cloned;

      cloned.Clone(static_cast<const NDb::AbilityUpgradeTechApplicator*>(applr.GetPtr()));

      cloned->abilityObjectId = talent->GetObjectId();
      cloned->abilityLastUseStep = talent->GetLastUseStep();

      // NOTE: place tech applicator at the very end of applicators list but preserve other applicators order
      if (i < count - 1)
      {
        applicators.erase(applicators.begin() + i);
        applicators.push_back(cloned.GetPtr());
      }
      else
      {
        applr = cloned.GetPtr();
      }

      ok = true;

      break;
    }

    NI_ASSERT(ok, "AbilityUpgradeApplicator: tech applicator not found!");
  }
  //

  ++appliesCount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAbilityUpgrade::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  return ( Base::Step(dtInSeconds) || !CheckAppliesCount() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAbilityUpgrade::Start()
{
  maxCount = RetrieveParam(GetDB().applyCount, 0);
  return Base::Start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::Texture* PFApplStatus::GetStatusImage() const
{
	return GetDB().image.GetPtr();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::GetChildrenStatMods( vector<PFApplStatMod const*>& statModContainer, bool activeOnly /* = false */ ) const
{
  if (IsEnabled())
  {
    TApplicators::const_iterator it = childApplicators.begin();
    TApplicators::const_iterator itEnd = childApplicators.end();

    for (; it != itEnd; ++it)
    {
      if (IsValid(*it) && (*it)->GetTypeId() == PFApplStatMod::typeId && ( !activeOnly || !(*it)->IsBlocked() ) )
      {
        statModContainer.push_back( static_cast<PFApplStatMod const*>((*it).GetPtr()) );
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::CompareByPower(PFApplStatus * pSecond)
{
  if (!pSecond)
    return;

  float remaningTime;
  float remaningTimeSecond;

  if (GetDB().power == pSecond->GetDB().power
        && GetRemainingLifeTime(remaningTime) && pSecond->GetRemainingLifeTime(remaningTimeSecond)
        && remaningTime > remaningTimeSecond 
      || GetDB().power > pSecond->GetDB().power)
  {
    blockApplicators.push_back(pSecond);
    pSecond->blockedByApplicators.push_back(this);
  }
  else
  {
    blockedByApplicators.push_back(pSecond);
    pSecond->blockApplicators.push_back(this);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::MergeByValue()
{
  if (!IsComparableByValue() || mergeApplicators.size() == 0)
    return;

  TApplicators::iterator it;
  TApplicators::iterator itEnd;

  // First step - disable all modifiers, so we will be able to apply one after another and compare the effect

  // Disable own child applicators
  if (IsEnabled())
  {
    it = childApplicators.begin();
    itEnd = childApplicators.end();

    for (; it != itEnd; ++it)
    {
      if (IsValid(*it) && (*it)->GetTypeId() == PFApplStatMod::typeId )
      {
        ((PFApplStatMod*)(*it).GetPtr())->Block();
      }
    }
  }

  TApplStatuses::iterator itCompare = mergeApplicators.begin();
  TApplStatuses::iterator itCompareEnd = mergeApplicators.end();

  // Disable child applicators of all statuses we have to merge with
  for (; itCompare != itCompareEnd; ++itCompare)
  {
    if ((*itCompare)->IsEnabled())
    {
      it = (*itCompare)->childApplicators.begin();
      itEnd = (*itCompare)->childApplicators.end();

      for (; it != itEnd; ++it)
      {
        if (IsValid(*it) && (*it)->GetTypeId() == PFApplStatMod::typeId )
        {
          ((PFApplStatMod*)(*it).GetPtr())->Block();
        }
      }
    }
  }

  // Second step - find highest modification value for each type of stat being modified.
  //               The comparison is done by modulo, so always the highst effect will be found,
  //               no matter buffs or debuffs are being compared

  typedef nstl::map<ValueWithModifiers*, pair<float, TApplicators::iterator>> TModifiers;
  TModifiers maxModifers;

  // Check own applicators modification values
  if (IsEnabled())
  {
    it = childApplicators.begin();
    itEnd = childApplicators.end();

    for (; it != itEnd; ++it)
    {
      if (IsValid(*it))
      {
        PFBaseApplicator* pCurBaseAppl = (*it).GetPtr();
        if ( pCurBaseAppl->GetTypeId() == PFApplStatMod::typeId )
        {
          PFApplStatMod* pCurApplStatMod = static_cast<PFApplStatMod*>(pCurBaseAppl);
          float val = pCurApplStatMod->GetAbsModification();
          maxModifers.insert( make_pair( pCurApplStatMod->pStat, make_pair( val, it ) ) );
        }
      }
    }
  }

  itCompare = mergeApplicators.begin();
  itCompareEnd = mergeApplicators.end();

  // Check child applicators modification values of all statuses we have to merge with
  for (; itCompare != itCompareEnd; ++itCompare)
  {
    if (IsValid((*itCompare)) && (*itCompare)->IsEnabled())
    {
      it = (*itCompare)->childApplicators.begin();
      itEnd = (*itCompare)->childApplicators.end();

      for (; it != itEnd; ++it)
      {
        if (IsValid(*it))
        {
          PFBaseApplicator* pCurBaseAppl = (*it).GetPtr();
          if ( pCurBaseAppl->GetTypeId() == PFApplStatMod::typeId )
          {
            PFApplStatMod* pCurApplStatMod = static_cast<PFApplStatMod*>(pCurBaseAppl);
            float val = pCurApplStatMod->GetAbsModification();

            // Try to find stored max value for the stat, if we already added it
            TModifiers::iterator itMod = maxModifers.find(pCurApplStatMod->pStat);

            // Compare if found, or add a new one to the list
            if (itMod != maxModifers.end())
            {
              if (val > itMod->second.first)
              {
                itMod->second.second = it;
              }
            }
            else
            {
              maxModifers.insert( make_pair( ((PFApplStatMod*)(*it).GetPtr())->pStat, make_pair( val, it) ) );
            }
          }
        }
      }
    }
  }

  // Third step - enable back only modifiers with the highst found effect

  TModifiers::iterator itMod = maxModifers.begin();
  TModifiers::iterator itModEnd = maxModifers.end();

  for (; itMod != itModEnd; ++itMod)
  {
    ((PFApplStatMod*)(itMod->second.second)->GetPtr())->Unblock();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplStatus::Start()
{
  if (!IsValid(pReceiver) || RetrieveParam( GetDB().startCondition, true ) == false )
  {
    PFApplBuff::Start();
    return true;
  }

  bStarted = true;

  // Structure for finding status stacking conflicts
  struct StatusStackingControl : public NonCopyable
  {
    StatusStackingControl(PFApplStatus* pNewcomer_) 
      : pNewcomer(pNewcomer_), statusCount(0) {}

    bool IsInList(NDb::BaseApplicator const* dbApplicator, NDb::ApplicatorsList const* pApplicatorsList)
    {
      if (!pApplicatorsList)
        return false;

      // Check applicators
      for ( vector<NDb::Ptr<NDb::BaseApplicator>>::const_iterator iAppl = pApplicatorsList->applicators.begin(), iEnd = pApplicatorsList->applicators.end(); iAppl != iEnd; ++iAppl )
        if ( (*iAppl) && (*iAppl)->GetDBID() == dbApplicator->GetDBID() ) // use DBID compare in this case, not DBBase
          return true;

      // Check lists
      for ( vector<NDb::Ptr<NDb::ApplicatorsList>>::const_iterator iList = pApplicatorsList->applicatorLists.begin(), iEnd = pApplicatorsList->applicatorLists.end(); iList != iEnd; ++iList )
        if ( (*iList) && IsInList( dbApplicator, (*iList) ) )
          return true;

      return false;
    }

    void operator()(CObj<PFApplStatus> &pAppl)
    {
      if (NULL == pNewcomer) // This means this status can't be applied
        return;

      if ( pAppl->GetDB().GetDBID() == pNewcomer->GetDB().GetDBID() ) // Is this applicator of the same type
      {
        if (pAppl->GetAbilityOwner() == pNewcomer->GetAbilityOwner()) // Is this applicator from the same unit
        {
          // Do count stacked same aplicators from same unit and check for allowed maximum
          if (++statusCount <= pNewcomer->GetDB().stackCount)
          {
            // Update lifetime of the old applicator from the new one, if needed
            if ( (pNewcomer->GetDB().flags & NDb::STATUSFLAGS_UPDATELIFETIME) != 0 && pNewcomer->GetLifetime() > 0 )
            {
                pAppl->ForceUpdateLifetime( pNewcomer->GetLifetime(), pNewcomer->GetDuration() );
            }
          }
          else
          {
            // If the counter of stacked applicators has exceeded the allowed maximum - remove the old one
            if ( (pNewcomer->GetDB().flags & NDb::STATUSFLAGS_STOPSAMECONFLICTED) != 0 )
            {
              pAppl->Stop();
              MemorizeApplicator( CObj<PFBaseApplicator>(pAppl) );
              return;
            }
            conflictedApplicators.push_back(pAppl.GetPtr());
          }
        }
        else if ( pNewcomer->GetDB().stackableAcrossUnits == NDb::STACKINGRULE_PARTIALLYSTACKABLE && ++statusCount > pNewcomer->GetDB().stackCount
               || pNewcomer->GetDB().stackableAcrossUnits == NDb::STACKINGRULE_UNSTACKABLE )
        {
          // If we have received same applicator from different units and 
          // it is not stackable across units - we have another conflict
          if ( (pNewcomer->GetDB().flags & NDb::STATUSFLAGS_STOPALLCONFLICTED) != 0 )
          {
            pAppl->Stop();
            MemorizeApplicator( CObj<PFBaseApplicator>(pAppl) );
            return;
          }
          conflictedApplicators.push_back(pAppl.GetPtr());
        }
        // Else - do nothing. if it is not from the same unit and fully stackable - new status should be added
      }
      else if ( IsInList(pAppl->GetDBBase(), pNewcomer->GetDB().unstackableWith) 
                || IsInList(pNewcomer->GetDBBase(), pAppl->GetDB().unstackableWith) )
      {
        // If we have different statuses which are unstackable - yet another conflict to resolve
        if ( (pNewcomer->GetDB().flags & NDb::STATUSFLAGS_STOPALLCONFLICTED) != 0 )
        {
          pAppl->Stop();
          MemorizeApplicator( CObj<PFBaseApplicator>(pAppl) );
          return;
        }
        conflictedApplicators.push_back(pAppl.GetPtr());
      }
      // Else - do nothing, the old and the new statuses are stackable
    }

  private:
    PFApplStatus * pNewcomer;
    int            statusCount;

  public:
    TApplStatuses  conflictedApplicators;

  } f(this);

  pReceiver->ForAllStatusApplicators(f);

  switch (GetDB().stopBehaviour)
  {
  case NDb::STOPBEHAVIOUR_STOPBYTIME:
    m_applicatorCount = GetDB().applicators.size() + 1;
    break;
  case NDb::STOPBEHAVIOUR_STOPBYCHILD:
    m_applicatorCount = 1;
    break;
  case NDb::STOPBEHAVIOUR_STOPBYALLCHILDS:
    m_applicatorCount = GetDB().applicators.size();
    break;
  default:
    NI_ALWAYS_ASSERT("Unknown enum value");
    m_applicatorCount = GetDB().applicators.size() + 1;
  }

  //// set comparable by value
  NDb::StatusApplicator const& db = GetDB();

  m_isComparableByValue = false;
  if ( !db.applicators.empty() )
  {
    if ( (db.flags & NDb::STATUSFLAGS_ALWAYSMERGE) != 0 )
    {
      m_isComparableByValue = true;
    }
    else
    {
      vector<NDb::Ptr<NDb::BaseApplicator>>::const_iterator it = db.applicators.begin();
      vector<NDb::Ptr<NDb::BaseApplicator>>::const_iterator itEnd = db.applicators.end();

      for (; it != itEnd; ++it)
      {
        if (IsValid(*it))
        {
          m_isComparableByValue = true;

          int _typeId = (*it)->GetObjectTypeID();
          if ( _typeId != NDb::StatModApplicator::typeId && _typeId != NDb::UIMessageApplicator::typeId )
          {
            m_isComparableByValue = false;
            break;
          }
        }
      }
    }
  }
  //// end of set comparable by value

  // Try to start the applicator, we will resolve the conflicts later
  if (PFApplBuff::Start())
    return true;

  TApplStatuses::iterator it = f.conflictedApplicators.begin();
  TApplStatuses::iterator itEnd = f.conflictedApplicators.end();

  if (IsComparableByValue())
  {
    for (; it != itEnd; ++it)
    {
      // If the conflict isComparableByValue too and it is comparable with current 
      if ((*it)->IsComparableByValue())
      {
        // Compare by value and set update merged applicators list
        mergeApplicators.push_back(*it);
        (*it)->mergeApplicators.push_back(this);
      }
      else
      {
        // Compare by "power"
        CompareByPower((PFApplStatus*)(*it).GetPtr());
      }
    }
  }
  else
  {
    // Compare with all conflicts by "power"
    for (; it != itEnd; ++it)
    {
      CompareByPower(*it);
    }
  }

  // If something blocks the new status and it is enabled - disable the new one
  if (blockedByApplicators.size() > 0)
  {
    Block();
  }

  // Disable all statuses the new one blocks
  it = blockApplicators.begin();
  itEnd = blockApplicators.end();

  for (; it != itEnd; ++it)
  {
    (*it)->Block();
  }

  // Merge with comparable statuses, if needed
  if (IsEnabled())
  {
    MergeByValue();
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::Enable()
{
  if ( !bStarted )
    return;

	PFApplBuff::Enable();

	Target targ;
	MakeApplicationTarget(targ);

	CreateAndActivateApplicators(GetDB().applicators, GetAbility(), targ, this);

  pReceiver->RegisterStatusApplicator(this);

  // Merge, if needed
  MergeByValue();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::Disable()
{
  if ( !bStarted )
    return;

	RemoveChildrenApplicators();

  // Clear also the internal list of applicators (previous line removes them from the unit)
  childApplicators.clear();

  if (activeStatusesPart.isLinked())
    ActiveStatusRing::remove(this);

	PFApplBuff::Disable();

  // Merge the remaining (conflicted) applicators, if needed
  MergeByValue();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::Stop()
{
  NI_PROFILE_FUNCTION

  PFApplBuff::Stop();

  TApplStatuses::iterator it;
  TApplStatuses::iterator itEnd;

  // Remove the applicator from all conflicted (nonstackable) applicators

  it = blockApplicators.begin();
  itEnd = blockApplicators.end();

  for (; it != itEnd; ++it)
  {
    if (IsValid(*it))
    {
      (*it)->blockedByApplicators.remove(this);

      // If the applicator we were bloking isn't blocked by anyone now - "unblock" it
      if((*it)->blockedByApplicators.size() == 0)
      {
        (*it)->Unblock();
      }
    }
  }

  blockApplicators.clear();

  it = blockedByApplicators.begin();
  itEnd = blockedByApplicators.end();

  for (; it != itEnd; ++it)
  {
    if (IsValid(*it))
    {
      (*it)->blockApplicators.remove(this);
    }
  }

  blockedByApplicators.clear();

  it = mergeApplicators.begin();
  itEnd = mergeApplicators.end();

  for (; it != itEnd; ++it)
  {
    if (IsValid(*it))
    {
      (*it)->mergeApplicators.remove(this);
    }
  }

  mergeApplicators.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplStatus::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  if (PFApplBuff::Step(dtInSeconds))
    return true;

  bool ret = m_applicatorCount <= 0 && GetDB().stopBehaviour != NDb::STOPBEHAVIOUR_STOPBYTIME;

  // If child applicator/s was/were changed - remerge
  if (!ret && IsChanged() && IsComparableByValue())
  {
    MergeByValue();
    SetChanged(false);
  }

  return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note)
{
  PFApplBuff::OnNotification(appl, note);

  if (NDb::PARENTNOTIFICATION_STOP == note)
  {
    m_applicatorCount -= 1;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplStatus::GetModifiedDuration(float original) const
{
  return original > 0.0f ? GetAbility()->GetData()->GetModifiedValue(original, NDb::ABILITYMODMODE_DURATION) : original;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplStatus::ForceUpdateLifetime( float newLifetime, float newDuration )
{
  SetLifetime( newLifetime );
	SetDuration( newDuration );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplFlags::Enable()
{
  PFApplBuff::Enable();

  unsigned int flags = GetDB().flag;
  if ( !GetDB().consumables.empty() )
    flags &= ~NDb::UNITFLAG_FORBIDUSECONSUMABLES;
  pReceiver->AddFlag(flags);

  if ( ( GetDB().flag & NDb::UNITFLAG_FORBIDPICK ) != 0 )
  {
    if ( NScene::SceneObject * pSObj = pReceiver->GetClientSceneObject() )
      pSObj->SetForbidPick( true );
  }

  if ( pReceiver->IsHero() )
  {
    PFBaseMaleHero* pHero = static_cast<PFBaseMaleHero*>(pReceiver.GetPtr());
    if ( ( GetDB().flag & NDb::UNITFLAG_FORBIDUSETALENTS ) != 0 )
    {
      struct DisableFunc : public NonCopyable
      {
        DisableFunc( vector<NDb::Ptr<NDb::Ability>> const& abilityList, NDb::EUseMode mode, const PFBaseApplicator* _pAppl ) : abilityList(abilityList), mode(mode), pAppl(_pAppl) {}

        virtual void operator()(PFTalent *pTalent, int level, int slot)
        {
          if ( PFAbilityData::IsAbilitySuitable( pTalent->GetTalentDesc(), abilityList, mode ) )
          {
            pTalent->AddForbid( pAppl );
          }
        }

        NDb::EUseMode mode;
        vector<NDb::Ptr<NDb::Ability>> const& abilityList;
        const PFBaseApplicator* pAppl;
      } disableFunc( GetDB().talents, GetDB().useListAs, this );

      if (pHero->GetPortal())
        disableFunc(pHero->GetPortal(), 0 , 0);

      pHero->ForAllTalents( disableFunc );
    }

    if ( ( GetDB().flag & NDb::UNITFLAG_FORBIDUSECONSUMABLES ) != 0 )
    {
      vector<NDb::Ptr<NDb::Ability>> const& consumList = GetDB().consumables;
      for ( vector<NDb::Ptr<NDb::Ability>>::const_iterator it = consumList.begin(); it != consumList.end(); ++it )
      {
        if ( PFAbilityData* pAbilityData = pHero->GetConsumableAbility( *it ) )
        {
          pAbilityData->AddForbid( this );
        }
      }
    }
  }

	// Send events
	if ((GetDB().flag & NDb::UNITFLAG_FORBIDMOVE) != 0)
		pReceiver->EventHappened(PFBaseUnitApplicatorEvent(NDb::BASEUNITEVENT_FORBIDMOVE, this));

	if ((GetDB().flag & NDb::UNITFLAG_FORBIDATTACK) != 0)
		pReceiver->EventHappened(PFBaseUnitApplicatorEvent(NDb::BASEUNITEVENT_FORBIDATTACK, this));

	const int castFlag = (NDb::UNITFLAG_FORBID_ABILITY1 | NDb::UNITFLAG_FORBID_ABILITY2 | 
		                    NDb::UNITFLAG_FORBID_ABILITY3 | NDb::UNITFLAG_FORBID_ABILITY4);
	if ((GetDB().flag & castFlag) != 0)
		pReceiver->EventHappened(PFBaseUnitApplicatorEvent(NDb::BASEUNITEVENT_FORBIDCAST, this));

  if ( (GetDB().flag & NDb::UNITFLAG_FORBIDINVISIBILITY) != 0 )
    pReceiver->EventHappened( PFBaseUnitApplicatorEvent( NDb::BASEUNITEVENT_CANCELINVISIBILITY, this ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplFlags::Disable()
{
  if(!IsValid(pReceiver))
    return;

  if ( PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>(pReceiver.GetPtr()) )
  {
    if ( ( ( GetDB().flag & NDb::UNITFLAG_FORBIDUSETALENTS ) != 0 ) )
    {
      struct EnableFunc : public NonCopyable
      {
        EnableFunc( vector<NDb::Ptr<NDb::Ability>> const& abilityList, NDb::EUseMode mode ) : abilityList(abilityList), mode(mode) {}

        virtual void operator()(PFTalent *pTalent, int level, int slot)
        {
          if ( PFAbilityData::IsAbilitySuitable( pTalent->GetTalentDesc(), abilityList, mode ) )
          {
            pTalent->RemoveForbid();
          }
        }

        NDb::EUseMode mode;
        vector<NDb::Ptr<NDb::Ability>> const& abilityList;
      } enableFunc( GetDB().talents, GetDB().useListAs );

      if (pHero->GetPortal())
        enableFunc(pHero->GetPortal(), 0 , 0);
      pHero->ForAllTalents( enableFunc );
    }

    if ( ( GetDB().flag & NDb::UNITFLAG_FORBIDUSECONSUMABLES ) != 0 )
    {
      vector<NDb::Ptr<NDb::Ability>> const& consumList = GetDB().consumables;
      for ( vector<NDb::Ptr<NDb::Ability>>::const_iterator it = consumList.begin(); it != consumList.end(); ++it )
      {
        if ( PFAbilityData* pAbilityData = pHero->GetConsumableAbility( *it ) )
        {
          pAbilityData->RemoveForbid();
        }
      }
    }
  }

  if ( ( GetDB().flag & NDb::UNITFLAG_FORBIDPICK ) != 0 )
  {
    if ( NScene::SceneObject * pSObj = pReceiver->GetClientSceneObject() )
      pSObj->SetForbidPick( false );
  }

  unsigned int flags = GetDB().flag;
  if ( !GetDB().consumables.empty() )
    flags &= ~NDb::UNITFLAG_FORBIDUSECONSUMABLES;
  pReceiver->RemoveFlag(flags);

  PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplFlags::Reset()
{
  PFApplBuff::Reset();

  if ( IsEnabled() && ( GetDB().flag & NDb::UNITFLAG_FORBIDPICK ) != 0 )
  {
    if ( NScene::SceneObject * pSObj = pReceiver->GetClientSceneObject() )
      pSObj->SetForbidPick( true );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplFlags::DumpInfo(NLogg::CChannelLogger &logger) const
{
	PFApplBuff::DumpInfo(logger);

	FixedString<512> buf;
	for (int i = 0; i < NDb::KnownEnum<NDb::EUnitFlagType>::sizeOf; i++)
	{
		if (GetDB().flag & (1 << i))
		{
			buf += NDb::EnumToString(NDb::EUnitFlagType(i));
			buf += " ";
		}
	}
	LogLogicInfo(logger)("      flags: %s\n", buf.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeBaseAttack::Enable()
{
	PFApplBuff::Enable();

	if (GetDB().attackAbility)
	{
		CObj<PFBaseAttackData> pNewAttack(new PFBaseAttackData(pReceiver, GetDB().attackAbility));
		pNewAttack->LevelUp();

		pSavedBaseAttack = pReceiver->ReplaceBaseAttack(pNewAttack);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeBaseAttack::Disable()
{
	if (pSavedBaseAttack)
	{
		pReceiver->ReplaceBaseAttack(pSavedBaseAttack, GetDB().applyPassivePart);
		pSavedBaseAttack = 0;
	}
	PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplCreepBehaviourChange::IsStackableWithTheSameType() const 
{ 
	return (GetDB().behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_CHANGEPERMANENTLY) == 0; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplCreepBehaviourChange::Enable()
{
	PFApplBuff::Enable();
	PFBaseCreep* pCreep = dynamic_cast<PFBaseCreep*>( pReceiver.GetPtr() );
	NI_VERIFY(pCreep, "Behaviour change could be applied for base creep only", return; );

  const NDb::CreepBehaviourChangeApplicator &DB = GetDB();

  if ( ( DB.behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_DISABLEBEHAVIOUR ) != 0 && pCreep->HasBehaviour() )
  {
    pBehaviour = pCreep->Behaviour();
    if ( pBehaviour )
      pBehaviour->Disable();
  }
  else
  {
    CObj<PFSummonBehaviour> pSummonBehaviour;
    const NDb::SummonBehaviourBase*   pSummonBehaviourBase   = DB.behaviour;
    const NDb::SummonBehaviourCommon* pSummonBehaviourCommon = dynamic_cast<const NDb::SummonBehaviourCommon*>( pSummonBehaviourBase );

    float lifeTime = RetrieveParam( DB.lifeTime, 0.0f );

    CPtr<PFBaseMaleHero> pHero = dynamic_cast<PFBaseMaleHero*>( GetAbilityOwner().GetPtr() );
	  NI_VERIFY( pHero, "CreepBehaviourChange sender should be MaleHero", return );
    if ( pHero->IsDead() )
      return;

    if ( ( DB.behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_DUMMYBEHAVIOUR ) == 0 )
	  {
		  NDb::SummonType summonType;
		  if ( ( DB.behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_PRIMARYSUMMON ) != 0 )
      {
        summonType = NDb::SUMMONTYPE_PRIMARY;
      }
		  else
      {
        summonType = NDb::SUMMONTYPE_SECONDARY;
      }

      int maxSummonCount  = 1;
      if ( pSummonBehaviourCommon )
        maxSummonCount = RetrieveParam( pSummonBehaviourCommon->maxCount, 1 );
      int curSummonsCount = pHero->GetSummonsCount( summonType, DB.summonGroupName );

      if ( curSummonsCount == maxSummonCount )
      {
        pHero->RemoveSummons( 1, summonType, DB.summonGroupName );
      }

      pHero->SetMaxAllowedSummons( summonType, DB.summonGroupName, maxSummonCount );

      pSummonBehaviour = PFSummonedUnitAIBehaviour::Create( pCreep, pHero.GetPtr(), pSummonBehaviourBase, summonType, 
        lifeTime, PFSummonedUnitBehaviour::BEHAVIOURFLAGS_NONE );
	  }
	  else
    {
      pSummonBehaviour = PFSummonedUnitBehaviour::Create( pCreep, pHero.GetPtr(), pSummonBehaviourBase, 
        lifeTime, PFSummonedUnitBehaviour::BEHAVIOURFLAGS_NONE );
    }

    pSummonBehaviour->SetGroupName( DB.summonGroupName );
    pBehaviour = pSummonBehaviour;

    // Disconnect neutral creep from its spawner and disable levelups, if it's gonna be a primary summon (NUM_TASK)
    if ( ( DB.behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_PRIMARYSUMMON ) != 0 )
    {
      NWorld::PFNeutralCreep * pNeutralCreep = dynamic_cast<NWorld::PFNeutralCreep *>( pReceiver.GetPtr() );

      if (pNeutralCreep)
      {
        pNeutralCreep->DettachFromSpawner();
        pNeutralCreep->DisableLevelUps();
      }
    }

	  // Change faction
	  if ( ( DB.behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_CHANGEFACTION ) != 0 )
	  {
      if ( pBehaviour->GetFaction() != GetAbilityOwner()->GetFaction() )
        GetAbilityOwner()->CancelAllDispatchFromUnit( pCreep );
		  pBehaviour->SetFaction( GetAbilityOwner()->GetFaction() );
	  }

	  // Change unit type
	  if ( ( DB.behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_CHANGETYPE2SUMMON ) != 0 )
	  {
		  pBehaviour->SetUnitType( NDb::UNITTYPE_SUMMON );
	  }

    pCreep->AddBehaviourOnTop( pBehaviour );

    if ( pSummonBehaviourCommon )
    {
      if ( pSummonBehaviourCommon->targetingParams )
      {
        oldTargetingParams = pCreep->GetTargetingParamsPtr();
        pCreep->OverrideTargetingParams( pSummonBehaviourCommon->targetingParams );
      }

      pSummonBehaviour->SetLashRange( pSummonBehaviourCommon->lashRange(pOwner, pCreep, this, 15.f ) );
      pSummonBehaviour->SetResponseRange( pSummonBehaviourCommon->responseRange );
      pSummonBehaviour->SetResponseTime( pSummonBehaviourCommon->responseTime );
    }
  }

	// Activate applicators on unit
	CPtr<PFBaseUnit> pChangedUnit( pCreep );
	CreateAndActivateApplicators( DB.applicators, pAbility, Target( pChangedUnit ), this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplCreepBehaviourChange::Disable()
{
	PFBaseCreep *pCreep = dynamic_cast<PFBaseCreep*>(pReceiver.GetPtr());
	NI_VERIFY(pCreep, 
		        NStr::StrFmt("Behaviour change could be applied for base creep only, but applying on %s", 
						              MakeUnitIDString(pReceiver)), 
			      PFApplBuff::Disable(); return; )

  if ( ( GetDB().behaviourChangeFlags & NDb::BEHAVIOURCHANGEFLAGS_DISABLEBEHAVIOUR ) != 0 )
  {
    if ( pBehaviour )
      pBehaviour->Enable();
  }
  else
  {
    if ( pBehaviour )
      pCreep->RemoveBehaviour(pBehaviour);
  }

  if ( oldTargetingParams )
  {
    pCreep->OverrideTargetingParams( oldTargetingParams );
  }

	PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplDamageReflect::OnDamage(CPtr<PFBaseUnit> pSender_, float damageInput, float damage4Apply, int damageType)
{
  if (!RetrieveParam(pDBAppl->enabled, true))
    return 0.0f;
  
  float damage2Reflect = damage4Apply * amountInPersent;
  // Deal damage to sender

  // Reduce damage
  return -damage2Reflect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplOnDamage::Enable()
{
	pReceiver->AddEventListener(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplOnDamage::Disable()
{
	pReceiver->RemoveEventListener(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PFApplOnDamage::OnEvent(const PFBaseUnitEvent *pEvent)
{
	if (pEvent->GetType() != NDb::BASEUNITEVENT_DAMAGE)
		return 0;

	// Get our event
	const PFBaseUnitDamageEvent *pDmg = static_cast<const PFBaseUnitDamageEvent*>(pEvent);
	NI_ASSERT(pDmg->pDesc, "Event should have description");

	if ( !CheckDamageTypeFilter(pDmg->pDesc->flags, pDmg->pDesc->damageType, GetDB().filterFlags, false) )
    return 0;
  
	Target targ;
	if (GetDB().spellTarget != NDb::APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET)
		MakeApplicationTarget(targ, GetDB().spellTarget);
	else
		targ.SetUnit(pDmg->pDesc->pSender);

	if (targ.IsValid())
	{
	  Target source;
	  MakeApplicationTarget(source);

		CreateDispatch(pAbility, this, source, targ, GetDB().spell, PFBaseApplicator::FLAG_REFLECTED);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFApplInvisibility::PFApplInvisibility(PFApplCreatePars const &cp)
  : Base(cp)
  , state(FADEIN)
  , time(0.0f)
  , invisible(false)
  , visibilityFlags()
  , partialVisibilityEnabled(false)
  , partialVisibilityRevision(0)
{

}

void PFApplInvisibility::PrepareEffects( bool manualDeathTypeOnly )
{
  PFApplBuff::PrepareEffects( manualDeathTypeOnly );

  for ( int i = 0; i < effects.size(); i++ )
  {
    PF_Core::BasicEffect* pEffect = effects[i];

    switch ( pEffect->GetDBDesc()->GetObjectTypeID() )
    {
    case NDb::EffectSwitcher::typeId:
      {
        NGameX::PFEffectSwitcher* pEffectSwitcher = static_cast<NGameX::PFEffectSwitcher*>( pEffect );
        pEffectSwitcher->SetDBFadeInTime( RetrieveParam( GetDB().fadeIn ) );
        if ( time <= 0.0f )
        {
          pEffectSwitcher->SetSwitchByVisibility();
        }
        break;
      }
    case NDb::InvisibilityEffect::typeId:
      {
        PF_Core::ScaleColorEffect* pScaleColorEffect = static_cast<PF_Core::ScaleColorEffect*>( pEffect );
        pScaleColorEffect->SetDBFadeInTime( RetrieveParam( GetDB().fadeIn ) );
        break;
      }
    }
  }
}

bool PFApplInvisibility::Start()
{
  if ( Base::Start() )
    return true;

  if ( pReceiver->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDINVISIBILITY ) )
    return true;

  return false;
}

void PFApplInvisibility::Enable()
{
  const NDb::InvisibilityApplicator& dbDesc = GetDB();

  pReceiver->AddEventListener( this );

  pReceiver->AddFlag( NDb::UNITFLAG_FORBIDAUTOATTACK );
  pReceiver->DropTarget();

  time = RetrieveParam( dbDesc.fadeIn );
  if ( time > 0.0f )
  {
    state = FADEIN;
  }
  else
  {
    becomeInvisible();
    state = INVISIBLE;
  }

  PFApplBuff::Enable();
}

void PFApplInvisibility::Disable()
{
  if (invisible)
    becomeVisible();

  if (IsValid(pReceiver))
  {
    pReceiver->RemoveFlag(NDb::UNITFLAG_FORBIDAUTOATTACK);
    pReceiver->RemoveEventListener(this);
  }

  PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplInvisibility::Step(float dtInSeconds)
{
  if (PFApplBuff::Step(dtInSeconds))
    return true;

  // do not update states if disabled
  if ( IsEnabled() )
  {
    if (FADEIN == state)
    {
      time -= dtInSeconds;
      if (time < 0.0f)
      {
        becomeInvisible();

        state = INVISIBLE;
      }
    }
  }

  UpdateVisibility();

  return (state == CANCEL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PFApplInvisibility::OnEvent(const PFBaseUnitEvent *pEvent)
{
  NI_VERIFY(NULL != pEvent, "PFApplInvisibility: Wrong event ptr", return 0);
  
  NDb::EBaseUnitEvent eventType = pEvent->GetType();

  if ( ( NDb::BASEUNITEVENT_CANCELINVISIBILITY == eventType && !GetDB().ignoreCancel ) || NDb::BASEUNITEVENT_ATTACK == eventType )
  {
    state = CANCEL;
  }
  else if (NDb::BASEUNITEVENT_CASTMAGIC == eventType || 
           NDb::BASEUNITEVENT_USECONSUMABLE == eventType ||
           NDb::BASEUNITEVENT_USETALENT == eventType)
  {
    PFBaseUnitUseAbilityEvent const *pAbilityEvent = dynamic_cast<PFBaseUnitUseAbilityEvent const *>(pEvent);
    NI_VERIFY(pAbilityEvent, "PFApplInvisibility: Wrong event type", return 0);
    NI_VERIFY(IsValid(pAbilityEvent->GetAbility()), "Invalid ability!", return 0);
    PFAbilityInstance const *pInstance = pAbilityEvent->GetAbility();

    // do nothing if it the same ability instance that created invisibility applicator
    if (pInstance == pAbility)
      return 0;

    NI_VERIFY(NULL != pInstance->GetData(), "Invalid ability data", return 0);
    if ((pInstance->GetFlags() & NDb::ABILITYFLAGS_STAYINVISIBLE) == 0)
    {
      state = CANCEL;
    }
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplInvisibility::becomeVisible()
{
  invisible = false;

  RemoveChildrenApplicators();

  if (IsValid(pReceiver))
  {
    pReceiver->RemoveFlag(NDb::UNITFLAG_INVISIBLE);
    pReceiver->UpdateInvisibility();
  }

  ApplyPartialVisibility(false, true);
}

void PFApplInvisibility::becomeInvisible()
{
  if (IsValid(pReceiver))
  {
    pReceiver->AddFlag(NDb::UNITFLAG_INVISIBLE);
    pReceiver->UpdateInvisibility();

    if (GetDB().onBecomeInvisible)
    {
      Target target(pReceiver);
      CreateDispatch(GetAbility(), this, target, target, GetDB().onBecomeInvisible);
    }
  }
  
  invisible = true;

  visibilityFlags.Reset();

  UpdateVisibility(true);
}

void PFApplInvisibility::ApplyPartialVisibility(const bool enabled, const bool force /*= false*/)
{
// TODO: VISUAL_CUTTED ?
#ifndef VISUAL_CUTTED
  struct Enabler : NScene::FullTraverser, NonCopyable
  {
    enum
    {
      flagsEffectIgnoreInvisibility = (NScene::SceneComponent::GROUPFLAGS_EFFECT | NDb::EFFECTGROUPFLAGS_IGNOREINVISIBILITY)
    };

    Enabler(const bool enabled = true)
      : enabled(enabled)
    {

    }

    void operator()(NScene::SceneComponent* const component) const
    {
      if (enabled)
      {
        const bool visible = ((component->GetGroupFlags() & flagsEffectIgnoreInvisibility) == flagsEffectIgnoreInvisibility);

        component->SetHide(!visible);
      }
      else
      {
        component->SetHide(false);
      }
    }
  private:
    bool enabled;
  };

  if (!IsValid(pReceiver))
    return;
  if (!IsValid(pReceiver->ClientObject()))
    return;

  if (NScene::SceneObject* const so = pReceiver->ClientObject()->GetSceneObject())
  {
    const int revision = so->GetListOfComponentsVersion();

    const bool changed =
      (partialVisibilityEnabled != enabled) ||
      (partialVisibilityRevision != revision);

    if (!changed && !force)
      return;

    partialVisibilityEnabled = enabled;
    partialVisibilityRevision = revision;

    const Enabler enabler(enabled);

    so->Traverse(enabler);
  }
#endif // VISUAL_CUTTED
}

void PFApplInvisibility::DoSwitchEffects(const bool visibleForPlayer) const
{
  if (!IsValid(pReceiver))
    return;

  for (int i = 0; i < effects.size(); ++i)
  {
    const CObj<PF_Core::BasicEffect> effect(effects[i]);

    if (effect->GetDBDesc()->GetObjectTypeID() != NDb::EffectSwitcher::typeId)
      continue;

    NGameX::PFEffectSwitcher* const effectSwitcher = static_cast<NGameX::PFEffectSwitcher*>(effect.GetPtr());

    if (IsValid(pOwner))
      effectSwitcher->SetActiveStateName(pOwner->GetSkinId());

    effectSwitcher->SwitchEffect(visibleForPlayer, pReceiver->ClientObject());
  }
}

void PFApplInvisibility::UpdateVisibility(const bool resetPartialVisibility /*= false*/)
{
  using namespace NGameX;

  const ClientVisibilityFlags currentVisibilityFlags(ClientVisibilityHelper::GetFlags(pReceiver));

  const bool changed = (visibilityFlags != currentVisibilityFlags);

  visibilityFlags = currentVisibilityFlags;

  if (changed)
    DoSwitchEffects(ClientVisibilityHelper::IsVisibleForPlayer(visibilityFlags));

  if (changed || resetPartialVisibility)
    ApplyPartialVisibility(ClientVisibilityHelper::IsPartialVisibilityApplicable(visibilityFlags), resetPartialVisibility);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplTargetsCounter::EnumerateTargets()
{
  struct CalcTargets : public ITargetAction, NonCopyable
  {
    CalcTargets(int &targetsCount) : targetsCount(targetsCount) {}
    int& targetsCount;
    virtual void operator()(const Target &target) { targetsCount++; }
  } f(targetsCount);

  PFTargetSelector::RequestParams pars( *this, GetTarget() );
  targetSelector->EnumerateTargets(f, pars);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplTargetsCounter::Start()
{
  NI_VERIFY( GetDB().targetSelector, "Have not target selector for enumerate targets", return false; );
  targetSelector = GetDB().targetSelector->Create( GetWorld() );
  NI_VERIFY( targetSelector, NStr::StrFmt("Failed to create TargetSelector for applicator id=%s", NDb::GetFormattedDbId( GetDB().GetDBID() ) ), return true );

  EnumerateTargets();

  return Base::Start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplTargetsCounter::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  if ( PFApplBuff::Step(dtInSeconds) )
    return true;
  
  targetsCount = 0;

  if ( !IsEnabled() )
  {
    return false;
  }
  
  EnumerateTargets();

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplTargetsCounter::GetVariable(const char* varName) const
{
  if ( !strncmp( varName, targetsCountVariableName, strlen(targetsCountVariableName) ) )
    return targetsCount;

  return Base::GetVariable(varName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplValue::Start()
{
  value = RetrieveParam(GetDB().value, 0.0f);

  return Base::Start(); 
}

float PFApplValue::GetVariable(const char* varName) const
{
  static const char* s_variableName = "Value";
  if ( strcmp( varName, s_variableName ) == 0 )
    return value;
  return Base::GetVariable(varName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplMarker::Start()
{
  string markerName( GetApplicatorName() );

  char buf[8];
  _itoa_s( GetAbilityOwner()->GetObjectId(), buf, 8, 36 ); // 8 is because radix 36 gives up to 7 digits for 2^32

  markerName.append( buf );

  pStat = pReceiver->GetVariableVWM( markerName.c_str() );

  if (PFApplBuff::Start())
    return true;

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplMarker::Enable()
{
  PFApplBuff::Enable();
  NI_ASSERT(IsValid(pReceiver), "Unit should be valid");
  if (!pStat)
    return;

  float multValue = GetDB().multValue(this->pOwner, pReceiver, this, 1.0f);
  float addValue = GetDB().addValue(this->pOwner, pReceiver, this, 1.0f);

  modifierID = pStat->AddModifier( multValue/*1.0f*/, addValue/*1.0f*/, GetAbilityOwner()->GetObjectId() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplMarker::Disable()
{
  if (!pStat)
    return;
  
	NI_ASSERT(modifierID >= 0, "Modifier should be valid");

  pStat->RemoveModifier( modifierID );
  modifierID = INVALID_MODIFIER_ID;

  PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplMarker::GetVariable(const char* varName) const
{
  static const char* s_variableName = "value";
  if ( !strncmp( varName, s_variableName, strlen(s_variableName) ) )
    return pStat->GetValue();
  return Base::GetVariable(varName);
}

void PFApplMarker::Reset()
{
	PFApplBuff::Reset();

  if (IsValid(pReceiver) && !pReceiver->IsObjectDead())
  {
	  string markerName( GetApplicatorName() );
	  char buf[8];
	  _itoa_s( GetAbilityOwner()->GetObjectId(), buf, 8, 36 );
	  markerName.append( buf );
	  pStat = pReceiver->SearchVariableVWM( markerName.c_str() );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeHeroState::Enable()
{
  PFBaseHero* pBaseHero = dynamic_cast<PFBaseHero*>(pReceiver.GetPtr());
  NI_VERIFY(pBaseHero, "Change hero state applicator can only be applied to hero!", return;);
  pBaseHero->SetHeroState(EHeroState::Second);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeHeroState::Disable()
{
  if (PFBaseHero* pBaseHero = dynamic_cast<PFBaseHero*>(pReceiver.GetPtr()))
    pBaseHero->SetHeroState(EHeroState::First);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSceneObjectChange::Start()
{
  const NDb::SceneObjectChangeApplicator &DB = GetDB();

  sceneObjectIndex = RetrieveParam( DB.sceneObjectIndex );

  NI_VERIFY(sceneObjectIndex >= 0 && sceneObjectIndex < DB.sceneObjects.size(),NStr::StrFmt("Wrong sceneObjectIndex formula in applicator '%s' (sceneObjectIndex: %i)!", NDb::GetFormattedDbId(DB.GetDBID()), sceneObjectIndex),
      sceneObjectIndex = 0; );

  NI_VERIFY( DB.sceneObjects[sceneObjectIndex], NStr::StrFmt("Failed to get sceneObject in applicator '%s' (sceneObjectIndex: %i)!", NDb::GetFormattedDbId(DB.GetDBID()), sceneObjectIndex),
      return true; );

  return PFApplBuff::Start();
}

bool PFApplSceneObjectChange::Step( float dtInSeconds )
{
  if ( PFApplBuff::Step( dtInSeconds ) )
  {
    return true;
  }

  if ( !IsEnabled() )
  {
    return false;
  }

  if ( pReceiver->IsTrueHero() )
  {
    PFBaseUnit* pBaseUnit = pReceiver;
    PFBaseHero* pBaseHero = dynamic_cast<PFBaseHero*>( pBaseUnit );
    float timeToRespawn = pBaseHero->GetTimeToRespawn();
    if ( ( timeToRespawn > 0.0f ) && ( timeToRespawn <= pWorld->GetStepLengthInSeconds() ) )
    {
      return true;
    }
  }

  return false;
}


void PFApplSceneObjectChange::Enable()
{
  PFApplBuff::Enable();

  if ( pReceiver->ClientObject() )
  {
    oldSceneObject = pReceiver->ClientObject()->GetSceneObjectDesc();
    pReceiver->ClientObject()->SetSceneObject( GetDB().sceneObjects[sceneObjectIndex] );
  }
  pReceiver->PlanToRestoreSceneObject( oldSceneObject );
  pReceiver->PlanToRestoreStatusEffects();
}

void PFApplSceneObjectChange::Disable()
{
  pReceiver->RestoreSceneObject();
  pReceiver->PlanToRestoreStatusEffects();

  PFApplBuff::Disable();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplTaunt::Start()
{
  if (PFApplBuff::Start())
    return true;

  Target tgt;
  MakeApplicationTarget(tgt, GetDB().tauntTarget);
  NI_VERIFY(tgt.IsUnit(), "Trying to taunt on non-unit target", return true; );

  tauntSource = tgt.GetUnit();
  if ( IsUnitValid(pReceiver) && IsUnitValid(tauntSource) && pReceiver->CanAttackTarget( tauntSource ) )
  {
    pReceiver->OnTarget( tauntSource, GetDB().strongTarget );
    pReceiver->OnBeginTaunt();
  }

  pReceiver->RegisterTauntApplicator(this);
  lastVisiblePos = tauntSource->GetPosition().AsVec2D();

  return false;
}

bool PFApplTaunt::Step(float dtInSeconds)
{
  if(!IsUnitValid(pReceiver) || !IsUnitValid(tauntSource))
  {
    return true;
  }

  if(tauntSource != pReceiver->GetAppliedTaunts().GetLast()->GetTauntSource())
    return PFApplBuff::Step(dtInSeconds);

  bool visible = pReceiver->CanSelectTarget(tauntSource, true);
  if(visible)
  {
    lastVisiblePos = tauntSource->GetPosition().AsVec2D();
  }

  // Keep attacking taunt source while taunted
  if(/*!pReceiver->IsInCombat() ||*/ pReceiver->GetCurrentTarget() != tauntSource)
  {
    if(IsUnitValid(pReceiver) && pReceiver->CanAttackTarget(tauntSource) && (pReceiver->GetCurrentTarget() != tauntSource))
    {
      // If target goes out of sight, move to last known position in hope to locate the taunt source
      if(!visible)
      {
        if(PFBaseMovingUnit* movingUnit = dynamic_cast<PFBaseMovingUnit*>(pReceiver.GetPtr()))
        {
          movingUnit->MoveTo(lastVisiblePos);
        }
      }
      else
      {
        pReceiver->OnTarget( tauntSource, GetDB().strongTarget );
        pReceiver->OnBeginTaunt();
      }
    }
  }

  return PFApplBuff::Step(dtInSeconds);
}

void PFApplTaunt::Stop()
{
  if(IsUnitValid(pReceiver))
  {
    if(/*!pReceiver->IsAlphaSummon() &&*/ IsUnitValid(pReceiver->GetMasterUnit()))
    {
      pReceiver->Cleanup();
    }
  }

  if(IsValid(pReceiver))
  {
    if(pReceiver->GetAppliedTaunts().IsItLast(this))
      pReceiver->GetAppliedTaunts().RemoveLast();

    pReceiver->OnEndTaunt();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFApplTechAbilityUpgrade::PFApplTechAbilityUpgrade(const PFApplCreatePars& cp)
  : Base(cp)
{
}

PFApplTechAbilityUpgrade::PFApplTechAbilityUpgrade()
{
}

PFApplTechAbilityUpgrade::~PFApplTechAbilityUpgrade()
{
}

bool PFApplTechAbilityUpgrade::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  const int talentObjectId = GetDB().abilityObjectId;
  const int talentLastUseStep = GetDB().abilityLastUseStep;

  ValueWithModifiers* const vwm = GetReceiver()->GetVariableVWM(GetTalentLastUseStepVariableName(talentObjectId));

  vwm->SetBaseValue(static_cast<float>(talentLastUseStep));

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // End of namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFApplDamageReflect,        NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplOnDamage,             NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplFlags,                NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplStatMod,              NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplPermanentStatMod,     NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAbilityMod,           NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAbilityUpgrade,       NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplStatus,               NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplChangeBaseAttack,     NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplCreepBehaviourChange, NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplInvisibility,         NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplTargetsCounter,       NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplValue,                NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplMarker,               NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplChangeHeroState,      NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSceneObjectChange,    NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplTaunt,                NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplTechAbilityUpgrade,   NWorld);
