#pragma once

#include "MonitoringSvc/MonitoringIface.h"
#include <Coordinator/ServiceAppearanceNotifierIface.h>
#include <Coordinator/RServiceAppearanceNotifierIface.auto.h>
#include <rpc/IfaceRequester.h>
#include "MonitoringSvc/CumulativePerfCounter.h"

namespace Monitoring
{
  class MonitorCore;

  class MonitorImpl : public IMonitor, public Coordinator::IServiceAppearanceSubscriber, 
    public rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>, 
    public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_4( MonitorImpl, 
      IMonitor, 
      Coordinator::IServiceAppearanceSubscriber, 
      rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>, 
      BaseObjectMT );

    RPC_REDEFINE_ID();

  public:
    MonitorImpl(StrongMT<rpc::GateKeeper> const & _gk, StrongMT<MonitorCore> const & _moncore);
    ~MonitorImpl();

    void Step();

  public:
    //  IMonitor
    virtual int RegisterPerfCounter(Transport::TServiceId const & _svcid, nstl::string const & _pcname, int _type, int _defaultSamplingPeriod, bool _toCumulate);
    virtual int UnregisterPerfCounter(Transport::TServiceId const & _svcid, nstl::string const & _pcname);

    //  Coordinator::IServiceAppearanceSubscriber
    virtual void OnRegisterSubscriber(Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const & cluster);
    virtual void OnRegisterService( Transport::TServiceId const & svcid );
    virtual void OnUnregisterService( Transport::TServiceId const & svcid );
    virtual void OnStartService( Coordinator::SvcInfo const & ssi );
    virtual void OnStopService( Transport::TServiceId const & svcid );
    virtual void OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/ int _status);

  private:
    //  rpc::IfaceRequesterCallback<Coordinator::RIServiceAppearancePublisher>
    void onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>> const & ifacereq);

  private:

    typedef StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>> SvcPublisherIfaceReqT;
    SvcPublisherIfaceReqT svcPublisherIfaceReq_;
    Coordinator::SubcriberIdT subscriberId_;

    StrongMT<MonitorCore> moncore_;
  };
}
