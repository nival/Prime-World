#include "stdafx.h"
#include "PFAnimController.h"
#include "../Scene/DiAnGr.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../System/RandomGen.h"

#include "../System/InlineProfiler.h"

#include "Client/MainTimer.h"

namespace 
{

static const float MAX_ANIM_DURATION_IN_GAME = 10.0f; // Максимальная длина анимации в игре
static const int MAX_COMMANDS_IN_QUEUE_ASSERT = 100; // Ассертить, если накопилось столько команд для AG
static int s_ag_commands_check_size = 99; // Количество команд, после которого начинаются попытки чистки очереди команд

DiAnimGraph* FindAnimGraph( NScene::SceneComponent* pRoot )
{
  DiAnimGraph* pResult = NULL;
  if ( pRoot )
  {
    NScene::SceneComponent* it = pRoot;
    do
    {
      if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
        pResult = asc->GetMainAnimGraph();
      it = it->GetBrother();
    } while ( it && it != pRoot && !pResult );
  }
  return pResult;
}

DiAnGrExtPars* FindExtPars( NScene::SceneComponent* pRoot, bool mainParams )
{
  DiAnGrExtPars* pResult = NULL;
  if ( pRoot )
  {
    NScene::SceneComponent* it = pRoot;
    do
    {
      if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
        pResult = mainParams ? asc->GetExtPars() : asc->GetAdditionalExtPars();
      it = it->GetBrother();
    } while ( it && it != pRoot && !pResult );
  }
  return pResult;
}

template<typename TLinker>
TLinker* CreateLinker(DiAnimGraph* pAG, NDb::AnimSet const* pAnimSet, bool upper)
{
  if( NULL == pAG )
  {
    NI_ALWAYS_ASSERT("Can`t create nodeLinker: no AnimGraph provided!");
    return NULL;
  }

  if( NULL == pAnimSet )
  {
    NI_ALWAYS_ASSERT("Can`t create nodeLinker: no AnimSet provided!");
    return NULL;
  }

  TLinker* pLinker = new TLinker(pAG, NDb::KnownEnum<NDb::EAnimStates>::SizeOf());
  for(int i = NDb::ANIMSTATES_INVALID + 1, count = NDb::KnownEnum<NDb::EAnimStates>::SizeOf(); i < count; ++i)
    pLinker->CreateLink(static_cast<NDb::EAnimStates>(i), upper ? pAnimSet->states[i].upperNode : pAnimSet->states[i].commonNode );

  return pLinker;
}

bool operator == (NGameX::AnimEventParams const& l, NGameX::AnimEventParams const& r)
{
  return l.type == r.type && l.state == r.state && l.sValue == r.sValue && l.mode == r.mode && fabs(l.fValue - r.fValue) < EPS_VALUE && l.nodeId == r.nodeId;
}

bool operator != (NGameX::AnimEventParams const& l, NGameX::AnimEventParams const& r)
{
  return !(l== r);
}

};

namespace NGameX
{

AnimEvent::AnimEvent(AnimEventParams const& params, DiUInt32 nodeId, PFAnimController* pController, IAnimEventCallback* pCallBack, int setId)
  : params(params)
  , pController(pController)
  , pCallBack(pCallBack)
  , setId(setId)
{
  this->params.nodeId = nodeId;
}

void AnimEvent::Trigger()
{
  if( NULL != pController && pController->GetCurrentSetId() == setId && NULL != pCallBack )
    (*pCallBack)(params);
}

bool AnimEvent::operator == ( AnimEvent const& other) const
{
  if( params != other.params || pController != other.pController || setId != other.setId )
    return false;
  
  if( NULL == pCallBack )
    return pCallBack != other.pCallBack;

  return pCallBack->IsEqualTo( other.pCallBack );
}


void PFAnimController::AnimSet::Reset()
{
  for(int i = 0, count = NDb::KnownEnum<NDb::EAnimStates>::sizeOf; i < count; ++i)
  {
    markers[i]             = "";
    upperMarkers[i]        = "";
    permissions[i]         = NDb::ANIMSTATEPLAYMODE_PLAYBOTH;
  } 

  animEvents.clear();

  ::Reset(pLinker, NULL);
  ::Reset(pUpperLinker, NULL);

  nodesBaseSpeedInfo.clear();
  surfaceSpeedMultiplier = 1.0f;

  isValid = false;
}


PFAnimController::PFAnimController()
  : pIScene(NULL)
  , pAG( NULL )
  , pUpperAG(NULL)
  , pAGBlender( NULL )
  , pAGExtParams( NULL )
  , pUpperAGExtParams( NULL )
  , activeAnimSet( -1 )
  , freezed(false)
  , queueTimeDepth(0.0f)
  , firstUpdateTime(-1.f)
{
}

bool PFAnimController::Initialize( NScene::SceneObject* pSceneObject, bool _isHero )
{
  NI_PROFILE_FUNCTION

  NScene::SceneComponent* pSceneComponent = pSceneObject ? pSceneObject->GetRootComponent() : NULL;

  NI_VERIFY(pSceneObject,    "Invalid scene object!",    return false; )
  NI_VERIFY(pSceneComponent, "Invalid scene component!", return false; );

  pIScene            = pSceneObject->GetScene();
  pAG                = FindAnimGraph(pSceneComponent);
  pAGExtParams       = FindExtPars(pSceneComponent, true);
  pUpperAGExtParams  = FindExtPars(pSceneComponent, false);

  if( NULL == pAG )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Provided SceneComponent hierarchy does not have AnimGraph!" << endl;
    return false;
  }

