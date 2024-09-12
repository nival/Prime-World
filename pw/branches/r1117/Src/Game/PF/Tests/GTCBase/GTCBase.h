#pragma once

#include <System/Basic.h>
#include <Server/RPC/GateKeeper.h>
#include <Server/rpc/LocalEntityFactory.h>
#include <Network/ClientTransportSystemIntf.h>
#include "Result.h"


namespace TransportLayer
{
  class TransportModule;
}

namespace lobbyTest
{
  class TestClientRunner;
}

namespace GameTestClient2
{
  namespace BaseStage
  {
    enum
    {
      INVALID = -1,
      INITIAL = 0,
      LOGIN_STARTED,
      LOGIN_FINISHED,
      LOGIN_FINISHED_POST_STEP,
    };
  };

  inline
  bool IsResultOk(int rc)
  {
    return (rc >= 0);
  }

  typedef NHPTimer::FTime Timestamp;

  class ClientBase : public rpc::IGateKeeperCallback
  {
    NI_DECLARE_CLASS( ClientBase )
      NI_DECLARE_BASE( rpc::IGateKeeperCallback )
    NI_DECLARE_END

  public:
    ClientBase(int localid, 
      Network::INetworkDriver * driver, 
      TransportLayer::TransportModule * sptm = 0, 
      unsigned int stepInMs = 100,
      nstl::string const & loginaddr = "",
      nstl::string const & user = "", 
      nstl::string const & pswd = "",
      nstl::string const & sessionKey = "",
      unsigned firstUdpPort = 0, unsigned udpPortSearchRange = 0 );
    ~ClientBase();

  public:
    Timestamp GetTime() { return NHPTimer::GetScalarTime(); }
    const nstl::string & getUserName() { return user_; }

    int stage() const { return stage_; }
    static char const * stageName(int st);

  public:
    virtual int Step();

  protected:
    //  rpc::IGateKeeperCallback
    virtual void OnNewNode( Transport::IChannel * channel, rpc::Node * node );
    virtual void OnChannelClosed( Transport::IChannel * channel, rpc::Node * node );
    virtual void OnCorruptData( Transport::IChannel * channel, rpc::Node * node );

  protected:
    void setStage( int _st ) { setStage( _st, 0 ); }
    void setStage( int _st, timer::Time _timeout );

    int lastresult() const { return lastresult_; }
    void setLastResult(int r) { lastresult_ = r; }

    void Poll();

    void exit(bool b) { bexit_ = b; }
    bool exit() { return bexit_; }

    int userid() const { return userId_; }

    StrongMT<rpc::GateKeeperClient> const & getGateKeeper() const { return gateKeeper_; }
    rpc::LocalEntityFactory* getLocalEntityFactory() const { return factory_; }

    Timestamp stepStartTime() const { return stepStartTime_; }
    unsigned int stepInMs() const { return stepInMs_; }
    unsigned int currentStep() const { return currentStep_; }

    StrongMT<Transport::IClientTransportSystem> clientTransport() const { return transport_; }

  private:
    //  login
    int startLogin();
    int checkLogin();

    bool checkTransportStatus();

  private:
    StrongMT<Network::INetworkDriver> netdriver_;
    StrongMT<TransportLayer::TransportModule> sptm_;
    StrongMT<Transport::IClientTransportSystem>  transport_;
    int userId_;
    StrongMT<rpc::GateKeeperClient> gateKeeper_;
    rpc::LocalEntityFactory* factory_;

    // test login
    Timestamp timeLoginStarted_;
    Timestamp timeLoginFinished_;

    // ---
    int stage_;
    timer::Time stageTimeout;
    int lastresult_;
    bool bexit_;

    nstl::string loginAddr_;
    nstl::string user_;
    nstl::string pswd_;
    nstl::string sessionKey_;
    int localid_;

    Timestamp stepStartTime_;
    unsigned int stepInMs_;
    unsigned int currentStep_;
  };
}
