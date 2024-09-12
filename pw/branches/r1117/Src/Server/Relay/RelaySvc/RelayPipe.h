#pragma once
#include "Resource.h"
#include "Network/TransportUtils.h"
#include "Types.h"
#include "ITrafficTracker.h"

namespace Relay
{
  class Pipe : public Resource
  {
  public:
    Pipe();

    Pipe(Transport::TServiceId const & _svcid,
      Transport::TPipeId const & _svcpid,
      BackendContextSP const & _svctx,
      StrongMT<ITrafficTracker> const & _tt);

    BackendContextWP const & svctx() const;
    Transport::TServiceId const & svcid() const;
    Transport::TServiceId const & svctxid() const;
    Transport::TPipeId const & svcpipeid() const;

    unsigned long lastInS2CSeqNum() const;
    void lastInS2CSeqNum(unsigned long seqnum);
    unsigned long lastOutS2CSeqNum() const;
    void lastOutS2CSeqNum(unsigned long seqnum);

    StrongMT<ITrafficTracker> trafficTracker() const;

  private:
    Transport::TServiceId svcid_;
    Transport::TServiceId svctxid_;
    Transport::TPipeId svcpipeid_;
    BackendContextWP svctx_;
    StrongMT<ITrafficTracker> trafficTracker_;

    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastInS2CSeqNum_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastOutS2CSeqNum_;
  };

  inline
  BackendContextWP const & Pipe::svctx() const
  {
    return svctx_;
  }

  inline
  Transport::TServiceId const & Pipe::svcid() const
  {
    return svcid_;
  }

  inline
  Transport::TServiceId const & Pipe::svctxid() const
  {
    return svctxid_;
  }

  inline
  Transport::TPipeId const & Pipe::svcpipeid() const
  {
    return svcpipeid_;
  }

  inline
  unsigned long Pipe::lastInS2CSeqNum() const
  {
    return lastInS2CSeqNum_.value();
  }

  inline
  void Pipe::lastInS2CSeqNum(unsigned long seqnum)
  {
    lastInS2CSeqNum_.operator =(seqnum);
  }

  inline
  unsigned long Pipe::lastOutS2CSeqNum() const
  {
    return lastOutS2CSeqNum_.value();
  }

  inline
  void Pipe::lastOutS2CSeqNum(unsigned long seqnum)
  {
    lastOutS2CSeqNum_ = seqnum;
  }

  inline
  StrongMT<ITrafficTracker> Pipe::trafficTracker() const
  {
    return trafficTracker_;
  }
}