  if(NScene::AnimatedSceneComponent* pAnsc = dynamic_cast<NScene::AnimatedSceneComponent*>(pSceneComponent) )
  {
    pAGBlender = pAnsc->GetGraphBlender();
    pUpperAG   = pAGBlender ? pAGBlender->GetAdditionalGraph() : NULL;
  }

  isHero = _isHero;
  return true;
}

bool PFAnimController::Initialize( NScene::IAnimGraphBlender* _blender, NScene::IScene* _scene, bool _isHero )
{
  pIScene = _scene;

  if ( _blender )
  {
    pAGBlender = _blender;
    pAG = _blender->GetMainGraph();
    pUpperAG = _blender->GetAdditionalGraph();
    isHero = _isHero;
    return true;
  }

  return false;
}

void PFAnimController::Freeze(const bool freeze, NScene::SceneObject& sceneObject, bool isClientVisible /* = true */ )
{
  if( freeze == freezed )
    return;

  freezed = freeze;
  if ( freezed )
  {
    TCommandQueue::iterator pCmd = commandQueue.insert(commandQueue.end(), Command() );
	  if ( commandQueue.size() > MAX_COMMANDS_IN_QUEUE_ASSERT )
	  {
      NI_ALWAYS_ASSERT( "Too many commands in AG queue!" );
#ifndef _SHIPPING
      DebugPrintAllCommands();
#endif
    }

    pCmd->type       = Command::CT_Nope;
    pCmd->time       = pIScene ? pIScene->GetRenderTime() : -1.0f;
    pCmd->duration   = MAX_ANIM_DURATION_IN_GAME;

	  if ( s_ag_commands_check_size > 0 && commandQueue.size() > s_ag_commands_check_size )
	  {
        TryDeleteRepeatedCommands();
	  }

	  return;
  }
  
  if( NULL == pIScene )
    return;

  // execute full command queue
  //bool restartPending = true;
  const NScene::Time currentTime = pIScene->GetRenderTime();
  for( TCommandQueue::iterator it = commandQueue.begin(), end = commandQueue.end(); it != end; ++it)
  {
    TCommandQueue::iterator next(it);
    ++next;

    //if(restartPending)
    //{
    //  Restart(NDb::ANIMSTATES_IDLE, NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
    //  restartPending = false;
    //}

    float dt = ( end == next ? currentTime : next->time ) - it->time;
    if ( !isHero )
      dt = min( dt, it->duration );
    else
      dt = max( dt, 0.0f );

    bool ok        = false;

    if( Command::CT_SetState    == it->type )
      ok = SetAnimStateInternal(it->stateIds, it->mode);
    else if( Command::CT_ReachMarker == it->type )
      ok = ReachStateMarkerInternal(it->markers, it->timeOffset, it->preferShortestPath, it->preferDefaultNextNode, it->mode, it->permission);
    else if ( Command::CT_Nope == it->type )
    {
      ok = true;
    }
    else
    {
      NI_ALWAYS_ASSERT("Invalid command type!");
    }

    sceneObject.ResetTimeBeingInvisible();
    sceneObject.UpdateForced( dt, true, isClientVisible );
  }

  commandQueue.clear();
}

void PFAnimController::Update( float /*timeDiff*/ )
{ 
  if( NULL == pIScene )
    return;

  if ( !isHero )
  {
    // non-standard extension: stl doesn`t support local functors
    struct CommandRemover
    {
      NScene::Time time;

      CommandRemover(NScene::Time time) : time(time) {}
      bool operator () (PFAnimController::Command const& arg) { return arg.time < time; } 
    };

    if ( commandQueue.size() > 5 )
    {  
      TCommandQueue::iterator last = commandQueue.end();
      if( !commandQueue.empty() )
        advance(last, -1);

      const NScene::Time time = pIScene->GetRenderTime() - queueTimeDepth;
      commandQueue.erase(remove_if(commandQueue.begin(), last, CommandRemover(time) ), last);
    }
  }

  if( firstUpdateTime < 0 )
    firstUpdateTime = NMainLoop::GetTime();
}

int PFAnimController::FindEmptyAnimSet()
{
  for(int i = 0; i < MaxAnimSets; ++i)
    if( !animSets[i].isValid )
      return i;

  return -1;
}

