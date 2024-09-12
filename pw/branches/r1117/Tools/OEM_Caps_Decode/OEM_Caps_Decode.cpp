// OEM_Caps_Decode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\Src\Render\Features.h"

const _TCHAR* const FeatureNames[] = {
  _TEXT("hasDF16"), // ATI DF16 depth format
  _TEXT("hasDF24"), // ATI DF24 depth format. Implies Fetch4 support
  _TEXT("hasRAWZ"), // NVidia RAWZ depth format
  _TEXT("hasINTZ"), // NV/ATI INTZ depth format
  _TEXT("hasRESZ"), // ATI-specific support for depth buffer copy
  _TEXT("hasR2VB"), // ATI Render-to-VB extension. Supported by GF6/GF7 too.
  _TEXT("hasNLRT"), // NV/ATI Null Render-Target format
  _TEXT("hasD16T"), // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D16
  _TEXT("hasD24X"), // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D24X8
  _TEXT("hasD24S"), // NV/ATI Depth/Stencil textures (hardware shadow maps) - D3DFMT_D24S8
  _TEXT("hasVT16"), // ARGB16F Vertex textures support
  _TEXT("hasVT32"), // ARGB32F Vertex textures support
};

int _tmain(int argc, _TCHAR* argv[])
{
  _tprintf_s(_TEXT("OEM D3D extensions flags cracker, ver. %d.\n"), featuresVersion);

  unsigned int flags = 0;
  if( 1 == argc || 0 == _stscanf_s(argv[1], _TEXT("%i"), &flags) )
  {
    _tprintf_s(_TEXT("\tUsage: OEM_Caps_Decode.exe arg.")
               _TEXT("\n\tArgument should be a crashrpt.xml <DXcapsOEM> tag value\n"), argv[0]);
    return 1; //EXIT_FAILURE
  }

  const int numFlags = sizeof(FeatureNames) / sizeof(FeatureNames[0]);
  _tprintf_s( _TEXT("Features supported:") );
  for(int i = 0; i < numFlags; ++i) {
    if((1 << i) & flags)
      _tprintf_s(_TEXT(" %s"), FeatureNames[i]);
  }
  _tprintf_s( _TEXT("\n") );

	return 0;
}

