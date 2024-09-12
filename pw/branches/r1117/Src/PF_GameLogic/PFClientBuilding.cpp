#include "stdafx.h"

#include "AdventureScreen.h"
#include <Scene/AnimatedSceneComponent.h>
#include "PFClientBuilding.h"
#include "../PF_Core/EffectsPool.h"
#include "PFAIWorld.h"

#include "PFClientObjectHelpers.h"
#include "PFClientSceneObjectsHolders.h"

#include "../System/InlineProfiler.h"

//#define DEBUG_BUILDING_TARGETING

#ifdef DEBUG_BUILDING_TARGETING
# include "../Render/debugrenderer.h"
#endif

#include "Minimap.h"


namespace
{
  static float s_forceBuildingsMinHealthExplosionPercent  = 0.0f; // минимальное кол-во хп, начиная с которого будем гореть (в процентах)
  static float s_forceBuildingsFragEffectProbability      = 0.0f; // вероятность вылета осколка из здания

  #define EXPL_COMPONENT_ID "fire"
  #define FRAG_LOCATOR_ID   "Frag"

  #define GET_AI_PARAM(param, forced) ( forced > 0 ? forced : WorldObject()->GetWorld()->GetAIWorld()->GetAIParameters().param )
}

namespace
{
  inline bool IsExplosionComponent(const string& id) { return id.length() > 4 && !strncmp(id.c_str(), EXPL_COMPONENT_ID, 4); }
  inline bool IsFragLocator(const string& id) { return id.length() > 4 && !strncmp(id.c_str(), FRAG_LOCATOR_ID, 4); }
  
  typedef bool (*ComponentUpdaterPredicate)(const string&);
  
  struct ComponentVisibilityUpdater : public NScene::FullTraverser, private NonCopyable
  {
    int affectedComponents;
    ComponentVisibilityUpdater(ComponentUpdaterPredicate pred, bool visibility) : predicate(pred), visibility(visibility), affectedComponents(0) {}
    void operator()(NScene::SceneComponent* pComponent)
    {
      if ( (*predicate)( pComponent->GetId() ) )
      {
        pComponent->EnableWeak(visibility);
        ++affectedComponents;
      }
    }
  private:
    ComponentUpdaterPredicate predicate;
    bool visibility;
  };

  //////////////////////////////////////////////////////////////////////////
  int GetFragLocatorsCount(NScene::SceneObject* pSceneObject)
  {
    struct Func
    {
      int count;

      Func() : count(0) {}

      void operator() (NScene::Locator const &l)
      {
        if ( IsFragLocator(l.locator.name) )
          ++count;
      }
    } f;

    pSceneObject->ForAllLocators(f);
    return f.count;
  }

  //////////////////////////////////////////////////////////////////////////
	inline float GetRnd(float min_, float max_) { return min_ + (float(rand())/float(RAND_MAX)) * (max_ - min_); }
  
  //////////////////////////////////////////////////////////////////////////
  NDb::EEffects GetFragEffectId( NDb::EFaction faction )
  {
    return  faction == NDb::FACTION_NEUTRAL ? NDb::EFFECTS_EMPTY :
            faction == NDb::FACTION_FREEZE  ? NDb::EFFECTS_ONDAMAGEFRAGTEAMA :
                                              NDb::EFFECTS_ONDAMAGEFRAGTEAMB;
  }
  