int PFAnimController::RegisterAnimSet( NDb::AnimSet const* pAnimSet )
{
  NI_VERIFY(NULL != pAnimSet,                "Invalid animated character!",        return -1; );

  int setId = FindEmptyAnimSet();
  if( setId < 0)
    return -1;
  
  AnimSet& newSet = animSets[setId];
  newSet.isValid  = true;
  if( pAG )
    Reset(newSet.pLinker, CreateLinker<TLinker>(pAG, pAnimSet, false) );
  if( pUpperAG )
    Reset(newSet.pUpperLinker, CreateLinker<TLinker>(pUpperAG, pAnimSet, true) );  
  
  for(int i = 0, count = NDb::KnownEnum<NDb::EAnimStates>::sizeOf; i < count; ++i)
  {
    newSet.markers[i]      = pAnimSet->states[i].commonMarker.c_str();
    newSet.upperMarkers[i] = pAnimSet->states[i].upperMarker.c_str();
    newSet.permissions[i]  = pAnimSet->states[i].playMode;
  } 

  if( pAG )
  {
    for ( unsigned int i = 0; i < pAG->GetNumNodes(); i++ )
    {
      if ( fabs( pAG->GetNodeSurfSpeed( i ) ) > 0.0f )
      {
        DiAnimNode* node = pAG->GetNodeData( i );
        DIASSERT( node != NULL );

        newSet.nodesBaseSpeedInfo.push_back( NodeSurfaceInfo( node->GetSpeed(), node->GetSurfSpeed() ) );
      }
    }
    newSet.surfaceSpeedMultiplier = 1.0f;
  }

  if( pUpperAG )
  {
    for ( unsigned int i = 0; i < pUpperAG->GetNumNodes(); i++ )
    {
      if ( fabs( pUpperAG->GetNodeSurfSpeed( i ) ) > 0.0f )
      {
        DiAnimNode* node = pUpperAG->GetNodeData( i );
        DIASSERT( node != NULL );

        newSet.upperNodesBaseSpeedInfo.push_back( NodeSurfaceInfo( node->GetSpeed(), node->GetSurfSpeed() ) );
      }
    }
    newSet.upperSurfaceSpeedMultiplier = 1.0f;
  }

  return setId;
}

bool PFAnimController::UnRegisterAnimSet( int id )
{
  if( 0 <= id && id < MaxAnimSets )
  {
    AnimSet& current = animSets[id];
    current.isValid  = false;

    for(list<AnimEvent>::iterator it = current.animEvents.begin(), end = current.animEvents.end(); it != end; ++it)
    {
      AnimEventParams const& params = it->GetParams();
      DiAnimGraph*           pGraph = (NDb::ANIMSTATEPLAYMODE_PLAYUPPER == params.mode) ? pUpperAG : pAG;
      
      if( AnimEventParams::Marker == params.type  )
        pGraph->UnregisterCallbackForAllSameMarkers( params.sValue, AnimEventDispatcher, static_cast<void*>(&*it) );
      else
        pGraph->UnregisterCallback(DIANGR_NODE, params.nodeId, AnimEventDispatcher, static_cast<void*>(&*it) );
    }   
    current.Reset();

    return true;
  }

  return false;
}

bool PFAnimController::ActivateAnimSet( int id )
{
  if( 0 <= id && id < MaxAnimSets )
  {
    activeAnimSet = id;
    return true;
  }
  
  NI_ALWAYS_ASSERT("Can`t activate animSet: invalid id!");
  return false;
}

PFAnimController::AnimSet* PFAnimController::GetActiveAnimSet()
{
  if( 0 <= activeAnimSet && activeAnimSet < MaxAnimSets )
    return &animSets[activeAnimSet];

  return NULL;
}

PFAnimController::AnimSet const* PFAnimController::GetActiveAnimSet() const
{
  if( 0 <= activeAnimSet && activeAnimSet < MaxAnimSets )
    return &animSets[activeAnimSet];

  return NULL;
}

bool PFAnimController::RegisterAnimEvent( AnimEventParams params, IAnimEventCallback* pCallback, int setId)
{
  NI_PROFILE_FUNCTION

  bool upperOk = true, normalOk = true;
  
  if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != params.mode )
  {
    params.mode = NDb::ANIMSTATEPLAYMODE_PLAYUPPER;
    upperOk     = RegisterAnimEventInternal( params, pCallback, setId);
  }

  if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER  != params.mode  )
  {
    params.mode = NDb::ANIMSTATEPLAYMODE_PLAYNORMAL;
    normalOk    = RegisterAnimEventInternal( params, pCallback, setId);
  }

  return upperOk && normalOk;
}

