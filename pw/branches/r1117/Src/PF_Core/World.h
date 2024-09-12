#pragma once

#include "../Core/WorldBase.h"
#include "../System/RandomGenerator.h"

namespace PF_Core
{
class      WorldObjectBase;

_interface IWorld : public NCore::IWorldBase
{
  virtual void             RegisterObject(WorldObjectBase* pObject, int realWObj, bool immediately) = 0; 
  virtual void             UnregisterObject(WorldObjectBase* pObject, bool full = true) = 0;
	virtual WorldObjectBase* GetObjectById(int id) const = 0;

  virtual NRandom::RandomGenerator *GetRndGen() = 0;
  virtual bool ProcessAddRemove() = 0; 
  virtual bool CanCreateClients() = 0;
};

IWorld* CreateWorld();
  
} // namespace PF_Core
