#ifndef RUDP_RDPEPHMUX_H_INCLUDED
#define RUDP_RDPEPHMUX_H_INCLUDED

#include "RdpCommon.h"
#include "System/RandomInterface.h"
#include <map>


namespace ni_udp
{

class RdpEphemeralMuxes : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpEphemeralMuxes, BaseObjectMT );

public:
  RdpEphemeralMuxes( RdpOptionsObject * _opt, ni_rnd::IGenerator * _rnd );

  unsigned AllocateMux( timer::Time _now );
  void FreeMux( unsigned _mux, timer::Time _expiretime );

private:
  struct Mux
  {
    timer::Time   expireTime;

    explicit Mux( timer::Time _expiretime = 0 ) :
    expireTime( _expiretime )
    {}
  };

  typedef std::map<unsigned, Mux>  Muxes;

  StrongMT<RdpOptionsObject>  options;
  Strong<ni_rnd::IGenerator>  rnd;
  Muxes                       muxes;
  unsigned                    suspendedNumber;

  void FlushSuspendedMuxes( timer::Time _now );
  unsigned RandomizeMux();
};

} //namespace ni_udp

#endif //RUDP_RDPEPHMUX_H_INCLUDED
