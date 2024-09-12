#include "stdafx.h"
#include "MonitoringSvc/MonitoringImpl.h"
#include "MonitoringSvc/MonitorCore.h"
#include <Coordinator/CoordinatorServerNaming.h>
#include "Server/ServerAppBase/ServerCfg.h"
#include "MonitoringSvc/MonitoringCfg.h"

NI_DEFINE_REFCOUNT(Monitoring::MonitorImpl);

namespace Monitoring
{
  MonitorImpl::MonitorImpl(StrongMT<rpc::GateKeeper> const & _gk, StrongMT<MonitorCore> const & _moncore)
    :subscriberId_(-1),
    moncore_(_moncore)
  {
    svcPublisherIfaceReq_ = new rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>;
    int rc = svcPublisherIfaceReq_->init(_gk, Transport::ENetInterface::Coordinator, Coordinator::SvcAppearancePublisherIfaceId, 
                                         &GetSystemLog(), MONLOG, this);
    if (rc < 0)
    {
      LOG_A(MONLOG).Trace("Can't init rpc iface requester(node=%s iface=%s)", Transport::ENetInterface::Coordinator.c_str(),
        Coordinator::SvcAppearancePublisherIfaceId);
    }
  }

  MonitorImpl::~MonitorImpl()
  {
  }

  void MonitorImpl::Step()
  {
    svcPublisherIfaceReq_->step();
  }

  void MonitorImpl::onChangeState(rpc::IfaceRequesterState::Enum st, 
    StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>> const & ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == st)
    {
      LOG_M(MONLOG).Trace("Service publisher iface received");
      ifacereq->iface()->RegisterSubscriber(this);
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == st)
    {
      LOG_W(MONLOG).Trace("Service publisher iface closed");
      subscriberId_ = -1;
    }
  }

  void MonitorImpl::OnRegisterSubscriber(Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const & cluster)
  {
    LOG_D(MONLOG).Trace("%s(sid=%d)", __FUNCTION__, id);

    if (id < 0)
    {
      LOG_E(MONLOG).Trace("Can't be registered as subscriber(rc=%d)", id);
      return;
    }

    subscriberId_ = id;

    LOG_M(MONLOG).Trace("Cluster services:");
    Coordinator::ClusterInfo::SvcInfosT const & svcinfos = cluster.svcinfos;
    for(Coordinator::ClusterInfo::SvcInfosT::const_iterator cit = svcinfos.begin(); cit != svcinfos.end(); ++cit)
    {
      Coordinator::SvcInfo const & si = *cit;
      LOG_M(MONLOG).Trace("Service svcid=%s netaddr=%s status=%s)", 
                          si.svcid.c_str(), si.netaddr.c_str(), Coordinator::ServiceStatus::ToString(si.st));
    }

    LOG_M(MONLOG).Trace("Registered as subscriber successfully(id=%d)", id);
  }

  void MonitorImpl::OnRegisterService( Transport::TServiceId const & _svcid )
  {
  }

  void MonitorImpl::OnUnregisterService( Transport::TServiceId const & svcid )
  {
  }

  void MonitorImpl::OnStartService( Coordinator::SvcInfo const & ssi )
  {
  }

  void MonitorImpl::OnStopService( Transport::TServiceId const & _svcid )
  {
    LOG_D(MONLOG).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }

  void MonitorImpl::OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/ int _status)
  {
    LOG_D(MONLOG).Trace("%s(svcid=%s status=%s)", __FUNCTION__, _svcid.c_str(), Coordinator::ServiceStatus::ToString((Coordinator::ServiceStatus::Enum)_status));
  }

  int MonitorImpl::RegisterPerfCounter(Transport::TServiceId const & _svcid, nstl::string const & _pcname, int _type, int _defaultSamplingPeriod, bool _toCumulate)
  {
    LOG_D(MONLOG).Trace("%s(svcid=%s perfCounter=%s type=%d samplingPeriod=%d toCumulate=%d)", 
      __FUNCTION__, _svcid.c_str(), _pcname.c_str(), _type, _defaultSamplingPeriod, (int)_toCumulate);

    StrongMT<PerfCounterCtx> pc;
    int rc = moncore_->CreatePerfCounter(_svcid, _pcname, NDebug::DebugVarType::Enum(_type), _defaultSamplingPeriod, Cfg::GetProviderRepairTimeout(), pc);
    if (0 == rc)
    {
      if (_toCumulate)
      {
        int svcidx = Transport::GetServerIndex(_svcid);
        if (svcidx >= 0)
        {
          Transport::TServiceId svcls;
          Transport::GetServiceClass(_svcid, svcls);

          StrongMT<CumulativePerfCounter> cpc;
          string path = moncore_->createPerfCounterPath(svcls, pc->name());
          StrongMT<PerfCounterCtx> ecpc = moncore_->FindPerfCounter(path);
          if (ecpc)
          {
            cpc = static_cast<CumulativePerfCounter*>(ecpc.Get());
          }
          else
          {
            cpc = new CumulativePerfCounter(path, pc->name(), pc->type());
            rc = moncore_->RegisterPerfCounter(StrongMT<PerfCounterCtx>(cpc));
            if (rc >= 0)
            {
              LOG_M(MONLOG).Trace("New cumulative counter registered(path=%s svcid=%s perfCounter=%s type=%d samplingPeriod=%d)", 
                cpc->path().c_str(), _svcid.c_str(), _pcname.c_str(), _type, _defaultSamplingPeriod);
            }
            else
            {
              LOG_E(MONLOG).Trace("Can't register cumulative counter(path=%s svcid=%s perfCounter=%s type=%d samplingPeriod=%d)", 
                cpc->path().c_str(), _svcid.c_str(), _pcname.c_str(), _type, _defaultSamplingPeriod);
            }
          }

          if (rc >= 0)
          {
            rc = cpc->AddCounter(pc);
            if (rc < 0)
            {
              LOG_E(MONLOG).Trace("Can't add counter to cumulative counter(path=%s svcid=%s perfCounter=%s type=%d samplingPeriod=%d)", 
                cpc->path().c_str(), pc->svcid().c_str(), pc->name().c_str(), (int)pc->type(), pc->samplingPeriod());
            }
          }
        }
        else
        {
          LOG_E(MONLOG).Trace("%s: can't cumulate counter for single service (svcid=%s perfCounter=%s type=%d samplingPeriod=%d toCumulate=%d)", 
            __FUNCTION__, _svcid.c_str(), _pcname.c_str(), _type, _defaultSamplingPeriod, (int)_toCumulate);
        }
        //  todo: cumulate
      }
    }
    else
    if (rc < 0)
    {
      LOG_E(MONLOG).Trace("%s: can't create perf counter(svcid=%s perfCounter=%s type=%d samplingPeriod=%d toCumulate=%d)", 
        __FUNCTION__, _svcid.c_str(), _pcname.c_str(), _type, _defaultSamplingPeriod, (int)_toCumulate);
    }
    else
    {
      LOG_W(MONLOG).Trace("%s: counter already registered(svcid=%s perfCounter=%s type=%d samplingPeriod=%d toCumulate=%d)", 
        __FUNCTION__, _svcid.c_str(), _pcname.c_str(), _type, _defaultSamplingPeriod, (int)_toCumulate);
    }

    return rc;
  }

  int MonitorImpl::UnregisterPerfCounter(Transport::TServiceId const & _svcid, nstl::string const & _pcname)
  {
    LOG_D(MONLOG).Trace("%s(svcid=%s perfCounter=%s)", __FUNCTION__, _svcid.c_str(), _pcname.c_str());

    return 0;
  }
}
