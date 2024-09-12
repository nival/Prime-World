#ifndef RUDP_RDPPROTO_H_INCLUDED
#define RUDP_RDPPROTO_H_INCLUDED

#include "System/EnumToString.h"

namespace ni_udp
{

namespace proto
{

typedef unsigned char Byte;
typedef int Int32;
typedef long long Int64;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;

//static const Int32 VERSION = 1;


namespace EPktType
{
  enum Enum
  {
    HandshakeInit         = 0,
    HandshakeInitAck      = 1,
    HandshakeAck          = 2,
    HandshakeRefused      = 3,
    RetryHandshake        = 4,
    Datagram              = 5,
    DatagramChunk         = 6,
    DatagramAck           = 7,
    DatagramRaw           = 8,
    Shutdown              = 9,
    ShutdownAck           = 10,
    Ping                  = 11,
    Pong                  = 12
  };

  NI_ENUM_DECL_STD;
}

static UInt32 Version = 1;
static Int32 SeqIndexClamp = 32768; //1024 is just for debugging

inline Int32 ClampSeqIndex( Int32 _idx ) { return _idx % SeqIndexClamp; }
inline Int32 NextSeqIndex( Int32 _idx ) { return ClampSeqIndex( _idx + 1 ); }

Int32 SeqIdxOffsetInWindow( Int32 _wndStart, Int32 _wndSize, Int32 _idx, Int32 _seqIdxClamp );

Int32 SeqIdxShortestDist( Int32 _from, Int32 _to, Int32 _seqIdxClamp ); // to - from


#pragma pack(push, 1)

struct Header
{
  UInt32    type:8;
  UInt32    index:16;
  UInt32    sourceMux:16;
  UInt32    destMux:16;

  Header( EPktType::Enum _type, UInt32 _srcMux, UInt32 _destMux, UInt32 _index ) :
  type( (UInt32)_type ),
  index( _index ),
  sourceMux( _srcMux ),
  destMux( _destMux )
  {}
};

#pragma pack(pop)

} // namespace proto

inline const char * PktTypeToString( proto::EPktType::Enum _t ) { return proto::EPktType::ToString( _t ); }
inline const char * PktTypeToString( int _t ) { return proto::EPktType::ToString( (proto::EPktType::Enum)_t ); }

} //namespace ni_udp

#endif //RUDP_RDPPROTO_H_INCLUDED
