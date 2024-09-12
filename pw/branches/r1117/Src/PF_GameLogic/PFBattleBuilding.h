#pragma once

#include "PFBuildings.h"

namespace NGameX { class PFBattleBuilding; }
namespace NDb { struct TurretParams; }

float NormalizeAngle( float angle );
float DetectMinAngleDelta( float currentAngle, float targetAngle );

namespace NWorld
{

  class PFBattleBuilding : public PFBuilding
  {
    WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C6CEAC1, PFBattleBuilding, NGameX::PFBattleBuilding)

  protected:
    explicit PFBattleBuilding() {}

    ZDATA_(PFBuilding)
    float            baseAngle;
    float            currentAngle;
    float            angleSpeed;
    float            maxAngleSpeed;
    float            angleAcceleration; 
    float            deltaAngle;
    float            targetingTolerance;
    float            lastAngleResetDelay;
    float            lastAngleResetDelayTime; 
    bool             accelerate;
    bool             controlTurret;
    bool             forceTargetAngle;
    float            forcedAngle;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); f.Add(2,&baseAngle); f.Add(3,&currentAngle); f.Add(4,&angleSpeed); f.Add(5,&maxAngleSpeed); f.Add(6,&angleAcceleration); f.Add(7,&deltaAngle); f.Add(8,&targetingTolerance); f.Add(9,&lastAngleResetDelay); f.Add(10,&lastAngleResetDelayTime); f.Add(11,&accelerate); f.Add(12,&controlTurret); f.Add(13,&forceTargetAngle); f.Add(14,&forcedAngle); return 0; }

    explicit PFBattleBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);

    float         GetTargetAngle()  const;
    float         GetAngleSpeed() const { return angleSpeed; }

    virtual bool  IsReadyToAttack() const;
    virtual bool  Step(float dtInSeconds);

    virtual void  OnAfterReset();

  protected:
    virtual void  OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
    virtual void  OnTargetAssigned();
            void  ContolTurret( bool control ) { controlTurret = control; }
            void  SetTurretParams(NDb::TurretParams const& params);
            void  SetBaseAngle(float angle);
            bool  IsInBasePosition() const;
            bool  IsInTargetPosition() const;
            void  ForceTargetAngle( bool force, float angle = 0.0f);
  };

};