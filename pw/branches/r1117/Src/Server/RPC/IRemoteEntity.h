#ifndef RPC_I_REMOTE_ENTITY_H__
#define RPC_I_REMOTE_ENTITY_H__

#include "System/ported/types.h"

namespace rpc
{

class ArgReader;
class ArgWriter;
class EntityHandler;
struct LocalInstanceInfo;
struct IUpdateCallback;

struct RemoteEntityTypeInfo
{
  uint classId;
  uint classCrc;
};

struct RemoteEntityInfo
{
  EntityId entityId;
  RemoteEntityTypeInfo typeInfo;
  GUID entityGUID;
  bool IsNull() const { return (entityId == 0xFFFFFFFF && typeInfo.classId == 0xFFFFFFFF && typeInfo.classCrc == 0xFFFFFFFF); }
};
static RemoteEntityInfo NullInfo  = { 0xFFFFFFFF, { 0xFFFFFFFF, 0xFFFFFFFF }, {0, 0, 0, 0} };

enum Status
{
  Unknown,
  Connected,
  PartiallyConnected,
  Disconnected,
  Connecting,
};

_interface IRemoteEntity : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IRemoteEntity, IBaseInterfaceMT);
  virtual ~IRemoteEntity() {}
  virtual bool RollbackMember(byte memberId, ArgReader& s) { return true; }
  virtual bool Synchronize(rpc::ArgWriter* args) { return true; }
  virtual RemoteEntityInfo GetInfo() const {  rpc::RemoteEntityInfo info = { 0xFFFFFFFF , { 0xFFFFFFFF , 0xFFFFFFFF  } }; return info; }
  virtual EntityHandler* GetHandler() { return 0; } 
  virtual const LocalInstanceInfo* GetLocalInstanceInfo() const { return 0; }
  virtual void Commit(bool publishAfterCommit=false) {}
  virtual rpc::IUpdateCallback* GetUpdateCallback() { return 0; }
  virtual void SetParent(rpc::IRemoteEntity* _parent) {}
  virtual rpc::Status GetStatus() { return Unknown; }
protected:
  friend class EntityHandler;
  friend class PipeEntities;
  friend class Args;
  friend class ArgReader;
  virtual bool vset(byte memberId, ArgReader& s) { return true; }
};

}

#endif // RPC_I_REMOTE_ENTITY_H__
