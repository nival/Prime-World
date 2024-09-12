#pragma once

#include "Db/DBServer.auto.h"
#include "Server/LiveMMaking/ProdMmLogicBase.h"
#include "Server/LiveMMaking/RankTable.h"

namespace mm_test
{

class MmData : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MmData, BaseObjectST );

public:
  MmData( const NDb::AdvMapDescription * _map, int _teamSize, mmaking::IHeroesTable * _heroes, mmaking::IRankTable * _ranks ) :
  map( _map ),
  db( _map->matchmakingSettings ),
  teamSize( _teamSize ),
  heroes( _heroes ),
  ranks( _ranks )
  {
  }

  const NDb::Ptr<NDb::AdvMapDescription> map;
  const NDb::Ptr<NDb::MapMMakingSettings> db;
  const int teamSize;
  const StrongMT<mmaking::IHeroesTable> heroes;
  const StrongMT<mmaking::IRankTable> ranks;
};




class MmDataLoader : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MmDataLoader, BaseObjectST );

public:
  MmDataLoader()
  {
  }

  Strong<MmData> Load( const char * mapId )
  {
    NDb::Ptr<NDb::HeroesDB> dbHer = NDb::SessionRoot::GetRoot()->logicRoot->heroes;
    StrongMT<mmaking::IHeroesTable> heroes = mmaking::ProdLogicBase::FillHeroesTable( mmaking::CreateConfigFromStatics(), dbHer );

    NDb::Ptr<NDb::MapList> maps = NDb::SessionRoot::GetRoot()->logicRoot->mapList;

    NI_VERIFY( maps, "", return 0 );

    //TEMP: Choose first PVP map
    NDb::Ptr<NDb::AdvMapDescription> map;
    if ( mapId )
    {
      MessageTrace( "Using specific map: %s", mapId );
      map = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( mapId ) );
      NI_VERIFY( map && map->matchmakingSettings, "Map MM settings is not defined!", return 0 );
    }
    else
      MessageTrace( "Looking for first PVP or CTE map..." );

    if ( !map )
      for ( int i = 0; i < maps->maps.size(); ++i )
      {
        NDb::Ptr<NDb::AdvMapDescription> m = maps->maps[i];

        if ( m->teamSize != 5 )
          continue;

        const NDb::EMapType type = (NDb::EMapType)m->mapType;
        if ( ( type != NDb::MAPTYPE_PVP ) && ( type != NDb::MAPTYPE_CTE ) )
          continue;

        if ( !m->matchmakingSettings )
          continue;

        map = m;
        break;
      }

    if ( !map )
      return 0;

    MessageTrace( "Using map: %s", map->GetDBID().GetFormatted() );

    StrongMT<mmaking::RankTable> ranks = new mmaking::RankTable;
    bool ranksOk = ranks->Init( map->matchmakingSettings );
    NI_VERIFY( ranksOk, "", 0 );

    return new MmData( map, map->teamSize, heroes, ranks );
  }
};

} //namespace mm_test
