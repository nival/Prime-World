//!Component('RPC/all')
//!Component('Chain.test')

#include <RPC/RPC.h>
#include <Server/RPC/RPCMixin.h>

#include "Classes.test.h"
#include "RClasses.test.auto.h"
#include "LClasses.test.auto.h"

namespace test
{

struct LocationServerFactory : rpc::ILocalEntityFactory
{

  rpc::Node* coordinatorNode;
  LocationServerFactory(rpc::Node* _coordinatorNode):coordinatorNode(_coordinatorNode) {}

  virtual rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return new test::LLocationServer(new test::LocationServer(coordinatorNode), entityMap, this);
  }

  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
  { 
    NI_ALWAYS_ASSERT("!!!");
    return 0; 
  }
  virtual void Destroy( rpc::ILocalEntity* entity ) 
  {
  }

};

struct ClientFactory : rpc::ILocalEntityFactory
{
  virtual rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return new test::LClient(new test::Client, entityMap, this);
  }
  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
  { 
    NI_ALWAYS_ASSERT("!!!");
    return 0; 
  }
  virtual void Destroy( rpc::ILocalEntity* entity ) 
  {
  }

};

struct BattleInstanceFactory : rpc::ILocalEntityFactory
{
  virtual rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return new test::LBattleInstance(new test::BattleInstance, entityMap, this);
  }
  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
  { 
    NI_ALWAYS_ASSERT("!!!");
    return 0; 
  }
  virtual void Destroy( rpc::ILocalEntity* entity ) 
  {
  }

};

struct DbRootFactory : rpc::ILocalEntityFactory
{
  virtual rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    if (entityInfo.classId == rpc::GetId<test::DbRoot>())
    {
      return new test::LDbRoot(new test::DbRoot, entityMap, this);
    }
    if (entityInfo.classId == rpc::GetId<test::ItemContainer>())
    {
      return new test::LItemContainer(new test::ItemContainer, entityMap, this);
    }
    if (entityInfo.classId == rpc::GetId<test::Item>())
    {
      return new test::LItem(new test::Item, entityMap, this);
    }
    return 0;
  }

  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
  { 
    if (classId == rpc::GetId<test::HeroDescription>())
    {
      return new test::LHeroDescription((test::HeroDescription*)value, entityMap);
    }
    if (classId == rpc::GetId<test::ItemContainer>())
    {
      return new test::LItemContainer((test::ItemContainer*)value, entityMap);
    }
    if (classId == rpc::GetId<test::Item>())
    {
      return new test::LItem((test::Item*)value, entityMap);
    }
    return 0; 
  }

};

test::RBattleInstance* LocationServer::CreateNew()
{
  instance = coordinatorNode->Create<test::RBattleInstance>(555, "Hello, World!");
  return instance;
}

void LocationInstance::Start()
{
  locationServer->CreateNew( this, &LocationInstance::OnCall);
}

void LocationInstance::OnCall(test::RBattleInstance* inst)
{
  client->OnNewBattle(inst); 
}

void Client::OnNewBattle(test::RBattleInstance* _instance)
{
  instance = _instance;
}

test::RHeroDescription* DbRoot::GetHeroDescription(const char* name)
{
  if (0 == strcmp(name, "redjack"))
  {
    return RemotePtr<test::RHeroDescription>(redjack);
  }
  if (0 == strcmp(name, "sippul"))
  {
    return RemotePtr<test::RHeroDescription>(sippul);
  }
  return 0;
}

} // test

struct Test_ChainPtr : public CxxTest::TestSuite, RPCMixin   
{

  void test_Simple()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> liP = new test::MockCorruptedPacketProcessor("LI", &c);
    StrongMT<test::MockCorruptedPacketProcessor> clP = new test::MockCorruptedPacketProcessor("CL", &c);
    StrongMT<test::MockCorruptedPacketProcessor> lsP = new test::MockCorruptedPacketProcessor("LS", &c);
    StrongMT<test::MockCorruptedPacketProcessor> bcP = new test::MockCorruptedPacketProcessor("BC", &c);

    rpc::Gate& li = c.AddGate("LI", liP);
    rpc::Gate& cl = c.AddGate("CL", clP);
    rpc::Gate& ls = c.AddGate("LS", lsP);
    rpc::Gate& bc = c.AddGate("BC", bcP);
    c.ConnectGates(cl, li);
    c.ConnectGates(li, ls);
    c.ConnectGates(ls, bc);
    c.WaitForConnections();