bool PFAnimController::RegisterAnimEventInternal(AnimEventParams const& params, IAnimEventCallback* pCallback, int setId)
{
  if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != params.mode && NDb::ANIMSTATEPLAYMODE_PLAYUPPER != params.mode )
  {
    NI_ALWAYS_ASSERT("Invalid animevent mode!");
    return false;
  }

  DiAnimGraph* pGraph   = (NDb::ANIMSTATEPLAYMODE_PLAYUPPER == params.mode) ? pUpperAG : pAG;
  AnimSet*     pAnimSet = ( 0 <= setId && setId < MaxAnimSets ) ? &animSets[setId] : NULL;
  
  if( NULL == pGraph || NULL == pAnimSet)
    return false;
    
  DiUInt32 const nodeId = GetStateId(params.state, NDb::ANIMSTATEPLAYMODE_PLAYUPPER == params.mode);
  if(  DIANGR_NO_SUCH_ELEMENT == nodeId && AnimEventParams::Marker != params.type )
    return false; 
  
  AnimEvent event(params, nodeId, this, pCallback, setId);
  if( pAnimSet->animEvents.end() != find(pAnimSet->animEvents.begin(), pAnimSet->animEvents.end(), event ) )
    return false;

  pAnimSet->animEvents.push_back( event );

  DiUInt32 flags = 0;
  switch( params.type )
  {
  case AnimEventParams::Invalid:
    NI_ALWAYS_ASSERT("Invalid anim event condition!");
    return false;
  case AnimEventParams::Marker:
    return pGraph ? pGraph->RegisterCallbackForAllSameMarkers(params.sValue, AnimEventDispatcher, static_cast<void*>( &(pAnimSet->animEvents.back() ) ) ) : false;
  case AnimEventParams::EnterNode:
    flags = DIANGR_CF_ELEMENT_ENTER;
    break;
  case AnimEventParams::LeaveNode:
    flags = DIANGR_CF_ELEMENT_LEAVE;
    break;
  case AnimEventParams::ExactParam:
    flags = DIANGR_CF_EXACT_PARAM;
    break;
  }
  
  return pGraph ? pGraph->RegisterCallback(DIANGR_NODE, nodeId, AnimEventDispatcher, flags, 
    static_cast<void*>( &(pAnimSet->animEvents.back()) ), params.fValue ) : false;
}

void  PFAnimController::Cleanup()
{
  SetSurfaceSpeedMultiplier( 1.0f );

  if( NULL != pAG )
  {
    for(int i = 0 ; i < MaxAnimSets;  ++i)
    {
      if(animSets[i].isValid)
      {
        NI_VERIFY(UnRegisterAnimSet(i), "Failed to unregister animSet!", );
      }
    }

    pIScene      = NULL;
    pAG          = NULL;
    pUpperAG     = NULL;
    pAGBlender   = NULL;
    pAGExtParams = NULL;
  }
}

bool PFAnimController::SetAnimState(NDb::EAnimStates target, ETargetAG targetGraph)
{
  return SetAnimStateInternal(GetStateIDs(target), targetGraph);
}

bool PFAnimController::SetAnimStateId(unsigned int nodeId)
{
  return SetAnimStateInternal(pair<DiUInt32, DiUInt32>(nodeId,  nodeId), NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
}

bool PFAnimController::SetAnimStateId(unsigned int nodeId, ETargetAG targetGraph )
{
  return SetAnimStateInternal(pair<DiUInt32, DiUInt32>(nodeId,  nodeId), targetGraph);
}

bool PFAnimController::SetAnimStateInternal(pair<DiUInt32, DiUInt32> const& ids, ETargetAG targetGraph)
{
  if( NULL == pAG )
    return false;

  if( freezed )
  {
    TCommandQueue::iterator pCmd = commandQueue.insert(commandQueue.end(), Command() );
	  if ( commandQueue.size() > MAX_COMMANDS_IN_QUEUE_ASSERT )
	  {
      NI_ALWAYS_ASSERT( "Too many commands in AG queue!" );
#ifndef _SHIPPING
      DebugPrintAllCommands();
#endif
    }

    pCmd->type       = Command::CT_SetState;
    pCmd->mode       = targetGraph;
    pCmd->permission = NDb::ANIMSTATEPLAYMODE_PLAYBOTH;
    pCmd->stateIds   = ids;
    pCmd->time       = pIScene ? pIScene->GetRenderTime() : -1.0f;
    pCmd->duration   = MAX_ANIM_DURATION_IN_GAME;
    if ( ids.first < pAG->GetNumNodes() )
      pCmd->duration = min( pAG->GetNodeDuration( ids.first ), pCmd->duration );
    if ( ids.second < pAG->GetNumNodes() )
      pCmd->duration = max( pAG->GetNodeDuration( ids.second ), pCmd->duration );

    if ( s_ag_commands_check_size > 0 && commandQueue.size() > s_ag_commands_check_size )
	  {
        TryDeleteRepeatedCommands();
	  }

    return true;
  }
  
  bool normalOk = true, upperOk = true;
  if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER != targetGraph)
    normalOk = DIANGR_NO_SUCH_ELEMENT != ids.first ? pAG->SetTargetNode(ids.first) : false;

  if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != targetGraph && NULL != pUpperAG)
    upperOk = DIANGR_NO_SUCH_ELEMENT != ids.second ? pAGBlender->SetAdditionalAGTargetNode(ids.second) : false;

  return normalOk && upperOk;
}

