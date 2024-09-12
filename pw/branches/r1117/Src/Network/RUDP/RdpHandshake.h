#ifndef RUDP_RDPHANDSHAKE_H_INCLUDED
#define RUDP_RDPHANDSHAKE_H_INCLUDED

#include "RdpCommon.h"
#include "RdpConnDescriptor.h"
#include "System/EnumToString.h"
#include <list>

namespace ni_udp
{

class RdpListenContext;
class RdpConnection;
class RdpWriter;


//TODO: 4-way handshake (SCTP-alike)
namespace EHandshakeStage
{
  enum Enum
  {
    None,

    Active_Start,
    Active_WaitingInitAck,
    Active_Completed,

    Reactive_Start,
    Reactive_WaitingAck,

    Failed,
    Finished
  };

  NI_ENUM_DECL_STD;
};



class IRdpHandshakeCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpHandshakeCallback, IBaseInterfaceMT );
public:
  virtual void OnHandshakeFailed() = 0;
  virtual void OnHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx ) = 0;
};



class RdpHandshakeBase : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpHandshakeBase, BaseObjectMT );

public:
  RdpHandshakeBase( const RdpCommonCtx & _ctx, const ConnDescriptor & _descr, IRdpHandshakeCallback * _cb, EHandshakeStage::Enum _initial, unsigned _seqIndex, timer::Time _now );

  bool Finished() const { return ( stage == EHandshakeStage::Finished ) || ( stage == EHandshakeStage::Failed ); }

protected:
  ConnDescriptor              descr;
  const timer::Time           totalTimeoutEnds;
  RdpCommonCtx                ctx;
  WeakMT<IRdpHandshakeCallback> callback;
  timer::Time                 now;
  unsigned                    sequenceIdx;
  timer::Time                 retryTemeout;
  unsigned                    retryIndex;

  EHandshakeStage::Enum Stage() const { return stage; }
  void SwitchStage( EHandshakeStage::Enum _new );

private:
  EHandshakeStage::Enum       stage;
  //std::list<EHandshakeStage::Enum> newStages;
};



class RdpActiveHandshake : public RdpHandshakeBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpActiveHandshake, RdpHandshakeBase );

public:
  RdpActiveHandshake( const RdpCommonCtx & _ctx, const ConnDescriptor & _descr, IRdpHandshakeCallback * _cb, unsigned _seqIndex, timer::Time _now ) :
  RdpHandshakeBase( _ctx, _descr, _cb, EHandshakeStage::Active_Start, _seqIndex, _now )
  {}

  bool Poll( timer::Time _now );

  void OnRefused( unsigned _seqIdx );
  void OnRetry( unsigned _seqIdx, IRdpLogic * _logic );
  void OnInitAck( unsigned _seqIdx );
  void OnAnyDatagram( unsigned _seqIdx );

private:
  bool Retry();
};



class RdpReactiveHandshake : public RdpHandshakeBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpReactiveHandshake, RdpHandshakeBase );

public:
  RdpReactiveHandshake( const RdpCommonCtx & _ctx, const ConnDescriptor & _descr, IRdpHandshakeCallback * _cb, unsigned _seqIndex, timer::Time _now ) :
  RdpHandshakeBase( _ctx, _descr, _cb, EHandshakeStage::Reactive_Start, _seqIndex, _now ),
  completeTime( 0 )
  {}

  bool Poll( timer::Time _now );

  void OnInit( unsigned _seqIdx );
  void OnAck( unsigned _seqIdx );

  timer::Time CompleteTime() const { return completeTime; }

private:
  timer::Time             completeTime;
};

} //namespace ni_udp

#endif //RUDP_RDPHANDSHAKE_H_INCLUDED
