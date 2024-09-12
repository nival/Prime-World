#include "stdafx.h"
#include "NivalService.h"
#include "System/InlineProfiler.h"
#include "System/EventAccumulator.h"
#include "RdpTransport/RdpFrontendAgent.h"
#include "RdpTransport/LRdpFrontendAgentInterface.auto.h"
#include "System/sleep.h"


NI_DEFINE_REFCOUNT( Transport::IPerfCounters );


namespace Transport
{

class BaseService::AutoPerfCounter : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( AutoPerfCounter, BaseObjectMT );

public:
  AutoPerfCounter( bool _measureRate, const char * _name, const char * _svcId, timer::Time _now ) :
  measureRate( _measureRate ),
  accu( 60.0, 6, _now ),
  debugVar( _name, _svcId )
  {}

  bool measureRate;
  EventAccumulator  accu;
  NDebug::DebugVar<volatile int> debugVar;
};





BaseService::BaseService( const ServiceParams & _svcParams, const CustomServiceParams & _customParams ) :
svcParams( _svcParams ),
customParams( _customParams ),
now( timer::Now() )
{
  if ( customParams.ownLogChannel )
  {
    string channelFileSuffix, channelId;
    if ( customParams.logChannelSuffix.empty() )
    {
      Transport::TServiceId svcclass;
      Transport::GetServiceClass( svcParams.serviceId, svcclass );

      channelFileSuffix = svcParams.serviceId.c_str();
      NStr::ReplaceAllChars( &channelFileSuffix, '/', '_' );
      channelId = svcclass.c_str();
    }
    else
    {
      channelFileSuffix = customParams.logChannelSuffix;
      channelId = customParams.logChannelSuffix;
    }

    fileDumper = NLogg::BasicTextFileDumper::New( 0, channelFileSuffix.c_str() );
    StrongMT<NLogg::CDumper> stdoutDumper = GetSystemLog().FindDumperByName("stdout");
    if (stdoutDumper)
      GetSystemLog().AddChannel( channelId.c_str(), fileDumper, stdoutDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );
    else
      GetSystemLog().AddChannel( channelId.c_str(), fileDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );
  }

  backendGateKeeper = new rpc::GateKeeper( svcParams.backendTransport, svcParams.serviceId, Transport::autoAssignClientId, this );
  Reset( backendRpcFactory, new rpc::LocalEntityFactory( backendGateKeeper->GetGate() ) );

#if defined( NV_WIN_PLATFORM )
  if ( svcParams.frontendTransport )
  {
    frontendAgent = new rdp_transport::FrontendAgent( now );
    svcParams.frontendTransport->AddFrontendAuth( svcParams.serviceId, frontendAgent );

    RegisterBackendAttach<rdp_transport::IFrontendAgent, rdp_transport::LIFrontendAgent>();
    RegisterBackendObject<rdp_transport::IFrontendAgent>( frontendAgent, rdp_transport::IFrontendAgent::InterfaceId );

    frontendGateKeeper = new rpc::GateKeeper( svcParams.frontendTransport, svcParams.serviceId, Transport::autoAssignClientId, this );
    Reset( frontendRpcFactory, new rpc::LocalEntityFactory( frontendGateKeeper->GetGate() ) );
  }
#endif

  //  performance counter provider
  nstl::string tmp( svcParams.serviceId.c_str() );
  tmp += Monitoring::intfSuffix;
  perfCounterProvider = new Monitoring::PerfCounterProvider( backendGateKeeper, svcParams.serviceId );
  RegisterBackendObject<Monitoring::IPerfCounterProvider>( perfCounterProvider.Get(), tmp.c_str() );
}



BaseService::~BaseService()
{
  Reset( backendRpcFactory, (rpc::LocalEntityFactory*)0 );
  Reset( frontendRpcFactory, (rpc::LocalEntityFactory*)0 );
}



void BaseService::StopSoftly()
{
  threading::MutexLock lock( globalMutex );

  OnSoftStop();
}



void BaseService::ReloadConfig()
{
  threading::MutexLock lock( globalMutex );

  OnConfigReload();
}



