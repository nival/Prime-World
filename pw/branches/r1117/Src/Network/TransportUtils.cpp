#include "stdafx.h"
#include "TransportUtils.h"
#include "System/ChunklessSaver.h"
#include "System/AddressOf.h"
#include "System/StreamUtils.h"
#include "Message.h"
#include <limits>

#ifdef max
#undef max
#endif

namespace Transport
{
  int _ChannelAddr::Serialize(Stream* pS) const
  {
    // pS->Write( (const void*)&(this->pipe), sizeof( TPipeId ) );
    ( void ) nival::WriteUInt16( pS, this -> pipe );
    // pS->Write( (const void*)&(this->client), sizeof( TClientId ) );
    ( void ) nival::WriteInt32( pS, this -> client );
    // pS->Write( (const void*)&(this->sender), sizeof( TClientId ) );
    ( void ) nival::WriteInt32( pS, this -> sender );
    return 0;
  }

  int _ChannelAddr::Deserialize(Stream* pS)
  {
    // pS->Read( (void*)&(this->pipe), sizeof( TPipeId ) );
    ( void ) nival::ReadUInt16( pS, this -> pipe );
    // pS->Read( (void*)&(this->client), sizeof( TClientId ) );
    ( void ) nival::ReadInt32( pS, this -> client );
    // pS->Read( (void*)&(this->sender), sizeof( TClientId ) );
    ( void ) nival::ReadInt32( pS, this -> sender );
    return 0;
  }

  int ChannelHeader::Serialize(Stream* pS) const
  {
    _ChannelAddr::Serialize(pS);
    // pS->Write((const void*)&this->seqnum, sizeof(this->seqnum));
    ( void ) nival::WriteUInt32( pS, this -> seqnum );
    return 0;
  }

  int ChannelHeader::Deserialize(Stream* pS)
  {
    _ChannelAddr::Deserialize(pS);
    // pS->Read((void*)&(this->seqnum), sizeof(this->seqnum));
    ( void ) nival::ReadUInt32( pS, this -> seqnum );
    return 0;
  }

