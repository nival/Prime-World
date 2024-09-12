#pragma once
#include <Network/TransportTypes.h>
#include <RPC/IfaceRequester.h>
#include "HybridServer/RGameServerAllocatorIface.auto.h"
#include "HybridServer/RGameServerDispenserIface.auto.h"
#include "GameBalancer/SvcAllocContext.h"
#include "GameBalancer/IGameCCUCounter.h"
#include "Network/AddressTranslator.h"

namespace HybridServer
{
struct IGameServerAllocatorNotify;
}

namespace GameBalancer
{
  class SvcContext :  public HybridServer::IGameServerAllocatorNotify, 
                      public ICCUCounter,
                      public rpc::IfaceRequesterCallback<HybridServer::RIGameServerAllocator>,
                      public rpc::IfaceRequesterCallback<HybridServer::RIGameServerDispenser>,
                      public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_5( SvcContext, HybridServer::IGameServerAllocatorNotify, ICCUCounter, 
      rpc::IfaceRequesterCallback<HybridServer::RIGameServerAllocator>, 
      rpc::IfaceRequesterCallback<HybridServer::RIGameServerDispenser>, 
      BaseObjectMT );

    struct SvcFreeContext
    {
      SvcFreeContext()
        :allocid_(0),
        userctx_(0)
      {
      }

      SvcFreeContext(uint _allocid)
        :allocid_(_allocid),
        userctx_(0)
      {
      }

      SvcFreeContext(uint _allocid, long long _userctx)
        :allocid_(_allocid),
        userctx_(_userctx)
      {
      }

      uint allocid_;
      long long userctx_;

      bool operator < (SvcFreeContext const & other) const
      {
        return allocid_ < other.allocid_;
      }
    };

    typedef nstl::map<uint, StrongMT<SvcAllocContext> > SvcAllocContextsT;
    typedef nstl::set<SvcFreeContext> SvcFreeContextsT;

  public:
    struct State
    {
      enum Enum
      {
        CLOSED = -1,
        INIT = 0,
        OPENING = 1,
        OPENED = 2,
        REOPENING = 3,
      };
    };

  public:
    SvcContext(Transport::TServiceId const & _svcid, uint _ccu=0);
    int open(StrongMT<rpc::GateKeeper> const & _gk, NLogg::CChannelLogger* _logstrm, char const * _chnlName, Transport::IAddressTranslator* _addrResolver);
    void close();

    bool isopen() const { return State::OPENED == st_; }
    bool isclosed() const { return State::CLOSED == st_; }

    int externalCCUCounter( ICCUCounter * counter );
    int openSvcAllocCtx(Transport::TServiceId const & _svcpath, Peered::TSessionId _userctx, StrongMT<RIBalancerCallback> const & _cb);

    void step();

  public:
    Transport::TServiceId const & svcpath() const { return svcpath_; }
    Transport::TServiceId const & svcid() const { return svcid_; }
    Transport::TServiceId const & localsvcid() const { return localsvcid_; }
    Network::NetAddress const & netaddr() const { return netaddr_; }

    HybridServer::RIGameServerAllocator * getAllocatorIface() const { return allocatorReq->iface(); }
    HybridServer::RIGameServerDispenser * getDispenserIface() const { return dispenserReq->iface(); }

  protected:
    void onAllocServerReturn(uint allocid, uint contextid, rpc::CallStatus rpcsts);

    virtual void AllocNotify( uint allocid, int result );
    virtual void FreeNotify(uint allocid);

    StrongMT<SvcAllocContext> findSvcAllocCtxByAllocId(uint allocid);

    //  IfaceRequesterCallback<HybridServer::RIGameServerAllocator>
    virtual void onChangeState(rpc::IfaceRequesterState::Enum _st, 
      StrongMT<rpc::IfaceRequester<HybridServer::RIGameServerAllocator> > const & _ifacereq);
    //  IfaceRequesterCallback<HybridServer::RIGameServerDispenser>
    virtual void onChangeState(rpc::IfaceRequesterState::Enum _st, 
      StrongMT<rpc::IfaceRequester<HybridServer::RIGameServerDispenser> > const & _ifacereq);

  private:
    bool isstate_(State::Enum _st) const { return st_ == _st; }
    void state_(State::Enum _st) {
      NI_ASSERT(st_ >= State::INIT, "Context MUST NOT be CLOSED");
      st_ = _st;
    }
    State::Enum state_() const { return st_; }

  private:
    Transport::TServiceId svcid_;
    Transport::TServiceId svcpath_;
    Transport::TServiceId localsvcid_;
    Network::NetAddress netaddr_;
    State::Enum st_;
    StrongMT<ICCUCounter> extCounter_;
    StrongMT<Transport::IAddressTranslator> addrResolver_;

    StrongMT<rpc::IfaceRequester<HybridServer::RIGameServerAllocator> > allocatorReq;
    StrongMT<rpc::IfaceRequester<HybridServer::RIGameServerDispenser> > dispenserReq;

    SvcAllocContextsT allocContexts;
    SvcFreeContextsT  freeContexts;
  };
}
