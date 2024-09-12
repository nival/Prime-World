#include "stdafx.h"

#include "renderflagsconverter.h"
#include "renderstatesmanager.h"
#include "../System/BitData.h"
#include "GlobalMasks.h"
#include "IConfigManager.h"
#include "MaterialSpec.h"

//#define USE_STATEBLOCK_CACHE

#ifdef _DEBUG
#define USE_STATESTATS
#endif

#ifdef USE_STATESTATS
#define STATESTATS(cmd) cmd
#else
#define STATESTATS(cmd) (void)0
#endif

namespace Render
{

namespace {
#ifdef USE_STATESTATS
	static int g_statesDebugAll;
	static int g_statesDebugSet;
	static int g_statesDebugAllSampler;
	static int g_statesDebugSetSampler;
  static int g_statesDebugAllStencil;
  static int g_statesDebugSetStencil;
	static int g_statesDebugDirect;
	static NDebug::StringDebugVar g_statesDebug("States", "Render");
#endif // USE_STATESTATS

	static CArray1Bit g_cachedStates;
}

RenderStatesManager::RenderStatesManager()
{
	g_cachedStates.SetSize(256);
	g_cachedStates.FillZero();
	g_cachedStates.SetData(D3DRS_ALPHABLENDENABLE);
	g_cachedStates.SetData(D3DRS_SRCBLEND);
	g_cachedStates.SetData(D3DRS_DESTBLEND);
	g_cachedStates.SetData(D3DRS_ALPHATESTENABLE);
	g_cachedStates.SetData(D3DRS_ALPHAREF);
	g_cachedStates.SetData(D3DRS_ALPHAFUNC);
	g_cachedStates.SetData(D3DRS_CULLMODE);
	//g_cachedStates.SetData(D3DRS_SEPARATEALPHABLENDENABLE);
	//g_cachedStates.SetData(D3DRS_SRCBLENDALPHA);
	//g_cachedStates.SetData(D3DRS_DESTBLENDALPHA);

  stencilLock = 0;

  Init();
}

RenderStatesManager::~RenderStatesManager()
{
}

void RenderStatesManager::OnDeviceLost()
{
  renderStateCache.clear();
  samplerStateCache.clear();
  std::fill( stencilStateCache, stencilStateCache + STENCILSTATE_COUNT, DXStateBlockRef() );
}

void RenderStatesManager::Init()
{
  lastRenderState.alwaysFailCompare = 1;
  for (int i = 0; i < ARRAY_SIZE(lastSamplerState); ++i)
    lastSamplerState[i].alwaysFailCompare = 1;
}

void RenderStatesManager::SetState(RenderState state)
{
	STATESTATS(g_statesDebugAll++);
  if(GetRuntimePins().RenderModeValue != NDb::RENDERMODEPIN_RENDERNORMAL)
    state.SetEmissive(NDb::ONOFFSTATE_OFF);
	if(lastRenderState == state)
		return;
	STATESTATS(g_statesDebugSet++);
	lastRenderState = state;

	IDirect3DDevice9* device = GetDevice();

#ifdef USE_STATEBLOCK_CACHE
	// Check cache first
	DXStateBlockRef& cached = renderStateCache[state.bitmask];
	if (cached)
	{
		cached->Apply();
		return;
	}
	
	// Begin caching
	device->BeginStateBlock();
#endif // USE_STATEBLOCK_CACHE

	// Set blend state
  const bool emissive = (state.GetEmissive() == NDb::ONOFFSTATE_ON);
  const D3DBLEND SrcAlpha = /*emissive ? D3DBLEND_ONE :*/ D3DBLEND_SRCALPHA;
  const D3DBLEND InvSrcAlpha = /*emissive ? D3DBLEND_SRCALPHA :*/ D3DBLEND_INVSRCALPHA;
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, state.GetBlendMode() != NDb::BLENDMODE_OFF ? TRUE : FALSE);
	switch (state.GetBlendMode())
	{
	case NDb::BLENDMODE_OFF:
		break;
  case NDb::BLENDMODE_LERPBYALPHA:
    device->SetRenderState(D3DRS_SRCBLEND,  SrcAlpha);
    device->SetRenderState(D3DRS_DESTBLEND, InvSrcAlpha);
    break;
  case NDb::BLENDMODE_PREMULTIPLIEDLERP:
    device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
    device->SetRenderState(D3DRS_DESTBLEND, InvSrcAlpha);
    break;
	case NDb::BLENDMODE_ADDCOLOR:
		device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case NDb::BLENDMODE_ADDCOLORMULALPHA:
		device->SetRenderState(D3DRS_SRCBLEND,  SrcAlpha);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case NDb::BLENDMODE_MULCOLOR:
		device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
  case NDb::BLENDMODE_MULINVCOLOR:
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
    break;
	default:
		NI_ALWAYS_ASSERT("Invalid blend mode");
	}

