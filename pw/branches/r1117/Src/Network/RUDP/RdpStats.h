#ifndef RUDP_RDPSTATS_H_INCLUDED
#define RUDP_RDPSTATS_H_INCLUDED


#include <intrin.h>
#pragma intrinsic(_InterlockedCompareExchange64)

namespace
{
  // This function will work on WinXP 32 bit (Unlike the InterlockedExchangeAdd64 which also isn't intrinsic)
  void NiInterlockedExchangeAdd64(__int64 volatile *Addend, __int64 Value)
  {
      __int64 Comperand;
      do 
      {
          Comperand = *Addend;
      } while (Comperand != _InterlockedCompareExchange64(Addend, Comperand + Value, Comperand));
  }
} // namespace


namespace ni_udp
{

class RdpStats : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpStats, BaseObjectMT );

public:
  RdpStats() :
  bytesWritten( 0 ),
  bytesRecieved( 0 ),
  bytesDelivered( 0 ),
  packetsWritten( 0 ),
  packetsRecieved( 0 ),
  datagramsDelivered( 0 ),
  datagramsQueued( 0 ),
  datagramsRecieved( 0 ),
  rawDatagramsSent( 0 ),
  rawDatagramsRecieved( 0 ),
  errors( 0 ),
  warnings( 0 ),
  retransmits( 0 )
  {}

  volatile LONGLONG     bytesWritten, bytesRecieved;
  volatile LONGLONG     bytesDelivered;
  volatile LONG         packetsWritten, packetsRecieved;
  volatile LONG         datagramsDelivered, datagramsQueued, datagramsRecieved;
  volatile LONG         rawDatagramsSent, rawDatagramsRecieved;
  volatile LONG         errors;
  volatile LONG         warnings;
  volatile LONG         retransmits;

  void Inc( volatile LONG RdpStats::*_field, int _inc = 1 )
  {
    InterlockedExchangeAdd( &(this->*_field), _inc );
  }

  void Inc( volatile LONGLONG RdpStats::*_field, int _inc = 1 )
  {
    NiInterlockedExchangeAdd64( &(this->*_field), _inc );
  }
};



class RdpConnStats : public RdpStats
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpConnStats, RdpStats );

public:
  explicit RdpConnStats( RdpStats * _global ) :
  globalStats( _global )
  {}

  template <class T>
  void Inc( volatile T RdpStats::*_field, int _inc = 1 )
  {
    RdpStats::Inc( _field, _inc );
    globalStats->RdpStats::Inc( _field, _inc );
  }

private:
  StrongMT<RdpStats>  globalStats;
};

} //namespace ni_udp

#endif //RUDP_RDPSTATS_H_INCLUDED
