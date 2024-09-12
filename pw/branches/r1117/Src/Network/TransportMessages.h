#pragma once
#include "Message.h"
#include "TransportLoginData.h"
#include "TransportAddress.h"
#include "TransportUtils.h"
#include "TransportChannelType.h"
#include "TransportMessagesResults.h"

namespace Transport
{

#if defined( NV_WIN_PLATFORM )
  typedef unsigned long long           SendTimeT;
  typedef unsigned long                SeqNumT;
  typedef TPipeId                      PipeIdT;
  typedef Transport::TClientId         ClientIdT;
#elif defined( NV_LINUX_PLATFORM )
  typedef nival::uint64_t              SendTimeT;
  typedef nival::uint32_t              SeqNumT;
  typedef nival::uint16_t              PipeIdT;
  typedef nival::int32_t               ClientIdT;
#endif

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  namespace ENetLogicMessage
  {
    enum Enum
    {
      OpenChannelReq,
      CloseChannel,
      OpenChannelResp,
      PingMessage,
      ThroughPingMessage,
      KeepAliveMessage,
      AddRecipientReq,
      AddRecipientResp,
      RemoveRecipient,
    };
  }

  typedef TypedMessageBase<ENetLogicMessage::Enum> NetLogicMessage;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct OpenChannelRequest : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::OpenChannelReq; }
    static int GetClassType() { return ENetLogicMessage::OpenChannelReq; }
    static MessageBase* NewInstance() { return new OpenChannelRequest(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    Address clientAddress;
    TLoginData loginData;
    PipeIdT localPipeId; //local to sender
    EChannelType::Enum channelType;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&clientAddress); if (!f.GetError()) f.Add(3,&loginData); if (!f.GetError()) f.Add(4,&localPipeId); if (!f.GetError()) f.Add(5, &channelType); return 0; }

    OpenChannelRequest()
      :channelType(EChannelType::Invalid) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct CloseChannelMessage : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::CloseChannel; }
    static int GetClassType() { return ENetLogicMessage::CloseChannel; }
    static MessageBase* NewInstance() { return new CloseChannelMessage(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    ChannelAddr clientAddress;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&clientAddress); return 0; }

    CloseChannelMessage() {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct OpenChannelResponse : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::OpenChannelResp; }
    static int GetClassType() { return ENetLogicMessage::OpenChannelResp; }
    static MessageBase* NewInstance() { return new OpenChannelResponse(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    bool success;
    Address clientAddress;
    //TClientId origUserId;
    PipeIdT localPipeId;  //local to receiver
    ChannelAddr remoteAddr; //remote to receiver
    EChannelType::Enum channelType;

    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&success); if (!f.GetError()) f.Add(3,&clientAddress); if (!f.GetError()) f.Add(4,&localPipeId); if (!f.GetError()) f.Add(5,&remoteAddr); if (!f.GetError()) f.Add(6, &channelType); return 0; }

    OpenChannelResponse() : success(false), localPipeId(0), channelType(EChannelType::Invalid) {}
    OpenChannelResponse(bool _res, EChannelType::Enum _chtype) : success(_res), localPipeId(0), channelType(_chtype) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct PingMessage : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::PingMessage; }
    static int GetClassType() { return ENetLogicMessage::PingMessage; }
    static MessageBase* NewInstance() { return new PingMessage(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    ChannelAddr requestingChannel;
    SendTimeT sendTime;
    SeqNumT seqNum;
    bool reply;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&requestingChannel); if (!f.GetError()) f.Add(3,&sendTime); if (!f.GetError()) f.Add(4, &seqNum); if (!f.GetError()) f.Add(5,&reply); return 0; }

    PingMessage() : sendTime(0), seqNum(0), reply(false) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct ThroughPingMessage : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::ThroughPingMessage; }
    static int GetClassType() { return ENetLogicMessage::ThroughPingMessage; }
    static MessageBase* NewInstance() { return new ThroughPingMessage(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    ChannelAddr requestingChannel;
    SendTimeT sendTime;
    SeqNumT seqNum;
    bool reply;
    SendTimeT throughSendTime;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&requestingChannel); if (!f.GetError()) f.Add(3,&sendTime); if (!f.GetError()) f.Add(4, &seqNum); if (!f.GetError()) f.Add(5,&reply); if (!f.GetError()) f.Add(6, &throughSendTime); return 0; }

    ThroughPingMessage() : sendTime(0), reply(false), throughSendTime(0) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct KeepAliveMessage : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::KeepAliveMessage; }
    static int GetClassType() { return ENetLogicMessage::KeepAliveMessage; }
    static MessageBase* NewInstance() { return new KeepAliveMessage(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    nival::int32_t keepAliveInterval; // Just for debug only!
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&keepAliveInterval); return 0; }

    KeepAliveMessage() : keepAliveInterval(0) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct AddRecipientRequest : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::AddRecipientReq; }
    static int GetClassType() { return ENetLogicMessage::AddRecipientReq; }
    static MessageBase* NewInstance() { return new AddRecipientRequest(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    ChannelAddr caddr;
    ClientIdT recipient;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&caddr); if (!f.GetError()) f.Add(3,&recipient); return 0; }

    AddRecipientRequest() : recipient(Transport::autoAssignClientId) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct AddRecipientResponse : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::AddRecipientResp; }
    static int GetClassType() { return ENetLogicMessage::AddRecipientResp; }
    static MessageBase* NewInstance() { return new AddRecipientResponse(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    AddRecipientResult::Enum result;
    ChannelAddr caddr;
    ClientIdT recipient;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&result); if (!f.GetError()) f.Add(3,&caddr); if (!f.GetError()) f.Add(4,&recipient); return 0; }

    AddRecipientResponse() : result(AddRecipientResult::FAIL), recipient(Transport::autoAssignClientId) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct RemoveRecipientMessage : public NetLogicMessage
  {
    virtual ENetLogicMessage::Enum GetType() const { return ENetLogicMessage::RemoveRecipient; }
    static int GetClassType() { return ENetLogicMessage::RemoveRecipient; }
    static MessageBase* NewInstance() { return new RemoveRecipientMessage(); }
    static void DeleteInstance(MessageBase* msg){ delete msg; }

    ZDATA
    ZNOPARENT(NetLogicMessage)
    ChannelAddr caddr;
    ClientIdT recipient;
    ZEND int operator&( IBinSaver &f ) { if (!f.GetError()) f.Add(2,&caddr); if (!f.GetError()) f.Add(3,&recipient); return 0; }

    RemoveRecipientMessage() : recipient(Transport::autoAssignClientId) {}
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void RegisterMessages( MessageFactory* pFactory );
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
