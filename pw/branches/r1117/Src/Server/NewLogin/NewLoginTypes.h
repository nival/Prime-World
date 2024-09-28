#ifndef NEWLOGINTYPES_H_INCLUDED
#define NEWLOGINTYPES_H_INCLUDED

#pragma warning(disable:4238)


#include "Server/RPC/Base.h"
#include "Network/TransportAddress.h"
#include "Network/Address.h"
#include "System/EnumToString.h"
#include "Network/LoginTypes.h"


namespace newLogin
{

namespace serviceIds
{
  const Transport::TServiceId Service = "newlogin";
  static const char * SessionKeySvc   = "newlogin:keys";
} //namespace serviceIds



namespace ESvcConnectionResult
{
  enum Enum
  {
    Ok = 0,
    UnknownSvc,
    Timeout,
    OutOfSvcResources,
    ServerFault,
    WrongFrontendKey
  };

  NI_ENUM_DECL_STD;
}



typedef nstl::fixed_string<char, 64> LoginString;
typedef nstl::fixed_string<char, 64> PasswordString;
typedef nstl::fixed_string<char, 32> SessionKeyString;
typedef nstl::fixed_string<char, 64> WelcomeString;
typedef nstl::fixed_string<char, 32> KeyString;
typedef nstl::fixed_string<char, 64> AddressString;



struct LoginHello : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  int clientRevision;
  int protocolVersion;
  LoginString login;
  PasswordString password;
  SessionKeyString sessionkey;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientRevision); f.Add(3,&protocolVersion); f.Add(4,&login); f.Add(5,&password); f.Add(6,&sessionkey); return 0; }

  LoginHello()
    : clientRevision( 0 )
    , protocolVersion( 0 )
  {
  }

  LoginHello(const LoginHello& other)
    : rpc::Data(other)
    , clientRevision(other.clientRevision)
    , protocolVersion(other.protocolVersion)
    , login(other.login)
    , password(other.password)
    , sessionkey(other.sessionkey)
  {
  }

  LoginHello& operator=(const LoginHello& other)
  {
    rpc::Data::operator=(other);
    clientRevision = other.clientRevision;
    protocolVersion = other.protocolVersion;
    login = other.login;
    password = other.password;
    sessionkey = other.sessionkey;
    return *this;
  }
};



struct LoginReply : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  Login::ELoginResult::Enum   code;
  Transport::TClientId        uid;
  WelcomeString               welcomingSvcId;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&code); f.Add(3,&uid); f.Add(4,&welcomingSvcId); return 0; }

  LoginReply()
    : code( Login::ELoginResult::NoResult )
    , uid( 0 )
  {
  }

  LoginReply(const LoginReply& other)
    : rpc::Data(other)
    , code(other.code)
    , uid(other.uid)
    , welcomingSvcId(other.welcomingSvcId)
  {
  }

  LoginReply& operator=(const LoginReply& other)
  {
    rpc::Data::operator=(other);
    code = other.code;
    uid = other.uid;
    welcomingSvcId = other.welcomingSvcId;
    return *this;
  }
};



struct ServiceRequest : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  int                         requestId;
  Transport::TServiceId       svcId;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&requestId); f.Add(3,&svcId); return 0; }

  ServiceRequest()
    : requestId( 0 )
  {
  }

  ServiceRequest(const ServiceRequest& other)
    : rpc::Data(other)
    , requestId(other.requestId)
    , svcId(other.svcId)
  {
  }

  ServiceRequest& operator=(const ServiceRequest& other)
  {
    rpc::Data::operator=(other);
    requestId = other.requestId;
    svcId = other.svcId;
    return *this;
  }
};



struct ServiceReqReply : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  int                         requestId;
  Transport::TServiceId       svcId;
  ESvcConnectionResult::Enum  code;
  mutable AddressString               externalAddress;
  KeyString                   key;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&requestId); f.Add(3,&svcId); f.Add(4,&code); f.Add(5,&externalAddress); f.Add(6,&key); return 0; }

  ServiceReqReply()
    : code( ESvcConnectionResult::Ok )
  {
  }

  ServiceReqReply(const ServiceReqReply& other)
    : rpc::Data(other)
    , requestId(other.requestId)
    , svcId(other.svcId)
    , code(other.code)
    , externalAddress(other.externalAddress)
    , key(other.key)
  {
  }

  ServiceReqReply& operator=(const ServiceReqReply& other)
  {
    rpc::Data::operator=(other);
    requestId = other.requestId;
    svcId = other.svcId;
    code = other.code;
    externalAddress = other.externalAddress;
    key = other.key;
    return *this;
  }
};



struct FrontendHello : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  Transport::TClientId        uid;
  KeyString                   key;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&uid); f.Add(3,&key); return 0; }

  FrontendHello()
    : uid( 0 )
  {
  }

  FrontendHello(const FrontendHello& other)
    : rpc::Data(other)
    , uid(other.uid)
    , key(other.key)
  {
  }

  FrontendHello& operator=(const FrontendHello& other)
  {
    rpc::Data::operator=(other);
    uid = other.uid;
    key = other.key;
    return *this;
  }
};



struct FrontendHelloReply : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  ESvcConnectionResult::Enum  code;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&code); return 0; }

  FrontendHelloReply()
    : code( ESvcConnectionResult::Ok )
  {
  }

  FrontendHelloReply(const FrontendHelloReply& other)
    : rpc::Data(other)
    , code(other.code)
  {
  }

  FrontendHelloReply& operator=(const FrontendHelloReply& other)
  {
    rpc::Data::operator=(other);
    code = other.code;
    return *this;
  }
};

} //namespace newLogin

#endif //NEWLOGINTYPES_H_INCLUDED
