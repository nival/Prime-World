#include "StdAfx.h"
#include "ConfigManager.h"
#include "ConfigDatabase.h"


static bool s_readableDepth = true;
static bool s_stencilEnable = true;


HRESULT GetVideoMemoryViaDirectDraw(HMONITOR hMonitor, DWORD* pdwAvailableVidMem); // returns total video memory minus driver-reserved memory.
HRESULT GetVideoMemoryViaWMI(HMONITOR hMonitor, DWORD* pdwAdapterRam);


namespace Render
{

class ConfigManagerImpl : public ConfigManager, public IConfigManager
{
public:
  ConfigManagerImpl(void);
  ~ConfigManagerImpl(void) {}

  HRESULT CheckDeviceCaps(IDirect3DDevice9* _pDevice, bool _checkFormats/* = true*/);
  void    CheckFormats(IDirect3D9* _pD3D, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat);

  // SetPerfomanceLevel - level 0 is of most quality
  void SetPerfomanceLevel(ResourceType _type, UINT _level);
  // Get adapter video memory in MB; _pAvailableVidMem shows total video memory minus driver-reserved memory
  virtual void GetVidMem(HMONITOR _hMonitor, UINT* _pAvailableVidMem, UINT* _pAdapterRAM);

  const IConfigManager::SysInfo& GetSysInfo() const { return sysInfo; }
  UINT GetPerfomanceLevel(ResourceType _type) const { return perfLevels[_type]; }
  UINT FindAcceptableTechnique(const TechniqueDesc **_pDesc, UINT numDesc) const;
  bool StencilSupported(ERenderFormat _depthFormat) const;
  ERenderFormat GetDepthFormatPreffered() const;
  bool CheckFeatureSupport(DWORD _features) const;
  bool CheckFeatureSupportExact(DWORD _features) const;
  DWORD      GetAllFeatures() const { return caps; }
  bool ReadableDepthEnabled() const { return s_readableDepth && !Compatibility::IsRunnedUnderWine() && ReadableDepthSupported(); }
  const ConfigParams& GetConfigParams() const { return config_params; }

