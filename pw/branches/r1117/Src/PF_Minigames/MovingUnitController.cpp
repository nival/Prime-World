#include "stdafx.h"

#include "../Scene/SceneObject.h"
#include "../Scene/AnimatedSceneComponent.h"

#include "MovingUnitController.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static DiAnimGraph* FindAnimGraph( NScene::SceneComponent* root )
{
  DiAnimGraph* result = NULL;

  if ( root )
  {
    NScene::SceneComponent* it = root;
    do
    {
      if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
        result = asc->GetMainAnimGraph();
      it = it->GetBrother();
    } while ( it && it != root && !result );
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static DiAnGrExtPars* FindExtPars( NScene::SceneComponent* root )
{
  DiAnGrExtPars* result = NULL;

  if ( root )
  {
    NScene::SceneComponent* it = root;
    do
    {
      if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
        result = asc->GetExtPars();
      it = it->GetBrother();
    } while ( it && it != root && !result );
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MovingUnitController::MovingUnitController( NScene::SceneObject* _sceneObject ) :
  sceneObject( _sceneObject ),
  angularVelocity( FP_2PI * 1.5f ),
  currentMoveNode(EMoveAnimationNode::Idle),
  prevVelocity(0.f),
  animBlockType(EMoveAnimationBlockType::None),
  animBlockTime(0),
  idleMovePause(0.1f),
  idleMovePauseRest(0.f)
{
  animationGraph = FindAnimGraph( _sceneObject->GetRootComponent() );
  animationExtParams = FindExtPars( _sceneObject->GetRootComponent() );

  prevPlacement = _sceneObject->GetPosition();

  animationID[EMoveAnimationNode::Move] = animationGraph->GetNodeIDByNameSlow( "move" );
  animationID[EMoveAnimationNode::Idle] = animationGraph->GetNodeIDByNameSlow( "idle" );

  animSurfSpeed[EMoveAnimationNode::Move] = animationGraph->GetNodeSurfSpeed( animationID[EMoveAnimationNode::Move] ).Length();
  animSurfSpeed[EMoveAnimationNode::Idle] = animationGraph->GetNodeSurfSpeed( animationID[EMoveAnimationNode::Idle] ).Length();

  animationGraph->SetTargetNode( animationID[EMoveAnimationNode::Idle] );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MovingUnitController::~MovingUnitController()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitController::SetAnimationName( EMoveAnimationNode::Enum animationNode, const char * name )
{
  SetAnimationName(animationNode, animationGraph->GetNodeIDByNameSlow( name ));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitController::SetAnimationName( EMoveAnimationNode::Enum animationNode, DiUInt32 animNodeId )
{
  if(animNodeId != animationID[animationNode])
  {
    //TODO: remove this when Priestess animation will be done
    //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: SetAnim: %s, block = %s", GetMoveNodeStr(), GetAnimBlockStr());

    animationID[animationNode] = animNodeId;
    if(currentMoveNode == animationNode)
    {
      bool changeAnim = false;
      if ( (currentMoveNode == EMoveAnimationNode::Idle) && (animBlockType == EMoveAnimationBlockType::None) )
        changeAnim = true;
      if ( (currentMoveNode == EMoveAnimationNode::Move) && (animBlockType != EMoveAnimationBlockType::All) )
        changeAnim = true;

      //TODO: remove this when Priestess animation will be done
      //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: %s", changeAnim ? "playing anim" : "do NOT playing anim");

      if ( changeAnim )
        animationGraph->SetTargetNode( animNodeId );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiUInt32 MovingUnitController::GetAnimNodeId(const char * name)
{
  return animationGraph->GetNodeIDByNameSlow(name);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitController::PlayAnimNode(DiUInt32 id, EMoveAnimationBlockType::Enum block)
{
  animBlockType = block;

  bool blockCurrent = (block == EMoveAnimationBlockType::All);

  if ( block == EMoveAnimationBlockType::IdleOnly && currentMoveNode == EMoveAnimationNode::Idle )
    blockCurrent = true;

  if ( blockCurrent )
  {
    animBlockTime = animationGraph->GetNodeDuration(id);
    currentMoveNode = EMoveAnimationNode::ExternalNode;
  }
  else
    animBlockTime = 0;

  //TODO: remove this when Priestess animation will be done
  //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: Playing node %i, block = %s", id, GetAnimBlockStr());

  animationGraph->SetTargetNode( id );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitController::Update( float deltaTime )
{
  if ( deltaTime <= EPS_VALUE )
    return;

  Placement nextPlacement = sceneObject->GetPosition();

  CVec3 direction = nextPlacement.pos - prevPlacement.pos;
  float distance = fabs( direction );

  // animation

  //TODO: remove this when Priestess animation will be done
  //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: block = %s, currentMove = %s", GetAnimBlockStr(), GetMoveNodeStr());

  if ( distance > EPS_VALUE )
  {
    if ( animBlockType != EMoveAnimationBlockType::All )
    {
      if ( currentMoveNode != EMoveAnimationNode::Move )
      {
        //TODO: remove this when Priestess animation will be done
        //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: Changed to Move, playing animation");

        currentMoveNode = EMoveAnimationNode::Move;
        animationGraph->SetTargetNode( animationID[currentMoveNode] );
        animationGraph->SetGraphSpeedCoeff(1.0f);

        ClearAnimBlock();
      }
    }

    SetCurrentVelocity( 0.5f * ( prevVelocity + distance / deltaTime ) );
    prevVelocity = distance / deltaTime;

    idleMovePauseRest = idleMovePause;
  }
  else
  {
    if ( animBlockType == EMoveAnimationBlockType::None )
    {
      idleMovePauseRest -= deltaTime;

      if ( currentMoveNode != EMoveAnimationNode::Idle && idleMovePauseRest < 0.f )
      {
        //TODO: remove this when Priestess animation will be done
        //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: Changed to Idle, playing animation");

        currentMoveNode = EMoveAnimationNode::Idle;
        animationGraph->SetTargetNode( animationID[currentMoveNode] );
      }
    }

    prevVelocity = 0.f;
  }

  // rotation
  if ( distance > 0.01f )
  {
    float dstAngle = atan2( direction.x, -direction.y );
    float deltaYaw = dstAngle - nextPlacement.rot.GetYaw();
    float deltaYawAbs = fabs( deltaYaw );

    if ( deltaYawAbs > angularVelocity * deltaTime )
    {
      if ( deltaYawAbs > FP_PI )
        deltaYaw = ( FP_2PI - fmod( deltaYawAbs, FP_2PI ) ) * -Sign( deltaYaw );

      deltaYaw = deltaYaw > 0 ? angularVelocity * deltaTime : -angularVelocity * deltaTime;

      nextPlacement.rot.FromEulerAngles( NormalizeAngleInRadian( nextPlacement.rot.GetYaw() + deltaYaw ), 0.f, 0.f);
    }
  }

  prevPlacement = nextPlacement;
  sceneObject->SetPlacement( nextPlacement );

  //track anim blocking
  if ( animBlockType != EMoveAnimationBlockType::None)
  {
    animBlockTime -= deltaTime;

    if ( animBlockTime < 0 )
      ClearAnimBlock();
  }
}

///DEBUG///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * MovingUnitController::GetMoveNodeStr() const
{
  switch(currentMoveNode)
  {
    case EMoveAnimationNode::Idle:          return "Idle";
    case EMoveAnimationNode::Move:          return "Move";
    case EMoveAnimationNode::ExternalNode:  return "ExternalNode";
  }
  return "<unknown>";
}

///DEBUG///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * MovingUnitController::GetAnimBlockStr() const
{
  switch(animBlockType)
  {
    case EMoveAnimationBlockType::None:       return "None";
    case EMoveAnimationBlockType::IdleOnly:   return "IdleOnly";
    case EMoveAnimationBlockType::All:        return "All";
  }
  return "<unknown>";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitController::ClearAnimBlock()
{
  //TODO: remove this when Priestess animation will be done
  //systemLog(NLogg::LEVEL_DEBUG).Trace(">>>Controller: Disabling block: %s", GetAnimBlockStr());

  animBlockTime = 0;
  animBlockType = EMoveAnimationBlockType::None;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovingUnitController::SetCurrentVelocity( float _value )
{ 
  if ( animSurfSpeed[EMoveAnimationNode::Move] > EPS_VALUE )
  {
    const float animatedSpeed = _value / animSurfSpeed[EMoveAnimationNode::Move];
    animationExtParams->setExtParValue( "moveSpeed", animatedSpeed );
  }
}


} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::MovingUnitController)
