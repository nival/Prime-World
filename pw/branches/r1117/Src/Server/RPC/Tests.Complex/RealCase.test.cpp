//!Component('RPC/all')
//!Component('RealCase.test')

#include <RPC/RPC.h>
#include <Server/RPC/RPCMixin.h>
#include <Server/RPC/LocalEntityFactory.h>

#include "RealCase.test.h"
#include "RRealCase.test.auto.h"
#include "LRealCase.test.auto.h"

SERIALIZE_FACTORY(HeroDesc)

namespace RealTest
{

struct TestUpdateCallback : rpc::IUpdateCallback
{
  bool isUpdated;
  const rpc::IRemoteEntity* entity;

  TestUpdateCallback() : isUpdated(false) {}

  void OnUpdated(const rpc::IRemoteEntity* entity)
  {
    isUpdated = true;
    this->entity = entity;
  }
};

void HeroHandler::SetLocationName( const nstl::string& locationName )
{
  if ( hero )
  {
    hero->locationName = locationName.c_str();
    hero->Commit();
  }
}

void HeroHandler::SetHero( RHeroDescription* _hero )
{
  hero = _hero;
  size = hero->vDescs.size();
}

void HeroHandler::HeroPublish()
{
  if ( hero )
  {
    hero->Publish();
  }
}

RealTest::RPlayer23* DatabaseRoot::GetPlayer(uint id)
{
  nstl::hash_map<uint, StrongMT<Player23> >::iterator it = players.find(id);
  if (it != players.end())
  {
    return RemotePtr<RPlayer23>(it->second);
  }
  StrongMT<Player23> result;
  if (id == 12)
  {
    result = new Player23();
    result->nick = "redjack";
    result->idZzima = id;
    result->kopeckAmount = 0;
  }
  if (result)
  {
    players.insertUnique(id, result);
  }
  return RemotePtr<RPlayer23>(result);
}

void Inventory::SetPlayer(RPlayer23* _player)
{
  player = _player;
}
}
struct Test_RemotePtrAsMember : public CxxTest::TestSuite, RPCMixin   
{
  void test_Simple()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::RemoteApi, RealTest::LRemoteApi>();
    rpc::LocalEntityFactory factory1(&leaf1);
    factory1.Register<RealTest::RemoteData, RealTest::LRemoteData>();

    rpc::Node* rl0 = c.GetNode(root, leaf0);
    rpc::Node* rl1 = c.GetNode(root, leaf1);

    StrongMT<RealTest::RRemoteApi> rapi = rl0->Create<RealTest::RRemoteApi>();
    StrongMT<RealTest::RRemoteData> rdata = rl1->Create<RealTest::RRemoteData>();

    c.Poll();
    c.Poll();

