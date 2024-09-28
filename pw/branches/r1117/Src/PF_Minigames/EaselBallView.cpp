#include "stdafx.h"

#include "EaselBallView.h"

#include "DBEasel.h"

#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Render/debugrenderer.h"
#include "../Render/RenderComponent.h"
#include "../Render/material.h"
#include "../System/RandomGen.h"

#include "Easel.h"
#include "EaselWorld.h"
#include "EaselSoundsInterface.h"

#include "LuxBall.h"

namespace PF_Minigames
{

static const char* shadowComponentName = "shadow";
static const char* trailComponentName = "Trail";

// opacity material processor
struct OpacityChanger : public Render::IMaterialProcessor, public NonCopyable
{
  float opacity;

  OpacityChanger(float o) : opacity(o) {}
  virtual void operator()(Render::BaseMaterial &material)
  {
    material.ModifyOpacity(opacity);
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiInt32 ResetAnimation(DiAnGrCallbackParams const &cpParams)
{
  EaselBallView* drop = reinterpret_cast<EaselBallView*>(cpParams.vpUserData);
  NI_VERIFY( drop, "", return DIOBJMSG_CONTINUE );
  drop->ResetSpeed();
  drop->EnableMovement(true);

  return DIOBJMSG_CONTINUE;
}

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselBallView::EaselBallView()
: defaultScale(1, 1, 1)
, currentState( NDb::DBEASELDROPSTATE_IDLE)
, lastState( NDb::DBEASELDROPSTATE_IDLE)
, enableAnimations(false)
, animationGraph(0)
, animationGraphParams(0)
, shadowOpacity(0.0001f)
, desiredShadowOpacity(0)
, desiredShadowRotation(0, 0, 0)
, shadowFadeSpeed(1)
, invisible(true)
, movementEnable(true)
, update(false)
, jumpInSpeed(-1)
, prevState(BALL_STATE_UNKNOWN)
{
  
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselBallView::~EaselBallView()
{
  if(animationGraph)
  {
    animationGraph->UnregisterCallback( DIANGR_NODE, animationsForStates[NDb::DBEASELDROPSTATE_MOVE], ResetAnimation);
    animationGraph->UnregisterCallback( DIANGR_NODE, animationsForStates[NDb::DBEASELDROPSTATE_MOVEUNDERGROUND], ResetAnimation );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Ptr<NDb::DBSceneObject> EaselBallView::GetDBByColor( EBallType::Enum ballType, BallState ballState, NDb::EColor color )
{
  NI_VERIFY( IsValid( easel ), "", return NULL );

  switch(ballType)
  {
    case EBallType::Simple:
    {
      const nstl::vector<NDb::Ptr<NDb::DBSceneObject>>& balls = easel->GetData()->commonParams->balls.colorBalls;
      NI_VERIFY( balls.size() >= NDb::KnownEnum<NDb::EColor>::SizeOf(), "", return NULL );
      return balls[color];
    }
    
    case EBallType::Joker:
    {
      const NDb::Ptr<NDb::DBSceneObject>& jokerBall = easel->GetData()->commonParams->balls.jokerBall;
      NI_VERIFY( IsValid( jokerBall ), "", return NULL );
      return jokerBall;
    }
  }

  const nstl::vector<NDb::Ptr<NDb::DBSceneObject>>& balls = easel->GetData()->commonParams->balls.colorBalls;
  
  NI_VERIFY( balls.size() >= NDb::KnownEnum<NDb::EColor>::SizeOf(), "", return NULL );
	
  return balls[color];
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselBallView::Init(Easel& _easel, LuxBall* ball, BallCoordsConverter* _converter)
{
	NI_VERIFY( IsValid( ball ), "", return false );

	easel = &_easel;
	logicBall = ball;

  movementEnable = true;

  if ( logicBall->Type() == EBallType::Joker )
    easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_BOOST_JOKER_CLICK);
  else if ( logicBall->Type() == EBallType::PainBlast )
    easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_BOOST_PAINTBLAST_CLICK);

  color = ball->Color();

	// load from db
  NDb::Ptr<NDb::DBSceneObject> dbSceneObject = GetDBByColor( ball->Type(), ball->State(), color );
	if(!IsValid(dbSceneObject))
	{
		return false;
	}

	// create placement
  Placement objPlacement = easel->GetPlacement();
  defaultScale = objPlacement.scale;

  NScene::SceneObject *pSceneObject = MinigameClientObject::Init(NULL, _easel.GetScene(), dbSceneObject.GetPtr(), objPlacement, false);
  if( pSceneObject == 0)
    return false;

  SetOpacity(1.0f);

  invisible = false;

  // init animations from 
  NDb::Ptr<NDb::DBEaselCommon> commonParams = easel->GetData()->commonParams;
  NI_VERIFY( IsValid( commonParams ), "", return false )
  enableAnimations = InitAnimations( *pSceneObject, commonParams.GetPtr() );

  // initializing lerp object 
  lerpBallPos = new EaselBallViewLerp(ball,_converter);

  // initializing rotator object
  director.SetEasel( &_easel );

  // set shadow opacity to current
  OpacityChanger opacityChanger(shadowOpacity);
  ForAllComponentMaterials(*pSceneObject, shadowComponentName, opacityChanger);

  // init shadow params
  desiredShadowRotation.FromEulerAngles( commonParams->balls.shadowRotation, 0, 0);
  desiredShadowRotation *= easel->GetPlacement().rot;
  shadowFadeSpeed = commonParams->balls.shadowOpacityChangeSpeed;

  pSceneObject->UpdateForced();

  // randomize animation
  if ( ball->Type() != EBallType::Joker )
  {
    float timeOffset = NRandom::Random(0.0f, 5.0f);
    pSceneObject->Update(timeOffset);
  }

  UpdateShadowRotation();

  Render::HDRColor color = _easel.GetData()->commonParams->colors[ ball->Color() ];

  EnableComponent( trailComponentName, false );
  SetComponentMulColor( trailComponentName, color );

  // Станет видимым когда отработает интерполятор
  SetVisible( false );
  invisible = true;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::SetLerpProcessor( EaselBallViewLerp* _lerpProcessor )
{
  lerpBallPos = _lerpProcessor;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::EnableMovement(bool _enable)
{
  movementEnable = _enable;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::ResetSpeed()
{
  NI_VERIFY( Get( sceneObject ), "", return );
  NI_VERIFY( sceneObject->GetRootComponent(), "", return );

  sceneObject->GetRootComponent()->ResetSpeed();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselBallView::InitAnimations(NScene::SceneObject& sceneObject, const NDb::DBEaselCommon* commonParams)
{
  // search for first animated component and get from it animation graph and params


  animationGraph = 0;
  animationGraphParams = 0;

  NScene::SceneComponent* currentComponent = sceneObject.GetRootComponent();

  if ( currentComponent == 0 )
  {
    return false;
  }
    
  do
  {
    NScene::AnimatedSceneComponent* animatedComponent = dynamic_cast<NScene::AnimatedSceneComponent*>(currentComponent);
    if ( animatedComponent != 0 )
    {
      animationGraph = animatedComponent->GetMainAnimGraph();
      animationGraphParams = animatedComponent->GetExtPars();
    }

    currentComponent = currentComponent->GetBrother();
  } while( (currentComponent != 0) && (animationGraph == 0) );

  if(animationGraph == 0)
  {
    animationGraphParams = 0;
    return false;
  }

  bool result = true;
  // get node ids by name
  for(int i = 0; i < NUM_DROP_STATES; ++i)
  {
    const char* nodeName = commonParams->balls.switchToAnimation[i].c_str();
    animationsForStates[i] = animationGraph->GetNodeIDByNameSlowQuite( nodeName );
    baseSpeed[i] = commonParams->balls.animationsBaseSpeed[i];
    speedModifier[i] = commonParams->balls.animationsSpeedModifier[i];
    if(animationsForStates[i] == DIANGR_NO_SUCH_ELEMENT)
    {
      systemLog(NLogg::LEVEL_CRITICAL) << "EaselBallView: animation node with name \"" << nodeName << "\" doesn't found"<< endl;
      result = false;
    }
  }

  if(result)
  {
    result = result && animationGraph->RegisterCallback( DIANGR_NODE, animationsForStates[NDb::DBEASELDROPSTATE_MOVE], ResetAnimation, DIANGR_CF_ELEMENT_ENTER, this );
    result = result && animationGraph->RegisterCallback( DIANGR_NODE, animationsForStates[NDb::DBEASELDROPSTATE_MOVEUNDERGROUND], ResetAnimation, DIANGR_CF_ELEMENT_ENTER, this );
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int64 EaselBallView::GetJumpInDistance()
{
  NI_VERIFY(animationGraph, "animation graph should be valid", return INT_MAX);

  //not magic 12/16. its a moment when ball cross zero level again. later it fallse underground
  //this is only for this animation
  float animationTime = animationGraph->GetNodeDuration(animationsForStates[NDb::DBEASELDROPSTATE_JUMPIN]) * (12.0f / 16.0f) ;
  return logicBall->Speed()*animationTime;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselBallView::IsNowInTunnel()
{
  BallState ballState = logicBall->State();
  bool isInTunnel = (ballState == BALL_STATE_IN_TUNNEL);
  int64 disnanceToTunnel = logicBall->GetNextTunnelPoint()-logicBall->GetCoveredPath();

  int64 jumpInDistance = GetJumpInDistance();
  isInTunnel |= disnanceToTunnel<jumpInDistance && disnanceToTunnel>0;

  return isInTunnel;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::UpdateAnimation(float deltaTime)
{
  if(!enableAnimations)
  {
    return;
  }

  NDb::DBEaselDropState newState;

  //BallState ballState = logicBall->State();
  bool nowInTunnel = IsNowInTunnel();
  float ballSpeed = logicBall->Speed();
 
  if(ballSpeed == 0 && !nowInTunnel)
  {
    newState = NDb::DBEASELDROPSTATE_IDLE;
  }
  else if(nowInTunnel)
  {
    newState = NDb::DBEASELDROPSTATE_MOVEUNDERGROUND;
  }
  else
  {
    newState  = NDb::DBEASELDROPSTATE_MOVE;
  }

  float chainVelocity = easel->GetData()->commonParams->ballVelocities.ballInChainVelocity;

  if(!movementEnable)
  {
    float timeModifier = ( stepLeft <= 0)?  0: stepLeft / deltaTime;
    float curBallSpeed = jumpInSpeed > ballSpeed? jumpInSpeed: ballSpeed;
    float speed = abs(timeModifier * curBallSpeed / chainVelocity);

    sceneObject->GetRootComponent()->SetSpeed(speed);
  }

  sceneObject->GetRootComponent()->ResetSpeed();
  static float tunnelLength = 200 * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  sceneObject->GetRootComponent()->SetSpeed(1.0f);
 
  if(newState == currentState)
  {
    return;
  }

  if(newState == NDb::DBEASELDROPSTATE_MOVEUNDERGROUND)
  {
    jumpInSpeed = ballSpeed;
    movementEnable = false;
  }

  if(currentState == NDb::DBEASELDROPSTATE_MOVEUNDERGROUND)
  {
    jumpInSpeed = -1;
    movementEnable = false;
  }

  animationGraph->SetTargetNode( animationsForStates[newState] );
  lastState = newState;
  currentState = newState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::RecalculateSize()
{
  Placement placement = sceneObject->GetPosition();
  Placement oldPlacement = placement;
  placement.scale.Mul( defaultScale, placement.scale );
  SetPlacement(placement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::Update(float deltaTime, bool gameOnPause)
{
	NI_VERIFY( IsValid( easel ), "", return );
  NI_VERIFY( IsValid( logicBall ), "", return );

  // need to increment delta timer
  lerpBallPos->IncrementElapsedTime(deltaTime);

  // calculating ball position based on interpolated data ...
  Placement newPlacement;
  if( !lerpBallPos->vLerp(newPlacement) )  // object is not visible at all
  {
    SetVisible(false);
    invisible = true;
    return;
  }

  if(invisible)
  {
    SetVisible(true);
    invisible = false;
  }

  UpdateAnimation(deltaTime);
  SetPlacement(newPlacement);
  RecalculateSize();
  UpdateBallState();
  UpdateShadow(deltaTime);
  
  stepLeft -= deltaTime;
  update = true;

  MinigameClientObject::Update( deltaTime, gameOnPause );	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::UpdateBallState()
{
  if ( !IsValid( logicBall ) )
    return;

  BallState newState = logicBall->State();

  if ( newState != prevState )
  {
    if ( newState == BALL_STATE_ON_PLATFORM )
    {
      EnableComponent( shadowComponentName, false );
    }
    else if ( prevState == BALL_STATE_ON_PLATFORM && newState == BALL_STATE_FIRED )
    {
      EnableComponent( trailComponentName, true );
      lerpBallPos->ResetPosition();
    }
    else if ( prevState == BALL_STATE_FIRED )
    {
      EnableComponent( trailComponentName, false );
      EnableComponent( shadowComponentName, true );
    }
    else if ( newState == BALL_STATE_HIT_MATCH || newState == BALL_STATE_HIT_MISSMATCH )
    {
      lerpBallPos->ResetPosition();
    }
  }

  prevState = newState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::UpdateOrientation(SVector direction)
{

  if(director.SetDirection(direction) == true)
  {
    Placement newPlacement(GetPlacement());

    newPlacement.rot = director.GetRotation();
    SetPlacement(newPlacement);       
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::UpdateShadowOpacity(float deltaTime)
{
  //// setting traverser
  struct ShadowOpacityUpdater : public NScene::TraverserById
  {
    OpacityChanger opacityProcessor;

    ShadowOpacityUpdater(const char *id, float _opacity)
      : TraverserById(id)
      , opacityProcessor(_opacity)
    {
    }

    void operator()(NScene::SceneComponent *pSC)
    {
      pSC->ForAllMaterials(opacityProcessor); 
    }
  };

  BallState state = logicBall->State();

  switch(state)
  {
  case BALL_STATE_IN_TUNNEL:
    desiredShadowOpacity = 0.0f;
    break;
  default: 
    desiredShadowOpacity = 1.0f;
    break;
  }
  
  //calculate new opacity
  if(shadowOpacity == desiredShadowOpacity)
  {
    return;
  }

  float chainVelocity = easel->GetData()->commonParams->ballVelocities.ballInChainVelocity;
  float ballSpeed = logicBall->Speed();
  float shadowFadeSpeedModifier = (state != BALL_STATE_FIRED) ? ballSpeed / chainVelocity : 1.0f;
  shadowFadeSpeedModifier = max(shadowFadeSpeedModifier, 0);


  if(shadowOpacity < desiredShadowOpacity)
  {
    shadowOpacity += shadowFadeSpeedModifier * shadowFadeSpeed * deltaTime;
    shadowOpacity = min(shadowOpacity, desiredShadowOpacity);
  }
  else
  {
    shadowOpacity -= shadowFadeSpeedModifier * shadowFadeSpeed * deltaTime;
    shadowOpacity = max(shadowOpacity, desiredShadowOpacity);
  }

  // set shadow opacity to current
  OpacityChanger opacityChanger(shadowOpacity);
  ForAllComponentMaterials(*sceneObject, shadowComponentName, opacityChanger);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::UpdateShadowRotation()
{
  //// setting traverser
  struct ShadowRotationUpdater : public NScene::TraverserById
  {
    CQuat newRotation;
    
    ShadowRotationUpdater (const char *id, CQuat _newRotation)
      : TraverserById(id)
      , newRotation(_newRotation) 
    {
    }

    void operator()(NScene::SceneComponent *pSC)
    {
      Placement placement = pSC->GetPlacement();
      pSC->SetBase(placement.pos, newRotation, placement.scale);
    }
  };

  ShadowRotationUpdater updater( shadowComponentName, desiredShadowRotation );

  // applying traverser
  sceneObject->Traverse( updater );

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::UpdateShadow(float deltaTime)
{
  UpdateShadowOpacity(deltaTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselBallView::Step( float deltaTime )
{
  if(update)
  {
    stepLeft = deltaTime;
  }
  else
  {
    stepLeft += deltaTime;
  }
  
  update = false;
}



} // PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::EaselBallView );