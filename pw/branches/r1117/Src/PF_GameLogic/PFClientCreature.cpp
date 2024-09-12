#include "stdafx.h"
#include "PFClientCreature.h"
#include "PFCreature.h"
#include "../System/RandomGen.h"
#include "../PF_Core/RecolorableTexture.h"
#include "PFAIWorld.h"

#include "../System/InlineProfiler.h"
#include "PFBaseAttackData.h"
#include "../PF_Core/EffectsPool.h"

#include "PFLogicConst.h"

#include "ClientVisibilityHelper.h"

#define USE_ABILITY_CALLBACKS


namespace
{
  float g_attackAnimtionSlowDown = 0.9f;
  bool g_UseControlInAbilityCallbacks = false;
	static float g_attackToIdleTime = 0.3f;
}

namespace NGameX
{

PFClientCreature::PFClientCreature(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp)
: PFClientBaseMovingUnit(pWO, cp)
, lifeState(Living)
, happyState(EHappyState::Ready)
, fallingTime(0.0f)
, isMoveAnimAllowed(true)
, isMoveAnimated(false)
, currentAnimSet(-1)
, deathAnimState(NDb::ANIMSTATES_DEATH)
, doFireAlreadyHappened(false)
, doFirePending(false)
, attackSpeed(-1.0f)
, baseAttackSpeed(-1.0f)
, moveSpeed(1.0f)
, deadTime(0.0f)
, isFighting(false)
, attackMarkerState(None)
, predictMarkerPending(false)
, stopAttackAnimation(false)
, pAnimSet( cp.pAnimSet )
, happyStateTimer( 0.0f )
, happyStateRestingTimer( 0.0f )
, isStunned(false)
, needUpdateStun(false)
, forcedAnimRestartTimer(0.f)

{
  NI_PROFILE_FUNCTION
  for( int i = 0, count = AbilitiesCount; i < count; ++i)
  {
    abilityAnims[i]      = false;
    upperAbilityAnims[i] = false;
  }
}

bool PFClientCreature::Initialize( NScene::SceneObject* pSceneObject, NDb::AnimSet const* const* pAnimSets, unsigned const count, bool isDeath, unsigned const defaultSet, bool isHero )
{
  NI_PROFILE_FUNCTION

  NI_VERIFY( NULL != pSceneObject,    "Invalid scene object!",    return false);
  NI_VERIFY( NULL != pAnimSets,       "No animSets!",             return false);
  NI_VERIFY( 0 < count,               "No animSets!",             return false);
  NI_VERIFY( defaultSet < count,      "Invalid default animSet!", return false);

  if( PFAnimController::Initialize( pSceneObject, isHero ) )
  {
    int defaultSetId = -1;
    for(unsigned i = 0; i < count; ++i)
    {
      const int setId = RegisterAnimSet( pAnimSets[i] );
      if( setId < 0)
      {
        NI_ALWAYS_ASSERT("Failed to register animSet!");
        return false;
      }

      if( defaultSet == i )
        defaultSetId = setId;
    }

    if( defaultSetId < 0 )
    {
      NI_ALWAYS_ASSERT("Failed to detect default animSet: defaulting to first registered!");
      defaultSetId = 0;
    }

    ActivateAnimSet(defaultSetId);
		if ( isDeath )
			Idle( true );
		else
			Summon();

    GetSceneObject()->SetUpdateHook( this );

    return true;
  }
  return false;
}

int  PFClientCreature::RegisterAnimSet( NDb::AnimSet const* pAnimSet )
{
  NI_PROFILE_FUNCTION

  int setId = PFAnimController::RegisterAnimSet(pAnimSet);
  if( 0 <= setId )
  {
    PFAnimController::ActivateAnimSet(setId);

    animSetParams.push_back();

    AnimSetParams& params   = animSetParams.back();
    params.setId            = setId;
    params.surfSpeed        = GetSurfaceSpeed( NDb::ANIMSTATES_MOVE );

    bool ok = false;

    {
      // check normal state
      string marker = GetStateMarker( NDb::ANIMSTATES_ATTACK, false );
      if( !marker.empty() )
      {
        ok = RegisterAnimEvent( AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, marker), CreateAnimEventCallback(this, &PFClientCreature::OnDoFireHappened), setId );
      }

      // check upper state
      marker = GetStateMarker( NDb::ANIMSTATES_ATTACK, true );
      if( !marker.empty()  )
      {
        ok = RegisterAnimEvent( AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYUPPER, marker), CreateAnimEventCallback(this, &PFClientCreature::OnDoFireHappened), setId );
      }
    }

#ifdef USE_ABILITY_CALLBACKS
		for(int i = NDb::ANIMSTATES_ABILITY1; i <= NDb::ANIMSTATES_ABILITY4; ++i)
    {
      NDb::EAnimStates const state = static_cast<NDb::EAnimStates>(i);
      if( IsValidState(state, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL) )
      {
        ok = RegisterAnimEvent( AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, state, AnimEventParams::ExactParam, 1.0 ), 
          CreateAnimEventCallback(this, &PFClientCreature::OnActionAnimFinished), setId);
				
        ok = RegisterAnimEvent( AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, state, AnimEventParams::LeaveNode ), 
          CreateAnimEventCallback(this, &PFClientCreature::OnActionAnimFinished), setId);
      }
    }
