#ifndef RUDP_RDP_H_INCLUDED
#define RUDP_RDP_H_INCLUDED

#include "IRdp.h"
#include "ISockSrv.h"
#include "System/JobThread.h"

namespace ni_udp
{

class RdpLogic;

class Rdp : public IRdp, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Rdp, IRdp, BaseObjectMT );

public:
  Rdp( bool _unitTestMode = false );
  ~Rdp();

  void UnitTestPoll();

  //IRdp
  virtual bool                  Init( IRdpSocketFactory * _socketFactory, const RdpOptions & _opt, ni_rnd::IGenerator * _rnd, timer::ITimer * _clock );
  virtual IRdpConnection *      Connect( const NetAddr & _remote, unsigned _mux, IRdpConnectionCallback * _cb );
  virtual IRdpListenContext *   Listen( unsigned _mux, IRdpListenContextCallback * _cb );

private:
  StrongMT<threading::JobThread>  workerThread;
  StrongMT<RdpLogic>              logic;

  bool                            unitTestMode;
};

} //namespace ni_udp

#endif //RUDP_RDP_H_INCLUDED
