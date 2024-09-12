#ifndef RUDP_RDPLOGIC_H_INCLUDED
#define RUDP_RDPLOGIC_H_INCLUDED

#include "IRdp.h"
#include "RdpCommon.h"
#include "RdpHandshake.h"
#include "RdpListenContext.h"
#include "RdpEphMux.h"
#include "System/JobThread.h"
#include "System/Histogram.h"
#include <map>
#include <vector>


namespace ni_udp
{

namespace proto
{
  namespace EPktType { enum Enum; }
}


class RdpOptionsObject;
class IRdpPacketAllocator;
class RdpListenContext;
class RdpConnection;
class RdpPacket;



class RdpLogic : public IRdpLogic, public threading::IThreadJob, public ISocketCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_4( RdpLogic, IRdpLogic, threading::IThreadJob, ISocketCallback, BaseObjectMT );

public:
  RdpLogic( const RdpOptions & _opt, ni_rnd::IGenerator * _rnd, timer::ITimer * _clock );
  ~RdpLogic();

  void Setup( ISocket * _socket, IRdpPacketAllocator * _pktAllocator );
  void Cleanup();

  IRdpListenContext *   StartListen( unsigned _mux, IRdpListenContextCallback * _cb );
  IRdpConnection *      StartConnection( const NetAddr & _remoteAddr, unsigned _mux, IRdpConnectionCallback * _cb );

  void ParallelPoll();

protected:
  //threading::IThreadJob
  virtual void Work( volatile bool & isRunning );

  //IRdpLogic
  virtual const RdpCommonCtx &  Ctx() const { return ctx; }
  virtual timer::Time           Now() { return now; }
  virtual void                  StopListen( RdpListenContext * _listenCtx );
  virtual void                  IncomingHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx, IRdpListenContextCallback * _listenCallback );
  virtual unsigned              ReallocateLocalEphemeralMux( const ConnDescriptor & _descr );

  //ISocketCallback
  virtual void  OnDatagram( ISocket * _socket, const NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime );

private:
  struct IncomingPkt
  {
    proto::EPktType::Enum   pktType;
    unsigned                seqIndex;
    ConnDescriptor          descr;
    StrongMT<RdpPacket>     data;

    explicit IncomingPkt( proto::EPktType::Enum _pkt, unsigned _seqIdx, const ConnDescriptor & _descr ) :
    pktType( _pkt ),
    seqIndex( _seqIdx ),
    descr( _descr )
    {}
  };

  typedef std::map<ConnDescriptor, StrongMT<RdpConnection>>  Connections;
  typedef std::map<unsigned, StrongMT<RdpListenContext>>  ListenContexts;
  typedef std::vector<IncomingPkt>  IncomingPackets;

  NetAddr                         localAddr; //for debug and logging
  StrongMT<ISocket>               socket;

  threading::Mutex                incomingMutex;
  IncomingPackets                 incomingPackets, incomingPacketsBuffer;

  threading::Mutex                mutex;
  timer::Time                     now;
  RdpCommonCtx                    ctx;
  Connections                     connections;
  ListenContexts                  listenContexts;
  Strong<ni_rnd::IGenerator>      rnd;
  StrongMT<timer::ITimer>         clock;
  StrongMT<RdpEphemeralMuxes>     ephemeralMuxes;
  StrongMT<RdpStats>              globalStats;

  timer::Time                     tempDbgNextDump, tempDbgPrevPollTime;
  LONG                            tempDbgDgSent, tempDbgDgRecv, tempDbgWarn, tempDbgErr, tempDbgRetr, tempDbgDelivered;
  CustomHistogram                 tempDbgPollHisto, tempDbgSleepHisto;

  void PollConnections();
  void PollListenContexts();
  
  void ParseIncomingPackets();
  void ParsePacket( const IncomingPkt & _slot );

  void on_HandshakeInit( const ConnDescriptor & _descr, unsigned _seqIdx );

  RdpConnection * FindConnNoLock( const ConnDescriptor & _descr ) const;
  RdpListenContext * FindListenCtxNoLock( const ConnDescriptor & _descr ) const;
};

} //namespace ni_udp

#endif //RUDP_RDPLOGIC_H_INCLUDED