#endif
    
    // Register death and unsummon nodes
    if( IsValidState(NDb::ANIMSTATES_DEATH, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL) )
    {
      ok = RegisterAnimEvent(AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, NDb::ANIMSTATES_DEATH, AnimEventParams::ExactParam, 0.99f), 
        CreateAnimEventCallback(this, &PFClientCreature::OnDeathAnimFinished), setId);
      NI_ASSERT(ok, "Failed to register anim event");
    }
    if ( IsValidState(NDb::ANIMSTATES_UNSUMMON, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL) )
    {
      ok = RegisterAnimEvent(AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, NDb::ANIMSTATES_UNSUMMON, AnimEventParams::ExactParam, 0.99f), 
        CreateAnimEventCallback(this, &PFClientCreature::OnDeathAnimFinished), setId);
      NI_ASSERT(ok, "Failed to register anim event");
    }

    if(NDb::Ptr<NDb::EmoteSettings> pSettings = NDb::SessionRoot::GetRoot()->visualRoot->emoteSettings )
    {
      for(int node = 0, nodesCount = pSettings->nodes.size(); node < nodesCount; ++node)
      {
        const unsigned stateId  = GetStateId(static_cast<NDb::EAnimStates>(node));        
        EmoteSettings& settings = params.emoParams[stateId];
        for(unsigned i = 0, count = pSettings->nodes[i].permissions.size(); i < count; ++i)
        {
          const bool both    = NDb::EMOTEPERMISSION_PLAYBOTH == pSettings->nodes[node].permissions[i];
          settings[i].first  = both || NDb::EMOTEPERMISSION_PLAYUPPER == pSettings->nodes[node].permissions[i];
          settings[i].second = both || NDb::EMOTEPERMISSION_PLAYLOWER == pSettings->nodes[node].permissions[i];
        }
      }
    }
  }

  return setId;
}

bool PFClientCreature::UnRegisterAnimSet( int id )
{
  if( id < 0 )
    return false;
  
  if( currentAnimSet == id )
  {
    currentAnimSet = animSetParams[id].prevSetId;
    NI_ASSERT( 0 < currentAnimSet,   "Trying to unregister last animSet!");
    NI_ASSERT( id != currentAnimSet, "Looped animSet change!");
  }

  return PFAnimController::UnRegisterAnimSet(id);
}

bool PFClientCreature::ActivateAnimSet( int id )
{
  const int current = currentAnimSet;
  for(int i = 0, count = animSetParams.size(); i < count ; ++i)
  {
    if( animSetParams[i].setId == id )
    {
      currentAnimSet             = i;
      animSetParams[i].prevSetId = current;
      break;
    }
  }

  return PFAnimController::ActivateAnimSet(id);
}

void PFClientCreature::OnDestroyContents()
{
  if( NScene::SceneObject* pSO = GetSceneObject() )
    pSO->SetUpdateHook( NULL );

  PFAnimController::Cleanup();
  PFClientBaseMovingUnit::OnDestroyContents();
}

void PFClientCreature::OnWorldObjectDie()
{
  RemoveGlowEffect();

  if( NScene::SceneObject* pSO = GetSceneObject() )
    pSO->SetUpdateHook( NULL );
  
  PFAnimController::Cleanup();
  PFClientBaseMovingUnit::OnWorldObjectDie();
}

void PFClientCreature::SetMoveSpeed( float speed )
{
  NI_VERIFY( speed >= 0.0f, NStr::StrFmt( "Move speed(%f) shouldn't be negative!", speed ), return );

  if ( speed == moveSpeed )
  {
    return;
  }

  moveSpeed = speed;

  UpdateCurAnimSetSurfSpeedMultiplier();
}

void PFClientCreature::SetAttackSpeed( float speed )
{
  NI_VERIFY( speed >= 0.0f, NStr::StrFmt( "Attack speed(%f) shouldn't be negative!", speed ), return );

  if ( baseAttackSpeed < 0.0f )
  {
    baseAttackSpeed = speed;
  }

  if ( fabs( attackSpeed - speed ) > EPS_VALUE )
  {
    attackSpeed = speed;

    PredictAttackMarker( Predictable );
  }
}

void PFClientCreature::OnStartMoving( bool animate )
{
  isMoveAnimAllowed = animate;

  if ( isMoveAnimAllowed )
  {
    needUpdateStun = false; // it is supposed that move animation is called when no stuns are applied
    SetAnimState( NDb::ANIMSTATES_MOVE, GetStatePlayMode( NDb::ANIMSTATES_MOVE ) );
  }
  
  isMoveAnimated = true;
}

