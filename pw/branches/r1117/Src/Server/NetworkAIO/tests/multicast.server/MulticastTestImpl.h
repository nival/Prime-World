#pragma once

#include "MulticastTestSvcIface.h"
#include <rpc/IfaceRequester.h>
#include "MulticastSession.h"

namespace MulticastTest
{

  class MulticastTestImpl : public IMulticastSvc, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MulticastTestImpl, IMulticastSvc, BaseObjectMT );

    RPC_REDEFINE_ID();

    typedef map<Transport::TClientId, StrongMT<MulticastSession>> SessionsT;

  public:
    MulticastTestImpl( StrongMT<rpc::GateKeeper> const & _gk, StrongMT<Transport::ITransportSystem> const & _ts);
    ~MulticastTestImpl();

    int RegisterClient(const char* name, uint clientId, IMulticastClient* _client);
    void ConfirmStep(unsigned int _sessionid, unsigned int _step);

    void Step();

  private:
    StrongMT<rpc::GateKeeper> gk_;
    StrongMT<Transport::ITransportSystem> ts_;
    SessionsT sessions_;
    StrongMT<MulticastSession> currentSession_;
    unsigned int step_;
    unsigned int sessionCount_;
  };
}
