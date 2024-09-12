#include "stdafx.h"

// #include "../PF_GameLogic/PFWorld.h"
// #include "../Render/TextureManager.h"
#include "../Render/dipdescriptor.h"
#include "../Render/ImmediateRenderer.h"
#include "../Render/MaterialSpec.h"
#include "../Render/WaterManager.h"

#include "Scene.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <d3d9.h>
#include "../System/lerp.h"
#include "../System/GeomMisc.h"

#include "SHGridCalculator.h"

//#define DEBUG_SH

static float s_harmonicsCalculationHeight = 3;

namespace
{

class PointLightsCalculator : NonCopyable
{
public:
  explicit PointLightsCalculator(CVec3 pos, const NDb::PointLightFlags lightFlags = NDb::POINTLIGHTFLAGS_NONE)
    : pos(pos)
    , lightFlags(lightFlags)
	{
		ZeroMemory( &shaderConsts, sizeof( Render::SHShaderConstants ) );
	}
	void operator ()(Render::PointLight const &light)
	{
    if (!(light.m_flags & lightFlags))
      return;

		Render::SHCoeffs lightCoeffs;
		Render::SHShaderConstants _consts;

		CVec3 dir = pos - light.GetLocation();
		float attenuation = light.GetAttenuation(dir.Length());
		Normalize(&dir);
		EvaluateSHCoeffsForDirLight(light.m_diffuseColor * light.m_diffuseIntensity * attenuation, -dir, lightCoeffs);
		ConvertSHCoeffs2ShaderConstants(lightCoeffs, _consts);

		shaderConsts.Add(_consts);
	}
	Render::SHShaderConstants const &getResultConsts() const { return shaderConsts; }

  NScene::VoxelGridObj::RenderGroups getRenderGroup() const { return Render::PointLight::SGetRenderGroup(); }
private:
  PointLightsCalculator()
    : lightFlags(NDb::POINTLIGHTFLAGS_NONE)
  {
  }

  const NDb::PointLightFlags lightFlags;
	Render::SHShaderConstants shaderConsts;
	CVec3 pos;
};

}

