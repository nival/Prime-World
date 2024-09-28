#pragma once

namespace UserManager
{
  class PrepareUserEnvCtx;

  class IPrepareUserEnvNotify : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IPrepareUserEnvNotify, IBaseInterfaceMT );

  public:
    virtual void OnRelayAllocationInProgress(StrongMT<PrepareUserEnvCtx> const & ctx) = 0;
    virtual void OnPrepareUserEnvCompleted(int rc, StrongMT<PrepareUserEnvCtx> const & ctx) = 0;
  };
}
