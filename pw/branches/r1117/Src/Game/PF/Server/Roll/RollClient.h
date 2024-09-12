#ifndef ROLL_CLIENT_H_INCLUDED
#define ROLL_CLIENT_H_INCLUDED

#include "RollTypes.h"

namespace roll
{

REMOTE class IClient : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( IClient, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void RollResults( const vector<SUserAward>& _award ) = 0;
  REMOTE virtual void ForgeRollAck() = 0;
  REMOTE virtual void RollFailed() = 0;
};

} //namespace roll


#endif // ROLL_CLIENT_H_INCLUDED
