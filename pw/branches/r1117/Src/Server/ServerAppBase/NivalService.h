#ifndef NIVALSERVICE_H_INCLUDED
#define NIVALSERVICE_H_INCLUDED

#include "ServerRunner.h"
#include "System/JobThread.h"
#include "RPC/GateKeeper.h"
#include "RPC/LocalEntityFactory.h" 
#include "Monitoring/PerfCounterProvider/PerfCounterProvider.h"
#include "PerfCounters.h"
#include <map>
#include <string>


namespace rdp_transport
{
  class FrontendAgent;
}


namespace Transport
{

struct CustomServiceParams
{
  int                             sleep;
  bool                            ownLogChannel;
  string                          logChannelSuffix;

  explicit CustomServiceParams( bool _ownLogChannel = true, const char * _logSuffix = "" ) :
  sleep( 10 ),
  ownLogChannel( _ownLogChannel ),
  logChannelSuffix( _logSuffix )
  {}
};



class BaseService : public rpc::IGateKeeperCallback, public threading::IThreadJob, public IPerfCounters, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_4( BaseService, rpc::IGateKeeperCallback, threading::IThreadJob, IPerfCounters, BaseObjectMT );

public:
  BaseService( const ServiceParams & _svcParams, const CustomServiceParams & _customParams );

  ~BaseService();

  void StopSoftly();
  void ReloadConfig();

  //IPerfCounters
  virtual void AutoPerfCounterRate( const char * _name, unsigned _number );
  virtual void AutoPerfCounterValue( const char * _name, double _value );

protected:
  //Overridables
  virtual void ThreadMain( volatile bool & _isRunning ); //Use with caution!
  virtual void Poll( timer::Time _now ) {}
  virtual void OnSoftStop() { NI_ALWAYS_ASSERT( "Soft stop not implemented" ); }
  virtual void OnConfigReload() { NI_ALWAYS_ASSERT( "Config reload not implemented" ); }

  //Utility
  const Transport::TServiceId & SvcId() const { return svcParams.serviceId; }
  Transport::ITransportSystem * BackendTransport() const { return svcParams.backendTransport; }
  Transport::ITransportSystem * FrontendTransport() const { return svcParams.frontendTransport ? svcParams.frontendTransport : svcParams.backendTransport; }

  Coordinator::ICoordinatorClient * CoordClient() const { return svcParams.coordClient; }

  Network::INetworkDriver * NetworkDriver() const { return svcParams.driver; }

  rpc::GateKeeper * BackendGk() const { return backendGateKeeper; }
  rpc::GateKeeper * FrontendGk() const { return frontendGateKeeper ? frontendGateKeeper : backendGateKeeper; }

  rpc::LocalEntityFactory * BackendRpcFactory() const { return Get( backendRpcFactory ); }
  rpc::LocalEntityFactory * FrontendRpcFactory() const { return frontendRpcFactory ? Get( frontendRpcFactory ) : Get( backendRpcFactory ); }

  const CustomServiceParams & CustomParams() const { return customParams; }
  const Transport::TServiceOptions & SvcOptions() const { return svcParams.options; }
  const Transport::TServerCmdLine & ServerCmdLine() const { return svcParams.commandLine; }

  timer::Time Now() const { return now; }

  template <typename T> void RegisterBackendObject( T * _obj, const char * _id, const char * _password = 0 ) {
    BackendGk()->GetGate()->RegisterObject<T>( _obj, _id, _password );
  }

  template <typename T> void RegisterFrontendObject( T * _obj, const char * _id, const char * _password = 0 ) {
    FrontendGk()->GetGate()->RegisterObject<T>( _obj, _id, _password );
  }

  template <typename T> void UnregisterBackendObject( T * _obj ) {
    BackendGk()->GetGate()->UnregisterObject<T>( _obj );
  }

  template <typename T> void UnregisterFrontendObject( T * _obj ) {
    FrontendGk()->GetGate()->UnregisterObject<T>( _obj );
  }

  template <typename O, typename L> void RegisterBackendAttach() {
    BackendRpcFactory()->RegisterAttach<O, L>();
  }

  template <typename O, typename L> void RegisterFrontendAttach() {
    FrontendRpcFactory()->RegisterAttach<O, L>();
  }

  int RegisterPerfCounter( const string & _name, NDebug::IDebugVar * _dv, bool _toCumulate = false, int _samplingPeriod = 15 );
  int UnregisterPerfCounter( const string & _name );

  bool GetLoginForActiveFrontendUser( Transport::TClientId _uid, string & _login );

  // rpc::IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel * channel,  rpc::Node * node );
  virtual void OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node );
  virtual void OnCorruptData( Transport::IChannel * channel,  rpc::Node * node );

  void PollInternal();

private:
  class AutoPerfCounter;

  typedef std::map<std::string, StrongMT<AutoPerfCounter> > AutoPerfCounters;

  ServiceParams svcParams;
  CustomServiceParams customParams;
  timer::Time now;
  StrongMT<rpc::GateKeeper> backendGateKeeper, frontendGateKeeper;
  ScopedPtr<rpc::LocalEntityFactory> backendRpcFactory, frontendRpcFactory;
  StrongMT<rdp_transport::FrontendAgent> frontendAgent;

  StrongMT<Monitoring::PerfCounterProvider> perfCounterProvider;
  AutoPerfCounters   perfCounters;
  StrongMT<NLogg::BasicTextFileDumper> fileDumper;
  threading::Mutex globalMutex;
  threading::Mutex perfCountersMutex;

  virtual void Work( volatile bool & _isRunning );

  AutoPerfCounter * AccessAutoPerfCounter( const char * _name, bool _rateMode );
  void PollPerfCounters();
};

} //namespace Transport

#endif //NIVALSERVICE_H_INCLUDED
