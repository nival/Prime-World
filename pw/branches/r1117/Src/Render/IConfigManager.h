#pragma once

namespace Render
{
  typedef pair<string, string> StringPair;

// Effect-side Config Manager interface
struct NOVTABLE IConfigManager
{
#include "Features.h"

  typedef vector<StringPair> ConfigParams;

  struct TechniqueDesc
  {
    DWORD flags;
    D3DFORMAT r2vbFormat;
  };

  enum ResourceType
  {
    Total = 0,
    Shaders,
    Textures,
    Geometry,
    NUM_RESOURCE_TYPES
  };

  struct SysInfo
  {
    DWORD MaxVertexShaderConst;
    bool  IsNullRef;
  };

  virtual const SysInfo& GetSysInfo() const = 0;
  virtual UINT GetPerfomanceLevel(ResourceType _type) const = 0;
  virtual UINT FindAcceptableTechnique(const TechniqueDesc **_pDesc, UINT numDesc) const = 0;
  virtual bool CheckFeatureSupport(DWORD _features) const = 0;      // return true if any of requested features supported
  virtual bool CheckFeatureSupportExact(DWORD _features) const = 0; // return true if all of requested features supported
  virtual bool ReadableDepthEnabled() const = 0;
  virtual bool StencilSupported(ERenderFormat _depthFormat) const = 0;
  virtual ERenderFormat GetDepthFormatPreffered() const = 0;
  virtual const ConfigParams& GetConfigParams() const = 0;

  // Wrappers
  bool HasDF16() const { return CheckFeatureSupport(hasDF16); } // ATI DF16 depth format
  bool HasDF24() const { return CheckFeatureSupport(hasDF24); } // ATI DF24 depth format. Implies Fetch4 support
  bool HasRAWZ() const { return CheckFeatureSupport(hasRAWZ); } // NVidia RAWZ depth format
  bool HasINTZ() const { return CheckFeatureSupport(hasINTZ); } // NV/ATI INTZ depth format
  bool HasRESZ() const { return CheckFeatureSupport(hasRESZ); } // ATI-specific support for depth buffer copy
  bool HasR2VB() const { return CheckFeatureSupport(hasR2VB); } // ATI Render-to-VB extension. Supported by GF6/GF7 too.
  bool HasNLRT() const { return CheckFeatureSupport(hasNLRT); } // NV/ATI Null Render-Target format
  bool HasD16T() const { return CheckFeatureSupport(hasD16T); } // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D16
  bool HasD24X() const { return CheckFeatureSupport(hasD24X); } // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D24X8
  bool HasD24S() const { return CheckFeatureSupport(hasD24S); } // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D24S8
  bool HasVT16() const { return CheckFeatureSupport(hasVT16); } // ARGB16F Vertex textures support
  bool HasVT32() const { return CheckFeatureSupport(hasVT32); } // ARGB32F Vertex textures support

  bool HasVT() const { return CheckFeatureSupport(hasVT16|hasVT32); } // Vertex textures support
  bool HasDF() const { return CheckFeatureSupport(hasDF16|hasDF24); } // ATI DF16/24 depth format
  // NV/ATI Depth/Stencil textures (hardware shadow maps)
  bool HasDSM() const { return CheckFeatureSupport(hasD16T|hasD24X|hasD24S); }

protected:
  IConfigManager(void)  {}
  ~IConfigManager(void) {}
};

const IConfigManager* GetIConfigManager();

}; // namespace Render