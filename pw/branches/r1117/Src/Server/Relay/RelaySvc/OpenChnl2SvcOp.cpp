#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TProactor/Proactor.h"
#include "TransportMessagesHeaders.h"
#include "OpenChnl2SvcOp.h"
#include "RelayServer2Cfg.h"
#include "ClientContext.h"

using namespace Transport;

namespace Relay
{

OpenChnl2SvcOp::OpenChnl2SvcOp(Transport::TServiceId const & destsvc,
                               Transport::TServiceId const & srcsvc,
                               ClientContextSP const & spclient,
                               Transport::OpenChannelResponse const & _response,
                               Transport::TLoginData loginData)
:Operation(OperationType::OPEN_CHNL_2_SVC),
  destsvc_(destsvc),
  srcsvc_(srcsvc),
  loginData_(loginData),
  response_(_response),
  spClientCtx_(spclient),
  res_(Result::INIT),
  bpid_(INVALID_BACKEND_PIPE_ID),
  startTime_(0)
{
  NI_ASSERT(response_.channelType == Transport::EChannelType::Unicast, "Incorrect channel type");
}

OpenChnl2SvcOp::~OpenChnl2SvcOp()
{

}

Transport::TServiceId const & OpenChnl2SvcOp::svcid() const
{
  return destsvc_;
}

void OpenChnl2SvcOp::callback(int err, BackendContextWeakPtr wpctx)
{
  int rc = -1;
  if (0 == err)
  {
    //  начинаем установку канала
    BackendContextSP spbc = wpctx.strong();
    if (!spbc.null())
    {
      if (!spbc->isclosed())
      {
        ACE_ASSERT(spbc->svcid() == destsvc_);

        rc = StartChannelCreation(spbc);
        if (0 < rc)
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't start to open channel to service(c=%d svc=%s svctx=%d)"), 
          __FUNCTION__, spClientCtx_->userid(), spbc->svcid().c_str(), spbc->id()));
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Backend context is CLOSED(c=%d svc=%s svctx=%d)"), 
        __FUNCTION__, spClientCtx_->userid(), spbc->svcid().c_str(), spbc->id()));
      }
    }
    else
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Backend context is null(c=%d svc=%s)"), 
        __FUNCTION__, spClientCtx_->userid(), destsvc_.c_str()));
  }

  if (err != 0 || rc < 0)
  {
    //  не удалось установить соединение или начать установку канала
    res_ = Result::FAIL;

    //  create fake result message
    response_.success = false;
    rc = spClientCtx_->HandleOpenChannelResponse(&response_);
    Close();
  }
}

void* OpenChnl2SvcOp::act() const
{
  return (void*)this;
}

int OpenChnl2SvcOp::StartChannelCreation(BackendContextSP const & spbc)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(u=%d svcid=%s)"), __FUNCTION__, spClientCtx_->userid(), spbc->svctxid().c_str()));

  cpid_ = spClientCtx_->generatePipeId();
  if (EKnownPipeId::Invalid == cpid_)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("No free client pipe id(c=%d svc=%s svctx=%d)"), spClientCtx_->userid(), destsvc_.c_str(), spbc->id()));
    return -1;
  }

  startTime_ = ACE_OS::gettimeofday().sec();

  bpid_ = spbc->RegisterOpenChnlOp(this);
  if (INVALID_BACKEND_PIPE_ID == bpid_)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("No free backend pipe id(c=%d svc=%s svctx=%d)"), spClientCtx_->userid(), destsvc_.c_str(), spbc->id()));
    return -1;
  }

  OpenChannelRequest msg;
  msg.clientAddress = response_.clientAddress;
  msg.clientAddress.source = srcsvc_;
  msg.localPipeId = bpid_.pid_;
  msg.loginData = loginData_;
  msg.channelType = response_.channelType;

  //  QFIX(NUM_TASK): сохраняем переменные, которые надо залогировать, на стеке, 
  //  т.к. к моменту когда будем логировать, может прийти ответ от сервиса(см. RelayBackendProtocol::HandleOpenChannelResponse)
  //  и там объект будет удален
  //  (да, надо переделать на использование intrusive pointer, но уже не успею)
  Transport::TClientId userid = spClientCtx_->userid();
  Transport::TPipeId cpid = cpid_;
  Transport::TServiceId svcid = spbc->svcid();
  ContextId svctxid = spbc->id();
  Transport::TPipeId bpid = bpid_.pid_;

  int rc = spbc->HandleOpenChannelRequest(&msg, bpid_.cid_);
  if (rc < 0)
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Can't send channel creation msg to service(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
      spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), bpid_.pid_));

    OpenChnl2SvcOp* op = spbc->UnregisterOpenChnlOp(bpid_);
    NI_ASSERT(op == this, "Unregister operation must be equal to this op");
    spClientCtx_->freePipeId(cpid_);
  }
  else
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("New channel creation started(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
      userid, cpid, svcid.c_str(), svctxid, bpid));
  }

  return rc;
}

