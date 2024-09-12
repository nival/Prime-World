#include "stdafx.h"
#include "PFHero.h"
#include "PFSummoned.h"
#include "PFHeroStates.h"
#include "PFAbilityData.h"
#include "PFAbilityInstance.h"
#include "PFStatistics.h"

#ifndef VISUAL_CUTTED
#include "PFClientHero.h"
#else
#include "../Game/PF/Audit/ClientStubs.h"
#endif

namespace NWorld
{

class PFHeroCloneBehaviour : public PFSummonBehaviour, public PFBaseUnitEventListener
{
  WORLD_OBJECT_METHODS(0x1F74E440, PFHeroCloneBehaviour)
protected:
  PFHeroCloneBehaviour() {}

	ZDATA_(PFSummonBehaviour)
	ZNOPARENT(PFBaseUnitEventListener)
	float              followRange;
	bool               mirrorOwnerAbilities;
  CPtr<PFBaseHero>   pHeroMaster;
  int                cloneId;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFSummonBehaviour*)this); f.Add(2,&followRange); f.Add(3,&mirrorOwnerAbilities); f.Add(4,&pHeroMaster); f.Add(5,&cloneId); return 0; }

	PFHeroCloneBehaviour( PFBaseHero* pUnit, const CPtr<PFBaseHero>& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, const CloneParams& params, int _cloneId )
	: PFSummonBehaviour( pUnit, pMaster, pBehaviourBase, params.lifeTime, BEHAVIOURFLAGS_CONTROLLEDLIFETIME )
	, followRange( params.followRange )
	, mirrorOwnerAbilities( params.mirrorOwnerAbilities )
  , pHeroMaster( pMaster )
  , cloneId( _cloneId )
	{
		pHeroMaster->AddEventListener( this );
	}

	virtual void OnStop()
	{
		pHeroMaster->RemoveEventListener( this );
    pHeroMaster->RemoveClone( cloneId );

    PFSummonBehaviour::OnStop();
	}

	virtual bool OnStep(float dtInSeconds)
	{
		CPtr<PFBaseHero> pUnit = static_cast<PFBaseHero*>(GetUnit().GetPtr());

		// kill controlled unit when master is dead
		if (!pUnit->IsDead() && IsValid(pMaster))
		{
			if (!pUnit->GetCurrentState())
				pUnit->EnqueueState(new PFHeroFollowUnitState(pUnit, pMaster, followRange), true);
			// control life time (part of PFSummonedUnitAIBehaviour::OnStep() code)
      if (!IsValid(pMaster) || pMaster->IsDead())
      {
        Unsummon();
        return true;
      }
		}

		return PFSummonBehaviour::OnStep(dtInSeconds);
	}

  
  void OnDamage( const PFBaseUnitDamageDesc& desc )
  {
    PFBaseBehaviour::OnDamage( desc );
  }

  bool CanSelectTarget( PFBaseUnit const* pTarget ) const
  {
    if ( followRange < 0.0f )
      return true;

    return pTarget->IsInRange( pMaster, followRange + pUnit->GetAttackRange() );
  }

	virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent)
	{
    CPtr<PFBaseHero> pUnit = static_cast<PFBaseHero*>(GetUnit().GetPtr());

		if (!IsUnitValid(pUnit))
			return 0;

		if (pEvent->GetType() == NDb::BASEUNITEVENT_CASTMAGIC && mirrorOwnerAbilities)
		{
			PFBaseUnitUseAbilityEvent const *pAbilityEvent = dynamic_cast<PFBaseUnitUseAbilityEvent const *>(pEvent);
			NI_VERIFY(pAbilityEvent, "PFHeroCloneBehaviour: wrong event type", return 0);

			PFAbilityInstance const *pInstance = pAbilityEvent->GetAbility();
			NI_VERIFY(IsValid(pInstance), "Invalid ability!", return 0);
			NWorld::PFAbilityData const* pAbility = pInstance->GetData();
			NI_VERIFY(pAbility, "Invalid ability data", return 0);

			if (!(pInstance->GetFlags() & NDb::ABILITYFLAGS_MIRROREDBYCLONE))
				return 0;
			int abilityId = pAbility->GetAbilityTypeId() - NDb::ABILITYTYPEID_ABILITY0;

      if (pUnit->CanUseAbility(abilityId))
      {
        CObj<IPFState> pState = pUnit->InvokeAbility(abilityId, pInstance->GetTarget());
        if (IsValid(pState))
          pUnit->EnqueueState(pState, true);
      }
		}

    if(pEvent->GetType() == NDb::BASEUNITEVENT_MOVE)
    {
      if (IsUnitValid(pUnit) && followRange > 0.0f )
      {
        IPFState const* pState = pUnit->GetCurrentState();
        if(pState && pState->GetTypeId() == PFBaseUnitAttackState::typeId)
          if(IsUnitValid(pMaster) && !pUnit->IsInRange( pMaster, followRange))
          {
            pUnit->Cleanup();
            pUnit->PushState(new PFHeroFollowUnitState(pUnit, pMaster, followRange));
          }
      }
    }

		return 0;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseHero* PFBaseHero::Clone( const CloneParams& params, float takeModDmg, NDb::ESpellTarget takeTypeUnit, const string& summonGroupName )
{
  PFBaseHero* pOwner = params.pOwner;
  //bool isSlave = ( pOwner != NULL );

	SpawnInfo info;
	info.playerId      = -1;
  info.inTeamId      = (params.bSlave && pOwner) ? pOwner->GetInTeamId() : GetInTeamId();
  info.placement.pos = GetPosition();
#ifndef VISUAL_CUTTED
  if ( ClientObject() )
  {
    info.placement.rot = ClientObject()->GetPosition().rot;
  }
#endif //VISUAL_CUTTED
	info.pHero         = GetDbHero();
  info.faction       = (params.bSlave && pOwner) ? pOwner->GetFaction() : GetFaction();
  info.bInitTalents  = params.initTalents;
  info.originalFaction = GetOriginalFaction();
  info.usePlayerInfoTalentSet = false;
	info.isClone = true;
	info.shouldPlaySummonEffect = params.shouldPlaySummonEffect;
  info.playerInfo.heroSkin = GetSkinId();
	PFBaseHero* pNewHero = CreateHero( GetWorld(), info );

  pNewHero->playerGender = playerGender;

  pNewHero->SetAdditionalDamageParam( takeModDmg, takeTypeUnit );

  // Only true clone should have playerId
  if ( !params.bSlave )
	  pNewHero->playerId = playerId;

	// unregister clone from statistic
  pNewHero->pStatistics = 0;

  // Copy stats
  if ( params.copyStats )
  {
    for ( int statId = 0; statId < NDb::KnownEnum<NDb::EStat>::SizeOf(); statId++ )
    {
      if ( StatValueWithModifiers const* pStat = GetStat( NDb::EStat( statId ) ) )
      {
        StatValueWithModifiers* pNewHeroStat = pNewHero->GetStat( NDb::EStat( statId ) );
        pNewHeroStat->CopyUnmodifiedValue( pStat );
      }
    }
  }

  // Copy stat modifiers with PF_Core::WORLD_ID provider from the hero 
  // being cloned, just in case the "global_stat_scale" cheat was used
  pNewHero->CopyStatModifiersFrom( this, PF_Core::WORLD_ID );

	CObj<PFSummonBehaviour> pB;
  if ( params.bSlave )
  {
    if ( params.isDummy )
    {
      pB = PFSummonedUnitBehaviour::Create( pNewHero, pOwner, NULL, params.lifeTime, PFSummonBehaviour::BEHAVIOURFLAGS_CONTROLLEDLIFETIME );
    }
    else
    {
      pNewHero->OverrideTargetingParams( params.targetingParams );
      pB = PFSummonedUnitAIBehaviour::Create( pNewHero, pOwner, NULL, NDb::SUMMONTYPE_PRIMARY, params.lifeTime, PFSummonBehaviour::BEHAVIOURFLAGS_CONTROLLEDLIFETIME );
    }
    pB->SetGroupName( summonGroupName );
  }
  else
  {
    pB = new PFHeroCloneBehaviour( pNewHero, this, NULL, params, cloneCounter );
  }

  pNewHero->AddBehaviourOnTop( pB );
  if ( pNewHero->ClientObject() )
  {
    if ( params.shouldPlaySummonEffect )
      pNewHero->ClientObject()->Summon();
	  else
		  pNewHero->ClientObject()->Idle( true );
  }

  pNewHero->SetNaftaLevel( naftaLevel );

  if ( !params.bSlave )
  {
    clones.push_back( CloneInfo( pNewHero, cloneCounter ) );
    cloneCounter++;
  }

	return pNewHero;
}

void PFBaseHero::RemoveClone( int id )
{
  for ( vector<CloneInfo>::iterator iter = clones.begin(); iter != clones.end(); iter++ )
  {
    if ( iter->id == id )
    {
      clones.erase( iter );
      return;
    }
  }
  NI_ALWAYS_ASSERT( NStr::StrFmt( "Can't find and remove clone with id = %d", id ) );
}

}

REGISTER_WORLD_OBJECT_NM(PFHeroCloneBehaviour, NWorld)
