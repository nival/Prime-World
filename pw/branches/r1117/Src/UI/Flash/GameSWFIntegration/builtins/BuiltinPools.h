#pragma once

namespace PoolType
{
  enum Type
  {
    Accessibility,
    Display,
    Events,
    Filters,
    Geom,
    System,
    Text,
    UI,
    Utils,
    XML,
    Sound,

    Last
  };
}

namespace avmplus
{
class PoolObject;
class AvmCore;

//getters for compiled pools. 
//Note that its implementation should be divided into several cpp files. cause of builtin map
class BuiltinPools
{
public:
  static PoolObject * GetAccessibilityPool(AvmCore * core);
  static PoolObject * GetByteArrayPool(AvmCore * core);
  static PoolObject * GetDisplayPool(AvmCore * core);
  static PoolObject * GetEventsPool(AvmCore * core);
  static PoolObject * GetFiltersPool(AvmCore * core);
  static PoolObject * GetGeomPool(AvmCore * core);
  static PoolObject * GetNetPool(AvmCore * core);
  static PoolObject * GetSoundPool(AvmCore * core);
  static PoolObject * GetSystemPool(AvmCore * core);
  static PoolObject * GetTextPool(AvmCore * core);
  static PoolObject * GetUIPool(AvmCore * core);
  static PoolObject * GetUtilsPool(AvmCore * core);
  static PoolObject * GetXMLPool(AvmCore * core);
  static PoolObject * GetTestingPool( AvmCore * core );
};
}

