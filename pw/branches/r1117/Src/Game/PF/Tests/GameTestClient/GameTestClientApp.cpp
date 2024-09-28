#include "stdafx.h"

#include <conio.h>
#include <iostream>
#pragma warning(push)
#pragma warning( disable : 4251)
#include <ace/ACE.h>
#include <ace/Get_Opt.h>

#include <Network/Initializer.h>
#include <Network/Transport.h>
#include <Network/TransportInitializer.h>
#include <Network/TransportMessages.h>
#include <transport/TLTransportModule.h>
#include <transport/TLCfg.h>
#include <transport/TLDefaultLogCallback.h>
#include <mballocator/MessageBlockFactory.h>

#include <System/ServerStdOutDumper.h>
#include <System/TextFileDumper.h>
#include <System/FileSystem/FileUtils.h>
#include <System/LogFileName.h>
#include <System/BSUtil.h>
#include "System/CrashRptWrapper.h"
#include "System/ConfigFiles.h"

#include "Server/LogMonitorAgent/LogMonitorAgent.h"
#include "Server/LogMonitorAgent/LogMonitorConfig.h"

#include "ReplayCmdFeeder.h"
#include "GameTestClient_Lobby.h"
#include "GameTestClient_TestMM.h"
#include "GameTestClient_Other.h"
#include "GameTestClient_ExtProc.h"
#include "GameTestClient_Roll.h"
#include "StatSvcTestClient.h"
#include "TestSocialMasterClient.h"
#include "TestSocialClient.h"
#include "GTCLog.h"
#include "System/SyncProcessorState.h"
#pragma warning(pop)
#include "Version.h"
#include "System/InlineProfiler.h"
#ifdef NI_ENABLE_INLINE_PROFILER
#include <conio.h>
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"
#include "System/JobThread.h"
#endif //NI_ENABLE_INLINE_PROFILER
#include "LagsStats.h"

#include "System/LoggingImpl.h" //TEMP

const nstl::string scenarioTestMm = "loadgamesrv";
const nstl::string scenarioSocial = "loadsocial";
const nstl::string scenario_login = "logintest";
const nstl::string scenarioReplay = "replaytest";
const nstl::string scenario_statistics = "gamestattest";
const nstl::string scenarioProdemu = "prodemu";
const nstl::string scenarioRoll = "roll";

namespace TestConfig {
  static const char* USER_NAMES[] = { "TestZ1", "TestZ2", "TestZ3", "TestZ4" };
  static const char* USER_PWDS[] = { "123123123", "123123123", "123123123", "123123123" };
  static const int USER_NAME_COUNT = sizeof(USER_NAMES) / sizeof(const char*);

//-- LIMITED SET user names (valid ZZima accs):
  const char* GetUserName_ZZima( int userId ) { return USER_NAMES[ userId % USER_NAME_COUNT ]; }

//-- HACKED user names (don't use name->userId map):
  const char* GetUserName_Hacked( int userId ) { return "GtcClient"; }

//-- UNLIMITED UNIQUE user names:
  char user_name_buf[32]; 
  const char* GetUserName_UniqueNumbered( int userId ) { sprintf_s(user_name_buf, 32, "user%d", userId); return user_name_buf; }

  const char* GetUserPwd( int userId ) { return USER_PWDS[ userId % USER_NAME_COUNT ]; }
};


struct GtcCfg
{
  static const int MAX_CLIENTS = 2000;

  GtcCfg() :
  enableCrashRpt(true),
  clients_(1),
  user_("_randori"),
  pUserNameFunc_(TestConfig::GetUserName_Hacked),
  baseUserNumber_(1000), // начиная с такого номера N присваиваются NUMBERED-имена вида "userN"
  transportVersion_(2),
  scenario_(scenarioTestMm),
  scenarioDurationInSec_(30*60),  //  30mins
  useTestMm( false ),
  maploadtime_( 10 ),
  extraSleep_(0),
  replayClientId_(1000),
  sorcvbuf_(-1),
  rcvbuf_(128 * 1024),
  sosndbuf_(-1),
  sendFreq_(4),
  sendSize_(0),
  lobbyTimeout_(0),
  traceStepConfirmation_(false),
  logGSStepLags(false),
  logEveryLagFromMs(0),
  chatMsgsInterval(0),
  transportLogLevel( 2 ),
  firstUdpPort( 38000 ),
  udpPortRange( 10000 )
  {}

  bool enableCrashRpt;
  nstl::string loginaddr_;
  nstl::string user_;
  nstl::string sessionKey_;
  int clients_;
  int transportVersion_;
  nstl::string scenario_;
  unsigned int scenarioDurationInSec_;
  bool useTestMm;
  int maploadtime_;

  nstl::string configFile_;

  nstl::string replayFile_;
  int replayClientId_;

  int sorcvbuf_;
  unsigned int rcvbuf_;
  int sosndbuf_;

  int sendFreq_;
  int sendSize_;

  bool traceStepConfirmation_;

  typedef const char* (*TUserNameFunc)(int);
  TUserNameFunc pUserNameFunc_;
  int baseUserNumber_;
  int extraSleep_;

  nstl::string pickupPath;
  int lobbyTimeout_;

  string liveClientExePath;

  bool logGSStepLags;
  int logEveryLagFromMs;

  int chatMsgsInterval;

  int transportLogLevel;

  unsigned firstUdpPort;
  unsigned udpPortRange;

  void print();
};

void GtcCfg::print()
{
  systemLog(NLogg::LEVEL_MESSAGE) 
    << "\n====================================" 
    << "\nGameTestClient config:"
    << "\nlogin address: " << loginaddr_ 
    << "\nusername/mode: " << user_
    << "\nsession key: " << sessionKey_
    << "\nnumber of clients: " << clients_ 
    << "\ntransport version: " << transportVersion_
    << "\nscenario: " << scenario_
    << "\nreplay file: " << replayFile_
    << "\nreplay client id: " << replayClientId_
    << "\nmap load timeout: " << maploadtime_
    << "\nSocial clients pickup path: " << pickupPath
    << "\nLobby service timeout: " << lobbyTimeout_
    << "\nScenario duration(sec): " << scenarioDurationInSec_
    << "\nConfig file: " << configFile_
    << "\n===================================="
    << endl;
}

