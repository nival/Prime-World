#pragma once
#include "../PF_GameLogic/StringExecutor.h"
#include "../PF_GameLogic/DBStats.h"
#include "../PF_GameLogic/TileMap.h"

namespace EditorNative {
namespace Terrain {

	public ref class TileMapHelper sealed
	{
		public:
			static System::Collections::Generic::List<System::Drawing::Point>^ FillOccupiedTiles(int _mapWidth, int _mapHeight, float _mapTileSize, DBTypes::FloatRect^ _coll, float _tileSize, System::Collections::Generic::IList<DBTypes::IntPoint^>^ _mask, DBTypes::Placement^ _placement);
	};

}
}