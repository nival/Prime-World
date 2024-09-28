#pragma once

#include "renderstates.h"
#include "SmartRenderer.h"
#include "material.h"

namespace Render
{

enum StencilState
{
  STENCILSTATE_INVALID,
  STENCILSTATE_IGNORE,
  STENCILSTATE_WRITEBITS,
  STENCILSTATE_CHECKBITS,

  STENCILSTATE_COUNT
};

enum StencilBit
{
  STENCILBIT_SHADOWRECEIVER = 0x01,
  STENCILBIT_DECALRECEIVER = 0x02,
  STENCILBIT_RENDERALLOW = 0x04,
};

class RenderStatesManager : public Render::DeviceLostHandler
{
protected:
  RenderStatesManager();

public:
	~RenderStatesManager();

	void SetState(RenderState state);
  RenderState const& GetCurrentState() const { return lastRenderState; }

	void SetStateDirect(D3DRENDERSTATETYPE State, DWORD Value);
	void SetStencilState(StencilState state, DWORD mask = 0xFFFFFFFF, DWORD bits = 0xFFFFFFFF);
  void SetStencilStateAddonBits(DWORD mask, DWORD bits);
	void SetSamplerState(unsigned index, SamplerState const& state);
  void SetSampler(unsigned index, SamplerState const& state, const Texture* texture)
  {
    SetSamplerState(index, state);
    SmartRenderer::BindTexture(index, texture);
  }

  // Next 2 functions return true at the case the lock state was changed
  bool LockStencil()   { return !stencilLock++; }
  bool UnlockStencil()
  {
    if(stencilLock > 0)
      return !--stencilLock;
    return false;
  }

	void UpdateStats();

  // debugging functionality
  static void DumpStates();

  // From Render::DeviceLostHandler
  virtual void OnDeviceLost();
  virtual void OnDeviceReset() { Init(); }

private:
  void Init();

private:
	RenderState lastRenderState;
	SamplerState lastSamplerState[16];
  StencilState lastStencilState;
  DWORD lastStencilBits;
  DWORD lastStencilMask;
  int   stencilLock;

	hash_map<unsigned long, DXStateBlockRef> renderStateCache;
  hash_map<unsigned long, DXStateBlockRef> samplerStateCache;
  DXStateBlockRef stencilStateCache[STENCILSTATE_COUNT];
};

}; // namespace Render