void PFClientCreature::OnStopped()
{
	//TODO: NUM_TASK
  if( isMoveAnimAllowed && isMoveAnimated && !isFighting && !isStunned )
    Idle();

  isMoveAnimated = false;
}

void PFClientCreature::OnMoveFailed( const CVec2& target )
{
	LookTo( target );
  if( !isMove )
  {
    SetAnimState( NDb::ANIMSTATES_BLOCKEDMOVE, GetStatePlayMode( NDb::ANIMSTATES_BLOCKEDMOVE ) );
  }
}

void PFClientCreature::OnUnitDie()
{
  RemoveGlowEffect();

  if( Living != lifeState)
    return;

  lifeState = Dying;

  //TODO
  UnFreezeAG();

  NI_ASSERT(NDb::ANIMSTATES_DEATH == deathAnimState || NDb::ANIMSTATES_UNSUMMON == deathAnimState, "Death animation state is different from Death and Unsummon");

  PFClientBaseMovingUnit::Stand();
  if( !SetAnimState(deathAnimState, GetStatePlayMode(deathAnimState) ) )
    OnDeathAnimFinished();

  if( NScene::SceneObject* pSO = GetSceneObject() )
    pSO->UpdateForced( 0.0f, false, IsVisible() );

  if( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(false);
  if( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(false);
}

void PFClientCreature::OnTeleportTo( const CVec2& target )
{
  if ( lifeState != Living )
  {
    PFClientBaseMovingUnit::OnTeleportTo( target, false );
  }
}

void PFClientCreature::Summon()
{
  Restart( IsValidState( NDb::ANIMSTATES_SUMMON, GetStatePlayMode(NDb::ANIMSTATES_SUMMON) ) ? NDb::ANIMSTATES_SUMMON : NDb::ANIMSTATES_IDLE );
}

void PFClientCreature::OnUnsummon()
{
  deathAnimState = NDb::ANIMSTATES_UNSUMMON;

  PFClientBaseMovingUnit::OnUnsummon();
}

void PFClientCreature::OnFakeUnsummon()
{
  PFClientBaseMovingUnit::Stand();

  SetAnimState(NDb::ANIMSTATES_UNSUMMON, GetStatePlayMode(NDb::ANIMSTATES_UNSUMMON) );

  if( NScene::SceneObject* pSO = GetSceneObject() )
    pSO->UpdateForced( 0.0f, false, IsVisible() );
}

void PFClientCreature::StartFallThrough(float fallingSpeed_)
{
  NI_ASSERT( lifeState >= Dying, "Fall through before perish complited!" );

  if ( GetSceneObject() )
  {
    float fallRange = GetSceneObject()->GetWorldAABB().halfSize.z * 3;
    fallingSpeed = fallingSpeed_;
    fallingTime = fallRange / fallingSpeed_;
  }
}

void PFClientCreature::OnDeathAnimFinished()
{
  if ( lifeState != Living )
    lifeState = Perished;
  deadTime = 0.0f;
}

void PFClientCreature::Resurrect()
{
  if( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(bVisible);
  if( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(bVisible);

  for( int i = 0, count = AbilitiesCount; i < count; ++i)
  {
    abilityAnims[i]      = false;
    upperAbilityAnims[i] = false;
  }
    
  Restart( IsValidState( NDb::ANIMSTATES_RESURRECT, GetStatePlayMode(NDb::ANIMSTATES_RESURRECT) ) ? NDb::ANIMSTATES_RESURRECT : NDb::ANIMSTATES_IDLE);

  lifeState = Living;
  fallingTime = 0.0f;
  deadTime = 0.0f;
}

void PFClientCreature::Attack(float timeOffset)
{
  NDb::EAnimStates target = NDb::ANIMSTATES_ATTACK;

	if( timeOffset < EPS_VALUE )
  {
    string objectDesc = 
#ifdef _SHIPPING
      "unknown";
#else
      WorldObject()->GetDebugDescription();
#endif
    string error = NStr::StrFmt("Final attack time offset <%.3f seconds> calculated as ( attackTimeOffset / attackSpeed )  is too small for animated character <%s>: check attackSpeed ( value of stat <%s> ) and attackTimeOffset!", timeOffset, objectDesc.c_str(), NDb::KnownEnum<NDb::EStat>::ToString(NDb::STAT_ATTACKSPEED) );
    NI_ALWAYS_ASSERT( error.c_str() );
    return;
  }
  
  float markerOffset = timeOffset;
  doFirePending     = true;
  attackMarkerState = Main;
  
  ReachStateMarker(target, markerOffset, Main == attackMarkerState, Main == attackMarkerState, GetStatePlayMode(target) ); 
}

void PFClientCreature::OnAttack( float attackTimeOffset, const CVec2& vTarget )
{
  const NWorld::PFCreature* pUnit = WorldObject();
  if ( IsValid( pUnit ) && pUnit->IsDead() )
  {
    return;
  }

  SynchronizeVisualPosition();

  LookTo( vTarget );
  Attack( attackTimeOffset );
}

void PFClientCreature::OnStartedFighting()
{
  doFireAlreadyHappened = false;
  isFighting            = true;
  attackMarkerState     = None;
	//TODO:HACK ( NUM_TASK )
	if ( WorldObject() && WorldObject()->GetAttackAbility() )
	{
		const NWorld::PFBaseAttackData* pAttack = WorldObject()->GetAttackAbility();
		if ( pAttack )
		{
			float time = pAttack->GetCurrentCooldown();
			if ( time > g_attackToIdleTime )
			{
				Stand();
				Idle();
			}
		}
	}
}

void PFClientCreature::OnFinishedFighting()
{
  doFireAlreadyHappened = false;
  isFighting            = false;
  attackMarkerState     = None;
}

void PFClientCreature::OnUseMagic(int id, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget)
{
  SynchronizeVisualPosition();

  if ( lookAtTarget != NWorld::DontLook )
  {
    LookTo( target.MakeTargetingPos().AsVec2D(), lookAtTarget == NWorld::TurnInstantly );
  }

  int const abilityId = id - NDb::ABILITY_ID_1;
  NI_VERIFY(abilityId >= 0, "Wrong ability index", return);

  NDb::EAnimStates const targetState = static_cast<NDb::EAnimStates>( NDb::ANIMSTATES_ABILITY1 + abilityId ); 
  ETargetAG const targetGraph = GetStatePlayMode(targetState);
  if( SetAnimState( targetState, targetGraph) )
  {
    if(EPS_VALUE < timeOffset)
      ReachStateMarker( targetState, timeOffset, true, GetStatePlayMode(targetState) );

		if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER != targetGraph)
			abilityAnims[abilityId] = true;

		if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != targetGraph)
			upperAbilityAnims[abilityId] = true;
	}
}

void PFClientCreature::OnUseAbility( const char* node, const char* marker, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget, bool syncVisual )
{
  if ( syncVisual )
	{
		SynchronizeVisualPosition();
	}

  if ( lookAtTarget != NWorld::DontLook )
  {
    LookTo( target.MakeTargetingPos().AsVec2D(), lookAtTarget == NWorld::TurnInstantly );
  }

  if ( NStr::Len( node ) == 0 )
  {
    return;
  }

  int const nodeId = GetStateIdByName( node );
  if ( SetTargetNode( nodeId ) )
  {
    if ( timeOffset > EPS_VALUE )
    {
      if ( NStr::Len( marker ) != 0 )
      {
        bool result = ReachStateMarker( marker, timeOffset, true );
        NI_DATA_ASSERT( result, NStr::StrFmt( "Trying to reach wrong marker ( %s )", marker ) )
      }
    }
  }
}

void PFClientCreature::OnAbilityDispatchStarted( int id )
{
  OnDispatchStarted( static_cast<NDb::EAnimStates>( NDb::ANIMSTATES_ABILITY1 + id - NDb::ABILITY_ID_1) );
}

void PFClientCreature::OnAbilityDispatchStarted( const char* marker )
{
  OnDispatchStarted( marker );
}

void PFClientCreature::OnAttackDispatchStarted()
{
  // REMINDER: need detect which attack happened: normal, critical or special
  OnDispatchStarted( NDb::ANIMSTATES_ATTACK );
  PredictAttackMarker( None | Special );
}

void PFClientCreature::OnDispatchStarted( NDb::EAnimStates state )
{
  if( NScene::SceneObject* pSO = GetSceneObject() )
  {
    ETargetAG const mode = GetStatePlayMode(state);

    string event = NDb::ANIMSTATEPLAYMODE_PLAYUPPER != mode ? GetStateMarker(state, false) : "";
    if( false == event.empty() )
      pSO->ProcessExternalEvent( event.c_str() );

    if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != mode )
    {
      string const& upper  = GetStateMarker(state, true);
      if( event != upper )
        pSO->ProcessExternalEvent( upper.c_str() );
    }
  }
}

void PFClientCreature::OnDispatchStarted( const char* marker )
{
  NScene::SceneObject* pSO = GetSceneObject();
  if( pSO && marker && ( marker[0] != '\0' ) )
  {
    pSO->ProcessExternalEvent( marker );
  }
}

bool PFClientCreature::IsAbilityAnimPlaying() const
{
#ifdef USE_ABILITY_CALLBACKS
	for( int i = 0, count = AbilitiesCount; i < count; ++i)
    if( abilityAnims[i] || upperAbilityAnims[i] )
      return true;
#endif

  return false;
}

void PFClientCreature::OnActionAnimFinished(AnimEventParams const& params)
{
  if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER == params.mode )
    upperAbilityAnims[ params.state - NDb::ANIMSTATES_ABILITY1 ] = false;
  else
    abilityAnims[ params.state - NDb::ANIMSTATES_ABILITY1 ]      = false;
  
  if ( g_UseControlInAbilityCallbacks )
  {
    if( Living == lifeState && false == IsAbilityAnimPlaying() )
    {
      if( isMove ) 
        OnStartMoving();
      else
        Idle();
    }
  }
}

