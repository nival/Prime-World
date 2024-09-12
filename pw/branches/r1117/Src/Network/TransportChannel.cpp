#include "stdafx.h"
#include "TransportChannel.h"
#include "Message.h"

namespace Transport
{
bool bTraceRecv = false;
bool bTraceSend = false;
REGISTER_VAR( "trans_trace_recv", bTraceRecv, STORAGE_NONE );
REGISTER_VAR( "trans_trace_send", bTraceSend, STORAGE_NONE );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Channel::Channel(  bool _isIncoming, const Address& _address, const TLoginData& _loginData, MessageFactory* _pMessageFactory, Network::IStreamAllocator* _pAlloc, bool _clientAddress ) 
: address( _address )
, loginData(_loginData)
, status( Network::ConnectionState::Connecting )
, pMessageFactory(_pMessageFactory)
, pAlloc( _pAlloc )
, closedRemotely( false )
, closePending( false )
, isIncoming( _isIncoming )
, pingTime( 0 )
, packAddress( _clientAddress )
, sendQueueBytes_(0)
, recvQueueBytes_(0)
, sendSeqNum_(0)
, lastRecvSeqNum_(0)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Channel::~Channel()
{
  CObj<Stream> s;
  while( DequeueSendMsg( s ) )
    ReleaseReceived( s );
  //NI_ASSERT(0 == sendQueueBytes_, "sendQueueBytes_ have to be 0 here");

  while( DequeueRecvMsg( s ) )
    ReleaseReceived( s );
  //NI_ASSERT(0 == recvQueueBytes_, "recvQueueBytes_ have to be 0 here");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::InitAdresses( const ChannelAddr& _channelAddr, const Address& _address )
{
  address = _address;
  channelAddr = _channelAddr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::AddReceivedMsg( Stream* pMessage)
{
  EnqueueRecvMsg(pMessage);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> Channel::GetMsgToSend()
{
  CObj<Stream> msg;
  if (!DequeueSendMsg(msg))
    return 0;

  msg->Seek( 0, SEEKORIGIN_BEGIN );
  ChannelAddr caddr(channelAddr.pipe, channelAddr.client, channelAddr.sender, ++sendSeqNum_);
  WriteAddress( msg, caddr );
  return msg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::ConnectionState::Enum Channel::GetStatus() const
{
  return status;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> Channel::GetBufferToSend()
{
  if ( pAlloc )
    return pAlloc->Allocate();
  return new MemoryStream();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Channel::Send( const CObj<Stream> & pMessage )
{
  pMessage->Seek( 0, SEEKORIGIN_BEGIN );
  EnqueueSendMsg(pMessage);
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Stream> Channel::Receive()
{
  CObj<Stream> msg;

  if ( !DequeueRecvMsg( msg ) )
    return 0;

  msg->Seek( 0, SEEKORIGIN_BEGIN );
  return msg;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::ReleaseReceived( const CObj<Stream> & stream )
{
  if ( pAlloc )
    pAlloc->Release( stream );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::SendMsg( MessageBase* pMessage )
{
  NI_ASSERT( status != Network::ConnectionState::Closed, "invalid state " );
  CObj<Stream> pMsg = GetBufferToSend();

  int addrSz = GetAddressSize( channelAddr );
  pMsg->Seek( addrSz, SEEKORIGIN_BEGIN );

  int msgType = pMessage->GetTypeId();
  pMsg->Write( (void*)&msgType, sizeof( int ) );
  {
    ChunklessSaver saver( pMsg, 0, false );
    (*pMessage) & saver;
  }

  EnqueueSendMsg(pMsg);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MessageBase* Channel::ReceiveMsg()
{
  CObj<Stream> msg;
  if (!DequeueRecvMsg(msg))
    return 0;

  ChannelAddr addr;
  MessageBase* pMessage = 0;
  UnpackNetMessage( msg, pMessageFactory, addr, &pMessage );

  int rcConsistencyCheck = addr.ConsistensyCheck(lastRecvSeqNum_);
  if (rcConsistencyCheck < 0)
  {
    systemLog(NLogg::LEVEL_CRITICAL).Trace("WRONG RECV SEQUENCE. Previous recv num(%d), recv num(%d).Channel(s=%s,t=%s,c=%d,p=%d)", 
              lastRecvSeqNum_, addr.SeqNum(),address.source.c_str(), address.target.c_str(), channelAddr.client, channelAddr.pipe);
    //lastRecvSeqNum_ = addr.SeqNum();

    pMessageFactory->Destroy(pMessage);
    pMessage = 0;

    Close();
  }
  else
  {
    //systemLog(NLogg::LEVEL_MESSAGE).Trace("Previous recv num(%d), recv num(%d).Channel(s=%s,t=%s,c=%d,p=%d)", 
    //  lastRecvSeqNum_, addr.SeqNum(),address.source.c_str(), address.target.c_str(), channelAddr.client, channelAddr.pipe);

    lastRecvSeqNum_ = addr.SeqNum();
  }

  ReleaseReceived( msg );

  return pMessage;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MessageBase* Channel::PeekMsg()
{
  NI_ALWAYS_ASSERT( "This function is obsolete and shoundn't be used");
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::SendRaw( const byte* data, int size )
{
  if ( status == Network::ConnectionState::Closed )
    return;

  CObj<Stream> pMessage = GetBufferToSend();
  int addrSz = GetAddressSize( channelAddr );
  pMessage->SetSize( size + addrSz );
  pMessage->Seek( addrSz, SEEKORIGIN_BEGIN );

  pMessage->Write( (const void*)data, size );

  EnqueueSendMsg(pMessage);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Channel::ReceiveRaw( vector<byte>* data )
{
  CObj<Stream> msg;
  if ( !DequeueRecvMsg( msg ) )
    return false;

  msg->Seek( 0, SEEKORIGIN_BEGIN );
  ChannelAddr addr;
  ReadAddress( msg, addr );

  int rcConsistencyCheck = addr.ConsistensyCheck(lastRecvSeqNum_);
  if (rcConsistencyCheck < 0)
  {
    systemLog(NLogg::LEVEL_CRITICAL).Trace("WRONG RECV SEQUENCE. Previous recv num(%d), recv num(%d).Channel(s=%s,t=%s,c=%d,p=%d)", 
      lastRecvSeqNum_, addr.SeqNum(),address.source.c_str(), address.target.c_str(), channelAddr.client, channelAddr.pipe);
    //lastRecvSeqNum_ = addr.SeqNum();

    Close();
  }
  else
  {
    //systemLog(NLogg::LEVEL_MESSAGE).Trace("Previous recv num(%d), recv num(%d).Channel(s=%s,t=%s,c=%d,p=%d)", 
    //  lastRecvSeqNum_, addr.SeqNum(),address.source.c_str(), address.target.c_str(), channelAddr.client, channelAddr.pipe);
    lastRecvSeqNum_ = addr.SeqNum();

    int size = msg->GetSize() - msg->GetPosition();
    data->resize( size );
    msg->Read( data->begin(), size );
  }

  ReleaseReceived( msg );
  return (rcConsistencyCheck >= 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Channel::PeekRaw( vector<byte>* data )
{
  NI_ALWAYS_ASSERT( "This function is obsolete and shoundn't be used");
  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::Close()
{
  if ( channelAddr.pipe == EKnownPipeId::Invalid )
    closePending = true;
  else
    status = Network::ConnectionState::Closed;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::CloseRemotely()
{
  Close();
  closedRemotely = true;
}



Ping Channel::GetPingTime() const
{
  return pingTime;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Channel::NeedCheckPing()
{
  return false; //obsolette
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Channel::UpdatePingTime( int time )
{
  pingTime.value = time;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
