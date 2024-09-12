#include "stdafx.h"
#include "AmbienceMap.h"

#include "../Render/TextureManager.h"
#include "../System/DebugVar.h"
#include "dxerr.h"

#include "../Render/dipdescriptor.h"
#include "../Render/ImmediateRenderer.h"
#include "../Render/renderer.h"

static NDebug::PerformanceDebugVar profile_UpdateEnvironment("AmbUpdate", "AmbienceMap", 0, 0.05, false);

AmbienceMap::AmbienceMap() : 
  valid(false),
  worldSize(1.0f, 1.0f),
  radius(0.5f),
  directivity(0.0f),
  pTexture(NULL),
  palette(),
  unpalette(),
  mapWidth(0),
  mapHeight(0),
  pMap(NULL),
  environment(),
  rect(0,0,0,0)
{
}

AmbienceMap::~AmbienceMap()
{
}

bool AmbienceMap::Init(NDb::SoundAmbienceMap const& dbAmbienceMap, CVec2 const& worldSize_, nstl::vector<unsigned int> const& colors)
{
  NI_VERIFY(!valid, "Initializing already initialized AmbienceMap", return false);

  worldSize = worldSize_;
  radius = dbAmbienceMap.radius;
  directivity = dbAmbienceMap.directivity;
  pTexture = NULL;
  if (IsValid(dbAmbienceMap.texture))
    pTexture = Render::LoadTexture2D(*dbAmbienceMap.texture);
  if (!pTexture || pTexture == Render::GetDefaultTexture2D())
  {
    pTexture = NULL;
    return false;
  }
  
  InitPalette(colors);

  // create map
  mapWidth = pTexture->GetWidth();
  mapHeight = pTexture->GetHeight();
  Reset(pMap, new unsigned char[mapWidth * mapHeight]);
  if (!FillMapFrom(pTexture))
    return false;

  valid = true;
  return valid;
}

void AmbienceMap::InitPalette(nstl::vector<unsigned int> const& colors)
{
  // mapping from index to color
  palette.resize(1 + colors.size());
  palette[0] = 0xBADBAD; // even if this color is used in a real texture there should be no problem
  for (int i = 0, n = colors.size(); i < n; ++i)
    palette[i + 1] = colors[i];

  // mapping from color to index (for texture decoding)
  unpalette.clear();
  for (int i = 0, n = palette.size(); i < n; ++i)
    unpalette[palette[i]] = (unsigned char)i;

  // calculated percents are of the same size as palette
  environment.resize(palette.size());
  for (int i = 0, n = environment.size(); i < n; ++i)
    environment[i] = 0.0f;
}

void AmbienceMap::Clear()
{
  ZeroMemory(Get(pMap), mapWidth * mapHeight);
}

bool AmbienceMap::FillMapFrom(Render::Texture2DRef const& pSource)
{
  const DXSurfaceRef &pSurface = pSource->GetSurface(0);
  D3DSURFACE_DESC desc;
  HRESULT hr = pSurface->GetDesc(&desc);
  NI_VERIFY(hr == D3D_OK, 
    NStr::StrFmt("Cannot access texture surface description, DX Error: [0x%08X] %s (%s)", hr, DXGetErrorStringA(hr), DXGetErrorDescriptionA(hr)),
    Clear(); return false);
  NI_VERIFY(desc.Width == mapWidth && desc.Height == mapHeight, 
    NStr::StrFmt("Texture dimensions (%u, %u) differ from those in AmbienceMap (%u, %u)", desc.Width, desc.Height, mapWidth, mapHeight),
    Clear(); return false);
  NI_VERIFY(desc.Format == D3DFMT_A8R8G8B8, 
    NStr::StrFmt("Texture format %u is unsupported, use D3DFMT_A8R8G8B8 instead", desc.Format),
    Clear(); return false);

  // copy the data from texture pixels to the easier accessible array
  Render::LockedRect lock = pSource->LockRect(0, Render::LOCK_READONLY);
  NI_VERIFY(lock.data, "Unable to lock texture to update map from it", return false);

  UnPalette::const_iterator itEnd = unpalette.end();

  unsigned char* pDst = &pMap[0];
  for (unsigned i = 0; i < mapHeight; i++)
  {
    unsigned int* pSrc = reinterpret_cast<unsigned int*>(lock.data);
    for (unsigned j = 0; j < mapWidth; j++)
    {
      UnPalette::iterator it = unpalette.find(*pSrc++ & 0x00FFFFFF);
      *pDst++ = (it == itEnd) ? 0 : it->second;
    }
    lock.data += lock.pitch;
  }
  pSource->UnlockRect(0);

  // update results for the first time
  UpdateEnvironment(VNULL2, VNULL2, true);

  return true;
}