	// Set alpha test states
  device->SetRenderState(D3DRS_ALPHATESTENABLE, state.GetAlphaTest() == NDb::ONOFFSTATE_ON);
  device->SetRenderState(D3DRS_ALPHAFUNC, emissive ? D3DCMP_LESSEQUAL : D3DCMP_GREATEREQUAL);
  DWORD alphaRef = state.GetAlphaTestRef();
  if( emissive )
    alphaRef = 255 - alphaRef * BLOOM_ENCODING_THRESHOLD; 
	device->SetRenderState(D3DRS_ALPHAREF, alphaRef );

	// Set culling state
	device->SetRenderState(D3DRS_CULLMODE, state.GetCulling() == NDb::ONOFFSTATE_ON ? D3DCULL_CW : D3DCULL_NONE);

	//// Mark emissive pixels in alpha channel
	//device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	//device->SetRenderState(D3DRS_SRCBLENDALPHA, emissive ? D3DBLEND_ONE : D3DBLEND_SRCALPHA);
	//device->SetRenderState(D3DRS_DESTBLENDALPHA,  emissive ? D3DBLEND_ZERO : D3DBLEND_ONE);

#ifdef USE_STATEBLOCK_CACHE
	// Store compiled states in cache
	IDirect3DStateBlock9 *pStateBlock = 0;
	device->EndStateBlock(&pStateBlock);
	cached.Attach(pStateBlock);
#endif // USE_STATEBLOCK_CACHE
}

void RenderStatesManager::SetStateDirect(D3DRENDERSTATETYPE State, DWORD Value)
{
	// invalidate cache if one of cached states is set directly
	if (g_cachedStates.GetData(State))
		lastRenderState.alwaysFailCompare = 1;

	GetDevice()->SetRenderState(State, Value);
	STATESTATS(g_statesDebugDirect++);
}

