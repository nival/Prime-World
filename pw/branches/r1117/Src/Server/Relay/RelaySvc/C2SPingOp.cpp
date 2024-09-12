#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"

#include "C2SPingOp.h"

using namespace Transport;

namespace Relay
{

C2SPingOp::C2SPingOp(ClientContextSP const & spsrc, Transport::TPipeId const & cpid, 
          Transport::TPipeId const & svcpid,
          BackendContextSP const & spdst, 
          ChannelAddr const & pingcaddr,
          unsigned long long sendTime,
          unsigned long seqNum)
  :C2SOp(OperationType::C2S_PING, spsrc, cpid, svcpid, spdst),
  chaddr_(pingcaddr),
  originalSendTime_(sendTime),
  seqNum_(seqNum)
{
  NI_PROFILE_FUNCTION;
}

C2SPingOp::~C2SPingOp()
{
}

int C2SPingOp::Execute(Terabit::AsynchChannel *channel, TransportProtocolHandler* tph)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d u=%d cpid=%d svc=%s svctx=%d spid=%d)"), __FUNCTION__, 
    channel->get_id(), spSrcCtx_->userid(), cpid_, spDstCtx_->svcid().c_str(), spDstCtx_->id(), svcpid_));

  Transport::ThroughPingMessage msg;
  msg.reply = false;
  msg.requestingChannel = chaddr_;
  msg.sendTime = originalSendTime_;
  msg.seqNum = seqNum_;
  ACE_OS::gettimeofday().msec(static_cast< int >( msg.throughSendTime ));

  ChannelAddr caddr;
  caddr.client = spSrcCtx_->userid();
  caddr.pipe = EKnownPipeId::NetLogic;
  rc = tph->HandleOutput(&msg, caddr, channel);

  NI_PROFILE_BLOCK("close");
  Close();

  return rc;
}

}
