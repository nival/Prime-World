#ifndef RUDP_RDPCOMMON_H_INCLUDED
#define RUDP_RDPCOMMON_H_INCLUDED

#include "ISockSrv.h"
#include "IRdp.h"
#include "RdpConnDescriptor.h"
#include <list>


namespace ni_udp
{

class RdpOptionsObject : public RdpOptions, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpOptionsObject, BaseObjectMT );

public:
  explicit RdpOptionsObject( const RdpOptions & _sett ) :
  RdpOptions( _sett )
  {}
};



class RdpListenContext;
class RdpWriter;
class RdpConnStats;
class RdpStats;
class IRdpPacketAllocator;


//TODO: Convert most of the members into methods of IRdpConnImplCallback 
struct RdpCommonCtx
{
  StrongMT<RdpOptionsObject>      options;
  StrongMT<RdpWriter>             writer;
  StrongMT<RdpConnStats>          stats;
  StrongMT<IRdpPacketAllocator>   allocator;
};



class IRdpLogic : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpLogic, IBaseInterfaceMT );

public:
  virtual const RdpCommonCtx &  Ctx() const = 0;
  virtual timer::Time           Now() = 0;
  virtual void                  StopListen( RdpListenContext * _listenCtx ) = 0;
  virtual void                  IncomingHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx, IRdpListenContextCallback * _listenCallback ) = 0;
  virtual unsigned              ReallocateLocalEphemeralMux( const ConnDescriptor & _descr ) = 0;
};



class IRdpConnImplCallback
{
public:
  virtual const ConnDescriptor & ConnDescr() const = 0;
  virtual void ConnCbFailure() = 0;
  virtual void ConnCbPacketAcknowledged( timer::Time _rtt ) = 0;
  virtual void ConnCbPacketRetransmitted() = 0;
};

} //namespace ni_udp

#endif //RUDP_RDPCOMMON_H_INCLUDED
