#include "stdafx.h"

#include "PFApplSummon.h"
#include "PFAbilityData.h"
#include "PFWorld.h"
#include "PFSummoned.h"
#include "PFMaleHero.h"
#include "PFTargetSelector.h"
#include "../System/InlineProfiler.h"
#include "libdb/dbid.h"

#ifndef VISUAL_CUTTED
#include "PFClientApplicators.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

static bool g_enableCloneAbilities = false; /// temporary

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFSummonedUnitBehaviour* PFSummonBehaviourDataCommon::CreateBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, float lifeTime, int behaviourFlags)
{
  return PFSummonedUnitAIBehaviour::Create(pSummonedUnit, pMaster, pBehaviourBase, dbDesc->summonType, lifeTime, behaviourFlags);
}

NDb::EUnitType PFSummonBehaviourDataCommon::GetSummonedUnitType() const
{
  return dbDesc && dbDesc->summonType == NDb::SUMMONTYPE_PET ? NDb::UNITTYPE_PET : NDb::UNITTYPE_SUMMON;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFSummonedUnitBehaviour* PFSummonBehaviourDataBase::CreateDummyBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, float lifeTime, int behaviourFlags)
{
  return PFSummonedUnitBehaviour::Create( pSummonedUnit, pMaster, pBehaviourBase, lifeTime, behaviourFlags );
}


