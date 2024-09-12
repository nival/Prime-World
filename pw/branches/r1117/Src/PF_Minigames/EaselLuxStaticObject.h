#pragma once

#include "MinigameClientObject.h"

namespace NDb
{
  struct DBSceneObject;
}

namespace PF_Minigames
{
class Easel;

//////////////////////////////////////////////////////////////////////////
//
// Minigame View Static object class
//
//////////////////////////////////////////////////////////////////////////
class EaselLuxStaticObject : public MinigameClientObject
{
  OBJECT_METHODS(0xF46653C0,EaselLuxStaticObject);

public:
  EaselLuxStaticObject();
  ~EaselLuxStaticObject();

  bool InitObject(const CPtr<Easel>& _easel,
                  const NDb::Ptr<NDb::DBSceneObject> _DBSceneObject,
                  const Placement& _placement);
  
private:
  EaselLuxStaticObject(const EaselLuxStaticObject &rhs);
  EaselLuxStaticObject& operator=(const EaselLuxStaticObject& rhs);

protected:
  CPtr<Easel> easel;

};

}