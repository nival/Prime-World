#include "stdafx.h"
#include "RdpListenContext.h"
#include "RdpConnection.h"
#include "RdpProto.h"
#include "RdpCommon.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( ni_udp::RdpListenContext );

namespace ni_udp
{

RdpListenContext::RdpListenContext( IRdpLogic * _logic, const RdpCommonCtx & _ctx, unsigned _mux, IRdpListenContextCallback * _cb ) :
mux( _mux ),
ctx( _ctx ),
now( _logic->Now() ),
callback( _cb ),
logic( _logic )
{
}



void RdpListenContext::Close()
{
  StrongMT<IRdpLogic> lockedLogic = logic.Lock();
  NI_VERIFY( lockedLogic, "", return );

  lockedLogic->StopListen( this );

  logic = 0;
}



bool RdpListenContext::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  now = _now;

  for ( Handshakes::iterator it = handshakes.begin(); it != handshakes.end(); )
  {
    StrongMT<RdpReactiveHandshake> & hs = it->second;

    if ( hs->Poll( now ) )
      ++it;
    else
      it = handshakes.erase( it );
  }

  if ( !callback.Lock().Valid() )
  {
    WarningTrace( "Null listen context callback. mux=%d", mux );
    return false;
  }

  return true;
}



void RdpListenContext::on_pkt_HandshakeInit( const ConnDescriptor & _descr, unsigned _seqIdx )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  StrongMT<RdpReactiveHandshake> & hs = handshakes[_descr];

  if ( hs.Valid() )
  {
    //Ok, re-sended Init
    hs->OnInit( _seqIdx );
    return;
  }

  hs = new RdpReactiveHandshake( ctx, _descr, this, /*proto::NextSeqIndex( _seqIdx )*/_seqIdx, now );
}



void RdpListenContext::on_pkt_HandshakeAck( const ConnDescriptor & _descr, unsigned _seqIdx )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  Handshakes::const_iterator it = handshakes.find( _descr );
  if ( it != handshakes.end() )
  {
    it->second->OnAck( _seqIdx );
    return;
  }
  else
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Unknown handshake connection descriptor. descr=%s, seq=%d", _descr, _seqIdx );
}



void RdpListenContext::OnHandshakeFailed()
{
  //do nothing
}



void RdpListenContext::OnHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx )
{
  //WARNING: no lock

  StrongMT<IRdpLogic> lockedLogic = logic.Lock();
  NI_VERIFY( lockedLogic, "", return );

  StrongMT<IRdpListenContextCallback> lockedCb = callback.Lock();
  if ( !lockedCb )
  {
    ErrorTrace( "Null listen context callback. descr=%s", _descr );
    return;
  }

  lockedLogic->IncomingHandshakeCompleted( _descr, _seqIdx, lockedCb );
}

} //namespace ni_udp