/***********************************************
//Command-line samples:

Sipliest:
-l localhost:35001 -s prodemu --scenarioduration 15 -m 10 -c 1 --socialmmtype Maps/Multiplayer/MOBA/Training.ADMPDSCR --gatewayurl http://localhost:34000

Std PVP smoke:
-l localhost:35001 -s prodemu --scenarioduration 60 -m 10 -c 250 --socialmmtype /Maps/Multiplayer/MOBA/_.ADMPDSCR --gatewayurl http://localhost:34000

-first_udp_port 38000 -udp_port_range 10000
***********************************************/

void usage(char* /*module*/)
{
  systemLog(NLogg::LEVEL_MESSAGE) << "Usage:\n"
                                     "-c: number of clients (--clients). Ignored in 'loadsocial' scenario\n"
                                     "-h: this message (--help)\n"
                                     "-l: login address (--login)\n"
                                     "-m: map load time in seconds(--maploadtime)\n"
                                     "-r: replay client events file (--replay)\n"
                                     "-s: scenario type (--scenario):\n"
                                     "    -s loadgamesrv | loadsocial | prodemu | logintest | replaytest | gamestattest\n"
                                     "-t: transport version(1,2) (--transport)\n"
                                     "-u: user name/mode (--user)\n"
                                     "    -u ZZIMA: give each user a predefined valid ZZima login, on round robin basis\n"
                                     "    -u NUMBERED_X: give each user a unique sequenced name, starting with seq. number X\n"
                                     "-k: game session key\n"
                                     "-x: eXtra sleep after each client, win7 startup hack (--extra)\n"
                                     "-y: replaY client id (--replayclient)\n"
                                     "-g: config to load (--config):\n"
                                     "--rcvbuf: read buffer size\n"
                                     "--sorcvbuf: system read buffer size(SO_RCVBUF)\n"
                                     "--sosndbuf: system send buffer size{SO_SNDBUF}\n"
                                     "--sndfreq: send data frequency in steps (for loadgamesrv scenario)\n"
                                     "--sndsize: send data size for each send step(for loadgamesrv scenario)\n"
                                     "--tracestepconfirm: trace step confirmation which client send back to server\n"
                                     "--sessionlogin: session login formatted like in PF_Game.exe\n"
                                     "--socpickupdir: directory from wich pick up new social clients\n"
                                     "--lobbytimeout: timeout for client operations with lobby service\n"
                                     "--scenarioduration: scenario duration in sec\n"
                                     "--socialmmtype: social matchmaking type (pvp, train, pvp1x1, pvp2x2, pvp5x5\n"
                                     "--gatewayurl: social http gateway URL; Or use RPC access instead\n"
                                     "--socspawnrate: spawn rate of social clients, default is 10 per seconds\n"
                                     "--dumpjson: Dump JSON requests to log, forces JSON to be formatted in human-readable style\n"
                                     "--maxjsonrequest: Limit number of JSON-items per single HTTP request\n"
                                     "--maxparty: Maximum party size in 'prodemu' scenario, 2...5\n"
                                     "--partyfreq: Party requests frequency in 'prodemu' scenario, 0...100\n"
                                     "--nocrashrpt: Disable crash handling and reporting\n"
                                     "--liveclientpath: Launch PW_Game.exe instead of internal test client\n"
                                     "--locales: set bots locales, e.g \"ru/tr\"\n"
                                     "--locations: set bots locations, e.g \"ru0/ru1/tr\"\n"
                                     "--logsteplags: write to log game server step lags\n"
                                     "--logeverylagms: write to log every lag which is longer than specified time (in ms)\n"
                                     "--chatmsginterval: interval between messages to chat (in game steps)\n"
                                     "Example: GameTestClientApp.exe -l localhost:35001 -c 100 -s loadgamesrv -m 0\n"
                                     "         GameTestClientApp.exe --login localhost:35001 --scenario loadsocial --scenarioduration 300 -m 10 --sessionlogin loginaddress/login/baadf00d\n"
                                     "         GameTestClientApp.exe --login localhost:35001 --scenario loadsocial --socpickupdir .\\pickup\n"
                                     "         GameTestClientApp.exe -l localhost:35001 -s prodemu --scenarioduration 60 -m 10 -c 100 --socialmmtype Maps/Multiplayer/PFmap/PVP.ADMPDSCR --gatewayurl http://localhost:34000\n"
                                     "         GameTestClientApp.exe -l localhost:35001 -s prodemu -c 2 --socialmmtype Maps/Test/PlaneMap/Test_PVP_1x1.ADMPDSCR --gatewayurl http://localhost:34000 --liveclientpath C:/pw/PvX/Bin/PW_Game.exe\n"
                                     "         GameTestClientApp.exe -l localhost:35001 -s roll -c 10\n";
}



bool ParseSessionKey( string & _loginAddr, string & _username, string & _key, const char * _sessKey )
{
  const char separator = '/';

  const char * addrEnd = strchr( _sessKey, separator );
  if ( !addrEnd )
    return false;
  NI_ASSERT( addrEnd[0], "" );

  const char * loginEnd = strchr( addrEnd + 1, separator );
  if ( !loginEnd )
    return false;
  NI_ASSERT( loginEnd[0], "" );

  _loginAddr = string( _sessKey, addrEnd - _sessKey );
  _username = string( addrEnd + 1, loginEnd - ( addrEnd + 1 ) );
  _key = string( loginEnd + 1 );
  return !_loginAddr.empty() && !_username.empty() && !_key.empty();
}



