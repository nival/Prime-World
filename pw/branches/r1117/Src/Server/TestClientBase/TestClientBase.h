#pragma once

#include <System/Basic.h>
#include <Server/RPC/P2PNode.h>
#include <Server/RPC/GateKeeper.h>
#include <Server/rpc/LocalEntityFactory.h>
#include <Server/Network/ClientTransportSystemIntf.h>

#include "System/HPTimer.h"
typedef NHPTimer::FTime Timestamp;

namespace TransportLayer
{
  class TransportModule;
}

namespace TestClientNs
{
  class ClientBase : public IObjectBase
  {
  public:
    struct Stage
    {
      enum
      {
        NONE = 0,
        INVALID = 1,
        LOGIN_STARTED = 2,
        LOGIN_FINISHED = 3
      };
    };

    struct Result
    {
      enum 
      {
        NONE = -2,
        FAIL = -1,
        SUCCESS = 0,
        IN_PROGRESS = 1
      };
    };

    static const int LOGIN_TIMEOUT_SECONDS = 120;

  public:

    ClientBase();
    ClientBase(StrongMT<Network::INetworkDriver> driver, 
      nstl::string const & loginaddr = "",
      nstl::string const & user = "", 
      nstl::string const & pswd = "",
      StrongMT<TransportLayer::TransportModule> const & sptm = 0);
    ~ClientBase();

    int stage() const;
    int lastResult() const;

    int startLogin();
    int startLogin(string const & netaddr, string const & username, string const & pass);
    int checkLogin();

    //bool Step();

  protected:
    int startLogin_(string const & loginaddr, string const & username, string const & pswd);

  protected:
    StrongMT<Network::INetworkDriver> netdriver_;
    StrongMT<TransportLayer::TransportModule> sptm_;
    Transport::TServiceId svcname_;
    CObj<Transport::IClientTransportSystem>  transport_;
    int userid_;

    int stage_;
    int lastresult_;
    bool bexit_;
    Timestamp timeLoginStarted_;

    nstl::string loginAddr_;
    nstl::string user_;
    nstl::string pswd_;
  };

  inline int ClientBase::stage() const
  {
    return stage_;
  }

  inline int ClientBase::lastResult() const
  {
    return lastresult_;
  }
}
