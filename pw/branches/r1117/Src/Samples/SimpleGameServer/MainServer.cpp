#include "stdafx.h"

#include <ServerAppBase/ServerAppBase.h>
#include <Chat/ChatManager.h>
#include <Samples/SimpleGame/LocationServerRunner.h>
#include <Samples/SimpleGame/BattleServerRunner.h>
#include <Samples/SimpleGameAI_CPP/AIServerRunner.h>
#include "Network/RelayServerRunner.h"
#include "Coordinator/LoginServerRunner.h"

class UniServerApp: public Transport::ServerAppBase
{
public:
  UniServerApp() 
  {

  }

  virtual bool OnInitServerFactory( Transport::ServerFactory* _serverFactory ) 
  { 
    _serverFactory->RegisterServer( "ai", new AI::AIServerRunner() );
    _serverFactory->RegisterServer( "relay", new Transport::RelayServerRunner() );
    _serverFactory->RegisterServer( "login", new Login::LoginServerRunner() );
//     _serverFactory->RegisterServer( "chat", new Chat::ChatManager() );
    _serverFactory->RegisterServer( "battle", new Battle::BattleServerRunner() );
    _serverFactory->RegisterServer( "location", new Location::LocationServerRunner() );
    return true; 
  }


  DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP_CONSOLE( UniServerApp );
BEGIN_EVENT_TABLE( UniServerApp, ServerAppBase )
END_EVENT_TABLE()


