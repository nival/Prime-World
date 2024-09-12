#pragma warning( push )
#pragma warning( disable : 4996)
#include "stdafx.h"
#include "MulticastPipe.h"
#include "ClientContext.h"
#pragma warning( pop )

namespace Relay
{
  MulticastPipe::MulticastPipe()
  {
  }

  MulticastPipe::MulticastPipe(Transport::TServiceId const & _svcid,
                              Transport::TPipeId const & _svcpid,
                              BackendContextSP const & _svctx,
                              StrongMT<ITrafficTracker> const & _tt)
    :Pipe(_svcid, _svcpid, _svctx, _tt)
  {
  }

  int MulticastPipe::AddRecipient(Transport::TPipeId _cpid, ClientContextSP const & _cctx)
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(cpid=%d c=%d svcid=%s)"), __FUNCTION__, _cpid, _cctx->userid(), svctxid().c_str()));

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);
    for(RecipientsT::const_iterator it = recipients_.begin(); it != recipients_.end(); ++it)
    {
      if (it->cctx_->userid() == _cctx->userid())
        return -1;
    }

    recipients_.push_back(Recipient(_cpid, _cctx));
    return 0;
  }

  int MulticastPipe::HandleOutput(char const * _data, size_t _size)
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);
    int rc = -1;

    lastOutS2CSeqNum(lastOutS2CSeqNum()+1);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(seq=%d svcid=%s)"), __FUNCTION__, lastOutS2CSeqNum(), svctxid().c_str()));

    for(RecipientsT::iterator it = recipients_.begin(); it != recipients_.end(); )
    {
      rc = it->cctx_->HandleOutput(it->cpid_, _data, _size, lastOutS2CSeqNum());
      if (rc < 0)
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s.  Can't send multicast packet to client. Recipient will be removed from multicast channel(c=%d p=%d svc=%s)"),
          __FUNCTION__, it->cctx_->userid(), it->cpid_, svctxid().c_str()));

        //  remove client from multicast
        it = recipients_.erase(it);
      }
      else
        ++it;
    }

    rc = 0;
    return rc;
  }

  Transport::TPipeId MulticastPipe::RemoveRecipient(Transport::TClientId const & _cid)
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d svcid=%s)"), __FUNCTION__, _cid, svctxid().c_str()));

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);
    Transport::TPipeId pipeid = Transport::EKnownPipeId::Invalid;
    for(RecipientsT::iterator it = recipients_.begin(); it != recipients_.end(); ++it)
    {
      if (it->cctx_->userid() == _cid)
      {
        pipeid = it->cpid_;
        recipients_.erase(it);
        break;
      }
    }

    return pipeid;
  }

  int MulticastPipe::HandleCloseChannel()
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(svcid=%s spid=%d)"), __FUNCTION__, svctxid().c_str(), svcpipeid()));

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);
    for(RecipientsT::iterator it = recipients_.begin(); it != recipients_.end(); ++it)
    {
      Recipient const & r = *it;
      if (r.cctx_->isopen())
      {
        Transport::CloseChannelMessage ccm;
        ccm.clientAddress = Transport::ChannelAddr(r.cpid_, r.cctx_->userid());
        r.cctx_->HandleCloseChannel(&ccm, false);

        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Close channel send to client(c=%d cpid=%d svc=%s spid=%d)"),
          __FUNCTION__, r.cctx_->userid(), r.cpid_, svctxid().c_str(), svcpipeid()));
      }
    }

    return 0;
 }
}
