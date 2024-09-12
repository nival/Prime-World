#pragma once

namespace PF_Core
{
  _interface IClientObject;
  _interface IWorldObject;

  _interface IClientObjectFactory : public CObjectBase
  {
    virtual IClientObject* CreateClientObject(IWorldObject* pWorldObject) const = 0;
  };

} // namespace PF_Core