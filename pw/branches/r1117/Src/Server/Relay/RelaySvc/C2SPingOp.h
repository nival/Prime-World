#pragma once

#include "C2SOp.h"

namespace Relay
{

class TransportProtocolHandler;

class C2SPingOp : public C2SOp
{
public:
  C2SPingOp(ClientContextSP const & spsrc, Transport::TPipeId const & cpid, 
            Transport::TPipeId const & svcpid,
            BackendContextSP const & spdst, 
            Transport::ChannelAddr const & pingcaddr,
            unsigned long long sendTime,
            unsigned long seqNum);
  ~C2SPingOp();

public:
  int Execute(Terabit::AsynchChannel *channel, TransportProtocolHandler* tph);

private:
  Transport::ChannelAddr chaddr_;
  unsigned long long originalSendTime_;
  unsigned long seqNum_;
};

}