void AmbienceMap::UpdateEnvironment(CVec3 const& pos, CVec3 const& dir, bool force /*= false*/)
{
  UpdateEnvironment(pos.AsVec2D(), dir.AsVec2D(), force); // its ok that direction is not normalized in that case, works as designed
}

void AmbienceMap::UpdateEnvironment(CVec2 const& pos, CVec2 const& dir, bool force)
{
  NDebug::PerformanceDebugVarGuard profile(profile_UpdateEnvironment, true);

  CVec2 pivot(pos);
  pivot.Displace(dir, directivity);
  pivot.x -= radius;
  pivot.y += radius;

  // convert to pixel indices
  NI_VERIFY(worldSize.x > FP_EPSILON && worldSize.y > FP_EPSILON, NStr::StrFmt("Zero or negative world size (%f, %f)", worldSize.x, worldSize.y), return);
  int xStart = (int)((float)mapWidth * pivot.x / worldSize.x);
  int xEnd = xStart + (int)((float)mapWidth * 2.0f * radius / worldSize.x);
  int yStart = (int)((float)mapHeight * (1.0f - pivot.y / worldSize.y));
  int yEnd = yStart + (int)((float)mapHeight * 2.0f * radius / worldSize.y);

  // clamp area
  xStart = ClampFast(xStart, 0, (int)mapWidth - 1);
  xEnd = ClampFast(xEnd, xStart, (int)mapWidth - 1); // last column excluded
  yStart = ClampFast(yStart, 0, (int)mapHeight - 1);
  yEnd = ClampFast(yEnd, yStart, (int)mapHeight - 1); // last row excluded

  // find if we need to recompute
  if (!force)
    force = !(rect.minx == xStart && rect.miny == yStart && rect.maxx == xEnd && rect.maxy == yEnd);
  if (!force)
    return;
  rect.Set(xStart, yStart, xEnd, yEnd);

  NI_ASSERT(environment.size() == palette.size(), "Calculated percents must be of the same size as palette");
  float total = 0.0f;
  for (int i = 0, n = environment.size(); i < n; ++i)
    environment[i] = 0.0f;

  int xCount = xEnd - xStart;
  int yCount = yEnd - yStart;
  if (xCount != 0 && yCount != 0)
  {
    // scan map and count different ambients
    unsigned char* pRow = Get(pMap) + yStart * mapWidth + xStart;
    for (int i = yCount; i > 0; --i)
    {
      unsigned char* pPixel = pRow;
      for (int j = xCount; j > 0; --j)
        environment[*pPixel++] += 1.0f;
      pRow += mapWidth;
    }

    // convert to percentages
    total = (float)(xCount * yCount);
    for (int i = 0, n = environment.size(); i < n; ++i)
      environment[i] /= total;
  }

/*
#ifdef _DEBUG
  static const int BUFFER_SIZE = 256;
  char buffer[BUFFER_SIZE], *ptr = buffer;
  int bufferSizeLeft = BUFFER_SIZE;
  for (int i = 0, n = environment.size(); i < n && bufferSizeLeft > 0; ++i)
  {
    int written = sprintf_s(ptr, bufferSizeLeft, "%3.0f%% ",  environment[i] * 100.0f);
    if (written <= 0)
      break;
    ptr += written;
    bufferSizeLeft -= written;
  }
  ambienceDebugStr.SetValue("%s", buffer);
#endif
*/
}

void AmbienceMap::RenderDebug()
{
  int x = 128, y = 128;
  CTRect<int> rc(x, y, x + mapWidth, y + mapHeight);
  Render::GetImmRenderer()->RenderScreenQuad(rc, Render::ImmRenderer::Params("DiffuseMap", pTexture));

  Render::RenderState rs;
  rs.SetBlendMode(NDb::BLENDMODE_LERPBYALPHA);
  rs.SetAlphaTest(NDb::ONOFFSTATE_OFF);
  Render::GetStatesManager()->SetState(rs);
  rc.Set(x + rect.minx, y + rect.miny, x + rect.maxx, y + rect.maxy);
  Render::GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST0, Render::HDRColor(0.0f, 0.0f, 0.0f, 0.25f));
  Render::GetImmRenderer()->RenderScreenQuad(rc, Render::ImmRenderer::Params("ConstantColor"));
}

// end of AmbienceMap.cpp