  NDb::EEffects GetDestructEffectId( NDb::EFaction faction )
  {
    return  faction == NDb::FACTION_NEUTRAL ? NDb::EFFECTS_EMPTY :
            faction == NDb::FACTION_FREEZE  ? NDb::EFFECTS_ONBUILDINGDESTRUCTTEAMA:
                                              NDb::EFFECTS_ONBUILDINGDESTRUCTTEAMB;
  }

} // noname namespace

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBuilding::PFBuilding(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject)
	: PFClientBaseUnit( pWO, cp, gameObject )
  , state(State_Normal)
  , turnedOnExplEffects(0)
  , fragLocatorsCount(0)
  , showRuinDelay(0.0f)
  , pRuinLocator(NULL)
  , updateUnderWarfog(false)
  , pAG(NULL)
{
	NI_ASSERT( dynamic_cast<const NDb::Building*>( gameObject ), "Bad cast to NDb::Building!" )
	const NDb::Building* pDBDesc = static_cast<const NDb::Building*>( gameObject );

	// Preload buildings
	NGameX::AdventureScreen::Instance()->PreloadEffectsInResourceTree(NDb::Ptr<NDb::DbResource>(gameObject), BADNODENAME);

	onDamageFragEffect = pDBDesc->onDamageFragEffect;
  onDestructionEffect = pDBDesc->onDestructionEffect;

  NScene::SceneObject* pSO = GetSceneObject();
  
  ComponentVisibilityUpdater explosionsDisabler( IsExplosionComponent, false );
  pSO->Traverse( explosionsDisabler );
  explCompsCount = explosionsDisabler.affectedComponents;
  
  if ( pDBDesc->ruinSceneObject )
  {
    pRuinSceneObject = MakeSceneObject( *pDBDesc->ruinSceneObject, pSO->GetPosition(), BADNODENAME );
    showRuinDelay = pDBDesc->showRuinDelay;
  }

  pRuinLocator = pSO->FindLocator( pDBDesc->ruinLocator.c_str() );
  
  fragLocatorsCount = GetFragLocatorsCount( pSO );

  if ( pSO && gameObject->heightObject )
  {
    // Process scene object
    struct Func : public Render::IMaterialProcessor
    {
      virtual void operator()(Render::BaseMaterial &material)
      {
        if(NDb::MATERIALPRIORITY_MESHESOPAQUE == material.GetPriority())
          material.SetPriority(NDb::MATERIALPRIORITY_TERRAINOBJECTS);
      }
    } f;

    NScene::ForAllMaterials( *GetSceneObject(), f );
  }

  NScene::AnimatedSceneComponent* pAnimatedRoot = pSO ? dynamic_cast<NScene::AnimatedSceneComponent *> (pSO->GetRootComponent()): NULL;
  pAG = pAnimatedRoot ? pAnimatedRoot->GetMainAnimGraph() : NULL;

  updateUnderWarfog = pDBDesc->updateUnderWarfog;
}

PFBuilding::~PFBuilding()
{
}

void PFBuilding::Hide(bool hide)
{
  static CPtr<NScene::IScene> pOldScene;

  if ( NScene::SceneObject * pSceneObject = GetSceneObject() )
  {
    if (pSceneObject->IsInScene())
    {
      if (hide)
      {
        pOldScene = pSceneObject->GetScene();
        pSceneObject->RemoveFromScene();
      }
    }
    else
    {
      if (!hide && IsValid(pOldScene))
      {
        pSceneObject->AddToScene(pOldScene);
      }
    }

    if ( IsVisible() || hide )
    {
      if ( pSceneObject->GetCollision() )
        pSceneObject->GetCollision()->SetEnabled(!hide);
      if ( pSceneObject->GetSmallCollision() )
        pSceneObject->GetSmallCollision()->SetEnabled(!hide);
    }
  }
}


void PFBuilding::OnDamage(float health, float damage)
{
  PFClientBaseUnit::OnDamage(health, damage);
  if ( bVisible )
  {
    ApplyHealthEffects();
    ShowFragEffect();
  }
}

void PFBuilding::OnHeal( float health, float delta )
{
  if ( bVisible )
  {
    ApplyHealthEffects();
  }
}


void PFBuilding::SetVisibility(bool _bVisible)
{
  if ( !updateUnderWarfog && !DoCheckVisible(_bVisible) )
  {
    if ( NScene::SceneObject* pSceneObject = GetSceneObject() )
    {
      // Freeze/unfreeze animation of scene object
      pSceneObject->SetFreeze( !_bVisible );
      
      // Enable/disable all effects components
      struct EffectSwitcher : public NScene::TraverserByGroupFlags
      {
        bool enable;
        EffectSwitcher(bool enable) : NScene::TraverserByGroupFlags(NScene::SceneComponent::GROUPFLAGS_EFFECT, true), enable(enable) {}
        void operator()( NScene::SceneComponent* comp ) const {
          comp->EnableWeak(enable);
        }
      } visibilityUpdater(_bVisible);
      
      pSceneObject->Traverse(visibilityUpdater);
    }
    // Apply health effects if become visible
    if (_bVisible)
      ApplyHealthEffects();
  }
  PFClientBaseUnit::SetVisibility(_bVisible);
}