bool PFAnimController::SetRandomAnimState(NDb::EAnimStates first, NDb::EAnimStates last, ETargetAG targetGraph )
{
  NI_VERIFY(first < last, "Invalid state range!", return false; );
  
  return SetAnimState(static_cast<NDb::EAnimStates>( 
    NRandom::Random( static_cast<int>(first), static_cast<int>(last) ) ), targetGraph );
}

float PFAnimController::GetStateDuration(NDb::EAnimStates state, bool upper) const
{
  pair<DiUInt32, DiUInt32> nodeIds = GetStateIDs(state);
  DiAnimGraph* pGraph = upper ? pUpperAG : pAG;
  DiUInt32     nodeId = upper ? nodeIds.second : nodeIds.first;
    
  return (DIANGR_NO_SUCH_ELEMENT == nodeId || NULL == pGraph ) ? -1.0f : pGraph->GetNodeDuration(nodeId);
}
float PFAnimController::GetStateIdDuration(unsigned int nodeId, bool upper) const
{
  DiAnimGraph* pGraph = upper ? pUpperAG : pAG;

  return (DIANGR_NO_SUCH_ELEMENT == nodeId || NULL == pGraph ) ? -1.0f : pGraph->GetNodeDuration(nodeId);
}
float PFAnimController::GetSurfaceSpeed(NDb::EAnimStates state, bool upper) const
{
  pair<DiUInt32, DiUInt32> nodeIds = GetStateIDs( state, false );
  DiAnimGraph* pGraph = upper ? pUpperAG : pAG;
  DiUInt32     nodeId = upper ? nodeIds.second : nodeIds.first;

  return (DIANGR_NO_SUCH_ELEMENT == nodeId || NULL == pGraph ) ? -1.0f : fabs(pGraph->GetNodeSurfSpeed(nodeId));
}

float PFAnimController::GetSurfaceSpeedCurrentNode( bool upper ) const
{
  DiAnimGraph* pGraph = upper ? pUpperAG : pAG;
  if ( pGraph )
  {
    if ( pGraph->GetCurNodeUnsafe() < pGraph->GetNumNodes() )
    {
      return fabs(pGraph->GetNodeSurfSpeed(pGraph->GetCurNodeUnsafe()));
    }
    else
    {
      return fabs(pGraph->GetNodeSurfSpeed(pGraph->GetNearestNode()));
    }
  }
  return -1.0f;
}

void PFAnimController::Restart(NDb::EAnimStates target, ETargetAG targetGraph)
{
  pair<DiUInt32, DiUInt32> nodeIds = GetStateIDs(target);
  if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER != targetGraph && DIANGR_NO_SUCH_ELEMENT != nodeIds.first )
    pAG->Restart( nodeIds.first, true );
  if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != targetGraph && DIANGR_NO_SUCH_ELEMENT != nodeIds.second && NULL != pUpperAG)
    pUpperAG->Restart( nodeIds.second, true );
}

void PFAnimController::Restart(const nstl::string& nodeName, ETargetAG targetGraph)
{
	unsigned target = pAG ? pAG->GetNodeIDByNameSlowQuite(nodeName.c_str()) : DIANGR_NO_SUCH_ELEMENT;
	if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER != targetGraph && DIANGR_NO_SUCH_ELEMENT != target )
		pAG->Restart( target, true );
	target = pUpperAG ? pUpperAG->GetNodeIDByNameSlowQuite(nodeName.c_str()) : DIANGR_NO_SUCH_ELEMENT;
	if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != targetGraph && DIANGR_NO_SUCH_ELEMENT != target && NULL != pUpperAG)
		pUpperAG->Restart( target, true );
}

bool PFAnimController::IsValidState(NDb::EAnimStates target, ETargetAG targetGraph ) const
{
  pair<DiUInt32, DiUInt32> nodeIds = GetStateIDs(target);
  bool normalOk = DIANGR_NO_SUCH_ELEMENT != nodeIds.first  || NDb::ANIMSTATEPLAYMODE_PLAYUPPER  == targetGraph, 
       upperOk  = DIANGR_NO_SUCH_ELEMENT != nodeIds.second || NDb::ANIMSTATEPLAYMODE_PLAYNORMAL == targetGraph ;
  
  return normalOk && upperOk;
}

