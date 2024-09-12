#include "stdafx.h"
#include "MonitorCore.h"
#include "System/DebugVar.h"
#include "System/TextFileDumper.h"
#include "Server/ServerAppBase/ServerCfg.h"
#include "UserManager/UserManagerSvc/UserManagerNaming.h"
#include "MonitoringSvc/MonitoringCfg.h"

NI_DEFINE_REFCOUNT( Monitoring::MonitorCore );

using namespace NDebug;

namespace Monitoring
{
  Thrift::PerfCounterType::type Convert2ThriftPerfCounterType(NDebug::DebugVarType::Enum dvtype)
  {
    switch(dvtype)
    {
    case DebugVarType::Bool:
      return Thrift::PerfCounterType::Bool;
    case DebugVarType::Byte:
      return Thrift::PerfCounterType::Byte;
    case DebugVarType::Int16:
      return Thrift::PerfCounterType::Int16;
    case DebugVarType::UInt16:
      return Thrift::PerfCounterType::UInt16;
    case DebugVarType::Int32:
      return Thrift::PerfCounterType::Int32;
    case DebugVarType::UInt32:
      return Thrift::PerfCounterType::UInt32;
    case DebugVarType::Int64:
      return Thrift::PerfCounterType::Int64;
    case DebugVarType::UInt64:
      return Thrift::PerfCounterType::UInt64;
    case DebugVarType::Float:
      return Thrift::PerfCounterType::Float;
    case DebugVarType::Double:
      return Thrift::PerfCounterType::Double;
    case DebugVarType::String:
      return Thrift::PerfCounterType::String;
    default:
      return Thrift::PerfCounterType::String;
    }
  }

  MonitorCore::MonitorCore()
    :lastctxid_(0)
  {
  }

  MonitorCore::~MonitorCore()
  {
  }

  int MonitorCore::Open(StrongMT<rpc::GateKeeper> const & _gk)
  {
    int rc = 0;
    if (_gk)
    {
      gk_ = _gk;
    }
    else
    {
      LOG_E(MONLOG).Trace("%s: gate keeper is NULL", __FUNCTION__);
    }

    return rc;
  }

  int MonitorCore::Close()
  {
    return 0;
  }

  int MonitorCore::Step()
  {
    //  provider's step
    for(ProviderContextsT::iterator it = contexts.begin(); it != contexts.end(); ++it)
    {
      it->second->step();
    }

    //  request counters
    PerfCountersSet::PerfCounterListT const & lst = activeMonitoringSet.getPerfCounterList();
    for(PerfCountersSet::PerfCounterListT::const_iterator cit = lst.begin();
      cit != lst.end(); ++cit)
    {
      StrongMT<PerfCounterCtx> pcctx = *cit;
      time_t currtime = time(0);
      if (currtime >= pcctx->lastSampleRecvTime() + pcctx->samplingPeriod() &&
          false == pcctx->inprogress())
      {
        if (!pcctx->svcid().empty())  //  отсекаем cumulative counters
        {
          StrongMT<ProviderContext> provctx = findProviderCtx(pcctx->svcid());
          if (provctx)
          {
            if (provctx->isopen())
            {
              provctx->iface()->GetPerfCounterSample(pcctx->name().c_str(), this, &MonitorCore::OnPerfCounterSample, provctx->id());
              pcctx->inprogress(true);

              LOG_M(MONLOG).Trace("Counter acquired from provider(perf=%s svc=%s)", pcctx->name().c_str(), pcctx->svcid().c_str());
            }
            else
            {
              LOG_W(MONLOG).Trace("%s. Provider is NOT OPENED(path=%s svc=%s)", __FUNCTION__, pcctx->path().c_str(), pcctx->svcid().c_str());
              pcctx->lastSampleRecvTime(time(0));
            }
          }
          else
          {
            LOG_W(MONLOG).Trace("%s. Provider is NOT FOUND(path=%s svc=%s)", __FUNCTION__, pcctx->path().c_str(), pcctx->svcid().c_str());
            pcctx->lastSampleRecvTime(time(0));
          }
        }
      }
    }

    return 0;
  }

