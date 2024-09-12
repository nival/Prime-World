#pragma once
#include <RPC/RPC.h>

namespace HybridServer
{
  REMOTE struct IGameServerAllocatorNotify : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IGameServerAllocatorNotify, IRemoteEntity );

    RPC_ID();

    REMOTE virtual void AllocNotify( uint allocid, int result ) = 0;
    REMOTE virtual void FreeNotify(uint allocid) = 0;
  };

  REMOTE struct IGameServerAllocator : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IGameServerAllocator, IBaseInterfaceMT );

    RPC_ID();

    REMOTE virtual uint AllocateServer( long long userctx, IGameServerAllocatorNotify* allocnotify) = 0;
  };

}