bool  PFAnimController::ReachStateMarker(char const* sMarker, float time, bool preferShortestPath, bool preferDefaultNextNode)
{
  return ReachStateMarkerInternal( make_pair( sMarker, string("") ), time, preferShortestPath, preferDefaultNextNode, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL, NDb::ANIMSTATEPLAYMODE_PLAYNORMAL);
}

bool PFAnimController::ReachStateMarker( NDb::EAnimStates target, float time, bool preferShortestPath, bool preferDefaultNextNode, ETargetAG targetGraph)
{
  AnimSet const* pAnimSet = GetActiveAnimSet();
  if( NULL == pAnimSet )
    return false;
  
  return ReachStateMarkerInternal( make_pair( GetStateMarker(target, false), GetStateMarker(target, true) ),
    time, preferShortestPath, preferDefaultNextNode, targetGraph, pAnimSet->permissions[target]);
}

bool  PFAnimController::ReachStateMarkerInternal(pair<string, string> const& markers, float time, bool preferShortestPath, bool preferDefaultNextNode, ETargetAG targetGraph, ETargetAG permission)
{
  if( freezed )
  {
    TCommandQueue::iterator pCmd = commandQueue.insert(commandQueue.end(), Command() );
	  if ( commandQueue.size() > MAX_COMMANDS_IN_QUEUE_ASSERT )
	  {
      NI_ALWAYS_ASSERT( "Too many commands in AG queue!" );
#ifndef _SHIPPING
      DebugPrintAllCommands();
#endif
    }

    pCmd->type                  = Command::CT_ReachMarker;
    pCmd->mode                  = targetGraph;
    pCmd->permission            = permission;
    pCmd->markers               = markers;
    pCmd->timeOffset            = time;
    pCmd->preferShortestPath    = preferShortestPath; 
    pCmd->preferDefaultNextNode = preferDefaultNextNode;
    
    pCmd->time                  = pIScene ? pIScene->GetRenderTime() : -1.0f;
    pCmd->duration              = time;

    if ( s_ag_commands_check_size > 0 && commandQueue.size() > s_ag_commands_check_size )
	  {
      TryDeleteRepeatedCommands();
	  }

    return true;
  }

  bool upperOk = true, normalOk = true;
  if( NDb::ANIMSTATEPLAYMODE_PLAYUPPER != targetGraph )
  {
    if( NULL != pAG && NDb::ANIMSTATEPLAYMODE_PLAYUPPER != permission && !markers.first.empty() )                                   
      normalOk = pAG->ReachMarkerByTime(markers.first.c_str(), static_cast<int>(time * 1e+3), preferShortestPath, preferDefaultNextNode );
    else
      normalOk = false;
  }

  if( NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != targetGraph )
  {
    if( NULL != pUpperAG && NDb::ANIMSTATEPLAYMODE_PLAYNORMAL != permission && !markers.second.empty() )                                   
      upperOk = pUpperAG->ReachMarkerByTime(markers.second.c_str(), static_cast<int>(time * 1e+3), preferShortestPath, preferDefaultNextNode );
    else
      upperOk = false;
  }

  return upperOk && normalOk;
}

void PFAnimController::SetSurfaceSpeedMultiplier( float multiplier )
{
  PFAnimController::AnimSet* animSet = GetActiveAnimSet();

  if ( pAG )
  {
    unsigned int k = 0;
    for ( unsigned int i = 0; i < pAG->GetNumNodes(); i++ )
    {
      if ( fabs( pAG->GetNodeSurfSpeed( i ) ) > 0.0f )
      {
        DiAnimNode* node = pAG->GetNodeData( i );
        DIASSERT( node != NULL );

        node->SetSurfSpeed( animSet->nodesBaseSpeedInfo[k].surfSpeed * multiplier );
        node->SetSpeed(     animSet->nodesBaseSpeedInfo[k].speed     * multiplier );

        k++;
      }
    }

    animSet->surfaceSpeedMultiplier = multiplier;
  }

  if ( pUpperAG )
  {
    unsigned int k = 0;
    for ( unsigned int i = 0; i < pUpperAG->GetNumNodes(); i++ )
    {
      if ( fabs( pUpperAG->GetNodeSurfSpeed( i ) ) > 0.0f )
      {
        DiAnimNode* node = pUpperAG->GetNodeData( i );
        DIASSERT( node != NULL );

        node->SetSurfSpeed( animSet->upperNodesBaseSpeedInfo[k].surfSpeed * multiplier );
        node->SetSpeed(     animSet->upperNodesBaseSpeedInfo[k].speed     * multiplier );

        k++;
      }
    }

    animSet->upperSurfaceSpeedMultiplier = multiplier;
  }
}

unsigned PFAnimController::GetCurrentStateId() const
{
  DiAnimGraph* pGraph = pAG;
  unsigned id = pGraph ? pGraph->GetCurNodeUnsafe() : DIANGR_NO_SUCH_ELEMENT;
  //systemLog( NLogg::LEVEL_MESSAGE ) << "Current node:" << pAG->GetNodeNameByID(id) << "(" << id << ")" << endl;
  return id;
}

