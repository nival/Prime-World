#include "naio/stdafx.h"
#include "naio/AcceptorHandle.h"
#include "naio/Acceptor.h"

namespace naio
{
  AcceptorHandle::AcceptorHandle()
    :usercontext_(0)
  {
  }

  AcceptorHandle::AcceptorHandle(AcceptorStrongPtr const & spAcceptor, 
                                ACE_INET_Addr const & addr, 
                                void* usercontext)
    :wpacceptor_(spAcceptor),
    addr_(addr),
    usercontext_(usercontext)
  {
  }

  AcceptorHandle::~AcceptorHandle()
  {
  }

  bool AcceptorHandle::valid() const
  {
    return !(wpacceptor_.strong().null());
  }
}