void PFBuilding::OnUnitDie()
{
  if (state < State_Dying)
  {
    state = State_Dying;
    if ( bVisible && GetSceneObject() )
    {
      ShowOnDestructionEffect();
      ApplyHealthEffects();
    }
    else
      showRuinDelay = 0.0f;
  }
}

void PFBuilding::ApplyHealthEffects()
{
  if ( state == State_Normal ) // apply on damage effect
  {
    if ( explCompsCount > 0 )
    {
      const NWorld::PFBaseUnit *pWorldObject = WorldObject();
      NI_ASSERT( IsValid(pWorldObject), "Invalid World Object!!" );

      float healthPercents = 100.0f * pWorldObject->GetHealthPercent();
      float minHealthExplosionPercent = GET_AI_PARAM(buildingsMinHealthExplosionPercent, s_forceBuildingsMinHealthExplosionPercent);

      if ( healthPercents > 0.0f )
      {
        // get number of enabled components effects
        int x = 1 + static_cast<int>( (minHealthExplosionPercent - healthPercents) * static_cast<float>(explCompsCount) / minHealthExplosionPercent );
        SetHealthEffectsNumber(x);
      }
    }
  }
  
  if ( state == State_Dying )
  {
    SwitchModel();

    state = State_Died;
  }
  
  if ( state == State_Died ) // Apply die effect
  {
    if ( showRuinDelay < EPS_VALUE  )
    {
      // show ruin object
      if ( GetSceneObject() )
        GetSceneObject()->AddToScene(pScene);

      state = State_Ruin;
    }
  }
}

void PFBuilding::SwitchModel()
{
  if ( pRuinSceneObject && GetSceneObject() && pRuinLocator )
  {
    Placement placement;
    pRuinLocator->CalculateWorldPlacement( placement );
    pRuinSceneObject->SetPlacement( placement );
    scalePermanent = placement.scale;
  }
  // Hide main model
  // Remove normal scene object from scene
  if ( GetSceneObject() )
  {
    GetSceneObject()->Deinit();
    GetSceneObject()->RemoveFromScene();
  }

  // Replace it with ruin object
  pSceneObjectsHolder->GetActive() = pRuinSceneObject;

  // Remove collision from scene
  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
  {
    GetSceneObject()->UnregisterCollisionGeometry();
  }
}

void PFBuilding::MakeRuined()
{
  SwitchModel();

  // show ruin object
  if ( GetSceneObject() )
    GetSceneObject()->AddToScene(pScene);

  state = State_Ruin;
}

void PFBuilding::Update( float timeDiff )
{
  NI_PROFILE_FUNCTION

  PFClientBaseUnit::Update( timeDiff );

  if ( state == State_Died && showRuinDelay > 0.0f )
  {
    showRuinDelay -= timeDiff;
    if ( bVisible && showRuinDelay < EPS_VALUE && GetSceneObject() )
      ApplyHealthEffects();
  }

  // update not visible buildings only if required by db data!!!!!
  if ( updateUnderWarfog && GetSceneObject() && !GetSceneObject()->IsVisible() )
    GetSceneObject()->Update( timeDiff, true );
}

bool PFBuilding::IsVisibleOnMinimap() const
{
  const NWorld::PFBuilding *pWorldUnit = WorldObject();

  if ( !IsValid( pWorldUnit ) )
    return bVisible;

  if ( pWorldUnit->CheckFlag( NDb::UNITFLAG_ISOLATED | NDb::UNITFLAG_INVISIBLE ) )
    return false;

  switch ( pWorldUnit->GetUnitType() )
  {
  case NDb::UNITTYPE_TOWER:
  case NDb::UNITTYPE_MAINBUILDING:
    return true;

  case NDb::UNITTYPE_SHOP:
    if ( pWorldUnit->GetFaction() == NDb::FACTION_NEUTRAL )
      return true;
    else
      return bVisible;

  case NDb::UNITTYPE_BUILDING:
    if ( IsValid( pWorldUnit->GetAdvMapObjectCopy().gameObject ) )
    {
      if ( pWorldUnit->GetAdvMapObjectCopy().gameObject->GetObjectTypeID() == NDb::Quarter::typeId )
        return true;
    }

    break;
  }

  return bVisible; 
}

