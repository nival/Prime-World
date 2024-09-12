#pragma once
#include "RelayPipe.h"

namespace Relay
{

struct PacketFreqCheckData
{
  PacketFreqCheckData()
    :period_(0),
    packets_(0),
    factor_(0),
    hard_(false)
  {}

  unsigned int period_;
  unsigned int packets_;
  unsigned int factor_;
  bool hard_;
};

class UnicastPipe : public Pipe
{
public:
  UnicastPipe();

  UnicastPipe(Transport::TServiceId const & _svcid,
    Transport::TPipeId const & _svcpid,
    BackendContextSP const & _svctx,
    StrongMT<ITrafficTracker> const & _tt,
    Transport::TClientId const & _cid, 
    Transport::TPipeId const & _cpid,
    ClientContextSP const & _cctx);

  Transport::TClientId cid() const;
  Transport::TPipeId const & cpipeid() const;
  ClientContextWP const & cctx() const;

  unsigned long lastInC2SSeqNum() const;
  void lastInC2SSeqNum(unsigned long seqnum);
  unsigned long lastOutC2SSeqNum() const;
  void lastOutC2SSeqNum(unsigned long seqnum);

  int checkC2SPacketFreqSoft(ACE_Time_Value const & _time, PacketFreqCheckData & _checkdata);
  int checkC2SPacketFreqHard(ACE_Time_Value const & _time, PacketFreqCheckData & _checkdata);

private:

  int checkC2SPacketFreq_(ACE_Time_Value const & _time, PacketFreqCheckData & _failureData, 
    unsigned long & _packetCount, unsigned long & _packetCountFactor, ACE_Time_Value & _packetPacketFreqCheckStartTime, 
    unsigned int _packetLimitPerCheckingPeriod, unsigned int _packetFreqCheckingPeriod);

private:
  Transport::TClientId cid_;
  Transport::TPipeId cpid_;
  ClientContextWP cctx_;

  ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastInC2SSeqNum_;
  ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastOutC2SSeqNum_;

  unsigned long softPacketCount_;
  unsigned long hardPacketCount_;
  unsigned long softPacketCountFactor_;
  unsigned long hardPacketCountFactor_;
  ACE_Time_Value softPacketFreqCheckStartTime_;
  ACE_Time_Value hardPacketFreqCheckStartTime_;
};

inline
Transport::TClientId UnicastPipe::cid() const
{
  return cid_;
}

inline
Transport::TPipeId const & UnicastPipe::cpipeid() const
{
  return cpid_;
}

inline
ClientContextWP const & UnicastPipe::cctx() const
{
  return cctx_;
}

inline
unsigned long UnicastPipe::lastInC2SSeqNum() const
{
  return lastInC2SSeqNum_.value();
}

inline
void UnicastPipe::lastInC2SSeqNum(unsigned long seqnum)
{
  lastInC2SSeqNum_.operator =(seqnum);
}

inline
unsigned long UnicastPipe::lastOutC2SSeqNum() const
{
  return lastOutC2SSeqNum_.value();
}

inline
void UnicastPipe::lastOutC2SSeqNum(unsigned long seqnum)
{
  lastOutC2SSeqNum_.operator =(seqnum);
}

}
