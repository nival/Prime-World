#pragma once
#include "IOTerabit/ChannelAcceptor.h"

namespace naio
{
  class Acceptor : public Terabit::ChannelAcceptor
  {
  public:
    Acceptor (Terabit::IOThreadPool &     task,
              Terabit::ProtocolFactory &  protocol_factory, 
              Terabit::ChannelManager &   manager);

    virtual ~Acceptor (void);

  public:
    //  redefine base method due to need act (asynchronous completion token)
    int start (const ACE_Addr & addr,
      void* act,
      int num_initial_accepts,
      int bytes_to_read = 0);

  private:

    virtual int  on_accept_completed (const TRB_Asynch_Accept::Result &result);

    Terabit::IOThreadPool &    task_;
    Terabit::ProtocolFactory & protocol_factory_;
    Terabit::ChannelManager &  manager_;
    void* act_;
  };
}
