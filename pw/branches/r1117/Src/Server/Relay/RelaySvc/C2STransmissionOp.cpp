#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"
#include "TransportProtocol.h"

#include "C2STransmissionOp.h"

using namespace Transport;

namespace Relay
{

C2STransmissionOp::C2STransmissionOp(ClientContextSP const & spsrc, Transport::TPipeId const & cpid,
                                     Transport::TPipeId const & svcpid,
                                     BackendContextSP const & spdst,
                                     char const * data, size_t size,
                                     unsigned long seqNum)
  :C2SOp(OperationType::C2S_TRANSMISSION, spsrc, cpid, svcpid, spdst),
  pmb_(0),
  seqNum_(seqNum)
{
  NI_PROFILE_FUNCTION;

  //  FIXME: в конструкторе мы никогда не узнаем что память не выделилась
  pmb_ = spDstCtx_->allocMsg(size);
  if (pmb_)
    pmb_->copy(data, size);
  else
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't allocate memory(sz=%d)"), __FUNCTION__, size));
}

C2STransmissionOp::~C2STransmissionOp()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if (pmb_)
  {
    spDstCtx_->freeMsg(pmb_);
    pmb_ = 0;
  }
}

int C2STransmissionOp::Start()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(u=%d p=%d)"), __FUNCTION__, spSrcCtx_->userid(), cpid_));

  if (!pmb_)
    return -1;

  return PostCompletion(spDstCtx_.get());
}

int C2STransmissionOp::Complete(Terabit::AsynchChannel *channel, TransportProtocolHandler* tph)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), __FUNCTION__, 
    channel->get_id(), spSrcCtx_->userid(), cpid_, spDstCtx_->svcid().c_str(), spDstCtx_->id(), svcpid_));

  UnicastPipeSP sp = spSrcCtx_->FindUnicastPipe(cpid_);
  if (!sp.null())
  {
    unsigned long lssn = sp->lastOutC2SSeqNum();
    if (seqNum_ && lssn >= seqNum_)
    {
     ACE_DEBUG((LM_ERROR, ACE_TEXT("C2S: wrong message sequence (lsn=%d sn=%d c=%d svc=%s svctx=%d svcpid=%d sz=%d ch=%d)"), 
       lssn, seqNum_, spSrcCtx_->userid(), spDstCtx_->svcid().c_str(), spDstCtx_->id(), svcpid_, pmb_->length(), channel->get_id()));
    }
  }

  NI_PROFILE_BLOCK("before handle output");

  int rc = -1;
  ChannelAddr caddr;
  caddr.client = spSrcCtx_->userid();
  caddr.pipe = svcpid_;
  caddr.SeqNum(seqNum_);
  rc = tph->HandleOutput(pmb_->base(), pmb_->length(), caddr, channel);

  NI_PROFILE_BLOCK("before set seqnum");

  if (!sp.null())
    sp->lastOutC2SSeqNum(seqNum_);

  ACE_DEBUG((LM_DEBUG, ACE_TEXT("C2S OUT(c=%d svc=%s svctx=%d svcpid=%d sz=%d ch=%d)"), 
    spSrcCtx_->userid(), spDstCtx_->svcid().c_str(), spDstCtx_->id(), svcpid_, pmb_->length(), channel->get_id()));

  NI_PROFILE_BLOCK("free msg");
  spDstCtx_->freeMsg(pmb_);
  pmb_ = 0;

  NI_PROFILE_BLOCK("close");
  Close();

  return rc;
}

}