    test::LocationServerFactory locationServerFactory(c.GetNode(ls, bc));
    test::ClientFactory clientFactory;
    test::BattleInstanceFactory battleInstanceFactory;
    ls.RegisterFactory<test::LocationServer>(locationServerFactory);
    cl.RegisterFactory<test::Client>(clientFactory);
    bc.RegisterFactory<test::BattleInstance>(battleInstanceFactory);

    StrongMT<test::RLocationServer> locationServer = c.GetNode(li, ls)->Create<test::RLocationServer>();
    StrongMT<test::RClient> client = c.GetNode(li, cl)->Create<test::RClient>();
    test::Client* realClient = waitForEntity<test::Client>(c.GetNode(cl, li), 1, c); 

    StrongMT<test::LocationInstance> locationInstance = new test::LocationInstance(locationServer, client);
    locationInstance->Start();
    TS_WAIT_FOR(realClient->instance != 0, 100);
    realClient->instance->DoIt();
    TS_WAIT_FOR(c.GetNode(bc, ls)->get<test::BattleInstance>(0)->isProcessed, 100);
  }

  void test_LatePacket()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> liP = new test::MockCorruptedPacketProcessor("LI", &c);
    StrongMT<test::MockCorruptedPacketProcessor> clP = new test::MockCorruptedPacketProcessor("CL", &c);
    StrongMT<test::MockCorruptedPacketProcessor> lsP = new test::MockCorruptedPacketProcessor("LS", &c);
    StrongMT<test::MockCorruptedPacketProcessor> bcP = new test::MockCorruptedPacketProcessor("BC", &c);

    rpc::Gate& li = c.AddGate("LI", liP);
    rpc::Gate& cl = c.AddGate("CL", clP);
    rpc::Gate& ls = c.AddGate("LS", lsP);
    rpc::Gate& bc = c.AddGate("BC", bcP);
    c.ConnectGates(cl, li);
    c.ConnectGates(li, ls);
    c.ConnectGates(ls, bc, 20);
    TS_WAIT_FOR(c.IsConnected(), 100);
    c.WaitForConnections();

    test::LocationServerFactory locationServerFactory(c.GetNode(ls, bc));
    test::ClientFactory clientFactory;
    test::BattleInstanceFactory battleInstanceFactory;
    ls.RegisterFactory<test::LocationServer>(locationServerFactory);
    cl.RegisterFactory<test::Client>(clientFactory);
    bc.RegisterFactory<test::BattleInstance>(battleInstanceFactory);

    StrongMT<test::RLocationServer> locationServer = c.GetNode(li, ls)->Create<test::RLocationServer>();
    StrongMT<test::RClient> client = c.GetNode(li, cl)->Create<test::RClient>();
    test::Client* realClient = waitForEntity<test::Client>(c.GetNode(cl, li), 1, c); 

    StrongMT<test::LocationInstance> locationInstance = new test::LocationInstance(locationServer, client);
    locationInstance->Start();
    TS_WAIT_FOR(realClient->instance != 0, 100);
    realClient->instance->DoIt();
    TS_WAIT_FOR(c.GetNode(bc, ls)->get<test::BattleInstance>(0) != 0, 100);
    //TS_WAIT_FOR(c.GetNode(bc, ls)->get<test::BattleInstance>(0)->isProcessed, 100);
  }
};