unsigned PFAnimController::GetNumNodes() const
{
  DiAnimGraph* pGraph = pAG;
  unsigned num = pGraph ? pGraph->GetNumNodes() : 0;
  return num;
}

unsigned PFAnimController::GetNextStateId() const
{
  DiAnimGraph* pGraph = pAG;
  unsigned id = pGraph ? pGraph->GetNextNode() : DIANGR_NO_SUCH_ELEMENT;
  //systemLog( NLogg::LEVEL_MESSAGE ) << "Current node:" << pAG->GetNodeNameByID(id) << "(" << id << ")" << endl;
  return id;
}

unsigned PFAnimController::GetNearestStateId() const
{
  DiAnimGraph* pGraph = pAG;
  if ( pGraph )
  {
    unsigned id = pGraph->GetNearestNode();
    DiAnimNode* node = pGraph->GetNodeData(id);
    if ( node->IsSubNode() )
    {
      return node->GetDispatcherNodeID();
    }
    return id;
  }
  return DIANGR_NO_SUCH_ELEMENT;
}

const char* PFAnimController::GetNearestStateName() const
{
	DiAnimGraph* pGraph = pAG;
	if ( pGraph )
	{
		uint curNode = GetNearestStateId();
		return pGraph->GetNodeNameByID( curNode );
	}
	NI_ALWAYS_ASSERT("GetNearestStateName: Bad AG");
	return 0;
}

unsigned PFAnimController::GetStateIdByName(char const* name) const
{
  DiAnimGraph* pGraph = pAG;
  return pGraph ? pGraph->GetNodeIDByNameSlowQuite(name) : DIANGR_NO_SUCH_ELEMENT;
}

unsigned PFAnimController::GetStateId(NDb::EAnimStates state, bool upper) const
{
  pair<DiUInt32, DiUInt32> ids = GetStateIDs(state);
  return upper ? ids.second : ids.first;
}

bool PFAnimController::IsSameInternalState(NDb::EAnimStates l, NDb::EAnimStates r, bool upper) const
{
  pair<DiUInt32, DiUInt32> const l_ids = GetStateIDs(l);
  pair<DiUInt32, DiUInt32> const r_ids = GetStateIDs(r);

  return upper ? r_ids.second == l_ids.second : r_ids.first == l_ids.first;
}

const char* PFAnimController::GetStateMarker( NDb::EAnimStates state, bool upper ) const
{
  static const string empty = "";
  if( AnimSet const* pAnimSet = GetActiveAnimSet() )
  {
    if( AnimReplaceData const* pReplace = GetStateReplacement(state, upper) )
      if( !pReplace->marker.empty() )
        return pReplace->marker.c_str();
    
    return upper ? pAnimSet->upperMarkers[state].c_str() : pAnimSet->markers[state].c_str();
  }
  
  return empty.c_str();
}

PFAnimController::ETargetAG   PFAnimController::GetStatePlayMode( NDb::EAnimStates state ) const
{
  AnimSet const* pAnimSet = GetActiveAnimSet();
  return pAnimSet ? pAnimSet->permissions[state] : NDb::ANIMSTATEPLAYMODE_PLAYBOTH; 
}

bool PFAnimController::IsValidStateId(unsigned id)
{
  return DIANGR_NO_SUCH_ELEMENT != id;
}

DiInt32 PFAnimController::AnimEventDispatcher(DiAnGrCallbackParams const& cpParams)
{
  if( AnimEvent* event = static_cast<AnimEvent*>(cpParams.vpUserData) )
    event->Trigger();

  return DIOBJMSG_CONTINUE;
}

pair<DiUInt32, DiUInt32> PFAnimController::GetStateIDs(NDb::EAnimStates state, bool checkReplaced /*= true*/) const
{
  pair<DiUInt32, DiUInt32> result = make_pair(DIANGR_NO_SUCH_ELEMENT, DIANGR_NO_SUCH_ELEMENT);
  AnimSet const*         pAnimSet = GetActiveAnimSet();
  if( pAG && pAnimSet )
  {
    if( pAnimSet->isValid && pAnimSet->pLinker )
    {
      result.first = pAnimSet->pLinker->GetID(state);
      if ( checkReplaced )
      {
        if( AnimReplaceData const* pReplace = GetStateReplacement(state, false) )
          result.first = pReplace->stateId;
      }
    }

    if( pAnimSet->isValid && pAnimSet->pUpperLinker )
    {
      result.second = pAnimSet->pUpperLinker->GetID(state);
      if ( checkReplaced )
      {
        if( AnimReplaceData const* pReplace = GetStateReplacement(state, true) )
          result.second = pReplace->stateId;
      }
    }

  }
  
  return result;
}