void PFClientCreature::Idle(bool forced)
{
  if(forced)
    Restart(NDb::ANIMSTATES_IDLE);
  else if ( !isStunned )	
    SetAnimState(NDb::ANIMSTATES_IDLE, GetStatePlayMode(NDb::ANIMSTATES_IDLE) );
  else 
    SetAnimState( NDb::ANIMSTATES_STUN );
}

void PFClientCreature::Update( float timeDiff )
{
  NI_PROFILE_FUNCTION;

  const NWorld::PFBaseUnit *pWorldUnit = WorldObject();

  if (IsValid(pWorldUnit) && pWorldUnit->IsSleep() && DeveloperClientVisibilityHelper::CanCreatureSleep(this))
    return;

  if ( lifeState <= Dying )
  {
    UpdateMovement( timeDiff );
  }

  if ( lifeState == Living )
  {
    if ( predictMarkerPending )
    {
      PredictAttackMarker( Main );
      predictMarkerPending = false;
    }

    if ( stopAttackAnimation )
    {
      Idle();
      stopAttackAnimation = false;
    }

    if ( needUpdateStun )
    {
      needUpdateStun = false;
      
      if( isStunned )
        SetAnimState( NDb::ANIMSTATES_STUN );
      else if ( GetStateId( NDb::ANIMSTATES_STUN ) == GetCurrentStateId() )
        SetAnimState( NDb::ANIMSTATES_IDLE );
    }
  }

  if ( lifeState >= Perished )
  {
    deadTime += timeDiff;
  }
  
  if ( lifeState == Perished )
  {
    lifeState = Corpse;

		if ( GetSceneObject())
		{
			struct EffectsGroupDisabler : public NScene::TraverserByGroupFlags, private NonCopyable
			{
				EffectsGroupDisabler() : TraverserByGroupFlags( NScene::SceneComponent::GROUPFLAGS_EFFECT, true ) { }
				void operator() ( NScene::SceneComponent* sc ) { sc->EnableWeak( false ); }
			} traverser;

			GetSceneObject()->Traverse( traverser );
		}
  }

  if ( lifeState == Corpse )
  {
    if ( fallingTime > 0 )
    {
      NI_ASSERT( lifeState >= Dying, "Fall through before perish complited!" );
      NScene::SceneObject* so = GetSceneObject();
      if ( so )
      {
        CVec3 pos = so->GetPosition().pos;
        pos.z -= timeDiff * fallingSpeed;
        so->SetPosition( pos );
        so->UpdateForced( 0.0f, false, IsVisible() );
      }
      fallingTime -= timeDiff;
    }
  }

  bool gameFinished = WorldObject()->GetWorld()->GetAIWorld()->WasGameFinished();
  if ( gameFinished )
  {
    switch ( happyState )
    {
    case EHappyState::Happy:
      happyStateTimer -= timeDiff;
      if ( happyStateTimer < 0.0f )
      {
        SetHappyState( EHappyState::Resting );
        happyStateTimer = 0.0f;
      }
      break;
    case EHappyState::Resting:
      happyStateRestingTimer -= timeDiff;
      if ( happyStateRestingTimer < 0.0f )
      {
        SetHappyState( EHappyState::Ready );
        happyStateRestingTimer = 0.0f;
      }
      break;
    }
  }
  if ( !forcedAnim.empty() )
  {
    forcedAnimRestartTimer -= timeDiff;
    if ( forcedAnimRestartTimer < 0 )
    {
      unsigned int stateId = GetStateIdByName(forcedAnim.c_str());
      if (stateId != DIANGR_NO_SUCH_ELEMENT) 
        SetAnimStateId(stateId, NDb::ANIMSTATEPLAYMODE_PLAYBOTH);

      forcedAnimRestartTimer = Max( GetStateIdDuration( stateId ), 0.f );
    }
  }

  PFClientBaseMovingUnit::Update( timeDiff );
  PFAnimController::Update( timeDiff );
}

