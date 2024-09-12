#include "stdafx.h"

#include "TerrainHeightManager.h"
#include "Terrain.h"
#include "ArraySampler.h"
#include "../System/GeomMisc.h"
#include "../System/lerp.h"
#include "../System/InlineProfiler.h"

#include "../Render/ImmediateRenderer.h"

// static float g_dx = 0.0f;
// static float g_dy = 0.0f;

TerrainAttributes operator*(TerrainAttributes const& a, float b)
{
	TerrainAttributes c = {a.height * b, a.normalX * b, a.normalY * b, 0};
	return c;
}

TerrainAttributes operator+(TerrainAttributes const& a, TerrainAttributes const& b)
{
	TerrainAttributes c = {a.height + b.height, a.normalX + b.normalX, a.normalY + b.normalY, 0};
	return c;
}

namespace Terrain {

// float -> short: short = scale * float + offset
const float TerrainHeightManager::SHORTHEIGHT_MIN = -32.0f;
const float TerrainHeightManager::SHORTHEIGHT_MAX = +32.0f;
const float TerrainHeightManager::SHORTHEIGHT_SCALE = 65536.0f / (TerrainHeightManager::SHORTHEIGHT_MAX - TerrainHeightManager::SHORTHEIGHT_MIN);
const float TerrainHeightManager::SHORTHEIGHT_OFFSET = -TerrainHeightManager::SHORTHEIGHT_MIN * TerrainHeightManager::SHORTHEIGHT_SCALE;

namespace {
	static NDebug::PerformanceDebugVar terrain_GetHeight( "GetHeight()", "Terrain", 10, 10, true );
}	// anonymous namespace

TerrainHeightManager::TerrainHeightManager() : pOwner(NULL)
#ifndef VISUAL_CUTTED
  , renderTargetMaterial(NULL), renderTarget(Render::FORMAT_A32B32G32R32F)
#endif
  , binaryData(NULL), version(0), dirty(true)
{
}

TerrainHeightManager::~TerrainHeightManager()
{
#ifndef VISUAL_CUTTED
	SAFE_DELETE(renderTargetMaterial);
#endif
	SAFE_DELETE_ARRAY(binaryData);
}

void TerrainHeightManager::Initialize()
{
	GridConstants const& params = pOwner->GetGridConstants();
	int gridWidth = params.sizeInTiles.x;
	int gridHeight = params.sizeInTiles.y;

	if (pOwner->IsEditable())
	{
#ifndef VISUAL_CUTTED
    renderTargetMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::TerrainHeightBuilderMaterial::typeId ) );
		renderTarget.Create(gridWidth, gridHeight);
#endif
	}

	asFloat.SetSizes(gridWidth, gridHeight);
	asFloat.FillEvery(0.0f);

  MarkAsDirty();
}

void TerrainHeightManager::Load(const nstl::string& filename)
{
  CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  if( pOwner->IsEditable() && !( pStream && pStream->IsOk() ) ) return;
  NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open heightmap file for reading: %s", filename ), return; );

// #ifndef VISUAL_CUTTED
//   NI_VERIFY(!renderTarget.IsReady(), "Heights are in dynamic update mode, loading is not supposed.", return; );
// #endif

	// version
	unsigned long dword;
	pStream->Read(&dword, sizeof(dword));
	NI_VERIFY( dword == BINARY_VERSION, NStr::StrFmt( "Heightmap binary data version is different: 0x%X != 0x%X", dword, BINARY_VERSION ), return; );

	// dimensions
	pStream->Read(&dword, sizeof(dword));
	NI_VERIFY( dword == (unsigned long)asFloat.GetSizeX(), NStr::StrFmt( "Heightmap binary data width is different: 0x%X != 0x%X", dword, asFloat.GetSizeX() ), return; );
	pStream->Read(&dword, sizeof(dword));
	NI_VERIFY( dword == (unsigned long)asFloat.GetSizeY(), NStr::StrFmt( "Heightmap binary data height is different: 0x%X != 0x%X", dword, asFloat.GetSizeY() ), return; );

	// height and normal values along with their size
	unsigned long totalSize = asFloat.GetSizeX() * asFloat.GetSizeY() * sizeof(TerrainAttributes);
	pStream->Read(&dword, sizeof(dword));
	NI_VERIFY( dword == totalSize, NStr::StrFmt( "Heightmap binary data size is different: 0x%X != 0x%X", dword, totalSize ), return; );
	binaryData = new unsigned char[dword];
	pStream->Read(binaryData, dword);
	heights.Set(reinterpret_cast<TerrainAttributes const*>(binaryData), asFloat.GetSizeX(), asFloat.GetSizeY(), asFloat.GetSizeX() );

	// synchronize separate arrays of floats and shorts
	SyncArrays();
}

void TerrainHeightManager::Save(const nstl::string& filename)
{
  NI_VERIFY( heights.Get(), "Heightmap array is missing when saving.", return; );

  CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
  NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open heightmap file for writing: %s", filename ), return; );

  // version
  unsigned long dword = BINARY_VERSION;
  pStream->Write(&dword, sizeof(dword));

  // dimensions
  dword = heights.GetSizeX();
  pStream->Write(&dword, sizeof(dword));
  dword = heights.GetSizeY();
  pStream->Write(&dword, sizeof(dword));

  // height and normal values along with their size
  dword = heights.GetSizeX() * heights.GetSizeY() * sizeof(TerrainAttributes);
  pStream->Write(&dword, sizeof(dword));
  pStream->Write(heights.Get(), dword);

  MessageTrace( "TerrainHeightManager::Save done" );
}

