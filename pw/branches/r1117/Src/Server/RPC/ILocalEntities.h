#ifndef RPC_I_LOCAL_ENTITIES_H__
#define RPC_I_LOCAL_ENTITIES_H__

#include "Types.h"

namespace rpc
{

struct LocalEntityInfo;

struct ILocalEntities
{
  virtual rpc::LocalEntityInfo* GetEntityInfo(EntityId entityId)=0;
};

}

#endif // RPC_I_LOCAL_ENTITIES_H__
