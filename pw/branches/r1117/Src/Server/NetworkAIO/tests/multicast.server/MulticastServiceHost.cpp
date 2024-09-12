#include "stdafx.h"

#include "ServerAppBase/NivalServer.h"
#include "RelaySvc/RelayServerRunner2.h"
#include "Coordinator/LoginServerRunner.h"

#include "Network/ClusterConfiguration.h"

#include "RelaySvc/RelaySvcNaming.h"
#include "Relay/RelayBalancer/RelayBalancerRunner.h"
#include "RelayBalancer/RelayBalancerNaming.h"
#include "UserManager/UserManagerSvc/UserManagerRunner.h"
#include "UserManager/UserManagerSvc/UserManagerNaming.h"
#include "Server/NetworkAIO/tests/multicast.server/MulticastTestRunner.h"
#include "Server/NetworkAIO/tests/multicast.server/MulticastTestNaming.h"

#include <System/LogFileName.h>
#include "MulticastServiceHost.h"
#include "Version.h"
#include <Server/AppFramework/TimeSlicer.h>
#include <System/FileSystem/FileUtils.h>

volatile bool g_isRunning = true;

namespace TransportTest
{
  MulticastServiceHost::MulticastServiceHost()
  {
  }

  bool MulticastServiceHost::OnInitServerFactory( Transport::NivalServer * _fact ) 
  { 
    DebugTrace( "MulticastServiceHost version: %s - %d.%d.%02d.%04d", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

    {
      using namespace Coordinator;

      //relays
      _fact->RegisterService<Relay::RelayServerRunner2>           ( Relay::ServiceClass,                1,  SInterfacePolicy( EServiceInstancing::MULTIPLE ) );
      _fact->RegisterService<Relay::Balancer::ServiceRunner>      ( Relay::Balancer::ServiceClass,      1,  SInterfacePolicy( EServiceInstancing::SINGLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG ) );

      //user management
      _fact->RegisterService<Login::LoginServerRunner>            ( Login::serviceId,                   1,  SInterfacePolicy( EServiceInstancing::SINGLE ) );
      _fact->RegisterService<UserManager::ServiceRunner>          ( UserManager::ServiceClass,          1,  SInterfacePolicy( EServiceInstancing::SINGLE ) );

      _fact->RegisterService<MulticastTest::ServiceRunner>        ( MulticastTest::ServiceClass,        1,  SInterfacePolicy( EServiceInstancing::SINGLE ) );
    }

    return true; 
  }

  bool MulticastServiceHost::OnInit(int argc, char* argv[])
  {
    NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "MulticastServiceHost", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);
    return Transport::ServerAppBase::OnInit( argc, argv );
  }

  int MulticastServiceHost::OnExit()
  {
    bool res = Transport::ServerAppBase::OnExit();
    LOG_M(0) << "Server stopped" << endl;
    return res;
  }
}

BOOL WINAPI ConsoleHandler(DWORD evt)
{
  switch(evt)
  {
  case CTRL_C_EVENT:
  case CTRL_BREAK_EVENT:
  case CTRL_CLOSE_EVENT:
  case CTRL_LOGOFF_EVENT:
  case CTRL_SHUTDOWN_EVENT:
    LOG_M(0) << "Stopping server ..." << endl;
    g_isRunning = false;
    return TRUE;
  }

  return FALSE;
}

int main(int argc, char* argv[])
{
  ::SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE);

  ni_detail::InitPointersStatics();

  StrongMT<TransportTest::MulticastServiceHost> app = new TransportTest::MulticastServiceHost;
  if (app->OnInit(argc, argv))
  {
    app->OnRun();
    AppFramework::TimeSlicer runner(0.f);
    runner.AddInstance(app);
    runner.Do(g_isRunning);
  }

  int appResult = app->OnExit();
  return appResult;
};
