#pragma once
#include <Server/RPC/RPC.h>
#include "MatchMakingTypes.h"

namespace MatchMaking
{
  class RIClient;

  class ClientCtx : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ClientCtx, BaseObjectMT );

  public:
    ClientCtx();
    ClientCtx(ClientId cid, StrongMT<MatchMaking::RIClient> const & rclient);
    ~ClientCtx();

    ClientId clientid() const;
    StrongMT<MatchMaking::RIClient> remoteClient() const;

    bool ready() const;
    void ready(bool rdy);

  private:
    ClientId clientid_;
    StrongMT<MatchMaking::RIClient> rclient_;
    int userid_;  //  TODO: server system wide user id
    bool ready_;
  };

  inline 
  ClientId ClientCtx::clientid() const
  {
    return clientid_;
  }

  inline
  StrongMT<MatchMaking::RIClient> ClientCtx::remoteClient() const
  {
    return rclient_;
  }

  inline
  bool ClientCtx::ready() const
  {
    return ready_;
  }

  inline
  void ClientCtx::ready(bool rdy)
  {
    ready_ = rdy;
  }
}
