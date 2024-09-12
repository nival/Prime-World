#pragma once

#include "EaselLuxStaticObject.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// well path object
//
//////////////////////////////////////////////////////////////////////////
class EaselLuxViewWellObject : public EaselLuxStaticObject
{
public:
  EaselLuxViewWellObject();
  ~EaselLuxViewWellObject();

  const CVec3& GetStartLocator() const { return startLocator; };
  const CVec3& GetMidLocator() const   { return midLocator; };
  const CVec3& GetEndLocator() const   { return endLocator; };

  bool InitWellObject(const CPtr<Easel>& _easel,
                      const NDb::Ptr<NDb::DBSceneObject> _DBSceneObject,
                      const Placement& _placement);

private:
  EaselLuxViewWellObject(const EaselLuxViewWellObject &rhs);
  EaselLuxViewWellObject& operator=(const EaselLuxViewWellObject &rhs);

  CVec3 startLocator;
  CVec3 midLocator;
  CVec3 endLocator;

protected:

};

}