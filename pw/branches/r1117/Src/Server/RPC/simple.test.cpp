//!Component('RPC/all')
//!Component('System/Threading')
//!Component('System/NSTL')
//!Component('System/Asserts')
//!Component('Network/Transport')
//!Component('Network/LocalNetDriver')
//!Component('RPC/RPCMixin')
//!Component('simple.test')

#include "stdafx.h"
#include <cxxtest/TestSuite.h>

#include <System/AutoPtr.h>
#include <System/ScopedArray.h>
#include <System/BinSaver.h>
#include <System/BitData.h>
#include <RPC/RPC.h>
#include <RPC/P2PNode.h>

#include "RPCMixin.h"

#include "RSimpleRPCRabbit.auto.h"
#include "LSimpleRPCRabbit.auto.h"
#include "LSimpleRPCRabbitAck.auto.h"

SERIALIZE_FACTORY(RabbitData);

namespace test 
{
SERIALIZE_FACTORY( SPreGamePerUserData );
SERIALIZE_FACTORY( SPreGameData );
SERIALIZE_FACTORY( SPostGamePerUserData );
SERIALIZE_FACTORY( SPostGameData );
SERIALIZE_FACTORY( SClientStatistics);
SERIALIZE_FACTORY( GameGuildData );
}

struct SimpleRPCRabbitFactory : rpc::ILocalEntityFactory
{
    rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& info, rpc::Arguments& args, rpc::IEntityMap* entityMap)
    {
        bool popResult = true;
        test::SimpleRPCRabbit* r = 0;
        if (0 == info.paramsCount)
        {
            r = new test::SimpleRPCRabbit;
        } else if (info.paramsCount == 1)
        {
          const nstl::wstring& nS  = args.Pop<const nstl::wstring&>(popResult);
          r = new test::SimpleRPCRabbit(nS);
        } else if (info.paramsCount == 2)
        {
          const FixedVector<float, 20>& fv  = args.PopFixedVector<float, 20>(popResult);
          r = new test::SimpleRPCRabbit(fv, 20);
        } else if (info.paramsCount == 3)
        {
            int _objectID = args.Pop<int>(popResult);
            const CVec3& _position = args.PopStruct<CVec3>(popResult);
            const CVec3& _target = args.PopStruct<CVec3>(popResult);
            _position;_target;
            r = new test::SimpleRPCRabbit(_objectID);
        } else if (info.paramsCount == 4)
        {
            const RabbitData& data = args.PopStruct<RabbitData>(popResult, rpc::GetGlobalDataFactory());
            const char* cS = args.Pop<const char*>(popResult);
            const nstl::string& nS  = args.Pop<const nstl::string&>(popResult);
            const nstl::vector<int>& vI = args.PopVector<int>(popResult);
            r = new test::SimpleRPCRabbit(cS, nS, vI, data);
        }        
        NI_ASSERT(r, "Class implementation should be created");
        return new test::LSimpleRPCRabbit(r, entityMap, this);
    }
};

static SimpleRPCRabbitFactory factory_SimpleRPCRabbit;
static rpc::CreationEntry entry_test_SimpleRPCRabbit(rpc::GetId<test::SimpleRPCRabbit>(), factory_SimpleRPCRabbit);

struct SimpleRPCRefCountedRabbitFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& info, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    test::SimpleRefCountedRPCRabbit* r = new test::SimpleRefCountedRPCRabbit;
    return new test::LSimpleRefCountedRPCRabbit( r, entityMap );
  }
};

static SimpleRPCRefCountedRabbitFactory factory_SimpleRefCountedRPCRabbit;
static rpc::CreationEntry entry_test_SimpleRefCountedRPCRabbit(rpc::GetId<test::SimpleRefCountedRPCRabbit>(), factory_SimpleRefCountedRPCRabbit);

struct ISimpleRPCRabbitAckFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& info, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return 0;
  }
  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
  { 
    return new test::LISimpleRPCRabbitAck((test::ISimpleRPCRabbitAck*)value, entityMap, this);
  }

};

static ISimpleRPCRabbitAckFactory factory_ISimpleRPCRabbitAck;
static rpc::CreationEntry entry_test_ISimpleRPCRabbitAck(rpc::GetId<test::ISimpleRPCRabbitAck>(), factory_ISimpleRPCRabbitAck);

struct Test_RPC_Simple : public CxxTest::TestSuite, RPCMixin   
{
    void test_VoidCall()
    {
        TwoNodesCase c;
        StrongMT<test::RSimpleRPCRabbit> client_object(c.cnode1->Create<test::RSimpleRPCRabbit>()); 

        test::SimpleRPCRabbit* server_object = waitForEntity<test::SimpleRPCRabbit>(c.cnode0, 0, c); 
        TS_ASSERT_EQUALS(false, server_object->is_processed);

        client_object->process();
        c.Poll();
        TS_WAIT_FOR(server_object->is_processed == true, 100);
        TS_ASSERT_EQUALS(true, server_object->is_processed);
    }

    void test_ASynchronousReturnIntValue()
    {
        TwoNodesCase c;

        StrongMT<test::RSimpleRPCRabbit> p0(c.cnode0->Create<test::RSimpleRPCRabbit>());
        c.Poll();

        for (int i=0;i<10;++i) 
        {
          StrongMT<rpc::RValue<int>> t = new rpc::RValue<int>;
          p0->processIntWithReturnValueIntAsync(i, t.Get(), &rpc::RValue<int>::OnCall);
          while(!t->IsSet()) c.Poll();
          TS_ASSERT_EQUALS(i*3, t->result);
        }
    }

  void test_ComplexStructReturn()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRPCRabbit> clientObject(c.cnode1->Create<test::RSimpleRPCRabbit>());
    c.Poll();

    test::SimpleRPCRabbit* serverObject = waitForEntity<test::SimpleRPCRabbit>(c.cnode0, 0, c); 
    serverObject->msg.serverTime = 50.f;

