#include "stdafx.h"
#include "PFApplInstant.h"
#include "PFBaseUnit.h"
#include "PFWorld.h"
#include "PFLogicDebug.h"
#include "PFHero.h"
#include "PFMainBuilding.h"
#include "PFApplMod.h"
#include "PFApplUtils.h"
#include "PFDispatchFactory.h"

#include "AnnouncementParams.h"

#include "PFAbilityData.h"
#include "PFAbilityInstance.h"

#include "PFGlyph.h"

#include "PrecompiledTooltips.h"

#include "SessionEventType.h"

#include "AdventureScreen.h"

#include "PFUIEvent.h"
#ifndef VISUAL_CUTTED
#include "UnitNameMap.h"
#include "AdventureScreenEvents.h"
#endif

#include "PFHeroStatistics.h"
#include "PFBaseAttackData.h"

#include "DBTalent.h"

namespace
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct ApplicatorNameMap : public NNameMap::Map
  {
    NAMEMAP_DECLARE;
  public:
    ApplicatorNameMap( NWorld::PFAbilityData const *pAbility, NWorld::PFBaseUnit  const *pUnit ) :
        ability( pAbility ), unit( pUnit ), owner( pAbility->GetOwner().GetPtr() ) {}
  protected:
    NWorld::PFAbilityData const *ability;
    NWorld::PFBaseUnit    const *unit;
    NWorld::PFBaseUnit    const *owner;

  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct UIMessageApplicatorNameMap : public ApplicatorNameMap
  {
    NAMEMAP_DECLARE;
  public:
    UIMessageApplicatorNameMap( NWorld::PFAbilityData const *pAbility, NWorld::PFBaseUnit  const *pUnit, float fValue ) :
        ApplicatorNameMap( pAbility, pUnit ), value( fValue ) {}

  protected:
    float value;
  };

  NAMEMAP_BEGIN(ApplicatorNameMap)
    NAMEMAP_CUSTOM_SUBMAP(ability, const_cast<NWorld::PFAbilityData*>(ability), ability);
  NAMEMAP_CUSTOM_SUBMAP(unit, const_cast<NWorld::PFBaseUnit*>(unit), unit);
  NAMEMAP_CUSTOM_SUBMAP(owner, const_cast<NWorld::PFBaseUnit*>(owner), owner);
  NAMEMAP_END

    NAMEMAP_BEGIN(UIMessageApplicatorNameMap)
    NAMEMAP_PARENT(ApplicatorNameMap)
    NAMEMAP_VAR_RO(value);
  NAMEMAP_END
}


namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
struct UIEventDamageDescription : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  explicit UIEventDamageDescription(float _value, bool _isCritical) : value(_value), isCritical(_isCritical) {};
protected:
  float value;
  bool  isCritical;
};
NAMEMAP_BEGIN(UIEventDamageDescription)
  NAMEMAP_VAR_RO(value)
  NAMEMAP_VAR_RO(isCritical)
