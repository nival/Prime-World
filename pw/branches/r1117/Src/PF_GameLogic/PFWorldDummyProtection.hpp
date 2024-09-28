#pragma once

#include "PFWorldProtection.h"

class PFWorldDummyProtection
  : public NWorld::PFWorldProtection
{
  WORLD_OBJECT_METHODS(0x15C5DC02, PFWorldDummyProtection)
public:
  explicit PFWorldDummyProtection(NWorld::PFWorld* const world)
    : PFWorldProtection(world)
  {
  }

  virtual ~PFWorldDummyProtection() {}
protected:
  PFWorldDummyProtection()
    : PFWorldProtection()
  {
  }
private:
  ZDATA_(NWorld::PFWorldProtection)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(NWorld::PFWorldProtection*)this); return 0; }
};

REGISTER_WORLD_OBJECT(PFWorldDummyProtection)
