#include "stdafx.h"

#include "../Render/RenderInterface.h"
#include "../Render/FullScreenFX.h"
#include "../Render/IConfigManager.h"
#include "../Render/renderflagsconverter.h"
#include "../Terrain/Terrain.h"
#include "PFWorld.h"
#include "PFRenderInterface.h"
#include "AdventureScreen.h"
#include "PFClientNatureMap.h"
#include "PFPostFXParams.h"


static bool s_enableDelay = true;
REGISTER_VAR( "pfx_enable_delay", s_enableDelay, STORAGE_NONE );


NDebug::DebugVar<CVec3> g_natureCoef( "ScreenNatureCoefs", "Statistics" );

static NDebug::PerformanceDebugVar g_pfxCalc( "PostFXCalc", "Render", 0, 1.0, false );
static NDebug::PerformanceDebugVar g_pfxGetRT( "PostFX:GetRTData", "Render", 0, 1.0, false );

static bool g_PostFXReadEnabled = true;

using namespace Render;

namespace
{
  DECLARE_NULL_RENDER_FLAG

  float inline Float16to32(unsigned short n)
  {
    unsigned int m = ((n & 0x8000) << 16) | (((n & 0x7FFF) << 13) + 0x38000000);
    return *reinterpret_cast<float*>(&m);
  }

  void inline ParsePixel16F(void* pData, CVec4* pOut)
  {
    unsigned short* pSrc = reinterpret_cast<unsigned short*>(pData);
    float* pDst = &pOut->r;
    *pDst++ = Float16to32(*pSrc++);
    *pDst++ = Float16to32(*pSrc++);
    *pDst++ = Float16to32(*pSrc++);
    *pDst++ = Float16to32(*pSrc++);
  }

  void inline ParsePixel32F(void* pData, CVec4* pOut)
  {
    float* pSrc = reinterpret_cast<float*>(pData);
    float* pDst = &pOut->r;
    *pDst++ = *pSrc++;
    *pDst++ = *pSrc++;
    *pDst++ = *pSrc++;
    *pDst++ = *pSrc++;
  }
} // anonymous namespace

