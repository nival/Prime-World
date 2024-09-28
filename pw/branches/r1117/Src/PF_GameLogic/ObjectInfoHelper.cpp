#include "stdafx.h"
#include "ObjectInfoHelper.h"

#include "PFLogicObject.h"
#include "PFBaseUnit.h"
#include "PFHero.h"
#include "PFGlyph.h"
#include "PFChest.h"

#include "AdventureScreen.h"

BASIC_REGISTER_CLASS(NGameX::ObjectInfoHelper)

namespace
{
  const NGameX::ObjectInfo l_dummyObjectInfo;
}

namespace NGameX
{

  const char* GetObjectKindString(const EObjectKind::Enum value)
  {
    switch (value)
    {
    case EObjectKind::Unknown:
      return "Unknown";
    case EObjectKind::Unit:
      return "Unit";
    case EObjectKind::Hero:
      return "Hero";
    case EObjectKind::LocalHero:
      return "LocalHero";
    case EObjectKind::Glyph:
      return "Glyph";
    case EObjectKind::NatureGlyph:
      return "NatureGlyph";
    case EObjectKind::Consumable:
      return "Consumable";
    case EObjectKind::Other:
      return "Other";
    default:
      return "n/a";
    }
  }

  // TODO: !!!
  static inline int GetWorldStepNumber()
  {
    NI_VERIFY(!!AdventureScreen::Instance(), "Adventure screen must exist!", return -1);
    NI_VERIFY(!!AdventureScreen::Instance()->GetWorld(), "World must exist!", return -1);

    return AdventureScreen::Instance()->GetWorld()->GetStepNumber();
  }

  template <class T, class S>
  static inline bool CheckType(const ConstPtr<S>& ptr)
  {
    return !!dynamic_cast<const T*>(ptr.GetPtr());
  }

  static inline void FillObjectInfoImpl(ObjectInfo& info)
  {
    if (!IsValid(info.logicObject))
      info.kind = EObjectKind::Unknown;
    else if (CheckType<NWorld::PFBaseHero>(info.logicObject))
      info.kind = EObjectKind::Hero;
    else if (CheckType<NWorld::PFBaseUnit>(info.logicObject))
      info.kind = EObjectKind::Unit;
    else if (CheckType<NWorld::PFGlyph>(info.logicObject))
      info.kind = EObjectKind::Glyph;
    else if (CheckType<NWorld::PFNatureGlyph>(info.logicObject))
      info.kind = EObjectKind::NatureGlyph;
    else if (CheckType<NWorld::PFConsumableChest>(info.logicObject))
      info.kind = EObjectKind::Consumable;
    else
      info.kind = EObjectKind::Other;

    if (!IsValid(info.logicObject))
      info.unitType = NDb::UNITTYPE_INVALID;
    else
      info.unitType = info.logicObject->GetUnitType();

//    DevTrace("*** INFO: %s -> %s", info.worldObject->GetObjectTypeName(), GetObjectKindString(info.kind));
  }

  static inline void FillObjectInfo(ObjectInfo& info, const PF_Core::WorldObjectBase* const object)
  {
    info.worldObject = object;
    info.logicObject = CDynamicCast<const NWorld::PFLogicObject>(object);

    FillObjectInfoImpl(info);
  }

  static inline void FillObjectInfo(ObjectInfo& info, const NWorld::PFLogicObject* const object)
  {
    info.worldObject = object;
    info.logicObject = object;

    FillObjectInfoImpl(info);
  }

  static inline void RefreshObjectInfo(ObjectInfo& info, const ConstPtr<NWorld::PFBaseHero>& localHero, const int step)
  {
    info.step = step;

    if (!IsValid(info.logicObject))
    {
      info.faction = NDb::FACTION_NEUTRAL;
    }
    else
    {
      info.faction = info.logicObject->GetFaction();

      if (EObjectKind::IsHero(info.kind))
      {
        if (info.logicObject.GetPtr() == localHero.GetPtr())
          info.kind = EObjectKind::LocalHero;
        else
          info.kind = EObjectKind::Hero;
      }
    }
  }

  ObjectInfoHelper::ObjectInfoHelper()
    : objects()
    , localHero()
  {

  }

  ObjectInfoHelper::~ObjectInfoHelper()
  {

  }

  void ObjectInfoHelper::SetLocalHero(const NWorld::PFBaseHero* const _hero)
  {
    if (localHero == _hero)
      return;

    localHero = _hero;

    Refresh();
  }

  const ObjectInfo& ObjectInfoHelper::UpdateObjectInfo(const PF_Core::WorldObjectBase* const object)
  {
    if (!object)
      return l_dummyObjectInfo;

    const int step = GetWorldStepNumber();

    ObjectInfo& info = AccessObjectInfo(object->GetObjectId());

    if (info.NeedUpdate(step))
    {
      if (info.IsEmpty())
        FillObjectInfo(info, object);

      RefreshObjectInfo(info, localHero, step);
    }

    return info;
  }

  const ObjectInfo& ObjectInfoHelper::UpdateObjectInfo(const NWorld::PFLogicObject* const object)
  {
    if (!object)
      return l_dummyObjectInfo;

    const int step = GetWorldStepNumber();

    ObjectInfo& info = AccessObjectInfo(object->GetObjectId());

    if (info.NeedUpdate(step))
    {
      if (info.IsEmpty())
        FillObjectInfo(info, object);

      RefreshObjectInfo(info, localHero, step);
    }

    return info;
  }

  ObjectInfo& ObjectInfoHelper::AccessObjectInfo(const int id)
  {
    ObjectInfoMap::iterator it = objects.find(id);

    if (it == objects.end())
      return objects[id];
    else
      return it->second;
  }

  void ObjectInfoHelper::Refresh()
  {
    const int step = GetWorldStepNumber();

    ObjectInfoMap::iterator it = objects.begin();
    ObjectInfoMap::iterator it_end = objects.end();
    for (; it != it_end; ++it)
    {
      ObjectInfo& info = it->second;

      if (info.IsOutdated(step))
        continue;

      RefreshObjectInfo(info, localHero, step);
    }
  }

  const ObjectInfo& ObjectInfoHelper::GetObjectInfo(const PF_Core::WorldObjectBase* const object) const
  {
    NI_VERIFY(!!object, "Invalid object!", return l_dummyObjectInfo);

    ObjectInfoMap::const_iterator it = objects.find(object->GetObjectId());

    NI_VERIFY(it != objects.end(), "You must update object info first!", return l_dummyObjectInfo);

    const ObjectInfo& info = it->second;

    NI_ASSERT(!info.IsOutdated(GetWorldStepNumber()), "You're getting outdated object info!");

    return it->second;
  }

}
