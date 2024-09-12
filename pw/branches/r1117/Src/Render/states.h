#pragma once

namespace Render
{

// @BVS@MAT Temporarily placed here
struct HDRColorModifier
{
	HDRColor mul;
	HDRColor add; 
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RenderState
{
	friend class RenderStatesManager;

public:
	RenderState() : bitmask(0) {}

	void operator=(const RenderState &state) { bitmask = state.bitmask; }
	bool operator==(const RenderState &state) { return bitmask == state.bitmask; }

	void operator=(const NDb::RenderState &state)
	{
		blendMode = state.blendMode;
		alphaTest = state.alphaTest;
		alphaTestRef = state.alphaTestRef;
		culling = state.culling;
		emissive = 0;
	}

	NDb::BlendMode GetBlendMode() const { return (NDb::BlendMode)blendMode; }
	NDb::OnOffState GetAlphaTest() const { return (NDb::OnOffState)alphaTest; }
	int GetAlphaTestRef() const { return (int)alphaTestRef; }
	NDb::OnOffState GetCulling() const { return (NDb::OnOffState)culling; }
	NDb::OnOffState GetEmissive() const { return (NDb::OnOffState)emissive; }
  const DWORD GetBitMask()  const { return bitmask; }
  RenderState GetCRCValue() const { return RenderState(*this).SetEmissive(NDb::ONOFFSTATE_OFF); }

	RenderState& SetBlendMode(NDb::BlendMode mode) { blendMode = mode; return *this; }
	RenderState& SetAlphaTest(NDb::OnOffState onoff) { alphaTest = onoff; return *this; }
	RenderState& SetAlphaTestRef(int alpha) { alphaTestRef = alpha; return *this; }
	RenderState& SetCulling(NDb::OnOffState onoff) { culling = onoff; return *this; }
	RenderState& SetEmissive(NDb::OnOffState onoff) { emissive = onoff; return *this; }

  static RenderState NoBlendNoTest() // this functions MUST return MODIFIABLE copy of 'state'
  {
    static const RenderState state = RenderState().SetBlendMode(NDb::BLENDMODE_OFF).SetAlphaTest(NDb::ONOFFSTATE_OFF);
    return state;
  }

private:
#pragma warning(disable:4201)
	union {
		DWORD bitmask;
		struct {
			DWORD blendMode : 3;
			DWORD alphaTest : 1;
			DWORD alphaTestRef : 8;
			DWORD culling : 1;
			DWORD emissive : 1;

			DWORD alwaysFailCompare : 1;
		};
	};
#pragma warning(default:4201)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SamplerState
{
	friend class RenderStatesManager;

public:
	// the most popular sampler states
  // WARNING - an attempt to return by value conflicts with ImmRenderer::Params
	static const SamplerState& PRESET_CLAMP_POINT();
	static const SamplerState& PRESET_CLAMP_BILINEAR();
  static const SamplerState& PRESET_CLAMP_MIP_BILINEAR();
  static const SamplerState& PRESET_CLAMP_TRILINEAR();
  static const SamplerState& PRESET_WRAP_POINT();
  static const SamplerState& PRESET_WRAP_BILINEAR();
  static const SamplerState& PRESET_WRAP_MIP_BILINEAR();
  static const SamplerState& PRESET_WRAP_TRILINEAR();

  static bool SamplerState::IsTriLinearDisabled();

	SamplerState() : bitmask(0) {}
  explicit SamplerState(DWORD _bitmask) : bitmask(_bitmask) {}
	SamplerState(NDb::MinFilterType a, NDb::MagFilterType b, NDb::MipFilterType c,
               NDb::TextureAddressType d, NDb::TextureAddressType e)
  {
    bitmask = 0;
	  minFilter = a; magFilter = b; mipFilter = c;
    addressU = d;  addressV = e;
  }
  explicit SamplerState(const NDb::SamplerState &state)
  {
    bitmask = 0;
    minFilter = state.minFilter;
    magFilter = state.magFilter;
    mipFilter = state.mipFilter;
    addressU = state.addressU;
    addressV = state.addressV;
  }

	void operator=(const SamplerState &state) { bitmask = state.bitmask; }
	bool operator==(const SamplerState &state) { return bitmask == state.bitmask; }

	NDb::MinFilterType GetMinFilter() const { return (NDb::MinFilterType)minFilter; }
	NDb::MagFilterType GetMagFilter() const { return (NDb::MagFilterType)magFilter; }
	NDb::MipFilterType GetMipFilter() const { return (NDb::MipFilterType)mipFilter; }
	NDb::TextureAddressType GetAddressU() const { return (NDb::TextureAddressType)addressU; }
	NDb::TextureAddressType GetAddressV() const { return (NDb::TextureAddressType)addressV; }

	SamplerState& SetMinFilter(NDb::MinFilterType mode) { minFilter = mode; return *this; }
	SamplerState& SetMagFilter(NDb::MagFilterType mode) { magFilter = mode; return *this; }
	SamplerState& SetMipFilter(NDb::MipFilterType mode) { mipFilter = mode; return *this; }
	SamplerState& SetAddressU(NDb::TextureAddressType mode) { addressU = mode; return *this; }
	SamplerState& SetAddressV(NDb::TextureAddressType mode) { addressV = mode; return *this; }

  SamplerState& CreateMask()
  {
    minFilter = UINT_MAX;
    magFilter = UINT_MAX;
    mipFilter = UINT_MAX;
    addressU  = UINT_MAX;
    addressV  = UINT_MAX;
    alwaysFailCompare = UINT_MAX;
  }

  const DWORD GetBitmask() const { return bitmask; }

protected:
#pragma warning(disable:4201)
	union {
		DWORD bitmask;
		struct {
			DWORD minFilter : 3;
			DWORD magFilter : 1;
			DWORD mipFilter : 2;
			DWORD addressU : 2;
			DWORD addressV : 2;

			DWORD alwaysFailCompare : 1;

      DWORD hasModifiers : 1;
      DWORD enableMode   : 2;
		};
	};
#pragma warning(default:4201)
};

class SamplerState2 : public SamplerState
{
public:
  enum {
    Enable = 0,
    Disable,
    ForceDisable
  };

  SamplerState2() {}
  SamplerState2(SamplerState _src): SamplerState(_src) {}

  operator SamplerState()
  {
    static const SamplerState mask = SamplerState().CreateMask();
    return SamplerState( bitmask & mask.GetBitmask() );
  }

  SamplerState2& operator=(const SamplerState2& _src)
  {
    bitmask = _src.GetBitmask();
    return *this;
  }

  bool             HasModifiers()    const { return hasModifiers; }
  SamplerState& SetHasModifiers(bool _has) { hasModifiers = _has; return *this; }

  bool             Enabled()        const { return 0 == enableMode; }
  bool             EnableMode()     const { return enableMode; }
  SamplerState& SetEnableMode(bool _mode) { enableMode = _mode; return *this; }
};

} // namespace Render
