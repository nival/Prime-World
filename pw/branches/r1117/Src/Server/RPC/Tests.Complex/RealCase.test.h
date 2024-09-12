#pragma once

struct HeroDesc : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  int age;
  int money;
  ZEND int operator&( IBinSaver &f ) { f.Add(2, &age); f.Add(3, &money); return 0; }
};

namespace RealTest
{

REMOTE class Character : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(Character, BaseObjectMT);
  RPC_ID();
public:                                   
  REMOTE nstl::string name;
  REMOTE nstl::string description;
};

REMOTE class Item : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(Item, BaseObjectMT);
  RPC_ID();
public:                                   
  REMOTE nstl::string name;
};

REMOTE class Achievement : public BaseObjectMT 
{
  NI_DECLARE_REFCOUNT_CLASS_1(Achievement, BaseObjectMT);
  RPC_ID();
public:                                   
  REMOTE nstl::string name;
};

REMOTE class CharacterItem : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(CharacterItem, BaseObjectMT);
  RPC_ID();
public:                                   
  REMOTE StrongMT<Item> item;
  REMOTE int amount;
};

REMOTE class PlayerCharacter : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(PlayerCharacter, BaseObjectMT);
  RPC_ID();
public:                                   
  REMOTE uint level;   
  REMOTE StrongMT<Character> character;
  REMOTE nstl::vector<StrongMT<Achievement>> achievements;
  REMOTE nstl::vector<StrongMT<CharacterItem>> items;
};
                    
REMOTE class Player23 : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(Player23, BaseObjectMT);
  RPC_ID();
public:
  Player23():isLinked(false) {}

  REMOTE uint idZzima;   
  REMOTE nstl::string nick;
  REMOTE bool isOnline;   
  REMOTE int kopeckAmount;   
  REMOTE nstl::vector<StrongMT<Player23>> friends;   
  REMOTE nstl::vector<StrongMT<PlayerCharacter>> characters;   
  REMOTE nstl::vector<StrongMT<Item>> items;   

  REMOTE void Link() { isLinked = true; }
  bool isLinked;
};

REMOTE class HeroDescription : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(HeroDescription, BaseObjectMT);
  RPC_ID();
public:                     
  HeroDescription()
  {
    x = 0.f;
    y = 0.f;
    z = 0.f;
    i = 0.f;
    j = 0.f;
    k = 0.f;
    w = 0.f;
  }
  REMOTE float x;
  REMOTE float y;
  REMOTE float z;

  REMOTE float i;
  REMOTE float j;
  REMOTE float k;
  REMOTE float w;

  REMOTE nstl::string resourceName;
  REMOTE nstl::string locationName;
  REMOTE CQuat quat;

  REMOTE nstl::vector<CQuat> vAngles;
  REMOTE nstl::vector<HeroDesc> vDescs;

/*  Character character;

  void SetCharacter( const Character& _character )
  {
    character = _character;
  }
*/
  REMOTE int GetTestInt()
  {
    return 6;
  }

  REMOTE void DoThenPublish()
  {
    locationName = "OObject";
    owner->Publish();
  }
};

class RHeroDescription;

REMOTE class HeroHandler : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(HeroHandler, BaseObjectMT);
  RPC_ID();

  StrongMT<RHeroDescription> hero;
  int size;

public:      
  HeroHandler() : hero(0), size(0) {}

  REMOTE void SetHero( RHeroDescription* _hero );
  REMOTE void SetLocationName( const nstl::string& locationName );
  REMOTE void HeroPublish();
  REMOTE int GetSize()
  {
    return size;
  }
};

class RPlayer23;
REMOTE class DatabaseRoot : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(DatabaseRoot, BaseObjectMT);
  RPC_ID();
public:
  REMOTE RPlayer23* GetPlayer(uint id);
  nstl::hash_map<uint, StrongMT<Player23>> players;
private:
};

REMOTE class RemoteApi : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(RemoteApi, BaseObjectMT);
  RPC_ID();
  bool isProcessed;
public:
  RemoteApi():isProcessed(false) {}

  REMOTE void Process() { isProcessed = true; }
};

REMOTE class RemoteData : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(RemoteData, BaseObjectMT);
  RPC_ID();
public:
  RemoteData() {}

  StrongMT<RemoteApi> ptr;
};

REMOTE class Inventory : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(Inventory, BaseObjectMT);
  RPC_ID();
public:
  Inventory() {}
  StrongMT<RPlayer23> player;

  REMOTE void SetPlayer(RPlayer23* player);
};       

} // test