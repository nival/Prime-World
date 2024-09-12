#include "stdafx.h"
#include "NivalServer.h"

#include "Network/ClusterConfiguration.h"

#include "ServerCfg.h"

#include "System/FileSystem/FileUtils.h"
#include "System/FileSystem/FilePath.h"
#include "System/ConfigFiles.h"


namespace Transport
{

NivalServer::NivalServer()
{
}



NivalServer::~NivalServer()
{
}



bool NivalServer::Startup( int argc, char* argv[] )
{
  LOG_M(0) << "First server address(not loopback): " << Network::GetHostIPByName("localhost", true) << endl;

  bool startAll = false;

  TStartList serversToStart;
  string currentCustomOption;
  TServerCmdLine serverCmdLine;

  bool paramParseRes = true;
  for ( int i = 1; paramParseRes && i < argc; ++i )
  {
    string arg = argv[i];
    NStr::ToLower( &arg );

    if ( arg == "coordinator" )
      SetStartCoordinator();
    else if ( arg == "all" )
      startAll = true;
    else if ( arg == "-netstat" )
      showNetStat = true;
    else if ( arg == "--svcpath" )
    {
      if (i+1 < argc)
      {
        ++i;
        svcpath.Assign(argv[i]);
        HostServer::Cfg::SetSvcPath(svcpath);
      }
      else
      {
        paramParseRes = false;
        LOG_C(0).Trace("Option '%s' requires a value", arg);
      }
    }
    else if (arg == "--config")
    {
      if (i+1 < argc)
      {
        ++i;
        string cfgpath = NProfile::GetFullFolderPath(NProfile::FOLDER_GLOBAL);
        NFile::AppendSlash(&cfgpath);
        cfgpath += argv[i];
        if (NFile::DoesFileExist(cfgpath))
        {
          NGlobal::ExecuteConfig(argv[i], NProfile::FOLDER_GLOBAL);
        }
        else
        {
          LOG_C(0) << "Option '" << arg << "': file '" << cfgpath << "' doesn't exist";
          paramParseRes = false;
        }
      }
      else
      {
        LOG_C(0).Trace("Option '%s' requires a value", arg);
        paramParseRes = false;
      }
    }
    else if ( ParseServiceSpawnDirective( serversToStart, arg ) )
    {
      //nothing
    }
    else if ( arg.substr(0, 2) == "--" ) {
      currentCustomOption = arg.substr( 2 ); // пропускаем все ключики вида "--option" вместе со следующими за ними значениями (это ключики для CCmdStr или чего-нибудь подобного)
      serverCmdLine[currentCustomOption] = string();
    }
    else if( !currentCustomOption.empty() ) {
      serverCmdLine[currentCustomOption] = arg;
      currentCustomOption.clear();
    }
    else
    {
      LOG_A(0) << "UNKNOWN service name '" << arg << "' in command line\n  NOTE: SERVICE OPTIONS SHOULD ONLY BE SET WITH CONFIG COMMAND 'add_service_option <name> <service>'";
      paramParseRes = false;
    }
  }

  if ( serversToStart.empty() && !IsStartCoordinator() && !startAll ) {
    SetStartCoordinator();
    startAll = true;
  }

  if (!paramParseRes)
  {
    LOG_C(0).Trace("Command line parsing is failed");
    return false;
  }

  if ( startAll )
  {
    serversToStart.clear();
    for ( ServiceSpawners::const_iterator it = Spawners().begin(); it != Spawners().end(); ++it )
      if ( !it->second->ServiceIsExternal() )
        serversToStart.push_back( ServiceStartupInfo( it->second ) );
  }

  string servicesStr = "";
  if ( IsStartCoordinator() )
    servicesStr += "Coordinator ";

  for ( TStartList::const_iterator it = serversToStart.begin(); it != serversToStart.end(); ++it )
    servicesStr += string( it->spawner->ServiceClass().c_str() ) + " ";

  // вырезаем номер порта координатора
  string ca = Network::GetCoordinatorAddress();
  if ( ca.find( ':' ) != string::npos )
    ca.erase( 0, ca.find( ':') + 1 );

  string serversStr = HostServer::Cfg::ClusterName() + ":" + ca + " " + servicesStr;

#if defined( NV_WIN_PLATFORM )
  DWORD processId = ::GetCurrentProcessId();
#elif defined( NV_LINUX_PLATFORM )
  DWORD processId = ::getpid();
#endif
  char strProcessId[16];
#if defined( NV_WIN_PLATFORM )
  itoa(processId, strProcessId, 10);
#elif defined( NV_LINUX_PLATFORM )
  snprintf(strProcessId, sizeof( strProcessId ), "%d", processId);
#endif
  serversStr += "[" + string(strProcessId) + "]";
  if (svcpath.size())
    serversStr += "[" + string(svcpath.c_str())+"]";

  string dumpServersStr = serversStr;
  systemLog( NLogg::LEVEL_MESSAGE ) << dumpServersStr;

#if defined( NV_WIN_PLATFORM )
  ::SetConsoleTitle(serversStr.c_str());
#endif

  if ( !NivalServerBase::Startup( serversToStart, serverCmdLine ) )
    return false;

  return true;
}



bool NivalServer::ParseServiceSpawnDirective( TStartList & serversToStart, const string & cmdLnOpt )
{
  vector<string> split;
  NStr::SplitString( cmdLnOpt, &split, '*' );

  if ( split.size() < 2 )
  {
    if ( StrongMT<IServiceSpawner> spawner = FindSvcSpawner( cmdLnOpt.c_str() ) )
    {
      serversToStart.push_back( ServiceStartupInfo( spawner, 1u ) );
      return true;
    }
    return false;
  }

  if ( split.size() != 2 )
    return false;

  TServiceId svcClass = split[0].c_str();
  StrongMT<IServiceSpawner> spawner = FindSvcSpawner( svcClass );
  if ( !spawner )
    return false;

  if ( !NStr::IsDecNumber( split[1] ) ) {
    ErrorTrace( "Wrong command-line syntax. Number of instances expected. Option: %s", cmdLnOpt );
    return false;
  }

  int instNum = instNum = NStr::ToULong( split[1] );
  if ( instNum < 1 ) {
    ErrorTrace( "Wrong command-line syntax. Invalid numbers of instances. Option: %s", cmdLnOpt );
    return false;
  }

  serversToStart.push_back( ServiceStartupInfo( spawner, (unsigned)instNum ) );
  return true;
}

} // namespace Transport
