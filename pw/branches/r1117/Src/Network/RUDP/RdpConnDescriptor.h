#ifndef RDPCONNDESCRIPTOR_H_INCLUDED
#define RDPCONNDESCRIPTOR_H_INCLUDED

#include "ISockSrv.h"

namespace ni_udp
{

struct ConnDescriptor
{
  NetAddr   remote;
  unsigned  localMux;
  unsigned  remoteMux;

  ConnDescriptor( const NetAddr & _remoteAddr, unsigned _localMux, unsigned _remoteMux ) :
  remote( _remoteAddr ), localMux( _localMux ), remoteMux( _remoteMux )
  {}

  bool operator < ( const ConnDescriptor & other ) const
  {
    if ( remoteMux != other.remoteMux )
      return remoteMux < other.remoteMux;

    if ( localMux != other.localMux )
      return localMux < other.localMux;

    return remote < other.remote;
  }

  bool operator == ( const ConnDescriptor & other ) const
  {
    return ( localMux == other.localMux ) && ( remoteMux == other.remoteMux ) && ( remote == other.remote );
  }
};

} //namespace ni_udp



//Log formatting stuff
namespace text
{

template<>
class TArg<ni_udp::ConnDescriptor> : public BasicArg
{
public:
  TArg( const ni_udp::ConnDescriptor & _descr ) : descr( _descr ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    char buf[48] = "";
    _snprintf( buf, 47, "(%d.%d.%d.%d:%u %u:%u)", 
      (unsigned)descr.remote.sin_addr.s_net, (unsigned)descr.remote.sin_addr.s_host, 
      (unsigned)descr.remote.sin_addr.s_lh, (unsigned)descr.remote.sin_addr.s_impno, 
      (unsigned)descr.remote.Port(),
      descr.localMux, descr.remoteMux );
    buf[47] = 0;

    FormatString( buffer, buf, specs );
  }

  virtual bool AsInt( int & _intValue ) const { return false; }

private:
  const ni_udp::ConnDescriptor & descr;
};

} //namespace text

#endif //RDPCONNDESCRIPTOR_H_INCLUDED