void TerrainHeightManager::Update()
{
#ifndef VISUAL_CUTTED
  using namespace Render;
	Renderer* pRenderer = GetRenderer();

	if (dirty && renderTarget.IsReady())   
	{
		NI_ASSERT(pOwner->IsEditable(), "In-game data updates disabled.");

		// substitute render target
		Texture2DRef const& texture = renderTarget.GetTexture();
		pRenderer->BeginScene();
		SmartRenderer::BindRenderTarget(texture);
		pRenderer->ClearColorOnly(Color(0, 0, 0, 0));

		// set default heights to abyss "height" (absolute minimum)
		CVec4 clear(SHORTHEIGHT_MIN, 0.0f, 0.0f, 0.0f);
		pRenderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, clear);
		GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params("ConstantColor"));

		// common settings
		CVec4 offset(-1.0f - 1.0f / texture->GetWidth(), -1.0f + 1.0f / texture->GetHeight(), 0.0f, 0.0f); // half pixel adjustment
		pRenderer->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST8,  offset);
		renderTargetMaterial->PrepareRenderer();

		// prepare top down projection
		GridConstants const& params = pOwner->GetGridConstants();
		SHMatrix projection;
		CreateOrthographicProjectionMatrixRH(&projection, params.worldSize.x, params.worldSize.y, -50.f, 50.f);

		// render all terrain elements
		struct BindDrawFunctor
		{
			SHMatrix* projection;

			void operator()(TerrainElementInfo const& elem)
			{
				SHMatrix world;
				Copy( &world, IDENTITY_MATRIX );
				SHMatrix MVP = (*projection) * world;
				GetRenderer()->SetVertexShaderConstantsMatrix(VSHADER_LOCALCONST0, MVP);
				GetRenderer()->SetVertexShaderConstantsMatrix(VSHADER_LOCALCONST4, world);
				elem.pElement->mesh.Bind();
				elem.pElement->mesh.Draw();
			}
		} bindAndDraw = {&projection};
		pOwner->GetElementManager().ForAllElementInfos(bindAndDraw);

		// restore render target
		SmartRenderer::BindRenderTargetDefault();

		// read results
		TerrainAttributes const* data = renderTarget.Fetch();
		heights.Set(data, texture->GetWidth(), texture->GetHeight(), texture->GetWidth());

		// synchronize separate arrays of floats and shorts
		SyncArrays();

		// done
		GetRenderer()->EndScene();
		dirty = false;
		++version;
	}

#endif
}

void TerrainHeightManager::SyncArrays()
{
	// update separate arrays in a fast way
	{
		for (int y = 0, h = heights.GetSizeY(); y < h; y++)
		{
			for (int x = 0, w = heights.GetSizeX(); x < w; x++)
			{
				float height = heights.Get(x, h - 1 - y).height;
				asFloat.Set(x, y, height);
			}
		}
	}
}

bool TerrainHeightManager::GetHeight(float x, float y, float* height, CVec3* normal /* = NULL*/) const
{
	//NDebug::PerformanceDebugVarGuard profile(terrain_GetHeight, false);
  NI_PROFILE_HEAVY_FUNCTION

	GridConstants const& params = pOwner->GetGridConstants();
	TerrainAttributes blended = {0.0f, 0.0f, 0.0f, 0.0f};

	if (heights.Get())
		blended = ArraySampler::Bilinear(heights, x / params.worldSize.x, 1.0f - y / params.worldSize.y);

	NI_VERIFY( height, "Invalid result storage!", return false; );
	*height = blended.height;

	if (normal != NULL)
	{
		normal->x = blended.normalX;
		normal->y = blended.normalY;
		normal->z = sqrtf(1 - normal->x * normal->x - normal->y * normal->y);
	}
	return true;
}

float TerrainHeightManager::GetHeightFast(float x, float y) const
{
  if (!heights.Get())
    return 0.0f;

	GridConstants const& params = pOwner->GetGridConstants();
	TerrainAttributes blended = {0.0f, 0.0f, 0.0f, 0.0f};

	blended = ArraySampler::Nearest(heights, x / params.worldSize.x, 1.0f - y / params.worldSize.y);
  return blended.height;
}

unsigned short TerrainHeightManager::FloatAsShort(float x)
{
	return (unsigned short)Float2Int(ClampFast(x * SHORTHEIGHT_SCALE + SHORTHEIGHT_OFFSET, 0.0f, 65535.0f));
}

float TerrainHeightManager::ShortAsFloat(unsigned short x)
{
	return ((float)x - SHORTHEIGHT_OFFSET) / SHORTHEIGHT_SCALE;
}

} // namespace Terrain

// REGISTER_DEV_VAR("dx", g_dx, STORAGE_NONE);
// REGISTER_DEV_VAR("dy", g_dy, STORAGE_NONE);

// end of TerrainHeightManager.cpp
