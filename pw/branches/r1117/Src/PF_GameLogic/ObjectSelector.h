#pragma once

namespace NWorld
{
class PFAbilityData;
class PFWorld;
}

namespace NGameX
{

struct PredicateSelector;

class ObjectSelector
{
  StaticArray<unsigned, NDb::KnownEnum<NDb::EUnitCategory>::sizeOf> unitCategories;
  CPtr<NWorld::PFWorld> pWorld;
  NDb::EFaction ourFaction;

public:
  ObjectSelector();
  void Init( NWorld::PFWorld* world, NDb::EFaction faction );
  int GetBestObject( const NScene::PickResult& pickResult, const CRay& cursorRay, bool isAbilityUse, const NWorld::PFAbilityData* ability );
private:
  NDb::EUnitCategory GetUnitCategory( PF_Core::WorldObjectBase* _worldObject );
  bool IsAbilityUseOnEnemy( const NWorld::PFAbilityData* ability );
  bool SelectObject( const NScene::PickResult& pickResult, const CRay& cursorRay, int* objectId, PredicateSelector* selector );

};

}