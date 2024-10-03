#include "stdafx.h"
#include "Vendor/DirectX/Include/DxErr.h"

#include "System/AssertDumper.h"
#include "System/InlineProfiler.h"
#include "System/CrashRptWrapper.h"
#include "RenderStatesManager.h"
#include "renderflagsconverter.h"
#include "RenderResourceManager.h"

#include "vertexformatdescriptor.h"
#include "texture.h"
#include "rendersurface.h"
#include "renderer.h"
#include "ImmediateRenderer.h"
#include "DxResourcesControl.h"
#include "DeviceLost.h"

#include "smartrenderer.h"
#include "ConfigManager.h"
#include "DXWarnSignal.h"

IMPLEMENT_SIMPLE_SIGNAL_ST(DXWarnSignal)

static DXWarnSignal s_DXWarnLevel;
REGISTER_VAR_INTERFACE( "DXWarnLevel", MakeSignalProxy(&s_DXWarnLevel, 0), STORAGE_NONE );

static bool s_render_threadsafe = true;
REGISTER_VAR( "render_threadsafe", s_render_threadsafe, STORAGE_NONE );

DEFINE_DEV_VAR(g_synchronizeRender, true, "synchronize_render", STORAGE_NONE);

static bool s_use_triple_buffer = false;
REGISTER_VAR("gfx_triple_buffer", s_use_triple_buffer, STORAGE_NONE);

static UINT s_adapterToUse = D3DADAPTER_DEFAULT;
REGISTER_VAR("adapter_to_use", s_adapterToUse, STORAGE_NONE);

static bool s_dump_adapters = false;
REGISTER_VAR("dump_adapters", s_dump_adapters, STORAGE_NONE);

// @BVS@CAPS DEPENDENT ACTUALLY
const int SHADER_REGISTERS_COUNT = 256;

const D3DFORMAT frontBufferFormat = D3DFMT_X8R8G8B8;

static bool forceSM20Usage = false;

#ifndef _SHIPPING
#define _NVPERFHUD_ // comment this to disable NVPerfHUD profiling //////////////////
#endif // _SHIPPING

IMPLEMENT_SIMPLE_SIGNAL_ST(NullRenderSignal)

