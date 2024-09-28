#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatSvc.h"
#include "ChatSvc/ChatSvcCfg.h"
#include "ChatSvc/ChatSvcNaming.h"
#include "ChatSvc/LChatManagementIface.auto.h"
#include "ChatSvc/LChatClientIface.auto.h"
#include "Coordinator/Interface.h"

namespace chat
{

Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  impl = new ChatSvcImpl;

  RegisterBackendObject<chat::IChatManagement>( impl, chat::ServiceRpcIface );
  RegisterBackendAttach<chat::IChatManagement, chat::LIChatManagement>();

  RegisterFrontendObject<chat::IChatClient>( impl, chat::ClientRpcIface );
  RegisterFrontendAttach<chat::IChatClient, chat::LIChatClient>();
}



Service::~Service()
{
  UnregisterBackendObject<chat::IChatManagement>( impl );
  UnregisterFrontendObject<chat::IChatClient>( impl );
}



void Service::Poll( timer::Time _now )
{
  impl->Step();
}



void Service::OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node )
{
  Transport::BaseService::OnChannelClosed( channel,  node );

  Transport::TClientId cid = channel->GetInternalClientId();
  if ( cid != Transport::autoAssignClientId )
  {
    impl->UnregisterUser(cid);
  }
}

}