BaseService::AutoPerfCounter * BaseService::AccessAutoPerfCounter( const char * _name, bool _rateMode )
{
  StrongMT<AutoPerfCounter> & slot = perfCounters[_name];
  if ( !slot )
  {
    slot = new AutoPerfCounter( _rateMode, _name, svcParams.serviceId.c_str(), now );
    RegisterPerfCounter( _name, &slot->debugVar, true, 10 );
  }
  else
  {
    if ( _rateMode )
      NI_VERIFY( slot->measureRate, "Wrong perfcounter mode, whould be 'rate'", return 0 )
    else
      NI_VERIFY( !slot->measureRate, "Wrong perfcounter mode, whould be 'value'", return 0 );
  }

  return slot;
}



void BaseService::AutoPerfCounterRate( const char * _name, unsigned _number )
{
  threading::MutexLock lock( perfCountersMutex );

  if ( AutoPerfCounter * slot = AccessAutoPerfCounter( _name, true ) )
    slot->accu.AddEvent( _number, 0.0 );
}



void BaseService::AutoPerfCounterValue( const char * _name, double _value )
{
  threading::MutexLock lock( perfCountersMutex );

  if ( AutoPerfCounter * slot = AccessAutoPerfCounter( _name, false ) )
    slot->accu.AddEvent( 1, _value );
}



void BaseService::PollPerfCounters()
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( perfCountersMutex );

  if ( perfCounterProvider )
    perfCounterProvider->step();

  for ( AutoPerfCounters::iterator it = perfCounters.begin(); it != perfCounters.end(); ++it )
  {
    StrongMT<AutoPerfCounter> counter = it->second;

    counter->accu.Poll( now );

    double value = counter->measureRate ? 60.0 * counter->accu.AvgRate() : counter->accu.AvgValue();

    counter->debugVar.SetValue( (int)value );
  }
}



void BaseService::ThreadMain( volatile bool & _isRunning )
{
  while ( _isRunning )
  {
    NI_PROFILE_BLOCK( "Main" )

    PollInternal();

    {
      NI_PROFILE_BLOCK( "Sleep" );
      nival::sleep( customParams.sleep );
    }
  }
}



void BaseService::Work( volatile bool & _isRunning )
{
  NI_PROFILE_THREAD;

  ThreadMain( _isRunning );
}




void BaseService::PollInternal()
{
  NI_PROFILE_FUNCTION;

  timer::Time t = timer::Now();

  threading::MutexLock lock( globalMutex );

  timer::Time pollTime = t - now;
  if ( now && ( pollTime > 1.0 ) )
    ErrorTrace( "Poll exceeded! svc_id=%s, dur=%.1f sec", svcParams.serviceId.c_str(), pollTime );
  now = t;

  if ( backendGateKeeper ) 
    backendGateKeeper->Poll();

  if ( frontendGateKeeper ) 
    frontendGateKeeper->Poll();

#if defined( NV_WIN_PLATFORM )
  if ( frontendAgent )
    frontendAgent->Poll( now );
#endif

  PollPerfCounters();

  {
    NI_PROFILE_BLOCK( "Poll" )
    Poll( t );
  }
}



void BaseService::OnNewNode( Transport::IChannel * channel,  rpc::Node * node )
{
  DebugTrace( "BaseService::OnNewNode. uid=%d, node=%s", channel ? channel->GetInternalClientId() : 0, node ? node->GetName() : "<null>" );
}



void BaseService::OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node )
{
  MessageTrace( "BaseService::OnChannelClosed. uid=%d, node=%s", channel ? channel->GetInternalClientId() : 0, node ? node->GetName() : "<null>" );
}



void BaseService::OnCorruptData( Transport::IChannel * channel,  rpc::Node * node )
{
  ErrorTrace( "BaseService::OnCorruptData. uid=%d, node=%s", channel ? channel->GetInternalClientId() : 0, node ? node->GetName() : "<null>" );
}



int BaseService::RegisterPerfCounter(nstl::string const & _name, NDebug::IDebugVar* _dv, bool _toCumulate, int _samplingPeriod)
{
  if (!_dv)
  {
    WarningTrace( "Can't register performance counter: %s", _name );
    return -1;
  }

  return perfCounterProvider->RegisterPerfCounter(_name, _dv, _toCumulate, _samplingPeriod);
}



int BaseService::UnregisterPerfCounter(nstl::string const & name)
{
  return perfCounterProvider->UnregisterPerfCounter(name);
}



bool BaseService::GetLoginForActiveFrontendUser( Transport::TClientId _uid, string & _login )
{
  if ( !frontendAgent )
    return false;

#if defined( NV_WIN_PLATFORM )
  return frontendAgent->GetActiveUserLogin( _uid, _login );
#else
  return false;
#endif
  
}

} //namespace Transport
