#pragma once

#include "Core/GameTypes.h"

namespace NCore
{
  struct MapStartInfo;
}

namespace NDb
{
	struct AdvMap;	
  struct AdvMapObject;
  struct AdvMapDescription;
}

namespace NScene
{
	_interface IScene;
}

namespace NWorld
{

class IMapLoader;
class IMapCollection;

class PFWorld;
class TileMap;


bool LoadAdvMap( PFWorld * pWorld, const NDb::AdvMap * pAdvMap, const NCore::TPlayersStartInfo & players, NScene::IScene * pScene );

IMapLoader * CreatePWFillMapStartInfo( const NDb::AdvMapDescription * _dbMapDescription );
IMapLoader * CreatePWFillMapStartInfo( const NDb::AdvMap * _dbMap );

} //namespace NWorld