void PFBuilding::UpdateMinimap() const
{
  static DI_WEAK(NGameX::Minimap) minimap;

  if (!IsValid(minimap))
    return;

  if (!IsVisibleOnMinimap())
    return;

  const NWorld::PFBuilding* const pWorldUnit = WorldObject();

  if (!pWorldUnit)
    return;
  if (pWorldUnit->IsDead())
    return;

  // TODO: dynamic_cast could be replaced with static_cast and typeId check
  if (const NDb::Building* const dbBuilding = dynamic_cast<const NDb::Building*>(pWorldUnit->DbUnitDesc()))
    minimap->AddObject(pWorldUnit, pWorldUnit->GetMinimapIcon(), CVec3(dbBuilding->minimapIconOffset, 0.0f));
  else
    minimap->AddObject(pWorldUnit, -1);
}

void PFBuilding::ShowFragEffect()
{
	using namespace PF_Core;

	if ( !GetWorldObject() || !fragLocatorsCount || (GetRnd(0.0f, 1.0f) > GET_AI_PARAM(buildingsFragEffectProbability, s_forceBuildingsFragEffectProbability)) )
    return;

  int locatorIndex = GetRnd( 1.0f, (float)fragLocatorsCount + 0.99f ); //0.99f делается чтобы fragLocatorsCount выпадало с такой же вероятностью как и остальные 
  const NScene::Locator* pLocator = GetSceneObject()->FindLocator( NStr::StrFmt( FRAG_LOCATOR_ID"%i", locatorIndex ) );
  NI_VERIFY( pLocator, NStr::StrFmt("Locator "FRAG_LOCATOR_ID"%i should present", locatorIndex), return; );

  CObj<BasicEffectStandalone> effect = 
		onDamageFragEffect ? EffectsPool::Get()->RetrieveKnownEffect<BasicEffectStandalone>( onDamageFragEffect )
                       : EffectsPool::Get()->RetrieveKnownEffect<BasicEffectStandalone>( GetFragEffectId( WorldObject()->GetFaction() ) );
  if ( effect )
  {
		Placement pl;
		GetSceneObject()->CalculateLocatorWorldPlacement(*pLocator, pl);
    effect->SetPosition(pl);
    effect->AddToScene(pScene);
  }
}

void PFBuilding::ShowOnDestructionEffect()
{
	using namespace PF_Core;

  if ( !NWorld::IsObjectValid(GetWorldObject()) )
    return;
  
  CObj<BasicEffectStandalone> effect = 
		onDestructionEffect ? EffectsPool::Get()->Retrieve<BasicEffectStandalone>( onDestructionEffect )
                        : EffectsPool::Get()->RetrieveKnownEffect<BasicEffectStandalone>( GetDestructEffectId( WorldObject()->GetFaction() ) );
  if ( effect && GetSceneObject() )
  {
    effect->Apply( GetSceneObject() );
  }
}

void PFBuilding::SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc )
{
	if ( sceneObjectDesc )
	{
		NI_ALWAYS_ASSERT( NStr::StrFmt("Error SetSceneObject for building: %s", sceneObjectDesc->GetDBID().GetFileName()) );
	}
	else
	{
		NI_ALWAYS_ASSERT( "Error SetSceneObject for building: NULL" );
	}
}

