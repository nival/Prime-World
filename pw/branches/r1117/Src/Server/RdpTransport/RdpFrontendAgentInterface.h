#ifndef RDPFRONTENDAGENTINTERFACE_H_INCLUDED
#define RDPFRONTENDAGENTINTERFACE_H_INCLUDED

#include "RPC/RPC.h"
#include "Network/TransportTypes.h"


namespace rdp_transport
{

class IFrontendAgentRemote;

REMOTE class IFrontendAgent : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1( IFrontendAgent, IBaseInterfaceMT );

  static const char * InterfaceId;

public:
  REMOTE virtual void PrepareUser( Transport::TClientId _uid, const string & _login, const string & _key, NI_LPTR IFrontendAgentRemote* _callback ) = 0;
  REMOTE virtual void KickUser( Transport::TClientId _uid ) = 0;
};

}; //namespace rdp_transport

#endif //RDPFRONTENDAGENTINTERFACE_H_INCLUDED
