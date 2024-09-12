#ifndef ROLL_BALANCER_H_INCLUDED
#define ROLL_BALANCER_H_INCLUDED

#include "RPC/RPC.h"

namespace roll
{

class IInstance;
class RIInstance;

REMOTE class IBalancer : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IBalancer, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void LoadNotify( RIInstance* inst, const string & serviceId, int currentLoad ) = 0;
  REMOTE virtual RIInstance* AllocateInstance() { return 0; }
};

} //namespace roll

#endif // ROLL_BALANCER_H_INCLUDED