namespace Render
{

static NullRenderSignal s_nullrender;

Renderer*  Renderer::s_pInstance = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer* Renderer::Get()
{
  return s_pInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const RenderMode& Renderer::GetCurrentRenderMode()
{
	return realRenderMode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(unsigned int _hWnd) : 
	pD3D(0), 
	pDevice(0),
	hWnd(_hWnd),
	bDeviceLost(true),
  bResetDevice(false),
  bTripleBufferUsed(false),
	isRunningUnderPerfHUD(false),
  renderSceneLocked( false )
{
  SmartRenderer::ResetTriangleAndDipCount();

	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D == 0)
	{
		//Log.Add(MAIN_LOG, "[!] ќшибка Direct3DCreate9\n"); FIXME
	}

	hWnd = _hWnd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::~Renderer()
{
  pDeviceDepthSurface = 0;
  pDeviceColorSurface = 0;
  pFrameSynchQuery = 0;

  NotifyDeviceLost();
  DeviceDeleteHandler::NotifyDeviceDelete();
  DumpDXResourcesLeaks();
  if (pDevice)
    pDevice->Release();
  pDevice = 0;

  pD3D->Release();
  pD3D = 0;

  DebugTrace("releasing renderer...\nnow we are NOT able to render  :)\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Renderer::GetModesCount() const
{
	return pD3D->GetAdapterModeCount(s_adapterToUse, frontBufferFormat);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::CorrectResolution( unsigned int &width, unsigned int &height ) const
{
  const int numModes = GetModesCount();
  float bestCoeff = FLT_MAX;
  unsigned int bestWidth = 0;
  unsigned int bestHeight = 0;

  for (int i = 0; i < numModes; i++)
  {
    unsigned int curWidth, curHeight, curRefreshRate;

    GetMode(i, curWidth, curHeight, curRefreshRate);

    if ( curWidth == width && curHeight == height )
      return; 

    float deltaWidth =  (float)curWidth - width;
    float deltaHeight = (float)curHeight - height;  

    //Ќайти разрешение больше запрошенного намного предпочтительнее чем меньше,
    //поэтому дл€ всех разрешений меньше запрошенного будет искусственно завышать 
    //коэффициент, тем самым разделив разрешени€ на два класса
    //
    //ƒл€ отрицательных разрешений искусственно добавл€ем следующую разницу 
    //в процентах
    const float additionalDeltaPercent = 0.1f;

    if( deltaWidth < 0 )  deltaWidth  -= width * additionalDeltaPercent;
    if( deltaHeight < 0 ) deltaHeight -= height * additionalDeltaPercent;

    //—реднеквадратичное отклонение текущего разрешени€ к запрошенному
    float curCoef = deltaWidth * deltaWidth + deltaHeight * deltaHeight;

    //DebugTrace( "Relation %dx%d to %dx%d is %g", width, height, curWidth, curHeight, curCoef );

    if( curCoef < bestCoeff )   
    {
      bestWidth = curWidth;
      bestHeight = curHeight;
      bestCoeff = curCoef;
    } 
  }

  NI_ASSERT( bestCoeff < FLT_MAX, "Problem with rendermodes" );

  DebugTrace("Requested resolution %d x %d not supported, change to %d x %d", width, height, bestWidth, bestHeight );

  width = bestWidth;
  height = bestHeight;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::CorrectRefreshRate( unsigned int width, unsigned int height, unsigned int &refreshRate ) const
{
  if( refreshRate == D3DPRESENT_RATE_DEFAULT )
    return;

  const int numModes = GetModesCount();
  float bestCoeff = FLT_MAX;
  unsigned int bestRefreshRate = 0;

  for (int i = 0; i < numModes; i++)
  {
    unsigned int curWidth, curHeight, curRefreshRate;

    GetMode(i, curWidth, curHeight, curRefreshRate);

    if ( curWidth != width || curHeight != height )
      continue;

    if( curRefreshRate == refreshRate )
      return;

    const float delta = (float)curRefreshRate - refreshRate;
    const float curCoef = delta * delta;

    if( curCoef < bestCoeff )   
    {
      bestRefreshRate = curRefreshRate;
      bestCoeff = curCoef;
    }
  }

  NI_ASSERT( bestCoeff < FLT_MAX, "Problem with rendermodes" );

  DebugTrace("Requested refresh rate %d not supported, change to %d ", refreshRate, bestRefreshRate );

  refreshRate = bestRefreshRate;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Renderer::GetMode(int index, unsigned int &width, unsigned int &height, unsigned int &refreshRate) const
{
  width = RenderMode::WIDTH_DEFAULT;
	height = RenderMode::HEIGHT_DEFAULT;
	refreshRate = RenderMode::REFRESH_RATE_DEFAULT;

	D3DDISPLAYMODE mode;
	HRESULT hr = pD3D->EnumAdapterModes(s_adapterToUse, frontBufferFormat, index, &mode);
	NI_VERIFY(hr == D3D_OK, NStr::StrFmt("Adapter mode enumeration problem for index %d (max:%d)", index, GetModesCount()), return; );
	width = mode.Width;
	height = mode.Height;
	refreshRate = mode.RefreshRate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::UpdateRealRenderMode( const RenderMode &configRenderMode )
{
  realRenderMode = configRenderMode;
  
  D3DDISPLAYMODE mode = {};
  pDevice->GetDisplayMode( 0, &mode );
  
  //¬ оконном режиме режиме mode.Width и mode.Height содержат разрешение 
  //рабочего стола, поэтому воспользуемс€ данными presentParams
  realRenderMode.width = presentParams.BackBufferWidth;
  realRenderMode.height = presentParams.BackBufferHeight;
  
  //≈сли в настройках refreshRate равен 0, то так мы точно получаем насто€щее значение
  realRenderMode.refreshRate = mode.RefreshRate; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Renderer::NeedToFilterResolutionFromUser( unsigned int width, unsigned int height ) const
{
  //http://msdn.microsoft.com/en-us/library/ee417691.aspx#_1.5
  if( width < 1024 || height < 768 )
    return true;
    
  //The desktop aspect ratio must be used as a search criterion if the game 
  //chooses a different default resolution.
  const float curAspectRatio = float(width) / height;
  unsigned int deskWidth, deskHeight;
  
  GetDesktopResolution( deskWidth, deskHeight );
  
  const float desktopAspectRatio = float(deskWidth) / deskHeight;
  
  //Ѕудем считать, что разрешение можно показывать пользователю если 
  //его соотношение сторон отличаетс€ от соотношени€ сторон рабочего стола 
  //менее чем на aspectRatioThreshold процентов
  const float aspectRatioThreshold = 0.1f;
  
  const float ratio = (curAspectRatio - desktopAspectRatio) / desktopAspectRatio;
  
  return ratio * ratio > aspectRatioThreshold * aspectRatioThreshold;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Renderer::OnDeviceChanged()
{
  DebugTrace("OnDeviceChanged");
  
  FillCaps();

  // Save links to surfaces
  IDirect3DSurface9 *pSurf;
  pDevice->GetDepthStencilSurface(&pSurf);
  pDeviceDepthSurface.Attach(pSurf);
  pDevice->GetRenderTarget(0, &pSurf);
  pDeviceColorSurface.Attach(pSurf);

  IDirect3DQuery9* pQuery;
  pDevice->CreateQuery(D3DQUERYTYPE_EVENT, &pQuery);
  pFrameSynchQuery = DXQueryRef(pQuery, false);

  
  //systemLog(NLogg::LEVEL_MESSAGE) << "Renderer: render mode is " << presentParams.BackBufferWidth << " x " << presentParams.BackBufferHeight << " @ " 
    //<< (presentParams.PresentationInterval == D3DPRESENT_INTERVAL_IMMEDIATE ? "NOSYNC" : "VSYNC") << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Renderer::CreateDevice(D3DPRESENT_PARAMETERS& pp)
{
  pDeviceDepthSurface = 0;
  pDeviceColorSurface = 0;
  pFrameSynchQuery = 0;

  if(RENDER_DISABLED) {
    bDeviceLost = true;
    return false;
  }
  // Defaults
  //UINT AdapterToUse = s_adapterToUse;
  D3DDEVTYPE DeviceType = s_nullrender ? D3DDEVTYPE_NULLREF : D3DDEVTYPE_HAL;

  // Look for 'NVIDIA PerfHUD' adapter
#ifdef _NVPERFHUD_
  for (UINT Adapter = 0; Adapter < pD3D->GetAdapterCount(); Adapter++)
  {
    D3DADAPTER_IDENTIFIER9 Identifier;
    HRESULT Res;
    Res = pD3D->GetAdapterIdentifier(Adapter, 0, &Identifier);

    if (strstr(Identifier.Description, "PerfHUD") != 0)
    {
      NI_ASSERT( !s_nullrender, "NullRender is activated under PerfHUD" );

      s_adapterToUse = Adapter;
      DeviceType = D3DDEVTYPE_REF;
			isRunningUnderPerfHUD = true;
      systemLog(NLogg::LEVEL_MESSAGE) << "Renderer: Attaching to adapter #" << Adapter << " (" << Identifier.Description << ")" << endl;
      break;
    }
  }

#endif // _NVPERFHUD_
  if(s_dump_adapters) {
    for (UINT Adapter = 0; Adapter < pD3D->GetAdapterCount(); Adapter++)
    {
      D3DADAPTER_IDENTIFIER9 Identifier;
      HRESULT Res;
      Res = pD3D->GetAdapterIdentifier(Adapter, 0, &Identifier);

      systemLog(NLogg::LEVEL_MESSAGE) << "Renderer: adapter #" << Adapter << " (" << Identifier.Description << ")" << endl;
    }

    D3DADAPTER_IDENTIFIER9 Identifier;
    HRESULT Res;
    Res = pD3D->GetAdapterIdentifier(s_adapterToUse, 0, &Identifier);
    systemLog(NLogg::LEVEL_MESSAGE) << "Renderer: adapter #" << s_adapterToUse << " (" << Identifier.Description << ") choosed" << endl;
  }
  DWORD dwCreateFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING/* | D3DCREATE_PUREDEVICE*/;
  if ( s_render_threadsafe )
    dwCreateFlags |= D3DCREATE_MULTITHREADED;

#ifndef NI_DISABLE_CRASHRPT
  //Report display adapter information
  D3DADAPTER_IDENTIFIER9 adapId;
  if ( SUCCEEDED( pD3D->GetAdapterIdentifier( s_adapterToUse, 0, &adapId ) ) )
  {
    UINT availableVidMem, adapterRAM;
    GetConfigManager()->GetVidMem(pD3D->GetAdapterMonitor(s_adapterToUse), &availableVidMem, &adapterRAM);

    CrashRptWrapper::AddTagToReport( "DisplayDeviceName",    adapId.DeviceName );
    CrashRptWrapper::AddTagToReport( "InstalledVideoMemory", NStr::StrFmt("%u/%u MB", availableVidMem, adapterRAM) );
    CrashRptWrapper::AddTagToReport( "DisplayDriver",        adapId.Driver );
    CrashRptWrapper::AddTagToReport( "DisplayDescription",   adapId.Description );
    CrashRptWrapper::AddTagToReport( "DisplayDriverVersion", NStr::StrFmt( "%u.%u.%u.%u",
      (unsigned)HIWORD( adapId.DriverVersion.HighPart ), (unsigned)LOWORD( adapId.DriverVersion.HighPart ),
      (unsigned)HIWORD( adapId.DriverVersion.LowPart ), (unsigned)LOWORD( adapId.DriverVersion.LowPart ) ) );
  }
#endif

  // Before creating device, test if we support given resolution and bit depth
  if(pp.Windowed == FALSE)
  {
    DWORD mode = 0, maxw = 0, maxh = 0;
    DEVMODE devmode;

    while(true)
    {
      if(EnumDisplaySettings(NULL, mode++, &devmode) == FALSE)
      {
        systemLog(NLogg::LEVEL_MESSAGE) << " Res-check indicates that requested resolution isn't supported:" << endl;
        systemLog(NLogg::LEVEL_MESSAGE) << pp.BackBufferWidth << "x" << pp.BackBufferHeight << "x32" << endl;      
        
        // Clamp if over size limit
        if(pp.BackBufferWidth > maxw || pp.BackBufferHeight > maxh)
        {
          systemLog(NLogg::LEVEL_MESSAGE) << "Clamped to: " << maxw << "x" << maxh << "x32" << endl; 

          pp.BackBufferWidth = pp.BackBufferWidth > maxw ? maxw : pp.BackBufferWidth;
          pp.BackBufferHeight = pp.BackBufferHeight > maxh ? maxh : pp.BackBufferHeight;
        }

        break;
      }
      
      maxw = devmode.dmPelsWidth > maxw ? devmode.dmPelsWidth : maxw;
      maxh = devmode.dmPelsHeight > maxh ? devmode.dmPelsHeight : maxh;

      if(devmode.dmBitsPerPel == 32 && devmode.dmPelsWidth == pp.BackBufferWidth && devmode.dmPelsHeight == pp.BackBufferHeight)
      {
        break;
      }
    }
  }

  // Try to create chosen device
  HRESULT hr = pD3D->CreateDevice(s_adapterToUse, DeviceType, (HWND)hWnd, dwCreateFlags,	&pp, &pDevice);
  bDeviceLost = (D3D_OK != hr);

  // Notify about failure
  if( FAILED(hr) ) {
    // Some of presentpapams could be rejected(e.g., triple buffer) and changed by CreateDevice. Retry.
    hr = pD3D->CreateDevice(s_adapterToUse, DeviceType, (HWND)hWnd, dwCreateFlags,	&pp, &pDevice);
    bDeviceLost = (D3D_OK != hr);

    if( FAILED(hr) ) {
      systemLog(NLogg::LEVEL_CRITICAL) << "Renderer: CreateDevice() failed, hr = " << NStr::StrFmt("0x%08X (%s)", hr, DXGetErrorStringA(hr)) << endl;
      systemLog(NLogg::LEVEL_MESSAGE) << " pp.BackBufferHeight: " << pp.BackBufferHeight << endl;
      systemLog(NLogg::LEVEL_MESSAGE) << " pp.BackBufferWidth: " << pp.BackBufferWidth << endl;
      systemLog(NLogg::LEVEL_MESSAGE) << " pp.FullScreen_RefreshRateInHz: " << pp.FullScreen_RefreshRateInHz << endl;
      systemLog(NLogg::LEVEL_MESSAGE) << " pp.hDeviceWindow: " << pp.hDeviceWindow << endl;
      systemLog(NLogg::LEVEL_MESSAGE) << " pp.Flags: " << pp.Flags << endl;
      systemLog(NLogg::LEVEL_MESSAGE) << " pp.Windowed: " << pp.Windowed << endl;
      return false;
    }
  }

  GetConfigManager()->CheckDeviceCaps(pDevice);
#ifndef NI_DISABLE_CRASHRPT
  CrashRptWrapper::AddTagToReport( "DXcapsOEM",  NStr::StrFmt("%#X", GetConfigManager()->GetAllFeatures()) );
  CrashRptWrapper::AddTagToReport( "DXcapsOEM_version",  NStr::StrFmt("%d", IConfigManager::featuresVersion) );
#endif // NI_DISABLE_CRASHRPT
  //systemLog(NLogg::LEVEL_MESSAGE) << "Renderer: CreateDevice() successful." << endl;
  presentParams = pp;
  OnDeviceChanged();
  
  DeviceDeleteHandler::NotifyDeviceCreate();
  
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Renderer::ResetDevice(D3DPRESENT_PARAMETERS& pp)
{
  DebugTrace("Try to reset");

  pDeviceDepthSurface = 0;
  pDeviceColorSurface = 0;
  pFrameSynchQuery = 0;

  // Try to create chosen device
  DebugTrace("Before device reset");
  HRESULT hr = pDevice->Reset(&pp);
  DebugTrace("After device reset");
  
  // Notify about failure
  if (FAILED(hr))
  {
    systemLog(NLogg::LEVEL_CRITICAL) << "Renderer: ResetDevice() failed, hr = " << NStr::StrFmt("0x%08X (%s)", hr, DXGetErrorStringA(hr)) << endl;
    return false;
  }

  //systemLog(NLogg::LEVEL_MESSAGE) << "Renderer: ResetDevice() successful." << endl;
  presentParams = pp;
  OnDeviceChanged();
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Renderer::Start(const RenderMode& _renderMode)
{
  // prepare mode parameters
  D3DPRESENT_PARAMETERS pp; 
  Convert(_renderMode, pp);
  
  // create or reset device
  bool ok = (pDevice == 0) ? CreateDevice(pp) : ResetDevice(pp);
  if (!ok)
    return false;

	NLogg::CAssertDumper::EnableAssertMessageBox(!_renderMode.isFullScreen && !isRunningUnderPerfHUD);
	UpdateRealRenderMode(_renderMode);

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Stop()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::FillCaps()
{
	D3DCAPS9 d3dCaps;
	if ( FAILED(GetDevice()->GetDeviceCaps(&d3dCaps)) )
	{
		caps.pixelShaderVersion = 0.0f;
		caps.vertexShaderVersion = 0.0f;
	}

	// 
	if (!forceSM20Usage)
	{
		caps.vertexShaderVersion = float((d3dCaps.VertexShaderVersion >> 8) & 0xFF) + 
			                         float(d3dCaps.VertexShaderVersion & 0xFF) * 0.1f;
		caps.pixelShaderVersion = float((d3dCaps.PixelShaderVersion >> 8) & 0xFF) + 
			                        float(d3dCaps.PixelShaderVersion & 0xFF) * 0.1f;
	}
	else
	{
		caps.vertexShaderVersion = 2.0f;
		caps.pixelShaderVersion = 2.0f;
	}

	caps.bSupportSM30 = caps.pixelShaderVersion >= 3.0f && caps.vertexShaderVersion >= 3.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DXVertexDeclarationRef Renderer::CreateVertexFormatDeclaration(const VertexFormatDescriptor& descr)
{
  unsigned int elements_count = descr.GetVertexElementsCount();
  NI_ASSERT(elements_count > 0, "Invalid vertex format!");

  nstl::vector<D3DVERTEXELEMENT9> elements;
  elements.reserve(elements_count);

  for (unsigned int i = 0; i < elements_count; i++)
  {
    const VertexElementDescriptor& element = descr.GetVertexElement(i);

    D3DVERTEXELEMENT9 d3d_element;
    d3d_element.Stream		 = static_cast<unsigned short>(element.stream);
    d3d_element.Offset		 = static_cast<unsigned short>(element.offset);
    d3d_element.Type			 = ConvertVertexElementType(element.type);
    d3d_element.Method		 = D3DDECLMETHOD_DEFAULT;
    d3d_element.Usage			= ConvertVertexElementUsage(element.usage);
    d3d_element.UsageIndex = static_cast<unsigned char>(element.usageIndex);

    elements.push_back(d3d_element);
  }
  D3DVERTEXELEMENT9 d3d_decl_end = D3DDECL_END();
  elements.push_back(d3d_decl_end);

  IDirect3DVertexDeclaration9* decl_d3d = 0;

  if(!RENDER_DISABLED) {
    HRESULT hr = GetDevice()->CreateVertexDeclaration(&elements[0], &decl_d3d);
    NI_DX_THROW( hr, "CreateVertexFormatDeclaration" );
  }

  return DXVertexDeclarationRef(decl_d3d, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DXVertexShaderRef Renderer::CreateVertexShader(unsigned char const* data)
{
	IDirect3DVertexShader9* d3dshader = 0;
	HRESULT hr = GetDevice()->CreateVertexShader( reinterpret_cast<DWORD const*>(data), &d3dshader );
	NI_DX_THROW(hr, "Creating vertex shader error!");
	return DXVertexShaderRef(d3dshader, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DXPixelShaderRef Renderer::CreatePixelShader(unsigned char const* data)
{
	IDirect3DPixelShader9* d3dshader = 0;
	HRESULT hr = GetDevice()->CreatePixelShader( reinterpret_cast<DWORD const*>(data), &d3dshader );
	NI_DX_THROW(hr, "Creating vertex shader error!");
	return DXPixelShaderRef(d3dshader, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::SetClipPlane(bool bEnable, CVec4 *pPlane)
{
	if (bEnable)
  {
		GetDevice()->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);
	  GetDevice()->SetClipPlane(0, (float*)pPlane);
	}
	else
	{
		GetDevice()->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::SetPixelShaderConstants(unsigned int startRegisterIndex, unsigned int registersCount, const void* data)
{
	NI_VERIFY(startRegisterIndex < SHADER_REGISTERS_COUNT, "Invalid register index!", return; );
	NI_VERIFY(SHADER_REGISTERS_COUNT - startRegisterIndex >= registersCount, "Invalid registers count!", return; );

#ifdef _DEBUG
	constChecker.SetPixelShaderConstants(startRegisterIndex, registersCount);
#endif

#ifdef FORCE_SM20			
  startRegisterIndex = min(startRegisterIndex, 31);
#endif
  bool res = GetDevice()->SetPixelShaderConstantF(startRegisterIndex, (const float*)(data), registersCount) == D3D_OK;

	NI_ASSERT(res, "SetPixelShaderConstants error!");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::SetVertexShaderConstants(unsigned int startRegisterIndex, unsigned int registersCount, const void* data)
{
	NI_VERIFY(startRegisterIndex < SHADER_REGISTERS_COUNT, "Invalid register index!", return; );
	NI_VERIFY(SHADER_REGISTERS_COUNT - startRegisterIndex >= registersCount, "Invalid registers count!", return; )

#ifdef _DEBUG
		constChecker.SetVertexShaderConstants(startRegisterIndex, registersCount);
#endif

	bool res = GetDevice()->SetVertexShaderConstantF(startRegisterIndex, reinterpret_cast<CONST float*>(data), registersCount) == D3D_OK;

	NI_ASSERT(res, "SetPixelShaderConstants error!");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::BeginScene()
{
  if ( s_render_threadsafe )
  {
    renderSceneLock.Lock();
    renderSceneLocked = true;
  }

	HRESULT hr = GetDevice()->BeginScene();
  NI_DX_WARN(hr, "BeginScene");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::EndScene()
{
  HRESULT hr = GetDevice()->EndScene();

  if ( renderSceneLocked )
  {
    renderSceneLocked = false;
    renderSceneLock.Unlock();
  }
  NI_DX_WARN(hr, "EndScene");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Present()
{
  Present((HWND)hWnd, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::Synchronize()
{
  NI_PROFILE_FUNCTION

  HRESULT issueResult = pFrameSynchQuery->Issue(D3DISSUE_END);
  RenderResourceManager::FrameTick();

  if ( issueResult != D3DERR_DEVICELOST )
  {
    HRESULT queryResult = pFrameSynchQuery->GetData( NULL, 0, D3DGETDATA_FLUSH );

    if ( queryResult == S_FALSE )
    {
      for(int i = 1000; --i > 0;)
      {
        queryResult = pFrameSynchQuery->GetData( NULL, 0, D3DGETDATA_FLUSH);
        
        if(queryResult != S_FALSE) {
          if( FAILED(queryResult) ) {
            //recreate query
            IDirect3DQuery9* pQuery;
            pDevice->CreateQuery(D3DQUERYTYPE_EVENT, &pQuery);
            pFrameSynchQuery.Attach(pQuery);
          }
          break;
        }

        // «десь можно что-нибудь сделать

        Sleep(1);
      }

      bResetDevice = (queryResult == S_FALSE);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::ClearDeviceResources()
{
  HRESULT hr = S_OK;
  hr = pDevice->SetVertexDeclaration(0);
  hr = pDevice->SetVertexShader(0);
  hr = pDevice->SetPixelShader(0);

  static const int MAX_SAMPLERS_NUMBER = 16; // for ps.3.0
  for(int i = 0; i < MAX_SAMPLERS_NUMBER; ++i)
    hr = pDevice->SetTexture(i, 0);

  D3DCAPS9 caps;
  if( SUCCEEDED( pDevice->GetDeviceCaps(&caps)) )
  {
    for(DWORD n = 0; n < caps.NumSimultaneousRTs; ++n)
      hr = pDevice->SetRenderTarget(n, 0);

    for(DWORD n = 0; n < caps.MaxStreams; ++n)
      hr = pDevice->SetStreamSource(n, 0, 0, 4);
  }
  
  pDeviceDepthSurface = 0;
  pDeviceColorSurface = 0;
  pFrameSynchQuery = 0;
  
  //SmartRenderer::NullThePointers();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Present( HWND hWnd_, const Rect* sourceRect_, const Rect* destRect_ )
{
  NI_PROFILE_FUNCTION

  {
    NI_PROFILE_BLOCK( "Present prepare" )

    SmartRenderer::ResetTriangleAndDipCount();

    if (sourceRect_)
      sourceRect = *sourceRect_;
  }

  if(!bTripleBufferUsed && pFrameSynchQuery && g_synchronizeRender )
    Synchronize();
  else
    RenderResourceManager::FrameTick();

  HRESULT hr = 0;

  {
    NI_PROFILE_BLOCK( "Present itself" )

    //HRESULT hr = GetDevice()->Present((const RECT*)sourceRect_, NULL, hWnd_, NULL);
    hr = GetDevice()->Present((const RECT*)sourceRect_, (const RECT*)destRect_, hWnd_, NULL);
    
    NI_DX_WARN( hr == D3D_OK || hr == D3DERR_DEVICELOST, "" );
  }

  if(hr == D3DERR_DEVICELOST || bResetDevice) {
    RecoverFromDeviceLost(presentParams);
    bResetDevice = false;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::InvalidateResources()
{
  ClearDeviceResources();
  NotifyDeviceLost();
  bDeviceLost = true;
  pDevice->EvictManagedResources();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
void Renderer::RecoverFromDeviceLost( D3DPRESENT_PARAMETERS& pp )
{
  NI_PROFILE_BLOCK( "Device lost" )

    // report failure
    if (!bDeviceLost)
    {
      bDeviceLost = true;
      NotifyDeviceLost();
    }

    const HRESULT coopLevel = pDevice->TestCooperativeLevel();
    // try to revive the device
    if (coopLevel == D3DERR_DEVICENOTRESET || coopLevel == D3D_OK )
    {
      DebugTrace("Device lost!");
      ClearDeviceResources();
      NotifyDeviceLost();
      DumpDXResourcesInDefaultPool();

      for( int n = 30; bDeviceLost; --n )       
        if( ResetDevice(pp) )
          bDeviceLost = false;   
        else
          NotifyDeviceLost();     

      if(bDeviceLost) 
      {
        NI_ALWAYS_ASSERT("Reset() failed on lost device! Exiting app.");
        exit(D3DERR_DEVICENOTRESET);
      }
      
      NotifyDeviceReset();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::ClearDepthStencil()
{
  HRESULT hr = GetDevice()->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1.0f, 0);
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "ClearDepthStencil");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Clear( Color color )
{
  HRESULT hr = GetDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, color.Dummy, 1.0f, 0);
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "Clear");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::ClearColorOnly( Color color )
{
	HRESULT hr = GetDevice()->Clear(0, 0, D3DCLEAR_TARGET, color.Dummy, 1.0f, 0);
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "ClearColorOnly");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Renderer::GetRenderTargetData(IDirect3DSurface9* pSrc, IDirect3DSurface9* pDst) 
{
	HRESULT hr = GetDevice()->GetRenderTargetData(pSrc, pDst);
  NI_DX_THROW(hr, __FUNCTION__);

	return (hr == D3D_OK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::StretchSurface(const DXSurfaceRef &pSrc, const DXSurfaceRef &pDst, bool bLinear)
{
  HRESULT hr = GetDevice()->StretchRect(::Get(pSrc), 0, ::Get(pDst), 0, bLinear ? D3DTEXF_LINEAR : D3DTEXF_POINT);
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "StretchSurface");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Convert( const RenderMode &_renderMode, D3DPRESENT_PARAMETERS &pp )
{
  ZeroMemory(&pp, sizeof(pp));
  pp.BackBufferWidth = _renderMode.width;
  pp.BackBufferHeight = _renderMode.height;
  pp.Windowed = 1;
  pp.FullScreen_RefreshRateInHz = _renderMode.refreshRate;
  pp.EnableAutoDepthStencil = true;
  pp.AutoDepthStencilFormat = D3DFMT_D24S8;
  pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  pp.BackBufferFormat = D3DFMT_A8R8G8B8;
  pp.hDeviceWindow = (HWND)hWnd;

	pp.BackBufferCount = 1;

  bTripleBufferUsed = s_use_triple_buffer && _renderMode.vsyncCount;
  if(bTripleBufferUsed)
    pp.BackBufferCount = 2;

  switch (_renderMode.vsyncCount)
  {                                   
    case 0: pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; break;
    case 1: pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; break;
    case 2: pp.PresentationInterval = D3DPRESENT_INTERVAL_TWO; break;
    case 3: pp.PresentationInterval = D3DPRESENT_INTERVAL_THREE; break;
    case 4: pp.PresentationInterval = D3DPRESENT_INTERVAL_FOUR; break;
    default: pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; break;
  }
  //pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
  //if( !pp.Windowed )
  //{
  //  CorrectResolution( pp.BackBufferWidth, pp.BackBufferHeight );
  //  CorrectRefreshRate( pp.BackBufferWidth, pp.BackBufferHeight, pp.FullScreen_RefreshRateInHz );
  //}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::CorrectRenderMode( RenderMode &_renderMode ) const
{
  if( _renderMode.isFullScreen )
  {
    //CorrectResolution( _renderMode.width, _renderMode.height );
    //CorrectRefreshRate( _renderMode.width, _renderMode.height, _renderMode.refreshRate );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::ApplyNewParams( const RenderMode &_renderMode )
{ 
  D3DPRESENT_PARAMETERS pp;
  Convert(_renderMode, pp);
  
  RecoverFromDeviceLost(pp);
  DebugTrace( "RecoverFromDeviceLost finished" ); 
  UpdateRealRenderMode(_renderMode);
}

} // namespace Render

REGISTER_DEV_VAR( "forceSM20Usage", forceSM20Usage, STORAGE_GLOBAL );