    /*TS_ASSERT_EQUALS(true, rdata->IsUpdated() );

    c.Poll();
    c.Poll();

    rdata->ptr = rapi;
    rdata->Commit();    

    c.Poll();
    c.Poll();

    rdata->ptr->Process();

    TS_WAIT_FOR(c.GetNode(leaf0, root)->get<RealTest::RemoteApi>(0)->isProcessed, 100);*/
  }

  void test_VectorOfData()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
    desc->vAngles.append( CQuat(1.0f,2.0f,3.0f) );
    desc->vAngles.append( CQuat(2.0f,4.0f,6.0f) );
    desc->Commit();
    HeroDesc hd;
    hd.age = 5;
    hd.money = 10;
    desc->vDescs.append( hd );
    desc->Commit();
    TS_WAIT_FOR( desc->IsUpdated(), 100 );
    RealTest::HeroDescription* ldesc = c.GetNode(leaf0, root)->get<RealTest::HeroDescription>(0);
    TS_WAIT_FOR(2 == ldesc->vAngles.size(), 100);
    TS_WAIT_FOR(1 == ldesc->vDescs.size(), 100);
  }

  void test_VectorOfDataInLocalRObject()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();
    factory0.Register<RealTest::HeroHandler, RealTest::LHeroHandler>();

    rpc::LocalEntityFactory factoryRoot(&root);
    factoryRoot.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();
    factoryRoot.Register<RealTest::HeroHandler, RealTest::LHeroHandler>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroHandler> herohandler = r01->Create<RealTest::RHeroHandler>();

    StrongMT<RealTest::HeroDescription> desc = new RealTest::HeroDescription();
    desc->vAngles.push_back( CQuat(1.0f,2.0f,3.0f) );
    desc->vAngles.push_back( CQuat(2.0f,4.0f,6.0f) );
    HeroDesc hd;
    hd.age = 5;
    hd.money = 10;
    desc->vDescs.push_back( hd );

    herohandler->SetHero( RemotePtr<RealTest::RHeroDescription>(desc) );
    c.Poll();
    c.Poll();
    c.Poll();

    StrongMT<rpc::RValue<int>> g = new rpc::RValue<int>;
    herohandler->GetSize( g.Get(), &rpc::RValue<int>::OnCall );
    TS_WAIT_FOR(1 == g->result, 100);
  }

  void test_FastData()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
    desc->locationName = "tik";
    desc->Commit();
    TS_WAIT_FOR( desc->IsUpdated(), 100 );
    RealTest::HeroDescription* ldesc = c.GetNode(leaf0, root)->get<RealTest::HeroDescription>(0);
    TS_WAIT_FOR(nstl::string("tik") == nstl::string(ldesc->locationName.c_str()), 100);
  }

  void test_HeroDescription()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
    TS_WAIT_FOR( desc->IsUpdated(), 100 );

    desc->x = 1.f;
    desc->y = 2.f;
    desc->z = 3.f;

    desc->i = 4.f;
    desc->j = 5.f;
    desc->k = 6.f;
    desc->w = 7.f;

    desc->locationName = "test";    
    desc->Commit();

    RealTest::HeroDescription* ldesc = c.GetNode(leaf0, root)->get<RealTest::HeroDescription>(0);

    TS_WAIT_FOR(ldesc->y==2.f, 100);
    TS_ASSERT_EQUALS(nstl::string("test"), nstl::string(ldesc->locationName.c_str()));
  }

  void test_MemoryLeak()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
    TS_WAIT_FOR( desc->IsUpdated(), 100 );
    StrongMT<rpc::RValue<int>> getter = new rpc::RValue<int>;
    desc->GetTestInt( getter.Get(), &rpc::RValue<int>::OnCall  );
  }

  void test_MultiROnL()
  {
    ManyToManyCase c;
    rpc::Gate& root = c.AddGate("root");
    rpc::Gate& leaf0 = c.AddGate("leaf0");
    rpc::Gate& leaf1 = c.AddGate("leaf1");
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    //rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    //rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<RealTest::HeroDescription> server_hero = new RealTest::HeroDescription();

    root.RegisterObject( server_hero, "rpc:://hero" );

    StrongMT<rpc::SPtrValue<RealTest::RHeroDescription>> r1 = new rpc::SPtrValue<RealTest::RHeroDescription>;
    a10->Query<RealTest::RHeroDescription>("rpc:://hero", r1.Get(), &rpc::SPtrValue<RealTest::RHeroDescription>::OnCall);
    TS_WAIT_FOR( r1->IsSet(), 100 );
    r1->result->Update();
    TS_WAIT_FOR( r1->result->IsUpdated(), 100 );

    StrongMT<rpc::SPtrValue<RealTest::RHeroDescription>> r2 = new rpc::SPtrValue<RealTest::RHeroDescription>;
    a20->Query<RealTest::RHeroDescription>("rpc:://hero", r2.Get(), &rpc::SPtrValue<RealTest::RHeroDescription>::OnCall);
    TS_WAIT_FOR( r2->IsSet(), 100 );

    r2->result->Update();
    TS_WAIT_FOR( r2->result->IsUpdated(), 100 );

    r1->result->locationName = "Lofik";
    r1->result->Commit();

    RealTest::HeroDescription* ldesc = c.GetNode(root, leaf0)->get<RealTest::HeroDescription>(0);
    TS_WAIT_FOR(nstl::string("Lofik") == nstl::string(ldesc->locationName.c_str()), 100);

    r2->result->locationName = "tufyak";
    r2->result->Commit();
    TS_WAIT_FOR(nstl::string("tufyak") == nstl::string(ldesc->locationName.c_str()), 100);

    r2->result->ReadOnly( true );

    r2->result->locationName = "badname";
    r2->result->Commit();

    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    TS_ASSERT_EQUALS(nstl::string("tufyak"), nstl::string(ldesc->locationName.c_str()));
    TS_ASSERT_EQUALS(nstl::string("tufyak"), nstl::string(r2->result->locationName.c_str()));
    TS_ASSERT_EQUALS(nstl::string("Lofik"), nstl::string(r1->result->locationName.c_str()));

    RealTest::TestUpdateCallback cb;
    r1->result->SetUpdateCallback( &cb );
    TS_ASSERT( !cb.isUpdated );
    r2->result->Publish();
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    TS_ASSERT( cb.isUpdated );
    TS_ASSERT_EQUALS(nstl::string("tufyak"), nstl::string(r1->result->locationName.c_str()));
  }

  void test_MultiROnMultiL()
  {
    ManyToManyCase c;
    rpc::Gate& root = c.AddGate("root");
    rpc::Gate& leaf0 = c.AddGate("leaf0");
    rpc::Gate& leaf1 = c.AddGate("leaf1");
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.ConnectGates(leaf0, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    //rpc::Node* a10 = c.GetNode(leaf0, root);
    //rpc::Node* a20 = c.GetNode(leaf1, root);
    TS_WAIT_FOR(c.IsConnected(), 100);

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::LocalEntityFactory factory1(&leaf1);
    factory1.Register<RealTest::HeroHandler, RealTest::LHeroHandler>();

    StrongMT<RealTest::RHeroDescription> hero = a01->Create<RealTest::RHeroDescription>();
    TS_WAIT_FOR( hero->IsUpdated(), 100 );
    StrongMT<RealTest::RHeroHandler> obj = a02->Create<RealTest::RHeroHandler>();

    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    obj->SetHero(hero);
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    RealTest::HeroDescription* lhero = c.GetNode(leaf0, root)->get<RealTest::HeroDescription>(0);
    //RealTest::HeroHandler* lobj = c.GetNode(leaf1, root)->get<RealTest::HeroHandler>(0);

    hero->locationName = "tyufyak";
    hero->Commit();
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    TS_WAIT_FOR(nstl::string("tyufyak") == nstl::string(lhero->locationName.c_str()), 100);

    obj->SetLocationName("Lofik");
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    obj->HeroPublish();
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();
    TS_WAIT_FOR(nstl::string("Lofik") == nstl::string(lhero->locationName.c_str()), 100);
    TS_ASSERT_EQUALS(nstl::string("Lofik"), nstl::string(hero->locationName.c_str()));
  }

  void test_OPublish()
  {
    ManyToManyCase c;
    rpc::Gate& root = c.AddGate("root");
    rpc::Gate& leaf0 = c.AddGate("leaf0");
    rpc::Gate& leaf1 = c.AddGate("leaf1");
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    //rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    //rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<RealTest::HeroDescription> server_hero = new RealTest::HeroDescription();

    root.RegisterObject( server_hero, "rpc:://hero" );

    StrongMT<rpc::SPtrValue<RealTest::RHeroDescription>> r1 = new rpc::SPtrValue<RealTest::RHeroDescription>;
    a10->Query<RealTest::RHeroDescription>("rpc:://hero", r1.Get(), &rpc::SPtrValue<RealTest::RHeroDescription>::OnCall);
    TS_WAIT_FOR( r1->IsSet(), 100 );
    r1->result->Update();
    TS_WAIT_FOR( r1->result->IsUpdated(), 100 );

    StrongMT<rpc::SPtrValue<RealTest::RHeroDescription>> r2 = new rpc::SPtrValue<RealTest::RHeroDescription>;
    a20->Query<RealTest::RHeroDescription>("rpc:://hero", r2.Get(), &rpc::SPtrValue<RealTest::RHeroDescription>::OnCall);
    TS_WAIT_FOR( r2->IsSet(), 100 );

    r2->result->Update();
    TS_WAIT_FOR( r2->result->IsUpdated(), 100 );

    r1->result->locationName = "Lofik";
    r1->result->Commit();

    RealTest::HeroDescription* ldesc = c.GetNode(root, leaf0)->get<RealTest::HeroDescription>(0);
    TS_WAIT_FOR(nstl::string("Lofik") == nstl::string(ldesc->locationName.c_str()), 100);

    r2->result->locationName = "tufyak";
    r2->result->Commit();
    TS_WAIT_FOR(nstl::string("tufyak") == nstl::string(ldesc->locationName.c_str()), 100);

    r1->result->DoThenPublish();
    c.Poll();
    c.Poll();
    c.Poll();
    c.Poll();

    TS_ASSERT_EQUALS(nstl::string("OObject"), nstl::string(r2->result->locationName.c_str()));
    TS_ASSERT_EQUALS(nstl::string("OObject"), nstl::string(r1->result->locationName.c_str()));
  }

  void test_HeroDescriptionSerializedStructs()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
    TS_WAIT_FOR( desc->IsUpdated(), 100 );

    /*RealTest::HeroDesc d;
    d.age = 555;
    d.money = 777;

    desc->descs.push_back(d);
    desc->Commit();

    RealTest::HeroDescription* ldesc = c.GetNode(leaf0, root)->get<RealTest::HeroDescription>(0);

    TS_WAIT_FOR(ldesc->descs.size() == 1, 100);
    TS_ASSERT_EQUALS(555, ldesc->descs[0].age);
    TS_ASSERT_EQUALS(777, ldesc->descs[0].money);*/
  }


  void test_HeroDescriptionCommitAndCallFunc()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::LocalEntityFactory factory0(&leaf0);
    factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

    rpc::Node* r01 = c.GetNode(root, leaf0);
    StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
    TS_WAIT_FOR( desc->IsUpdated(), 100 );

    desc->x = 1.f;
    desc->y = 2.f;
    desc->z = 3.f;

    desc->i = 4.f;
    desc->j = 5.f;
    desc->k = 6.f;
    desc->w = 7.f;

    desc->locationName = "test";    

    /*RealTest::Character character;
    character.name = "Lofik";
    character.description = "Hmm";

    ..desc->SetCharacter( character );*/

    desc->Commit();

    RealTest::HeroDescription* ldesc = c.GetNode(leaf0, root)->get<RealTest::HeroDescription>(0);

    TS_WAIT_FOR(ldesc->y==2.f, 100);
    TS_ASSERT_EQUALS(nstl::string("test"), nstl::string(ldesc->locationName.c_str()));
  }

  void test_VectorOfCObjs()
  {

  }
};

