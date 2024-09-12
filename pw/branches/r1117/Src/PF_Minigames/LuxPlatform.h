#pragma once

#include "EaselNotifications.h"

#include "DBEasel.h"
#include "LuxBall.h"

#include "Random.h"

#include "../PF_Core/WorldObject.h"

namespace PF_Minigames
{

class Easel;
class EaselWorldClientConvertHelper;
class LuxGameBoard;

class LuxPlatform : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BC3C0, LuxPlatform );

public:
  typedef nstl::vector<CObj<LuxBall>> Balls;

  LuxPlatform( Easel* easel, EaselNotifier* pNotifier );
	~LuxPlatform();

  void InitialCreateBalls( LuxGameBoard* gameBoard );
  bool UpdateBalls( bool forceNewBall, LuxGameBoard* gameBoard );
  void SwapBalls();

  LuxBall* GetBulletBall() { NI_ASSERT( !balls.empty(), "Platform has no balls" ); return balls[0]; }

  LuxBall* CreatePaintBlastBall();
  LuxBall* CreateJokerBall();

  Balls& GetBalls() { return balls; }
  
  // [AZ] здесь нужна копия 
  CObj<LuxBall> FireBulletBall();
  
	// platform positioning
	bool    SetPlatformPos(SVector newPos);
	SVector GetPlatformPos() { return platformPos; };

  void    Update(int deltaTime) { SetPlatformPos( platformPos ); }

  const SVector& GetCollisionPoint() const { return collisionPoint; }
  void    SetCollisionPoint( const SVector& _point ) { collisionPoint = _point; }	

  bool    HasCollision() const { return hasCollision; }
  void    SetHasCollision( bool _hasCollision ) { hasCollision = _hasCollision; }
private:
  // platform is unique, no copy-assignement
  LuxPlatform() {}

  
  LuxBall* CreateBall( int pos, NDb::EColor color, EBallType::Enum _type );
  bool FindLocator( const NDb::DBSceneObject* _sceneObject, const char* name, Placement& locatorPlacement );
  float GetBulletVelocity();

  struct ColorDesc
  {
    int count;
    float weight;

    ColorDesc() : count( 0 ), weight ( 0.f ) {}
  };

  typedef nstl::map< NDb::EColor, ColorDesc > ColorWeights;

  NDb::EColor GetNextColor( NDb::EColor _exceptColor, LuxGameBoard* gameBoard );
  NDb::EColor GetNextColorByWeight( NDb::EColor _exceptColor, const ColorWeights& _weights, LuxGameBoard* gameBoard );
  NDb::EColor PerformLowAct( const ColorWeights& _weights );
  bool IsColorInChains( NDb::EColor color, LuxGameBoard* gameBoard ) const;

  void CollectColorWeights( ColorWeights& _weights, LuxGameBoard* gameBoard ) const;

  ZDATA_(PF_Core::WorldObjectBase)
  bool isBallOnPlatform;

  Balls balls;

	SVector platformPos;

  SVector collisionPoint;
  bool hasCollision;

  RandomGenerator randomGenerator;
  NDb::EColor lastColor;
  int lastColorRepeatNum;

  CPtr<Easel> easel;
  CPtr<EaselNotifier> notifier;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&isBallOnPlatform); f.Add(3,&balls); f.Add(4,&platformPos); f.Add(5,&collisionPoint); f.Add(6,&hasCollision); f.Add(7,&randomGenerator); f.Add(8,&lastColor); f.Add(9,&lastColorRepeatNum); f.Add(10,&easel); f.Add(11,&notifier); return 0; }

};

}