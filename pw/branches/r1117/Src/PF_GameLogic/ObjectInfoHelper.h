#pragma once

#include "DI/DI.hpp"

namespace NWorld
{
  class PFLogicObject;
  class PFBaseHero;
}

namespace NGameX
{
  namespace EObjectKind
  {
    enum Enum
    {
      Unknown,
      Unit,
      Hero,
      LocalHero,
      Glyph,
      NatureGlyph,
      Consumable,
      Other,
    };

    static inline bool IsHero(const Enum value)
    {
      switch (value)
      {
      case Hero:
      case LocalHero:
        return true;
      default:
        return false;
      }
    }
  }

  struct ObjectInfo
  {
    enum
    {
      InvalidStep = -1
    };

    ConstPtr<PF_Core::WorldObjectBase> worldObject;
    ConstPtr<NWorld::PFLogicObject> logicObject;

    EObjectKind::Enum kind;

    NDb::EUnitType unitType;
    NDb::EFaction faction;

    int step;

    ObjectInfo()
      : worldObject()
      , logicObject()
      , kind(EObjectKind::Unknown)
      , unitType(NDb::UNITTYPE_INVALID)
      , faction(NDb::FACTION_NEUTRAL)
      , step(InvalidStep)
    {

    }

    bool IsEmpty() const
    {
      return (step == InvalidStep);
    }

    bool NeedUpdate(const int currentStep) const
    {
      return (step == InvalidStep) || (step != currentStep);
    }

    bool IsOutdated(const int currentStep) const
    {
      return (currentStep - step > 1);
    }
  };

  class ObjectInfoHelper
    : public CObjectBase
    , public DI::SelfProvider<ObjectInfoHelper>
  {
    OBJECT_BASIC_METHODS(ObjectInfoHelper)
  public:
    ObjectInfoHelper();
    virtual ~ObjectInfoHelper();

    void SetLocalHero(const NWorld::PFBaseHero* const _hero);

    const ObjectInfo& UpdateObjectInfo(const PF_Core::WorldObjectBase* const object);
    const ObjectInfo& UpdateObjectInfo(const NWorld::PFLogicObject* const object);

    const ObjectInfo& GetObjectInfo(const PF_Core::WorldObjectBase* const object) const;
  private:
    typedef map<int, ObjectInfo> ObjectInfoMap;

    ObjectInfo& AccessObjectInfo(const int id);

    void Refresh();

    ObjectInfoMap objects;

    ConstPtr<NWorld::PFBaseHero> localHero;
  };
}
