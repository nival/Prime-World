#ifndef TRANSPORTUTILS_H_03E1BB5B_DCD5_4
#define TRANSPORTUTILS_H_03E1BB5B_DCD5_4

#include "TransportAddress.h"
#include "../System/IDGenerator.h"

namespace Transport
{
  const TClientId firstAutoAssignId = -1024;

  const bool compressRelayTraffic = false;

  class MessageFactory;
  struct MessageBase;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  typedef unsigned short TPipeId;

  namespace EKnownPipeId
  {
    const TPipeId Invalid = 0;  // non assigned pipe id
    const TPipeId NetLogic = 1; // transport system internal pipe 
    const TPipeId Client = 2;   // client-to-client pipe, makes use of sender field in ChannelAddr    
    const TPipeId FrontEnd = 3;   // client-to-client pipe, makes use of sender field in ChannelAddr    
    const TPipeId FirstCustomPipeId = 4;
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct _ChannelAddr
  {
    ZDATA
    TPipeId pipe;
    TClientId client;
    TClientId sender;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&pipe); f.Add(3,&client); f.Add(4,&sender); return 0; }

    _ChannelAddr() : pipe( EKnownPipeId::Invalid ), client( autoAssignClientId ), sender( autoAssignClientId ) {}
    _ChannelAddr( TPipeId _pipe, TClientId _client ) : pipe( _pipe ), client( _client ), sender( autoAssignClientId ) {}
    _ChannelAddr( TPipeId _pipe, TClientId _client, TClientId _sender ) : pipe( _pipe ), client( _client ), sender( _sender ) {}
    _ChannelAddr( TPipeId _pipe, TClientId _client, TClientId _sender, uint /*dummy*/ ) 
      : pipe( _pipe ), client( _client ), sender( _sender ) {}

    int Serialize(Stream* pS) const;
    int Deserialize(Stream* pS);
    int ConsistensyCheck(unsigned int /*seqNum*/) const { return 0;};
    unsigned int SeqNum() const { return 0; }
    void SeqNum(unsigned int sn) { return; }
    size_t GetSeqNumSize() const { return 0; }
  };

  struct ChannelHeader : public _ChannelAddr
  {
    uint seqnum;
    int operator&( IBinSaver &f ) 
    {
      int rc = this->_ChannelAddr::operator & (f);
      f.Add(5, &seqnum); 
      return rc;
    }

    ChannelHeader() : seqnum(0) {}
    ChannelHeader( TPipeId _pipe, TClientId _client ) : _ChannelAddr(_pipe, _client), seqnum(0) {}
    ChannelHeader( TPipeId _pipe, TClientId _client, TClientId _sender ) : _ChannelAddr(_pipe, _client, _sender), seqnum(0) {}
    ChannelHeader( TPipeId _pipe, TClientId _client, TClientId _sender, uint _seqnum ) 
      : _ChannelAddr(_pipe, _client, _sender), seqnum(_seqnum) {}

    int Serialize(Stream* pS) const;
    int Deserialize(Stream* pS);
    int ConsistensyCheck(unsigned int prevSeqNum) const;
    unsigned int SeqNum() const { return seqnum; }
    void SeqNum(unsigned int sn)
    {
      seqnum = sn;
    }

    size_t GetSeqNumSize() const
    {
#if defined( NV_WIN_PLATFORM )
      return sizeof(seqnum);
#elif defined( NV_LINUX_PLATFORM )
      return sizeof( nival::uint32_t );
#endif
    }
  };

#undef TRANSPORT_SEQ_PACKET_CHECK
#define TRANSPORT_SEQ_PACKET_CHECK

#ifdef TRANSPORT_SEQ_PACKET_CHECK
  #define ChannelAddr ChannelHeader
#else
  #define ChannelAddr _ChannelAddr
#endif
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct MessageHeader : public Transport::ChannelAddr
  {
    int msgType_;

    MessageHeader(ChannelAddr const & addr, int msgtype)
      :ChannelAddr(addr),
      msgType_(msgtype)
    {
    }
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  inline bool operator==( const ChannelAddr& a, const ChannelAddr& b )
  {
    return a.pipe == b.pipe && a.client == b.client && a.sender == b.sender;
  }
  inline bool operator!=( const ChannelAddr& a, const ChannelAddr& b )
  {
    return !( a == b );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct ChannelAddrIsLess 
  { 
    inline bool operator()( const ChannelAddr& a, const ChannelAddr& b ) const 
    { 
      if ( a.pipe < b.pipe )
        return true;
      if ( a.pipe > b.pipe ) 
        return false;
      if ( a.client < b.client )
        return true;
      if ( a.client > b.client ) 
        return false;
      return a.sender < b.sender;
    };
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct ChannelAddrHash
  { 
    inline unsigned int operator()( const ChannelAddr& a ) const
    {
      return a.client ^ a.sender ^ ( a.pipe << 24 );
    }
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class ClientIdGenerator : public IDGenerator
  {
  public:
    ClientIdGenerator() : IDGenerator( EKnownPipeId::FirstCustomPipeId, 65535 ) {}
    int GeneratePipeForInterface( TServiceId intf );
  };
  typedef ClientIdGenerator PipeIdGenerator;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Stream* PackNetMessage(const ChannelAddr& addr, MessageBase* pMsg, Stream* pS );
  void UnpackNetMessage( Stream* pS, MessageFactory* factory, ChannelAddr& address, MessageBase** ppMsg );

  namespace UnpackResult
  {
    enum Enum
    {
      UNKNOWN_MSG_TYPE = -4,
      INVALID_FIELD_SIZE = -3,
      TOO_BIG_SIZE = -2,
      FAIL = -1,
      OK = 0,
    };
  }
  UnpackResult::Enum UnpackMessage(int msgType, MessageFactory* factory, Stream* pS, uint msgSizeLimit, MessageBase*& _pMsg);

  unsigned int GetMessageSize(MessageBase* pMsg);
  unsigned int GetNetMessageSize(ChannelAddr const & address, MessageBase* pMsg);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ReadAddress( Stream* pS, ChannelAddr& address);
  bool ReadMessageType(Stream* pS, int & msgtype);
  void WriteAddress( Stream* pS, const ChannelAddr& address);
  int GetAddressSize( const ChannelAddr& address );
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class CalcSizeStream : public Stream, public CObjectBase
  {
    OBJECT_METHODS( 0x49845B00, CalcSizeStream );

    char const * pBuffer;
    int offset;
    int realSize;
    int bufferSize;

  public:
    CalcSizeStream(); //  for write size
    CalcSizeStream(char const * _buf, int _size);  //  for read size

  protected:
    void SeekInternal( const int offset );
    void SetSizeInternal( const int size );

    int ReadInternal( void *pData, const int length );
    int WriteInternal( const void *pData, const int length );

    const char *GetBuffer() const { return 0; }
    void Close() {}

  public:

    int GetSize() const { return realSize; }
    int GetPosition() const { return offset; }
  };

}
#endif //#define TRANSPORTUTILS_H_03E1BB5B_DCD5_4