void RenderStatesManager::SetSamplerState(unsigned index, SamplerState const& state)
{
	STATESTATS(g_statesDebugAllSampler++);
	if (index < ARRAY_SIZE(lastSamplerState) && lastSamplerState[index] == state)
		return;
	STATESTATS(g_statesDebugSetSampler++);

  if (index < ARRAY_SIZE(lastSamplerState))
    lastSamplerState[index] = state;

	// texture address
	static const D3DTEXTUREADDRESS tblAddress[] = {D3DTADDRESS_WRAP, D3DTADDRESS_CLAMP, D3DTADDRESS_MIRROR, D3DTADDRESS_BORDER};
  // minification filter
  static const D3DTEXTUREFILTERTYPE tblMinFilter[] = {D3DTEXF_POINT, D3DTEXF_LINEAR, D3DTEXF_ANISOTROPIC, D3DTEXF_ANISOTROPIC, 
    D3DTEXF_ANISOTROPIC, D3DTEXF_ANISOTROPIC, D3DTEXF_ANISOTROPIC, D3DTEXF_ANISOTROPIC};
  // magnification filter
  static const D3DTEXTUREFILTERTYPE tblMagFilter[] = {D3DTEXF_POINT, D3DTEXF_LINEAR};
  // mip-mapping filter
  static const D3DTEXTUREFILTERTYPE tblMipFilter[] = {D3DTEXF_NONE, D3DTEXF_POINT, D3DTEXF_LINEAR};

  IDirect3DDevice9* device = GetDevice();

#ifdef USE_STATEBLOCK_CACHE
  // Check cache first
  NI_ASSERT(index < 256, "RenderStatesManager::SetSamplerState: Too big sampler index");
  NI_ASSERT(0 == (state.bitmask & 0xFF000000), "RenderStatesManager::SetSamplerState: wrong sampler state");
  const DWORD idx = state.bitmask | (index << 24);
  DXStateBlockRef& cached = samplerStateCache[idx];
  if (cached)
  {
    cached->Apply();
#ifdef _DEBUG
    DWORD value;
#pragma warning( push )
#pragma warning(disable:4389) // '==' : signed/unsigned mismatch 
    device->GetSamplerState(index, D3DSAMP_ADDRESSU, &value);
    NI_ASSERT(tblAddress[state.addressU] == value, "RenderStatesManager::SetSamplerState: wrong state block");
    device->GetSamplerState(index, D3DSAMP_ADDRESSV, &value);
    NI_ASSERT(tblAddress[state.addressV] == value, "RenderStatesManager::SetSamplerState: wrong state block");
    //device->GetSamplerState(index, D3DSAMP_MAXANISOTROPY, &value);
    //NI_ASSERT(state.minFilter - NDb::MINFILTERTYPE_ANISOTROPIC1X + 1 == value, "RenderStatesManager::SetSamplerState: wrong state block");
    device->GetSamplerState(index, D3DSAMP_MINFILTER, &value);
    NI_ASSERT(tblMinFilter[state.minFilter] == value, "RenderStatesManager::SetSamplerState: wrong state block");
    device->GetSamplerState(index, D3DSAMP_MAGFILTER, &value);
    NI_ASSERT(tblMagFilter[state.magFilter] == value, "RenderStatesManager::SetSamplerState: wrong state block");
    device->GetSamplerState(index, D3DSAMP_MIPFILTER, &value);
    NI_ASSERT(tblMipFilter[state.mipFilter] == value, "RenderStatesManager::SetSamplerState: wrong state block");
#pragma warning( pop )
#endif
    return;
  }

  // Begin caching
  device->BeginStateBlock();
#endif // USE_STATEBLOCK_CACHE

	ASSERT(state.addressU < ARRAY_SIZE(tblAddress) && state.addressV < ARRAY_SIZE(tblAddress));
	device->SetSamplerState(index, D3DSAMP_ADDRESSU, tblAddress[state.addressU]);
	device->SetSamplerState(index, D3DSAMP_ADDRESSV, tblAddress[state.addressV]);

	// anisotropy
	//if (state.minFilter >= NDb::MINFILTERTYPE_ANISOTROPIC1X)
	  //device->SetSamplerState(index, D3DSAMP_MAXANISOTROPY, state.minFilter - NDb::MINFILTERTYPE_ANISOTROPIC1X + 1);

	ASSERT(state.minFilter < ARRAY_SIZE(tblMinFilter));
	device->SetSamplerState(index, D3DSAMP_MINFILTER, tblMinFilter[state.minFilter]);

	ASSERT(state.magFilter < ARRAY_SIZE(tblMagFilter));
	device->SetSamplerState(index, D3DSAMP_MAGFILTER, tblMagFilter[state.magFilter]);

	ASSERT(state.mipFilter < ARRAY_SIZE(tblMipFilter));
	device->SetSamplerState(index, D3DSAMP_MIPFILTER, tblMipFilter[state.mipFilter]);

#ifdef USE_STATEBLOCK_CACHE
  // Store compiled states in cache
  IDirect3DStateBlock9 *pStateBlock = 0;
  device->EndStateBlock(&pStateBlock);
  cached.Attach(pStateBlock);
#endif // USE_STATEBLOCK_CACHE
}

void RenderStatesManager::SetStencilState(StencilState state, DWORD mask /*= 0xFFFFFFFF*/, DWORD bits /*= 0xFFFFFFFF*/)
{
  if(stencilLock)
    return;
  STATESTATS(g_statesDebugAllStencil++);

    if( bits == DWORD(-1) )
      bits = mask;  // Wine bugs workaround

  IDirect3DDevice9* const device = GetDevice();

  if(state > STENCILSTATE_IGNORE)
  {
    if( bits != lastStencilBits )
      device->SetRenderState(D3DRS_STENCILREF, lastStencilBits = bits);

    if( mask != lastStencilMask )
    {
      lastStencilMask = mask;
      device->SetRenderState(D3DRS_STENCILMASK, lastStencilMask);
      device->SetRenderState(D3DRS_STENCILWRITEMASK, lastStencilMask);
    }
  }

  if( state == lastStencilState )
    return;
  STATESTATS(g_statesDebugSetStencil++);

  lastStencilState = state;
  if (state == STENCILSTATE_INVALID)
    return;


  static struct StencilStateParams {
    StencilState state;
    DWORD enable;
    DWORD pass;
    DWORD func;
  } presets[STENCILSTATE_COUNT] = {
    {STENCILSTATE_INVALID,   FALSE, D3DSTENCILOP_KEEP,    D3DCMP_ALWAYS},
    {STENCILSTATE_IGNORE,    FALSE, D3DSTENCILOP_KEEP,    D3DCMP_ALWAYS},
    {STENCILSTATE_WRITEBITS, TRUE,  D3DSTENCILOP_REPLACE, D3DCMP_ALWAYS},
    {STENCILSTATE_CHECKBITS, TRUE,  D3DSTENCILOP_KEEP,    D3DCMP_EQUAL},
  };

#ifdef USE_STATEBLOCK_CACHE
  // Check cache first
  DXStateBlockRef& cached = stencilStateCache[state];
  if (cached)
  {
    cached->Apply();
    return;
  }

  // Begin caching
  device->BeginStateBlock();
#endif // USE_STATEBLOCK_CACHE

  NI_ASSERT(presets[state].state == state, "Array of StencilStateParams corrupted.");
  StencilStateParams& params = presets[state];

  device->SetRenderState(D3DRS_STENCILENABLE, params.enable);
  device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
  device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
  device->SetRenderState(D3DRS_STENCILPASS, params.pass);
  device->SetRenderState(D3DRS_STENCILFUNC, params.func);

#ifdef USE_STATEBLOCK_CACHE
	// Store compiled states in cache
	IDirect3DStateBlock9 *pStateBlock = 0;
	device->EndStateBlock(&pStateBlock);
	cached.Attach(pStateBlock);
#endif // USE_STATEBLOCK_CACHE
}

