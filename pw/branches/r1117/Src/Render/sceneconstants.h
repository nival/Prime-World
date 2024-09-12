#pragma once

#include "texture.h"
#include "SHCoeffs.h"

namespace Render
{

struct SceneConstants
{
	SHMatrix view;
	SHMatrix projection;
	SHMatrix invView;
	SHMatrix viewProjection;
	CVec3    campos;
  CVec3    camfrustum;
  float    farplane;
  AABB     cameraAABB;
	
	CVec4    light1Direction;
	CVec4    light2Direction;
  CVec4    shadowDirection;
	
	HDRColor ambientColor;
	HDRColor diffuse1Color;
	HDRColor diffuse2Color;
  HDRColor minBakedColor;
  HDRColor maxBakedColor;

  CVec2 worldSize;

	float renderTime;

	TextureCubeRef pEnvCubeMap;

	SHShaderConstants envLighting;

  float nightFraction;
  float nightSpecularReduction;

	SceneConstants()
    : pEnvCubeMap(0)
    , farplane(10.f)
    , renderTime(0.f)
    , nightFraction(0.f)
    , nightSpecularReduction(0.5f)
  {
    Identity(&view);
    Identity(&projection);
    Update();
  }

	void Update();
	static const SceneConstants& Global();
	static SceneConstants& RetriveForModification();
};

}