void SetupSummonsLifeAndEnergy( const NDb::SpawnStats& spawnStats, const PFBaseApplicator* pSummoningAppl, PFBaseUnit* pSummonedUnit )
{
  float life = spawnStats.life( pSummoningAppl->GetAbilityOwner(), pSummonedUnit, pSummoningAppl, -1.0f );
  float energy = spawnStats.energy( pSummoningAppl->GetAbilityOwner(), pSummonedUnit, pSummoningAppl, -1.0f );
  if ( life > 0.0f )
  {
    pSummonedUnit->ChangeHealth( life - pSummonedUnit->GetLife() );
  }
  if ( energy >= 0.0f )
  {
    pSummonedUnit->ChangeMana( energy - pSummonedUnit->GetEnergy() );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSummon::Start()
{
  NI_PROFILE_FUNCTION

  if ( PFBaseApplicator::Start() )
  {
    return true;
  }

  const NDb::SummonApplicator& db = GetDB();

  bool isSummonClone = ( db.summonSource == NDb::SUMMONSOURCE_TARGETCLONE );

  // Obtain unit to summon
  NDb::Ptr<NDb::Creature> pUnitDesc;
  if ( isSummonClone )
  {
    pUnitDesc = dynamic_cast<NDb::Creature*>( const_cast<NDb::Unit*>( pReceiver->DbUnitDesc() ) );

    NI_VERIFY( pUnitDesc, NStr::StrFmt( "Summon receiver should be creature, but it is %s", pReceiver->GetDebugDescription() ), return true );
  }
  else
  {
    NI_VERIFY( !db.summonedUnits.empty(), NStr::StrFmt( "No units to summon in applicator '%s'!", NDb::GetFormattedDbId(db.GetDBID()) ),
      return true; );
    int summonedUnitIndex = RetrieveParam( db.summonedUnitIndex, 0 );
    NI_VERIFY(summonedUnitIndex >= 0 && summonedUnitIndex < db.summonedUnits.size(),NStr::StrFmt("Wrong summonedUnitIndex formula in applicator '%s' (summonedUnitIndex: %i)!", NDb::GetFormattedDbId(db.GetDBID()), summonedUnitIndex),
      summonedUnitIndex = 0; );
    pUnitDesc = db.summonedUnits[summonedUnitIndex];
    NI_VERIFY( pUnitDesc, NStr::StrFmt("Failed to get unit to summon in applicator '%s' (summonedUnitIndex: %i)!", NDb::GetFormattedDbId(db.GetDBID()), summonedUnitIndex) ,
      return true; );
  }

  CObj<PFSummonBehaviourDataBase> pBehaviourData;
  if (db.behaviour)
  {
    pBehaviourData = db.behaviour->Create();
    pBehaviourData->Initialize(this);
  }

  float lifeTime = RetrieveParam(db.lifeTime, 0.0f);
  NDb::EUnitType unitType = pBehaviourData ? pBehaviourData->GetSummonedUnitType() : NDb::UNITTYPE_DUMMYUNIT; // unit would be an dummy by default (if have no behaviour)

  int summonedUnitsCount = RetrieveParam( db.summonedUnitsCount, 1 );
  NI_DATA_VERIFY( summonedUnitsCount > 0, NStr::StrFmt( "Summoned units count should be positive (now %d)!", summonedUnitsCount ), summonedUnitsCount = 1 );

  const NDb::SummonBehaviourBase* const pSummonBehaviourBase = db.behaviour;
  const NDb::SummonBehaviourCommon* const pSummonBehaviourCommon = dynamic_cast<const NDb::SummonBehaviourCommon*>( pSummonBehaviourBase );

  if ( pSummonBehaviourCommon )
  {
    NDb::SummonType const& summonType = pSummonBehaviourCommon->summonType;

    // No primary summons for dead masters
    if ( summonType == NDb::SUMMONTYPE_PRIMARY && pOwner->IsDead() )
      return true;

    int maxSummonCount = pSummonBehaviourCommon->maxCount( GetAbilityOwner(), GetReceiver(), this, 1 );
    int curSummonsCount = pOwner->GetSummonsCount( summonType, db.summonGroupName );

    int maxThisSummonCount = pSummonBehaviourCommon->maxThisCount( GetAbilityOwner(), GetReceiver(), this, 0 );

    NI_DATA_ASSERT( maxThisSummonCount <= maxSummonCount, "maxThisCount should be less than maxCount" );
    
    // Pet turn off logic
    if (unitType == NDb::UNITTYPE_PET && curSummonsCount != 0)
    {
      struct UnsummonAct 
      {
        UnsummonAct( const NDb::DBID& id ) : bDontSpawn(false), dbid(id) {}
        void operator()( PFSummonBehaviour* pBehaviour )
        {
          if ( pBehaviour->GetUnit()->DbUnitDesc()->GetDBID() == dbid)
          {
            bDontSpawn = true;
            pBehaviour->Unsummon();
          }
        }

        NDb::DBID dbid;
        bool bDontSpawn;
      } unsummon(pUnitDesc->GetDBID());

      PFBehaviourGroup* pets = pOwner->GetSummonedGroup(NDb::SUMMONTYPE_PET);
      pets->ForAllBehaviour(unsummon);
      if (unsummon.bDontSpawn)
        return true;
    }
    else // ordinary summon
    {
      ExecutableFloatString const& sortingFormula = db.unsummonSortCriterion;
      UnsummonCriterion unsummonCriterion( &sortingFormula, GetAbilityOwner(), this );
      // Check for default formula value (zero)
      bool bUseCriterion = false;
      if ( !sortingFormula.sString.empty() )
      {
      float val = 0.0f;
      const int occurences = sscanf( sortingFormula.sString.c_str(), "%g%*[f]", &val ); // note that something like "0.f + someCode" will be treated as "0.f"
        bUseCriterion = occurences != 1 || val != 0.0f;
      }

      int countToUnsummon = summonedUnitsCount;
      if ( maxThisSummonCount > 0 )
      {
        countToUnsummon -= pOwner->RemoveSummons( summonedUnitsCount, pSummonBehaviourCommon->summonType, db.summonGroupName, pUnitDesc, maxThisSummonCount, bUseCriterion ? &unsummonCriterion : 0 );
      }
      pOwner->RemoveSummons( summonedUnitsCount, pSummonBehaviourCommon->summonType, db.summonGroupName, 0, maxSummonCount, bUseCriterion ? &unsummonCriterion : 0 );
    }

    pOwner->SetMaxAllowedSummons( pSummonBehaviourCommon->summonType, db.summonGroupName, maxSummonCount );
  }

  Placement placement(pOwner->GetPosition());
  if ( (db.flags & NDb::SUMMONFLAGS_TURNBYMASTERDIRECTION) != 0 )
  {
    if ( PFBaseMovingUnit* mOwner = dynamic_cast<PFBaseMovingUnit*>(pOwner.GetPtr()) )
      placement.rot.FromDirection( CVec3( -mOwner->GetMoveDirection(), 0.0f ) );
  }
  for ( int i = 0; i < summonedUnitsCount; i++ )
  {
    bool opensWarFog = unitType == NDb::UNITTYPE_PET ? false : GetDB().openWarFog;
    CPtr<PFBaseSummonedUnit> pSummonedUnit( 
      new PFBaseSummonedUnit(pReceiver->GetWorld(), pUnitDesc, unitType, pOwner.GetPtr(), placement,
        GetDB().flags & NDb::SUMMONFLAGS_NOSUMMONANIMATION , 
        GetDB().flags & NDb::SUMMONFLAGS_USEGLOWEFFECT, 
        opensWarFog) );

    if(isSummonClone && (unitType != NDb::UNITTYPE_HEROMALE || unitType != NDb::UNITTYPE_HEROFEMALE))
      pSummonedUnit->ModifyStatsByForce();

    pSummonedUnit->SetAdditionalDamageParam( db.takeModDmg( pOwner, pSummonedUnit, this, 1.f ), db.takeTypeUnit );

    if ( pSummonBehaviourCommon && pSummonBehaviourCommon->targetingParams )
    {
      pSummonedUnit->OverrideTargetingParams( pSummonBehaviourCommon->targetingParams );
    }

    int behFlags = PFSummonedUnitBehaviour::BEHAVIOURFLAGS_CONTROLLEDLIFETIME;
    if ( (db.flags & NDb::SUMMONFLAGS_ESSENTIAL) != 0 )
      behFlags |= PFSummonedUnitBehaviour::BEHAVIOURFLAGS_ESSENTIALSUMMON;
    if ( (db.flags & NDb::SUMMONFLAGS_ALPHASUMMON) != 0 )
      behFlags |= PFSummonedUnitBehaviour::BEHAVIOURFLAGS_ALPHASUMMON;
    if ( (db.flags & NDb::SUMMONFLAGS_NOHEALTHPRIORITY) != 0 )
      behFlags |= PFSummonedUnitBehaviour::BEHAVIOURFLAGS_NOHEALTHPRIORITY;
    if ( (db.flags & NDb::SUMMONFLAGS_LIKEHERO) != 0 )
      behFlags |= PFSummonedUnitBehaviour::BEHAVIOURFLAGS_LIKEHERO;

    // If unit have an behaviour (it is not a dummy unit)
    CObj<PFSummonedUnitBehaviour> pBehaviour = pBehaviourData
      ? pBehaviourData->CreateBehaviour(pSummonedUnit, pOwner.GetPtr(), db.behaviour.GetPtr(), lifeTime, behFlags)
      : PFSummonBehaviourDataBase::CreateDummyBehaviour(pSummonedUnit, pOwner.GetPtr(), db.behaviour.GetPtr(), lifeTime, behFlags);

    if ( pBehaviour )
    {
      pBehaviour->SetGroupName( db.summonGroupName );

      if (pSummonBehaviourCommon)
      {
        pBehaviour->SetLashRange( pSummonBehaviourCommon->lashRange(pOwner, pSummonedUnit, this, 15.f ) );
        pBehaviour->SetResponseRange( pSummonBehaviourCommon->responseRange );
        pBehaviour->SetResponseTime( pSummonBehaviourCommon->responseTime );
      }

      pSummonedUnit->AddBehaviourOnTop(pBehaviour.GetPtr());
    }

    // Obtain spawn position from target selector
    Target spawnTarget = GetTarget();
    if ( db.placeMode == NDb::SUMMONPLACEMODE_BYTARGETSELECTOR )
    {
      CObj<PFSingleTargetSelector> pTargetSelector = static_cast<PFSingleTargetSelector*>(db.placeSelector->Create( GetWorld() ));
      Target receiver(pReceiver);
      PFTargetSelector::RequestParams pars(*this, receiver);
      pTargetSelector->FindTarget(pars, spawnTarget);
    }
    else if ( db.placeMode == NDb::SUMMONPLACEMODE_BYBEHAVIOUR )
    {
      if (pBehaviour)
        pBehaviour->AcquireBehaviourDefinedSpawnPosition(spawnTarget);
    }
    //else if ( db.placeMode == NDb::SUMMONPLACEMODE_BYAPPLICATOR ) // default value

    // if we have not valid target to spawn to, obtain it from ability target
    if ( !spawnTarget.IsValid( true ) )
      spawnTarget = GetTarget();

    if(db.flags == NDb::SUMMONFLAGS_NOCOLLISION)
      pSummonedUnit->SetPlaceUnitIgnoreCollision(true);

    pSummonedUnit->TeleportTo( spawnTarget.AcquirePosition().AsVec2D() );

    if ( ( db.flags & NDb::SUMMONFLAGS_COPYLEVELANDSTATS ) != 0 )
    {
      pSummonedUnit->SetNaftaLevel( 1 );
      pSummonedUnit->DoLevelups( pReceiver->GetNaftaLevel() - 1 );
    }
    
    SetupSummonsLifeAndEnergy( db.spawnStats, this, pSummonedUnit );

    // Activate applicators on unit
    Target createdUnit(CPtr<PFBaseUnit>(pSummonedUnit.GetPtr()));
    CreateAndActivateApplicators(db.applicators, pAbility, createdUnit, this);

    // hide primary summon if hero is playing minigame
    if ( pOwner->IsHero() && IsValid(pBehaviour) && ( pBehaviour->GetSummonTypeInt() == NDb::SUMMONTYPE_PRIMARY || pBehaviour->GetSummonTypeInt() == NDb::SUMMONTYPE_PET ) )
    {
      PFBaseHero* pHero = dynamic_cast<PFBaseHero*>( pOwner.GetPtr() );
      if ( pHero && pHero->IsIsolated() )
        pSummonedUnit->Hide( true );
    }
  }

  return true;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplCloneHero::Start()
{
  if ( Base::Start() )
  {
    return true;
  }

  PFBaseHero* pHero      = dynamic_cast<PFBaseHero*>( pReceiver.GetPtr() );
  NI_ASSERT( pHero, "PFApplCloneHero can be applied only on a hero" );

  PFBaseHero* pOwnerHero = dynamic_cast<PFBaseHero*>( pOwner.GetPtr() );
  NI_ASSERT( pOwnerHero, "PFApplCloneHero can be applied only by a hero" );

  NDb::CloneHeroApplicator const& db = GetDB();

  int flags = db.flags;

	// prepare clone parameters
	CloneParams params;
	params.lifeTime = RetrieveParam(   db.lifeTime,    0.0f );
	float followRange = RetrieveParam( db.followRange, 0.0f );
	if ( followRange > 0 )
  {
    params.followRange = followRange;
  }
  params.mirrorOwnerAbilities   = ( flags & NDb::CLONEFLAGS_MIRROROWNERSPELLS ) && g_enableCloneAbilities;
  params.shouldPlaySummonEffect = ( flags & NDb::CLONEFLAGS_PLAYSUMMONEFFECT  );
  params.copyStats              = ( flags & NDb::CLONEFLAGS_COPYSTATS );
  params.isDummy                = ( flags & NDb::CLONEFLAGS_DUMMYBEHAVIOUR );
  params.initTalents            = ( flags & NDb::CLONEFLAGS_INITTALENTS );

  const bool makeSlave = ( flags & NDb::CLONEFLAGS_MAKESLAVE );

  params.pOwner = pOwnerHero;

  if ( makeSlave )
  {
    // No slave clones for dead master
    if ( pOwnerHero->IsDead() )
      return true;

    params.bSlave = true;
    params.targetingParams = db.targetingParams;

    // remove old clones
    int maxSummonCount = RetrieveParam( db.maxCount, 0 );
    int curSummonsCount = pOwnerHero->GetSummonsCount( NDb::SUMMONTYPE_PRIMARY, db.summonGroupName );
    pOwnerHero->RemoveSummons( 1 + curSummonsCount - maxSummonCount, NDb::SUMMONTYPE_PRIMARY, db.summonGroupName );
    pOwnerHero->SetMaxAllowedSummons( NDb::SUMMONTYPE_PRIMARY, db.summonGroupName, maxSummonCount );
  }

	// clone hero
  PFBaseHero *pClone = pHero->Clone(params, db.takeModDmg( pOwner, pHero, this, 1.f ), db.takeTypeUnit, db.summonGroupName );
  if (!pClone)
    return true;

  // slave must have unittype = summon
  if( makeSlave )
  {
    pClone->SetUnitType( NDb::UNITTYPE_SUMMON );
  }
  else if ( params.isDummy )
  {
    pClone->SetUnitType( NDb::UNITTYPE_DUMMYUNIT );
  }

	// setup non-hero properties
  pClone->SetGhostMode(flags & NDb::CLONEFLAGS_GHOSTMOVE, false);
  pClone->EnableAbilityAI(flags & NDb::CLONEFLAGS_USEABILITYAI);

  SetupSummonsLifeAndEnergy( db.spawnStats, this, pClone );

  // Activate applicators on unit
  CPtr<PFBaseUnit> pUnit(pClone);
  Target createdUnit(pUnit);
  CreateAndActivateApplicators(db.applicators, pAbility, createdUnit, this);

  return true;
}

REGISTER_DEV_VAR("enable_clone_abilities", g_enableCloneAbilities, STORAGE_NONE); /// temporary

} // namespace

REGISTER_WORLD_OBJECT_NM(PFSummonBehaviourDataBase,   NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonBehaviourDataCommon, NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSummon,                NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplCloneHero,             NWorld);