struct Test_RealCasePW : public CxxTest::TestSuite, RPCMixin   
{
  void test_Login()
  {
    OneToManyCase c("cache");

    rpc::Gate& cache = c.GetRootGate();
    rpc::Gate& user = c.AddConnectedGate("user");
    rpc::LocalEntityFactory factory(&cache);
    factory.Register<RealTest::DatabaseRoot, RealTest::LDatabaseRoot>();
    factory.Register<RealTest::Character, RealTest::LCharacter>();
    factory.Register<RealTest::Item, RealTest::LItem>();
    factory.Register<RealTest::Achievement, RealTest::LAchievement>();
    factory.Register<RealTest::CharacterItem, RealTest::LCharacterItem>();
    factory.Register<RealTest::PlayerCharacter, RealTest::LPlayerCharacter>();
    factory.Register<RealTest::Player23, RealTest::LPlayer23>();

    rpc::Node* node = c.GetNode(user, cache);
    StrongMT<RealTest::RDatabaseRoot> dbRoot = node->Create<RealTest::RDatabaseRoot>();

    StrongMT<rpc::SPtrValue<RealTest::RPlayer23>> redjack = new rpc::SPtrValue<RealTest::RPlayer23>;
    dbRoot->GetPlayer(12, redjack.Get(), &rpc::SPtrValue<RealTest::RPlayer23>::OnCall);
    TS_WAIT_FOR( redjack->IsSet(), 100 );
    TS_ASSERT_EQUALS(nstl::string("redjack"), nstl::string(redjack->result->nick.c_str()));
    {
      rpc::TransactionHandler h = rpc::StartTransaction(redjack->result);
      redjack->result->isOnline = true;
      rpc::Commit(h);
    }

    {
      rpc::TransactionHandler h = rpc::StartTransaction(redjack->result);
      StrongMT<RealTest::RItem> ring = node->Create<RealTest::RItem>();
      redjack->result->items.push_back(ring);
      rpc::Commit(h);
    }
  }

