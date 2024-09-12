#pragma once

#include "Vendor/DirectX/Include/d3d9.h"
#include "Vendor/DirectX/Include/d3dx9.h"

#include "DxResourcesControl.h"

/**
  @brief Default reference management policy class

  @note And an exemplar as well :)

  This class should manage reference counting
  for pointers. The class should implement
  two static methods: DefaultRefPolicy::addRef
  and DefaultRefPolicy::release that add and release
  a reference correspondingly.

  @note Pointers are guaranteed to be not NULL!

  @param T Type to manage pointers to
*/
struct DXObjectRefPolicy
{
  template <class T>
  static void OnCreate(T * p, bool shouldAdd = true)
  {
    if(!shouldAdd && p)
      RegisterDXPtr(p);
  }

  /**
    @brief Add a reference
    @param p Pointer to add a reference
  */
  static void addRef(IUnknown * p)
  {
    p->AddRef();
  }

  /**
    @brief Release
    @param p Pointer to release
  */
  static void release(IUnknown * p)
  {
    int rc = p->Release();
    if (rc == 0)
      UnregisterDXPtr(p);
  }
};

typedef IntrusivePtr<IDirect3DVertexShader9, DXObjectRefPolicy> DXVertexShaderRef;
typedef IntrusivePtr<IDirect3DPixelShader9, DXObjectRefPolicy> DXPixelShaderRef;
typedef IntrusivePtr<IDirect3DVertexBuffer9, DXObjectRefPolicy> DXVertexBufferRef;
typedef IntrusivePtr<IDirect3DIndexBuffer9, DXObjectRefPolicy> DXIndexBufferRef;
typedef IntrusivePtr<ID3DXConstantTable> DXConstantTableRef;
typedef IntrusivePtr<IDirect3DVertexDeclaration9, DXObjectRefPolicy> DXVertexDeclarationRef;
typedef IntrusivePtr<ID3DXMesh> DXMeshRef;
typedef IntrusivePtr<IDirect3DCubeTexture9> DXCubeTextureRef;
typedef IntrusivePtr<IDirect3DBaseTexture9> DXBaseTextureRef;
typedef IntrusivePtr<IDirect3DTexture9> DXTextureRef;
typedef IntrusivePtr<ID3DXEffect> DXEffectRef;
typedef IntrusivePtr<IDirect3DQuery9> DXQueryRef;
typedef IntrusivePtr<IDirect3DStateBlock9> DXStateBlockRef;

typedef IntrusivePtr<IDirect3DSurface9> DXSurfaceRef; // Use this as a holder for surfaces that belongs to textures
typedef IntrusivePtr<IDirect3DSurface9, DXObjectRefPolicy> DXSurfacePtr; // Use this as a holder for standalone surfaces
