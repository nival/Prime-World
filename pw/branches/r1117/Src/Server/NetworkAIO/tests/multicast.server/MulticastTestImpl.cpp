#include "stdafx.h"
#include "MulticastTestImpl.h"

NI_DEFINE_REFCOUNT(MulticastTest::MulticastTestImpl)

namespace MulticastTest
{
  MulticastTestImpl::MulticastTestImpl(StrongMT<rpc::GateKeeper> const & _gk, StrongMT<Transport::ITransportSystem> const & _ts)
    :gk_(_gk),
    ts_(_ts),
    step_(0),
    sessionCount_(0)
  {
    GetSystemLog().SetChannelMinLevelFilter(LOG, NLogg::LEVEL_DEBUG);
  }

  MulticastTestImpl::~MulticastTestImpl()
  {
  }

  int MulticastTestImpl::RegisterClient(const char* name, uint clientId, IMulticastClient* _client)
  {
    if (!currentSession_ || currentSession_->full())
    {
      ++sessionCount_;
      currentSession_.Set(new MulticastSession(ts_, 10));
      sessions_[sessionCount_] = currentSession_;
    }

    return currentSession_->RegisterClient(name, clientId, _client);
  }

  void MulticastTestImpl::ConfirmStep(unsigned int _sessionid, unsigned int _step)
  {
    
  }

  void MulticastTestImpl::Step()
  {
    for(SessionsT::const_iterator cit = sessions_.begin(); cit != sessions_.end(); ++cit)
    {
      cit->second->Step();
    }
  }
}
