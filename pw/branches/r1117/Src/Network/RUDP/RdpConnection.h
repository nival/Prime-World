#ifndef RUDP_RDPCONNECTION_H_INCLUDED
#define RUDP_RDPCONNECTION_H_INCLUDED

#include "IRdp.h"
#include "RdpCommon.h"
#include "RdpConnDescriptor.h"
#include "RdpHandshake.h"
#include "RdpInPktQueue.h"
#include "RdpOutPktQueue.h"
#include "RdpPing.h"
#include "RdpCongestionControl.h"


namespace ni_udp
{

class RdpWriter;
class RdpActiveHandshake;
class RdpOptionsObject;
class IRdpPacketAllocator;


class RdpConnection : public IRdpHandshakeCallback, public BaseObjectMT, public IRdpPktQueueCallback
{
  NI_DECLARE_REFCOUNT_CLASS_2( RdpConnection, IRdpHandshakeCallback, BaseObjectMT );

public:
  RdpConnection( timer::Time _now, const RdpCommonCtx & _ctx, const ConnDescriptor & _descr );
  ~RdpConnection();

  RdpActiveHandshake * ActiveHandshake() { return activeHandshake; }

  void SetupAsActiveSide( IRdpConnection * _iface, IRdpConnectionCallback * _cb, RdpActiveHandshake * _hs );

  void SetupAsReactiveSide1( IRdpConnection * _iface, unsigned _seqIdx );
  void SetupAsReactiveSide2( IRdpConnectionCallback * _cb );

  bool ActiveSide() const { return activeSide; }
  void ChangeLocalMuxUnsafe( unsigned _localMux ) { descr.localMux = _localMux; }

  //IRdpConnection mirror
  EConnStatus::Enum     Status();
  void                  Close();
  void                  SendDatagram( const void * _data, size_t _size, unsigned _options );
  timer::Time           AvgRtt( int * _index );
  void                  FillDebugString( string & _outStr ) const;

  bool Poll( timer::Time _now );

  bool on_pkt_InitAck( unsigned _seqIdx );
  bool on_pkt_Refused( unsigned _seqIdx );
  bool on_pkt_RetryHandshake( unsigned _seqIdx, IRdpLogic * _logic );
  void on_pkt_DatagramRaw( RdpPacket * _packet );
  void on_pkt_Datagram( RdpPacket * _packet );
  void on_pkt_DatagramAck( unsigned _seqIdx, proto::EPktType::Enum _pktType );
  void on_pkt_Ping( unsigned _seqIdx, proto::EPktType::Enum _pktType );

  //IRdpHandshakeCallback
  virtual void OnHandshakeFailed();
  virtual void OnHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx );

  //IRdpConnImplCallback
  virtual const ConnDescriptor & ConnDescr() const { return descr; }
  virtual void ConnCbFailure();
  virtual void ConnCbPacketAcknowledged( timer::Time _rtt );
  virtual void ConnCbPacketRetransmitted();

  //IRdpPktQueueCallback
  virtual timer::Time ConnCbCurrentRetransmitTime() const { return ccLogic.RetransmitTimeout(); }
  virtual unsigned ConnCbCurrentWindowSize() const { return ccLogic.WindowSize(); }
  virtual void QueCbDatagram( RdpPacket * _pkt );
  virtual void QueCbShutdownAcknowledged();
  virtual void QueCbShutdownRecieved();

private:
  struct Notify
  {
    EConnStatus::Enum   status;
    StrongMT<RdpPacket> datagram;
    Notify( EConnStatus::Enum _st, RdpPacket * _dg ) :
    status( _st ), datagram( _dg )
    {}
  };

  typedef std::vector<Notify> NotifyQueue;

  ConnDescriptor                    descr;
  bool                              activeSide;
  threading::Mutex                  mutex;
  RdpCommonCtx                      ctx;
  EConnStatus::Enum                 status;
  NotifyQueue                       incomingNotifyQueue, notifyReadBuffer;
  WeakMT<IRdpConnectionCallback>    callback;
  WeakMT<IRdpConnection>            face;
  timer::Time                       now;
  StrongMT<RdpActiveHandshake>      activeHandshake;
  unsigned                          sequenceIdx;

  RdpOutPktQueue                    outQueue;
  RdpInPktQueue                     inQueue;

  CCLogic                           ccLogic;

  timer::Time                       shutdownTimeWait;

  RdpPing                           ping;

  bool Switch( EConnStatus::Enum _st, bool _notifyChange = true );
  bool PollLocked( timer::Time _now );
  void AddNotify( const Notify & _evt );
};



//Proxy to more clean refcounting interface
class RdpConnectionProxy : public IRdpConnection, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RdpConnectionProxy, IRdpConnection, BaseObjectMT );

public:
  RdpConnectionProxy( RdpConnection * _conn ) :
  conn( _conn )
  {}

  ~RdpConnectionProxy()
  {
    conn->Close();
    conn = 0;
  }

protected:
  virtual EConnStatus::Enum     Status() { return conn->Status(); }
  virtual void                  Close() { conn->Close(); }
  virtual void                  SendDatagram( const void * _data, size_t _size, unsigned _options ) { conn->SendDatagram( _data, _size, _options ); }
  virtual timer::Time           AvgRtt( int * _index ) const { return conn->AvgRtt( _index ); }
  virtual void                  FillDebugString( string & _outStr ) const { conn->FillDebugString( _outStr ); }

private:
  StrongMT<RdpConnection>       conn;
};

} //namespace ni_udp

#endif //RUDP_RDPCONNECTION_H_INCLUDED
