#ifndef RDPFRONTENDAGENTREMOTE_H_INCLUDED
#define RDPFRONTENDAGENTREMOTE_H_INCLUDED

#include "RPC/RPC.h"
#include "Network/TransportTypes.h"


namespace rdp_transport
{

REMOTE class IFrontendAgentRemote : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1( IFrontendAgentRemote, rpc::IRemoteEntity );

public:
  REMOTE virtual void UserPrepared( Transport::TClientId _uid ) = 0;
  REMOTE virtual void UserConnected( Transport::TClientId _uid ) = 0;
  REMOTE virtual void UserTimedOut( Transport::TClientId _uid ) = 0;
  REMOTE virtual void UserKicked( Transport::TClientId _uid ) = 0;
  REMOTE virtual void UserDropped( Transport::TClientId _uid ) = 0;
};

}; //namespace clientCtl

#endif //RDPFRONTENDAGENTREMOTE_H_INCLUDED
