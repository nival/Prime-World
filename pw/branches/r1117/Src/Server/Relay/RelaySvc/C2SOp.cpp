#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"
#include "C2SOp.h"

using namespace Transport;

namespace Relay
{

C2SOp::C2SOp(OperationType::Enum optype, 
             ClientContextSP const & spsrc, Transport::TPipeId const & cpid, 
             Transport::TPipeId const & svcpid,
             BackendContextSP const & spdst)
  :Operation(optype),
  spSrcCtx_(spsrc),
  spDstCtx_(spdst),
  cpid_(cpid),
  svcpid_(svcpid)
{
  ACE_ASSERT(!spsrc.null());
  ACE_ASSERT(!spdst.null());
}

C2SOp::~C2SOp()
{
}

}