  bool ReadableDepthSupported() const;

protected:
  DWORD caps;
  UINT perfLevels[NUM_RESOURCE_TYPES];
  vector<D3DFORMAT>  r2vbFormats;
  vector<StringPair> config_params;
  IConfigManager::SysInfo sysInfo;
};

static inline bool AllowDF24(DWORD _caps)
{ // Allow only for Radeon X1000 family
  return false;
  //return (_caps & IConfigManager::hasDF24) && !(_caps & IConfigManager::hasVT16) && !(_caps & IConfigManager::hasVT32);
}

ConfigManagerImpl::ConfigManagerImpl() : caps()
{
  ZeroMemory( perfLevels, sizeof(perfLevels) );
}


inline void SetFlag(DWORD _flag, bool _val, DWORD *_pDest)
{
  NI_STATIC_ASSERT((0 == int(false)) && (1 == int(true)), WRONG_ASSUMPTION_ABOUT_BOOL_REPRESENTATION);

  *_pDest = (~_flag & *_pDest) | (-int(_val) & _flag);
}


static const D3DFORMAT g_R2VBFormats[] = {
   D3DFMT_A32B32G32R32F,
   D3DFMT_G32R32F,
   D3DFMT_A16B16G16R16F,
   D3DFMT_A16B16G16R16,
   D3DFMT_Q16W16V16U16,
   D3DFMT_R32F,
   D3DFMT_G16R16F,
   D3DFMT_G16R16,
   D3DFMT_V16U16,
   D3DFMT_A2W10V10U10,
   D3DFMT_A2R10G10B10,
   D3DFMT_Q8W8V8U8,
   D3DFMT_A8R8G8B8,
};

HRESULT ConfigManagerImpl::CheckDeviceCaps(IDirect3DDevice9* _pDevice, bool _checkFormats)
{
  ASSERT(_pDevice);

  HRESULT hr = E_FAIL;

  D3DCAPS9 caps9;
  _pDevice->GetDeviceCaps(&caps9);
  sysInfo.MaxVertexShaderConst = caps9.MaxVertexShaderConst;

  D3DADAPTER_IDENTIFIER9 adapterID;
  IntrusivePtr<IDirect3D9> pD3D;

  {
    IDirect3D9 *p;
    hr = _pDevice->GetDirect3D( &p );
    NI_DX_THROW(hr, "Corrupted D3D device");
    pD3D.Attach(p);
  }   
  
  hr = pD3D->GetAdapterIdentifier(caps9.AdapterOrdinal, 0, &adapterID);

  sysInfo.IsNullRef = (D3DDEVTYPE_NULLREF == caps9.DeviceType);
  //if(D3DDEVTYPE_REF == caps9.DeviceType) // Probably this mean it is NULLREF actually. OR this mean we are under PerfHUD.
  //  sysInfo.IsNullRef = !strstr(adapterID.Description, "PerfHUD");

  if(D3DDEVTYPE_REF == caps9.DeviceType)  // Probably this mean it is NULLREF actually.
    sysInfo.IsNullRef = NGlobal::GetVar("nullrender").GetInt64();

  if( _checkFormats ) {
    D3DDISPLAYMODE displayMode;
    pD3D->GetAdapterDisplayMode(caps9.AdapterOrdinal, &displayMode);

    CheckFormats(::Get(pD3D), caps9.AdapterOrdinal, caps9.DeviceType, displayMode.Format);
  }

  if( hasR2VB & caps )
  {
    IDirect3DTexture9* pRT = 0;
    const DWORD usage = D3DUSAGE_RENDERTARGET | D3DUSAGE_DMAP;
    for(int i = 0; i < ARRAY_SIZE(g_R2VBFormats); ++i)
      if( SUCCEEDED(_pDevice->CreateTexture(1, 1, 1, usage, g_R2VBFormats[i], D3DPOOL_DEFAULT, &pRT, 0)) )
      {
        r2vbFormats.push_back(g_R2VBFormats[i]);
        pRT->Release();
        hr = S_OK;
      }
  }
  
  if( IConfigDatabase* const pCDB = IConfigDatabase::Create() )
  {
    SOUND_DEVICE sndDev;
    if( pCDB->Load("config.txt", sndDev, adapterID, caps9, 1024, 64, 1700) )
        config_params = pCDB->GetAggregateProperties();
    pCDB->Release();

    for(int i = config_params.size(); --i >= 0;) {
      const StringPair& curProperty = config_params[i];
      if( NGlobal::IsCommandRegistred(curProperty.first) )
        if( curProperty.second.empty() )
          NGlobal::RunCommand( NStr::ToUnicode(curProperty.first) );
        else
          NGlobal::RunCommand( NStr::ToUnicode(curProperty.first) + wstring(L" ")
                              + NStr::ToUnicode(curProperty.second) );
    }
  }

  return hr;
}


void ConfigManagerImpl::CheckFormats(IDirect3D9* _pD3D, UINT _Adapter, D3DDEVTYPE _DeviceType, D3DFORMAT _AdapterFormat)
{
  ASSERT(_pD3D);

#define CHECK_SUPPORT(usage, type, fmt) (D3D_OK == _pD3D->CheckDeviceFormat(_Adapter, _DeviceType, _AdapterFormat, usage, type, fmt))

  SetFlag(hasDF16, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, FOURCC_DF16), &caps);
  SetFlag(hasDF24, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, FOURCC_DF24), &caps);
  SetFlag(hasRAWZ, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, FOURCC_RAWZ), &caps);
  SetFlag(hasINTZ, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, FOURCC_INTZ), &caps);
  SetFlag(hasRESZ, CHECK_SUPPORT(D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, FOURCC_RESZ), &caps);
  SetFlag(hasR2VB, CHECK_SUPPORT(                    0, D3DRTYPE_SURFACE, FOURCC_R2VB), &caps);
  SetFlag(hasNLRT, CHECK_SUPPORT(D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, FOURCC_NULL), &caps);
  SetFlag(hasD16T, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, D3DFMT_D16),  &caps);
  SetFlag(hasD24X, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, D3DFMT_D24X8), &caps);
  SetFlag(hasD24S, CHECK_SUPPORT(D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE, D3DFMT_D24S8), &caps);
  SetFlag(hasVT16, CHECK_SUPPORT(D3DUSAGE_QUERY_VERTEXTEXTURE, D3DRTYPE_TEXTURE, D3DFMT_A16B16G16R16F), &caps);
  SetFlag(hasVT32, CHECK_SUPPORT(D3DUSAGE_QUERY_VERTEXTEXTURE, D3DRTYPE_TEXTURE, D3DFMT_A32B32G32R32F), &caps);

