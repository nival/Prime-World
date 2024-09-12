#pragma once

#include "IOTerabit/ChannelAcceptor.h"

namespace Relay
{

class ClientAcceptor : public Terabit::ChannelAcceptor
{
public:
    ClientAcceptor (Terabit::IOThreadPool &     task,
                    Terabit::ProtocolFactory &  protocol_factory, 
                    Terabit::ChannelManager &   manager);

    virtual ~ClientAcceptor (void);

private:

    virtual int  on_accept_completed (const TRB_Asynch_Accept::Result &result);

    Terabit::IOThreadPool &    task_;
    Terabit::ProtocolFactory & protocol_factory_;
    Terabit::ChannelManager &  manager_;
};

}
