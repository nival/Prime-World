#include "stdafx.h"

#include "PFWorld.h"
#include "PFAIWorld.h"

#include "PFApplicator.h"
#include "PFApplBuff.h"
#include "PFApplInstant.h"

#include "PFBaseUnit.h"
#include "PFBaseAttackData.h"

#include "PFStatistics.h"
#include "TargetSelectorFormulaPars.h"

#include "PFTalent.h"

namespace NWorld
{

namespace 
{

float const s_appliedApplicatorHistoryDecayTime = 35.f;
float const s_sentApplicatorHistoryDecayTime = 35.f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct StopAndDeleteApplicator_
{
	void operator()(const CObj<PFBaseApplicator> &app)
	{
		app->Stop();
		app->RemoveFromRingsSafe();
	}
};

struct StopAndDeleteApplicatorOnDeath_
{
  void operator()(const CObj<PFBaseApplicator> &app)
  {
    if ( app->NeedToStopOnDeath() )
    {
      app->SetStopReason(APPL_STOP_REASON_ONDEATH);
      app->Stop();
      app->RemoveFromRingsSafe();
    }
  }
};

struct StopAndDeleteApplicatorOnSenderDeath_
{
  void operator()(const CObj<PFBaseApplicator> &app)
  {
    if ( app->NeedToStopOnSenderDeath() )
    {
      app->Stop();
      app->RemoveFromRingsSafe();
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DeleteAppliedApplicator_
{
	void operator()(const CObj<PFBaseApplicator> &app) { app->RemoveFromAppliedRing(); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DeleteSentApplicator_
{
	void operator()(const CObj<PFBaseApplicator> &app) { app->RemoveFromSentRing(); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RecalculateApplicator1_
{
	void operator()(const CObj<PFBaseApplicator> &app) { app->Recalculate(); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DamageCalculator
{
  DamageCalculator(): amount(0) {}
  void operator()(const NWorld::PFBaseApplicator * pApp)
  {
    const NWorld::PFApplDamage * damageAppl = dynamic_cast<const NWorld::PFApplDamage *> (pApp);
    if (damageAppl)
      amount+=damageAppl->GetDamageDealed();
  }

  int amount;
};

struct DamageCalculatorEx
{
  DamageCalculatorEx(const PFAbilityData* const pAbility, const unsigned mask)
    : pAbility(pAbility)
    , mask(mask)
    , amount(0)
  {
  }

  void operator()(const NWorld::PFBaseApplicator * pApp)
  {
    if (pApp->GetTypeId() != NWorld::PFApplDamage::typeId)
      return;

    const NWorld::PFApplDamage* const applDamage = static_cast<const NWorld::PFApplDamage*>(pApp);

    if (mask & DMG_UNIT)
    {
      amount += applDamage->GetDamageDealed();
      return;
    }

    const NWorld::PFAbilityData* const abilityData = pApp->GetAbilityData();

    if (mask & DMG_APPLICATOR_ABILITY)
    {
      if (abilityData != pAbility)
        return;
    }

    // HACKY: упрощает дальнейшую проверку
    unsigned flags = DMG_APPLICATOR_ABILITY;

    switch (abilityData->GetAbilityTypeId())
    {
    case NDb::ABILITYTYPEID_BASEATTACK:
      flags |= DMG_ABILITY_ATTACK;
      break;
    case NDb::ABILITYTYPEID_ABILITY0:
      flags |= DMG_ABILITY1;
      break;
    case NDb::ABILITYTYPEID_ABILITY1:
      flags |= DMG_ABILITY2;
      break;
    case NDb::ABILITYTYPEID_ABILITY2:
      flags |= DMG_ABILITY3;
      break;
    case NDb::ABILITYTYPEID_ABILITY3:
      flags |= DMG_ABILITY4;
      break;
    case NDb::ABILITYTYPEID_ABILITY4:
      flags |= DMG_ABILITY5;
      break;
    case NDb::ABILITYTYPEID_TALENT:
      flags |= DMG_TALENT;

      NI_ASSERT(abilityData->GetTypeId() == NWorld::PFTalent::typeId, "Ability is not a talent!");

      {
        const NWorld::PFTalent* const talent = static_cast<const NWorld::PFTalent*>(abilityData);

        switch (talent->GetTalentDesc()->rarity)
        {
        case NDb::TALENTRARITY_CLASS:
          flags |= DMG_TALENT_CLASS;
          break;
        case NDb::TALENTRARITY_ORDINARY:
          flags |= DMG_TALENT_ORDINARY;
          break;
        case NDb::TALENTRARITY_GOOD:
          flags |= DMG_TALENT_GOOD;
          break;
        case NDb::TALENTRARITY_EXCELLENT:
          flags |= DMG_TALENT_EXCELLENT;
          break;
        case NDb::TALENTRARITY_MAGNIFICENT:
          flags |= DMG_TALENT_MAGNIFICENT;
          break;
        case NDb::TALENTRARITY_EXCLUSIVE:
          flags |= DMG_TALENT_EXCLUSIVE;
          break;
        case NDb::TALENTRARITY_OUTSTANDING:
          flags |= DMG_TALENT_OUTSTANDING;
          break;
        }
      }

      switch (abilityData->GetTalentLevel())
      {
      case NDb::TALENTLEVEL_ID0:
        flags |= DMG_TALENT_TIER1;
        break;
      case NDb::TALENTLEVEL_ID1:
        flags |= DMG_TALENT_TIER2;
        break;
      case NDb::TALENTLEVEL_ID2:
        flags |= DMG_TALENT_TIER3;
        break;
      case NDb::TALENTLEVEL_ID3:
        flags |= DMG_TALENT_TIER4;
        break;
      case NDb::TALENTLEVEL_ID4:
        flags |= DMG_TALENT_TIER5;
        break;
      case NDb::TALENTLEVEL_ID5:
        flags |= DMG_TALENT_TIER6;
        break;
      }

      break;
    case NDb::ABILITYTYPEID_SPECIAL:
      flags |= DMG_ABILITY_SPECIAL;
      break;
    }

    if (flags & mask)
      amount += applDamage->GetDamageDealed();
  }

  const PFAbilityData* pAbility;
  unsigned mask;
  int amount;
};

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::OnApplicatorApply(CObj<PFBaseApplicator> pApplicator)
{
	PFBaseUnitApplicatorAppliedEvent evtApplicator(pApplicator);
  EventHappened(evtApplicator);
  if ( evtApplicator.IsApplicatorCancelled() )
    return false;

  // Start applicator on this unit
  if (pApplicator->Start())
	{
		pApplicator->Stop();
		NI_ASSERT(!pApplicator->IsLinkedToAppliedRing() && !pApplicator->IsLinkedToSentRing(), "Strange");
		MemorizeApplicator(pApplicator);
	}
	else
	{
    {
      string const& applName = pApplicator->GetApplicatorName();
      if ( !applName.empty() )
        RegisterNamedApplicator(pApplicator.GetPtr());
    }
    
    RegisterAppliedApplicator(pApplicator);
		CPtr<PFBaseUnit> pSender = pApplicator->GetAbilityOwner();
    if (IsValid(pSender))
			pSender->RegisterSentApplicator(pApplicator);
    else
      NI_ASSERT( !pApplicator->GetAbility(), "Sender must be valid!");
	}

  GetWorld()->GetStatistics()->OnApplicatorApply(pApplicator);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::StepApplicators(float dtInSeconds)
{
  NI_PROFILE_FUNCTION
	PFBaseApplicator::StepRing( appliedApplicators, dtInSeconds );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::StepApplicatorsHistory()
{
  {
    DeleteAppliedApplicator_ d;
		ForAllAppliedApplicatorsInHistoryGreater(d, s_appliedApplicatorHistoryDecayTime);
	}
	{
		DeleteSentApplicator_ d;
		ForAllSentApplicatorsInHistoryGreater(d, s_sentApplicatorHistoryDecayTime);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RecalculateApplicators()
{
	RecalculateApplicator1_ rec;
	ForAllAppliedApplicatorsSafe(rec);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveAppliedApplicators()
{
	StopAndDeleteApplicator_ d;
	ForAllAppliedApplicators(d);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveSentApplicators()
{
	StopAndDeleteApplicator_ d;
	ForAllSentApplicators(d);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveAppliedApplicatorsOnDeath()
{
  StopAndDeleteApplicatorOnDeath_ d;
  ForAllAppliedApplicators(d);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveSentApplicatorsOnDeath()
{
  StopAndDeleteApplicatorOnSenderDeath_ d;
  ForAllSentApplicators(d);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CleanupHistoryApplicators()
{
	DeleteAppliedApplicator_ dA;
	ForAllAppliedApplicatorsInHistory(dA);

	DeleteSentApplicator_ dS;
	ForAllSentApplicatorsInHistory(dS);
}

void PFBaseUnit::CleanupTauntApplicatorsStack()
{
  tauntApplicators.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AddEventListener(CPtr<PFBaseUnitEventListener> pListener)
{
  // LISTENER_DEFAULT has lowest priority
  // Other listener types have their priority judged by order in EListenerType enum
  // Priority for same listener types is resolved by GetPriority(); for Shield Applicators it is a duration
  struct PosFinder
  {
    PosFinder( PFBaseUnitEventListener const* _pNewListener ) : pNewListener(_pNewListener) {}

    bool operator()( CObj<PFBaseUnitEventListener>& pItem )
    {
      PFBaseUnitEventListener::EListenerType newListenerType = pNewListener->GetListenerType();
      PFBaseUnitEventListener::EListenerType itemListenerType = pItem->GetListenerType();
      if ( itemListenerType == PFBaseUnitEventListener::LISTENER_DEFAULT || newListenerType < itemListenerType )
      {
        return true;
      }
      else if ( newListenerType == itemListenerType )
      {
        return pNewListener->GetListenerPriority() > pItem->GetListenerPriority();
      }
      return false;
    }

    PFBaseUnitEventListener const* pNewListener;
  } listenerPosFinder( pListener );

	nstl::list<CObj<PFBaseUnitEventListener>>::iterator it = nstl::find( eventListeners.begin(), eventListeners.end(), pListener );
	if ( it == eventListeners.end() )
  {
    // no preferences for default listeners
    if ( pListener->GetListenerType() == PFBaseUnitEventListener::LISTENER_DEFAULT )
    {
      eventListeners.push_back( pListener.GetPtr() );
    }
    else
    {
      it = nstl::find_if( eventListeners.begin(), eventListeners.end(), listenerPosFinder );
      eventListeners.insert( it, pListener.GetPtr() );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveEventListener(CPtr<PFBaseUnitEventListener> pListener)
{
  if(IsValid(pListener) && !eventListeners.empty())
  {
	  nstl::list<CObj<PFBaseUnitEventListener>>::iterator it = nstl::find( eventListeners.begin(), eventListeners.end(), pListener );
	  if ( it != eventListeners.end() )
		  eventListeners.erase( it );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::EventHappened(const PFBaseUnitEvent &evt)
{
	if ( eventListeners.empty() )
		return;

  bool isAlive = true;
  unsigned int returnFlags;
	
	for ( nstl::list<CObj<PFBaseUnitEventListener>>::iterator it = eventListeners.begin(); it != eventListeners.end(); )
	{
		PFBaseUnitEventListener *pListener = *it;

    if (pListener)
    {
      isAlive = pListener->IsAlive();
      returnFlags = 0;

      if(isAlive)
        returnFlags = pListener->OnEvent(&evt);

      if ((returnFlags & PFBaseUnitEventListener::FLAGS_REMOVE) || !isAlive)
        it = eventListeners.erase( it );
      else 
        ++it;
    }
    else
    {
      NI_ALWAYS_ASSERT("Bad event listener!");
      it = eventListeners.erase( it );
    }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AddAbilityUpgradeApplicator( PFApplAbilityUpgrade *pAppl )
{
  abilitiesUpgrades.addLast(pAppl);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveAbilityUpgradeApplicator( PFApplAbilityUpgrade *pAppl )
{
  PFApplAbilityUpgrade::Ring::remove(pAppl);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplAbilityUpgrade::Ring const & PFBaseUnit::GetAbilityUpgradeApplicators() const
{
  return abilitiesUpgrades;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IMiscFormulaPars const* PFBaseUnit::FindApplicator(const char* name, IMiscFormulaPars const* pMisc, ApplicatorSearchType searchType) const
{
  return FindApplicator( name, pMisc, searchType, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const IMiscFormulaPars* PFBaseUnit::FindApplicator( const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType, int idx ) const
{
  TargetSelectorFormulaPars const* pTSPars = dynamic_cast<TargetSelectorFormulaPars const*>(pMisc);

  const IMiscFormulaPars* pOrigMisc = pMisc;

  if ( pTSPars )
    pMisc = pTSPars->GetMisc();

  PFBaseApplicator const* pMiscAppl = dynamic_cast<PFBaseApplicator const*>(pMisc);
  PFAbilityData const* pMiscAblt = dynamic_cast<PFAbilityData const*>(pMisc);
  
  if ( searchType != GLOBAL )
  {
    if ( pMiscAblt )
    {
      NI_VERIFY( searchType == GLOBAL || searchType == UNIT || searchType == UNIT_AND_SUMMONS, "Wrong searchType in FindApplicator for ability formula: can search only for GLOBAL, UNIT or UNIT_AND_SUMMONS if formula is not in the applicator. GLOBAL searchType will be used instead!"
        , searchType = GLOBAL );
    }
    else
    {
      NI_VERIFY( pMiscAppl, "pMisc must be an applicator or ability! Find applicator by name can be called only from an applicators or abilities formulas!"
        , return pMisc );
    }
  }

  CPtr<PFBaseUnit> pMiscAbilityOwner = (searchType == GLOBAL) ? 0 : (pMiscAblt ? pMiscAblt->GetOwner() : pMiscAppl->GetAbilityOwner());

  int foundCount = 0;
  for (ring::Range<PFBaseApplicator::NamedRing> it(namedApplicators); it;)
  {
    PFBaseApplicator *pApplicator = &(*it);
    ++it;

    const string& applName = pApplicator->GetApplicatorName();
    bool found = false;
    if ( !applName.compare(name) )
    {
      if (searchType == UNIT)
      {
        if ( pApplicator->GetAbilityOwner() == pMiscAbilityOwner )
          found = true;
      }
      else if (searchType == ABILITY)
      {
        if ( pApplicator->GetAbility() == pMiscAppl->GetAbility() )
          found = true;
      }
      else if (searchType == DISPATCH)
      {
        if ( pApplicator->GetDispatch() == pMiscAppl->GetDispatch() )
          found = true;
      }
      else if (searchType == UNIT_AND_SUMMONS)
      {
        if ( ( pApplicator->GetAbilityOwner() == pMiscAbilityOwner ) || ( pApplicator->GetAbilityOwner()->GetMasterUnit() == pMiscAbilityOwner ) )
          found = true;
      }
      else //if (searchType == GLOBAL)
        found = true;
    }
    if ( found )
    {
      if ( foundCount >= idx )
        return pApplicator;
      ++foundCount;
    }
  }

  // Check for instant applicator proxied in ability
  //if ( searchType == ABILITY )
  //{
  //  IMiscFormulaPars const* proxiedApplData;
  //  if ( pMiscAppl->GetAbility()->FindProxiedApplicatorData( name, proxiedApplData ) )
  //    return proxiedApplData;
  //}

  //NI_ALWAYS_ASSERT( NStr::StrFmt("Applicator '%s' not found by name!", name) );
  return pOrigMisc;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::CountApplicators( const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const
{
  TargetSelectorFormulaPars const* pTSPars = dynamic_cast<TargetSelectorFormulaPars const*>(pMisc);

  if ( pTSPars )
    pMisc = pTSPars->GetMisc();

  const PFBaseApplicator* pMiscAppl = dynamic_cast<PFBaseApplicator const*>( pMisc );
  const PFAbilityData*    pMiscAblt = dynamic_cast<PFAbilityData const*>(    pMisc );

  if ( searchType != GLOBAL )
  {
    if ( pMiscAblt )
    {
      NI_VERIFY( ( searchType == GLOBAL ) || ( searchType == UNIT ) || ( searchType == UNIT_AND_SUMMONS ),
        "Wrong searchType in FindApplicator for ability formula: can search only for GLOBAL, UNIT or UNIT_AND_SUMMONS if formula is not in the applicator. GLOBAL searchType will be used instead!",
        searchType = GLOBAL );
    }
    else
    {
      NI_VERIFY( pMiscAppl,
        "pMisc must be an applicator or ability! Find applicator by name can be called only from an applicators or abilities formulas!",
        return 0 );
    }
  }

  CPtr<PFBaseUnit> pMiscAbilityOwner = ( searchType == GLOBAL ) ? 0 : ( pMiscAblt ? pMiscAblt->GetOwner() : pMiscAppl->GetAbilityOwner() );

  int result = 0;

  for ( ring::Range<PFBaseApplicator::NamedRing> it( namedApplicators ); it; )
  {
    PFBaseApplicator* pApplicator = &(*it);
    ++it;
 
    const string& applName = pApplicator->GetApplicatorName();
    if ( pApplicator->IsEnabled() && !applName.compare( name ) )
    {
      switch( searchType )
      {
      case UNIT:
        if ( pApplicator->GetAbilityOwner() == pMiscAbilityOwner )
        {
          result++;
        }
        break;
      case ABILITY:
        if ( pApplicator->GetAbility() == pMiscAppl->GetAbility() )
        {
          result++;
        }
        break;
      case DISPATCH:
        if ( pApplicator->GetDispatch() == pMiscAppl->GetDispatch() )
        {
          result++;
        }
        break;
      case UNIT_AND_SUMMONS:
        if ( ( pApplicator->GetAbilityOwner() == pMiscAbilityOwner ) || ( pApplicator->GetAbilityOwner()->GetMasterUnit() == pMiscAbilityOwner ) )
        {
          result++;
        }
        break;
      case GLOBAL:
        result++;
        break;
      }
    }
  }
 
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IMiscFormulaPars const* PFBaseUnit::GetAblt(AbilityID abilityId) const
{
  if (BASE_ATTACK == abilityId)
    return pAttackAbility.GetPtr();
  if (ABILITY0 <= abilityId && abilityId <= ABILITY4)
    return GetAbility(abilityId);

  return PFLogicObject::GetAblt(abilityId);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetDamageTaken( float dt ) const
{
  DamageCalculator damageCalculator;
  ForAllAppliedApplicatorsInHistoryLess( damageCalculator, dt );
  return damageCalculator.amount;
}

float PFBaseUnit::GetDamageDealt( float dt ) const
{
  DamageCalculator damageCalculator;
  ForAllSentApplicatorsInHistoryLess( damageCalculator, dt );
  return damageCalculator.amount;
}

float PFBaseUnit::GetDamageTakenEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc) const
{
  const PFBaseApplicator* pMiscApplicator;
  const PFAbilityData* pMiscApplicatorAbility = NULL;

  if (mask & DMG_APPLICATOR_ABILITY)
  {
    pMiscApplicator = dynamic_cast<const PFBaseApplicator*>(pMisc);
    NI_ASSERT(!!pMiscApplicator, "DMG_APPLICATOR_ABILITY requires pMisc being a valid applicator");
    if (pMiscApplicator)
      pMiscApplicatorAbility = pMiscApplicator->GetAbilityData();
  }

  DamageCalculatorEx damageCalculator(pMiscApplicatorAbility, mask);
  ForAllSentApplicatorsInHistoryLess(damageCalculator, dt);
  return damageCalculator.amount;
}

float PFBaseUnit::GetDamageDealtEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc) const
{
  const PFBaseApplicator* pMiscApplicator;
  const PFAbilityData* pMiscApplicatorAbility = NULL;

  if (mask & DMG_APPLICATOR_ABILITY)
  {
    pMiscApplicator = dynamic_cast<const PFBaseApplicator*>(pMisc);
    NI_ASSERT(!!pMiscApplicator, "DMG_APPLICATOR_ABILITY requires pMisc being a valid applicator");
    if (pMiscApplicator)
      pMiscApplicatorAbility = pMiscApplicator->GetAbilityData();
  }

  DamageCalculatorEx damageCalculator(pMiscApplicatorAbility, mask);
  ForAllSentApplicatorsInHistoryLess(damageCalculator, dt);
  return damageCalculator.amount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::CountStatusesForDispel( const IUnitFormulaPars* pDispeller ) const
{
  const PFLogicObject* pObject = dynamic_cast<const PFLogicObject*>(pDispeller);
  NI_VERIFY( pObject, "Dispeller should exists!", return 0 );

  vector<PFBaseApplicator*> statuses;
  int count = PFApplDispell::SearchStatus2Dispell( vector<const PFBaseUnit*>( 1, this ), pObject->GetOppositeFactionFlags(), Target((PFBaseUnit*)this ), statuses);

  return count;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld
