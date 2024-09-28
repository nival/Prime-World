#include "StdAfx.h"
#include "MapDescriptionLoader.h"

#include "DBAdvMap.h"


namespace NWorld
{

MapDescriptionLoader::MapDescriptionLoader(const string & mapDescName)
: IsSuccessfullyLoaded (false)
{
  Description = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( mapDescName ) );
  NI_VERIFY( IsValid(Description), NStr::StrFmt( "Couldn't get map descriptor '%s'", mapDescName.c_str() ), return );

  Map = Description->map;
  NI_VERIFY( IsValid(Map), NStr::StrFmt( "Couldn't get map for '%s'", mapDescName.c_str() ), return );

  Settings = IsValid(Description->mapSettings) ? (Description->mapSettings) : (Map->mapSettings);
  NI_VERIFY( IsValid(Settings), NStr::StrFmt( "Couldn't get map settings for '%s'", mapDescName.c_str() ), return );

  IsSuccessfullyLoaded = true;
}

bool MapDescriptionLoader::IsStatisticsEnabled() const
{
  if (IsValid(Settings))
    return Settings->enableStatistics;

  return false;
}

}
NI_DEFINE_REFCOUNT( NWorld::MapDescriptionLoader );

