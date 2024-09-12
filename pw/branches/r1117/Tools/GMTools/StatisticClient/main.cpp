#include "stdafx.h"
#include <conio.h>
#include <System/systemStdAfx.h>
#include <Server/RPC/all.h>

#include <Server/Network/Initializer.h>
#include <Server/Network/Transport.h>
#include <Server/Network/TransportInitializer.h>
#include <Server/Network/TransportMessages.h>
#include <Server/Network/AddressTranslator.h>
#include <Server/RPC/P2PNode.h>
#include <PF_GameLogic/SessionEventType.h>

#include <Server/RPC/LocalEntityFactory.h>
#include <Server/DebugVarUpdate/DebugVarReporter.h>

#include "../StatisticService/RPC/RStatisticWriter.auto.h"
#include "../StatisticService/RPC/RStatisticDebugWriter.auto.h"
#include <Server/Statistic/RStatisticClusterWriter.auto.h>

NDebug::DebugVar<int> var1("_var1", "");
NDebug::DebugVar<float> var2("_var2", "");

namespace StatisticClient
{

class CallbackHandler: public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( CallbackHandler, BaseObjectMT );

public:
  void DoNothing(int x)
  {
    printf("Do nothing with %d", x);
  }
};

}


int main(int argc, const char* argv[])
{
  printf("Sample: Simple Remote Objects demonstration.\n");

  StrongMT<Network::INetworkDriver> driver = Network::Initialize(); 
  StrongMT<Transport::ITransportSystem> transport = Transport::CreateTransportSystem(driver, Transport::GetGlobalMessageFactory(), 0);
  //StrongMT<rpc::Gate> gate = new rpc::Gate();

  {
    printf("Connecting to localhost:40001\n");

    StrongMT<Transport::IChannel> channel = transport->OpenChannelDirect( Transport::Address( "test", rand()%1000 ), "", "192.168.2.59:40001" );
    while (channel->GetStatus() == Network::ConnectionState::Connecting)
    {
      Sleep( 5 );
    }
    StrongMT<StatisticClient::CallbackHandler> chandler = new StatisticClient::CallbackHandler();
    if (channel->GetStatus() == Network::ConnectionState::Connected)
    {
      printf("Connected to server\n");
      
      //rpc::P2PNode node(channel, gate);
      StrongMT<rpc::GateKeeper> gateKeeper = new rpc::GateKeeper(transport, "", Transport::autoAssignClientId);

      rpc::P2PNode* node = new rpc::P2PNode(channel, &gateKeeper->GetGate());

      //StrongMT<StatisticService::RPC::RStatisticWriter> remoteStatistic = node.node->Create<StatisticService::RPC::RStatisticWriter>();
      StrongMT<StatisticService::RPC::RStatisticClusterWriter> clusterStatistic = node->node->Create<StatisticService::RPC::RStatisticClusterWriter>();
      StrongMT<StatisticService::RPC::RStatisticDebugWriter> debugStatistic = node->node->Create<StatisticService::RPC::RStatisticDebugWriter>();

      Sleep(1000);

      int i = 1;
      if (channel->GetStatus() == Network::ConnectionState::Connected)
      {
        StatisticService::RPC::SessionStartInfoSV st_info;
        st_info.sessionid = 100500 + i;
        st_info.map = L"";
        st_info.server = L"";
        st_info.sessionType = 4;
        st_info.players.reserve(10);
        for(int p_count = 0; p_count < 10; p_count++)
        {
          st_info.players.push_back();
          StatisticService::RPC::SessionStartPlayerSV & dest = st_info.players.back();
          dest.userid = 100 + i;
          dest.faction = p_count % 2;
          dest.sex = 0;
          dest.heroid = 538757077;
          dest.nickname = L"test morjovy";
        }
        clusterStatistic->LogSessionStart(st_info, chandler.Get(), &StatisticClient::CallbackHandler::DoNothing);
        printf("Logging session %d start...\n", st_info.sessionid);
        
        gateKeeper->Poll();
        Sleep(5000);

        // Debug statistics
        StatisticService::RPC::ExceedingStepTimeInfo lag_info;
        lag_info.sessionId = 100500 + i;
        lag_info.playerId = 100 + i;

        debugStatistic->LogExceedingStepTime(lag_info);
        gateKeeper->Poll();
        Sleep(1000);

        i++;
      }
      else
      {
        printf("CHANNEL CLOSED");
      }

/*      for (int i=1; i<=10000000; i++)
      {

        StatisticService::RPC::SessionEventInfo e0;
        e0.intParam1 = 201;
        e0.intParam2 = 101;
        e0.intParam3 = 51;
        remoteStatistic->LogSessionEvent(1050, 0, 0, 0, 100+i, SessionEventType::HeroKill, e0);
        node.Poll();
        Sleep(1);

        StatisticService::RPC::SessionEventInfo e1;
        e1.intParam1 = 202;
        e1.intParam2 = 102;
        e1.intParam3 = 52;
        remoteStatistic->LogSessionEvent(1050, 0, 0, 0, 100+i, SessionEventType::NaftaIncomeFromCreature, e1);
        node.Poll();
        Sleep(1);
        
        remoteStatistic->LogDebugVar(1050, 11, 100+i, L"Mood", L"SotonaaaaaaMBAXAXAXA");
        node.Poll();

        printf("step ");
        Sleep(10);
      }
*/
      /*
      StatisticService::RPC::SessionResultInfo info;
      info.sessionId = sessionId;
      info.sideWon = L"sideA";
      info.finalLevel = 34;
      info.score = 100500;
      info.kills = 10;
      info.deaths = 6;
      info.assists = 120;
      info.enemyCreepsKilled = 870;
      info.neutralCreepsKilled = 2;
      info.characterId = characterId;

      info.login = L"rpcplayer0";
      remoteStatistic->LogSessionResults(info);

      printf("\nLogging session result...\n");
      node.Poll();
      Sleep(1000);
      */

      if (channel->GetStatus() != Network::ConnectionState::Connected)
      {
        printf("Server dropped\n");
      }

      // теперь побегаем немного для проверки DebugVarReporter
      /*
      for( int i=0; i<60; i++ )
      {
        node.Poll();
        Sleep(1000);
      }
      */

    } else
    {
      printf("Not connected to server, aborted\n");
    }
  }
  return 0;
} 

static bool CommandSendClientVar( const char *cmdname, const vector<wstring> &params )
{
  //TODO: начать слать в статистику что-то

  //else
  {
    LOG_M(0) << "usage: sendvar <var_name> <period_seconds>"; // шлите нам переменную var_name раз в столько секунд (float)
  }
	return true;
}

static bool CommandStopClientVar( const char *cmdname, const vector<wstring> &params )
{
  //TODO: прекратить слать в статистику что-то

  if ( params.size() == 1 && params[0] == L"ALL" )
  {
    LOG_M(0) << "usage: stopvar ALL"; // лайк, совсем перестаньте спамить сервер своими переменными
  }
  else
  {
    LOG_M(0) << "usage: stopvar <var_name>"; // перестаньте спамить конкретно эту переменную
  }
	return true;
}

REGISTER_CMD( sendvar, CommandSendClientVar ); // "sendvar name period" -- начинаем слать серверу статистики соотв. переменную с соотв. периодичностью
REGISTER_CMD( stopvar, CommandStopClientVar ); // "stopvar name", "stopvar ALL" -- прекращаем слать соотв. переменные

