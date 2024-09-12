#pragma once

#include "ObjectInfoHelper.h"

#include "PFHero.h"
#include "PFBaseUnit.h"
#include "PFGlyph.h"
#include "PFChest.h"

namespace NGameX
{
  namespace ObjectInfoMapper
  {
    namespace Private
    {
      template <class T>
      struct Impl0
      {
        inline const T* operator()(const ObjectInfo& info) const
        {
          {
            return static_cast<const T*>(info.logicObject.GetPtr());
          }
        }
      };

      template <class T, const EObjectKind::Enum K0>
      struct Impl1
      {
        inline const T* operator()(const ObjectInfo& info) const
        {
          switch (info.kind)
          {
          case K0:
            return static_cast<const T*>(info.logicObject.GetPtr());
          default:
            return NULL;
          }
        }
      };

      template <class T, const EObjectKind::Enum K0, const EObjectKind::Enum K1>
      struct Impl2
      {
        inline const T* operator()(const ObjectInfo& info) const
        {
          switch (info.kind)
          {
          case K0:
          case K1:
            return static_cast<const T*>(info.logicObject.GetPtr());
          default:
            return NULL;
          }
        }
      };

      template <class T, const EObjectKind::Enum K0, const EObjectKind::Enum K1, const EObjectKind::Enum K2>
      struct Impl3
      {
        inline const T* operator()(const ObjectInfo& info) const
        {
          switch (info.kind)
          {
          case K0:
          case K1:
          case K2:
            return static_cast<const T*>(info.logicObject.GetPtr());
          default:
            return NULL;
          }
        }
      };
    }

    template <class>
    struct Mapper
    {
      BOOST_STATIC_ASSERT_MSG(false, "Unsupported ObjectInfo cast");
    };

    template <> struct Mapper<NWorld::PFBaseUnit>         : public Private::Impl3<NWorld::PFBaseUnit, EObjectKind::Unit, EObjectKind::Hero, EObjectKind::LocalHero> {};
    template <> struct Mapper<NWorld::PFBaseHero>         : public Private::Impl2<NWorld::PFBaseHero, EObjectKind::Hero, EObjectKind::LocalHero> {};
    template <> struct Mapper<NWorld::PFGlyph>            : public Private::Impl1<NWorld::PFGlyph, EObjectKind::Glyph> {};
    template <> struct Mapper<NWorld::PFNatureGlyph>      : public Private::Impl1<NWorld::PFNatureGlyph, EObjectKind::NatureGlyph> {};
    template <> struct Mapper<NWorld::PFConsumableChest>  : public Private::Impl1<NWorld::PFConsumableChest, EObjectKind::Consumable> {};
    template <> struct Mapper<NWorld::PFLogicObject>      : public Private::Impl0<NWorld::PFLogicObject> {};
  }

  template <class T>
  static inline const T* GetObject(const ObjectInfo& info)
  {
    return ObjectInfoMapper::Mapper<T>()(info);
  }

  template <class T>
  static inline const T* GetObjectUnchecked(const ObjectInfo& info)
  {
    typedef ObjectInfoMapper::Mapper<T> MapperImpl;
    return static_cast<const T*>(info.worldObject.GetPtr());
  }
}