namespace PF_Render
{

Render::FullScreenFX::Params  s_pivotParams[NATURE_TYPES_COUNT];

Render::FullScreenFX::Params s_overrideParams[NATURE_TYPES_COUNT];
bool s_useOverrideParams = false;

const Render::FullScreenFX::Params* PostFXParamsManager::GetPivotParams() { return s_useOverrideParams ? s_overrideParams : s_pivotParams; }


const int screenMapWidth = 8;
const int screenMapHeight = 8;

static bool s_SharpTheSame = false;
static bool s_ColorTheSame = false;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return true if all of postprocessing parameters are the same for different nature types
static void NeedCalculateCoefs()
{
  if ( s_useOverrideParams )
  {
    s_SharpTheSame = true;
    s_ColorTheSame = false;
    return;
  }

  bool allTheSame = true;
  bool colorTheSame = true;
  s_SharpTheSame = true;
  for(int i = 0; i < NATURE_TYPES_COUNT - 1;)
  {
    Render::FullScreenFX::Params &param = s_pivotParams[i];
    Render::FullScreenFX::Params &nextParam = s_pivotParams[++i];
    allTheSame &= (param.Gamma == nextParam.Gamma);  
    allTheSame &= (param.InMin == nextParam.InMin);  
    allTheSame &= (param.InMax == nextParam.InMax);  
    allTheSame &= (param.OutMin == nextParam.OutMin);  
    allTheSame &= (param.OutMax == nextParam.OutMax);  
    colorTheSame &= (param.Color == nextParam.Color);  
    colorTheSame &= (param.ColorCastCoef == nextParam.ColorCastCoef);  
    s_SharpTheSame &= (param.SharpCoef == nextParam.SharpCoef);  
    s_SharpTheSame &= (param.SharpPixelSize == nextParam.SharpPixelSize);  
  }

  bool colorCoefIsZero = true;
  if(!colorTheSame)
    for(int i = 0; i < NATURE_TYPES_COUNT; ++i)
      colorCoefIsZero &= (s_pivotParams[i].ColorCastCoef == 0.0f);  

  s_ColorTheSame = (allTheSame && (colorTheSame || colorCoefIsZero));
}

void PostFXParamsManager::SetOverrideFXParams( const Render::FullScreenFX::Params* params )
{
  if ( !params )
  {
    s_useOverrideParams = false;
  }
  else 
  {
    for ( int i = 0; i < NATURE_TYPES_COUNT; ++i )
    {
      s_overrideParams[i] = *params;
      s_overrideParams[i].Color = s_pivotParams[i].Color;
      s_overrideParams[i].ColorCastCoef = s_pivotParams[i].ColorCastCoef;
      s_overrideParams[i].SharpPixelSize = s_pivotParams[i].SharpPixelSize;
      s_overrideParams[i].SharpCoef = s_pivotParams[i].SharpCoef;
    }
    s_useOverrideParams = true;
  }

  NeedCalculateCoefs();
}

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PostFXParamsManager::PostFXParamsManager()
  : DeviceLostHandler(HANDLERPRIORITY_LOW)
  , dbParams(this, &PostFXParamsManager::OnDBParamsChanged)
  , currSurf()
  , isCoeffChanged(false)
  , disabled(false)
  , coeff(VNULL4)
  , coefParser(NULL)
{
  SetDBParams( NDb::Get<NDb::PostFXParams>( NDb::DBID( "Tech/PostFX.PFXP.xdb" ) ) );
  
  const IConfigManager* const pCManager = GetIConfigManager();
  disabled = RENDER_DISABLED || pCManager->GetSysInfo().IsNullRef || !pCManager->HasVT() && !pCManager->HasR2VB();
  if(disabled)
    return;

  for(int i = 0; i < 2; ++i) {
    screenMap[i] = CreateRenderTexture2D(screenMapWidth, screenMapHeight, FORMAT_A8R8G8B8);
    mapData[i] = Create<TextureVtx>(TextureVtx::Sizes(1, 1, 4, 1), false);
  }

  D3DSURFACE_DESC desc = { mapData[0]->GetFormat(), D3DRTYPE_SURFACE, 0, D3DPOOL_SYSTEMMEM,
                           D3DMULTISAMPLE_NONE, 0, mapData[0]->GetWidth(), mapData[0]->GetHeight() };
  offscreenSurf = Create<RenderSurface>(desc);
  if (desc.Format == D3DFMT_A16B16G16R16F)
    coefParser = ParsePixel16F;
  else if (desc.Format == D3DFMT_A32B32G32R32F)
    coefParser = ParsePixel32F;
  else {
    NI_ALWAYS_ASSERT(NStr::StrFmt("Unsupported surface format 0x%08X", desc.Format));
  }

  AcquireSurfaces();

}

void PostFXParamsManager::SetDBParams( const NDb::PostFXParams* params )
{
  ZeroMemory(&s_pivotParams, sizeof(FullScreenFX::Params) * NATURE_TYPES_COUNT);

  dbParams = params;
  OnDBParamsChanged( NDb::DBID() );
}



void PostFXParamsManager::AcquireSurfaces()
{
  for(int i = 0; i < 2; ++i)
  {
    if( screenMap[i] )
      screenSurf[i] = screenMap[i]->GetSurface(0);
    if( mapData[i] )
      GetDevice()->ColorFill( Get(mapSurf[i] = mapData[i]->GetSurface(0)), NULL, D3DCOLOR_XRGB(0,255,0) );
  }
}


void PostFXParamsManager::OnDeviceLost()
{
  std::fill_n( screenSurf, ARRAY_SIZE(screenSurf), DXSurfaceRef() );
  std::fill_n( mapSurf, ARRAY_SIZE(mapSurf), DXSurfaceRef() );
}


void PostFXParamsManager::OnDeviceReset()
{
  if(disabled)
    return;

  AcquireSurfaces();
}


bool PostFXParamsManager::Calculate(bool _postFXEnabled, bool _sharpEnabled, bool _force)
{
  NI_STATIC_ASSERT((NATURE_TYPES_COUNT == NDb::KnownEnum<NDb::ENatureType>::sizeOf), WRONG_NATURE_TYPES_COUNT);

  if(disabled)
    return false;

  if(_force || _sharpEnabled && !s_SharpTheSame || _postFXEnabled && !s_ColorTheSame)
  {
    NDebug::PerformanceDebugVarGuard perfGuard(g_pfxCalc, true);

    // calculate coefs based on nature visibility
    if( RenderNatureMapToSurface(screenSurf[currSurf]) )
    {
      SmartRenderer::BindRenderTargetColor( 0, mapSurf[currSurf] );
      currSurf ^= int(s_enableDelay);

      // I assume here that RenderScreenQuad() sets bilinear filtering for source texture
      CVec4 startAndStep(1.0f / screenMapWidth, 1.0f / screenMapHeight, 2.0f / screenMapWidth, 2.0f / screenMapHeight);
      GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST1, startAndStep);

      GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params("DownScale", screenMap[currSurf]));

      SmartRenderer::BindRenderTargetDefault();
      isCoeffChanged = true;
    }
    return true;
  }
  return false;
}


