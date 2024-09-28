#include "stdafx.h"

#include "PFTriggerApplicator.h"
#include "PFBaseUnit.h"
#include "PFWorld.h"
#include "PFHero.h"
#include "PFDispatchFactory.h"
#include "PFTargetSelector.h"
#include "PFAIWorld.h"
#include "PFAbilityData.h"
#include "PFAbilityInstance.h"
#include "PFApplUtils.h"

#include "PFApplHelper.h"
#include "PFApplUtils.h"
#include "TargetSelectorFormulaPars.h"

#include "DBConsumable.h"

namespace NWorld
{
  const char* PFEventProcessorPickupGlyph::glyphNumberVariableName = "glyphNumber";
  const char* PFEventProcessorDamageTransformer::damageConvertedVariableName = "damageConverted";
  const char *PFEventProcessorDamageTransformer::rawDamageVariableName = "rawDamage";
  const char* PFEventProcessorAbilityManacostTransformer::manaCostVariableName = "manaCost";
  int PFEventProcessorPickupGlyph::glyphNumber = -1;

  namespace
  {
    bool CheckAbilityInFilter( NDb::TriggerAbilitiesFilter const& filter, const IMiscFormulaPars* pAbility, PFAbilityData const* pAbilityData, bool isAlly, const PFBaseApplicator* pOwner )
    {
      if ( filter.exceptThis && IsValid(pOwner->GetAbility()) && pAbilityData == pOwner->GetAbility()->GetData() )
        return false;

      if ( !( (filter.flags&NDb::TRIGGERABILITIESABILITIESFLAGS_FROMALLY) && isAlly ) &&
           !( (filter.flags&NDb::TRIGGERABILITIESABILITIESFLAGS_FROMENEMY) && !isAlly ) )
         return false;

      // check single target
      if ( filter.onlySingleTarget )
      {
        if( !pAbilityData->IsSingleTarget() && pAbilityData->GetAbilityTypeId() != NDb::ABILITYTYPEID_BASEATTACK )
          return false;
      }

      //check custom condition
      if ( !filter.abilityCondition( pOwner->GetAbilityOwner().GetPtr(), pOwner->GetReceiver().GetPtr(), pAbility, true ) )
        return false;

      const NDb::Ability * ability = pAbilityData->GetDBDesc();
      // check list of abilities
          if ( ability && filter.flags & NDb::TRIGGERABILITIESABILITIESFLAGS_FROMLIST )
      {
        for ( vector<NDb::Ptr<NDb::Ability>>::const_iterator iAbility = filter.abilitiesList.begin(), iEnd = filter.abilitiesList.end(); iAbility != iEnd; ++iAbility )
        {
          if ( *iAbility && (*iAbility)->GetDBID() == ability->GetDBID() )
            return true;
        }
      }
          
          if ( (filter.flags & NDb::TRIGGERABILITIESABILITIESFLAGS_ONLYCLASSTALENT) == NDb::TRIGGERABILITIESABILITIESFLAGS_ONLYCLASSTALENT )
          {
            int rarity = pAbilityData->GetTalentRarity();
            if ( rarity != -1 )
              return rarity == NDb::TALENTRARITY_CLASS;
          }
          
      // check abilityTypeId
      return ( (1<<pAbilityData->GetAbilityTypeId()) & filter.flags );
    }

  } // unnamed namespace

