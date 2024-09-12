#pragma once

#include "MinigameClientObject.h"

#include "LuxFallingObject.h"
#include "EaselLuxLerp.h"

namespace NDb
{
	struct DBSceneObject;
  enum EColor;
}

namespace PF_Minigames
{

class Easel;
class Minigames;

class EaselLuxViewFallingObject : public MinigameClientObject
{
	OBJECT_METHODS(0xC8654204, EaselLuxViewFallingObject);
public:

	EaselLuxViewFallingObject();

	bool Init( Easel * _easel, CLuxFallingObject * _object );

	virtual void Update(float deltaTime, bool gameOnPause);

  bool IsWorldObjectValid() { return IsValid( object ); }

  bool IsPicked() const;
  void Reset();

private:

	// changes on db in the future
  NDb::Ptr<NDb::DBSceneObject> GetDB(NDb::EFallingObject type);
  
	CPtr<Easel> easel;
	CPtr<CLuxFallingObject> object;

  CObj<CLuxFallingObject> localObject;
  int localIntTime;
  float localTime;
};

} // PF_Minigames