  void test_UpdateCallbackForOneEntity()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> processor0 = new test::MockCorruptedPacketProcessor("server", &c);
    StrongMT<test::MockCorruptedPacketProcessor> processor1 = new test::MockCorruptedPacketProcessor("cache", &c);
    StrongMT<test::MockCorruptedPacketProcessor> processor2 = new test::MockCorruptedPacketProcessor("client", &c);

    rpc::Gate& server = c.AddGate("server", processor0);
    rpc::Gate& cache = c.AddGate("cache", processor1);
    rpc::Gate& client = c.AddGate("client", processor2);
    c.ConnectGates(server, cache);
    c.ConnectGates(client, server);
    c.ConnectGates(client, cache);

    rpc::LocalEntityFactory factory(&cache);
    factory.Register<RealTest::DatabaseRoot, RealTest::LDatabaseRoot>();
    factory.Register<RealTest::Character, RealTest::LCharacter>();
    factory.Register<RealTest::Item, RealTest::LItem>();
    factory.Register<RealTest::Achievement, RealTest::LAchievement>();
    factory.Register<RealTest::CharacterItem, RealTest::LCharacterItem>();
    factory.Register<RealTest::PlayerCharacter, RealTest::LPlayerCharacter>();
    factory.Register<RealTest::Player23, RealTest::LPlayer23>();

