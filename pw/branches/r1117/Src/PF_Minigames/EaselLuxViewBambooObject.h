#pragma once

#include "EaselLuxStaticObject.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// bamboo path object
//
//////////////////////////////////////////////////////////////////////////
class EaselLuxViewBambooObject : public EaselLuxStaticObject
{
public:
  EaselLuxViewBambooObject();
  ~EaselLuxViewBambooObject();

  const CVec3& GetStartLocator() const { return startLocator; };
  const CVec3& GetEndLocator() const   { return endLocator; };

  bool InitBambooObject(const CPtr<Easel>& _easel,
                        const NDb::Ptr<NDb::DBSceneObject> _DBSceneObject,
                        const Placement& _placement);

private:
  EaselLuxViewBambooObject(const EaselLuxViewBambooObject &rhs);
  EaselLuxViewBambooObject& operator=(const EaselLuxViewBambooObject &rhs);

  CVec3 startLocator;
  CVec3 endLocator;

protected:

};


}