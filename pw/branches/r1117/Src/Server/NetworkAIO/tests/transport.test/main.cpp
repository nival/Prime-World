#include "transport/TLTransportModule.h"
#include "transport/TLCfg.h"
#include "naio/Types.h"
#include <transport/TLDefaultLogCallback.h>
#include <Network/AddressTranslator.h>
#include <Network/TransportMessages.h>
#include <System/StdOutDumper.h>
#include <System/TextFileDumper.h>
#include <System/FileSystem/FileUtils.h>
#include <System/LogFileName.h>
#include <System/Pointers/Strong.h>
#include <mballocator/MessageBlockFactory.h>
#include <conio.h>


class LocalAddressResolver : public Transport::IAddressTranslator
{
  Network::NetAddress GetNetworkAddress( const Transport::TServiceId& service )
  {
    return Network::NetAddress("localhost:35001");
  }
};

bool OpenSendCloseChannel(TL::TransportModule* tm)
{
  Transport::Address taddr;
  taddr.target = "relay";
  StrongMT<Transport::IChannel>  chnl = tm->OpenChannelDirect(taddr, "", "localhost:35001");
  if (!chnl)
    return 1;

  while(chnl->GetStatus() == Network::ConnectionState::Connecting)
    ::Sleep(100);

  if (chnl->GetStatus() == Network::ConnectionState::Connected)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << "Connected" << endl;
  }
  else
  if (chnl->GetStatus() == Network::ConnectionState::Closed)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << "Can't connect" << endl;
    return 1;
  }

  unsigned char data[] = "HELLO";
  chnl->SendRaw(&data[0], sizeof(data));

  int ch = 0;
  while ((ch = _getch()) != 'P');

  chnl->Close();

  return true;
}

bool OpenChannels(TL::TransportModule* tm, unsigned int n)
{
  Transport::Address taddr;
  taddr.target = "relay";

  unsigned int num = n;

  typedef list<StrongMT<Transport::IChannel>> ChannelsT;
  ChannelsT channels;
  ChannelsT newchannels;
  do
  {
    StrongMT<Transport::IChannel>  chnl = tm->OpenChannelDirect(taddr, "", "localhost:35001");
    if (!chnl)
      break;

    newchannels.push_back(chnl);
  }
  while (--num);

  bool epicfail = false;
  unsigned int i = 0;
  do 
  {
    StrongMT<Transport::IChannel>  chnl = newchannels.front();
    {
      while (chnl->GetStatus() == Network::ConnectionState::Connecting)
        ::Sleep(100);

      if (chnl->GetStatus() == Network::ConnectionState::Connected)
      {
        systemLog(NLogg::LEVEL_MESSAGE) << "Connected" << endl;
        ++i;
        channels.push_back(chnl);
      }
      else
      if (chnl->GetStatus() == Network::ConnectionState::Closed)
      {
        systemLog(NLogg::LEVEL_MESSAGE) << "Can't connect" << endl;
        epicfail = true;
      }
    }
    newchannels.pop_front();
  }
  while (!epicfail && i != n);

  if (epicfail)
    return false;

  for (ChannelsT::iterator it = channels.begin(); it != channels.end(); ++it)
  {
    unsigned char data[] = "HELLO";
    (*it)->SendRaw(&data[0], sizeof(data));
  }

  int ch = 0;
  while ((ch = _getch()) != 'P');

  for (ChannelsT::iterator it = channels.begin(); it != channels.end(); ++it)
  {
    (*it)->Close();
  }

  return true;
}

