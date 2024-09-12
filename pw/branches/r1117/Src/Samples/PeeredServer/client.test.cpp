//!Component('System/Ptr')
//!Component('System/NSTL')
//!Component('System/Streams')
//!Component('System/Savers')
//!Component('System/Savers')
//!Component('Game/PF/Client/LobbyPvx/HybridClient')
//!Component('Game/PF/HybridServer/PeeredTypes')
//!Component('Game/PF/Server/Roll/RollTypes')
//!Component('Server/RPC')
//!Component('PW_Client/GameStatistics')
//!Component('Client/Timer')
//!Component('System/CrashHandler')
//!Component('Render/Lighting')
//!Component('Render/Occlusion')
//!Component('Game/PF/Server/Statistic/GameStatClient')
//!Component('Render/ImmediateRenderer')
//!Component('Render/BatchedRenderer')
//!Component('System/MainFrame')
//!Component('Render/PostEffects')
//!Component('System/Random')
//!Component('Render/RenderScene')
//!Component('Render/RenderScene')
//!Component('UI/Core')
#include <cxxtest/TestSuite.h>
#include <System/systemStdAfx.h>
#include <System/Basic.h>
#include <System/nvector.h>
#include <System/nstring.h>
#include <System/BinSaver.h>
#include <Core/GameCommand.h>
#include <Game/PF/HybridServer/Peered.h>
#include <Game/PF/Client/LobbyPvx/HybridServerNodeImpl.h>


//int Peered::ClientSettings::ID = 0x41ec85d;
//int Peered::ClientStartInfo::ID = 0x66c8e600;

namespace test
{

class MockWorldCommand 
{
public:
  MockWorldCommand() {}
  MockWorldCommand(const void* data, int size) 
  {
    stream.Write(data, size);
  }
  int size() const { return stream.GetPosition(); }
  const void* data() const { return stream.GetBuffer(); }
public:
  MemoryStream stream;
};


struct MockServer : Peered::IGameServer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockServer, Peered::IGameServer, BaseObjectMT );
public:
  struct CachedCommand
  {
    int clientIndex;
    rpc::CachedMemoryBlock data;
  };
  virtual void AddClient(const char* name, uint clientId, Peered::IGameClient* _client)
  {
  }
  virtual void AddClientFast(int clientId, int clientIndex, NI_LPTR Peered::IGameClient* _client, int fromStep) {}
  virtual void SendCommand(int clientIndex, const rpc::MemoryBlock& command)
  {
    CachedCommand& cmd = commands.push_back();
    cmd.clientIndex = clientIndex;
    cmd.data = command;
  }
  virtual void OnFinishStep(int clientIndex, uint step, uint worldCrc) {}
  virtual void OnClientReady(int clientIndex) {}
  virtual void SetTimeScale(int clientIndex, float _scale) {}

  virtual void OnGameFinish(int clientIndex, int step, const StatisticService::RPC::SessionClientResults & finishInfo) {}
  virtual void RequestWorldData(int clientIndex) {}
  virtual bool OnRejoinClient( uint clientId ) { return true; }
  virtual bool OnGameLeave(int clientIndex) { return true; }
  virtual void SendCrcData(int clientIndex, int step, const rpc::MemoryBlock& crcData) {}
  virtual void OnDisconnectAck(int clientIndex) {}
  virtual void AddSpectator( uint clientId, const wstring& nickname ) {}

  void DeserializeCommand(int index, test::MockWorldCommand& cmd)
  {
    cmd.stream.Write(commands[index].data.memory, commands[index].data.size);
  }

  rpc::CachedMemoryBlock SerializeCommand(test::MockWorldCommand& cmd)
  {
    return rpc::CachedMemoryBlock(cmd.stream.GetBuffer(), cmd.stream.GetPosition());
  }

  nstl::vector<CachedCommand> commands;
};

struct CommandsPacker
{
  CommandsPacker(test::MockServer* server):server(server) {}

  void Pack(void* data, int size)
  {
    test::MockWorldCommand mcmd(data, size);
    memoryBlocks.push_back(server->SerializeCommand(mcmd));

  }
  const nstl::vector<rpc::MemoryBlock>& Get()
  {
    result.resize(0);
    for (int i=0;i<memoryBlocks.size();++i)
    {
      rpc::MemoryBlock& b = result.push_back();
      b.memory = memoryBlocks[i].memory;
      b.size = memoryBlocks[i].size;
    }
    return result;
  }

  StrongMT<test::MockServer> server;
  
  nstl::vector<rpc::MemoryBlock> result;
  nstl::vector<rpc::CachedMemoryBlock> memoryBlocks;
};
} // test

