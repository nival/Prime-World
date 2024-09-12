#pragma once

namespace test
{

REMOTE class Item : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(Item, BaseObjectMT);
  RPC_ID();
public:
  REMOTE nstl::string dbId;
  REMOTE uint itemId;
};

class RItemContainer;
class RItem;
REMOTE class ItemContainer : public BaseObjectMT 
{
  NI_DECLARE_REFCOUNT_CLASS_1(ItemContainer, BaseObjectMT);
  RPC_ID();
public:
  REMOTE nstl::vector<StrongMT<Item> > items;
  REMOTE int type;
  REMOTE void MoveItem(RItemContainer* targetContainer, RItem* item)
  {
  }
};

REMOTE class HeroDescription : public BaseObjectMT 
{
  NI_DECLARE_REFCOUNT_CLASS_1(HeroDescription, BaseObjectMT);
  RPC_ID();
public:                                   // TODO: why we write public modifier ?
  REMOTE nstl::vector<StrongMT<ItemContainer> > containers;   
  REMOTE nstl::string name;
  REMOTE nstl::vector<StrongMT<HeroDescription> > friends;   
};

class RHeroDescription;

REMOTE class DbRoot : public BaseObjectMT  
{
  NI_DECLARE_REFCOUNT_CLASS_1(DbRoot, BaseObjectMT);
  RPC_ID();
public:
  DbRoot()
  {
    redjack = new HeroDescription;
    redjack->name = "redjack";
    {
      StrongMT<ItemContainer> container0 = new ItemContainer;
      container0->type = 0;
      StrongMT<ItemContainer> container1 = new ItemContainer;
      container1->type = 1;
      redjack->containers.push_back(container0);
      redjack->containers.push_back(container1);

      StrongMT<Item> item = new Item();
      item->dbId = "Ring of Power";
      item->itemId = 555;
      redjack->containers[0]->items.push_back(item);
    }

    sippul = new HeroDescription;
    sippul->name = "sippul";
    {
      StrongMT<ItemContainer> container0 = new ItemContainer;
      container0->type = 0;
      StrongMT<ItemContainer> container1 = new ItemContainer;
      container1->type = 1;
      sippul->containers.push_back(container0);
      sippul->containers.push_back(container1);
    }
  }
  REMOTE test::RHeroDescription* GetHeroDescription(const char* name);

  StrongMT<HeroDescription> redjack;
  StrongMT<HeroDescription> sippul;
};

REMOTE struct BattleInstance : BaseObjectMT
{
  RPC_ID();
  NI_DECLARE_REFCOUNT_CLASS_1(BattleInstance, BaseObjectMT);
public:
  BattleInstance():isProcessed(false)
  {
  }

  REMOTE void DoIt() 
  {
    isProcessed = true;
  }
  bool isProcessed;
};

class RBattleInstance;
class RLocationServer;
class RClient;

REMOTE struct LocationServer : BaseObjectMT
{
  RPC_ID();
  NI_DECLARE_REFCOUNT_CLASS_1(LocationServer, BaseObjectMT);
public:
  rpc::Node* coordinatorNode;
  LocationServer(rpc::Node* _coordinatorNode):coordinatorNode(_coordinatorNode) {}

  StrongMT<test::RBattleInstance> instance;
  
  REMOTE test::RBattleInstance* CreateNew();
  LocationServer() {}
};

struct LocationInstance : BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(LocationInstance, BaseObjectMT);
  LocationInstance(RLocationServer* _locationServer, RClient* _client):
  locationServer(_locationServer),
  client(_client)
  {
  }

  StrongMT<RLocationServer> locationServer;
  StrongMT<RClient> client;
  
  void Start();
  void OnCall(test::RBattleInstance* instance);
};

REMOTE struct Client : BaseObjectMT
{
  RPC_ID();
  NI_DECLARE_REFCOUNT_CLASS_1(Client, BaseObjectMT);
public:
  REMOTE void OnNewBattle(test::RBattleInstance* instance);
  StrongMT<test::RBattleInstance> instance;
};

} // test