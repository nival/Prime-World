#ifndef STATICGAMEOBJECT_H_F26C42D7_8B92
#define STATICGAMEOBJECT_H_F26C42D7_8B92

#include "GameObject.h"

namespace Location
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StaticGameObject : public GameObject
{
  OBJECT_METHODS( 0x9D689C00, StaticGameObject );

public:
  StaticGameObject();
	virtual ~StaticGameObject();

  bool IsPassive() const { return false; }
  void SetPassive( bool _passive ) { }

	virtual	void Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime );

private:

};

} // namespace Location

#endif //#define STATICGAMEOBJECT_H_F26C42D7_8B92