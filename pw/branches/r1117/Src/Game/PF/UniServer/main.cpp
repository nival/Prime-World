#include "stdafx.h"
#include "main.h"

#if defined( NV_PLATFORM_WIN32 )
#include <WinCon.h>
#endif

#if defined( NV_LINUX_PLATFORM )
#include "mballocator/MessageBlockFactory.h"
#endif
#include "ServerAppBase/NivalServer.h"
#include "RelaySvc/RelayServerRunner2.h"
#include "Network/LoginServerAsync.h"
#include "Server/Accounting/BillingImpulsiveBuffsLoader.h"
#include "Server/LobbyPvx/LobbyServerNode.h"
#include "Server/LobbySocial/SocialLobbyService.h"

#include "HybridServer/GameService.h"

#include "libdb/Db.h"
#include "Network/ClusterConfiguration.h"
#include "main.ace.h"

#include "MatchMaking/MatchMakingNaming.h"
#include "MatchMaking/MatchMakingSvc.h"

#include "Server/HttpGateway/HttpGatewaySvc.h"
#include "Server/LiveMMaking/LiveMMakingSvcRunner.h"
#include "Server/Roll/RollServiceBalancerRunner.h"
#include "Server/Roll/RollServiceInstanceRunner.h"

#include <ClusterAdmin/ClusterAdminSvc/ClusterAdminSvc.h>
#include "ClusterAdmin/ClusterAdminSvc/ClusterAdminNaming.h"

#include <Monitoring/MonitoringSvc/MonitoringSvc.h>
#include "Monitoring/MonitoringSvc/MonitoringNaming.h"

#include "GameBalancer/GameBalancerSvc.h"
#include "GameBalancer/GameBalancerTypes.h"

#include "RelaySvc/RelaySvcNaming.h"
#include "Relay/RelayBalancer/RelayBalancerSvc.h"
#include "RelayBalancer/RelayBalancerNaming.h"

#include "UserManager/UserManagerSvc/UserManagerSvc.h"
#include "UserManagerSvc/UserManagerNaming.h"
#include "UserManagerSvc/Types.h"

#include <System/LogFileName.h>
#include "System/FileSystem/FileUtils.h"

#include "Version.h"
#include <Server/AppFramework/TimeSlicer.h>
#include "System/JobThread.h"
#include "ServerAppBase/NivalServiceRunner.h"

#include "System/InlineProfiler.h"
#include "Chat/ChatSvc/ChatSvc.h"
#include "ChatSvc/ChatSvcNaming.h"

#include "Server/NewLogin/NewLoginService.h"
#include "Server/NewLogin/NewLoginTypes.h"

#include "Server/ClientControl/ClientControlService.h"
#include "Server/ClientControl/ClientControlTypes.h"
#include "Server/ClientControl/ClientControlLog.h"

#include "System/CrashRptWrapper.h"
#include "System/sleep.h"

#ifdef NI_ENABLE_INLINE_PROFILER
#include <conio.h>
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"
#endif //NI_ENABLE_INLINE_PROFILER

volatile bool g_isRunning = true;

UniServerApp::UniServerApp()
{
}

