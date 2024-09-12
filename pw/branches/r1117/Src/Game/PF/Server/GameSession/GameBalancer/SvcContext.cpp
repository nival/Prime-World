#include "stdafx.h"
#include "GameBalancer/RGameBalancerIface.auto.h"
#include "GameBalancer/SvcContext.h"
#include "GameBalancer/GameBalancerCfg.h"

NI_DEFINE_REFCOUNT(GameBalancer::SvcContext);

namespace GameBalancer
{
  SvcContext::SvcContext(Transport::TServiceId const & _svcid, uint _ccu)
    :svcid_(_svcid),
    st_(State::INIT)
  {
    if (!Transport::GetLocalServiceId(svcid_, localsvcid_))
    {
      LOG_E(GBALANCER).Trace("Can't get local service id(svcid=%s)", svcid_.c_str());
    }

    Transport::GetServicePath(svcid_, svcpath_);

    allocatorReq = new rpc::IfaceRequester<HybridServer::RIGameServerAllocator>;
    dispenserReq = new rpc::IfaceRequester<HybridServer::RIGameServerDispenser>;
  }

  int SvcContext::open(StrongMT<rpc::GateKeeper> const & _gk, NLogg::CChannelLogger* _logstrm, char const * _chnlName, 
    Transport::IAddressTranslator* _addrResolver)
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, svcid_.c_str());

    int rc = -1;
    if (state_() > State::INIT)
    {
      LOG_W(GBALANCER).Trace("Context is already in open* state(svcid=%s st=%d)", svcid_.c_str(), (int)state_());
      rc = 1;
      return rc;
    }

    addrResolver_ = _addrResolver;

    Transport::TServiceId localsvcid;
    if (Transport::GetLocalServiceId(svcid_, localsvcid))
    {
      rc = allocatorReq->init(_gk, localsvcid, HybridServer::AllocatorIfaceId, _logstrm, _chnlName, this);
      if (rc >= 0)
      {
        rc = dispenserReq->init(_gk, localsvcid, HybridServer::DispenserIfaceId, _logstrm, _chnlName, this);
        if (rc >= 0)
        {
          st_ = State::OPENING;
        } 
        else
        {
          LOG_E(GBALANCER).Trace("Can't init iface requester(svcid=%s iface=%s)", 
            svcid_.c_str(), HybridServer::DispenserIfaceId);
        }
      }
      else
      {
        LOG_E(GBALANCER).Trace("Can't init iface requester(svcid=%s iface=%s)", 
          svcid_.c_str(), HybridServer::AllocatorIfaceId);
      }
    }

    if (rc < 0)
      close();

    return rc;
  }

  void SvcContext::close()
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s ccu=%d)", __FUNCTION__, svcid_.c_str(), ccu());

    if (isstate_(State::CLOSED))
    {
      LOG_W(GBALANCER).Trace("%s. Context already closed(svcid=%s)", __FUNCTION__, svcid_.c_str());
      return;
    }

    LOG_M(GBALANCER).Trace("%s. Close context(svcid=%s ccu=%d)", __FUNCTION__, svcid_.c_str(), ccu());
    state_(State::CLOSED);

    if (allocatorReq)
    {
      allocatorReq->close();
    }

    if (dispenserReq)
    {
      dispenserReq->close();
    }
  }

  int SvcContext::openSvcAllocCtx(Transport::TServiceId const & _svcpath, Peered::TSessionId _userctx, StrongMT<RIBalancerCallback> const & _cb)
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s svcpath=%s userctx=%016x ccu=%d)", __FUNCTION__, svcid_.c_str(), _svcpath.c_str(), _userctx, ccu());

    int rc = -1;
    StrongMT<HybridServer::RIGameServerAllocator> alloctorIface = getAllocatorIface();
    if (alloctorIface)
    {
      StrongMT<SvcAllocContext> alloctx(new SvcAllocContext(_svcpath, _userctx, _cb));
      if (allocContexts.insert(make_pair(alloctx->id(), alloctx)).second)
      {
        alloctorIface->AllocateServer(_userctx, RemotePtr<HybridServer::RIGameServerAllocatorNotify>(this), this, 
          &SvcContext::onAllocServerReturn, alloctx->id(), Cfg::GetAllocResponseTimeout());
        inccu();
        if (extCounter_)
          extCounter_->inccu();
        alloctx->state(SvcAllocContext::State::SERVER_ALLOC_IN_PROGRESS);
        rc = 0;
      }
      else
      {
        LOG_E(GBALANCER).Trace("Allocation context with the same id already exists(svcpath=%s userctx=%016x allocid=%d)", 
          _svcpath.c_str(), _userctx, alloctx->id());
      }
    }
    else
    {
      LOG_E(GBALANCER).Trace("Game allocator interface is not available(svcpath=%s userctx=%016x)", 
        _svcpath.c_str(), _userctx);
      close();
    }

    return rc;
  }

  void SvcContext::onAllocServerReturn(uint _allocid, uint _ctxid, rpc::CallStatus rpcsts)
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s allocid=%d ctxid=%d rpcsts=%d)", 
      __FUNCTION__, svcid_.c_str(), _allocid, _ctxid, (int)rpcsts);

    SvcAllocContextsT::iterator it = allocContexts.find(_ctxid);
    if (it != allocContexts.end())
    {
      StrongMT<SvcAllocContext> const & alloctx = it->second;
      alloctx->allocid(_allocid);

      if (rpc::CallSuccessful == rpcsts)
      {
        if (getDispenserIface())
        {
          if (alloctx->allocid())
          {
            LOG_M(GBALANCER).Trace("Alloc game service return OK(svcid=%s allocid=%d userctx=%016x)", 
              svcid_.c_str(), alloctx->allocid(), alloctx->userctx());

            alloctx->cb->OnGameSvcAllocated(alloctx->userctx(), alloctx->allocid(), getDispenserIface());
            alloctx->allocNotifyWaitStartTime = NHPTimer::GetScalarTime();
            alloctx->state(SvcAllocContext::State::WAIT_FOR_ALLOC_NOTIFY);
          }
          else
          {
            LOG_E(GBALANCER).Trace("Alloc game service return FAIL(svcid=%s allocid=%d userctx=%016x)", 
              svcid_.c_str(), alloctx->allocid(), alloctx->userctx());
          }
        }
        else
        {
          LOG_E(GBALANCER).Trace("Alloc game service return OK, but NO dispenser iface(svcid=%s allocid=%d userctx=%016x)", 
            svcid_.c_str(), alloctx->allocid(), alloctx->userctx());
        }
      }
      else
      {
        LOG_E(GBALANCER).Trace("%s: rpc call is failed(svcid=%s userctx=%016x rpcsts=%d)", 
          __FUNCTION__, svcid_.c_str(), alloctx->userctx(), (int)rpcsts);
      }

      if (SvcAllocContext::State::WAIT_FOR_ALLOC_NOTIFY != alloctx->state())
      {
        alloctx->cb->OnGameSvcAllocated(alloctx->userctx(), 0, 0);
        deccu();
        if (extCounter_)
          extCounter_->deccu();
        alloctx->state(SvcAllocContext::State::CLOSED);
        allocContexts.erase(_ctxid);
      }
    }
    else
    {
      LOG_E(GBALANCER).Trace("No allocation context found(svcid=%s ctxid=%d)", svcid_.c_str(), _ctxid);
    }
  }

  void SvcContext::AllocNotify( uint _allocid, int result )
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s allocid=%d result=%d)", __FUNCTION__, svcid_.c_str(), _allocid, result);

    StrongMT<SvcAllocContext> const & alloctx = findSvcAllocCtxByAllocId(_allocid);
    if (alloctx)
    {
      if (result < 0)
      {
        LOG_E(GBALANCER).Trace("Game allocation failed(svcid=%s allocid=%d usrctx=%016x)", 
          svcid_.c_str(), alloctx->allocid(), alloctx->userctx());
        deccu();
        if (extCounter_)
          extCounter_->deccu();
        allocContexts.erase(alloctx->id());
      }
      else
      {
        LOG_M(GBALANCER).Trace("Game successfully allocated(svcid=%s usrctx=%016x)", svcid_.c_str(), alloctx->userctx());

        bool res = freeContexts.insert(SvcFreeContext(alloctx->allocid(), alloctx->userctx())).second;
        if (!res)
        {
          LOG_A(GBALANCER).Trace("Can't create free context: context with the same allocid already exists(allocid=%d svcid=%s)", 
            alloctx->allocid(), svcid_.c_str());
        }

        allocContexts.erase(alloctx->id());
      }
    }
    else
    {
      LOG_E(GBALANCER).Trace("Allocation notification received, but NOT found(allocid=%d svcid=%s)", _allocid, svcid_.c_str());
    }
  }

  void SvcContext::FreeNotify(uint allocid)
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s allocid=%d)", __FUNCTION__, svcid_.c_str(), allocid);

    SvcFreeContextsT::iterator it = freeContexts.find(allocid);
    if (it != freeContexts.end())
    {
      StrongMT<SvcAllocContext> alloctx = findSvcAllocCtxByAllocId(allocid);
      if (alloctx)
      {
        LOG_E(GBALANCER).Trace("%s: remove non-notified allocation(allocid=%d userctx=%016x svcid=%s)", 
          __FUNCTION__, it->allocid_, it->userctx_, svcid_.c_str());
        allocContexts.erase(alloctx->id());
      }

      LOG_M(GBALANCER).Trace("Game session freed(allocid=%d userctx=%016x svcid=%s)", it->allocid_, it->userctx_, svcid_.c_str());
      deccu();
      if (extCounter_)
        extCounter_->deccu();
    }
    else
    {
      LOG_E(GBALANCER).Trace("Free notification received, but contexts not found(allocid=%d svcid=%s)", allocid, svcid_.c_str());
    }
  }

  StrongMT<SvcAllocContext> SvcContext::findSvcAllocCtxByAllocId(uint allocid)
  {
    for(SvcAllocContextsT::iterator it = allocContexts.begin(); it != allocContexts.end(); ++it)
    {
      if (allocid == it->second->allocid())
      {
        return it->second;
      }
    }

    return StrongMT<SvcAllocContext>(0);
  }

  void SvcContext::step()
  {
    if (st_ <= State::INIT)
      return;

    allocatorReq->step();
    dispenserReq->step();

    if (allocatorReq->isopen() && dispenserReq->isopen())
    {
      if (netaddr_.empty())
      {
        netaddr_ = addrResolver_->GetSvcAddress( localsvcid() );
        if (!netaddr_.empty())
        {
          LOG_M(GBALANCER).Trace("Service network address resolved(svcid=%s netaddr=%s)", svcid_.c_str(), netaddr_.c_str());
        }
      }

      if (!isstate_(State::OPENED))
      {
        LOG_M(GBALANCER).Trace("%s: service context is OPENED(svcid=%s)", __FUNCTION__, svcid_.c_str());
        state_(State::OPENED);
      }

    }
    else
    if (!isstate_(State::OPENING) && !isstate_(State::REOPENING))
    {
      LOG_A(GBALANCER).Trace("Context have to be in OPENING state(svcid=%s st=%d)", svcid_.c_str(), (int)state_());
      close();
    }

    //  check allocation notify timeout
    int const allocNotifyTimeout = Cfg::GetAllocNotifyTimeout();
    if (allocNotifyTimeout)
    {
      for(SvcAllocContextsT::iterator it = allocContexts.begin(); it != allocContexts.end(); )
      {
        StrongMT<SvcAllocContext> alloctx = it->second;
        if (SvcAllocContext::State::WAIT_FOR_ALLOC_NOTIFY == alloctx->state())
        {
          NHPTimer::FTime curr = NHPTimer::GetScalarTime();
          if (curr - alloctx->allocNotifyWaitStartTime > allocNotifyTimeout )
          {
            LOG_E(GBALANCER).Trace("Alloc notify timeout(allocid=%d userctx=%016x svcid=%s timeout=%d)", 
              alloctx->allocid(), alloctx->userctx(), svcid_.c_str(), Cfg::GetAllocNotifyTimeout());

            alloctx->state(SvcAllocContext::State::CLOSED);
            it = allocContexts.erase(it);
            continue;
          }
        }
        ++it;
      }
    }
  }

  void SvcContext::onChangeState(rpc::IfaceRequesterState::Enum _st, 
    StrongMT<rpc::IfaceRequester<HybridServer::RIGameServerAllocator> > const & _ifacereq)
  {
    if (rpc::IfaceRequesterState::CLOSED == _st)
    {
      LOG_W(GBALANCER).Trace("IGameServerAllocator interface is CLOSED(svcid=%s st=%d)", svcid_.c_str(), (int)state_());
      if (!isstate_(State::CLOSED))
        state_(State::REOPENING);
    }
  }

  void SvcContext::onChangeState(rpc::IfaceRequesterState::Enum _st, 
    StrongMT<rpc::IfaceRequester<HybridServer::RIGameServerDispenser> > const & _ifacereq)
  {
    if (rpc::IfaceRequesterState::CLOSED == _st)
    {
      LOG_W(GBALANCER).Trace("IGameServerDispenser interface is CLOSED(svcid=%s st=%d)", svcid_.c_str(), (int)state_());
      if (!isstate_(State::CLOSED))
        state_(State::REOPENING);
    }
  }



  int SvcContext::externalCCUCounter( ICCUCounter * counter )
  {
    if (!extCounter_)
    {
      extCounter_ = counter;
      return 0;
    }

    return -1;
  }
}
