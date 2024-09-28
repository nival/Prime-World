#include "stdafx.h"

#include <Coordinator/CoordinatorLocalClient.h>

#include <Network/ClientTransportSystem.h>
#include <Network/FreePortsFinder.h>
#include <Network/Initializer.h>
#include <Network/Message.h>

#include "GameStarter.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameStarter::GameStarter()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameStarter::~GameStarter()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameStarter::Start()
{
  networkDriver = Network::Initialize();

  Network::InitFreePortsFinder( Coordinator::GetPeersListenPort() );
  clientTransportSystem = new Transport::ClientTransportSystem( networkDriver, Transport::GetGlobalMessageFactory(), Network::GetFreePortsFinder() );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameStarter::Connect( const char* _loginServerAddr, const char* _login, const char* _password )
{
  clientTransportSystem->Login( _loginServerAddr, _login, _password, NULL );

  Login::ELoginResult::Enum result = Login::ELoginResult::NoResult;

  while ( Login::ELoginResult::NoResult == result )
  {
    result = clientTransportSystem->GetLoginResult();

    switch( result )
    {
    case Login::ELoginResult::Success:
      return true;

    case Login::ELoginResult::NoConnection:
      systemLog( NLogg::LEVEL_MESSAGE  ) << "Login error: cannot connect to login server at " << _loginServerAddr << endl;
      return false;
 
    case Login::ELoginResult::Refused:
      systemLog( NLogg::LEVEL_MESSAGE  ) << "Login error: login refused on login server at " << _loginServerAddr << endl;
      return false;
    }

    Sleep( 50 );
  }

  return false;
}


} // namespace Town
