#include "stdafx.h"
#include "../EditorNative/Utility.h"
#include "TileMapHelper.h"

namespace EditorNative {
namespace Terrain {

	System::Collections::Generic::List<System::Drawing::Point>^ TileMapHelper::FillOccupiedTiles(int _mapWidth, int _mapHeight, float _mapTileSize, DBTypes::FloatRect^ _coll, float _tileSize, System::Collections::Generic::IList<DBTypes::IntPoint^>^ _mask, DBTypes::Placement^ _placement)
	{
		//prepare data
		CTRect<float> collision = CTRect<float>(CVec2(_coll->x1, _coll->y1), CVec2(_coll->x2, _coll->y2));

		vector<CTPoint<int>> mask = vector<CTPoint<int>>(_mask->Count);
		for each(DBTypes::IntPoint^ pt in _mask)
		{
			mask.push_back(CTPoint<int>(pt->x, pt->y));
		}

		Placement placement;
		convertPlacement(_placement, &placement);

		//calculate result
		vector<SVector> tilesToMark;
		NWorld::TileMap tileMap1;
		tileMap1.Prepare(_mapWidth, _mapHeight, _mapTileSize);
		tileMap1.FillOccupiedTiles(tilesToMark, collision, _tileSize, mask, placement);

		//prepare result
		System::Collections::Generic::List<System::Drawing::Point>^ result = gcnew System::Collections::Generic::List<System::Drawing::Point>(tilesToMark.size());

		for(int i = 0; i < tilesToMark.size(); ++i)
		{
			result->Add(System::Drawing::Point(tilesToMark[i].x, tilesToMark[i].y));
		}

		return result;
	}
}
}