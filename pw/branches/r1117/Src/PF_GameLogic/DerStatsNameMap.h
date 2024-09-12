#pragma once

#include "../System/NameMap.h"

namespace NWorld
{
  class PFBaseUnit;
}


namespace NGameX
{

class DerStatsNameMap: public NNameMap::Map, public CObjectBase
{
  OBJECT_BASIC_METHODS(DerStatsNameMap);
  NAMEMAP_DECLARE;
  DerStatsNameMap() {}
protected:
  virtual NNameMap::Variant* ResolveVariant( const char* name, int length, const char* args, int argsLength, void* prms, bool readonly );
public:
  DerStatsNameMap(const NWorld::PFBaseUnit * _unit): unit(_unit) {}
private:
  ConstPtr<NWorld::PFBaseUnit> unit;
};

}