    StrongMT<rpc::RefValue<test::InitialSnapshot>> r = new rpc::RefValue<test::InitialSnapshot>;
    clientObject->GetServerDef(r.Get(), &rpc::RefValue<test::InitialSnapshot>::OnCall);
    TS_WAIT_FOR(r->IsSet() == true, 100);
    TS_ASSERT_EQUALS(50.f, r->result.serverTime);
  }

  void test_ComplexStructReturnDisconnect()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRPCRabbit> clientObject(c.cnode1->Create<test::RSimpleRPCRabbit>());
    c.Poll();

    test::SimpleRPCRabbit* serverObject = waitForEntity<test::SimpleRPCRabbit>(c.cnode0, 0, c); 
    serverObject->msg.serverTime = 50.f;

    StrongMT<rpc::RefValue<test::InitialSnapshot>> r = new rpc::RefValue<test::InitialSnapshot>;
    clientObject->GetServerDef(r.Get(), &rpc::RefValue<test::InitialSnapshot>::OnCall);
    c.Disconnect(true, true);
    c.Poll();
  }

  void test_ComplexStruct()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRPCRabbit> clientObject(c.cnode1->Create<test::RSimpleRPCRabbit>());
    c.Poll();

    test::SimpleRPCRabbit* serverObject = waitForEntity<test::SimpleRPCRabbit>(c.cnode0, 0, c); 
    test::InitialSnapshot snapshot;
    snapshot.serverTime = 4.f;
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1004;
      desc.isDead = false;
      snapshot.difference.push_back(desc);
    }
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1001;
      desc.isDead = true;
      snapshot.difference.push_back(desc);
    }
    clientObject->processSnapshot(snapshot);
    c.Poll();
    TS_WAIT_FOR(serverObject->isSnapshotRecieved == true, 10000);
    TS_ASSERT_EQUALS(true, serverObject->isSnapshotRecieved);
    TS_ASSERT_EQUALS(4.f, serverObject->msg.serverTime);
    TS_ASSERT_EQUALS(2, serverObject->msg.difference.size());
  }


    void test_ComplexParamsInContructor()
    {
      const char* cS = "Hello!";
      nstl::string sS = "World !";
      nstl::vector<int> vI;
      vI.push_back(1);vI.push_back(2);
      RabbitData data;
      data.i = 555;
      data.f = 2.f;

      TwoNodesCase c;

      StrongMT<test::RSimpleRPCRabbit> s0(c.cnode0->Create<test::RSimpleRPCRabbit>(data, cS, sS, vI));
      c.Poll();

      test::SimpleRPCRabbit* c0 = waitForEntity<test::SimpleRPCRabbit>(c.cnode1, 0, c); 
      TS_ASSERT_EQUALS("Hello!", c0->cS);
      TS_ASSERT_EQUALS("World !", c0->sS);
      TS_ASSERT_EQUALS(2, c0->vI.size());
      TS_ASSERT_EQUALS(1, c0->vI[0]);
      TS_ASSERT_EQUALS(2, c0->vI[1]);
      TS_ASSERT_EQUALS(555, c0->data.i);
      TS_ASSERT_EQUALS(2.f, c0->data.f); 
    }

    void test_WStringInContrustor()
    {
      TwoNodesCase c;

      nstl::wstring s(L"Hello!");
      StrongMT<test::RSimpleRPCRabbit> s0(c.cnode0->Create<test::RSimpleRPCRabbit>(s));
      test::SimpleRPCRabbit* serverObject = waitForEntity<test::SimpleRPCRabbit>(c.cnode1, 0,c );
      TS_WAIT_FOR(s == serverObject->sW, 100);
    }

    void test_FixedVectorInContrustor()
    {
      TwoNodesCase c;


      FixedVector<float, 20> fv;
      fv.push_back(1.f);
      fv.push_back(2.f);
      fv.push_back(3.f);
      fv.push_back(4.f);
      StrongMT<test::RSimpleRPCRabbit> s0(c.cnode0->Create<test::RSimpleRPCRabbit>(fv, 100));
      test::SimpleRPCRabbit* serverObject = waitForEntity<test::SimpleRPCRabbit>(c.cnode1, 0,c );
      TS_WAIT_FOR(fv.size() == serverObject->ff.size(), 100);
      for (uint i=0;i<fv.size();++i)
      {
        TS_ASSERT_EQUALS(fv[i], serverObject->ff[i]);
      }
    }

    void test_BadPopParams()
    {
    }

    void test_ReplicationParams()
    {
/*      ManyToManyCase c;
      rpc::Gate& serverGate = c.AddGate("server");

      nstl::vector<StrongMT<test::RSimpleRPCRabbit> > rabbits;
      nstl::vector<rpc::Node*> serverNodes;
      for (int j=0;j<20;++j)
      {
        char buffer[20];
        sprintf(buffer, "client%d", j);
        rpc::Gate& gate = c.AddGate(buffer);
        c.ConnectGates(serverGate, gate);
        c.WaitForConnections();

        rpc::Node* node = c.GetNode(serverGate, gate);
        test::RSimpleRPCRabbit* s = node->Create<test::RSimpleRPCRabbit>(j+1, VNULL3, VNULL3); 

        // replicate rabbits to new created node
        for (int i=0;i<rabbits.size();++i)
        {
          serverGate.Replicate(*rabbits[i], *nodes.f_s);
        }
        rabbits.push_back(s);

        // replicate new created rabbit to all nodes instead new
        for (int i=0;i<serverNodes.size();++i)
        {
          serverGate.Replicate(*s, *serverNodes[i]);
        }
        serverNodes.push_back(nodes.f_s);
        c.Poll();

        // check that new rabbit was created on new node
        test::SimpleRPCRabbit* c = nodes.s_f->get<test::SimpleRPCRabbit>(j);
        TS_ASSERT_EQUALS(j+1, c->id);

        // check that replicated rabbits was created on new node with correct creation params
        for (int i=0;i<c->id-1;++i)
        {
          test::SimpleRPCRabbit* c2_0 = nodes.s_f->get<test::SimpleRPCRabbit>(i);
          TS_ASSERT_EQUALS(i+1, c2_0->id);
        }
      }*/
    }

    void test_Refcounted_Local() 
    {            
      TwoNodesCase c;
      StrongMT<test::RSimpleRefCountedRPCRabbit> robject(c.cnode1->Create<test::RSimpleRefCountedRPCRabbit>()); 

      WeakMT<test::SimpleRefCountedRPCRabbit> lobject = waitForEntity<test::SimpleRefCountedRPCRabbit>(c.cnode0, 0, c); 
      TS_ASSERT_EQUALS(false, lobject.Lock()->is_processed);

      robject->process();
      c.Poll();
      TS_WAIT_FOR(lobject.Lock()->is_processed == true, 100);

      robject = 0;
      TS_WAIT_FOR( (bool)lobject.Lock() == false, 100);
    }

    void test_PrePostCall()
    {
        TwoNodesCase c;
        StrongMT<test::RSimpleRPCRabbit> client_object(c.cnode1->Create<test::RSimpleRPCRabbit>()); 

        test::SimpleRPCRabbit* server_object = waitForEntity<test::SimpleRPCRabbit>(c.cnode0, 0, c); 
        TS_ASSERT_EQUALS(false, server_object->is_processed);

        test::SPreGameData preGame;
        preGame.mapDesc = "0123456789012345678901234567890123456789012345678901234567890123456789";
        const int playersCount = 10;
        const int inventoryCount = 10;
        const int friendsCount = 500;
        const int talentsCount = 36;
        const int talentRollsCount = 5;
        const int talentRollsItemsCount = 5;
        preGame.users.resize(playersCount);
        for (int i=0;i<playersCount;++i)
        {
          preGame.users[i].playerInfo.inventory.resize(inventoryCount);
          preGame.users[i].playerInfo.friends.resize(friendsCount);
          preGame.users[i].playerInfo.heroSkin = "0123456789";
          preGame.users[i].playerInfo.locale = "01";
          for (int j=0;j<talentsCount;++j)
          {
            preGame.users[i].playerInfo.talents[j] = test::TalentInfo();
          }
          for (int j=0;j<talentRollsCount;++j)
          {
            char buffer[64];
            sprintf(buffer, "012345678901234567890123456789%d", j);
            preGame.users[i].playerInfo.talentRollData.rollTable.insert(buffer);
            preGame.users[i].playerInfo.talentRollData.rollTable[buffer].items.resize(talentRollsItemsCount);
            for (int k=0;k<talentRollsItemsCount;++k)
            {
              preGame.users[i].playerInfo.talentRollData.rollTable[buffer].items[k].dbid = "012345678901234567890123456789";
            }
          }
        }
        test::SPostGameData postGame;
        postGame.users.resize(playersCount);
        class SimpleRPCRabbitAck : public test::ISimpleRPCRabbitAck, public BaseObjectMT
        {
          NI_DECLARE_REFCOUNT_CLASS_2( SimpleRPCRabbitAck, test::ISimpleRPCRabbitAck, IBaseInterfaceMT );
        };
        StrongMT<SimpleRPCRabbitAck> ack = new SimpleRPCRabbitAck;
        client_object->Roll(preGame, postGame, ack);
        c.Poll();
        TS_WAIT_FOR(server_object->is_processed == true, 100);
        TS_ASSERT_EQUALS(true, server_object->is_processed);
        TS_WAIT_FOR(ack->value == 456, 100);
    }

};

NI_DEFINE_REFCOUNT(test::SimpleRefCountedRPCRabbit);

