#ifndef ROLL_INSTANCE_H_INCLUDED
#define ROLL_INSTANCE_H_INCLUDED

#include "RPC/RPC.h"
#include "RollTypes.h"

namespace roll
{

class IClient;

REMOTE class IInstance : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IInstance, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void Roll( NI_LPTR IClient* client, const SPreGameData& preGame, const SPostGameData& postGame ) = 0;
  REMOTE virtual void ForgeRoll( NI_LPTR IClient* client, const SForgeRollData & data ) = 0;
};

} //namespace roll


#endif // ROLL_INSTANCE_H_INCLUDED