#undef CHECK_SUPPORT
}


void ConfigManagerImpl::SetPerfomanceLevel(ResourceType _type, UINT _level)
{
  perfLevels[_type] = _level;
}


void ConfigManagerImpl::GetVidMem(HMONITOR _hMonitor, UINT* _pAvailableVidMem, UINT* _pAdapterRAM)
{
  DWORD dwAvailableVidMem;
  HRESULT hr = GetVideoMemoryViaDirectDraw( _hMonitor, &dwAvailableVidMem );
  *_pAvailableVidMem = SUCCEEDED(hr) ? dwAvailableVidMem / 1024 / 1024 : 0;

  DWORD dwAdapterRAM;
  hr = GetVideoMemoryViaWMI( _hMonitor, &dwAdapterRAM );
  *_pAdapterRAM = SUCCEEDED(hr) ? dwAdapterRAM / 1024 / 1024 : 0;
}


UINT ConfigManagerImpl::FindAcceptableTechnique(const TechniqueDesc **_pDesc, UINT numDesc) const
{
  ASSERT(numDesc > 0);
  UINT n = 0;
  do {
    const TechniqueDesc &desc = *(_pDesc[n]);
    if( desc.flags != (desc.flags & caps) )
      continue;
    if( (desc.flags & hasR2VB) &&
        (std::find(r2vbFormats.begin(), r2vbFormats.end(), desc.r2vbFormat) == r2vbFormats.end()) )
      continue;
    break;
  } while(++n < numDesc);
  return n;
}


bool ConfigManagerImpl::CheckFeatureSupport(DWORD _features) const
{
  return _features & caps;
}


bool ConfigManagerImpl::CheckFeatureSupportExact(DWORD _features) const
{
  return _features == (_features & caps);
}


bool ConfigManagerImpl::ReadableDepthSupported() const
{
  return caps & (/*hasDF16 |*/ hasRAWZ|hasINTZ) || AllowDF24(caps)
         || (caps & hasRESZ) && NGlobal::GetVar("enableRESZ").GetInt64();
}


bool ConfigManagerImpl::StencilSupported(ERenderFormat _depthFormat) const
{
  return s_stencilEnable &&(FORMAT_DF24 != _depthFormat) && (FORMAT_DF16 != _depthFormat);
}


ERenderFormat ConfigManagerImpl::GetDepthFormatPreffered() const
{
  if( caps & hasINTZ ) {
    DebugTrace("DepthFormat: INTZ");
    return FORMAT_INTZ;
  } else if( caps & hasRAWZ ) {
    DebugTrace("DepthFormat: RAWZ");
    return FORMAT_RAWZ;
  } else if( AllowDF24(caps) ) {
    DebugTrace("DepthFormat: DF16");
    return FORMAT_DF16;
  }
  //else if( caps & hasDF16 )
  //  return FOURCC_DF16;

  return FORMAT_D24S8;
}

///////////////////////////////////////////////////////////////////////////////


ConfigManager* GetConfigManager()
{
  static ConfigManagerImpl manager;
  return &manager;
}

const IConfigManager* GetIConfigManager()
{
  return static_cast<ConfigManagerImpl*>( GetConfigManager() );
}

}; // namespace Render


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static bool EnableReadableDepth( const char *name, const vector<wstring> &args )
//{
//  if( args.empty() )
//    return false;
//
//  const bool enable( 0 != NStr::ToULong(NStr::ToMBCS(args[0])) );
//  s_readableDepth = enable && static_cast<Render::ConfigManagerImpl*>(Render::GetConfigManager())->ReadableDepthSupported();
//
//  return enable == s_readableDepth;
//}
//
//REGISTER_CMD( readableDepthEnable, EnableReadableDepth );

REGISTER_VAR("readableDepthEnable", s_readableDepth, STORAGE_NONE);
REGISTER_DEV_VAR("stencilEnable", s_stencilEnable, STORAGE_NONE);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
