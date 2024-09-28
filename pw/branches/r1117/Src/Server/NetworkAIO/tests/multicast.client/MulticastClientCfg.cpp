#include "stdafx.h"
#include "MulticastClientCfg.h"
#include <ace/ACE.h>
#include <ace/Get_Opt.h>
#include <ace/OS_NS_string.h>

namespace MulticastTest
{
  MulticastCfg::MulticastCfg()
    :user_("_randori"),
    sorcvbuf_(-1),
    rcvbuf_(128 * 1024),
    sosndbuf_(-1)
  {}

  void MulticastCfg::print()
  {

  }

  bool MulticastCfg::parse_args(int argc, char* argv[])
  {
    if (argc <= 1)
      return false;

    static const ACE_TCHAR options[] = ACE_TEXT ("hl:u:");
    ACE_Get_Opt get_opt (argc, argv, options, 1, 1);
    get_opt.long_option(ACE_TEXT ("help"), 'h', ACE_Get_Opt::NO_ARG);
    get_opt.long_option(ACE_TEXT ("login"), 'l', ACE_Get_Opt::ARG_REQUIRED);
    get_opt.long_option(ACE_TEXT ("user"), 'u', ACE_Get_Opt::ARG_REQUIRED);
    get_opt.long_option(ACE_TEXT ("rcvbuf"), ACE_Get_Opt::ARG_REQUIRED);
    get_opt.long_option(ACE_TEXT ("sorcvbuf"), ACE_Get_Opt::ARG_REQUIRED);
    get_opt.long_option(ACE_TEXT ("sosndbuf"), ACE_Get_Opt::ARG_REQUIRED);

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
        loginaddr_ = get_opt.optarg;
        res = true;
        break;

      case 'u':
        user_ = get_opt.optarg;
        res = true;
        break;

      case ':':
        systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
          << " requires an argument" << endl;
        break;

      case 0:
        {
          ACE_TCHAR const * longoptname = get_opt.long_option();
          if (!ACE_OS::strcmp(longoptname, "sorcvbuf"))
          {
            sorcvbuf_ = ACE_OS::atoi(get_opt.optarg);
            res = true;
          }
          else
          if (!ACE_OS::strcmp(longoptname, "rcvbuf"))
          {
            int val = ACE_OS::atoi(get_opt.optarg);
            if (val >= 0)
            {
              rcvbuf_ = unsigned int(val); 
              res = true;
            }
          }
          else
          if (!ACE_OS::strcmp(longoptname, "sosndbuf"))
          {
            sosndbuf_ = ACE_OS::atoi(get_opt.optarg);
            res = true;
          }
        }
        break;

      default:
        systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
          << " wrong option" << endl;
      }
    }

    return res;
  }

}