struct Test_CObjAsRemoteData : public CxxTest::TestSuite, RPCMixin   
{
  void test_Simple()
  {
    OneToManyCase c("cache");

    rpc::Gate& cache = c.GetRootGate();
    rpc::Gate& user = c.AddConnectedGate("user");

    test::DbRootFactory factory;
    cache.RegisterFactory<test::DbRoot>(factory);
    cache.RegisterFactory<test::HeroDescription>(factory);
    cache.RegisterFactory<test::ItemContainer>(factory);
    cache.RegisterFactory<test::Item>(factory);

    rpc::Node* node = c.GetNode(user, cache);
    StrongMT<test::RDbRoot> dbRoot = node->Create<test::RDbRoot>();
    StrongMT<rpc::SPtrValue<test::RHeroDescription>> redjack = new rpc::SPtrValue<test::RHeroDescription>;
    dbRoot->GetHeroDescription("redjack", redjack.Get(), &rpc::SPtrValue<test::RHeroDescription>::OnCall);
    TS_WAIT_FOR( redjack->IsSet(), 100 );

    TS_ASSERT_EQUALS(true, redjack->result->IsUpdated()); 
    TS_ASSERT_EQUALS(nstl::string("redjack"), nstl::string(redjack->result->name.c_str()));
    TS_ASSERT_EQUALS(2, redjack->result->containers.size());

    TS_ASSERT_EQUALS(true, redjack->result->containers[0]->IsUpdated());
    TS_ASSERT_EQUALS(true, redjack->result->containers[1]->IsUpdated());

    TS_ASSERT_EQUALS(0, redjack->result->containers[0]->type);
    TS_ASSERT_EQUALS(1, redjack->result->containers[1]->type);

    TS_ASSERT_EQUALS(1, redjack->result->containers[0]->items.size());
    TS_ASSERT_EQUALS(true, redjack->result->containers[0]->items[0]->IsUpdated());
    TS_ASSERT_EQUALS(nstl::string("Ring of Power"), nstl::string(redjack->result->containers[0]->items[0]->dbId.c_str()));
    TS_ASSERT_EQUALS(555, redjack->result->containers[0]->items[0]->itemId);

    StrongMT<rpc::SPtrValue<test::RHeroDescription>> sippul = new rpc::SPtrValue<test::RHeroDescription>;
    dbRoot->GetHeroDescription("sippul", sippul.Get(), &rpc::SPtrValue<test::RHeroDescription>::OnCall);
    TS_WAIT_FOR( sippul->IsSet(), 100 );
    TS_ASSERT_EQUALS(true, sippul->result->IsUpdated());
    TS_ASSERT_EQUALS(nstl::string("sippul"), nstl::string(sippul->result->name.c_str()));

    TS_ASSERT_EQUALS(2, sippul->result->containers.size());
    TS_ASSERT_EQUALS(true, redjack->result->containers[0]->IsUpdated());
    TS_ASSERT_EQUALS(true, redjack->result->containers[1]->IsUpdated());

    TS_ASSERT_EQUALS(0, sippul->result->containers[0]->type);
    TS_ASSERT_EQUALS(1, sippul->result->containers[1]->type);

    rpc::TransactionHandler t = rpc::StartTransaction(redjack->result, sippul->result);
    StrongMT<test::RItem> ring = redjack->result->containers[0]->items[0];
    redjack->result->containers[0]->items.remove(ring);
    sippul->result->containers[0]->items.push_back(ring);

    TS_ASSERT_EQUALS(0, redjack->result->containers[0]->items.size());
    TS_ASSERT_EQUALS(1, sippul->result->containers[0]->items.size());
    TS_ASSERT_EQUALS(nstl::string("Ring of Power"), nstl::string(sippul->result->containers[0]->items[0]->dbId.c_str()));
    TS_ASSERT_EQUALS(555, sippul->result->containers[0]->items[0]->itemId);
    rpc::Commit(t);

    test::DbRoot* localRoot = c.GetNode(cache, user)->get<test::DbRoot>(0);
    TS_WAIT_FOR(localRoot->redjack->containers[0]->items.size() == 0, 100);
    TS_WAIT_FOR(localRoot->sippul->containers[0]->items.size() == 1, 100);
    TS_ASSERT_EQUALS(nstl::string("Ring of Power"), nstl::string(localRoot->sippul->containers[0]->items[0]->dbId.c_str()));
  }

  void test_LinkToOtherStruct()
  {
    OneToManyCase c("cache");

    rpc::Gate& cache = c.GetRootGate();
    rpc::Gate& user = c.AddConnectedGate("user");

    test::DbRootFactory factory;
    cache.RegisterFactory<test::DbRoot>(factory);
    cache.RegisterFactory<test::HeroDescription>(factory);
    cache.RegisterFactory<test::ItemContainer>(factory);
    cache.RegisterFactory<test::Item>(factory);

    rpc::Node* node = c.GetNode(user, cache);
    StrongMT<test::RDbRoot> dbRoot = node->Create<test::RDbRoot>();
    StrongMT<rpc::SPtrValue<test::RHeroDescription>> redjack = new rpc::SPtrValue<test::RHeroDescription>;
    dbRoot->GetHeroDescription("redjack", redjack.Get(), &rpc::SPtrValue<test::RHeroDescription>::OnCall);
    TS_WAIT_FOR( redjack->IsSet(), 100 );

    StrongMT<rpc::SPtrValue<test::RHeroDescription>> sippul = new rpc::SPtrValue<test::RHeroDescription>;
    dbRoot->GetHeroDescription("sippul", sippul.Get(), &rpc::SPtrValue<test::RHeroDescription>::OnCall);
    TS_WAIT_FOR( sippul->IsSet(), 100 );

    rpc::TransactionHandler t = rpc::StartTransaction(redjack->result, sippul->result);
    redjack->result->friends.push_back(sippul->result);
    rpc::Commit(t);

    test::DbRoot* localRoot = c.GetNode(cache, user)->get<test::DbRoot>(0);
    TS_WAIT_FOR(localRoot->redjack->friends.size() == 1, 100);
    TS_ASSERT_EQUALS(localRoot->sippul, localRoot->redjack->friends[0]);
  }

