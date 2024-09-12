#pragma once
#include "naio/Types.h"
#include <ace/INET_Addr.h>

namespace naio
{
  class AcceptorHandle
  {
  public:
    AcceptorHandle();
    AcceptorHandle(AcceptorStrongPtr const & spAcceptor, 
      ACE_INET_Addr const & addr_, 
      void* usercontext = 0);

    ~AcceptorHandle();

  public:

    bool valid() const;
    bool invalid() const
    {
      return !valid();
    }

    void* userContext() const
    {
      return usercontext_;
    }

    ACE_INET_Addr address() const
    {
      return addr_;
    }

  private:
    AcceptorWeakPtr wpacceptor_;
    ACE_INET_Addr addr_;
    void* usercontext_;
  };
}
