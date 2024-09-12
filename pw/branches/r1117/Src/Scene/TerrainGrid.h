#pragma once
#include "Scene.h"
#include "../Render/StaticMesh.h"

namespace NScene
{

class TerrainGrid
{

	CPtr<IScene> pScene;
	Render::StaticMesh* pStaticMesh_free;
	Render::StaticMesh* pStaticMesh_blocked;
	const HeightsController* pHeightController;
	float step;
	int size;
	float accur;
	int version;
	//CRAP{
	//TODO: Только на 3ий кадр появляется правильная высота
	int cycle;
	//CRAP}


public:

	TerrainGrid( IScene *_pScene, const HeightsController* controller, int _size, float _step, float _accur );
	~TerrainGrid();

	void Render();

	float GetHeight( int x, int y );
};

}
