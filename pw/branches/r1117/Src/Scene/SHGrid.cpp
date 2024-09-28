#include "stdafx.h"

// #include "../PF_GameLogic/PFWorld.h"
#include "../Render/dipdescriptor.h"
#include "../Render/GlobalMasks.h"
#include "../Render/MaterialSpec.h"

#include "Scene.hpp"

// #define _USE_MATH_DEFINES
// #include <math.h>
// #include <d3d9.h>
#include "../System/lerp.h"
// #include "../System/GeomMisc.h"

#include "SHGrid.h"

#define BAKED_FILE_VERSION 0x01
#define BAKED_FILE_SIGN  MAKELONG('HS', BAKED_FILE_VERSION)

namespace
{
static bool bDebugRender = false;
}
namespace NScene
{


void SHGrid::Init(NDb::BakedLighting const &initParams)
// void SHGrid::Init(Scene *pScene, NDb::Ptr<NDb::BakedLighting> const &pInitParams)
{
  properties = initParams;

//   InitGrid(pInitParams->dynObjLightingGridResX, pInitParams->dynObjLightingGridResY);
//   if (pInitParams->dynObjBakedLighting != "")
  InitGrid(initParams.dynObjLightingGridResX, initParams.dynObjLightingGridResY);

  bool initWithDefaultValues = true;

  if (initParams.dynObjBakedLighting != "")
    initWithDefaultValues = !Load();

  if (initWithDefaultValues)
  {
    const Render::SHShaderConstants& envD = owner->GetSceneConstants(NDb::LIGHTENVIRONMENT_DAY).envLighting;
    const Render::SHShaderConstants& envN = owner->GetSceneConstants(NDb::LIGHTENVIRONMENT_NIGHT).envLighting;

    for (int y = 0; y < nodesD.GetSizeY(); y++)
      for (int x = 0; x < nodesD.GetSizeX(); x++)
      {
        nodesD[y][x] = envD;
        nodesN[y][x] = envN;
      }
  }

#ifndef _SHIPPING
  pMeshGeom = Render::RenderResourceManager::LoadStaticMeshGeometry(
    "Debug/ShHarmonics/_.stat", false );

  NDb::Ptr<NDb::Material> pMat = NDb::Get<NDb::Material>( NDb::DBID(
    "Debug/ShHarmonics/_.MTRL.xdb" ) );

  NI_DATA_VERIFY( IsValid( pMat ), "Cannot load SH debug material", return  );

  pMaterial = Render::CreateRenderMaterial(pMat.GetPtr());

  Render::Sampler *pSampler = static_cast<Render::BaseMaterial*>(pMaterial)->GetDiffuseMap();
  NI_ASSERT(pSampler, "Should present");
  pSampler->SetTexture( Render::GetWhiteTexture2D() );
	pMaterial->MarkMaterialUpdated();
#endif
}
SHGrid::SHGrid(Scene *pScene) : owner(pScene), cellSizeX(0.f), cellSizeY(0.f), cellsX(0), cellsY(0)
#ifndef _SHIPPING
, pMeshGeom(0), pMaterial(0)
#endif
{}

#ifndef _SHIPPING
SHGrid::~SHGrid()
{
  if (pMaterial)
   delete pMaterial;
  pMaterial = NULL;
}
#endif

void SHGrid::InitGrid(int cX, int cY)
{
  if (cX + 1 == nodesD.GetSizeX() && cY + 1 == nodesD.GetSizeY())
    return;
  cellsX = cX, cellsY = cY;
  CVec2 mapSize = owner->GetGridConstants().worldSize.AsVec2D();
  cellSizeX = mapSize.x / cellsX;
  cellSizeY = mapSize.y / cellsY;

  nodesD.SetSizes(cellsX + 1, cellsY + 1);
  nodesN.SetSizes(cellsX + 1, cellsY + 1);
}

// void SHGrid::Load(string const &fileName)
bool SHGrid::Load()
{
  CObj<Stream> gridFileStream = RootFileSystem::OpenFile( properties.dynObjBakedLighting, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  if (!gridFileStream)
    return false;

  {
    unsigned sign;

    const bool sign_read = (gridFileStream->Read(&sign, sizeof(sign)) == sizeof(sign));

    NI_DATA_VERIFY(sign_read, "Invalid SH grid file!", return false);
    NI_DATA_VERIFY(sign == BAKED_FILE_SIGN, "Invalid SH grid file format!", return false);
  }

//   NI_VERIFY( gridFileStream.IsOk(), NStr::StrFmt("Cannot open file for reading: %s", fileName.c_str()), return );
  int dimensions[2];
  gridFileStream->Read(dimensions, 2 * sizeof(int));
  InitGrid(dimensions[0] - 1, dimensions[1] - 1);
  gridFileStream->Read(const_cast<Render::SHShaderConstants *>(&nodesD.GetUnsafe(0, 0)), dimensions[0] * dimensions[1] * sizeof(Render::SHShaderConstants));
  gridFileStream->Read(const_cast<Render::SHShaderConstants *>(&nodesN.GetUnsafe(0, 0)), dimensions[0] * dimensions[1] * sizeof(Render::SHShaderConstants));
  gridFileStream->Close();

  return true;
}

// void SHGrid::Save(string const &fileName)
void SHGrid::Save()
{
//   FileStream gridFileStream( properties.dynObjBakedLighting, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
  CObj<Stream> gridFileStream = RootFileSystem::OpenFile( properties.dynObjBakedLighting, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
  if (!gridFileStream)
    return;

  {
    const unsigned sign = BAKED_FILE_SIGN;

    gridFileStream->Write(&sign, sizeof(sign));
  }

	//NI_VERIFY( gridFileStream.IsOk(), NStr::StrFmt("Cannot open file for writing: %s", fileName.c_str()), return );
  int dimensions[2] = {nodesD.GetSizeX(), nodesD.GetSizeY()};
  gridFileStream->Write(dimensions, 2 * sizeof(int));
  gridFileStream->Write(&nodesD.GetUnsafe(0, 0), dimensions[0] * dimensions[1] * sizeof(Render::SHShaderConstants));
  gridFileStream->Write(&nodesN.GetUnsafe(0, 0), dimensions[0] * dimensions[1] * sizeof(Render::SHShaderConstants));
	gridFileStream->Close();
}

namespace Local
{
  static inline void BiLerp(
    Render::SHShaderConstants& target,
    const Render::SHShaderConstants& a,
    const Render::SHShaderConstants& b,
    const Render::SHShaderConstants& c,
    const Render::SHShaderConstants& d,
    const float fx,
    const float fy)
  {
    for (int i = 0; i < 3; ++i)
    {
      target.linearAndConstant[i] = BiLerp(a.linearAndConstant[i], b.linearAndConstant[i], c.linearAndConstant[i], d.linearAndConstant[i], fx, fy);
    }

    for (int i = 0; i < 3; ++i)
    {
      target.quadratic[i] = BiLerp(a.quadratic[i], b.quadratic[i], c.quadratic[i], d.quadratic[i], fx, fy);
    }

    {
      target.quadraticRGB = BiLerp(a.quadraticRGB, b.quadraticRGB, c.quadraticRGB, d.quadraticRGB, fx, fy);
    }
  }

  static inline void Lerp(
    Render::SHShaderConstants& target,
    const Render::SHShaderConstants& a,
    const Render::SHShaderConstants& b,
    const float f)
  {
    for (int i = 0; i < 3; ++i)
    {
      target.linearAndConstant[i].Lerp(f, a.linearAndConstant[i], b.linearAndConstant[i]);
    }

    for (int i = 0; i < 3; ++i)
    {
      target.quadratic[i].Lerp(f, a.quadratic[i], b.quadratic[i]);
    }

    {
      target.quadraticRGB.Lerp(f, a.quadraticRGB, b.quadraticRGB);
    }
  }
}

void SHGrid::CalculateSH(CVec2 const &pos, Render::SHShaderConstants &shConsts)
{
  if (cellSizeX == 0.f || cellSizeY == 0.f)
  {
		NI_ASSERT(owner, "Owner should present");
		shConsts = owner->GetEnvLighting();
    return;
  }

  float fracx = pos.x / cellSizeX;
  float fracy = pos.y / cellSizeY;
  int blendx = (int)fracx;
  int blendy = (int)fracy;
  fracx -= blendx;
  fracy -= blendy;

  // Fit indices in case when object is out of world
  blendx = max(0, min(cellsX - 1, blendx));
  blendy = max(0, min(cellsY - 1, blendy));

  NI_VERIFY((blendx + 1) < nodesD.GetSizeX(), NStr::StrFmt("Index %d out of bounds. cellsX = %d, Max elements: %d", blendx, cellsX, nodesD.GetSizeX()), blendx = max(0, nodesD.GetSizeX() - 2););
  NI_VERIFY((blendy + 1) < nodesD.GetSizeY(), NStr::StrFmt("Index %d out of bounds. cellsY = %d, Max elements: %d", blendy, cellsY, nodesD.GetSizeY()), blendy = max(0, nodesD.GetSizeY() - 2););

  Render::SHShaderConstants cd;
  Render::SHShaderConstants cn;

  Local::BiLerp(cd, nodesD[blendy + 0][blendx + 0], nodesD[blendy + 0][blendx + 1], nodesD[blendy + 1][blendx + 0], nodesD[blendy + 1][blendx + 1], fracx, fracy);
  Local::BiLerp(cn, nodesN[blendy + 0][blendx + 0], nodesN[blendy + 0][blendx + 1], nodesN[blendy + 1][blendx + 0], nodesN[blendy + 1][blendx + 1], fracx, fracy);

  Local::Lerp(shConsts, cd, cd, owner->GetSceneConstants().nightFraction);
}

void SHGrid::DebugRender()
{
#ifndef _SHIPPING
  if (!pMeshGeom || !pMaterial || !bDebugRender)
    return;

  Render::GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 1);
  Render::GetStatesManager()->SetStateDirect(D3DRS_ZWRITEENABLE, 1);

  Render::Batch batch;
  pMeshGeom->primitives[0]->Bind();

  Render::SHShaderConstants shConsts;

  const float nightFraction = owner->GetSceneConstants().nightFraction;

  for (int y = 0; y < nodesD.GetSizeY(); y++)
    for (int x = 0; x < nodesD.GetSizeX(); x++)
    {
      CVec3 pnt(x * cellSizeX, y * cellSizeY, 0);
      owner->GetHeightsController().GetHeight(pnt.x, pnt.y, 0, &pnt.z, 0);
      static float deltaZ = 1;
      pnt.z += deltaZ;

      pMaterial->PrepareRenderer();

      Local::Lerp(shConsts, nodesD[x][y], nodesN[x][y], nightFraction);

      batch.pSHConsts = &shConsts;
      pMaterial->PrepareRendererWithBatch(batch);

      SHMatrix world;
      world.Set(pnt);
      Render::GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, world );

      pMeshGeom->primitives[0]->Draw();    
    }
  Render::GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);
  Render::GetStatesManager()->SetStateDirect(D3DRS_ZWRITEENABLE, 0);
#endif
}

#ifndef _SHIPPING
void SHGrid::ToggleDebugRender()
{
  bDebugRender = !bDebugRender;
}
#endif // #ifndef _SHIPPING
}

REGISTER_DEV_VAR("sh_render_probes", bDebugRender,   STORAGE_NONE);