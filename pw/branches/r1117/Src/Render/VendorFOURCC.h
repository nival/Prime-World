#pragma once

//Vendor-specific depth-stencil formats
#define FOURCC_DF16 ((D3DFORMAT)(MAKEFOURCC('D','F','1','6')))
#define FOURCC_DF24 ((D3DFORMAT)(MAKEFOURCC('D','F','2','4')))
#define FOURCC_RAWZ ((D3DFORMAT)(MAKEFOURCC('R','A','W','Z')))
#define FOURCC_INTZ ((D3DFORMAT)(MAKEFOURCC('I','N','T','Z')))

//ATI-specific Fetch4
#define FOURCC_GET4 MAKEFOURCC('G','E','T','4')
#define FOURCC_GET1 MAKEFOURCC('G','E','T','1')

//ATI-specific support for depth buffer copy, including multisample resolve
#define FOURCC_RESZ ((D3DFORMAT)(MAKEFOURCC('R','E','S','Z')))
//ATI-specific RESZ depth buffer copy token
#define RESZ_CODE 0x7fa05000

//ATI Render-to-VB extension. Supported by GF6/GF7 too.
#define FOURCC_R2VB ((D3DFORMAT)(MAKEFOURCC('R','2','V','B')))
//NV/ATI-specific support for null Render Target
#define FOURCC_NULL ((D3DFORMAT)(MAKEFOURCC('N','U','L','L')))

