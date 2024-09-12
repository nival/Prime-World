#pragma once

#include "rendersurface.h"
#include "DxIntrusivePtr.h"
#include "DeviceLost.h"

namespace Render
{

void OnTextureDestruction(class Texture *tex);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Texture : public CObjectBase
{
  OBJECT_BASIC_METHODS( Texture );

public:
  Texture() {}

  explicit Texture(IDirect3DBaseTexture9 *pTex) : pDXTexture(pTex, false)
  {
    RegisterDXPtr(pTex);
  }
  virtual ~Texture()
  {
    if( pDXTexture )
      UnregisterDXPtr( Get(pDXTexture) );
    OnTextureDestruction(this);
  }

	unsigned int GetMipSubLevelsCount() const;

  const DXBaseTextureRef& GetDXTexture() const { return pDXTexture; }
  void  GenerateMipSubLevels()
  {
    if( Compatibility::IsRunnedUnderWine() )
      GenerateMipSubLevels_(); // Wine did not implemented automipmaps yet
    else
      if( IDirect3DBaseTexture9* pTex = Get(GetDXTexture()) )
        pTex->GenerateMipSubLevels();
  }

protected:
  virtual void GenerateMipSubLevels_() {}
  void SetTexture(IDirect3DBaseTexture9 *_tex);

	DXBaseTextureRef pDXTexture;
};

template <typename T>
class TextureTyped : public Texture
{
public: 
	TextureTyped() {}
	TextureTyped(T *pDXTex) : Texture(pDXTex) {}

	T* GetDXTexture() const { return static_cast<T*>(Get(pDXTexture)); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Texture2D : public TextureTyped<IDirect3DTexture9>, public DeviceLostHandler
{
  OBJECT_BASIC_METHODS( Texture2D );

public:
  typedef DeviceLostWrapper<Texture2D> Wrapped;

  unsigned int GetWidth()  const { return desc.Width; }
	unsigned int GetHeight() const { return desc.Height; }
  D3DFORMAT    GetFormat() const { return desc.Format; }

	// Texture locking
  LockedRect LockRect(unsigned int level, unsigned int left, unsigned int right, unsigned int top, unsigned int bottom, ERenderLockType lockType);
  LockedRect LockRect(unsigned int level, RECT *pRect, ERenderLockType lockType);
	LockedRect LockRect(unsigned int level, ERenderLockType lockType);
	void UnlockRect(unsigned int level);

	// Texture updating
	bool Update(Texture2D *pTex);

	// Retrieving surface
	DXSurfaceRef GetSurface(unsigned int level) const;

  // Handle lost device
  virtual void OnDeviceLost();
  virtual void OnDeviceReset();

  // Set new texture
  void SetTexture(Texture2D const& pOther);

protected:
  Texture2D() : levels(0) { ZeroMemory(&desc, sizeof(desc)); }
  explicit Texture2D(IDirect3DTexture9 *pTex, HandlerPriority deviceLostHandlerPriority = HANDLERPRIORITY_NORMAL);
  explicit Texture2D(D3DSURFACE_DESC const& desc_, HandlerPriority deviceLostHandlerPriority = HANDLERPRIORITY_NORMAL);

  void CreateInternal();

  virtual void GenerateMipSubLevels_();

  UINT levels;
  D3DSURFACE_DESC desc;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// R2VB texture - default-pool, RT, contains vertex data. Depending on actual hardware,
// switches between Render-to-Vertex-Buffer and Vertex-Texture modes.
class TextureVtx : public Texture2D
{
  OBJECT_METHODS(0x3D897500, TextureVtx);

public:
  typedef DeviceLostWrapper<TextureVtx> Wrapped;

  struct Sizes
  {
    SIZE vtx;
    SIZE r2vb;

    Sizes() {}
    Sizes(UINT _width, UINT _heigth)
    {
      vtx.cx = r2vb.cx = _width;
      vtx.cy = r2vb.cy = _heigth;
    }
    Sizes(UINT _w_vtx, UINT _h_vtx, UINT _w_r2vb, UINT _h_r2vb)
    {
      vtx.cx = _w_vtx;
      vtx.cy = _h_vtx;
      r2vb.cx = _w_r2vb;
      r2vb.cy = _h_r2vb;
    }
  };

  // WARNING! These methods are NOT virtual! Use typecasts and GetTypeId().
  void Bind(UINT _sampler, UINT _stream = 15); 
  void UnBind();
  bool UsingR2VB() const { return desc.Usage & D3DUSAGE_DMAP; }
  UINT GetPixelSize() const { return pixelSize; }

  virtual void OnDeviceReset();

protected:
  TextureVtx() { NI_ASSERT(FALSE, "Invalid TextureVtx constructor called!"); } // just to make OBJECT_METHODS happy
  TextureVtx(const Sizes& _sizes, bool _preferR2VB = true);

private:
  UINT pixelSize;
  UINT sampler;
  UINT stream;
  Sizes sizes;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TextureCube : public TextureTyped< IDirect3DCubeTexture9 >
{
public :
  explicit TextureCube( IDirect3DCubeTexture9 *pTex );

  // Set new texture
  void SetTexture(TextureCube const& pOther);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref types
typedef CObj<Texture> TextureRef;
typedef CObj<Texture2D> Texture2DRef;
typedef CObj<TextureVtx> TextureVtxRef;
typedef CObj<TextureCube> TextureCubeRef;

inline bool IsValidPtr(const Texture* _tex)
{
  return _tex && _tex->GetDXTexture();
}

}; // namespace Render
