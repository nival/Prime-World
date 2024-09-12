#pragma warning( disable : 4996)
#include "stdafx.h"
#include "OpenChnl2ClientOp.h"
#include "BackendContext.h"
#include "MulticastPipe.h"
#include "ClientContext.h"
#include <Network/TransportMessages.h>

using namespace Transport;

namespace Relay
{
  OpenChnl2ClientOp::OpenChnl2ClientOp(BackendContextSP const & _backendctx,
                                       MulticastPipeSP const & _pipe,
                                       ClientContextSP const & _clientctx,
                                       AddRecipientRequest const & _initialRequest)
    :Operation(OperationType::OPEN_CHNL_2_CLIENT),
    backendctx_(_backendctx),
    pipe_(_pipe),
    clientctx_(_clientctx),
    initialRequest_(_initialRequest),
    startTime_(0),
    localpid_(Transport::EKnownPipeId::Invalid)
  {
  }

  OpenChnl2ClientOp::~OpenChnl2ClientOp()
  {
  }

  int OpenChnl2ClientOp::Start()
  {
    int rc = -1;
    localpid_ = clientctx_->RegisterOpenChnlOp(this);
    if (Transport::EKnownPipeId::Invalid != localpid_)
    {
      startTime_ = ACE_OS::gettimeofday().sec();

      OpenChannelRequest msg;
      msg.clientAddress = Address(backendctx_->svcid(), "", clientctx_->userid());
      msg.localPipeId = localpid_;
      msg.channelType = Transport::EChannelType::Unicast;

      rc = clientctx_->HandleOpenChannelRequest(&msg);
      if (rc < 0)
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("Can't send channel creation msg to client(c=%d localpid=%d svc=%s)"), 
          clientctx_->userid(), localpid_, backendctx_->svctxid().c_str()));

        OpenChnl2ClientOpPtr op = clientctx_->UnregisterOpenChnlOp(localpid_);
        NI_ASSERT(op == this, "Unregister operation must be equal to this op");
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("New channel creation to client started(c=%d localpid=%d svc=%s)"), 
          clientctx_->userid(), localpid_, backendctx_->svctxid().c_str()));
      }
    }

    return rc;
  }

  int OpenChnl2ClientOp::Complete(Transport::OpenChannelResponse* imsg)
  {
    int rc = -1;

    if (!pipe_->isclosed())
    {
      if (imsg->success)
      {
        rc = clientctx_->registerPipeId(imsg->remoteAddr.pipe);
        if (rc < 0)
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't register client pipeid (c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__,
            clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));

          Transport::CloseChannelMessage ccm;
          ccm.clientAddress = imsg->remoteAddr;
          if (clientctx_->HandleCloseChannel(&ccm, false) < 0)
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't send close channel msg(c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__,
                clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));
          }
          else
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("%s: close channel msg sent to client(c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__,
              clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));
          }
        }
        else
        {
          rc = pipe_->AddRecipient(imsg->remoteAddr.pipe, clientctx_);
          if (rc < 0)
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("Can't add client context as recipeint to multicast pipe(c=%d cpid=%d svc=%s svcpid=%d)"), 
              clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));

            clientctx_->unregisterPipeId(imsg->remoteAddr.pipe);

            Transport::CloseChannelMessage ccm;
            ccm.clientAddress = imsg->remoteAddr;
            if (clientctx_->HandleCloseChannel(&ccm, false) < 0)
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't send close channel msg(c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__,
                clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));
            }
            else
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("%s: close channel msg sent to client(c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__,
                clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));
            }
          }
          else
          {
            rc = clientctx_->AttachMulticastPipe(pipe_);
            if (rc < 0)
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("Can't attach multicast pipe to client context(c=%d cpid=%d svc=%s svcpid=%d)"), 
                clientctx_->userid(), imsg->remoteAddr.pipe, pipe_->svctxid().c_str(), pipe_->svcpipeid()));
            }
          }
        }
      }

      Transport::AddRecipientResponse omsg;
      omsg.caddr = initialRequest_.caddr;
      omsg.recipient = initialRequest_.recipient;
      if (imsg->success)
      {
        if (rc >= 0)
          omsg.result = AddRecipientResult::OK;
        else
          omsg.result =  AddRecipientResult::FAIL;
      }
      else
        omsg.result =  AddRecipientResult::FAIL;

      rc = backendctx_->HandleAddRecipientResponse(&omsg);
      if (rc < 0)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("Can't send add recipient response(c=%d svc=%s svcpid=%d)"), 
          clientctx_->userid(), backendctx_->svctxid().c_str(), pipe_->svcpipeid()));
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("Add recipient response sent(c=%d res=%d svc=%s svcpid=%d)"), 
          clientctx_->userid(), (int)omsg.result, backendctx_->svctxid().c_str(), pipe_->svcpipeid()));
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s: multicast pipe is CLOSED(c=%d svc=%s svcpid=%d state=%d)"), 
        clientctx_->userid(), pipe_->svctxid().c_str(), pipe_->svcpipeid(), (int)pipe_->state()));
    }

    return rc;
  }
}