void PFBuilding::SetHealthEffectsNumber( int newEffectsCount )
{
  newEffectsCount = Clamp(newEffectsCount, 0, explCompsCount);

  if (turnedOnExplEffects < newEffectsCount)
  {
    // Turn on some new explosion effects
    for( int index = turnedOnExplEffects; index < newEffectsCount; ++index)
    {
      struct TurnOnFireEffect : public NScene::TraverserById
      {
        TurnOnFireEffect(const char* id) : TraverserById(id) {}
        void operator()( NScene::SceneComponent* comp ) { comp->EnableWeak(true); }
      } traverser( NStr::StrFmt(EXPL_COMPONENT_ID"%i", index + 1) );

      GetSceneObject()->Traverse(traverser);
    }
  }
  else if ( turnedOnExplEffects > newEffectsCount )
  {
    // Turn off some explosion effects
    for( int index = turnedOnExplEffects; index >= newEffectsCount; --index)
    {
      struct TurnOffFireEffect : public NScene::TraverserById
      {
        TurnOffFireEffect(const char* id) : TraverserById(id) {}
        void operator()( NScene::SceneComponent* comp ) { comp->EnableWeak(false); }
      } traverser( NStr::StrFmt(EXPL_COMPONENT_ID"%i", index + 1) );

      GetSceneObject()->Traverse(traverser);
    }
  }
  turnedOnExplEffects = newEffectsCount;
}

unsigned PFBuilding::GetCurrentStateId() const
{
  return pAG ? pAG->GetCurNodeUnsafe() : DIANGR_NO_SUCH_ELEMENT;
}

unsigned PFBuilding::GetNextStateId() const
{
  return pAG ? pAG->GetNextNode() : DIANGR_NO_SUCH_ELEMENT;
}

unsigned PFBuilding::GetStateIdByName(char const* name) const
{
  return pAG ? pAG->GetNodeIDByNameSlowQuite(name) : DIANGR_NO_SUCH_ELEMENT;
}

unsigned PFBuilding::GetNumNodes() const
{
  return pAG ? pAG->GetNumNodes() : 0;
}

bool PFBuilding::SetAnimStateId(unsigned int nodeId)
{
  if (DIANGR_NO_SUCH_ELEMENT != nodeId && NULL != pAG)
    return pAG->SetTargetNode(nodeId);

  return false;
}

bool PFBuilding::ReachStateMarker(char const* sMarker, float time, bool preferShortestPath, bool preferDefaultNextNode)
{
  if (pAG)
    return pAG->ReachMarkerByTime(sMarker, static_cast<int>(time * 1e+3f), preferShortestPath, preferDefaultNextNode );
  return false;
}