namespace NScene
{

void SHGridCalculator::RecalculateSceneSH(SHGrid &grid, LightingScene &lightingScene, Render::AABB const *region)
{
	grid.InitGrid(grid.properties.dynObjLightingGridResX, grid.properties.dynObjLightingGridResY);

	int xMin, xMax, yMin, yMax;
	CalculateRegionBounds(grid, region, xMin, xMax, yMin, yMax);

  const Render::SHShaderConstants& envD = grid.owner->GetSceneConstants(NDb::LIGHTENVIRONMENT_DAY).envLighting;

  for (int y = yMin; y <= yMax; y++)
  {
    for (int x = xMin; x <= xMax; x++)
    {
      CVec3 pnt(x * grid.cellSizeX, y * grid.cellSizeY, 0);
      grid.owner->GetHeightsController().GetHeight(pnt.x, pnt.y, 0, &pnt.z, 0);
      pnt.z += s_harmonicsCalculationHeight;
      PointLightsCalculator pc(pnt, NDb::POINTLIGHTFLAGS_DAY);

      Render::GetLightsManager()->ForLightsAffectingBBox(Render::AABB(pnt, CVec3(0.1f, 0.1f, 0.1f)), pc);

      grid.nodesD[y][x] = envD;
      grid.nodesD[y][x].Add( pc.getResultConsts() );
    }
  }

  const Render::SHShaderConstants& envN = grid.owner->GetSceneConstants(NDb::LIGHTENVIRONMENT_NIGHT).envLighting;

  for (int y = yMin; y <= yMax; y++)
  {
    for (int x = xMin; x <= xMax; x++)
    {
      CVec3 pnt(x * grid.cellSizeX, y * grid.cellSizeY, 0);
      grid.owner->GetHeightsController().GetHeight(pnt.x, pnt.y, 0, &pnt.z, 0);
      pnt.z += s_harmonicsCalculationHeight;
      PointLightsCalculator pc(pnt, NDb::POINTLIGHTFLAGS_NIGHT);

      Render::GetLightsManager()->ForLightsAffectingBBox(Render::AABB(pnt, CVec3(0.1f, 0.1f, 0.1f)), pc);

      grid.nodesN[y][x] = envN;
      grid.nodesN[y][x].Add( pc.getResultConsts() );
    }
  }
}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLD FAKE RADIOCITY STUFF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace 
{
static BOOL IsPow2(DWORD i) { return ((i&(i-1))==0); }
static DWORD NextPow2(DWORD i) { DWORD d=0x1; while (d<i) d<<=1; return d; }
void CubeCoord( D3DXVECTOR3* vec, int face, const D3DXVECTOR2* uv )
{
  D3DXVECTOR3 tmp;
  switch (face)
  {
  case 0: tmp = D3DXVECTOR3(   1.f, -uv->y, -uv->x); break;
  case 1: tmp = D3DXVECTOR3(  -1.f, -uv->y,  uv->x); break;
  case 2: tmp = D3DXVECTOR3( uv->x,    1.f,  uv->y); break;
  case 3: tmp = D3DXVECTOR3( uv->x,   -1.f, -uv->y); break;
  case 4: tmp = D3DXVECTOR3( uv->x, -uv->y,    1.f); break;
  case 5: tmp = D3DXVECTOR3(-uv->x, -uv->y,   -1.f); break;
  }
  D3DXVec3Normalize(&tmp, &tmp);
  *vec = tmp;
}

HRESULT BuildCubemapWeightTexture(Render::Texture2DRef &weightTexture, LPDIRECT3DDEVICE9 lpDevice, DWORD dwOrder, DWORD dwSize)
{
  if (!IsPow2(dwSize))
    return E_FAIL;

  DWORD nSize = NextPow2( dwOrder );
  static bool hack = true;
  if (hack)
    nSize = dwOrder;

  // compute the total differential solid angle for samples over the dwSize*dwSize cube.  this is
  // used as a normalization scale factor for the individual solid angles...
  double *d_omega;
  double sum_d_omega = 0.f; 
  d_omega = new double[dwSize*dwSize];
  float* basisProj = new float[dwOrder*dwOrder];

  unsigned int s, t;

  //  faces are symmetrical, so just compute d_omega for one face, and replicate 6 times.
  for (t=0; t<dwSize; t++)
  {
    for (s=0; s<dwSize; s++)
    {
      D3DXVECTOR3 cubeVec;
      double sd=((s+0.5)/double(dwSize))*2. - 1.;
      double td=((t+0.5)/double(dwSize))*2. - 1.;
      D3DXVECTOR2 stVec ( (float)sd, (float)td );
      int index = t*dwSize + s;
      double r_sqr = sd*sd+td*td+1;        // distance origin to texel
      double cos_theta = 1./sqrt(r_sqr);   // dot product between cube vector (sphere direction)
      // and surface normal (axis direction)
      d_omega[index] = cos_theta / r_sqr;  // =(r^-3/2)
      sum_d_omega += d_omega[index];
    }
  }

  double d_omega_scale = 4.*M_PI / (6.f*sum_d_omega);

  int rowSize = dwSize * nSize * nSize;
  weightTexture = Render::CreateTexture2D(rowSize, 6 * dwSize, 0, Render::RENDER_POOL_MANAGED, Render::FORMAT_R32F);
  Render::LockedRect lockRect = weightTexture->LockRect(0, Render::LOCK_DEFAULT);
  unsigned char* dst = (unsigned char*)lockRect.data;


  for (int face=0; face<6; face++)
  {
    float* coefficients;
    coefficients = new float[rowSize * dwSize];
    ZeroMemory(coefficients, rowSize * dwSize * sizeof(float));

    for (t=0; t<dwSize; t++)
    {
      for (s=0; s<dwSize; s++)
      {
        D3DXVECTOR3 cubeVec;
        double sd=((s+0.5)/double(dwSize))*2. - 1.;
        double td=((t+0.5)/double(dwSize))*2. - 1.;
        D3DXVECTOR2 stVec ( (float)sd, (float)td );

        CubeCoord(&cubeVec, face, &stVec);

        int index = t*dwSize + s;

        //  compute the N^2 spherical harmonic basis functions
        D3DXSHEvalDirection( basisProj, dwOrder, &cubeVec );

        int basis=0;
        for (int l=0; l<(int)dwOrder; l++)
        {
          for (int m=-l; m<=l; m++, basis++)
          {
            int tiley = basis / dwOrder;
            int tilex = basis % dwOrder;
            double Ylm = basisProj[l*(l+1)+m];

            //             int offset = ((tiley*dwSize+t)*dwSize*nSize * nSize) + tilex*dwSize+s;
            int offset = t * rowSize + (tiley * dwOrder + tilex) * dwSize + s;
            float weight = (float)(Ylm * d_omega[index] * d_omega_scale);
            coefficients[offset] = weight;
          }
        }
      }
    }

    unsigned char* src = (unsigned char*)coefficients;
    unsigned int  srcPitch = rowSize * sizeof(float);

    for ( UINT i=0; i<dwSize; i++, dst+=lockRect.pitch, src+=srcPitch )
      memcpy(dst, src, srcPitch);

    delete [] coefficients;
  }
  weightTexture->UnlockRect(0);

  lockRect = weightTexture->LockRect(0, Render::LOCK_DEFAULT);

  weightTexture->UnlockRect(0);


  delete [] basisProj;
  delete [] d_omega;

  return S_OK;
}

} // namespace.


namespace NScene
{

void SHGridCalculator::CalculateRegionBounds(SHGrid const &grid, Render::AABB const *region, int &xMin, int &xMax, int &yMin, int &yMax)
{
  if (!region)
  {
    xMin = 0;
    yMin = 0;
    xMax = grid.nodesD.GetSizeX() - 1;
    yMax = grid.nodesD.GetSizeY() - 1;
    return;
  }

  CVec3 min = region->center - region->halfSize;
  CVec3 max = region->center + region->halfSize;

  xMin = floor(min.x / grid.cellSizeX);
  yMin = floor(min.y / grid.cellSizeY);
  xMax = ceil(max.x / grid.cellSizeX);
  yMax = ceil(max.y / grid.cellSizeY);

  xMin = Clamp(xMin, 0, grid.nodesD.GetSizeX() - 1);
  yMin = Clamp(yMin, 0, grid.nodesD.GetSizeY() - 1);
  xMax = Clamp(xMax, 0, grid.nodesD.GetSizeX() - 1);
  yMax = Clamp(yMax, 0, grid.nodesD.GetSizeY() - 1);
}

}