void PFClientCreature::OnEmote(NDb::EEmotion emotion)
{
  if( Living != lifeState)
    return;

  if( currentAnimSet < 0 || animSetParams.size() <= currentAnimSet )
    return;

  NDb::EAnimStates state = NDb::ANIMSTATES_INVALID;
  switch(emotion)
  {
  case NDb::EMOTION_HAPPY:
    state      = NDb::ANIMSTATES_HAPPY;
    break;
  case NDb::EMOTION_SAD:
    state      = NDb::ANIMSTATES_SAD;
    break;
  case NDb::EMOTION_HELLO:
    state      = NDb::ANIMSTATES_HELLO;
    break;
  }

  bool isUpperState = NDb::ANIMSTATES_INVALID != state && IsValidState(state, NDb::ANIMSTATEPLAYMODE_PLAYUPPER);
  bool isLowerState = NDb::ANIMSTATES_INVALID != state && IsValidState(state, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL);

  AnimSetParams const& params  = animSetParams[currentAnimSet];
  EmoParams::const_iterator it = params.emoParams.find(GetCurrentStateId());
  if( params.emoParams.end() == it )
    return; // do not have settings -> assume both emotions are prohibited

  if( it->second[emotion].first && isUpperState && SetAnimState(state, NDb::ANIMSTATEPLAYMODE_PLAYUPPER) )
    return;

  if( it->second[emotion].second && isLowerState)
    SetAnimState(state, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL);
}

