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

#include "Server/Coordinator/CoordinatorClient.h"
#include "Server/Coordinator/CoordinatorClientRunner.h"

#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include "System/FileSystem/FileUtils.h"
#include "System/LogFileName.h"

#include "Server/DebugVarUpdate/DebugVarRequester.h" // TScenarioVars
#include "DebugConsole.h"
//#pragma warning(pop)

Transport::TServiceId const dcGameStatSvc = "dcgamestat";

enum {
  TRANSPORT_CLIENT_OLD = 1,
  TRANSPORT_CLIENT_NEW = 2,
  TRANSPORT_COORDINATOR = 3,
};


typedef StrongMT<DebugConsole::Client> ClientPtrT;
typedef nstl::vector<ClientPtrT> ClientsT;

struct Cfg
{
  static const int MAX_CLIENTS = 2000;

  Cfg()
    :clients_(1),
    user_("_randori"),
    statisticAddr_(":40002"),
    transportVersion_(TRANSPORT_COORDINATOR),
    service_(dcGameStatSvc)
    //DEBUG: vars_("ServerSide_TestVar_ONCE:0" ) // ,ServerSide_TestVar_PERIODIC:5,ServerSide_TestVar_NEVER:15")
  {}

  nstl::string loginaddr_;
  nstl::string statisticAddr_;

  nstl::string user_;
  nstl::string pswd_;
  int clients_;
  int transportVersion_;
  nstl::string service_;
  
  nstl::string vars_;
  NDebug::DebugVarRequesterMap::TScenarioVars vars_vector_; // сразу в готовом виде для скармливания requester'у

  void print();
  int parse_vars();
};

void Cfg::print()
{
  systemLog(NLogg::LEVEL_MESSAGE) 
    << "\n====================================" 
    << "\nVarUpdClient config:"
    << "\nlogin address: " << loginaddr_ 
    << "\nstatistic server address: " << statisticAddr_
    << "\nusername: " << user_
    << "\nnumber of clients: " << clients_ 
    << "\ntransport version: " << transportVersion_
    << "\nservice name: " << service_
    << "\nvar count: " << vars_vector_.size()
    << "\n===================================="
    << endl;
}


int Cfg::parse_vars()
{
  int pair_count = 0;
  int start = 0;
  int pos;
  do
  {// "var:value,var:value,.."
    pos = vars_.find(",", start);
    nstl::string pair = vars_.substr(start, pos-start); // "var:value"
    NDebug::SScenarioVar svar;
    if ( svar.Parse( pair, true ) )
    {
      vars_vector_.push_back( svar );
      pair_count++;
    }
    else
    {
      systemLog(NLogg::LEVEL_MESSAGE) << "bad name:value pair (" << pair << ") at vars[" << start << "]";
      return false;
    }          
    start = pos+1;    
  }
  while( pos > 0 && pos < vars_.length() );
   
  return pair_count;
}




void usage(char* /*module*/)
{
  systemLog(NLogg::LEVEL_MESSAGE) << "Usage:\n"
                                     "-h: this message (--help)\n"
                                     "-l: login address:port (--login)\n"
                                     "-d: statistic data server address:port (--data)\n"
                                     "-s: service name (--service)\n"
                                     "-v: var list (--vars) var:period[,var:period,...]\n"
                                     "Example: VarUpdClientApp.exe -l localhost:35001 -t 1 -s matchmaking\n"
                                     "         VarUpdClientApp.exe --login localhost:35001 --transport 1 --service matchmaking\n";
}

bool parse_args(int argc, char* argv[], Cfg & cfg)
{
  if (argc <= 1)
    return false;

  static const ACE_TCHAR options[] = ACE_TEXT ("hl:d:s:v:");
  ACE_Get_Opt get_opt (argc, argv, options, 1, 1);
  get_opt.long_option(ACE_TEXT ("help"), 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("login"), 'l', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("data"), 'd', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("service"), 's', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("vars"), 'v', ACE_Get_Opt::ARG_REQUIRED);

  bool res = true;
  bool vars_parsed = false;
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

    case 'd':
      cfg.statisticAddr_ = get_opt.optarg;
      res = true;
      break;

    case 's':
      cfg.service_ = get_opt.optarg;
      cfg.statisticAddr_ = ""; // если задано имя service, надо зачистить "имя для прямого коннекта к статистике"
      res = true;
      break;

    case 'v':
      {
        cfg.vars_ = get_opt.optarg;
        res = ( cfg.parse_vars() > 0 ); 
        vars_parsed = true;
      }
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

  if ( !vars_parsed && !cfg.vars_.empty() )
    res = cfg.parse_vars();

  return res;
}

