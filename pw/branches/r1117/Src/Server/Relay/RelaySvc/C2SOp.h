#pragma once

#include "Operation.h"
#include "ClientContext.h"
#include "BackendContext.h"

namespace Relay
{

class C2SOp : public Operation
{
public:
  C2SOp(OperationType::Enum optype, 
        ClientContextSP const & spsrc, Transport::TPipeId const & cpid, 
        Transport::TPipeId const & svcpid,
        BackendContextSP const & spdst);
  ~C2SOp();

public:
  Transport::TPipeId GetClientPipeId() const;
  Transport::TPipeId GetSvcPipeId() const;
  Transport::TServiceId GetServiceId() const;
  Transport::TClientId GetClientId() const;
  BackendContextSP const & GetSvcCtx() const;

protected:
  ClientContextSP  spSrcCtx_;
  Transport::TPipeId        cpid_;
  Transport::TPipeId        svcpid_;
  BackendContextSP spDstCtx_;
};

inline
Transport::TPipeId C2SOp::GetClientPipeId() const
{
  return cpid_;
}

inline
Transport::TPipeId C2SOp::GetSvcPipeId() const
{
  return svcpid_;
}

inline
Transport::TServiceId C2SOp::GetServiceId() const
{
  return spDstCtx_->svcid();
}

inline
Transport::TClientId C2SOp::GetClientId() const
{
  return spSrcCtx_->userid();
}

inline
BackendContextSP const & C2SOp::GetSvcCtx() const
{
  return spDstCtx_;
}

}