class ClientContext : public CObjectBase
{
  OBJECT_BASIC_METHODS(ClientContext);

public:
  struct Stage
  {
    enum
    {
      NONE = 0,
      INVALID,
      OPEN_CHANNEL_STARTED,
      OPEN_CHANNEL_FINISHED,
      SEQUENCE_PACKET_SENT,
      SEQUENCE_PACKET_RECEIVED,
      //REQ_MATCH_MAKING_MANAGER_STARTED = 4,
      //REQ_MATCH_MAKING_MANAGER_FINISHED = 5,
      //REQ_MATCH_MAKING_STARTED = 6,
      //REQ_MATCH_MAKING_FINISHED = 7,
      //MATCH_MAKING_COMPLETED = 8,
      //PLAYER_READY_TO_PLAY = 9,
      //ALL_PLAYERS_READY_TO_PLAY = 10,
      //JOIN_GAME_SESSION_STARTED = 11,
      //JOIN_GAME_SESSION_FINISHED = 12,
      //CLIENT_READY_TO_PLAY = 13,
      //GAME = 14,
      //GAME_SESSION_FINISHED = 15,
      //
    };
  };

  struct Result
  {
    enum 
    {
      NONE = -2,
      FAIL = -1,
      SUCCESS = 0,
      IN_PROGRESS = 1
    };
  };

  ClientContext(int internalid = 0)
    :stage_(Stage::NONE),
    lastresult_(Result::NONE),
    bexit_(false),
    sendSeqNum_(0),
    lastSendSeqNum_(0),
    lastRecvSeqNum_(0),
    internalid_(internalid)
  {
  }

  bool Init(naio::DriverSP spdrv, TL::Cfg cfg)
  {
    return tm_.Init(cfg, spdrv);
  }

  int startOpenChannel()
  {
    Transport::Address taddr;
    taddr.target = "relay";

    chnl_ = tm_.OpenChannelDirect(taddr, "", "localhost:35001");
    if (!chnl_)
      return Result::FAIL;

    stage_ = Stage::OPEN_CHANNEL_STARTED;
    return Result::IN_PROGRESS;
  }

  int checkOpenChannel()
  {
    if (Network::ConnectionState::Connecting == chnl_->GetStatus())
      return Result::IN_PROGRESS;
    else
    if (Network::ConnectionState::Connected != chnl_->GetStatus())
      return Result::FAIL;

    stage_ = Stage::OPEN_CHANNEL_FINISHED;
    return Result::SUCCESS;
  }

  int startSendSequencePacket()
  {
    if (Network::ConnectionState::Connected != chnl_->GetStatus())
      return Result::FAIL;

    int rc = Result::IN_PROGRESS;
    char buf[64];
    ++sendSeqNum_;
    memcpy(&buf[0], &sendSeqNum_, sizeof(sendSeqNum_));
    chnl_->SendRaw((byte*)(&buf[0]), sizeof(buf));
    systemLog( NLogg::LEVEL_MESSAGE ).Trace("Send(c=%d sendseq=%d size=%d)", internalid_, sendSeqNum_, sizeof(buf));
    stage_ = Stage::SEQUENCE_PACKET_SENT;

    return rc;
  }

  int checkSequencePacket()
  {
    if (Network::ConnectionState::Connected != chnl_->GetStatus())
      return Result::FAIL;

    int rc = Result::IN_PROGRESS;
    vector<byte> recvData;
    unsigned long recvSeqNum = unsigned long(-1);
    if (chnl_->ReceiveRaw(&recvData))
    {
      memcpy(&recvSeqNum, recvData.begin(), sizeof(recvSeqNum));
      systemLog( NLogg::LEVEL_MESSAGE ).Trace("Received(c=%d recvseq=%d lastrecvseq=%d size=%d)",internalid_, recvSeqNum, lastRecvSeqNum_, recvData.size());

      NI_ASSERT(recvSeqNum > lastRecvSeqNum_, NStr::StrFmt("WRONG RECV SEQUENCE(recvseq=%d lastrecvseq=%d", recvSeqNum, lastRecvSeqNum_));
      if (recvSeqNum <= lastRecvSeqNum_)
      {
        //systemLog(NLogg::LEVEL_MESSAGE) << 
        //  "transport: recv: WRONG SEQUENCE(time = "<< NHPTimer::GetScalarTime() << 
        //  " recvseq " << recvSeqNum << 
        //  " lastrecvseq " << lastRecvSeqNum_ << 
        //  ")" << endl;
        rc = Result::FAIL;
      }
      else
      {
        lastRecvSeqNum_ = recvSeqNum;
        rc = Result::SUCCESS;
      }

      stage_ = Stage::SEQUENCE_PACKET_RECEIVED;
    }

    return rc;
  }