bool init_clients_cluster(Cfg const & cfg, StrongMT<Transport::ITransportSystem> transport, 
                          StrongMT<Coordinator::CoordinatorClient> coord, ClientsT & clients)
{
  int clientsNum = cfg.clients_;
  if (clientsNum <= 0)
    return false;

  for (int i = 0; i < clientsNum; ++i)
  {
    clients.push_back( ClientPtrT( new DebugConsole::Client( i, transport, coord, cfg.vars_vector_, cfg.service_.c_str() ) ) );
  }

  return true;
}

void run_coordinator_connect_test( ClientsT & clients )
{
  int count = 0;
  do 
  {
    count = 0;
    for(ClientsT::iterator it = clients.begin(); it != clients.end(); )
    {
      ClientPtrT pc = *it;
      if ( pc->StepVarUpdate_Cluster() )
      {
        ++count;
        ++it;
      }
      else
      {
        it = clients.erase(it);
      }
      ::Sleep(10);
    }
  }
  while (count);
}

int ACE_TMAIN(int argc, char* argv[])
{
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "DebugConsole", "private", 0, 0, 0, 0);
  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
  ScopedPtr<NLogg::BasicTextFileDumper> textLogDumper;
  Reset( textLogDumper, NLogg::BasicTextFileDumper::New( &GetSystemLog(), "output" ) );

  Cfg cfg;
  if (!parse_args(argc, argv, cfg))
  {
    usage(argv[0]);
    return -1;
  }

  cfg.print();

  if ( TRANSPORT_COORDINATOR == cfg.transportVersion_ )
  {
    // Network initialization (server way: передрано из ServerFactory::Startup)
    StrongMT<Network::INetworkDriver> netDriver = Network::Initialize();
    //? думаю, в нашем случае heavy это перебор //netDriver->SetTrafficType( Network::EDriverTrafficType::Heavy ); 

    Network::InitFreePortsFinder( Network::GetFirstServerPort() );
    string myAddr = Network::GetHostIPByName( "localhost" );
    systemLog( NLogg::LEVEL_MESSAGE ) << "Local IP address: " << myAddr;
    netDriver->SetStreamAllocator( new Network::StreamAllocator() );

    StrongMT<Coordinator::CoordinatorClientRunner> coordClientRunner = 
      new Coordinator::CoordinatorClientRunner( "", Network::GetFreePortsFinder(), netDriver );
    StrongMT<Transport::ITransportSystem> transport = 
      TransportLayer::CreateTransportSystem(Transport::GetGlobalMessageFactory(), coordClientRunner->GetClient());

    StrongMT<Coordinator::CoordinatorClient> cli = coordClientRunner->GetClient();
    cli->SetBackendAddress( myAddr );

    if (!cfg.statisticAddr_.empty())
    {
      cli->AddRoute( dcGameStatSvc, cfg.statisticAddr_);
    }
    else
    {
      // автоматически регистрируем внешний сервис "сервер статистики" (по умолчанию - на нашем собственном localhost:40002)
      string coordAddr = cfg.loginaddr_;
      if (!coordAddr.empty())
      {
        coordClientRunner->Open( transport, coordAddr, "DebugCons_" );
        while( coordClientRunner->GetClient()->state() == Coordinator::ClientState::OPENING )
          Sleep( 10 );

        if ( coordClientRunner->GetClient()->state() != Coordinator::ClientState::OPEN )
        {
          LOG_C(0) << "CAN'T CONNECT TO COORDINATOR SERVICE"; 
          //return 0;
        }
        else
          LOG_M(0) << "Connected to coordinator service"; 
      }
    }

    ClientsT clients;
    if (init_clients_cluster(cfg, transport, cli, clients))
    {
      run_coordinator_connect_test( clients );
    }
  }

  return 0;
}