bool parse_args(int argc, char* argv[], GtcCfg & cfg, GtcSocial::SSocialConfig & socConfig )
{
  if (argc <= 1)
    return false;

  static const ACE_TCHAR options[] = ACE_TEXT ("c:hl:m:p:r:s:t:u:x:y:k:");
  ACE_Get_Opt get_opt (argc, argv, options, 1, 1);
  get_opt.long_option(ACE_TEXT ("nocrashrpt"), ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("clients"), 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("help"), 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("login"), 'l', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("maploadtime"), 'm', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("password"), 'p', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("replay"), 'r', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("scenario"), 's', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("transport"), 't', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("user"), 'u', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("extra"), 'x', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("replayclient"), 'y', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("sessionkey"), 'k', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("rcvbuf"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("sorcvbuf"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("sosndbuf"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("sndfreq"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("sndsize"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("tracestepconfirm"), ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("sessionlogin"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("socpickupdir"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("lobbytimeout"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("scenarioduration"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("socialmmtype"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("gatewayurl"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("socspawnrate"), ACE_Get_Opt::ARG_REQUIRED );
  get_opt.long_option(ACE_TEXT ("maxjsonrequest"), ACE_Get_Opt::ARG_REQUIRED );
  get_opt.long_option(ACE_TEXT ("dumpjson"), ACE_Get_Opt::NO_ARG );
  get_opt.long_option(ACE_TEXT ("maxparty"), ACE_Get_Opt::ARG_REQUIRED );
  get_opt.long_option(ACE_TEXT ("partyfreq"), ACE_Get_Opt::ARG_REQUIRED );  
  get_opt.long_option(ACE_TEXT ("liveclientpath"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("locales"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("locations"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("config"), 'g', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("logsteplags"), ACE_Get_Opt::NO_ARG);
  get_opt.long_option(ACE_TEXT ("logeverylagms"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("chatmsginterval"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("transport_log_level"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("first_udp_port"), ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option(ACE_TEXT ("udp_port_range"), ACE_Get_Opt::ARG_REQUIRED);

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

    case 'r':
      cfg.replayFile_ = get_opt.optarg;
      res = true;
      break;
    
    case 'g':
      cfg.configFile_ = get_opt.optarg;
      res = true;
      break;

    case 'c':
      {
        cfg.clients_ = ACE_OS::atoi(get_opt.optarg);
        if (cfg.clients_ <= 0 || cfg.clients_ > GtcCfg::MAX_CLIENTS)
        {
          systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
            << " wrong number of clients (min=1, max=" << GtcCfg::MAX_CLIENTS << ")" << endl;
        }
        else
          res = true;
      }
      break;

    case 'y':
      {
        cfg.replayClientId_ = ACE_OS::atoi(get_opt.optarg);
        if (cfg.replayClientId_ <= 0 )
        {
          systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() << " wrong client id (min=1)";
        }
        else
          res = true;
      }
      break;

    case 't':
      {
        cfg.transportVersion_ = ACE_OS::atoi(get_opt.optarg);
        if (cfg.transportVersion_ != 1 && cfg.transportVersion_ != 2)
        {
          systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
            << " wrong transport version(acceptable version: 1, 2)" << endl;
        }
        else
          res = true;
      }
      break;

    case 'u':
      cfg.user_ = get_opt.optarg;
      if ( cfg.user_ == "ZZIMA" )
        cfg.pUserNameFunc_ = TestConfig::GetUserName_ZZima;
      else if ( cfg.user_.substr(0, strlen("NUMBERED")) == "NUMBERED" )
      {
        cfg.pUserNameFunc_ = TestConfig::GetUserName_UniqueNumbered;
        string baseNum = cfg.user_.substr( strlen("NUMBERED")+1 );
        cfg.baseUserNumber_ = NStr::ToInt( baseNum.c_str() );
      }
      res = true;
      break;

    case 'x':
      cfg.extraSleep_ = ACE_OS::atoi(get_opt.optarg);
      res = true;
      break;

    case 'p':
      //UNUSED
      //cfg.pswd_ = get_opt.optarg;
      res = true;
      break;

    case 'k':
      cfg.sessionKey_ = get_opt.optarg;
      res = true;
      break;

    case 's':
      cfg.scenario_ = get_opt.optarg;
      // replay умеет исполняться на стадии Stage::GAME обычного hybrid_server_test
      cfg.useTestMm = ( cfg.scenario_ == scenarioTestMm ) || ( cfg.scenario_ == scenarioReplay );
      res = true;
      break;

    case 'm':
      cfg.maploadtime_ = ACE_OS::atoi(get_opt.optarg);
      if (cfg.maploadtime_ < 0)
      {
        systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
          << " map load time < 0" << endl;
        res = false;
      }
      else
        res = true;
      break;

    case ':':
      systemLog(NLogg::LEVEL_MESSAGE) << "-" << (char)get_opt.opt_opt() 
        << " requires an argument" << endl;
      break;

    case 0:
      {
        ACE_TCHAR const * longoptname = get_opt.long_option();
        if ( !ACE_OS::strcmp( longoptname, "nocrashrpt" ) )
        {
          cfg.enableCrashRpt = false;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "sorcvbuf"))
        {
          cfg.sorcvbuf_ = ACE_OS::atoi(get_opt.optarg);
          res = true;
        }
        else
        if (!ACE_OS::strcmp(longoptname, "rcvbuf"))
        {
          int val = ACE_OS::atoi(get_opt.optarg);
          if (val >= 0)
          {
            cfg.rcvbuf_ = unsigned int(val); 
            res = true;
          }
        }
        else
        if (!ACE_OS::strcmp(longoptname, "sosndbuf"))
        {
          cfg.sosndbuf_ = ACE_OS::atoi(get_opt.optarg);
          res = true;
        }
        else
        if (!ACE_OS::strcmp(longoptname, "sndfreq"))
        {
          cfg.sendFreq_ = ACE_OS::atoi(get_opt.optarg);
          if (cfg.sendFreq_ <= 0)
            LOG_C(0) << "sndfreq have to be more then 0";
          else
            res = true;
        }
        else
        if (!ACE_OS::strcmp(longoptname, "sndsize"))
        {
          cfg.sendSize_ = ACE_OS::atoi(get_opt.optarg);
          if (cfg.sendSize_ <= 0)
            LOG_C(0) << "sndsize have to be more then 0";
          else
            res = true;
        }
        else
        if (!ACE_OS::strcmp(longoptname, "tracestepconfirm"))
        {
          cfg.traceStepConfirmation_ = true;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "sessionlogin"))
        {
          string loginAddr, username, key;
          res = ParseSessionKey( loginAddr, username, key, get_opt.optarg );
          if ( res )
          {
            cfg.loginaddr_ = loginAddr;
            cfg.user_ = username;
            cfg.pUserNameFunc_ = 0;
            cfg.sessionKey_ = key;
          }
        }
        else if (!ACE_OS::strcmp(longoptname, "socpickupdir"))
        {
          cfg.pickupPath = get_opt.optarg;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "lobbytimeout"))
        {
          cfg.lobbyTimeout_ = ACE_OS::atoi(get_opt.optarg);
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "scenarioduration"))
        {
          int sessionDuration = ACE_OS::atoi(get_opt.optarg);
          if (sessionDuration >= 0)
          {
            cfg.scenarioDurationInSec_ = sessionDuration;
            res = true;
          }
        }
        else if (!ACE_OS::strcmp(longoptname, "socialmmtype"))
        {
          socConfig.map = get_opt.optarg;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "gatewayurl"))
        {
          socConfig.gatewayUrl = get_opt.optarg;
          res = true;
        }
        else if ( !ACE_OS::strcmp( longoptname, "socspawnrate" ) )
        {
          int rate = ACE_OS::atoi( get_opt.optarg );
          if ( rate >= 1 ) {
            socConfig.spawnRate = rate;
            res = true;
          }
          else
            res = false;
        }
        else if ( !ACE_OS::strcmp( longoptname, "dumpjson" ) )
        {
          socConfig.dumpJson = true;
          socConfig.prettyJson = true;
          res = true;
        }
        else if ( !ACE_OS::strcmp( longoptname, "maxjsonrequest" ) )
        {
          int maxreq = ACE_OS::atoi( get_opt.optarg );
          if ( maxreq >= 1 ) {
            socConfig.jsonItemsPerRequest = maxreq;
            res = true;
          }
          else
            res = false;
        }
        else if ( !ACE_OS::strcmp( longoptname, "maxparty" ) )
        {
          int m = ACE_OS::atoi( get_opt.optarg );
          if ( m >= 2 && m <= 5 ) {
            socConfig.maxPartySize = m;
            res = true;
          }
          else
            res = false;
        }
        else if ( !ACE_OS::strcmp( longoptname, "partyfreq" ) )
        {
          float f = ACE_OS::atof( get_opt.optarg );
          if ( f >= 0.0f && f <= 100.0f ) {
            socConfig.partyFrequency = f;
            res = true;
          }
          else
            res = false;
        }
        else if (!ACE_OS::strcmp(longoptname, "liveclientpath"))
        {
          cfg.liveClientExePath = get_opt.optarg;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "locales"))
        {
          NStr::SplitString( get_opt.optarg, &socConfig.botLocales, '/' );
          res = !socConfig.botLocales.empty();
        }
        else if (!ACE_OS::strcmp(longoptname, "locations"))
        {
          NStr::SplitString( get_opt.optarg, &socConfig.botLocations, '/' );
          res = !socConfig.botLocations.empty();
        }
        else if (!ACE_OS::strcmp(longoptname, "logsteplags"))
        {
          cfg.logGSStepLags = true;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "logeverylagms"))
        {
          cfg.logGSStepLags = true;
          int ms = ACE_OS::atoi( get_opt.optarg );
          if (ms > 0)
            cfg.logEveryLagFromMs = ms;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "chatmsginterval"))
        {
          cfg.logGSStepLags = true;
          int steps = ACE_OS::atoi( get_opt.optarg );
          if (steps > 0)
            cfg.chatMsgsInterval = steps;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "transport_log_level"))
        {
          int lvl = ACE_OS::atoi( get_opt.optarg );
          if ( ( lvl >= 0 ) && ( lvl <= 2 ) )
            cfg.transportLogLevel = lvl;
          res = true;
        }
        else if (!ACE_OS::strcmp(longoptname, "first_udp_port"))
        {
          int m = ACE_OS::atoi( get_opt.optarg );
          if ( m >= 1000 && m <= 65000 ) {
            cfg.firstUdpPort = m;
            res = true;
          }
          else
            res = false;
        }
        else if (!ACE_OS::strcmp(longoptname, "udp_port_range"))
        {
          int m = ACE_OS::atoi( get_opt.optarg );
          if ( m >= 1 && m <= 32000 ) {
            cfg.udpPortRange = m;
            res = true;
          }
          else
            res = false;
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


class TestClients : public gtc::IClientsContainer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(TestClients, gtc::IClientsContainer, BaseObjectMT);

public:
  typedef StrongMT<gtc::IGameTestClient> ClientPtrT;
  typedef nstl::vector<ClientPtrT> ClientsT;
  typedef nstl::vector<StrongMT<GameTestClient2::ClientBase> > BaseClientsT;

  StrongMT<Network::INetworkDriver>   pDriver;
  naio::DriverSP                      pNaioDriver;
  ClientsT                            clients;
  int                                 nextLocalClientId;
  timer::Time                         nextPickupTime;

  BaseClientsT                        baseClients;
  GameTestClient2::EventsScheduleT    statEventSchedule;

  StrongMT<GtcSocial::SocialMasterClient> socialMasterClient;

  TestClients() : nextLocalClientId( 0 ), nextPickupTime( 0 ) {}

  gtc::LagsStatsContainer & GetLagsStatsContainer() { return lagsStats; }

private:
  gtc::LagsStatsContainer lagsStats;

public:
  bool Init( const GtcCfg & _cfg, const GtcSocial::SSocialConfig & _socConfig, Network::INetworkDriver * _driver, naio::IProtocolHandlerFactory * _phf, Transport::MessageFactory * _mf )
  {
    pDriver = _driver;

    if (_cfg.logGSStepLags)
      lagsStats.Init();

    if ( _cfg.transportVersion_ == 2 )
      InitTransport2( _cfg, _phf );

    if ( _cfg.scenario_ == scenarioProdemu )
    {
      string user = _cfg.pUserNameFunc_ ? _cfg.pUserNameFunc_( 1 + _cfg.baseUserNumber_ ) : _cfg.user_;
      string pass = _cfg.sessionKey_.empty() ? TestConfig::GetUserPwd( 1 ) : string();
      socialMasterClient = new GtcSocial::SocialMasterClient( pDriver, CreateTranspMod( _mf, _cfg ), _cfg.loginaddr_, user, pass, _cfg.clients_, _socConfig, _cfg.firstUdpPort, _cfg.udpPortRange );
      return true;
    }
    else  if ( _cfg.scenario_ == scenarioSocial )
    {
      if ( !_cfg.sessionKey_.empty() && _cfg.pickupPath.empty() )
      {
        MessageTrace( "Starting SINGLE social client with key '%s'", _cfg.sessionKey_.c_str() );
        CreateClientInstance( _cfg, 1, _cfg.loginaddr_, _cfg.user_, string(), _cfg.sessionKey_, _mf, 0 );
      }
      else if ( !_cfg.pickupPath.empty() && _cfg.sessionKey_.empty() )
      {
        MessageTrace( "Waiting oncoming social clients from folder '%s'", _cfg.pickupPath.c_str() );
      }
      else
      {
        MessageTrace( "Only single session login OR social pickup folder can be specified!" );
        return false;
      }
      //empty
    }
    else if ( _cfg.scenario_ == scenario_statistics )
    {
      GameTestClient2::EventFreqT evtFreq;
      evtFreq.resize(SessionEventType::NumberOfEvents + 2);

      evtFreq[SessionEventType::Deed] = 11;
      evtFreq[SessionEventType::KillAssist] = 5;
      evtFreq[SessionEventType::BuildingDestroyed] = 2;
      evtFreq[SessionEventType::ConsumableBought] = 3;
      evtFreq[SessionEventType::ConsumableUsed] = 3;
      evtFreq[SessionEventType::HeroDeath] = 5;
      evtFreq[SessionEventType::FlagPoleDropped] = 7;
      evtFreq[SessionEventType::FlagPoleRaised] = 8;
      evtFreq[SessionEventType::ImpulsiveBuffUsed] = 2;
      evtFreq[SessionEventType::HeroKill] = 10;
      evtFreq[SessionEventType::LevelUp] = 20;
      evtFreq[GameTestClient2::StatSvcTestClient::DamageEvt] = 266;
      evtFreq[GameTestClient2::StatSvcTestClient::DebugVarEvt] = 974;

      GameTestClient2::GenerateEventSchedule(evtFreq, _cfg.scenarioDurationInSec_*1000, 100, statEventSchedule);

      for ( int i = 0; i < _cfg.clients_; ++i )
      {
        string username = _cfg.pUserNameFunc_ ? _cfg.pUserNameFunc_( i + _cfg.baseUserNumber_ ) : _cfg.user_;
        string password = _cfg.sessionKey_.empty() ? TestConfig::GetUserPwd( i ) : string();

        StrongMT<GameTestClient2::ClientBase> cli = 
          new GameTestClient2::StatSvcTestClient(_cfg.scenarioDurationInSec_*10, statEventSchedule, i, pDriver, CreateTranspMod( _mf, _cfg ), 100, 
          _cfg.loginaddr_, username, password, _cfg.sessionKey_);
        baseClients.push_back(cli);
      }
    }
    else
    {
      for ( int i = 0; i < _cfg.clients_; ++i )
      {
        string username = _cfg.pUserNameFunc_ ? _cfg.pUserNameFunc_( i + _cfg.baseUserNumber_ ) : _cfg.user_;
        string password = _cfg.sessionKey_.empty() ? TestConfig::GetUserPwd( i ) : string();
        CreateClientInstance( _cfg, nextLocalClientId++, _cfg.loginaddr_, username, password, _cfg.sessionKey_, _mf, 0 );
      }
    }

    return true;
  }


private:
  bool InitTransport2( const GtcCfg & _cfg, naio::IProtocolHandlerFactory * _phf )
  {
    NI_ASSERT( pNaioDriver == 0, "" );

    naio::DriverSP pDrv( new naio::Driver );
    naio::LogMsgCallbackSP pLogCb( new TL::LogCallback(::GetSystemLog() ) );

    naio::Cfg naiocfg;
    naiocfg.loglvl_ = _cfg.transportLogLevel;
    naiocfg.terabit_loglvl_ = _cfg.transportLogLevel;
    naiocfg.spLogMsgCb_ = pLogCb;
    naiocfg.phf_ = _phf;
    naiocfg.read_block_size_= _cfg.rcvbuf_;
    naiocfg.so_rcvbuf_ = _cfg.sorcvbuf_;
    naiocfg.so_sndbuf_ = _cfg.sosndbuf_;
    naiocfg.checkActivityTimeout_ = 20;

    if ( pDrv->Init( naiocfg ) )
    {
      pNaioDriver = pDrv;
      return true;
    }

    return false;
  }


private:
  StrongMT<TL::TransportModule> CreateTranspMod( Transport::MessageFactory * _mf, const GtcCfg & _cfg ) {
    if ( pNaioDriver != 0 ) { //Transport 2
      TL::Cfg tlcfg;
      tlcfg.mf_ = _mf;
      tlcfg.mbHeapDumpFreq_ = 1000000;
      tlcfg.loglvl_ = _cfg.transportLogLevel;
      tlcfg.terabit_loglvl_ = _cfg.transportLogLevel;
      //tlcfg.packAddress_ = true;
      StrongMT<TL::TransportModule> pTranspMod = new TL::TransportModule;
      if ( pTranspMod->Init( tlcfg, pNaioDriver ) )
        return pTranspMod;
    }
    return 0;
  }



  StrongMT<gtc::IGameTestClient> CreateClientInstance( const GtcCfg & _cfg, int index, const string & _loginAddr, const string & _username, const string & _password, const string & _sessionKey, Transport::MessageFactory * _mf, int _gameId )
  {
    gtc::TestClientBaseParams params( index, pDriver, _loginAddr, _username, _password, 
      _cfg.sendFreq_, _cfg.sendSize_, _cfg.maploadtime_, CreateTranspMod( _mf, _cfg ), _sessionKey,
      _cfg.traceStepConfirmation_, _cfg.logGSStepLags, _cfg.logEveryLagFromMs, _cfg.chatMsgsInterval, _cfg.firstUdpPort + 1, _cfg.udpPortRange, this );

    StrongMT<gtc::IGameTestClient> c;

    if ( _cfg.scenario_ == scenario_login )
      c = new gtc::Client_Login( params );
    else if ( _cfg.scenario_ == scenarioTestMm )
    {
      StrongMT<gtc::Client_TestMm> testmmcl = new gtc::Client_TestMm( params );
      if ( _cfg.scenarioDurationInSec_ )
        testmmcl->SetupGameFinish( _cfg.scenarioDurationInSec_ );
      c = testmmcl;
    }
    else if ( _cfg.scenario_ == scenarioRoll )
      c = new gtc::Client_Roll( params );
    else if ( ( _cfg.scenario_ == scenarioProdemu ) || ( _cfg.scenario_ == scenarioSocial ) )
    {
      if ( _cfg.liveClientExePath.empty() )
      {
        StrongMT<gtc::Client_Lobby> lobbycl = new gtc::Client_Lobby( params );
        if ( _cfg.scenarioDurationInSec_ )
          lobbycl->SetupGameFinish( _cfg.scenarioDurationInSec_ + _cfg.scenarioDurationInSec_ * ( _gameId % 10 ) / 50 );
        c = lobbycl;
      }
      else {
        string combinedSessKey = _loginAddr + "/" + _username + "/" + _sessionKey;
        c = new gtc::Client_ExtProc( _cfg.liveClientExePath.c_str(), combinedSessKey.c_str() );
      }
    }
    else if ( _cfg.scenario_ == scenarioReplay )
    {
      StrongMT<gtc::Client_Replay> replcl = new gtc::Client_Replay( params );
      replcl->LoadReplay( _cfg.replayFile_.c_str(), _cfg.replayClientId_ );
    }
    else
      NI_ALWAYS_ASSERT( NI_STRFMT( "Unknown scenario '%s'", _cfg.scenario_ ) );

    clients.push_back( c );
    return c;
  }

  StrongMT<gtc::IGameTestClient> CreateClientInstanceSocial( const GtcCfg & _cfg, const char * _combinedSessionKey, Transport::MessageFactory * _mf, int _gameId )
  {
    string loginAddr, username, key;
    if ( !ParseSessionKey( loginAddr, username, key, _combinedSessionKey ) ) {
      ErrorTrace( "Failed to parse session login '%s'", _combinedSessionKey );
      return 0;
    }

    MessageTrace( "Adding social client: %s / %s / %s...", loginAddr.c_str(), username.c_str(), key.c_str() );
    StrongMT<gtc::IGameTestClient> c = CreateClientInstance( _cfg, nextLocalClientId++, loginAddr, username, string(), key, _mf, _gameId );
    return c;
  }


private:
  void dump_debug_info( timer::Time & nextDumpTime )
  {
    NI_PROFILE_FUNCTION;

    timer::Time now = timer::Now();
    
    if ( now < nextDumpTime )
      return;
    nextDumpTime = now + 15;

    LOG_M( GameTestClient::StatusChannel ) << "-------------------------";
    LOG_M( GameTestClient::StatusChannel ).Trace( "Clients: %d social, %d pvx", socialMasterClient ? socialMasterClient->SocialClientsCount() : 0, clients.size() );

    NLogg::SCounters cnt = GetSystemLog().GetCounters();
    LOG_M( GameTestClient::StatusChannel ).Trace( "Error counters: %d warnings, %d errors, %d asserts, %d criticals", cnt.warnings, cnt.errors, cnt.asserts, cnt.criticals );

    if ( socialMasterClient ) {
      socialMasterClient->DumpStatistics();
      socialMasterClient->DumpStates();
      socialMasterClient->DumpStatesStatistics();
    }

    map<int, int> hysto;
    for( ClientsT::iterator it = clients.begin(); it != clients.end(); ++it )
      ++hysto[(*it)->Stage()];

    LOG_M( GameTestClient::StatusChannel ) << "Client stages distribution:";
    for ( map<int, int>::iterator it = hysto.begin(); it != hysto.end(); ++it )
      LOG_M( GameTestClient::StatusChannel ).Trace( "Stage %3d: %d", it->first, it->second );

    size_t virtualSize = 0;
    utils::GetMemoryStatus( virtualSize );
    LOG_M( GameTestClient::StatusChannel ).Trace( "Virtual Memory Usage: %u mb", virtualSize / ( 1024 * 1024 ) );

    int threads = utils::GetThreadCount();
    LOG_M( GameTestClient::StatusChannel ).Trace( "Total threads count: %d", threads );

    lagsStats.DumpLags();
  }



  void update_window_title( timer::Time & nextWindowTitleUpd )
  {
    NI_PROFILE_FUNCTION;

    timer::Time now = timer::Now();

    if( now < nextWindowTitleUpd )
      return;

    nextWindowTitleUpd = now + 2;

    nstl::string consoleTitle;
    consoleTitle.reserve( 512 );
    consoleTitle.append( NStr::StrFmt( "Clients (%d/%d)", socialMasterClient ? socialMasterClient->SocialClientsCount() : 0, clients.size() ) );

    if ( socialMasterClient )
      socialMasterClient->AppendStatesDebugText( consoleTitle );

    ::SetConsoleTitleA( consoleTitle.c_str() );
  }



  void dump_clients_stage_hysto2( time_t & nextDumpTime )
  {
    NI_PROFILE_FUNCTION;

    time_t now = 0;
    time( &now );

    if ( now < nextDumpTime )
      return;
    nextDumpTime = now + 10;

    map<int, int> hysto;
    for( BaseClientsT::iterator it = baseClients.begin(); it != baseClients.end(); ++it )
    {
      int stage = (*it)->stage();
      ++hysto[stage];

      //DAN
      if( stage == 2 )
        DebugTrace( "User not connected to relay: %s", (*it)->getUserName() );
    }

    nstl::string consoleTitle;
    consoleTitle.reserve(256);
    consoleTitle.append("Stages: ");
    DebugTrace( "Client stages distribution:" );
    for ( map<int, int>::iterator it = hysto.begin(); it != hysto.end(); ++it )
    {
      DebugTrace( "%s_%d(%d)", GameTestClient2::StatSvcTestClient::stageName(it->first), it->first, it->second );
      consoleTitle += NStr::StrFmt("%s(%d) ", GameTestClient2::StatSvcTestClient::stageName(it->first), it->second);
    }

    ::SetConsoleTitleA(consoleTitle.c_str());
  }



public:
  void run_hybridserver_test( const GtcCfg & _cfg, Transport::MessageFactory * _mf )
  {
    NI_PROFILE_FUNCTION;

    timer::Time nextDumpTime = 0, nextWindowTitleUpd = 0;
    timer::Time lastPoll = timer::Now();
    while ( true )
    {
      ::Sleep(1);

      timer::Time now = timer::Now();
      timer::Time pollDuration = now - lastPoll;
      lastPoll = now;

      if ( pollDuration > 1.0 )
        WarningTrace( "GTC poll time exceeded: %d", pollDuration );

      NI_PROFILE_BLOCK_MEM( "Iteration" );

      //TODO: Move next code to SocialMasterClient::Poll ?
      if ( ( _cfg.scenario_ == scenarioSocial ) && !_cfg.pickupPath.empty() )
        PickUpNewClientsFromFiles( _cfg, _mf );

      PollSocialClients( _cfg, _mf );

      for( ClientsT::iterator it = clients.begin(); it != clients.end(); )
      {
        StrongMT<gtc::IGameTestClient> cl = it->Get();
        if ( cl->MainStep().Ok() )
          ++it;
        else
        {
          DebugTrace( "Removing test client. userId=%d, state=%d", cl->UserId(), cl->Stage() );
          it = clients.erase( it );
          if ( cl->SocialClient() )
            cl->SocialClient()->PvXClientTerminated();
        }
      }

      dump_debug_info( nextDumpTime );
      update_window_title( nextWindowTitleUpd );

      if ( clients.empty() ) {
        if ( !( ( _cfg.scenario_ == scenarioSocial ) || ( _cfg.scenario_ == scenarioProdemu ) ) )
          break;
        if ( _cfg.pickupPath.empty() && !socialMasterClient.Valid() )
          break;
      }
    }
  }


private:
  void PollSocialClients( const GtcCfg & _cfg, Transport::MessageFactory * _mf )
  {
    if ( !socialMasterClient ) 
      return;

    if ( socialMasterClient->Poll() < 0 )
      return;

    while ( true ) {
      StrongMT<GtcSocial::SocialClient> socCl = socialMasterClient->PopToPvx();
      if ( !socCl )
        break;

      string sessKey = socCl->SessionKey();
      StrongMT<gtc::IGameTestClient> cl = CreateClientInstanceSocial( _cfg, sessKey.c_str(), _mf, socCl->GameId() );

      socCl->PoppedToPvX( cl );

      cl->SetSocialClient( socCl );
    }
  }


  bool PickUpNewClientsFromFiles( const GtcCfg & _cfg, Transport::MessageFactory * _mf )
  {
    timer::Time t = timer::Now();
    if ( t < nextPickupTime )
      return true;
    nextPickupTime = t + 0.25;

    NI_PROFILE_FUNCTION;

    if ( !NFile::DoesFolderExist( _cfg.pickupPath ) )
      return false;

    string searchPath = NFile::Combine( _cfg.pickupPath, "*.pw.sess.key" );

    for ( NFile::CFileIterator it( searchPath ); !it.IsEnd(); ++it )
    {
      if ( it.IsDirectory() )
        continue;

      string filename = NFile::Combine( _cfg.pickupPath, it.GetFileName() );

      if ( FILE * f = fopen( filename.c_str(), "rt" ) )
      {
        int count = 0;
        while ( true )
        {
          char buf[256] = "";
          if ( fscanf( f, "%256s", buf ) != 1 )
            break;

          if ( !CreateClientInstanceSocial( _cfg, buf, _mf, 0 ) )
            break;

          ++count;
        }
        if ( !count )
          ErrorTrace( "File '%s' does not contain any valid sessionLogins!", filename.c_str() );

        fclose( f );
        DeleteFile( filename.c_str() );
      }
    }

    return true;
  }



public:
  void run_common_test( const GtcCfg & _cfg )
  {
    int count = 0;
    do 
    {
      ::Sleep(10);

      NI_PROFILE_BLOCK_MEM( "Iteration" );

      count = 0;
      for(ClientsT::iterator it = clients.begin(); it != clients.end(); )
      {
        ClientPtrT pc = *it;
        if (pc->MainStep().Ok())
        {
          ++count;
          ++it;
        }
        else
          it = clients.erase(it);

        if ( _cfg.extraSleep_ > 0 )
          ::Sleep( _cfg.extraSleep_ );
      }
    }
    while (count);
  }

public:
  void run_statistics_test()
  {
    int count = 0;
    time_t nextHystoDump = 0;
    do 
    {
      ::Sleep(10);

      NI_PROFILE_BLOCK_MEM( "Statistics Test Cycle" );

      count = 0;
      for(BaseClientsT::iterator it = baseClients.begin(); it != baseClients.end(); )
      {
        StrongMT<GameTestClient2::ClientBase> pc = *it;
        int rc = pc->Step();
        if (rc>=0 && rc != GameTestClient2::Result::SCENARIO_FINISHED)
        {
          ++count;
          ++it;
        }
        else
        {
          it = baseClients.erase(it);
        }
      }

      dump_clients_stage_hysto2( nextHystoDump );
    }
    while (count);
  }
}; //class TestClients



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
    }
    profiler3ui::Shutdown();
  }
};

#endif //NI_ENABLE_INLINE_PROFILER


int main(int argc, char* argv[])
{
/*
  StrongMT<ni_log::IMain> mainLoger = new ni_log::Main;
  StrongMT<ni_log::Handle> logHandle = mainLoger->GetHandle();
  logHandle->info.Trace( "Test trace. x=%d, y=%d", 10, 20 );
*/

#ifdef NI_ENABLE_INLINE_PROFILER
  profiler3::GetControl()->Setup( profiler3::SSettings() );

  StrongMT<threading::JobThread> profilerUIKeyboardListener = new threading::JobThread( new ProfilerUIKeyboardListener, "ProfilerUIKeyboardListener" );

  NI_PROFILE_THREAD_NAMED( "main" );
#endif //NI_ENABLE_INLINE_PROFILER

//  rpc::EnableLog( 2 );

  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "GameTestClient", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  StrongMT<NLogg::CServerStdOutDumper> stdoutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );

  StrongMT<NLogg::BasicTextFileDumper> textLogDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "gtc" );

  StrongMT<NLogg::BasicTextFileDumper> statusChannelDumper = NLogg::BasicTextFileDumper::New( 0, GameTestClient::StatusChannel );
  GetSystemLog().AddChannel( GameTestClient::StatusChannel, statusChannelDumper, stdoutDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );

  GtcCfg cfg;
  GtcSocial::SSocialConfig socConfig;
  cfg.lobbyTimeout_ = NGlobal::GetVar("lobby_cl_svc_timeout", NGlobal::VariantValue(float(0.0))).GetFloat();
  if ( !parse_args( argc, argv, cfg, socConfig ) )
  {
    usage(argv[0]);
    return -1;
  }

  if (cfg.configFile_.size() > 0)
  {
    if (!NGlobal::ExecuteConfig( cfg.configFile_.c_str(), NProfile::FOLDER_GLOBAL ))
    {
      return -1;
    }
  }


  NI_ASSERT( !cfg.loginaddr_.empty(), "Login address is EMPTY!" );

  if ( cfg.enableCrashRpt ) {
    Sleep( 100 ); //UGLY: Let text file dumpers to create their files
    CrashRptWrapper::InstallForProcess( "http://SITE.com/upload/", true, false, "GameTestClient" );
    CrashRptWrapper::AddFileToReport( textLogDumper->FileName().c_str(), "GTC Log File" );
    CrashRptWrapper::AddFileToReport( statusChannelDumper->FileName().c_str(), "GTC Status Log File" );
  }

  //FIXME реализация Replay.cpp никак не годится для параллельного использования; кривой синглтон, жуткая "синхронизация" и т.п.
  // так что проигрывать replay разрешаем только в режиме "single client"
  if ( scenarioReplay == cfg.scenario_ )
  {
    LOG_W(0) << "Replay scenario: forcing single client mode.";
    cfg.clients_ = 1;
  }

  cfg.print();

  if ( cfg.enableCrashRpt ) {
    CrashRptWrapper::AddTagToReport( "GtcScenario", cfg.scenario_.c_str() );
    CrashRptWrapper::AddTagToReport( "GtcClients", NStr::StrFmt( "%d", cfg.clients_ ) );
    CrashRptWrapper::AddTagToReport( "GtcServer", cfg.loginaddr_.c_str() );
  }

  NGlobal::SetVar("lobby_cl_svc_timeout", float(cfg.lobbyTimeout_), STORAGE_NONE);

  StrongMT<logMonitor::AgentParallelPoller> logMonAgent = new logMonitor::AgentParallelPoller( new logMonitor::Agent( logMonitor::CreateConfigFromStatics(), "gtc" ) );

  StrongMT<Network::INetworkDriver> pDriver = Network::Initialize(Network::EDriverTrafficType::ExtraLight);
  Transport::MessageFactory msgFactory;
  Transport::RegisterMessages( &msgFactory );
  TL::ChannelFactory channelFactory_;
  TL::ProtocolHandlerFactory phFactory;
  phFactory.Init(&msgFactory, &channelFactory_, TL::MessageBlockFactorySP(new TL::MessageBlockFactory("default", 10000)));

  StrongMT<TestClients> clients = new TestClients();

  if ( clients->Init( cfg, socConfig, pDriver, &phFactory, &msgFactory ) )
  {
    if ( ( cfg.scenario_ == scenarioProdemu ) || ( cfg.scenario_ == scenarioSocial ) || ( cfg.scenario_ == scenarioTestMm ) )
    {
      clients->run_hybridserver_test( cfg, &msgFactory );
    }
    else if ( cfg.scenario_ == scenarioRoll )
    {
      clients->run_common_test( cfg );
    }
    else if ( cfg.scenario_ == scenario_login )
    {// логин-тест запускает "две волны" юзеров с одинаково генерящимися именами
      TestClients clients2; // такое же множество клиентов, для второго прохода
      if ( clients2.Init( cfg, socConfig, pDriver, &phFactory, &msgFactory ))
      {
        clients->run_common_test( cfg );

        ::Sleep( 200 ); // небольшая пауза между 1-й и 2-й волнами логинов

        clients2.run_common_test( cfg );
      }
    }
    else 
    if ( cfg.scenario_ == scenario_statistics )
    {
      clients->run_statistics_test();
    }      
    else
    {
      systemLog(NLogg::LEVEL_MESSAGE) << "Unknown scenario";
    }
  }

  if ( cfg.enableCrashRpt )
    CrashRptWrapper::UninstallFromProcess();

  return 0;
}
