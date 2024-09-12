enum Features {
  hasDF16 = 1,            // ATI DF16 depth format
  hasDF24 = hasDF16 << 1, // ATI DF24 depth format. Implies Fetch4 support
  hasRAWZ = hasDF24 << 1, // NVidia RAWZ depth format
  hasINTZ = hasRAWZ << 1, // NV/ATI INTZ depth format
  hasRESZ = hasINTZ << 1, // ATI-specific support for depth buffer copy
  hasR2VB = hasRESZ << 1, // ATI Render-to-VB extension. Supported by GF6/GF7 too.
  hasNLRT = hasR2VB << 1, // NV/ATI Null Render-Target format
  hasD16T = hasNLRT << 1, // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D16
  hasD24X = hasD16T << 1, // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D24X8
  hasD24S = hasD24X << 1, // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D24S8
  hasVT16 = hasD24S << 1, // ARGB16F Vertex textures support
  hasVT32 = hasVT16 << 1, // ARGB32F Vertex textures support
};

static const int featuresVersion = 1;
