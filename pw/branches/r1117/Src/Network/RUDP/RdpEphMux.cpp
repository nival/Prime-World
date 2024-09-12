#include "stdafx.h"
#include "RdpEphMux.h"
#include <algorithm>
#include "System/InlineProfiler.h"


namespace ni_udp
{

RdpEphemeralMuxes::RdpEphemeralMuxes( RdpOptionsObject * _opt, ni_rnd::IGenerator * _rnd ) :
options( _opt ),
rnd( _rnd ),
suspendedNumber( 0 )
{
}



unsigned RdpEphemeralMuxes::AllocateMux( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  FlushSuspendedMuxes( _now );

  const size_t maxMuxes = options->lastEphemeralMux - options->firstEphemeralMux;
  if ( muxes.size() >= maxMuxes )
    return 0;

  unsigned m = RandomizeMux();
  NI_VERIFY( m, "", return 0 );

  Mux & slot = muxes[m];
  NI_ASSERT( slot.expireTime == 0, "" );

  slot.expireTime = -1;
  return m;
}



unsigned RdpEphemeralMuxes::RandomizeMux()
{
  if ( !muxes.size() )
    return rnd->Next( options->firstEphemeralMux, options->lastEphemeralMux );

  size_t n = rnd->Next( muxes.size() );

  Muxes::iterator it = muxes.begin();
  std::advance( it, n );

  while ( true )
  {
    unsigned m = it->first;
    Muxes::iterator next = it;
    ++next;

    if ( next != muxes.end() )
    {
      unsigned delta = next->first - m;
      if ( delta <= 1 )
      {
        it = next;
        continue;
      }

      return it->first + 1 + rnd->Next( delta - 1 );
    }

    next = muxes.begin();

    unsigned delta = options->lastEphemeralMux - m;
    delta += next->first - options->firstEphemeralMux;
    delta += 1;

    if ( delta <= 1 )
    {
      it = next;
      continue;
    }

    unsigned d = rnd->Next( delta - 1 );

    if ( it->first + d + 1 <= options->lastEphemeralMux )
      return it->first + d + 1;
    else
      return options->firstEphemeralMux + ( ( it->first + d ) - options->lastEphemeralMux );
  }
}



void RdpEphemeralMuxes::FreeMux( unsigned _mux, timer::Time _expiretime )
{
  Muxes::iterator it = muxes.find( _mux );
  NI_VERIFY( it != muxes.end(), "", return );

  if ( ( it->second.expireTime < 0 ) && ( _expiretime >= 0 ) )
    ++suspendedNumber;
  
  it->second.expireTime = _expiretime;
}



void RdpEphemeralMuxes::FlushSuspendedMuxes( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  if ( !suspendedNumber )
    return;

  for ( Muxes::iterator it = muxes.begin(); it != muxes.end(); )
  {
    if ( it->second.expireTime >= 0 )
      if ( _now > it->second.expireTime )
      {
        --suspendedNumber;
        it = muxes.erase( it );
        continue;
      }
    ++it;
  }
}

} //namespace ni_udp

