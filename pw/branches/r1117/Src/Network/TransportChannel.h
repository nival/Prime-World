#pragma once
#include "Transport.h"

#include "TransportLoginData.h"
#include "TransportAddress.h"
#include "TransportMessages.h"
#include "Network.h"

#include "System/TSList.h"
#include "System/Thread.h"

namespace Transport
{
  extern bool bTraceRecv;
  extern bool bTraceSend;

	struct MessageBase;
	struct ConnectionMux;
	class MessageFactory;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Channel : public BaseObjectMT, public IChannel
	{
    NI_DECLARE_REFCOUNT_CLASS_2( Channel, BaseObjectMT, IChannel )

	public:
		Channel( bool isIncoming, const Address& address, const TLoginData& loginData, MessageFactory* _pMessageFactory, Network::IStreamAllocator* pAlloc, bool clientAddress );
    ~Channel();

		// internal interface
    void InitAdresses( const ChannelAddr& _channelAddr, const Address& _address );
    const ChannelAddr& GetChannelAddr() const { return channelAddr; }

		void AddReceivedMsg( Stream* pMessage );
		CObj<Stream> GetMsgToSend();
    void SetStatus( Network::ConnectionState::Enum _status ) { status = _status; }

    void CloseRemotely();
    bool IsClosedRemotely() const { return closedRemotely; }
    bool IsClosePending() const { return closePending; }

    CObj<Stream> GetBufferToSend();
    bool Send( const CObj<Stream> & data );
    CObj<Stream> Receive();
    void ReleaseReceived( const CObj<Stream> & stream );

    bool NeedCheckPing();
    void UpdatePingTime( int time );

    // IChannel
    virtual Network::ConnectionState::Enum GetStatus() const;
    virtual void Close();

		virtual const Address& GetAddress() const { return address; }
    virtual TClientId GetInternalClientId() const { return channelAddr.client; }

		virtual const TLoginData& GetLoginData() const { return loginData; }
    virtual bool IsIncomingConnection() const { return isIncoming; }

		virtual void SendMsg( MessageBase* pMessage );
		virtual MessageBase* ReceiveMsg();
    virtual MessageBase* PeekMsg();

    virtual void SendRaw( const byte* data, int size );
    virtual bool ReceiveRaw( vector<byte>* data );
    virtual bool PeekRaw( vector<byte>* data );

    virtual Ping GetPingTime() const;
    virtual void FillDebugString( string & _outStr ) {}

    unsigned int GetLastRecvSeqNum() const;
    void IncLastRecvSeqNum();

  private:
    bool EnqueueRecvMsg(CObj<Stream> const & msg);
    bool DequeueRecvMsg(CObj<Stream> & msg);
    bool EnqueueSendMsg(CObj<Stream> const & msg);
    bool DequeueSendMsg(CObj<Stream> & msg);

  private:
    Channel() {}
    Address address;
    ChannelAddr channelAddr;

    TLoginData loginData;
    Network::ConnectionState::Enum status;
    bool closedRemotely;
    bool closePending;
    bool isIncoming;
    bool packAddress;

    Ping pingTime;

    SPSCQueue<CObj<Stream>, Stream*> sendMessages;
    SPSCQueue<CObj<Stream>, Stream*> recvMessages;

    Network::IStreamAllocator* pAlloc;
    MessageFactory* pMessageFactory;

    //  total messages size in queues
    unsigned int sendQueueBytes_;
    unsigned int recvQueueBytes_;

    unsigned int sendSeqNum_;
    unsigned int lastRecvSeqNum_;
  };
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  inline
  bool Channel::EnqueueRecvMsg(CObj<Stream> const & msg)
  {
    recvMessages.Enqueue(msg);
    recvQueueBytes_ += msg->GetSize();
    if (Transport::bTraceRecv)
    {
      systemLog(NLogg::LEVEL_MESSAGE) << 
        "transport: recv.IN  (time = "<< NHPTimer::GetScalarTime() << 
        " msg.size = " << msg->GetSize() << 
        " queue.size = " << recvMessages.Size() << 
        " queue.bytes = " << recvQueueBytes_ << 
        " tid = " << threading::CurrentThreadID() << 
        ")" << endl;
    }

    return true;
  }

  inline
  bool Channel::DequeueRecvMsg(CObj<Stream> & msg)
  {
    if ( !recvMessages.Dequeue( msg ) )
      return false;

    recvQueueBytes_ -= msg->GetSize();
    if (Transport::bTraceRecv)
    {
      systemLog(NLogg::LEVEL_MESSAGE) << 
        "transport: recv.OUT (time = "<< NHPTimer::GetScalarTime() << 
        " msg.size = " << msg->GetSize() << 
        " queue.size = " << recvMessages.Size() << 
        " tid = " << threading::CurrentThreadID() << 
        ")" << endl;
    }
    return true;
  }

  inline
  bool Channel::EnqueueSendMsg(CObj<Stream> const & msg)
  {
    sendMessages.Enqueue(msg);
    sendQueueBytes_ += msg->GetSize();

    if (Transport::bTraceSend)
    {
      systemLog(NLogg::LEVEL_MESSAGE) << 
        "transport: send IN  (time = "<< NHPTimer::GetScalarTime() << 
        " msg.size = " << msg->GetSize() << 
        " queue.size = " << sendMessages.Size() << 
        " queue.bytes = " << sendQueueBytes_ << 
        " tid = " << threading::CurrentThreadID() << 
        ")" << endl;
    }
    return true;
  }

  inline
  bool Channel::DequeueSendMsg(CObj<Stream> & msg)
  {
    if (!sendMessages.Dequeue(msg))
      return false;

    sendQueueBytes_ -= msg->GetSize();
    if (Transport::bTraceSend)
    {
      systemLog(NLogg::LEVEL_MESSAGE) << 
        "transport: send OUT (time = "<< NHPTimer::GetScalarTime() << 
        " msg.size = " << msg->GetSize() << 
        " queue.size = " << sendMessages.Size() << 
        " queue.bytes = " << sendQueueBytes_ << 
        " tid = " << threading::CurrentThreadID() << 
        ")" << endl;
    }
    return true;
  }

  inline
  unsigned int Channel::GetLastRecvSeqNum() const
  {
    return lastRecvSeqNum_;
  }

  inline
  void Channel::IncLastRecvSeqNum()
  {
    ++lastRecvSeqNum_;
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}