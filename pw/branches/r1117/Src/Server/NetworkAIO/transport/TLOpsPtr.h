#pragma once
#include <naio/Ptr.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    class ChannelOp;
    typedef naio::Ptr<ChannelOp> ChannelOpPtr;
    class OpenChannel;
    typedef naio::Ptr<OpenChannel> OpenChannelPtr;
    class PingChannel;
    typedef naio::Ptr<PingChannel> PingChannelPtr;
    class SendData;
    typedef naio::Ptr<SendData> SendDataPtr;
    class CloseChannel;
    typedef naio::Ptr<CloseChannel> CloseChannelPtr;
    class ConnectionOutput;
    typedef naio::Ptr<ConnectionOutput> ConnectionOutputPtr;
    class AddRecipient;
    typedef naio::Ptr<AddRecipient> AddRecipientPtr;
    class RemoveRecipient;
    typedef naio::Ptr<RemoveRecipient> RemoveRecipientPtr;
  }
}