bool PostFXParamsManager::RenderNatureMapToSurface(const DXSurfaceRef& surf)
{
  if(!NGameX::AdventureScreen::Instance() || disabled)
    return false;

  NWorld::PFWorld *pWorld = NGameX::AdventureScreen::Instance()->GetWorld();
  if ( !pWorld || !IsValid( pWorld->GetScene() ) )
    return false;

  if ( !pWorld->GetScene()->GetTerrain() )
    return false;

  RenderStatesManager &rsManager = *GetStatesManager();

  rsManager.SetState( RenderState::NoBlendNoTest() );
  rsManager.SetStateDirect(D3DRS_ZENABLE, 0);
  rsManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);
  
  SmartRenderer::BindRenderTargetColor( 0, surf );
  SmartRenderer::BindRenderTargetColor(1,  DXSurfaceRef());
  SmartRenderer::BindRenderTargetDepth( DXSurfaceRef() );
  
  // special depth texture built during scene rendering
  PF_Render::Interface *pRI = dynamic_cast<PF_Render::Interface *>(Render::Interface::Get());
  rsManager.SetSampler( 1, SamplerState::PRESET_CLAMP_MIP_BILINEAR(), pRI->GetDepthTexture() );

  CVec3 const &campos3 = pWorld->GetScene()->GetSceneConstants().campos;
  CVec4 camPos(campos3.x, campos3.y, campos3.z, 1.f);

  Terrain::GridConstants const &gc = pWorld->GetScene()->GetTerrain()->GetGridConstants();
  CVec4 mapScaleOffset = VNULL4;
  mapScaleOffset.x = 1.f / gc.worldSize.x;
  mapScaleOffset.y = -1.f / gc.worldSize.y;
  mapScaleOffset.w = 1.f;

  Renderer &renderer = *GetRenderer();
  renderer.SetPixelShaderConstantsMatrix(PSHADER_LOCALCONST0, pWorld->GetScene()->GetSceneConstants().invView);
  renderer.SetPixelShaderConstantsVector4(PSHADER_LOCALCONST4, camPos);
  renderer.SetPixelShaderConstantsVector4(PSHADER_LOCALCONST5, mapScaleOffset);
  GetImmRenderer()->RenderScreenQuad( ImmRenderer::Params("NatureMapProj",
    pWorld->GetNatureMap()->ClientObject()->GetTexture(), &SamplerState::PRESET_CLAMP_MIP_BILINEAR()) );

  return true;
}



