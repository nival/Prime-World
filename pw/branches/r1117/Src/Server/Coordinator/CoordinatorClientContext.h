#pragma once
#include "Coordinator/RCoordinatorClientIface.auto.h"
#include "Coordinator/ServerDef.h"
#include "Coordinator/CoordinatorTypes.h"
#include "Coordinator/CoordinatorSvcContext.h"

namespace Coordinator
{

typedef vector<Transport::TServiceId> ServiceIdsT;

class ClientContext : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(ClientContext, BaseObjectMT);

public:

  struct State
  {
    enum Enum
    {
      CLOSE = -1,
      INIT = 0,
      OPENING = 1,
      OPEN = 2,
      REOPENING = 3,
    };
  };

  typedef list<StrongMT<SvcContext> > SvcContextsT;

public:
  ClientContext( RICoordinatorClientRemote * cl );
  ~ClientContext();

public:
  void step();

public:
  ServerIdT srvid_;
  ServerDef serverDef;
  SvcContextsT svcContexts_;

  State::Enum state() const { return state_; }
  void state(State::Enum _st) { state_ = _st; }

  StrongMT<RICoordinatorClientRemote> client() const { return client_; }
  void client( RICoordinatorClientRemote * _client ) { client_ = _client; }

  bool isopen() const { return (State::OPEN == state()); }
  bool isclose() const { return (State::CLOSE == state()); }

  void close()
  {
    if (isclose())
      return;

    state(State::CLOSE);
    client_ = 0;
  }

  void OnPingReturn(unsigned int _result, int _context, rpc::CallStatus _status);

  StrongMT<SvcContext> findSvcContext(Transport::TServiceId const & _svcid);

private:
  StrongMT<RICoordinatorClientRemote> client_;
  rpc::Status prevClientStatus_;
  State::Enum state_;
  NHPTimer::FTime repairStartTime_;

  unsigned int pingSeqNum_;
  NHPTimer::FTime lastPingTime_;
};

}