  int MonitorCore::CreateProviderContext(Transport::TServiceId const & _svcid, StrongMT<rpc::GateKeeper> const & _gk, 
                                         unsigned int _repairTimeout, StrongMT<ProviderContext>& _ctx)
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s repairTimeout=%d)", __FUNCTION__, _svcid.c_str(), _repairTimeout);

    int rc = -1;

    _ctx = findProviderCtx(_svcid);
    if (!_ctx)
    {
      _ctx = new ProviderContext();
      rc = _ctx->open(++lastctxid_, _svcid, gk_, _repairTimeout);
      if (rc >= 0)
        contexts.insert(ProviderContextsT::value_type(_ctx->id(), _ctx));
      else
        LOG_E(MONLOG).Trace(" %s: can't open provider context(svc='%s')", _ctx->svcid().c_str());
    }
    else
    {
      LOG_W(MONLOG).Trace("Provider context already exists (svc='%s')", _ctx->svcid().c_str());
      rc = 1;
    }

    return rc;
  }

  void MonitorCore::OnPerfCounterSample(PerfCounterSample result, ProviderCtxId ctxid, rpc::CallStatus status)
  {
    ProviderContext* provctx = findProviderCtx(ctxid);
    if (provctx)
    {
      StrongMT<PerfCounterCtx> pcc = activeMonitoringSet.findByName(provctx->svcid(), result.name);
      if (pcc)
      {
        if (0 == result.rc)
        {
          pcc->time(result.time);
          pcc->val(result.val);
          pcc->lastSampleRecvTime(time(0));
          pcc->type(NDebug::DebugVarType::Enum(result.type));

          LOG_M(MONLOG) << pcc->path() << " : " << result.val;
          StrongMT<PerfCounterCtx> pccc = activeMonitoringSet.findByName("", result.name);
          if (pccc)
            LOG_M(MONLOG) << pccc->path() << " : " << pccc->val();
        }
        else
        {
          pcc->lastSampleRecvTime(time(0));

          LOG_E(MONLOG).Trace("%s: can't get perf counter, perf provider return error(svc=%s name=%s)", 
            __FUNCTION__, provctx->svcid().c_str(), result.name.c_str());
        }

        pcc->inprogress(false);
      }
      else
      {
        LOG_E(MONLOG).Trace("%s: perf counter context NOT found(svc=%s name=%s)", 
          __FUNCTION__, provctx->svcid().c_str(), result.name.c_str());
      }
    }
    else
    {
      LOG_A(MONLOG).Trace("%s: provider context NOT found(id=%d)", __FUNCTION__, ctxid);
    }
  }

  StrongMT<ProviderContext> MonitorCore::findProviderCtx(Transport::TServiceId const & svcid)
  {
    for(ProviderContextsT::iterator it = contexts.begin();
      it != contexts.end(); ++it)
    {
      if (it->second->svcid() == svcid)
        return it->second;
    }

    return 0;
  }

  StrongMT<ProviderContext> MonitorCore::findProviderCtx(ProviderCtxId const & ctxid)
  {
    ProviderContextsT::iterator it = contexts.find(ctxid);
    if (it == contexts.end())
      return 0;

    return it->second;
  }

  void MonitorCore::GetPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return)
  {
    LOG_M(MONLOG).Trace("%s", __FUNCTION__);

    PerfCountersSet::PerfCounterListT const & activeCounters = activeMonitoringSet.getPerfCounterList();
    for(PerfCountersSet::PerfCounterListT::const_iterator it = activeCounters.begin();
      it != activeCounters.end(); ++it)
    {
      Thrift::PerfCounterInfo pci;
      pci.name = (*it)->path().c_str();
      pci.period = (*it)->samplingPeriod();
      _return.push_back(pci);
    }
  }

  int MonitorCore::RegisterPerfCounters(const std::vector<Thrift::PerfCounterInfo> & counters)
  {
    LOG_M(MONLOG).Trace("%s", __FUNCTION__);

    int rc = -1;
    for(std::vector<Thrift::PerfCounterInfo>::const_iterator it = counters.begin();
      it != counters.end(); ++it)
    {
      StrongMT<PerfCounterCtx> pcc = activeMonitoringSet.findByPath(it->name.c_str());
      if (!pcc)
      {
        pcc = availableCounters.findByPath(it->name.c_str());
        if (pcc)
        {
          activeMonitoringSet.registerPerfCounter(pcc);
          rc = 0;
        }
        else
        {
          LOG_W(MONLOG).Trace("Requested counter is NOT found: %s", it->name.c_str());
          break;
        }
      }
      else
      {
        LOG_W(MONLOG).Trace("Counter is already registered: %s", it->name.c_str());
        rc = 1;
      }
    }

    return rc;
  }

  int MonitorCore::UnregisterPerfCounters(const std::vector<std::string> & counters)
  {
    LOG_M(MONLOG).Trace("%s", __FUNCTION__);

    int rc = 0;
    for(std::vector<std::string>::const_iterator it = counters.begin();
      it != counters.end(); ++it)
    {
      rc = activeMonitoringSet.unregisterPerfCounter((*it).c_str());
    }

    return 0;
  }

  int MonitorCore::UnregisterAllPerfCounters()
  {
    LOG_M(MONLOG).Trace("%s", __FUNCTION__);

    return 0;
  }

  void MonitorCore::GetRegisteredPerfCounters(std::vector<Thrift::PerfCounterInfo> & _return)
  {
    LOG_M(MONLOG).Trace("%s", __FUNCTION__);

    PerfCountersSet::PerfCounterListT const & activeCounters = activeMonitoringSet.getPerfCounterList();
    for(PerfCountersSet::PerfCounterListT::const_iterator it = activeCounters.begin();
      it != activeCounters.end(); ++it)
    {
      StrongMT<PerfCounterCtx> const & pcc = *it;
      Thrift::PerfCounterInfo inf;
      inf.name = pcc->path().c_str();
      inf.period = pcc->samplingPeriod();
      _return.push_back(inf);
    }
  }

  void MonitorCore::GetPerfCounterSamples(std::vector<Thrift::PerfCounterSample> & _return)
  {
    LOG_M(MONLOG).Trace("%s", __FUNCTION__);

    PerfCountersSet::PerfCounterListT const & activeCounters = activeMonitoringSet.getPerfCounterList();
    for(PerfCountersSet::PerfCounterListT::const_iterator it = activeCounters.begin();
      it != activeCounters.end(); ++it)
    {
      StrongMT<PerfCounterCtx> const & pcc = *it;
      Thrift::PerfCounterSample sample;

      sample.name = pcc->path().c_str();
      sample.value = NStr::ToMBCS(pcc->val()).c_str();
      sample.type = Convert2ThriftPerfCounterType(pcc->type());
      sample.timestamp = (int32_t)pcc->time();  //  2032 year coming soon

      _return.push_back(sample);
    }
  }

  int MonitorCore::CreatePerfCounter(Transport::TServiceId const & _svcid, string const & _name, 
    NDebug::DebugVarType::Enum _type, int _samplingPeriod, unsigned int _repairTimeout, StrongMT<PerfCounterCtx> & _pc)
  {
    LOG_M(MONLOG).Trace("%s(svcid=%s name=%s type=%d period=%d)", __FUNCTION__, _svcid.c_str(), _name.c_str(), (int)_type, _samplingPeriod);

    return CreatePerfCounter(createPerfCounterPath(_svcid, _name), _svcid, _name, _type, _samplingPeriod, _repairTimeout, _pc);
  }

  int MonitorCore::CreatePerfCounter(string const & _path, Transport::TServiceId const & _svcid, string const & _name, 
    NDebug::DebugVarType::Enum _type, int _samplingPeriod, unsigned int _repairTimeout, StrongMT<PerfCounterCtx> & _pc)
  {
    LOG_M(MONLOG).Trace("%s(path=%s svcid=%s name=%s type=%d period=%d)", __FUNCTION__, _path.c_str(), _svcid.c_str(), _name.c_str(), (int)_type, _samplingPeriod);

    if (_samplingPeriod < 0)
    {
      LOG_W(MONLOG).Trace("%s. Sampling period is negative(path=%s svcid=%s name=%s type=%d period=%d)", __FUNCTION__, _path.c_str(), _svcid.c_str(), _name.c_str(), (int)_type, _samplingPeriod);
      return -1;
    }

    if (!_samplingPeriod)
    {
      LOG_M(MONLOG).Trace("%s. Sampling period is 0 => use default sampling period(path=%s svcid=%s name=%s type=%d defaultPeriod=%d)", 
        __FUNCTION__, _path.c_str(), _svcid.c_str(), _name.c_str(), (int)_type,  Cfg::GetDefaultSamplingPeriod());
      _samplingPeriod = Cfg::GetDefaultSamplingPeriod();
    }

    StrongMT<PerfCounterCtx> pc = new PerfCounterCtx( _path, _svcid, _name, _type, _samplingPeriod);

    int rc = activeMonitoringSet.registerPerfCounter(pc);
    if (0 == rc)
    {
      StrongMT<ProviderContext> ctx;
      rc = CreateProviderContext(_svcid, gk_, _repairTimeout, ctx);
      if (rc >= 0)
      {
        rc = ctx->RegisterPerfCounter(pc);
      }
      else
      {
        LOG_E(MONLOG).Trace("%s. Can't create provider context(svcid=%s counter=%s)", __FUNCTION__, _svcid.c_str(), pc->path().c_str());
      }
    }
    else
    if (rc < 0)
    {
      LOG_E(MONLOG).Trace("%s. Can't register perf counter(svcid=%s counter=%s)", __FUNCTION__, _svcid.c_str(), pc->path().c_str());
    }
    else
    {
      LOG_W(MONLOG).Trace("%s. Perf counter already registered(svcid=%s counter=%s)", __FUNCTION__, _svcid.c_str(), pc->path().c_str());
    }

    if (0 == rc)
    {
      _pc = pc;
    }
    else
    if (rc < 0)
    {
      activeMonitoringSet.unregisterPerfCounter(pc->path());
    }

    return rc;
  }

  int MonitorCore::RegisterPerfCounter(StrongMT<PerfCounterCtx> const & _pc)
  {
    LOG_M(MONLOG).Trace("%s(path=%s svcid=%s name=%s)", __FUNCTION__, 
      _pc->path().c_str(), _pc->svcid().c_str(), _pc->name().c_str());

    return activeMonitoringSet.registerPerfCounter(_pc);
  }

  string MonitorCore::createPerfCounterPath(Transport::TServiceId const & _svcid, string const & _name)
  {
    string path(HostServer::Cfg::ClusterName());
    path += "/";
    path += _svcid.c_str();
    path += "/";
    path += _name;
    return path;
  }

  StrongMT<PerfCounterCtx> MonitorCore::FindPerfCounter(string const & _path)
  {
    return activeMonitoringSet.findByPath(_path);
  }
}
