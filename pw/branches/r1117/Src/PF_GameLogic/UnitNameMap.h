#pragma once

#include "../System/NameMap.h"
#include "../System/TypeList.h"

namespace NWorld
{
  class PFAbilityData;
  class PFTalent;
  class PFBaseHero;
  class PFBaseMaleHero;
  class PFBaseUnit;
  class PFBaseCreep;
  class PFBuilding;
  class PFMinigamePlace;
  class PFConsumable;
  class PFConsumableChest;
  class PFCreep;
  class PFGlyph;
  class PFNatureGlyph;
}

namespace UI
{
  class Window;
}

namespace NGameX
{

class DieTimer;
class SessionTimer;
class PlayerData;

class UnitNameMap : public NNameMap::Map { friend class WindowNameMap; };

namespace
{
template <class TList, template <class> class Unit> class GenScatterHierarchy;
template <class H, class T, template <class> class Unit> 
class GenScatterHierarchy<NMeta::TypeList<H, T>, Unit> 
  : public GenScatterHierarchy<H, Unit>
  , public GenScatterHierarchy<T, Unit>
{
  NAMEMAP_DECLARE;
public:
  typedef NMeta::TypeList<H,T> TList;
  typedef GenScatterHierarchy<H, Unit> LeftBase;
  typedef GenScatterHierarchy<T, Unit> RightBase;

  template <typename T> struct Rebind
  {
    typedef Unit<T> Result;
  };
};
template <class Atomic, template <class> class Unit>
class GenScatterHierarchy : public Unit<Atomic>
{
  NAMEMAP_DECLARE;
public:
  typedef Unit<Atomic> LeftBase;

  template <typename T> struct Rebind
  {
    typedef Unit<T> Result;
  };
};

template <template <class> class Unit>
class GenScatterHierarchy<NMeta::NullType, Unit> : public virtual UnitNameMap
{
  NAMEMAP_DECLARE;

  template <typename T> struct Rebind
  {
    typedef Unit<T> Result;
  };
};

template <class T, class H> typename H::template Rebind<T>::Result& Field(H& obj) { return obj; }
template <class T, class H> const typename H::template Rebind<T>::Result& Field(const H& obj) { return obj; }


} // End of anonimous namespace

template <class T> struct TupleUnit {};

#define UNITINFOTUPLEUNIT(className)\
template <> struct TupleUnit<className> : public virtual UnitNameMap { NAMEMAP_DECLARE; public: className const *pObject; };

UNITINFOTUPLEUNIT(NWorld::PFAbilityData)
UNITINFOTUPLEUNIT(NWorld::PFConsumable)
UNITINFOTUPLEUNIT(NWorld::PFTalent)
UNITINFOTUPLEUNIT(NWorld::PFBaseHero)
UNITINFOTUPLEUNIT(NWorld::PFBaseMaleHero)
UNITINFOTUPLEUNIT(NWorld::PFBaseUnit)
UNITINFOTUPLEUNIT(NWorld::PFBaseCreep)
UNITINFOTUPLEUNIT(NWorld::PFBuilding)
UNITINFOTUPLEUNIT(NWorld::PFMinigamePlace)
UNITINFOTUPLEUNIT(NWorld::PFConsumableChest)
UNITINFOTUPLEUNIT(NWorld::PFGlyph)
UNITINFOTUPLEUNIT(NWorld::PFNatureGlyph)
UNITINFOTUPLEUNIT(PlayerData)
UNITINFOTUPLEUNIT(SessionTimer)

template <class TList> struct UnitInfoNameMap : public GenScatterHierarchy<TList, TupleUnit> { };

#define UNITINFOCLASSNAMENULL(U) GenScatterHierarchy<NMeta::NullType, U>
#define UNITINFOCLASSNAME_2(A, U) GenScatterHierarchy<A, U>
#define UNITINFOCLASSNAME_3(H, T, U) GenScatterHierarchy<NMeta::TypeList<H, T>, U>

template <class H, class T, template <class> class Unit> 
NAMEMAP_BEGIN(UNITINFOCLASSNAME_3(H, T, Unit))
  NAMEMAP_PARENT(LeftBase)
  NAMEMAP_PARENT(RightBase)
NAMEMAP_END

template <class Atomic, template <class> class Unit>
NAMEMAP_BEGIN(UNITINFOCLASSNAME_2(Atomic, Unit))
  NAMEMAP_PARENT(LeftBase)
NAMEMAP_END

template <template <class> class Unit>
NAMEMAP_BEGIN(UNITINFOCLASSNAMENULL(Unit))
NAMEMAP_END

// --------------------------------------------------------------------------------------------

template <typename T>
struct SingleValueNameMapT : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  explicit SingleValueNameMapT(T const &_value) : value(_value) {};
protected:
  T value;
};

typedef SingleValueNameMapT<int>     SingleValueNameMapInt;
typedef SingleValueNameMapT<float>   SingleValueNameMapFloat;
typedef SingleValueNameMapT<wstring> SingleValueNameMapWstring;

// --------------------------------------------------------------------------------------------

//@ask Oleg (D-Inter) about this class
//I think this should be included in UI::Window

class WindowNameMap : public NNameMap::IMap, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( WindowNameMap, NNameMap::IMap, BaseObjectST );
  NAMEMAP_DECLARE;

public:
  explicit WindowNameMap(Weak<UI::Window> const &pBaseWindow, bool assignToInvisiable = true);
  void UpdateWindows(UnitNameMap *pMap);

protected:
  WindowNameMap(){};

  void assignMeToWindows(UI::Window *pRoot, bool assignToInvisible);
  void updateWindowsRecursive(UI::Window *pRoot);

  Weak<UI::Window>  m_baseWindow;
  UnitNameMap       *m_pNameMap;
};

} // End of namespace NGameX