void PFBuilding::SetAnimState( string animStateName, bool skipAnimTransaction )
{
  unsigned int stateId = GetStateIdByName( animStateName.c_str() );

  NI_VERIFY( stateId != DIANGR_NO_SUCH_ELEMENT, NStr::StrFmt("Bad animation name '%s'", animStateName.c_str()), return );

  bool res = SetAnimStateId( stateId );

  if ( res && GetSceneObject() )
  {
    // It is more correct to calc total transaction time. But it is seems currently impossible. So we pass 100 secs.
    GetSceneObject()->UpdateForced( skipAnimTransaction ? 100 : 0.1f, skipAnimTransaction );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBattleBuilding::AnimatedData::AnimatedData()
  : ids(NULL)
  , pAG(NULL)
  , statesCount(0)
{
}

PFBattleBuilding::AnimatedData::~AnimatedData()
{
  Reset();
}

void PFBattleBuilding::AnimatedData::Reset()
{
  SAFE_DELETE_ARRAY(ids);
  pAG         = NULL;
  statesCount = 0;
}

void PFBattleBuilding::AnimatedData::Init(DiAnimGraph* pAG, char const** stateNames, const int count)
{
  Reset();
  if( 0 == count || NULL == pAG || NULL == stateNames )
    return;

  this->pAG   = pAG;
  ids         = new DiUInt32[count];
  statesCount = count;
  for( int i = 0; i < count; ++i)
    ids[i] = pAG->GetNodeIDByNameSlowQuite( stateNames[i] );
}

PFBattleBuilding::PFBattleBuilding(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject)
	: PFBuilding(pWO, cp, pScene, gameObject)
  , pTurret(NULL)
  , pBase(NULL)
  , turretPitch(0.0f)
  , turretRoll(0.0f)
  , baseRotation(0.0f)
  , currentRotation(0.0f)
  , targetRotation(0.0f)
{
  NScene::SceneObject* pSO = GetSceneObject();
  
  pBase                    = pSO   ? pSO->GetRootComponent() : NULL;
  pTurret                  = pBase ? pBase->GetChild() : NULL;

  if( pTurret )
  {
    float dummy = 0.0f;
    pTurret->GetPlacement().rot.DecompEulerAngles( &dummy, &turretPitch, &turretRoll );
		cp.placement->GetPlace().rot.DecompEulerAngles( &baseRotation, &dummy, &dummy );
  }
}

void PFBattleBuilding::OnRotationChanged( float angle, bool forced )
{
  RotateTurret( forced ? angle : targetRotation );
  targetRotation = NormalizeAngle( angle );
}

void PFBattleBuilding::RotateTurret(float angle)
{
  if( pTurret )
  {
    Placement placement    = pTurret->GetOriginalPlacement();

    const bool changed = currentRotation != NormalizeAngle( angle );
    changed;

    const float result = NormalizeAngle( angle - baseRotation );
    placement.rot.FromEulerAngles( result, turretPitch, turretRoll);
    pTurret->SetPlacement(placement);
  }

  currentRotation = NormalizeAngle( angle );
}

void PFBattleBuilding::Update( float timeDiff )
{
  float delta = targetRotation - currentRotation;

  if( fabs(delta + FP_2PI) < fabs(delta) )
    delta += FP_2PI;
  if( fabs(delta - FP_2PI) < fabs(delta) )
    delta -= FP_2PI;

  float rotation =  timeDiff * delta / 0.1f;
  rotation += currentRotation;

  RotateTurret( NormalizeAngle(rotation) );

  PFBuilding::Update(timeDiff);

#ifdef DEBUG_BUILDING_TARGETING
  NWorld::PFBattleBuilding* pWO = WorldObject();

  CVec3 pos    = pWO->GetPosition();
  CVec3 offset = CVec3( cos( NormalizeAngle( targetRotation - baseRotation ) ), sin( NormalizeAngle( targetRotation - baseRotation ) ), 0.0f );

  Render::DebugRenderer::DrawLine3D(pos, pos + offset * 10.0f, Render::Color(255, 0, 0, 255), Render::Color(255, 0, 0, 255), false );

  offset = CVec3( cos( NormalizeAngle( currentRotation - baseRotation ) ), sin( NormalizeAngle( currentRotation - baseRotation ) ), 0.0f );
  Render::DebugRenderer::DrawLine3D(pos, pos + offset * 10.0f, Render::Color(0, 0, 255, 255), Render::Color(0, 0, 255, 255), false );
#endif
}

bool PFBattleBuilding::SetAnimState( int target, EAnimTarget part, float* nodeDuration)
{
  bool result = true;

  if( !bVisible )
  {
    TCommandQueue::iterator pCmd = commandQueue.insert(commandQueue.end(), AGCommand() );

    pCmd->type = AGCommand::CT_SetState;
    pCmd->targetNode = target;
    pCmd->part = part;
    pCmd->time = pScene ? pScene->GetRenderTime() : -1.0f;

    if ( nodeDuration )
    {
      bool canCalcDuration = ( NULL != base.pAG && DIANGR_NO_SUCH_ELEMENT != base.ids[target] && base.statesCount > target );
      if ( canCalcDuration )
      {
        *nodeDuration = base.pAG->GetNodeDuration( base.ids[target] );
      }
    }

    return true;
  }


  if( Turret != part )
  {
    result  = ( NULL != base.pAG && DIANGR_NO_SUCH_ELEMENT != base.ids[target] && base.statesCount > target );
    if ( result )
    {
      result = static_cast<bool>( base.pAG->SetTargetNode( base.ids[target] ) );
      if ( nodeDuration )
        *nodeDuration = base.pAG->GetNodeDuration( base.ids[target] );
    }
  }

  if( Base != part )
    result &= ( NULL == turret.pAG || DIANGR_NO_SUCH_ELEMENT == turret.ids[target] || turret.statesCount <= target ) ? false : 
      static_cast<bool>( turret.pAG->SetTargetNode( turret.ids[target] ) );

  return result;
}

bool PFBattleBuilding::ReachMarker( string const& marker, const float time, EAnimTarget part)
{
  bool result = true;

  if( !bVisible )
  {
    TCommandQueue::iterator pCmd = commandQueue.insert(commandQueue.end(), AGCommand() );

    pCmd->type = AGCommand::CT_ReachMarker;
    pCmd->part = part;
    pCmd->marker = marker;
    pCmd->timeOffset = time;
    pCmd->time = pScene ? pScene->GetRenderTime() : -1.0f;

    return true;
  }

  if( Turret != part )
    result  = NULL ==  base.pAG  ? false : base.pAG->ReachMarkerByTime(marker, static_cast<int>(time * 1e+3) );

  if( Base != part )
    result &= NULL == turret.pAG ? false : turret.pAG->ReachMarkerByTime(marker, static_cast<int>(time * 1e+3) );

  return result;
}

void PFBattleBuilding::AttackInternal(float attackTimeOffset, CVec2 const& target, char const* marker, int stateId)
{
  if( attackTimeOffset < EPS_VALUE )
  {
//    string objectDesc = 
//#ifdef _SHIPPING
//      "unknown";
//#else
//      WorldObject()->GetDebugDescription();
//#endif
//    string error = NStr::StrFmt("Too small time offset <%.3f seconds> calculated as ( attackTimeOffset / attackSpeed ) and rounded to WorldStep is too small for animated character <%s>: check attackSpeed ( value of stat <%s> ) and attackTimeOffset!", attackTimeOffset, objectDesc.c_str(), NDb::KnownEnum<NDb::EStat>::ToString(NDb::STAT_ATTACKSPEED) );
//    systemLog( NLogg::LEVEL_DEBUG ) << error.c_str() << endl;

    SetAnimState( stateId );
  }
  else
    ReachMarker(marker, attackTimeOffset);
}

void PFBattleBuilding::SetVisibility( bool _bVisible )
{
  if (DoCheckVisible(_bVisible))
    return;

  PFBuilding::SetVisibility( _bVisible );

  if ( !bVisible )
  {
    TCommandQueue::iterator pCmd = commandQueue.insert(commandQueue.end(), AGCommand() );

    pCmd->type       = AGCommand::CT_Nope;
    pCmd->time       = pScene ? pScene->GetRenderTime() : -1.0f;

    return;
  }

  if( pScene == 0 || GetSceneObject() == 0 )
    return;

  const NScene::Time currentTime = pScene->GetRenderTime();
  for( TCommandQueue::iterator it = commandQueue.begin(), end = commandQueue.end(); it != end; ++it)
  {
    TCommandQueue::iterator next(it);
    ++next;

    const float dt = ( end == next ? currentTime : next->time ) - it->time; 
    bool ok        = false;

    if( AGCommand::CT_SetState    == it->type )
      ok = SetAnimState(it->targetNode, it->part);
    else if( AGCommand::CT_ReachMarker == it->type )
      ok = ReachMarker(it->marker, it->timeOffset, it->part);
    else if ( AGCommand::CT_Nope == it->type )
    {
      ok = true;
    }
    else
    {
      NI_ALWAYS_ASSERT("Invalid command type!");
    }

    GetSceneObject()->ResetTimeBeingInvisible();
    GetSceneObject()->UpdateForced( dt, true );
  }

  commandQueue.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFTower::PFTower(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject)
: PFBattleBuilding(pWO, cp, pScene, gameObject)
{
  char const* animStates[EAnimStatesCount] = { "idle", "attack" };

  if( NScene::AnimatedSceneComponent* pAnimated = dynamic_cast<NScene::AnimatedSceneComponent*>(pBase) )
    base.Init(pAnimated->GetMainAnimGraph(), animStates, DIM(animStates) );

  if( NScene::AnimatedSceneComponent* pAnimated = dynamic_cast<NScene::AnimatedSceneComponent*>(pTurret) )
    turret.Init(pAnimated->GetMainAnimGraph(), animStates, DIM(animStates) );

  SetAnimState( Idle );
}

void PFTower::OnAttack(float attackTimeOffset, CVec2 const& target)
{
  AttackInternal(attackTimeOffset, target, "doFire", Attack);
}

void PFTower::OnUnitDie()
{
  NGameX::AdventureScreen::Instance()->OnTowerDie();
  PFBattleBuilding::OnUnitDie();
}

void PFTower::OnTargetAssigned()
{
  bool isAlly = (WorldObject()->GetFaction() != NGameX::AdventureScreen::Instance()->GetPlayerFaction());

  NDb::EEffects effect;

  if ( isAlly )
  {
    effect = NDb::EFFECTS_TOWERATTACKEFFECTALLY;
  }
  else
  {
    effect = NDb::EFFECTS_TOWERATTACKEFFECTENEMY;
  }

  NScene::SceneObject* sceneObj = WorldObject()->GetCurrentTarget()->GetClientSceneObject();
  if ( sceneObj )
  {
    if ( !towerAttackEffect )
    {
      CreateTowerAttackEffect( effect, sceneObj );
    }
    else if ( towerAttackEffect && towerAttackEffect->GetSceneObject() != sceneObj )
    {
      towerAttackEffect->Die();
      CreateTowerAttackEffect( effect, sceneObj );
    }
  }
}

void PFTower::CreateTowerAttackEffect( NDb::EEffects effect, NScene::SceneObject* sceneObj )
{
  if ( NDb::SessionRoot::GetRoot()->visualRoot->effects->effectsList[ effect ] )
  {
    towerAttackEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>( effect );
    
    towerAttackEffect->SetDeathType( NDb::EFFECTDEATHTYPE_MANUAL );
    towerAttackEffect->Attach( sceneObj );
    sceneObj->UpdateForced();
  }
}

void PFTower::OnTargetDropped()
{
  if ( towerAttackEffect )
  {
    towerAttackEffect->Die();
    towerAttackEffect = 0;
  }
}

PFClientMainBuilding::PFClientMainBuilding(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject)
: PFBattleBuilding(pWO, cp, pScene, gameObject)
, onDie( 0.0f )
, isDying( false )
{
  char const* animStates[EAnimStatesCount] = { "idle", "activate", "deactivate", "battleidle", "attack", "attackMelee", "attackAOE", "death" };

  if( NScene::AnimatedSceneComponent* pAnimated = dynamic_cast<NScene::AnimatedSceneComponent*>(pBase) )
    base.Init(pAnimated->GetMainAnimGraph(), animStates, DIM(animStates) );

  if( NScene::AnimatedSceneComponent* pAnimated = dynamic_cast<NScene::AnimatedSceneComponent*>(pTurret) )
    turret.Init(pAnimated->GetMainAnimGraph(), animStates, DIM(animStates) );

  SetAnimState( Idle );
}

void PFClientMainBuilding::OnActivate(bool activate)
{
  SetAnimState( activate ? Activate : Deactivate );
}

void PFClientMainBuilding::OnActivated(bool activated)
{
}

void PFClientMainBuilding::OnAttack(float attackTimeOffset, CVec2 const& target)
{
  static char const* markers[] = { "doFire", "doFireMelee", "doFireAOE" };

  int type = WorldObject()->GetSelectedAttack();
  AttackInternal(attackTimeOffset, target, markers[type], AttackRange + type);
}

void PFClientMainBuilding::OnUnitDie()
{
  SetAnimState( Death, Both, &onDie );
  isDying = true;
}

void PFClientMainBuilding::Update( float timeDiff )
{
  PFBattleBuilding::Update( timeDiff );
  if ( isDying )
  {
    onDie -= timeDiff;
    if ( onDie < 0 )
    {
      isDying = false;
      onDie = 0.0f;
      UpdateVisibility();
      PFBuilding::OnUnitDie();
    }
  }
}

}

REGISTER_DEV_VAR("buildings_force_frag_effect_prob", s_forceBuildingsFragEffectProbability, STORAGE_NONE);
REGISTER_DEV_VAR("buildings_force_min_health_expl_percent", s_forceBuildingsMinHealthExplosionPercent, STORAGE_NONE);