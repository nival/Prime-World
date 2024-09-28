#pragma once

#include "IGameTestClient.h"
#include <System/Basic.h>
#include <Server/RPC/GateKeeper.h>
#include <Server/rpc/LocalEntityFactory.h>
#include <Network/ClientTransportSystemIntf.h>
#include <Network/FreePortsFinder.h>

namespace TransportLayer
{
  class TransportModule;
}

namespace lobbyTest
{
  class TestClientRunner;
}


namespace gtc
{

class IClientsContainer;

Transport::TServiceId const MatchMakingSvc = "matchmaking";
static char const * MatchMakingManagerObjPath = "matchmaking.manager";

typedef NHPTimer::FTime Timestamp;


struct TestClientBaseParams
{
  TestClientBaseParams(int _localid, 
    StrongMT<Network::INetworkDriver> _driver, 
    nstl::string const & _loginaddr = "",
    nstl::string const & _user = "", 
    nstl::string const & _pswd = "",
    unsigned int _sendFreq = 4,
    unsigned int _sendDataSize = 0,
    DWORD _mapLoadTimeout = 0,
    StrongMT<TransportLayer::TransportModule> const & _sptm = 0, 
    nstl::string const & _sessionKey = "",
    bool _traceStepConfirmation = false,
    bool _logGSStepLags = false,
    int _logEveryLagFromMs = 0,
    bool _chatMsgsInterval = 0,
    unsigned _firstUdpPort = 38001,
    unsigned _udpPortSearchRange = 10000,
    IClientsContainer * _clientsContainer = 0
    ) :
  localid( _localid ),
  driver( _driver ),
  loginaddr( _loginaddr ),
  user( _user ),
  pswd( _pswd ),
  sendFreq( _sendFreq ),
  sendDataSize( _sendDataSize ),
  mapLoadTimeout( _mapLoadTimeout ),
  sptm( _sptm ),
  sessionKey( _sessionKey ),
  traceStepConfirmation( _traceStepConfirmation ),
  logGSStepLags(_logGSStepLags),
  logEveryLagFromMs(_logEveryLagFromMs),
  chatMsgsInterval(_chatMsgsInterval),
  firstUdpPort( _firstUdpPort ),
  udpPortSearchRange( _udpPortSearchRange ),
  clientsContainer(_clientsContainer)
  {}

  int                                 localid;
  StrongMT<Network::INetworkDriver>   driver;
  nstl::string                        loginaddr;
  nstl::string                        user;
  nstl::string                        pswd;
  unsigned int                        sendFreq;
  unsigned int                        sendDataSize;
  DWORD                               mapLoadTimeout;
  StrongMT<TransportLayer::TransportModule> sptm;
  nstl::string                        sessionKey;
  bool                                traceStepConfirmation;
  bool                                logGSStepLags;
  int                                 logEveryLagFromMs;
  int                                 chatMsgsInterval;
  unsigned                            firstUdpPort;
  unsigned                            udpPortSearchRange;
  WeakMT<IClientsContainer>           clientsContainer;
};




class TestClientBase : public IGameTestClient, public rpc::IGateKeeperCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( TestClientBase, IGameTestClient, rpc::IGateKeeperCallback, BaseObjectMT );

public:
  TestClientBase( const TestClientBaseParams & _params );
  ~TestClientBase();

  static int DbgInstancesCount() { return instancesCount; }

  //int lastResult() const { return lastresult_; }
  //const nstl::string & getUserName() { return params.user; }

  //  login
  int startLogin();
  int checkLogin();

public:
  //IGameTestClient
  virtual void Init() {}
  virtual void Shutdown() {}
  virtual StepResult MainStep();
  virtual void TerminatePvx() {}
  virtual int Stage() const { return stage_; }
  virtual Transport::TClientId UserId() const { return userId_; }

  virtual void SetSocialClient( GtcSocial::SocialClient * _socClient ) { socialClient = _socClient; }
  virtual GtcSocial::SocialClient * SocialClient() const { return  socialClient; }

protected:
  bool checkTransportStatus();

  // rpc::IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel * channel, rpc::Node * node );
  virtual void OnChannelClosed( Transport::IChannel * channel, rpc::Node * node );
  virtual void OnCorruptData( Transport::IChannel * channel, rpc::Node * node );

  void StartOperationTimer( timer::Time _to, bool restart = false );
  void StopOperationTimer();
  timer::Time OperationDuration();

protected:
  static int instancesCount;

  TestClientBaseParams params;

  StrongMT<Transport::IClientTransportSystem>  transport_;
  int userId_;
  StrongMT<rpc::GateKeeperClient> gateKeeper_;
  rpc::LocalEntityFactory* factory_;

  // test login
  Timestamp timeLoginStarted_;

  // ---
  int stage_;
  int lastresult_;
  bool bexit_;

  StrongMT<GtcSocial::SocialClient> socialClient;

  timer::Time operationStart, operationTimeout;
}; //class TestClientBase

} //namespace gtc
