#pragma once
#include <IOTerabit/ChannelConnector.h>

namespace naio
{
  class Connector : public Terabit::ChannelConnector
  {
  public:
    Connector (Terabit::IOThreadPool & tp,
      Terabit::ProtocolFactory & protocol_factory, 
      Terabit::ChannelManager & manager);
    ~Connector();

  private:
    virtual int on_connect_completed(const TRB_Asynch_Connect::Result &result);

  private:
    Terabit::ProtocolFactory & protocol_factory_;
    Terabit::ChannelManager &  manager_;
  };

}
