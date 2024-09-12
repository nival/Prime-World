#pragma once
#include "../System/matrix43.h"
#include "HeightsController.h"

namespace NScene
{

class LandPlacementMutator
{

	const HeightsController* pHeightController;
	bool isNormalize;
	int layer;

public:

	LandPlacementMutator( const HeightsController* controller, int _layer, bool _normalize );

	void Apply( Placement* placement ) const;

};

}