NAMEMAP_END

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplDamage::PFApplDamage(PFApplCreatePars const &cp)
  : Base(cp)
  , damageDealed(0.f)
  , damage(0.0f)
  , isCritical(false)
  , ignoreDefences(false)
  , delegatedDamage(0.0f)
  , delegateDamageDesc(NULL)
  { }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplDamage::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  bool delegated = IsDelegated();

  if( IsTargetValid(pReceiver) )
  {
    if ( !delegated )
    {
  	  damage = RetrieveParam(GetDB().damage);

      // Apply critical
      if ((GetDB().damageMode & NDb::DAMAGEMODE_COULDBECRITICAL) != 0)
      {
        CPtr<PFBaseUnit> const &pOwner = GetAbilityOwner();
        float probability = pOwner->GetCritChance();
        isCritical = pOwner->GetWorld()->GetRndGen()->Roll(probability);
        if (isCritical)
        {
          damage *= pOwner->GetCritMult();
        }
      }
    }

    if (GetDB().damageType == NDb::APPLICATORDAMAGETYPE_MANA )
    {
      NI_VERIFY( !delegated, "No mana damage allowed for damage delegating", return true );
      damageDealed = pReceiver->OnBurnEnergy(GetAbilityOwner(), damage);
    }
    else
    {
      const bool dontAttackBack = !!(GetDB().damageMode & NDb::DAMAGEMODE_DONTATTACKBACK);

      damageDealed = damage; // used in damageReduction formulas
      if ( !delegated )
      {
        PFBaseUnit::DamageDesc desc;

        desc.pSender = GetAbilityOwner();
        desc.amount = damage;
        desc.damageType = GetDB().damageType == NDb::APPLICATORDAMAGETYPE_NATIVE ? GetAbilityOwner()->GetNativeDamageType() : GetDB().damageType;
        desc.flags = flags;
        desc.damageMode = GetDB().damageMode;
        desc.dontAttackBack = dontAttackBack;
        desc.pDealerApplicator = this;
        desc.isDelegatedCriticalDamage = isCritical;

        PFOutgoingDamageEvent evt( pReceiver, desc, damage );
        pOwner->EventHappened( evt );
        desc.amount = evt.damage;

        damageDealed = pReceiver->OnBeforeDamage(desc);
        damageDealed = pReceiver->OnDamage(desc);
        delegatedDamage = desc.delegatedDamage; // note that we need to get delegatedDaamge only in this case
      }
      else
      {
        damageDealed = pReceiver->OnDamage(*delegateDamageDesc);
        isCritical = delegateDamageDesc->isDelegatedCriticalDamage;
        delegateDamageDesc = 0;
      }

      if (IsValid(pOwner) && !dontAttackBack)
      {
        const bool byAutoAttack = (GetAbilityData() ? GetAbilityData()->IsAutoAttack() : false);

        pOwner->SetLastAttackData(pReceiver, byAutoAttack, pReceiver->GetFaction());
      }

      // Log damage for statistics (will log only damage related to local player's hero)
      LogDamage(pOwner, pReceiver);
    }

    if ( GetDB().cancelInvisibility && !delegated )
    {
      PFBaseUnitEvent cancelInvisEvent( NDb::BASEUNITEVENT_CANCELINVISIBILITY );
      pOwner->EventHappened( cancelInvisEvent );
    }

#ifndef VISUAL_CUTTED
    if (damageDealed < 0.0f || ( damageDealed == 0.0f && GetDB().damageType == NDb::APPLICATORDAMAGETYPE_MANA ) )
      return true;

    if (GetDB().uiEvent && damageDealed)
    {
      // init UI Event
      pUIEvent = new NGameX::PFUITwoUnitsEvent( GetDB().uiEvent, pReceiver );

      if (pUIEvent) 
      {
        UIEventDamageDescription eventData(damageDealed, isCritical);

        pUIEvent->SetSender(GetAbilityOwner());
        pUIEvent->SetReciever(pReceiver);
        NGameX::AdventureScreen::Instance()->OnUIEvent(  pUIEvent.GetPtr(), &eventData );
      }
    }
#endif
  }
  
  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplDamage::SetDelegated( PFBaseUnit::DamageDesc const* desc )
{
  NI_VERIFY( desc, "Trying to SetDelegated with 0 desc", return );
  NI_VERIFY( GetTarget().IsUnit(), "Trying to SetDelegated while target is not a unit", return );
  flags |= FLAG_DELEGATED;
  pReceiver = GetTarget().GetUnit();
  delegateDamageDesc = desc;
  damage = desc->amount;
  ignoreDefences = desc->ignoreDefences;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Log damage for statistics
void PFApplDamage::LogDamage(PFBaseUnit const * pOwner, PFBaseUnit const * pReceiver) const
{
  NWorld::PFBaseHero const * heroOwner = dynamic_cast<NWorld::PFBaseHero const *>(pOwner);
  NWorld::PFBaseHero const * heroReceiver = dynamic_cast<NWorld::PFBaseHero const *>(pReceiver);

  float material = 0.0f;
  float magic = 0.0f;
  float pure = 0.0f;

  NDb::EApplicatorDamageType damageType = GetDB().damageType;

  if (damageType == NDb::APPLICATORDAMAGETYPE_MATERIAL
    || damageType == NDb::APPLICATORDAMAGETYPE_NATIVE && pOwner->GetNativeDamageType() == NDb::APPLICATORDAMAGETYPE_MATERIAL)
  {
    material = damageDealed;
  }
  else if (damageType == NDb::APPLICATORDAMAGETYPE_ENERGY
    || damageType == NDb::APPLICATORDAMAGETYPE_NATIVE && pOwner->GetNativeDamageType() == NDb::APPLICATORDAMAGETYPE_ENERGY)
  {
    magic = damageDealed;
  }
  else if (damageType == NDb::APPLICATORDAMAGETYPE_PURE
    || damageType == NDb::APPLICATORDAMAGETYPE_NATIVE && pOwner->GetNativeDamageType() == NDb::APPLICATORDAMAGETYPE_PURE)
  {
    pure = damageDealed;
  }

  const HeroDamage hdamage( material, magic, pure );

  PFHeroStatistics* pOwnerHeroSt = 0;

  if ( heroOwner && heroOwner->IsTrueHero() )
  {
    pOwnerHeroSt = heroOwner->GetHeroStatistics();
    if (const PFWorld * pWorld = heroOwner->GetWorld())
    {
      pOwnerHeroSt->SetLastDealtDamageStep( pWorld->GetStepNumber() );
    }
  }
  else if ( IsValid( pOwner->GetMasterUnit() ) )
  {
    if ( PFBaseHero const * pMaster = dynamic_cast<NWorld::PFBaseHero const *>(pOwner->GetMasterUnit().GetPtr()) )
      pOwnerHeroSt = pMaster->GetHeroStatistics();
  }

  if ( pOwnerHeroSt )
  {
    pOwnerHeroSt->AddDamageDealed( hdamage );
    if ( heroReceiver && heroReceiver->IsTrueHero())
    {
      if (heroOwner && heroOwner->IsTrueHero())
      {
        if (heroOwner->GetPlayerId() != heroReceiver->GetPlayerId())
        {
          pOwnerHeroSt->AddDamageDealedToHeroes( hdamage );
          heroReceiver->GetHeroStatistics()->AddDamageReceivedFromHeroes( hdamage );
        }
      }
      else
      {
        pOwnerHeroSt->AddDamageDealedToHeroes( hdamage );
        heroReceiver->GetHeroStatistics()->AddDamageReceivedFromHeroes( hdamage );
      }
    }
  }

  if ( heroReceiver && heroReceiver->IsTrueHero() )
  {
    heroReceiver->GetHeroStatistics()->AddDamageReceived( hdamage );
  }

  // Local hero statistics
  if (heroOwner && heroOwner->IsLocal() 
    || heroReceiver && heroReceiver->IsLocal())
  {
    NGameX::AdventureScreen * adventureScreen = NGameX::AdventureScreen::Instance();

    if (IsValid(adventureScreen) && hdamage)
    {
      NWorld::PFHeroLocalStatistics * hls = adventureScreen->GetHeroLocalStatistics();

      if (IsValid(hls))
      {
        unsigned int opponentId = 0;
        int          opponentType = 0;
        unsigned int abilityId = 0;

        //const NDb::Ability* pDBAbility = GetAbilityData()->GetDBDesc();
        const NDb::Ability* pDBAbility = GetAbility()->GetData()->GetDBDesc();
        if( const NDb::Talent*  talent = dynamic_cast<const NDb::Talent*>( pDBAbility ) )
          abilityId = Crc32Checksum().AddString( talent->persistentId.c_str() ).Get();
        else
          abilityId = Crc32Checksum().AddString( pDBAbility->GetDBID().GetFormatted().c_str() ).Get();

        bool         dealt = false;

        if (heroOwner && heroOwner->IsLocal())
        {
          if (heroReceiver && heroReceiver->GetDbHero())
            opponentId = Crc32Checksum().AddString( heroReceiver->GetDbHero()->persistentId.c_str() ).Get();
          else
            opponentId = pReceiver->DbUnitDesc()->GetDBID().GetHashKey();
          opponentType = pReceiver->GetUnitType();
          dealt = true;
        }
        else
        {
          if (heroOwner && heroOwner->GetDbHero())
            opponentId = Crc32Checksum().AddString( heroOwner->GetDbHero()->persistentId.c_str() ).Get();
          else
            opponentId = pOwner->DbUnitDesc()->GetDBID().GetHashKey();
          opponentType = pOwner->GetUnitType();
          dealt = false;
        }

        hls->AddDamage(HeroOpponent(opponentId, opponentType), abilityId, hdamage, dealt);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplDamage::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "damageDealed") == 0 )
    return damageDealed + delegatedDamage; // supposed to be used only and exclusively in formulas! via VariableProxy for example
  if ( strcmp(sVariableName, "isCritical") == 0 )
    return isCritical ? 1.0f : 0.0f;
  if ( strcmp(sVariableName, "isAutoAttack") == 0 )
    return GetAbility() && GetAbility()->GetData()->IsAutoAttack() ? 1.0f : 0.0f; 
  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplDamage::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFBaseApplicator::DumpInfo(logger);
  LogLogicInfo(logger)("      dmg: %3.1f, dealed: %3.1f, type: %s\n", damage, damageDealed, NDb::EnumToString(GetDB().damageType));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplHeal::PFApplHeal(PFApplCreatePars const &cp) 
  : Base(cp), amountRestored(0), amount(0)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplHeal::Start()
{
  if (PFBaseApplicator::Start())
    return true;

	amount = RetrieveParam(GetDB().amount);

  if( IsUnitValid(pReceiver) )
  {
    if (GetDB().healTarget == NDb::HEALTARGET_HEALTH)
      amountRestored = pReceiver->OnHeal(GetAbilityOwner(), amount, GetDB().ignoreHealingMods );
    else
      amountRestored = pReceiver->OnHealEnergy(GetAbilityOwner(), amount);

#ifndef VISUAL_CUTTED
    if ( amountRestored <= 0.f )
      return true;

    if (GetDB().uiEvent)
    {
      pUIEvent = new NGameX::PFUIEvent( GetDB().uiEvent, pReceiver );

      if (pUIEvent) 
      {
        NGameX::SingleValueNameMapFloat eventData(amountRestored);

        NGameX::AdventureScreen::Instance()->OnUIEvent( pUIEvent, &eventData );
      }
    }
#endif
  }
  
  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplHeal::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "amountRestored") == 0 )
    return amountRestored;
  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplKill::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  int flags = PFBaseUnit::UNITDIEFLAGS_NONE;

  if (GetDB().dontGiveRewards)
    flags |= PFBaseUnit::UNITDIEFLAGS_FORBIDREWARDS;

  CPtr<PFBaseUnit> killer;

  switch ( GetDB().flag )
  {
    case NDb::KILLMODE_UNSUMMON:
      flags |= PFBaseUnit::UNITDIEFLAGS_UNSUMMON;
      break;
    case NDb::KILLMODE_DONTSHOWDEATH:
      flags |= PFBaseUnit::UNITDIEFLAGS_DONTPLAYDEATHANIMATION;
      killer = GetAbilityOwner();
      break;
    case NDb::KILLMODE_INSTANTREMOVE:
      flags |= PFBaseUnit::UNITDIEFLAGS_FORCEREMOVECORPSE;
      killer = GetAbilityOwner();
      break;
    default:
      killer = GetAbilityOwner();
      break;
  }
  
  PFBaseUnitDamageDesc tempDD;
  tempDD.pDealerApplicator = this;
  tempDD.pSender = pOwner;

  pReceiver->KillUnit(killer, flags, &tempDD);

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplRefreshCooldown::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  if (pReceiver->IsHero())
  {
    PFBaseHero *pHero = static_cast<PFBaseHero*>(pReceiver.GetPtr());

    float reductionAmount = RetrieveParam( GetDB().reductionAmount );

    if ( reductionAmount < 0.0f && !GetDB().allowCdIncrease ) // this case means "drop cd to 0"
      reductionAmount = 0.0f;
    else if ( reductionAmount == 0.0f && GetDB().allowCdIncrease ) // this case means "do nothing"
      return true;

    if ( GetDB().talents.empty() && GetDB().flags == 0 && GetDB().refreshThis )
    {
      GetAbility()->GetData()->DropCooldown(true, reductionAmount, GetDB().reduceByPercent );
    }
    else
    {
      const DropCooldownParams dropCdParams( GetDB().flags, GetDB().talents, GetDB().useListAs, GetDB().refreshThis ? NULL : GetAbility()->GetData(), reductionAmount, GetDB().reduceByPercent );
      pHero->DropCooldowns( dropCdParams );
    }
  }

  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpell::Start()
{
	if (PFBaseApplicator::Start())
		return true;

	numSpellsSent = SendSpell2Targets(this, GetDB().spell, GetDB().targetSelector);
	if (IsValid(pParent))
	{
		pParent->OnNotification(*this, numSpellsSent > 0 ? NDb::PARENTNOTIFICATION_DONE : NDb::PARENTNOTIFICATION_CANCEL);
	}

	return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplSpell::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "spellsSent") == 0 )
    return (float)numSpellsSent;
  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAbilityEnd::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  GetAbility()->NotifyAbilityEnd();

  if ( GetDB().cancelApplicators )
  {
    GetAbility()->GetData()->CancelAbility();
  }

  if (IsValid(pParent))
  {
    pParent->OnNotification( *this, NDb::PARENTNOTIFICATION_DONE );
  }

  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplDispell::Start()
{
	if (PFBaseApplicator::Start())
		return true;

  vector<const PFBaseUnit*> targetsToDispell;

  if ( GetDB().targets )
  {
    targetsToDispell.reserve( 16 );
    CObj<PFTargetSelector> pTargetSelector = GetDB().targets->Create( GetWorld() );
    PFTargetSelector::TargetsCollector<const PFBaseUnit> targetsCollector(targetsToDispell);
    PFTargetSelector::RequestParams rp( *this, GetTarget() );
    pTargetSelector->EnumerateTargets( targetsCollector, rp );
  }
  else
  {
    NI_VERIFY( pReceiver, "Applying Dispell without target selector to land", return true );
    targetsToDispell.push_back( pReceiver );
  }

  if ( targetsToDispell.empty() )
    return true;

	int effects2Dispell = RetrieveParam( GetDB().maxEffectsToDispell, 1 );
	NI_VERIFY(effects2Dispell > 0, ErrorStr("maxEffectsToDispell should be > 0"), return true; );

	int factionFlags = GetAbilityOwner()->GetOppositeFactionFlags();
	int potentialEffectApplicatorsCount;
	do 
	{
		potentialEffectApplicatorsCount = DispellOneEffect( factionFlags, targetsToDispell );
	} while (--effects2Dispell > 0 && potentialEffectApplicatorsCount > 0);

	return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFApplDispell::SearchStatus2Dispell(const vector<const PFBaseUnit*> &targetsToDispell, const int dispellFactionFlags, const Target& requester, vector<PFBaseApplicator*> &statuses)
{
  struct SearchForStatusesToDispell : public NonCopyable
	{
    const int              factionFlags;
    const CVec2            requestPos;

		int                    potentialStatuses2Remove;
    map<pair<const PFBaseUnit*, NDb::DBID>, vector<PFBaseApplicator*>> statusesMap;
    NDb::DBID              bestApplDBID;
		NDb::EDispellPriority  maxPriority;
    float                  maxRemainingDurationPercent;
    float                  bestUnitDistToRequester2;
    const PFBaseUnit*      currentUnit;
    const PFBaseUnit*      bestUnit;

		SearchForStatusesToDispell( int factionFlags_, const Target& requester )
			: factionFlags(factionFlags_)
      , requestPos( requester.AcquirePosition().AsVec2D() )
			, potentialStatuses2Remove(0)
      , maxPriority(NDb::DISPELLPRIORITY_NONDISPELLABLE)
      , maxRemainingDurationPercent(0)
      , bestUnitDistToRequester2(1e10)
      , currentUnit(0)
      , bestUnit(0)
		{}

		void operator()(const CObj<PFBaseApplicator> &pAppl)
		{
			// Check that it is status
			if ( pAppl->GetTypeId() != PFApplStatus::typeId )
				return;

      NI_VERIFY( pAppl->GetAbilityOwner(), NStr::StrFmt( "Applicator %s without owner!", pAppl->GetDBBase()->GetDBID().GetFormatted().c_str() ), return );

			// Faction check
			if ( (factionFlags & (1 << pAppl->GetAbilityOwner()->GetFaction())) == 0 )
				return;

			// Cast to status
			PFApplStatus *pStatus = static_cast<PFApplStatus*>(pAppl.GetPtr());

			NDb::EDispellPriority dispellPriority = pStatus->GetDB().dispellPriority;

			// Priority check
			if (dispellPriority == NDb::DISPELLPRIORITY_NONDISPELLABLE)
				return;

      NDb::DBID applDBID = pStatus->GetDBBase()->GetDBID();

      vector<PFBaseApplicator*>& vecStatus = statusesMap[ make_pair( currentUnit, applDBID ) ];

      if ( vecStatus.empty() )
			  potentialStatuses2Remove++;

      vecStatus.push_back( pStatus );

      if ( dispellPriority < maxPriority )
        return;

      const float otherRemainingDurationPercent = pStatus->GetDuration() / pStatus->GetLifetime();

			if ( dispellPriority > maxPriority )
			{
				maxPriority = dispellPriority;
				bestApplDBID = applDBID;
        bestUnit = currentUnit;
        maxRemainingDurationPercent = otherRemainingDurationPercent;
			}
      else if ( dispellPriority == maxPriority )
      {
        if ( otherRemainingDurationPercent > maxRemainingDurationPercent )
        {
          bestApplDBID = applDBID;
          bestUnit = currentUnit;
          maxRemainingDurationPercent = otherRemainingDurationPercent;
        }
        else if ( otherRemainingDurationPercent == maxRemainingDurationPercent ) // fabs < EPS_VALUE ???
        {
          const float dist = fabs2( requestPos - currentUnit->GetPosition().AsVec2D() );
          if ( dist < bestUnitDistToRequester2 )
          {
            bestApplDBID = applDBID;
            bestUnit = currentUnit;
            bestUnitDistToRequester2 = dist;
          }
        }
      }
		}

    vector<PFBaseApplicator*>& GetStatuses()
    {
      return statusesMap[ make_pair( bestUnit, bestApplDBID ) ];
    }
	} f( dispellFactionFlags, requester );

  for( int i = 0, cnt = targetsToDispell.size(); i < cnt; ++i )
  {
    const PFBaseUnit* const& pUnit = targetsToDispell[i];
    f.currentUnit = pUnit;
	  pUnit->ForAllAppliedApplicators(f);
  }

  statuses = f.GetStatuses();

	return f.potentialStatuses2Remove;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFApplDispell::DispellOneEffect( const int dispellFactionFlags, const vector<const PFBaseUnit*> &targetsToDispell )
{
	vector<PFBaseApplicator*> appls2Remove;
	int potentialStatuses2Remove = SearchStatus2Dispell( targetsToDispell, dispellFactionFlags, GetTarget(), appls2Remove );
	if (potentialStatuses2Remove == 0)
		return 0;

	// Remove applicators
  for ( int i = 0, cnt = appls2Remove.size(); i < cnt; i++ )
  {
    if ( appls2Remove[i]->IsAlive() ) // Handle cases with status inside status and both are present in appls2Remove
    {
	    appls2Remove[i]->Stop();
	    MemorizeApplicator(appls2Remove[i]);
    }
  }

  ++effectsDispelled;

	return potentialStatuses2Remove - 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplDispell::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "effectsDispelled" ) == 0 )
	{
		return (float)effectsDispelled;
	}

  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFUIMessageApplicator::PFUIMessageApplicator(PFApplCreatePars const& cp)
  : Base( cp )
{
}

bool PFUIMessageApplicator::Start()
{
  if ( Base::Start() )
  {
    return true;
  }

#ifndef VISUAL_CUTTED
 
  const NDb::UIMessageApplicator &DB = GetDB();
  if ( GetDB().uiEvent )
  {
    NGameX::PFUITwoUnitsEvent* pUIEvent = new NGameX::PFUITwoUnitsEvent( DB.uiEvent, pReceiver );

    if ( pUIEvent )
    {
      pUIEvent->SetSender(pOwner);
      pUIEvent->SetReciever(pReceiver);

      wstring text;
      wstring const& message = DB.message.GetText();
      if ( message.length() > 0 )
      {
        UIMessageApplicatorNameMap myMap( pAbility->GetData(), pReceiver.GetPtr(), RetrieveParam( DB.value ) );
        NGameX::PrecompiledTooltip tooltip;

        tooltip.Init( &myMap, message );
        tooltip.MakeText( text );
      }
      NGameX::SingleValueNameMapWstring eventData( text );

      NGameX::AnnouncementParams annParams;
      annParams.killer = pOwner;

      NGameX::AdventureScreen::Instance()->OnUIEvent( pUIEvent, &eventData, &annParams );
    }
  }
#endif

  return true;
}

PFResurrectApplicator::PFResurrectApplicator(PFApplCreatePars const& cp)
  : Base( cp )
{
}

bool PFResurrectApplicator::Start()
{
  if( Base::Start() )
    return true;
  
  CDynamicCast<PFBaseHero> pHero(pReceiver);
  if( pHero && pHero->IsDead() && !pHero->IsResurrecting())
    pHero->Resurrect( PFBaseHero::ResurrectParams(PFBaseHero::ResurrectParams::Base, 
      Clamp(GetDB().healthPercent * 1e-2f, 0.0f, 1.0f), Clamp(GetDB().energyPercent * 1e-2f, 0.0f, 1.0f) ) );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAddNaftaApplicator::PFAddNaftaApplicator(PFApplCreatePars const &cp)
  : Base(cp)
  , nafta(0.0f) 
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAddNaftaApplicator::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  nafta = RetrieveParam(GetDB().nafta);
  
	if ( nafta == 0.0f )
		return true;

  if ( IsValid(pReceiver) )
  {
    PFBaseHero* pHero = dynamic_cast<PFBaseHero*>(pReceiver.GetPtr());
    NI_VERIFY(pHero, "Receiver must be a Hero!", return true ); 
    if ( nafta > 0 )
		  pHero->OnAddGold(GetAbilityOwner(), nafta);
    else
      nafta = pHero->OnRemoveGold(GetAbilityOwner(), nafta);

    // Log adding nafta

    SessionEventType::EventType eventType;
    if (GetDB().isFromImpulseBuff)
      eventType = SessionEventType::NaftaIncomeFromImpulsiveBuff;
    else
      eventType = SessionEventType::NaftaIncomeFromTalent;

    StatisticService::RPC::SessionEventInfo eventParams;
    eventParams.intParam1 = nafta;

    pHero->LogSessionEvent(eventType, eventParams);
  }

  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAddNaftaApplicator::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFBaseApplicator::DumpInfo(logger);
  LogLogicInfo(logger)("      nafta: %3.1f\n", nafta);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAddNaftaApplicator::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "nafta") == 0 )
    return nafta;
  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplVariableProxy::PFApplVariableProxy(PFApplCreatePars const &cp) : Base( cp ), currentAppl(0), applicatorCount(0) {};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplVariableProxy::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  CPtr<PFBaseUnit> pSender = GetAbilityOwner();
  if (!IsValid(pSender) || !IsValid(pReceiver))
    return true;

  Target targ(pReceiver);

  variables.reserve( GetDB().applicators.size() );

  PFApplCreatePars cp(pAbility, targ, this);
  for ( int i = 0, applsNumber = GetDB().applicators.size(); i < applsNumber; ++i )
  {
    currentAppl = i;

    const int varNamesSize = GetDB().applicators[i].variableNames.size();

    // fill with default values
    variables.push_back( vector<float>(varNamesSize, 0.0f) );

    cp.pDBAppl = GetDB().applicators[i].applicator;

    NI_DATA_VERIFY(cp.pDBAppl, ErrorStr("Empty applicator found in list"), continue;)

    CObj<PFBaseApplicator> pAppl = CreateApplicator(cp);

    if ( pAppl && ActivateApplicator(pAppl, pAbility) )
        applicatorCount++;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplVariableProxy::OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note)
{
	if ( note != NDb::PARENTNOTIFICATION_STOP )
		return;

	for ( int i = 0, applsNumber = GetDB().applicators.size(); i < applsNumber; ++i )
	{
    const NDb::ApplicatorToProxy& proxiedAppl = GetDB().applicators[i];

    if ( proxiedAppl.applicator )
    {
      if ( proxiedAppl.applicator->GetDBID() == appl.GetDBBase()->GetDBID() )
		  {
        for ( int v = 0, varsNumber = proxiedAppl.variableNames.size(); v < varsNumber; ++v )
        {
          if ( !proxiedAppl.variableNames[v].empty() )
            variables[i][v] = appl.GetVariable( proxiedAppl.variableNames[v].c_str() );
        }

        applicatorCount -= 1;
			  return;
		  }
    }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplVariableProxy::Step(float dtInSeconds)
{
  if (PFBaseApplicator::Step(dtInSeconds))
    return true;
  return applicatorCount <= 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplVariableProxy::Stop()
{
	RemoveChildrenApplicators();

	PFBaseApplicator::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplVariableProxy::GetVariable(const char* sVariableName) const
{
  const char* delimPos = strchr( sVariableName, ':' );
  const int varStrLen = delimPos ? delimPos - sVariableName : strlen( sVariableName );

	for ( int i = 0, applsNumber = GetDB().applicators.size(); i < applsNumber; ++i )
	{
    const NDb::ApplicatorToProxy& proxiedAppl = GetDB().applicators[i];

    if ( proxiedAppl.applicator )
    {
      // check for applicator name
      if ( delimPos && strncmp( sVariableName, proxiedAppl.applicator->formulaName.c_str(), varStrLen ) != 0 )
        continue;

      for ( int v = 0, varsNumber = proxiedAppl.variableNames.size(); v < varsNumber; ++v )
      {
        if ( !proxiedAppl.variableNames[v].empty() && strncmp(delimPos ? (delimPos + 1) : sVariableName, proxiedAppl.variableNames[v].c_str(), varStrLen ) == 0 )
          return variables[i][v];
      }
    }
	}

  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplCreateGlyph::PFApplCreateGlyph(PFApplCreatePars const &cp)
 : Base(cp) 
 , originalParentDir(0.0f, 0.0f)
{
  if (NWorld::PFBaseMovingUnit * pBaseMovingUnit = dynamic_cast<NWorld::PFBaseMovingUnit *>(cp.target.GetUnit().GetPtr()))
  {
    originalParentDir = pBaseMovingUnit->GetMoveDirection();
  }
}

bool PFApplCreateGlyph::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  Target const &targ = GetTarget();

  CVec3 position = targ.IsPosition() ? targ.GetPosition() : targ.GetObject()->GetPosition();

  const NDb::CreateGlyphApplicator * pCreateGlyphApplicator = &GetDBAppl<NDb::CreateGlyphApplicator>();

  if( pCreateGlyphApplicator->angle < 0.f && pCreateGlyphApplicator->distance < 0.f && pCreateGlyphApplicator->radius < 0.f )
  {
    position.x = pCreateGlyphApplicator->absolutePosition.x;
    position.y = pCreateGlyphApplicator->absolutePosition.y;
  }
  else
  {
    // Try to get PFBaseMovingUnit and if successful - process glyph positioning relative to the unit
    if (NWorld::PFBaseMovingUnit * pBaseMovingUnit = dynamic_cast<NWorld::PFBaseMovingUnit *>(pOwner.GetPtr()))
    {
      // Get the desired appearance direction angle
      float angle = ToRadian(pCreateGlyphApplicator->angle);

      // Do additional calculations, if the appearance direction angle must be relative to the unit's direction
      if (pCreateGlyphApplicator->angleIsRelative)
      {
        // Calculate rotation angle of the unit's direction
        float originalAngle = acos(originalParentDir.x);
        if (originalParentDir.y < 0) originalAngle = FP_2PI - originalAngle;

        // Calculate required angle for glyph to appear
        angle += originalAngle; 
      }

      // Calculate the position relative to the unit by angle (if angleIsRelative) and distance
      CVec2 newPos = (CVec2(cos(angle), sin(angle)) * pCreateGlyphApplicator->distance) + CVec2(position.x, position.y);

      CVec2 foundPos;

      // Now try to find a free and walkable place around the desired position. 
      // If successful - found position will be used. The unit's position will be used otherwise.
      if (pBaseMovingUnit->FindFreePlaceForDrop(newPos, pCreateGlyphApplicator->radius, foundPos, 2.0f, true, false))
      {
        position.x = foundPos.x;
        position.y = foundPos.y;
      }
    }
  }

  CPtr<PFGlyph> pGlyph = new PFGlyph( pOwner->GetWorld(), GetDB().glyph, position );
  pGlyph->SetScriptName( GetDB().scriptName );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplVictory::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  NDb::EFaction losingFaction = GetDB().oppositeFaction ? pOwner->GetFaction() : pOwner->GetOppositeFaction();

  if ( GetDB().destroyMainBuilding )
  {
    struct MBFinder
    {
      MBFinder::MBFinder( NDb::EFaction faction_ ) : faction(faction_), mainBuilding(0) {}
      void operator()( PFLogicObject &object )
      {
        if ( object.GetUnitType() == NDb::UNITTYPE_MAINBUILDING && object.GetFaction() == faction )
        {
          mainBuilding = &object;
        }
      }
      NDb::EFaction faction;
      PFLogicObject* mainBuilding;
    } finder( losingFaction );
    pOwner->GetWorld()->GetAIWorld()->ForAllUnits( finder );

    if ( CDynamicCast<PFMainBuilding> mainBuilding = finder.mainBuilding )
    {
      mainBuilding->OnUnitDie( pOwner.GetPtr(), PFBaseUnit::UNITDIEFLAGS_NONE );
    }
  }
  else
  {
    pOwner->GetWorld()->OnGameFinished( losingFaction );
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplChangeState::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  ILogicStatesMapObject* pLSMapObject = dynamic_cast<ILogicStatesMapObject*>(pReceiver.GetPtr());
  NI_VERIFY( pLSMapObject, "Invalid target for PFApplChangeState", return true );

  string const& newStateName = GetDB().newStateName;

  NI_DATA_VERIFY( !newStateName.empty(), "PFApplChangeState: empty newStateName specified", return true );

  pLSMapObject->SetState( newStateName );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplGiveConsumable::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  PFBaseHero* pHero = dynamic_cast<PFBaseHero*>(pReceiver.GetPtr());

  NI_VERIFY( pHero, "PFApplGiveConsumable should be applied on a hero", return true );

  pHero->TakeConsumable( GetDB().consumable, RetrieveParam( GetDB().amount, 1 ), NDb::CONSUMABLEORIGIN_APPLICATOR );

  return true;
}

}; // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFApplDamage,                NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplHeal,                  NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplKill ,                 NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplRefreshCooldown,       NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSpell,                 NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAbilityEnd,            NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplDispell,               NWorld);
REGISTER_WORLD_OBJECT_NM(PFUIMessageApplicator,       NWorld);
REGISTER_WORLD_OBJECT_NM(PFResurrectApplicator,       NWorld);
REGISTER_WORLD_OBJECT_NM(PFAddNaftaApplicator,        NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplVariableProxy,         NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplCreateGlyph,           NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplVictory,               NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplChangeState,           NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplGiveConsumable,        NWorld);
