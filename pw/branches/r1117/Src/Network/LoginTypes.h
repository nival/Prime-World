#ifndef NETWORK_LOGINTYPES_H_INCLUDED
#define NETWORK_LOGINTYPES_H_INCLUDED

#include "System/EnumToString.h"
#include "Network/TransportTypes.h"
#include "Network/Address.h"

namespace Login
{

namespace ELoginResult
{
  enum Enum
  {
    NoResult = 0,
    NoConnection,
    Refused,
    AlreadyIn,
    ServerError,
    Success,
    ClientOutdated,
    ServerOutdated,
    UndefinedSex,
    AccessDenied,
    AsyncWait, // internal: async login processsing started, but no reply yet
    AsyncTimeout, // internal: cluster operation resulted in timeout (not failed tho')
    AsyncSuccess,
    AsyncFail
  };

  NI_ENUM_DECL_STD;
}



namespace LoginType
{
  enum Enum
  {
    ORDINARY = 0,
    FAST_RECONNECT = 1,
    PARTIAL_RECONNECT = 2,
  };

  NI_ENUM_DECL_STD;
}

#if defined( NV_LINUX_PLATFORM )
inline unsigned short MAKEWORD( unsigned char lo, unsigned char hi )
{
  return ( static_cast< unsigned short >( hi ) << 8 ) | lo;
}
#endif  

static const ushort PROTOCOL_VERSION = MAKEWORD( 5, 5 ); //Transport version 3, RPC version 5 - not used

struct LoginRequestMessage 
{
  ZDATA
  ushort protocolVersion; //  here for compatibility with old unversioned clients
  string login;
  string password;
  string sessionKey; // для SessionLogin
  ushort majorVer;
  ushort minorVer;
  uint   patchVer;
  uint   revisionVer;
  LoginType::Enum loginType;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&protocolVersion); f.Add(3,&login); f.Add(4,&password); f.Add(5,&sessionKey); f.Add(6,&majorVer); f.Add(7,&minorVer); f.Add(8,&patchVer); f.Add(9,&revisionVer); f.Add(10, &loginType); return 0; }
  LoginRequestMessage() : protocolVersion(PROTOCOL_VERSION), majorVer(ushort(0)), minorVer(ushort(-1)), patchVer(uint(-1)), revisionVer(uint(-1)), loginType(LoginType::ORDINARY) {}  
};



struct LoginResultMessage 
{
  ZDATA
  ELoginResult::Enum loginResult;
  Network::NetAddress relayAddress;
  int userId;
  string sessionId;
  string relayCertificate;
  Transport::TServiceId sessionPath; // куда ломиться после SessionLogin
  Network::NetAddress secondaryRelayAddress;
  bool partialReconnectSupport;
  unsigned int partialReconnectRetries;
  unsigned int partialReconnectRetryTimeout;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&loginResult); f.Add(3,&relayAddress); f.Add(4,&userId); f.Add(5,&sessionId); f.Add(6,&relayCertificate); f.Add(7,&sessionPath); f.Add(8,&secondaryRelayAddress); f.Add(9,&partialReconnectSupport); f.Add(10, &partialReconnectRetries); f.Add(11, &partialReconnectRetryTimeout); return 0; }
  LoginResultMessage() 
    :loginResult(ELoginResult::NoResult),
    userId(-1), 
    partialReconnectSupport(false),
    partialReconnectRetries(0),
    partialReconnectRetryTimeout(0)
  {}
};
  
} //namespace Login

#endif //NETWORK_LOGINTYPES_H_INCLUDED
