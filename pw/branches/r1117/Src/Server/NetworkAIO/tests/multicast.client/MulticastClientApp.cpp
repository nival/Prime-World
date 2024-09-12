#include "stdafx.h"

#include <conio.h>
#include <iostream>
#pragma warning(push)
#pragma warning( disable : 4251)

#include <transport/TLTransportModule.h>
#include <transport/TLCfg.h>
#include <transport/TLDefaultLogCallback.h>

#include <System/ServerStdOutDumper.h>
#include <System/TextFileDumper.h>
#include <System/FileSystem/FileUtils.h>
#include <System/LogFileName.h>
#include <Network/Initializer.h>
#include <Network/TransportMessages.h>
#include <mballocator/MessageBlockFactory.h>

#include "MulticastClientCfg.h"
#include "MulticastClient.h"

void usage(char* /*module*/)
{
  systemLog(NLogg::LEVEL_MESSAGE) << "Usage:\n"
                                     "-h: this message (--help)\n"
                                     "-l: login address (--login)\n"
                                     "-u: user name (--user)\n"
                                     "--rcvbuf: read buffer size\n"
                                     "--sorcvbuf: system read buffer size(SO_RCVBUF)\n"
                                     "--sosndbuf: system send buffer size{SO_SNDBUF}\n";
}

int main(int argc, char* argv[])
{
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "MulticastClient", 0, 0, 0, 0, 0 );

  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );

  ScopedPtr<NLogg::BasicTextFileDumper> textLogDumper;
  Reset( textLogDumper, NLogg::BasicTextFileDumper::New( &GetSystemLog(), "multicast" ) );

  MulticastTest::MulticastCfg cfg;
  if (!cfg.parse_args(argc, argv))
  {
    usage(argv[0]);
    return -1;
  }
  cfg.print();

  StrongMT<Network::INetworkDriver> pDriver = Network::Initialize(Network::EDriverTrafficType::ExtraLight);
  Transport::MessageFactory msgFactory;
  Transport::RegisterMessages( &msgFactory );
  TL::ChannelFactory channelFactory_;
  TL::ProtocolHandlerFactory phFactory;
  phFactory.Init(&msgFactory, &channelFactory_, TL::MessageBlockFactorySP(new TL::MessageBlockFactory("default", 10000)));

  StrongMT<MulticastTest::MulticastClient> mc = new MulticastTest::MulticastClient(pDriver, 0, cfg.loginaddr_, cfg.user_);

  int rc = 0;
  do 
    rc = mc->Step();
  while(rc >= 0);

  return rc;
}
