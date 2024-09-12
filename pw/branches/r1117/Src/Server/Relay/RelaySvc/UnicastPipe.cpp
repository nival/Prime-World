#pragma warning( push )
#pragma warning( disable : 4996)
#include "stdafx.h"
#include "UnicastPipe.h"
#include "RelayServer2Cfg.h"
#pragma warning( pop )

namespace Relay
{

UnicastPipe::UnicastPipe()
  :cpid_(Transport::EKnownPipeId::Invalid),
  lastInC2SSeqNum_(0),
  lastOutC2SSeqNum_(0),
  softPacketCountFactor_(1),
  hardPacketCountFactor_(1)
{
}

UnicastPipe::UnicastPipe(Transport::TServiceId const & _svcid,
            Transport::TPipeId const & _svcpid,
            BackendContextSP const & _svctx,
            StrongMT<ITrafficTracker> const & _tt,
            Transport::TClientId const & _cid, 
            Transport::TPipeId const & _cpid,
            ClientContextSP const & _cctx)
  :Pipe(_svcid, _svcpid, _svctx, _tt),
  cid_(_cid),
  cpid_(_cpid),
  cctx_(_cctx),
  lastInC2SSeqNum_(0),
  lastOutC2SSeqNum_(0),
  softPacketCountFactor_(1),
  hardPacketCountFactor_(1)
{
}

int UnicastPipe::checkC2SPacketFreq_(ACE_Time_Value const & _time, PacketFreqCheckData & _checkdata, 
                                     unsigned long & _packetCount, unsigned long & _packetCountFactor, ACE_Time_Value & _packetFreqCheckStartTime, 
                                     unsigned int _packetLimitPerCheckingPeriod, unsigned int _packetFreqCheckingPeriod)
{
  int rc = 1;

  ++_packetCount;
  if (_packetLimitPerCheckingPeriod && _packetLimitPerCheckingPeriod * _packetCountFactor <= _packetCount)
  {
    rc = 0;

    //  check
    if (_time >= _packetFreqCheckStartTime)
    {
      ACE_Time_Value t = _time - _packetFreqCheckStartTime;
      if (t.msec() < RelayServer2Cfg::GetClientPacketFreqCheckingPeriod()*_packetCountFactor)
        rc = -1;

      _checkdata.packets_ = _packetCount;
      _checkdata.period_ = t.msec();
      _checkdata.factor_ = _packetCountFactor;

      _packetFreqCheckStartTime = _time;
    }
    else
      rc = -2;

    //  reset counters
    _packetCount = 0;
    if (1 == _packetCountFactor)
      _packetCountFactor = 2;
    else
      _packetCountFactor = 1;
  }

  return rc;
}

int UnicastPipe::checkC2SPacketFreqSoft(ACE_Time_Value const & _time, PacketFreqCheckData & _checkdata)
{
    return checkC2SPacketFreq_(_time, _checkdata, softPacketCount_, softPacketCountFactor_, softPacketFreqCheckStartTime_, 
      RelayServer2Cfg::GetClientPacketSoftLimitPerCheckingPeriod(), RelayServer2Cfg::GetClientPacketFreqCheckingPeriod());
}

int UnicastPipe::checkC2SPacketFreqHard(ACE_Time_Value const & _time, PacketFreqCheckData & _checkdata)
{
  return checkC2SPacketFreq_(_time, _checkdata, hardPacketCount_, hardPacketCountFactor_, hardPacketFreqCheckStartTime_, 
    RelayServer2Cfg::GetClientPacketHardLimitPerCheckingPeriod(), RelayServer2Cfg::GetClientPacketFreqCheckingPeriod());
}

}
