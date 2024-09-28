#pragma once

namespace NDb
{
  struct AdvMap;
  struct AdvMapDescription;
  struct AdvMapSettings;
}

namespace NWorld
{

class MapDescriptionLoader: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MapDescriptionLoader, BaseObjectST );

public:
  MapDescriptionLoader(const string & mapDescName);

  bool IsStatisticsEnabled() const;

  NDb::Ptr<NDb::AdvMap>             Map;
  NDb::Ptr<NDb::AdvMapDescription>  Description;
  NDb::Ptr<NDb::AdvMapSettings>     Settings;
  bool IsSuccessfullyLoaded;
};
}