void PFClientCreature::SetHappyState( EHappyState::Type _happyState )
{
  if ( !WorldObject()->GetWorld()->GetAIWorld()->WasGameFinished() )
  {
    return;
  }

  NI_VERIFY( ( ( _happyState == happyState + 1 ) || ( ( happyState == EHappyState::Resting ) && ( _happyState == EHappyState::Ready ) ) ),
    NStr::StrFmt( "Can't change happy state from %d to %d!", happyState, _happyState ), return );

  switch ( _happyState )
  {
  case EHappyState::Happy:
    happyStateTimer = GetStateDuration( NDb::ANIMSTATES_HAPPY );
    SetAnimState( NDb::ANIMSTATES_HAPPY );
    break;
  case EHappyState::Resting:
    happyStateRestingTimer = WorldObject()->GetWorld()->GetAIWorld()->GetAIParameters().creatureHappyStateParams.minRestTime;
    break;
  }

  happyState = _happyState;
}


int  PFClientCreature::GetAnimSetId( int idx )const
{
  if( 0 <= idx && idx < animSetParams.size() )
    return animSetParams[idx].setId;

  return -1;
}

void PFClientCreature::SetCommandQueueDepth(const float seconds)
{
  PFAnimController::SetCommandQueueDepth(seconds);
}


bool PFClientCreature::OnSceneObjectBecomeVisible(NScene::SceneObject& sceneObject, float /*timeBeingInvisible*/)
{
  Freeze(false, sceneObject, IsVisible() );
  return true;
}

void PFClientCreature::OnSceneObjectBecomeInvisible(NScene::SceneObject& sceneObject)
{
  Freeze(true, sceneObject);
}

void PFClientCreature::OnDoFireHappened()
{
  if( doFirePending )
  {
    doFirePending           = false;
    if( Main == attackMarkerState )
      predictMarkerPending  = true;
  }
  else
  {
    if( isFighting )
      doFireAlreadyHappened = true;
    else
      stopAttackAnimation   = true;
  }
}

void PFClientCreature::PredictAttackMarker( int const allowedStates )
{
}

float PFClientCreature::GetAttackDuration() const
{
  const float attackDuration = EPS_VALUE < attackSpeed ? 1.0f / attackSpeed : 1e+3f;
  return attackDuration;
}

void PFClientCreature::OnBecameIdle()
{
  if( false == isMove && false == IsAbilityAnimPlaying() && !isStunned )
    Idle();
}

void PFClientCreature::ForceIdle()
{
  for( int i = 0, count = AbilitiesCount; i < count; ++i)
  {
    abilityAnims[i]      = false;
    upperAbilityAnims[i] = false;
  }
  
  Idle( true );
}

void PFClientCreature::OnStunned( bool stunned )
{
  isStunned = stunned;

  // It is supposed that successive OnStunned calls during single step are incoming with alternating 'stunned' param (according to PFApplFlags logic)
  needUpdateStun = !needUpdateStun;
}

void PFClientCreature::OnFreeze( bool freezed )
{
  if( freezed )
  {
    FreezeAG();
  }
  else
  {
    UnFreezeAG();
    ForceIdle();
  }
}

float PFClientCreature::ForceAnimation( const string& anim )
{
  forcedAnim = anim;
  unsigned int stateId = GetStateIdByName(forcedAnim.c_str());
  if (stateId != DIANGR_NO_SUCH_ELEMENT) 
    SetAnimStateId(stateId, NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
  forcedAnimRestartTimer = Max( GetStateIdDuration( stateId ), 0.f);
  return forcedAnimRestartTimer;
}
void PFClientCreature::StopForcedAnimation()
{
  Idle(false);
  forcedAnim.clear();
  forcedAnimRestartTimer = 0.f;
}

int  PFClientCreature::ReplaceAnimSet( NDb::Ptr<NDb::AnimSet> pSet ) 
{
  int setId = RegisterAnimSet(pSet);
  if( 0 <= setId && ActivateAnimSet(setId))
    return setId;
  
  NI_VERIFY( UnRegisterAnimSet(setId), "Failed to unregister animSet!", );
  return -1; 
} 

bool PFClientCreature::RollbackAnimSet( int setId ) 
{
  return setId < 0 ? false : UnRegisterAnimSet(setId);
}

int  PFClientCreature::ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool affectAllSets) 
{
  const int result = PFAnimController::ReplaceAnimation(state, name, marker, upper, affectAllSets);
  if( -1 != result )
  {
#ifdef USE_ABILITY_CALLBACKS
    if( NDb::ANIMSTATES_ABILITY1 <= state && state <= NDb::ANIMSTATES_ABILITY4)
    {
      if( IsValidState(state, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL) )
      {
        RegisterAnimEvent( AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, state, AnimEventParams::ExactParam, 1.0 ), 
          CreateAnimEventCallback(this, &PFClientCreature::OnActionAnimFinished), GetCurrentSetId() );
        
        RegisterAnimEvent( AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, state, AnimEventParams::LeaveNode ), 
          CreateAnimEventCallback(this, &PFClientCreature::OnActionAnimFinished), GetCurrentSetId() );
      }
    }
