#include "stdafx.h"
#include "ObjectSelector.h"
#include "PFAbilityData.h"
#include "PFLogicObject.h"

namespace NGameX
{

struct PredicateSelector
{
  virtual bool IsIt( PF_Core::WorldObjectBase* _worldObject, NDb::EUnitCategory category ) const = 0;
};

struct PredicateAllyHero : PredicateSelector
{
  NDb::EFaction ourFaction;

  PredicateAllyHero( NDb::EFaction ourFaction ) : ourFaction(ourFaction) {}
  virtual bool IsIt( PF_Core::WorldObjectBase* object, NDb::EUnitCategory category ) const
  {
    if ( category == NDb::UNITCATEGORY_HEROES ) 
    {
      NWorld::PFLogicObject* hero =  dynamic_cast<NWorld::PFLogicObject*>( object );
      if ( hero->GetFaction() == ourFaction )
        return true;
    }
    return false;
  }
};

struct PredicateEnemyHero : PredicateSelector
{
  NDb::EFaction ourFaction;

  PredicateEnemyHero( NDb::EFaction ourFaction ) : ourFaction(ourFaction) {}
  virtual bool IsIt( PF_Core::WorldObjectBase* object, NDb::EUnitCategory category ) const
  {
    if ( category == NDb::UNITCATEGORY_HEROES ) 
    {
      NWorld::PFLogicObject* hero =  dynamic_cast<NWorld::PFLogicObject*>( object );
      if ( hero->GetFaction() != ourFaction )
        return true;
    }
    return false;
  }
};

struct PredicateEnemy : PredicateSelector
{
  NDb::EFaction ourFaction;

  PredicateEnemy( NDb::EFaction ourFaction ) : ourFaction(ourFaction) {}
  virtual bool IsIt( PF_Core::WorldObjectBase* object, NDb::EUnitCategory category ) const
  {
    if ( category == NDb::UNITCATEGORY_HEROES ) 
    {
      NWorld::PFLogicObject* hero =  dynamic_cast<NWorld::PFLogicObject*>( object );
      if ( hero->GetFaction() != ourFaction )
        return true;
    }
    return false;
  }
};

ObjectSelector::ObjectSelector() 
: unitCategories()
{
  const int categoriesCount = NDb::KnownEnum<NDb::EUnitCategory>::sizeOf;
  NI_ASSERT(unitCategories.capacity()      == categoriesCount, "" );
  for(int i = 0, count = unitCategories.capacity(); i < count; ++i)
  {
    unitCategories[i] = 0;
  }

  if(NDb::Ptr<NDb::UnitCategories> pCategores = NDb::SessionRoot::GetRoot()->uiRoot->unitCategories )
  {
    const int unitTypesCount = NDb::KnownEnum<NDb::EUnitType>::SizeOf();
    NI_ASSERT(unitTypesCount == pCategores->elements.size(), "" );
    for(int i = NDb::UNITTYPE_INVALID + 1; i < unitTypesCount; ++i )
      if( NDb::UNITCATEGORY_INVALID != pCategores->elements[i] )
        unitCategories[pCategores->elements[i]] |= (1 << i);
  }
}

int ObjectSelector::GetBestObject( const NScene::PickResult& pickResult, const CRay& cursorRay, bool isAbilityUse, const NWorld::PFAbilityData* ability )
{
  const int intersectionsCount = pickResult.usedIntersections;
  
  if ( intersectionsCount == 0 )
    return PF_Core::INVALID_OBJECT_ID;

  bool isSelected = false;
  int objectId = PF_Core::INVALID_OBJECT_ID;

  if ( isAbilityUse && !IsAbilityUseOnEnemy( ability ) )
  {
    PredicateAllyHero selector( ourFaction );
    isSelected = SelectObject( pickResult, cursorRay, &objectId, &selector );
    if ( isSelected )
      return objectId;
  }
  else if ( isAbilityUse && IsAbilityUseOnEnemy( ability ) )
  {
    PredicateEnemyHero selector( ourFaction );
    isSelected = SelectObject( pickResult, cursorRay, &objectId, &selector );
    if ( isSelected )
      return objectId;
  }
  else if ( !isAbilityUse )
  {
    PredicateEnemy selector( ourFaction );
    isSelected = SelectObject( pickResult, cursorRay, &objectId, &selector );
    if ( isSelected )
      return objectId;
  }

  struct PredicateAnything : PredicateSelector
  {
    virtual bool IsIt( PF_Core::WorldObjectBase* object, NDb::EUnitCategory category ) const
    {
      return true;
    }
  } selector;

  isSelected = SelectObject( pickResult, cursorRay, &objectId, &selector );
  if ( isSelected )
    return objectId;

  return PF_Core::INVALID_OBJECT_ID;
}

NDb::EUnitCategory ObjectSelector::GetUnitCategory( PF_Core::WorldObjectBase* _worldObject )
{
  if ( NWorld::PFLogicObject* pLO = dynamic_cast<NWorld::PFLogicObject*>( _worldObject ) )
  {
    const NDb::EUnitType type = pLO->GetUnitType();
    for(int i = 0; i < NDb::KnownEnum<NDb::EUnitCategory>::sizeOf; ++i)
    {
      if ( unitCategories[i] & (1 << type ) )
      {
        return static_cast<NDb::EUnitCategory>(i);
      }
    }
  }

  return NDb::UNITCATEGORY_INVALID;
}

void ObjectSelector::Init( NWorld::PFWorld* world, NDb::EFaction faction )
{
  pWorld = world;
  ourFaction = faction;
}

bool ObjectSelector::IsAbilityUseOnEnemy( const NWorld::PFAbilityData* ability )
{
  if ( ability && ability->GetDBDesc() && (ability->GetDBDesc()->targetType & NDb::SPELLTARGET_ALLY) && !(ability->GetDBDesc()->targetType & NDb::SPELLTARGET_ENEMY) )
  {
    return false;
  }
  
  return true;
}

bool ObjectSelector::SelectObject( const NScene::PickResult& pickResult, const CRay& cursorRay, int* objectId, PredicateSelector* selector )
{
  CPtr<PF_Core::WorldObjectBase> pPO = NULL;
  NScene::SceneObject* pPSO = NULL;

  const int intersectionsCount = pickResult.usedIntersections;

  float minDistance = FLT_MAX;

  for ( int i = 0; i < intersectionsCount; ++i)
  {
    NScene::Intersection const& intersection = pickResult.intersections[i];

    if ( NScene::SceneObject* pSO = intersection.pHull ? intersection.pHull->GetSceneObject() : NULL)
    {
      const int objectID = pSO->GetOwnerID();
      if( -1 == objectID || pSO->IsForbidPick() )
        continue;

      float distanceFromRay = (cursorRay.ptDir ^ ( intersection.pHull->GetBoundsCenter() - cursorRay.ptOrigin ) ).Length();

      PF_Core::WorldObjectBase* pCurrent = pWorld->GetObjectById(objectID);
      if ( selector->IsIt( pCurrent, GetUnitCategory(pCurrent) ) && distanceFromRay < minDistance )
      {
        minDistance = distanceFromRay;
        pPO = pCurrent;
        pPSO = pSO;
      }
    }
  }

  if ( pPO )
  {
    *objectId = pPO->GetObjectId();
    return true;
  }

  *objectId = PF_Core::INVALID_OBJECT_ID;
  return false;
}
}