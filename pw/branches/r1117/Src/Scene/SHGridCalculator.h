#pragma once
#include "../Render/texture.h"
#include "../Render/RenderInterface.h"
//#include "../PF_GameLogic/DBAdvMap.h"
#include "LightingScene.h"

#include "SHGrid.h"

namespace NScene
{

class SHGridCalculator
{
public:
  static void RecalculateSceneSH(SHGrid &grid, LightingScene &lightingScene, Render::AABB const *region = NULL);
private:
  static void CalculateRegionBounds(SHGrid const &grid, Render::AABB const *region, int &xMin, int &xMax, int &yMin, int &yMax);
};
}