#endif

    if( NDb::ANIMSTATES_DEATH == state )
    {
      RegisterAnimEvent(AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, NDb::ANIMSTATES_DEATH, AnimEventParams::ExactParam, 0.99f), 
        CreateAnimEventCallback(this, &PFClientCreature::OnDeathAnimFinished), GetCurrentSetId() );
    }
    if( NDb::ANIMSTATES_UNSUMMON == state )
    {
      RegisterAnimEvent(AnimEventParams(NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, NDb::ANIMSTATES_DEATH, AnimEventParams::ExactParam, 0.99f), 
        CreateAnimEventCallback(this, &PFClientCreature::OnDeathAnimFinished), GetCurrentSetId() );
    }
  }

  return result;
}

bool PFClientCreature::RollbackAnimation( NDb::EAnimStates state, int id, bool upper) 
{ 
  return PFAnimController::RollbackAnimation(state, id, upper); 
}


float PFClientCreature::GetCurAnimSetSurfSpeed() const
{
  if( ( currentAnimSet < 0 ) || ( animSetParams.size() <= currentAnimSet ) )
  {
    return 0.0f;
  }
  const AnimSetParams& params = animSetParams[currentAnimSet];

  return params.surfSpeed;
}

void PFClientCreature::SetCurAnimSetSurfSpeed( float speed )
{
  NI_VERIFY( speed >= 0.0f, NStr::StrFmt( "Surface speed(%f) shouldn't be negative!", speed ), return );

  if( ( currentAnimSet < 0 ) || ( animSetParams.size() <= currentAnimSet ) )
  {
    return;
  }
  AnimSetParams& params = animSetParams[currentAnimSet];

  if ( speed == params.surfSpeed )
  {
    return;
  }

  params.surfSpeed = speed;

  UpdateCurAnimSetSurfSpeedMultiplier();
}

void PFClientCreature::MultiplyAnimSpeed( float scale )
{
  float curSpeed = GetCurAnimSetSurfSpeed();
  if ( curSpeed != -1.0f )
  {
    SetCurAnimSetSurfSpeed( GetCurAnimSetSurfSpeed() * scale );
  }
}

void PFClientCreature::UpdateCurAnimSetSurfSpeedMultiplier()
{
  if( ( currentAnimSet < 0 ) || ( animSetParams.size() <= currentAnimSet ) )
  {
    return;
  }
  AnimSetParams& params = animSetParams[currentAnimSet];

  SetSurfaceSpeedMultiplier( moveSpeed / params.surfSpeed );
}

void PFClientCreature::SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc )
{
  RemoveGlowEffect();

	if( sceneObjectDesc && GetSceneObject() && pAnimSet )
	{
		GetSceneObject()->UnregisterCollisionGeometry();
		NScene::SceneObject* so = Release(pSceneObjectsHolder->GetActive());
		so->SetOwnerID( -3 );
		so->SetUpdateHook( 0 );
    nstl::string curState( GetNearestStateName() );

    pSceneObjectsHolder->SetSceneObject( sceneObjectDesc );
		pSceneObjectsHolder->Recreate( so->GetPosition(), IDLENODE );
		GetSceneObject()->RegisterCollisionGeometry( pSceneObjectsHolder->GetCollision() );
    if ( !bVisible )
    {
      if ( GetSceneObject()->GetCollision() )
        GetSceneObject()->GetCollision()->SetEnabled( false );
      if ( GetSceneObject()->GetSmallCollision() )
        GetSceneObject()->GetSmallCollision()->SetEnabled( false );
    }

		so->RemoveFromScene();

		Cleanup();
    ClearCommandQueue();
		Initialize( GetSceneObject(), &pAnimSet, 1, true, 0, false );
    unsigned stateID = GetStateIdByName( curState.c_str() );
    if ( stateID < GetNumNodes() )
    {
      SetTargetNode( stateID );
    }

    UpdateColor();
    UpdateCurAnimSetSurfSpeedMultiplier();
	}
	else
	{
		if ( sceneObjectDesc )
		{
			NI_ALWAYS_ASSERT( NStr::StrFmt("Error SetSceneObject: %s",sceneObjectDesc->GetDBID().GetFileName()) );
		}
		else
		{
			NI_ALWAYS_ASSERT( "Error SetSceneObject: NULL" );
		}
	}

  AttachGlowEffect();
}

