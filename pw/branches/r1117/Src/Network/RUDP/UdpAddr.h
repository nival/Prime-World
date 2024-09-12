#ifndef RUDP_UDPADDR_H_INCLUDED
#define RUDP_UDPADDR_H_INCLUDED

#include <winsock2.h>
#include <ws2tcpip.h>

namespace ni_udp
{

typedef unsigned IpAddr;


struct NetAddr : public sockaddr_in
{
  NetAddr();
  NetAddr( const char * _addr, unsigned _port );
  NetAddr( const sockaddr_in & _addrin ) : sockaddr_in( _addrin ) {}
  NetAddr( const char * _combined );

  bool Set( const char * _addr, unsigned _port ); // pass _addr=0 for INADDR_ANY
  bool Set( const char * _combined );
  void SetPort( unsigned _port );
  
  bool operator < ( const NetAddr & that ) const;
  bool operator == ( const NetAddr & that ) const;

  IpAddr Address() const { return sin_addr.s_addr; }
  unsigned Port() const;
  void Clear();

  void Str( char * _buf, size_t _bufSz ) const;
  void StrIp( char * _buf, size_t _bufSz ) const;
};

} //namespace ni_udp



//Log formatting stuff
namespace text
{

template<>
class TArg<ni_udp::NetAddr> : public BasicArg
{
public:
  TArg( const ni_udp::NetAddr & _a ) : addr( _a ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    char buf[32];
    addr.Str( buf, 32 );

    FormatString( buffer, buf, specs );
  }

  virtual bool AsInt( int & _intValue ) const { return false; }

private:
  const ni_udp::NetAddr & addr;
};

} //namespace text

#endif //RUDP_UDPADDR_H_INCLUDED
