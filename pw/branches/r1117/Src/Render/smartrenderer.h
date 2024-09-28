#pragma once

#include "DxIntrusivePtr.h"
#include "texture.h"
#include "dxutils.h"

namespace Render
{
class VertexFormatDescriptor;
struct VertexStreamDescriptor;
class IVertexFormatDeclaration;
class RenderTarget;
struct DipDescriptor;

template <class VBREF>
struct VertexStreamT
{
	VBREF        pVertexBuffer;
	unsigned int offset;
	unsigned int stride;

	void Set(const VBREF &pVB, unsigned int stride_, unsigned int offset_ = 0)
	{
		pVertexBuffer = pVB;
		stride = stride_;
		offset = offset_;
	}
};

typedef VertexStreamT<DXVertexBufferRef> VertexStream;

namespace SmartRenderer
{
void GetTriangleAndDipCount(unsigned int& triangles, unsigned int& dips);
void ResetTriangleAndDipCount();
void OnFrameStart();

///
void AddRect(float l, float t, float r, float b, int R, int G, int B);
void AddLine(float sx, float sy, float ex, float ey, int R, int G, int B, float width = 1.0f);
void RenderDeferred2D();

///
void Init();
void NullThePointers();
bool IsResourceBound(const IUnknown* const ptr);

// Sorry for profiling code [11/17/2009 smirnov]
// void _DebugSamplerBind(int idx, unsigned long crc);
// void _DebugSamplerBindDump();
// void _DebugSamplerBindReset();

///
const DXVertexDeclarationRef & GetVertexFormatDeclaration(const VertexFormatDescriptor& descr);

///
void BindVertexBufferRaw(unsigned int streamNumber, IDirect3DVertexBuffer9* buffer, unsigned int stride, unsigned int offset = 0);

///  This function can modify stream number depending on 'instancing' state
void BindVertexBuffer(unsigned int streamNumber, IDirect3DVertexBuffer9* buffer, unsigned int stride, unsigned int offset = 0);

///  set instance Id VB to stream 1
void BindInstanceVB(unsigned int offset = 0);

///
void UnBindVertexBufferRaw(UINT streamNumber);

///  This function can modify stream number depending on 'instancing' state
void UnBindVertexBuffer(UINT streamNumber);

/// Enable hardware instancing for all streams from 0 to _lastGeomStream inclusive
void EnableHardwareInstancing(UINT _numInstances, UINT _lastGeomStream = 0, UINT _instanceStream = UINT_MAX);

///
void DisableHardwareInstancing();

bool InstancingEnabled();

///
void SetFVF(DWORD _fvf);

///
void DrawIndexedPrimitive(const DipDescriptor& _descr);

///
void DrawIndexedPrimitiveUP(const DipDescriptor& _descr, const WORD* pIndexData,
                            const void* pVertexStreamZeroData, UINT VertexStreamZeroStride);

///
void DrawPrimitive(const DipDescriptor& descr);

///
void DrawPrimitiveUP(const DipDescriptor& _descr, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride);

///
inline void BindVertexBuffer(unsigned int streamNumber, DXVertexBufferRef const &buffer, unsigned int stride, unsigned int offset = 0)
{
	BindVertexBuffer(streamNumber, Get(buffer), stride, offset);
}

///
template <class VBREF>
void BindVertexStream(unsigned int streamNumber, const VertexStreamT<VBREF> &vs)
{
	BindVertexBuffer(streamNumber, Get(vs.pVertexBuffer), vs.stride, vs.offset);
}

///
void BindIndexBuffer(IDirect3DIndexBuffer9* buffer);

///
inline void BindIndexBuffer(DXIndexBufferRef const &buffer) { BindIndexBuffer( Get(buffer) ); }
template<UINT elemSize>
inline void BindIndexBuffer(DXIndexBufferDynamicRef_<elemSize> const &buffer) { BindIndexBuffer( Get(buffer) ); }

///
void BindVertexDeclarationRaw(IDirect3DVertexDeclaration9 *pDecl);

// This function can modify declaration set depending on 'instancing' state
void BindVertexDeclaration(DXVertexDeclarationRef const &pDecl);

///
void BindVertexShader(IDirect3DVertexShader9 *shader);
inline void BindVertexShader(DXVertexShaderRef const & shader) { BindVertexShader( Get(shader) ); }

/// 
void BindPixelShader(IDirect3DPixelShader9 *shader);
inline void BindPixelShader(DXPixelShaderRef const & shader) { BindPixelShader( Get(shader) ); }

///
void BindTexture(unsigned int samplerIndex, const Texture* texture, bool bProtect = false);
void UnBindTexture(unsigned int samplerIndex);
void UnBindTexture(const Texture* texture); // searches all PS samplers

///

// general RT control
void BindRenderTarget(const Texture2DRef& pColorTexture);
void BindRenderTarget(const Texture2DRef& pColorTexture, const RenderSurfaceRef& pDepthSurface);
void BindRenderTargetDefault();
void SetDefaultRenderTarget(const DXSurfaceRef &pRT0, const DXSurfaceRef &pDepth);
void SetDefaultRenderTarget(const DXSurfaceRef &pRT0, const DXSurfaceRef &pRT1, const DXSurfaceRef &pDepth);
// precise RT control
void BindRenderTargetColor(unsigned int renderTargetIndex, IDirect3DSurface9* pColorSurface);
inline void BindRenderTargetColor(unsigned int renderTargetIndex, const DXSurfaceRef &pColorSurface)
{
  BindRenderTargetColor( renderTargetIndex, ::Get(pColorSurface) );
}

void BindRenderTargetDepth(IDirect3DSurface9* pDepthStencilSurface);
inline void BindRenderTargetDepth(const DXSurfaceRef &pDepthStencilSurface) { BindRenderTargetDepth( ::Get(pDepthStencilSurface) ); }

// viewport control
void SetMainViewport( int x, int y, int width, int height );
void GetMainViewport( int& x, int& y, int& width, int& height );
void ResetMainViewport();
void FixViewport(); // clip viewport size by depth-stencil's surface size

void SetUseMainViewport( bool _useViewport );
bool UseMainViewport();

///
void Release();

IDirect3DSurface9* GetRenderTarget(unsigned int renderTargetIndex);
IDirect3DSurface9* GetRenderTargetDepth();
int GetRenderTargetWidth();
int GetRenderTargetHeight();

void DumpScreenshot( const nstl::string& filename, bool keepAlpha );
int GetScreenshotCount();
byte* DumpScreenshotToMemory( int width, int height );

} // namespace SmartRenderer
} // namespace Render