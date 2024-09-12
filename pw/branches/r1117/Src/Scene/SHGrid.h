#pragma once
#include "../System/2Darray.h"
#include "../Render/SHCoeffs.h"
#include "../Render/MeshResource.h" // debug
#include "../Render/texture.h"
#include "../Render/RenderInterface.h"

namespace Render
{
	class BatchQueue;
}

namespace NScene
{

class Scene;

class SHGrid
{
  CArray2D<Render::SHShaderConstants> nodesD;
  CArray2D<Render::SHShaderConstants> nodesN;
  Scene *owner;
  float cellSizeX, cellSizeY;
  int cellsX, cellsY;
//   NDb::Ptr<NDb::BakedLighting> pProperties;
  NDb::BakedLighting properties;

#ifndef _SHIPPING
  // debug
  Render::MeshGeometry const *pMeshGeom;
  Render::Material *pMaterial;
#endif

  void InitGrid(int cX, int cY);
public:
	SHGrid(Scene *pScene);

	void Save();
  bool Load();

	void Init(NDb::BakedLighting const &initParams);
  void CalculateSH(CVec2 const &pos, Render::SHShaderConstants &shConsts);

  // debug
  void DebugRender();
#ifndef _SHIPPING
  void ToggleDebugRender();
//   void SetDebugRender(bool bRender) { bDebugRender = !bDebugRender; }

  ~SHGrid();
#endif

  friend class SHGridCalculator;
};
}