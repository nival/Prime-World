#ifndef AIGAMEOBJECT_H__
#define AIGAMEOBJECT_H__

#include "../SimpleGame/GameObject.h"
#include "../SimpleGame/Protocol.h"

namespace AI
{

class AIGameObject : public Location::GameObject
{
  OBJECT_BASIC_METHODS( AIGameObject );

public:
  AIGameObject() {}
  virtual ~AIGameObject() {}

  virtual void InitPlacement( const CVec2& _startPos, const CVec2& _targetPos, Protocol::AbsoluteTime _finishTime ) {}
  virtual void MoveTo( const CVec2& _targetPos, Protocol::AbsoluteTime _finishTime ) {}

private:
};

} // namespace Town

#endif // AIGAMEOBJECT_H__