void PFClientCreature::CreateStandaloneEffect()
{
	if( GetSceneObject() && pAnimSet && TryCreateStandaloneEffect() )
	{
		Cleanup();
		NI_VERIFY( NULL != GetSceneObject(), "Invalid scene object!", return );
		UpdateColor();
		Initialize( GetSceneObject(), &pAnimSet, 1, true, 0, false );

		PFClientBaseMovingUnit::Stand();
		if ( NDb::ANIMSTATES_UNSUMMON == deathAnimState )
			Restart( UNSUMMONEDNODE );
		else
			Restart( DEADNODE );


		if( NScene::SceneObject* pSO = GetSceneObject() )
			pSO->UpdateForced( 0.0f, false, IsVisible() );

		if( GetSceneObject() && GetSceneObject()->GetCollision() )
			GetSceneObject()->GetCollision()->SetEnabled(false);
		if( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
			GetSceneObject()->GetSmallCollision()->SetEnabled(false);
	}
}

bool PFClientCreature::IsInAttackNode() const
{
  return GetStateId( NDb::ANIMSTATES_ATTACK ) == GetNearestStateId();
}

void PFClientCreature::RemoveGlowEffect()
{
  if( IsValid( pGlowEffect ) )
  {
    pGlowEffect->Die();
    pGlowEffect = 0;
  }
}

void PFClientCreature::AttachGlowEffect()
{
  if( WorldObject()->GetFaction() == NDb::FACTION_FREEZE )
    pGlowEffect = PF_Core::EffectsPool::Get()->Retrieve(NDb::EFFECTS_GLOWEFFECTA);
  if( WorldObject()->GetFaction() == NDb::FACTION_BURN )
    pGlowEffect = PF_Core::EffectsPool::Get()->Retrieve(NDb::EFFECTS_GLOWEFFECTB);

  if( IsValid( pGlowEffect ) )
    pGlowEffect->Apply(this);
}


void  PFClientCreature::SetCinematicPause( bool pause )
{
  if ( lifeState != Living )
    return;

  if ( pause )
  {
    ClearCommandQueue();
    Freeze(false, *GetSceneObject());
    Idle();
    Freeze(true, *GetSceneObject());
  }
  else 
  {
    Freeze(false, *GetSceneObject());
    if( isMove ) 
      OnStartMoving();
    else 
      Idle();
  }
}

void PFClientCreature::SetVisibility(bool visible)
{
  using namespace NScene;
  using namespace NWorld;

  if (const PFLogicObject* const worldObject = WorldObject())
  {
    if (worldObject->GetHiddenCounter())
      visible = false;

    const bool renderable =
      (visible) ||
      (ClientVisibilityHelper::IsPartialVisibilityApplicable(worldObject) && IsPartiallyVisible());

    pSceneObjectsHolder->SetVisibility(renderable);

    if (!DoSetVisible(visible))
      return;

    if (const SceneObject* const sceneObject = GetSceneObject())
    {
      if (CollisionHull* const collision = sceneObject->GetCollision())
      {
        collision->SetEnabled(bVisible);
      }
      if (CollisionHull* const collision = sceneObject->GetSmallCollision())
      {
        collision->SetEnabled(bVisible);
      }
    }
  }
}

bool PFClientCreature::IsPartiallyVisible() const
{
  using NScene::SceneComponent;
  using NScene::SceneObject;

  struct Traverser : public NScene::TraverserByGroupFlags
  {
    enum
    {
      flagEffectIgnoreInvisibility = NDb::EFFECTGROUPFLAGS_IGNOREINVISIBILITY | NScene::SceneComponent::GROUPFLAGS_EFFECT,
    };

    unsigned count;

    Traverser()
      : TraverserByGroupFlags(flagEffectIgnoreInvisibility, true)
      , count(0)
    {
    }

    void operator()(SceneComponent* const)
    {
      ++count;
    }
  };

  // TODO: несколько SceneObject'ов?
  if (SceneObject* const sceneObject = GetSceneObject())
  {
    Traverser f;

    sceneObject->Traverse(f);

    return !!f.count;
  }

  return false;
}

} // namespace NGameX

REGISTER_DEV_VAR("anim_attack_slowdown",       g_attackAnimtionSlowDown, STORAGE_GLOBAL);
REGISTER_DEV_VAR("use_contol_in_ability_callbacks",       g_UseControlInAbilityCallbacks, STORAGE_GLOBAL );
REGISTER_DEV_VAR( "attackToIdleTime", g_attackToIdleTime, STORAGE_NONE );
