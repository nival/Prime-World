#pragma once

#include "Operation.h"
#include "Network/TransportMessages.h"

namespace Relay
{
  class OpenChnl2ClientOp : public Operation
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
    OpenChnl2ClientOp(BackendContextSP const & _backendctx,
                      MulticastPipeSP const & _pipe,
                      ClientContextSP const & _clientctx,
                      Transport::AddRecipientRequest const & _initialRequest);
    ~OpenChnl2ClientOp();

  public:

    int Start();
    int Complete(Transport::OpenChannelResponse* imsg);
    time_t startTime() const;
    Transport::TPipeId localpid() const;
    MulticastPipeSP const & pipe() const;

  private:
    BackendContextSP backendctx_;
    MulticastPipeSP pipe_;
    ClientContextSP clientctx_;
    Transport::AddRecipientRequest initialRequest_;
    volatile time_t startTime_;
    Transport::TPipeId localpid_;
  };

  inline
  time_t OpenChnl2ClientOp::startTime() const
  {
    return startTime_;
  }

  inline
  Transport::TPipeId OpenChnl2ClientOp::localpid() const
  {
    return localpid_;
  }

  inline
  MulticastPipeSP const & OpenChnl2ClientOp::pipe() const
  {
    return pipe_;
  }


  typedef Relay::Ptr<OpenChnl2ClientOp> OpenChnl2ClientOpPtr;
}
