#pragma once

#include <IOTerabit/IOThreadPool.h>

namespace naio
{
  class ThreadPool : public Terabit::IOThreadPool
  {
  public:

    ThreadPool(const ACE_TCHAR *name, ACE_Log_Msg_Callback* logcb);
    virtual ~ThreadPool();

  public:
    virtual int svc();

  private:
    ACE_Log_Msg_Callback* logcb_;
  };
}
