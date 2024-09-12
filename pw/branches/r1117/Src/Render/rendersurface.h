#pragma once

#include "Rect.h"
#include "locktype.h"
#include "DxIntrusivePtr.h"
#include "DeviceLost.h"

namespace Render
{

struct LockedRect
{
	int pitch;
	unsigned char* data;

  LockedRect() {}
  LockedRect(int _pitch, uchar* _data) : pitch(_pitch), data(_data) {}
};

class RenderSurface : public CObjectBase, public DeviceLostHandler
{
  OBJECT_BASIC_METHODS( RenderSurface );

protected:
  RenderSurface();
  explicit RenderSurface( IDirect3DSurface9* pSurface_ );
  explicit RenderSurface( D3DSURFACE_DESC const& desc_ );

public:
  typedef DeviceLostWrapper<RenderSurface> Wrapped;

  ~RenderSurface();

  void Init( D3DSURFACE_DESC const& desc_ );

	const DXSurfaceRef& GetDXSurface() const { return pSurface; }

	LockedRect LockRect( const Rect& rect, ERenderLockType lockType );
	LockedRect Lock( ERenderLockType lockType );
	void Unlock();
	void StretchTo( IDirect3DSurface9 *other, bool bLinear = false );
  unsigned int GetWidth() const { return desc.Width; }
  unsigned int GetHeight() const { return desc.Height; }
  D3DFORMAT GetD3DFormat() const { return desc.Format; }

  // Handle lost device
  virtual void OnDeviceLost();
  virtual void OnDeviceReset();

private:
  void CreateInternal();
	LockedRect LockRectInternal( RECT* rect, ERenderLockType lockType );

private:
  DXSurfaceRef pSurface;
  D3DSURFACE_DESC desc;
};

typedef CObj<RenderSurface> RenderSurfaceRef;

inline bool IsValidPtr(const RenderSurface* _tex)
{
  return _tex && _tex->GetDXSurface();
}

} // namespace Render