struct Test_PeeredClient : public CxxTest::TestSuite
{

  void test_Simple()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);
    TS_ASSERT_EQUALS(false, node.IsStarted());

    TS_ASSERT_EQUALS(-1, node.GetAsyncStep());
    NCore::IServerNode::TMessageList commands;
    NCore::IServerNode::TStatusList statuses;
    
    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(false, node.GetServerSegment(commands, statuses));

    Peered::ClientStartInfo info;
    info.index = 555;
    node.Start( info, 0 ); // 555
    TS_ASSERT_EQUALS(true, node.IsStarted());
    {
      test::MockWorldCommand cmd("aaaa", 4);
      node.SendMessage(&cmd.stream);

      TS_ASSERT_EQUALS(1, server->commands.size());
      TS_ASSERT_EQUALS(555, server->commands[0].clientIndex);
    }

    {
      test::MockWorldCommand cmd;
      server->DeserializeCommand(0, cmd);
      TS_ASSERT_EQUALS(4, cmd.size());
      TS_ASSERT_SAME_DATA(cmd.data(), "aaaa", 4);
    }
  }

  void test_GetSegment()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);
    TS_ASSERT_EQUALS(-1, node.GetAsyncStep());
    NCore::IServerNode::TMessageList commands;
    NCore::IServerNode::TStatusList statuses;

    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(false, node.GetServerSegment(commands, statuses));

    Peered::ClientStartInfo info;
    node.Start( info, 0 ); // 777

    {
      test::MockWorldCommand wcmd0("bbbbb", 5);
      rpc::CachedMemoryBlock cmd0 =  server->SerializeCommand(wcmd0);

      test::MockWorldCommand wcmd1("ccc", 3);
      rpc::CachedMemoryBlock cmd1 =  server->SerializeCommand(wcmd1);

      nstl::vector<rpc::MemoryBlock> blocks;
      rpc::MemoryBlock& b0 = blocks.push_back();
      b0.memory = cmd0.memory;
      b0.size = cmd0.size;

      rpc::MemoryBlock& b1 = blocks.push_back();
      b1.memory = cmd1.memory;
      b1.size = cmd1.size;

      node.Step(0, 0, blocks, nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
      
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));

      TS_ASSERT_EQUALS(2, commands.size());

      TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), "bbbbb", 5);
      TS_ASSERT_SAME_DATA(commands[1]->GetBuffer(), "ccc", 3);
    }

    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(false, node.GetServerSegment(commands, statuses));

    {
      node.Step(1, 1, nstl::vector<rpc::MemoryBlock>(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );

      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));

      TS_ASSERT_EQUALS(0, commands.size());
    }

    {
      test::MockWorldCommand wcmd0("gggggg", 6);
      rpc::CachedMemoryBlock cmd0 =  server->SerializeCommand(wcmd0);

      test::MockWorldCommand wcmd1("hhhhhhh", 7);
      rpc::CachedMemoryBlock cmd1 =  server->SerializeCommand(wcmd1);

      test::MockWorldCommand wcmd2("ee", 2);
      rpc::CachedMemoryBlock cmd2 =  server->SerializeCommand(wcmd2);

      nstl::vector<rpc::MemoryBlock> blocks;
      rpc::MemoryBlock& b0 = blocks.push_back();
      b0.memory = cmd0.memory;
      b0.size = cmd0.size;

      rpc::MemoryBlock& b1 = blocks.push_back();
      b1.memory = cmd1.memory;
      b1.size = cmd1.size;

      rpc::MemoryBlock& b2 = blocks.push_back();
      b2.memory = cmd2.memory;
      b2.size = cmd2.size;

      node.Step(2, 2, blocks, nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
  
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));

      TS_ASSERT_EQUALS(3, commands.size());

      TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), "gggggg", 6);
      TS_ASSERT_SAME_DATA(commands[1]->GetBuffer(), "hhhhhhh", 7);
      TS_ASSERT_SAME_DATA(commands[2]->GetBuffer(), "ee", 2);
    }
    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(false, node.GetServerSegment(commands, statuses));
  }

  void test_TwoStepsWithoutGet()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);

    NCore::IServerNode::TMessageList commands;
    NCore::IServerNode::TStatusList statuses;
    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(false, node.GetServerSegment(commands, statuses));

    Peered::ClientStartInfo info;
    node.Start( info, 0 ); // 777
    {
      test::CommandsPacker packer(server);
      packer.Pack("bbbb", 4);
      packer.Pack("zzz", 3);

      node.Step( 0, 0, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }
    {
      test::CommandsPacker packer(server);
      packer.Pack("aaa", 3);
      packer.Pack("v", 1);
      packer.Pack("ww", 2);

      node.Step( 1, 1, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }

    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));

    TS_ASSERT_EQUALS(2, commands.size());

    TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), "bbbb", 4);
    TS_ASSERT_SAME_DATA(commands[1]->GetBuffer(), "zzz", 3);

    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));

    TS_ASSERT_EQUALS(3, commands.size());

    TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), "aaa", 3);
    TS_ASSERT_SAME_DATA(commands[1]->GetBuffer(), "v", 1);
    TS_ASSERT_SAME_DATA(commands[2]->GetBuffer(), "ww", 2);
  }

  void test_OffsetStep()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);

    NCore::IServerNode::TMessageList commands;
    NCore::IServerNode::TStatusList statuses;

    Peered::ClientStartInfo info;
    node.Start( info, 0 ); // 777
    {
      test::CommandsPacker packer(server);
      packer.Pack("bbbb", 4);

      node.Step( 666, 666, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }

    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));

    TS_ASSERT_EQUALS(1, commands.size());
    TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), "bbbb", 4);

    node.GetServerSegment(commands, statuses);
    //TS_ASSERT_EQUALS(false, node.GetServerSegment(commands, statuses));
  }

  void test_StepCaching()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);

    Peered::ClientStartInfo info;
    node.Start( info, 0 ); // 777
    for (int i=0;i<25;++i)
    {
      test::CommandsPacker packer(server);
      packer.Pack(&i, 4);
      node.Step( i, i, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }

    for (int i=0;i<25;++i)
    {
      NCore::IServerNode::TMessageList commands;
      NCore::IServerNode::TStatusList statuses;
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));
      TS_ASSERT_EQUALS(1, commands.size());
      TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), &i, 4);
    }
    for (int i=0;i<27;++i)
    {
      test::CommandsPacker packer(server);
      packer.Pack(&i, 4);
      node.Step( i, i, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }

    for (int i=0;i<27;++i)
    {
      NCore::IServerNode::TMessageList commands;
      NCore::IServerNode::TStatusList statuses;
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));
      TS_ASSERT_EQUALS(1, commands.size());
      TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), &i, 4);
    }
  }

  void test_CachingOfEmptySteps()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);

    for (int i=0;i<27;++i)
    {
      test::CommandsPacker packer(server);
      node.Step( i, i, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }
    for (int i=0;i<27;++i)
    {
      NCore::IServerNode::TMessageList commands;
      NCore::IServerNode::TStatusList statuses;
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));
      TS_ASSERT_EQUALS(0, commands.size());
    }
    {
      test::CommandsPacker packer(server);
      packer.Pack("aaaa", 4);
      node.Step( 28, 28, packer.Get(), nstl::vector<Peered::BriefClientInfo>(), nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
      NCore::IServerNode::TMessageList commands;
      NCore::IServerNode::TStatusList statuses;
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));
      TS_ASSERT_EQUALS(1, commands.size());
      TS_ASSERT_SAME_DATA(commands[0]->GetBuffer(), "aaaa", 4);
    }
  }

  void test_AddingEntities()
  {
    StrongMT<test::MockServer> server = new test::MockServer;
    NCore::ServerNode node(server);

    Peered::ClientStartInfo info;
    node.Start( info, 0 ); // 777
    {
      nstl::vector<Peered::BriefClientInfo> addedEntities;
      test::CommandsPacker packer(server);
      {
        Peered::BriefClientInfo info = { 4, Peered::Active, 0xA };
        addedEntities.push_back(info);
        packer.Pack("entity4", 7);
      }
      {
        Peered::BriefClientInfo info = { 12, Peered::Active, 0xD };
        addedEntities.push_back(info);
        packer.Pack("entity12", 8);
      }
      node.Step( 0, 0, nstl::vector<rpc::MemoryBlock>(), addedEntities, nstl::vector<Peered::GapInfo>(), NHPTimer::STime() );
    }
    {
      NCore::IServerNode::TMessageList commands;
      NCore::IServerNode::TStatusList statuses;
      node.GetServerSegment(commands, statuses);
      //TS_ASSERT_EQUALS(true, node.GetServerSegment(commands, statuses));
      TS_ASSERT_EQUALS(0, commands.size());
      nstl::vector<Peered::BriefEntityInfo> addedEntities;
      nstl::vector<rpc::MemoryBlock> addedEntitiesData;
      //node.GetAddedEntities(addedEntities, addedEntitiesData);
      //TS_ASSERT_EQUALS(2, addedEntities.size());
      //TS_ASSERT_EQUALS(2, addedEntitiesData.size());
    }
  }

};

NI_DEFINE_REFCOUNT( test::MockServer );