    rpc::LocalEntityFactory factory1(&client);
    factory1.Register<RealTest::Inventory, RealTest::LInventory>();

    rpc::Node* server_cache = c.GetNode(server, cache);
    rpc::Node* cache_server = c.GetNode(cache, server);
    rpc::Node* server_client = c.GetNode(server, client);
    rpc::Node* client_server = c.GetNode(client, server);

    StrongMT<RealTest::RDatabaseRoot> dbRoot = server_cache->Create<RealTest::RDatabaseRoot>();
    RealTest::DatabaseRoot* ldbRoot = waitForEntity<RealTest::DatabaseRoot>(cache_server, 0, c);

    StrongMT<rpc::SPtrValue<RealTest::RPlayer23>> redjack = new rpc::SPtrValue<RealTest::RPlayer23>;
    dbRoot->GetPlayer(12, redjack.Get(), &rpc::SPtrValue<RealTest::RPlayer23>::OnCall);
    TS_WAIT_FOR( redjack->IsSet(), 100 );

    StrongMT<RealTest::RInventory> inventory = server_client->Create<RealTest::RInventory>();
    RealTest::Inventory* linventory = waitForEntity<RealTest::Inventory>(client_server, 2, c);

    inventory->SetPlayer(redjack->result);
    TS_WAIT_FOR(linventory->player, 100);

    linventory->player->Link();
    TS_WAIT_FOR(ldbRoot->players[12]->isLinked, 100);

