#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <ace/Get_Opt.h>
#include <Network/Initializer.h>
#include <Network/Transport.h>
#include <Network/TransportInitializer.h>
#include <System/StdOutDumper.h>
#include <System/TextFileDumper.h>

#include "ClusterAdminClient.h"


struct Cfg : public ClusterAdmin::ClientConfig
{
  Cfg()
    :shutdownTimeout_(0xFFFFFFFF)
  {}

  unsigned int shutdownTimeout_;
};

void usage(char* /*module*/)
{
  std::cout << "Usage:\n"
               "-h: this message (--help)\n"
               "-s: shutdown cluster in N seconds (--shutdown)\n"
               "-c: connect to ip-address:port (--connect)\n"
               "Example: ClusterAdminClientApp.exe -c localhost:35002 -s 3000\n"
               "         ClusterAdminClientApp.exe --connect localhost:35002 --shutdown 60"
               << std::endl;
}

bool parse_args(int argc, char* argv[], Cfg & cfg)
{
  static const ACE_TCHAR options[] = ACE_TEXT ("l:c:u:p:h");
  ACE_Get_Opt get_opt (argc, argv, options, 1, 1);
  get_opt.long_option(ACE_TEXT ("help"), 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("shutdown"), 's', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("connect"), 'c', ACE_Get_Opt::ARG_REQUIRED);

  bool res = true;
  int option;
  while (res && (option = get_opt ()) != EOF)
  {
    res = false;
    switch (option)
    {
    case 'h':
    case '?':
      usage(argv[0]);
      res = true;
      break;

    case 's':
      cfg.shutdownTimeout_ = ACE_OS::atoi(get_opt.optarg);
      res = true;
      break;

    case 'c':
      cfg.svcNetAddr_ = get_opt.optarg;
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


int ACE_TMAIN(int argc, char* argv[])
{
  StrongMT<NLogg::CStdOutDumper> stdoutDumper = new NLogg::CStdOutDumper( &GetSystemLog() );
  StrongMT<NLogg::CTextFileDumper> textLogDumper = new NLogg::CTextFileDumper( &GetSystemLog() );
  textLogDumper->SetFileName("output");

  Cfg cfg;
  if (!parse_args(argc, argv, cfg))
  {
    usage(argv[0]);
    return -1;
  }

  StrongMT<ClusterAdmin::Client> client = new ClusterAdmin::Client;
  if (client->Init(cfg))
  {
    if (0xFFFFFFFF != cfg.shutdownTimeout_)
      client->Shutdown(cfg.shutdownTimeout_);
  }

  GetSystemLog().ClearAllDumpers();

  return 0;
}
