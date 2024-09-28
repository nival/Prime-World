#pragma once
#include <RPC/RPC.h>
#include <Network/TransportTypes.h>
#include <System/EnumToString.h>

namespace Relay
{
  namespace OutgoingClientReason
  {
    enum Enum
    {
      Disconnect,
      ConnectTimeoutExpired,
    };
  }

  REMOTE struct IOutgoingClientNotifySink : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IOutgoingClientNotifySink, IRemoteEntity );

    RPC_ID();

    REMOTE virtual void OutgoingClientNotify(Transport::TClientId _clientid, int _reason) = 0;
    REMOTE virtual void ClientConnectedNotify(Transport::TClientId _clientid) = 0;
  };

  REMOTE class IIncomingClientNotifySink : public IBaseInterfaceMT
  {
    RPC_ID();

  public:
    REMOTE virtual int RegisterOutgoingClientNotifySink(IOutgoingClientNotifySink* _cb) = 0;
    REMOTE virtual bool IncomingClientNotify(Transport::TClientId _clientid, string const & _sessionkey) = 0;
  };
}
