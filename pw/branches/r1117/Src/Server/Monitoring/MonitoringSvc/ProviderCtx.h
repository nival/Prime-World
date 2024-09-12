#pragma once
#include "PerfCounterProvider/RPerfCounterProviderIface.auto.h"
#include <rpc/IfaceRequester.h>
#include "MonitoringSvc/MonitoringSet.h"

namespace Monitoring
{
  typedef unsigned int ProviderCtxId;

  class ProviderContext : public rpc::IfaceRequesterCallback<RIPerfCounterProvider>, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2(ProviderContext, rpc::IfaceRequesterCallback<RIPerfCounterProvider>, BaseObjectMT);
  public:
    struct State
    {
      enum Enum
      {
        CLOSE = -1,
        INIT = 0,
        OPENING = 1,
        OPEN = 2,
        REPAIR = 3,
      };
    };

  public:

    ProviderContext();
    ~ProviderContext();

  public:
    int open(ProviderCtxId const & _id, Transport::TServiceId const & _svcid, StrongMT<rpc::GateKeeper> const & gk, unsigned int _repairTimeout = 0);
    void step();
    int close();

    bool isopen() const;
    bool isclose() const;

    StrongMT<RIPerfCounterProvider> const & iface() const;
    Transport::TServiceId const & svcid() const;
    ProviderCtxId id() const;

    int RegisterPerfCounter(StrongMT<PerfCounterCtx> const & _pc);
    int UnregisterPerfCounter(StrongMT<PerfCounterCtx> const & _pc);

  private:
    void state(State::Enum _st);
    State::Enum state() const;

    //  rpc::IfaceRequesterCallback<RIPerfCounterProvider>
    void onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<RIPerfCounterProvider>> const & _ifacereq);

  private:
    StrongMT<rpc::IfaceRequester<RIPerfCounterProvider>> ifacereq_;
    ProviderCtxId id_;
    nstl::string alias_;
    Transport::TServiceId svcid_;
    State::Enum st_;
    NHPTimer::FTime repairEndtime_;
    unsigned int repairTimeout_;

    PerfCountersSet counters_;
  };

  inline
  ProviderCtxId ProviderContext::id() const
  {
    return id_;
  }

  inline
  StrongMT<RIPerfCounterProvider> const & ProviderContext::iface() const
  {
    return ifacereq_->iface();
  }

  inline
  bool ProviderContext::isopen() const
  {
    return (State::OPEN == state());
  }

  inline
  bool ProviderContext::isclose() const
  {
    return (State::CLOSE == state());
  }

  inline
  Transport::TServiceId const & ProviderContext::svcid() const
  {
    return svcid_;
  }

  inline
  void ProviderContext::state(State::Enum _st)
  {
    st_ = _st;
  }

  inline
  ProviderContext::State::Enum ProviderContext::state() const
  {
    return st_;
  }
}