  bool Step()
  {
    if (bexit_)
      return false;

    bool bres = false;
    int rc = Result::NONE;
    switch(stage_)
    {
      case Stage::NONE:
      {
        rc = startOpenChannel();
        bres = (Result::FAIL != rc);
      }
      break;

      case Stage::OPEN_CHANNEL_STARTED:
      {
        rc = checkOpenChannel();
        bres = (Result::FAIL != rc);
      }
      break;

      case Stage::OPEN_CHANNEL_FINISHED:
      case Stage::SEQUENCE_PACKET_RECEIVED:
      {
        rc = startSendSequencePacket();
        bres = (Result::FAIL != rc);
      }
      break;

      case Stage::SEQUENCE_PACKET_SENT:
      {
        rc = checkSequencePacket();
        bres = (Result::FAIL != rc);
      }
      break;

      default:
      {
        bexit_ = true;
      }
      break;
    }

    return bres;
  }

  unsigned long sendSeqNum_;
  unsigned long lastSendSeqNum_;
  unsigned long lastRecvSeqNum_;
  vector<byte> recvData_;

  int stage_;
  int lastresult_;
  bool bexit_;
  int internalid_;

  TL::TransportModule tm_;
  StrongMT<Transport::IChannel>  chnl_;
};

typedef CObj<ClientContext> ClientPtrT;
typedef nstl::vector<ClientPtrT> ClientsT;

struct Cfg : public TL::Cfg
{
  Cfg()
  {
    clients_ = 0;
  }
  int clients_;
};

int init_clients(naio::DriverSP const & spdrv, Cfg const & cfg, ClientsT& clients)
{
  if (cfg.clients_ <= 0)
    return -1;

  int i = 0;
  do 
  {
    CObj<ClientContext> cl(new ClientContext(++i));
    if (cl->Init(spdrv, cfg))
      clients.push_back(cl);
    else
    {
      clients.clear();
      return -1;
    }
  }
  while (i < cfg.clients_);

  return 0;
}

int run_test(ClientsT& clients)
{
  int count = 0;
  do 
  {
    count = 0;
    for(ClientsT::iterator it = clients.begin(); it != clients.end(); )
    {
      ClientPtrT pc = *it;
      if (pc->Step())
      {
        ++count;
        ++it;
      }
      else
      {
        it = clients.erase(it);
      }
    }

    ::Sleep(10);
  }
  while (count);

  return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//  main
//
int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  argc;
  argv;

  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "transport.test", "private", 0, 0, 0, 0);

  ScopedPtr<NLogg::CStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CStdOutDumper( &GetSystemLog() ) );
  ScopedPtr<NLogg::CTextFileDumper> textLogDumper;
  Reset( textLogDumper, new NLogg::CTextFileDumper( &GetSystemLog() ) );
  textLogDumper->SetFileSuffix("output");

  LocalAddressResolver addrResolver;
  Cfg cfg;
  cfg.at_ = &addrResolver;
  cfg.clients_ = 500;

  ClientsT clients;

  naio::DriverSP spdrv(new naio::Driver());
  naio::LogMsgCallbackSP splogcb(new TL::LogCallback(::GetSystemLog()));
  Transport::MessageFactory msgFactory;
  Transport::RegisterMessages(&msgFactory);
  TL::ProtocolHandlerFactory phFactory;
  TL::ChannelFactory chnlFactory;
  phFactory.Init(&msgFactory, &chnlFactory, true);

  naio::Cfg naiocfg;
  naiocfg.loglvl_ = 1;
  naiocfg.spLogMsgCb_ = splogcb;
  naiocfg.phf_ = &phFactory;
  if (!spdrv->Init(naiocfg))
    return -1;

  if (init_clients(spdrv, cfg, clients) >= 0)
  {
    run_test(clients);

    int ch = 0;
    while ((ch = _getch()) != 'Q');
  }

  clients.clear();
  splogcb.reset(0);
  spdrv.reset(0);

  return 0;
}
