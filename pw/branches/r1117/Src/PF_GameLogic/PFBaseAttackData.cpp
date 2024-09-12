#include "stdafx.h"

#include "PFBaseAttackData.h"
#include "PFAbilityInstance.h"
#include "PFAIWorld.h"

#include "PFBaseUnit.h"
#include "PFDispatchFactory.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Scene/SceneObjectCreation.h"


namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFBaseAttackInstance
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFBaseAttackInstance::PFBaseAttackInstance(CObj<PFBaseAttackData> const& pAttackData, Target const& target, bool _allowAllies /*= false*/)
  : PFAbilityInstance( static_cast<PFAbilityData*>(pAttackData.GetPtr()), target, false )
  , attackDelay( pAttackData->GetTimeOffset() )
  , rawAttackDelay( pAttackData->GetTimeOffset( true ) )
  , isAttackFinished( false )
  , allowAllies(_allowAllies)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseAttackInstance::ApplyAttack()
{
  PFBaseAttackData const* pAttackData = static_cast<PFBaseAttackData const*>( GetData() );
  Target const source( pAttackData->GetOwner() );
  NDb::Spell const* pSpell = pAttackData->GetDBDesc();

  PFDispatch *pDispatch = CreateDispatch(this, NULL, source, target, pSpell, PFBaseApplicator::FLAG_BASE_ATTACK, false, rawAttackDelay);
  if (!pDispatch)
    return;

  dispatch.Attach(pDispatch);

  if (attackDelay < EPS_VALUE)
    DoAttack();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseAttackInstance::DoAttack()
{
  if( IsUnitValid( target.GetUnit() ) && ( allowAllies || pOwner->GetFaction() != target.GetUnit()->GetFaction() ) )
  {
    if( IsValid( pOwner ) )
    {
      pOwner->OnAttackDispatchStarted();
    }
    dispatch.Start();
  }
  isAttackFinished = true;
  Cancel(); // CleanUp
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseAttackInstance::Cancel()
{
  attackDelay = 0.0f;  
  target = AbilityTarget();
  dispatch.Cancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseAttackInstance::IsReadyToDie() const
{
  return isAttackFinished && !GetActiveApplicatorsCount();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseAttackInstance::Update(float dt)
{
	if ( attackDelay > 0 )
	{
		attackDelay -= dt;
		if( attackDelay < EPS_VALUE  ) 
			DoAttack();
	}

	return IsReadyToDie();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFBaseAttackData
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFBaseAttackData::PFBaseAttackData(CPtr<PFBaseUnit> const& pOwner, NDb::Ptr<NDb::BaseAttack> const& pDBDesc)
  : PFAbilityData( pOwner, pDBDesc.GetPtr(), NDb::ABILITYTYPEID_BASEATTACK )
  , damageType(pOwner->GetNativeDamageType())
  , processInstances( false )
  , delayedCancel( false )
{
  // collect damage type from applicators
  for ( vector<NDb::Ptr<NDb::BaseApplicator>>::const_iterator iAppl = pDBDesc->applicators.begin(), iEnd = pDBDesc->applicators.end(); iAppl != iEnd; ++iAppl )
  {
    NDb::Ptr<NDb::BaseApplicator> const& pAppl = *iAppl;
    if (pAppl && pAppl->GetObjectTypeID() == NDb::DamageApplicator::typeId)
    {
      damageType = static_cast<NDb::DamageApplicator const*>(pAppl.GetPtr())->damageType;
      if ( damageType == NDb::APPLICATORDAMAGETYPE_NATIVE )
        damageType = pOwner->GetNativeDamageType();
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseAttackData::PFBaseAttackData()
  : processInstances(false)
  , delayedCancel(false)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseAttackData::DoAttack(Target const& target, bool allowAllies /*= false*/)
{
  if ( !target.IsUnitValid() || !CanBeUsed() )
    return false;

  NI_VERIFY( GetOwner()->IsTargetInAttackRange( target, true ), "Target is out of attack range!", return false );
  CObj<PFBaseAttackInstance> pInst = new PFBaseAttackInstance( this, target, allowAllies );
  pInst->ApplyAttack();

  NI_VERIFY( !processInstances, "Cannot push_back to rgAttackInstances duiring self update", return false );
  rgAttackInstances.push_back(pInst);
  
  AddInstance(pInst.GetPtr());

  // recalculate cooldown from attack speed
  const float fAttackSpeed = GetSpeed();
  RestartCooldown( fAttackSpeed < EPS_VALUE ? FP_MAX_VALUE : (1.0f / fAttackSpeed) );
  
  //NI_ALWAYS_ASSERT("Implement critical!");
  
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseAttackData::Update(float dt, bool fullUpdate)
{
  struct AttackInstancesUpdater
  {
    float dt;
    AttackInstancesUpdater(float dt) : dt(dt) {}
    bool operator()( CObj<PFBaseAttackInstance>& inst ) { return !IsValid(inst) || inst->Update(dt); }
  } updater(dt);

  processInstances = true;
  rgAttackInstances.erase( remove_if( rgAttackInstances.begin(), rgAttackInstances.end(), updater ), rgAttackInstances.end() );
  processInstances = false;
  if ( delayedCancel )
    Cancel();

  PFAbilityData::Update(dt, fullUpdate);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseAttackData::Cancel()
{
  for (AttackInstances::iterator iAttack = rgAttackInstances.begin(), iEnd = rgAttackInstances.end(); iAttack != iEnd; ++iAttack )
    (*iAttack)->Cancel();

  NI_VERIFY( !processInstances, "Cannot clear rgAttackInstances duiring self update", { delayedCancel = true; return; } );
  rgAttackInstances.clear();
  delayedCancel = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseAttackData::GetWorkTime() const
{
	float calcWorkTime = 0.0f;

	bool needDelete = false;
	NScene::SceneObject* pSO = GetSO(needDelete);
	if ( !pSO )
	{
		calcWorkTime = 0.0f;
	}
	else
	{
		calcWorkTime = GetAttackNodeDuration( pSO );
		if ( needDelete )
			delete pSO;
	}

  return calcWorkTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseAttackData::GetSpeed() const
{
  const float speed = GetOwner()->GetAttacksPerSecond();//GetStatValue(NDb::STAT_ATTACKSPEED);
  return speed < EPS_VALUE ? 0.0f : speed;
  //const float baseAttackTime = GetOwner()->GetWorld()->GetAIWorld()->GetAIParameters().baseAttackTime;
 //return baseAttackTime < EPS_VALUE ? 0.0f : 1e-2f * (speed / baseAttackTime);
}

float PFBaseAttackData::GetAttackNodeDuration( NScene::SceneObject* pSO ) const
{
	float duration = 0.0f;
	nstl::string nodeName = "attack";
	::DiAnimGraph* pAG = GetAG( pSO );
	if ( !pAG )
	{
		return 0.0f;
	}

	uint nodeId = pAG->GetNodeIDByNameSlowQuite( nodeName.c_str() );
	if ( nodeId >= pAG->GetNumNodes() )
	{
		return 0.0f;
	}
	DiAnimNode* node = pAG->GetNodeData( nodeId );
	if ( !node )
	{
		NI_ALWAYS_ASSERT( NStr::StrFmt("Can not find node %s in %s in %s", nodeName.c_str(), pAG->GetDBFileName().c_str(), pSO->GetRootComponent()->GetDBID().GetFileName().c_str()) );
		return 0.0f;
	}

	if ( node->IsSwitcher() )
	{
		struct FindNode : public INeiFunctor
		{
			bool isFind;
			DiAnimNode* animNode;
			DiAnimGraph* pAG;
			float duration;

			FindNode( DiAnimGraph* ag ) : isFind( false ), animNode( 0 ), pAG( ag ), duration( 0.0f ) {}
			virtual void operator()( DiUInt32 nodeId )
			{
				if ( isFind )
					return;

				DiAnimNode* node = pAG->GetNodeData( nodeId );
				if ( node->IsSubNode() )
				{
					duration = pAG->GetNodeDuration( nodeId );
					animNode = node;
					isFind = true;
				}
			}
		} f( pAG );
		pAG->ForAllNeighbours( nodeId, &f );

		if ( f.isFind )
		{
			duration = f.duration;
		}
	}
	else
	{
		duration = pAG->GetNodeDuration( nodeId );
	}

	return duration;
}

bool PFBaseAttackData::IsMelee() const
{
  return static_cast<NDb::BaseAttack const*>(GetDBDesc())->isMelee;
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFBaseAttackInstance, NWorld);
REGISTER_WORLD_OBJECT_NM(PFBaseAttackData, NWorld);