#ifndef UDPTESTCLIENT_H_INCLUDED
#define UDPTESTCLIENT_H_INCLUDED

#include "UdpTest.h"


class UdpTestClient : public UdpTestBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( UdpTestClient, UdpTestBase );
public:
  UdpTestClient( const char * _bindAddr, const char * _targetAddr, unsigned _pingRate, unsigned _pingSize, timer::Time _timeout, timer::Time _dumpPeriod, int _bufferSize );
  ~UdpTestClient();

  void Poll();
  void Finish();

private:
  struct Ping : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( Ping, BaseObjectST );

    Ping() :
    index( 0 ),
    time( 0 )
    {}

    int           index;
    timer::Time   time;
  };

  typedef std::map<int, Strong<Ping> > ActivePings;
  typedef std::list<Strong<Ping> > PingsHist;

  const ni_udp::NetAddr target;
  const int     rate, pingSize;
  const timer::Time timeout;
  timer::Time   nextPing;
  int           nextPingIndex;
  std::vector<ni_detail::Byte> buffer;

  threading::Mutex  mutex;
  ActivePings       pings;
  PingsHist         hist;
  timer::Time       nextTimeoutsPoll;
  timer::Time       nextDump;
  timer::Time       dumpPeriod;
  int               lostPings, okPings;
  CustomHistogram   dumpHisto;
  FILE *            csvFile;
  timer::Time       nextCpuMeasure;
  PDH_HQUERY        cpuQuery;
  PDH_HCOUNTER      cpuTotal;
  double            cpuLoadSum;
  int               cpuLoadCounter;


  virtual void  OnDatagram( ni_udp::ISocket * _socket, const ni_udp::NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime );
  void PollTimeouts( timer::Time _now );
  void PollDump( timer::Time _now );
  void PollCpuUsage( timer::Time _now );
};

#endif //UDPTESTCLIENT_H_INCLUDED