bool UniServerApp::OnInitServerFactory( Transport::NivalServer * _fact ) 
{ 
  DebugTrace( "UniServer version: %s - %d.%d.%02d.%04d", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  {
    using namespace Coordinator;

#if defined( NV_WIN_PLATFORM )
    //relays
    _fact->RegisterServiceEx<Relay::RelayServerRunner2>           ( Relay::ServiceClass,                1,  SInterfacePolicy( EServiceInstancing::MULTIPLE, Coordinator::ESvcFlags::EXTERNAL ) );
    _fact->RegisterService<Relay::Balancer::Service>              ( Relay::Balancer::ServiceClass,      1,  SInterfacePolicy( EServiceInstancing::SINGLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG ), Transport::CustomServiceParams( true, Relay::RBLOG ) );

    //user management
    _fact->RegisterService<Login::LoginServerAsync>               ( Login::serviceId,                   1,  SInterfacePolicy( EServiceInstancing::SINGLE ), Transport::CustomServiceParams( true, LOGIN_CHNL ) );
    _fact->RegisterService<UserManager::Service>                  ( UserManager::ServiceClass,          1,  SInterfacePolicy( EServiceInstancing::SINGLE ), Transport::CustomServiceParams( true, UserManager::UMLOG ) );
    _fact->RegisterService<newLogin::InstanceSvc>                 ( newLogin::serviceIds::Service,      2,  SInterfacePolicy( EServiceInstancing::MULTIPLE, 0 ), Transport::CustomServiceParams( true ) );
    _fact->RegisterService<clientCtl::InstanceSvc>                ( clientCtl::serviceIds::Service,     1,  SInterfacePolicy( EServiceInstancing::SINGLE, 0 ), Transport::CustomServiceParams( true, CLIENTCTL_SVC_CHNL ) );

    //game services
    _fact->RegisterService<GameBalancer::Service>                 ( GameBalancer::ServiceClass,         1,  SInterfacePolicy( EServiceInstancing::SINGLE ), Transport::CustomServiceParams( true, GameBalancer::GBALANCER ) );
    _fact->RegisterService<HybridServer::GameService>             ( HybridServer::ServiceClass,         2,  SInterfacePolicy( EServiceInstancing::MULTIPLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG | Coordinator::ESvcFlags::EXTERNAL ), Transport::CustomServiceParams( false ) );
    _fact->RegisterService<lobby::ServerNode>                     ( lobby::serviceIds::Service,         2,  SInterfacePolicy( EServiceInstancing::MULTIPLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG | Coordinator::ESvcFlags::EXTERNAL ) );
    _fact->RegisterService<chat::Service>                         ( chat::ServiceClass,                 1,  SInterfacePolicy( EServiceInstancing::SINGLE, Coordinator::ESvcFlags::EXTERNAL ) );

    //mmaking and social lobby
    _fact->RegisterService<HttpGateway::Service>                  ( HttpGateway::ServiceInterfaceId,    1,  SInterfacePolicy( EServiceInstancing::MULTIPLE ) );
    _fact->RegisterService<mmaking::Service>                      ( mmaking::serviceIds::Service,       32, SInterfacePolicy( EServiceInstancing::MULTIPLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG ), Transport::CustomServiceParams( false ) );
    _fact->RegisterService<socialLobby::Service>                  ( socialLobby::serviceIds::Service,   1,  SInterfacePolicy( EServiceInstancing::SINGLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG | Coordinator::ESvcFlags::EXTERNAL ) ); //Only external interface is for GTC

    //roll
    _fact->RegisterService<roll::BalancerSvc>                     ( roll::serviceIds::BalancerService,  1,  SInterfacePolicy( EServiceInstancing::SINGLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG ), Transport::CustomServiceParams( false ) );
    _fact->RegisterService<roll::InstanceSvc>                     ( roll::serviceIds::InstanceService,  3,  SInterfacePolicy( EServiceInstancing::MULTIPLE, Coordinator::ESvcFlags::CAN_RELOAD_CFG ) );

    //misc
    _fact->RegisterService<ClusterAdmin::Service>                 ( ClusterAdmin::ServiceClass,         1,  SInterfacePolicy( EServiceInstancing::SINGLE ) );

    _fact->RegisterService<Monitoring::Service>                   ( Monitoring::ServiceId,              1,  SInterfacePolicy( EServiceInstancing::SINGLE ) );

    //Test services
    _fact->RegisterService<MatchMaking::Service>                  ( MatchMaking::ServiceClass,          0,  SInterfacePolicy( EServiceInstancing::SINGLE ) );
#elif defined( NV_LINUX_PLATFORM )
    _fact->RegisterService<chat::Service>                         ( chat::ServiceClass,                 1,  SInterfacePolicy( EServiceInstancing::SINGLE, Coordinator::ESvcFlags::EXTERNAL ) );
#endif
  }

  return true; 
}

bool  UniServerApp::OnInit(int argc, char* argv[])
{
  if (-1 == ace_init())
    return false;

  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "UniServer", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);

#ifdef _DEBUG
  bool crashRepNoGui = false;
#else
  bool crashRepNoGui = true;
#endif //_DEBUG
#if defined( NV_WIN_PLATFORM )
  CrashRptWrapper::InstallForProcess( "http://SITE.com/upload/", true, crashRepNoGui, "Uniserver" );
#endif

  return Transport::ServerAppBase::OnInit( argc, argv );
}

int UniServerApp::OnExit()
{
  bool res = Transport::ServerAppBase::OnExit();

#if defined( NV_WIN_PLATFORM )
  CrashRptWrapper::UninstallFromProcess();
#endif

  ace_fini();
  LOG_M(0) << "Server stopped" << endl;
  return res;
}


#ifdef NI_ENABLE_INLINE_PROFILER
class ProfilerUIKeyboardListener : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( ProfilerUIKeyboardListener, threading::IThreadJob, BaseObjectMT );
public:
  ProfilerUIKeyboardListener() {}
  virtual void Work( volatile bool & isRunning ) {
    profiler3ui::Init();
    while( isRunning ) {
      if ( _kbhit() )
      {
        char c = _getch();
        if ( c == 'p' || c == 'P' )
          profiler3ui::Show( NULL );
      }
      Sleep( 10 );
    }
    profiler3ui::Shutdown();
  }
};

#endif //NI_ENABLE_INLINE_PROFILER



//Debug tool to stop cluster
class DebugServerBrake : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( DebugServerBrake, threading::IThreadJob, BaseObjectMT );
public:
  DebugServerBrake() : flag( None ) {}
  virtual void Work( volatile bool & isRunning ) {
    while( isRunning ) {
      EFlag newf = None;
      if ( FILE * f = fopen( "stopme.flag", "rb" ) ) {
        fclose( f );
        newf = Present;
      }
      else
        newf = Absent;

      if ( ( flag != None ) && ( flag != newf ) && ( newf == Present ) )
      {
        MessageTrace( "Stopping server with file flag!" );
        g_isRunning = false;
      }

      flag = newf;
      nival::sleep( 500 );
    }
  }
private:
  enum EFlag { None, Present, Absent } flag;
};


#if defined( NV_WIN_PLATFORM )
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
#endif


int main(int argc, char* argv[])
{
#if defined( NV_WIN_PLATFORM )
  ::SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE);
#endif

  ni_detail::InitPointersStatics();

#ifdef NI_ENABLE_INLINE_PROFILER
  profiler3::GetControl()->Setup( profiler3::SSettings() );

  StrongMT<threading::JobThread> profilerUIKeyboardListener = new threading::JobThread( new ProfilerUIKeyboardListener, "ProfilerUIKeyboardListener" );

  NI_PROFILE_THREAD;
#endif //NI_ENABLE_INLINE_PROFILER

  StrongMT<threading::JobThread> debugServerBrake = new threading::JobThread( new DebugServerBrake, "DebugServerBrake" );

  StrongMT<UniServerApp> app = new UniServerApp;
  if (app->OnInit(argc, argv))
  {
    app->OnRun();
    AppFramework::TimeSlicer runner(0.f);
    runner.AddInstance(app);
    runner.Do(g_isRunning);
  }

  debugServerBrake = 0;

  int appResult = app->OnExit();

  GetSystemLog().ClearAllDumpers();

  app = 0;
  return appResult;
};
