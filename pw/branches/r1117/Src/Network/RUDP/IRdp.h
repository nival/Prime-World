#ifndef RUDP_IRDP_H_INCLUDED
#define RUDP_IRDP_H_INCLUDED

#include "ISockSrv.h"

namespace ni_rnd
{
  class IGenerator;
}


namespace timer
{
  class ITimer;
}


namespace ni_udp
{


struct RdpCcOptions
{
  unsigned    historyLen;
  unsigned    initWindowSize, maxWindowSize;
  unsigned    windowSizeInc, windowSizeDec;
  float       initRetransmitTime, maxRetransmitTime;
  float       rttoAdditiveMargin, rttoMultiplicativeMargin;
  float       rttoFactor;

  RdpCcOptions();
};



struct RdpOptions
{
  unsigned      firstEphemeralMux;
  unsigned      lastEphemeralMux;
  float         handshakeTotalTimeout;
  float         handshakeRetryTimeout;
  unsigned      handshakeMaxTries;
  float         shutdownTimeWait;
  RdpCcOptions  cc;
  unsigned      initInPacketsQueue;
  unsigned      initOutPacketsQueue;
  unsigned      maxInQueuePackets;
  unsigned      maxInQueueSize;
  unsigned      maxOutQueueSize;
  unsigned      maxOutQueuePackets;
  unsigned      maxDataSegment;
  unsigned      retransmitLimit;
  float         pingPeriod;
  unsigned      logEvents;
  unsigned      incomingBufferPreallocate;
  unsigned      incomingBufferHardlimit;
  unsigned      outgoingBufferPreallocate;
  unsigned      outgoingBufferHardlimit;
  bool          usePoolAllocator;
  int           logicThreadPriority;

  enum ELogEvents
  {
    LogMajorEvents        = 1,
    LogHandshake          = 2,
    LogShutdown           = 4,
    LogPackets            = 8,
    LogDetails            = 16,
    LogCc                 = 32,
    LogWarnings           = 1024,
    LogErrors             = 2048,
    LogAllEvents          =  LogMajorEvents | LogHandshake | LogShutdown | LogPackets | LogDetails | LogCc | LogWarnings | LogErrors
  };

  RdpOptions();
};


namespace EDatagramOpt
{
  enum Enum
  {
    Raw           = 1, //Unreliable and no ordering,
  };
}



namespace EConnStatus
{
  enum Enum { None, Pending, Ready, Closed, Failed };
}



class IRdpConnection : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpConnection, IBaseInterfaceMT );

public:
  virtual EConnStatus::Enum     Status() = 0;
  virtual void                  Close() = 0;
  virtual void                  SendDatagram( const void * _data, size_t _size, unsigned _options = 0 ) = 0;
  virtual timer::Time           AvgRtt( int * _index = 0 ) const = 0;
  virtual void                  FillDebugString( string & _outStr ) const = 0;
};




class IRdpConnectionCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpConnectionCallback, IBaseInterfaceMT );

public:
  virtual void    OnConnectionEstablished( IRdpConnection * _conn ) = 0;
  virtual void    OnConnectionClosed( IRdpConnection * _conn ) = 0; //i.e. gracefully
  virtual void    OnConnectionFailed( IRdpConnection * _conn ) = 0; //handshake failed, or disconnect
  virtual void    OnDatagram( IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime ) = 0;
};




class IRdpListenContext : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpListenContext, IBaseInterfaceMT );

public:
  virtual void                  Close() = 0;
};



class IRdpListenContextCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpListenContextCallback, IBaseInterfaceMT );

public:
  virtual IRdpConnectionCallback * OnConnectionEstablished( IRdpConnection * _conn, const NetAddr & _remoteAddr ) = 0;
};



class IRdpSocketFactory : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpSocketFactory, IBaseInterfaceMT );

public:
  virtual StrongMT<ISocket>     OpenSocket( ISocketCallback * _cb ) = 0;
};




class IRdp : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdp, IBaseInterfaceMT );

public:
  virtual bool                  Init( IRdpSocketFactory * _socketFactory, const RdpOptions & _opt, ni_rnd::IGenerator * _rnd, timer::ITimer * _timer ) = 0;
  virtual IRdpConnection *      Connect( const NetAddr & _remote, unsigned _mux, IRdpConnectionCallback * _cb ) = 0;
  virtual IRdpListenContext *   Listen( unsigned _mux, IRdpListenContextCallback * _cb ) = 0;
};

IRdp * NewRdpInstance();

} //namespace ni_udp

#endif //RUDP_IRDP_H_INCLUDED
