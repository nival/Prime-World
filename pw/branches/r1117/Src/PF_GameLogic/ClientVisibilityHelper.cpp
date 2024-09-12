#include "stdafx.h"
#include "ClientVisibilityHelper.h"

namespace NGameX
{
  DI_WEAK(AdventureScreen) ClientVisibilityHelper::advScreen;
  DI_WEAK(VisibilityMapClient) ClientVisibilityHelper::visMap;
  DI_WEAK(NWorld::FogOfWar) ClientVisibilityHelper::fogOfWar;
  DI_WEAK(NWorld::TileMap) ClientVisibilityHelper::tileMap;
}
