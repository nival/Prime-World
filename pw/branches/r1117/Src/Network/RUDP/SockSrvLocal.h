#ifndef RUDP_SOCKSRVLOCAL_H_INCLUDED
#define RUDP_SOCKSRVLOCAL_H_INCLUDED

#include "ISockSrv.h"
#include "System/RandomGenerator.h"
#include <vector>
#include <map>
#include <list>


namespace timer
{
  class ITimer;
}


namespace ni_udp
{

class LocalDatagram : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( LocalDatagram, BaseObjectMT );
public:
  typedef std::vector<ni_detail::Byte>  Data;

  LocalDatagram( const void * _data, size_t _size, const NetAddr & _srcAddr ) :
  data( (const ni_detail::Byte *)_data, (const ni_detail::Byte *)_data + _size ),
  deliveryTime( 0 ),
  srcAddr( _srcAddr )
  {}

  const void * Bytes() const { return data.empty() ? 0 : &data[0]; }
  size_t Size() const { return data.size(); }
  const NetAddr & SrcAddr() const { return srcAddr; }
  timer::Time DeliveryTime() const { return deliveryTime; }
  void SetDeliveryTime( timer::Time _t ) { deliveryTime = _t; }

private:
  const Data      data;
  timer::Time     deliveryTime;
  const NetAddr   srcAddr;
};



class LocalSocket;

class LocalSocketServer : public ISocketServer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalSocketServer, ISocketServer, BaseObjectMT );

public:
  explicit LocalSocketServer( timer::ITimer * _clock, bool _verbose = false );

  //ISocket
  virtual StrongMT<ISocket> Open( ISocketCallback * _cb, const NetAddr & _bindAddr, TAuxData _auxData );

  void Poll();
  void Post( const NetAddr & _destAddr, LocalDatagram * _dg );
  void SetDefaultDelay( timer::Time _delay ) { defaultDelay = _delay; }
  void AddIncomingLossPattern( const char * _pattern ); //e.g. "111000110"
  void AddPacketDelay( int _pktIdx, timer::Time _addDelay );
  void SetRandomPacketLoss( float _percent );
  bool Verbose() const { return verbose; }

private:
  typedef std::map<NetAddr, WeakMT<LocalSocket>>  Sockets;
  typedef std::list<std::pair<int, timer::Time>> DelayPattern;
  typedef std::list<std::pair<NetAddr, StrongMT<LocalDatagram>>>  DatagramBuffer;

  const bool          verbose;
  timer::Time         defaultDelay;
  StrongMT<timer::ITimer> clock;
  Sockets             sockets;
  DatagramBuffer      incomingBuffer;
  threading::Mutex    incomingMutex;
  threading::Mutex    mainMutex;
  std::list<int>      lossPatern;
  DelayPattern        delayPattern;
  NRandom::RandomGenerator random;
  int                 packetLossProbability; //100% is 10000

  bool DistortDatagram( timer::Time & _delay );
};



class LocalSocket : public ISocket, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalSocket, ISocket, BaseObjectMT );

public:
  LocalSocket( timer::ITimer * _clock, LocalSocketServer * _sv, const NetAddr & _bindAddr, ISocketCallback * _cb, TAuxData _auxData, bool _verbose );
  ~LocalSocket();

  //ISocket
  virtual ESocketStatus::Enum   Status();
  virtual TAuxData              AuxData() const { return auxData; }
  virtual const NetAddr &       LocalAddr() const { return bindAddr; }
  virtual void                  Close();
  virtual void                  SendDatagram( const NetAddr & _destAddr, const void * _data, size_t size );

  bool Poll();
  void Post( LocalDatagram * _dg );

private:
  typedef std::list<StrongMT<LocalDatagram>> PostQueue;

  const bool                    verbose;
  const NetAddr                 bindAddr;
  const TAuxData                auxData;
  StrongMT<timer::ITimer>       clock;
  bool                          opened;
  WeakMT<LocalSocketServer>     server;
  WeakMT<ISocketCallback>       callback;
  PostQueue                     queue;
  threading::Mutex              mutex;

  timer::Time                   lastStatReport;
  unsigned                      statSamplesCount;
  unsigned                      queLenSum;
  unsigned                      maxQueLen;
  unsigned                      totalPackets;

  void StatReport();
};

} //namespace ni_udp

#endif //RUDP_SOCKSRVLOCAL_H_INCLUDED