  struct PFApplicatorStepEvent : public PFBaseUnitEvent
  {
  public:
    PFApplicatorStepEvent(float dt) : PFBaseUnitEvent(NDb::BASEUNITEVENT_APPLICATORSTEP), dt(dt) {}
    float dt;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFTriggerApplicator::PFTriggerApplicator(PFApplCreatePars const &cp)
    : Base(cp)
    , actionsCount(0)
    , maxActionsCount(0)
    , scale(0.0f)
  {
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFTriggerApplicator::Start()
  {
    NI_VERIFY( GetDB().processor, "No processor found for TriggerApplicator!", return true; );

    eventProcessor = CObj<PFEventProcessorBase>( GetDB().processor->Create( GetWorld() ) );
    eventProcessor->Initialize(this);

    // Check max actions count
    maxActionsCount = RetrieveParam(GetDB().actionsCount, false);

    return Base::Start();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFTriggerApplicator::Enable()
  {
    Base::Enable();
    if ( eventProcessor && eventProcessor->GetAccessibleEventsMask() != (1 << NDb::BASEUNITEVENT_APPLICATORSTEP) )
      if( IsValid(pReceiver) )
        pReceiver->AddEventListener(this);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFTriggerApplicator::Disable()
  {
    Base::Disable();
    if ( eventProcessor && eventProcessor->GetAccessibleEventsMask() != (1 << NDb::BASEUNITEVENT_APPLICATORSTEP) )
      if( IsValid(pReceiver) )
        pReceiver->RemoveEventListener(this);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFTriggerApplicator::Step(float dtInSeconds)
  {
    NI_PROFILE_FUNCTION

      if ( Base::Step(dtInSeconds) )
        return true;

    if ( maxActionsCount > 0 && actionsCount >= maxActionsCount )
      return true; // stop applicator, if count

    if ( IsEnabled() )
    {
      eventProcessor->Step( dtInSeconds );

      PFApplicatorStepEvent evt(dtInSeconds);
      OnEvent(&evt);

      if ( maxActionsCount > 0 && actionsCount >= maxActionsCount )
        return true; // stop applicator, if count
    }

    return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  unsigned int PFTriggerApplicator::OnEvent(const PFBaseUnitEvent *pEvent)
  {
    if ( maxActionsCount > 0 && actionsCount >= maxActionsCount )
      return 0;

    int64 eventType = (int64)1 << pEvent->GetType();
    if ( eventProcessor && ( eventType & eventProcessor->GetAccessibleEventsMask() ) )
    {
      CPtr<PFAbilityData> pAbilityData;

      if (pAbility && pOwner)
      {
        pAbilityData = pAbility->GetData();

        if ( GetDB().useAbilityCooldown && (!pAbilityData->IsReady() || !pOwner->CanUseAbility(pAbilityData)) )
          return 0;
        if ( GetDB().useAbilityOwnerMana && !pAbilityData->IsEnoughMana() )
          return 0;
      }

      if ( eventProcessor->ProcessEvent(pEvent) )
      {
        // Trigger worked 1 more time
        ++actionsCount;

        if (pAbility && pOwner)
        {
          // restart cooldown and take mana
          if (GetDB().useAbilityCooldown)
            pAbilityData->RecalculateAndRestartCooldown();
          if (GetDB().useAbilityOwnerMana)
            pAbilityData->SpendMana();
          if ( GetDB().playAck )
            pAbilityData->PlayAck( 0 );
        }
      }
    }
    return 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float PFTriggerApplicator::GetVariable(const char* varName) const
  {
    if ( eventProcessor )
      return eventProcessor->GetVariable(varName);
    return Base::GetVariable(varName);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFAbsorbShieldApplicator::PFAbsorbShieldApplicator( const PFApplCreatePars& cp )
    : Base( cp )
    , damageToAbsorb( 0.0f )
    , shield(0.f)
    , damage(0.f)
  {
  }

  PFAbsorbShieldApplicator::PFAbsorbShieldApplicator()
    : damageToAbsorb( 0.0f )
    , shield(0.f)
    , damage(0.f)
  {

  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFAbsorbShieldApplicator::Start()
  {
    damageToAbsorb = Max(0.f, RetrieveParam( GetDB().damageToAbsorb ));

    shield = damageToAbsorb;
    damage = 0.f;

    return Base::Start();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFAbsorbShieldApplicator::Enable()
  {
    Base::Enable();
    pReceiver->AddEventListener( this );

    ModifyReceiverShield(+shield);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFAbsorbShieldApplicator::Disable()
  {
    Base::Disable();
    pReceiver->RemoveEventListener( this );

    ModifyReceiverShield(-shield);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFAbsorbShieldApplicator::Step( float dtInSeconds )
  {
    if ( Base::Step( dtInSeconds ) )
    {
      return true;
    }

    if (damage > 0.f)
    {
      if (damage < shield)
      {
        ModifyReceiverShield(-damage);

        shield = shield - damage;
      }
      else
      {
        ModifyReceiverShield(-shield);

        shield = 0.f;
      }

      damage = 0.f;
    }

    const bool isShieldOver = !(damageToAbsorb > 0.f);

    return isShieldOver;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  unsigned int PFAbsorbShieldApplicator::OnEvent( const PFBaseUnitEvent* pEvent )
  {
    if (damageToAbsorb > 0.f)
      ;
    else
      return 0;

    const PFBaseUnitDamageEvent* const pDamageEvent = dynamic_cast<const PFBaseUnitDamageEvent*>(pEvent);

    if (!pDamageEvent || pDamageEvent->pDesc->ignoreDefences)
      return 0;

    float damageToDeal = pDamageEvent->damage2Deal;

    damageToAbsorb -= damageToDeal;
    damage += damageToDeal;

    if (damageToAbsorb < 0.f)
    {
      damageToDeal = -damageToAbsorb;
      damageToAbsorb = 0.f;
    }
    else
    {
      damageToDeal = 0.f;
    }

    pDamageEvent->damage2Deal = damageToDeal;

    return 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float PFAbsorbShieldApplicator::GetVariable(const char* varName) const
  {
    if ( strcmp(varName, "damageToAbsorb") == 0 )
      return damageToAbsorb;
    return PFBaseApplicator::GetVariable(varName);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFAbsorbShieldApplicator::ModifyReceiverShield(const float delta) const
  {
    NI_VERIFY(IsValid(pReceiver), "Invariant", return);

    pReceiver->SetShield(pReceiver->GetShield() + delta);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFEventProcessorBase::Initialize(CPtr<PFTriggerApplicator> const& _pOwner)
  {
    NI_ASSERT( !pOwner, "PFEventProcessor already initialized!" );
    pOwner = _pOwner;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFEventProcessorBase::DoSpell( const CPtr<PFBaseUnit> &pEventSender) const
  {
    if ( dbData && dbData->spell )
    {
      Target target;
      if ( GetApplicationTarget() != NDb::APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET || !pEventSender )
        pOwner->MakeApplicationTarget( target, GetApplicationTarget() );
      else
        target.SetUnit( pEventSender );

      SendSpellToSingleTarget( pOwner.GetPtr(), dbData->spell, target, false );
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  NDb::EApplicatorApplyTarget PFEventProcessorBase::GetApplicationTarget() const
  {
    return dbData->applyTarget;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CPtr<PFBaseUnit> const& PFEventProcessorBase::GetReceiver() const
  {
    return pOwner->GetReceiver();
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFEventProcessorGroup::Initialize(CPtr<PFTriggerApplicator> const& pOwner_)
  {
    Base::Initialize(pOwner_);

    // Create child processors
    processors.reserve( GetDB().processors.size() );
    for( vector<NDb::Ptr<NDb::EventProcessorBase>>::const_iterator iDB = GetDB().processors.begin(), iEnd = GetDB().processors.end(); iDB != iEnd; ++iDB )
    {
      NI_DATA_VERIFY( IsValid(*iDB), NStr::StrFmt( "Proccessor in processors list of EventProcessorGroup must be valid in applicator '%s'", NDb::GetFormattedDbId(pOwner->GetDB().GetDBID()) ), continue );
      CObj<PFEventProcessorBase> pProcessor = (*iDB)->Create( GetWorld() );
      NI_DATA_VERIFY( IsValid(pProcessor), NStr::StrFmt( "Failed to create proccessor in processors list of EventProcessorGroup in applicator '%s'", NDb::GetFormattedDbId(pOwner->GetDB().GetDBID()) ), continue );
      pProcessor->Initialize(pOwner_);

      processors.push_back( pProcessor );
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int PFEventProcessorGroup::GetAccessibleEventsMask() const
  {
    int mask = 0;
    for( vector<CObj<PFEventProcessorBase>>::const_iterator iProcessor = processors.begin(), iEnd = processors.end(); iProcessor != iEnd; ++iProcessor )
      mask |= (*iProcessor)->GetAccessibleEventsMask();

    return mask;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorGroup::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    bool result = false;

    for( vector<CObj<PFEventProcessorBase>>::const_iterator iProcessor = processors.begin(), iEnd = processors.end(); iProcessor != iEnd; ++iProcessor )
    {
      int64 eventType = (int64)1 << pEvent->GetType();
      if ( eventType & (*iProcessor)->GetAccessibleEventsMask() )
        result = (*iProcessor)->ProcessEvent(pEvent) || result;
    }

    if ( result )
      DoSpell();

    return result;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorCondition::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    if ( GetDB().condition( pOwner->GetAbilityOwner(), pOwner->GetReceiver(), pOwner, false) )
    {
      if ( GetDB().onlyParent )
      {
        if ( IsValid(pOwner) && IsValid(pOwner->GetAbilityData()) && pOwner->GetAbilityData()->GetDBDesc() )
        {
          if ( pEvent && IsValid(pEvent->GetAbility()) && IsValid(pEvent->GetAbility()->GetData()) && pEvent->GetAbility()->GetData()->GetDBDesc() )
          {
            if ( pOwner->GetAbilityData()->GetDBDesc()->GetDBID() == pEvent->GetAbility()->GetData()->GetDBDesc()->GetDBID() )
            {
              DoSpell();
              return true;
            }
          }
        }
      }
      else
      {
        DoSpell();
        return true;
      }
    }

    return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorCancelDispatch::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitDispatchEvent const* pDispatchEvent = dynamic_cast<PFBaseUnitDispatchEvent const*>(pEvent);
    NI_VERIFY( pDispatchEvent, "Need PFBaseUnitDispatchEvent to process BASEUNITEVENT_DISPATCHAPPLIED! (PFBaseUnitEvent's logic error)", return false; );

    PFDispatch const* pDispatch = pDispatchEvent->GetDispatch();
    bool bIsAlly = (pDispatch->GetSender()->GetFaction()==pOwner->GetReceiver()->GetFaction());
    const CPtr<PFBaseUnit> pEventSender = pDispatchEvent->GetDispatch()->GetSender();

    PFAbilityData const* pAbilityData = pDispatch->GetAbility()->GetData();

    // Look for upgrade of a dispatch. Use it for comparison if exists.
    PFAbilityData const* pDispUpgrader = pDispatch->GetUpgraderAbilityData();

    if ( !CheckAbilityInFilter(GetDB().filter, pDispUpgrader, pDispUpgrader ? pDispUpgrader : pAbilityData, bIsAlly, pOwner ) )
      return false;

    if ( GetDB().checkSender & NDb::TRIGGEREVENTCHECKSENDER_MATCHTARGET )
    {
      Target target;
      pOwner->MakeApplicationTarget( target, GetDB().senderMatchTarget );
      if ( target.GetUnit() != pEventSender )
        return false;
    }

    pDispatchEvent->CancelDispatch();
    DoSpell( pEventSender );

    return true;
  }

  bool PFEventProcessorPickupGlyph::ProcessEvent( const PFBaseUnitEvent* pEvent )
  {
    const PFBaseUnitPickupEvent* pPickupEvent = dynamic_cast<const PFBaseUnitPickupEvent*>(pEvent);
    NI_VERIFY( pPickupEvent, "Need PFBaseUnitPickupEvent to process BASEUNITEVENT_DISPATCHAPPLIED! (PFBaseUnitEvent's logic error)", return false; );

    if ( pPickupEvent->GetGlyphNumber() >= 0 )
    {
      glyphNumber = pPickupEvent->GetGlyphNumber();

      pPickupEvent->SetNeedActivate( false );
      DoSpell();
    }
    return true;
  }

  float PFEventProcessorPickupGlyph::GetVariable( const char* varName ) const
  {
    if ( !strncmp( varName, glyphNumberVariableName, strlen(glyphNumberVariableName) ) )
      return glyphNumber;

    return PFEventProcessorBase::GetVariable(varName);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct PFEventProcessorDamageTransformer::DummyFormulaPars : public TargetSelectorFormulaPars
  {
    DummyFormulaPars( const IMiscFormulaPars* _pMisc, const IUnitFormulaPars * _pDealer )
      : TargetSelectorFormulaPars(_pMisc ), pDealer(_pDealer) {}

    virtual const IUnitFormulaPars* GetObject( char const *name ) const
    {
      if ( strcmp( name, "DamageDealer" ) == 0 )
        return pDealer;

      return TargetSelectorFormulaPars::GetObject( name );
    }

    const IUnitFormulaPars * pDealer;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorDamageTransformer::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitDamageEvent const* pDamageEvent = dynamic_cast<PFBaseUnitDamageEvent const*>(pEvent);
    NI_VERIFY( pDamageEvent, "Need PFBaseUnitDamageEvent to process BASEUNITEVENT_DAMAGE! (PFBaseUnitEvent's logic error)", return false; );

    if ( (GetDB().flags & NDb::TRIGGEREVENTFLAGS_ONCEPERSTEP) != 0 && bProcessedThisStep )
    {
      return false;
    }

    PFBaseApplicator const* pDamageAppl = pDamageEvent->pDesc->pDealerApplicator;

    if ( !IsValid( pDamageAppl ) )
      return false;

    PFBaseApplicator const* pDamageParent = pDamageAppl->GetParentAppl();
    const bool processDelegated = pDamageAppl->IsDelegated() && GetDB().treatDelegatedByDelegator;
    
    if ( processDelegated )
    {
      NI_VERIFY( IsValid(pDamageParent), "Invalid parent of delegated damage applicator", return false );
    }

    PFBaseUnit* pEventSender =          processDelegated ? pDamageParent->GetAbilityOwner() : pDamageEvent->pDesc->pSender;
    PFAbilityData const* pAbilityData = processDelegated ? pDamageParent->GetAbilityData() : pDamageAppl->GetAbilityData();

    rawDamage = pDamageEvent->pDesc->amount;

    DummyFormulaPars dummy( pOwner, pEventSender );

    if ( !PFBaseApplicator::CheckDamageTypeFilter(pDamageEvent->pDesc->flags, pDamageEvent->pDesc->damageType, GetDB().damageTypeFilter, false) )
      return false;

    if ( !CheckAbilityInFilter( GetDB().abilityFilter, pDamageAppl, pAbilityData, GetReceiver()->GetFaction()==pEventSender->GetFaction(), pOwner ) )
      return false;

    if ( GetDB().checkSender & NDb::TRIGGEREVENTCHECKSENDER_MATCHTARGET )
    {
      Target target;
      pOwner->MakeApplicationTarget( target, GetDB().senderMatchTarget );
      if ( (target.GetUnit() != pEventSender && !GetDB().matchTargetInverted)
        || (target.GetUnit() == pEventSender && GetDB().matchTargetInverted))
        return false;
    }

    if ( GetDB().checkSender & NDb::TRIGGEREVENTCHECKSENDER_OBJECTFILTER )
    {
      bool isValidSender = UnitMaskingPredicate( GetReceiver(), GetDB().objectFilter )( *pEventSender );
      if ( !isValidSender ^ GetDB().matchTargetInverted )
        return false;
    }

    if ( GetDB().flags & NDb::TRIGGEREVENTFLAGS_ONLYFIRSTFROMABILITY )
    {
      PFAbilityInstance* pAbilityInstance = pDamageAppl->GetAbility();
      vector<CPtr<PFAbilityInstance>>::iterator it = processedAbilityInstances.begin();
      for(; it != processedAbilityInstances.end(); ++it )
      {
        if ( IsValid(*it) && (*it) == pAbilityInstance )
          return false;
      }

      processedAbilityInstances.push_back( pAbilityInstance );
    }

    float mul = GetDB().mul(pOwner->GetAbilityOwner(), pOwner->GetReceiver(), &dummy, 1.0f);
    float add = GetDB().add(pOwner->GetAbilityOwner(), pOwner->GetReceiver(), &dummy, 0.0f);

    float beforeDamage = pDamageEvent->damage2Deal;
    pDamageEvent->damage2Deal = max( 0.0f, add + pDamageEvent->damage2Deal * mul );
    damageConverted = beforeDamage - pDamageEvent->damage2Deal;

    DoSpell( pEventSender );

    bProcessedThisStep = true;

    return true;
  }

  bool PFEventProcessorDamageTransformer::Step( float dtInSeconds )
  {
    if ( GetDB().flags & NDb::TRIGGEREVENTFLAGS_ONLYFIRSTFROMABILITY )
    {
      struct AbilitiesInstancesRemover
      {
        bool operator() ( CPtr<PFAbilityInstance> const& pAbility ) { return !IsValid(pAbility) || pAbility->GetActiveApplicatorsCount() == 0; }
      } remover;
      processedAbilityInstances.erase( remove_if(processedAbilityInstances.begin(), processedAbilityInstances.end(), remover), processedAbilityInstances.end() );
    }

    bProcessedThisStep = false;

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float PFEventProcessorDamageTransformer::GetVariable(const char* varName) const
  {
    if ( !strncmp( varName, damageConvertedVariableName, strlen(damageConvertedVariableName) ) )
      return damageConverted;

    if ( !strncmp( varName, rawDamageVariableName, strlen(rawDamageVariableName) ) )
      return rawDamage;

    return PFEventProcessorBase::GetVariable(varName);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorIncomingDamage::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitDamageEvent const* pDamageEvent = dynamic_cast<PFBaseUnitDamageEvent const*>(pEvent);
    NI_VERIFY( pDamageEvent, "Need PFBaseUnitDamageEvent to process BASEUNITEVENT_DAMAGE! (PFBaseUnitEvent's logic error)", return false; );

    PFBaseUnit::DamageDesc const* damageDesc = pDamageEvent->pDesc;

    delegatedDamage = 0;
    damage = damageDesc->amount;

    if ( GetDB().damageDelegate && damageDesc->delegated )
    {
      PFBaseApplicator const* pDelegateAppl = damageDesc->pDealerApplicator->GetParentAppl();
      NI_ASSERT( pDelegateAppl, "No DamageDelegateApplicator" );

      if ( pDelegateAppl && pDelegateAppl->GetDBBase()->GetDBID() == GetDB().damageDelegate->GetDBID() )
      {
        Target target;
        pOwner->MakeApplicationTarget( target, GetDB().damageDelegateOwner );
        if ( target.GetUnit() == pDelegateAppl->GetAbilityOwner() )
        {
          delegatedDamage = damage;
          damage = 0;
        }
      }
    }

    DoSpell( damageDesc->pSender );

    return true;
  }

  float PFEventProcessorIncomingDamage::GetVariable(const char* varName) const
  {
    if ( strcmp( varName, "Damage" ) == 0 )
      return damage;

    if ( strcmp( varName, "DelegatedDamage" ) == 0 )
      return delegatedDamage;

    return PFEventProcessorBase::GetVariable(varName);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorAbilityManacostTransformer::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitUseAbilityEvent const* pUseAbilityEvent = dynamic_cast<PFBaseUnitUseAbilityEvent const*>(pEvent);
    NI_VERIFY( pUseAbilityEvent, "Need PFBaseUnitUseAbilityEvent to process BASEUNITEVENTFLAGS_CASTMAGIC! (PFBaseUnitEvent's logic error)", return false; );

    PFAbilityInstance const* pAbilityInstance = pUseAbilityEvent->GetAbility();
    PFAbilityData const* pAbilityData = pAbilityInstance->GetData();
    if ( !CheckAbilityInFilter( GetDB().filter, pAbilityData, pAbilityData, true, pOwner ) )
      return false;

    // Check ability cost mode
    if ( GetDB().filter.abilityCostMode != NDb::ABILITYCOSTMODE_ANY
      && ( ( GetDB().filter.abilityCostMode == NDb::ABILITYCOSTMODE_LIFE ) ^ pAbilityData->DoesSpendLifeInsteadEnergy() ) )
      return false;

    if ( (GetDB().filter.abilityCostMode == NDb::ABILITYCOSTMODE_CUSTOM || GetDB().filter.abilityCostMode == NDb::ABILITYCOSTMODE_ANY) &&
      pAbilityData->IsActiveCustomTrigger() == false)
      return false;
    
    manaCost = pAbilityData->GetManaCost();
    baseManaCost = pAbilityData->GetBaseManaCost();

    DoSpell();
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float PFEventProcessorAbilityManacostTransformer::GetVariable(const char* varName) const
  {
    if ( strcmp( varName, manaCostVariableName ) == 0 )
      return manaCost;

    if ( strcmp( varName, "BaseManaCost" ) == 0 )
      return baseManaCost;

    return PFEventProcessorBase::GetVariable(varName);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct PFEventProcessorApplicatorApplied::DummyFormulaPars : public TargetSelectorFormulaPars
  {
    DummyFormulaPars( const IMiscFormulaPars* _pMisc, float _lifeTime )
      : TargetSelectorFormulaPars(_pMisc ), lifeTime(_lifeTime) {}

    virtual float GetVariable( const char * varName ) const
    {
      if ( strcmp( varName, "Lifetime" ) == 0 )
      {
        return lifeTime;
      }

      return 0.f;
    }

    float lifeTime;
  };

  bool PFEventProcessorApplicatorApplied::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitApplicatorAppliedEvent const* pApplicatorEvent = dynamic_cast<PFBaseUnitApplicatorAppliedEvent const*>(pEvent);
    NI_VERIFY( pApplicatorEvent, "Need PFBaseUnitApplicatorAppliedEvent to process BASEUNITEVENT_APPLICATORAPPLIED! (PFBaseUnitEvent's logic error)", return false; );
    PFBaseApplicator* pApplicator = pApplicatorEvent->GetApplicator();
    const CPtr<PFBaseUnit> &pEventSender = pApplicator->GetAbilityOwner();

    const NDb::EventProcessorApplicatorApplied& db = GetDB();

    /*bool bIsAlly = (pEventSender->GetFaction()==pOwner->GetReceiver()->GetFaction());

    if ( ( ( (GetDB().filter & NDb::TRIGGERABILITIESABILITIESFLAGS_FROMALLY) == 0 || !bIsAlly ) &&
    ( (GetDB().filter & NDb::TRIGGERABILITIESABILITIESFLAGS_FROMENEMY) == 0 || bIsAlly ) ) ||
    ( (1 << pApplicator->GetAbility()->GetData()->GetAbilityTypeId()) & GetDB().filter ) == 0 )
    return false;*/

    if ( !IsApplicatorInList( pApplicator->GetDBBase(), db.applicatorTypesList, ByTypeID ) &&
         !IsApplicatorInList( pApplicator->GetDBBase(), db.applicatorsList, ByDBID ) )
      return false;

    if ( db.checkSender & NDb::TRIGGEREVENTCHECKSENDER_MATCHTARGET )
    {
      Target target;
      pOwner->MakeApplicationTarget( target, db.senderMatchTarget );
      if ( target.GetUnit() != pEventSender )
        return false;
    }

    if ( db.mode == NDb::APPLICATORAPPLIEDMODE_CANCEL )
    {
      pApplicatorEvent->CancelApplicator();
    }
    else if ( db.mode == NDb::APPLICATORAPPLIEDMODE_SETNEWLIFETIME )
    {
      if ( PFApplBuff* pBuffApplicator = dynamic_cast<PFApplBuff*>( pApplicator ) )
      {
        DummyFormulaPars dummy( pOwner, pBuffApplicator->GetLifetime() );
        const float newLifetime = db.newLifetime( pOwner->GetAbilityOwner(), pOwner->GetReceiver(), &dummy );
        pBuffApplicator->SetLifetime( newLifetime ); // что с дочерними аппликаторами, если они вдруг используют lifetime?
        pBuffApplicator->SetDuration( pBuffApplicator->GetModifiedDuration( newLifetime ) );
      }
      else
      {
        NI_ALWAYS_ASSERT( NI_STRFMT( "Trying to set new lifetime to non-buff applicator. %s", db.GetDBID().GetFormatted().c_str() ) );
      }
    }

    DoSpell( pEventSender );

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorOnDeath::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    if ( pEvent->GetType() == NDb::BASEUNITEVENT_APPLICATORSTEP && castSpellDelay > 0.0f )
    {
      PFApplicatorStepEvent const* pStepEvent = dynamic_cast<PFApplicatorStepEvent const*>(pEvent);
      NI_VERIFY(pStepEvent, "Need PFApplicatorStepEvent to process BASEUNITEVENT_APPLICATORSTEP! (PFBaseUnitEvent's logic error)", return false; );
      castSpellDelay-=pStepEvent->dt;

      if (castSpellDelay < EPS_VALUE)
      {
        DoSpell( pTempEventSender );
        pTempEventSender = 0;
        return true;
      }
    }
    else if ( pEvent->GetType() == NDb::BASEUNITEVENT_DEATH )
    {
      PFBaseUnitEventUnitDeath const* pEvtDeath = dynamic_cast<PFBaseUnitEventUnitDeath const*>(pEvent);
      NI_VERIFY( pEvtDeath, "Need PFBaseUnitEventUnitDeath to process BASEUNITEVENT_DEATH! (PFBaseUnitEvent's logic error)", return false; );
      const CPtr<PFBaseUnit> &pEventSender = pEvtDeath->GetKiller();

      if ( GetDB().checkSender & NDb::TRIGGEREVENTCHECKSENDER_MATCHTARGET )
      {
        Target target;
        pOwner->MakeApplicationTarget( target, GetDB().senderMatchTarget );
        if ( target.GetUnit() != pEventSender )
          return false;
      }

      if ( ( GetDB().checkSender & NDb::TRIGGEREVENTCHECKSENDER_OBJECTFILTER ) && IsValid( pEventSender ) )
      {
        if ( !UnitMaskingPredicate( GetReceiver(), GetDB().objectFilter )( *pEventSender ) )
          return false;
      }

      if ( pEvtDeath->GetVictim() == pOwner->GetReceiver() )
      {
        castSpellDelay = GetDB().castSpellDelay( pOwner->GetAbilityOwner(), pOwner->GetReceiver(), pOwner, 0.0f);

        if (castSpellDelay < EPS_VALUE)
        {
          DoSpell( pEventSender );
          return true;
        }

        pTempEventSender = pEventSender;
      }
    }

    return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFEventProcessorOnTarget::PFEventProcessorOnTarget(CreateParams const& dbData, PFWorld* world)
    : Base(dbData, world)
  {
    if ( GetDB().targetSelector )
    {
      pTargetSelector = GetDB().targetSelector->Create( world );
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorOnTarget::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    float minTargets = GetDB().minTargets(pOwner->GetAbilityOwner(), pOwner->GetReceiver(), pOwner, 1.0f);
    int targetsCount = SendSpell2Targets( pOwner.GetPtr(), dbData->spell, pTargetSelector.GetPtr(), true );

    if ( targetsCount >= minTargets )
    {
      SendSpell2Targets( pOwner.GetPtr(), dbData->spell, pTargetSelector.GetPtr(), false );
      return true;
    }

    return false;
  }

  void PFEventProcessorOnTarget::Initialize( CPtr<PFTriggerApplicator> const& pOwner )
  {
    Base::Initialize( pOwner );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorUnitDieNearMe::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitEventUnitDeath const* pEvtDeath = dynamic_cast<PFBaseUnitEventUnitDeath const*>(pEvent);
    NI_VERIFY( pEvtDeath, "Need PFBaseUnitEventUnitDeath to process BASEUNITEVENT_DEATH! (PFBaseUnitEvent's logic error)", return false; );
    const CPtr<PFBaseUnit> &pEventSender = pEvtDeath->GetVictim();

    if ( !CheckKiller(pEvtDeath->GetKiller()) )
      return false;

    if (!CheckVictim(pEvtDeath->GetVictim()) )
      return false;

    if ( GetDB().checkSender & NDb::TRIGGEREVENTCHECKSENDER_MATCHTARGET )
    {
      Target target;
      pOwner->MakeApplicationTarget( target, GetDB().senderMatchTarget );
      if ( target.GetUnit() != pEventSender )
        return false;
    }

    float maxRange = GetDB().range( pOwner->GetAbilityOwner(), pOwner->GetReceiver(), pOwner, 0.0f);
    if ( maxRange > EPS_VALUE )
    {
      float range = fabs( pEvtDeath->GetVictim()->GetPosition().AsVec2D() - GetReceiver()->GetPosition().AsVec2D() );
      if ( maxRange < range )
        return false;
    }

    DoSpell( pEventSender );
    return true;
  }

  bool PFEventProcessorUnitDieNearMe::CheckKiller( CPtr<PFBaseUnit> const& pKiller ) const
  {
    if ( !IsValid( pKiller ) )
      return false;

    return ( (  GetDB().killerFlags == NDb::UNITDIEKILLERSFLAGS_KILLEDBYALL ) ||
      ( (GetDB().killerFlags & NDb::UNITDIEKILLERSFLAGS_KILLEDBYME)      && pKiller == GetReceiver()) ||
      ( (GetDB().killerFlags & NDb::UNITDIEKILLERSFLAGS_KILLEDBYMYSUMMONS) &&  pKiller->GetMasterUnit() == GetReceiver() ) ||
      ( (GetDB().killerFlags & NDb::UNITDIEKILLERSFLAGS_KILLEDBYALLIES)  && pKiller->GetFaction() == GetReceiver()->GetFaction() ) ||
      ( (GetDB().killerFlags & NDb::UNITDIEKILLERSFLAGS_KILLEDBYENEMY)   && pKiller->GetFaction() != GetReceiver()->GetFaction() ) );
  }

  bool PFEventProcessorUnitDieNearMe::CheckVictim( CPtr<PFBaseUnit> const& pVictim ) const
  {
    return ( ( ( (GetDB().targets & NDb::SPELLTARGET_ALLY) && pVictim->GetFaction() == GetReceiver()->GetFaction() ) ||
      ( ( GetDB().targets & NDb::SPELLTARGET_ENEMY) && pVictim->GetFaction() != GetReceiver()->GetFaction() ) ) 
      && ( GetDB().targets & (1 << pVictim->GetUnitType()) ) );
  }

  bool PFEventProcessorOnUseAbilityForceStrike::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitUseAbilityEvent const* pUseAbilityEvent = dynamic_cast<PFBaseUnitUseAbilityEvent const*>(pEvent);
    NI_VERIFY( pUseAbilityEvent, "Need PFBaseUnitUseAbilityEvent to process BASEUNITEVENTFLAGS_CASTMAGIC! (PFBaseUnitEvent's logic error)", return false; );

    PFAbilityInstance const* pAbilityInstance = pUseAbilityEvent->GetAbility();
    PFAbilityData const* pAbilityData = pAbilityInstance->GetData();
    if ( !CheckAbilityInFilter( GetDB().filter, pAbilityData, pAbilityData, true, pOwner ) )
      return false;

    IMiscFormulaPars const* pApplicator = pOwner->GetReceiver()->FindApplicator(GetDB().applicatorName.c_str(), pOwner, DISPATCH);
    if ( pApplicator )
    {
      PFApplSpellPeriodicallyVisual const* pControlledApplicator = dynamic_cast<PFApplSpellPeriodicallyVisual const*>(pApplicator);
      NI_ASSERT(pControlledApplicator, "Applicator name in EventProcessorOnUseAbilityForceStrike must be an SpellPeriodicallyVisualApplicator!");
      if (pControlledApplicator)
      {
        // HACK!!! ћы не можем сделать иначе, потому что внутри страйка нужен неконстантный this :(
        const_cast<PFApplSpellPeriodicallyVisual*>(pControlledApplicator)->DoStrike();
      }
    }

    DoSpell();
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFEventProcessorLastHit::ProcessEvent(const PFBaseUnitEvent *pEvent)
  {
    PFBaseUnitLastHitEvent const* pLastHitEvent = dynamic_cast<PFBaseUnitLastHitEvent const*>(pEvent);
    NI_VERIFY( pLastHitEvent, "Need PFBaseUnitLastHitEvent to process BASEUNITEVENT_LASTHIT! (PFBaseUnitEvent's logic error)", return false; );
    const CPtr<PFBaseUnit> &pEventSender = pLastHitEvent->GetAttacker();

    DoSpell( pEventSender );

    return true;
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFEventProcessorOnConsumableObtained::ProcessEvent(const PFBaseUnitEvent *pEvent)
{
  PFHeroEventConsumableObtained const* pConsObtainedEvent = dynamic_cast<PFHeroEventConsumableObtained const*>(pEvent);
  NI_VERIFY( pConsObtainedEvent, "Need PFHeroEventConsumableObtained to process BASEUNITEVENT_CONSUMABLEOBTAINED!", return false );

  NDb::EventProcessorOnConsumableObtained const& db = GetDB();

  if ( (db.origin & (1 << pConsObtainedEvent->GetOrigin())) == 0 )
    return false;

  if ( db.consumable && db.consumable->GetDBID() != pConsObtainedEvent->GetDBConsumable()->GetDBID() )
    return false;

  DoSpell();

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PFEventProcessorOutgoingDamage::DummyFormulaPars : public TargetSelectorFormulaPars
{
  DummyFormulaPars( const IMiscFormulaPars* _pMisc, float _damage, const IUnitFormulaPars * _pTaker )
    : TargetSelectorFormulaPars(_pMisc ), damage(_damage), pTaker(_pTaker) {}

  virtual float GetVariable( const char * varName ) const
  {
    if ( strcmp( varName, "Damage" ) == 0 )
    {
      return damage;
    }

    return 0.f;
  }

  virtual const IUnitFormulaPars* GetObject( char const *name ) const
  {
    if ( strcmp( name, "DamageTaker" ) == 0 )
      return pTaker;

    return TargetSelectorFormulaPars::GetObject( name );
  }

  float damage;
  const IUnitFormulaPars * pTaker;
};

bool PFEventProcessorOutgoingDamage::ProcessEvent( const PFBaseUnitEvent *pEvent )
{
  const PFOutgoingDamageEvent* pOutgoingDamEvent = dynamic_cast<const PFOutgoingDamageEvent*>(pEvent);
  NI_VERIFY( pOutgoingDamEvent, "Need PFOutgoingDamageEvent to process BASEUNITEVENT_OUTGOINGDAMAGE!", return false );

  const PFBaseUnitDamageDesc* pDesc = pOutgoingDamEvent->pDesc;

  PFBaseApplicator const* pDamageAppl = pDesc->pDealerApplicator;

  if ( !IsValid( pDamageAppl ) )
    return false;

  if ( !PFBaseApplicator::CheckDamageTypeFilter( pDesc->flags, pDesc->damageType, GetDB().damageTypeFilter, false ) )
    return false;

  // Outgoing damage is supposed to be always ally
  if ( !CheckAbilityInFilter( GetDB().abilityFilter, pDamageAppl, pDamageAppl->GetAbilityData(), true, pOwner ) )
    return false;

  DummyFormulaPars dummy( pOwner, pOutgoingDamEvent->damage, pOutgoingDamEvent->pTaker );

  pOutgoingDamEvent->damage = GetDB().modifiedDamage( pOwner->GetAbilityOwner(), pOwner->GetReceiver(), &dummy );

  // designer's code, see NUM_TASK
  // TODO: fix PFBaseUnitEvent.h to be able to send spell to damage taker from editor
  // const CPtr<PFBaseUnit> &pEventSender = pOutgoingDamEvent->GetTaker();
  DoSpell();

  return true;
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFTriggerApplicator, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAbsorbShieldApplicator, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorBase, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorGroup, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorCondition, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorCancelDispatch, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorPickupGlyph, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorDamageTransformer, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorIncomingDamage, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorAbilityManacostTransformer, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorApplicatorApplied, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorOnDeath, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorOnTarget, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorUnitDieNearMe, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorOnUseAbilityForceStrike, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorLastHit, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorOnConsumableObtained, NWorld);
REGISTER_WORLD_OBJECT_NM(PFEventProcessorOutgoingDamage, NWorld);
