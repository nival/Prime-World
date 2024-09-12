#pragma once

#include "MinigameClientObject.h"

#include "LuxBall.h"
#include "EaselLuxLerp.h"
#include "EaselLuxViewDropDirector.h"
#include "../Scene/DiAnGrUtils.h"

class DiAnimGraph;
class DiAnGrExtPars;

namespace NDb
{
	struct DBSceneObject;
  enum EColor;
}

namespace PF_Minigames
{

class Easel;
class Minigames;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselBallView : public MinigameClientObject
{
	OBJECT_METHODS(0xC8664A80, EaselBallView);
public:

	EaselBallView();
  virtual ~EaselBallView();

  ILuxViewLerp* GetLerpProcessor() const { return lerpBallPos; };
  void SetLerpProcessor( EaselBallViewLerp* _lerpProcessor );

	bool Init(Easel& _easel, LuxBall* ball, BallCoordsConverter* _converter);

	virtual void Update(float deltaTime, bool gameOnPause);
  virtual void Step( float deltaTime );

  void EnableMovement(bool _enable);
  void ResetSpeed();

private:

  enum
  {
    NUM_DROP_STATES = NDb::KnownEnum<NDb::DBEaselDropState>::sizeOf,
  };

	// changes on db in the future
  NDb::Ptr<NDb::DBSceneObject> GetDBByColor( EBallType::Enum ballType, BallState ballState, NDb::EColor color );

  // interpolation 
  CObj<EaselBallViewLerp> lerpBallPos;
  
  // orientation
  LuxViewDropDirector director;
  
  bool InitAnimations(NScene::SceneObject& sceneObject, const NDb::DBEaselCommon* commonParams);

  void RecalculateSize();
  void UpdateOrientation(SVector direction);
  void UpdateAnimation(float deltaTime);

  void UpdateBallState();
  void UpdateShadow( float deltaTime);
  void UpdateShadowOpacity(float deltaTime);
  void UpdateShadowRotation();

  int64 GetJumpInDistance();
  bool IsNowInTunnel();

  NDb::DBEaselDropState currentState; 
  NDb::DBEaselDropState lastState; 

  // animation params
  DiUInt32 animationsForStates[ NUM_DROP_STATES ];
  float baseSpeed[ NUM_DROP_STATES ];
  float speedModifier[ NUM_DROP_STATES ];

  bool enableAnimations;
  DiAnimGraph* animationGraph;
  DiAnGrExtPars* animationGraphParams;

	CPtr<Easel> easel;
	CPtr<LuxBall> logicBall;
  BallState prevState;

  CVec3 defaultScale;

  NDb::EColor color;
  bool invisible;

  // shadow fade params
  float shadowOpacity;
  float desiredShadowOpacity;
  float shadowFadeSpeed;

  bool movementEnable;
  float jumpInSpeed;

  float stepLeft;
  bool update;
  
  // 
  CQuat desiredShadowRotation;
};

} // PF_Minigames
