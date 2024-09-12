#pragma warning( push )
#pragma warning( disable : 4996)
#include "stdafx.h"
#include "RelayPipe.h"
#include "BackendContext.h"
#pragma warning( pop )


namespace Relay
{
  Pipe::Pipe()
    :lastInS2CSeqNum_(0),
    lastOutS2CSeqNum_(0)
  {
  }

  Pipe::Pipe(Transport::TServiceId const & _svcid,
    Transport::TPipeId const & _svcpid,
    BackendContextSP const & _svctx,
    StrongMT<ITrafficTracker> const & _tt)
    :Resource(Resource::State::OPENED),
    svcid_(_svcid),
    svcpipeid_(_svcpid),
    svctxid_(_svctx->svctxid()),
    svctx_(_svctx),
    trafficTracker_(_tt),
    lastInS2CSeqNum_(0),
    lastOutS2CSeqNum_(0)
  {
  }
}
