#pragma once

#include <IOTerabit/IOThreadPool.h>

namespace Relay
{
  class IOThreadPool : public Terabit::IOThreadPool
  {
  public:

    IOThreadPool(const ACE_TCHAR *name, ACE_Log_Msg_Callback* logcb);
    virtual ~IOThreadPool();

  public:
    virtual int svc();

  private:
    ACE_Log_Msg_Callback* logcb_;
  };
}
