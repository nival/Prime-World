#pragma once
#include "C2SOp.h"

namespace Relay
{

class TransportProtocolHandler;

class C2STransmissionOp : public C2SOp
{
public:
  C2STransmissionOp(ClientContextSP const & spsrc, Transport::TPipeId const & cpid, 
                    Transport::TPipeId const & svcpid,
                    BackendContextSP const & spdst, 
                    char const * data, size_t size,
                    unsigned long seqNum);
  ~C2STransmissionOp();

public:
  int Start();
  int Complete(Terabit::AsynchChannel *channel, TransportProtocolHandler* tph);

  size_t GetDataSize() const;
  unsigned long GetSeqNum() const;

private:
  ACE_Message_Block*        pmb_;
  unsigned long             seqNum_;
};

inline
size_t C2STransmissionOp::GetDataSize() const
{
  if (!pmb_)
    return 0;

  return pmb_->length();
}

inline
unsigned long C2STransmissionOp::GetSeqNum() const
{
  return seqNum_;
}

}
