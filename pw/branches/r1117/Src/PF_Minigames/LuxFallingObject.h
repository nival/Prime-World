#ifndef LUXFALLINGOBJECT_H_INCLUDED
#define LUXFALLINGOBJECT_H_INCLUDED

#include "DBEasel.h"
#include "EaselWorldObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SInitialConditions
{
  SInitialConditions() {}

  SInitialConditions( const SVector & pos, const SVector & vel, const SVector & accel );

  SInitialConditions( const SVector & from, const SVector & to, int upvelocity, int gravity );

  SVector position;
  SVector velocity;
  SVector acceleration;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLuxFallingObject : public EaselWorldObject
{
  OBJECT_METHODS( 0x9A6CE4C6, CLuxFallingObject )

public:
  CLuxFallingObject( PF_Core::IWorld* _pWorld, const SInitialConditions & start );
  CLuxFallingObject( PF_Core::IWorld* _pWorld, const CLuxFallingObject& rhs );

  virtual ~CLuxFallingObject() {}

  const SVector & GetPosition() const { return position; };
  const SVector & GetVelocity() const { return velocity; };
  const SVector & GetAcceleration() const { return acceleration; };

  void SetPosition( const SVector & pos ) { position = pos; }
  void SetVelocity( const SVector & vel ) { velocity = vel; }
  void SetAcceleration( const SVector & accel ) { acceleration = accel; }

  void Update( int deltaTime );

  bool IsInValidPosition() const;

  int CurrentTime() const { return currentTime; }

  void SetPicked( bool picked ) { isPicked = picked; }
  bool IsPicked() const { return isPicked; }

protected:
  CLuxFallingObject() {}

private:

  CLuxFallingObject& operator=(const CLuxFallingObject& rhs);

  ZDATA_(EaselWorldObject)

  SVector position;
  SVector velocity;
  SVector acceleration;
  int currentTime;
  bool isPicked;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(EaselWorldObject*)this); f.Add(2,&position); f.Add(3,&velocity); f.Add(4,&acceleration); f.Add(5,&currentTime); f.Add(6,&isPicked); return 0; }
};

}

#endif //LUXFALLINGOBJECT_H_INCLUDED
