#pragma once

#include "../Render/sceneconstants.h"
#include "../Scene/RenderableScene.h"

namespace PF_Render
{

class Interface;

void RenderWater(Interface &iface, const Render::SceneConstants &sceneConsts, IRenderableScene* pScene, bool detailedRender);

}