void PostFXParamsManager::OnDBParamsChanged( const NDb::DBID& dbid )
{
  if ( IsValid(dbParams) )
  {
    for (int i = 0; i < NATURE_TYPES_COUNT; ++i)
    {
      s_pivotParams[i] = FullScreenFX::Params(&dbParams->fullScreenFXParams[i]);
    }
    NeedCalculateCoefs();

    NGlobal::VariantValue value( dbParams->mipMapLodBias );
    SetVar( "mipmaplodbias", value, STORAGE_NONE );
  }
}

void PostFXParamsManager::SyncCoeffValue()
{
  if (isCoeffChanged && g_PostFXReadEnabled && !disabled)
  {
    NDebug::PerformanceDebugVarGuard perfGuard(g_pfxGetRT, true);

    coeff = VNULL4;

    Texture2DRef const& pTexture = GetCoeff();
    DXSurfaceRef pSource = pTexture->GetSurface(0);

    if (Render::GetRenderer()->GetRenderTargetData(Get(pSource), Get(offscreenSurf->GetDXSurface())))
    {
      Render::LockedRect lock = offscreenSurf->Lock(Render::LOCK_READONLY);
      if (lock.data)
      {
        coefParser(lock.data, &coeff);
        isCoeffChanged = false;
        offscreenSurf->Unlock();
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Console commands
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{

  bool GetSetColorVectorCmd(int fieldOffset, char const* pName, vector<wstring> const& params)
  {
    if (!(params.size() == 0 || params.size() == 1 || params.size() == 2 || params.size() == 4))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "usage: [" << pName << " nature R G B]    or    [" << pName << "nature RGB]" << endl;
      return true;
    }

    int nature;

    if (params.size() == 0)
    {
      for (int nature = 0; nature < NATURE_TYPES_COUNT; ++nature)
      {
        CVec4 &vec = *(CVec4*)((char*)&s_pivotParams[nature] + fieldOffset);
        int channels[3];
        for (int i = 0; i < 3; ++i)
        {
          channels[i] = Round(vec[i] * 255.f);
        }
        systemLog( NLogg::LEVEL_MESSAGE ) << "nature " << nature << ": " << channels[0] << " " << channels[1] << " " << channels[2] << " " << endl;
      }

      return true;
    }

    nature = NStr::ToInt( params[0] );
    if (!(0 <= nature && nature < NATURE_TYPES_COUNT))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "wrong nature type" << endl;
      return true;
    }

    CVec4 &vec = *(CVec4*)((char*)&s_pivotParams[nature] + fieldOffset);

    if (params.size() == 1)
    {
      int channels[3];
      for (int i = 0; i < 3; ++i)
      {
        channels[i] = Round(vec[i] * 255.f);
      }

      systemLog( NLogg::LEVEL_MESSAGE ) << "nature " << nature << ": " << channels[0] << " " << channels[1] << " " << channels[2] << " " << endl;
      return true;
    }

    if (params.size() == 2)
    {
      vec[0] = vec[1] = vec[2] = NStr::ToInt( params[1] ) / 255.f;
      NeedCalculateCoefs();
      return true;
    }

    vec[0] = NStr::ToInt( params[1] ) / 255.f;
    vec[1] = NStr::ToInt( params[2] ) / 255.f;
    vec[2] = NStr::ToInt( params[3] ) / 255.f;
    NeedCalculateCoefs();
    return true;
  }

  bool GetSetFloatVectorCmd(int fieldOffset, char const* pName, vector<wstring> const& params)
  {
    if (!(params.size() == 0 || params.size() == 1 || params.size() == 2 || params.size() == 4))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "usage: [" << pName << " nature R G B]    or    [" << pName << "nature RGB]" << endl;
      return true;
    }

    int nature;

    if (params.size() == 0)
    {
      for (int nature = 0; nature < NATURE_TYPES_COUNT; ++nature)
      {
        CVec4 &vec = *(CVec4*)((char*)&s_pivotParams[nature] + fieldOffset);
        int channels[3];
        for (int i = 0; i < 3; ++i)
        {
          channels[i] = Round(vec[i] * 255.f);
        }
        systemLog( NLogg::LEVEL_MESSAGE ) << "nature " << nature << ": " << vec[0] << " " << vec[1] << " " << vec[2] << " " << endl;
      }

      return true;
    }

    nature = NStr::ToInt( params[0] );
    if (!(0 <= nature && nature < NATURE_TYPES_COUNT))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "wrong nature type" << endl;
      return true;
    }

    CVec4 &vec = *(CVec4*)((char*)&s_pivotParams[nature] + fieldOffset);

    if (params.size() == 1)
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "nature " << nature << ": " << vec[0] << " " << vec[1] << " " << vec[2] << " " << endl;
      return true;
    }

    if (params.size() == 2)
    {
      vec[0] = vec[1] = vec[2] = NStr::ToFloat( params[1] );
      NeedCalculateCoefs();
      return true;
    }

    vec[0] = NStr::ToFloat( params[1] );
    vec[1] = NStr::ToFloat( params[2] );
    vec[2] = NStr::ToFloat( params[3] );
    NeedCalculateCoefs();

    return true;
  }

  bool GetSetFloatCmd(int fieldOffset, char const* pName, vector<wstring> const& params)
  {
    if (!(params.size() == 0 || params.size() == 1 || params.size() == 2))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "usage: "<< pName << " nature value" << endl;
      return true;
    }

    int nature;

    if (params.size() == 0)
    {
      for (int nature = 0; nature < NATURE_TYPES_COUNT; ++nature)
      {
        float &v = *(float*)((char*)&s_pivotParams[nature] + fieldOffset);
        systemLog( NLogg::LEVEL_MESSAGE ) << "nature " << nature << ": " << v << endl;
      }

      return true;
    }

    nature = NStr::ToInt( params[0] );
    if (!(0 <= nature && nature < NATURE_TYPES_COUNT))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "wrong nature type" << endl;
      return true;
    }

    float &v = *(float*)((char*)&s_pivotParams[nature] + fieldOffset);

    if (params.size() == 1)
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << v << endl;
      return true;
    }

    v = NStr::ToFloat( params[1] );
    NeedCalculateCoefs();
    return true;
  }

  /////////////////////////////////////////////////////////////////////////////////////
