#include "stdafx.h"
#include "ClusterConfiguration.h"
#include "System/Commands.h"
#include "Network/FreePortsFinder.h"
#include "PW_Game/server_ip.h"

namespace 
{
  string coordinatorAddr = string(SERVER_IP) + ":" + SERVER_PORT;
  string loginAddr = string(SERVER_IP) + ":" + LOGIN_PORT + "@10";
  int firstServerPort = SERVER_PORT_INT;
  string frontendIPAddr = "localhost";
  string backendIPAddr = "localhost";

  REGISTER_VAR( "coordinator_address", coordinatorAddr, STORAGE_GLOBAL );
  //REGISTER_VAR( "login_address", loginAddr, STORAGE_GLOBAL );
  //REGISTER_VAR( "first_server_port", firstServerPort, STORAGE_GLOBAL );
  REGISTER_VAR( "frontend_ip_addr", frontendIPAddr, STORAGE_GLOBAL);
  REGISTER_VAR( "backend_ip_addr", backendIPAddr, STORAGE_GLOBAL);
}

namespace Network
{

const string & GetCoordinatorAddress()
{
  return coordinatorAddr;
}

const string & GetLoginServerAddress()
{
  return loginAddr;
}

int GetFirstServerPort()
{
  return firstServerPort;
}

const string & GetFrontendIPAddr()
{
  return frontendIPAddr;
}

const string & GetBackendIPAddr()
{
  return backendIPAddr;
}

}