void RenderStatesManager::SetStencilStateAddonBits(DWORD mask, DWORD bits)
{
  if (lastStencilState == STENCILSTATE_WRITEBITS)
    GetDevice()->SetRenderState(D3DRS_STENCILREF, lastStencilBits & ~mask | bits & mask);
}

void RenderStatesManager::UpdateStats()
{
#ifdef USE_STATESTATS
  g_statesDebug.SetValue("RS: %i/%i + %i; SS: %i/%i; StS: %i/%i", g_statesDebugSet, g_statesDebugAll, g_statesDebugDirect,
                         g_statesDebugSetSampler, g_statesDebugAllSampler, g_statesDebugSetStencil, g_statesDebugAllStencil);
	g_statesDebugAll = 0;
	g_statesDebugSet = 0;
	g_statesDebugAllSampler = 0;
	g_statesDebugSetSampler = 0;
  g_statesDebugAllStencil = 0;
  g_statesDebugSetStencil = 0;
	g_statesDebugDirect = 0;
#endif // USE_STATESTATS
}

namespace {
#define ENUM_PAIR(e) {e, #e}
  struct {
    D3DRENDERSTATETYPE state;
    char const* pName;
  } g_renderStates[] = {
    ENUM_PAIR(D3DRS_ZENABLE),
    ENUM_PAIR(D3DRS_FILLMODE),
    ENUM_PAIR(D3DRS_SHADEMODE),
    ENUM_PAIR(D3DRS_ZWRITEENABLE),
    ENUM_PAIR(D3DRS_ALPHATESTENABLE),
    ENUM_PAIR(D3DRS_LASTPIXEL),
    ENUM_PAIR(D3DRS_SRCBLEND),
    ENUM_PAIR(D3DRS_DESTBLEND),
    ENUM_PAIR(D3DRS_CULLMODE),
    ENUM_PAIR(D3DRS_ZFUNC),
    ENUM_PAIR(D3DRS_ALPHAREF),
    ENUM_PAIR(D3DRS_ALPHAFUNC),
    ENUM_PAIR(D3DRS_DITHERENABLE),
    ENUM_PAIR(D3DRS_ALPHABLENDENABLE),
    ENUM_PAIR(D3DRS_FOGENABLE),
    ENUM_PAIR(D3DRS_SPECULARENABLE),
    ENUM_PAIR(D3DRS_FOGCOLOR),
    ENUM_PAIR(D3DRS_FOGTABLEMODE),
    ENUM_PAIR(D3DRS_FOGSTART),
    ENUM_PAIR(D3DRS_FOGEND),
    ENUM_PAIR(D3DRS_FOGDENSITY),
    ENUM_PAIR(D3DRS_RANGEFOGENABLE),
    ENUM_PAIR(D3DRS_STENCILENABLE),
    ENUM_PAIR(D3DRS_STENCILFAIL),
    ENUM_PAIR(D3DRS_STENCILZFAIL),
    ENUM_PAIR(D3DRS_STENCILPASS),
    ENUM_PAIR(D3DRS_STENCILFUNC),
    ENUM_PAIR(D3DRS_STENCILREF),
    ENUM_PAIR(D3DRS_STENCILMASK),
    ENUM_PAIR(D3DRS_STENCILWRITEMASK),
    ENUM_PAIR(D3DRS_TEXTUREFACTOR),
    ENUM_PAIR(D3DRS_WRAP0),
    ENUM_PAIR(D3DRS_WRAP1),
    ENUM_PAIR(D3DRS_WRAP2),
    ENUM_PAIR(D3DRS_WRAP3),
    ENUM_PAIR(D3DRS_WRAP4),
    ENUM_PAIR(D3DRS_WRAP5),
    ENUM_PAIR(D3DRS_WRAP6),
    ENUM_PAIR(D3DRS_WRAP7),
    ENUM_PAIR(D3DRS_CLIPPING),
    ENUM_PAIR(D3DRS_LIGHTING),
    ENUM_PAIR(D3DRS_AMBIENT),
    ENUM_PAIR(D3DRS_FOGVERTEXMODE),
    ENUM_PAIR(D3DRS_COLORVERTEX),
    ENUM_PAIR(D3DRS_LOCALVIEWER),
    ENUM_PAIR(D3DRS_NORMALIZENORMALS),
    ENUM_PAIR(D3DRS_DIFFUSEMATERIALSOURCE),
    ENUM_PAIR(D3DRS_SPECULARMATERIALSOURCE),
    ENUM_PAIR(D3DRS_AMBIENTMATERIALSOURCE),
    ENUM_PAIR(D3DRS_EMISSIVEMATERIALSOURCE),
    ENUM_PAIR(D3DRS_VERTEXBLEND),
    ENUM_PAIR(D3DRS_CLIPPLANEENABLE),
    ENUM_PAIR(D3DRS_POINTSIZE),
    ENUM_PAIR(D3DRS_POINTSIZE_MIN),
    ENUM_PAIR(D3DRS_POINTSPRITEENABLE),
    ENUM_PAIR(D3DRS_POINTSCALEENABLE),
    ENUM_PAIR(D3DRS_POINTSCALE_A),
    ENUM_PAIR(D3DRS_POINTSCALE_B),
    ENUM_PAIR(D3DRS_POINTSCALE_C),
    ENUM_PAIR(D3DRS_MULTISAMPLEANTIALIAS),
    ENUM_PAIR(D3DRS_MULTISAMPLEMASK),
    ENUM_PAIR(D3DRS_PATCHEDGESTYLE),
    ENUM_PAIR(D3DRS_DEBUGMONITORTOKEN),
    ENUM_PAIR(D3DRS_POINTSIZE_MAX),
    ENUM_PAIR(D3DRS_INDEXEDVERTEXBLENDENABLE),
    ENUM_PAIR(D3DRS_COLORWRITEENABLE),
    ENUM_PAIR(D3DRS_TWEENFACTOR),
    ENUM_PAIR(D3DRS_BLENDOP),
    ENUM_PAIR(D3DRS_POSITIONDEGREE),
    ENUM_PAIR(D3DRS_NORMALDEGREE),
    ENUM_PAIR(D3DRS_SCISSORTESTENABLE),
    ENUM_PAIR(D3DRS_SLOPESCALEDEPTHBIAS),
    ENUM_PAIR(D3DRS_ANTIALIASEDLINEENABLE),
    ENUM_PAIR(D3DRS_MINTESSELLATIONLEVEL),
    ENUM_PAIR(D3DRS_MAXTESSELLATIONLEVEL),
    ENUM_PAIR(D3DRS_ADAPTIVETESS_X),
    ENUM_PAIR(D3DRS_ADAPTIVETESS_Y),
    ENUM_PAIR(D3DRS_ADAPTIVETESS_Z),
    ENUM_PAIR(D3DRS_ADAPTIVETESS_W),
    ENUM_PAIR(D3DRS_ENABLEADAPTIVETESSELLATION),
    ENUM_PAIR(D3DRS_TWOSIDEDSTENCILMODE),
    ENUM_PAIR(D3DRS_CCW_STENCILFAIL),
    ENUM_PAIR(D3DRS_CCW_STENCILZFAIL),
    ENUM_PAIR(D3DRS_CCW_STENCILPASS),
    ENUM_PAIR(D3DRS_CCW_STENCILFUNC),
    ENUM_PAIR(D3DRS_COLORWRITEENABLE1),
    ENUM_PAIR(D3DRS_COLORWRITEENABLE2),
    ENUM_PAIR(D3DRS_COLORWRITEENABLE3),
    ENUM_PAIR(D3DRS_BLENDFACTOR),
    ENUM_PAIR(D3DRS_SRGBWRITEENABLE),
    ENUM_PAIR(D3DRS_DEPTHBIAS),
    ENUM_PAIR(D3DRS_WRAP8),
    ENUM_PAIR(D3DRS_WRAP9),
    ENUM_PAIR(D3DRS_WRAP10),
    ENUM_PAIR(D3DRS_WRAP11),
    ENUM_PAIR(D3DRS_WRAP12),
    ENUM_PAIR(D3DRS_WRAP13),
    ENUM_PAIR(D3DRS_WRAP14),
    ENUM_PAIR(D3DRS_WRAP15),
    ENUM_PAIR(D3DRS_SEPARATEALPHABLENDENABLE),
    ENUM_PAIR(D3DRS_SRCBLENDALPHA),
    ENUM_PAIR(D3DRS_DESTBLENDALPHA),
    ENUM_PAIR(D3DRS_BLENDOPALPHA),
  };

