#include "stdafx.h"
#include "SocialLobbyMaps.h"
#include "Db/DBServer.auto.h"
#include <vector>

namespace socialLobby
{

class Maps : public IMaps, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( Maps, IMaps, BaseObjectST );

public:
  Maps()
  {
    NDb::Ptr<NDb::MapList> dbMaps = NDb::SessionRoot::GetRoot()->logicRoot->mapList;

    maps.reserve( dbMaps->maps.size() );

    for ( int i = 0; i < dbMaps->maps.size(); ++i )
      if ( dbMaps->maps[i] )
        maps.push_back( Map( dbMaps->maps[i] ) );
  }

  virtual size_t Size() const
  {
    return maps.size();
  }

  virtual const char * GetMapId( size_t idx ) const
  {
    NI_VERIFY( idx < maps.size(), "", return 0 );
    return maps[idx].mapId.c_str();
  }

  virtual const NDb::AdvMapDescription * GetMap( size_t idx ) const
  {
    NI_VERIFY( idx < maps.size(), "", return 0 );
    return maps[idx].dbmap;
  }

  virtual const NDb::AdvMapDescription * FindMap( const char * mapId ) const
  {
    string prepared( mmaking::PrepareGameModeName( mapId ) );
    for ( size_t i = 0; i < maps.size(); ++i )
      if ( maps[i].mapId == prepared )
        return maps[i].dbmap;
    return 0;
  }

private:
  struct Map
  {
    NDb::Ptr<NDb::AdvMapDescription>    dbmap;
    string                              mapId;

    Map( const NDb::AdvMapDescription * _map ) :
    dbmap( _map ),
    mapId( mmaking::PrepareGameModeName( dbmap->GetDBID().GetFormatted() ) )
    {}
  };
  std::vector<Map>  maps;
};



IMaps * LoadMaps()
{
  //UGLY: Take care of not-so-thread-safe resource system
  static threading::Mutex mutex;

  threading::MutexLock lock( mutex );

  return new Maps;
}

} //namespace socialLobby

NI_DEFINE_REFCOUNT( socialLobby::IMaps );
