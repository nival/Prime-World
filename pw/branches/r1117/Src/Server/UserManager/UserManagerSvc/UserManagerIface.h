#pragma once
#include <RPC/RPC.h>
#include <Network/Address.h>
#include <Network/TransportTypes.h>
#include <Network/LoginData.h>
#include <ClusterTypes/ClusterTypes.h>
#include "UserEnvInfo.h"
#include <Coordinator/ServiceRole.h>

namespace UserManager
{
  namespace Result
  {
    enum Enum
    {
      PARTIAL_RECONNECT_NOT_SUPPORTED = -6,
      USER_ALREADY_REGISTERED = -5,
      RELAY_ALLOCATION_FAILED = -4,
      REQUEST_FOR_SUCH_USER_ALREADY_REGISTERED = -3,
      NO_RELAY_BALANCER = -2,
      FAIL = -1,
      SUCCESS = 0,
      IN_PROGRESS = 1,
    };

    inline
    char const * const ToString(Enum err)
    {
      switch(err)
      {
      case PARTIAL_RECONNECT_NOT_SUPPORTED:
        return "Partial reconnect not supported";
      case USER_ALREADY_REGISTERED:
        return "User already registered";
      case RELAY_ALLOCATION_FAILED:
        return "Relay allocation is failed";
      case REQUEST_FOR_SUCH_USER_ALREADY_REGISTERED:
        return "Request for such user already registered";
      case NO_RELAY_BALANCER:
        return "There is no relay balancer";
      case FAIL:
        return "Ti kto takoi, davai dosvidaniya";
      case SUCCESS:
        return "Success";
      case IN_PROGRESS:
        return "In progress";
      default:
        return "Unknown error";
      }
    }
  }

  struct UserSessionInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    Cluster::TUserId userid_;
    Transport::TServiceId sessionPath_;
    bool partialReconnect_;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid_); f.Add(3,&sessionPath_); f.Add(4,&partialReconnect_); return 0; }

    UserSessionInfo() : userid_(Cluster::INVALID_USER_ID) {}
    UserSessionInfo(Cluster::TUserId const & _userid, Transport::TServiceId const & _sessionPath, bool _partialReconnect)
      :userid_(_userid), sessionPath_(_sessionPath), partialReconnect_(_partialReconnect)
    {}
  };

  struct RelayInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    Transport::TServiceId primary_;
    Network::NetAddress primaryAddr_;
    Transport::TServiceId secondary_;
    Network::NetAddress secondaryAddr_;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&primary_); f.Add(3,&primaryAddr_); f.Add(4,&secondary_);  f.Add(5,&secondaryAddr_); return 0; }

    RelayInfo(){}
    RelayInfo(Transport::TServiceId const & _primary, Network::NetAddress const & _primaryAddr,
      Transport::TServiceId const & _secondary, Network::NetAddress const & _secondaryAddr)
      :primary_(_primary), primaryAddr_(_primaryAddr), secondary_(_secondary), secondaryAddr_(_secondaryAddr)
    {}
  };

  struct PartialReconnectInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    bool supported_;
    unsigned int retries_;
    unsigned int retryTimeout_;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&supported_); f.Add(3,&retries_); f.Add(4,&retryTimeout_); return 0; }

    PartialReconnectInfo(){}
    PartialReconnectInfo(bool _supported, unsigned int _retries, unsigned int _retryTimeout)
      :supported_(_supported),
      retries_(_retries),
      retryTimeout_(_retryTimeout)
    {}
  };

  REMOTE class IPrepareUserEnvCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IPrepareUserEnvCallback, IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnPrepareUserEnv(int _result, Cluster::TUserId _userid, RelayInfo const & _relayInfo, PartialReconnectInfo const & _partialReconnectInfo) = 0;
  };

  REMOTE class IUserManager : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IUserManager, IBaseInterfaceMT );
    RPC_ID();

  public:
    REMOTE virtual bool AddUser(Cluster::TUserId _userId, string const & _sessionKey, Transport::TServiceId const & _sessionPath, wstring const & _username) = 0;
    REMOTE virtual bool RemoveUser(Cluster::TUserId _userId) = 0;
    REMOTE virtual UserSessionInfo FindUserSession(string const & _sessionKey, bool _partialReconnect) = 0;

    REMOTE virtual Result::Enum PrepareUserEnv(UserManager::UserEnvInfo const & uei, UserManager::IPrepareUserEnvCallback* cb) = 0;

    REMOTE virtual bool OnUserLeave(Cluster::TUserId _userId, Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole) = 0;

  };
}