  struct {
    D3DSAMPLERSTATETYPE state;
    char const* pName;
  } g_samplerStates[] = {
    ENUM_PAIR(D3DSAMP_ADDRESSU),
    ENUM_PAIR(D3DSAMP_ADDRESSV),
    ENUM_PAIR(D3DSAMP_ADDRESSW),
    ENUM_PAIR(D3DSAMP_BORDERCOLOR),
    ENUM_PAIR(D3DSAMP_MAGFILTER),
    ENUM_PAIR(D3DSAMP_MINFILTER),
    ENUM_PAIR(D3DSAMP_MIPFILTER),
    ENUM_PAIR(D3DSAMP_MIPMAPLODBIAS),
    ENUM_PAIR(D3DSAMP_MAXMIPLEVEL),
    ENUM_PAIR(D3DSAMP_MAXANISOTROPY),
    ENUM_PAIR(D3DSAMP_SRGBTEXTURE),
    ENUM_PAIR(D3DSAMP_ELEMENTINDEX),
    ENUM_PAIR(D3DSAMP_DMAPOFFSET),
  };
#undef ENUM_PAIR
}// anonymous namespace

void RenderStatesManager::DumpStates()
{
  for (int i = 0; i < ARRAY_SIZE(g_renderStates); i++)
  {
    DWORD val;
    HRESULT hr = GetDevice()->GetRenderState(g_renderStates[i].state, &val);
    if (SUCCEEDED(hr))
    {
      DebugTrace("0x%08X = %s", val, g_renderStates[i].pName);
    }
    else
    {
      DebugTrace("  FAILED = %s", g_renderStates[i].pName);
    }
  }

  for (int j = 0; j < 8; j++)
  {
    DebugTrace("Sampler States (%i)", j);
    for (int i = 0; i < ARRAY_SIZE(g_samplerStates); i++)
    {
      DWORD val;
      HRESULT hr = GetDevice()->GetSamplerState(j, g_samplerStates[i].state, &val);
      if (SUCCEEDED(hr))
      {
        DebugTrace("0x%08X = (%i) %s", val, j, g_samplerStates[i].pName);
      }
      else
      {
        DebugTrace("  FAILED = (%i) %s", j, g_samplerStates[i].pName);
      }
    }
  }

  CVec4 values[32];
  DebugTrace("Vertex Shader Constants");
  HRESULT hr = GetDevice()->GetVertexShaderConstantF(0, (float*)values, ARRAY_SIZE(values));
  if (SUCCEEDED(hr))
  {
    for (int i = 0; i < ARRAY_SIZE(values); i++)
    {
      DebugTrace("%02i 0x%08X 0x%08X 0x%08X 0x%08X", i, *(DWORD*)&values[i].x, *(DWORD*)&values[i].y, *(DWORD*)&values[i].z, *(DWORD*)&values[i].w);
    }
  }
  else
  {
    DebugTrace("FAILED");
  }

  DebugTrace("Pixel Shader Constants");
  hr = GetDevice()->GetPixelShaderConstantF(0, (float*)values, ARRAY_SIZE(values));
  if (SUCCEEDED(hr))
  {
    for (int i = 0; i < ARRAY_SIZE(values); i++)
    {
      DebugTrace("%02i 0x%08X 0x%08X 0x%08X 0x%08X", i, *(DWORD*)&values[i].x, *(DWORD*)&values[i].y, *(DWORD*)&values[i].z, *(DWORD*)&values[i].w);
    }
  }
  else
  {
    DebugTrace("FAILED");
  }
}

}; // namespace Render