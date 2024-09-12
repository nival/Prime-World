#include "stdafx.h"
#include "PFApplDelegateDamage.h"
#include "PFBaseUnit.h"
#include "PFDispatchFactory.h"
#include "PFApplInstant.h"

namespace NWorld
{

PFApplDelegateDamage::PFApplDelegateDamage( const PFApplCreatePars& cp )
  : Base( cp )
  , totalDamage( 0.0f )
  , damageToDelegate( 0.0f )
  , stopByCondition(false)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplDelegateDamage::Start()
{
  totalDamage = RetrieveParam( GetDB().totalDamage );

  if ( GetDB().delegateTargets )
  {
    pTargetSelector = GetDB().delegateTargets->Create(GetWorld());
  }

  NI_VERIFY( pTargetSelector, "PFApplDelegateDamage: no delegate targets", return true);

  return Base::Start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplDelegateDamage::Enable()
{
  Base::Enable();
  pReceiver->AddEventListener( this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplDelegateDamage::Disable()
{
  Base::Disable();
  pReceiver->RemoveEventListener( this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplDelegateDamage::Step( float dtInSeconds )
{
  if ( Base::Step( dtInSeconds ) )
  {
    return true;
  }

  return DelegateIsOver();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PFApplDelegateDamage::OnEvent( PFBaseUnitEvent const* pEvent )
{
  if ( DelegateIsOver() )
    return 0;

  PFBaseUnitDamageEvent const* pDamageEvent = dynamic_cast<PFBaseUnitDamageEvent const*>( pEvent );
  if ( !pDamageEvent )
    return 0;

  PFBaseUnit::DamageDesc const* pOriginalDesc = pDamageEvent->pDesc;
  // only single damage delegation allowed!
  if ( pOriginalDesc->delegated || !pOriginalDesc->pDealerApplicator )
    return 0;

  // Collect targets
  vector<PFBaseUnit*> delegateTargets;
  PFTargetSelector::TargetsCollector<PFBaseUnit> targetsCollector(delegateTargets);
  PFTargetSelector::RequestParams rp( *this, GetTarget() );
  pTargetSelector->EnumerateTargets( targetsCollector, rp );

  if ( delegateTargets.empty() )
    return 0;

  // Calc numbers
  damageToDelegate = pDamageEvent->damage2Deal;
  // damageToDelegate is used in next formulas via ::GetVariable
  float damageToApply = RetrieveParam( GetDB().damageToApply );
  stopByCondition = RetrieveParam( GetDB().stopCondition );
  damageToDelegate = RetrieveParam( GetDB().damageToDelegate );

  if ( !GetDB().infiniteTotalDamage )
  {
    const float remainingCapacity = totalDamage - damageToDelegate;

    if ( remainingCapacity < 0.0f )
    {
      damageToApply += -remainingCapacity;
      damageToDelegate = totalDamage;
    }

    totalDamage = remainingCapacity;
  }

  // set new damage to original target (receiver)
  pDamageEvent->damage2Deal = damageToApply;

  DelegateDamage( pDamageEvent, delegateTargets );

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplDelegateDamage::DelegateDamage( const PFBaseUnitDamageEvent* pEvent, vector<PFBaseUnit*> const& delegateTargets )
{
  PFBaseUnit::DamageDesc const* pOriginalDesc = pEvent->pDesc;
  PFBaseApplicator const* pOriginalDealerApplicator = pOriginalDesc->pDealerApplicator;
  if ( !pOriginalDealerApplicator )
    return;

  const int targetsCount = delegateTargets.size();
  NI_VERIFY( targetsCount > 0, "delegateTargets should not be empty", return );
  const float damagePart = damageToDelegate / (float)targetsCount;
  // Process targets
  for ( int i = 0; i < targetsCount; ++i )
  {
    PFBaseUnit* pDelegateUnit = delegateTargets[i];

    bool senderIsOriginal = ( pDelegateUnit->GetFaction() == pReceiver->GetFaction() );
    CPtr<PFBaseUnit> pDamageSender = senderIsOriginal ? pOriginalDesc->pSender : pOwner.GetPtr();
    CObj<PFAbilityInstance> const& pDamageAbility = senderIsOriginal ? pOriginalDealerApplicator->GetAbility() : pAbility;

    Target const delegateTarget( pDelegateUnit );
    PFApplCreatePars cp(pDamageAbility, delegateTarget, this);
    cp.pDBAppl = pOriginalDealerApplicator->GetDBBase();

    CObj<PFBaseApplicator> pApplicator( CreateApplicator(cp) );
    PFApplDamage* pDamageApplicator = static_cast<PFApplDamage*>(pApplicator.GetPtr());

    int damageMode = pOriginalDesc->damageMode;
    if ( (GetDB().flags & NDb::DELEGATEDAMAGEFLAGS_ALLOWDRAINS) == 0 )
      damageMode &= ~(NDb::DAMAGEMODE_APPLYLIFEDRAINS | NDb::DAMAGEMODE_APPLYENERGYDRAINS);

    PFBaseUnit::DamageDesc desc;
    desc.pSender        = pDamageSender;
	  desc.amount         = damagePart;
    desc.damageType     = pOriginalDesc->damageType;
	  desc.flags          = 0;
    desc.damageMode     = (NDb::EDamageMode)damageMode;
    desc.dontAttackBack = GetDB().forceDontAttackBack ? true : pOriginalDesc->dontAttackBack;
	  desc.pDealerApplicator = pDamageApplicator;
    desc.ignoreDefences = GetDB().ignoreDefences;
    desc.delegated = true;
    desc.isDelegatedCriticalDamage = pOriginalDesc->isDelegatedCriticalDamage;

    pDamageApplicator->SetDelegated( &desc );
    pDelegateUnit->OnApplicatorApply( pApplicator );

    // update delegated damage if needed
    if ( senderIsOriginal )
    {
      pOriginalDesc->delegatedDamage += pDamageApplicator->GetDamageDealed();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplDelegateDamage::DelegateIsOver()
{
  return stopByCondition || !GetDB().infiniteTotalDamage && totalDamage <= 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplDelegateDamage::GetVariable(const char* varName) const
{
  if ( strcmp(varName, "Damage") == 0 )
    return damageToDelegate;
  else if (strcmp(varName, "DelegateDamageCapacity") == 0)
  {
    if( GetDB().infiniteTotalDamage )
      return -1.0f;
    else
      return totalDamage;
  }
  return PFBaseApplicator::GetVariable(varName);
}


}

REGISTER_WORLD_OBJECT_NM(PFApplDelegateDamage, NWorld);