int OpenChnl2SvcOp::OnChannelEstablished(OpenChnl2SvcOp::Result::Enum _res, Transport::OpenChannelResponse const * msg, BackendContextSP const & spbc)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(r=%d c=%d p=%d)"), __FUNCTION__, (int)_res, bpid_.cid_, bpid_.pid_));

  ACE_ASSERT(destsvc_ == spbc->svcid());
  ACE_ASSERT(bpid_.cid_ == msg->remoteAddr.client);
  ACE_ASSERT(bpid_.pid_ == msg->localPipeId);
  ACE_ASSERT(spbc.null() == false);
  ACE_ASSERT(msg->channelType == response_.channelType);

  int rc = 0;
  res_ = _res;
  if (Result::SUCCESS == res_)
  {
    spbc->resetOpeningChannelTimeoutCounter();

    if (!spClientCtx_->isclosed())
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("New channel request approved(c=%d cpid=%d svc=%s svctx=%d svcpipes=%d svcpid=%d)"), 
        spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), spbc->UnicastPipeCount(), msg->remoteAddr.pipe));

      UnicastPipeSP svcpipe = spClientCtx_->RegisterUnicastPipe(destsvc_, spbc, cpid_, msg->remoteAddr.pipe);
      if (svcpipe.null() || svcpipe->isclosed())
      {
        res_ = Result::FAIL;

        ACE_ERROR((LM_ERROR, ACE_TEXT("Can't register unicast pipe(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
          spClientCtx_->userid(), cpid_, destsvc_.c_str(), spbc->id(), msg->remoteAddr.pipe));
      }
    }
    else
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("New channel request approved, but client is already closed(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
        spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), msg->remoteAddr.pipe));

      CloseChannelMessage ccmsg;
      ccmsg.clientAddress.client = msg->remoteAddr.client;
      ccmsg.clientAddress.pipe = msg->remoteAddr.pipe;

      rc = spbc->HandleCloseChannel(&ccmsg);
      if (rc < 0)
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("Can't send close channel msg to service(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
          spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), msg->remoteAddr.pipe));
      }
    }
  }
  else
  {
    if (Result::DECLINED == res_)
      ACE_ERROR((LM_WARNING, ACE_TEXT("New channel request DECLINED(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
        spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), msg->remoteAddr.pipe));
    else
    if (Result::TIMEOUT == res_)
    {
      spbc->incOpeningChannelTimeoutCounter();

      ACE_ERROR((LM_WARNING, ACE_TEXT("New channel request TIMEOUT(c=%d cpid=%d svc=%s svctx=%d svcpid=%d to=%d)"), 
        spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), msg->remoteAddr.pipe, RelayServer2Cfg::GetOpenBackendChannelTimeout()));
    }
    else
      ACE_ERROR((LM_WARNING, ACE_TEXT("New channel request FAILED(c=%d cpid=%d svc=%s svctx=%d svcpid=%d)"), 
        spClientCtx_->userid(), cpid_, spbc->svcid().c_str(), spbc->id(), msg->remoteAddr.pipe));

    spClientCtx_->freePipeId(cpid_);
  }

  OpenChnl2SvcOp* op = spbc->UnregisterOpenChnlOp(bpid_);
  NI_ASSERT(op == this, "Unregister operation must be equal to this op");

  if (!spClientCtx_->isclosed() && 0 == rc)
  {
    //  send result
    response_.success = (Result::SUCCESS == res_);
    if (response_.success)
      response_.remoteAddr.pipe = cpid_;

    rc = spClientCtx_->HandleOpenChannelResponse(&response_);
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("Can't send new channel response(c=%d cpid=%d svc=%s svctx=%d svcpipes=%d svcpid=%d)"), 
        spClientCtx_->userid(), cpid_, destsvc_.c_str(), spbc->id(), spbc->UnicastPipeCount(), bpid_.pid_));
    }
    else
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("New channel response sent(c=%d res=%d cpid=%d svc=%s svctx=%d svcpipes=%d svcpid=%d)"), 
        spClientCtx_->userid(), (int)res_, cpid_, destsvc_.c_str(), spbc->id(), spbc->UnicastPipeCount(), bpid_.pid_));
    }
  }

  return rc;
}

}
