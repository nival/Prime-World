#pragma once

#include "Operation.h"
#include "Network/TransportMessages.h"
#include "TransportProtocol.h"
#include "SvcConnectionManager.h"

namespace Relay
{

class OpenChnl2SvcOp : public Operation, public SvcConnectionManager::ICallback
{
public:

  struct Result
  {
    enum Enum
    {
      TIMEOUT = -3,
      DECLINED = -2,
      FAIL = -1,
      SUCCESS = 0,
      INIT = 1,
    };
  };

public:
  OpenChnl2SvcOp(Transport::TServiceId const & destsvc,
                Transport::TServiceId const & srcsvc,
                ClientContextSP const & spclient,
                Transport::OpenChannelResponse const & result,
                Transport::TLoginData loginData);

  ~OpenChnl2SvcOp();

public:
  int StartChannelCreation(BackendContextSP const & spbc);
  int OnChannelEstablished(OpenChnl2SvcOp::Result::Enum _res, Transport::OpenChannelResponse const * msg, BackendContextSP const & spbc);

public:
  //  getters
  Transport::TServiceId const & GetDstSvcId() const;
  Transport::TLoginData const & GetLoginData() const;
  ClientContextSP const & GetClientCtx() const;
  bool IsSuccess() const;
  time_t GetStartTime() const;
  Transport::OpenChannelResponse const & GetOpenChannelResponse() const;
  BackendPipeId const & GetBackendPipeId() const;

protected:
  //  SvcConnectionManager::ICallback
  virtual Transport::TServiceId const & svcid() const;
  virtual void* act() const;
  virtual void callback(int err, BackendContextWeakPtr wpctx);

private:
  Transport::TServiceId destsvc_;
  Transport::TServiceId srcsvc_;
  Transport::TLoginData loginData_;
  Transport::OpenChannelResponse response_;
  ClientContextSP  spClientCtx_;
  Transport::TPipeId  cpid_;
  BackendPipeId bpid_;
  volatile time_t startTime_;

  Result::Enum res_;
};

inline
Transport::TLoginData const & OpenChnl2SvcOp::GetLoginData() const
{
  return loginData_;
}

inline
Transport::TServiceId const & OpenChnl2SvcOp::GetDstSvcId() const
{
  return destsvc_;
}

inline
ClientContextSP const & OpenChnl2SvcOp::GetClientCtx() const
{
  return spClientCtx_;
}

inline
bool OpenChnl2SvcOp::IsSuccess() const
{
  return Result::SUCCESS == res_;
}

inline
time_t OpenChnl2SvcOp::GetStartTime() const
{
  return startTime_;
}

inline
Transport::OpenChannelResponse const & OpenChnl2SvcOp::GetOpenChannelResponse() const
{
  return response_;
}

inline
BackendPipeId const & OpenChnl2SvcOp::GetBackendPipeId() const
{
  return bpid_;
}

}
