#include "stdafx.h"
#include "Coordinator/CoordinatorClientContext.h"
#include "Coordinator/CoordinatorServerCfg.h"

namespace Coordinator
{

ClientContext::ClientContext( RICoordinatorClientRemote * cl ) :
client_(cl),
srvid_(0), serverDef(), state_(State::INIT), repairStartTime_(0), prevClientStatus_(rpc::Unknown), pingSeqNum_(0), lastPingTime_(0)
{
}



ClientContext::~ClientContext()
{
  close();
}



void ClientContext::step()
{
  if (isclose())
    return;

  if (rpc::Connected == client_->GetStatus())
  {
    if (prevClientStatus_ != client_->GetStatus())
    {
      LOG_M(0).Trace( "Coord client connected (srvid=%d)", srvid_ );

      state(State::OPEN);
      repairStartTime_ = 0;
      prevClientStatus_ = client_->GetStatus();
    }
    else
    {
      //  send ping
      NHPTimer::FTime currTime = NHPTimer::GetScalarTime();
      if (lastPingTime_ + Cfg::GetClientPingPeriod() < currTime)
      {
        client_->Ping(++pingSeqNum_, this, &ClientContext::OnPingReturn, 0, Cfg::GetClientPingResponseTimeout());
        lastPingTime_ = currTime;
      }
    }
  }
  else
  if (rpc::Disconnected == client_->GetStatus())
  {
    if (prevClientStatus_ != client_->GetStatus())
    {
      LOG_W(0).Trace( "Coord client disconnected. Waiting for it(srvid=%d to=%d)", srvid_, Cfg::GetClientRepairTimeout() );
      state(State::REOPENING);
      repairStartTime_ = NHPTimer::GetScalarTime();
      prevClientStatus_ = client_->GetStatus();
    }
    else
    {
      if (repairStartTime_ + Cfg::GetClientRepairTimeout() < NHPTimer::GetScalarTime())
      {
        //  timeout
        LOG_W(0).Trace( "Repair timeout is expired(srvid=%d to=%d)", srvid_, Cfg::GetClientRepairTimeout() );
        close();
      }
    }
  }
}

void ClientContext::OnPingReturn(unsigned int _result, int _context, rpc::CallStatus _status)
{
  LOG_M(0).Trace("%s(result=%d rpcsts=%d srvid=%d)", __FUNCTION__, _result, (int)_status, srvid_);

  if (!isclose())
  {
    if (_status != rpc::CallSuccessful)
    {
      string services;
      for(ServerDef::ServiceDefsT::const_iterator cit = serverDef.svcdefs.begin(); 
        cit != serverDef.svcdefs.end(); ++cit)
      {
        if (cit != serverDef.svcdefs.begin())
          services += ";";

        services += cit->svcid.c_str();
      }

      LOG_E(0).Trace("%s: ping FAILED(rpcsts=%d srvid=%d services=%s)", __FUNCTION__, (int)_status, srvid_, services.c_str());
    }
  }
}

StrongMT<SvcContext> ClientContext::findSvcContext(Transport::TServiceId const & _svcid)
{
  for(SvcContextsT::const_iterator cit = svcContexts_.begin(); cit != svcContexts_.end(); ++cit)
  {
    StrongMT<SvcContext> const & svctx = *cit;
    if (_svcid == svctx->svcid())
    {
      return svctx;
    }
  }

  return 0;
}

}