  int ChannelHeader::ConsistensyCheck(unsigned int prevSeqNum) const
  {
    int rc = -1;
    if (prevSeqNum + 1 == this->seqnum)
      rc = 0;

    return rc;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void UnpackNetMessage( Stream* pS, MessageFactory* factory, ChannelAddr& address, MessageBase** ppMsg )
  {
    int msgType;
    ReadAddress( pS, address );
    // pS->Read( (void*)&msgType, sizeof( int ) );
    ( void ) nival::ReadInt32( pS, msgType );

    MessageBase* pMsg = factory->Create( msgType );
    if ( !pMsg )
      return;

    {
      ChunklessSaver saver( pS, 0, true );
      (*pMsg) & saver;
    }

    *ppMsg = pMsg;
  }

  bool ReadMessageType(Stream* pS, int & msgtype)
  {
    return nival::ReadInt32( pS, msgtype );
  }

  UnpackResult::Enum UnpackMessage(int msgType, MessageFactory* factory, Stream* pS, uint msgSizeLimit, MessageBase*& _pMsg)
  {
    UnpackResult::Enum rc = UnpackResult::FAIL;
    MessageBase* pMsg = factory->Create( msgType );
    if (pMsg)
    {
      CalcSizeStream css(pS->GetBuffer() + pS->GetPosition(), pS->GetSize() - pS->GetPosition());
      ChunklessSaver sizechecker(nival::getaddressof( css ), 0, true, msgSizeLimit);
      (*pMsg) & sizechecker;

      if (IBinSaver::BINSAVER_ERR_OK == sizechecker.GetError() && 
          css.GetPosition() <= (int)msgSizeLimit)
      {
        ChunklessSaver saver(pS, 0, true, msgSizeLimit);
        (*pMsg) & saver;
        if (IBinSaver::BINSAVER_ERR_OK == saver.GetError())
          rc = UnpackResult::OK;
        else
          rc = UnpackResult::INVALID_FIELD_SIZE;
      }
      else
      {
        if (sizechecker.GetError() != IBinSaver::BINSAVER_ERR_OK)
          rc = UnpackResult::INVALID_FIELD_SIZE;
        else
          rc = UnpackResult::TOO_BIG_SIZE;
      }

      if (UnpackResult::OK == rc)
        _pMsg = pMsg;
      else
        factory->Destroy(pMsg);
    }
    else
    {
      rc = UnpackResult::UNKNOWN_MSG_TYPE;
    }

    return rc;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Stream* PackNetMessage( const ChannelAddr& addr, MessageBase* pMsg, Stream* pS )
  {
    NI_VERIFY( pS, "Stream must be set!", pS = new MemoryStream() );

    ChannelAddr address = addr;
    int msgType = pMsg->GetTypeId();
    WriteAddress( pS, address );
    // pS->Write( (void*)&msgType, sizeof( int ) );
    ( void ) nival::WriteInt32( pS, msgType );

    {
      ChunklessSaver saver( pS, 0, false );
      (*pMsg) & saver;
    }
    return pS;
  }

  unsigned int GetMessageSize(MessageBase* pMsg)
  {
    CalcSizeStream s;
    int msgtype = pMsg->GetTypeId();
    // s.Write(&msgtype, sizeof(msgtype));
    ( void ) nival::WriteInt32( nival::getaddressof( s ), msgtype );
    ChunklessSaver saver( nival::getaddressof( s ), 0, false );
    (*pMsg) & saver;
    return s.GetPosition();
  }

  unsigned int GetNetMessageSize(ChannelAddr const & address, MessageBase* pMsg)
  {
    return GetAddressSize(address) + GetMessageSize(pMsg);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ReadAddress( Stream* pS, ChannelAddr& address )
  {
    address.Deserialize(pS);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void WriteAddress( Stream* pS, const ChannelAddr& address )
  {
    address.Serialize(pS);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int GetAddressSize( ChannelAddr const & address )
  {
#if defined( NV_WIN_PLATFORM )
    int sz = sizeof( address.pipe );
    sz += sizeof( address.client );
    sz += sizeof( address.sender );
    sz += address.GetSeqNumSize();
#elif defined( NV_LINUX_PLATFORM )
    int sz = sizeof( nival::uint16_t );
    sz += sizeof( nival::int32_t );
    sz += sizeof( nival::int32_t );
    sz += address.GetSeqNumSize();
#endif
    return sz;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int ClientIdGenerator::GeneratePipeForInterface( TServiceId intf )
  {
    if ( intf == ENetInterface::Client )
      return EKnownPipeId::Client;
    else if ( intf == ENetInterface::FrontEnd )
      return EKnownPipeId::FrontEnd;

    if( !HasFreeID() )
      return EKnownPipeId::Invalid;

    return Generate();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool IsServiceOfClass(const TServiceId& service, const TServiceId& serviceClass)
  {
    return (strncmp(service.c_str(), serviceClass.c_str(), serviceClass.size()) == 0);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CalcSizeStream::CalcSizeStream()
    :pBuffer(0),
    offset(0),
    realSize(0),
    bufferSize(0)
  {
    SetCanSeek( true );
    SetCanWrite( true );
    SetCanRead( true );
    SetBroken( false );
  }

  CalcSizeStream::CalcSizeStream(char const * _buf, int _size)
    :pBuffer(_buf),
    offset(0),
    realSize(_size),
    bufferSize(_size)
  {
    SetCanSeek( true );
    SetCanWrite( true );
    SetCanRead( true );
    SetBroken( false );
  }

  void CalcSizeStream::SeekInternal( const int _offset )
  {
    offset = _offset;
  }

  void CalcSizeStream::SetSizeInternal( const int size )
  {
    realSize = size;
  }

  int CalcSizeStream::ReadInternal( void *pData, const int length )
  {
    NI_ASSERT(pBuffer, "Buffer must not be 0!");
    if (length <= sizeof(int) && pBuffer)  //  it can be size of field
      memcpy(pData, pBuffer + offset, length);

    //  check for int overflow
    long long sumCheck = (long long)offset + (long long)length;
    if (sumCheck < 0 || sumCheck > std::numeric_limits<int>::max())
      return -1;

    offset += length;
    return length;
  }

  int CalcSizeStream::WriteInternal( const void *pData, const int length )
  {
    pData;

    //  check for int overflow
    long long sumCheck = (long long)offset + (long long)length;
    if (sumCheck < 0 || sumCheck > std::numeric_limits<int>::max())
      return -1;

    offset += length;
    return length;
  }
}
