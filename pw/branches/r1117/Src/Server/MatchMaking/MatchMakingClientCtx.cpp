#include "stdafx.h"
#include "MatchMakingClientCtx.h"

NI_DEFINE_REFCOUNT(MatchMaking::ClientCtx);

namespace MatchMaking
{
  ClientCtx::ClientCtx()
    :clientid_(INVALID_CLIENT_ID),
    userid_(0),
    ready_(false)
  {
  }

  ClientCtx::ClientCtx(ClientId cid, StrongMT<MatchMaking::RIClient> const & rclient)
    :clientid_(cid),
    rclient_(rclient),
    userid_(0),
    ready_(false)
  {
  }

  ClientCtx::~ClientCtx()
  {
    rclient_ = 0;
  }
}
