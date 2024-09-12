#pragma once

#include "LoginTypes.h"
#include "LoginClientVersion.h"
#include "Network/TransportTypes.h"

namespace Network
{
  _interface INetworkDriver;
  _interface IConnection;
}

struct ssl_ctx_st;
typedef struct ssl_ctx_st SSL_CTX;

namespace Login
{

class LoginClient : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoginClient, BaseObjectMT )

public:
  LoginClient( Network::INetworkDriver* _driver, Login::ClientVersion const & ver );

  void LoginRequest( const Network::NetAddress& loginServerAddress, const string& login, const string& password, 
    ::SSL_CTX* secureContext, const string& sessionKey="", Login::LoginType::Enum _loginType = Login::LoginType::ORDINARY );

  ELoginResult::Enum Step();

  //Use only after ELoginResult::Success was received
  void GetConnectionData( Network::NetAddress* baseRelayAddress, Network::NetAddress* secondaryRelayAddress, 
    int* userId, string* sessionId, string* relayCertificate = 0, Transport::TServiceId* sessionPath=0, 
    bool* partialReconnectSupport = 0, unsigned int * partialReconnectRetries = 0, unsigned int * partialReconnectRetryTimeout = 0 );
private:
  enum State
  {
    NotInitialized,
    Connecting,
    LoggingIn,
  };

  StrongMT<Network::INetworkDriver> driver;
  StrongMT<Network::IConnection> connection;
  LoginRequestMessage requestMsg;
  LoginResultMessage resultMsg;
  LoginClient::State state;
  Login::ClientVersion version;
  LoginClient() {}
};

}
