#include "stdafx.h"
#include "LoginClient.h"
#include "Network/Network.h"


namespace Login
{

LoginClient::LoginClient( Network::INetworkDriver* _driver, Login::ClientVersion const & ver)
: driver(_driver), 
  state( NotInitialized ), 
  version(ver)
{
}



void LoginClient::LoginRequest( const Network::NetAddress& loginServerAddress, const string& login, const string& password,
                               ::SSL_CTX* secureContext, const string& sessionKey, Login::LoginType::Enum _loginType )
{
  if ( state == Connecting )
    return;

  state = Connecting;
  connection = driver->Connect( loginServerAddress ); 

  if  ( secureContext )
    connection->StartSSL( secureContext, false );

  requestMsg.login    = login;
  requestMsg.password = password;
  requestMsg.sessionKey = sessionKey;
  requestMsg.majorVer = version.major_;
  requestMsg.minorVer = version.minor_;
  requestMsg.patchVer = version.patch_;
  requestMsg.revisionVer = version.revision_;
  requestMsg.loginType = _loginType;
}



ELoginResult::Enum LoginClient::Step()
{
  if( state == NotInitialized )
    return ELoginResult::NoResult;

  if( !connection || connection->GetStatus() == Network::ConnectionState::Closed )
  {
    state = NotInitialized;
    return ELoginResult::NoConnection;
  }

  switch( state )
  {
  case Connecting:
    if ( connection->GetStatus() == Network::ConnectionState::Connected )
    {
      SendMessageHelper( connection, requestMsg );
      state = LoggingIn;
    }
    return ELoginResult::NoResult;

  case LoggingIn:
    {
      CObj<Stream> stream = connection->Receive();
      if ( !stream )
        return ELoginResult::NoResult;

      CObj<IBinSaver> saver = CreateChunklessSaver( (MemoryStream*)stream.GetPtr(), 0, true );
      resultMsg & (*saver);

      connection->ReleaseReceived( stream );
      stream = 0;

      connection->AsyncClose();
      connection = 0;

      state = NotInitialized;

      return resultMsg.loginResult;
    }
  }

  return ELoginResult::NoResult;
}



void LoginClient::GetConnectionData( Network::NetAddress* baseRelayAddress, Network::NetAddress* secondaryRelayAddress, 
                                    int* userId, string* sessionId, string* relayCertificate, Transport::TServiceId* sessionPath,
                                    bool* partialReconnectSupport, unsigned int * partialReconnectRetries, unsigned int * partialReconnectRetryTimeout )
{
  if (baseRelayAddress)
    *baseRelayAddress = resultMsg.relayAddress;
  if (secondaryRelayAddress)
    *secondaryRelayAddress = resultMsg.secondaryRelayAddress;
  if (userId)
    *userId = resultMsg.userId;
  if(sessionId)
    *sessionId = resultMsg.sessionId;
  if ( relayCertificate )
    *relayCertificate = resultMsg.relayCertificate;
  if( sessionPath )
    *sessionPath = resultMsg.sessionPath.c_str();
  if (partialReconnectSupport)
    *partialReconnectSupport = resultMsg.partialReconnectSupport;
  if (partialReconnectRetries)
    *partialReconnectRetries = resultMsg.partialReconnectRetries;
  if (partialReconnectRetryTimeout)
    *partialReconnectRetryTimeout = resultMsg.partialReconnectRetryTimeout;

  MessageTrace( "Client: sessionPath='%s'", resultMsg.sessionPath.c_str() );
}

} //namespace Login
