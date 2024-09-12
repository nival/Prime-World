#pragma once

#include "../Scene/DiAnGrUtils.h"

namespace NScene
{
  class SceneObject;
}

class DiAnimGraph;
class DiAnGrExtPars;

namespace PF_Minigames
{

namespace EMoveAnimationNode
{
  enum Enum
  {
    Idle,
    Move,
    ExternalNode,
    Last
  };
}

namespace EMoveAnimationBlockType
{
  enum Enum
  {
    None,
    IdleOnly,
    All
  };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovingUnitController : public CObjectBase
{
  OBJECT_BASIC_METHODS( MovingUnitController )

public:
  MovingUnitController( NScene::SceneObject* _sceneObject );
  virtual ~MovingUnitController();

  void Update( float deltaTime );

  void SetAngularVelocity( float _velocity );
  float GetAngularVelocity() const;

  void SetAnimationName( EMoveAnimationNode::Enum animationNode, const char * name );
  void SetAnimationName( EMoveAnimationNode::Enum animationNode, DiUInt32 animNodeId );

  DiUInt32 GetAnimNodeId(const char * name);
  void PlayAnimNode(DiUInt32 id, EMoveAnimationBlockType::Enum block = EMoveAnimationBlockType::None);

  void SetDefaultMoveVelocity( float _value );
  void SetCurrentVelocity( float _value );

private:
  MovingUnitController() {}

  ///DEBUG///
  const char * GetMoveNodeStr() const;
  const char * GetAnimBlockStr() const;

  void ClearAnimBlock();

  NScene::SceneObject*  sceneObject;
  DiAnimGraph*  animationGraph;
  DiAnGrExtPars*  animationExtParams;

  EMoveAnimationNode::Enum currentMoveNode;

  DiUInt32 animationID[EMoveAnimationNode::Last];
  float animSurfSpeed[EMoveAnimationNode::Last];

  Placement prevPlacement;
  float prevVelocity;

  float angularVelocity;

  EMoveAnimationBlockType::Enum animBlockType;
  float animBlockTime;

  float idleMovePause;
  float idleMovePauseRest;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MovingUnitController::SetAngularVelocity( float _velocity ) { angularVelocity = _velocity; }
inline float MovingUnitController::GetAngularVelocity() const { return angularVelocity; } 

} // namespace PF_Minigames

