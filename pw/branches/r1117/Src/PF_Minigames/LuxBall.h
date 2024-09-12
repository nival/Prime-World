#pragma once

#include "../PF_Core/WorldObject.h"

#include "DBEasel.h"
#include "EaselDef.h"
#include "LuxCollidable.h"

namespace PF_Minigames
{


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EBallType
{
  enum Enum
  {
    Simple,
    PainBlast,
    Joker
  };
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum BallState
{
  BALL_STATE_UNKNOWN,             //< default ball state
  BALL_STATE_ROLL_IN,            //< ball is rolling out to the board. length of coordinates vector of the ball represent distance to the start point
  BALL_STATE_ON_BOARD,            //< ball is moving on the game board.
  BALL_STATE_ROLL_OUT,              //< ball reached end of the game path
  BALL_STATE_IN_TUNNEL,           //< ball is moving through tunnel right now
  BALL_STATE_ON_PLATFORM,         //< ball is active on platform
  BALL_STATE_FIRED,               //< ball was just fired form platform
  BALL_STATE_HIT_MATCH,           //< ball has just hit chain ball with the same color
  BALL_STATE_HIT_MISSMATCH,       //< ball has just hit chain ball with another color
  BALL_STATE_MISSED,              //< ball has just missed something
  BALL_STATE_EXPLODED,            //< ball was just exploded
};


//////////////////////////////////////////////////////////////////////////
//
// Luxor basic ball object (logic part)
//
//////////////////////////////////////////////////////////////////////////

_interface IEaselNotifier;

class LuxBall : public ICollidable, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4CA, LuxBall )

public:
  LuxBall( PF_Core::IWorld* _pWorld, IEaselNotifier * _pnotifier, EBallType::Enum startType, const SVector & startPos, NDb::EColor startColor );

  virtual ~LuxBall();

  virtual void        OnDestroyContents();
          void        InitVisual();

  EBallType::Enum     Type() const { return type; };

  virtual void        SetColor(NDb::EColor _color);
  NDb::EColor         Color() const { return color; };

  virtual void        SetState( BallState _state );
  BallState           State() const { return state; };

  void                SetLastTunelPoint(int64 _tunnelPoint) { lastTunnelPoint = _tunnelPoint; }
  void                SetNextTunelPoint(int64 _tunnelPoint) { nextTunnelPoint = _tunnelPoint; }
  int64               GetLastTunnelPoint() const { return lastTunnelPoint; }
  int64               GetNextTunnelPoint() const { return nextTunnelPoint; }

  int64               GetCoveredPath() const { return coveredPath; };
  bool                SetCoveredPath(int64 _coveredPath);

  //ICollidable:
  virtual void        SetPosition( const SVector & _coord ) { position = _coord; }
  virtual const SVector & Position() const { return position; };

  virtual void        SetSize( int _size ) { size = _size; }
  virtual int         Size() const { return size; }

  virtual int         Speed() const { return speed; }
  virtual void        SetSpeed( int _speed ) { speed = _speed; }

  virtual const SVector & Direction() const { return direction; }
  virtual void        SetDirection( const SVector & _direction ) { direction = _direction; }

  virtual bool        Hit() { return false; }
  virtual bool        IsExhausted() const { return false; }


          // $TODO Get rid of double & int64 [AZ]
          double      GetInsertionShift( ICollidable* _other, double collisionTime );
          void        GetCollisionPoint( ICollidable* _other, double collisionTime, double& collisionX, double& collisionY );
          bool        GetCollisionTime( ICollidable* _other, double& collisionTime );
          bool        CanCollide() const;

 void OnAfterReset();

protected:
  ZDATA_(PF_Core::WorldObjectBase)
  ZNOPARENT(ICollidable)

  EBallType::Enum type;      // current ball type
  SVector       position;    // current ball position
  NDb::EColor   color;     // current ball color
  BallState     state;     // current ball state
  int           size;      // current ball size
  int           speed;     // current ball speed
  SVector       direction; // current ball direction

  // path already covered by spline
  int64         coveredPath;

  int64 lastTunnelPoint;
  int64 nextTunnelPoint;

  CPtr<IEaselNotifier> pNotifier; 

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&type); f.Add(3,&position); f.Add(4,&color); f.Add(5,&state); f.Add(6,&size); f.Add(7,&speed); f.Add(8,&direction); f.Add(9,&coveredPath); f.Add(10,&lastTunnelPoint); f.Add(11,&nextTunnelPoint); f.Add(12,&pNotifier); return 0; }

private:
  void          GetVectorVelocity( ICollidable* _collidable, double& velocityX, double& velocityY );
  void          GetVectorVelocityAndDir( ICollidable* _collidable, double& velocityX, double& velocityY, double& dirX, double& dirY );

  void SendBallHitChainNotification(bool fMatch);
  void SendBallMissedNotification();
  void SendBallExplodedNotification();
  void SendBallFiredNotification();
  void SendBallColorChangedNotification();
  void SendBallCreatedNotification();
  void SendBallDestroyedNotification();
  void SendBallEntersTunnelNotification();
  void SendBallLeavesTunnelNotification();

protected:
  LuxBall() {}
  
};

} //namespace PF_Minigames
