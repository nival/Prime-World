#pragma once

#include "../System/Noncopyable.h"
#include "../System/Geom.h"
#include "GlobalMasks.h"
#include "material.h"

#define ONLINE_SHADERS_PATH "Shaders/OnlineShaders/"

namespace Render
{

class ImmRenderer
{
public:
   struct BasicParams : public NonCopyable
  {
    CTRect<float> uvRect;

    virtual void BindMaterial(const CTRect<float> *rect = NULL) const = 0;
    BasicParams(float _minx, float _miny, float _maxx, float _maxy, bool _useViewPort = false)
      : uvRect(_minx, _miny, _maxx, _maxy)/*, useViewPort(_useViewPort), doHalfPixelShift(true)*/ {}
  };

  // this class doesn't own anything
	class Params : public BasicParams
	{
  protected:
		DXPixelShaderRef const& pPixelShader;
    IDirect3DVertexShader9 *pVertexShader;
		const Texture2D* pTexture;
		SamplerState const* pCustomSamplerState;

  public:
		explicit Params(DXPixelShaderRef const& pPixelShader_, const Texture2D* pTexture_ = Texture2DRef(), SamplerState const* pCustomSamplerState_ = NULL)
			: BasicParams(0.f, 0.f, 1.f, 1.f), pPixelShader(pPixelShader_), pVertexShader(::Get(ImmRenderer::Get()->GetVShader(0)))
      , pTexture(pTexture_), pCustomSamplerState(pCustomSamplerState_) {}

    // pPixelShaderName MUST point to PERSISTENT CONSTANT string
		explicit Params(char const* pPixelShaderName, const Texture2D* pTexture_ = 0, SamplerState const* pCustomSamplerState_ = NULL)
			: BasicParams(0.f, 0.f, 1.f, 1.f), pPixelShader(ImmRenderer::Get()->GetPShader(pPixelShaderName))
      , pVertexShader(::Get(ImmRenderer::Get()->GetVShader(0))), pTexture(pTexture_), pCustomSamplerState(pCustomSamplerState_) {}

    // Potentially dangerous function. LostDevice WILL INVALIDATE pVertexShader;
    // pName MUST point to PERSISTENT CONSTANT string
    Params& SetVShader(char const* pName) { pVertexShader = ::Get(ImmRenderer::Get()->GetVShader(pName)); return *this; }
    Params& SetTexture(Texture2D const* _pTexture) { pTexture = _pTexture; return *this; }

    virtual void BindMaterial(const CTRect<float> *rect = NULL) const;
	};

  // This class sets uvRect according to viewport
	class ParamsVP : public Params
	{
    void SetUV();

  public:
		explicit ParamsVP(DXPixelShaderRef const& pPixelShader_, Texture2DRef const& pTexture_, SamplerState const* pCustomSamplerState_ = NULL)
			: Params(pPixelShader_, pTexture_, pCustomSamplerState_)
    { SetUV(); }

    // pPixelShaderName MUST point to PERSISTENT CONSTANT string
		explicit ParamsVP(char const* pPixelShaderName, Texture2DRef const& pTexture_, SamplerState const* pCustomSamplerState_ = NULL)
			: Params(pPixelShaderName, pTexture_, pCustomSamplerState_)
    { SetUV(); }
	};

  class MaterialParams : public BasicParams
  {
    Material *pMaterial;

  public:
    explicit MaterialParams(Material *_pMaterial) : BasicParams(0.f, 0.f, 1.f, 1.f), pMaterial(_pMaterial) {}
    virtual void BindMaterial(const CTRect<float> *rect = NULL) const;
  };

public:
	ImmRenderer();
	~ImmRenderer();

	static void Init();
	static void Term();
	static ImmRenderer* Get();

	void ReloadShaders();

  //Arbitrary polygon in clip space [-1.0,+1.0]x[-1.0,+1.0]
  void RenderScreenQuad( const CTPoint<float> poly[4], const BasicParams & params );
	// full-screen area
	void RenderScreenQuad(BasicParams const& params);
  void RenderScreenQuad(BasicParams const& params, DXVertexDeclarationRef const &pVDecl);
	// rectangular area in clip space -- [-1.0,+1.0]x[-1.0,+1.0]
	void RenderScreenQuad(CTRect<float> const& rect, BasicParams const& params);
  void RenderScreenQuad(CTRect<float> const& rect, BasicParams const& params, DXVertexDeclarationRef const &pVDecl);
	// rectangular area in target pixel space -- [0,W-1]x[0,H-1] -- NB! full-screen = [0,W]x[0,H] with bottom-right excluded
	void RenderScreenQuad(CTRect<int> const& rect, BasicParams const& params);
	// smirnov [2008/12/22]: !!!NB!!! Bottom-right pixels are excluded from width and height in
	// the integer implementation of CTRect<>. However other methods do consider them as internal 
	// ones.

	// load/retrieve runtime shader
	// pName MUST point to PERSISTENT CONSTANT string
 	DXPixelShaderRef const& GetPShader(char const* pName);
  DXVertexShaderRef const& GetVShader(char const* pName);

  // Read-only
  const IDirect3DVertexBuffer9* GetFullVB() const { return ::Get(pFullVB); }

private:
	static ImmRenderer* s_pInstance;

	DipDescriptor     dip;
	DXVertexDeclarationRef pVDecl;
	DXVertexBufferRef pFullVB;
	DXVertexBufferDynamicRef::Wrapped pRectVB;
	DXIndexBufferRef  pIB;

	typedef hash_map<const char*, DXPixelShaderRef> PixelShaderCache;
  typedef hash_map<const char*, DXVertexShaderRef> VertexShaderCache;
  VertexShaderCache shaderVCache;
	PixelShaderCache  shaderPCache;
};

inline ImmRenderer* GetImmRenderer() { return ImmRenderer::Get(); }

} // namespace Render