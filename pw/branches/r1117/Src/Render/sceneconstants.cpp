#include "stdafx.h"
#include "sceneconstants.h"

namespace Render
{

static SceneConstants g_sceneConstants;

void SceneConstants::Update()
{
	viewProjection = projection * view;
	//			const float abc = viewProjection.m[0][0]*viewProjection.m[0][0]+viewProjection.m[1][1]*viewProjection.m[1][1]+viewProjection.m[2][2]*viewProjection.m[2][2];
	//			NI_VERIFY( abc > 0.00001f, "wrong camera matrix", return; );
	invView.HomogeneousInverse(view);
}

const SceneConstants& SceneConstants::Global()
{
  return g_sceneConstants;
}

SceneConstants& SceneConstants::RetriveForModification() { return g_sceneConstants; }

}