PFAnimController::AnimReplaceData const* PFAnimController::GetStateReplacement(NDb::EAnimStates state, bool upper) const
{
  vector<AnimReplaceData> const& anims = upper ? replacedAnims[state].upper : replacedAnims[state].normal;
  for( int i = anims.size() - 1; 0 <= i; --i)
    if( -1 == anims[i].setId || activeAnimSet == anims[i].setId )
      return &(anims[i]);

  return NULL;
}

int  PFAnimController::ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool allSets)
{
  DiAnimGraph* pGraph  = upper ? pUpperAG : pAG;
  if( pGraph && ( GetActiveAnimSet() || allSets ) )
  {
    StateReplacement& anims    = replacedAnims[state];
    int& lastUsed              = upper ? anims.lastUpperUsed : anims.lastNormalUsed;
    vector<AnimReplaceData>& v = upper ? anims.upper : anims.normal;

    v.push_back();

    AnimReplaceData& data      = v.back();
    data.marker                = marker;
    data.stateId               = pGraph->GetNodeIDByNameSlowQuite(name);
    data.setId                 = allSets ? ((DiUInt32)(-1)) : activeAnimSet;
    data.id                    = ++lastUsed;
    
    return data.id;
  }

  return -1;
}

bool PFAnimController::RollbackAnimation( NDb::EAnimStates state, const int id, bool upper)
{
  StateReplacement& anims    = replacedAnims[state];
  vector<AnimReplaceData>& v = upper ? anims.upper : anims.normal;
  
  for( vector<AnimReplaceData>::iterator it = v.begin(), end = v.end(); it != end; ++it )
  {
    if( id == it->id )
    {
      v.erase(it);
      return true;
    }
  }
  
  return false;
}

void PFAnimController::FreezeAG()
{
  if ( pAG )
    pAG->Freeze();
  if ( pUpperAG )
    pUpperAG->Freeze();
}

void PFAnimController::UnFreezeAG()
{
  if ( pAG )
    pAG->UnFreeze();
  if ( pUpperAG )
    pUpperAG->UnFreeze();
}

bool PFAnimController::IsSameCommand( Command& cmd1, Command& cmd2 )
{
  switch ( cmd1.type )
  {
    case Command::CT_Invalid:
    case Command::CT_Nope:
      return cmd1.type == cmd2.type;

    case Command::CT_SetState:
      return cmd1.type == cmd2.type 
        && cmd1.mode == cmd2.mode 
		    && cmd1.permission == cmd2.permission 
		    && cmd1.duration == cmd2.duration 
		    && cmd1.stateIds.first == cmd2.stateIds.first
		    && cmd1.stateIds.second == cmd2.stateIds.second;

    case Command::CT_ReachMarker:
      return cmd1.type == cmd2.type 
		    && cmd1.mode == cmd2.mode 
		    && cmd1.permission == cmd2.permission 
		    && cmd1.preferShortestPath == cmd2.preferShortestPath 
		    && cmd1.preferDefaultNextNode == cmd2.preferDefaultNextNode 
		    && cmd1.markers.first == cmd2.markers.first
		    && cmd1.markers.second == cmd2.markers.second;

    default:
      return false;
  }
}

void PFAnimController::TryDeleteRepeatedCommands()
{
  if ( commandQueue.empty() )
    return;

  TCommandQueue::iterator it = commandQueue.end();
  it--;
  Command lastCommand = *it;
  int sameCommands = 1;
  while ( it != commandQueue.begin() )
  {
    it--;
    if ( IsSameCommand( lastCommand, *it ) )
    {
      sameCommands++;
    }
    else
      break;
  }
  
  if ( sameCommands > 1 && (commandQueue.size() - sameCommands) >= 0 )
  {
    commandQueue.resize( commandQueue.size() - sameCommands );
    commandQueue.push_back( lastCommand );
  }

  return;
}

#ifndef _SHIPPING
void PFAnimController::DebugPrintAllCommands()
{
  if ( !commandQueue.empty() )
  {
    DebugTrace( "==============================================================" );
    if( pAG )
      DebugTrace( "%s", pAG->GetDBFileName().c_str() );

    for ( int i = 0; i < commandQueue.size(); i++ )
    {
      const Command& cmd = commandQueue[i];
      DebugTrace( "%d: type=%d, stateIds=(%d(%s),%d(%s)), markers=(%s,%s), timeOffset=%f, time=%f", i, (int)cmd.type, cmd.stateIds.first, 
                                                                                                pAG->GetNodeNameByID(cmd.stateIds.first), 
                                                                                                cmd.stateIds.second, pAG->GetNodeNameByID(cmd.stateIds.second),
                                                                                                cmd.markers.first.c_str(), cmd.markers.second.c_str(), 
                                                                                                cmd.timeOffset, cmd.time );
    }
    DebugTrace( "==============================================================" );
    return;
  }
}
#endif

} // namespace NGameX

REGISTER_VAR( "ag_commands_check_size", s_ag_commands_check_size, STORAGE_NONE );