    test::UpdateCallback cb;
    linventory->player->SetUpdateCallback(&cb);
    {
      StrongMT<RealTest::RItem> ring0 = server_cache->Create<RealTest::RItem>();
      redjack->result->items.push_back(ring0);
      redjack->result->Commit(true);
      TS_WAIT_FOR(ldbRoot->players[12]->items.size() == 1, 100);
    }
    cb.Reset();
    {
      redjack->result->items[0]->name = "Test";
      redjack->result->items[0]->Commit(true);
    }
    TS_WAIT_FOR(cb.isUpdated, 100);
    TS_ASSERT_EQUALS(1, cb.entities.size());
    TS_ASSERT_EQUALS(linventory->player->items[0].Get(), cb.entities[0]);
    TS_ASSERT_EQUALS(nstl::string("Test"), nstl::string(linventory->player->items[0]->name.c_str()));
  }

  void test_UpdateCallbackOnVectorOfStructs()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> processor0 = new test::MockCorruptedPacketProcessor("server", &c);
    StrongMT<test::MockCorruptedPacketProcessor> processor1 = new test::MockCorruptedPacketProcessor("cache", &c);
    StrongMT<test::MockCorruptedPacketProcessor> processor2 = new test::MockCorruptedPacketProcessor("client", &c);

    rpc::Gate& server = c.AddGate("server", processor0);
    rpc::Gate& cache = c.AddGate("cache", processor1);
    rpc::Gate& client = c.AddGate("client", processor2);
    c.ConnectGates(server, cache);
    c.ConnectGates(client, server);

    rpc::LocalEntityFactory factory(&cache);
    factory.Register<RealTest::DatabaseRoot, RealTest::LDatabaseRoot>();
    factory.Register<RealTest::Character, RealTest::LCharacter>();
    factory.Register<RealTest::Item, RealTest::LItem>();
    factory.Register<RealTest::Achievement, RealTest::LAchievement>();
    factory.Register<RealTest::CharacterItem, RealTest::LCharacterItem>();
    factory.Register<RealTest::PlayerCharacter, RealTest::LPlayerCharacter>();
    factory.Register<RealTest::Player23, RealTest::LPlayer23>();

    rpc::LocalEntityFactory factory1(&client);
    factory1.Register<RealTest::Inventory, RealTest::LInventory>();

    rpc::Node* server_cache = c.GetNode(server, cache);
    rpc::Node* cache_server = c.GetNode(cache, server);
    rpc::Node* server_client = c.GetNode(server, client);
    rpc::Node* client_server = c.GetNode(client, server);

    StrongMT<RealTest::RDatabaseRoot> dbRoot = server_cache->Create<RealTest::RDatabaseRoot>();
    RealTest::DatabaseRoot* ldbRoot = waitForEntity<RealTest::DatabaseRoot>(cache_server, 0, c);

    StrongMT<rpc::SPtrValue<RealTest::RPlayer23>> redjack = new rpc::SPtrValue<RealTest::RPlayer23>;
    dbRoot->GetPlayer(12, redjack.Get(), &rpc::SPtrValue<RealTest::RPlayer23>::OnCall);
    TS_WAIT_FOR( redjack->IsSet(), 100 );

    StrongMT<RealTest::RInventory> inventory = server_client->Create<RealTest::RInventory>();
    RealTest::Inventory* linventory = waitForEntity<RealTest::Inventory>(client_server, 2, c);

    inventory->SetPlayer(redjack->result);
    TS_WAIT_FOR(linventory->player, 100);

    test::UpdateCallback cb;
    linventory->player->SetUpdateCallback(&cb);

    // test that UpdateCallback will be called for two items and root struct
    {
      StrongMT<RealTest::RItem> ring0 = server_cache->Create<RealTest::RItem>();
      redjack->result->items.push_back(ring0);
      StrongMT<RealTest::RItem> ring1 = server_cache->Create<RealTest::RItem>();
      redjack->result->items.push_back(ring1);
      redjack->result->Commit(true);
      TS_WAIT_FOR(ldbRoot->players[12]->items.size() == 2, 100);
    }
    TS_WAIT_FOR(cb.isUpdated, 100);
    TS_ASSERT_EQUALS(3, cb.entities.size());

    // add two more items and wait for update callback for all of them
    cb.Reset();
    {
      StrongMT<RealTest::RItem> ring0 = server_cache->Create<RealTest::RItem>();
      redjack->result->items.push_back(ring0);
      StrongMT<RealTest::RItem> ring1 = server_cache->Create<RealTest::RItem>();
      redjack->result->items.push_back(ring1);
      redjack->result->Commit(true);
      TS_WAIT_FOR(ldbRoot->players[12]->items.size() == 4, 100);
    }
    TS_WAIT_FOR(cb.isUpdated, 100);
    TS_ASSERT_EQUALS(4, linventory->player->items.size());
    TS_ASSERT_EQUALS(3, cb.entities.size());                // 3 entities have been updated (player and 2 new rings)
    TS_ASSERT_EQUALS(true, cb.entities.find(linventory->player) != cb.entities.end());
    TS_ASSERT_EQUALS(true, cb.entities.find(linventory->player->items[2]) != cb.entities.end());
    TS_ASSERT_EQUALS(true, cb.entities.find(linventory->player->items[3]) != cb.entities.end());

    for (int i=0;i<100;++i)
    {
      c.Poll();
    }
    cb.Reset();
    {
      //redjack->result->items[0]->name = "Test";
      //redjack->result->items[0]->Commit(true);
    }
    //TS_WAIT_FOR(cb.isUpdated, 100);
    //TS_ASSERT_EQUALS(1, cb.entities.size());
    //TS_ASSERT_EQUALS(linventory->player->items[0].GetPtr(), cb.entities[0]);
    //TS_ASSERT_EQUALS(nstl::string("Test"), nstl::string(linventory->player->items[0]->name.c_str()));
  }

  //void test_ActiveTransactionAssert()
  //{
  //  OneToManyCase c("root");

  //  rpc::Gate& root = c.GetRootGate();
  //  rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

  //  rpc::LocalEntityFactory factory0(&leaf0);
  //  factory0.Register<RealTest::HeroDescription, RealTest::LHeroDescription>();

  //  rpc::Node* r01 = c.GetNode(root, leaf0);
  //  StrongMT<RealTest::RHeroDescription> desc = r01->Create<RealTest::RHeroDescription>();
  //  desc->vAngles.append( CQuat(1.0f,2.0f,3.0f) );
  //  desc->vAngles.append( CQuat(2.0f,4.0f,6.0f) );
  //  HeroDesc hd;
  //  hd.age = 5;
  //  hd.money = 10;
  //  desc->vDescs.append( hd );
  //  desc->Commit();
  //}
};
