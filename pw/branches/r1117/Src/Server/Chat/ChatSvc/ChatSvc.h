#pragma once
#include "ServerAppBase/NivalService.h"
#include "ChatSvc/ChatSvcImpl.h"

namespace chat
{

class Service : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( Service, Transport::BaseService );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~Service();

protected:
  virtual void Poll( timer::Time _now );
  virtual void OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node );
private:
  StrongMT<ChatSvcImpl> impl;
};

FORCE_INIT_FACTORY( ChatUserInfo );
FORCE_INIT_FACTORY( ChannelInfo );
FORCE_INIT_FACTORY( SessionInfo );

FORCE_INIT_FACTORY( RIChatManagement );
FORCE_INIT_FACTORY( RIChatClientCallback );

}
