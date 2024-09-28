#pragma once

#include "Network/TransportTypes.h"
#include "Network/Address.h"
#include "Network/TransportDefaults.h"
#include "Network/LoginTypes.h"

struct ssl_ctx_st;
typedef struct ssl_ctx_st SSL_CTX;

namespace Transport
{
  class MessageFactory;
  _interface IChannel;
  _interface IChannelListener;

  namespace EStatus {
    enum Enum {
      NONE = 0,
      OK,
      FAIL,
      CRITICAL_FAIL,
    };
  }
  _interface IClientTransportSystem : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IClientTransportSystem, IBaseInterfaceMT );
    virtual int GetUserId() const = 0;

    virtual StrongMT<Transport::IChannel> OpenChannel( Transport::TServiceId interfaceId, 
      unsigned int pingperiod = Defaults::GetPingPeriod(), unsigned int to = Defaults::GetOpenChannelTimeout()) = 0;
    virtual void GetNewAcceptedChannels(vector< StrongMT< Transport::IChannel > > & _chnls) { _chnls; }

    virtual void Login( const Network::NetAddress& loginServerAddress, const nstl::string& login, const nstl::string& _password, const nstl::string& sessionKey="", Login::LoginType::Enum _loginType = Login::LoginType::ORDINARY ) = 0;
    virtual void Logout() = 0;
    virtual Login::ELoginResult::Enum GetLoginResult() const = 0;
    virtual EStatus::Enum GetStatus() = 0; // в частности, по CRITICAL_FAIL можно прибивать
    virtual TServiceId GetSessionPath() const { return TServiceId(); };
    virtual Network::NetAddress GetRelayAddress() const = 0;
    virtual Network::NetAddress GetSecondaryRelayAddress() const = 0;
    virtual void Step() = 0;
  };

}
