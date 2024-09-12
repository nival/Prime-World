#include "StdAfx.h"
#include "DerStatsNameMap.h"

#include "DBStats.h"
#include "PFBaseUnit.h"

namespace
{
  class StatDerValueVariant : public NNameMap::Variant, NonCopyable
  {
  public:
    StatDerValueVariant(float _statValue) : statValue(_statValue){}

    virtual float GetFloat() const
    {
      return statValue;
    }

    virtual NNameMap::VariantType::Enum GetType() const { return NNameMap::VariantType::Float; }
    virtual bool IsReadonly() const                     { return true; }

  private:
    float statValue;
  };
}

namespace NGameX
{
NAMEMAP_BEGIN(DerStatsNameMap)
NAMEMAP_END

NNameMap::Variant* DerStatsNameMap::ResolveVariant( const char* name, int length, const char* args, int argsLength, void* prms, bool readonly )
{
  NI_DATA_VERIFY( name && name[0], "Stat name shouldn't be empty", return 0; );
  NI_DATA_ASSERT( !argsLength, "Arguments are not supported in unit.stat" );

  NDb::EDerivativeStat stat = NDb::StringToEnum_EDerivativeStat(name);
  float statValue = unit->GetStatValue(stat);
  return new StatDerValueVariant(statValue);
}
}

BASIC_REGISTER_CLASS(NGameX::DerStatsNameMap);