#include "stdafx.h"
#include "TransportMessages.h"

namespace Transport
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void RegisterMessages( MessageFactory* pFactory )
  {
    pFactory->RegisterInFactory( ENetLogicMessage::OpenChannelReq, OpenChannelRequest::NewInstance, OpenChannelRequest::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::CloseChannel, CloseChannelMessage::NewInstance, CloseChannelMessage::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::OpenChannelResp, OpenChannelResponse::NewInstance, OpenChannelResponse::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::PingMessage, PingMessage::NewInstance, PingMessage::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::ThroughPingMessage, ThroughPingMessage::NewInstance, ThroughPingMessage::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::KeepAliveMessage, KeepAliveMessage::NewInstance, KeepAliveMessage::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::AddRecipientReq, AddRecipientRequest::NewInstance, AddRecipientRequest::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::AddRecipientResp, AddRecipientResponse::NewInstance, AddRecipientResponse::DeleteInstance );
    pFactory->RegisterInFactory( ENetLogicMessage::RemoveRecipient, RemoveRecipientMessage::NewInstance, RemoveRecipientMessage::DeleteInstance );
  }

  namespace
  {
    struct SRegisterNetLogicMesssages
    {
      SRegisterNetLogicMesssages()
      {
        Transport::RegisterMessages( Transport::GetGlobalMessageFactory() );
      }
    } registerNetLogicMesssages;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
