#ifndef RUDP_RDPLISTENCONTEXT_H_INCLUDED
#define RUDP_RDPLISTENCONTEXT_H_INCLUDED

#include "RdpCommon.h"
#include "RdpHandshake.h"
#include <map>
#include <list>


namespace ni_udp
{

class IRdpLogic;


struct RdpCompletedReactiveHandshake
{
  ConnDescriptor                      descr;
  unsigned                            sequenceIdx;
  WeakMT<IRdpListenContextCallback>   callback;

  RdpCompletedReactiveHandshake( const ConnDescriptor & _descr, unsigned _seqIdx, WeakMT<IRdpListenContextCallback> & _cb ) :
  descr( _descr ),
  sequenceIdx( _seqIdx ),
  callback( _cb )
  {}
};



class RdpListenContext : public IRdpHandshakeCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RdpListenContext, IRdpHandshakeCallback, BaseObjectMT );

public:
  RdpListenContext( IRdpLogic * _logic, const RdpCommonCtx & _ctx, unsigned _mux, IRdpListenContextCallback * _cb );

  unsigned Mux() const { return mux; }

  void Close();

  bool Poll( timer::Time _now );

  void on_pkt_HandshakeInit( const ConnDescriptor & _descr, unsigned _seqIdx );
  void on_pkt_HandshakeAck( const ConnDescriptor & _descr, unsigned _seqIdx );

private:
  typedef std::map<ConnDescriptor, StrongMT<RdpReactiveHandshake>>  Handshakes;
  typedef std::list<StrongMT<RdpReactiveHandshake>>  HandshakesList;

  const unsigned                    mux;
  threading::Mutex                  mutex;
  RdpCommonCtx                      ctx;
  timer::Time                       now;
  WeakMT<IRdpListenContextCallback> callback;
  WeakMT<IRdpLogic>                 logic;
  Handshakes                        handshakes;

  //IRdpHandshakeCallback
  virtual void OnHandshakeFailed();
  virtual void OnHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx );
};



class RdpListenContextProxy : public IRdpListenContext, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RdpListenContextProxy, IRdpListenContext, BaseObjectMT );

public:
  RdpListenContextProxy( RdpListenContext * _ctx ) :
  ctx( _ctx )
  {}

  ~RdpListenContextProxy()
  {
    ctx->Close();
  }

protected:
  virtual void                  Close() { ctx->Close(); }

private:
  StrongMT<RdpListenContext>    ctx;
};

} //namespace ni_udp

#endif //RUDP_RDPLISTENCONTEXT_H_INCLUDED
