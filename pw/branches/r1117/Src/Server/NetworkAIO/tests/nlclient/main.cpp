#include "stdafx.h"
#include "System/StdOutDumper.h"
#include "System/ThreadHelpers.h"
#include "System/FileSystem/FileUtils.h"
#include "System/ProfileManager.h"
#include "System/ConfigFiles.h"
#include "NLClient.h"
#include "NLProtocolHandlerFactory.h"
#include <ace/Get_Opt.h>
#include "NLClientCfg.h"

bool parse_args(int argc, char* argv[], NetworkLayer::ClientCfg & cfg)
{
  if (argc <= 1)
    return false;

  static const ACE_TCHAR options[] = ACE_TEXT ("s:h?");
  ACE_Get_Opt get_opt (argc, argv, options, 1, 1);
  get_opt.long_option(ACE_TEXT ("help"), 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("server"), 's', ACE_Get_Opt::ARG_REQUIRED);

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

    case 's':
      {
        cfg.serverAddr_.assign(get_opt.optarg);
        res = true;
      }
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
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "NLClient", "private", 0, 0, 0, 0);
  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
  ScopedPtr<NLogg::BasicTextFileDumper> textLogDumper;
  Reset( textLogDumper, NLogg::BasicTextFileDumper::New( &GetSystemLog(), "" ) );
  NBSU::InitUnhandledExceptionHandler();

  GetSystemLog().AddChannel(NetworkLayer::logname);

  NetworkLayer::ClientCfg cfg;
  if (parse_args(argc, argv, cfg))
  {
    NetworkLayer::ProtocolHandlerFactory phf;
    NetworkLayer::Client cl;
    cl.cfg_.naiocfg_.loglvl_ = 1;
    cl.cfg_.naiocfg_.phf_ = &phf;
    cl.cfg_.serverAddr_ = cfg.serverAddr_;

    cl.Run();
    return 0;
  }
  else
  {
    return 1;
  }
}