#define GET_SET_CMD(cmd, type, name)                                              \
  bool GetSet##name##Cmd(char const* pName, vector<wstring> const& params)          \
  {                                                                                 \
  return GetSet##type##Cmd(offsetof(FullScreenFX::Params, name), pName, params);  \
  }                                                                                 \
  REGISTER_DEV_CMD(cmd, GetSet##name##Cmd);


  /////////////////////////////////////////////////////////////////////////////////////
  // RGB levels
  GET_SET_CMD(pfx_in_min,  ColorVector, InMin);
  GET_SET_CMD(pfx_in_max,  ColorVector, InMax);
  GET_SET_CMD(pfx_out_min, ColorVector, OutMin);
  GET_SET_CMD(pfx_out_max, ColorVector, OutMax);
  GET_SET_CMD(pfx_gamma,   FloatVector, Gamma);

  /////////////////////////////////////////////////////////////////////////////////////
  // color cast
  GET_SET_CMD(pfx_color,      ColorVector, Color);
  GET_SET_CMD(pfx_color_coef, Float,       ColorCastCoef);

  /////////////////////////////////////////////////////////////////////////////////////
  // sharp
  GET_SET_CMD(pfx_sharp_pixel_size, Float, SharpPixelSize);
  GET_SET_CMD(pfx_sharp_coef,       Float, SharpCoef);

} // ns

} // ns PF_Render

REGISTER_VAR( "pfx_read_enable", g_PostFXReadEnabled, STORAGE_USER );
