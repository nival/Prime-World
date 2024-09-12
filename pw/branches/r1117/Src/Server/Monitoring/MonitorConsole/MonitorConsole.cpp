#include "stdafx.h"
#include "MonThriftClient.h"
#include "System/ServerStdOutDumper.h"
#include "System/TextFileDumper.h"
#include <conio.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace Monitoring;

void usage()
{
  LOG_M(0).Trace("Usage:\nMonitorConsole.exe --server localhost:8707\nMonitorConsole.exe -s localhost:8707");
}

int main(int argc, char** argv)
{
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "MonitorConsole", "private", 0, 0, 0, 0);

  StrongMT<NLogg::CServerStdOutDumper> stdoutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );
  StrongMT<NLogg::BasicTextFileDumper> textLogDumper = NLogg::BasicTextFileDumper::New( &GetSystemLog(), "output" );

  NBSU::InitUnhandledExceptionHandler();

  if (1 == argc)
  {
    usage();
    return 1;
  }

  WSADATA wsaData = { 0 };
  ::WSAStartup( MAKEWORD( 2, 2 ), &wsaData );

  MonThriftClientCfg cfg;
  bool parse = true;
  for ( int i = 1; parse && i < argc; ++i )
  {
    if (0 == strcmp(argv[i],"--server") ||
        0 == strcmp(argv[i],"-s") )
    {
      ++i;
      if (i < argc)
      {
        cfg.addr = Network::Address(argv[i]);
        LOG_M(0).Trace("Server address: %s:%d", cfg.addr.GetIp(), cfg.addr.GetPort());
      }
      else
      {
        LOG_E(0).Trace("Option %s require an argument", argv[i-1]);
        parse = false;
      }
    }
    else
    {
      LOG_E(0).Trace("Unknown option %s", argv[i]);
      parse = false;
    }
  }

  if (parse)
  {
    int rc = -1;
    StrongMT<MonThriftClient> mtc(new MonThriftClient);
    rc = mtc->open(cfg);
    if (rc < 0)
    {
      LOG_E(0) << "Can't open monitor thrift client with code: " << rc;
      return rc;
    }

    int ch = 0;
    do
      ch = getch();
    while (ch != 'Q');

    mtc->close();
  }
  else
  {
    usage();
  }

  system("pause");
  ::WSACleanup();

  GetSystemLog().ClearAllDumpers();

  return 0;
}
