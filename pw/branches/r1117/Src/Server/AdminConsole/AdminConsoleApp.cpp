#include "stdafx.h"
#include <conio.h>
#include <iostream>
//#pragma warning(push)
//#pragma warning( disable : 4251)
#include <ace/ACE.h>
#include <ace/Get_Opt.h>

#include "Server/Network/ClusterConfiguration.h"
#include "Server/Network/StreamAllocator.h"
#include "Server/Network/Initializer.h"
#include "Server/Network/Transport.h"
#include "Server/Network/TransportInitializer.h"
#include "Server/Network/TransportMessages.h"
#include "transport/TLTransportModule.h"
#include "transport/TLCfg.h"
#include "transport/TLDefaultLogCallback.h"

#include "System/ServerStdOutDumper.h"
#include "System/ServerTextFileDumper.h"
#include "System/FileSystem/FileUtils.h"
#include "System/LogFileName.h"

#include "AdminConsole.h"

typedef StrongMT<AdminConsole::Client> ClientPtrT;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Cfg
{
  static const int MAX_CLIENTS = 2000;

  Cfg()
  {}

  nstl::string loginaddr_;

  void print();
  int parse_vars();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Cfg::print()
{
  systemLog(NLogg::LEVEL_MESSAGE) 
    << "\n====================================" 
    << "\nAdminConsole config:"
    << "\nlogon address: " << loginaddr_ 
    << "\n===================================="
    << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void usage()
{
  systemLog(NLogg::LEVEL_MESSAGE) << "Usage:\n"
                                     "-h: this message (--help)\n"
                                     "-l: logon address:port (--logon) for ClusterAdmin service\n"
                                     "Example: AdminConsole.exe -l localhost:35010\n"
                                     ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool parse_args(int argc, char* argv[], Cfg & cfg)
{
  if (argc <= 1)
    return false;

  static const ACE_TCHAR options[] = ACE_TEXT ("hl:d:s:v:");
  ACE_Get_Opt get_opt (argc, argv, options, 1, 1);
  get_opt.long_option(ACE_TEXT ("help"), 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("logon"), 'l', ACE_Get_Opt::ARG_REQUIRED);

  bool res = true;
  int option;
  while (res && (option = get_opt ()) != EOF)
  {
    res = false;
    switch (option)
    {
    case 'h':
    case '?':
      break;

    case 'l':
      cfg.loginaddr_ = get_opt.optarg;
      res = true;
      break;

    case ':':
      systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
        << " requires an argument" << endl;
      break;
    default:
      systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
        << " wrong option" << endl;
    }
  }

  return res;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ACE_TMAIN(int argc, char* argv[])
{
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "AdminConsole", "private", 0, 0, 0, 0);
  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
  ScopedPtr<NLogg::CServerTextFileDumper> textLogDumper;
  Reset( textLogDumper, new NLogg::CServerTextFileDumper( &GetSystemLog() ) );
  textLogDumper->SetFileName("output");

  Cfg cfg;
  if (!parse_args(argc, argv, cfg))
  {
    usage();
    return -1;
  }

  cfg.print();

  // автоматически регистрируем внешний сервис "сервер статистики" (по умолчанию - на нашем собственном localhost:40002)
  if( !cfg.loginaddr_.empty() )
  {
    StrongMT<Network::INetworkDriver> netDriver = Network::Initialize();

    Network::InitFreePortsFinder( Network::GetFirstServerPort() );
    string myAddr = Network::GetHostIPByName( "localhost" );
    systemLog( NLogg::LEVEL_MESSAGE ) << "Local IP address: " << myAddr;
    netDriver->SetStreamAllocator( new Network::StreamAllocator() );

    Transport::DummyAddressResolver dummyResolver( cfg.loginaddr_ );
    StrongMT<Transport::ITransportSystem> transport = 
      Transport::CreateTransportSystem( netDriver, Transport::GetGlobalMessageFactory(), &dummyResolver );

    // gatekeeper пусть AdminConsole::Client создает сам, и связь устанавливает сам; чтобы если что, удобно было встроить в другой App
    ClientPtrT client = new AdminConsole::Client( 1, transport, cfg.loginaddr_ ); 
    //run_coordinator_connect_test:
    while( client && client->StepVarUpdate_Cluster() )
      ::Sleep(10);
  }
  else
  {
    LOG_C(0) << "no logon address specified";
    usage();
  }
  
  return 0;
}
