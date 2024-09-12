#pragma once

#include "PFClientBaseUnit.h"
#include "PFBaseMovingUnit.h"
#include "../Scene/DiAnGr.h"
#include "../Scene/DiAnGrNLinker.h"

namespace NGameX
{
class PFClientBaseMovingUnit : public PFClientBaseUnit
{
  CLIENT_OBJECT_WORLD( PFClientBaseMovingUnit, NWorld::PFBaseMovingUnit )
public:
	struct CreatePars : public PFClientLogicObject::CreatePars
	{
		CreatePars(NDb::Ptr<NDb::DBSceneObject> const& sceneObject, NScene::IScene *pS, const nstl::string& nodeName) 
			: PFClientLogicObject::CreatePars(pS, nodeName, sceneObject)
		{}

	};
          
          void LookTo( const CVec2& target, bool instantRotate = false, float time = 0.0f );
          void TurnBy(CQuat const& rot);
          bool IsMoving() const { return isMove; }
          void StartFlying();
          void StartFlying( NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> trajectory,
                            NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> angle,
                            float flightDuration_, float heightModifier, const CVec2& startPos, const CVec2& endPos, NDb::EThrowType _flightType );
          void SetFlightHeight( float height, bool absolute );
          void SetFlightAngle( float angle );
          void StopFlying();
          void Stand();

  virtual void SetRotation( CQuat const &quat );
  
  // Move
  virtual void OnMoveTo( const CVec2& newpos, bool animate = true );
  virtual void OnStop();
  virtual void OnTeleportTo( const CVec2& target, bool needReplace = true );
  virtual void OnMoveFailed( const CVec2& target ) {}

  virtual void OnFakeUnsummon() {}
  virtual void OnHide(bool hide);
  
  bool IsFlying() const { return isFlying; }
  virtual void SetVisibility(bool bVisible) { SetVisibilityAsObject(bVisible); } // Choosing visibility policy

protected:
  // @BVS@TODO: Remove this ctor
  PFClientBaseMovingUnit() {}
  PFClientBaseMovingUnit(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp);

          void CalculateRotationParams( const CVec2& dir, float time = 0.0f );
          void CalculateRotationParams( float angle, float time = 0.0f );

          void UpdateMovement( float timeDiff );
          float GetTerrainHeight() const;
          float GetTerrainHeight( const CVec2& pos ) const;

          CVec3 GetTerrainNormal() const;
          CVec3 GetTerrainNormal( const CVec2& pos ) const;

          CVec3 GetTerrainNormalSmooth() const;
          CVec3 GetTerrainNormalSmooth( const CVec2& pos ) const;


  virtual void OnStartMoving(bool animate = true) {}
  virtual void OnStopped() {}


          void SynchronizeVisualPosition();

  CVec3 destination;
  float dstAngle;
  float curAngle;
  float rotSpeed;

  float dstAngleZ;
  float curAngleZ;
  float rotSpeedZ;

  float speed;
  float heightSpeed;
  float turnSpeed;
  bool  isMove;
  bool  isStopPending;		 // Stop() was called, should stop unit animation when destination position reached
  bool  isFlying;
  bool  isFlyingByTrajectory;
  bool  isFlyingHeightAbsolute;
  float dstHeight;
  float curHeight;

  mutable CVec3 cashedNormal;
  mutable CVec2 cashedTilePos;
  CBetaSpline3D betaSpline3D;
  

  NDb::Animated2Spline<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>> heightWrapper;
  NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>> angleWrapper;

  float flightStartHeight;
  float flightEndHeight;
  float flightDuration;
  float flightTime;
  float flightHeightModifier;
  NDb::EThrowType flightType;
};

}