  void test_CreateNewItem()
  {
    OneToManyCase c("cache");

    rpc::Gate& cache = c.GetRootGate();
    rpc::Gate& user = c.AddConnectedGate("user");

    test::DbRootFactory factory;
    cache.RegisterFactory<test::DbRoot>(factory);
    cache.RegisterFactory<test::HeroDescription>(factory);
    cache.RegisterFactory<test::ItemContainer>(factory);
    cache.RegisterFactory<test::Item>(factory);

    rpc::Node* node = c.GetNode(user, cache);
    StrongMT<test::RDbRoot> dbRoot = node->Create<test::RDbRoot>();
    StrongMT<rpc::SPtrValue<test::RHeroDescription>> redjack = new rpc::SPtrValue<test::RHeroDescription>;
    dbRoot->GetHeroDescription("redjack", redjack.Get(), &rpc::SPtrValue<test::RHeroDescription>::OnCall);
    TS_WAIT_FOR( redjack->IsSet(), 100 );

    test::DbRoot* localRoot = c.GetNode(cache, user)->get<test::DbRoot>(0);
    {
      rpc::TransactionHandler t = rpc::StartTransaction(redjack->result);
      StrongMT<test::RItem> ring0 = node->Create<test::RItem>();
      ring0->dbId = "test0";
      redjack->result->containers[1]->items.push_back(ring0);
      rpc::Commit(t);

      TS_WAIT_FOR(localRoot->redjack->containers[1]->items.size() == 1, 100);
      TS_ASSERT_EQUALS(nstl::string("test0"), nstl::string(localRoot->redjack->containers[1]->items[0]->dbId.c_str()));
    }
    {
      rpc::TransactionHandler t = rpc::StartTransaction(redjack->result);
      StrongMT<test::RItem> ring1 = node->Create<test::RItem>();
      ring1->dbId = "test1";
      redjack->result->containers[1]->items.push_back(ring1);
      StrongMT<test::RItem> ring2 = node->Create<test::RItem>();
      ring2->dbId = "test2";
      redjack->result->containers[1]->items.push_back(ring2);
      rpc::Commit(t);
      TS_WAIT_FOR(localRoot->redjack->containers[1]->items.size() == 3, 100);
      TS_ASSERT_EQUALS(nstl::string("test1"), nstl::string(localRoot->redjack->containers[1]->items[1]->dbId.c_str()));
      TS_ASSERT_EQUALS(nstl::string("test2"), nstl::string(localRoot->redjack->containers[1]->items[2]->dbId.c_str()));
    }
    {
      rpc::TransactionHandler t = rpc::StartTransaction(redjack->result);
      StrongMT<test::RItem> ring2 = node->Create<test::RItem>();
      ring2->dbId = "test2";
      redjack->result->containers[1]->items[0] = ring2;
      rpc::Commit(t);
    }
    TS_WAIT_FOR(nstl::string("test2") == nstl::string(localRoot->redjack->containers[1]->items[0]->dbId.c_str()), 100);
  }

  // TODO: assert if we are changing data without started transaction
  // TODO: assert if we are starting transaction inside already transaction data
  // TODO: check sizes of remote entities
  // TODO: check circles
  // TODO: check that all changes applied as one 
  // TODO: vector resize support
  // TODO: remote ptr to client and data cache connection forbid (read only)
  // TODO: work with cache local pointer through remote pointers to local pointers (in cache methods) 
  // TODO: data push from server to client
  // TODO: update data received while transaction on the way
  // TODO: hash_map support
};



