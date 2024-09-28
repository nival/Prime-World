#include "stdafx.h"
#include "ClusterConfiguration.h"
#include "System/Commands.h"
#include "Network/FreePortsFinder.h"

namespace 
{
  string coordinatorAddr = "26.2.255.15:55001";
  string loginAddr = "26.2.255.15:55001";
  int firstServerPort = 55001;
  string frontendIPAddr = "26.2.255.15";
  string backendIPAddr = "26.2.255.15";

  REGISTER_VAR( "coordinator_address", coordinatorAddr, STORAGE_GLOBAL );
  REGISTER_VAR( "login_address", loginAddr, STORAGE_GLOBAL );
  REGISTER_VAR( "first_server_port", firstServerPort, STORAGE_GLOBAL );
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
