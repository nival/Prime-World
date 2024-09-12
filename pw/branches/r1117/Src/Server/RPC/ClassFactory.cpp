
#include "stdafx.h"
#include "ClassFactory.h"

namespace rpc
{

rpc::ILocalEntity* LocalEntities::GetEntity(EntityId entityId, const RemoteEntityTypeInfo& info)
{
  NI_PROFILE_HEAVY_FUNCTION;

  rpc::LocalEntityInfo* linfo = GetEntityInfo(entityId);
  if (linfo && linfo->IsMatched(info.classId, info.classCrc))
  {
    return linfo->Get();
  }
  return 0;
}



rpc::LocalEntityInfo* LocalEntities::FindMember(const void* value, int& _index)
{
  for (LocalEntityContainer::iterator it=_entities.begin();it != _entities.end();++it)
  {
    int index = it->second->Get()->GetMemberIndex(value);
    if (index >= 0)
    {
      if (it->second->getHandlerInfo(index)) 
      {
        return 0;
      }
      _index = index;
      return it->second;
    }
  }
  return 0;
}

}
