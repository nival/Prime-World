#include "stdafx.h"

#include "rendersurface.h"
#include "renderflagsconverter.h"

// pSurface == 0, desc == 0  =>  empty
// pSurface == 0, desc != 0  =>  waiting for OnDeviceReset()
// pSurface != 0, desc != 0  =>  ready

namespace Render
{

RenderSurface::~RenderSurface()
{
  if( pSurface && (D3DPOOL_MANAGED != desc.Pool) )
    UnregisterDXPtr( Get(pSurface) );
}

RenderSurface::RenderSurface()
{
  ZeroMemory(&desc, sizeof(desc));
}

RenderSurface::RenderSurface( IDirect3DSurface9* pSurface_ ) : pSurface( pSurface_, false )
{
  ZeroMemory(&desc, sizeof(desc));
  if (!pSurface)
    return;
  pSurface->GetDesc(&desc);
  ASSERT(desc.Type == D3DRTYPE_SURFACE);
}

RenderSurface::RenderSurface( D3DSURFACE_DESC const& desc_ ) : desc( desc_ )
{
  ASSERT(desc.Type == D3DRTYPE_SURFACE);
  CreateInternal();
}

void RenderSurface::Init( D3DSURFACE_DESC const& desc_ )
{
  ASSERT(desc_.Type == D3DRTYPE_SURFACE);
  desc = desc_;
  CreateInternal();
}

void RenderSurface::CreateInternal()
{
  ASSERT(!pSurface);
  IDirect3DSurface9* pDirect3DSurface = 0;
  HRESULT hr = E_INVALIDARG;
  const bool wasNotManaged = (D3DPOOL_MANAGED != desc.Pool);

  if( desc.Format == D3DFMT_D24S8 )
  {
    hr = GetDevice()->CreateDepthStencilSurface(desc.Width, desc.Height, desc.Format, desc.MultiSampleType, desc.MultiSampleQuality,
                                                FALSE, &pDirect3DSurface, NULL);
    desc.Pool = D3DPOOL_DEFAULT;
  }
  else if( D3DUSAGE_RENDERTARGET == desc.Usage )
  {
    hr = GetDevice()->CreateRenderTarget(desc.Width, desc.Height, desc.Format, desc.MultiSampleType, desc.MultiSampleQuality,
                                         FALSE, &pDirect3DSurface, NULL);
    desc.Pool = D3DPOOL_DEFAULT;
  }
  else if( D3DPOOL_MANAGED != desc.Pool )
    hr = GetDevice()->CreateOffscreenPlainSurface(desc.Width, desc.Height, desc.Format, desc.Pool, &pDirect3DSurface, NULL);

  if( D3D_OK == hr )
  {
    if( pSurface && wasNotManaged )
      UnregisterDXPtr( Get(pSurface) );

    pSurface.Attach(pDirect3DSurface);
    RegisterDXPtr(pDirect3DSurface);
  }
  else
    NI_ASSERT( false, NStr::StrFmt("RenderSurface::CreateInternal() Failed. code: 0x%08X, error: %s description: %s",
                                   hr, DXGetErrorStringA(hr), DXGetErrorDescriptionA(hr)) );
}

LockedRect RenderSurface::LockRect( const Rect& rect, ERenderLockType lockType )
{
	RECT d3drect;
	d3drect.bottom = rect.bottom;
	d3drect.top = rect.top;
	d3drect.left = rect.left;
	d3drect.right = rect.right;

	return LockRectInternal(&d3drect, lockType);
}

LockedRect RenderSurface::Lock( ERenderLockType lockType )
{
	return LockRectInternal(0, lockType );
}

void RenderSurface::Unlock()
{
	pSurface->UnlockRect();
}

void RenderSurface::StretchTo( IDirect3DSurface9 *other, bool bLinear )
{
	HRESULT hr = GetDevice()->StretchRect(Get(pSurface), 0, other, 0, bLinear ? D3DTEXF_LINEAR : D3DTEXF_POINT);
  NI_DX_THROW(hr, __FUNCTION__);
}

LockedRect RenderSurface::LockRectInternal( RECT* rect, ERenderLockType lockType )
{
  D3DLOCKED_RECT d3dlocked_rect = {0};
	HRESULT hr = pSurface->LockRect( &d3dlocked_rect, rect, ConvertRenderLockType(lockType) );
  NI_DX_THROW(hr, __FUNCTION__);

	LockedRect res;
	res.data = reinterpret_cast< unsigned char* >( d3dlocked_rect.pBits );
	res.pitch = d3dlocked_rect.Pitch;

	return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSurface::OnDeviceLost()
{
  if (!pSurface)
    return;
  ASSERT(desc.Type == D3DRTYPE_SURFACE);

  if( pSurface && (D3DPOOL_MANAGED != desc.Pool) )
    UnregisterDXPtr( Get(pSurface) );

  // free VRAM resource
  if(desc.Pool == D3DPOOL_DEFAULT)
    pSurface = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSurface::OnDeviceReset()
{
  // skip empty surfaces and the ones that not in VRAM
  if (desc.Type == D3DRTYPE_SURFACE && desc.Pool == D3DPOOL_DEFAULT)
    CreateInternal(); // note: may fail due to device lost again
}

} // namespace Render
